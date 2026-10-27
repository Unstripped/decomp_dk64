#!/usr/bin/env python3
"""Private-/tmp probe (dkd integration tests, in-container).

Usage: tmpjob.py <tag> <seconds>
Writes <tag> into /tmp/f, logs a shared START/END interval around `seconds` of sleep, then prints
one JSON line with the file content read back and the directory listing of /tmp.  Two concurrent
jobs with different tags only agree with their own tag if each has a private /tmp.
"""
import json
import os
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ev  # noqa: E402


def main(tag, seconds):
    with open("/tmp/f", "w") as f:
        f.write(tag)
    ev.emit("START", "shared", "tmp-" + tag)
    time.sleep(seconds)
    ev.emit("END", "shared", "tmp-" + tag)
    with open("/tmp/f") as f:
        content = f.read()
    print(json.dumps({"tag": tag, "content": content, "listing": sorted(os.listdir("/tmp"))}))


if __name__ == "__main__":
    main(sys.argv[1], float(sys.argv[2]))
