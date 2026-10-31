# Matching-agent brief template

Fill `<...>` and write it to `local://brief.md`; each `task` `context` is then "Read
`local://brief.md` FIRST and follow it exactly" plus that file's facts. One `tasks[]` item
per agent with its target file, mode, and function list (near-misses first, each with its
last known diff note and stage reached).

````
# Goal
Matching decompilation of Donkey Kong 64 (USA), repo <repo root> (ALWAYS use absolute paths
under it for read/edit/write). Read AGENTS.md first:
IDO 5.3 `-O2 -mips2`, run every build tool inside the container via `tools/dk <cmd>`,
write C from the local asm only (do not reuse code from the community DK64 decomp),
never commit, never edit ok-fine (report findings instead). Read the ok-fine quirks
by writing JSON to `xd://mcp__ok_fine_read_concept`:
`{"project":"dk64","id":"notes/ido-matching-quirks"}` and
`{"project":"dk64","id":"runbooks/decompile-function"}`.
Read the matched functions already in your file and REUSE its declarations and structs.
<file-specific facts: shared header (e.g. include/actor.h), key globals, names so far>
<IDO tricks the previous rounds of this unit found (from their reports, section 3)>
<hidden empty functions (8-byte `jr $ra; nop` merged into a preceding `.s`): addresses and
their owners; the C needs `void func_ADDR(void) {}` right after the owner>

Register-allocation toolbox (most later-round near misses are regalloc only): access a
global struct pointer directly vs caching it in a local; local declaration order; split or
merge temporaries, s32 vs narrow temps, scope temps per switch case; commutative operand
order; sequential vs chained assignment; exact prototypes (void vs s32 return, f32 vs
unprototyped, a callback symbol declared as a function rather than `&D_...`); nested call
argument vs sequential assignment; ternary vs if/else; `do {} while` vs `while`; signedness
of compares and selectors (constant webs are typed). A `lbu a0; move v1,a0` copy with
swapped registers: compare `adjsave` in `uopt_trace.sh -l 5`. Before reporting a match, diff
`objdump -dr` relocations against expected (swapped externs look identical in the text).

# Concurrency rules (several agents run at once)
- NEVER run `tools/dk make` (any target), `make split`, `python3 -m splat`, `make expected`,
  `make clean` or `./diff.sh`: they change shared outputs for everyone (`make split` deletes
  the asm of every function matched since your base). If a `.s` your copy references is
  missing, report it and work on other functions; never rebuild your copy from `src`. A
  `tools/dk` call pausing on `dk: waiting for ... lock` while the gate runs is normal: wait.
- Never `pkill`/`kill` by pattern (`pkill -f "permute.py run"` killed every sibling's
  permuter): stop only a PID you started.
- Put every scratch/probe file (`cc -S` output, objdump/`.s` dumps) under `.scratch/<YourName>/`, never the repo root.
- PRIVATE COPY mode: create your copy ONCE from the exact base commit in your task
  (`git show <commit>:src/<seg>/<file>.c > .scratch/<YourName>/<file>.c`); never re-copy it or
  `cp` it over `src`; after any multi-line replace, `diff` it against the base (block replaces
  ate other functions). Check: `tools/fdiff.sh .scratch/<YourName>/<file>.c src/<seg>/<file>.c [FUNC]`.
- Keep a blank line before every `#pragma GLOBAL_ASM` line, including the last one in
  the file. A parked function's `#ifdef NON_MATCHING` block must wrap only that function
  and the declarations nothing else uses; declarations matched code needs stay outside it
  (inside the block they vanish from the matching build: an f32 callee then gets
  double-promoted args), and never redeclare in it a global or callee the file declares
  elsewhere (another type breaks the NON_MATCHING compile). Parked C calling a function now
  defined in the file with another prototype casts at the call site; check with
  `tools/fdiff.sh --non-matching`.
- Before reporting, grep every extern/symbol you added in `asm/`: fdiff does not catch a
  misspelled symbol, only the link does.
- If the text is identical but fdiff prints `FAILED: Relocations mismatch` only because the
  expected asm used a raw address constant or a named label where your C uses the symbol
  (or `.rodata+off`), keep the function as GLOBAL_ASM, save the draft, and report it as
  "text-identical, reloc only": the orchestrator checks it against the ROM hash. Only call
  it that after diffing the objdump instruction streams: the same message can hide a real
  scheduling difference.
