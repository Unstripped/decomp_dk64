"""Table and property tests for ``classify.classify_request`` / ``classify.classify_make``.

``classify_make(argv, cwd)`` takes make's arguments WITHOUT the leading ``make``
(the shim passes ``sys.argv[1:]``) and returns ``"none"``, ``("keyed", frozenset)``
or ``"exclusive"``.  ``classify_request(argv)`` takes the full command line
(including the command name) and returns ``"none"``, ``"shared"`` or ``"exclusive"``.

Invariants checked:
  * the documented table of make invocations (goals, dry-run/query forms, -C and
    cwd handling, -j/-s/-k bundling, -f, unknown options, ``--``);
  * classify_make never raises and always returns one of the three shapes, with
    keyed keys being a non-empty frozenset of normalised ``build*/**.o`` paths;
  * allowlisted assignments (OPT_FLAGS, CFLAGS, ASFLAGS, MIPSBIT, CC, IDO71 with = := ::= :::= ?= +=
    and no `$`/backtick in the value) and -s/--no-print-directory/-k never change the result, while
    any other assignment, `!=`, or an expanding value forces "exclusive" (also on dry-run forms);
  * request classification of permuter / splat / make / shell / helper scripts.
"""

import re

import pytest
from hypothesis import given, settings
from hypothesis import strategies as st

from classify import classify_make, classify_request

ROOT = "/dk64"


def keyed(*keys):
    return ("keyed", frozenset(keys))


# ---- classify_make: table ----------------------------------------------------------

EXCLUSIVE_CASES = [
    [],  # default `all`
    ["split"],
    ["expected"],
    ["clean"],
    ["progress"],
    ["setup"],
    ["NON_MATCHING=1"],
    ["build/src/a.o", "NON_MATCHING=1"],
    ["build/src/a.o", "build/dk64.us.z64"],  # ROM target mixed in
    ["build/dk64.us.z64"],
    ["build/src/a.c"],  # under build/ but not an object file
    ["src/a.o"],  # object file outside build/
    ["build/../x.o"],  # normalises out of build/
    ["-f", "Other.mk"],
    ["-f", "Other.mk", "build/src/a.o"],
    ["--file=Other.mk", "build/src/a.o"],
    ["--frobnicate"],
    ["--frobnicate", "build/src/a.o"],
    ["-j4"],  # jobs only, still no goal
    ["-j", "4"],
    ["--", "-n"],  # after `--`, `-n` is a goal, not a flag
    ["--", "split"],
    ["build/src/a.o", "VAR=1"],  # arbitrary variables can redirect outputs
    ["VAR=1", "build/src/a.o"],
    ["build/src/a.o", "V_0="],
    ["build/src/a.o", "BUILD_DIR=other"],
    ["build/src/a.o", "cflags=-g"],  # make variables are case-sensitive
    ["build/src/a.o", "CFLAGS2=-g"],
    ["build/src/a.o", "CFLAGS!=echo -g"],  # shell assignment
    ["build/src/a.o", "CFLAGS=$(X)"],  # expansion in the value
    ["build/src/a.o", "CFLAGS=$$"],
    ["build/src/a.o", "CC=`cc`"],
    ["-n", "CFLAGS=$(X)", "build/src/a.o"],  # expansion forces exclusive even on dry-run
    ["-n", "CC=`cc`"],
    ["build/other/a.o"],  # only src|asm|assets objects are keyable
    ["build/a.o"],
    ["build_nonmatching/other/a.o"],
    ["build/src/a.o", "build/other/b.o"],
    ["-n", "-f", "Other.mk"],  # makefile/eval/environment overrides beat dry-run
    ["-n", "--file=Other.mk", "build/src/a.o"],
    ["-n", "--makefile=Other.mk"],
    ["--makefile=Other.mk", "build/src/a.o"],
    ["-e", "build/src/a.o"],
    ["--environment-overrides", "build/src/a.o"],
    ["-E", "A=1", "build/src/a.o"],
    ["-n", "-E", "A=1"],
    ["--eval=A=1", "build/src/a.o"],
    ["-n", "--eval=A=1"],
    ["--eval", "A=1", "build/src/a.o"],
    ["-p"],  # prints the database but still runs the default goal
]

