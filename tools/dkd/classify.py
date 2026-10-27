"""Lock classification for dkd: pure functions, no I/O (stdlib only, Python 3.9 compatible).

Two entry points:

``classify_request(argv)``
    Lock class of a whole ``tools/dk <cmd>`` job: ``"none"``, ``"shared"`` or ``"exclusive"``.

``classify_make(argv, cwd)``
    What the ``make`` shim must hold for one ``make`` invocation (``argv`` excludes the program
    name): ``"none"``, ``"exclusive"`` or ``("keyed", frozenset_of_goal_paths)`` where the goal
    paths are normalised relative to the repo root ``/dk64`` (``./build/src/a.o`` and
    ``/dk64/build/src/a.o`` both become ``build/src/a.o``).

Invariant shared by both: the cheap answers (``"none"``, ``"shared"``, ``("keyed", ..)``) are only
returned when the invocation is positively recognised as safe; anything unparseable, unknown or
surprising degrades to the stronger lock (``"exclusive"`` for make, ``"shared"`` for requests,
``"exclusive"`` for splat).  A wrong ``"exclusive"`` only costs parallelism; a wrong ``"none"``
or ``"keyed"`` can corrupt shared outputs.

GNU make 4.3 command-line syntax (the container ships exactly this version) is parsed the way
glibc ``getopt_long`` + make's ``decode_switches`` do, see ``_parse_make_argv``.
"""
import posixpath
import re
import shlex
from typing import FrozenSet, List, Optional, Tuple, Union

ROOT = "/dk64"

NONE = "none"
SHARED = "shared"
EXCLUSIVE = "exclusive"
KEYED = "keyed"

MakeClass = Union[str, Tuple[str, FrozenSet[str]]]

# ---------------------------------------------------------------------------------------------
# make option table (GNU make 4.3 `switches[]` in main.c, verified against `make --help`).
# ---------------------------------------------------------------------------------------------
_NO, _REQ, _OPT = "none", "required", "optional"

# (canonical key, short chars, long names, argument mode).  Aliases share one key.
_OPTIONS = (
    ("ignored", "bm", (), _NO),
    ("always-make", "B", ("always-make",), _NO),
    ("directory", "C", ("directory",), _REQ),
    ("d", "d", (), _NO),
    ("debug", "", ("debug",), _OPT),
    ("environment-overrides", "e", ("environment-overrides",), _NO),
    ("eval", "E", ("eval",), _REQ),
    ("file", "f", ("file", "makefile"), _REQ),
    ("help", "h", ("help",), _NO),
    ("ignore-errors", "i", ("ignore-errors",), _NO),
    ("include-dir", "I", ("include-dir",), _REQ),
    ("jobs", "j", ("jobs",), _OPT),
    ("jobserver", "", ("jobserver-auth", "jobserver-fds"), _REQ),
    ("keep-going", "k", ("keep-going",), _NO),
    ("check-symlink-times", "L", ("check-symlink-times",), _NO),
    ("load-average", "l", ("load-average", "max-load"), _OPT),
    ("just-print", "n", ("just-print", "dry-run", "recon"), _NO),
    ("old-file", "o", ("old-file", "assume-old"), _REQ),
    ("output-sync", "O", ("output-sync",), _OPT),
    ("print-data-base", "p", ("print-data-base",), _NO),
    ("question", "q", ("question",), _NO),
    ("no-builtin-rules", "r", ("no-builtin-rules",), _NO),
    ("no-builtin-variables", "R", ("no-builtin-variables",), _NO),
    ("silent", "s", ("silent", "quiet"), _NO),
    ("no-silent", "", ("no-silent",), _NO),
    ("no-keep-going", "S", ("no-keep-going", "stop"), _NO),
    ("touch", "t", ("touch",), _NO),
    ("trace", "", ("trace",), _NO),
    ("version", "v", ("version",), _NO),
    ("print-directory", "w", ("print-directory",), _NO),
    ("no-print-directory", "", ("no-print-directory",), _NO),
    ("what-if", "W", ("what-if", "new-file", "assume-new"), _REQ),
    ("warn-undefined-variables", "", ("warn-undefined-variables",), _NO),
)

_SHORT = {}  # type: dict
_LONG = {}  # type: dict
for _key, _shorts, _longs, _mode in _OPTIONS:
    for _c in _shorts:
        _SHORT[_c] = (_key, _mode)
    for _name in _longs:
        _LONG[_name] = (_key, _mode)

