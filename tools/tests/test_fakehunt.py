import os
import subprocess
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools import fakehunt as fh  # noqa: E402


def test_descendants_walks_the_host_process_table(monkeypatch):
    tree = {1: [2, 3], 2: [4], 4: [5], 9: [10]}
    monkeypatch.setattr(fh, "nt_children" if os.name == "nt" else "ps_children", lambda: tree)
    monkeypatch.setattr(fh.os, "getpid", lambda: 1)
    assert sorted(fh.descendants()) == [2, 3, 4, 5]


# A child that starts a grandchild holding the same stdout pipe: the pipe reaches EOF only once both are dead.
HARNESS = r"""
import subprocess, sys
sys.path.insert(0, sys.argv[1])
import fakehunt
fakehunt.client_jobs = lambda pids: []  # no dkd server here: only the host process tree
sleep = [sys.executable, "-c", "import time; time.sleep(120)"]
kid = subprocess.Popen([sys.executable, "-c", "import subprocess, sys; "
                        f"subprocess.Popen({sleep!r}, stdout=sys.stdout); print('ready', flush=True); "
                        "import time; time.sleep(120)"], stdout=subprocess.PIPE, text=True)
assert kid.stdout.readline() == "ready\n"
print("before", len(fakehunt.descendants()), flush=True)
fakehunt.stop_children(grace=5)
print("after", len(fakehunt.descendants()), flush=True)
kid.communicate(timeout=10)
print("pipe closed", flush=True)
"""


def test_stop_children_ends_a_real_process_tree():
    """Child and grandchild end on this host (ps + SIGINT on POSIX; Toolhelp32 + TerminateProcess on
    Windows, where a venv's python.exe is a launcher with the interpreter as its child); no container."""
    r = subprocess.run([sys.executable, "-c", HARNESS, str(REPO_ROOT / "tools")], capture_output=True, text=True,
                       timeout=60)
    assert r.returncode == 0, r.stderr
    before, after, closed = r.stdout.split("\n")[:3]
    assert int(before.split()[1]) >= 2 and (after, closed) == ("after 0", "pipe closed")


def test_client_jobs_finds_requests_of_killed_clients(monkeypatch):
    out = ("server   dk64-x (container y, id z)\nstate    serving\ngranted  2\n"
           "  shared    a1.1  sleep 300 [pid 176528]\n  shared    b2.1  python3 tools/variants.py try ... [pid 99]\n"
           "waiting  0\njobs     2\n  a1  lock=shared pid=None  sleep 300 [pid 176528]\n"
           "  b2  lock=shared pid=7  python3 tools/variants.py try ... [pid 99]\n")
    monkeypatch.setattr(fh.subprocess, "run", lambda cmd, **kw: subprocess.CompletedProcess(cmd, 0, out, ""))
    assert fh.client_jobs({176528, 5}) == ["  shared    a1.1  sleep 300 [pid 176528]",
                                           "  a1  lock=shared pid=None  sleep 300 [pid 176528]"]
    assert fh.client_jobs({5}) == []