- If code matches but `.rodata` differs only by zero padding between functions, report it:
  that is a hidden translation-unit boundary, not something to fix in C.
- Key compiler patterns: when you discover a pattern that resolves a common near-miss
  (e.g. post-increment equality `if (reg++ == N)` placing stores in delay slots, K&R spills,
  unrolled loop idioms), report it clearly or message siblings via `write agent://<id>`.
- DIRECT mode (you are the only agent on the file): edit it in place, check with
  `tools/objdiff.sh src/<seg>/<file>.c [FUNC]`.
- Both print `OK` (exit 0) or `TEXT OK` (exit 3) when code matches, else FAILED plus an
  asm-differ diff of FUNC. Exact diff, in ONE call (each `tools/dk` call gets its own fresh
  /tmp, which does not survive): `tools/dk sh -c 'mips-linux-gnu-objdump -d
  --no-show-raw-insn <your .o> > /tmp/b; mips-linux-gnu-objdump -d --no-show-raw-insn
  expected/build/src/<seg>/<file>.o > /tmp/e; diff /tmp/e /tmp/b'`
  (private objects: `build/.scratch/.scratch_<YourName>_<file>.c.o`; ignore pure `%lo`
  addend differences like `0(at)` vs `532(at)`). A function whose size differs shifts
  everything after it: get the size right first.
  A whole-file FAILED in functions you never touched is normal for a copy older than the
  orchestrator's latest merges: a function still GLOBAL_ASM in your copy but C in the
  expected object differs in REL addends. Judge your own function's diff and say so.
- NEVER edit shared headers in `include/` (another agent may own them this round); use a
  local struct/cast prefixed with your agent name. Headers are live, not copied: if the
  orchestrator messages you about a header change, drop your conflicting local externs.
- NEVER redeclare a global the file (or `include/`) already declares, with any type: an
  agent-local `extern MyActor *D_807FBB40;` breaks the merge. Cast instead:
  `#define MyA ((MyActorView *)D_807FBB40)` with a local view struct holding only the
  fields you need. The same holds for callees: if the file already declares one, use that
  declaration; when your code needs another parameter type, adapt your locals or cast the
  data (`u8 sel` instead of `s32 sel`), and report it.
- Merge hygiene: change only your functions' lines. New externs/prototypes/structs go
  IMMEDIATELY ABOVE your first function that uses them, never in the top block or another
  agent's range. Never change an existing declaration, with one exception: a prototype
  may become unprototyped (`void f(void);` → `void f();`) if every C caller in the file
  still matches; say so in your report. Otherwise adapt your code with casts on data, never
  a function-pointer cast at a call site (it emits `jalr` and grows the frame: report the
  prototype the orchestrator must change instead). If your function calls or is called by
  a function matched in another agent's range, its declaration must agree with that
  definition (cfe rejects a K&R `void f();` next to a prototyped `void f(s32, f32)`
  definition): read the callee/caller first. Prefix new type names with your agent name,
  also types copied from a stored draft (two agents reusing one draft's `F9N6_` clashed).
  When you revert a function to GLOBAL_ASM, delete the declarations you added for it.
  Don't reorder or reformat; never search-and-replace across the file (it rewrote a parked function).
  Never move an existing block (typedefs/externs) even if your function sits above it:
  declare a forward `struct Tag *` or a new agent-prefixed view right above your function
  (one moved block turned a merge into a hand-resolved 3-way conflict).
  Other agents' merges land in `src` while you work: before declaring a callee or global
  your file may already have, grep the current file too (`grep -n <name> src/<seg>/<file>.c`)
  and reuse that declaration's exact type.
- Relaunched agent whose private copy already exists: fdiff it and continue; never re-create it.
- Skip formatters and linters. NEVER edit `tools/`, `Makefile` or the splat configs.

# Large functions and near-misses
- Follow AGENTS.md "Decompiling a function" step 4 (stage order, `tools/uopt_trace.sh`,
  permuter search-hint rule, NON_MATCHING parking) with these exceptions: no ROM build (your
  gates are `fdiff.sh` OK/TEXT OK and `--non-matching`), `uopt_trace.sh` before guessing at
  any register question; every `tools/dk` call under ~10 min (permuter `-j 2 --seconds 600`,
  deadsweep `--rounds 1` per call, rerun on the improved body: a 40-min sweep starved the gate).
  At stage 4+ run `tools/dk python3 tools/deadsweep.py sweep <copy> <src> FUNC --extra <each
  local>` first. When it and the permuter stall, write your own harness (it matched most parks
  of the 2026-10-31 unit): a grid over 1-5 statements' spellings (casts, chained/split
  assignments, order) or a random hill-climb accepting ties, scored per region with branch
  targets blanked, the `.o` deleted before each probe and one scratch file per parallel job.
  Reject any dead use (also from permuter) of a local unassigned on that path.
