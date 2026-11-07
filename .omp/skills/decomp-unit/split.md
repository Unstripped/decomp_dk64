# Pick and split a unit (SKILL.md §1–2)

Commands below run on the host unless prefixed `tools/dk`. `tools/unit_check.py` and
`tools/rodata_owners.py` work on the current all-asm split. For a file that is already a C
baseline (every global file now is), run them in a throwaway worktree with that file set
back to `asm` (`git worktree add -f .scratch/wt HEAD; rm -rf .scratch/wt/.dkd; cp -R bin baserom.us.z64 .scratch/wt/`
(symlinks dangle: only the worktree is mounted in its container), edit
its yaml, `tools/dk sh -c 'cd .scratch/wt && python3 -m splat split dk64.global.us.yaml'`,
then the worktree's own `tools/`), and `git worktree remove --force` it afterwards.

## Pick

- Order (ROADMAP): overlays and global are all C units (global's remaining asm files are
  hand asm, data or RSP microcode); a unit is now matching rounds on one or two overlays'
  `GLOBAL_ASM` functions (`python3 tools/unit_check.py left src/<ovl>/*.c`, critter + jetpac
  ≈160 functions was one unit) or on ROADMAP's listed global near-misses. A revisit of two
  early file groups' stage-1–4 drafts (~88 functions, 23 units later) matched 82, F4C0–19A00's
  (61, 20 units later) 33 in round 1 + refills: rank them.
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
- Hidden TUs found only by matching (revisit 6: 131B0 → 13980 at `schedCreate`, boss C920 → DAA0):
  a function ending in an endless loop whose count is off by tail nops (IDO's `.align 5` is
  relative to the .o start), or a text-identical match whose `.rodata` refs all sit 4 bytes off.
  The idle agent that found it splits text, `.rodata` and `.bss` in a worktree (precedent `8853f16`), landed like a carve.
- A single-user `.data` global that matches only as a function-local `static` needs a `.data`
  carve of its TU's range (revisit 6: 3 functions). Queue these with the bss carves for one worktree agent.
- Own `.data`/`.bss`/`.rodata`: a single-`lui` u64 store, one `lui at` shared by stores to
  `sym`/`sym+2`, an extern f64 that must be a hoisted literal, or an old note "needs TU
  BSS/data" means the TU defines that object. Users per label: scan every `D_`/named symbol in
  `asm/<seg>` + `src/<seg>` (bss is laid out in TU order, so the owner's run sits between its
  neighbours' labels). Carving is ONE worktree agent's job, run alongside round 1 on the other
  files (early-units unit: 3 carve agents matched 12 functions blocked since unit 1 and found 2
  hidden TUs): it carves (`[0xOFF, .data, <file>]`, `{type: .bss, vram, name}` between bss
  pieces, `[0xOFF, .rodata, <file>]`), defines every object in address order with gap sizes
  (.bss arrays >= 8 bytes align 8), puts interior labels in `undefined_syms.us.txt` (`/* */`
  only), gates the carve alone, then matches the blocked functions there (its task: worktree
  setup, ranges + users, precedent commits `18e0b66`/`f5d9b84`, blocked functions with notes;
  it may run make/split in its worktree). Land it by `git cherry-pick` + one
  `tools/dk --hold sh -c 'tools/dk make split && tools/restore_split_asm.sh <oldest base> <yaml>'`,
  touch, make, `make expected`. Retyping a carved object wider later turns its neighbours
  into interior labels: add them to `undefined_syms.us.txt` or the link fails. A one-object
  carve the orchestrator does inline (yaml `.bss` entry + next auto `bss` piece, define in C,
  split + restore under one lease) must START 16-aligned: IDO 16-aligns a TU's `.bss`, so
  `D_807F6C88` alone landed at `...C90`; `0x807F6C80`–`0x807F6CC0` with its leading neighbours
  defined matched (unused tail before the next label is fine).
- Before another scheduling search, inspect data relocations referencing the target function
  and include its owned callback initializers in the whole-TU comparison (Q0552).
- An interior `.data` carve is not a TU boundary: preserve both fragment lengths and linker
  subalignment, then gate the full ROM rather than importing unrelated asset bytes.

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
  output) was emitted as `.rodata`; fix in the symbol file (`python3 tools/quirks.py search late_rodata force_migration`).
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
Two files sharing a command/state struct or a dispatch table: move the struct into
`include/<subsystem>.h` before round 1 and list the table's entries with their signature in
the brief (cutscene unit: 118 handlers, no signature clashes across 22 agents).

## Gate

`tools/dk make` OK, then `tools/dk make expected`. Commit
`<Seg>: split <files> as C units (GLOBAL_ASM baseline)`.
