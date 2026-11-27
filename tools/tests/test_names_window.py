import subprocess
import sys
from pathlib import Path

import pytest

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools import names_window  # noqa: E402


def result(rc=0, out="", err=""):
    return subprocess.CompletedProcess([], rc, out, err)


def test_carry_runs_once_per_file_and_prints_each_result(capsys):
    cmds = []

    def runner(cmd):
        cmds.append(cmd)
        return result(out="carry: skipped x\ncarried 3 events\n" if cmd[-1] == "src/a.c" else "")

    assert names_window.carry_files(["src/a.c", "src/b.c"], "abc123", "U1", runner) is None
    assert cmds == [["uv", "run", "tools/quality.py", "carry", "--rev", "abc123^", "--unit", "U1", f]
                    for f in ("src/a.c", "src/b.c")]
    assert capsys.readouterr().out == "carry src/a.c: carried 3 events\ncarry src/b.c: nothing\n"


def test_carry_stops_at_the_first_failure_and_names_what_is_left(capsys):
    seen = []

    def runner(cmd):
        seen.append(cmd[-1])
        return result(rc=-9 if cmd[-1] == "src/b.c" else 0, out="done\n", err="boom\n")

    files = ["src/a.c", "src/b.c", "src/c.c"]
    cmd, r, left = names_window.carry_files(files, "g", "U", runner)
    assert seen == ["src/a.c", "src/b.c"] and r.returncode == -9
    assert cmd[-1] == "src/b.c" and left == ["src/b.c", "src/c.c"]  # the failed file is not carried
    assert capsys.readouterr().out == "carry src/a.c: done\n"


def test_carry_failure_report(capsys):
    cmd = ["uv", "run", "tools/quality.py", "carry", "--rev", "g^", "--unit", "U", "src/b.c"]
    err = "".join(f"line {i}\n" for i in range(30))
    with pytest.raises(SystemExit) as ex:
        names_window.carry_failed(cmd, result(rc=3, err=err), ["src/b.c", "src/c.c"], "g", "U", header_carve=True)
    assert ex.value.code == 1
    out, e = capsys.readouterr()
    assert out == "NAMES_WINDOW_FAIL: carry (not yet carried: src/b.c src/c.c)\n"
    assert "carry failed: uv run tools/quality.py carry --rev 'g^' --unit U src/b.c\n" in e
    assert "exit code: 3\n" in e
    assert "line 29\n" in e and "line 10\n" in e and "line 9\n" not in e  # the last 20 lines
    assert "not yet carried (2): src/b.c src/c.c\n" in e
    assert "retry: uv run tools/quality.py carry --rev 'g^' --unit U src/b.c src/c.c\n" in e
    assert "not yet run: carry --header-carve\n" in e


def test_header_carve_failure_has_nothing_left(capsys):
    cmd = ["uv", "run", "tools/quality.py", "carry", "--rev", "g^", "--unit", "U", "--header-carve"]
    with pytest.raises(SystemExit):
        names_window.carry_failed(cmd, result(rc=1, err="bad\n"), [], "g", "U")
    out, e = capsys.readouterr()
    assert out == "NAMES_WINDOW_FAIL: carry --header-carve\n"
    assert "not yet carried" not in e and "not yet run" not in e and "exit code: 1\n" in e
