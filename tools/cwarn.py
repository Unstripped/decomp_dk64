#!/usr/bin/env python3
"""IDO cfe warnings of the matching compile (libultra excluded), cached per file content.

  python3 tools/cwarn.py list [--as SRC [--shadow DIR]...] FILE...
                                                  one line per warning `path:line: Warning N: msg`,
                                                  then `total N`; --as (one FILE only): compile the
                                                  FILE (a private copy) with SRC's make flags and its
                                                  shadow headers (tools/shadow.py, as tools/fdiff.sh:
                                                  include/ paths beside the copy or in a --shadow DIR,
                                                  plus every include/ header quote-including one);
                                                  FILE = SRC (an includer of an edited header): only
                                                  the --shadow DIRs shadow
  python3 tools/cwarn.py count [--json] [FILE...]  `<n> <path>` per file with warnings plus `TOTAL <n>`;
                                                  --json: {path: n} for every file (zeros included).
                                                  Default FILE set: every src/**/*.c outside /libultra/
  python3 tools/cwarn.py ratchet BEFORE.json AFTER.json
                                                  per path of AFTER: `new <path>: <n>` when BEFORE lacks
                                                  it, `ROSE <path>: <b> -> <a>` when it rose (exit 1);
                                                  else `warnings OK (<sumB> -> <sumA>)`, exit 0
  python3 tools/cwarn.py compile-json JOBS.json    container side: compile each
                                                  {"input": .c, "src": src whose flags to use,
                                                  "shadow": flags ahead of `-I include`} with the
                                                  command `make -n` prints for SRC (as tools/fdiff.sh,
                                                  matching side, no -DNON_MATCHING); prints
                                                  [{"rc", "out"}] as JSON

One printed `cfe: Warning N: <path>, line L: <msg>` line is one warning (no dedupe). `cfe: Error`
fails the compile (never reported as 0 warnings; `CompileError` names the file, the rev and the first
`cfe: Error` line); `cc: Warning:` driver lines are ignored. Results are cached in .scratch/cwarn/cache/
keyed by the Makefile, every include/ file, the flags src path, the compiled text and, for an in-place
compile, the *.h files beside it (a copy compiled in place with another file's flags: also the headers
it shadows); all cache misses of one call compile in one `tools/dk` request
(inheriting DK64_LEASE). `collect(..., rev=REV)` compiles texts against REV's include/ and REV's *.h
beside each path instead (exported into the call's stage dir by `export_tree`, asm/ and assets/ linked to
the checkout's; keyed by REV's include/ tree id). Warnings printed for the compiled input are reported
under the given path; other paths (headers, shadowed ones under their source path) are kept as printed.
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

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import shadow as shadow_headers  # noqa: E402
from shadow import dk_argv, posix  # noqa: E402

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
    return posix(os.path.relpath(os.path.join(ROOT, p), ROOT))


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
    if job.get("shadow"):
        cmd = cmd.replace(" -I include ", f" {job['shadow']} -I include ")
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


class CrlfError(CompileError):
    """PATH (a private copy, its text, or a src file) has CRLF line endings; never compiled."""

    def __init__(self, path):
        super().__init__(path, "")

    def __str__(self):
        return f"copy has CRLF line endings: {self.path}"


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
                pairs.append((posix(os.path.relpath(p, ROOT)), sha1(open(p, "rb").read())))
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


GENERATED = ("asm", "assets")  # checkout dirs an export tree links to (generated, not in git)


def export_tree(rev, tree):
    """REV's include/ under TREE (`export_include`), plus TREE/asm and TREE/assets linking to the
    checkout's. A host that cannot make a symlink (Windows without the privilege) has the container
    make it, a link later container calls resolve; `unlink_generated` removes either kind."""
    export_include(rev, tree)
    for generated in GENERATED:
        target, link = os.path.relpath(os.path.join(ROOT, generated), tree), os.path.join(tree, generated)
        try:
            os.symlink(target, link)
        except OSError:
            container_symlink(posix(target), link)


def export_include(rev, tree):
    """REV's include/ under TREE (`export_rev`)."""
    export_rev(rev, tree, "include")


