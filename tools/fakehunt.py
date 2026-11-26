# /// script
# requires-python = ">=3.12"
# dependencies = ["libclang==18.1.1"]
# ///
"""Unattended, resumable hunt for hack-free matches of every `// FAKE` site (FAKE-kind sites of
tools/quality.py, untagged AST hacks included). Host-side; container work goes through tools/dk.
Never edits src/ and never writes the quality ledger: it writes hits for workers to apply.

  uv run tools/fakehunt.py run [--seg S] [--file SRC] [--func NAME] [--stages recipes,as1,permute]
        [--parallel 3] [-j 2] [--seconds S] [--hours H] [--dry-run]
  uv run tools/fakehunt.py status [--func NAME]
  uv run tools/fakehunt.py hits
  uv run tools/fakehunt.py show FUNC

  run     works pass N (state `pass`) over the selected functions, least recently hunted first, one
          stage after another (--stages picks a subset):
            recipes  per function, once per fingerprint (fp_local): candidates are each site's removal
                     (quality.remove_edit) and first plain rewrite, plus tools/variants.py splitlocal and
                     unalias over the function as written and with every removable site removed; all are
                     scored in one `variants.py try` call (-j J). A full=0 candidate with fewer `// FAKE`
                     lines in the function that passes quality.check (fdiff --reloc-ok exit 0, no new
                     uninit) is written by quality.write_hit (`HIT <key> <recipe> <path>`). Each site keeps
                     its best candidate (`best`, whole file in .scratch/fakehunt/run/<seg>_<func>/best_<h>.c):
                     the hack-free base of the later stages. A failed `try` leaves recipes undone (`SKIP`).
            as1      per site, once per fingerprint: `as1probe.py keep` on the best candidate, then
                     `scan --rounds 3`; output in .scratch/fakehunt/as1/<seg>_<func>_<h>/scan.txt (hints).
            permute  per site, once per pass: permute.batch_row on the best candidate under
                     .scratch/fakehunt/pass<N>/ (headers/ snapshot of include/ + assets/inc/ taken at
                     the pass's first permute job), hack-free weights, --seconds S (default
                     min(900 * 2^(N-1), 14400)). Zero outputs are listed, never written as hits.
          An unfiltered run loops: once every FAKE site at HEAD has a pass-N permute entry the state
          moves to pass N+1, until --hours H elapse (0: no limit) or no FAKE site remains (`NO FAKE
          SITES`). A run filtered by --seg/--file/--func works the current pass for its sites and exits
          (the counter advances only in an unfiltered run); without the permute stage any run exits
          after one round. Ctrl-C (SIGINT) stops every child job (SIGINT, which tools/dk forwards to its
          container job, then SIGTERM/SIGKILL after 30 s each; on Windows TerminateProcess, then a wait
          until the dkd server lists no request of a killed client), waits for them, saves the state and exits
          130 (`INTERRUPTED pass=<N>`); interrupted jobs record nothing and re-run next time. --dry-run
          prints the planned jobs (`RECIPES <func>`, `AS1 <key>`, `PERMUTE <key> seconds=<S>`) and writes
          nothing.
  status  one line per site: `<key> <func> recipes=<best|->(<n> hits) as1=<rc|-> permute=<pass:best,...>`,
          then `pass=<N> sites=<n> hits=<n> zeros=<n>`.
  hits    open hits (site still at HEAD, its file unchanged since the hit): `HIT <key> <func> <file> <path>`;
          permuter zeros of current sites: `ZERO-PERMUTE <key> <func> <file> <dir>`. Exit 0.
  show    everything the state holds for FUNC's sites; workers read it before a retry.

State: .scratch/fakehunt/state.json (atomic writes after every job). A site whose fp_local changed
starts again from empty stages; sites gone from HEAD are dropped at pass start. A file changed while
the run works on it is re-analysed before the next job of that file and before writing its hits.
"""
import argparse
import collections
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
import threading
import time
import signal
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import quality as q  # noqa: E402
import variants  # noqa: E402
import permute  # noqa: E402
from shadow import dk_argv  # noqa: E402

