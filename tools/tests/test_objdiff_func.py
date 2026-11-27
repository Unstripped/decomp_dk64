import subprocess
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools import asmdiff_func, objdiff  # noqa: E402


def test_asm_differ_command_runs_the_function_limiting_wrapper_for_an_explicit_func():
    cmd = objdiff.asm_differ_command("b.o", "e.o", "foo", only_func=True)
    assert cmd[1:] == [objdiff.ASMDIFF_FUNC_PY, "-o", "-n", "-f", "b.o", "-F", "e.o", "--no-pager", "foo"]
    assert Path(objdiff.ASMDIFF_FUNC_PY) == REPO_ROOT / "tools" / "asmdiff_func.py"
    # no FUNC given: the first function is picked and diff.py prints it and everything after it, as before
    assert objdiff.asm_differ_command("b.o", "e.o", "foo", only_func=False)[1] == objdiff.DIFF_PY


def test_wrapper_adds_disassemble_only_to_the_functions_dump():
    flags = ["-d", "-rz", "-j", ".text"]
    assert asmdiff_func.function_flags(flags, "foo", "foo") == flags + ["--disassemble=foo"]
    assert asmdiff_func.function_flags(flags, None, "foo") == flags
    assert asmdiff_func.function_flags(flags, "bar", "foo") == flags


def test_objdump_fallback_diff_is_the_functions_only(monkeypatch):
    calls = []

    def check_output(cmd, **kw):
        calls.append(cmd)
        return (b"a\nb\n" if cmd[-1] == "e.o" else b"a\nc\n")

    monkeypatch.setattr(subprocess, "check_output", check_output)
    lines = list(objdiff.objdump_fallback_diff("b.o", "e.o", "foo"))
    assert [c[-1] for c in calls] == ["b.o", "e.o"]
    assert all("--disassemble=foo" in c for c in calls)
    assert "-b" in lines and "+c" in lines
    calls.clear()
    list(objdiff.objdump_fallback_diff("b.o", "e.o"))
    assert not any(a.startswith("--disassemble") for c in calls for a in c)
