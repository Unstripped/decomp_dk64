# gfxBuildScrollingBackground

## Sites
- global:80706F90:other:1c23c5 (line 481), `*(s16 *)((u8 *)gTintKeyframes + 0x18) = scroll;`: stores gBgScrollX (0x80754F70) through gTintKeyframes+0x18, so the store keeps its own `lui at; sh t7,0x18(at)` at 0x2d00/0x2d04. A direct `gBgScrollX = scroll` makes the store share the lda {551|1} with the tail read (`lui v1; addiu v1,%lo(gBgScrollX); lh v0,0(v1)` at 0x2cd8).
- global:80706F90:other:797f1c (line 483), `*(s16 *)((u8 *)D_80754EF8 + 0x78) = 0;`: the same for the wrap store. Target: `lui at; sh zero,0x78(at)` at 0x2d14/0x2d18. Plain: `sh zero,0(v1)`.

## Attempts
- Rounds 10, 16, 17, 20: plain, permute, diagnose and reconstruct (see the history file).
- 2026-11 Hack109660BgScroll (claude-opus-5-5), all fdiff `--reloc-ok` row counts or variants text rows:
  - struct view `{ s16 x; s16 pad2; s16 y; }` over gBgScrollX: 28 rows; `s16 gBgScrollX[]` view: 28 rows (plain is 20).
  - function-local `static s16` X/Y (Q0761): text 31. The S-var stores the unnarrowed v0 and loads Y first.
  - tail shapes, text: xfirst 19, else-arm 15, s32 temp 17, Y temp 49, wrap order 28, re-read compare 40, assign-in-compare 44, chained assign 19, `+=` 40.
  - `(&gBgScrollX)[0]` and `*(u16 *)&gBgScrollX`: 15 (same as plain).
  - pointer local: 31.
  - uopt_trace -l 6, plain vs base: the global colouring is identical.
- sweep at the copy: plain and recipe nohit. `variants.py scan` of the plain copy: nothing below the baseline (text 15).

## Untried ideas
- Owning the TU's .data (0x80754CE0..0x80754F80) in 109660.c, so that the layout itself shows whether gBgScrollX/Y were one object. This is a yaml/data migration (owner item). The Q0761 static test already shows a function-local static does not match.
- An as-yet-unknown spelling that gives the stores a different (block, offset) lda key than the loads.

## Evidence
- Target tail at 0x2cd8-0x2d38: X and Y each load with their own lui. The Y store is at 0x2cf8; the X store of the narrowed t7 (`sra t7,t9,0x10` at 0x2cfc) is at 0x2d04. The conditional X zero store is at 0x2d18. Y is reloaded at 0x2d1c and its zero store is at 0x2d38.
- Data: gTintKeyframes 0x80754F58 (0x18 bytes), gBgScrollX 0x80754F70 (s16 + 2-byte pad), gBgScrollY 0x80754F74 (0xC bytes of zero). Both are used only by this function.
- Trace: `evidence/trace_plain6.txt` vs `evidence/trace_base6.txt`. The candidate table differs only in uistr bits 299/301, at address {551|1} vs 311/1226.