_DIGITS = "0123456789"


class _MakeCmdline:
    """Result of parsing a make command line."""

    def __init__(self) -> None:
        self.keys = set()  # type: set          # canonical keys of every option seen
        self.directories = []  # type: List[str]  # -C / --directory arguments in order
        self.assignments = []  # type: List[Tuple[str, str, str]]  # (name, operator, value)
        self.goals = []  # type: List[str]


def _long_lookup(name: str) -> Optional[Tuple[str, str]]:
    """glibc getopt_long long-option lookup: exact match, else unique (or alias-only) prefix."""
    if name in _LONG:
        return _LONG[name]
    found = None
    for full, spec in _LONG.items():
        if full.startswith(name):
            if found is None:
                found = spec
            elif found != spec:  # different option (key or argument mode): ambiguous
                return None
    return found


def _parse_assignment(arg: str) -> Optional[Union[Tuple[str, str, str], str]]:
    """Classify a non-option word: ``None`` = goal, tuple = variable definition,
    ``"bad"`` = contains ``=`` but is neither a well-formed definition nor a plain goal."""
    index = arg.find("=")
    if index < 0:
        return None
    left, value = arg[:index], arg[index + 1:]
    operator = "="
    for symbol in (":::", "::", ":", "+", "?", "!"):
        if left.endswith(symbol):
            operator = symbol + "="
            left = left[: -len(symbol)]
            break
    name = left.strip()
    if not name or ":" in name or any(c.isspace() for c in name):
        return "bad"
    return (name, operator, value)


def _parse_make_argv(argv: List[str]) -> Optional[_MakeCmdline]:
    """Parse like ``getopt_long`` (options permuted among operands, ``--`` ends options).

    Returns None for anything make would reject or that we cannot model faithfully (unknown or
    ambiguous option, missing option argument, malformed operand); callers treat that as the
    conservative class.
    """
    out = _MakeCmdline()
    operands = []  # type: List[str]
    n = len(argv)
    i = 0
    only_operands = False
    while i < n:
        arg = argv[i]
        i += 1
        if only_operands or arg == "-" or not arg.startswith("-"):
            operands.append(arg)
            continue
        if arg == "--":
            only_operands = True
            continue
        if arg.startswith("--"):
            body = arg[2:]
            name, eq, attached = body.partition("=")
            spec = _long_lookup(name)
            if spec is None:
                return None
            key, mode = spec
            value = None  # type: Optional[str]
            if mode == _NO:
                if eq:
                    return None
            elif mode == _REQ:
                if eq:
                    value = attached
                elif i < n:
                    value = argv[i]
                    i += 1
                else:
                    return None
            else:  # optional: only `--opt=value` binds an argument ...
                if eq:
                    value = attached
                elif key == "jobs" and i < n and all(c in _DIGITS for c in argv[i]):
                    i += 1  # ... except make swallows a following all-digit word for -j/--jobs
                elif key == "load-average" and i < n and argv[i][:1] and (argv[i][0] in _DIGITS or argv[i][0] == "."):
                    i += 1  # ... and a following word starting with a digit or '.' for -l
            out.keys.add(key)
            if key == "directory":
                out.directories.append(value or "")
            continue
        # short option bundle
        word = arg[1:]
        pos = 0
        while pos < len(word):
            char = word[pos]
            pos += 1
            spec = _SHORT.get(char)
            if spec is None:
                return None
            key, mode = spec
            out.keys.add(key)
            if mode == _NO:
                continue
            rest = word[pos:]
            if mode == _REQ:
                if rest:
                    value = rest
                elif i < n:
                    value = argv[i]
                    i += 1
                else:
                    return None
                if key == "directory":
                    out.directories.append(value)
            else:
                if not rest:
                    if key == "jobs" and i < n and all(c in _DIGITS for c in argv[i]):
                        i += 1
                    elif key == "load-average" and i < n and argv[i][:1] and (argv[i][0] in _DIGITS or argv[i][0] == "."):
                        i += 1
            break  # an option taking (or possibly taking) an argument consumes the word's rest
    for operand in operands:
        parsed = _parse_assignment(operand)
        if parsed is None:
            out.goals.append(operand)
        elif parsed == "bad":
            return None
        else:
            out.assignments.append(parsed)
    return out


