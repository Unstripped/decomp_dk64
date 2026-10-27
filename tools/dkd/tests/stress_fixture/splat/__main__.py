"""`python3 -m splat run <id> <seconds>`: log an exclusive interval (see splat/__init__.py)."""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "fx"))
import ev  # noqa: E402

if __name__ == "__main__":
    ev.run("exclusive", sys.argv[2], float(sys.argv[3]))
