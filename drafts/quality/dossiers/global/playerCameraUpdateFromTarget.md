# playerCameraUpdateFromTarget (global, src/global/8F4B0.c)

## Sites
global:8068BBF8:dead-if:14b99b dead-if: `if (D_807FC624 && D_807FC624) {}` before the mathSinF call. It stands in for D_807FC624 being a function-local `static s16`. With that static and no dead tests the text matches (TEXT OK; only the TU's own .bss differs). Blocked until 8F4B0 owns bss 0x807FC620-0x807FC630 (header-request.md).
global:8068BBF8:dead-if:71a1f8 dead-if: `if (gGameMode && gGameMode) {}` before the fade. It is coupled with 14b99b, and the function-local static removes both. classify gives class 1.
global:8068BBF8:goto:ua6653 goto: case 0x63 (0x17b8) ends with `b 0x17e8` into the shared calc tail (Q0591 kept).
(fixed 2026-11-14: cac527 dead store, b16157 dead read and adc136 (u16), all by the calc-tail rewrite.)

## Attempts
2026-11-11 round 11 CleanGlobal8F4B0 claude-opus-5-5:low: views/names/retype; diagnose+permute every site; natural reconstruct fdiff=1; goto-hand via if(0x63) factors fdiff=1.
2026-11-11 round 16 Rev16J claude-opus-5-5:low: diagnoses (frame 0x58->0x80, ring t5->t4, a2/a1); permute with all five removed (calcAngle flag), no zero; flag reconstruct nohit.
2026-11-12 round 20 Rev20C claude-opus-5-5:low: b16157 diagnosis; AimActorAngles view retired.
2026-11-12 round 21 Rev21B claude-opus-5-5:low: diagnoses; goto-hand kept (Q0591, duplicated tail score 5065); reconstruct with per-case (s16) diff score 5865; permute 4 removed, no zero.
2026-11-14 HackplayerCameraUpdateFromTarget claude-opus-5-5:high (discarded run; attempts listed so they are not repeated): rawDiff placement/role/width grids, chain spellings, (u16) spellings, D_807FC624 prototype/pitch/fade/switch spellings, MIN(MAX()) and variants scans. None reached zero.
2026-11-14 HackplayerCameraUpdateFromTarget2 claude-opus-5-5:high:
- Calc tail `angleDiff = angleDiffRaw = angleA - angleB; if (angleDiffRaw > 0x800) angleDiff = angleDiffRaw - 0x1000; else if (angleDiffRaw < -0x800) angleDiff = angleDiffRaw + 0x1000;` with NO trailing `break` (last case): fdiff 0, which removes cac527, b16157, adc136 and the rawDiff local. The same body with the trailing break scores 8; with breaks inside the if arms, 5.
- D_807FC624 as a function-local `static s16` with both dead tests removed: text=0 reloc=10 (fdiff exit 3 TEXT OK). As a file-scope static: text=16.
- Without the static: `fadeTimer = D_807FC624; mathSinF(fadeTimer)` (copy temp) scores 13 (fixes only the fade block). A pointer local `timer = &D_807FC624` scores 16-48. `else if (gGameMode != 1)` in place of the return, nested under the primary-player test, scores 16. The fade as one statement scores 48. `switch (camState->unk0->state)` without the stateVal local scores 19.
- variants scan on the copy with only adc136 removed: best 6 (minLimit u8/u16, which changes meaning). On the copy with only cac527+b16157 removed: best 4.

## Untried ideas
- Order the bss bytes 620/621/622 once 8F4B0 owns them (Q0565 `(void)&G`, a struct, or function-local statics in their owners), then land the static.

## Evidence
- Frame 0x58. Homes in declaration order: camState 0x54, angleA 0x52, angleDiff 0x4e, angleRad 0x48, stepFactor 0x40, scaleFactor 0x3c, maxDiff 0x3a, player 0x34.
- 0x17ec subu v1; 0x17f0/0x17f4 sll a0/a1; 0x17f8/0x17fc sra t1/t0. a1 is angleDiff's coloured split piece (-l5: bbs 57-60, stores at the end of each path: 0x1818 path 1, 0x1824 path 2 delay slot, 0x182c path 3). The reload `lh a1,0x4e(sp)` at 0x1834 starts the next piece.
- 0x1828 `addiu t5,a0,0x1000`: ugen emits `addu a1; sll t4; sra t5` for path 3 inside the piece, and as1 deletes the sext (path 1 the same: t2/t3 -> t3 at 0x1810).
- 0x1654-0x170c: every D_807FC624 access is in a0. The function-local static (an isvar S candidate) gives that colouring with plain code. The u8 bytes 0x807FC620-0x807FC622 are used only by other functions in 8F4B0.c.
