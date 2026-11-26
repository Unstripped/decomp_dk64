#!/usr/bin/env python3
"""Shadow headers for compiling a private copy against private versions of include/ headers
(stdlib only; tools/fdiff.sh and `tools/cwarn.py list --as` use it), and the host-portability
helpers every host-side tool imports from here (`posix`, `dk_argv`, `script_argv`, below).

A copy shadows `include/<rel>` with `<copy dir>/<rel>` (cpp searches the includer's directory
first) or with `<DIR>/<rel>` of a shadow dir (`--shadow DIR`, ahead of `-I include`). cpp resolves
a quote include of an include/ header in that header's own directory first, so an unchanged
include/ header quote-including a shadowed one (race.h and boss.h include "actor.h") would still
reach the repo's version: every such includer is shadowed too, unchanged, transitively.

  python3 tools/shadow.py COPY [--no-beside] [--shadow DIR]... --out OUT
      writes OUT (the shadowed headers plus their unchanged includers, at their include/ paths) and
      prints the flags to put ahead of `-I include`: `-I OUT -I <copy dir>` when an include/ header
      is shadowed (the copy dir for headers include/ lacks), then `-I DIR` per DIR; prints nothing
      when neither applies. A note naming the shadowed headers goes to stderr. --no-beside: COPY is
      the src file itself (tools/fdiff.sh `<src> <src>`, `cwarn.py list --as SRC SRC`): only the DIRs
      shadow (the *.h beside it are make's own headers, never shadows) and no `-I <copy dir>`.
"""
import argparse
import hashlib
import os
import re
import shutil
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
QUOTE_INCLUDE = re.compile(r'^[ \t]*#[ \t]*include[ \t]*"([^"]+)"', re.M)


# ---------------------------------------------------------------- host portability
# A no-op on macOS/Linux; on a Windows host, repo-relative strings keep `/` and the repo's
# `#!` scripts get spawned through an interpreter, since CreateProcess runs neither.

def posix(path):
    """PATH with `/` separators: the form of a repo-relative path that becomes a ledger key, a
    container argument, generated text or a `"/..."` substring filter."""
    return str(path).replace(os.sep, "/")


def dk_argv(*args):
    """argv of `tools/dk ARGS...` for this checkout: what tools/dk execs (its dkd client), run
    with this Python."""
    return [sys.executable, os.path.join(ROOT, "tools", "dkd", "client.py"), *args]


def interpreter(script):
    """argv prefix that runs SCRIPT (ROOT-relative or absolute) through the program its `#!` line
    names (`env PROG`: PROG), found on PATH by name: `shutil.which` keeps PATH order, where
    Windows' CreateProcess would search System32 (whose bash.exe is the WSL launcher) first.
    [] when SCRIPT has no `#!` line (a binary)."""
    with open(os.path.join(ROOT, script), "rb") as f:
        line = f.readline().decode("utf-8", "replace")
    words = line[2:].split() if line.startswith("#!") else []
    if words and os.path.basename(words[0]) == "env":
        words = words[1:]
    if not words:
        return []
    prog = os.path.basename(words[0])
    return [shutil.which(prog) or prog, *words[1:]]


def script_argv(script, *args):
    """argv that runs the repo shell script SCRIPT (ROOT-relative, run with cwd ROOT, or absolute)
    with ARGS: the script itself where the OS honours its `#!` line, else (Windows) through
    `interpreter`."""
    if os.name != "nt":
        return [script, *args]
    return [*interpreter(script), script, *args]


# ---------------------------------------------------------------- shadow headers


def include_files():
    """include/-relative paths of every file under include/."""
    base = os.path.join(ROOT, "include")
    return {posix(os.path.relpath(os.path.join(d, f), base)) for d, _, fs in os.walk(base) for f in fs}


