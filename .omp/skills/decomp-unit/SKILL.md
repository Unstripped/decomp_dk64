---
name: decomp-unit
description: Orchestrate one unit of DK64 matching-decompilation work (split a segment into C, parallel matching rounds, naming, ROADMAP, ok-fine) with subagents. Use when asked to "orchestrate the next unit of work" on this decomp.
---

# DK64 decompilation unit

One unit = pick the next segment or subsystem, make it C, match as many functions as the
rounds yield, name them, record status. AGENTS.md rules always apply (matching build,
no game data, tools only via `tools/dk`). Compiler quirks and per-overlay facts live in
ok-fine, not here; this skill is the procedure.

## 0. Ingest

1. ok-fine: `list_projects` with `repository` = `git remote get-url origin`; read
   `architecture/overlay-c-units`, `notes/ido-matching-quirks`, `runbooks/decompile-function`,
   and any concept for the chosen subsystem (`search_concepts`).
2. Re-read `ROADMAP.md` section 9 and this skill's Run log; `git status` (unexpected
   changes are the user's).
3. `tools/dk make` must end with `build/dk64.us.z64: OK`; `tools/dk make progress` for the
   starting numbers.

## 1. Pick the unit

ROADMAP order: overlays smallest-first by `<ovl>_TEXT_SIZE` in `Makefile`, two at a time
(they are independent); then the listed global subsystems. All nine overlays are C units
since the boss unit (2026-10-22): next units are global subsystems (the next candidate
files named at the end of ROADMAP's section 9 bullets, e.g. `CC800`, `CEAE0`)
or further matching rounds on near-misses listed in
ROADMAP. A global subsystem is a set of `asm/global/<file>.s` files: find them from what
the overlays' named functions call (`grep -o 'func_80[67]…'` in their C) and from the
globals each file references most (`grep -oE '%hi\(D_[0-9A-F]+\)' asm/global/<f>.s | sort | uniq -c`).
Count the work:

```sh
for s in asm/<seg>/nonmatchings/<file>/*.s; do echo "$(grep -c '^ *\/\* ' $s) $s"; done
for f in asm/global/*.s; do echo "$f $(grep -c ^glabel $f) $(grep -c '^ *\/\* [0-9A-F]' $f)"; done  # still-asm global files
```

Skip hand-written asm before converting: a file with 64-bit ops or `$k0`/`$k1` is not IDO
C (`77B90` collision code: 579 `ld`/`sd`/`dmult`; also `15010`, `16B60`, `61690`):
`grep -cE '\s(dmult|ld|sd|daddu?)\s|\$k[01]' asm/global/<f>.s` must be 0.
Find hidden empty functions (unsymbolised `jr $ra; nop` pairs merged into a preceding
function's `.s`) in the same pass: any glabel with more than one `jr $ra` is a candidate
(`CBEA0` opened with 26 of them); write them as `void func_ADDR(void) {\n}` in the seeded
stub yourself:
`awk '/^glabel/{g=$2;n=0} /jr +\$ra/{if(++n>1) print g, $2}' asm/global/<f>.s`.

## 2. Split into C (one agent per segment, parallel; a lone segment: do it inline)

Agent edits only `dk64.<seg>.us.yaml`, `symbol_addrs.<seg>.us.txt`, `src/<seg>/*.c`;
re-splits only its own segment (`tools/dk python3 -m splat split dk64.<seg>.us.yaml`) and
may build only `build/<seg>.text.bin build/<seg>.data.bin` + `sha1sum -c dk64.<seg>.us.sha1`.
TU boundary evidence, from the all-asm split: `python3 tools/rodata_owners.py <seg>` lists
each run of data/rodata labels with its owning text file and kinds (under 1 s on `global`;
grep its output for your files); a string/word run
after doubles/jump tables inside one splat file is a hidden TU (boss `9C60` was three:
`9C60`/`A7A0`/`B100`), and so is a `(TU end pad after <label> ...)` flag inside one owner's
run: IDO pads every object's rodata to 16 bytes, so unreferenced zero bytes reaching a
16-byte boundary end a TU (global `699B0` was three: `699B0`/`69E60`/`6AD90`, missed at
split time and found only when round-1/2 agents matched code but not rodata; the tool
lists 15 more such flags inside still-asm global files, e.g. `17B90`, `36880`, `42630`,
`A8400`, `CEAE0` (two), `1025E0`, `114270`, `119370`). Split those BEFORE round 1. To find
which function owns the padded label, grep `asm/<seg>/<file>.s` for it. Place the text
boundary at the only 16-byte-aligned function start
between the owners' functions. Also: nop padding only at file ends, 16-byte alignment.
BSS use narrows it too: `func_80666090` touched only the later TU's bss cluster
(`D_807F9514`–`D_807F951C`), so the `69E60`/`6AD90` boundary went before it.
When several 16-aligned starts qualify, data ownership can narrow them: a 16-aligned
`.data` object whose users all lie in the later TU marks where that TU's data starts, so
the text boundary is at or before its first user (an upper bound, not the boundary itself:
a TU may start several functions earlier). `8F4B0`/`90D80`: `D_807501E0`, first used by
`func_8068C20C`, left `func_8068C080` as the only aligned start after the last first-TU
rodata owner. If candidates remain, look for other ownership evidence (rodata/data users,
padding) before choosing.
Unreferenced strings that end exactly where a file's first rodata label starts (no
alignment gap) belong to that file's TU (actor `7CA80` kong names).
Overlays: data stays one named asm `[0xOFF, data, 0]`. Global: data stays in the shared
`[0x14B740, data]` blob; only add `.rodata` entries. Rodata `.rodata` per file. A first build
that is exactly N bytes long usually means an unreferenced late_rodata float (owner `-`
in the tool output) was emitted as `.rodata`; fix in the symbol file (ok-fine quirks).
An f32+f64 pair splat merged into one label (`999999.0f`, pad, unreferenced `2000.0`)
shows up as a standalone `asm/<seg>/nonmatchings/<file>/D_XXXXXXXX.s`: give the float
`type:f32 size:0x4` and the double `type:f64 force_migration:True function_owner:<func>`.
After any symbol fix, delete the freshly generated (still unedited) stub `src/<seg>/<file>.c`
files and re-split (stubs keep `GLOBAL_ASM` lines for the vanished standalone files), then
`touch src/<seg>/*.c` (make does not rebuild objects whose asm changed).
Seed every new stub before round 1, under `#include "common.h"`: `#include "actor.h"` (global)
and the file family's shared hot externs with one agreed type (behaviour files:
`extern Actor *D_807FBB40; extern Actor *D_807FBB4C; extern ActorGlobalState D_807FBB70;
extern u8 D_807FBD70;`); the brief then forbids redeclaring them and asks for agent-prefixed
view macros (`#define R1DA ((R1DView *)D_807FBB40)`) for missing fields. Otherwise every
round-1 copy adds them with its own type and each merge after the first conflicts (the
`BA790`–`BDEE0` unit, seeded, needed no unify agent). Commit the seeded stubs, then snapshot.