HUNT = os.path.join(q.ROOT, ".scratch", "fakehunt")
STATE = os.path.join(HUNT, "state.json")
STAGES = ("recipes", "as1", "permute")
TRY_LINE = re.compile(r"^(\S+) full=(\d+) text=(\d+) reloc=(\d+) shape=(\d+)")


def sha1_of(path):
    try:
        return hashlib.sha1(open(os.path.join(q.ROOT, path), "rb").read()).hexdigest()
    except FileNotFoundError:
        return None


def tag(key):
    """Directory-safe part of a site key after its last `:` (`abc123#2` -> `abc123-2`)."""
    return key.rsplit(":", 1)[-1].replace("#", "-")


def fake_sites(fn):
    return [s for s in fn["sites"] if s["kind"] in q.FAKE_KINDS]


def empty(fn, path, sha):
    return {"file": path, "func": fn["name"], "seg": fn["seg"], "fp": fn["fp_local"], "src_sha1": sha,
            "recipes": {"done": False, "best": None, "best_copy": None, "hits": []},
            "as1": {"done": False, "out": None, "rc": None}, "permute": []}


def load_state():
    try:
        return json.load(open(STATE))
    except FileNotFoundError:
        return {"version": 1, "pass": 1, "sites": {}}


def last_pass(e):
    return max((p["pass"] for p in e["permute"]), default=0)


def fake_count(lines):
    return sum("// FAKE" in l for l in lines)