def _effective_dir(cwd: str, directories: List[str]) -> Optional[str]:
    """Directory make ends up in after applying every -C in order (each relative to the last).

    Lexical (no symlink resolution; this module does no I/O).  Returns None when the result
    cannot be determined: relative ``cwd``, empty ``-C`` (make fails on chdir("")), or a
    ``~``-leading argument (make expands it against $HOME, which we cannot see).
    """
    if not cwd.startswith("/"):
        return None
    current = posixpath.normpath(cwd)
    for directory in directories:
        if not directory or directory.startswith("~"):
            return None
        current = posixpath.normpath(posixpath.join(current, directory))
    return current


# Goals that keep a build keyed: object files whose implicit rule has no shared prerequisite.
#
# Makefile re-check (object rules, Makefile lines ~202-219): the only rules that produce a
# `$(BUILD_DIR)/**.o` are the pattern rules `$(BUILD_DIR)/%.o: %.s`, `: %.c` (plain and the
# asm-processor static-pattern variant) and `: %.bin`.  Each has exactly ONE prerequisite, the
# source file itself, and the recipe writes only `$@` (after `mkdir -p $(dir $@)`).  Nothing .o
# depends on a generated shared file (no .ld, undefined_syms, ELF, expected/, ...).  The one way
# a `.o` goal can still reach shared outputs is when the stem path happens to be a make TARGET:
# `build/bin/segments/x.o` has prerequisite `bin/segments/x.bin`, which the `bin/segments/%.bin`
# rule (re)generates, and `build/build/boot.o` would need `build/boot.bin`, i.e. a full link.
# Hence only stems under the split/source roots (src/, asm/, assets/) -- which no rule
# generates -- are keyed; every other `.o` goal is EXCLUSIVE.
#
# Deviation from "build/**/*.o": goals outside src|asm|assets are exclusive (see above).
_OBJECT_GOAL = re.compile(r"(?:build|build_nonmatching)/(?:src|asm|assets)/[^/].*\.o")
_BAD_GOAL_CHARS = re.compile(r"[\s%*?\[\]$:;#|\\`=]")

# Command-line variables that only tune the compile of the goal; they cannot change which
# files a `.o` rule reads or writes.  Anything else (BUILD_DIR, NON_MATCHING, VERSION, SHELL,
# MAKE, ...) can re-point or re-shape rules => EXCLUSIVE.  `!=` always runs a shell at parse time.
_KEYED_SAFE_VARS = frozenset(["OPT_FLAGS", "CFLAGS", "ASFLAGS", "MIPSBIT", "CC", "IDO71"])
_KEYED_SAFE_OPERATORS = frozenset(["=", ":=", "::=", ":::=", "?=", "+="])

# Options that read or run arbitrary makefile code (so even `-n` may execute `$(shell ...)`).
_ALTERNATE_MAKEFILE_KEYS = frozenset(["file", "eval"])


def _object_goal(goal: str) -> Optional[str]:
    """Normalised repo-relative path if ``goal`` is a keyed-safe object file, else None."""
    if not goal or goal.endswith("/") or _BAD_GOAL_CHARS.search(goal):
        return None
    path = posixpath.normpath(posixpath.join(ROOT, goal))
    if not path.startswith(ROOT + "/"):
        return None
    relative = path[len(ROOT) + 1:]
    if _OBJECT_GOAL.fullmatch(relative) is None:
        return None
    return relative