Gate: `tools/dk make` OK, then `tools/dk make expected`. Commit
`Overlays: split <a> (<files>) and <b> (<files>) as C units (GLOBAL_ASM baseline)`.

## 3. Matching rounds (up to 6 agents per round)

1. Partition by instruction count: round 1 ~600–1,300 per agent, ≤20 functions,
   contiguous by address; functions over ~400 insns held back for later rounds, each
   on its own agent using the large-function method (stage-order work plus a bounded
   permuter run once at stage 5–6). Large agents matched 0 in five units, then 6 of 10 in
   the `ACDC0`–`B7490` unit and 2 of 5 directly in the `BA790`–`BDEE0` unit, whose other three
   (parked at stage 6) all matched in one near-miss round: the 430–760-insn enemy-behaviour
   functions share one shape, so
   each finished large agent's key tricks (`s32 sel` switch copy, spare K&R arg pinning
   `$a1`, non-void callee return types for v0/v1 swaps) went into the next large and
   near-miss agent's task text; 800+-insn HUD functions still parked
   at stage 4–6. Dispatch large agents as soon as slots free, smallest first, and forward
   every large-function trick (`write agent://<id>`, one by one). Later rounds ≤6 functions
   per agent, near-misses first; a stage-6 near-miss of 1–8 insns is worth one dedicated
   agent each (5 of 6 matched in that unit, 6–35 min). In the `C0EE0`–`CBEA0` unit large
   agents given the previous units' tricks matched 5 of 7 directly (4–8 min each for
   420–1029 insns). A SECOND dedicated pass on a stage-6 near-miss is worth it when the
   context carries the round's new key findings (register preference from a shared
   variable, uopt `compute_save` arithmetic): 2 of 5 second passes matched there
   (`func_806BE8BC`, `func_806C75A4`); two stage-6 ones dropped to 2 and 9 pairs, the
   1384-insn stage-5 one barely moved.
   Near-miss rounds and large functions use the stage order, `tools/uopt_trace.sh`,
   and permuter. Never a function in two agents' lists, and never one in none: before
   dispatch, diff the union of the lists (round 1 plus held-back large functions) against
   `ls asm/<seg>/nonmatchings/<file>/func_*.s` (the audio unit silently skipped two
   400-insn functions until review). Every agent works in PRIVATE COPY mode,
   even alone on a file, so `src/` only changes by your merges and the full build can gate
   each commit while agents run.

   Methodology for large functions and near-misses:
   - Stage order for non-trivial functions (OoT IDO 5.3 -O2 guide, https://github.com/n64decomp/oot/blob/master/docs/guides/-O2%20decompilation%20(for%20IDO%205.3).md):
     (1) behaviourally equivalent C (m2c), (2) basic-block order, (3) large reorderings,
     (4) same callee-saved register set and frame size, (5) small reorderings,
     (6) register allocation. Agents report the stage reached, not only an instruction
     count. Register-allocation tricks are wasted before stage 4.
   - Why large functions are hard: IDO's uopt assigns registers by priority-based coloring
     (Chow & Hennessy, TOPLAS 1990, https://doi.org/10.1145/88616.88621): priority = estimated
     savings of a live range weighted by block frequency and normalised by its length,
     highest first, with live-range splitting; so a change in one loop shifts registers in another.
   - Diagnose register allocation with `tools/uopt_trace.sh [-l LEVEL] [-s src/<seg>/<file>.c] <file.c> [FUNC]`
     on a private copy before guessing (level 6 = coloring trace, 5 = live ranges/savings;
     see header comment in `tools/uopt_trace.sh` for how to read it): compare which candidate
     got which register with the target asm.
   - Use the permuter at stages 5–6: `tools/permute.py setup <seg> <FUNC> [--from FILE.c] [--src src/<seg>/<file>.c]`
     -> `.scratch/permuter/<seg>_<FUNC>/` (base.c from the stored draft by default, target.o
     from the function's asm, compile.sh with make's flags), `tools/permute.py run <dir> [-j N] [--seconds S]`
     (always passes `--stack-diffs` and `--stop-on-zero`, default -j = half the CPUs),
     `tools/permute.py best <dir>` (lists outputs by score and diffs best against base.c).
     Its mutations are NOT semantics-preserving (moves statements, randomises types, deletes
     if statements) and its score checks disassembly (stack only via `--stack-diffs`), not
     relocations or data. A result is a search hint: rewrite the idea into readable C that
     keeps the asm's behaviour; then the normal gates (fdiff/objdiff OK or TEXT OK, then full
     ROM `build/dk64.us.z64: OK`). Never paste permuter output unreviewed. Several agents
     share the CPU: give each permuter run an explicit small -j (e.g. `-j 2`) and `--seconds` limit.
   - NON_MATCHING parking: a function that will not match but whose C is behaviourally equivalent
     (remaining diff only regalloc/scheduling/stack layout, reviewed) may go into `src` as:
     ```c
     #ifdef NON_MATCHING
     <C>
     #else

     #pragma GLOBAL_ASM("asm/...")
     #endif
     ```
     (asm-processor drops the asm when the dummy is ifdef'd out; note the required blank line
     before `#pragma GLOBAL_ASM`). `tools/dk make NON_MATCHING=1` builds into `build_nonmatching/`
     without any hash check ('Build complete (NON_MATCHING=1: output is not compared)');
     `make expected`/`progress` refuse `NON_MATCHING=1`; the default build is unchanged and
     still the only gate. Parked functions count as unmatched. Otherwise keep the draft in `drafts/`.
2. For every file, BEFORE dispatch: `python3 tools/merge_drafts.py snapshot src/<seg>/<file>.c`.
3. Write the filled [brief.md](brief.md) once to `local://brief.md` and pass the `context`
   "Read `local://brief.md` FIRST and follow it exactly", plus per-file facts and the
   previous rounds' tricks for that file; each `tasks[]` item lists its functions
   with the last known diff note and stage reached; agents start from the stored draft
   (`tools/drafts.py show SEG FUNC`; drafts are keyed by segment because overlays share names like `func_80024000`), not from m2c.
   Agents finish after 15–25 min whatever the list length; re-prompting an idle agent to
   "continue" returned the same report with no new matches (boss round 1, 5 tries):
   dispatch the next round instead. Round-1 agents of the `55B20` unit stopped at 11–13 min
   with functions never attempted; adding "Use your WHOLE budget (~25+ minutes) before
   reporting" to every later task `context` made agents run 20–37 min. Check each report
   against its assigned list before merging: `M55P3` silently skipped `func_80654418`.
   Rolling dispatch: rounds are per agent, not per file or global. Every copy names its
   exact base commit (`git show <commit>:src/<seg>/<file>.c > .scratch/<YourName>/<file>.c`),
   so merge EACH agent's copy as soon as it finishes (`merge --base <its commit> ...`), gate,
   commit, and refill the freed slot at once from the new HEAD (`699B0` unit: 12 merges into
   one file while 4–5 siblings kept running, no lost work). Only a TU re-split of a file
   waits for every agent on that file.
   Cross-agent discovery: when an agent finds a key compiler pattern that unblocks a common
   near-miss (e.g. `if (reg++ == 2)` post-increment equality placing the store in the delay
   slot for `xori`/`addiu`), immediately forward it to running siblings via `write agent://<id>`.
4. Merge each shared file: `python3 tools/merge_drafts.py merge src/<seg>/<file>.c .scratch/<A>/<file>.c ...`
   (merges into the current `src`, so edits made after the snapshot survive; drops
   duplicate declarations (keeping the first, but never pruning an unconditional one as a
   duplicate of a copy inside `#if`, i.e. parked NON_MATCHING code) and unused ones the drafts
   added; prints clashing declarations on compile errors; exit 2 on conflicts leaves `src`
   untouched).
   Drafts copied before the latest snapshot (an agent still running from an older round):
   `merge --base <commit the copy started from> src/... .scratch/<A>/...`, else the merge
   reverts everything committed since.
   Callee prototype clashes are now the usual merge failure (cfe "redeclaration" or
   "prototype and non-prototype"): one agent's `void f();` K&R vs another's prototyped
   definition, `u8` vs `s32` first parameter, `void *` vs `Actor *`. Fix inline: keep the
   declaration that already matches in `src` (or the definition), delete the other, re-run
   `merge src/<seg>/<f>.c` (re-prunes and re-checks) and `--non-matching`. If the kept
   prototype changes the other agent's code (an `andi` appears or vanishes), adapt that
   function's local types (`u8 sel` instead of `s32 sel` restored `func_806BA76C`), never
   the prototype a matched caller relies on. Move a declaration above its first user when a
   pasted function needs it earlier in the file.
   Round 1 on a fresh file without a seeded top block yields per-agent types
   (`ActAActor`, `BehBActor`) that clash: dispatch one unify fix-up agent per file right
   after round 1 (PRIVATE COPY, merged
   like a round; it extends the shared header in place, additively only), that
   creates/extends a shared header (`include/actor.h`) with one struct per object and moves
   all declarations to one top block. Two files sharing a header: serialize their unify
   agents (second extends the header additively), but start the first file's round 2 at
   once. A clash of one global between two drafts: unify inline. On one fresh file split
   across 6 round-1 agents (`55B20`) nearly every merge had one (`D_807F6C18` struct,
   `D_807F70B0` struct vs `s32`, `func_80610FE8` `s32` vs `void *`): delete the newer
   declaration and adapt its users (a cast in parked code, `&arr[i]` for byte offsets),
   check both sides (`tools/fdiff.sh [--non-matching] src/<seg>/<f>.c src/<seg>/<f>.c`), and
   name the merged structs in every later task's `context` so new agents reuse them.
   A file-local clash (types only one file uses): run the failing merge, copy the merged
   (non-compiling) `src` file to `.scratch/Unify<F>/<file>.c`, `git checkout` the src file,
   and give the unify agent that copy; its result replaces `src` directly (`cp`) if `src`
   has not changed since. If that file's agents are still running, start the clashing
   agent's next round FROM ITS OWN PRIVATE COPY (`cp .scratch/<A>/<file>.c .scratch/<B>/`)
   so it keeps its types, and merge it with `--base <commit its copy started from>`.
5. Merge single-agent copies the same way; revert declaration-only leftovers from
   zero-yield agents. Then persist drafts: `python3 tools/drafts.py collect` (imports any
   newer `.scratch/*/<FUNC>_best.c` an agent left instead of saving; check `git diff drafts/`
   after it: it once replaced a draft saved with a note by a note-less older `_best.c`) and
   `python3 tools/drafts.py prune` (drops drafts of functions that now match); commit
   `drafts/<seg>/<FUNC>.c` is the only place in-progress C
   survives a session; `.scratch/` is per-session and may be wiped. Parked NON_MATCHING
   functions stay in `src/` under `#ifdef NON_MATCHING`.
6. Gate EVERY commit with the full build: `tools/dk make` must end with
   `build/dk64.us.z64: OK` (AGENTS.md: never commit a non-matching state). Per-file
   `tools/objdiff.sh` OK/TEXT OK is only a pre-check: TEXT OK hid a `.rodata` shift once (a C
   jump table dropped the 4-byte late_rodata pad before an asm function's floats, `7AF60`
   `func_8067680C`) and two swapped externs in one comparison (`D_807FBB4C == D_807FDC94`,
   `func_806BB32C`); `objdiff.py` now fails on `.rodata` byte diffs and on `D_` labels that
   resolve to different addresses, but the ROM hash stays the gate. A merge whose check
   prints `FAILED` after the agent's copy passed means the unified declarations changed
   another function's code: `objdump -dr` both objects and diff before anything else. Run
   the gate as its own step: `touch` the
   merged files, run `tools/dk make`, and commit only after seeing `build/dk64.us.z64: OK`
   (a `make | grep 'FAIL|OK' && git commit` chain committed a red tree: grep also matches
   the FAILED line). Commit `<Seg>: match N/T <file> functions`.
7. Stop rule: stop a file after a round that matched fewer than ~1 function per agent, or
   when only near-misses and 500+-insn functions remain. Record the closest diffs in ROADMAP.
8. An agent that reports "100% instruction match, objdiff fails only on relocations"
   (expected asm used a raw address such as `lui 0x8080; sb -0x6B52` where C uses
   `D_807F94AE`, or a named label where IDO emits `.rodata+off` / `sym+0xA0`): paste its
   draft into `src` and let the ROM hash decide (`func_80668520`, `func_80697CEC`,
   `func_80658BD0` matched that way). If the ROM fails it was not reloc-only: `tools/dk make
   build/global.text.bin`, `cmp -l` against the last good copy and objdump the function to
   find the real diff (the first `func_80658BD0` draft had a `sb` two slots early behind the
   reloc message); revert and fix the draft note. An agent that matches code but not rodata
   padding has found a hidden TU (section 2).

## 4. Names, ROADMAP, knowledge

1. One naming agent per segment: only matched-C functions with behaviour confirmed from
   the code, `name = 0xADDR; // type:func` in `symbol_addrs.<seg>.us.txt`, rename in
   `src/<seg>/`, re-split own segment, check own sha1. Give it the agents' reports
   (save each as it arrives: `read agent://<id>` appended to `.scratch/all-reports.md`, then
   write that file to `local://all-reports.md`; start the file fresh per unit). Tell it to reject
   address-encoding report names (`actorEnqueueTableD5D0`), rename agent-prefixed types
   (`Act8CA_Node` → `AnimNode`) in the unit's files, and NEVER edit `tools/` (one patched
   `objdiff.py` to resolve renamed symbols by address; reverted): renamed functions
   differ from `expected/` by name only, the ROM build after step 2 is the check. It can
   run while a last agent works on one file if it skips that agent's functions. Tell it to
   rename the old `func_` names in EVERY other `src/` C file that calls them (overlays
   included) and never to add `#pragma weak func_X = name` aliases (the `68960`–`6AD90`
   namer added 69 of them to make `build/global.*` link; corrected to a clean rename).
