import sys
from pathlib import Path

import pytest

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools import rename  # noqa: E402


@pytest.fixture(autouse=True)
def _restore_root():
    # rename.main(--root) repoints the shared clint/ledger ROOT at the test tree; later test files read it.
    root = rename.ROOT
    yield
    rename.set_root(root)


TYPES = """\
typedef struct A {
    s32 x;
    s32 y;
} A;
typedef struct B {
    s32 x;
} B;
#define AX(p) ((p)->x)
"""


def _tree(root: Path, files: dict) -> None:
    files = {"include/common.h": "typedef int s32;\ntypedef unsigned char u8;\n", **files}
    for rel, text in files.items():
        p = root / rel
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(text)


def _snapshot(root: Path) -> dict:
    return {p: p.read_bytes() for p in root.rglob("*") if p.is_file()}


def _run(root: Path, *args) -> int:
    return rename.main(["--root", str(root), *args])


def test_field_renames_only_that_struct_across_tus(tmp_path, capsys):
    _tree(tmp_path, {
        "include/types.h": TYPES,
        "src/global/one.c": '#include "common.h"\n#include "types.h"\n'
                            "s32 f(A *a, B *b) {\n    return a->x + b->x;\n}\n",
        "src/global/two.c": '#include "common.h"\n#include "types.h"\n'
                            "void g(A a, B *b) {\n    b->x = a.x;\n}\n",
    })
    assert _run(tmp_path, "field", "include/types.h", "A", "x", "count", "-j", "2") == 0
    assert "return a->count + b->x;" in (tmp_path / "src/global/one.c").read_text()
    assert "b->x = a.count;" in (tmp_path / "src/global/two.c").read_text()
    types = (tmp_path / "include/types.h").read_text()
    assert "typedef struct A {\n    s32 count;" in types and "typedef struct B {\n    s32 x;" in types
    assert "#define AX(p) ((p)->x)" in types
    assert "x→count" in capsys.readouterr().out


def test_field_dry_run_writes_nothing(tmp_path, capsys):
    _tree(tmp_path, {"include/types.h": TYPES,
                     "src/global/one.c": '#include "common.h"\n#include "types.h"\ns32 f(A *a) { return a->x; }\n'})
    before = _snapshot(tmp_path)
    assert _run(tmp_path, "field", "--dry-run", "include/types.h", "A", "x", "count", "-j", "1") == 0
    out = capsys.readouterr().out.splitlines()
    assert out == ["include/types.h:2:9 x→count", "src/global/one.c:3:25 x→count"]
    assert _snapshot(tmp_path) == before


def test_field_ref_inside_macro_aborts_without_writes(tmp_path):
    _tree(tmp_path, {
        "include/types.h": TYPES,
        "src/global/one.c": '#include "common.h"\n#include "types.h"\ns32 f(A *a) { return a->x; }\n',
        "src/global/two.c": '#include "common.h"\n#include "types.h"\ns32 g(A *a) { return AX(a); }\n',
    })
    before = _snapshot(tmp_path)
    assert _run(tmp_path, "field", "include/types.h", "A", "x", "count", "-j", "1") == 1
    assert _snapshot(tmp_path) == before


def test_field_refuses_existing_field(tmp_path):
    _tree(tmp_path, {"include/types.h": TYPES})
    assert _run(tmp_path, "field", "include/types.h", "A", "x", "y", "-j", "1") == 1


def _symtree(tmp_path):
    _tree(tmp_path, {
        "symbol_addrs.us.txt": "fooBar = 0x80600000; // type:func size:0x8\nlater = 0x80700000;\n",
        "src/global/a.c": '#include "common.h"\n#define PROTO_SKIP_fooBar\n'
                          "void fooBar(void) {}\n"
                          '#pragma GLOBAL_ASM("asm/global/nonmatchings/a/func_80600010.s")\n',
        "src/global/b.c": '#include "common.h"\nvoid fooBar(void);\nextern s32 D_80600000;\n'
                          "void g(void) { fooBar(); func_80600010(); D_80600000 = 1; }\n",
    })


