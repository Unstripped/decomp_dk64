# Pick and split a unit (SKILL.md §1–2)

Commands below run on the host unless prefixed `tools/dk`. `tools/unit_check.py` and
`tools/rodata_owners.py` work on the current all-asm split.

## Pick

- Order (ROADMAP): overlays are all C units; next come global subsystems, i.e. the candidate
  files named at the end of ROADMAP section 9's bullets, or more matching rounds on
  ROADMAP's listed near-misses.
- A global subsystem is a set of `asm/global/<file>.s` files. Find them from what the
  already-named functions call (`grep -o 'func_80[67]…'` in their C) and from the globals a
  file references most (`grep -oE '%hi\(D_[0-9A-F]+\)' asm/global/<f>.s | sort | uniq -c`).
- Size: `python3 tools/unit_check.py count global` (all still-asm files) or
  `count global <file>...`.
- Hand-written asm is not IDO C: `python3 tools/unit_check.py handasm global <file>...` must
  print 0 (64-bit ops, `$k0`/`$k1`; `77B90`, `15010`, `16B60`, `61690` are hand-written). It
  misses 64-bit-free hand asm: entries without a prologue using unsaved `$s`/`$f` state and
  `j` into `alabel`s (`1E2D0`), or one function falling into the next (`17A10` cos→sin).
- `python3 tools/unit_check.py boundaries <seg> <file>...` before the split: `falls into` is
  hand-written fall-through or a spimdisasm split at a continuation label (the "function"
  starts mid-body, e.g. in a `jal` delay slot: give the real function `size:` in the symbol
  file); `trailing nops` after a `jr` is 16-byte TU padding, a hidden TU at the next function.
- A `.word` run splat labels `func_` (an f32 table in `.text`, `1F9A0`) gets its own
  `[0xOFF, asm]` subsegment.
- Compiler per file: unoptimised code (every argument homed to the stack, a dead `b` to the
  epilogue after each `return`, two `jr $ra` ending a void leaf) is `-g`. Compile one small
  function at `-O2`, 5.3 `-g` and 7.1 `-g` and compare
  (`tools/dk sh -c '/opt/ido7.1/cc -c ... -g -mips2 ...'`); `-g` files go into
  `GLOBAL_G_FILES` in the Makefile. When several agents report the same "no source form
  changes it" code-generation pattern, send one agent to test other compilers/flags instead
  of more source variants (that is how IDO 7.1 was found).

## TU boundaries (before round 1)

Hidden TUs found only after round 1 cost a re-split while agents run; settle them now.
- `python3 tools/rodata_owners.py <seg>` lists each run of data/rodata labels with its owning
  text file and kinds. Inside one splat file, a string/word run after doubles/jump tables,
  or a `(TU end pad after <label> ...)` flag, marks a TU end: IDO pads every object's rodata
  to 16 bytes. Grep `asm/<seg>/<file>.s` for the padded label to find its owner function.
- Not every pad flag is a TU end: a flag where the file's late_rodata (floats, jump tables)
  starts after its own const tables is the `.rodata`/late_rodata edge inside one TU when
  functions on both sides use labels on both sides. Check with a min/max rodata-address
  listing per function: monotonic, non-straddling ranges mean real TUs.
- Place the text boundary at a 16-byte-aligned function start between the owners' functions
  (nop padding only at file ends). When several aligned starts qualify, narrow in order:
  1. BSS clusters the functions touch;
  2. a 16-aligned `.data` object whose users all lie in the later TU (an upper bound: the
     TU starts at or before its first user);
  3. rodata/data users or padding between the candidates.
  If nothing separates them, the choice is layout-neutral: take the first aligned start after
  the last first-TU data/rodata user and say so in the yaml comment.
- Shared globals only rank candidates; they are not proof.
- A data pad after one nonzero float and two zero words may be a 3-float struct or a scalar
  plus 8-byte TU padding: record the choice as tentative in ROADMAP and re-check when a
  function in that range matches.
- Unreferenced strings ending exactly where a file's first rodata label starts belong to
  that file's TU.

## Hidden empty functions

`python3 tools/unit_check.py empty-funcs <seg> <file>...` prints `owner func_ADDR` for each
unsymbolised `jr $ra; nop` merged into a preceding function (owner == address: already
symbolised). At a file start write them as `void func_ADDR(void) {\n}` in the seeded stub;
after another function, first add `func_ADDR = 0xADDR; // type:func` to the symbol file so
splat gives each its own `.s`, then replace that pragma with the same C body at split time.
List them in the brief.

## Split

- One agent per segment in parallel; a lone segment inline. The agent edits only
  `dk64.<seg>.us.yaml`, `symbol_addrs.<seg>.us.txt`, `src/<seg>/*.c`; re-splits only its
  segment (`tools/dk python3 -m splat split dk64.<seg>.us.yaml`); builds only
  `build/<seg>.text.bin build/<seg>.data.bin` + `sha1sum -c dk64.<seg>.us.sha1`.
- Data: overlays keep one named asm `[0xOFF, data, 0]`; global keeps the shared
  `[0x14B740, data]` blob and only gains `.rodata` entries, one per file.
- First build exactly N bytes long: an unreferenced late_rodata float (owner `-` in the tool
  output) was emitted as `.rodata`; fix in the symbol file (ok-fine quirks).
- An f32+f64 pair merged into one label shows up as a standalone
  `asm/<seg>/nonmatchings/<file>/D_XXXXXXXX.s`: give the float `type:f32 size:0x4` and the
  double `type:f64 force_migration:True function_owner:<func>`.
- After any symbol fix: delete the still-unedited generated stubs `src/<seg>/<file>.c`,
  re-split, then `touch src/<seg>/*.c` (make does not rebuild objects whose asm changed).
- Keep carved files all `GLOBAL_ASM` and commit the split before any matching.

## `-g` files

asm-processor rejects tiny GLOBAL_ASM blocks (`too short .text block`) and asm-only data
blocks (`.text block without an initial glabel`). Before the first build list glabels of
≤6 instructions:
- a 4-insn `jr $ra; nop; jr $ra; nop` after a non-void leaf is that leaf's dead tail: delete
  the symbol, give the leaf `size:0x18`;
- genuinely tiny functions: write them as C at split time;
- `.word` runs with RSP opcodes (`mtc0`, `jal` into IMEM) are microcode: carve them into
  their own `asm` subsegment.

## Seed the stubs

Under `#include "common.h"` in every new stub: `#include "actor.h"` (global) and the file
family's hot externs with ONE agreed type, including hot array/struct globals with a full
struct (behaviour files: `extern Actor *D_807FBB40; extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70; extern u8 D_807FBD70;`). Unseeded, every round-1 copy
declares them with its own type and each merge after the first clashes. Commit the seeded
stubs, then snapshot. Skip seeding only when each file gets exactly one agent.

## Gate

`tools/dk make` OK, then `tools/dk make expected`. Commit
`<Seg>: split <files> as C units (GLOBAL_ASM baseline)`.
