# arcadeUpdateDonkeyKongStage2 (arcade, src/arcade/0.c)
## Sites
arcade:8002FE28:noop-arith:08110d noop-arith: FIXED. `x == x * 0` only made the facing andi land in v0; the real cause was the cnt copy local.
arcade:8002FE28:other:ff5952 other: now ORIG (parameter reuse). New entity index lives in the a0 home slot 0x30(sp).
## Attempts
2026-11-14 U HackarcadeUpdateDonkeyKongStage2 anthropic/claude-opus-5-5:high: plain == 0 / named temps / !x / (u32)x < 1 on the cnt body -> 58-66
2026-11-14 U HackarcadeUpdateDonkeyKongStage2 anthropic/claude-opus-5-5:high: no cnt, every use re-reads (s32)D_8004BCD0[entIndex].animTimer, flash temp as in Stage3 -> fdiff 0
2026-11-14 U HackarcadeUpdateDonkeyKongStage2 anthropic/claude-opus-5-5:high: separate newIndex local on the cnt-free body -> full=26 (frame 0x30 -> 0x38)
## Untried ideas
none (function hack-free)
## Evidence
target 0xbe70 mfc1 a0 (first trunc) and 0xbec8 mfc1 a0 (PRE re-trunc after n_alSndpPlay); 0xbed0 andi v0,a0,0x20 = PRE temp of the field read.
A cnt local is its own web: move v0,a0 + andi t5 and every later t-reg shifts by one.
0xc000 sw v0,0x30(sp) / 0xc010 lw a1,0x30(sp): the param home slot of the 0x30 frame (Q0233).
