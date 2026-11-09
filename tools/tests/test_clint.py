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