def classify_make(argv: List[str], cwd: str) -> MakeClass:
    """Classify one ``make`` invocation (``argv`` without the program name) run in ``cwd``.

    * unparseable / unknown option                                 -> "exclusive"
    * ``-v``/``--version``/``-h``/``--help`` (make exits at once)  -> "none"
    * effective directory (``cwd`` then each ``-C``) != /dk64      -> "none"
      (worktree builds under /dk64/.scratch/... have their own tree)
    * assignment value containing ``$`` or a backtick, or ``-f``/``--eval`` (alternate makefile
      code runs even under ``-n``)                                -> "exclusive"
    * ``-n``/``--just-print``/``--dry-run``/``--recon``, ``-q``/``--question`` -> "none"
      (no recipe runs; ``$(MAKE)`` recipe lines run as dry-run sub-makes)
    * no goals (default ``all``) or any goal that is not a keyed-safe object file -> "exclusive"
    * ``-e``, a non-whitelisted variable assignment (notably ``NON_MATCHING=``/``BUILD_DIR=``),
      or a ``!=`` operator                                         -> "exclusive"
    * otherwise                                                    -> ("keyed", frozenset(goals))

    Residual risk: sub-makes started by ``$(MAKE)`` under an outer ``-n`` get ``n`` through the
    MAKEFLAGS environment variable, not argv, so this argv-only classifier sees them as real
    builds and asks for the stronger lock (harmless over-locking, never under-locking).
    """
    cmdline = _parse_make_argv(list(argv))
    if cmdline is None:
        return EXCLUSIVE
    keys = cmdline.keys
    directory = _effective_dir(cwd, cmdline.directories)
    if directory is None:
        return EXCLUSIVE
    if "version" in keys or "help" in keys:
        return NONE
    if directory != ROOT:
        return NONE
    for name, operator, value in cmdline.assignments:
        if "$" in name or "$" in value or "`" in value:
            return EXCLUSIVE
    if keys & _ALTERNATE_MAKEFILE_KEYS:
        return EXCLUSIVE
    if "just-print" in keys or "question" in keys:
        return NONE
    if "environment-overrides" in keys or not cmdline.goals:
        return EXCLUSIVE
    for name, operator, value in cmdline.assignments:
        if name not in _KEYED_SAFE_VARS or operator not in _KEYED_SAFE_OPERATORS:
            return EXCLUSIVE
    objects = set()
    for goal in cmdline.goals:
        relative = _object_goal(goal)
        if relative is None:
            return EXCLUSIVE
        objects.add(relative)
    return (KEYED, frozenset(objects))


# ---------------------------------------------------------------------------------------------
# classify_request
# ---------------------------------------------------------------------------------------------
#
# "none" is reserved for `tools/permute.py run`.  Why that is safe to leave unlocked (verified
# by reading tools/permute.py `cmd_run`, `cmd_setup`'s generated compile.sh, and the
# decomp-permuter sources in the image, src/main.py, src/compiler.py, src/preprocess.py):
#
# What a RUNNING permuter reads from the shared /dk64 tree:
#   * tools/permute.py itself (once, at interpreter start);
#   * only the input directory `.scratch/permuter/<seg>_<FUNC>/` (base.c, target.o, compile.sh,
#     settings.toml, function.txt), all produced earlier by `permute.py setup`;
#   * `include/` -- indirectly: compile.sh is `<cc> <cflags> "$1" -o "$3"` with cflags holding the
#     relative `-I include`, resolved against the permuter's cwd (/dk64).  It is consulted only
#     if an `#include` survives in base.c.  setup runs `cpp -E -P` over the whole TU, so base.c
#     has none, and the permuter's own preprocessing pass is `cpp -P -nostdinc`.  So include/
#     is read only if a user hand-edits base.c to add an #include.
#   It never reads build/, asm/, src/, assets/, bin/ or expected/, and never invokes make.  The
#   compilers/objdump/permuter live in the image (/opt/ido*, /opt/decomp-permuter, binutils);
#   its temp .c/.o files go to /tmp, which is private per request.
# What it writes: `<dir>/output-<score>-<n>/{source.c,score.txt,diff.txt}` inside .scratch/, a
#   gitignored directory that make/split/expected/clean never touch.
# Residual risk of running it unlocked:
#   1. A hand-added #include in base.c resolves against include/ while some exclusive job (a
#      checkout/merge under a lease) rewrites headers: that candidate's compile can fail or use
#      mixed headers.  Permuter output is only a search hint and must pass the normal gates, so
#      this cannot corrupt shared outputs.
#   2. Deleting .scratch/ (e.g. `git clean -fdx`, `rm -rf .scratch`) mid-run makes the run fail
#      or lose output; again no shared output is affected.
#   3. `setup`/`best` are NOT exempt: setup shells out to `make -n` and reads asm/ and src/.
#   4. Only a directly invoked permuter is "none"; wrappers (`timeout ... permute.py run`,
#      `sh -c`) are "shared" and hold the lock for the whole search -- invoke it directly and
#      use `--seconds` for a wall-clock limit.
#
# splat rewrites asm/, assets/ and the linker scripts of the shared tree -> "exclusive" for any
# splat invocation (even `--help`: conservative and rare).  Everything else is "shared"; `make`
# invocations are upgraded by the make shim.

