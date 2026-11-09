#!/bin/bash
set -e

# If running on host, delegate to tools/dk
if [ ! -f /.dockerenv ] && [ ! -d /opt/ido5.3 ]; then
    exec tools/dk tools/objdiff.sh "$@"
fi

if [ -z "$1" ]; then
    echo "Usage: tools/objdiff.sh <path/to/file.c> [function_name]" >&2
    exit 1
fi

C_FILE="$1"
# Strip leading ./
C_FILE="${C_FILE#./}"

# Convert src/.../*.c to build/src/.../*.o
OBJ="build/${C_FILE%.c}.o"
EXP="expected/$OBJ"

if [ ! -f "$EXP" ]; then
    echo "Error: expected object '$EXP' not found." >&2
    exit 1
fi

# Build ONLY this object (quietly, leaving other outputs untouched). -B: the Makefile has no
# header dependencies, so an object built before a header edit would otherwise be reused.
make -B "$OBJ" > /dev/null

# Compare sections and relocations
python3 tools/objdiff.py "$OBJ" "$EXP" "$2"
