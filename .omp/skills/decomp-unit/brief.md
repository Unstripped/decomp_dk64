# Matching-agent brief template

Fill `<...>` and write it to `local://brief.md`; each `task` `context` is then "Read
`local://brief.md` FIRST and follow it exactly" plus that file's facts. One `tasks[]` item
per agent with its target file, mode, and function list (near-misses first, each with its
last known diff note).

```
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
- PRIVATE COPY mode: copy `src/<seg>/<file>.c` once to `.scratch/<YourName>/<file>.c`,
  edit only the copy, check with
  `tools/fdiff.sh .scratch/<YourName>/<file>.c src/<seg>/<file>.c [FUNC]`.
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

# Method
Your budget is finite: near-misses first, then never-attempted functions from smallest to
largest. After a serious effort on one function, move on and come back if budget remains.
Use the whole budget before reporting. A function that won't match gets its exact
original `#pragma GLOBAL_ASM(...)` line back, and its best draft (the function plus the
local declarations it needs) is persisted for later sessions with
`python3 tools/drafts.py save <seg> <FUNC> <file> --note "<closest diff, what you tried>"`
(writes `drafts/<seg>/<FUNC>.c`, replacing the old draft). Start from the stored draft
(`python3 tools/drafts.py show <seg> <FUNC>`) if there is one. Your final file MUST give OK or
TEXT OK: never leave non-matching C in it.

# Report (final message)
1. Newly matched functions; remaining GLOBAL_ASM with a one-line closest-diff note each
   (and confirm you saved its draft).
2. Names ONLY for behaviour you confirmed: `func_X -> <prefix>CamelCase` + one-line reason.
3. New IDO quirks not already in the ok-fine note (one bullet each).
4. Final file path.
```
