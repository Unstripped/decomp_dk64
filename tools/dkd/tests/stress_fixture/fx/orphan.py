#!/usr/bin/env python3
"""Job that leaves a setsid'ed heartbeat grandchild behind (dkd integration tests, in-container).

Usage: orphan.py [--trap] <heartbeat file> <seconds>
Spawns beat.py in a new session, prints "started", then sleeps `seconds`.  With --trap, SIGHUP /
SIGINT / SIGTERM make this process exit with status 128+N immediately (the grandchild is NOT told,
so it only dies if the server tears down the job's whole process tree).
"""
import os
import signal
import subprocess
import sys
import time


def main(argv):
    trap = argv[0] == "--trap"
    if trap:
        argv = argv[1:]
        for sig in (signal.SIGHUP, signal.SIGINT, signal.SIGTERM):
            signal.signal(sig, lambda signum, _frame: os._exit(128 + signum))
    heartbeat, seconds = argv[0], float(argv[1])
    beat = os.path.join(os.path.dirname(os.path.abspath(__file__)), "beat.py")
    subprocess.Popen([sys.executable, beat, heartbeat], start_new_session=True,
                     stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    sys.stdout.write("started\n")
    sys.stdout.flush()
    deadline = time.monotonic() + seconds
    while time.monotonic() < deadline:
        time.sleep(0.1)


if __name__ == "__main__":
    main(sys.argv[1:])
