# playerWeaponCrosshairRender (global, src/global/F56F0.c)
## Sites
global:806F2A40:dead-if:e02a3d dead-if (FIXED 2026-11-17f): `if (gActivePlayerState && gActivePlayerState) {}` made the gActivePlayerState load candidate 0 so ps took v0 and the u16 timer local v1; the timer local itself was the cause (a named local is numbered at its store, before the load it holds).
global:806F2A40:dead-if:ff1a40 dead-if (FIXED 2026-11-17f): `if (timer == 0) {}` kept ucvt(timer) live across the clamp (candidate 56 -> a0) so adj took a1 and inc a0; real cause: the switch selector temp and the ternary result share one cfe int temp coloured a0.
global:806F2A40:dead-if:c06f57 dead-if (FIXED 2026-11-17f): `if (entries && entries) {}` re-raised the entries param adjsave to 1.0 (s0) after the other two dead tests split blocks inside its range (0.714 without it); coupled steer, gone with them.
## Attempts
2026-11-09..2026-11-13 rounds 3/6/12/16/23/24/37 (CleanF56F0, ActorTypes, ReReview, CleanGlobalF56F0, Rev16E, Rev24; opus-5-5 low/xhigh): removals, re-read variants of unk21E with the timer local kept, ps temp, second Actor * temp, permuter runs (best=0 only by re-inserting dead tests) -> nohit, all three kept.
2026-11-17 2026-11-17: cleanup CleanplayerWeaponCrosshairRender CleanplayerWeaponCrosshairRender anthropic/claude-opus-5-5: no timer local (unk21E read on the field twice, CSE) -> full=5 with all three dead tests removed (e02a3d + c06f57 solved, a0/a1 swap left); if/else, (adj < 3) ? adj : 2, MIN order, inline ternary in +=, no adj local, inc = 2 default, inc copy, single refined local -> 5..19; `if (sel) {}` after adj -> 0 (dead test, not kept); switch (actor->state) + inline ternary in the += -> fdiff 0, no hacks (switch + inc local -> 5; switch with the timer local -> 28).
## Untried ideas
none open: the function has no hack site left.
## Evidence
0x2050-0x2058 lui/addiu t0,&gActivePlayerState; lw v0,0(t0): ps in v0 (bit 2), &global in t0 (bit 86).
0x2064 lhu v1,542(v0): unk21E in v1, reused without reload by 0x20d0/0x2188 slti at,v1,30 (one CSE candidate, bit 3).
0x205c/0x2060 addiu sp,sp,-8 / sw s0,4(sp), 0x2068 move s0,a1: entries in s0 (reg 14, adjsave 1.0).
0x206c move a3,a0: actor in a3 (a0 taken by the selector temp first).
0x20b4/0x20bc lbu a0,340(a3): switch selector in a0 = cfe int temp -20vreg (candidate 11, adjsave 3.0, live bb2-3 and bb14-16).
0x21b0 subu a1,t4,v1: remaining in a1 (candidate 57); 0x21bc move a0,a1 (bnez delay slot) / 0x21c0 b / 0x21c4 li a0,2: ternary result in a0, the same temp as the selector.
0x2158 lhu v1,542(v0) / 0x215c addiu t8,v1,-1 / 0x2168 sh: decrement re-read after the float stores (gActivePlayerState reloaded after every indirect store: no ps local).
