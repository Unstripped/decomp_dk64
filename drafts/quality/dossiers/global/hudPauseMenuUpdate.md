# hudPauseMenuUpdate (global, src/global/ACDC0.c)
## Sites
global:806A8158:dead-if:3a273f dead-if: entry read of D_807505D4 keeps its address unpointerised so the end decrement/clamp uses fresh lui pairs and the s8 truncation (0xf64-0xf8c) (KEPT)
## Attempts
2026-11-10..12 (low, medium): as1probe, permutes (self-assignment, *0 fold)
2026-11-14 HackhudPauseMenuUpdate opus-5-5:high: end respellings (29-34), snapshot locals (58-64), pointer local (48), mid test as !x / switch / <= 0 (29-30)
## Untried ideas
none natural found (D_807505D4 is extern .data, no local static)
## Evidence
0xf64 lui t7 / lb t7; 0xf74 addiu t8,t7,-1; sll/sra t4; bgez t4 with sb t8 in the slot; 0xf88 lui at / sb zero.