def export_rev(rev, tree, top, want=None):
    """REV's files under the top-level directory TOP under TREE, only those whose path WANT accepts
    when given. All of TOP on a POSIX host: `git archive | tar`. Otherwise (Windows, or WANT):
    `git checkout-index` from a private index of just those files (`git ls-tree` into `update-index
    --index-info`), which writes them as this checkout has them (core.symlinks false: the
    include/libultra/PR link is a file holding its target, where tar fails without the symlink
    privilege) and reads no other path of REV (`git archive` or `read-tree` of REV's src/ fail on a
    path Windows cannot check out: `src/arcade/lso ` before 2ddb60d1)."""
    os.makedirs(tree, exist_ok=True)
    if os.name == "nt" or want is not None:
        r = subprocess.run(["git", "ls-tree", "-r", "-z", rev, "--", top], cwd=ROOT, capture_output=True)
        if r.returncode:
            raise CompileError(None, f"git ls-tree {rev} {top} failed: {r.stderr.decode('utf-8', 'replace')}", rev)
        info = b"".join(e + b"\0" for e in r.stdout.split(b"\0")
                        if e and (want is None or want(e.split(b"\t", 1)[1].decode("utf-8", "replace"))))
        env = dict(os.environ, GIT_INDEX_FILE=posix(os.path.join(tree, ".index")))
        for args, data in ((["update-index", "-z", "--index-info"], info),
                           (["checkout-index", "-a", f"--prefix={posix(tree)}/"], None)):
            r = subprocess.run(["git", *args], cwd=ROOT, env=env, input=data, capture_output=True)
            if r.returncode:
                raise CompileError(None, f"git {args[0]} {rev}:{top} failed: {r.stderr.decode('utf-8', 'replace')}",
                                   rev)
        if os.path.exists(env["GIT_INDEX_FILE"]):
            os.remove(env["GIT_INDEX_FILE"])
        return
    arc = subprocess.Popen(["git", "archive", rev, top], cwd=ROOT, stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE)
    tar = subprocess.run(["tar", "-x", "-C", tree], stdin=arc.stdout, capture_output=True, text=True)
    arc.stdout.close()
    err = arc.stderr.read().decode("utf-8", "replace")
    if arc.wait() or tar.returncode:
        raise CompileError(None, f"git archive {rev} {top} failed: {err}{tar.stderr}", rev)


def container_symlink(target, link):
    """`ln -s TARGET LINK` run in the container (LINK: a path under ROOT)."""
    r = subprocess.run(dk_argv("ln", "-s", target, rel(link)), cwd=ROOT, capture_output=True, text=True,
                       errors="replace")
    if r.returncode:
        raise CompileError(None, f"ln -s {target} {rel(link)} in the container failed: {r.stdout}{r.stderr}")


def unlink_generated(tree):
    """Remove an export tree's asm/assets links, before anything removes the tree: a link the container
    made on a Windows host is a WSL symlink that rmtree cannot remove and unlink may not, while rmdir
    removes just the link (never the checkout's directory behind it)."""
    for generated in GENERATED:
        link = os.path.join(tree, generated)
        try:
            os.unlink(link)
        except FileNotFoundError:
            pass
        except OSError:
            try:
                os.rmdir(link)
            except OSError:
                pass


def write_atomic(path, text):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    fd, tmp = tempfile.mkstemp(dir=os.path.dirname(path), suffix=".tmp")
    with os.fdopen(fd, "w", newline="\n") as f:
        f.write(text)
    os.replace(tmp, path)


