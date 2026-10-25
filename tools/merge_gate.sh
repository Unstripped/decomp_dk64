#!/bin/sh
# Host-side: merge one agent's private copies into src/ and gate on the full ROM build.
#   tools/merge_gate.sh <copy-dir> <base-commit> <src/seg/file.c> [<src/seg/file.c> ...]
# For each src file, merges <copy-dir>/<basename> with `merge_drafts.py merge --base`, stops
# on a merge failure (exit 1 compile/clash, 2 conflict: src left for inspection), then touches
# the files and runs `tools/dk make`; prints GATE_OK only when the build ends with
# `build/dk64.us.z64: OK`. Never commits: commit after GATE_OK yourself.
[ $# -ge 3 ] || { echo "usage: $0 <copy-dir> <base-commit> <src/seg/file.c>..." >&2; exit 64; }
dir=$1; base=$2; shift 2
mkdir -p .scratch
for src in "$@"; do
  name=$(basename "$src")
  log=.scratch/merge_$(basename "$dir")_$name.log
  python3 tools/merge_drafts.py merge --base "$base" "$src" "$dir/$name" > "$log" 2>&1
  rc=$?
  tail -4 "$log"
  echo "merge $src exit $rc"
  [ $rc -eq 0 ] || [ $rc -eq 3 ] || exit $rc
done
touch "$@"
tools/dk make > .scratch/gate.log 2>&1
grep -E 'FAILED|Error|error:|exceeds' .scratch/gate.log | head -5
if tail -3 .scratch/gate.log | grep -q 'build/dk64.us.z64: OK'; then
  echo GATE_OK
else
  echo GATE_FAIL
  exit 1
fi