NONE_CASES = [
    ["-n", "-e"],  # -e only changes variable precedence; a dry run still runs no recipe
    ["-n", "-W", "src/a.c", "build/src/a.o"],
    ["-nW", "src/a.c", "build/src/a.o"],
    ["-W", "src/a.c", "-n", "build/src/a.o"],
    ["-n"],
    ["--dry-run"],
    ["--dry-run", "split"],
    ["--just-print", "clean"],
    ["--recon", "build/src/a.o"],
    ["-q", "x"],
    ["--question", "split"],
    ["--version"],
    ["-v"],
    ["--help"],
    ["-h"],
    ["-C", ".scratch/wt"],
    ["-C", ".scratch/wt", "split"],
    ["-C", "/dk64/.scratch/wt", "build/src/a.o"],
    ["-C", "/dk64/.scratch/wt"],
    ["-n", "VAR=1", "build/src/a.o"],  # plain assignments do not break dry-run
    ["-n", "NON_MATCHING=1"],
    ["-n", "CFLAGS=-g", "build/src/a.o"],
]


@pytest.mark.parametrize("argv", EXCLUSIVE_CASES, ids=lambda a: " ".join(a) or "<no args>")
def test_make_exclusive(argv):
    assert classify_make(argv, ROOT) == "exclusive"


@pytest.mark.parametrize("argv", NONE_CASES, ids=lambda a: " ".join(a))
def test_make_none(argv):
    assert classify_make(argv, ROOT) == "none"


KEYED_CASES = [
    (["build/src/a.o"], {"build/src/a.o"}),
    (["CFLAGS=-g", "build/src/a.o"], {"build/src/a.o"}),
    (["build/src/a.o", "CFLAGS=-g"], {"build/src/a.o"}),
    (["build/src/a.o", "OPT_FLAGS=-O2 -g3", "ASFLAGS=-x", "MIPSBIT=-mips2", "CC=cc", "IDO71=1"], {"build/src/a.o"}),
    (["build/src/a.o", "CFLAGS:=-g", "CFLAGS::=-g", "CFLAGS:::=-g", "CFLAGS?=-g", "CFLAGS+=-g"], {"build/src/a.o"}),
    (["build/assets/x.o"], {"build/assets/x.o"}),
    (["build_nonmatching/asm/x.o"], {"build_nonmatching/asm/x.o"}),
    (["./build/src/a.o", "build/asm/b.o"], {"build/src/a.o", "build/asm/b.o"}),
    (["build/src/../src/a.o"], {"build/src/a.o"}),
    (["build//src/a.o"], {"build/src/a.o"}),
    (["build/src/a.o", "build/src/a.o"], {"build/src/a.o"}),
    (["build_nonmatching/src/a.o"], {"build_nonmatching/src/a.o"}),
    (["build/src/a.o", "build_nonmatching/src/a.o"], {"build/src/a.o", "build_nonmatching/src/a.o"}),
    (["--", "build/src/a.o"], {"build/src/a.o"}),
    (["-s", "-k", "--no-print-directory", "build/src/a.o"], {"build/src/a.o"}),
    (["-j4", "build/src/a.o"], {"build/src/a.o"}),
    (["-j", "4", "build/src/a.o"], {"build/src/a.o"}),  # purely numeric arg is the jobs count
    (["-j", "build/src/a.o"], {"build/src/a.o"}),  # non-numeric: -j has no argument
    (["-sj4", "build/src/a.o"], {"build/src/a.o"}),
    (["-sj", "4", "build/src/a.o"], {"build/src/a.o"}),
    (["-kj4", "build/src/a.o"], {"build/src/a.o"}),
    (["--jobs=4", "build/src/a.o"], {"build/src/a.o"}),
    (["--jobs", "4", "build/src/a.o"], {"build/src/a.o"}),
    (["-I", "inc", "build/src/a.o"], {"build/src/a.o"}),  # option argument is not a goal
    (["-o", "x.c", "build/src/a.o"], {"build/src/a.o"}),
    (["-C", "/dk64", "build/src/a.o"], {"build/src/a.o"}),
    (["-C", ".", "build/src/a.o"], {"build/src/a.o"}),
]


@pytest.mark.parametrize("argv,keys", KEYED_CASES, ids=lambda v: " ".join(v) if isinstance(v, list) else "")
def test_make_keyed(argv, keys):
    assert classify_make(argv, ROOT) == ("keyed", frozenset(keys))


def test_make_keyed_result_shape():
    result = classify_make(["build/src/a.o"], ROOT)
    assert isinstance(result, tuple) and len(result) == 2
    assert result[0] == "keyed" and isinstance(result[1], frozenset)


# ---- classify_make: directory handling ---------------------------------------------


def test_make_from_scratch_worktree_cwd_is_none():
    assert classify_make([], "/dk64/.scratch/wt") == "none"
    assert classify_make(["build/src/a.o"], "/dk64/.scratch/wt") == "none"
    assert classify_make(["split"], "/dk64/.scratch/wt") == "none"