def test_func_refuses_address_names(tmp_path):
    _symtree(tmp_path)
    before = _snapshot(tmp_path)
    for bad in ("actorTable5D0", "func_80600000", "sp1C", "arg0", "unk4", "var_v0"):
        assert _run(tmp_path, "func", "global", "fooBar", bad) == 1, bad
    assert _snapshot(tmp_path) == before
    assert rename.check_name("spawnActor") is None and rename.check_name("speed") is None


def test_func_renames_tokens_skip_define_and_symbol_line(tmp_path):
    _symtree(tmp_path)
    assert _run(tmp_path, "func", "global", "fooBar", "doThing") == 0
    a = (tmp_path / "src/global/a.c").read_text()
    b = (tmp_path / "src/global/b.c").read_text()
    assert "#define PROTO_SKIP_doThing\nvoid doThing(void) {}" in a
    assert "void doThing(void);\nextern s32 doThing;" in b  # D_<VRAM> alias follows the name
    syms = (tmp_path / "symbol_addrs.us.txt").read_text()
    assert syms.startswith("doThing = 0x80600000; // type:func size:0x8\n")


def test_func_adds_symbol_line_and_retargets_pragma(tmp_path):
    _symtree(tmp_path)
    assert _run(tmp_path, "func", "global", "func_80600010", "helper") == 0
    assert '#pragma GLOBAL_ASM("asm/global/nonmatchings/a/helper.s")' in (tmp_path / "src/global/a.c").read_text()
    assert (tmp_path / "symbol_addrs.us.txt").read_text().splitlines() == [
        "fooBar = 0x80600000; // type:func size:0x8", "helper = 0x80600010; // type:func", "later = 0x80700000;"]


def test_func_refuses_in_use_and_header_prototyped(tmp_path):
    _symtree(tmp_path)
    _tree(tmp_path, {"include/PR/os.h": "void osThing(void);\n",
                     "src/global/c.c": '#include "common.h"\nvoid osThing(void);\nvoid h(void) { osThing(); }\n'})
    before = _snapshot(tmp_path)
    assert _run(tmp_path, "func", "global", "fooBar", "later") == 1
    assert _run(tmp_path, "func", "global", "osThing", "osOther") == 1
    assert _snapshot(tmp_path) == before


def test_global_ref_inside_macro_aborts(tmp_path):
    _symtree(tmp_path)
    _tree(tmp_path, {"src/global/c.c": '#include "common.h"\nextern s32 later;\n#define L (later + 1)\n'})
    before = _snapshot(tmp_path)
    assert _run(tmp_path, "global", "global", "later", "laterValue") == 1
    assert _snapshot(tmp_path) == before


def test_local_renames_kr_param_and_refuses_collisions(tmp_path):
    _tree(tmp_path, {"src/global/k.c": '#include "common.h"\nextern s32 gCount;\n'
                                       "s32 f(arg0, arg1) s32 arg0; u8 arg1; {\n"
                                       "    s32 sp1C = arg0;\n    s32 count = 1;\n"
                                       "    return sp1C + arg1 + gCount + count;\n}\n"})
    path = "src/global/k.c"
    assert _run(tmp_path, "local", path, "f", "arg0", "gCount") == 1
    assert _run(tmp_path, "local", path, "f", "arg0", "count") == 1
    assert _run(tmp_path, "local", path, "f", "arg0", "base") == 0
    assert _run(tmp_path, "local", path, "f", "sp1C", "total") == 0
    text = (tmp_path / path).read_text()
    assert "s32 f(base, arg1) s32 base; u8 arg1; {\n    s32 total = base;\n" in text
    assert "return total + arg1 + gCount + count;" in text


