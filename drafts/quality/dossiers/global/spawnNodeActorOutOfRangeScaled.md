# spawnNodeActorOutOfRangeScaled (global, src/global/1295B0.c)
## Sites
global:8072818C:other:7d9940 other: `r` (sqrtf(rangeSq)) reused for dy; the reuse pins r * 1.5 (lui at,0x3ff8 hoisted into the initialState block, cvt.d.s/mul.d before the dz/dx/dy loads); register-only, r has no stack home
## Attempts
2026-11-14 Rereview1295B0b opus-5-5:high: separate f32 dy changes the FP schedule and drops the early 0x3FF8 load
2026-11-15 HackspawnNodeActorOutOfRangeScaled opus-5-5:high: separate f32 dy in 8 declaration positions (31, identical: no slot involved), + s32 pad (31), recipe scan around it (31-34), Actor local (31), scaledRange *= scaledRange (31), sum local (31), reversed compare (31), r reused for the squared threshold (24), sequential/&&/early-return guard chains (52-71), ret = 0; if (cmp) ret = 1 (32/46), scaledRange computed at the top or after dz/dx/dy, or (s32)(sqrtf(rangeSq) * 1.5) with no r (31: uopt sinks it to the use); as1probe scan (no as1-only fix, best 28); redundant (s32)/(f32) casts removed (fdiff 0); permuter 900 s on the separate-dy base: 127 zeros, all redefine r after r * 1.5 (r = dy, r = sum, (r = dz) * dz) or add a dead if
## Untried ideas
none natural: only a redefinition of r between r * 1.5 and the compare reproduces the uopt-level constant hoist
## Evidence
Frame 24, no locals homed (a0 at 24(sp) across sqrtf only). Target: sqrtf -> $f0; lui at,0x3ff8 at 0x3930 in the initialState test block; cvt.d.s $f6,$f0 / mul.d at 0x3950/0x3958 before the lwc1 loads; dx $f12, dz $f2, dy $f14 (same colours with a separate dy: the difference is schedule + constant placement, decided in uopt not as1).
