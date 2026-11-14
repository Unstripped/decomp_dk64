import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools import variants as v  # noqa: E402


def texts(gen, text):
    return [t for _, _, t in gen(text)]


def test_swap_mirrors_comparison():
    assert texts(v.gen_swap, "    if (a < b->c) {}") == ["    if (b->c > a) {}"]
    assert texts(v.gen_swap, "    if (x == 0x10 && p[i] >= -1) {} // FAKE: x < y") == [
        "    if (0x10 == x && p[i] >= -1) {} // FAKE: x < y", "    if (x == 0x10 && -1 <= p[i]) {} // FAKE: x < y"]


def test_swap_skips_tighter_binding_operands():
    assert texts(v.gen_swap, "    z = x << 2 < y;") == []  # (x << 2) < y: 2 is not an operand of <
    assert texts(v.gen_swap, "    z = a + b < c;") == []
    assert texts(v.gen_swap, "    if ((s32)a < b) {}") == []  # a cast binds tighter
    assert texts(v.gen_swap, "    if (!a == b) {}") == []
    assert texts(v.gen_swap, "    if (f(a) < b) {}") == []
    assert texts(v.gen_swap, "    if (a < b[0] + 1) {}") == []
    assert texts(v.gen_swap, '    if (a < b) { print("x"); }') == []  # string literal on the line
    assert texts(v.gen_swap, "#if A < B") == []


def test_float_suffix():
    assert texts(v.gen_float, "    x = 0.5f;") == ["    x = 0.5;"]
    assert texts(v.gen_float, "    x = 0.5;") == ["    x = 0.5f;"]
    assert texts(v.gen_float, "    x = 1.07;") == []  # not exact in f32


def test_width_variants():
    out = v.gen_width("    s16 i;")
    assert [t for _, _, t in out] == [f"    {w} i;" for w in ("s8", "u8", "u16", "s32", "u32")]
    assert v.gen_width("    s16 i, j;") == []


def test_declswap_swaps_adjacent_declarations():
    text = "void f(void) {\n    s32 a;\n    s32 b;\n    a = b;\n}"
    assert texts(v.gen_declswap, text) == ["void f(void) {\n    s32 b;\n    s32 a;\n    a = b;\n}"]


def test_variants_order_and_limit():
    text = "void f(void) {\n    s16 a;\n    s32 b;\n    if (a < b) {}\n    b = 0.5f;\n}"
    assert [r for r, _, _ in v.variants(text)] == ["swap", "float"] + ["width"] * 10 + ["declswap"]
    assert [r for r, _, _ in v.variants(text, ("swap",))] == ["swap"]
    assert len(v.variants(text, max_n=3)) == 3
