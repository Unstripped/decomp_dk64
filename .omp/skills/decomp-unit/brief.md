# Matching-agent brief template

Fill `<...>` into `local://brief.md`; each task says "Read `local://brief.md` FIRST and
follow it exactly", plus the file, mode and function list (near-misses first, with stage/diff).

````
# Goal
Matching decompilation of Donkey Kong 64 (USA), repo <repo root> (ALWAYS use absolute paths
under it for read/edit/write). Read AGENTS.md first:
IDO 5.3 `-O2 -mips2`, run every build tool inside the container via `tools/dk <cmd>`,
write C from the local asm only (do not reuse code from the community DK64 decomp),
never commit, never edit `knowledge/ido/` or ok-fine (report findings instead); follow
"# Knowledge lookups" below throughout.
Read the matched functions already in your file and REUSE its declarations and structs.
<file-specific facts: shared header (e.g. include/actor.h), key globals, names so far>
<knowledge IDs earlier rounds of this unit found useful (report section 3), new entries added this unit>
<hidden empty functions (8-byte `jr $ra; nop` merged into a preceding `.s`): addresses and
their owners; the C needs `void func_ADDR(void) {}` right after the owner>

# Knowledge lookups (mandatory, frequent)
`knowledge/ido/` holds ~560 IDO quirks and guides from every past unit; most problems you
meet are already solved there, and re-deriving a known rule wastes budget. Query it with
`python3 tools/quirks.py` (host-side, compact output) at least:
- before writing C for a function: `func <FUNC>` (what earlier attempts learned about it);
- at every stage change and whenever a diff stops shrinking: `search --symptom <tag> <words
  from the diff>` (`tags` lists symptoms with the diff each one means; regalloc-only near
  misses: `--symptom regalloc`);
- before any trick or tool route not in this brief, and before reporting a new quirk.
`get <ID>` prints an entry or guide section in full. Report the IDs you used (section 3).
A `lbu a0; move v1,a0` copy with swapped registers: compare `adjsave` in `uopt_trace.sh -l 5`.
Before reporting a match, diff `objdump -dr` relocations against expected (swapped externs
look identical in the text).

# Concurrency rules (several agents run at once)
- NEVER run `tools/dk make` (any target), `make split`, `python3 -m splat`, `make expected`,
  `make clean` or `./diff.sh`: they change shared outputs for everyone (`make split` deletes
  the asm of every function matched since your base). If a `.s` your copy references is
  missing, report it and work on other functions; never rebuild your copy from `src`. A
  `tools/dk` call pausing on `dk: waiting for ... lock` while the gate runs is normal: wait.
- Never kill by pattern: stop only a PID you started. Never delete shared `.scratch`
  directories (including `.scratch/permuter`); clean only your own task-specific files.
- Put scratch/probe files under `.scratch/<YourName>/`, never the repo root.
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
- Keep per-function compiler derivations and rejected routes in the task's shared `.scratch/`
  notes directory; hand the paths to the next agent. Report new rules clearly or message
  siblings via `write agent://<id>`; when spelling grids stall, derive the rule before editing.
- DIRECT mode (you are the only agent on the file): edit it in place, check with
  `tools/objdiff.sh src/<seg>/<file>.c [FUNC]`.
