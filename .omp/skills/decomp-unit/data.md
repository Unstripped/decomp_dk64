# Data units (SKILL.md §1, every function matched)

A data unit moves one segment's static data from splat asm to C. It replaces §2–3; §0, §4
(ROADMAP, knowledge) and §5 apply. Order: ROADMAP `### 12. Static data`, phases B–H.

## 1. Pick

The first unchecked line of ROADMAP §12. Units on different yaml files are independent:
run them in parallel worktrees. Inside one yaml, one carve agent at a time.

## 2. Owners

`python3 tools/data_owners.py <seg> --range 0xLO-0xHI` (yaml file offsets or VRAMs) on a
fresh `tools/dk make`. Each object prints owners from relocations (`via <label>`: reached
only through another data object); `RUN` lines group objects by owner set.
- `-`: unreferenced. Assign it to the run it pads or sits inside (strings ending exactly
  where a TU's first label starts belong to that TU), else to the previous run's TU.
- `PAD16`: 4+ zero bytes ending 16-aligned, a TU-end candidate. IDO 16-aligns each TU's
  `.data`/`.rodata` start (Q1228) and 4-aligns objects (Q0395, Q0913).
- `ORDER?`: owner earlier in text order than the previous run's. Data order equals text
  order across TUs; an object used by a later TU still belongs to the TU whose range it
  sits in (minecart `gMinecartJunctionTable`). Give the run to the earliest owner in text
  order that keeps every TU contiguous; if none can, the TU whose run starts first defines it all.
- A user in another segment (global code reading overlay data) keeps the name and its
  symbol-file line.
Resolve every `-` and `ORDER?` before carving; write the TU ranges into the task.

## 3. Recipes

**Pragma** (`#pragma GLOBAL_ASM("asm/<seg>/nonmatchings/<file>/D_*.s")`, all `.rodata`):
replace each pragma with a definition at the same position, explicit size = the label's
stride: strings `const char X[N] = "...";` (precedent `fdcf8f98590a`), scripts and
tables `const u8 X[N]`, floats `const f32 X[N]`, an existing struct type when the C
already has one (`3d13888`: CC800's four pragmas became one `KongCharacterEntry` table).
An aggregate-copy blob takes the struct type of the extern that copies it. A trailing pad
belongs to the last object's size only when fdiff shows the bytes missing without it.
Interior labels another file references become absolute lines in `undefined_syms.us.txt`
(`2c70c29e8c0c`). Make users `const` (extern, locals, parameters; then
`uv run tools/protos.py gen`).

**Single-TU `.data` carve**: `[0xOFF, data, X]` → `[0xOFF, .data, <owner>]`; an adjacent
`.data` subsegment of the same file merges into one starting at the lower offset. Define
every object in address order, at the position in the `.c` that keeps definition order
equal to address order (function-local statics sit at their function's position: Q0838,
Q0947, Q1137). Explicit sizes keep each stride; zero objects need `= 0` to stay in
`.data`. Split labels inside one object: `tools/rename.py fold`, else an absolute line in
`undefined_syms.us.txt`. Splat false symbols (`D_80200000`) become casts
(`(void *)0x80200000`). Function pointers use the `include/proto` prototypes.

**Multi-TU carve**: one `.data` subsegment per TU at its 16-aligned start, each defined as
above. A carve can change a same-TU function's code (function-pointer initialisers, Q0552):
retry with every entry naming its function exactly as the asm does (no casts); if the text
still differs, keep that TU's run as its own asm `data` subsegment and list it blocked in
ROADMAP §12 with the function and diff.

**Asset include** (pixel pools, gzip images; bytes stay out of git): a row
`seg name vram size width file` in `data_inc.us.txt`, `python3 tools/data_inc.py gen`
(`make split` runs it), and in the owning `.c`:
`const u8 D_80032220[0x208] = {\n#include "arcade/D_80032220.inc.c"\n};` (`u16`/`u32` for
width 2/4; drop `const` when the object is in `.data`). Never hand-convert asset bytes; a
cfe size limit means one include per object (already the default).

**Handwritten registration**: data whose only users are registered handwritten asm gets a
`handwritten_asm.json` key `asm/<seg>/data/<name>.s` with a reason naming the user. Check
`data_owners.py` first: any C owner (beyond data the plan names) makes it a carve instead.

**libultra data**: a new `src/boot/libultra/<dir>/<file>.c` from decompals/ultralib with
ultralib's object names and macros; literal initialisers if the macros give other bytes.
Data-only files take the directory's flags from the Makefile libultra block.

## 4. Gates

- Pragmas: `tools/fdiff.sh <copy> src/...c` exit 0, or exit 3 with `TEXT OK` and no rodata
  line (objdiff exits 1 on any `.rodata` byte difference).
- Carves: `tools/dk make` → `build/dk64.us.z64: OK`. objdiff does not gate `.data`; after a
  failed make, `python3 tools/datadiff.py <seg>` names the first differing object and symbol.
- Every landing: `merge_gate.sh`'s cfe ratchet; `tools/dk make expected` after it.

## 5. Parallelism

Pragma agents: private copies, one file each, all in parallel (`merge_drafts.py snapshot`
first). Carve agents: one per yaml file, each in its own worktree (split.md header: worktree
setup with `bin`/`baserom.us.z64` copied, its own `.dkd`), may run make/split there.
Brief: fill [data-brief.md](data-brief.md) into `local://data-brief.md`.

## 6. Landing

- Pragmas: `tools/merge_gate.sh --commit "data: <file> rodata to C" [--stage <header/symbol
  file>]... [--allow-lost L]... .scratch/<A> <base> src/<seg>/<file>.c` (`--allow-lost` for
  every label the copy no longer defines by name).
- Carves: `git cherry-pick` the worktree commit, then one lease:
  `tools/dk --hold sh -c 'tools/dk make split && tools/restore_split_asm.sh <oldest base> <yaml>'`,
  `find src -name '*.c' -exec touch {} +`, `tools/dk make`, `tools/dk make expected`.
- A file losing its last pragma leaves asm-processor (`C_FILES_WITH_GLOBAL_ASM`): rebuild
  it, the gate covers it.

## 7. Close

Tick the ROADMAP §12 line (blocked items with address, function and diff stay listed),
`tools/dk python3 tools/progress.py --readme` (the segment's Data % must rise), commit, then
a [run-log.md](run-log.md) row (SKILL.md §5).
