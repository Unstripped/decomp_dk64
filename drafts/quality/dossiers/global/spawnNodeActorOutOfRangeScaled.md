# spawnNodeActorOutOfRangeScaled (global, src/global/1295B0.c)
## Sites
- global:8072818C:other:7d9940 (was `r` reused for dy): FIXED (HackspawnNodeActorOutOfRangeScaled2). The squared distance is written inline in the compare, `(scaledRange * scaledRange) < (camX - x)*(camX - x) + (camY - y)*(camY - y) + (camZ - z)*(camZ - z)`, with no dz/dx/dy locals; `r` only holds the sqrtf result.
## Attempts
- 2026-11-14 Rereview1295B0b opus-5-5:high: separate f32 dy changes the FP schedule and drops the early 0x3FF8 load.
- 2026-11-15 HackspawnNodeActorOutOfRangeScaled opus-5-5:high: separate dy in 8 declaration positions (31), s32 pad, recipe scan, Actor local, sum local, guard chains, early returns, permuter 900 s (127 zeros, all redefine r).
- 2026-11-16 HackspawnNodeActorOutOfRangeScaled2 opus-5-5:high (variants.py try):
  - separate dy, statement order of dz/dx/dy/scaledRange (24) x 4 sum orders: best 27
  - f64 r, f32/u32 scaledRange, PlayerStruct and Actor pointer locals: 31-61
  - inline subsets (each of x/y/z difference inline or a local) x local order x scaledRange position x 6 sum orders (294 bodies): only all three inline with the x, y, z sum order scores 0 (applied); z-first sums 6-19
## Evidence
- Frame 24, no locals homed (a0 at 24(sp) across sqrtf only). Target: lui at,0x3ff8 at 0x3930 in the initialState block, cvt.d.s/mul.d at 0x3950/0x3958 before the lwc1 loads (camX 528 / x 124 first).
- With the differences in locals uopt sinks `r * 1.5` to the compare. With the loads inside the compare expression it stays at its statement. Likely cause, not traced: the expression holds memory loads (Q0510 has_ilod).
