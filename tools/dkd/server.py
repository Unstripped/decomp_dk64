"""dkd server: executes toolchain requests for one DK64 checkout inside a persistent container.

Launched as `python3 tools/dkd/server.py` (cwd /dk64, Python 3.12, stdlib only, env DKD_TOKEN and
DKD_IMAGE). Speaks the pinned protocol in proto.py on TCP 0.0.0.0:7564 (HELLO with token first)
and on the container-internal UNIX socket /run/dkd/internal.sock (no HELLO; used by the make shim).

Invariants:
  * Every RUN is a job executed through `unshare --mount --pid --fork --kill-child --mount-proc`
    with a fresh private tmpfs on /tmp; namespace PID 1 is `docker-init -g`, which relays
    signals to the job's process group and returns 128+N for a job killed by signal N. Client
    SIGNAL frames go to that init only. For disconnect/lease kills the init gets SIGTERM and,
    after 2 s, the whole process group of `unshare` gets SIGKILL: that kills `unshare`, whose
    PR_SET_PDEATHSIG kills the namespace init, and the kernel then kills every process of the
    namespace, including descendants that called setsid().
  * Locks come only from locks.LockManager. A job has one holder id; an UPGRADE (from the make
    shim) strengthens it atomically via LockManager.upgrade, after the job's other running
    makes finished if the current grant does not cover the need. A shim-make is "running"
    while its connection (inherited by make and its recipe children) is open. Grants are
    dropped only after the job's processes are dead.
  * A lease (HOLD) is an EXCLUSIVE grant tied to its connection; closing the connection kills
    the jobs running under it, then releases the lock. Jobs under a lease never request locks.
  * Retiring: RUN/HOLD/STANDALONE/lock-less UPGRADE requests (and still-waiting ones) are
    rejected with `retiring: true`; already-granted work (locked jobs, their upgrades, runs and
    re-entrant HOLDs under a live lease, standalone leases) is served to completion. RETIRED is
    sent once nothing locked remains and the process exits when nothing at all is running.
  * The only bytes ever sent as STDOUT/STDERR are the job's own; server diagnostics go to the
    container log (our stderr).
"""
import asyncio
import hmac
import itertools
import os
import secrets
import signal
import subprocess
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import proto  # noqa: E402
from classify import classify_request  # noqa: E402
from locks import LockManager, Mode, combine, compatible, covers  # noqa: E402

WORKDIR = "/dk64"
SHIM_DIR = "/dk64/tools/dkd/shims"
DEFAULT_PATH = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
HELLO_TIMEOUT = 10.0
SELFTEST_TIMEOUT = 30
INIT_WAIT = 5.0
DOCKER_INIT = "/sbin/docker-init"
RETIRE_LINGER = 30.0
KILL_GRACE = 2.0
NESTED_MESSAGE = ("dk: nested make needs a stronger lock than its parent make holds while "
                  "another upgrade is pending; run the outer make with the stronger target")
CHUNK = 65536
DESC_MAX = 200

# Runs inside the new mount+pid namespace as pid 1: give the job a private empty /tmp, then
# become the job. A failed mount must be visible and distinguishable from a job's own status.
TMP_SETUP = ('mount -t tmpfs -o mode=1777 tmpfs /tmp || '
             '{ echo "dkd: cannot mount private /tmp" >&2; exit 125; }; exec "$@"')

# The server's own credentials must never reach jobs.
SERVER_ONLY_ENV = ("DKD_TOKEN", "DKD_IMAGE")


def log(msg):
    print("dkd %s %s" % (time.strftime("%H:%M:%S"), msg), file=sys.stderr, flush=True)


def isolated_argv(argv):
    """The exact isolation command for one job. Namespace PID 1 is docker-init (tini): with -g
    it forwards every signal it receives to the job's process group, reaps orphans, and exits
    with the job's status (128+N when the job dies from signal N), printing nothing."""
    return ["unshare", "--mount", "--pid", "--fork", "--kill-child", "--mount-proc",
            "--propagation", "private", "--", DOCKER_INIT, "-g", "--",
            "sh", "-c", TMP_SETUP, "sh"] + list(argv)


def read_init_pid(unshare_pid):
    """Host pid of the job's namespace init (docker-init), once it is ready: `unshare` has
    forked it AND it has spawned the job, which tini does only after its signal handling is
    set up. A pid-namespace init ignores signals it has no handler for, so anything sent
    earlier would be lost: None until then."""
    try:
        with open("/proc/%d/task/%d/children" % (unshare_pid, unshare_pid)) as f:
            kids = f.read().split()
        if not kids:
            return None
        init = int(kids[0])
        with open("/proc/%d/task/%d/children" % (init, init)) as f:
            return init if f.read().split() else None
    except OSError:
        return None



def base_env():
    env = {k: v for k, v in os.environ.items() if k not in SERVER_ONLY_ENV}
    env["PWD"] = WORKDIR
    return env


def job_env(base, job_id):
    env = dict(base)
    env["PATH"] = SHIM_DIR + ":" + base.get("PATH", DEFAULT_PATH)
    env["DKD_JOB"] = job_id
    env["DKD_SOCK"] = proto.INTERNAL_SOCK
    return env


