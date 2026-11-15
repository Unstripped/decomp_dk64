# arcadeUpdateDonkeyKongStage4 (arcade, src/arcade/0.c)
## Sites
arcade:8002F82C:noop-arith:08110d noop-arith: FIXED (cnt copy local removed; param re-read).
arcade:8002F82C:comma:ee9630 comma: FIXED (frame index in the single tmp local).
## Attempts
2026-11-14 U HackarcadeUpdateDonkeyKongStage2 anthropic/claude-opus-5-5:high: cnt + flash -> full=22/20 (only t0 spill 0x2c -> 0x28); no cnt with (u8)++param / ++param / param++ -> 87; (u8)(s32)++param or (++param & 0xFF) -> 0 (steers, not kept)
2026-11-14 U HackarcadeUpdateDonkeyKongStage2 anthropic/claude-opus-5-5:high: comma: inline == 2 or 2 == x -> 1 (bne v1,v0); switch -> 17; separate frame local -> 20 (spill shift); same tmp as the facing flag -> 0
2026-11-14 U HackarcadeUpdateDonkeyKongStage2 anthropic/claude-opus-5-5:high: final: s32 tmp = ++param; (u8)tmp < 0xA0; tmp = flag; tmp = (s32)(animTimer / 6.0f) % 3 -> fdiff 0
## Untried ideas
none (function hack-free)
## Evidence
0xb93c andi v1,t8,0xff = PRE value of ++param; 0xb940 andi t9,v1,0xff = (u8)tmp; 0xb994 lbu v1,0x1c(t0) re-read after n_alSndpPlay; 0xb998 andi v0,v1,0x20.
Frame 0x38 has room for exactly one declared word: any second declared local moves the t0 spill from 0x2c(sp) to 0x28(sp) (Q0563 frame accounting, ido-uopt-temp-slots).
0xbc7c bne v0,v1: v0 = frame index, v1 = constant 2 shared with D_8004C708 (0xbbc4, 0xbc00).
