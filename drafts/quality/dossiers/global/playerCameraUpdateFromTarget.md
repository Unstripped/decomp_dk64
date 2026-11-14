# playerCameraUpdateFromTarget (global, src/global/8F4B0.c)

## Sites
global:8068BBF8:dead-if:14b99b dead-if: `if (D_807FC624 && D_807FC624) {}` before the mathSinF call. uopt -l5: the D_807FC624 load candidate `uilod{20}` ({472}) gets live bbs 16,17,19,21,75,23,24,26,29 (adjsave 2.75) and colour a0 because its range holds bb19, the mathSinF argument block. Without it the range is 18,72,20,21 (2.33): the argument load sits outside it, so the lowest free register v1 wins (lui/lh v1 at 0x167c/0x169c/0x16cc/0x1708, sfx args hoist, 16 lines).
global:8068BBF8:dead-if:71a1f8 dead-if: `if (gGameMode && gGameMode) {}` before the fade update. It adds bbs 26-28 so the {472} range reaches bb29 and the reload at 0x1708 lands in a0 (v0 without, 3 lines). It is coupled with 14b99b: removing both costs 16 lines, the same as removing 14b99b alone (Q0602).
global:8068BBF8:other:cac527 other: `rawDiff = 0;` dead store before the switch. global:8068BBF8:dead-if:b16157 dead-if: `if (rawDiff) {}` after it. These two are one steer: removing both costs 4 lines, the same as removing b16157 alone (angleB second web in a2 instead of a1 at 0x17f4/0x17fc/0x1804/0x1824). -l5: with them, rawDiff ({381}) spans bbs 31,62,57,32-41,58-61 (adjsave 0.8) and colours after angleB ({669}, 1.0). Without them, rawDiff is bb57 only (2.0), colours first and takes a1 (forbidden v0,v1,a0), so angleB gets a2. Removing cac527 alone grows the frame (43 lines).
global:8068BBF8:other:adc136 other: `(u16)angleDiffRaw + 0x1000`. ringfifo sim on the as1probe ugen listing shows that the plain `addu` takes ring front $12 (t4). The target `addiu t5,a0,0x1000` at 0x1828 needs one more ring allocation in that path. The `and 0xffff` that the cast emits is deleted by as1 (8 lines without it).
global:8068BBF8:goto:ua6653 goto: case 0x63 (0x17b8) ends with `b 0x17e8` into calc_angle. That shared tail is the block that 0x7-0x14 (0x17d4) falls into and that 0x4F/0x6D reach with `beql ... 0x17ec`. The target body order is 0x63, 0x7-0x14, tail (Q0591 kept).

## Attempts
2026-11-11 round 11 CleanGlobal8F4B0 claude-opus-5-5:low: views/names/retype; diagnose+permute every site; natural reconstruct fdiff=1; goto-hand via if(0x63) factors fdiff=1.
2026-11-11 round 16 Rev16J claude-opus-5-5:low: diagnoses (frame 0x58->0x80, ring t5->t4, a2/a1); permute with all five removed (calcAngle flag), no zero; flag reconstruct nohit.
2026-11-12 round 20 Rev20C claude-opus-5-5:low: b16157 diagnosis; AimActorAngles view retired.
2026-11-12 round 21 Rev21B claude-opus-5-5:low: diagnoses; goto-hand kept (Q0591, duplicated tail score 5065); reconstruct with per-case (s16) diff score 5865; permute 4 removed, no zero.
2026-11-14 HackplayerCameraUpdateFromTarget claude-opus-5-5:high:
- CamState view for customState (`camState->unkFB`, `camState->unk0`) -> fdiff 0.
- Dropped the redundant `(s16)(s32)` / `(f32)` casts (camYInt, two pitch stores, curAngle) -> fdiff 0.
- Split the reused selector `stateVal` from the clamp result (`clampedDiff`) -> fdiff 0.
- Replaced pad50/pad44/pad30 by the angleB/pitchRad/dx declarations (every local gets a home in declaration order; all 216 placements of real locals into the pad slots match) -> fdiff 0.
- 670+707 together: 4 lines. rawDiff declaration at 22 positions: 4-40. rawDiff replaced by stateVal (15) or minLimit (4). The clamp result held in rawDiff: 4/30. rawDiff computed right after the angleB call: 9 (both cvts CSE). `rawDiff = angleA; rawDiff -= angleB;`: 4. X/Y variable reuse grid (angleB/angleA/fadeTimer/angleDiffRaw x 3 temps x cast): best 4. 64 role grid (which of angleB/angleDiffRaw feeds each compare/store, both assignment orders): best 10 without the cast.
- No rawDiff at all: `angleB = angleDiffRaw = angleA - angleB;` gets a0/a1 right, but the sext temps swap (t1/t0 at 0x17f8/0x17fc). That is 7 lines with the (u16), 15 without. The same happens for `angleDiffRaw = angleA - angleB; angleB = angleA - angleB;`. A 128-variant role grid on both gave a best of 5.
- angleB s32 holding the diff (one sext CSE) 27. New s16 diff local: one sext, 9.
- (u16) site: -/+ path spellings (-=, +=, commuted, angleDiff += 0x1000) best 8; widths u16/s32/u32 of angleDiff, angleDiffRaw, angleB, maxDiff and angleA best 11 (angleA/angleB u16 3 with the cast, lhu at 0x52).
- D_807FC624: shadow mathSinF prototypes s16/s32/u16/u32 gave 17. Pitch spellings x fade spellings (f0-f4) x fadeTimer s16/s32/u16 gave 16-107. switch(gCurrentMap) gave 50, else-if layout 16, swapped || operands 20, fadeTimer at 24 declaration positions 3-40.
- goto: case labels inside `if (0) {}` after the 0x63 body match (fdiff 0) but that is a dead-if steer, so the goto is kept.
- MIN(MAX(angleDiff, minLimit), maxDiff) as one statement: 5 (v1/a0 swap). The two-statement clamp with the doubled MAX is the target behaviour: slt is evaluated twice at 0x1840/0x1860.
- variants.py scan on all-removed (31), coupled-removed (28) and 14b99b-removed (16) copies: no zero.
- permuter 900 s from the hack-free chain body (see report).

## Untried ideas
- A real D_807FC624 read in a block before the mathSinF block (no such load in the target, so likely none).
- Coupled steers 14b99b+71a1f8 replaced by one natural statement that adds blocks before the fade block (Q0592 style dead init is still a hack).

## Evidence
- Frame 0x58. Homes in declaration order: camState 0x54, angleA 0x52, (0x50 slot), angleDiff 0x4e, angleRad 0x48, (0x44), stepFactor 0x40, scaleFactor 0x3c, maxDiff 0x3a, player 0x34, (0x30).
- 0x17ec subu v1,t9,v0; 0x17f0/0x17f4 sll a0/a1; 0x17f8 sra t1,a0; 0x17fc sra t0,a1; move a1,t0; move a0,t1. angleB's sext is emitted first (t0), so it is assigned before angleDiffRaw.
- 0x1824 `sh a1,0x4e(sp)` sits in the beqz delay slot: the angleDiff = angleB store comes before the inner if.
- 0x1840/0x1860: MAX(angleDiff, minLimit) is evaluated twice (MIN(MAX()) macro shape).