2. `tools/dk make split` (the WHOLE split, not only `dk64.global.us.yaml`: the namer's
   global-only re-split left overlay asm calling the old names, and `minecart.elf` failed
   to link), then `touch src/*/*.c` (renamed global functions are referenced
   from overlay GLOBAL_ASM; their objects are not rebuilt and fail to link with the old
   name otherwise), `tools/dk make` OK; `tools/dk make expected`. If agents are still
   running, the split deletes the asm of every function matched since their base commits:
   run `tools/restore_split_asm.sh <oldest running base> dk64.global.us.yaml` right after
   it (the `C0EE0`–`CBEA0` namer ran mid-unit; restoring kept the late agent working).
3. ROADMAP: one bullet per segment (files, data/rodata offsets, N of T matched per file,
   named groups, near misses, unattempted large functions; parked NON_MATCHING functions
   are listed as near-misses and still count unmatched). Check every name you cite
   exists in the symbol file. Refresh the README progress table:
   `tools/dk python3 tools/progress.py --readme`.
4. Commit `<A>/<b>: name N functions; ROADMAP + README: overlay unit status`.
5. ok-fine (you, not agents): update `architecture/overlay-c-units` (or the subsystem
   concept) and append new quirks to `notes/ido-matching-quirks`; sources at
   `git rev-parse HEAD`; `verify_concept`. Agents editing ok-fine in parallel broke
   footnote source ids once; keep them read-only.

