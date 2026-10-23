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
files named at the end of ROADMAP's section 9 bullets, e.g. `9BF30`, `6710`, `63EC0`)
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
Add `#include "actor.h"` (global) under `#include "common.h"` in every new stub before
round 1: otherwise every round-1 copy adds it and each merge after the first conflicts on
that line.

Gate: `tools/dk make` OK, then `tools/dk make expected`. Commit
`Overlays: split <a> (<files>) and <b> (<files>) as C units (GLOBAL_ASM baseline)`.

## 3. Matching rounds (up to 6 agents per round)

1. Partition by instruction count: round 1 ~600–1,300 per agent, ≤20 functions,
   contiguous by address; functions over ~400 insns held back for later rounds, each
   on its own agent (one-function agents on 400–815-insn functions got to 1–4 insns or one
   register off, never a match, in two units: dispatch them only to fill idle slots).
   Later rounds ≤6 functions per agent, near-misses
   first. Never a function in two agents' lists. Every agent works in PRIVATE COPY mode,
   even alone on a file, so `src/` only changes by your merges and the full build can gate
   each commit while agents run.
2. For every file, BEFORE dispatch: `python3 tools/merge_drafts.py snapshot src/<seg>/<file>.c`.
3. Write the filled [brief.md](brief.md) once to `local://brief.md` and pass the `context`
   "Read `local://brief.md` FIRST and follow it exactly", plus per-file facts and the
   previous rounds' tricks for that file; each `tasks[]` item lists its functions
   with the last known diff note; agents start from the stored draft
   (`tools/drafts.py show SEG FUNC`; drafts are keyed by segment because overlays share names like `func_80024000`), not from m2c.
   Agents finish after 15–25 min whatever the list length; re-prompting an idle agent to
   "continue" returned the same report with no new matches (boss round 1, 5 tries):
   dispatch the next round instead.
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
   duplicate declarations (keeping the first) and unused ones the drafts added; prints
   clashing declarations on compile errors; exit 2 on conflicts leaves `src` untouched).
   Drafts copied before the latest snapshot (an agent still running from an older round):
   `merge --base <commit the copy started from> src/... .scratch/<A>/...`, else the merge
   reverts everything committed since.
   Round 1 on a fresh file always yields per-agent types (`ActAActor`, `BehBActor`) that
   clash: dispatch one unify fix-up agent per file right after round 1 (PRIVATE COPY, merged
   like a round; it extends the shared header in place, additively only), that
   creates/extends a shared header (`include/actor.h`) with one struct per object and moves
   all declarations to one top block. Two files sharing a header: serialize their unify
   agents (second extends the header additively), but start the first file's round 2 at
   once. A clash of one global between two drafts: unify inline.
   A file-local clash (types only one file uses): run the failing merge, copy the merged
   (non-compiling) `src` file to `.scratch/Unify<F>/<file>.c`, `git checkout` the src file,
   and give the unify agent that copy; its result replaces `src` directly (`cp`) if `src`
   has not changed since. If that file's agents are still running, start the clashing
   agent's next round FROM ITS OWN PRIVATE COPY (`cp .scratch/<A>/<file>.c .scratch/<B>/`)
   so it keeps its types, and merge it with `--base <commit its copy started from>`.
5. Merge single-agent copies the same way; revert declaration-only leftovers from
   zero-yield agents. Then persist drafts: `python3 tools/drafts.py collect` (imports any
   newer `.scratch/*/<FUNC>_best.c` an agent left instead of saving) and
   `python3 tools/drafts.py prune` (drops drafts of functions that now match); commit
   `drafts/` with the merge. `drafts/<seg>/<FUNC>.c` is the only place in-progress C
   survives a session; `.scratch/` is per-session and may be wiped.
6. Gate EVERY commit with the full build: `tools/dk make` must end with
   `build/dk64.us.z64: OK` (AGENTS.md: never commit a non-matching state). Per-file
   `tools/objdiff.sh` OK/TEXT OK is only a pre-check: TEXT OK hid a `.rodata` shift once (a C
   jump table dropped the 4-byte late_rodata pad before an asm function's floats, `7AF60`
   `func_8067680C`, committed and only caught later); `objdiff.py` now fails on `.rodata`
   byte diffs, but the ROM hash stays the gate. Commit `<Seg>: match N/T <file> functions`.
7. Stop rule: stop a file after a round that matched fewer than ~1 function per agent, or
   when only near-misses and 500+-insn functions remain. Record the closest diffs in ROADMAP.