- Run fdiff and `--non-matching` serially for each copy: both overwrite the same object.
  fdiff prints `OK` (exit 0), `TEXT OK` (3), or FAILED with a diff. Exact diff in ONE call
  (each `tools/dk` call gets a fresh /tmp): `tools/dk sh -c 'mips-linux-gnu-objdump -d
  --no-show-raw-insn <your .o> > /tmp/b; mips-linux-gnu-objdump -d --no-show-raw-insn
  expected/build/src/<seg>/<file>.o > /tmp/e; diff /tmp/e /tmp/b'`
  (private objects: `build/.scratch/.scratch_<YourName>_<file>.c.o`; ignore pure `%lo`
  addend differences like `0(at)` vs `532(at)`). A function whose size differs shifts
  everything after it: get the size right first.
  A whole-file FAILED in functions you never touched is normal for a copy older than the
  orchestrator's latest merges; a FAILED in YOUR function is real even when deadsweep scores
  0 (its reduced TU hides a missing prototype of a callee declared only inside a park).
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
- Follow AGENTS.md "Decompiling a function" step 4 (stage order, permuter search-hint rule,
  NON_MATCHING parking) except: no ROM build (gates: `fdiff.sh` OK/TEXT OK, `--non-matching`);
  `uopt_trace.sh` before any register guess, `as1probe.py keep`+`scan` before any schedule-only
  spelling search (aim at its routes; report hits C cannot emit with the edit); every `tools/dk`
  call under ~10 min (permuter `-j 2 --seconds 600`, deadsweep `--rounds 1`); never bypass its lock.
  Order: callee prototypes vs definitions (`unit_check.py protos`, also arity), cfe hidden
  temps (nested calls), structural spelling grids, then `deadsweep.py sweep --extra <locals>`,
  then simulated annealing (`.scratch/*/anneal.py` from past units: dead tests + which local
  each use reads + declaration order, cost full + 6*|insn delta| + 0.3*fakes), then greedy-delete
  FAKEs that no longer change the score. A wrong register at stage 6: run
  `python3 tools/quirks.py get ido-load-overlay-diagnostics` and `search --symptom regalloc
  forbidden` first (cheapest legal register, forbidden sets, coordinated cross-loop lifetimes).
  Once allocation matches, combine independent `.loc`-removal hits before abandoning a
  schedule near-miss: each may fix only part of one multi-initializer scheduling group.
  Never keep a dead read of a local unassigned on some path: guard it or add a real pre-definition.
- Any construct you keep only to steer codegen (deadsweep statements, `volatile`, `x ^ 0`,
  `do {} while (0)`) ends in a trailing `// FAKE: <what it steers>` comment (AGENTS.md
  Conventions); keep deadsweep's own tag. Shared globals use the type most of `src/` gives
  them (`extern Actor *D_807FBB40;`), never `void *` plus a local view.
- Park only stage 4+ (same callee-saved set AND frame size, remaining diff only regalloc/
  scheduling/stack layout) in your copy as `#ifdef NON_MATCHING` / `<C>` / `#else` / blank line /
  `#pragma GLOBAL_ASM("asm/...")` / `#endif` (the blank line before the pragma is required);
  stage 2–3 stays on its GLOBAL_ASM line. Check the parked C compiles with
  `tools/fdiff.sh --non-matching <copy> <src> [FUNC]` and the plain `tools/fdiff.sh` still gives
  OK/TEXT OK. Parks count as unmatched; not genuinely equivalent: keep the draft in `drafts/`.

# Method
Your budget is finite: near-misses first, then never-attempted functions smallest to largest;
after a serious effort on one, move on and come back if budget remains. Before writing C,
read the matched C that `tools/dk python3 tools/similar.py -s <segment> <FUNC>` lists, then
take starter C from `tools/dk python3 tools/m2c.py -s <segment> <FUNC>`. First run `python3
tools/unit_check.py protos [--seg <overlay>] <your copy>`: callee return/param widths and arity
that differ from the CURRENT definition (`void` vs `s32`, `u8`/`s16` declared `s32`, phantom
params) each flip the caller's v0/v1, ring or `andi`s; an unused `s32` result takes a ring temp.
When a scorer reaches zero, put readable C UNPARKED in your whole-file copy and run fdiff
on that same form: a parked `OK` checks asm, not C; `--non-matching` is only a compile check.
A draft-only or still-parked "match" is not a match, even if a ROM gate passes.
Stop on outcome, not time: report as soon as every assigned function is matched, or is back
on its exact `GLOBAL_ASM` line with a saved draft whose note names the stage and the exact
remaining diff, and you have no untried idea left (a few attempts in a row that no longer
shrink the diff). Never idle to fill time. Save the draft after every improving attempt.
Keep context small: diff one function's objdump at a time, pipe long output through `head`.
A function reported at stage 1-3 with untried next steps is unfinished work; a frame-size or
instruction-count mismatch is stage 3 at most (never parked). A function's own rodata (`dlabel D_8075xxxx` in its
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
3. Knowledge: per function, the `quirks.py` IDs you used and whether each helped; then new
   IDO quirks that `quirks.py search` does not already have (one bullet each: title, phase,
   symptom tags, one-paragraph rule naming the function it came from).
4. Final file path.
````
