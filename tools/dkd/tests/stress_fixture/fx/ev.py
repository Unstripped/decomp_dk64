#!/usr/bin/env python3
"""Event-log helper for the dkd integration tests (runs INSIDE the toolchain container).

Every lock-observing fixture job records `<PHASE> <kind> <id> <monotonic ns>` lines in the shared
log `<root>/.evlog/events.log`.  Each line is emitted with ONE os.write on an O_APPEND descriptor,
so concurrent jobs never interleave partial lines.  Timestamps come from CLOCK_MONOTONIC, which is
shared by every container on the same kernel, so intervals recorded by different servers (e.g.
across a retire/restart) are directly comparable.

Usage:
    ev.py run <kind> <id> <seconds>     START line, sleep, END line, prints "done <id>" on stdout
    ev.py log <START|END> <kind> <id>   one line only (used for lease span markers)

`kind` is one of: shared, exclusive, keyed:<key>, unlocked, none.
"""
import os
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LOG = os.path.join(ROOT, ".evlog", "events.log")


def emit(phase, kind, ident):
    """Append one event line atomically."""
    os.makedirs(os.path.dirname(LOG), exist_ok=True)
    line = ("%s %s %s %d\n" % (phase, kind, ident, time.monotonic_ns())).encode()
    fd = os.open(LOG, os.O_WRONLY | os.O_APPEND | os.O_CREAT, 0o644)
    try:
        os.write(fd, line)
    finally:
        os.close(fd)


def run(kind, ident, seconds):
    """Log START, hold for `seconds`, log END, then report completion on stdout."""
    emit("START", kind, ident)
    time.sleep(seconds)
    emit("END", kind, ident)
    sys.stdout.write("done %s\n" % ident)
    sys.stdout.flush()


def main(argv):
    if len(argv) == 5 and argv[1] == "run":
        run(argv[2], argv[3], float(argv[4]))
    elif len(argv) == 5 and argv[1] == "log":
        emit(argv[2], argv[3], argv[4])
    else:
        sys.stderr.write(__doc__)
        return 2
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