class Hunter:
    def __init__(self, a):
        self.a, self.st = a, load_state()
        # RLock: Ctrl-C may land while the main thread holds it; the handler then saves under it
        self.lock, self.plock, self.alock = threading.RLock(), threading.Lock(), threading.Lock()
        self.ans, self.sha, self.deadline, self.ex, self.stopping = {}, {}, None, None, False
        self.stages = [s for s in a.stages.split(",") if s]
        bad = [s for s in self.stages if s not in STAGES]
        if bad:
            sys.exit(f"fakehunt: unknown stage {','.join(bad)} (one of {','.join(STAGES)})")

    # ------------------------------------------------------------ state

    def save(self):
        if self.a.dry_run:
            return
        os.makedirs(HUNT, exist_ok=True)
        tmp = STATE + ".tmp"
        with open(tmp, "w") as f:
            json.dump(self.st, f, indent=1, sort_keys=True)
        os.replace(tmp, STATE)

    def sync(self, an, sha, names=None):
        """Create/reset the state entries of AN's FAKE sites (functions NAMES only, when given); a
        changed fp starts a site from empty stages, a changed file sha invalidates its hits."""
        sites = self.st["sites"]
        for fn in an["functions"]:
            if names is not None and fn["name"] not in names:
                continue
            for s in fake_sites(fn):
                e = sites.get(s["key"])
                if e is None or e["fp"] != fn["fp_local"] or e["file"] != an["path"]:
                    sites[s["key"]] = empty(fn, an["path"], sha)
                elif e["src_sha1"] != sha:
                    e["src_sha1"] = sha
                    if e["recipes"]["hits"]:  # whole-file hits of the old text: make them again
                        e["recipes"].update(done=False, hits=[])

    def collect(self):
        """[(path, fn)] of the selected functions with FAKE sites, least recently hunted first; syncs
        the state and drops entries whose site is gone from the analysed files."""
        a = self.a
        files = ([q.cli_path(a.file)] if a.file else q.seg_files(a.seg) if a.seg
                 else q.grep_files(a.func) if a.func else q.clint.src_files())
        ans = q.analyze_many(files)
        q.require_resolved(ans)
        present, out = set(), []
        with self.lock:
            for an in ans:
                self.ans[an["path"]], self.sha[an["path"]] = an, sha1_of(an["path"])
                present |= {s["key"] for fn in an["functions"] for s in fake_sites(fn)}
                fns = [fn for fn in an["functions"] if fake_sites(fn) and (not a.func or fn["name"] == a.func)]
                self.sync(an, self.sha[an["path"]], {fn["name"] for fn in fns})
                out += [(an["path"], fn) for fn in fns]
            analysed = set(self.ans)
            for k, e in list(self.st["sites"].items()):
                if (e["file"] in analysed and k not in present) or not os.path.exists(os.path.join(q.ROOT, e["file"])):
                    del self.st["sites"][k]
            self.save()
        sites = self.st["sites"]
        out.sort(key=lambda pf: (min(last_pass(sites[s["key"]]) for s in fake_sites(pf[1])), pf[0], pf[1]["line"]))
        return out

    def current(self, path, name):
        """FN NAME of PATH as the file is now (re-analysed when it changed since its analysis), or None."""
        with self.alock:
            sha = sha1_of(path)
            if sha != self.sha.get(path):
                an = q.analyze(path, q.seg_of(path))
                q.require_resolved([an])
                q._base_uninit.pop(path, None)
                with self.lock:
                    self.ans[path], self.sha[path] = an, sha
                    self.sync(an, sha)
                    self.save()
            return next((fn for fn in self.ans[path]["functions"] if fn["name"] == name and fake_sites(fn)), None)

    def expired(self):
        return self.stopping or (self.deadline is not None and time.monotonic() >= self.deadline)

    def seconds(self, n):
        return self.a.seconds or min(900 * 2 ** (n - 1), 14400)

    # ------------------------------------------------------------ stages

    def candidates(self, lines, fn):
        """[(site key, recipe, whole-file lines)] of FN's FAKE sites, first of each text kept."""
        sites, s0 = fake_sites(fn), fn["line"] - 1
        out = []
        rem = [(s, e) for s in sites if (e := q.remove_edit(s, lines, fn)) is not None]
        out += [(s["key"], "remove", q.apply(lines, e).split("\n")) for s, e in rem]
        for s in sites:
            texts = q.plain_rewrites(s, lines)
            if texts:
                out.append((s["key"], "plain", texts[0].split("\n")))
        bases = [(lines, list(range(len(lines))))]
        if rem:
            ed = q.merged(rem)
            bases.append((q.apply(lines, ed).split("\n"), [i for i in range(len(lines)) if ed.get(i, lines[i]) is not None]))
        at = {s["line"]: s for s in sites}
        for bl, kept in bases:
            lo, hi = kept.index(s0), sum(i < fn["end"] for i in kept)
            body = "\n".join(bl[lo:hi])
            for recipe, desc, vt in variants.gen_splitlocal(body) + variants.gen_unalias(body):
                n = int(re.match(r"lines? (\d+)", desc).group(1))
                s = at.get(kept[lo + n - 1] + 1) if lo + n - 1 < len(kept) else None
                out.append(((s or sites[0])["key"], recipe, bl[:lo] + vt.split("\n") + bl[hi:]))
        seen, uniq = set(), []
        for key, recipe, cl in out:
            t = "\n".join(cl)
            if t not in seen:
                seen.add(t)
                uniq.append((key, recipe, cl))
        return uniq

    def job_recipes(self, path, name):
        if self.expired():
            return
        fn = self.current(path, name)
        if fn is None:
            return
        print(f"RECIPES {name}", flush=True)
        seg, sha = fn["seg"], self.sha[path]
        lines = open(os.path.join(q.ROOT, path), encoding="utf-8", errors="replace").read().split("\n")
        s0, end = fn["line"] - 1, fn["end"]
        cands = self.candidates(lines, fn)
        d = os.path.join(HUNT, "run", f"{seg}_{name}")
        shutil.rmtree(d, ignore_errors=True)
        os.makedirs(d)
        bodies = []
        for k, (_, _, cl) in enumerate(cands, 1):
            b = os.path.join(d, f"b{k}.c")
            open(b, "w", newline="\n").write("\n".join(cl[s0:end + len(cl) - len(lines)]) + "\n")
            bodies.append(q.rel(b))
        scores = {}
        if bodies:
            r = subprocess.run(dk_argv("python3", "tools/variants.py", "try", path, path, name, *bodies,
                                       "-j", str(self.a.j)), cwd=q.ROOT, capture_output=True, text=True)
            if r.returncode != 0:
                tail = ((r.stderr or "") + (r.stdout or "")).strip().splitlines()
                print(f"SKIP {name}: {tail[-1] if tail else f'exit {r.returncode}'}", flush=True)
                return
            for line in r.stdout.splitlines():
                if m := TRY_LINE.match(line):
                    scores[m.group(1)] = int(m.group(2))
        src_fake = fake_count(lines[s0:end])
        best, hits = {}, {}
        for (key, recipe, cl), b in zip(cands, bodies):
            full = scores.get(b)
            if full is None:
                continue
            if key not in best or full < best[key][0]:
                best[key] = (full, cl)
            if full == 0 and fake_count(cl[s0:end + len(cl) - len(lines)]) < src_fake:
                text = "\n".join(cl)
                if not q.check(text, path, path):
                    continue
                if sha1_of(path) != sha:  # the file changed under the hunt: hunt it again
                    print(f"STALE {name}: {path} changed; recipes re-run", flush=True)
                    return
                p = q.write_hit(seg, path, text)
                hits.setdefault(key, []).append(p)
                print(f"HIT {key} {recipe} {p}", flush=True)
        with self.lock:
            if self.stopping:  # interrupted: its subprocesses died with the run
                return
            for s in fake_sites(fn):
                e = self.st["sites"].get(s["key"])
                if e is None:
                    continue
                r = e["recipes"]
                r["hits"] += hits.get(s["key"], [])
                if s["key"] in best:
                    bc = os.path.join(d, f"best_{tag(s['key'])}.c")
                    open(bc, "w", newline="\n").write("\n".join(best[s["key"]][1]))
                    r.update(best=best[s["key"]][0], best_copy=q.rel(bc))
                else:
                    r.update(best=None, best_copy=None)
                r["done"] = True
            self.save()
        print(f"RECIPES {name} done: {len(cands)} candidates, {sum(map(len, hits.values()))} hits, best "
              + (" ".join(f"{tag(k)}={v[0]}" for k, v in best.items()) or "-"), flush=True)

    def job_as1(self, key):
        if self.expired():
            return
        e = self.st["sites"][key]
        bc = e["recipes"]["best_copy"]
        if not bc:
            with self.lock:
                if self.stopping:
                    return
                e["as1"] = {"done": True, "out": None, "rc": None}
                self.save()
            return
        print(f"AS1 {key}", flush=True)
        d = q.rel(os.path.join(HUNT, "as1", f"{e['seg']}_{e['func']}_{tag(key)}"))
        r = subprocess.run(dk_argv("python3", "tools/as1probe.py", "keep", bc, e["file"], e["func"], "--out", d),
                           cwd=q.ROOT, capture_output=True, text=True)
        if r.returncode == 0:
            r = subprocess.run(dk_argv("python3", "tools/as1probe.py", "scan", d, "--rounds", "3",
                                       "-j", str(self.a.j)), cwd=q.ROOT, capture_output=True, text=True)
        os.makedirs(os.path.join(q.ROOT, d), exist_ok=True)
        out = os.path.join(d, "scan.txt")
        open(os.path.join(q.ROOT, out), "w").write((r.stdout or "") + (r.stderr or ""))
        with self.lock:
            if self.stopping:
                return
            e["as1"] = {"done": True, "out": out, "rc": r.returncode}
            self.save()
        print(f"AS1 {key} done: rc={r.returncode} {out}", flush=True)

    def job_permute(self, key, n):
        if self.expired():
            return
        e, secs = self.st["sites"][key], self.seconds(n)
        bc, best = e["recipes"]["best_copy"], e["recipes"]["best"]
        if not bc:
            entry = {"pass": n, "error": "no hack-free base"}
        else:
            print(f"PERMUTE {key} seconds={secs}", flush=True)
            pass_dir = Path(HUNT) / f"pass{n}"
            d = pass_dir / f"{e['seg']}_{e['func']}_{tag(key)}"
            shutil.rmtree(d, ignore_errors=True)
            d.mkdir(parents=True)
            copy = d / os.path.basename(e["file"])
            shutil.copyfile(os.path.join(q.ROOT, bc), copy)
            row = [q.rel(str(d)), e["seg"], e["func"], q.rel(str(copy)), e["file"], key, str(best)]
            try:
                permute.batch_row(row, pass_dir, argparse.Namespace(j=self.a.j, seconds=secs), self.plock)
                res = json.loads((d / "result.json").read_text())
                entry = {"pass": n, "seconds": secs, **{k: res.get(k) for k in ("base", "best", "zeros", "error")}}
            except Exception as ex:
                entry = {"pass": n, "error": f"{type(ex).__name__}: {ex}"}
        with self.lock:
            if self.stopping:
                return
            e["permute"].append(entry)
            self.save()

    def snapshot_headers(self, n):
        out = os.path.join(HUNT, f"pass{n}", "headers")
        if os.path.isdir(os.path.join(out, "include")):
            return
        for d in ("include", os.path.join("assets", "inc")):
            if os.path.isdir(os.path.join(q.ROOT, d)):
                shutil.copytree(os.path.join(q.ROOT, d), os.path.join(out, d), dirs_exist_ok=True)

    # ------------------------------------------------------------ passes

    def plan(self, fns, n):
        sites = self.st["sites"]
        rec = [(p, fn["name"]) for p, fn in fns if "recipes" in self.stages
               and not all(sites[s["key"]]["recipes"]["done"] for s in fake_sites(fn))]
        keys = [s["key"] for _, fn in fns for s in fake_sites(fn)]
        as1 = [k for k in keys if "as1" in self.stages and not sites[k]["as1"]["done"]]
        per = [k for k in keys if "permute" in self.stages and not any(p["pass"] == n for p in sites[k]["permute"])]
        return rec, as1, per

    def pool(self, jobs):
        """Run JOBS [(label, fn, args)] --parallel at a time; a job's exception is printed, not raised."""
        if not jobs:
            return
        ex = ThreadPoolExecutor(max(1, self.a.parallel))
        self.ex = ex
        futs = {ex.submit(f, *args): label for label, f, args in jobs}
        for fut in as_completed(futs):
            try:
                fut.result()
            except Exception as err:
                print(f"ERROR {futs[fut]}: {type(err).__name__}: {err}", flush=True)
        ex.shutdown()
        self.ex = None

    def run_pass(self, fns, n):
        """Run pass N's remaining jobs for FNS stage by stage; the number of jobs started."""
        rec, as1, per = self.plan(fns, n)
        if self.a.dry_run:
            for _, name in rec:
                print(f"RECIPES {name}")
            for k in as1:
                print(f"AS1 {k}")
            for k in per:
                print(f"PERMUTE {k} seconds={self.seconds(n)}")
            return len(rec) + len(as1) + len(per)
        self.pool([(f"RECIPES {name}", self.job_recipes, (p, name)) for p, name in rec])
        _, as1, per = self.plan(fns, n)  # recipes may have finished: as1 needs their best candidate
        as1 = [k for k in as1 if self.st["sites"][k]["recipes"]["done"]]
        self.pool([(f"AS1 {k}", self.job_as1, (k,)) for k in as1])
        if per:
            self.snapshot_headers(n)
        self.pool([(f"PERMUTE {k}", self.job_permute, (k, n)) for k in per])
        return len(rec) + len(as1) + len(per)


