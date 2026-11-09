import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools import rename  # noqa: E402

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