## 5. Improve this skill (mandatory, every run)

Before the final yield:
1. Edit this file and `brief.md` with what this run taught you about the *procedure*:
   a step that failed, a brief instruction agents misread, a better partition size or
   stop threshold, a new tool flag. Fix or delete stale advice rather than appending
   contradictions. IDO quirks go to ok-fine, not here.
2. Append one row to the Run log (keep the last ~10 rows).
3. If a manual step repeated across rounds, turn it into a `tools/` script and replace
   the prose here with the command.
4. Commit `decomp-unit skill: <what changed>` together with or right after the unit's
   last commit.

## Known pitfalls

- The persistent shell keeps `set -e` between calls; use it only inside `sh -c`.
- Agents hit budget limits after ~20 min; "unattempted" functions mean the list was too
  long, not that they are hard. Shorter lists, near-misses first.
- An agent that reverts its function to GLOBAL_ASM often leaves its declarations; the
  merge tool prunes unused ones, DIRECT files need a manual `git diff` look.
- Probe/test files belong in `.scratch/` (gitignored). Older probes in the repo root
  (`test_*.c`, `t.s`, `tl.c`) are tracked; ask the user before removing them.
- Agents asked to change an existing `void f(void)` prototype to `void f();` (needed when a
  caller passes its own argument through in `$a0`). The brief allows it as long as every
  C caller still matches; check that in the merged file.
