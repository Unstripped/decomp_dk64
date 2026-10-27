"""End-to-end tests of the real dkd client/server (tools/dk -> tools/dkd/client.py -> container).

Run on the host (Docker + image `dk64-decomp` required, otherwise the module is skipped):

    uv run --python 3.12 --with pytest --with hypothesis pytest tools/dkd/tests/test_integration.py

Only the OBSERVABLE contract (CLI behaviour + pinned wire protocol, see the design contract) is
exercised; nothing here imports client/server internals.

Harness
-------
Every root is an isolated fake repo `<worktree>/.scratch/dkd-tests/<uuid>/` holding a copy of
`tools/dk`, `tools/dkd/` (without tests/) and the fixture tree `stress_fixture/` (Makefile, fx/
helper scripts, a fake `splat` package, a fake `tools/permute.py`, `.scratch/sub/Makefile`).  A
fake root hashes to its own container name, so it gets its own server; teardown stops that server
(`tools/dk --stop`), force-removes ONLY containers whose label `dk64.root` equals the fake root
(re-verified per container before `docker rm -f`), and deletes the directory.  An atexit sweep
repeats this for roots whose fixture teardown never ran.

Lock observation: fixture jobs append `START|END <kind> <id> <monotonic ns>` lines (one O_APPEND
write each) to `<root>/.evlog/events.log` (kind = shared | exclusive | keyed:<key> | unlocked |
none).  CLOCK_MONOTONIC is shared by all containers of the Docker VM, so intervals logged by
different servers are comparable.  An interval is logged INSIDE the lock, so "no overlap" is a
necessary condition of lock safety, never a sufficient one; the deterministic compatibility matrix
(`test_compatibility_matrix`) covers the converse (compatible jobs really run concurrently, so a
server that simply serialises everything fails).  Jobs nested under one `--hold` lease share a
group (id prefix before the first '.') and may overlap each other, never anyone else.

Invariant -> check
------------------
* byte-exact streams / exit status / 127 / stdin / env / cwd: `test_stream_bytes_exact` (hypothesis,
  random binary chunks, <=256 KiB, random stdout/stderr interleaving), `test_exit_status_passthrough`
  (hypothesis), `test_*` in section 1.
* private /tmp: `test_private_tmp_isolation` (concurrent jobs, proven concurrent by overlapping
  intervals; later job sees empty /tmp).
* lock safety under concurrency: `test_lock_safety_random_schedules` (hypothesis; parses the interval
  log: exclusive vs any other group, keyed vs keyed on the same key); all jobs exit 0 with stdout
  exactly the job's bytes and stderr only `dk: waiting for ...` notices.
* writer preference / no starvation / single waiting notice: `test_writer_preference_*`.
* kill on disconnect: `test_kill_on_disconnect_*` (heartbeat file written every 0.1 s by a setsid'ed
  grandchild stops within 3 s of the kill; /proc scan inside the container finds no process of the
  job; a following exclusive job runs promptly).
* leases: `test_lease_*`.   startup race / recovery / retire / throughput: the same-named tests.
* regressions: `test_retire_during_lease_does_not_deadlock` (code change while a hold runs),
  `test_parallel_makes_in_job_vs_external_exclusive` (upgrade-path release/request gap, interval log),
  `test_shim_wait_prints_exactly_one_notice`, `test_slow_reader_gets_all_bytes` (4 MiB, 12 s late reader).
* containers are found by label `dk64.root` (re-verified per container); the name/`dk64.rootid` label
  are checked once, in `test_startup_race_single_container`, against sha256("<st_dev>:<st_ino>")[:12].

Python note: the host client must run on the host's python3 (3.9, mise); the pytest venv is
removed from PATH for every client subprocess so `python3` resolves like it does for agents.
"""
import atexit
import dataclasses
import hashlib
import json
import os
import random
import re
import shutil
import signal
import statistics
import subprocess
import sys
import threading
import time
import uuid
from pathlib import Path
from typing import Callable, List, Optional, Tuple

import pytest
from hypothesis import HealthCheck, Phase, example, given, settings
from hypothesis import strategies as st

IMAGE = "dk64-decomp"
HERE = Path(__file__).resolve().parent
WORKTREE = HERE.parents[2]
FIXTURE = HERE / "stress_fixture"
BASE = WORKTREE / ".scratch" / "dkd-tests"

WAIT_RE = re.compile(r"^dk: waiting for (shared|keyed|exclusive) lock( \(held by: .*\))?$")


def _skip_reason() -> Optional[str]:
    if shutil.which("docker") is None:
        return "docker is not available"
    try:
        probe = subprocess.run(["docker", "image", "inspect", IMAGE], stdout=subprocess.DEVNULL,
                               stderr=subprocess.DEVNULL, timeout=60)
    except (OSError, subprocess.TimeoutExpired):
        return "docker daemon is not usable"
    if probe.returncode != 0:
        return "docker image %s is missing" % IMAGE
    if not (WORKTREE / "tools" / "dk").is_file() or not (WORKTREE / "tools" / "dkd").is_dir():
        return "tools/dk or tools/dkd not found at %s" % WORKTREE
    return None


_reason = _skip_reason()
if _reason:
    pytest.skip(_reason, allow_module_level=True)


# --------------------------------------------------------------------------------------------
# docker helpers
# --------------------------------------------------------------------------------------------

def docker(*args: str, timeout: float = 60) -> subprocess.CompletedProcess:
    return subprocess.run(["docker", *args], stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                          stdin=subprocess.DEVNULL, timeout=timeout)


def _client_env(extra: Optional[dict] = None) -> dict:
    """Environment for host-side client processes: like an agent's shell, minus the pytest venv."""
    env = dict(os.environ)
    for key in ("DK64_LEASE", "DK64_IMAGE", "VIRTUAL_ENV", "PYTHONPATH", "PYTHONHOME"):
        env.pop(key, None)
    original = env.get("PATH", "")
    in_venv = sys.prefix != sys.base_prefix

    def injected(p: str) -> bool:  # the pytest venv and uv's `--with` overlay put their bin dirs first
        return (in_venv and p.startswith(sys.prefix)) or "/.cache/uv/" in p

    kept = [p for p in original.split(os.pathsep) if p and not injected(p)]
    cleaned = os.pathsep.join(kept)
    env["PATH"] = cleaned if shutil.which("python3", path=cleaned) else original
    if extra:
        env.update(extra)
    return env


@dataclasses.dataclass
class Result:
    rc: int
    out: bytes
    err: bytes

    def text(self) -> str:
        return "rc=%r\nstdout=%r\nstderr=%r" % (self.rc, self.out[:2000], self.err[:2000])


_LIVE_ROOTS: List["Root"] = []