def exit_status(returncode):
    return 128 - returncode if returncode < 0 else returncode


def parse_need(need):
    """Wire `need` -> (Mode, keys) or None when malformed."""
    if need == "exclusive":
        return Mode.EXCLUSIVE, frozenset()
    if isinstance(need, dict):
        keys = need.get("keyed")
        if isinstance(keys, list) and keys and all(isinstance(k, str) for k in keys):
            return Mode.KEYED, frozenset(keys)
    return None


# --------------------------------------------------------------------------------------
# startup self-test


def _spawn(argv, env):
    return subprocess.Popen(isolated_argv(argv), stdin=subprocess.DEVNULL,
                            stdout=subprocess.PIPE, stderr=subprocess.PIPE, cwd=WORKDIR,
                            env=env, start_new_session=True)


def _find_exact(argv):
    """Host-visible pids whose command line is exactly argv (so `unshare`/`docker-init`/`sh`
    wrappers that merely carry argv as arguments never match)."""
    want = b"\0".join(a.encode() for a in argv) + b"\0"
    found = []
    for name in os.listdir("/proc"):
        if not name.isdigit():
            continue
        try:
            with open("/proc/%s/cmdline" % name, "rb") as f:
                if f.read() == want:
                    found.append(int(name))
        except OSError:
            continue
    return found


def _wait_for(check, what, timeout=SELFTEST_TIMEOUT):
    deadline = time.monotonic() + timeout
    while not check():
        if time.monotonic() > deadline:
            raise RuntimeError("timed out after %d s waiting for %s" % (timeout, what))
        time.sleep(0.05)


def _finish(p, what, timeout=SELFTEST_TIMEOUT):
    """communicate() with a precise failure message."""
    try:
        return p.communicate(timeout=timeout)
    except subprocess.TimeoutExpired:
        raise RuntimeError("%s did not exit within %d s" % (what, timeout))


def _reap(p):
    if p.poll() is None:
        p.kill()
        p.wait()


def _selftest_isolation(env):
    marker = "/tmp/dkd-selftest-%s" % secrets.token_hex(4)
    leaked = marker + "-job"
    script = (
        '[ "$PPID" = 1 ] || { echo "pid namespace inactive (ppid is $PPID)" >&2; exit 3; }\n'
        '[ "$(cat /proc/1/comm)" = docker-init ] || { echo "/proc not remounted" >&2; exit 4; }\n'
        '[ "$(stat -f -c %T /tmp)" = tmpfs ] || { echo "/tmp is not a tmpfs" >&2; exit 5; }\n'
        '[ -z "$(ls -A /tmp)" ] || { echo "/tmp is not empty" >&2; exit 6; }\n'
        'touch ' + leaked + ' || exit 7\n')
    open(marker, "w").close()
    p = _spawn(["sh", "-c", script], env)
    try:
        out, err = _finish(p, "the isolation script")
        if p.returncode != 0 or out or err:
            raise RuntimeError("isolation script failed (status %d, stdout %r, stderr %r)"
                               % (p.returncode, out, err))
        if os.path.exists(leaked):
            raise RuntimeError("job /tmp is not private: its files appeared in the container /tmp")
    finally:
        _reap(p)
        for path in (marker, leaked):
            try:
                os.unlink(path)
            except FileNotFoundError:
                pass


def _selftest_signals(env):
    """Signals forwarded to the namespace init must reach the job and map to 128+N."""
    for sig, want in ((signal.SIGINT, 130), (signal.SIGTERM, 143)):
        what = "forwarded %s" % sig.name
        tag = "86401.%06d" % secrets.randbelow(10 ** 6)
        p = _spawn(["sleep", tag], env)
        try:
            _wait_for(lambda: _find_exact(["sleep", tag]) and read_init_pid(p.pid) is not None,
                      "the `sleep` job to run under docker-init (%s)" % what)
            os.kill(read_init_pid(p.pid), sig)
            _, err = _finish(p, "a `sleep` job after " + what)
        finally:
            _reap(p)
        if p.returncode != want or err:
            raise RuntimeError("%s gave status %d (want %d), stderr %r"
                               % (what, p.returncode, want, err))
    p = _spawn(["sh", "-c", "kill -TERM $$"], env)
    try:
        _, err = _finish(p, "`sh -c 'kill -TERM $$'`")
    finally:
        _reap(p)
    if p.returncode != 143 or err:
        raise RuntimeError("a job killed by SIGTERM gave status %d (want 143), stderr %r"
                           % (p.returncode, err))


def _selftest_kill(env):
    tag = "86400.%06d" % secrets.randbelow(10 ** 6)
    p = _spawn(["sh", "-c", "setsid sleep %s & exec sleep %s" % (tag, tag)], env)
    try:
        _wait_for(lambda: len(_find_exact(["sleep", tag])) >= 2,
                  "the job and its setsid() child to run (kill check)")
        os.killpg(p.pid, signal.SIGKILL)
        try:
            p.wait(timeout=SELFTEST_TIMEOUT)
        except subprocess.TimeoutExpired:
            raise RuntimeError("the job's process group survived SIGKILL")
        _wait_for(lambda: not _find_exact(["sleep", tag]),
                  "the setsid() descendant to die after killing the job's process group")
    finally:
        _reap(p)


