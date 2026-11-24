# csModelIdTableReset (global, src/global/42630_cutscene_interp.c)

## Sites
- global:8063D930:other:cc0f6b other: ORIG (ReMeasureKnow24b, 2026-11-24b, Q1629). `do { gCsModelIds[i] = -1; i++; } while (&gCsModelIds[i] < &gCsModelIds[600]);`
  is the target's ordered end-address exit test. a0 = gCsModelIds + 1200 (lui/addiu a0 0x4/0x8), walk v1 += 2 (0x14),
  `sltu at,v1,a0` 0x18, `bnez at` 0x1c, `sh v0,-2(v1)` in the delay slot. The loop is not unrolled.
- The one-line `j < 0x212` loop is `// LAYOUT:` (Q0364), not a site. Its index bound unrolls 4x with `bne v1,v0` at 0x50.

## Attempts
- 2026-11-10..13 Clean42630 / Rev16E / CleanGlobal42630: `for (i < 600)` unrolls 4x (27 vs 25 insns); permuter best 10 only
  with an address-taken index.
- 2026-11-24 Polishglobal42630e: pre-existing, tagged FAKE. Tried `for (i = 0; i < 600; i++)` (unrolls 4x), for/do/while
  pointer walks over `s16 *id` (-1 in v1, walk in v0), and an end-pointer local (-1 in a0, end in v0): fdiff 1 each.
- 2026-11-24b continue ReMeasureKnow24b anthropic/claude-opus-5-5 (re-measure after Q1629; variants.py try full=):
  - Every literal index bound unrolls 4x (`addiu v1,v1,8`, four `sh`, `bne v1,a0`): do-while `i < 600` 5, `i != 600` 5,
    `u32 i` 5, `for` 5, `while` 5, sizeof bound 5.
  - Pointer-local walks keep `sltu`/`bnez` with other registers: do-while 9 (-1 in v1, walk in v0, lui/addiu order),
    `for` 6. Index i against a pointer local is regalloc only.
  - Retagged FAKE -> `// ORIG:` citing sltu 0x18. Whole-object fdiff 0.

## Evidence
- Q0765: no literal trip count avoids unrolling, and an end-pointer bound gives `sltu` through LFTR. Q1629: as a loop exit test
  the address compare is not a respelling of the index compare (Q1617 holds only outside loop control).
- Q0439/Q0184: the TU owns gCsModelIds and gCsVarsDirty in .bss, so as1 shares one `lui at` across the peeled stores.
