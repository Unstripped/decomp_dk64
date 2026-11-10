import subprocess
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(REPO_ROOT / "tools"))

import clint  # noqa: E402

BASE = """#include "common.h"
void f(void) {
    s32 x;
    x = 0;
    if (x) {}
}
"""


def uninit_cli(copy, base):
    return subprocess.run([sys.executable, str(REPO_ROOT / "tools" / "clint.py"), "uninit", str(copy), "--base", str(base)],
                          capture_output=True, text=True)


def test_uninit_base_flags_new_uninitialised_read(tmp_path):
    base = tmp_path / "base.c"
    base.write_text(BASE)
    same = tmp_path / "same.c"
    same.write_text(BASE)
    cut = tmp_path / "cut.c"
    cut.write_text(BASE.replace("    x = 0;\n", ""))
    r = uninit_cli(cut, base)
    assert r.returncode == 1, r.stdout + r.stderr
    assert "NEW UNINIT" in r.stdout and " f x" in r.stdout
    r = uninit_cli(same, base)
    assert r.returncode == 0, r.stdout + r.stderr
    assert "NEW UNINIT" not in r.stdout


def test_uninit_default_error_warnings_and_parse_errors(tmp_path):
    # critter/0: a default-error -Wint-conversion in the warnings-mode parse made clang skip the
    # base's analysis, so its pre-existing reads looked new; only the uninit warnings are enabled now
    head = "void g(void *p);\nvoid h(s32 v) {\n    g(%s);\n}\nvoid f(void)"
    conv = tmp_path / "conv.c"
    conv.write_text(BASE.replace("void f(void)", head % "v").replace("    x = 0;\n", ""))
    fixed = tmp_path / "fixed.c"
    fixed.write_text(BASE.replace("void f(void)", head % "(void *)v").replace("    x = 0;\n", ""))
    r = uninit_cli(fixed, conv)
    assert r.returncode == 0, r.stdout + r.stderr
    assert f"UNINIT {fixed}:" in r.stdout and "NEW UNINIT" not in r.stdout
    # a real parse error before f still hides its reads: unknown, not clean
    broken = tmp_path / "broken.c"
    broken.write_text(BASE.replace("void f(void)", "void h(void) {\n    undeclared = 1;\n}\nvoid f(void)")
                      .replace("    x = 0;\n", ""))
    r = uninit_cli(fixed, broken)
    assert r.returncode == 3, r.stdout + r.stderr
    assert f"UNKNOWN {broken}: 1 error(s)" in r.stdout and "undeclared" in r.stdout
    assert f"UNINIT {fixed}:" in r.stdout and "NEW UNINIT" not in r.stdout
    assert uninit_cli(broken, broken).returncode == 3
    r = subprocess.run([sys.executable, str(REPO_ROOT / "tools" / "clint.py"), "scan", str(broken), str(conv)],
                       capture_output=True, text=True)
    assert f"{broken} errors=1 werrors=1 functions=2" in r.stdout and "  werror: " in r.stdout
    assert f"{conv} errors=0 werrors=0 functions=2" in r.stdout


def test_uninit_base_survives_local_renames(tmp_path):
    # F9450 round 5: renaming m2c locals already read uninitialised in the base (sp7C -> x) is not new
    fn = ('#include "common.h"\nvoid f(void) {\n    s32 %(a)s;\n    s32 %(b)s;\n%(init)s'
          '    if (%(a)s) {}\n    if (%(b)s) {}\n}\n')
    base = tmp_path / "base.c"
    base.write_text(fn % dict(a="sp7C", b="sp78", init="    sp78 = 1;\n"))
    renamed = tmp_path / "renamed.c"
    renamed.write_text(fn % dict(a="x", b="y", init="    y = 1;\n"))
    r = uninit_cli(renamed, base)
    assert r.returncode == 0, r.stdout + r.stderr
    assert "RENAMED UNINIT" in r.stdout and " f x (base sp7C)" in r.stdout and "NEW UNINIT" not in r.stdout
    # the same renames plus a genuinely new uninitialised read of y in that function
    worse = tmp_path / "worse.c"
    worse.write_text(fn % dict(a="x", b="y", init=""))
    r = uninit_cli(worse, base)
    assert r.returncode == 1, r.stdout + r.stderr
    assert " f x (base sp7C)" in r.stdout and "NEW UNINIT" in r.stdout and " f y" in r.stdout.split("NEW UNINIT")[1]
    # a retyped local is not matched by position: its read stays new
    retyped = tmp_path / "retyped.c"
    retyped.write_text(fn.replace("    s32 %(a)s;", "    u8 %(a)s;") % dict(a="x", b="y", init="    y = 1;\n"))
    r = uninit_cli(retyped, base)
    assert r.returncode == 1 and "NEW UNINIT" in r.stdout, r.stdout + r.stderr


HEADER = """typedef struct Fix {
    s32 unk0;
    char pad4[0xC];
    f32 unk10;
} Fix;
"""


def layout(tmp_path, new_header):
    (tmp_path / "old").mkdir()
    (tmp_path / "new").mkdir()
    (tmp_path / "old" / "fix.h").write_text(HEADER)
    (tmp_path / "new" / "fix.h").write_text(new_header)
    old = clint.records(clint.clang_args() + [f"-I{tmp_path / 'old'}"], "fix.h")
    new = clint.records(clint.clang_args() + [f"-I{tmp_path / 'new'}"], "fix.h")
    assert "Fix" in old
    return clint.layout_diff(old, new)


def test_layout_rejects_appended_field(tmp_path):
    diffs = layout(tmp_path, HEADER.replace("    f32 unk10;\n", "    f32 unk10;\n    void *unk14;\n"))
    assert any(d.startswith("Fix size") for d in diffs)


def test_layout_accepts_named_padding_at_same_offset(tmp_path):
    assert layout(tmp_path, HEADER.replace("    char pad4[0xC];\n", "    s32 unk4;\n    char pad8[0x8];\n")) == []

def test_layout_accepts_array_over_same_bytes(tmp_path):
    assert layout(tmp_path, HEADER.replace("    s32 unk0;\n    char pad4[0xC];\n", "    s32 unk0[4];\n")) == []



def test_layout_rejects_shifted_field(tmp_path):
    diffs = layout(tmp_path, HEADER.replace("char pad4[0xC]", "char pad4[0x10]"))
    assert "Fix unk10 offset 0x10 -> 0x14" in diffs


def test_metrics_punned_scalar_only(tmp_path):
    c = tmp_path / "p.c"
    c.write_text('#include "common.h"\ntypedef struct A { s32 x; } A;\ntypedef struct B { s32 y; } B;\n'
                 "f32 g; A a;\ns32 f(void) {\n    B *b = (B *)&a;\n    return *(s32 *)&g + b->y;\n}\n")
    m = clint.metrics(str(c))["f"]
    assert m["punned"] == 1
    assert [(line, kind) for line, kind, _ in m["untagged"]] == [(7, "punned-cast")]
