#!/usr/bin/env python3
"""Shadow headers for compiling a private copy against private versions of include/ headers
(stdlib only; tools/fdiff.sh and `tools/cwarn.py list --as` use it).

A copy shadows `include/<rel>` with `<copy dir>/<rel>` (cpp searches the includer's directory
first) or with `<DIR>/<rel>` of a shadow dir (`--shadow DIR`, ahead of `-I include`). cpp resolves
a quote include of an include/ header in that header's own directory first, so an unchanged
include/ header quote-including a shadowed one (race.h and boss.h include "actor.h") would still
reach the repo's version: every such includer is shadowed too, unchanged, transitively.

  python3 tools/shadow.py COPY [--shadow DIR]... --out OUT
      writes OUT (the shadowed headers plus their unchanged includers, at their include/ paths) and
      prints the flags to put ahead of `-I include`: `-I OUT -I <copy dir>` when an include/ header
      is shadowed (the copy dir for headers include/ lacks), then `-I DIR` per DIR; prints nothing
      when neither applies. A note naming the shadowed headers goes to stderr.
"""
import argparse
import hashlib
import os
import re
import shutil
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
QUOTE_INCLUDE = re.compile(r'^[ \t]*#[ \t]*include[ \t]*"([^"]+)"', re.M)


def include_files():
    """include/-relative paths of every file under include/."""
    base = os.path.join(ROOT, "include")
    return {os.path.relpath(os.path.join(d, f), base) for d, _, fs in os.walk(base) for f in fs}


def shadowed(copy, dirs=()):
    """{include/-relative path: ROOT-relative source} of the include/ headers COPY's directory or a
    DIRS entry shadows (the copy's directory first, then DIRS in order)."""
    out = {}
    for rel in sorted(include_files()):
        for d in (os.path.dirname(copy), *dirs):
            p = os.path.join(d, rel)
            if os.path.isfile(os.path.join(ROOT, p)):
                out[rel] = os.path.normpath(p)
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
            target = os.path.normpath(os.path.join(os.path.dirname(h), name))
            if target in files:
                by_target.setdefault(target, set()).add(h)
    seen, todo = set(rels), list(rels)
    while todo:
        for h in by_target.get(todo.pop(), ()):
            if h not in seen:
                seen.add(h)
                todo.append(h)
    return sorted(seen - set(rels))


def materialise(copy, dirs, out):
    """Write OUT for COPY (ROOT-relative paths) and return (`-I` flags, shadowed map, includers,
    {OUT path: source} of every header written)."""
    shadow = shadowed(copy, dirs)
    shutil.rmtree(os.path.join(ROOT, out), ignore_errors=True)
    flags, extra, written = [], [], {}
    if shadow:
        extra = includers(shadow)
        for rel, src in [*shadow.items(), *((h, os.path.join("include", h)) for h in extra)]:
            dst = os.path.normpath(os.path.join(out, rel))
            os.makedirs(os.path.dirname(os.path.join(ROOT, dst)), exist_ok=True)
            shutil.copyfile(os.path.join(ROOT, src), os.path.join(ROOT, dst))
            written[dst] = src
        flags = ["-I", os.path.normpath(out), "-I", os.path.dirname(copy) or "."]
    for d in dirs:
        flags += ["-I", os.path.normpath(d)]
    return flags, shadow, extra, written


def fingerprint(copy, dirs):
    """`path:sha1` of every file under DIRS and of every header COPY's directory shadows: what a
    shadowed compile reads beyond include/ and the copy."""
    paths = set(shadowed(copy).values())
    for d in dirs:
        for base, _, fs in os.walk(os.path.join(ROOT, d)):
            paths.update(os.path.relpath(os.path.join(base, f), ROOT) for f in fs)
    out = []
    for p in sorted(paths):
        with open(os.path.join(ROOT, p), "rb") as f:
            out.append(f"{p}:{hashlib.sha1(f.read()).hexdigest()}")
    return out


def main(argv=None):
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("copy")
    p.add_argument("--shadow", action="append", default=[], metavar="DIR")
    p.add_argument("--out", required=True)
    a = p.parse_args(argv)
    rel = lambda x: os.path.relpath(os.path.abspath(x), ROOT)  # noqa: E731
    flags, shadow, extra, _ = materialise(rel(a.copy), [rel(d) for d in a.shadow], rel(a.out))
    if shadow:
        print(f"shadow: {' '.join(shadow)}" + (f" (+ unchanged includers {' '.join(extra)})" if extra else ""),
              file=sys.stderr)
    if flags:
        print(" ".join(flags))


if __name__ == "__main__":
    main()