def _require_docker_init(env):
    if not os.access(DOCKER_INIT, os.X_OK):
        raise RuntimeError("%s is missing" % DOCKER_INIT)


def selftest(env):
    """Fail loudly at startup if the container cannot provide per-job isolation."""
    checks = (("docker-init present", _require_docker_init),
              ("private /tmp and pid namespace", _selftest_isolation),
              ("signal forwarding and exit statuses", _selftest_signals),
              ("kill of the whole namespace", _selftest_kill))
    for name, check in checks:
        try:
            check(env)
        except (RuntimeError, OSError, subprocess.SubprocessError) as e:
            print("dkd: FATAL: self-test '%s' failed: %s\n"
                  "dkd: (the container must run with --init --cap-add SYS_ADMIN)" % (name, e),
                  file=sys.stderr, flush=True)
            sys.exit(1)


# --------------------------------------------------------------------------------------
# server state


class Retiring(Exception):
    """The server is retiring and refuses this request."""


class JobGone(Exception):
    """The job an UPGRADE was waiting for ended."""


class NestedUpgrade(Exception):
    """A nested make needs a stronger lock that cannot be granted without deadlock."""


class Upgrade:
    """Per-UPGRADE-request state shared between the request handler and its task."""
    __slots__ = ("victim",)

    def __init__(self):
        self.victim = False


class Pending:
    __slots__ = ("fut", "rejectable")

    def __init__(self, fut, rejectable):
        self.fut = fut
        self.rejectable = rejectable


class Lease:
    __slots__ = ("token", "holder", "jobs")

    def __init__(self, token, holder):
        self.token = token
        self.holder = holder
        self.jobs = set()


class Job:
    def __init__(self, job_id, argv, desc, conn):
        self.id = job_id
        self.argv = argv
        self.desc = desc
        self.conn = conn
        self.kind = "none"          # classification of the RUN
        self.lease = None
        self.holder = None          # lock holder id (granted, or waiting for its first grant)
        self.has_lock = False       # ever granted; stays True while an upgrade is queued
        self.state = "new"          # new | waiting | starting | running | done
        self.task = None
        self.proc = None
        self.init_pid = None
        self.kill_requested = False
        self.exited = asyncio.Event()
        self.finished = asyncio.Event()
        self.ulock = asyncio.Lock()             # serialises upgrades of this job
        self.shims = {}                         # shim Conn -> shim id, granted and still running
        self.shims_changed = asyncio.Event()
        self.grants = itertools.count(1)


class Conn:
    """One accepted connection: serialised frame writes plus a 'lost' event for EOF/errors."""

    def __init__(self, reader, writer, unix):
        self.reader = reader
        self.writer = writer
        self.unix = unix
        self.wlock = asyncio.Lock()
        self.lost = asyncio.Event()
        self.on_signal = None       # callable(sig) while a job runs
        self.on_lost = None         # coroutine function; default: cancel the op task
        self.closed = False

    async def send(self, ftype, payload):
        """Write one frame; False once the peer is gone (never raises)."""
        if self.closed or self.writer.is_closing():
            return False
        data = proto.encode(ftype, payload)
        try:
            async with self.wlock:
                self.writer.write(data)
                await self.writer.drain()
            return True
        except (ConnectionError, OSError):
            self.closed = True
            return False

    async def error(self, message, retiring=False):
        await self.send(proto.ERROR, {"code": proto.DKD_ERROR, "message": message,
                                      "retiring": retiring})

    async def pump(self):
        """After the request frame: forward SIGNALs, flag EOF/protocol errors as lost."""
        try:
            while True:
                frame = await proto.read_frame(self.reader)
                if frame is None:
                    return
                ftype, payload = frame
                if ftype == proto.SIGNAL and self.on_signal is not None:
                    sig = payload.get("sig")
                    if isinstance(sig, int) and not isinstance(sig, bool) and 1 <= sig <= 64:
                        self.on_signal(sig)
                    continue
                await self.error("unexpected frame 0x%02x" % ftype)
                return
        except (proto.ProtocolError, ConnectionError, OSError, asyncio.IncompleteReadError):
            return
        finally:
            self.closed = True
            self.lost.set()


