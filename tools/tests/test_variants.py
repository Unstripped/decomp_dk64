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
    assert [t for _, _, t in out] == [f"    {w} i;" for w in ("s8", "u8", "u16", "s32", "u32", "int", "unsigned int")]
    assert [t for _, _, t in v.gen_width("    unsigned int i = 0;")][-1] == "    int i = 0;"
    assert v.gen_width("    s16 i, j;") == []


def test_declswap_swaps_adjacent_declarations():
    text = "void f(void) {\n    s32 a;\n    s32 b;\n    a = b;\n}"
    assert texts(v.gen_declswap, text) == ["void f(void) {\n    s32 b;\n    s32 a;\n    a = b;\n}"]


def test_variants_order_and_limit():
    text = "void f(void) {\n    s16 a;\n    s32 b;\n    if (a < b) {}\n    b = 0.5f;\n}"
    assert [r for r, _, _ in v.variants(text)] == ["swap", "float"] + ["width"] * 14 + ["declswap"]
    assert [r for r, _, _ in v.variants(text, ("swap",))] == ["swap"]
    assert len(v.variants(text, max_n=3)) == 3


def test_truth_respells_whole_tests():
    assert texts(v.gen_truth, "    if (spawn != 0) {}") == ["    if (spawn) {}"]
    assert texts(v.gen_truth, "    if (p->a == 0 && b) {}") == ["    if (!p->a && b) {}", "    if (p->a == 0 && b != 0) {}"]
    assert texts(v.gen_truth, "    while (!q[i]) {}") == ["    while (q[i] == 0) {}"]
    assert texts(v.gen_truth, "    z = accept(a && x != 0);") == ["    z = accept(a && x);"]  # && reads only truth


def test_truth_skips_value_contexts():
    assert texts(v.gen_truth, "    if (accept(x != 0)) {}") == []  # call argument: 0/1 vs raw x
    assert texts(v.gen_truth, "    if (accept(x)) {}") == []
    assert texts(v.gen_truth, "    if ((x != 0) + y) {}") == []  # arithmetic paren
    assert texts(v.gen_truth, "    if ((s32)b) {}") == []  # cast
    assert texts(v.gen_truth, "    if (flags & x) {}") == []  # bitwise operand
    assert texts(v.gen_truth, "    if (a < x) {}") == []
    assert texts(v.gen_truth, "    if (1) {}") == []
    assert texts(v.gen_truth, "    x = (a != 0);") == []  # no condition on the line


def test_switch_from_if_else():
    t = "    if (n->k == -1) {\n        a();\n    } else {\n        b();\n    }"
    assert texts(v.gen_switch, t) == [
        "    switch (n->k) {\n        case -1:\n            a();\n            break;\n        default:\n            b();\n            break;\n    }"]


def test_switch_one_case_needs_return():
    assert texts(v.gen_switch, "    if (x == 1) {\n        a();\n        return;\n    }") == [
        "    switch (x) {\n        case 1:\n            a();\n            return;\n    }"]
    assert texts(v.gen_switch, "    if (x == 1) {\n        a();\n    }") == []  # falls through: not the same as a switch
    assert texts(v.gen_switch, "    if (x == 1) {\n        a();\n    } else if (y) {\n    }") == []


def test_switch_skips_bodies_with_break():
    assert texts(v.gen_switch, "        if (x == 1) {\n            break;\n        } else {\n            a();\n        }") == []
    assert texts(v.gen_switch, "        if (x == 1) {\n            a();\n        } else {\n            break;\n        }") == []


def test_branch_swaps_arms():
    t = "    if (x == 3) {\n        a();\n    } else {\n        b();\n    }"
    assert texts(v.gen_branch, t) == ["    if (x != 3) {\n        b();\n    } else {\n        a();\n    }"]
    assert texts(v.gen_branch, "    if (!p->f) {\n        a();\n    } else {\n        b();\n    }") == [
        "    if (p->f) {\n        b();\n    } else {\n        a();\n    }"]
    assert texts(v.gen_branch, "    if (a < b && c) {\n        a();\n    } else {\n        b();\n    }") == [
        "    if (!(a < b && c)) {\n        b();\n    } else {\n        a();\n    }"]


