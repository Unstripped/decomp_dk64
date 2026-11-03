#!/bin/sh
# Host-side: merge one agent's private copies into src/ and gate on the full ROM build.
#   tools/merge_gate.sh [--commit MSG [--stage PATH]...] <copy-dir> <base-commit> <src/seg/file.c> [<src/seg/file.c> ...]
#   tools/merge_gate.sh [--commit MSG [--stage PATH]...] - - <src/seg/file.c> ...   re-check src after a manual fix (merge with no copies)
# For each src file, merges <copy-dir>/<basename> with `merge_drafts.py merge --base`, stops
# on a merge failure (exit 1 compile/clash, 2 conflict: src left for inspection). The merges
# (and their objdiff checks) run in this checkout. A merge whose only complaint is
# `FAILED: Relocations mismatch` (reloc-only: own late_rodata as .rodata+off, raw-address
# constants) goes on to the ROM gate.
# The build runs in a separate gate worktree (DK64_GATE_DIR, default .scratch/gate) with its own
# dkd container: it is reset to HEAD, gets exactly the given src files and every --stage PATH
# copied in (so it builds what the commit will contain), and runs `tools/dk make` there; GATE_OK
# only when that build ends with `build/dk64.us.z64: OK`. The gate tree re-splits itself when a
# splat config or symbol file changed, and touches every C file when include/ changed (make has
# no header deps). Then every file is compiled there with -DNON_MATCHING (parked blocks) and any
# cfe error fails the gate. Agents' tools/dk calls in this checkout never wait for the gate,
# and the gate never waits for them; gates are serialised by an exclusive lease of the gate
# tree's server. This checkout's build/ is not updated by the gate.
# Without --commit it never commits. With --commit MSG it commits only after GATE_OK: deletes
# the drafts of the given files' newly matched functions, then commits exactly the given src
# files, the drafts of their functions (`unit_check.py drafts`) and every --stage PATH (files the
# build depends on outside them: include/ headers, symbol files), never other staged changes;
# any failure exits non-zero before committing, so no pipe can turn a failed gate into a commit.
# Any tracked *.sha1 differing from HEAD fails the gate (checked before the merges and after the build).
root=$(cd "$(dirname "$0")/.." && pwd)
cd "$root" || exit 1
gate=${DK64_GATE_DIR:-$root/.scratch/gate}

if [ -z "$DK64_GATE_LEASE" ]; then
  # First run: create the gate worktree (no .dkd state: it gets its own container).
  if [ ! -e "$gate/.git" ]; then
    git worktree add -q --detach "$gate" HEAD || { echo "GATE_FAIL: cannot create gate worktree $gate"; exit 1; }
    rm -rf "$gate/.dkd"
  fi
  # Serialise gates on the gate tree's server; keep this checkout's own lease (if any) for the merges.
  DK64_MAIN_LEASE=${DK64_LEASE:-} DK64_GATE_LEASE=1 DK64_LEASE= \
    exec "$gate/tools/dk" --hold "$0" "$@"
fi

# tools/dk calls for THIS checkout must not carry the gate tree's lease.
main_dk_env() {
  if [ -n "$DK64_MAIN_LEASE" ]; then env DK64_LEASE="$DK64_MAIN_LEASE" "$@"; else env -u DK64_LEASE "$@"; fi
}

msg=; extra=
if [ "$1" = "--commit" ]; then
  msg=$2; shift 2; [ -n "$msg" ] || { echo "--commit needs a message" >&2; exit 64; }
  while [ "$1" = "--stage" ]; do extra="$extra $2"; shift 2; done