def test_field_dry_run_lists_every_reference_and_flags_macros(tmp_path, capsys):
    _tree(tmp_path, {"include/types.h": TYPES,
                     "src/global/one.c": '#include "common.h"\n#include "types.h"\n'
                                         "s32 f(A *a) {\n    return AX(a) + a->x;\n}\n",
                     "src/global/two.c": '#include "common.h"\n#include "types.h"\n'
                                         "s32 g(A *a) {\n    return a->x;\n}\n"})
    before = _snapshot(tmp_path)
    assert _run(tmp_path, "field", "--dry-run", "include/types.h", "A", "x", "count", "-j", "1") == 1
    cap = capsys.readouterr()
    assert "src/global/one.c:4:23 x→count" in cap.out  # the plain reference after the macro one
    assert "src/global/two.c:4:15 x→count" in cap.out  # files after the macro one are still scanned
    assert "MACRO AX src/global/one.c:4:12" in cap.out
    assert "reference inside a macro" in cap.err
    assert _snapshot(tmp_path) == before


FOLD_SRC = """\
typedef struct P { s32 x; s32 y; } P;
extern P gPair;
extern s32 D_80700004;
s32 f(void) { return D_80700004 + 1; }
s32 g(void) { return D_80700004; }
"""


def _fold_tree(tmp_path, held=""):
    _tree(tmp_path, {
        "src/global/a.c": '#include "common.h"\n' + FOLD_SRC,
        "symbol_addrs.us.txt": "gPair = 0x80700000;\nD_80700004 = 0x80700004;\nother = 0x80700010;\n",
        ".scratch/cleanup-brief.md": "# Round 1\n- src: src/global/b.c\n" + held,
    })


def test_fold_replaces_refs_drops_extern_and_symbol(tmp_path, monkeypatch, capsys):
    _fold_tree(tmp_path)
    monkeypatch.setattr(rename, "VERIFY", lambda copy, src: 0)
    assert _run(tmp_path, "fold", "global", "D_80700004", "gPair.y") == 0
    text = (tmp_path / "src/global/a.c").read_text()
    assert "D_80700004" not in text and text.count("gPair.y") == 2
    assert "D_80700004" not in (tmp_path / "symbol_addrs.us.txt").read_text()


def test_fold_dry_run_and_mismatch_keep_everything(tmp_path, monkeypatch):
    _fold_tree(tmp_path)
    before = _snapshot(tmp_path)
    monkeypatch.setattr(rename, "VERIFY", lambda copy, src: 0)
    assert _run(tmp_path, "fold", "global", "D_80700004", "gPair.y", "--dry-run") == 0
    monkeypatch.setattr(rename, "VERIFY", lambda copy, src: 1)
    assert _run(tmp_path, "fold", "global", "D_80700004", "gPair.y") == 2
    after = {p: b for p, b in _snapshot(tmp_path).items() if ".scratch/fold" not in p.as_posix()}
    assert after == before


def test_fold_per_ref_keeps_mismatching_reference(tmp_path, monkeypatch):
    _fold_tree(tmp_path)
    # a fold matches only while the reference in g() keeps the label
    monkeypatch.setattr(rename, "VERIFY", lambda copy, src: 0 if "return D_80700004;" in open(Path(tmp_path) / copy).read() else 1)
    assert _run(tmp_path, "fold", "global", "D_80700004", "gPair.y", "--per-ref") == 2
    text = (tmp_path / "src/global/a.c").read_text()
    assert "return gPair.y + 1;" in text and "return D_80700004;" in text and "extern s32 D_80700004;" in text
    assert "D_80700004" in (tmp_path / "symbol_addrs.us.txt").read_text()


def test_fold_refuses_checked_out_file(tmp_path, monkeypatch):
    _fold_tree(tmp_path, held="- src: src/global/a.c\n")
    monkeypatch.setattr(rename, "VERIFY", lambda copy, src: 0)
    before = _snapshot(tmp_path)
    assert _run(tmp_path, "fold", "global", "D_80700004", "gPair.y") == 1
    assert _snapshot(tmp_path) == before


