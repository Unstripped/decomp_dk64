import os
import re
import sys
from pathlib import Path
import pytest

# Ensure repository root is on sys.path so tools.permute can be imported
REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools.permute import strip_other_fns


def old_strip_other_fns(source: str, keep_fn: str) -> str:
    """Old strip_other_fns from commit HEAD before fix."""
    result = ""
    remain = source
    kr_decl_pat = r"\s*(?:[a-zA-Z0-9_* \t,()]+;\s*)*"
    fn_regex = re.compile(
        r"^([a-zA-Z0-9_* \t]+?)\b(\w+)\s*\(([^;{}]*?)\)" + kr_decl_pat + r"\{",
        re.M,
    )
    control_flow = {"if", "while", "for", "switch", "catch"}
    while True:
        m = fn_regex.search(remain)
        if not m:
            result += remain
            break
        fn_name = m.group(2)
        if fn_name in control_flow or "#" in m.group(1):
            result += remain[:m.end()]
            remain = remain[m.end():]
            continue
        start_idx = m.end() - 1
        level = 1
        i = start_idx + 1
        n = len(remain)
        while i < n and level > 0:
            if remain[i] == "{":
                level += 1
            elif remain[i] == "}":
                level -= 1
            i += 1
        if fn_name == keep_fn or fn_name.startswith("PERM"):
            result += remain[:i]
        else:
            proto = remain[:m.end(3) + 1].rstrip() + ";"
            result += proto + "\n"
        remain = remain[i:]
    return result


def test_indented_macro_continuation_regression():
    """An indented continuation line of a multi-line macro expansion inside another

    function must not be mistaken for a function header, and the kept function must
    survive intact.
    """
    synthetic_src = """void other_fn(void) {
    foo();
}

#define GBI_MACRO(a) \\
    gSPDisplayList(a, \\
        dl)

int target_fn(int a) {
    return a + 1;
}
"""
    # Confirm old implementation failed (target function body was stripped into a prototype)
    old_out = old_strip_other_fns(synthetic_src, "target_fn")
    assert "return a + 1;" not in old_out

    # Confirm new implementation passes (target function survives intact with its body)
    new_out = strip_other_fns(synthetic_src, "target_fn")
    assert "return a + 1;" in new_out
    assert "int target_fn(int a) {" in new_out
    assert "void other_fn(void);" in new_out


def test_indented_macro_inside_function_regression():
    """An indented macro continuation ending in { inside another function does not corrupt

    the kept function.
    """
    synthetic_src = """void
other_fn(void) {
    SOME_MACRO(
        gSPDisplayList(dl,
            other_dl) {
                inner_body();
            }
    );
}

int target_fn(int a) {
    return a + 1;
}
"""
    # On the old implementation, other_fn was corrupted because the inner macro was treated as a function
    old_out = old_strip_other_fns(synthetic_src, "other_fn")
    assert "inner_body();" not in old_out

    # On new implementation, other_fn survives intact
    new_out = strip_other_fns(synthetic_src, "other_fn")
    assert "inner_body();" in new_out
    assert "int target_fn(int a);" in new_out
