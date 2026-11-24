# arcadeUpdateDonkeyKongStage4 (arcade, src/arcade/0_game.c)
## Sites
arcade:8002F82C:noop-arith:08110d noop-arith: FIXED 2026-11-14 (cnt copy local removed; param re-read).
arcade:8002F82C:comma:ee9630 comma: FIXED 2026-11-14 (frame index in the single tmp local).
arcade:8002F82C:other:fad443 other (kept): `s32 tmp` is the function's only declared word. Since 2026-11-24 it holds two
  roles: the incremented param byte (`tmp = ++param`: v1 = andi t8,0xff at 0xb93c, `(u8)tmp` = andi t9,v1,0xff at 0xb940)
  and the stage-clear frame selector (`tmp = (s32)(animTimer / 6.0f) % 3`: mfhi v0, `bne v0,v1` at 0xbc7c with v1 = the
  constant 2). The facing-flag role is gone: `facing = !((param & 0x20) / 32);` matches (fdiff 0), while
  `facing = (... / 32) == 0;` does not (andi t4 instead of v0 at 0xb998, every later t register +1: 65 lines).
## Attempts
2026-11-14 U HackarcadeUpdateDonkeyKongStage2 anthropic/claude-opus-5-5:high: cnt + flash -> full=22/20 (only t0 spill 0x2c -> 0x28); no cnt with (u8)++param / ++param / param++ -> 87; (u8)(s32)++param or (++param & 0xFF) -> 0 (steers, not kept)
2026-11-14 U HackarcadeUpdateDonkeyKongStage2 anthropic/claude-opus-5-5:high: comma: inline == 2 or 2 == x -> 1 (bne v1,v0); switch -> 17; separate frame local -> 20 (spill shift); same tmp as the facing flag -> 0
2026-11-14 U HackarcadeUpdateDonkeyKongStage2 anthropic/claude-opus-5-5:high: final: s32 tmp = ++param; (u8)tmp < 0xA0; tmp = flag; tmp = (s32)(animTimer / 6.0f) % 3 -> fdiff 0
2026-11-24 2026-11-24: cleanup CleanarcadeUpdateDonkeyKongStage4 CleanarcadeUpdateDonkeyKongStage4 anthropic/claude-opus-5-5 (base 2e593510, re-measure after 05c5a664):
  - three per-role s32 locals (timer, dir, frame) at function scope -> 2: only the frame 0x38 -> 0x40 (addiu sp at
    0xb840/0xbe1c); the t0 spill stays 0x2c. Block-scoped (timer/dir in the gArcadeFrozen block, frame in the girder
    else block) -> 2. Two locals (any pair) -> 20 (t0 spill 0x2c -> 0x28). Zero locals -> frame 0x30, spill 0x28.
    So the original declares exactly one word of locals (odd local-word count keeps the spill at 0x2c, Q0869/Q0361).
  - width grid of the three locals (6^3 types, cast/no cast on the counter, 396 bodies): best 2 (s32/s32|u32/s32);
    u8 timer drops the second andi at 0xb940 (93); narrow frame adds sll/sra or andi after the mfhi (>= 37).
  - `ArcadeEntity *e = &gArcadeEntities[entIndex]` for every access: with tmp -> 20 (spill shift), roles inline -> 15.
  - facing-flag spellings with tmp kept for the other roles: `!((p & 0x20) / 32)` -> 0 (APPLIED), `(...) == 0` /
    `0 == ...` -> 76, `?:` forms -> 79, `!(p / 32 & 1)` -> 6.
  - after the facing fix: timer + frame as two s32 locals -> 20 (spill), function or block scope, either order; s32
    timer + frame inline -> 1 (`bne v1,v0` at 0xbc7c, uequ{2}{rem} canonicalisation); variants scan of that body: no
    zero; s32 frame + counter inline (`++p < 0xA0`, `(u8)++p`, `p++; if (p < 0xA0)`, `(p += 1)`, `(s32)++p`,
    `!(++p >= 0xA0)`) -> 85 (the second andi 0xff at 0xb940 is missing), `(p = p + 1) < 0xA0` -> 125; two-local width
    grid (36 types x order x cast): packed s16/s8 pairs restore the frame and spill but add sll/sra at 0xb940 and after
    the mfhi at 0xbc48 (37).
## Untried ideas
- none from the local asm: the counter needs a 32-bit holder plus an executed u8 conversion (0xb940), the frame
  selector needs a variable operand (bne v0,v1 at 0xbc7c), and the frame (0x38, spill 0x2c) admits one declared word.
## Evidence
0xb93c andi v1,t8,0xff = value of ++param; 0xb940 andi t9,v1,0xff = (u8)tmp; 0xb958 andi t2,v1,0x1f; 0xb994 lbu v1,0x1c(t0) re-read after n_alSndpPlay; 0xb998 andi v0,v1,0x20; 0xb9b8 sltiu t5,t4,1; 0xb9c0 sb t5,0x1a(t0).
Frame 0x38, ra 0x24, t0 spill 0x2c: zero locals 0x30/0x28, one 0x38/0x2c, two 0x38/0x28, three 0x40/0x2c (Q0869, Q0361).
0xbc7c bne v0,v1: v0 = frame index, v1 = constant 2 shared with gArcadeGirderState (0xbbc4, 0xbc00).