def test_make_from_subdir_without_C_is_none():
    assert classify_make([], "/dk64/src") == "none"
    assert classify_make(["build/src/a.o"], "/dk64/src") == "none"


def test_make_C_dotdot_from_subdir_is_root():
    assert classify_make(["-C", ".."], "/dk64/src") == "exclusive"
    assert classify_make(["-C", "..", "build/src/a.o"], "/dk64/src") == keyed("build/src/a.o")


def test_make_C_absolute_root_from_elsewhere():
    assert classify_make(["-C", "/dk64"], "/dk64/.scratch/wt") == "exclusive"
    assert classify_make(["-C", "/dk64", "build/src/a.o"], "/tmp") == keyed("build/src/a.o")


def test_make_C_relative_to_cwd():
    assert classify_make(["-C", "dk64"], "/") == "exclusive"
    assert classify_make(["-C", "wt"], "/dk64/.scratch") == "none"


def test_make_multiple_C_are_cumulative():
    # make: `-C a -C b` == `-C a/b`; relative ones chain.
    assert classify_make(["-C", "src", "-C", ".."], ROOT) == "exclusive"
    assert classify_make(["-C", ".scratch", "-C", "wt"], ROOT) == "none"
    assert classify_make(["-C", ".scratch", "-C", ".."], ROOT) == "exclusive"
    assert classify_make(["-C", "src", "-C", "..", "build/src/a.o"], ROOT) == keyed("build/src/a.o")


def test_make_C_attached_and_long_forms():
    assert classify_make(["-C.scratch/wt"], ROOT) == "none"
    assert classify_make(["--directory=.scratch/wt"], ROOT) == "none"
    assert classify_make(["--directory", ".scratch/wt"], ROOT) == "none"
    assert classify_make(["--directory=/dk64", "build/src/a.o"], "/tmp") == keyed("build/src/a.o")


def test_make_C_trailing_slash_and_dot_segments_normalise():
    assert classify_make(["-C", "/dk64/"], "/tmp") == "exclusive"
    assert classify_make(["-C", "/dk64/src/.."], "/tmp") == "exclusive"
    assert classify_make([], "/dk64/") == "exclusive"


def test_make_goals_are_relative_to_effective_directory():
    # goal is under build/ of the effective directory (/dk64), not of the cwd
    assert classify_make(["-C", "..", "build/src/a.o"], "/dk64/src") == keyed("build/src/a.o")
    assert classify_make(["-C", "/dk64/.scratch/wt", "build/src/a.o"], ROOT) == "none"


# ---- classify_make: properties -----------------------------------------------------

TOKENS = [
    "", "-", "--", "-n", "-q", "-s", "-k", "-j", "-j4", "-sj4", "-nW", "-W", "-C", "-f", "-h", "-v", "-p", "-e", "-E",
    "-C.", "-C..", "--dry-run", "--version", "--directory=..", "--file=x", "--makefile=x", "--eval=A=1", "--jobs=2",
    "--no-print-directory", "--frobnicate", "--", "4", "VAR=1", "NON_MATCHING=1", "CFLAGS=-g", "CC:=cc", "CFLAGS=$(X)",
    "CFLAGS!=echo", "=", "A=", "=B", "split", "clean", "build/src/a.o", "./build/src/a.o", "build/dk64.us.z64",
    "build_nonmatching/src/x.o", "build/assets/x.o", "build/other/x.o", "build/../x.o", "..", ".", "/dk64",
    ".scratch/wt", "src/a.c",
]
CWDS = ["/dk64", "/dk64/src", "/dk64/.scratch/wt", "/", "/tmp", "/dk64/"]


def assert_valid_shape(result):
    if result in ("none", "exclusive"):
        return
    assert isinstance(result, tuple) and len(result) == 2 and result[0] == "keyed", result
    keys = result[1]
    assert isinstance(keys, frozenset) and keys, result
    for key in keys:
        assert isinstance(key, str)
        assert re.fullmatch(r"(build|build_nonmatching)/(src|asm|assets)/.*\.o", key, re.DOTALL), key
        assert ".." not in key.split("/") and not key.startswith("./"), key


@settings(max_examples=500, deadline=None)
@given(
    st.lists(st.one_of(st.sampled_from(TOKENS), st.text(max_size=12)), max_size=10),
    st.one_of(st.sampled_from(CWDS), st.text(max_size=12).map(lambda s: "/" + s)),
)
def test_classify_make_never_raises_and_returns_valid_shape(argv, cwd):
    assert_valid_shape(classify_make(argv, cwd))


