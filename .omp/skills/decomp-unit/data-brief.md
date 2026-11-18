# Data-agent brief template

Fill every `<...>` and copy the whole brief into `local://data-brief.md`; each task names its
class (pragma or carve), files, ranges and owners from `tools/data_owners.py`.

# Goal

Move static data of Donkey Kong 64 (USA) from splat asm to C without changing a ROM byte.
Repository: `/Users/mquinlan/Workspace/purse/games/donkey-kong` (AGENTS.md rules apply:
no game data in git, build tools only via `tools/dk`, never commit). Your task:
`local://tasks/<Name>.md`.

# Knowledge lookups

`python3 tools/quirks.py search --symptom <tag> <words>` before any layout trick; data
order/alignment entries: Q0395, Q0552, Q0838, Q0913, Q0947, Q1137, Q1228 (`get <ID>`).
Report the IDs you used.

# Setup

**Pragma task (private copy):** `mkdir -p .scratch/<Name>`, copy each listed
`src/<seg>/<file>.c` there. Edit only the copies; `src/` changes only through the
orchestrator's merge. Base commit: `<base>`.

**Carve task (worktree):**
```sh
git worktree add -f .scratch/wt-<Name> <base>; rm -rf .scratch/wt-<Name>/.dkd
cp -Rc bin baserom.us.z64 .scratch/wt-<Name>/   # symlinks dangle in its container
cd .scratch/wt-<Name> && tools/dk make split && tools/dk make   # must end build/dk64.us.z64: OK
```
Work, build and commit only inside the worktree (`git -C .scratch/wt-<Name> commit`); you may
run `make split`/`make` there. Never touch the main checkout's `src/`, yaml or build.

# Recipes

Your task names one. The full rules are in `skill://decomp-unit/data.md` §3; the essentials:

- **Pragma:** each `#pragma GLOBAL_ASM("asm/<seg>/nonmatchings/<file>/<label>.s")` becomes a
  definition at the same position with the label's name and explicit size = its stride
  (read the `.s`: `.asciz` length + NUL + `.align` padding). Strings `const char X[N]`,
  scripts/tables `const u8 X[N]`, floats `const f32 X[N]`, an existing struct type where
  the C already declares one, the copying extern's struct type for an aggregate-copy
  blob. Keep extern users `const` (headers: say which; the orchestrator stages them).
- **Carve:** in the yaml, `[0xOFF, data, X]` → `[0xOFF, .data, <owner>]` per TU start
  (16-aligned); merge with an adjacent `.data` subsegment of the same file. Define every
  object in address order in the owner `.c` (function-local statics sit at their
  function's position), explicit sizes, zero objects `= 0`. Split labels inside an object:
  `tools/rename.py fold <seg> <label> <parent-expr>`, else an absolute line in
  `undefined_syms.us.txt`. False splat symbols (`D_80200000`) become integer casts.
  Function pointers use the generated `include/proto` prototypes.
- **Asset include:** a `data_inc.us.txt` row `seg name vram size width file`, then
  `python3 tools/data_inc.py gen` and `T X[N] = {\n#include "<seg>/<name>.inc.c"\n};`.
  Never paste asset bytes into a source file.

# Gates

- Pragma copy: `tools/fdiff.sh .scratch/<Name>/<file>.c src/<seg>/<file>.c` must exit 0, or
  3 with `TEXT OK` and no `.rodata` difference line. Then
  `python3 tools/cwarn.py list --as src/<seg>/<file>.c .scratch/<Name>/<file>.c`: no new
  warning versus `python3 tools/cwarn.py list src/<seg>/<file>.c`.
- Carve worktree: `tools/dk make` ends `build/dk64.us.z64: OK`. On a hash failure run
  `python3 tools/datadiff.py <seg>` (it names the first differing object, symbol and bytes)
  and fix that object; never edit a `.sha1`.
- A same-TU function whose text changes after a carve (function-pointer data, Q0552): retry
  with each entry naming its function exactly as the asm does (no casts); if it still
  differs, keep that TU's run asm (`[0xOFF, data, <name>]`) and report it blocked.

# Rules

- No `// FAKE` steers to make data match; data needs none. Report instead.
- Keep `const` on rodata objects; keep names as splat or the symbol files give them (new
  names only through the symbol file, after the orchestrator agrees).
- Never stage or commit in the main checkout; never delete `asm/` or run `make split` there.
- A finding that contradicts the task's ranges or owners: stop that object and report it
  with addresses and `data_owners.py` output.

# Report (final message)

1. Objects converted: file, label → C definition (type, size), per file.
2. Gate output: the last lines of `fdiff.sh` (pragma) or `tools/dk make` (carve), plus
   `datadiff.py` output if it was used; the worktree commit sha for a carve.
3. Blockers: address, label, the failing gate's output, what you tried.
4. Files outside your list that the change needs (headers, symbol files, `undefined_syms`).
5. Knowledge IDs used; new layout facts with evidence (orchestrator files them).
