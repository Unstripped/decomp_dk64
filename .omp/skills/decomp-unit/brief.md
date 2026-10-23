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

Register-allocation toolbox (most later-round near misses are regalloc only): access a
global struct pointer directly vs caching it in a local; local declaration order; split
or merge temporaries, s32 vs narrow temps, scope temps per switch case; commutative
operand order; sequential vs chained assignment; exact prototypes (void vs s32 return,
f32 vs unprototyped, a callback symbol declared as a function rather than `&D_...`);
nested call argument vs sequential assignment; ternary vs if/else; `do {} while` vs
`while`. Loop-invariant hoisting order follows first use in the loop.

# Concurrency rules (several agents run at once)
- NEVER run `tools/dk make` (any target), `make split`, `make expected`, `make clean`
  or `./diff.sh`: they rebuild shared outputs and race.
- Starter C: `tools/dk python3 tools/m2c.py -s <segment> <FUNC>`.
- Put every scratch/probe file under `.scratch/<YourName>/`, never in the repo root.
- PRIVATE COPY mode: create your copy ONCE from the exact base commit in your task
  (`git show <commit>:src/<seg>/<file>.c > .scratch/<YourName>/<file>.c`), never re-copy
  mid-run, edit only the copy, check with
  `tools/fdiff.sh .scratch/<YourName>/<file>.c src/<seg>/<file>.c [FUNC]`.
- Keep a blank line before every `#pragma GLOBAL_ASM` line, including the last one in
  the file.
- If the text is identical but fdiff prints `FAILED: Relocations mismatch` only because the
  expected asm used a raw address constant where your C uses the symbol, keep the
  function as GLOBAL_ASM, save the draft, and report it as "text-identical, reloc only":
  the orchestrator checks it against the ROM hash.
- If code matches but `.rodata` differs only by zero padding between functions, report it:
  that is a hidden translation-unit boundary, not something to fix in C.
- Key compiler patterns: when you discover a pattern that resolves a common near-miss
  (e.g. post-increment equality `if (reg++ == N)` placing stores in delay slots, K&R spills,
  unrolled loop idioms), report it clearly or message siblings via `write agent://<id>`.
- DIRECT mode (you are the only agent on the file): edit it in place, check with
  `tools/objdiff.sh src/<seg>/<file>.c [FUNC]`.
- Both print `OK` (exit 0) or `TEXT OK` (exit 3) when code matches, else FAILED plus an
  asm-differ diff of FUNC. Exact diff, in ONE call (each `tools/dk` call is a fresh
  container, /tmp does not survive): `tools/dk sh -c 'mips-linux-gnu-objdump -d
  --no-show-raw-insn <your .o> > /tmp/b; mips-linux-gnu-objdump -d --no-show-raw-insn
  expected/build/src/<seg>/<file>.o > /tmp/e; diff /tmp/e /tmp/b'`
  (private objects: `build/.scratch/.scratch_<YourName>_<file>.c.o`; ignore pure `%lo`
  addend differences like `0(at)` vs `532(at)`). A function whose size differs shifts
  everything after it: get the size right first.
- NEVER edit shared headers in `include/` (another agent may own them this round); use a
  local struct/cast prefixed with your agent name.
- Merge hygiene: change only your functions' lines. New externs/prototypes/structs go
  IMMEDIATELY ABOVE your first function that uses them, never in the top block or another
  agent's range. Never change an existing declaration, with one exception: a prototype
  may become unprototyped (`void f(void);` → `void f();`) if every C caller in the file
  still matches; say so in your report. Otherwise adapt your code with casts. Prefix new
  type names with your agent name. When you revert a function
  to GLOBAL_ASM, delete the declarations you added for it. Don't reorder or reformat.
- Skip formatters and linters. NEVER edit `tools/`, `Makefile` or the splat configs.