- `tools/dk` runs each call in a fresh container: `/tmp` files from one call are gone in the
  next, so objdump-and-diff must be one `tools/dk sh -c '...'`.
- A merged file whose last line was `#pragma GLOBAL_ASM(...)` directly after a function's
  closing `}` built without that function under `make` (link error `undefined reference to
  func_80664044` from another file) although the agent's identical copy passed `fdiff.sh`;
  a blank line before the pragma and a trailing newline fixed it. The brief now requires
  the blank line; check the file tail when a merge is followed by an undefined reference.
- `write agent://all` also wakes every idle (finished) agent, which then answers and may act:
  message running agents one by one instead.
- An aborted dispatch (user interrupt or machine crash) leaves each agent's `.scratch/<Name>/`
  private copy behind with partial edits. First run `tools/fdiff.sh` on every surviving copy:
  merge the ones that pass (`--base <its commit>`; check the stage notes of anything it
  parked in its saved draft), move the others to `.scratch/<Name>.old/`, and relaunch fresh
  copies from HEAD telling the agent to harvest its per-function C from the `.old` copy
  (a crashed copy was mid-edit: one had redeclaration errors, one was 16 bytes too big;
  harvesting gave 19 matches in 8 minutes). Agents that had no copy yet restart as usual.
  Check `git status` for unrelated uncommitted work (a parallel session's `55B20.c`
  match appeared during this unit): stage only the unit's files, never `git add -A`.
