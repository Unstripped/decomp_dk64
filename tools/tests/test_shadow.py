import os
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools import shadow  # noqa: E402

HEADERS = {
    "common.h": "#define COMMON 1\n",
    "actor.h": '#include "common.h"\n#define ACTOR_REPO 1\n',
    "race.h": '#include "common.h"\n#include "actor.h"\n',
    "boss.h": '#include "actor.h"\n',
    "cutscene.h": '#include "boss.h"\n',
    "x/deep.h": '#include "../race.h"\n',
    "proto/global/a.h": '#include "actor.h"\n',  # no actor.h beside it: -I order reaches the shadow
}


@pytest.fixture
def root(tmp_path, monkeypatch):
    for rel, text in HEADERS.items():
        p = tmp_path / "include" / rel
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(text)
    a = tmp_path / ".scratch" / "A"
    a.mkdir(parents=True)
    (a / "file.c").write_text('#include "race.h"\nint x = ACTOR_PRIVATE;\n')
    monkeypatch.setattr(shadow, "ROOT", str(tmp_path))
    return tmp_path


def test_includers_of_a_shadowed_header_are_shadowed_transitively(root):
    (root / ".scratch" / "A" / "actor.h").write_text('#include "common.h"\n#define ACTOR_PRIVATE 1\n')
    assert shadow.shadowed(".scratch/A/file.c") == {"actor.h": ".scratch/A/actor.h"}
    assert shadow.includers({"actor.h"}) == ["boss.h", "cutscene.h", "race.h", "x/deep.h"]
    flags, _, extra, written = shadow.materialise(".scratch/A/file.c", [], "build/sh")
    assert flags == ["-I", "build/sh", "-I", ".scratch/A"] and extra == ["boss.h", "cutscene.h", "race.h", "x/deep.h"]
    assert written["build/sh/race.h"] == "include/race.h" and written["build/sh/actor.h"] == ".scratch/A/actor.h"
    assert (root / "build/sh/race.h").read_text() == HEADERS["race.h"]
    assert "ACTOR_PRIVATE" in (root / "build/sh/actor.h").read_text()


def test_shadow_dir_and_nothing_shadowed(root):
    flags, shadowed, _, _ = shadow.materialise(".scratch/A/file.c", [], "build/sh")
    assert (flags, shadowed) == ([], {}) and not (root / "build/sh").exists()
    d = root / ".scratch" / "A" / "shadow" / "proto" / "global"
    d.mkdir(parents=True)
    (d / "a.h").write_text("/* private */\n")
    (root / ".scratch/A/shadow/new.h").write_text("/* not in include/ */\n")
    flags, shadowed, extra, _ = shadow.materialise(".scratch/A/file.c", [".scratch/A/shadow"], "build/sh")
    assert shadowed == {"proto/global/a.h": ".scratch/A/shadow/proto/global/a.h"} and extra == []
    assert flags == ["-I", "build/sh", "-I", ".scratch/A", "-I", ".scratch/A/shadow"]
    fp = shadow.fingerprint(".scratch/A/file.c", [".scratch/A/shadow"])
    assert [x.split(":")[0] for x in fp] == [".scratch/A/shadow/new.h", ".scratch/A/shadow/proto/global/a.h"]


@pytest.mark.skipif(not (shutil.which("cc") or shutil.which("gcc")), reason="no host C preprocessor")
def test_nested_include_reaches_the_private_header(root):
    (root / ".scratch" / "A" / "actor.h").write_text('#include "common.h"\n#define ACTOR_PRIVATE 1\n')
    flags, _, _, _ = shadow.materialise(".scratch/A/file.c", [], "build/sh")
    cc = shutil.which("cc") or shutil.which("gcc")
    run = lambda fl: subprocess.run([cc, "-E", "-P", *fl, "-I", "include", ".scratch/A/file.c"],  # noqa: E731
                                    cwd=root, capture_output=True, text=True).stdout
    assert "int x = ACTOR_PRIVATE;" in run([])  # without the shadow race.h reaches include/actor.h
    assert "int x = 1;" in run(flags)
    assert os.path.exists(root / "build/sh/race.h")
