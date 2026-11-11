#!/usr/bin/env python3
"""IDO cfe warnings of the matching compile (libultra excluded), cached per file content.

  python3 tools/cwarn.py list [--as SRC] FILE...   one line per warning `path:line: Warning N: msg`,
                                                  then `total N`; --as (one FILE only): compile the
                                                  FILE (a private copy) with SRC's make flags
  python3 tools/cwarn.py count [--json] [FILE...]  `<n> <path>` per file with warnings plus `TOTAL <n>`;
                                                  --json: {path: n} for every file (zeros included).
                                                  Default FILE set: every src/**/*.c outside /libultra/
  python3 tools/cwarn.py ratchet BEFORE.json AFTER.json
                                                  per path of AFTER: `new <path>: <n>` when BEFORE lacks
                                                  it, `ROSE <path>: <b> -> <a>` when it rose (exit 1);
                                                  else `warnings OK (<sumB> -> <sumA>)`, exit 0
  python3 tools/cwarn.py compile-json JOBS.json    container side: compile each
                                                  {"input": .c, "src": src whose flags to use} with the
                                                  command `make -n` prints for SRC (as tools/fdiff.sh,
                                                  matching side, no -DNON_MATCHING); prints
                                                  [{"rc", "out"}] as JSON

One printed `cfe: Warning N: <path>, line L: <msg>` line is one warning (no dedupe). `cfe: Error`
fails the compile (never reported as 0 warnings; `CompileError` names the file, the rev and the first
`cfe: Error` line); `cc: Warning:` driver lines are ignored. Results are cached in .scratch/cwarn/cache/
keyed by the Makefile, every include/ file, the flags src path, the compiled text and, for an in-place
compile, the *.h files beside it; all cache misses of one call compile in one `tools/dk` request
(inheriting DK64_LEASE). `collect(..., rev=REV)` compiles texts against REV's include/ and REV's *.h
beside each path instead (exported into the call's stage dir with `git archive`, asm/ linked to the
checkout's; keyed by REV's include/ tree id). Warnings printed for the compiled input are reported
under the given path; other paths (headers) are kept as printed.
"""
import argparse
import glob
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
import uuid
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SCRATCH = os.path.join(ROOT, ".scratch", "cwarn")
WARNING = re.compile(r"^cfe: Warning (\d+): (.+?), line (\d+): (.*)$")
CARET = re.compile(r"^ -*\^\s*$")
COMPILE = re.compile(r"asm-processor|/opt/ido[0-9.]+/cc")


def in_container():
    return os.path.exists("/.dockerenv") or os.path.isdir("/opt/ido5.3")


def rel(p):
    """ROOT-relative form of a repo path. Relative inputs are already ROOT-relative
    (git, ledger, internal joins) and are never re-resolved against the process cwd."""
    return os.path.relpath(os.path.join(ROOT, p), ROOT)


def cli_path(p):
    """argparse type: a user-typed path, relative to the user's cwd, made ROOT-relative once."""
    return rel(os.path.abspath(p))


def sha1(b):
    return hashlib.sha1(b if isinstance(b, bytes) else b.encode("utf-8")).hexdigest()


# ---------------------------------------------------------------- container side

def compile_one(job, tmpdir, n):
    """Compile JOB["input"] (relative to the tree JOB["cwd"], default the checkout) with the command
    `make -n` prints for JOB["src"]; the command's relative include/ and asm/ paths resolve in that tree."""
    src = job["src"]
    r = subprocess.run(["make", "-n", "-W", src, "build/" + src[:-2] + ".o"], cwd=ROOT, capture_output=True,
                       text=True)
    cmds = [line for line in r.stdout.splitlines() if COMPILE.search(line)]
    if not cmds:
        return {"rc": 1, "out": f"no compile rule for {src}\n{r.stderr}"}
    cmd = cmds[-1]
    cmd = cmd[:cmd.rindex(" -o ")] + f" -o {tmpdir}/{n}.o {job['input']}"
    r = subprocess.run(["sh", "-c", cmd], cwd=os.path.join(ROOT, job.get("cwd", "")), stdout=subprocess.PIPE,
                       stderr=subprocess.STDOUT, text=True, errors="replace")
    return {"rc": r.returncode, "out": r.stdout}


def compile_jobs(jobs):
    tmpdir = tempfile.mkdtemp(prefix="cwarn")
    try:
        with ThreadPoolExecutor(max_workers=os.cpu_count() or 4) as pool:
            return list(pool.map(lambda x: compile_one(x[1], tmpdir, x[0]), enumerate(jobs)))
    finally:
        shutil.rmtree(tmpdir, ignore_errors=True)


# ---------------------------------------------------------------- host side