def test_branch_skips_chains_and_lone_ifs():
    assert texts(v.gen_branch, "    if (x) {\n        a();\n    }") == []
    assert texts(v.gen_branch, "    if (x) {\n        a();\n    } else if (y) {\n        b();\n    }") == []
    assert texts(v.gen_branch, "    } else if (x) {\n        a();\n    } else {\n        b();\n    }") == []


def test_arith_swaps_bounded_operands():
    assert texts(v.gen_arith, "    x = a + b->c;") == ["    x = b->c + a;"]
    assert texts(v.gen_arith, "    x = a * b + c;") == ["    x = b * a + c;"]
    assert texts(v.gen_arith, "    x = c + a * b;") == ["    x = c + b * a;"]
    assert texts(v.gen_arith, "    return a + b;") == ["    return b + a;"]


def test_arith_keeps_meaning():
    assert texts(v.gen_arith, "    x = c - a + b;") == []  # (c - a) + b
    assert texts(v.gen_arith, "    x = c / a * b;") == []  # (c / a) * b
    assert texts(v.gen_arith, "    x = -a + b;") == []
    assert texts(v.gen_arith, "    x = &a + b;") == []
    assert texts(v.gen_arith, "    x = a[i] * b[0];") == ["    x = b[0] * a[i];"]
    assert texts(v.gen_arith, "    x++; y += 2; u8 *p;") == []
    assert texts(v.gen_arith, "    x = (s32)a + b;") == []  # the cast binds a


def test_elem_rotates_element_spellings():
    assert texts(v.gen_elem, "    x = gTab[i].f;") == ["    x = (gTab + i)->f;", "    x = (&gTab[i])->f;"]
    assert texts(v.gen_elem, "    x = gTab[a ? b : c].f;")[0] == "    x = (gTab + (a ? b : c))->f;"
    assert texts(v.gen_elem, "    x = (gTab + i)->f; y = (&gTab[j])->g;") == [
        "    x = gTab[i].f; y = (&gTab[j])->g;", "    x = (gTab + i)->f; y = gTab[j].g;"]
    assert texts(v.gen_elem, "    x = p->arr[i].f; y = s.arr[j].g;") == []  # member arrays keep their path


def fn(*lines):
    return "\n".join(lines)


def test_splitlocal_splits_reused_local():
    text = "void f(void) {\n    s32 x;\n    s32 y;\n    x = a();\n    b(x);\n    x = c(); // FAKE: x reused\n    d(x);\n}"
    out = texts(v.gen_splitlocal, text)
    assert len(out) == 3  # decl slots 0, 1, 2
    assert out[2] == ("void f(void) {\n    s32 x;\n    s32 y;\n    s32 x_2;\n    x = a();\n    b(x);\n"
                      "    x_2 = c();\n    d(x_2);\n}")


def test_splitlocal_start_tag_names_local_alone_on_line():
    head = ("void f(void) {", "    s32 x;", "    s32 y;", "    x = a();", "    b(x);")
    assert texts(v.gen_splitlocal, fn(*head, "    x = c(); // FAKE: reuse", "    d(x);", "}")) == []
    assert texts(v.gen_splitlocal, fn(*head, "    x = c(); y = 1; // FAKE: x reused", "    d(x);", "}")) == []


def test_splitlocal_skips_compound_and_untagged():
    assert texts(v.gen_splitlocal, "void f(void) {\n    s32 x;\n    x = a();\n    x += c(); // FAKE: x\n}") == []
    assert texts(v.gen_splitlocal, "void f(void) {\n    s32 x;\n    x = a();\n    x = c();\n    d(x);\n}") == []


def test_unalias_removes_alias():
    text = "void f(T *p) {\n    T *q = p; // FAKE: alias\n    g(q);\n    h(q->a);\n}"
    assert texts(v.gen_unalias, text) == ["void f(T *p) {\n    g(p);\n    h(p->a);\n}"]


def test_unalias_needs_untagged_reader():
    # (e) only tagged lines read A: deleting the alias re-points the steer at B, the steer unchanged
    text = fn("void f(T *p) {", "    T *q = p; // FAKE: alias", "    if (q) {} // FAKE: dead test", "    g(p);", "}")
    assert texts(v.gen_unalias, text) == []
    text = fn("void f(T *p) {", "    T *q = p; // FAKE: alias", "    if (q) {} // FAKE: dead test", "    g(q);", "}")
    assert texts(v.gen_unalias, text) == [fn("void f(T *p) {", "    if (p) {} // FAKE: dead test", "    g(p);", "}")]


