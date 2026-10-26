#!/bin/sh
# Host-side: merge one agent's private copies into src/ and gate on the full ROM build.
#   tools/merge_gate.sh <copy-dir> <base-commit> <src/seg/file.c> [<src/seg/file.c> ...]
#   tools/merge_gate.sh - - <src/seg/file.c> ...   re-check src after a manual fix (merge with no copies)
# For each src file, merges <copy-dir>/<basename> with `merge_drafts.py merge --base`, stops
# on a merge failure (exit 1 compile/clash, 2 conflict: src left for inspection), then touches
# the files and runs `tools/dk make`; prints GATE_OK only when the build ends with
# `build/dk64.us.z64: OK`. A merge whose only complaint is `FAILED: Relocations mismatch`
# (reloc-only: own late_rodata as .rodata+off, raw-address constants) goes on to the ROM gate.
# After the build, every file is compiled with -DNON_MATCHING (parked blocks) and any cfe
# error fails the gate. Never commits: commit after GATE_OK yourself.
[ $# -ge 3 ] || { echo "usage: $0 <copy-dir>|- <base-commit>|- <src/seg/file.c>..." >&2; exit 64; }
dir=$1; base=$2; shift 2
mkdir -p .scratch
for src in "$@"; do
  name=$(basename "$src")
  if [ "$dir" = "-" ]; then
    log=.scratch/merge_recheck_$name.log
    python3 tools/merge_drafts.py merge "$src" > "$log" 2>&1
  else
    log=.scratch/merge_$(basename "$dir")_$name.log
    python3 tools/merge_drafts.py merge --base "$base" "$src" "$dir/$name" > "$log" 2>&1
  fi
  rc=$?
  tail -4 "$log"
  echo "merge $src exit $rc"
  if [ $rc -eq 1 ] && grep -q 'FAILED: Relocations mismatch' "$log" && ! grep -qE 'cfe: Error|Error:|error:' "$log"; then
    echo "reloc-only differences: the ROM gate decides"
    continue
  fi
  [ $rc -eq 0 ] || [ $rc -eq 3 ] || exit $rc
done
touch "$@"
tools/dk make > .scratch/gate.log 2>&1
grep -E 'FAILED|Error|error:|exceeds' .scratch/gate.log | head -5
if ! tail -3 .scratch/gate.log | grep -q 'build/dk64.us.z64: OK'; then
  echo GATE_FAIL
  exit 1
fi
for src in "$@"; do
  nmlog=.scratch/nonmatching_$(basename "$src").log
  if ! tools/fdiff.sh --non-matching "$src" "$src" > "$nmlog" 2>&1; then
    grep -iE 'error' "$nmlog" | head -5
    echo "GATE_FAIL: NON_MATCHING compile of $src (log: $nmlog)"
    exit 1
  fi
done
echo GATE_OK