# Large functions and near-misses
- Stage order for non-trivial functions (OoT IDO 5.3 -O2 guide): (1) behaviourally equivalent C
  (m2c), (2) basic-block order, (3) large reorderings, (4) same callee-saved register set
  and frame size, (5) small reorderings, (6) register allocation. Report the stage reached
  (stages 1–6); register-allocation tricks are wasted before stage 4.
- Why large functions are hard: IDO's uopt assigns registers by priority-based coloring
  (Chow & Hennessy, TOPLAS 1990): priority = estimated savings of a live range weighted by
  block frequency and normalised by its length, highest first, with live-range splitting;
  so a change in one loop shifts registers in another.
- Diagnose register allocation with `tools/uopt_trace.sh [-l LEVEL] [-s src/<seg>/<file>.c] <file.c> [FUNC]`
  on your private copy before guessing (level 6 = coloring trace, 5 = live ranges/savings;
  see header comments in `tools/uopt_trace.sh` for candidate table and coloring order):
  compare which candidate got which register with the target asm.
- Permuter at stages 5–6: `tools/permute.py setup <seg> <FUNC> [--from FILE.c] [--src src/<seg>/<file>.c]`,
  `tools/permute.py run <dir> -j 2 --seconds <S>` (always passes `--stack-diffs` and `--stop-on-zero`),
  `tools/permute.py best <dir>`. Search-hint rule: permuter mutations are NOT semantics-preserving
  (moves statements, randomises types, deletes if statements) and score checks disassembly
  only (stack diffs with `--stack-diffs`, no relocations or data). A result is a search hint:
  rewrite the idea into readable C that keeps the asm's behaviour, then verify with fdiff.
  Never paste permuter output unreviewed. Several agents share the CPU: always pass an
  explicit small `-j 2` and a `--seconds` limit. NEVER run `tools/dk make`.
- NON_MATCHING parking: a function that will not match but whose C is behaviourally equivalent
  (remaining diff only regalloc/scheduling/stack layout, reviewed) may be parked in your copy as:

```c
#ifdef NON_MATCHING
<C>
#else

#pragma GLOBAL_ASM("asm/...")
#endif
```

  Notice the required blank line before `#pragma GLOBAL_ASM`. Check that the parked C
  compiles with `tools/fdiff.sh --non-matching <copy> <src> [FUNC]` (compile only) and that
  the plain `tools/fdiff.sh` still gives OK/TEXT OK. Parked functions still count as
  unmatched. If not genuinely equivalent, keep the draft in `drafts/` instead.

# Method
Your budget is finite: near-misses first, then never-attempted functions from smallest to
largest. After a serious effort on one function, move on and come back if budget remains.
Use the whole budget before reporting. A function that won't match gets its exact
original `#pragma GLOBAL_ASM(...)` line back (or is parked under `#ifdef NON_MATCHING`
if behaviourally equivalent; see above), and its best draft (the function plus the
local declarations it needs) is persisted for later sessions with
`python3 tools/drafts.py save <seg> <FUNC> .scratch/<YourName>/<FUNC>_best.c --note "<closest diff, what you tried>"`,
where `<FUNC>_best.c` holds ONLY that function and the declarations it needs (never your
whole private copy: `save` rejects files with `#pragma GLOBAL_ASM` lines)
(writes `drafts/<seg>/<FUNC>.c`, replacing the old draft). Start from the stored draft
(`python3 tools/drafts.py show <seg> <FUNC>`) if there is one. Your final file MUST give OK or
TEXT OK: never leave non-matching C in it.

# Report (final message)
1. Newly matched functions; remaining GLOBAL_ASM (or parked NON_MATCHING) with stage
   reached (stages 1–6), a one-line closest-diff note each (and confirm you saved its draft
   or parked it under NON_MATCHING).
2. Names ONLY for behaviour you confirmed: `func_X -> <prefix>CamelCase` + one-line reason.
3. New IDO quirks not already in the ok-fine note (one bullet each).
4. Final file path.
````
