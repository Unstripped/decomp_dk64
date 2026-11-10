#!/bin/bash
# Compile a PRIVATE COPY of a C file and compare it with expected/ without touching
# build/src/*, so several agents can work on copies of the same file at once.
#
#   tools/fdiff.sh [--non-matching] [--reloc-ok] <copy.c> <src/.../original.c> [FUNC]
#
# The copy is compiled with exactly the flags make uses for the original (asm-processor
# included) into build/.scratch/. Output and exit codes are tools/objdiff.py's:
# 0 OK, 3 TEXT OK (code matches, own data differs), 1 mismatch (asm-differ diff of FUNC).
# --reloc-ok: a relocation-only difference resolving to the same addresses (e.g. `D_807506D0 + 5`
# for a split splat label `D_807506D5`) prints `RELOC-EQUIV OK` and exits 0.
set -e

if [ ! -f /.dockerenv ] && [ ! -d /opt/ido5.3 ]; then
    if [ -n "$EXTRA_CFLAGS" ]; then
        exec tools/dk env EXTRA_CFLAGS="$EXTRA_CFLAGS" tools/fdiff.sh "$@"
    else
        exec tools/dk tools/fdiff.sh "$@"
    fi
fi

OBJDIFF_FLAGS=""
while [ "$1" = "--non-matching" ] || [ "$1" = "--reloc-ok" ]; do
    if [ "$1" = "--non-matching" ]; then
        EXTRA_CFLAGS="$EXTRA_CFLAGS -DNON_MATCHING"
    else
        OBJDIFF_FLAGS="--reloc-ok"
    fi
    shift
done

if [ -z "$2" ]; then
    echo "Usage: tools/fdiff.sh <copy.c> <src/.../original.c> [FUNC]" >&2
    exit 1
fi

COPY="${1#./}"
ORIG="${2#./}"
EXP="expected/build/${ORIG%.c}.o"
[ -f "$EXP" ] || { echo "Error: expected object '$EXP' not found (run make expected)." >&2; exit 1; }

OBJ="build/.scratch/${COPY//\//_}.o"
mkdir -p build/.scratch

# The compile command make would run for the original, retargeted at the copy.
CMD=$(make -n -W "$ORIG" "build/${ORIG%.c}.o" | grep -E 'asm-processor|/opt/ido[0-9.]+/cc' | tail -1)
[ -n "$CMD" ] || { echo "Error: no compile rule found for $ORIG" >&2; exit 1; }
eval "${CMD% -o *} $EXTRA_CFLAGS -o $OBJ $COPY"

case "$EXTRA_CFLAGS" in
    *-DNON_MATCHING*)
        echo "NON_MATCHING: not a match check"
        exit 0
        ;;
esac

exec python3 tools/objdiff.py $OBJDIFF_FLAGS "$OBJ" "$EXP" "$3"