- `make split` while agents run deletes `asm/<seg>/nonmatchings/<file>/<FUNC>.s` of every
  function matched since the agents' base commit, so their copies (still `GLOBAL_ASM` for
  those) stop compiling and agents rebuild them from the current `src` (losing the base).
  The brief forbids it for agents, but in the `ACDC0` unit 89 `.s` files vanished at once,
  minutes before a parallel user session in the same tree committed a `7130` match (most
  likely its `make split`). Recover with
  `tools/restore_split_asm.sh <split commit> dk64.global.us.yaml` (re-splits that commit in a
  temporary worktree and copies back every missing `.s`, recreating fully matched files'
  directories; never overwrites), then message the running agents not to re-copy. A copy
  rebuilt from a later `src` merges with
  `--base` = the commit whose file differs least from it (`git show <c>:<file> | diff - copy`).
- `include/` is live, not part of any private copy: a unify agent that extends
  `include/actor.h` with an `extern` for a global breaks every running copy that declares that
  global with its own type. After such a header change, message each running agent on an
  affected file (one by one) with the new type names and tell it to drop its local externs.
- Per-file actor views: every agent on a fresh behaviour file declared its own
  `extern <Agent>Actor *D_807FBB40;`, so `B2CE0` needed three unify passes. Seeding the stub
  top block before round 1 (section 2) and requiring agent-prefixed view macros removed the
  unify step entirely in the `BA790`–`BDEE0` unit.
- A parked definition with a prototype rejects parked callers passing extra args (cfe:
  argument count). Write the parked definition K&R-style (`void f(a, b) T *a; s32 b; {`):
  same code for int/pointer params, and the file's `void f();` declaration then accepts both.
- An agent whose last message answers a late async-job notice ("the permuter finished,
  earlier report stands") hides its real report: read `history://<id>` and take the last
  `## 1.` section.
- Declarations inside a parked `#ifdef NON_MATCHING` block are invisible to the matching
  build: matched code below it that relies on them silently gets K&R promotion (f32 args
  passed as doubles). After every merge that adds a parked block also compile the
  `NON_MATCHING` side (`tools/fdiff.sh --non-matching src/<seg>/<f>.c src/<seg>/<f>.c`):
  this unit hit 7 redeclaration clashes between parked blocks and later matched code
  (fix: one declaration outside the blocks, casts at parked call sites). A stray prototype
  of function X inside another function's parked block also makes `permute.py`/`uopt_trace.sh`
  treat X as parked.
- fdiff does not resolve symbols: a misspelled extern (`D_807F50398`) passed fdiff and broke
  the link; the gate catches it, and the brief tells agents to grep added externs in `asm/`.
- Hidden empty functions: splat merges an unsymbolised `jr $ra; nop` (8 bytes, not a branch
  target) into the preceding function's `.s`; the matching C needs `void func_ADDR(void) {}`
  after it. List them before round 1 (two `jr $ra` lines two instructions apart in one
  `.s`, second not a `.L` target) and put them in the brief.
- Two agents' functions can be individually matching yet clash in one TU (caller declared
  `void f();` K&R-style, callee defined `void f(s32, f32)`: cfe rejects the pair). Merge,
  revert one side to its `GLOBAL_ASM` line, save its draft with the clash in the note, and
  give both functions to one next-round agent (`seqRouteChannelVolume`: the fix was an
  ANSI caller `(s32, f32)`).
- A same-global clash between merged drafts (`extern s8 D_x;` vs `extern u8 D_x;`, or two
  struct types for one pointer) is fixed inline: keep the wider struct (the one indexed
  with the right stride), delete the other declaration, gate.
- Park under `NON_MATCHING` only stage 4+ drafts (same blocks and saved registers); a
  stage-3 draft of a 3,000-insn function stays in `drafts/` only: its equivalence is not
  reviewable. Such drafts can still match: `func_806057F8` went from stage 3 to ROM match
  by rewriting m2c temps as direct array accesses and fixing diffs top-down (ok-fine
  `notes/ido-uopt-statics-and-live-ranges`).
- Agents passed their whole private copy to `drafts.py save`, storing 25 whole-file
  "drafts"; `save` now refuses files with `GLOBAL_ASM` lines and the brief says to save a
  `<FUNC>_best.c` holding only the function.