_PYTHON = re.compile(r"python(?:\d+(?:\.\d+)*)?")
_PERMUTE_SCRIPTS = frozenset(["tools/permute.py", ROOT + "/tools/permute.py"])
_ENV_FLAG_CHARS = frozenset("i0v")


def _strip_env(argv: List[str]) -> Optional[List[str]]:
    """Remove leading ``env [options] [NAME=value ...]`` wrappers; None if not understood."""
    args = list(argv)
    while args and posixpath.basename(args[0]) == "env":
        i = 1
        while i < len(args):
            arg = args[i]
            if arg == "--":
                i += 1
                break
            if arg == "-":  # historic spelling of -i
                i += 1
            elif arg in ("-u", "--unset"):
                i += 2
            elif arg.startswith("--unset=") or (arg.startswith("-u") and not arg.startswith("--")):
                i += 1
            elif arg in ("--ignore-environment", "--null", "--debug"):
                i += 1
            elif arg in ("-S", "--split-string") or arg.startswith("--split-string=") or (
                arg.startswith("-S") and not arg.startswith("--")
            ):
                if arg in ("-S", "--split-string"):
                    if i + 1 >= len(args):
                        return None
                    text, i = args[i + 1], i + 2
                elif arg.startswith("--split-string="):
                    text, i = arg[len("--split-string="):], i + 1
                else:
                    text, i = arg[2:], i + 1
                try:
                    args = args[:1] + shlex.split(text) + args[i:]
                except ValueError:
                    return None
                i = 1
            elif arg.startswith("-") and not arg.startswith("--") and set(arg[1:]) <= _ENV_FLAG_CHARS:
                i += 1
            elif arg.startswith("-"):
                return None  # -C/--chdir/-P/unknown: the command's relative paths may change
            else:
                break
        while i < len(args) and "=" in args[i]:
            i += 1
        if i > len(args):
            return None
        args = args[i:]
    return args


def _python_target(args: List[str]) -> Optional[Tuple[str, str, List[str]]]:
    """Parse python's own options. Returns (kind, value, remaining args) with kind
    ``"module"`` (-m) or ``"script"``; None for ``-c``/stdin/no target (opaque -> shared)."""
    i = 0
    n = len(args)
    while i < n:
        arg = args[i]
        i += 1
        if arg == "--":
            return ("script", args[i], args[i + 1:]) if i < n else None
        if arg == "-" or not arg.startswith("-"):
            return ("script", arg, args[i:]) if arg != "-" else None
        if arg.startswith("--"):
            continue  # --version, --help, ...
        word = arg[1:]
        pos = 0
        while pos < len(word):
            char = word[pos]
            pos += 1
            if char == "c":
                return None
            if char in "mWX":
                rest = word[pos:]
                if rest:
                    value = rest
                elif i < n:
                    value = args[i]
                    i += 1
                else:
                    return None
                if char == "m":
                    return ("module", value, args[i:])
                break
    return None


def _is_splat_script(path: str) -> bool:
    return posixpath.basename(path) == "splat"


def classify_request(argv: List[str]) -> str:
    """Lock class of a whole ``tools/dk <argv>`` job: "none", "shared" or "exclusive".

    * ``tools/permute.py run ...`` (as ``python[3] [opts] [./]tools/permute.py run``, the script
      itself, or behind ``env [opts] [NAME=value ...]``)                       -> "none"
    * splat on the shared tree (``python[3] -m splat ...``, ``splat ...``)      -> "exclusive"
    * everything else, including ``sh -c ...`` and ``make``                      -> "shared"
    """
    args = _strip_env(list(argv))
    if not args:
        return SHARED
    command = args[0]
    base = posixpath.basename(command)
    if _is_splat_script(command):
        return EXCLUSIVE
    if posixpath.normpath(command) in _PERMUTE_SCRIPTS:
        return NONE if args[1:2] == ["run"] else SHARED
    if _PYTHON.fullmatch(base):
        target = _python_target(args[1:])
        if target is None:
            return SHARED
        kind, value, rest = target
        if kind == "module":
            return EXCLUSIVE if value == "splat" or value.startswith("splat.") else SHARED
        if _is_splat_script(value):
            return EXCLUSIVE
        if posixpath.normpath(value) in _PERMUTE_SCRIPTS:
            return NONE if rest[:1] == ["run"] else SHARED
    return SHARED