@settings(max_examples=300, deadline=None)
@given(st.lists(st.text(), max_size=6), st.text().map(lambda s: "/" + s))
def test_classify_make_total_on_arbitrary_text(argv, cwd):
    assert_valid_shape(classify_make(argv, cwd))


# Bases: (option "units" that precede goals, goals).  Units are never split by an insertion.
BASES = [
    ([], []),
    ([], ["split"]),
    ([], ["build/src/a.o"]),
    ([], ["build/src/a.o", "build/asm/b.o"]),
    ([], ["build/src/a.o", "build/dk64.us.z64"]),
    ([["-n"], ["-W", "src/a.c"]], ["build/src/a.o"]),
    ([["-nW", "src/a.c"]], ["build/src/a.o"]),
    ([["-q"]], ["x"]),
    ([["--version"]], []),
    ([["-C", ".scratch/wt"]], ["build/src/a.o"]),
    ([["-C", "src"], ["-C", ".."]], ["build/src/a.o"]),
    ([["-j", "4"]], ["build/src/a.o"]),
    ([["-f", "Other.mk"]], ["build/src/a.o"]),
]
KEYED_BASES = [
    ([], ["build/src/a.o"]),
    ([], ["build/src/a.o", "build/asm/b.o"]),
    ([], ["build_nonmatching/assets/c.o"]),
    ([["-s"]], ["build/src/a.o"]),
    ([["-j", "4"]], ["build/src/a.o"]),
    ([["-C", "src"], ["-C", ".."]], ["build/src/a.o"]),
]
DRY_BASES = [
    ([["-n"]], []),
    ([["--dry-run"]], ["split"]),
    ([["-n"], ["-W", "src/a.c"]], ["build/src/a.o"]),
    ([["-nW", "src/a.c"]], ["build/src/a.o"]),
]

ALLOWED_NAMES = ["OPT_FLAGS", "CFLAGS", "ASFLAGS", "MIPSBIT", "CC", "IDO71"]
ALLOWED_OPS = ["=", ":=", "::=", ":::=", "?=", "+="]
SAFE_VALUES = st.text(alphabet=st.characters(blacklist_characters="$`"), max_size=8)
UNSAFE_VALUES = st.builds(
    lambda a, c, b: a + c + b, st.text(max_size=4), st.sampled_from(["$", "`", "$(X)"]), st.text(max_size=4)
)


def assignment(names, ops, values):
    return st.builds(lambda n, o, v: n + o + v, names, ops, values)


ALLOWED_ASSIGNMENTS = assignment(st.sampled_from(ALLOWED_NAMES), st.sampled_from(ALLOWED_OPS), SAFE_VALUES)
OTHER_NAMES = st.one_of(
    st.sampled_from(["VAR", "V_0", "BUILD_DIR", "NON_MATCHING", "cflags", "CFLAGS2"]),
    st.text(alphabet="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_", min_size=1, max_size=6).map(lambda s: "V_" + s),
)
# Assignments the keyed path must refuse: any name outside the allowlist, `!=`, or `$`/backtick values.
DISALLOWED_ASSIGNMENTS = st.one_of(
    assignment(OTHER_NAMES, st.sampled_from(ALLOWED_OPS + ["!="]), SAFE_VALUES),
    assignment(st.sampled_from(ALLOWED_NAMES), st.sampled_from(ALLOWED_OPS), UNSAFE_VALUES),
    assignment(st.sampled_from(ALLOWED_NAMES), st.just("!="), SAFE_VALUES),
)
FLAGS = st.sampled_from(["-s", "--no-print-directory", "-k"])


def insert_tokens(base, insertions):
    """Insert (kind, token, n) items into base at unit boundaries; flags only before the first goal."""
    prefix, goals = base
    units = [list(u) for u in prefix] + [[g] for g in goals]
    first_goal = len(prefix)  # index of the first goal unit
    for kind, token, n in insertions:
        if kind == "flag":
            pos = n % (first_goal + 1)
            first_goal += 1
        else:  # assignments may appear anywhere, also after the goals
            pos = n % (len(units) + 1)
            if pos <= first_goal:
                first_goal += 1
        units.insert(pos, [token])
    return [t for unit in units for t in unit]


def base_argv(base):
    prefix, goals = base
    return [t for unit in prefix for t in unit] + goals


POSITIONS = st.integers(min_value=0)