def shadowed(copy, dirs=(), beside=True):
    """{include/-relative path: ROOT-relative source} of the include/ headers COPY's directory
    (unless not BESIDE) or a DIRS entry shadows (the copy's directory first, then DIRS in order)."""
    out = {}
    for rel in sorted(include_files()):
        for d in ((os.path.dirname(copy),) if beside else ()) + tuple(dirs):
            p = os.path.join(d, rel)
            if os.path.isfile(os.path.join(ROOT, p)):
                out[rel] = posix(os.path.normpath(p))
                break
    return out


def includers(rels):
    """Sorted include/ headers outside RELS that quote-include one of RELS, or such an includer,
    from their own directory (transitively)."""
    files = include_files()
    by_target = {}
    for h in files:
        with open(os.path.join(ROOT, "include", h), encoding="utf-8", errors="replace") as f:
            text = f.read()
        for name in QUOTE_INCLUDE.findall(text):
            target = posix(os.path.normpath(os.path.join(os.path.dirname(h), name)))
            if target in files:
                by_target.setdefault(target, set()).add(h)
    seen, todo = set(rels), list(rels)
    while todo:
        for h in by_target.get(todo.pop(), ()):
            if h not in seen:
                seen.add(h)
                todo.append(h)
    return sorted(seen - set(rels))


def materialise(copy, dirs, out, beside=True):
    """Write OUT for COPY (ROOT-relative paths) and return (`-I` flags, shadowed map, includers,
    {OUT path: source} of every header written). BESIDE false: COPY is the src file itself, shadowed
    by DIRS only, and its directory gets no `-I`."""
    shadow = shadowed(copy, dirs, beside)
    shutil.rmtree(os.path.join(ROOT, out), ignore_errors=True)
    flags, extra, written = [], [], {}
    if shadow:
        extra = includers(shadow)
        for rel, src in [*shadow.items(), *((h, posix(os.path.join("include", h))) for h in extra)]:
            dst = posix(os.path.normpath(os.path.join(out, rel)))
            os.makedirs(os.path.dirname(os.path.join(ROOT, dst)), exist_ok=True)
            shutil.copyfile(os.path.join(ROOT, src), os.path.join(ROOT, dst))
            written[dst] = src
        flags = ["-I", posix(os.path.normpath(out))]
        if beside:
            flags += ["-I", posix(os.path.dirname(copy)) or "."]
    for d in dirs:
        flags += ["-I", posix(os.path.normpath(d))]
    return flags, shadow, extra, written


def fingerprint(copy, dirs, beside=True):
    """`path:sha1` of every file under DIRS and of every header COPY's directory shadows (unless not
    BESIDE): what a shadowed compile reads beyond include/ and the copy."""
    paths = set(shadowed(copy).values()) if beside else set()
    for d in dirs:
        for base, _, fs in os.walk(os.path.join(ROOT, d)):
            paths.update(posix(os.path.relpath(os.path.join(base, f), ROOT)) for f in fs)
    out = []
    for p in sorted(paths):
        with open(os.path.join(ROOT, p), "rb") as f:
            out.append(f"{p}:{hashlib.sha1(f.read()).hexdigest()}")
    return out


def main(argv=None):
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("copy")
    p.add_argument("--shadow", action="append", default=[], metavar="DIR")
    p.add_argument("--no-beside", dest="beside", action="store_false",
                   help="COPY is the src file itself: only the --shadow DIRs shadow")
    p.add_argument("--out", required=True)
    a = p.parse_args(argv)
    rel = lambda x: posix(os.path.relpath(os.path.abspath(x), ROOT))  # noqa: E731
    flags, shadow, extra, _ = materialise(rel(a.copy), [rel(d) for d in a.shadow], rel(a.out), a.beside)
    if shadow:
        print(f"shadow: {' '.join(shadow)}" + (f" (+ unchanged includers {' '.join(extra)})" if extra else ""),
              file=sys.stderr)
    if flags:
        print(" ".join(flags))


if __name__ == "__main__":
    main()
