# controllerAnimSetFromTable (global, src/global/17B90.c)
## Sites
global:80613FB0:dead-if:cbf645 dead-if: splits the single block so the u16 param animIndex is live only in bb 0 and is coloured a1 (move t6,a1 at 0x1134) instead of reloaded from its home (lhu t7,30(sp)); class 1 kept
## Attempts
2026-11-10 r4 QualityTools opus-5-5:xhigh: review, kept as ring-temp steer
2026-11-11 r12/r16 opus-5-5:low: review, sweep remove/cond nohit, classify kept class 1
2026-11-14 HackcontrollerBuildSubcommandList opus-5-5:high: one-expression index `gActorScriptAnimTable[(u16)(animIndex * 7 + actor->actorType - 2)]` 16; actorType first / -2 grouped orders 8-10; s32/u32 idx, x widths (scan) 8; animIndex*8-animIndex 11; param reuse `animIndex = ...` (Q0535) 17; `*=`/`+=` 16; s32 base local 8; type local first 17. None colours the param.
## Untried ideas
none natural: the match needs a block boundary between the index sum and the jal (any real control flow changes the code)
## Evidence
0x1128 sw a1,28(sp) (home, present with and without the test); 0x1130 lw t9,88(a0) actorType; 0x1134 move t6,a1 (param coloured a1); 0x1144 addu v0,t8,t9; 0x1154 andi t0,v0,0xffff; 0x1170 lhu a1,0(t3) in the jal delay slot.
uopt -zdbug:5 without the test: {1581} animIndex adjsave 1, forbidden [1 3 4 5 6] (call arg registers used in the same block) -> not coloured, not splittable. With the test: live bb 0 only, adjsave 2, forbidden [3 6] -> a1.
