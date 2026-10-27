"""pytest configuration for the dkd suites.

Makes the flat modules in ``tools/dkd`` (``locks``, ``classify``, ``proto``, ...)
importable by their bare names, exactly as the server imports them inside the
container where ``tools/dkd`` is the script directory.
"""

import sys
from pathlib import Path

DKD_DIR = str(Path(__file__).resolve().parents[1])
if DKD_DIR not in sys.path:
    sys.path.insert(0, DKD_DIR)
