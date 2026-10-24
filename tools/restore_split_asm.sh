#!/bin/sh
# Restore asm/<seg>/nonmatchings/*/*.s files deleted by a mid-unit re-split.
#
# A `make split` / splat run while agents work deletes the .s of every function
# matched since the agents' base commit, so their private copies (still GLOBAL_ASM
# for those functions) stop compiling. This re-splits <commit> in a temporary
# worktree and copies back every .s file (and directory) missing from asm/.
# Existing files are never overwritten.
#
# usage: tools/restore_split_asm.sh <commit> <segment yaml>
#   e.g. tools/restore_split_asm.sh c308a49 dk64.global.us.yaml
set -eu
commit=$1
yaml=$2
wt=.scratch/wt-restore
git worktree remove --force "$wt" 2>/dev/null || true
git worktree add -f "$wt" "$commit" >/dev/null
ln -sfn ../../bin "$wt/bin"
tools/dk sh -c "cd $wt && python3 -m splat split $yaml >/dev/null 2>&1"
n=0
for f in $(cd "$wt" && find asm -path '*/nonmatchings/*' -name '*.s'); do
    if [ ! -e "$f" ]; then
        mkdir -p "$(dirname "$f")"
        cp "$wt/$f" "$f"
        n=$((n + 1))
    fi
done
git worktree remove --force "$wt"
echo "restored $n file(s)"
