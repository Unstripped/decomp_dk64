"""Fake permuter: `python3 tools/permute.py run <id> <seconds>` (dkd integration tests).

dkd classifies `tools/permute.py run` as a lock-free ("none") job; this logs a `none` interval.
"""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "fx"))
import ev  # noqa: E402

if __name__ == "__main__":
    ev.run("none", sys.argv[2], float(sys.argv[3]))