def descendants():
    """PIDs of this process's live job descendants (zombies and multiprocessing's resource tracker, which
    ignores SIGINT/SIGTERM and exits with this process, excluded), from one process-table snapshot."""
    kids = nt_children() if os.name == "nt" else ps_children()
    found, todo = [], [os.getpid()]
    while todo:
        for c in kids.get(todo.pop(), ()):
            found.append(c)
            todo.append(c)
    return found


def ps_children():
    """{ppid: [pid]} of one `ps` snapshot (the ps itself, zombies and the resource tracker left out)."""
    ps = subprocess.Popen(["ps", "-Ao", "pid=,ppid=,stat=,command="], stdout=subprocess.PIPE, text=True)
    out = ps.communicate()[0]
    kids = collections.defaultdict(list)
    for line in out.splitlines():
        f = line.split(None, 3)
        if (len(f) >= 3 and int(f[0]) != ps.pid and not f[2].startswith("Z")
                and "multiprocessing.resource_tracker" not in (f[3] if len(f) > 3 else "")):
            kids[int(f[1])].append(int(f[0]))
    return kids


def nt_children():
    """{ppid: [pid]} of one Toolhelp32 process snapshot: Windows has no `ps` (and no zombies, no
    resource tracker). Windows reuses a dead parent's PID, so a process created before the live
    process its parent PID names now is no child of it (and one whose times cannot be read is none
    of ours: this process can query every process it started)."""
    import ctypes
    from ctypes import wintypes

    class Entry(ctypes.Structure):
        _fields_ = [("dwSize", wintypes.DWORD), ("cntUsage", wintypes.DWORD), ("th32ProcessID", wintypes.DWORD),
                    ("th32DefaultHeapID", ctypes.c_size_t), ("th32ModuleID", wintypes.DWORD),
                    ("cntThreads", wintypes.DWORD), ("th32ParentProcessID", wintypes.DWORD),
                    ("pcPriClassBase", wintypes.LONG), ("dwFlags", wintypes.DWORD),
                    ("szExeFile", wintypes.WCHAR * 260)]

    k32 = ctypes.WinDLL("kernel32", use_last_error=True)
    k32.CreateToolhelp32Snapshot.restype = wintypes.HANDLE
    k32.CreateToolhelp32Snapshot.argtypes = (wintypes.DWORD, wintypes.DWORD)
    k32.Process32FirstW.argtypes = k32.Process32NextW.argtypes = (wintypes.HANDLE, ctypes.POINTER(Entry))
    k32.OpenProcess.restype = wintypes.HANDLE
    k32.OpenProcess.argtypes = (wintypes.DWORD, wintypes.BOOL, wintypes.DWORD)
    k32.GetProcessTimes.argtypes = (wintypes.HANDLE, *[ctypes.POINTER(ctypes.c_ulonglong)] * 4)
    k32.CloseHandle.argtypes = (wintypes.HANDLE,)
    snap = k32.CreateToolhelp32Snapshot(0x2, 0)  # TH32CS_SNAPPROCESS
    if snap is None or snap == wintypes.HANDLE(-1).value:
        raise ctypes.WinError(ctypes.get_last_error())
    pairs = []
    try:
        e = Entry(dwSize=ctypes.sizeof(Entry))
        ok = k32.Process32FirstW(snap, ctypes.byref(e))
        while ok:
            pairs.append((e.th32ProcessID, e.th32ParentProcessID))
            ok = k32.Process32NextW(snap, ctypes.byref(e))
    finally:
        k32.CloseHandle(snap)
    born = {}

    def created(pid):
        if pid not in born:
            born[pid] = None
            h = k32.OpenProcess(0x1000, False, pid)  # PROCESS_QUERY_LIMITED_INFORMATION
            if h:
                t = [ctypes.c_ulonglong() for _ in range(4)]
                if k32.GetProcessTimes(h, *map(ctypes.byref, t)):
                    born[pid] = t[0].value
                k32.CloseHandle(h)
        return born[pid]

    alive = {pid for pid, _ in pairs}
    kids = collections.defaultdict(list)
    for pid, ppid in pairs:
        if ppid in alive and pid != ppid:
            child, parent = created(pid), created(ppid)
            if child is not None and parent is not None and child >= parent:
                kids[ppid].append(pid)
    return kids