class CompileError(Exception):
    """A failed compile of PATH (its text at REV when REV is given); OUT: the compiler output."""

    def __init__(self, path, out, rev=None):
        super().__init__(path, out, rev)
        self.path, self.out, self.rev = path, out, rev

    def first(self):
        lines = [line for line in self.out.splitlines() if line.strip()]
        return next((line for line in lines if line.startswith("cfe: Error")), lines[-1] if lines else "no output")

    def __str__(self):
        return f"cannot compile {self.path}" + (f" at {self.rev}" if self.rev else "") + f": {self.first()}"


def parse(out):
    """[dict(code, path, line, col, msg)] of every `cfe: Warning` line of OUT, in output order; COL is
    the caret's index in the second following line, else -1."""
    lines = out.split("\n")
    res = []
    for i, line in enumerate(lines):
        m = WARNING.match(line)
        if not m:
            continue
        caret = lines[i + 2] if i + 2 < len(lines) else ""
        col = caret.index("^") if CARET.match(caret) else -1
        res.append(dict(code=int(m.group(1)), path=m.group(2), line=int(m.group(3)), col=col, msg=m.group(4)))
    return res


_static = {}


def static_key():
    """sha1 of the Makefile and of every include/ file (computed once per process)."""
    if "key" not in _static:
        pairs = []
        for d, _, files in os.walk(os.path.join(ROOT, "include")):
            for f in files:
                p = os.path.join(d, f)
                pairs.append((os.path.relpath(p, ROOT), sha1(open(p, "rb").read())))
        inc = sha1("".join(f"{p}\0{s}\n" for p, s in sorted(pairs)))
        mk = sha1(open(os.path.join(ROOT, "Makefile"), "rb").read())
        _static["key"] = (mk, inc)
    return _static["key"]


def cache_key(path, data, src, in_place, inc=None, side=()):
    """INC: the include/ part (default the working tree's); SIDE: `name:sha` of the *.h beside a
    text compiled at a rev."""
    mk, inc0 = static_key()
    parts = ["cwarn-v1", mk, inc or inc0, src, sha1(data), *side]
    if in_place:
        d = os.path.dirname(os.path.join(ROOT, path))
        parts += [f"{os.path.basename(h)}:{sha1(open(h, 'rb').read())}" for h in sorted(glob.glob(os.path.join(d, "*.h")))]
    return sha1("\0".join(parts))


def git(*args):
    r = subprocess.run(["git", *args], cwd=ROOT, capture_output=True)
    return r.stdout if r.returncode == 0 else None


def rev_side_headers(rev, path):
    """{basename: blob sha} of the *.h beside PATH at REV."""
    out = {}
    for line in (git("ls-tree", rev, "--", os.path.dirname(path) + "/") or b"").decode().splitlines():
        meta, name = line.split("\t", 1)
        if meta.split()[1] == "blob" and name.endswith(".h"):
            out[os.path.basename(name)] = meta.split()[2]
    return out


def export_tree(rev, tree):
    """REV's include/ under TREE, plus TREE/asm linking to the checkout's (generated, not in git)."""
    os.makedirs(tree, exist_ok=True)
    arc = subprocess.Popen(["git", "archive", rev, "include"], cwd=ROOT, stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE)
    tar = subprocess.run(["tar", "-x", "-C", tree], stdin=arc.stdout, capture_output=True, text=True)
    arc.stdout.close()
    err = arc.stderr.read().decode("utf-8", "replace")
    if arc.wait() or tar.returncode:
        raise CompileError(None, f"git archive {rev} include failed: {err}{tar.stderr}", rev)
    os.symlink(os.path.relpath(os.path.join(ROOT, "asm"), tree), os.path.join(tree, "asm"))




def write_atomic(path, text):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    fd, tmp = tempfile.mkstemp(dir=os.path.dirname(path), suffix=".tmp")
    with os.fdopen(fd, "w") as f:
        f.write(text)
    os.replace(tmp, path)


def run_jobs(jobs):
    if in_container():
        return compile_jobs(jobs)
    jf = os.path.join(SCRATCH, "jobs", f"{uuid.uuid4()}.json")
    write_atomic(jf, json.dumps(jobs))
    try:
        r = subprocess.run([os.path.join(ROOT, "tools", "dk"), "python3", "tools/cwarn.py", "compile-json", rel(jf)],
                           cwd=ROOT, capture_output=True, text=True, errors="replace")
    finally:
        os.remove(jf)
    if r.returncode != 0:
        raise CompileError(None, r.stdout + r.stderr)
    return json.loads(r.stdout)


