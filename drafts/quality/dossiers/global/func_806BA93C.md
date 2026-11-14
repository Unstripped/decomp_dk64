# func_806BA93C (global, src/global/BDEE0.c)
## Sites
global:806BA93C:dead-store:7af59a `dir = rock->tilt;` in the 0x37/unk155==0 arm: REMOVED; replaced by `s32 dir = 0;` at the declaration. Either gives dir an early def so it is coloured before the rock->side load: dir v0, side v1 (0x19ec/0x19f0).
## Attempts
2026-11-11 round 11 CleanGlobalBDEE0: sweep remove/cond (fdiff 1), uopt_trace diagnose (side load v0, dir constants v1), permute zero only via other dead stores / constant locals. Round 16 Rev16J: permute moved the dead store to dir = -1.
2026-11-14 HackbehaviourFairyInitPlayerScale opus:high (variants.py try): removal 6; --rock->tilt 6; tilt snapshot u16/s32 188; dir s16 58; dir declared first 34, last 9, in the rollPhase block 9; ?: 6; negated if/else 6; dir = -1; if (side) dir = 1; 1 (one-insn layout shift); dir = 1; if (!side) dir = -1; 7; s16 side snapshot 172; side test moved before rollPhase -= 0x800 14; s32 dir = 0 at the declaration 0.
## Untried ideas
none.
## Evidence
0x194c-0x198c tilt decrement and compare never read into dir; 0x19ec lh v1,2(s1) (side), 0x19f0 li v0,-1, 0x1a00 li v0,1, 0x1a1c move a1,v0.