def stop_children(grace=30):
    """SIGINT every descendant (a tools/dk client forwards it to its container job, so the permuter or
    scorer stops there too), then SIGTERM and SIGKILL what is still alive after GRACE seconds each;
    returns once none is left, so a resumed run never shares a run directory with a live job. On
    Windows every os.kill is TerminateProcess (no SIGKILL there; the first round ends each process):
    a killed tools/dk client forwards nothing, and the dkd server kills its container job (SIGTERM,
    SIGKILL 2 s later, then frees its lock) once it sees the connection drop, which Docker Desktop's
    port forward delivers some 10-15 s later; so it then waits, up to GRACE, until the server lists
    no job of a killed client (`client_jobs`)."""
    gone = OSError if os.name == "nt" else ProcessLookupError  # nt: an exited PID gives WinError 5/87
    killed = set()
    for sig in (signal.SIGINT, signal.SIGTERM, getattr(signal, "SIGKILL", signal.SIGTERM)):
        pids = descendants()
        if not pids:
            break
        killed.update(pids)
        for p in pids:
            try:
                os.kill(p, sig)
            except gone:
                pass
        end = time.monotonic() + grace
        while time.monotonic() < end and descendants():
            time.sleep(0.5)
    if os.name == "nt" and killed:
        end = time.monotonic() + grace
        while time.monotonic() < end and client_jobs(killed):
            time.sleep(0.5)