@settings(max_examples=400, deadline=None)
@given(
    st.sampled_from(BASES),
    st.lists(
        st.one_of(
            st.tuples(st.just("assign"), ALLOWED_ASSIGNMENTS, POSITIONS),
            st.tuples(st.just("flag"), FLAGS, POSITIONS),
        ),
        max_size=8,
    ),
)
def test_allowlisted_assignments_and_harmless_flags_never_change_result(base, insertions):
    baseline = classify_make(base_argv(base), ROOT)
    assert classify_make(insert_tokens(base, insertions), ROOT) == baseline


@settings(max_examples=400, deadline=None)
@given(
    st.sampled_from(KEYED_BASES),
    st.lists(st.tuples(st.just("flag"), FLAGS, POSITIONS), max_size=3),
    DISALLOWED_ASSIGNMENTS,
    POSITIONS,
)
def test_disallowed_assignment_makes_keyed_base_exclusive(base, flags, bad, pos):
    assert classify_make(base_argv(base), ROOT)[0] == "keyed"
    argv = insert_tokens(base, flags + [("assign", bad, pos)])
    assert classify_make(argv, ROOT) == "exclusive"


@settings(max_examples=300, deadline=None)
@given(
    st.sampled_from(DRY_BASES),
    st.lists(
        st.tuples(
            st.just("assign"),
            assignment(
                st.one_of(OTHER_NAMES, st.sampled_from(ALLOWED_NAMES)), st.sampled_from(ALLOWED_OPS), SAFE_VALUES
            ),
            POSITIONS,
        ),
        max_size=5,
    ),
)
def test_dry_run_stays_none_with_any_plain_assignment(base, insertions):
    assert classify_make(base_argv(base), ROOT) == "none"
    assert classify_make(insert_tokens(base, insertions), ROOT) == "none"


@settings(max_examples=300, deadline=None)
@given(
    st.sampled_from(DRY_BASES),
    assignment(
        st.one_of(OTHER_NAMES, st.sampled_from(ALLOWED_NAMES)), st.sampled_from(ALLOWED_OPS), UNSAFE_VALUES
    ),
    POSITIONS,
)
def test_dry_run_with_expansion_in_assignment_value_is_exclusive(base, bad, pos):
    assert classify_make(insert_tokens(base, [("assign", bad, pos)]), ROOT) == "exclusive"


# ---- classify_request --------------------------------------------------------------

REQUEST_CASES = [
    # permuter runs hold no lock
    (["python3", "tools/permute.py", "run", "d"], "none"),
    (["python3", "tools/permute.py", "run"], "none"),
    (["python3", "tools/permute.py", "run", "d", "--jobs", "4"], "none"),
    (["tools/permute.py", "run", "d"], "none"),
    (["tools/permute.py", "run"], "none"),
    (["env", "A=B", "python3", "tools/permute.py", "run", "d"], "none"),
    # other permute.py subcommands touch shared state
    (["python3", "tools/permute.py", "setup", "d"], "shared"),
    (["python3", "tools/permute.py", "setup"], "shared"),
    (["tools/permute.py", "setup", "d"], "shared"),
    # splat rewrites the shared tree
    (["python3", "-m", "splat", "split", "x.yaml"], "exclusive"),
    (["python3", "-m", "splat", "split", "x.yaml", "--verbose"], "exclusive"),
    (["splat", "split", "x.yaml"], "exclusive"),
    # everything else is shared (make upgrades via the shim)
    (["sh", "-c", "python3 -m splat split x.yaml"], "shared"),
    (["make"], "shared"),
    (["make", "split"], "shared"),
    (["make", "build/src/a.o"], "shared"),
    (["make", "-C", ".scratch/wt"], "shared"),
    (["tools/fdiff.sh", "func_80001234"], "shared"),
    (["tools/fdiff.sh", "-a", "b"], "shared"),
    (["tools/objdiff.sh", "src/a.c"], "shared"),
    (["ls", "-la"], "shared"),
    (["env", "X=Y", "ls"], "shared"),
    (["bash", "-lc", "echo hi"], "shared"),
    (["python3", "tools/other.py"], "shared"),
]


@pytest.mark.parametrize("argv,expected", REQUEST_CASES, ids=lambda v: " ".join(v) if isinstance(v, list) else v)
def test_classify_request_table(argv, expected):
    assert classify_request(argv) == expected


REQUEST_TOKENS = TOKENS + ["python3", "-m", "splat", "tools/permute.py", "run", "make", "sh", "-c", "env"]


@settings(max_examples=300, deadline=None)
@given(st.lists(st.one_of(st.sampled_from(REQUEST_TOKENS), st.text(max_size=10)), min_size=1, max_size=8))
def test_classify_request_total(argv):
    assert classify_request(argv) in ("none", "shared", "exclusive")