def run_jobs(jobs):
    if in_container():
        return compile_jobs(jobs)
    jf = os.path.join(SCRATCH, "jobs", f"{uuid.uuid4()}.json")
    write_atomic(jf, json.dumps(jobs))
    try:
        r = subprocess.run(dk_argv("python3", "tools/cwarn.py", "compile-json", rel(jf)),
                           cwd=ROOT, capture_output=True, text=True, errors="replace")
    finally:
        os.remove(jf)
    if r.returncode != 0:
        raise CompileError(None, r.stdout + r.stderr)
    return json.loads(r.stdout)


def collect(items, rev=None, shadow=()):
    """[[dict(code, path, line, col, msg)] per item] for ITEMS = [(path, text or None, src or None)]: the
    warnings of compiling PATH (TEXT None: in place) or TEXT with the make flags of SRC (else PATH).
    REV: compile every TEXT (required) against REV's include/ and REV's *.h beside PATH. A copy
    compiled in place (SRC another file) gets its shadow headers (tools/shadow.py: include/ paths
    beside it or in a SHADOW dir, plus every include/ header quote-including one); a file compiled in
    place with its own flags only those of the SHADOW dirs (its *.h beside it are make's own). Raises
    CompileError for the first item that fails."""
    keys, todo, written = [], {}, {}
    dirs = [rel(d) for d in shadow]
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
        beside = flags != p
        shadowing = text is None and (beside or bool(dirs))
        fp = shadow_headers.fingerprint(p, dirs, beside) if shadowing else []
        data = open(os.path.join(ROOT, p), "rb").read() if text is None else text.encode("utf-8")
        if b"\r\n" in data:  # IDO cfe prints W513 for each carriage return: a CRLF copy would count them
            raise CrlfError(p)
        key = cache_key(p, data, flags, text is None, inc, [f"{n}:{s}" for n, s in sorted(side.items())]
                        + (["shadow-v1", *dirs, *fp] if fp or (shadowing and dirs) else []))
        keys.append(key)
        if key in todo or os.path.exists(os.path.join(SCRATCH, "cache", key + ".json")):
            continue
        job = {"src": flags}
        if text is None:
            job["input"] = p
            if shadowing:
                sflags, _, _, written[key] = shadow_headers.materialise(p, dirs, rel(os.path.join(stage, key, "shadow")),
                                                                        beside)
                if sflags:
                    job["shadow"] = " ".join(sflags)
        else:
            d = os.path.join(tree if rev else stage, key)
            os.makedirs(d, exist_ok=True)
            open(os.path.join(d, os.path.basename(p)), "wb").write(data)
            for name, blob in side.items():
                open(os.path.join(d, name), "wb").write(git("cat-file", "blob", blob))
            if rev:
                job.update(input=posix(os.path.join(key, os.path.basename(p))), cwd=rel(tree))
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
            unlink_generated(tree)  # first: rmtree cannot remove a container-made link
            shutil.rmtree(stage, ignore_errors=True)
        for (key, (p, job)), r in zip(todo.items(), results):
            if r["rc"] != 0:
                raise CompileError(p, r["out"].replace(job["input"], p), rev)
            ws = parse(r["out"])
            for w in ws:
                w["path"] = None if w["path"] == job["input"] else written.get(key, {}).get(w["path"], w["path"])
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
    paths = (posix(p) for p in glob.glob("src/**/*.c", root_dir=ROOT, recursive=True))
    return sorted(p for p in paths if "/libultra/" not in p)


def cmd_list(a):
    if a.as_ and len(a.files) != 1:
        sys.exit("cwarn: --as takes exactly one FILE")
    if a.shadow and not a.as_:
        sys.exit("cwarn: --shadow needs --as")
    res = collect([(f, None, a.as_) for f in a.files], shadow=a.shadow)
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
    c.add_argument("--shadow", action="append", default=[], type=cli_path, metavar="DIR")
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
        sys.exit(f"cwarn: {ex}" + (f"\n{tail}" if tail else ""))


if __name__ == "__main__":
    main()
