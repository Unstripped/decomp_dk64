"""dkd host client: the implementation behind `tools/dk` (Python 3.9, stdlib only).

`tools/dk <cmd> [args...]` runs <cmd> in /dk64 inside the toolchain image exactly like the old
`docker run --rm` wrapper did (byte-exact stdout/stderr, the command's exit status, 128+N for
signals), but through one long-lived server container per checkout (tools/dkd/server.py) that
serialises jobs with a reader/writer lock. This module only talks to that server over the pinned
wire protocol in proto.py and manages the container's lifecycle.

Modes (first argument only; anything else is the command):
  tools/dk <cmd> ...            RUN a job; interactive (stdin and stdout TTYs) -> `docker exec -it`
  tools/dk --hold <cmd> ...     run a HOST command under an exclusive lease (DK64_LEASE for nesting)
  tools/dk --status | --stop    debug aid / retire-and-stop the server

Invariants:
  * The success path prints nothing but the job's own bytes; every diagnostic is one `dk: ...`
    line on stderr, and dkd-level failures exit 125.
  * The container named `dk64-<sha256(st_dev:st_ino of root)[:12]>` (docker's atomic name registry) is the only
    source of truth for "the" server. `.dkd/state.json` only caches {port, token, image id}
    to skip `docker inspect` on the fast path; any doubt falls back to inspecting.
  * A server that does not match (code hash / image id) or is already retiring is replaced only
    after it has answered RETIRED (no locked job or lease left, nothing new accepted), so two
    servers never grant conflicting locks for one root.
  * A RUN is never re-sent once the server granted it.
"""
import json
import hashlib
import os
import re
import secrets
import select
import shlex
import signal
import socket
import subprocess
import sys
import threading
import time

import proto

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.realpath(__file__))))
# realpath does not normalise case/firmlinks on macOS, so identity is the directory's
# (st_dev, st_ino); the container name and the dk64.rootid label derive from it.
_ROOT_STAT = os.stat(ROOT)
ROOT_ID = "%d:%d" % (_ROOT_STAT.st_dev, _ROOT_STAT.st_ino)
NAME = "dk64-" + hashlib.sha256(ROOT_ID.encode()).hexdigest()[:12]
IMAGE = os.environ.get("DK64_IMAGE") or "dk64-decomp"
ABSENT_GRACE = 5.0        # seconds a just-conflicted container may stay un-inspectable
STATE_DIR = os.path.join(ROOT, ".dkd")
STATE_FILE = os.path.join(STATE_DIR, "state.json")

IMAGE_RECHECK_SECONDS = 5.0
READY_TIMEOUT = 30.0
HANDSHAKE_TIMEOUT = 5.0
WAIT_NOTICE_DELAY = 2.0
DOUBLE_SIGINT_WINDOW = 2.0
MAX_ROUNDS = 10           # restart-flow iterations before giving up
MAX_RETRIES = 10          # transparent RUN/HOLD retries after ERROR{retiring}
DEAD_STATES = ("exited", "dead", "removing")
FORWARDED_SIGNALS = (signal.SIGINT, signal.SIGTERM, signal.SIGHUP)
DEFAULT_PATH = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
SHIM_DIR = "/dk64/tools/dkd/shims"

USAGE = """\
usage: tools/dk <command> [args...]            run a command in the toolchain container
       tools/dk --hold <command> [args...]     run a host command under an exclusive lease
       tools/dk --status                       show the dkd server, lock holders and jobs
       tools/dk --stop                         retire and stop the dkd server
"""


class DkError(Exception):
    """A dkd-level failure: message goes to stderr with a `dk: ` prefix, exit status `code`."""

    def __init__(self, message, code=proto.DKD_ERROR):
        Exception.__init__(self, message)
        self.code = code


class _Exit(Exception):
    """Silent early exit with a status (interrupt handling)."""

    def __init__(self, code):
        Exception.__init__(self, code)
        self.code = code


class _Rejected(Exception):
    """The server answered HELLO with an ERROR frame."""

    def __init__(self, payload):
        Exception.__init__(self, payload.get("message", "rejected"))


def _clean(value):
    """Strip control characters from text that came from the server before printing it."""
    return re.sub(r"[\x00-\x1f\x7f-\x9f]", "?", str(value))