class Server:
    def __init__(self, token, image, code, env):
        self.token = token.encode()
        self.image = image
        self.code = code
        self.server_id = secrets.token_hex(8)
        self.env = env
        self.lm = LockManager()
        self.holders = {}           # holder id -> description (registered while requested)
        self.pending = {}           # holder id -> Pending (waiting for a grant)
        self.jobs = {}              # job id -> Job
        self.leases = {}            # token -> Lease (granted, connection open)
        self.retiring = False
        self.retire_waiters = []    # connections owed a RETIRED reply
        self.retire_conns = set()   # connections that asked RETIRE and are still open
        self.wake = asyncio.Event()
        self.done = asyncio.Event()
        self.seq = itertools.count(1)
        self.bg = set()             # strong refs to fire-and-forget tasks

    def spawn(self, coro):
        task = asyncio.ensure_future(coro)
        self.bg.add(task)
        task.add_done_callback(self._reap)
        return task

    def _reap(self, task):
        self.bg.discard(task)
        if not task.cancelled() and task.exception() is not None \
                and not isinstance(task.exception(), (Retiring, JobGone)):
            log("background task failed: %r" % (task.exception(),))

    # ---- lock plumbing -------------------------------------------------------------

    def _wake_granted(self, holders):
        for h in holders:
            p = self.pending.pop(h, None)
            if p is not None and not p.fut.done():
                p.fut.set_result(None)

    def drop(self, holder):
        """Remove a waiting or granted holder (idempotent) and wake newly granted waiters."""
        self.pending.pop(holder, None)
        if self.holders.pop(holder, None) is not None:
            try:
                self._wake_granted(self.lm.cancel(holder))
            except KeyError:    # the request itself was rejected; nothing to remove
                pass
        self.notify()

    def lock_label(self, job):
        if job.lease is not None:
            return "lease"
        grant = self.lm.granted().get(job.holder)
        return grant[0].value if grant is not None else "none"

    def blockers(self, holder, mode, keys):
        """Descriptions of what holder's request for (mode, keys) is waiting on."""
        out = []
        for h, (m, k) in self.lm.granted().items():
            if h != holder and not compatible(mode, keys, m, k):
                out.append("%s %s" % (m.value, self.holders.get(h, h)))
        if not out:
            queued = [(h, m, k) for h, m, k, _ in self.lm.pending_upgrades()]
            queued += self.lm.waiting()
            for h, m, k in queued:
                if h == holder:
                    break
                if not compatible(mode, keys, m, k):
                    out.append("%s %s (queued)" % (m.value, self.holders.get(h, h)))
        return list(dict.fromkeys(out))

    async def acquire(self, holder, mode, keys, desc, conn, rejectable):
        """Return once granted. Raises Retiring (rejectable waits during retirement) or JobGone;
        on any exception the holder is dropped."""
        if rejectable and self.retiring:
            raise Retiring()
        fut = asyncio.get_running_loop().create_future()
        self.pending[holder] = Pending(fut, rejectable)
        self.holders[holder] = desc
        try:
            if self.lm.request(holder, mode, keys):
                self.pending.pop(holder, None)
                return
            held_by = self.blockers(holder, mode, keys)
            log("%s waits for %s lock (%s), blocked by: %s"
                % (holder, mode.value, desc, "; ".join(held_by) or "queue"))
            await conn.send(proto.WAITING, {"mode": mode.value, "held_by": held_by})
            await fut
        except BaseException:
            self.drop(holder)
            raise

    def locked(self):
        """True while anything may still be running under a grant."""
        return bool(self.lm.granted()) or any(
            j.has_lock for j in self.jobs.values() if j.state != "done")

    def none_jobs(self):
        return sum(1 for j in self.jobs.values()
                   if j.state in ("starting", "running") and j.lease is None
                   and not j.has_lock and j.holder is None)

    def notify(self):
        self.wake.set()

    # ---- retirement ----------------------------------------------------------------

    def start_retire(self):
        if self.retiring:
            return
        self.retiring = True
        log("retiring")
        for p in list(self.pending.values()):
            if p.rejectable and not p.fut.done():
                p.fut.set_exception(Retiring())
        self.spawn(self.retire_monitor())

    async def retire_monitor(self):
        """Answer RETIRE once nothing locked remains; exit once nothing runs at all (after the
        retiring clients had a chance to rename the container, bounded by RETIRE_LINGER)."""
        loop = asyncio.get_running_loop()
        replied = False
        deadline = None
        while True:
            timeout = None if deadline is None else max(0.0, deadline - loop.time())
            try:
                await asyncio.wait_for(self.wake.wait(), timeout)
            except asyncio.TimeoutError:
                log("retire clients did not disconnect; exiting")
                self.done.set()
                return
            self.wake.clear()
            if self.locked():
                continue
            if self.retire_waiters:
                waiters, self.retire_waiters = self.retire_waiters, []
                for c in waiters:
                    await c.send(proto.RETIRED, {"none_jobs": self.none_jobs()})
                replied = True
                log("retired (locked work drained, %d lock-less jobs running)" % self.none_jobs())
            if replied and not self.jobs:
                if not self.retire_conns:
                    log("no jobs left; exiting")
                    self.done.set()
                    return
                if deadline is None:
                    deadline = loop.time() + RETIRE_LINGER

    # ---- connection handling -------------------------------------------------------

    async def handle(self, reader, writer, unix):
        conn = Conn(reader, writer, unix)
        try:
            if not unix and not await self.hello(conn):
                return
            await self.serve_requests(conn)
        except proto.ProtocolError as e:
            log("protocol error: %s" % e)
            await conn.error("protocol error: %s" % e)
        except (ConnectionError, OSError, asyncio.IncompleteReadError) as e:
            log("connection dropped: %s: %s" % (type(e).__name__, e))
        except Exception as e:  # one bad connection must never take the server down
            log("internal error: %r" % (e,))
            try:
                await conn.error("internal server error: %s" % (e,))
            except Exception:
                pass
        finally:
            conn.closed = True
            if conn in self.retire_conns:
                self.retire_conns.discard(conn)
                self.notify()
            try:
                writer.close()
                await writer.wait_closed()
            except Exception:
                pass

    async def hello(self, conn):
        frame = await asyncio.wait_for(proto.read_frame(conn.reader), HELLO_TIMEOUT)
        if frame is None:
            return False
        ftype, p = frame
        if ftype != proto.HELLO:
            await conn.error("first frame must be HELLO")
            return False
        token = p.get("token")
        if not isinstance(token, str) or not hmac.compare_digest(token.encode(), self.token):
            await conn.error("bad token")
            return False
        await conn.send(proto.HELLO_OK, {"code": self.code, "image": self.image,
                                         "retiring": self.retiring, "server_id": self.server_id})
        return True

    async def serve_requests(self, conn):
        """STATUS/RETIRE may repeat on one connection; any other request owns it until done."""
        ops = {proto.RUN: self.op_run, proto.HOLD: self.op_hold,
               proto.UPGRADE: self.op_upgrade, proto.STANDALONE: self.op_standalone}
        while True:
            frame = await proto.read_frame(conn.reader)
            if frame is None:
                return
            ftype, p = frame
            if ftype == proto.STATUS:
                await conn.send(proto.STATUS_REPLY, self.status())
            elif ftype == proto.RETIRE:
                self.retire_waiters.append(conn)
                self.retire_conns.add(conn)
                self.start_retire()
                self.notify()
            elif ftype in ops:
                if ftype in (proto.UPGRADE, proto.STANDALONE) and not conn.unix:
                    await conn.error("UPGRADE/STANDALONE are only accepted on the internal socket")
                    return
                await self.run_op(conn, ops[ftype], p)
                return
            else:
                await conn.error("unexpected frame 0x%02x" % ftype)
                return

    async def run_op(self, conn, op, payload):
        """Run op(conn, payload) while watching the connection; on loss, abort it."""
        pump = asyncio.ensure_future(conn.pump())
        main = asyncio.ensure_future(op(conn, payload))
        lost = asyncio.ensure_future(conn.lost.wait())
        try:
            await asyncio.wait({main, lost}, return_when=asyncio.FIRST_COMPLETED)
            if not main.done():
                if conn.on_lost is not None:
                    await conn.on_lost()
                else:
                    main.cancel()
                await asyncio.gather(main, return_exceptions=True)
            elif not main.cancelled() and main.exception() is not None:
                exc = main.exception()
                log("request failed: %r" % (exc,))
                await conn.error("internal server error: %s" % (exc,))
        finally:
            for t in (lost, pump, main):
                if not t.done():
                    t.cancel()
            await asyncio.gather(lost, pump, main, return_exceptions=True)

    # ---- RUN -----------------------------------------------------------------------

    async def op_run(self, conn, p):
        argv, tok = p.get("argv"), p.get("lease")
        if (not isinstance(argv, list) or not argv or not all(isinstance(a, str) for a in argv)
                or "\0" in "".join(argv)):
            await conn.error("RUN needs a non-empty argv of strings")
            return
        if tok is not None and not isinstance(tok, str):
            await conn.error("bad lease")
            return
        desc = str(p.get("desc") or " ".join(argv))[:DESC_MAX]

        lease = None
        if tok is not None:
            lease = self.leases.get(tok)
            if lease is None:
                await conn.error("unknown or expired lease (DK64_LEASE)")
                return
        elif self.retiring:
            await conn.error("server is retiring", retiring=True)
            return

        job = Job(secrets.token_hex(6), argv, desc, conn)
        job.task = asyncio.current_task()
        self.jobs[job.id] = job
        if lease is not None:
            job.lease = lease
            lease.jobs.add(job)
        conn.on_signal = lambda sig: self.signal_job(job, sig)
        conn.on_lost = lambda: self.abort_job(job)
        try:
            if lease is None:
                try:
                    job.kind = classify_request(argv)
                except Exception as e:
                    log("classify_request failed (%r); treating as exclusive" % (e,))
                    job.kind = "exclusive"
                if job.kind not in ("none", "shared", "exclusive"):
                    log("classify_request returned %r; treating as exclusive" % (job.kind,))
                    job.kind = "exclusive"
                if job.kind != "none":
                    mode = Mode.SHARED if job.kind == "shared" else Mode.EXCLUSIVE
                    job.state = "waiting"
                    await self.job_acquire(job, mode, frozenset(), conn, rejectable=True)
            job.state = "starting"
            log("job %s start [%s] %s" % (job.id, self.lock_label(job), desc))
            await conn.send(proto.GRANTED, {})
            status = await self.execute(job, conn)
            log("job %s exit %d" % (job.id, status))
            job.state = "done"
            self.release_job(job)
            await conn.send(proto.EXIT, {"status": status})
        except Retiring:
            await conn.error("server is retiring", retiring=True)
        except asyncio.CancelledError:
            log("job %s cancelled while waiting for its lock" % job.id)
        finally:
            job.state = "done"
            self.release_job(job)
            if lease is not None:
                lease.jobs.discard(job)
            self.jobs.pop(job.id, None)
            job.finished.set()
            job.shims_changed.set()
            self.notify()

    async def job_acquire(self, job, mode, keys, conn, rejectable):
        """First grant for a job (RUN classification, or a lock-less job's first make)."""
        job.holder = "%s.%d" % (job.id, next(job.grants))
        try:
            await self.acquire(job.holder, mode, keys, job.desc, conn, rejectable)
        except BaseException:
            job.holder = None
            raise
        job.has_lock = True

    def release_job(self, job):
        """Drop the job's grant (idempotent). Once the job is done, an UPGRADE still waiting
        for a grant is failed instead of left hanging."""
        if job.holder is not None:
            p = self.pending.get(job.holder)
            if p is not None and job.state == "done" and not p.fut.done():
                p.fut.set_exception(JobGone())
            self.drop(job.holder)
            job.holder = None

    async def execute(self, job, conn):
        """Spawn the isolated job, stream its output, return the client-visible exit status."""
        try:
            proc = await asyncio.create_subprocess_exec(
                *isolated_argv(job.argv), stdin=asyncio.subprocess.DEVNULL,
                stdout=asyncio.subprocess.PIPE, stderr=asyncio.subprocess.PIPE,
                cwd=WORKDIR, env=job_env(self.env, job.id), start_new_session=True)
        except OSError as e:
            await conn.send(proto.STDERR, ("dkd: cannot start job: %s\n" % e).encode())
            job.exited.set()
            return proto.DKD_ERROR
        job.proc = proc
        job.state = "running"
        readers = asyncio.gather(self.pump_stream(proc.stdout, proto.STDOUT, conn),
                                 self.pump_stream(proc.stderr, proto.STDERR, conn))
        if job.kill_requested:
            self.spawn(self.kill_job(job))
        rc = await proc.wait()
        job.exited.set()
        # Pipes reach EOF once the namespace is empty, so wait for all output; only bound the
        # wait when nobody is left to receive it.
        lost = asyncio.ensure_future(conn.lost.wait())
        try:
            await asyncio.wait({readers, lost}, return_when=asyncio.FIRST_COMPLETED)
            if not readers.done():
                try:
                    await asyncio.wait_for(readers, 10)
                except asyncio.TimeoutError:
                    log("job %s: output pipes still open 10 s after exit" % job.id)
        finally:
            lost.cancel()
        return exit_status(rc)

    async def pump_stream(self, stream, ftype, conn):
        while True:
            chunk = await stream.read(CHUNK)
            if not chunk:
                return
            await conn.send(ftype, chunk)

    # ---- signals and killing -------------------------------------------------------

    async def init_pid(self, job):
        """Host pid of the job's namespace init once it is ready to take signals (see
        read_init_pid); None if the job ends or INIT_WAIT passes first."""
        proc = job.proc
        deadline = time.monotonic() + INIT_WAIT
        while job.init_pid is None:
            if proc is None or proc.returncode is not None or time.monotonic() > deadline:
                return None
            job.init_pid = read_init_pid(proc.pid)
            if job.init_pid is None:
                await asyncio.sleep(0.02)
        return job.init_pid

    def signal_job(self, job, sig):
        """Forward a client signal to the namespace init only: docker-init relays it to the
        job's process group. (Never to `unshare` itself: it would die on e.g. SIGHUP.)"""
        self.spawn(self.forward(job, sig))

    async def forward(self, job, sig):
        pid = await self.init_pid(job)
        if pid is not None and job.proc.returncode is None:
            try:
                os.kill(pid, sig)
            except ProcessLookupError:
                pass

    async def kill_job(self, job):
        """SIGTERM via the init, SIGKILL the whole group after KILL_GRACE (which kills `unshare`
        and, through --kill-child, everything in the namespace); returns once it has exited."""
        proc = job.proc
        if proc is None or proc.returncode is not None:
            return
        pid = await self.init_pid(job)
        if pid is not None:
            try:
                os.kill(pid, signal.SIGTERM)
            except ProcessLookupError:
                pass
            try:
                await asyncio.wait_for(job.exited.wait(), KILL_GRACE)
                return
            except asyncio.TimeoutError:
                log("job %s ignored SIGTERM; SIGKILL" % job.id)
        if proc.returncode is None:
            try:
                os.killpg(proc.pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
        try:
            await asyncio.wait_for(job.exited.wait(), 10)
        except asyncio.TimeoutError:
            log("job %s did not exit after SIGKILL" % job.id)

    async def abort_job(self, job):
        """Stop a job because its client or lease went away (any state)."""
        job.kill_requested = True
        if job.state == "waiting":
            job.task.cancel()
        elif job.state == "running":
            await self.kill_job(job)
        # state "starting": execute() sees kill_requested right after the spawn.

    # ---- HOLD / STANDALONE / UPGRADE -----------------------------------------------

    async def op_hold(self, conn, p):
        tok = p.get("lease")
        if tok is not None:
            if isinstance(tok, str) and tok in self.leases:
                await conn.send(proto.LEASE, {"lease": tok})
                await conn.lost.wait()      # re-entrant: this connection owns nothing
            else:
                await conn.error("unknown or expired lease (DK64_LEASE)")
            return
        if self.retiring:
            await conn.error("server is retiring", retiring=True)
            return
        desc = str(p.get("desc") or "hold")[:DESC_MAX]
        holder = "hold-%d" % next(self.seq)
        try:
            await self.acquire(holder, Mode.EXCLUSIVE, frozenset(), desc, conn, rejectable=True)
        except Retiring:
            await conn.error("server is retiring", retiring=True)
            return
        lease = Lease(secrets.token_urlsafe(18), holder)
        self.leases[lease.token] = lease
        log("lease %s granted (%s)" % (holder, desc))
        try:
            await conn.send(proto.LEASE, {"lease": lease.token})
            await conn.lost.wait()
        finally:
            # Shielded: run_op cancels this task when the connection drops, and the teardown
            # (kill jobs, then release the lock) must run to completion regardless.
            await asyncio.shield(self.spawn(self.end_lease(lease)))

    async def end_lease(self, lease):
        self.leases.pop(lease.token, None)
        jobs = list(lease.jobs)
        log("lease %s ended; killing %d job(s)" % (lease.holder, len(jobs)))
        for j in jobs:
            self.spawn(self.abort_job(j))
        await asyncio.gather(*(j.finished.wait() for j in jobs))
        self.drop(lease.holder)

    async def op_standalone(self, conn, p):
        need = parse_need(p.get("need"))
        if need is None:
            await conn.error("bad need")
            return
        if self.retiring:
            await conn.error("server is retiring", retiring=True)
            return
        desc = str(p.get("desc") or "make")[:DESC_MAX]
        holder = "sa-%d" % next(self.seq)
        try:
            await self.acquire(holder, need[0], need[1], desc, conn, rejectable=True)
            log("standalone %s granted [%s] %s" % (holder, need[0].value, desc))
            await conn.send(proto.GRANTED, {})
            await conn.lost.wait()
        except Retiring:
            await conn.error("server is retiring", retiring=True)
        finally:
            self.drop(holder)

    def covered(self, job, mode, keys):
        grant = self.lm.granted().get(job.holder)
        return grant is not None and covers(grant[0], grant[1], mode, keys)

    async def upgrade_grant(self, job, mode, keys, conn, up):
        """Return once the job holds a grant covering (mode, keys): a first grant for a
        lock-less job, else LockManager.upgrade (recording in `up` whether that took the victim
        path). Raises JobGone if the job ends while waiting."""
        holder = job.holder
        if holder is None:
            await self.job_acquire(job, mode, keys, conn, rejectable=True)
            return
        cur_mode, cur_keys = self.lm.granted()[holder]
        target = combine(cur_mode, cur_keys, mode, keys)
        fut = asyncio.get_running_loop().create_future()
        self.pending[holder] = Pending(fut, False)
        try:
            granted_now, newly = self.lm.upgrade(holder, mode, keys)
            self._wake_granted(newly)
            if granted_now:
                self.pending.pop(holder, None)
                return
            up.victim = not any(e[0] == holder and e[3] for e in self.lm.pending_upgrades())
            log("job %s upgrade %s -> %s %s (%s)" % (
                job.id, cur_mode.value, target[0].value, sorted(target[1]),
                "victim" if up.victim else "atomic"))
            await conn.send(proto.WAITING, {"mode": target[0].value,
                                            "held_by": self.blockers(holder, *target)})
            await fut
        except BaseException:
            self.pending.pop(holder, None)
            entry = next((e for e in self.lm.pending_upgrades() if e[0] == holder), None)
            if entry is not None and entry[3]:
                self._wake_granted(self.lm.cancel_upgrade(holder))     # keeps the old grant
            raise

    async def upgrade_job(self, job, conn, mode, keys, shim_id, ancestors, up):
        """Task: make the job's grant cover (mode, keys), then register the shim connection as a
        running make of the job. Runs detached from the connection so that a victim upgrade
        (grant already released) still completes if the shim disappears.

        Order of checks (all synchronous between awaits, hence race-free in asyncio):
          1. covered -> no lock needed, nothing to wait for (covered makes run in parallel).
          2. Uncovered: wait, WITHOUT holding job.ulock, until no non-ancestor make of this job
             is running. Ancestors are excluded: a parent make cannot finish before its
             sub-make, so waiting for it would deadlock. LockManager.upgrade may release the
             job's grant (victim path), which must never happen under a running make.
          3. Take job.ulock (serialises upgraders), re-check 1 and 2 (state may have changed
             while queued for it), then call upgrade_grant.
          4. If an ancestor make is still running, the need is uncovered and another holder
             already has a pending ATOMIC upgrade, LockManager.upgrade would take the victim
             path and drop the grant under that running parent. Waiting instead would deadlock
             (the atomic upgrader waits for this job's grant), so refuse: NestedUpgrade."""
        notified = False
        while True:
            if job.state == "done":
                raise JobGone()
            if conn.closed:
                return                      # shim gone: abandon before touching any lock
            if self.covered(job, mode, keys):
                break
            if [sid for sid in job.shims.values() if sid not in ancestors]:
                if not notified:
                    notified = True
                    await conn.send(proto.WAITING, {"mode": mode.value,
                                                    "held_by": ["earlier make in the same job"]})
                job.shims_changed.clear()
                await job.shims_changed.wait()
                continue
            async with job.ulock:
                if (job.state == "done" or conn.closed or self.covered(job, mode, keys)
                        or [sid for sid in job.shims.values() if sid not in ancestors]):
                    continue                # re-evaluate outside the lock
                if (any(sid in ancestors for sid in job.shims.values())
                        and any(e[3] for e in self.lm.pending_upgrades())):
                    raise NestedUpgrade()
                await self.upgrade_grant(job, mode, keys, conn, up)
                if job.state == "done":
                    raise JobGone()
                if not conn.closed:
                    job.shims[conn] = shim_id
                return
        if not conn.closed:
            job.shims[conn] = shim_id

    async def op_upgrade(self, conn, p):
        need = parse_need(p.get("need"))
        job = self.jobs.get(p.get("job")) if isinstance(p.get("job"), str) else None
        if need is None:
            await conn.error("bad need")
            return
        if job is None or job.state not in ("starting", "running"):
            await conn.error("unknown job")
            return
        if job.lease is not None:
            await conn.send(proto.GRANTED, {})      # an exclusive lease covers everything
            return
        shim_id, ancestors = p.get("shim"), p.get("ancestors")
        if not isinstance(shim_id, str):
            shim_id = ""
        if not isinstance(ancestors, list):
            ancestors = []
        up = Upgrade()
        task = self.spawn(self.upgrade_job(job, conn, need[0], need[1], shim_id,
                                           frozenset(a for a in ancestors if isinstance(a, str)),
                                           up))
        try:
            try:
                await asyncio.shield(task)
            except Retiring:
                await conn.error("server is retiring", retiring=True)
                return
            except JobGone:
                await conn.error("job ended")
                return
            except NestedUpgrade:
                await conn.error(NESTED_MESSAGE)
                return
            except asyncio.CancelledError:
                # Shim gone while waiting. This request's own upgrade is withdrawn unless it
                # is a victim entry: then the job holds no grant, so it stays queued until it
                # is granted again or the job ends.
                if not task.done() and not up.victim:
                    task.cancel()
                raise
            await conn.send(proto.GRANTED, {})
            await conn.lost.wait()      # the make (and its recipe children) hold this open
        finally:
            if job.shims.pop(conn, None) is not None:
                job.shims_changed.set()

    # ---- STATUS --------------------------------------------------------------------

    def status(self):
        def entry(h, m, k):
            return {"holder": h, "mode": m.value, "keys": sorted(k),
                    "desc": self.holders.get(h, "")}
        return {
            "server_id": self.server_id, "image": self.image, "code": self.code,
            "retiring": self.retiring,
            "granted": [entry(h, m, k) for h, (m, k) in self.lm.granted().items()],
            "waiting": ([entry(h, m, k) for h, m, k in self.lm.waiting()]
                        + [entry(h, m, k) for h, m, k, _ in self.lm.pending_upgrades()]),
            "jobs": [{"id": j.id, "desc": j.desc, "lock": self.lock_label(j),
                      "pid": j.proc.pid if j.proc is not None else None}
                     for j in self.jobs.values()],
        }


# --------------------------------------------------------------------------------------


async def serve(server):
    sock_dir = os.path.dirname(proto.INTERNAL_SOCK)
    os.makedirs(sock_dir, mode=0o700, exist_ok=True)
    os.chmod(sock_dir, 0o700)
    try:
        os.unlink(proto.INTERNAL_SOCK)
    except FileNotFoundError:
        pass
    unix = await asyncio.start_unix_server(lambda r, w: server.handle(r, w, True),
                                           path=proto.INTERNAL_SOCK)
    os.chmod(proto.INTERNAL_SOCK, 0o600)
    tcp = await asyncio.start_server(lambda r, w: server.handle(r, w, False),
                                     host="0.0.0.0", port=proto.PORT, reuse_address=True)
    log("ready: server_id=%s image=%s code=%s" % (server.server_id, server.image, server.code[:12]))
    await server.done.wait()
    tcp.close()
    unix.close()


def main():
    token = os.environ.get("DKD_TOKEN")
    if not token:
        print("dkd: FATAL: DKD_TOKEN is not set", file=sys.stderr, flush=True)
        sys.exit(1)
    image = os.environ.get("DKD_IMAGE", "")
    env = base_env()
    selftest(env)
    server = Server(token, image, proto.code_hash(WORKDIR), env)
    asyncio.run(serve(server))


if __name__ == "__main__":
    main()