- `merge_drafts.py merge` builds the merged file's object via `objdiff.sh`; once that object
  came out without the file's GLOBAL_ASM functions (merge printed `FAILED: Relocations
  mismatch`, `make` then reused it and failed to link with undefined references to every
  asm function of the file). `touch src/<seg>/<file>.c` and rebuild before reading anything
  into it. `merge` starts from the current `src` on purpose so uncommitted merges and inline
  fixes survive, and `merge src/<seg>/<file>.c` with no copies re-prunes and re-checks after
  a manual conflict fix: never re-merge the same copy a second time, and never `git checkout`
  the file to retry. To retry a failed merge, restore the pre-merge state you verified
  (a `cp` you made before merging, or HEAD only when `git diff` shows that file has no
  uncommitted work).
- A one-agent-per-chunk split of one file (four agents on `63EC0`) produced four type sets
  for the same globals, and one agent still put its block at the top of the file: two unify
  passes. Once unified, name the unified types in every later task's `context` (agents then
  reused them with no further clash).
- Permuter output is a search hint, not verified code: `tools/permute.py` mutations are
  NOT semantics-preserving (moves statements, randomises types, deletes if statements) and
  its score checks disassembly only (stack diffs with `--stack-diffs`, no relocations or
  data). Never paste permuter output unreviewed; rewrite the idea into readable C that keeps
  the asm's behaviour, then verify through fdiff/objdiff and full ROM `tools/dk make`. Several
  agents share the CPU: always run the permuter with an explicit small thread count (`-j 2`)
  and a `--seconds` limit to avoid starving siblings.

## Run log

|Date|Unit|Rounds × agents|Matched per round|Result|
|---|---|---|---|---|
|2026-10-22|global actor collision/matrices/projectiles (70FD0 + 936B0)|split inline; rolling rounds (28 matching agents + 1 unify)|47 / 32 / 10 / 2|70FD0 52/79, 936B0 39/54, 82 named; exact git show base for rolling copies; cross-agent pattern broadcast (if (reg++ == 2) delay slot); +23,640 bytes in global|
|2026-10-23|global collision state / BST / asset tables (68960, 68AA0, 68EA0, 699B0 → 699B0 + 69E60 + 6AD90 hidden TUs)|split inline; per-agent rolling merges, 25 matching agents (6 / 5 / 6 / 5 / 3, incl. 4 one-function large agents) + namer + 1 tool agent|61 / 14 / 9 / 2|86/117 (68960 1/1, 68AA0 2/3, 68EA0 5/8, 699B0 2/2, 69E60 14/15, 6AD90 62/88), 69 named, +14,124 bytes; hidden TUs found from rodata end padding only after round 2 → `rodata_owners.py` pad flag; 2 matches by pasting "reloc-only" drafts and gating on the ROM; `drafts.py save` rejects whole-file copies (25 such drafts cut down); namer's `#pragma weak` aliases replaced by a clean rename; large agents again 0 matches (best 1–20 insns off)|
|2026-10-23|global render caches / effect nodes / water / target table / trigger zones (61AA0, 63810, 63EC0, 67890, 684C0)|split inline (no hidden TU); rolling per-agent merges, 20 matching agents (round 1: 6; then 14 rolling, incl. 4 one-function large agents) + 1 unify (2 passes) + namer|54 / 14 (rolling; last 9 agents 0)|68/89 (61AA0 15/22, 63810 1/3, 63EC0 44/53, 67890 3/5, 684C0 5/6), 68 named, +12,008 bytes; a focused 6-near-miss list after the unify matched 6/6; large agents 0 again; red commit from a `grep && commit` chain and a stale merge object → gate as its own step, `touch` before `make`|
|2026-10-23|global audio manager / fog / hash table / lights (6710 → 6710 + 7130 hidden TU, 5DE10, 5E020, 5E2F0)|split inline (data-pad hidden TU, f64 pair fix); round 1 aborted by user and relaunched on the same copies; rolling per-agent merges, 20 matching agents (6 / then 14 rolling, incl. 4 one-function large agents) + namer; clashes unified inline|48 / 18 (rolling; last 7 agents 1)|68/83 (6710 7/9, 7130 32/42, 5DE10 4/4, 5E020 8/8, 5E2F0 17/20), 67 named; 2 functions (`func_8060956C`, `func_80609B80`) were left out of every task list until a reviewer caught it, both matched at once → before round 1, check that the task lists cover every function in the files; 12 parked NON_MATCHING; large agents 0 again (best: 1179-insn `func_8065A884` stage 4); cross-agent prototype clash reverted then fixed next round; namer's global-only re-split broke overlay links → whole `make split`|
|2026-10-23|global model slots / map chunks / projectile behaviours (54150, 55B20, 9BF30, 9CE20)|split inline (no hidden TU); rolling per-agent merges, 28 matching agents (9 round-1 incl. 6 on one fresh `55B20`, 5 one-function large, 14 rounds 2–4) + 1 unify + namer|49 / 14 / 4 / 0|67/117 (54150 16/28, 55B20 45/80, 9BF30 2/4, 9CE20 4/5), 67 named, +13,032 bytes, 37 parked; type clash on almost every `55B20` merge (unified inline, struct names then passed in later contexts); `merge_drafts.py` pruned live declarations kept only inside parked `#ifdef` blocks → fixed; `objdiff.py` asm-differ `-n`; round-1 agents quit at 11–13 min → "whole budget" line in every context; one "reloc-only" paste failed the ROM (real scheduling diff), two later ones matched; large agents 0 matches again (3 parked at stage 4–5)|
|2026-10-24|global text markers / round banner / attached actors / effect sprites (9DD70, A2F10, A6280, A7710, A8400 → A8400 + AA960 hidden TU)|split inline (data-pad hidden TU, found before round 1); 9 round-1 agents, then rolling; machine crash killed 14 running agents mid-unit → salvaged 4 passing copies, relaunched the rest; ~35 matching agents total (incl. 10 one-function large) + namer|74 / 15 / 5 (+5 salvaged) / 0|94/127 incl. one hidden empty function (9DD70 27/37, A2F10 20/25, A6280 4/8, A7710 4/7, A8400 5/13, AA960 33/36), 52 named, +18,832 bytes, 18 parked; unsymbolised 8-byte empty functions inside splat `.s` files → listed in the brief; an agent's `make split` mid-run deleted matched functions' asm under 15 agents → restored from a worktree split, split ban in the brief; parked-block declarations clashed with matched code 7 times → `--non-matching` compile after each merge; misspelled extern passed fdiff → grep externs; large agents 0 matches again (8 parked at stage 4–6, best: 1-insn `func_8069E088`); a parallel session's uncommitted `55B20` work in the tree → stage only unit files|
|2026-10-24|global HUD text screens / enemy behaviours (ACDC0, B1F60, B2CE0, B5EC0, B6C50, B7490)|split inline (no hidden TU; leading unreferenced strings stay rodata GLOBAL_ASM); 6 round-1 agents, then rolling: 10 one-function large agents, 7 near-miss agents (rounds 2–4), 5 unify passes (B7490, B1F60, B2CE0 ×3, ACDC0) + namer|55 round 1 (incl. 3 reloc-only pastes) / large 6 of 10 / near-miss 7|69/79 incl. the empty stub (ACDC0 15/21, B1F60 6/7, B2CE0 13/13, B5EC0 11/11, B6C50 2/2, B7490 22/25), 23 named, +35,320 bytes, 9 parked + 1 draft; first unit where large agents matched (430–650-insn enemy updates, tricks forwarded between large agents); unify of `D_807FDC90`–`9C` into `include/actor.h` broke running copies (live header) → message agents; per-agent `D_807FBB40` views forced 3 B2CE0 unifies → brief bans redeclaring globals; 89 `.s` deleted mid-unit (parallel session split) → `tools/restore_split_asm.sh`; an agent's late async-notice reply hid its report → read `history://`|
|2026-10-24|global enemy behaviours / cursor actor / emitters (BA790, BB300, BC3B0, BD820, BDEE0)|split inline (no hidden TU, no empty functions); stubs seeded with the hot current-actor externs before round 1; 6 round-1 agents (incl. 1 large), then rolling: 4 one-function large agents, 6 one-function near-miss agents, no unify agent + namer|35 round 1 (incl. 2 reloc-only pastes, 1 large) / large 1 more of 4 / near-miss 5 of 6|42/42 (BA790 3/3, BB300 7/7, BC3B0 10/10, BD820 4/4, BDEE0 18/18), 12 named, +26,404 bytes, 0 parked; merges failed only on callee prototype clashes (fixed inline); fdiff/objdiff TEXT OK passed two swapped `D_` externs in a comparison → ROM caught it, `objdiff.py` now compares `D_` label addresses; a merged `u8` prototype added an `andi` to another agent's function → `u8 sel` local; near-miss tricks: non-void callee returns for v0/v1 swaps, `adjsave` reading in `uopt_trace -l 5`|
|2026-10-25|global camera (201B0), one large function `func_80622B24` (1941 insns)|split inline; single-agent session with uopt `-l 6` piece scripts and 4 long permuter runs|0|0/103 matched; `func_80622B24` parked NON_MATCHING (1945 insns, `u8` type `ucvt` piece colored `$t0`); draft with two post-switch goto labels reaches 1941 insns and an identical opcode stream but diverges in ugen scratch numbering. Brute-forcing control-flow shapes against `-l 6` piece priorities found the spill condition in minutes where the permuter never did. `make NON_MATCHING=1` already fails at HEAD: the global segment's compressed size exceeds 0xBAA80|
|2026-10-25|global camera (201B0), `func_80622B24` resumed from the 1941-insn draft|single-agent session; no permuter; `cc -S` ugen listings + an LRU simulator of ugen scratch allocation|1|1/103 matched. Diffs that are pure scratch-register numbering come from instructions ugen emits and as1 deletes (home-slot reloads, sign-extension of an `s32`-declared callee result): compare `cc -S` output, not the final asm. Three C-level facts fixed it in 4 compiles: `s16` callee return type, a `f64` local in a frame gap (`-l 6` showed the `f32` version colored `$f12`), `*arg1 + call*dist` operand order. The two goto labels stayed (every single-label or label-free shape re-colors `type`)|
|2026-10-25|global enemy behaviours / particle node rings / spotlight / matrix sprites (C0EE0, C1E70, C2A90 → C2A90 + C4620 hidden TU, C8C10, CB230, CBEA0)|split inline (rodata-pad hidden TU; 26 hidden empty functions written into the seeded stub); stubs seeded; 6 round-1 agents, then rolling: 7 one-function large agents (smallest first), 8 near-miss agents, 3 second-pass near-miss agents + namer (mid-unit, split + `restore_split_asm.sh`); no unify agent|50 round 1 (incl. 1 reloc-only paste) / large 5 of 7 / near-miss 4 of 8 / second pass 1 of 3|59/63 (C0EE0 3/4, C1E70 3/4, C2A90 7/7, C4620 22/23, C8C10 17/17, CB230 5/5, CBEA0 2/3), 6 functions + 2 actor-core globals named, ~+36,400 bytes, 4 parked; merges failed only on duplicate prototypes and on declarations inside parked blocks (caught by `--non-matching` after every merge); older copies printed whole-file FAILED from REL addends of since-merged functions (brief note added); a parallel session committed and re-split mid-unit without harm; an agent's broad `pkill` killed siblings' permuters (brief rule)|
