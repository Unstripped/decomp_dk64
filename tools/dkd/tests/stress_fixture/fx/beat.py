#!/usr/bin/env python3
"""Heartbeat writer (dkd integration tests, in-container).

Usage: beat.py <heartbeat file>
Appends one line every 0.1 s forever.  Started by orphan.py in its own session so that only the
job's PID-namespace teardown (not process-group signals) can stop it.
"""
import os
import sys
import time


def main(path):
    fd = os.open(path, os.O_WRONLY | os.O_APPEND | os.O_CREAT, 0o644)
    while True:
        os.write(fd, ("%d\n" % time.monotonic_ns()).encode())
        time.sleep(0.1)


if __name__ == "__main__":
    main(sys.argv[1])