def _warn(message):
    sys.stderr.write("dk: %s\n" % message)
    sys.stderr.flush()


def _describe(words, prefix=""):
    text = prefix + shlex.join(words)
    if len(text) > 80:
        text = text[:77] + "..."
    return "%s [pid %d]" % (text, os.getpid())


# --------------------------------------------------------------------------- docker helpers

def _docker(*args, env=None):
    try:
        proc = subprocess.run(("docker",) + args, stdin=subprocess.DEVNULL, env=env,
                              stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    except FileNotFoundError:
        raise DkError("docker not found in PATH", 127)
    return (proc.returncode, proc.stdout.decode("utf-8", "replace"),
            proc.stderr.decode("utf-8", "replace"))


def _inspect(ref):
    """`docker inspect` of a container by name/id; None if it does not exist."""
    rc, out, err = _docker("inspect", "--type", "container", ref)
    if rc != 0:
        if "no such" in err.lower():
            return None
        raise DkError("docker inspect %s failed: %s" % (ref, err.strip()))
    return json.loads(out)[0]


class _Srv:
    """The facts about a server container that we take from `docker inspect`."""

    def __init__(self, info):
        self.id = info["Id"]
        self.status = (info.get("State") or {}).get("Status", "")
        cfg = info.get("Config") or {}
        self.labels = cfg.get("Labels") or {}
        self.env = {}
        for entry in cfg.get("Env") or []:
            key, _, value = entry.partition("=")
            self.env[key] = value
        self.token = self.env.get("DKD_TOKEN")
        self.port = None
        binds = ((info.get("NetworkSettings") or {}).get("Ports") or {}).get(
            "%d/tcp" % proto.PORT) or []
        local = [b for b in binds if b.get("HostIp") == "127.0.0.1"] or binds
        if local and local[0].get("HostPort"):
            self.port = int(local[0]["HostPort"])


def _named_server():
    """The current server container for this root, or None. Refuses foreign containers."""
    info = _inspect(NAME)
    if info is None:
        return None
    srv = _Srv(info)
    if srv.labels.get("dk64.rootid") != ROOT_ID:
        raise DkError("container name %s is taken by a container that is not this checkout's "
                      "dkd server (label dk64.rootid=%r)" % (NAME, srv.labels.get("dk64.rootid")))
    return srv


# --------------------------------------------------------------------------- state cache

def _read_state():
    try:
        with open(STATE_FILE) as f:
            state = json.load(f)
    except (OSError, ValueError):
        return {}
    return state if isinstance(state, dict) else {}


def _update_state(**fields):
    """Merge fields into the cache; atomic (rename), 0700 dir, 0600 file. Best effort: the
    cache is an optimisation, so an unwritable checkout must not fail the command."""
    state = _read_state()
    state.update(fields)
    tmp = "%s.%d.%s.tmp" % (STATE_FILE, os.getpid(), secrets.token_hex(4))
    try:
        os.makedirs(STATE_DIR, mode=0o700, exist_ok=True)
        os.chmod(STATE_DIR, 0o700)
        fd = os.open(tmp, os.O_WRONLY | os.O_CREAT | os.O_EXCL, 0o600)
        with os.fdopen(fd, "w") as f:
            json.dump(state, f)
        os.replace(tmp, STATE_FILE)
    except OSError:
        try:
            os.unlink(tmp)
        except OSError:
            pass


def _wanted_image_id():
    """Image id of DK64_IMAGE; `docker image inspect` result cached for IMAGE_RECHECK_SECONDS."""
    state = _read_state()
    now = time.time()
    checked = state.get("image_checked")
    cached = state.get("image_id")
    if (state.get("image_name") == IMAGE and isinstance(cached, str)
            and isinstance(checked, (int, float)) and 0 <= now - checked < IMAGE_RECHECK_SECONDS):
        return cached
    rc, out, err = _docker("image", "inspect", "--format", "{{.Id}}", IMAGE)
    if rc != 0:
        raise DkError("cannot inspect image %s: %s" % (IMAGE, err.strip()))
    image_id = out.strip()
    _update_state(image_name=IMAGE, image_id=image_id, image_checked=now)
    return image_id


# --------------------------------------------------------------------------- connections

def _handshake(port, token, image_id, code):
    """Connect + HELLO. -> (socket, HELLO_OK payload), or None if the server is not (yet)
    answering. Raises _Rejected if the server answers with an ERROR frame (bad token)."""
    try:
        sock = socket.create_connection(("127.0.0.1", port), timeout=HANDSHAKE_TIMEOUT)
    except OSError:
        return None
    try:
        sock.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
        sock.sendall(proto.encode(proto.HELLO, {
            "token": token, "code": code, "image": image_id,
            "desc": "client pid %d" % os.getpid()}))
        frame = proto.recv_frame(sock)
    except (OSError, proto.ProtocolError):
        sock.close()
        return None
    if frame is not None and frame[0] == proto.HELLO_OK:
        sock.settimeout(None)
        return sock, frame[1]
    sock.close()
    if frame is not None and frame[0] == proto.ERROR:
        raise _Rejected(frame[1])
    return None


def _matches(hello, image_id, code):
    return (not hello.get("retiring") and hello.get("code") == code
            and hello.get("image") == image_id)


def _try_cached(image_id, code):
    """Fast path: connect with the cached port/token. Only a matching, non-retiring server is
    accepted; everything else (stale cache, other container's port, mismatch) -> None."""
    state = _read_state()
    port, token = state.get("port"), state.get("token")
    if not (isinstance(port, int) and isinstance(token, str)):
        return None
    try:
        got = _handshake(port, token, image_id, code)
    except _Rejected:
        return None
    if got is None:
        return None
    if _matches(got[1], image_id, code):
        return got
    got[0].close()
    return None


class _LogTail:
    """`docker logs --follow` of the server container, so the reason a freshly started server
    died is still available after --rm removed the container."""

    def __init__(self):
        self.proc = subprocess.Popen(
            ["docker", "logs", "--follow", "--tail", "50", NAME], stdin=subprocess.DEVNULL,
            stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    def collect(self):
        """Wait for the follower to end (the container is gone) and return the last lines."""
        try:
            out = self.proc.communicate(timeout=5)[0]
        except subprocess.TimeoutExpired:
            self.proc.kill()
            out = self.proc.communicate()[0]
        lines = out.decode("utf-8", "replace").splitlines()
        return "\n".join(_clean(line) for line in lines[-20:])

    def stop(self):
        if self.proc.poll() is None:
            self.proc.kill()
        self.proc.wait()
        self.proc.stdout.close()


def _exited_message(tail):
    logs = tail.collect() if tail is not None else ""
    if not logs or "no such container" in logs.lower():
        return ("dkd server container %s exited before becoming ready (no logs available)"
                % NAME)
    return "dkd server container %s exited before becoming ready; its output:\n%s" % (NAME, logs)


def _start(image_id, code):
    """`docker run` the server. True if we started it; False if we lost the name race to a
    concurrent client (docker's Conflict / already-in-use error), whatever state the winner's
    container is in right now."""
    rc, _, err = _docker(
        "run", "-d", "--rm", "--init", "--cap-add", "SYS_ADMIN",
        "-p", "127.0.0.1::%d" % proto.PORT, "-v", "%s:/dk64" % ROOT, "-w", "/dk64",
        "-e", "DKD_TOKEN", "-e", "DKD_IMAGE=" + image_id,
        "--label", "dk64.root=" + ROOT, "--label", "dk64.rootid=" + ROOT_ID,
        "--label", "dk64.image=" + image_id, "--label", "dk64.code=" + code,
        "--name", NAME, image_id, "python3", "tools/dkd/server.py",
        env=dict(os.environ, DKD_TOKEN=secrets.token_hex(32)))
    if rc == 0:
        return True
    low = err.lower()
    if "conflict" in low or "already in use" in low or _inspect(NAME) is not None:
        return False
    raise DkError("cannot start dkd server: %s" % err.strip())


def _wait_ready(image_id, code, started, attempted):
    """Poll the named container until its server answers HELLO.

    -> (socket, hello, _Srv); or None if the container vanished and we did not start it (the
    caller re-runs the restart flow). If we started it and it died, raises with its logs.
    `attempted`: we just tried `docker run`, so if we lost the name race the winner's container
    may be briefly not inspectable while docker is still creating it; that is tolerated for
    ABSENT_GRACE seconds before treating it as vanished. The created/starting states and a
    missing port mapping are always polled through (within the READY_TIMEOUT budget)."""
    deadline = time.monotonic() + READY_TIMEOUT
    absent_deadline = time.monotonic() + ABSENT_GRACE
    delay = 0.05
    tail = _LogTail() if started else None
    try:
        while True:
            srv = _named_server()
            if srv is None and attempted and not started and time.monotonic() < absent_deadline:
                time.sleep(delay)
                delay = min(delay * 1.5, 0.5)
                continue
            if srv is None or srv.status in DEAD_STATES:
                if started:
                    raise DkError(_exited_message(tail))
                return None
            if srv.status == "paused":
                raise DkError("dkd server container %s is paused" % NAME)
            if srv.status == "running" and srv.port is not None and srv.token:
                try:
                    got = _handshake(srv.port, srv.token, image_id, code)
                except _Rejected as e:
                    raise DkError("dkd server rejected the handshake: %s" % _clean(e))
                if got is not None:
                    return got[0], got[1], srv
            if tail is None:
                tail = _LogTail()
            if time.monotonic() > deadline:
                raise DkError("timed out after %d s waiting for dkd server %s to accept "
                              "connections" % (READY_TIMEOUT, NAME))
            time.sleep(delay)
            delay = min(delay * 1.5, 0.5)
    finally:
        if tail is not None:
            tail.stop()


def _clear_dead(srv):
    """An exited container still holds the name (--rm removal pending): wait for it to go, and
    `docker rm` it if it lingers. Ownership (dk64.rootid label) was checked by _named_server."""
    deadline = time.monotonic() + 10
    while time.monotonic() < deadline:
        cur = _inspect(srv.id)
        if cur is None:
            return
        time.sleep(0.2)
    _docker("rm", "-f", srv.id)


def _alive(container_id):
    info = _inspect(container_id)
    return info is not None and (info.get("State") or {}).get("Running") is True


def _rename_away(srv):
    """Rename the retired container (by id) so the name is free for a replacement. Failure is
    fine if the container is already gone or dying (exited/dead/removing)."""
    new_name = "%s-retired-%d-%s" % (NAME, int(time.time()), secrets.token_hex(3))
    rc, _, err = _docker("rename", srv.id, new_name)
    if rc == 0:
        return
    info = _inspect(srv.id)
    if info is None or (info.get("State") or {}).get("Status") in DEAD_STATES:
        return
    raise DkError("cannot rename retired dkd server: %s" % err.strip())


def _retire(srv, image_id, code):
    """Retire srv and free the container name for a replacement.

    Sends RETIRE on a fresh connection and waits for RETIRED (no locked job or lease left; the
    server accepts nothing new from then on). Only then is the container renamed away, with
    the RETIRE connection still open until the rename completed. The rename is by container
    id, so a replacement that already took the name is never touched, and a concurrent client
    doing the same is tolerated. If the connection drops before RETIRED the container is
    re-inspected and RETIRE retried; an unreachable-but-running server is never renamed (it
    might still grant locks) and is given up on after READY_TIMEOUT."""
    notice_at = time.monotonic() + WAIT_NOTICE_DELAY
    noticed = False
    unreachable_since = None
    while True:
        try:
            got = _handshake(srv.port, srv.token, image_id, code) if srv.port else None
        except _Rejected as e:
            raise DkError("dkd server rejected the handshake: %s" % _clean(e))
        if got is None:
            if not _alive(srv.id):
                return  # gone: the name is free or about to be (--rm), nothing to rename
            unreachable_since = unreachable_since or time.monotonic()
            if time.monotonic() - unreachable_since > READY_TIMEOUT:
                raise DkError("dkd server %s is running but not answering; refusing to "
                              "replace it" % NAME)
            time.sleep(0.2)
            continue
        unreachable_since = None
        sock = got[0]
        try:
            sock.sendall(proto.encode(proto.RETIRE, {}))
            while True:
                if not noticed:
                    timeout = max(0.0, notice_at - time.monotonic())
                    if not select.select([sock], [], [], timeout)[0]:
                        _warn("waiting for dkd server to become idle so it can be replaced")
                        noticed = True
                        continue
                frame = proto.recv_frame(sock)
                if frame is None:
                    break
                if frame[0] == proto.RETIRED:
                    _rename_away(srv)
                    return
                if frame[0] == proto.ERROR:
                    raise DkError("dkd server refused RETIRE: %s"
                                  % _clean(frame[1].get("message", "")))
        except (OSError, proto.ProtocolError):
            pass
        finally:
            sock.close()
        time.sleep(0.2)  # connection dropped before RETIRED: re-check the container and retry


def _connect_leased():
    """Nested call under DK64_LEASE: never run the match/retire flow. The server holding the
    lease cannot have been replaced (retire waits for leases) and keeps serving lease RUNs and
    re-entrant HOLDs while retiring, so connect to it whatever its code/image/retiring state.
    Gone or unreachable means the lease is dead: fail, never run unlocked.

    The cached port/token are tried first (no docker call). That is safe: a server that does
    not hold the lease rejects the request as an unknown lease (125), never running it
    unlocked. Only a connect/HELLO failure falls back to `docker inspect`."""
    code = proto.code_hash(ROOT)
    state = _read_state()
    port, token = state.get("port"), state.get("token")
    if isinstance(port, int) and isinstance(token, str):
        try:
            got = _handshake(port, token, "", code)
        except _Rejected:
            got = None
        if got is not None:
            return got
    srv = _named_server()
    if srv is None or srv.status != "running" or srv.port is None or not srv.token:
        raise DkError("lease lost: dkd server %s is gone" % NAME)
    try:
        got = _handshake(srv.port, srv.token, "", code)
    except _Rejected as e:
        raise DkError("lease lost: dkd server rejected the handshake: %s" % _clean(e))
    if got is None:
        raise DkError("lease lost: dkd server %s is not answering" % NAME)
    return got


def _ensure_server():
    """Return (socket, HELLO_OK) for a live, non-retiring server matching our code and image,
    starting or replacing the container as needed (under a lease: the leased server as is)."""
    if os.environ.get("DK64_LEASE"):
        return _connect_leased()
    code = proto.code_hash(ROOT)
    image_id = _wanted_image_id()
    hit = _try_cached(image_id, code)
    if hit is not None:
        return hit
    for _ in range(MAX_ROUNDS):
        srv = _named_server()
        started = False
        if srv is not None and srv.status in DEAD_STATES:
            _clear_dead(srv)
            continue
        attempted = srv is None
        if attempted:
            started = _start(image_id, code)
        ready = _wait_ready(image_id, code, started, attempted)
        if ready is None:
            continue
        sock, hello, srv = ready
        if _matches(hello, image_id, code):
            _update_state(port=srv.port, token=srv.token, container=srv.id)
            return sock, hello
        sock.close()
        _retire(srv, image_id, code)
    raise DkError("could not obtain a matching dkd server after %d attempts" % MAX_ROUNDS)


# --------------------------------------------------------------------------- RUN / HOLD plumbing

class _Job:
    def __init__(self, sock):
        self.sock = sock
        self.granted = False
        self.last_sigint = None


def _install_job_handlers(job):
    """Before GRANTED an interrupt cancels the request (closing the connection withdraws it);
    afterwards it is forwarded to the job, and a second SIGINT within 2 s drops the connection
    (the server kills the job) and exits 130."""
    def handler(signum, _frame):
        if not job.granted:
            raise _Exit(128 + signum)
        if signum == signal.SIGINT:
            now = time.monotonic()
            if job.last_sigint is not None and now - job.last_sigint < DOUBLE_SIGINT_WINDOW:
                raise _Exit(130)
            job.last_sigint = now
        try:
            job.sock.sendall(proto.encode(proto.SIGNAL, {"sig": int(signum)}))
        except OSError:
            pass
    for sig in FORWARDED_SIGNALS:
        signal.signal(sig, handler)


def _lost():
    return DkError("connection to server lost")


def _await_grant(sock, final):
    """Read frames until one of the types in `final` arrives and return it. Prints the single
    `dk: waiting for ...` line if WAITING was seen and 2 s passed without a grant. Returns None
    when the server is retiring (request never ran; caller retries)."""
    sent = time.monotonic()
    waiting = None
    printed = False
    while True:
        timeout = None
        if waiting is not None and not printed:
            timeout = max(0.0, WAIT_NOTICE_DELAY - (time.monotonic() - sent))
        if select.select([sock], [], [], timeout)[0]:
            try:
                frame = proto.recv_frame(sock)
            except (OSError, proto.ProtocolError):
                raise _lost()
            if frame is None:
                raise _lost()
            ftype, payload = frame
            if ftype in final:
                return frame
            if ftype == proto.WAITING:
                waiting = payload
            elif ftype == proto.ERROR:
                if payload.get("retiring"):
                    return None
                raise DkError(_clean(payload.get("message", "server error")))
        if waiting is not None and not printed and time.monotonic() - sent >= WAIT_NOTICE_DELAY:
            held = "; ".join(_clean(h) for h in waiting.get("held_by") or [])
            _warn("waiting for %s lock%s" % (_clean(waiting.get("mode", "?")),
                                             " (held by: %s)" % held if held else ""))
            printed = True


def _submit(ftype, payload, final):
    """Connect (restarting the server if needed), send one request and wait until it is granted.
    A request bounced with ERROR{retiring} never ran, so it is retried on the replacement
    server. -> (_Job, first frame of type in `final`) with the interrupt handlers installed."""
    for _ in range(MAX_RETRIES):
        sock, _hello = _ensure_server()
        job = _Job(sock)
        _install_job_handlers(job)
        try:
            sock.sendall(proto.encode(ftype, payload))
            frame = _await_grant(sock, final)
        except OSError:
            sock.close()
            raise _lost()
        except BaseException:
            sock.close()
            raise
        if frame is not None:
            return job, frame
        sock.close()
        if payload.get("lease"):
            raise DkError("lease lost: server is retiring and refused the request")
    raise DkError("dkd server kept retiring; giving up")


class _Output:
    """Write job bytes to fds 1/2, handling partial writes and non-blocking descriptors. A
    broken/closed descriptor stops being written but the job keeps being drained."""

    def __init__(self):
        self.dead = set()

    def write(self, fd, data):
        if fd in self.dead:
            return
        view = memoryview(data)
        while view:
            try:
                n = os.write(fd, view)
            except BlockingIOError:
                select.select([], [fd], [])
                continue
            except OSError:
                self.dead.add(fd)
                return
            view = view[n:]


def _run(argv):
    lease = os.environ.get("DK64_LEASE") or None
    job, frame = _submit(proto.RUN, {"argv": argv, "lease": lease, "desc": _describe(argv)},
                         {proto.GRANTED, proto.STDOUT, proto.STDERR, proto.EXIT})
    job.granted = True
    out = _Output()
    try:
        while True:
            ftype, payload = frame
            if ftype == proto.STDOUT:
                out.write(1, payload)
            elif ftype == proto.STDERR:
                out.write(2, payload)
            elif ftype == proto.EXIT:
                return int(payload.get("status", proto.DKD_ERROR)) % 256
            elif ftype == proto.ERROR:
                raise DkError(_clean(payload.get("message", "server error")))
            try:
                frame = proto.recv_frame(job.sock)
            except (OSError, proto.ProtocolError):
                raise _lost()
            if frame is None:
                raise _lost()
    finally:
        job.sock.close()


def _hold(cmd):
    lease = os.environ.get("DK64_LEASE") or None
    job, frame = _submit(proto.HOLD, {"desc": _describe(cmd, "hold: "), "lease": lease},
                         {proto.LEASE})
    sock = job.sock
    token = frame[1]["lease"]
    try:
        child = subprocess.Popen(cmd, env=dict(os.environ, DK64_LEASE=token))
    except FileNotFoundError:
        sock.close()
        raise DkError("%s: command not found" % cmd[0], 127)
    except OSError as e:
        sock.close()
        raise DkError("%s: %s" % (cmd[0], e.strerror or e), 126)

    def forward(signum, _frame):
        try:
            child.send_signal(signum)
        except OSError:
            pass
    for sig in FORWARDED_SIGNALS:
        signal.signal(sig, forward)

    finished = threading.Event()
    lost = threading.Event()

    def watch():
        """The lease lives as long as this connection; any frame or EOF from the server
        other than our own close means it is gone."""
        try:
            while proto.recv_frame(sock) is not None:
                pass
        except (OSError, proto.ProtocolError):
            pass
        if not finished.is_set():
            lost.set()
            try:
                child.terminate()
            except OSError:
                pass
            if not finished.wait(5):
                try:
                    child.kill()
                except OSError:
                    pass
    threading.Thread(target=watch, daemon=True).start()

    status = child.wait()
    finished.set()
    sock.close()
    if lost.is_set():
        raise DkError("lease lost")
    return 128 - status if status < 0 else status


def _interactive(argv):
    sock, _hello = _ensure_server()
    sock.close()
    srv = _named_server()
    if srv is None:
        raise DkError("dkd server container %s disappeared" % NAME)
    path = srv.env.get("PATH") or DEFAULT_PATH
    os.execvp("docker", ["docker", "exec", "-it", "-w", "/dk64",
                         "-e", "DKD_SOCK=" + proto.INTERNAL_SOCK,
                         "-e", "PATH=%s:%s" % (SHIM_DIR, path), srv.id] + argv)


# --------------------------------------------------------------------------- --status / --stop

def _connect_named():
    """Connect to the existing server (whatever its code/image) -> (socket, hello, _Srv) or
    None if no server is running. Never starts anything."""
    srv = _named_server()
    if srv is None or srv.status != "running" or srv.port is None or not srv.token:
        return None
    try:
        got = _handshake(srv.port, srv.token, "", proto.code_hash(ROOT))
    except _Rejected as e:
        raise DkError("dkd server rejected the handshake: %s" % _clean(e))
    if got is None:
        raise DkError("dkd server %s is not answering" % NAME)
    return got[0], got[1], srv


def _status():
    found = _connect_named()
    if found is None:
        print("dkd: no server running for %s (container %s)" % (ROOT, NAME))
        return 0
    sock, hello, srv = found
    try:
        sock.sendall(proto.encode(proto.STATUS, {}))
        frame = proto.recv_frame(sock)
    except (OSError, proto.ProtocolError):
        raise _lost()
    finally:
        sock.close()
    if frame is None or frame[0] != proto.STATUS_REPLY:
        raise _lost()
    reply = frame[1]
    code = str(reply.get("code", ""))
    print("server   %s (container %s, id %s)" % (NAME, srv.id[:12], _clean(reply.get("server_id"))))
    print("image    %s" % _clean(reply.get("image")))
    print("code     %s%s" % (_clean(code[:12]),
                             "" if code == proto.code_hash(ROOT) else "  (differs from this checkout)"))
    print("state    %s" % ("retiring" if reply.get("retiring") else "serving"))
    for title, key in (("granted", "granted"), ("waiting", "waiting")):
        entries = reply.get(key) or []
        print("%s  %d" % (title, len(entries)))
        for e in entries:
            keys = ",".join(_clean(k) for k in e.get("keys") or [])
            print("  %-9s %s%s  %s" % (_clean(e.get("mode")), _clean(e.get("holder")),
                                       " keys=" + keys if keys else "", _clean(e.get("desc"))))
    jobs = reply.get("jobs") or []
    print("jobs     %d" % len(jobs))
    for j in jobs:
        print("  %s  lock=%s pid=%s  %s" % (_clean(j.get("id")), _clean(j.get("lock")),
                                             _clean(j.get("pid")), _clean(j.get("desc"))))
    return 0


def _stop():
    found = _connect_named()
    if found is None:
        _warn("no dkd server running")
        return 0
    found[0].close()
    srv = found[2]
    _retire(srv, "", proto.code_hash(ROOT))
    _docker("stop", srv.id)  # may already be gone (--rm): nothing to report
    return 0


# --------------------------------------------------------------------------- entry point

def main(argv):
    args = argv[1:]
    try:
        if args and args[0] == "--hold":
            if len(args) < 2:
                sys.stderr.write(USAGE)
                return 64
            return _hold(args[1:])
        if args and args[0] in ("--status", "--stop"):
            if len(args) != 1:
                sys.stderr.write(USAGE)
                return 64
            return _status() if args[0] == "--status" else _stop()
        tty = sys.stdin.isatty() and sys.stdout.isatty()
        if not args:
            if not tty:
                sys.stderr.write(USAGE)
                return 64
            args = ["/bin/bash"]
        if tty and not os.environ.get("DK64_LEASE"):
            _interactive(args)
        return _run(args)
    except DkError as e:
        for line in str(e).splitlines() or [""]:
            _warn(line)
        return e.code
    except _Exit as e:
        return e.code
    except KeyboardInterrupt:
        return 130


if __name__ == "__main__":
    sys.exit(main(sys.argv))