def test_unalias_skips_store_read_by_loop_step():
    # the for step reads q after the loop body stores it: respelling q there would read p every iteration
    text = fn("void f(T *p) {", "    T *q;", "    T *r;", "    q = p; // FAKE: alias", "    r = q;",
              "    for (i = 0; i < 4; i++, r = q) {", "        q = h(i);", "        g(r);", "    }", "}")
    assert texts(v.gen_unalias, text) == []


def test_splitlocal_skips_steer_only_local():
    # the split local would be read only by tagged lines: renaming a steer drops a tag, not a hack
    text = ("void f(void) {\n    s32 g;\n    g = a();\n    b(g);\n    g = m; // FAKE: g holds a0\n"
            "    if (g) {} // FAKE: dead test\n}")
    assert texts(v.gen_splitlocal, text) == []


def test_splitlocal_role_refined_in_place():
    # (a) a clamp, a lone if arm and a one-line conditional store refine x_2's role: the range runs through
    # them to d(); the unconditional x = e() begins x's next role
    text = fn("void f(void) {", "    s32 x;", "    x = a();", "    b(x);", "    x = c(); // FAKE: x reused",
              "    if (x > 9) {", "        x = 9;", "    }", "    if (k) {", "        x = 0;", "    }",
              "    if (m) x = 1;", "    d(x);", "    x = e();", "    g(x);", "}")
    assert texts(v.gen_splitlocal, text)[-1] == fn(
        "void f(void) {", "    s32 x;", "    s32 x_2;", "    x = a();", "    b(x);", "    x_2 = c();",
        "    if (x_2 > 9) {", "        x_2 = 9;", "    }", "    if (k) {", "        x_2 = 0;", "    }",
        "    if (m) x_2 = 1;", "    d(x_2);", "    x = e();", "    g(x);", "}")


def test_splitlocal_switch_case_merging_refines():
    # (a) a switch case whose value merges at d() refines the role; one read only inside its case begins a role
    text = fn("void f(s32 k) {", "    s32 x;", "    x = a();", "    b(x);", "    x = c(); // FAKE: x reused",
              "    switch (k) {", "    case 1:", "        x = 2;", "        break;", "    }", "    d(x);", "}")
    assert texts(v.gen_splitlocal, text)[-1] == fn(
        "void f(s32 k) {", "    s32 x;", "    s32 x_2;", "    x = a();", "    b(x);", "    x_2 = c();",
        "    switch (k) {", "    case 1:", "        x_2 = 2;", "        break;", "    }", "    d(x_2);", "}")
    text = fn("void f(s32 k) {", "    s32 x;", "    x = a();", "    b(x);", "    x = c(); // FAKE: x reused",
              "    d(x);", "    switch (k) {", "    case 1:", "        x = 2;", "        g(x);", "        break;", "    }", "}")
    assert texts(v.gen_splitlocal, text)[-1] == fn(
        "void f(s32 k) {", "    s32 x;", "    s32 x_2;", "    x = a();", "    b(x);", "    x_2 = c();",
        "    d(x_2);", "    switch (k) {", "    case 1:", "        x = 2;", "        g(x);", "        break;", "    }", "}")


def test_splitlocal_declaration_starts_only_new_roles():
    # (a) a tagged declaration splits at each store beginning a role: not the lone if arm `x = 0`, and an if/else
    # storing x in both arms is one store (its role starts at the then arm and runs through the else arm)
    text = fn("void f(s32 k) {", "    s32 x; // FAKE: x serves two roles", "    x = a();", "    if (k) {",
              "        x = 0;", "    }", "    b(x);", "    if (m) {", "        x = c();", "    } else {",
              "        x = d();", "    }", "    g(x);", "}")
    out = v.gen_splitlocal(text)
    assert [d for _, d, _ in out] == ["line 2: x -> new local x_2 from line 9 (decl slot 0)",
                                      "line 2: x -> new local x_2 from line 9 (decl slot 1)"]
    assert out[-1][2] == fn(
        "void f(s32 k) {", "    s32 x;", "    s32 x_2;", "    x = a();", "    if (k) {", "        x = 0;", "    }",
        "    b(x);", "    if (m) {", "        x_2 = c();", "    } else {", "        x_2 = d();", "    }", "    g(x_2);", "}")


