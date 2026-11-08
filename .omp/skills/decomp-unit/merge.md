# Merge, gate, commit (SKILL.md §3)

Read before the first merge of a unit and again whenever a merge fails.

## Merge + gate

```sh
python3 tools/drafts.py collect && git diff drafts/      # restore any draft collect replaced (also other overlays' same-named func_80024000)
tools/merge_gate.sh --commit "<Seg>: match N/T <file> functions" [--stage <path>]... .scratch/<A> <its base commit> src/<seg>/<f>.c ...
```

- It runs `merge_drafts.py merge --base` per file in this checkout, then builds in its own
  gate worktree (`.scratch/gate`, own dkd container): HEAD + exactly the given src files +
  `--stage` paths, `tools/dk make`, each file's `NON_MATCHING` side; only after `GATE_OK` it
  deletes the drafts of the files' newly matched functions and commits exactly the given src
  files, the drafts of their functions (`unit_check.py drafts`) and each `--stage` path (never
  other drafts or staged changes). Agents never wait for it, nor it for them; gates serialise
  on the gate tree's lease. This checkout's `build/` is not refreshed: `tools/dk make` at unit
  end. Read the output for `GATE_OK` / `COMMITTED`.
- `--stage` every file outside the given `src` files the merged build depends on (a header a
  unify agent extended, a symbol file, a splat config): the gate tree has only HEAD plus what
  you pass, so a missing one fails the gate instead of the later commit.
- The copy argument is a DIRECTORY holding `<f>.c`. An agent's HEAD-based file
  (`<f>_head.c`, built against current `src`) goes to `.scratch/<A>H/<f>.c` with its base,
  or, when `src` is unchanged since, `cp` it over `src` and gate `- - src/<seg>/<f>.c`.
- Track full and shape scores: retain structural gains despite a worse full score, but reject backend-scan gains from deleting required definitions. Count instructions separately from relocations; `deadsweep`'s combined `n` is not a code-length check.
- After a reduced-TU zero, confirm the C is UNPARKED and run whole-file `fdiff.sh`; normalized text may erase wrong branch targets, and reduced TUs omit later data definitions.
- `vanished` counts both park branches: after unparking, compare old/new object text symbols before treating a count drop as deletion.
- Never pipe a merge or gate into `tail`/`grep` and chain `&& git commit`: the pipe hides the
  exit status, and a conflict (src untouched) or a red build was committed that way twice.
  Without `--commit`, commit only after reading `GATE_OK`; `--stage` is parsed only after `--commit MSG`. A bare `merge_drafts.py merge`
  goes inside `sh -c '...; echo "exit $?"'` (the persistent shell's `set -e` otherwise
  aborts silently after merge already wrote `src`). Run gates with the bash tool and a long
  timeout, never from the eval kernel: its 30 s cell deadline kills the client mid-gate.
- `--base` is the commit the copy started from. A second pass in the SAME copy merges with
  the commit that merged its first pass; a copy rebuilt from a later `src` uses the commit
  whose file differs least from it (`git show <c>:<file> | diff - copy`). A wrong base
  reverts everything committed since or gives blank-line-only conflicts (take `src` for
  blank lines/pragmas, the copy for its new function). The blank line before a pragma
  matters at the file tail (`unit_check.py pragma-tail`); mid-file pragmas right after `}`
  build fine (dozens in the matching tree).
- Never run the gate on a file another agent (the namer) edits in place: merge rewrites
  `src` (pruning).
- The ROM hash is the final gate, not proof that C was unparked: check the active branch
  and its fdiff first. Per-file TEXT OK alone can hide a `.rodata` shift or swapped externs.
- A zero-yield copy is merged only for its parks: when one moved up a stage, replaced a
  non-equivalent park, or its declarations live only in the copy (drafts hold the function
  alone). Merge prunes unused declarations; a DIRECT-mode file needs a manual `git diff` look.
- An agent that made `void f(void);` unprototyped (`void f();`, allowed by the brief) must
  leave every C caller in the file matching: the ROM gate checks it.
- `drafts/` is the only place in-progress C survives a session; collect before every gate.
  `git diff drafts/` after collect: restore only a note that an OLDER `.scratch/*_best.c`
  replaced; a draft an agent saved with `drafts.py save` is newer, keep it.
- An agent asking for a shared prototype change (`s32` → `u8` param so a constant is not
  shared, `s16` → `s32` so a register arg is not re-extended): apply it in `src` yourself,
  `tools/objdiff.sh` the file, gate, then message every running agent on that file.
- A file created by a mid-unit TU split has no `expected/` object: `snapshot` it, gate with
  `touch` + `tools/dk make`, commit by hand, then `tools/dk make expected`.

## When a merge fails

- `merge` writes `src` even when the result does not compile (only textual conflicts leave
  it untouched). Never re-merge the same copy and never `git checkout` the file to retry:
  fix the printed clash in `src`, then `tools/merge_gate.sh - - src/<seg>/<f>.c` (merge with
  no copies: re-prunes, re-checks, gates). To restart a failed merge, restore the pre-merge
  state you verified (your own `cp`, or HEAD only when `git diff` shows no uncommitted work).
- `build/global.gz: ... exceed segment size` means some text differs (a bare unparked C
  function, or a non-match such as swapped `mul.s` operands in a "reloc-only" paste). Check
  the merged file for a function that lost its `#ifdef NON_MATCHING` block. Before restoring,
  `git diff` the file and `cp` it aside; then restore and take only real matches (`drafts.py paste`).
