# screenBlurApply (global, src/global/2DE90.c)
## Sites
global:8062A3F0:other:757606 other: `idx++;` before the g/b stores, which use idx - 1; puts the three byte-pointer IV increments (addiu v0/v1/a0 at 0x13b8-0x13c0) ahead of sb vg/vb at -1(v1)/-1(a0) (0x13c8/0x13d0), after sb vr,0(v0) at 0x1398
## Attempts
2026-11-11 r17 CleanGlobal2DE90 opus-5-5:low: three order steers tagged, two dropped after diagnosis; reconstruct (for loops) 4743; permute joint runs
2026-11-11 r17 Rev17L opus-5-5:low: diagnose (stores before idx++ move the sb out of the loop tail), permute best 10 keeps early increment
2026-11-14 HackscreenWipeStart opus-5-5:high: stores then idx++ (12), src++ before idx++ (2, addiu s1 order), b[idx++] (8), pointer cursors per channel (244), chained r[idx] = vr = (12-27), src++ in the for header (12), r[idx++] = vr + g/b idx - 1 (0, same steer); as1probe keep: the -1 offsets are already in ugen output; permuter 900 s from the natural body: best 10 changes behaviour
## Untried ideas
none natural found: the target's ugen order needs the index increment between the r store and the g/b stores
## Evidence
Loop 1: 0x1370-0x137c IV inits r/g/b + half (v0/v1/a0), 0x1398 sb t6,0(v0), 0x13b8-0x13c4 addiu v0/v1/a0/s1, 0x13c8 sb t8,-1(v1), 0x13d0 sb t6,-1(a0). Stack arrays b sp+100, g sp+152, r sp+204.