def _filetree(tmp_path):
    _tree(tmp_path, {
        "dk64.global.us.yaml": "segments:\n"
                               "      - [0x100, c, A1]\n"
                               "      - [0x200, asm, A1]\n"
                               "      - [0x300, c, B2]\n"
                               "      - [0x900, .data, A1] # see src/global/A1.c\n"
                               "      - [0x980, .data, B2]\n"
                               "      - { start: 0x9F0, type: .bss, vram: 0x80700000, name: A1 }\n",
        "Makefile": "CC := cc\nGLOBAL_G_FILES := A1 B2\n",
        "data_inc.us.txt": "# seg name vram size width file\nglobal sTable 0x80700100 0x10 1 src/global/A1.c\n",
        "src/global/A1.c": '#include "proto/global/A1.h"\nint f(int x) { return x; }\n',
        "src/global/B2.c": '#include "proto/global/A1.h"\n#include "proto/global/B2.h"\nint g(void) { return f(1); }\n',
        "AGENTS.md": "A1 lives in src/global/A1.c; its prototypes in include/proto/global/A1.h.\n",
        "include/proto/global/A1.h": "/* Generated by tools/protos.py gen from src/global/A1.c: do not edit. */\n"
                                     "#ifndef PROTO_GLOBAL_A1_H\n#define PROTO_GLOBAL_A1_H\nint f(int);\n#endif\n",
    })


def test_files_renames_tu_everywhere(tmp_path, capsys):
    _filetree(tmp_path)
    (tmp_path / "batch.txt").write_text("# global\nglobal A1 A1_alpha\n\n")
    assert _run(tmp_path, "files", str(tmp_path / "batch.txt"), "--no-gen") == 0
    assert (tmp_path / "src/global/A1_alpha.c").exists() and not (tmp_path / "src/global/A1.c").exists()
    assert (tmp_path / "src/global/A1_alpha.c").read_text().startswith('#include "proto/global/A1_alpha.h"\n')
    assert (tmp_path / "src/global/B2.c").read_text().startswith(
        '#include "proto/global/A1_alpha.h"\n#include "proto/global/B2.h"\n')
    assert (tmp_path / "dk64.global.us.yaml").read_text() == (
        "segments:\n"
        "      - [0x100, c, A1_alpha]\n"
        "      - [0x200, asm, A1]\n"
        "      - [0x300, c, B2]\n"
        "      - [0x900, .data, A1_alpha] # see src/global/A1_alpha.c\n"
        "      - [0x980, .data, B2]\n"
        "      - { start: 0x9F0, type: .bss, vram: 0x80700000, name: A1_alpha }\n")
    assert (tmp_path / "Makefile").read_text() == "CC := cc\nGLOBAL_G_FILES := A1_alpha B2\n"
    assert (tmp_path / "data_inc.us.txt").read_text().endswith("1 src/global/A1_alpha.c\n")
    assert (tmp_path / "AGENTS.md").read_text() == (
        "A1 lives in src/global/A1_alpha.c; its prototypes in include/proto/global/A1_alpha.h.\n")
    assert not (tmp_path / "include/proto/global/A1.h").exists()
    assert (tmp_path / "include/proto/global/A1_alpha.h").read_text() == (
        "/* Generated by tools/protos.py gen from src/global/A1_alpha.c: do not edit. */\n"
        "#ifndef PROTO_GLOBAL_A1_ALPHA_H\n#define PROTO_GLOBAL_A1_ALPHA_H\nint f(int);\n#endif\n")
    out = capsys.readouterr().out
    assert "MV src/global/A1.c src/global/A1_alpha.c" in out and out.rstrip().endswith("files: 1 renamed")


def test_files_refusals_write_nothing(tmp_path):
    _filetree(tmp_path)
    (tmp_path / "src/global/C3.c").write_text('#pragma GLOBAL_ASM("asm/global/nonmatchings/C3/h.s")\n')
    before = _snapshot(tmp_path)
    for row in ("global A1 alpha", "global A1 B2_x", "global C3 C3_asm", "global A1 A1_Alpha"):
        (tmp_path / "batch.txt").write_text(f"global B2 B2_beta\n{row}\n")
        before[tmp_path / "batch.txt"] = (tmp_path / "batch.txt").read_bytes()
        assert _run(tmp_path, "files", str(tmp_path / "batch.txt"), "--no-gen") == 1, row
        assert _snapshot(tmp_path) == before, row