def test_splitlocal_for_header_ends_and_starts_role():
    # (b) a `for (i = ...)` header begins a new role: the split stops before it, or starts at it; one whose
    # initialiser reads i continues the role
    text = fn("void f(void) {", "    s32 i;", "    i = a();", "    b(i);", "    i = c(); // FAKE: i reused", "    d(i);",
              "    for (i = 0; i < 4; i++) {", "        g(i);", "    }", "}")
    assert texts(v.gen_splitlocal, text)[-1] == fn(
        "void f(void) {", "    s32 i;", "    s32 i_2;", "    i = a();", "    b(i);", "    i_2 = c();", "    d(i_2);",
        "    for (i = 0; i < 4; i++) {", "        g(i);", "    }", "}")
    text = fn("void f(void) {", "    s32 i; // FAKE: i serves two roles", "    i = a();", "    b(i);",
              "    for (i = 0; i < 4; i++) {", "        g(i);", "    }", "}")
    assert texts(v.gen_splitlocal, text)[-1] == fn(
        "void f(void) {", "    s32 i;", "    s32 i_2;", "    i = a();", "    b(i);",
        "    for (i_2 = 0; i_2 < 4; i_2++) {", "        g(i_2);", "    }", "}")
    text = fn("void f(void) {", "    s32 i;", "    i = a();", "    b(i);", "    i = c(); // FAKE: i reused",
              "    for (i = i + 1; i < 4; i++) {", "        g(i);", "    }", "}")
    assert texts(v.gen_splitlocal, text)[-1] == fn(
        "void f(void) {", "    s32 i;", "    s32 i_2;", "    i = a();", "    b(i);", "    i_2 = c();",
        "    for (i_2 = i_2 + 1; i_2 < 4; i_2++) {", "        g(i_2);", "    }", "}")


def test_splitlocal_start_keeps_reading_old_value():
    # (c) the start's right-hand side keeps reading x; an untagged update `x = x + 1` refines the role in place
    text = fn("void f(void) {", "    s32 x;", "    x = a();", "    x = x * 2; // FAKE: x reused", "    b(x);", "}")
    assert texts(v.gen_splitlocal, text)[-1] == fn(
        "void f(void) {", "    s32 x;", "    s32 x_2;", "    x = a();", "    x_2 = x * 2;", "    b(x_2);", "}")
    text = fn("void f(void) {", "    s32 x;", "    x = a();", "    b(x);", "    x = c(); // FAKE: x reused",
              "    x = x + 1;", "    d(x);", "}")
    assert texts(v.gen_splitlocal, text)[-1] == fn(
        "void f(void) {", "    s32 x;", "    s32 x_2;", "    x = a();", "    b(x);", "    x_2 = c();",
        "    x_2 = x_2 + 1;", "    d(x_2);", "}")


def test_splitlocal_keeps_a_role_for_the_old_local():
    # (d) x must keep a store and an untagged read outside the split, else the split renames every use of x
    assert texts(v.gen_splitlocal, fn("void f(void) {", "    s32 x;", "    x = a(); // FAKE: x reused", "    b(x);",
                                      "}")) == []
    assert texts(v.gen_splitlocal, fn("void f(void) {", "    s32 x;", "    x = a();", "    if (x) {} // FAKE: dead",
                                      "    x = c(); // FAKE: x reused", "    d(x);", "}")) == []
    assert texts(v.gen_splitlocal, fn("void f(void) {", "    s32 x;", "    x = a();", "    x = 3; // FAKE: x reused",
                                      "    b(x);", "}")) == []


def test_splitlocal_skips_local_declared_again():
    text = fn("void f(void) {", "    s32 x;", "    x = a();", "    b(x);", "    x = c(); // FAKE: x reused", "    d(x);",
              "    {", "        s32 x;", "        x = e();", "        g(x);", "    }", "}")
    assert texts(v.gen_splitlocal, text) == []