def client_jobs(pids):
    """`tools/dk --status` lines (granted, waiting, jobs) of requests whose client is one of PIDS: the
    client names its PID in each request (`<desc> [pid N]`)."""
    r = subprocess.run(dk_argv("--status"), cwd=q.ROOT, capture_output=True, text=True, errors="replace")
    return [l for l in r.stdout.splitlines() if (m := re.search(r"\[pid (\d+)\]$", l)) and int(m.group(1)) in pids]


def cmd_run(a):
    h = Hunter(a)
    if a.hours:
        h.deadline = time.monotonic() + a.hours * 3600
    filtered = bool(a.seg or a.file or a.func)
    try:
        while True:
            fns = h.collect()
            if not fns:
                print("NO FAKE SITES")
                return 0
            n = h.st["pass"]
            started = h.run_pass(fns, n)
            if a.dry_run:
                return 0
            if h.expired():
                print(f"TIME UP pass={n}")
                return 0
            if "permute" not in h.stages:
                print(f"DONE pass={n} ({started} jobs)")
                return 0
            sites = h.st["sites"]
            done = all(any(p["pass"] == n for p in sites[s["key"]]["permute"]) for _, fn in fns for s in fake_sites(fn))
            if done and not filtered:
                with h.lock:
                    h.st["pass"] = n + 1
                    h.save()
                print(f"PASS {n} DONE", flush=True)
                continue
            if done or not started:
                print(f"DONE pass={n} ({started} jobs; the pass counter advances in an unfiltered run)")
                return 0
    except KeyboardInterrupt:
        signal.signal(signal.SIGINT, signal.SIG_IGN)  # a second Ctrl-C must not cut the cleanup short
        h.stopping = True  # running jobs commit nothing more and start no further job
        print("INTERRUPTED: stopping child jobs ...", flush=True)
        workers = threading.Thread(target=lambda: h.ex and h.ex.shutdown(wait=True, cancel_futures=True))
        workers.start()
        while workers.is_alive():  # a job may start its next subprocess (scan after keep, run after setup)
            stop_children()
            workers.join(0.5)
        stop_children()
        with h.lock:
            h.save()
        print(f"INTERRUPTED pass={h.st['pass']}", flush=True)
        return 130