- Any construct you keep only to steer codegen (deadsweep statements, `volatile`, `x ^ 0`,
  `do {} while (0)`) ends in a trailing `// FAKE: <what it steers>` comment (AGENTS.md
  Conventions); keep deadsweep's own tag. Shared globals use the type most of `src/` gives
  them (`extern Actor *D_807FBB40;`), never `void *` plus a local view.
- Park only stage 4+ (same callee-saved set AND frame size, remaining diff only regalloc/
  scheduling/stack layout) in your copy as below; stage 2–3 stays on its GLOBAL_ASM line:

```c
#ifdef NON_MATCHING
<C>
#else

#pragma GLOBAL_ASM("asm/...")
#endif
```

  Notice the required blank line before `#pragma GLOBAL_ASM`. Check the parked C compiles with
  `tools/fdiff.sh --non-matching <copy> <src> [FUNC]` and the plain `tools/fdiff.sh` still gives
  OK/TEXT OK. Parks count as unmatched; not genuinely equivalent: keep the draft in `drafts/`.

# Method
Your budget is finite: near-misses first, then never-attempted functions smallest to largest;
after a serious effort on one, move on and come back if budget remains. Before writing C,
read the matched C that `tools/dk python3 tools/similar.py -s <segment> <FUNC>` lists, then
take starter C from `tools/dk python3 tools/m2c.py -s <segment> <FUNC>`. First check every
callee's return type and WIDTH, parameter widths and arity against its CURRENT definition in
`src/` (`void` vs `s32`, `u8`/`s16` declared `s32`, phantom params: each flips the caller's
v0/v1, ring or `andi`s; an unused-result `s32` callee takes one ring temp). Fdiff each once.
When the permuter (or anything else) reaches score 0, put the readable C into your copy in place
of the function's `GLOBAL_ASM` line and confirm with fdiff: a draft-only match is not merged.
Stop on outcome, not time: report as soon as every assigned function is matched, or is back
on its exact `GLOBAL_ASM` line with a saved draft whose note names the stage and the exact
remaining diff, and you have no untried idea left (a few attempts in a row that no longer
shrink the diff). Never idle to fill time. Save the draft after every improving attempt.
Keep context small: diff one function's objdump at a time, pipe long output through `head`.
A function reported at stage 1-3 with untried next steps is unfinished work; a frame-size
mismatch is stage 3 at most. A function's own rodata constants (`dlabel D_8075xxxx` in its
`.s`) are C literals of the right type (`0.35f`, `1.07`), one per rodata entry in source
order, never `extern f64 D_8075...` (identical code, but `.rodata` fails).
Report every assigned function, matched or not. One that won't match gets its exact original
`#pragma GLOBAL_ASM(...)` line back (or a NON_MATCHING park, see above) and EVERY unmatched
function gets a saved draft (even "no stored draft" ones):
`python3 tools/drafts.py save <seg> <FUNC> .scratch/<YourName>/<FUNC>_best.c --note "<closest diff, what you tried>"`,
where `<FUNC>_best.c` holds ONLY that function and its declarations (`save` rejects
`#pragma GLOBAL_ASM` lines). Start from `python3 tools/drafts.py show <seg> <FUNC>` if one
exists. Your final file MUST give OK or TEXT OK: never leave non-matching C in it.

# Report (final message)
(Write it in full as your LAST message: if an async job notice arrives after it, repeat the
whole report rather than replying "earlier report stands".)
1. Newly matched functions; remaining GLOBAL_ASM (or parked NON_MATCHING) with stage
   reached (stages 1–6), a one-line closest-diff note each (and confirm you saved its draft
   or parked it under NON_MATCHING).
2. Names ONLY for behaviour you confirmed: `func_X -> <prefix>CamelCase` + one-line reason.
3. New IDO quirks not already in the ok-fine note (one bullet each).
4. Final file path.
````