fi
[ $# -ge 3 ] || { echo "usage: $0 [--commit MSG [--stage PATH]...] <copy-dir>|- <base-commit>|- <src/seg/file.c>..." >&2; exit 64; }
dir=$1; base=$2; shift 2
sha1_guard() {
  changed=$(git diff --name-only HEAD -- '*.sha1') || { echo "GATE_FAIL: git diff failed"; exit 1; }
  [ -z "$changed" ] || { echo "GATE_FAIL: expected hashes differ from HEAD:" $changed; exit 1; }
}
sha1_guard
mkdir -p .scratch
for src in "$@"; do
  name=$(basename "$src")
  if [ "$dir" = "-" ]; then
    log=.scratch/merge_recheck_$name.log
    main_dk_env python3 tools/merge_drafts.py merge "$src" > "$log" 2>&1
  else
    log=.scratch/merge_$(basename "$dir")_$name.log
    main_dk_env python3 tools/merge_drafts.py merge --base "$base" "$src" "$dir/$name" > "$log" 2>&1
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

# Gate tree = HEAD + the given files + --stage paths.
head=$(git rev-parse HEAD) || exit 1
prev=$(git -C "$gate" rev-parse HEAD) || exit 1
git -C "$gate" checkout -q -f --detach "$head" || { echo "GATE_FAIL: gate checkout failed"; exit 1; }
git -C "$gate" clean -fdq -- src include drafts || exit 1
for p in "$@" $extra; do
  if [ -e "$p" ]; then
    mkdir -p "$gate/$(dirname "$p")" && cp -p "$p" "$gate/$p" || exit 1
  else
    rm -f "$gate/$p"
  fi
done
[ -d "$gate/bin" ] || cp -Rc bin "$gate/" 2>/dev/null || cp -R bin "$gate/" || exit 1
[ -e "$gate/baserom.us.z64" ] || cp -c baserom.us.z64 "$gate/" 2>/dev/null || cp baserom.us.z64 "$gate/" || exit 1
glog=$gate/.scratch/gate.log
mkdir -p "$gate/.scratch"
stamp() { (cd "$gate" && cat dk64*.yaml symbol_addrs*.txt undefined_syms*.txt | shasum | cut -c1-40); }
want=$(stamp)
if [ ! -d "$gate/asm" ] || [ "$(cat "$gate/.scratch/split.stamp" 2>/dev/null)" != "$want" ]; then
  echo "gate: splitting the gate tree"
  (cd "$gate" && tools/dk make split > .scratch/split.log 2>&1) || { tail -5 "$gate/.scratch/split.log"; echo "GATE_FAIL: gate split failed"; exit 1; }
  echo "$want" > "$gate/.scratch/split.stamp"
  find "$gate/src" -name '*.c' -exec touch {} +
elif ! git -C "$gate" diff --quiet "$prev" HEAD -- include || [ -n "$(git -C "$gate" status --porcelain -- include)" ]; then
  find "$gate/src" -name '*.c' -exec touch {} +
fi
(cd "$gate" && touch "$@" && tools/dk make > "$glog" 2>&1)
grep -E 'FAILED|Error|error:|exceeds' "$glog" | head -5
if ! tail -3 "$glog" | grep -q 'build/dk64.us.z64: OK'; then
  echo "GATE_FAIL (log: $glog)"
  exit 1
fi
# fdiff.sh --non-matching reads the expected object's flags: snapshot this (matching) build.
(cd "$gate" && tools/dk make expected > .scratch/expected.log 2>&1) || { tail -5 "$gate/.scratch/expected.log"; echo "GATE_FAIL: gate make expected failed"; exit 1; }
sha1_guard
for src in "$@"; do
  nmlog=$gate/.scratch/nonmatching_$(basename "$src").log
  if ! (cd "$gate" && tools/fdiff.sh --non-matching "$src" "$src" > "$nmlog" 2>&1); then
    grep -iE 'error' "$nmlog" | head -5
    echo "GATE_FAIL: NON_MATCHING compile of $src (log: $nmlog)"
    exit 1
  fi
done
echo GATE_OK
if [ -n "$msg" ]; then
  [ "$(git rev-parse HEAD)" = "$head" ] || { echo "COMMIT_FAILED: HEAD moved during the gate"; exit 1; }
  drafts=$(python3 tools/unit_check.py drafts --prune "$@") || exit 1
  git add -A -- "$@" $drafts $extra && git commit -q -m "$msg" -- "$@" $drafts $extra || { echo "COMMIT_FAILED"; exit 1; }
  echo "COMMITTED $(git rev-parse --short HEAD)"
fi