def site_line(k, e):
    r = e["recipes"]
    rec = ("-" if r["best"] is None else str(r["best"])) if r["done"] else "-"
    perm = ",".join(f"{p['pass']}:{'err' if p.get('error') else p.get('best')}" for p in e["permute"]) or "-"
    as1 = "-" if e["as1"]["rc"] is None else str(e["as1"]["rc"])
    return f"{k} {e['func']} recipes={rec}({len(r['hits'])} hits) as1={as1} permute={perm}"


def cmd_status(a):
    st = load_state()
    sites = {k: e for k, e in sorted(st["sites"].items()) if not a.func or e["func"] == a.func}
    for k, e in sites.items():
        print(site_line(k, e))
    print(f"pass={st['pass']} sites={len(sites)} hits={sum(len(e['recipes']['hits']) for e in sites.values())} "
          f"zeros={sum(len(p.get('zeros') or []) for e in sites.values() for p in e['permute'])}")
    return 0


def cmd_hits(a):
    st = load_state()
    files = sorted({e["file"] for e in st["sites"].values() if os.path.exists(os.path.join(q.ROOT, e["file"]))})
    if not files:
        return 0
    ans = q.analyze_many(files)
    present = {s["key"] for an in ans for fn in an["functions"] for s in fake_sites(fn)}
    sha = {f: sha1_of(f) for f in files}
    for k, e in sorted(st["sites"].items()):
        if k not in present:
            continue
        if sha.get(e["file"]) == e["src_sha1"]:
            for p in e["recipes"]["hits"]:
                if os.path.exists(os.path.join(q.ROOT, p)):
                    print(f"HIT {k} {e['func']} {e['file']} {p}")
        for p in e["permute"]:
            for z in p.get("zeros") or ():
                print(f"ZERO-PERMUTE {k} {e['func']} {e['file']} {z}")
    return 0