8. An agent that reports "100% instruction match, objdiff fails only on relocations"
   (expected asm used a raw address such as `lui 0x8080; sb -0x6B52` where C uses
   `D_807F94AE`): paste its draft into `src` and let the ROM hash decide (`func_80668520`
   matched that way). An agent that matches code but not rodata padding has found a
   hidden TU (section 2).

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
2. `tools/dk make split`, then `touch src/*/*.c` (renamed global functions are referenced
   from overlay GLOBAL_ASM; their objects are not rebuilt and fail to link with the old
   name otherwise), `tools/dk make` OK; `tools/dk make expected`.
3. ROADMAP: one bullet per segment (files, data/rodata offsets, N of T matched per file,
   named groups, near misses, unattempted large functions). Check every name you cite
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
- Agents passed their whole private copy to `drafts.py save`, storing 25 whole-file
  "drafts"; `save` now refuses files with `GLOBAL_ASM` lines and the brief says to save a
  `<FUNC>_best.c` holding only the function.

## Run log

|Date|Unit|Rounds × agents|Matched per round|Result|
|---|---|---|---|---|
|2026-10-21|arcade (ovl08) + menu (ovl10)|split 2; match 6/6/6 (+1 type-unify fix-up)|81 / 31 / 7|arcade 62/98, menu 57/113, 84 named; tools added after this run|
|2026-10-22|boss (ovl07), last overlay|split inline (11 TUs, 9C60 = 3); match 6/6/6; 5 "continue" re-prompts|46 / 8 / 4|boss 58/79, 15 named; `tools/rodata_owners.py` added; best-draft handoff between rounds|
|2026-10-22|global actor core (7CA80 + 80150)|split inline; match 6 / 11 rolling (incl. 4 one-function large agents) / 4; +2 unify fix-ups|85 / 21 / 3|7CA80 62/73, 80150 47/64, 31 named; `include/actor.h`; merge_drafts keeps first duplicate, `--base REV`; large (600–1400 insn) agents: 0 matches, best 8–19 insns off|
|2026-10-22|global actor behaviour (79890, 7A510, 7AF60, 7BBD0, 89250; 77B90 reverted to asm)|split inline; rolling per-file rounds, 22 matching agents total (7 / 6 / 6 / 3) + 1 unify|50 / 21 / 6 / 1|79890 6/8, 7A510 8/13, 7AF60 27/29, 7BBD0 3/6, 89250 34/40, 35 named; one matched function reverted after the ROM check (C jump table lost late_rodata pad) → `objdiff.py` now fails on `.rodata` byte diffs; `rodata_owners.py` <1 s on global; shared brief via `local://brief.md`|
|2026-10-22|global actor lists / animation / render (8CA50, 8D3E0, 8F050, 8F4B0 → 8F4B0 + 90D80 hidden TU)|split inline; 6 round-1 agents, then 14 rolling (incl. 5 one-function large agents) + 1 unify|75 / 7 / 3|8CA50 18/19, 8D3E0 40/47, 8F050 5/7, 8F4B0 11/15, 90D80 11/17, 53 named; data-alignment rule for hidden TUs; file-local unify from a pre-merged copy; round-1 agents with 28 functions left 10 unattempted at ~13 min → smaller round-1 lists; naming agent edited tools/ (reverted)|
|2026-10-22|global actor collision/matrices/projectiles (70FD0 + 936B0)|split inline; rolling rounds (28 matching agents + 1 unify)|47 / 32 / 10 / 2|70FD0 52/79, 936B0 39/54, 82 named; exact git show base for rolling copies; cross-agent pattern broadcast (if (reg++ == 2) delay slot); +23,640 bytes in global|
|2026-10-23|global collision state / BST / asset tables (68960, 68AA0, 68EA0, 699B0 → 699B0 + 69E60 + 6AD90 hidden TUs)|split inline; per-agent rolling merges, 25 matching agents (6 / 5 / 6 / 5 / 3, incl. 4 one-function large agents) + namer + 1 tool agent|61 / 14 / 9 / 2|86/117 (68960 1/1, 68AA0 2/3, 68EA0 5/8, 699B0 2/2, 69E60 14/15, 6AD90 62/88), 69 named, +14,124 bytes; hidden TUs found from rodata end padding only after round 2 → `rodata_owners.py` pad flag; 2 matches by pasting "reloc-only" drafts and gating on the ROM; `drafts.py save` rejects whole-file copies (25 such drafts cut down); namer's `#pragma weak` aliases replaced by a clean rename; large agents again 0 matches (best 1–20 insns off)|
