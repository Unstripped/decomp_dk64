# csCmdStepMultiModelAnimations (global, src/global/478F0.c)
## Sites
global:8064AC28:dead-if:5c9098 dead-if (FIXED 2026-11-17): `if (cs) {}` between the trigger test and the timer decrement in the main loop. Not a cs priority effect (cs, P 0vreg, is never coloured: target reloads it from 168(sp) at 80a0/8180/84d8/84e4). Its test block added block units to the constant-1 range, dropping const 1 adjsave 3.727 -> 3.417 below csId (P 6vreg, 3.714), so csId was coloured first ($s4) and const 1 second ($s5). Without it the two swap s4/s5 (full=23, pure register swap).
`// LAYOUT:` line 2531 (`for (i = 0; i < 9; i++) { p->ent[i].state = 3; }` on one line): separate class, still needed (body on its own lines full=3 after the fix).
## Attempts
2026-11-09 Clean478F0 opus:low: reconstruct 3 FAKE -> 1 (permuter hint seconds=38 best=0); classify class 1.
2026-11-10 ReReview opus:xhigh: diagnose removal colouring 26/26 with 6 differing from candidate 2, full=23; permute best=0 only via inserted `if (1) {}` (hack swap).
2026-11-11 Rev17L, 2026-11-14 RereviewMixedMid2, 2026-11-16d TypesOwner: sweep / review / views (gPlayerCharacterId[] shared array), no site change.
2026-11-17 CleancsCmdStepMultiModelAnimations opus: uopt_trace -l 5/-l 6 base vs removal: colouring order differs only csId (57) vs const 1 (195/197); const 1 adjsave 41/12 (base) vs 41/11 (removal), csId 26/7 both -> fixed by `i = 0; do {...} while (i != 9)` -> `for (i = 0; i < 9; i++)` in the nearest-node search (Q0767: entry-test block adds a unit to the const-1 range): fdiff 0 whole object, clint uninit exit 0. Refuted (variants try): j as modelSlotGetNodePos arg full=143; `n++` before `j = i + 1` 23; nested anim/animT/timer ifs (3 forms) 23; csId test folded into the && chain 23; `for (i = 0; i != 9; i++)` also 0 (the `<` form chosen: same as the 3 other loops).
## Untried ideas
none open: no hack site left.
## Evidence
Frame 0xA8. cs home 168(sp) (sw a0 at 806c, reloaded 80a0, 8180, 84d8, 84e4); p home 164(sp); allDone 135(sp) (li t7,1 at 803c); x/y/z at 128/124/120(sp), s8 = sp+128.
s4 = csId (8084 sll s4,a1,16; 808c move s4,t6); s5 = constant 1 (li s5,1 at 8100/810c/818c; sb s5 active stores 812c-8170, 848c; andi a1,s5,0xff u8 arg at 8284/83d0); s6 = 9 (init loops and the search loop bne s2,s6 at 8434); s7 = n (81c8-81dc); s1 = i, s2 = i + 1 (s32 arg a2 at 8288/83c8), s3 = j (s16).
Init path reloads cs->data after the init block (8180 lw t1,168(sp); 8184 lw v0,0(t1)): `p = cs->data;` after the block is behaviour.
heapFreeDeferred(cs->data) reloads cs (84d8/84e0), not p.
