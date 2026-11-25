import json
import os
import subprocess
import sys
from pathlib import Path

import pytest

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools import cwarn  # noqa: E402

OUT = """\
cfe: Warning 712: src/global/x.c, line 119: illegal combination of pointer and integer
                                 a = (s32)b;
 ------------------^
cfe: Warning 709: src/global/x.c, line 119: incompatible pointer type assignment
                                 a = (s32)b;
 --------------------------^
cc: Warning: -mips3 should not be used for ucode 32-bit compiles
cfe: Warning 712: src/global/x.c, line 120: illegal combination of pointer and integer
         c = d;
 ------------^
cfe: Warning 712: src/global/x.c, line 120: illegal combination of pointer and integer
         c = d;
 ------------^
cfe: Warning 709: include/actor.h, line 7: incompatible pointer type assignment
"""


def test_parse():
    w = lambda code, path, line, col, msg: dict(code=code, path=path, line=line, col=col, msg=msg)  # noqa: E731
    p712, p709 = "illegal combination of pointer and integer", "incompatible pointer type assignment"
    assert cwarn.parse(OUT) == [
        w(712, "src/global/x.c", 119, 19, p712),
        w(709, "src/global/x.c", 119, 27, p709),
        w(712, "src/global/x.c", 120, 13, p712),
        w(712, "src/global/x.c", 120, 13, p712),
        w(709, "include/actor.h", 7, -1, p709),
    ]


def _ratchet(tmp_path, before, after):
    b, a = tmp_path / "b.json", tmp_path / "a.json"
    b.write_text(json.dumps(before))
    a.write_text(json.dumps(after))
    cwarn.main(["ratchet", str(b), str(a)])


def test_ratchet_rise_fails(tmp_path, capsys):
    with pytest.raises(SystemExit) as ex:
        _ratchet(tmp_path, {"src/a.c": 2, "src/b.c": 1}, {"src/a.c": 3, "src/b.c": 0})
    assert ex.value.code == 1
    assert "ROSE src/a.c: 2 -> 3" in capsys.readouterr().out


def test_ratchet_new_file_passes(tmp_path, capsys):
    _ratchet(tmp_path, {"src/a.c": 2}, {"src/a.c": 1, "src/n.c": 4})
    out = capsys.readouterr().out
    assert "new src/n.c: 4" in out and "warnings OK (2 -> 5)" in out


def test_concurrent_misses_keep_their_inputs(tmp_path, monkeypatch):
    monkeypatch.setattr(cwarn, "ROOT", str(tmp_path))
    monkeypatch.setattr(cwarn, "SCRATCH", str(tmp_path / ".scratch" / "cwarn"))
    monkeypatch.setattr(cwarn, "_static", {"key": ("makefile", "include")})
    item = [(str(tmp_path / "src" / "global" / "x.c"), "int x;\n", None)]
    seen, depth = [], []

    def run_jobs(jobs):
        depth.append(1)
        if len(depth) == 1:
            cwarn.collect(item)  # another process misses the same key and finishes first
        seen.append((tmp_path / jobs[0]["input"]).read_text())
        return [{"rc": 0, "out": ""}]

    monkeypatch.setattr(cwarn, "run_jobs", run_jobs)
    assert cwarn.collect(item) == [[]]
    assert seen == ["int x;\n", "int x;\n"]


def test_copy_compiles_with_its_shadow_headers(tmp_path, monkeypatch):
    monkeypatch.setattr(cwarn, "ROOT", str(tmp_path))
    monkeypatch.setattr(cwarn.shadow_headers, "ROOT", str(tmp_path))
    monkeypatch.setattr(cwarn, "SCRATCH", str(tmp_path / ".scratch" / "cwarn"))
    monkeypatch.setattr(cwarn, "_static", {"key": ("makefile", "include")})
    (tmp_path / "include").mkdir()
    (tmp_path / "include" / "actor.h").write_text("#define A 0\n")
    (tmp_path / "include" / "race.h").write_text('#include "actor.h"\n')
    a = tmp_path / ".scratch" / "A"
    a.mkdir(parents=True)
    (a / "x.c").write_text('#include "race.h"\n')
    item = [(".scratch/A/x.c", None, "src/global/x.c")]
    seen = []

    def run_jobs(jobs):
        seen.extend(jobs)
        out = jobs[0]["shadow"].split()[1] if "shadow" in jobs[0] else "include"
        return [{"rc": 0, "out": f"cfe: Warning 709: {out}/race.h, line 1: m\n"}]

    monkeypatch.setattr(cwarn, "run_jobs", run_jobs)
    assert cwarn.collect(item)[0][0]["path"] == "include/race.h"
    assert "shadow" not in seen[0]  # nothing shadowed: make's own flags
    (a / "actor.h").write_text("#define A 1\n")  # shadows include/actor.h, so race.h is shadowed too
    ws = cwarn.collect(item)[0]
    assert len(seen) == 2 and seen[1]["shadow"].split()[2:] == ["-I", ".scratch/A"]
    assert ws[0]["path"] == "include/race.h"  # the unchanged includer, under its include/ path


def test_rev_compile_links_through_the_container_when_the_host_cannot(tmp_path, monkeypatch):
    """No symlink privilege (Windows): the container makes the export tree's asm/assets links, and the
    stage is removed links first (rmtree cannot remove a container-made link)."""
    monkeypatch.setattr(cwarn, "ROOT", str(tmp_path))
    monkeypatch.setattr(cwarn, "SCRATCH", str(tmp_path / ".scratch" / "cwarn"))
    monkeypatch.setattr(cwarn, "_static", {"key": ("makefile", "include")})
    (tmp_path / "include").mkdir()
    (tmp_path / "include" / "s.h").write_text("int s;\n")
    for args in (["init", "-q"], ["add", "-A"], ["-c", "user.email=t@example.com", "-c", "user.name=t",
                                                 "-c", "commit.gpgsign=false", "commit", "-qm", "a"]):
        subprocess.run(["git", *args], cwd=tmp_path, check=True, capture_output=True)
    made, seen = [], []

    def no_symlink(*a, **k):
        raise OSError(1314, "A required privilege is not held by the client")

    def container_symlink(target, link):
        made.append(target)
        os.mkdir(link)  # stand-in for the container's link: unlink may not remove it, rmdir does

    def run_jobs(jobs):
        seen.extend(p.name for p in (tmp_path / jobs[0]["cwd"]).iterdir())
        return [{"rc": 0, "out": ""}]

    monkeypatch.setattr(cwarn.os, "symlink", no_symlink)
    monkeypatch.setattr(cwarn, "container_symlink", container_symlink)
    monkeypatch.setattr(cwarn, "run_jobs", run_jobs)
    assert cwarn.collect([("src/global/x.c", "int x;\n", None)], rev="HEAD") == [[]]
    assert made == ["../../../../../asm", "../../../../../assets"]
    assert {"asm", "assets", "include"} <= set(seen)
    assert list((tmp_path / ".scratch" / "cwarn" / "in").iterdir()) == []