- A multi-file gate stops at the first failing file: the later files' copies were never
  merged. After fixing, re-gate those files WITH the copy and its base (`- -` merges nothing:
  jetpac 3060.c's two matches were silently dropped that way and found only via `left`).
- Declaration clashes (cfe "redeclaration", "prototype and non-prototype"):
  - keep the declaration that already matches in `src` (or the definition), delete the
    other, cast at the newer call sites; never change a prototype a matched caller relies on.
    If the kept prototype changes the other agent's code, adapt that function's local types
    (`u8 sel` instead of `s32 sel`);
  - one global with two struct types: keep the wider struct (indexed with the right stride),
    `typedef` the other name to it or delete it and adapt users; scalar vs array: keep the
    array; one agent's `extern void *G;` above another's `extern T *G;`: make the first
    `extern struct T *G;` and give `T`'s typedef that tag (2 clashes this way in one unit);
  - two callers with different prototypes for one cross-file callee: pick the one consistent
    with the callee's asm (an int `a3` is homed with `sw`, an f32 goes through `mtc1`); keep a
    needed extra argument via an unprototyped declaration (`void f();`);
  - K&R caller vs prototyped callee in one TU: revert one side to its `GLOBAL_ASM` line, save
    its draft with the clash in the note, give both to one next-round agent;
  - move a declaration above its first user when a pasted function needs it earlier;
  - an early prototype (another agent's range) disagreeing with a later definition (the
    most common clash: 7 in the 2C700 unit): give the prototype the definition's types;
    a typedef'd struct param needs a forward `struct Tag;` line before the prototype.
  Name every unified type in later tasks' `context` (and `local://findings.md`).
- Conflict with an empty `src` side and a copy side starting with a stale pragma: a sibling
  matched the function above the copy's new code. Take the copy side minus that pragma in
  `.scratch/merged/<f>.c`, `cp` it to `src`, gate `- -`.
- Per-agent types on a fresh unseeded file (`ActAActor`, `BehBActor`): one unify agent per file
  right after round 1 (PRIVATE COPY, merged like a round), building one struct per object in
  a shared header (additive only) and one top declaration block. Two files on one header:
  serialize their unify agents, start round 2 of the first at once. File-local clash: copy
  the merged (non-compiling) `src` to `.scratch/Unify<F>/`, `git checkout` the src file, give
  the agent that copy; `cp` its result into `src` if `src` has not changed since. A clashing
  agent still running keeps working from ITS OWN copy (`cp .scratch/<A>/<f>.c .scratch/<B>/`)
  and merges with `--base` its start commit.
- `include/` is live: a unify agent adding an `extern` there breaks running copies that
  declare that global; message each affected agent (one by one) with the new type names.
- A merge whose check prints `FAILED` although the agent's copy passed: the unified
  declarations changed another function's code; `objdump -dr` both objects and diff first.
- The merged object came out without the file's `GLOBAL_ASM` functions once (`FAILED:
  Relocations mismatch`, then link errors for every asm function): `touch` the file and
  rebuild before reading anything into it.
- Undefined reference to a function of a just-merged file:
  `python3 tools/unit_check.py pragma-tail src/<seg>/<f>.c` (a last pragma directly after `}`
  or a missing trailing newline dropped that function from the build).

## Parked NON_MATCHING blocks

- Declarations inside a parked block vanish from the matching build: matched code below
  then gets K&R promotion (f32 args passed as doubles). Keep one declaration outside the
  blocks and cast at parked call sites; the gate's `--non-matching` compile catches clashes.
  A function matched after a park that declares the same globals with other types fails only
  that compile: hoist the matched code's declarations above the park, delete the park's
  copies, cast inside it; hand this to the agent already working that park (B100 unit).
- A parked definition with a prototype rejects parked callers passing extra args: write it
  K&R-style (`void f(a, b) T *a; s32 b; {`) so the file's `void f();` accepts both. A park
  calling a matched ANSI callee with extra args (stale `a2`/`a3` in the asm): drop them.
- A stray prototype of X inside another function's parked block makes `permute.py` /
  `uopt_trace.sh` treat X as parked.
- Park stage-6 drafts yourself when an agent did not: paste into the parked form,
  `tools/fdiff.sh --non-matching src/... src/...`, `tools/objdiff.sh src/...`, gate.

## "Reloc-only" and paste candidates

Treat every "text-identical, reloc only" report or parked claim as a paste candidate:
`python3 tools/drafts.py paste <seg> FUNC` (replaces its pragma or park with the draft), then
`tools/merge_gate.sh - - src/<seg>/<f>.c` (prunes duplicated declarations) lets the ROM gate
decide. Usual harmless causes: raw address constants vs `D_` symbols, own late_rodata as
`.rodata+off`, jump-table relocations, `D_x+4` vs splat's `D_x4` label, a loop bound as
`D_x+0x80` vs splat's next label, a `%hi/%lo` pair for a plain constant (`.text content
mismatch` in fdiff although the ROM matches). On a failed
gate it was not reloc-only: `tools/dk make build/global.text.bin`, `cmp -l` against the last
good copy, objdump the function (found: a store two slots early, swapped delay-slot
constants, a view struct 4 bytes short, a spill slot 4 bytes off, an `extern f64` that must
be a literal, a segment that grew past its size). Fix or revert and correct the draft note.
A draft saved with its own head (`#include`, externs typed differently from the file's) pastes
clashing declarations: replace the function with the agent copy's body instead (104F0 revisit 9).
A text-identical draft needing declarations reconciled across the file goes to a short
integration agent, not hand-pasting. Code matching but rodata padding differing = hidden TU
([split.md](split.md)).
Before accepting dead-read codegen hints, prove every evaluated access is initialized in C
(including short-circuit paths), then smoke the input boundaries; a ROM match alone does not prove this.