class Root:
    """One isolated fake repo root (and therefore one dkd server)."""

    def __init__(self, path: Path):
        self.path = path
        self.dk_bin = str(path / "tools" / "dk")
        self.log = path / ".evlog" / "events.log"
        st = os.stat(path)
        self.rootid = "%d:%d" % (st.st_dev, st.st_ino)
        self.expected_name = "dk64-" + hashlib.sha256(self.rootid.encode()).hexdigest()[:12]
        self.procs: List[subprocess.Popen] = []
        self.cleaned = False

    # ---- running clients -------------------------------------------------------------------
    def env(self, extra: Optional[dict] = None) -> dict:
        return _client_env(extra)

    def dk(self, *args: str, timeout: float = 120, env: Optional[dict] = None,
           input: Optional[bytes] = None, cwd: Optional[str] = None) -> Result:
        kwargs = {"stdin": subprocess.DEVNULL} if input is None else {"input": input}
        try:
            done = subprocess.run([self.dk_bin, *args], cwd=cwd or str(self.path), env=self.env(env),
                                  stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=timeout,
                                  **kwargs)
        except subprocess.TimeoutExpired as exc:
            pytest.fail("tools/dk %r timed out after %ss\nstdout=%r\nstderr=%r"
                        % (args, timeout, (exc.stdout or b"")[:2000], (exc.stderr or b"")[:2000]))
        return Result(done.returncode, done.stdout, done.stderr)

    def popen(self, *args: str, env: Optional[dict] = None, cwd: Optional[str] = None) -> subprocess.Popen:
        proc = subprocess.Popen([self.dk_bin, *args], cwd=cwd or str(self.path), env=self.env(env),
                                stdin=subprocess.DEVNULL, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                start_new_session=True)
        self.procs.append(proc)
        return proc

    def finish(self, proc: subprocess.Popen, timeout: float = 120) -> Result:
        try:
            out, err = proc.communicate(timeout=timeout)
        except subprocess.TimeoutExpired:
            _killpg(proc)
            out, err = proc.communicate()
            pytest.fail("client %r timed out after %ss\nstdout=%r\nstderr=%r"
                        % (proc.args[1:], timeout, out[:2000], err[:2000]))
        return Result(proc.returncode, out, err)

    def finish_all(self, procs: List[subprocess.Popen], timeout: float = 180) -> List[Result]:
        deadline = time.monotonic() + timeout
        return [self.finish(p, max(1.0, deadline - time.monotonic())) for p in procs]

    def warm(self) -> None:
        res = self.dk("true", timeout=300)
        assert res.rc == 0, "cannot start dkd server: " + res.text()

    # ---- event log -------------------------------------------------------------------------
    def log_lines(self) -> List[str]:
        try:
            raw = self.log.read_bytes().decode("utf-8", "replace")
        except FileNotFoundError:
            return []
        return raw.split("\n")[:-1]  # drop a trailing partial line

    def wait_log(self, prefix: str, timeout: float = 90) -> None:
        wait_until(lambda: any(l.startswith(prefix + " ") for l in self.log_lines()), timeout,
                   "log line %r never appeared" % prefix)

    def intervals(self, ids=None) -> List["Iv"]:
        """Complete START/END intervals; with `ids`, exactly those ids must be present and complete."""
        starts = {}
        done = {}
        for line in self.log_lines():
            phase, kind, ident, ns = line.split(" ")
            if phase == "START":
                assert ident not in starts, "duplicate START for %s" % ident
                starts[ident] = (kind, int(ns))
            else:
                assert phase == "END" and ident in starts and starts[ident][0] == kind and ident not in done, \
                    "bad END line %r" % line
                done[ident] = int(ns)
        wanted = list(starts) if ids is None else sorted(ids)
        out = []
        for ident in wanted:
            assert ident in starts, "job %s never logged START" % ident
            assert ident in done, "job %s never logged END" % ident
            out.append(Iv(starts[ident][0], ident, starts[ident][1], done[ident]))
        return out

    # ---- containers ------------------------------------------------------------------------
    def containers(self) -> List[Tuple[str, str, str]]:
        """(id, name, state) of every container (any state) labelled dk64.root=<this root>."""
        res = docker("ps", "-a", "--no-trunc", "--filter", "label=dk64.root=%s" % self.path,
                     "--format", "{{.ID}}\t{{.Names}}\t{{.State}}")
        rows = []
        for line in res.stdout.decode().splitlines():
            cid, name, state = line.split("\t")
            label = docker("inspect", "--format", '{{index .Config.Labels "dk64.root"}}', cid)
            if label.returncode == 0 and label.stdout.decode().strip() == str(self.path):
                rows.append((cid, name, state))
        return rows

    def server_id(self) -> Optional[str]:
        """Container id of the live (running, non-retired) server for this root, found by label."""
        for cid, name, state in self.containers():
            if "-retired-" not in name and state == "running":
                return cid
        return None

    def server_name(self) -> str:
        for _cid, name, state in self.containers():
            if "-retired-" not in name and state == "running":
                return name
        pytest.fail("no running server container for %s: %r" % (self.path, self.containers()))

    def exec_scan(self, token: str) -> str:
        """Processes inside the server container whose cmdline contains `token` (empty = none)."""
        script = ("import os\ntok=os.environ['TOK']\nme=os.getpid()\n"
                  "for p in os.listdir('/proc'):\n"
                  "  if p.isdigit() and int(p)!=me:\n"
                  "    try: c=open('/proc/'+p+'/cmdline','rb').read().replace(b'\\0',b' ').decode('utf8','replace')\n"
                  "    except OSError: continue\n"
                  "    if tok in c: print(p,c)\n")
        res = docker("exec", "-e", "TOK=" + token, self.server_name(), "python3", "-c", script, timeout=60)
        assert res.returncode == 0, "docker exec scan failed: %r" % res.stderr
        return res.stdout.decode()

    def container_now_ns(self) -> int:
        res = docker("exec", self.server_name(), "python3", "-c", "import time;print(time.monotonic_ns())", timeout=60)
        assert res.returncode == 0, res.stderr
        return int(res.stdout)

    def status_text(self) -> str:
        return self.dk("--status", timeout=60).out.decode("utf-8", "replace")

    # ---- cleanup ---------------------------------------------------------------------------
    def cleanup(self) -> None:
        if self.cleaned:
            return
        self.cleaned = True
        for proc in self.procs:
            _killpg(proc)
        try:
            subprocess.run([self.dk_bin, "--stop"], cwd=str(self.path), env=self.env(), timeout=45,
                           stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        except (OSError, subprocess.TimeoutExpired):
            pass
        for cid, _name, _state in self.containers():  # labels re-verified inside containers()
            docker("rm", "-f", cid, timeout=60)
        shutil.rmtree(self.path, ignore_errors=True)
        if self.path.exists():  # files created as root inside the container
            docker("run", "--rm", "-v", "%s:/p" % self.path.parent, IMAGE, "rm", "-rf", "/p/" + self.path.name,
                   timeout=120)
            shutil.rmtree(self.path, ignore_errors=True)
        if self in _LIVE_ROOTS:
            _LIVE_ROOTS.remove(self)


def _killpg(proc: subprocess.Popen) -> None:
    try:
        os.killpg(proc.pid, signal.SIGKILL)
    except (ProcessLookupError, PermissionError):
        pass


@atexit.register
def _sweep() -> None:
    for root in list(_LIVE_ROOTS):
        root.cleanup()


def create_root() -> Root:
    BASE.mkdir(parents=True, exist_ok=True)
    path = BASE / uuid.uuid4().hex[:16]
    path.mkdir()
    path = Path(os.path.realpath(path))
    root = Root(path)
    _LIVE_ROOTS.append(root)
    (path / "tools").mkdir()
    shutil.copy2(WORKTREE / "tools" / "dk", path / "tools" / "dk")
    shutil.copytree(WORKTREE / "tools" / "dkd", path / "tools" / "dkd",
                    ignore=shutil.ignore_patterns("tests", "__pycache__"))
    shutil.copytree(FIXTURE, path, dirs_exist_ok=True, ignore=shutil.ignore_patterns("__pycache__"))
    (path / ".evlog").mkdir(exist_ok=True)
    (path / ".payload").mkdir(exist_ok=True)
    return root


@pytest.fixture(scope="module")
def shared_root():
    root = create_root()
    try:
        root.warm()
        yield root
    finally:
        root.cleanup()


@pytest.fixture
def fresh_root():
    root = create_root()
    try:
        yield root
    finally:
        root.cleanup()


# --------------------------------------------------------------------------------------------
# generic helpers
# --------------------------------------------------------------------------------------------

def wait_until(pred: Callable[[], bool], timeout: float, message: str, step: float = 0.05) -> None:
    deadline = time.monotonic() + timeout
    while True:
        if pred():
            return
        if time.monotonic() > deadline:
            pytest.fail("timeout after %ss: %s" % (timeout, message))
        time.sleep(step)


@dataclasses.dataclass(frozen=True)
class Iv:
    kind: str
    ident: str
    start: int
    end: int

    @property
    def group(self) -> str:
        return self.ident.split(".")[0]


def overlap(a: Iv, b: Iv) -> bool:
    return a.start < b.end and b.start < a.end


def safety_violations(ivs: List[Iv]) -> List[str]:
    """Interval-log lock safety: exclusive vs any other group; keyed vs keyed on the same key."""
    problems = []
    ivs = [iv for iv in ivs if iv.kind != "none"]
    for i, a in enumerate(ivs):
        for b in ivs[i + 1:]:
            if a.group == b.group or not overlap(a, b):
                continue
            if "exclusive" in (a.kind, b.kind):
                problems.append("exclusive overlap: %s vs %s" % (a, b))
            elif a.kind.startswith("keyed:") and a.kind == b.kind:
                problems.append("keyed overlap: %s vs %s" % (a, b))
    return problems


def done(ident: str) -> bytes:
    return ("done %s\n" % ident).encode()


def make_cmd(ident: str, seconds, *goals: str) -> List[str]:
    """dk argv running the fixture make with ID/SLEEP passed through `env`.

    Command-line VAR=value assignments make dkd classify the build as exclusive (only a small
    allowlist like CFLAGS/CC is keyed-safe), so the fixture parameters travel in the environment.
    """
    return ["env", "ID=%s" % ident, "SLEEP=%s" % seconds, "make", *goals]


def make_sh(ident: str, seconds, *goals: str) -> str:
    """Shell-string form of make_cmd for `sh -c` jobs."""
    return " ".join(["ID=%s" % ident, "SLEEP=%s" % seconds, "make", *goals])


def notice_lines(err: bytes) -> List[str]:
    return err.decode("utf-8", "replace").splitlines()


def assert_only_notices(res: Result, what: str) -> None:
    bad = [l for l in notice_lines(res.err) if not WAIT_RE.match(l)]
    assert not bad, "%s: unexpected stderr lines %r" % (what, bad)


def assert_bytes_equal(actual: bytes, expected: bytes, label: str) -> None:
    if actual == expected:
        return
    first = next((i for i, (x, y) in enumerate(zip(actual, expected)) if x != y), min(len(actual), len(expected)))
    pytest.fail("%s differs: len %d vs expected %d, first difference at byte %d"
                % (label, len(actual), len(expected), first))


def wait_queued(root: Root, needle: str, timeout: float = 6) -> bool:
    """Best effort: poll `tools/dk --status` until `needle` shows up (format is a debug aid)."""
    deadline = time.monotonic() + timeout
    while time.monotonic() < deadline:
        if needle in root.status_text():
            return True
        time.sleep(0.2)
    return False


HYP = dict(deadline=None, database=None, suppress_health_check=list(HealthCheck),
           phases=[Phase.explicit, Phase.generate])


# --------------------------------------------------------------------------------------------
# 1. basic fidelity
# --------------------------------------------------------------------------------------------

def _rand_bytes(seed: int, n: int) -> bytes:
    return random.Random(seed).getrandbits(8 * n).to_bytes(n, "little") if n else b""


chunk_st = st.tuples(st.sampled_from([1, 2]), st.one_of(st.integers(0, 16), st.integers(0, 65536)),
                     st.integers(0, 2 ** 32 - 1))
payload_st = st.lists(chunk_st, min_size=1, max_size=8).filter(lambda cs: sum(c[1] for c in cs) <= 256 * 1024)


@settings(max_examples=15, **HYP)
@given(chunks=payload_st)
@example(chunks=[(1, 262144, 1)])
@example(chunks=[(2, 262144, 2)])
@example(chunks=[(1, 10, 1), (2, 10, 2), (1, 100000, 3), (2, 70000, 4), (1, 0, 5), (2, 65536, 6)])
def test_stream_bytes_exact(shared_root, chunks):
    blobs = [(fd, _rand_bytes(seed, n)) for fd, n, seed in chunks]
    spec = b"".join(bytes([fd]) + len(data).to_bytes(4, "big") + data for fd, data in blobs)
    name = ".payload/%s.bin" % uuid.uuid4().hex
    (shared_root.path / name).write_bytes(spec)
    try:
        res = shared_root.dk("python3", "fx/emit.py", name, timeout=120)
    finally:
        (shared_root.path / name).unlink()
    assert res.rc == 0, res.text()
    assert_bytes_equal(res.out, b"".join(d for fd, d in blobs if fd == 1), "stdout")
    assert_bytes_equal(res.err, b"".join(d for fd, d in blobs if fd == 2), "stderr")


@settings(max_examples=12, **HYP)
@given(code=st.integers(0, 255))
@example(code=0)
@example(code=1)
@example(code=125)
@example(code=126)
@example(code=130)
@example(code=255)
def test_exit_status_passthrough(shared_root, code):
    res = shared_root.dk("sh", "-c", "exit %d" % code)
    assert res.rc == code, res.text()


def test_signal_death_and_command_not_found(shared_root):
    # The server runs a tini-style init as PID 1 of the job's namespace, so the job is never the
    # namespace init: a self-sent TERM kills it (143) and a kernel-raised SIGSEGV gives 139.
    term = shared_root.dk("sh", "-c", "kill -TERM $$")
    assert term.rc == 128 + signal.SIGTERM, term.text()
    seg = shared_root.dk("python3", "-c", "import ctypes; ctypes.string_at(0)")
    assert seg.rc == 128 + signal.SIGSEGV, seg.text()
    missing = shared_root.dk("definitely-not-a-command-%s" % uuid.uuid4().hex[:8])
    assert missing.rc == 127, missing.text()
    assert shared_root.dk("sh", "-c", "definitely-not-a-command-xyz").rc == 127


def test_stdin_is_dev_null(shared_root):
    res = shared_root.dk("sh", "-c", "cat | wc -c; readlink /proc/self/fd/0", input=b"host stdin must not leak\n")
    assert res.rc == 0, res.text()
    assert res.out.split() == [b"0", b"/dev/null"], res.text()


def test_host_env_not_leaked_but_env_command_works(shared_root):
    secret = "leak-" + uuid.uuid4().hex
    res = shared_root.dk("sh", "-c", "printenv DKD_ITEST_SECRET; echo rc=$?; env", env={"DKD_ITEST_SECRET": secret})
    assert res.rc == 0, res.text()
    assert secret.encode() not in res.out and b"DKD_ITEST_SECRET" not in res.out, res.text()
    assert res.out.startswith(b"rc=1\n"), res.text()
    explicit = shared_root.dk("env", "X=1", "sh", "-c", "echo $X")
    assert (explicit.rc, explicit.out) == (0, b"1\n"), explicit.text()


def test_cwd_is_dk64_from_any_host_cwd(shared_root):
    for cwd in (str(shared_root.path), "/", str(shared_root.path / "tools")):
        res = shared_root.dk("sh", "-c", "pwd; test -f fx/ev.py && echo seen", cwd=cwd)
        assert (res.rc, res.out) == (0, b"/dk64\nseen\n"), "cwd=%s %s" % (cwd, res.text())


# --------------------------------------------------------------------------------------------
# 2. private /tmp
# --------------------------------------------------------------------------------------------

def test_private_tmp_isolation(shared_root):
    r = shared_root
    tags = [uuid.uuid4().hex[:8] for _ in range(2)]
    procs = [r.popen("python3", "fx/tmpjob.py", tag, "2") for tag in tags]
    results = r.finish_all(procs, 120)
    for tag, res in zip(tags, results):
        assert res.rc == 0, res.text()
        assert json.loads(res.out) == {"tag": tag, "content": tag, "listing": ["f"]}, res.text()
    ivs = r.intervals(["tmp-" + t for t in tags])
    assert overlap(ivs[0], ivs[1]), "jobs did not run concurrently, test proves nothing: %s" % ivs
    later = r.dk("sh", "-c", "ls -A /tmp | wc -l")
    assert (later.rc, later.out.strip()) == (0, b"0"), "a later job saw leftovers in /tmp: " + later.text()


# --------------------------------------------------------------------------------------------
# 3. lock safety under concurrency
# --------------------------------------------------------------------------------------------

sleep_st = st.sampled_from([0.05, 0.1, 0.2, 0.3, 0.4])
key_st = st.sampled_from(["a", "b", "c"])
nested_st = st.one_of(st.tuples(st.just("shared"), sleep_st), st.tuples(st.just("excl"), sleep_st),
                      st.tuples(st.just("keyed"), key_st, sleep_st))
job_st = st.one_of(
    st.tuples(st.just("shared"), sleep_st),
    st.tuples(st.just("excl"), sleep_st),
    st.tuples(st.just("keyed"), key_st, sleep_st),
    st.tuples(st.just("shimup"), key_st, sleep_st),
    st.tuples(st.just("unlocked"), sleep_st),
    st.tuples(st.just("hold"), st.lists(nested_st, min_size=1, max_size=3)),
)
offset_st = st.sampled_from([0.0, 0.05, 0.1, 0.2, 0.3, 0.45, 0.6])
schedule_st = st.lists(st.tuples(job_st, offset_st), min_size=6, max_size=20).filter(
    lambda s: sum(1 for job, _ in s if job[0] == "hold") <= 3)


def _plain_command(root: Root, spec, ident: str):
    """-> (dk args, expected stdout) for one non-lease job spec."""
    kind = spec[0]
    if kind == "shared":
        return ["python3", "fx/ev.py", "run", "shared", ident, str(spec[1])], done(ident)
    if kind == "excl":
        return make_cmd(ident, spec[1]), done(ident)
    if kind == "keyed":
        return make_cmd(ident, spec[2], "build/src/%s.o" % spec[1]), done(ident)
    if kind == "shimup":
        return ["sh", "-c", make_sh(ident, spec[2], "build/src/%s.o" % spec[1])], done(ident)
    if kind == "unlocked":
        return ["sh", "-c", "cd .scratch/sub && " + make_sh(ident, spec[1])], done(ident)
    raise AssertionError(spec)


def _hold_command(root: Root, nested, ident: str):
    """-> (dk args, expected stdout, expected log ids) for a `--hold` job running nested tools/dk calls."""
    lines = ["set -e", 'D="%s"' % root.dk_bin, '"$D" python3 fx/ev.py log START exclusive %s.span' % ident]
    expected = b""
    ids = [ident + ".span"]
    for n, spec in enumerate(nested):
        nid = "%s.%d" % (ident, n)
        args, out = _plain_command(root, spec, nid)
        lines.append('"$D" ' + " ".join(args))
        expected += out
        ids.append(nid)
    lines.append('"$D" python3 fx/ev.py log END exclusive %s.span' % ident)
    return ["--hold", "sh", "-c", "\n".join(lines) + "\n"], expected, ids


@settings(max_examples=10, **HYP)
@given(schedule=schedule_st)
@example(schedule=[
    (("excl", 0.1), 0.0), (("keyed", "a", 0.1), 0.0), (("shimup", "a", 0.1), 0.05),
    (("hold", [("excl", 0.1), ("shared", 0.1), ("keyed", "b", 0.1)]), 0.05),
    (("shared", 0.2), 0.1), (("unlocked", 0.1), 0.1), (("keyed", "b", 0.3), 0.2),
])
def test_lock_safety_random_schedules(shared_root, schedule):
    r = shared_root
    nonce = uuid.uuid4().hex[:6]
    jobs = []  # (offset, dk args, expected stdout, expected ids, label)
    for i, (spec, offset) in enumerate(schedule):
        if spec[0] == "hold":
            ident = "h%s_%d" % (nonce, i)
            args, out, ids = _hold_command(r, spec[1], ident)
        else:
            ident = "j%s_%d" % (nonce, i)
            args, out = _plain_command(r, spec, ident)
            ids = [ident]
        jobs.append((offset, args, out, ids, "%s=%r" % (ident, spec)))
    jobs.sort(key=lambda j: j[0])

    t0 = time.monotonic()
    procs = []
    for offset, args, _out, _ids, _label in jobs:
        delay = t0 + offset - time.monotonic()
        if delay > 0:
            time.sleep(delay)
        procs.append(r.popen(*args))
    results = r.finish_all(procs, 240)

    all_ids = []
    for (offset, args, out, ids, label), res in zip(jobs, results):
        assert res.rc == 0, "%s failed: %s\nschedule=%r" % (label, res.text(), schedule)
        assert res.out == out, "%s stdout %r != %r\nschedule=%r" % (label, res.out, out, schedule)
        assert_only_notices(res, label)
        all_ids.extend(ids)
    ivs = r.intervals(all_ids)
    assert not safety_violations(ivs), "\n".join(safety_violations(ivs)) + "\nschedule=%r" % (schedule,)
    for span in (iv for iv in ivs if iv.ident.endswith(".span")):
        for iv in ivs:
            if iv.group == span.group and iv is not span:
                assert span.start <= iv.start and iv.end <= span.end, "nested job escaped its lease span: %s" % iv


def _job(root: Root, name: str, ident: str, seconds: float):
    return {
        "shared": lambda: ["python3", "fx/ev.py", "run", "shared", ident, str(seconds)],
        "keyed_a": lambda: make_cmd(ident, seconds, "build/src/a.o"),
        "keyed_b": lambda: make_cmd(ident, seconds, "build/src/b.o"),
        "shimup_a": lambda: ["sh", "-c", make_sh(ident, seconds, "build/src/a.o")],
        "excl": lambda: make_cmd(ident, seconds),
        "unlocked": lambda: ["sh", "-c", "cd .scratch/sub && " + make_sh(ident, seconds)],
    }[name]()


MATRIX = [
    ("shared", "shared", True), ("shared", "keyed_a", True), ("keyed_a", "keyed_b", True),
    ("keyed_a", "keyed_a", False), ("keyed_a", "shimup_a", False),
    ("excl", "shared", False), ("excl", "keyed_a", False), ("excl", "excl", False),
    ("unlocked", "shared", True), ("unlocked", "keyed_a", True), ("unlocked", "excl", False),
]


@pytest.mark.parametrize("first,second,concurrent", MATRIX)
def test_compatibility_matrix(shared_root, first, second, concurrent):
    """Compatible jobs MUST overlap (not merely be safe), incompatible ones MUST NOT."""
    r = shared_root
    tag = uuid.uuid4().hex[:6]
    ids = ["m%s_a" % tag, "m%s_b" % tag]
    procs = [r.popen(*_job(r, first, ids[0], 1.2)), r.popen(*_job(r, second, ids[1], 1.2))]
    results = r.finish_all(procs, 120)
    for ident, res in zip(ids, results):
        assert res.rc == 0 and res.out == done(ident), res.text()
    a, b = r.intervals(ids)
    assert overlap(a, b) == concurrent, "%s + %s expected concurrent=%s: %s / %s" % (first, second, concurrent, a, b)


# --------------------------------------------------------------------------------------------
# 4. writer preference / no starvation
# --------------------------------------------------------------------------------------------

def test_writer_preference_and_single_notice(fresh_root):
    r = fresh_root
    r.warm()
    quick = r.dk("python3", "-m", "splat", "run", "Q", "0.1")
    assert (quick.rc, quick.out, quick.err) == (0, done("Q"), b""), "uncontended exclusive must be silent: " + quick.text()

    s1 = r.popen("python3", "fx/ev.py", "run", "shared", "S1", "7")
    r.wait_log("START shared S1")
    e = r.popen("python3", "-m", "splat", "run", "E", "0.5")
    wait_queued(r, "splat")
    time.sleep(0.5)
    later = [r.popen("python3", "fx/ev.py", "run", "shared", "S%d" % n, "0.3") for n in (2, 3, 4)]
    res_e = r.finish(e, 120)
    res_later = [r.finish(p, 120) for p in later]
    res_s1 = r.finish(s1, 120)

    assert (res_s1.rc, res_s1.out, res_s1.err) == (0, done("S1"), b""), res_s1.text()
    assert (res_e.rc, res_e.out) == (0, done("E")), res_e.text()
    lines = notice_lines(res_e.err)
    assert len(lines) == 1 and re.match(r"^dk: waiting for exclusive lock( \(held by: .*\))?$", lines[0]), \
        "exclusive client must print exactly one notice: " + res_e.text()
    assert res_e.err.endswith(b"\n")
    for n, res in zip((2, 3, 4), res_later):
        assert (res.rc, res.out) == (0, done("S%d" % n)), res.text()
        waits = notice_lines(res.err)
        assert len(waits) == 1 and WAIT_RE.match(waits[0]), "S%d must print exactly one notice: %s" % (n, res.text())

    iv = {i.ident: i for i in r.intervals(["S1", "E", "S2", "S3", "S4"])}
    assert iv["E"].start >= iv["S1"].end, "exclusive started while a shared job was running"
    for n in (2, 3, 4):
        assert iv["S%d" % n].start >= iv["E"].end, \
            "shared S%d (queued behind a waiting exclusive) overtook it: %s vs %s" % (n, iv["S%d" % n], iv["E"])


def test_writer_preference_for_make_upgrade(fresh_root):
    """`tools/dk make` starts shared and upgrades to exclusive via the shim; later shared jobs queue behind it."""
    r = fresh_root
    r.warm()
    s1 = r.popen("python3", "fx/ev.py", "run", "shared", "S1", "7")
    r.wait_log("START shared S1")
    x = r.popen(*make_cmd("X", 0.3))
    wait_queued(r, "exclusive")
    time.sleep(0.5)
    s2 = r.popen("python3", "fx/ev.py", "run", "shared", "S2", "0.2")
    res_x, res_s2, res_s1 = r.finish(x, 120), r.finish(s2, 120), r.finish(s1, 120)
    assert (res_x.rc, res_x.out) == (0, done("X")), res_x.text()
    assert (res_s2.rc, res_s2.out) == (0, done("S2")), res_s2.text()
    assert (res_s1.rc, res_s1.out) == (0, done("S1")), res_s1.text()
    assert_only_notices(res_x, "X")
    assert len(notice_lines(res_x.err)) <= 1, "more than one waiting notice: " + res_x.text()
    iv = {i.ident: i for i in r.intervals(["S1", "X", "S2"])}
    assert iv["X"].start >= iv["S1"].end
    assert iv["S2"].start >= iv["X"].end, "shared job overtook a waiting exclusive upgrade"


# --------------------------------------------------------------------------------------------
# 5. kill on disconnect
# --------------------------------------------------------------------------------------------

def _heartbeat_ns(path: Path) -> List[int]:
    try:
        return [int(l) for l in path.read_text().split("\n")[:-1] if l]
    except FileNotFoundError:
        return []


def _assert_job_gone(r: Root, hb: Path, token: str, kill_stamp_ns: int, within: float = 3.0) -> None:
    """Heartbeats must stop within `within` s of the kill and no process of the job may remain."""
    wait_until(lambda: r.container_now_ns() - kill_stamp_ns >= (within + 1.5) * 1e9, 30, "settle", step=0.2)
    beats = _heartbeat_ns(hb)
    last = beats[-1]
    now = r.container_now_ns()
    assert last - kill_stamp_ns <= within * 1e9, \
        "heartbeat kept running %.2fs after the kill" % ((last - kill_stamp_ns) / 1e9)
    assert now - last >= 1.0e9, "heartbeat still alive (last beat %.2fs ago)" % ((now - last) / 1e9)
    wait_until(lambda: not r.exec_scan(token).strip(), 10, "processes of the killed job remain:\n" + r.exec_scan(token))


def _assert_lock_released_promptly(r: Root, limit: float = 10.0) -> None:
    ident = "after-" + uuid.uuid4().hex[:6]
    t0 = time.monotonic()
    res = r.dk(*make_cmd(ident, 0.1), timeout=60)
    took = time.monotonic() - t0
    assert (res.rc, res.out) == (0, done(ident)), res.text()
    assert took < limit, "exclusive job needed %.1fs after the holder died (lock not released promptly)" % took


def test_kill_on_disconnect_sigkill_client(fresh_root):
    r = fresh_root
    r.warm()
    tok = uuid.uuid4().hex[:12]
    hb = r.path / ".evlog" / ("hb-" + tok)
    client = r.popen("env", "HB=.evlog/hb-" + tok, "make", "orphan")  # exclusive job + setsid'ed grandchild
    wait_until(lambda: len(_heartbeat_ns(hb)) >= 3, 60, "heartbeats never started")
    assert r.exec_scan(tok).strip(), "job processes should be visible while it runs"
    stamp = r.container_now_ns()
    client.kill()
    client.wait(timeout=10)
    _assert_lock_released_promptly(r)
    _assert_job_gone(r, hb, tok, stamp)


@pytest.mark.parametrize("sig", [signal.SIGINT, signal.SIGTERM, signal.SIGHUP], ids=lambda s: s.name)
def test_kill_on_signal_forwarded_to_job(fresh_root, sig):
    """Client signal -> forwarded -> job exits 128+N on its own -> client mirrors it; grandchild torn down."""
    r = fresh_root
    r.warm()
    tok = uuid.uuid4().hex[:12]
    hb = r.path / ".evlog" / ("hb-" + tok)
    client = r.popen("python3", "fx/orphan.py", "--trap", ".evlog/hb-" + tok, "120")
    wait_until(lambda: len(_heartbeat_ns(hb)) >= 3, 60, "heartbeats never started")
    stamp = r.container_now_ns()
    client.send_signal(sig)
    res = r.finish(client, 30)
    assert res.rc == 128 + sig, "expected exit %d: %s" % (128 + sig, res.text())
    _assert_lock_released_promptly(r)
    _assert_job_gone(r, hb, tok, stamp)


@pytest.mark.parametrize("sig,status", [(signal.SIGINT, 130), (signal.SIGTERM, 143)], ids=["SIGINT", "SIGTERM"])
def test_signal_to_plain_job_ends_it(fresh_root, sig, status):
    """A job without any signal handling (`sleep`): the namespace init forwards the signal, the job dies
    of it and the client exits 128+N; nothing of the job survives and the lock is free."""
    r = fresh_root
    r.warm()
    tok = "120.%05d" % random.randint(10000, 99999)
    client = r.popen("sleep", tok)
    wait_until(lambda: tok in r.exec_scan(tok), 30, "sleep never started")
    client.send_signal(sig)
    res = r.finish(client, 30)
    assert res.rc == status, res.text()
    wait_until(lambda: not r.exec_scan(tok).strip(), 10, "sleep survived")
    _assert_lock_released_promptly(r)


# --------------------------------------------------------------------------------------------
# 6. leases
# --------------------------------------------------------------------------------------------

def test_lease_reentrant_no_deadlock_and_blocks_others(fresh_root):
    r = fresh_root
    r.warm()
    script = "\n".join([
        "set -e",
        'D="%s"' % r.dk_bin,
        '"$D" python3 fx/ev.py log START exclusive h1.span',
        '"$D" env ID=h1.a SLEEP=0.3 make',
        "sleep 3",
        '"$D" env ID=h1.b SLEEP=0.3 make build/src/a.o',
        '"$D" --hold sh -c \'"$0" env ID=h1.c SLEEP=0.2 make\' "$D"',
        '"$D" python3 fx/ev.py run shared h1.p1 0.8 &',
        '"$D" env ID=h1.p2 SLEEP=0.8 make build/src/b.o &',
        "wait",
        '"$D" python3 fx/ev.py log END exclusive h1.span',
        "",
    ])
    hold = r.popen("--hold", "sh", "-c", script)
    r.wait_log("START exclusive h1.span")
    outsider = r.popen("python3", "fx/ev.py", "run", "shared", "S", "0.2")
    res_hold = r.finish(hold, 120)
    res_s = r.finish(outsider, 120)
    assert res_hold.rc == 0, "nested calls under a lease failed / deadlocked: " + res_hold.text()
    assert_only_notices(res_hold, "hold")
    assert (res_s.rc, res_s.out) == (0, done("S")), res_s.text()
    ivs = {i.ident: i for i in r.intervals(["h1.span", "h1.a", "h1.b", "h1.c", "h1.p1", "h1.p2", "S"])}
    assert ivs["S"].start >= ivs["h1.span"].end, "a shared job ran while the lease was held (incl. gaps between nested calls)"
    for ident in ("h1.a", "h1.b", "h1.c", "h1.p1", "h1.p2"):
        assert ivs["h1.span"].start <= ivs[ident].start and ivs[ident].end <= ivs["h1.span"].end


def test_lease_death_kills_nested_job_and_releases_lock(fresh_root):
    r = fresh_root
    r.warm()
    tok = uuid.uuid4().hex[:12]
    hb = r.path / ".evlog" / ("hb-" + tok)
    script = 'D="%s"\n"$D" python3 fx/orphan.py .evlog/hb-%s 120\necho $? > .evlog/rc-%s\n' % (r.dk_bin, tok, tok)
    hold = r.popen("--hold", "sh", "-c", script)
    wait_until(lambda: len(_heartbeat_ns(hb)) >= 3, 90, "nested job never started")
    stamp = r.container_now_ns()
    hold.kill()
    hold.wait(timeout=10)
    _assert_lock_released_promptly(r)
    _assert_job_gone(r, hb, tok, stamp)
    rc_file = r.path / ".evlog" / ("rc-" + tok)
    wait_until(rc_file.exists, 30, "nested client never returned after its lease died")
    assert rc_file.read_text().strip() not in ("", "0"), "nested job of a dead lease must not report success"


def test_lease_bogus_and_expired_tokens_exit_125(fresh_root):
    r = fresh_root
    r.warm()
    bogus = r.dk("python3", "fx/ev.py", "run", "shared", "BOGUS", "0", env={"DK64_LEASE": "bogus-" + uuid.uuid4().hex})
    assert bogus.rc == 125, bogus.text()
    assert any(l.startswith("dk: ") for l in notice_lines(bogus.err)), bogus.text()
    assert not any(l.startswith("START shared BOGUS ") for l in r.log_lines()), "job ran without a valid lease"
    hold = r.dk("--hold", "true", env={"DK64_LEASE": "bogus-" + uuid.uuid4().hex})
    assert hold.rc == 125, hold.text()

    tokfile = r.path / ".evlog" / "lease-token"
    ok = r.dk("--hold", "sh", "-c", 'echo "$DK64_LEASE" > .evlog/lease-token; "%s" true' % r.dk_bin)
    assert ok.rc == 0, ok.text()
    token = tokfile.read_text().strip()
    assert token, "host command did not see DK64_LEASE"
    expired = r.dk("true", env={"DK64_LEASE": token})
    assert expired.rc == 125, "a lease must die with its --hold client: " + expired.text()
    assert any(l.startswith("dk: ") for l in notice_lines(expired.err)), expired.text()


# --------------------------------------------------------------------------------------------
# 7./8. startup race, recovery
# --------------------------------------------------------------------------------------------

def test_startup_race_single_container(fresh_root):
    r = fresh_root
    assert r.containers() == []
    procs = [r.popen("true") for _ in range(20)]
    results = r.finish_all(procs, 240)
    for res in results:
        assert res.rc == 0, res.text()
    rows = r.containers()
    assert len(rows) == 1, "expected exactly one container for the root, got %r" % rows
    assert rows[0][2] == "running", rows
    assert rows[0][1] == r.expected_name, "container name should derive from the root's dev:ino: %r" % rows
    label = docker("inspect", "--format", '{{index .Config.Labels "dk64.rootid"}}', rows[0][0])
    assert label.stdout.decode().strip() == r.rootid, "label dk64.rootid mismatch: %r" % label.stdout


def test_recovery_after_container_kill_and_removal(fresh_root):
    r = fresh_root
    r.warm()
    first = r.server_id()
    assert first
    docker("kill", first)
    res = r.dk("python3", "fx/ev.py", "run", "shared", "R1", "0.1", timeout=180)
    assert (res.rc, res.out) == (0, done("R1")), res.text()
    second = r.server_id()
    assert second and second != first, "no new server after `docker kill`"
    docker("rm", "-f", second)
    res = r.dk("true", timeout=180)
    assert res.rc == 0, res.text()
    third = r.server_id()
    assert third and third not in (first, second), "no new server after `docker rm -f`"
    assert len(r.containers()) == 1


# --------------------------------------------------------------------------------------------
# 9. retire on code change
# --------------------------------------------------------------------------------------------

def _status_server_id(r: Root) -> Optional[str]:
    m = re.search(r"server[_ ]?id\W+([0-9A-Za-z-]+)", r.status_text(), re.I)
    return m.group(1) if m else None


def test_retire_on_code_change(fresh_root):
    r = fresh_root
    r.warm()
    old_container = r.server_id()
    old_sid = _status_server_id(r)
    assert old_container

    permuter = r.popen("python3", "tools/permute.py", "run", "P", "22")
    long_job = r.popen("python3", "fx/ev.py", "run", "shared", "L", "6")
    r.wait_log("START none P")
    r.wait_log("START shared L")

    with open(r.path / "tools" / "dkd" / "classify.py", "a") as f:  # changes the code hash
        f.write("\n# dkd-itest: code change %s\n" % uuid.uuid4().hex)

    finished = {}

    def watch(name, proc):
        proc.wait()
        finished[name] = time.monotonic()

    watchers = []
    newcomers = {"T": r.popen("true"), "N": r.popen("python3", "fx/ev.py", "run", "shared", "N", "0.2"),
                 "E": r.popen(*make_cmd("E", 0.3)), "M": r.popen("python3", "fx/ev.py", "run", "shared", "M", "0.2")}
    for name, proc in list(newcomers.items()) + [("L", long_job)]:
        t = threading.Thread(target=watch, args=(name, proc), daemon=True)
        t.start()
        watchers.append(t)

    results = {name: r.finish(proc, 180) for name, proc in newcomers.items()}
    res_l = r.finish(long_job, 60)
    for t in watchers:
        t.join(timeout=10)
    assert res_l.rc == 0 and res_l.out == done("L"), res_l.text()
    for name in ("T", "N", "E", "M"):
        assert results[name].rc == 0, "%s: %s" % (name, results[name].text())
    assert results["N"].out == done("N") and results["E"].out == done("E") and results["M"].out == done("M")
    assert finished["T"] > finished["L"] - 0.3, "`tools/dk true` finished before the running locked job did"

    ivs = {i.ident: i for i in r.intervals(["L", "N", "E", "M"])}
    assert ivs["N"].start >= ivs["L"].end and ivs["M"].start >= ivs["L"].end, \
        "new-server jobs started before the old locked job ended: %s" % ivs
    assert not safety_violations(list(ivs.values())), safety_violations(list(ivs.values()))

    new_container = r.server_id()
    assert new_container and new_container != old_container, "no new server container after the code change"
    new_sid = _status_server_id(r)
    if old_sid and new_sid:
        assert new_sid != old_sid, "server_id did not change across the retire"
    assert permuter.poll() is None, "permuter (none job) ended before the switch finished; test inconclusive"
    assert len(r.containers()) >= 2, "retired container should still host the running none job: %r" % r.containers()

    res_p = r.finish(permuter, 120)
    assert (res_p.rc, res_p.out) == (0, done("P")), res_p.text()
    p = r.intervals(["P"])[0]
    assert p.start < ivs["L"].end and ivs["N"].start < p.end, "permuter did not span the switch: %s" % p
    wait_until(lambda: len(r.containers()) == 1, 60, "retired container did not exit when idle: %r" % r.containers())
    assert r.server_id() == new_container


def test_retire_during_lease_does_not_deadlock(fresh_root):
    """A code change while a hold is running: the hold (and its nested calls) finish on the retiring
    server; a client launched meanwhile runs afterwards, on a new server."""
    r = fresh_root
    r.warm()
    old_container = r.server_id()
    script = "\n".join([
        "set -e",
        'D="%s"' % r.dk_bin,
        '"$D" python3 fx/ev.py log START exclusive h2.span',
        '"$D" true',
        "sleep 3",
        '"$D" env ID=h2.a SLEEP=0.3 make',
        '"$D" env ID=h2.b SLEEP=0.3 make build/src/a.o',
        '"$D" python3 fx/ev.py log END exclusive h2.span',
        "",
    ])
    hold = r.popen("--hold", "sh", "-c", script)
    r.wait_log("START exclusive h2.span")
    time.sleep(1)
    with open(r.path / "tools" / "dkd" / "classify.py", "a") as f:  # changes the code hash
        f.write("\n# dkd-itest: code change %s\n" % uuid.uuid4().hex)
    newcomer = r.popen("python3", "fx/ev.py", "run", "shared", "N", "0.2")
    res_hold = r.finish(hold, 150)
    res_new = r.finish(newcomer, 150)
    assert res_hold.rc == 0, "hold must complete while the server retires: " + res_hold.text()
    assert (res_new.rc, res_new.out) == (0, done("N")), res_new.text()
    ivs = {i.ident: i for i in r.intervals(["h2.span", "h2.a", "h2.b", "N"])}
    assert ivs["N"].start >= ivs["h2.span"].end, "new client ran while the lease was held: %s" % ivs
    assert not safety_violations(list(ivs.values())), safety_violations(list(ivs.values()))
    new_container = r.server_id()
    assert new_container and new_container != old_container, "new client did not run on a new server"
    wait_until(lambda: len(r.containers()) == 1, 60, "retired container did not exit: %r" % r.containers())


@pytest.mark.parametrize("stagger", [0.1, 0.2, 0.35])
def test_parallel_makes_in_job_vs_external_exclusive(shared_root, stagger):
    """Two makes running in parallel inside ONE job (each upgrading to keyed) vs an external exclusive
    make and another keyed job: no exclusive overlaps anything, no same-key overlap (regression for a
    release-then-request gap in the upgrade path)."""
    r = shared_root
    tag = uuid.uuid4().hex[:6]
    p1, p2, x, q = ("p%s_%s" % (tag, s) for s in ("1", "2", "x", "q"))
    parallel = r.popen("sh", "-c", "%s & %s; wait" % (make_sh(p1, 1, "build/src/a.o"), make_sh(p2, 1, "build/src/b.o")))
    time.sleep(stagger)
    external = r.popen(*make_cmd(x, 0.3))
    other = r.popen("sh", "-c", make_sh(q, 1, "build/src/a.o"))
    res_p, res_x, res_q = r.finish(parallel, 120), r.finish(external, 120), r.finish(other, 120)
    assert res_p.rc == 0 and sorted(res_p.out.splitlines()) == sorted([done(p1).strip(), done(p2).strip()]), res_p.text()
    assert (res_x.rc, res_x.out) == (0, done(x)), res_x.text()
    assert (res_q.rc, res_q.out) == (0, done(q)), res_q.text()
    ivs = r.intervals([p1, p2, x, q])
    assert not safety_violations(ivs), "\n".join(safety_violations(ivs))


def test_shim_wait_prints_exactly_one_notice(fresh_root):
    """While a hold is running, `tools/dk make build/src/a.o` waits and prints exactly one notice line."""
    r = fresh_root
    r.warm()
    script = "\n".join([
        "set -e",
        'D="%s"' % r.dk_bin,
        '"$D" python3 fx/ev.py log START exclusive h3.span',
        "sleep 5",
        '"$D" python3 fx/ev.py log END exclusive h3.span',
        "",
    ])
    hold = r.popen("--hold", "sh", "-c", script)
    r.wait_log("START exclusive h3.span")
    waiter = r.popen(*make_cmd("K", 0.2, "build/src/a.o"))
    res_k, res_hold = r.finish(waiter, 120), r.finish(hold, 120)
    assert res_hold.rc == 0, res_hold.text()
    assert (res_k.rc, res_k.out) == (0, done("K")), res_k.text()
    lines = notice_lines(res_k.err)
    assert len(lines) == 1 and WAIT_RE.match(lines[0]) and res_k.err == (lines[0] + "\n").encode(), \
        "expected exactly one `dk: waiting for ` line and nothing else: " + res_k.text()
    ivs = {i.ident: i for i in r.intervals(["h3.span", "K"])}
    assert ivs["K"].start >= ivs["h3.span"].end


def test_slow_reader_gets_all_bytes(shared_root):
    """4 MiB on stdout while the host reader sleeps 12 s before reading: back-pressure, no loss, exit 0."""
    r = shared_root
    expected = bytes(range(256)) * 16384
    client = r.popen("python3", "-c", "import sys; sys.stdout.buffer.write(bytes(range(256)) * 16384)")
    time.sleep(12)
    res = r.finish(client, 120)
    assert res.rc == 0, res.text()
    assert_bytes_equal(res.out, expected, "stdout")
    assert res.err == b"", res.text()


# --------------------------------------------------------------------------------------------
# 10. throughput
# --------------------------------------------------------------------------------------------

def test_throughput_vs_docker_run(fresh_root, request):
    r = fresh_root
    n = int(os.environ.get("DKD_TEST_THROUGHPUT_N", "50"))
    t0 = time.perf_counter()
    r.warm()
    cold = time.perf_counter() - t0
    dkd_times = []
    for _ in range(n):
        t = time.perf_counter()
        res = r.dk("true", timeout=60)
        dkd_times.append(time.perf_counter() - t)
        assert res.rc == 0, res.text()
    docker_times = []
    for _ in range(n):
        t = time.perf_counter()
        res = docker("run", "--rm", "-v", "%s:/dk64" % r.path, "-w", "/dk64", IMAGE, "true", timeout=120)
        docker_times.append(time.perf_counter() - t)
        assert res.returncode == 0, res.stderr
    summary = {
        "n": n, "dkd_cold_start_s": round(cold, 3),
        "dkd_mean_s": round(statistics.mean(dkd_times), 4), "dkd_median_s": round(statistics.median(dkd_times), 4),
        "docker_run_mean_s": round(statistics.mean(docker_times), 4),
        "docker_run_median_s": round(statistics.median(docker_times), 4),
    }
    print("\nTHROUGHPUT " + json.dumps(summary))
    request.node.user_properties.append(("throughput", summary))
    assert statistics.mean(dkd_times) < statistics.mean(docker_times), summary
    assert statistics.median(dkd_times) < statistics.median(docker_times), summary
