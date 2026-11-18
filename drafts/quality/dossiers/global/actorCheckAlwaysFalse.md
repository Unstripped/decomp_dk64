# actorCheckAlwaysFalse (global, src/global/9DD70.c)
## Sites
global:8069A750:other:c56038 other: `if (v != 2 && v != 3) { v = 0; }` - the dead carrier store `v = 0` (uopt store bit 19, ugen `move $2,$0` between `beq $2,$6,$33` and `$33`) is the one record that keeps ugen's labelopt from deleting both state tests; as1 deletes the move after its jump-to-next pass, leaving `beq v0,v1` / `beq v0,a2` to the latch at 0x1728.
global:8069A750:dead-if:0641d2 dead-if (was c1eebc `if (v == 5) {}` + 1aaf2a `if (i == 5) {}`, merged 2026-11-17): `if (v == 5 || i == 5) {}` - v == 5 is the uopt use of the carrier store; both terms add loop-invariant webs (li $7,5 -> a3, la $8,gActorGlobalState+20 -> t0) that as1 deletes; t0 being a uopt web drops it from ugen's ring, so lw 88(t9) at 0x173c takes t1.
## Attempts
2026-11-10 cleanup round 4 Clean9DD70 opus-5-5:low: diagnose/permute all sites, switch/|| reconstruct -> nohit
2026-11-11 cleanup round 16 Rev16I opus-5-5:low: plain/cond/classify (class 2 both dead ifs), permute (dead unk7C tests) -> nohit; switch/|| reconstruct .text 20864 vs 20896
2026-11-12 cleanup round 20 Rev20B/Perm20B opus-5-5: removal diagnoses (bnezl at,1704 + t0 for t1), permute best=0 only by new dead tests -> nohit
2026-11-12 cleanup round 26 Rev26B opus-5-5:low: permute c1eebc -> steer swap
2026-11-13 cleanup round 38 CleanGlobal9DD70 opus-5-5:xhigh: uopt traces (uneq bits 15-18, uequ bits 20/21, store bit 19; webs 37-40 -> v1,a2,a3,t0), permute -> steer swaps only
2026-11-17 cleanup CleanactorCheckAlwaysFalse CleanactorCheckAlwaysFalse opus-5-5: c1eebc + 1aaf2a merged into `if (v == 5 || i == 5) {}` -> fdiff 0 (FAKE 3 -> 2; uopt candidate table and colouring identical to base); `v == 5 || v == 6`, `v == 5 && i == 5`, `v == 5 || i == 0` also 0; `v == 5 || 1` / `v == 5 || v == 5` / lone `v == 5` 2 rows; nested arm test without store 3; self-copy `v = v` 11, `v ^= 0` 11, post-loop guard 29, loop-top guard 14; switch default / ternary / else-arm carriers 0 (same dead store); kong then-arm flag 6, early continue 11; `u32 v` 0 (kept)
2026-11-17 same unit: hack-free-weights permuter (perm_allrm) from the body with both dead tests deleted (carrier kept), -j 2, 900 s, 43275 iterations -> base 1013, best 10; every output under 100 re-inserts a dead test (lone `if (!v) {}` 10, constant local `new_var = 3` + dead test 20/55/80, `(i && i) && i` in the arm 45, triple unk39/unk7C dead tests 85/95)
## Untried ideas
none with a natural construct left: the arm needs a uopt-coloured def that only as1 deletes, and uopt keeps such a def only with a later no-code use (a dead test, Q0561/Q1026); a ring-temp arm def is folded by uopt (nested field/shift tests) and would take t9 by the ring model (Q0554/Q0441)
## Evidence
target 0x16e0-0x1754 (expected/build/src/global/9DD70.o): loop 0x170c-0x172c = lw t8,124(a0); addiu a0,4; sltu at,a0,a1; lw v0,88(t8); beq v0,v1 (v1 = 2, li at 0x1700) -> 0x1728; nop; beq v0,a2 (a2 = 3, li at 0x1704) -> 0x1728; nop; bnezl at,0x170c
no instruction between 0x1724 and the latch 0x1728: the target never performs a store in the non-2/3 arm (the v = 0 carrier is dead, not a one-path store)
post-loop: lui t9 hoisted to 0x16f4; lw t9,0(t9) 0x1730; lw t1,88(t9) 0x173c (t1: t0 is excluded from the ring by the uopt web); move v0,zero hoisted to 0x1738 into the lw/bne stall
ugen (as1probe keep): `li $7,5`, `la $8,gActorGlobalState+20`, the arm `move $2,$0` and entry `move $2,$0` are all deleted by as1 as dead defs