def cmd_show(a):
    st = load_state()
    sites = {k: e for k, e in sorted(st["sites"].items()) if e["func"] == a.func}
    if not sites:
        print(f"{a.func}: not hunted yet (pass={st['pass']})")
        return 0
    for k, e in sites.items():
        r = e["recipes"]
        print(f"{k} {e['func']} {e['file']} fp={e['fp']}")
        print(f"  recipes: done={r['done']} best={r['best']} best_copy={r['best_copy'] or '-'}")
        for p in r["hits"]:
            print(f"  hit: {p}")
        out = e["as1"]["out"]
        print(f"  as1: done={e['as1']['done']} rc={e['as1']['rc']} out={out or '-'}")
        if out and os.path.exists(os.path.join(q.ROOT, out)):
            for line in open(os.path.join(q.ROOT, out), errors="replace").read().splitlines()[:20]:
                print(f"    {line}")
        for p in e["permute"]:
            if p.get("error"):
                print(f"  permute pass {p['pass']}: error {p['error']}")
            else:
                print(f"  permute pass {p['pass']}: seconds={p.get('seconds')} base={p.get('base')} best={p.get('best')}"
                      f" zeros={len(p.get('zeros') or [])}")
                for z in p.get("zeros") or ():
                    print(f"    zero: {z}")
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("run")
    p.add_argument("--seg")
    p.add_argument("--file")
    p.add_argument("--func")
    p.add_argument("--stages", default=",".join(STAGES))
    p.add_argument("--parallel", type=int, default=3)
    p.add_argument("-j", type=int, default=2)
    p.add_argument("--seconds", type=int)
    p.add_argument("--hours", type=float, default=0)
    p.add_argument("--dry-run", action="store_true")
    p = sub.add_parser("status")
    p.add_argument("--func")
    sub.add_parser("hits")
    p = sub.add_parser("show")
    p.add_argument("func")
    a = ap.parse_args(argv)
    return {"run": cmd_run, "status": cmd_status, "hits": cmd_hits, "show": cmd_show}[a.cmd](a)


if __name__ == "__main__":
    sys.exit(main())
