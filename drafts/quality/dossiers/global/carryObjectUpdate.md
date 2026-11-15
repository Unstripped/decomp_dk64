```
# carryObjectUpdate (global, src/global/9DD70.c)
## Sites
global:8069B908:volatile:25d017 volatile: kept the lda effectLightPulseOscillate store/load at sp+0x6c (0x33f8/0x3400) - REMOVED
global:8069B908:dead-if:cc0832 dead-if: block split between randVal def and effectCreateAtPosition (randVal spill at sp+0x78) - REMOVED
## Attempts
2026-11-14 HackcarryObjectUpdate HackcarryObjectUpdate anthropic/claude-opus-5-5:high: plain callback -> 0x64 (full=2); no callback -> 0x68 (full=2); callback def before if/loop/block -> still propagated (full=2)
2026-11-14 HackcarryObjectUpdate: IV loop (particleIdx 0..7, effectSetAngle(particleIdx * 2)) + no callback local + scale via dz -> every slot right, frame 0x138 vs 0x140 (uniform 8-byte shift)
2026-11-14 HackcarryObjectUpdate: + randVal/randomFloat nested in effectCreateAtPosition args -> dead-if gone, still frame 0x138 (uopt Mmt 236)
2026-11-14 HackcarryObjectUpdate: + case 10 squared differences inline (dx/dy/dz unused -> pad) -> fdiff 0 (uopt Mmt 244)
2026-11-14 HackcarryObjectUpdate: shared i for the particle loop -> 10 lines (volumeTrigger loop v0/v1/a0 rotation); separate loop local needed
## Untried ideas
none open (function hack-free)
## Evidence
0x32f8 sw zero,0x70(sp) / 0x33bc lh a0,0x72(sp) / 0x35c8 addiu t8,t6,2; bne t8,0x10: IV temp of particleIdx*2 (uopt vreg -208)
0x33dc lui/addiu t6 effectLightPulseOscillate, 0x33f8 sw t6,0x6c(sp) in effectSetSpeed delay slot, 0x3400 lw a0,0x6c(sp): uopt spill temp (vreg Adt -212)
0x3538 sw v0,0x78(sp) / 0x3540 lw v1,0x78(sp): randomNonNegative result kept across randomFloat in the cfe hidden u32 temp (-200, shared with the switch selector)
cfe def Mmt 204 (hidden temps -200 u32, -204 f32); uopt def Mmt 244 -> frame 244+0x48 = 0x13c -> 0x140
case 10 inline (a-b)*(a-b) terms add block-local CSE temps at the bottom of the temp area (236 -> 244)
```