def collect(items, rev=None):
    """[[dict(code, path, line, col, msg)] per item] for ITEMS = [(path, text or None, src or None)]: the
    warnings of compiling PATH (TEXT None: in place) or TEXT with the make flags of SRC (else PATH).
    REV: compile every TEXT (required) against REV's include/ and REV's *.h beside PATH. Raises
    CompileError for the first item that fails."""
    keys, todo = [], {}
    stage = os.path.join(SCRATCH, "in", str(uuid.uuid4()))  # this call's own inputs: another may share keys
    tree = os.path.join(stage, "tree")  # REV's include/ and asm/: inputs compile with it as cwd
    inc = None
    if rev:
        t = git("rev-parse", "--verify", "-q", f"{rev}:include")
        if t is None:
            raise CompileError(items[0][0] if items else None, f"no include/ tree at {rev}", rev)
        inc = "rev-include:" + t.decode().strip()
    for path, text, src in items:
        p, flags = rel(path), rel(src or path)
        if rev and text is None:
            raise ValueError("cwarn.collect: rev needs the text")
        side = rev_side_headers(rev, p) if rev else {}
        data = open(os.path.join(ROOT, p), "rb").read() if text is None else text.encode("utf-8")
        key = cache_key(p, data, flags, text is None, inc, [f"{n}:{s}" for n, s in sorted(side.items())])
        keys.append(key)
        if key in todo or os.path.exists(os.path.join(SCRATCH, "cache", key + ".json")):
            continue
        job = {"src": flags}
        if text is None:
            job["input"] = p
        else:
            d = os.path.join(tree if rev else stage, key)
            os.makedirs(d, exist_ok=True)
            open(os.path.join(d, os.path.basename(p)), "wb").write(data)
            for name, blob in side.items():
                open(os.path.join(d, name), "wb").write(git("cat-file", "blob", blob))
            if rev:
                job.update(input=os.path.join(key, os.path.basename(p)), cwd=rel(tree))
            else:
                job["input"] = rel(os.path.join(d, os.path.basename(p)))
        todo[key] = (p, job)
    if todo:
        try:
            if rev:
                export_tree(rev, tree)
            results = run_jobs([job for _, job in todo.values()])
        except CompileError as ex:
            ex.path, ex.rev = ex.path or next(iter(todo.values()))[0], rev
            raise
        finally:
            shutil.rmtree(stage, ignore_errors=True)
        for (key, (p, job)), r in zip(todo.items(), results):
            if r["rc"] != 0:
                raise CompileError(p, r["out"].replace(job["input"], p), rev)
            ws = parse(r["out"])
            for w in ws:
                w["path"] = None if w["path"] == job["input"] else w["path"]
            write_atomic(os.path.join(SCRATCH, "cache", key + ".json"), json.dumps(ws))
    out = []
    for (path, _, _), key in zip(items, keys):
        ws = json.load(open(os.path.join(SCRATCH, "cache", key + ".json")))
        for w in ws:
            if w["path"] is None:
                w["path"] = rel(path)
        out.append(ws)
    return out


def src_files():
    return sorted(p for p in glob.glob("src/**/*.c", root_dir=ROOT, recursive=True) if "/libultra/" not in p)


def cmd_list(a):
    if a.as_ and len(a.files) != 1:
        sys.exit("cwarn: --as takes exactly one FILE")
    res = collect([(f, None, a.as_) for f in a.files])
    n = 0
    for ws in res:
        for w in ws:
            print(f"{w['path']}:{w['line']}: Warning {w['code']}: {w['msg']}")
            n += 1
    print(f"total {n}")


def cmd_count(a):
    files = [rel(f) for f in a.files] or src_files()
    counts = {f: len(ws) for f, ws in zip(files, collect([(f, None, None) for f in files]))}
    if a.json:
        print(json.dumps(counts, indent=1, sort_keys=True))
        return
    for f, n in counts.items():
        if n:
            print(f"{n} {f}")
    print(f"TOTAL {sum(counts.values())}")


def cmd_ratchet(a):
    before, after = json.load(open(a.before)), json.load(open(a.after))
    rose = False
    for p, n in sorted(after.items()):
        if p not in before:
            print(f"new {p}: {n}")
        elif n > before[p]:
            print(f"ROSE {p}: {before[p]} -> {n}")
            rose = True
    if rose:
        sys.exit(1)
    print(f"warnings OK ({sum(before.values())} -> {sum(after.values())})")


def cmd_compile_json(a):
    print(json.dumps(compile_jobs(json.load(open(a.jobs)))))


def main(argv=None):
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    s = p.add_subparsers(dest="cmd", required=True)
    c = s.add_parser("list")
    c.add_argument("--as", dest="as_")
    c.add_argument("files", nargs="+", type=cli_path)
    c.set_defaults(fn=cmd_list)
    c = s.add_parser("count")
    c.add_argument("--json", action="store_true")
    c.add_argument("files", nargs="*", type=cli_path)
    c.set_defaults(fn=cmd_count)
    c = s.add_parser("ratchet")
    c.add_argument("before")
    c.add_argument("after")
    c.set_defaults(fn=cmd_ratchet)
    c = s.add_parser("compile-json")
    c.add_argument("jobs")
    c.set_defaults(fn=cmd_compile_json)
    a = p.parse_args(argv)
    try:
        a.fn(a)
    except CompileError as ex:
        tail = "\n".join(ex.out.rstrip().splitlines()[-5:])
        sys.exit(f"cwarn: {ex}\n{tail}")


if __name__ == "__main__":
    main()
