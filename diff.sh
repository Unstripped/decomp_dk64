#!/bin/sh
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

if [ $# -eq 0 ]; then
    echo "Usage: $0 [-s SEGMENT] FUNC [extra diff.py args]" >&2
    echo "Segments: boot (default), global, multiplayer, minecart, bonus, race, critter, boss, arcade, jetpac, menu" >&2
    exit 1
fi

SEGMENT="${DIFF_SEGMENT:-boot}"

if [ "$1" = "-s" ] || [ "$1" = "--segment" ]; then
    if [ $# -lt 2 ]; then
        echo "Error: $1 requires a segment name" >&2
        echo "Usage: $0 [-s SEGMENT] FUNC [extra diff.py args]" >&2
        echo "Segments: boot (default), global, multiplayer, minecart, bonus, race, critter, boss, arcade, jetpac, menu" >&2
        exit 1
    fi
    SEGMENT="$2"
    shift 2
    if [ $# -eq 0 ]; then
        echo "Error: missing function name" >&2
        echo "Usage: $0 [-s SEGMENT] FUNC [extra diff.py args]" >&2
        exit 1
    fi
fi

if [ ! -f /opt/asm-differ/diff.py ]; then
    echo "Error: /opt/asm-differ/diff.py not found." >&2
    echo "Run via Docker toolchain: tools/dk ./diff.sh [args]" >&2
    exit 1
fi

export DIFF_SEGMENT="$SEGMENT"
exec python3 /opt/asm-differ/diff.py "$@"
