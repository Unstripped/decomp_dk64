#!/usr/bin/env python3
"""Replay a recorded write schedule onto fd 1 / fd 2 (dkd integration tests, in-container).

Argument: path of a spec file made of records `<1 byte fd><4 byte big-endian length><data>`.
Each record is written with os.write on the raw descriptor (looping on short writes), so the
chunk boundaries and the stdout/stderr interleaving are exactly the recorded ones.
"""
import os
import sys


def write_all(fd, data):
    view = memoryview(data)
    while view:
        n = os.write(fd, view)
        view = view[n:]


def main(path):
    with open(path, "rb") as f:
        blob = f.read()
    pos = 0
    while pos < len(blob):
        fd = blob[pos]
        size = int.from_bytes(blob[pos + 1:pos + 5], "big")
        write_all(fd, blob[pos + 5:pos + 5 + size])
        pos += 5 + size


if __name__ == "__main__":
    main(sys.argv[1])
