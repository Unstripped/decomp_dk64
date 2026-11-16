# playerCameraUpdateFromTarget (global, src/global/8F4B0.c)

## Sites
global:8068BBF8:goto:ua6653 goto: case 0x63 (0x17b8) ends with `b 0x17e8` into the shared calc tail (Q0591 kept).
(fixed 2026-11-14: cac527 dead store, b16157 dead read and adc136 (u16), all by the calc-tail rewrite; 14b99b/71a1f8 dead-ifs by the function-local static, landed with the .bss carve.)

## Attempts
2026-11-11 round 11 CleanGlobal8F4B0 claude-opus-5-5:low: views/names/retype; diagnose+permute every site; natural reconstruct fdiff=1; goto-hand via if(0x63) factors fdiff=1.
2026-11-11 round 16 Rev16J claude-opus-5-5:low: diagnoses (frame 0x58->0x80, ring t5->t4, a2/a1); permute with all five removed (calcAngle flag), no zero; flag reconstruct nohit.
2026-11-12 round 20 Rev20C claude-opus-5-5:low: b16157 diagnosis; AimActorAngles view retired.
2026-11-12 round 21 Rev21B claude-opus-5-5:low: diagnoses; goto-hand kept (Q0591, duplicated tail score 5065); reconstruct with per-case (s16) diff score 5865; permute 4 removed, no zero.
2026-11-14 HackplayerCameraUpdateFromTarget claude-opus-5-5:high (discarded run; attempts listed so they are not repeated): rawDiff placement/role/width grids, chain spellings, (u16) spellings, D_807FC624 prototype/pitch/fade/switch spellings, MIN(MAX()) and variants scans. None reached zero.
2026-11-14 HackplayerCameraUpdateFromTarget2 claude-opus-5-5:high:
- Calc tail `angleDiff = angleDiffRaw = angleA - angleB; if (angleDiffRaw > 0x800) angleDiff = angleDiffRaw - 0x1000; else if (angleDiffRaw < -0x800) angleDiff = angleDiffRaw + 0x1000;` with NO trailing `break` (last case): fdiff 0, which removes cac527, b16157, adc136 and the rawDiff local. The same body with the trailing break scores 8; with breaks inside the if arms, 5.
- D_807FC624 as a function-local `static s16` with both dead tests removed: text=0 reloc=10 (fdiff exit 3 TEXT OK). As a file-scope static: text=16. (Landed with the .bss carve, in src at f9b2e9c7.)
- Without the static: `fadeTimer = D_807FC624; mathSinF(fadeTimer)` (copy temp) scores 13. A pointer local `timer = &D_807FC624` scores 16-48. `else if (gGameMode != 1)` in place of the return scores 16. The fade as one statement scores 48. `switch (camState->unk0->state)` without the stateVal local scores 19.
2026-11-15 HackplayerCameraUpdateFromTarget3 anthropic/claude-opus-5-5:high (base f9b2e9c7, static landed):
- goto: nested `switch (stateVal) { case 0x63: ...; break; default: ...; }` inside a merged 0x63 + 0x7-0x14 group: text 4 (outer beq/jump-table entries land on an inner `li at,99; bne` re-test). Case labels inside `do { } while (0)` with `break` after the 0x63 body: full 0, but that only swaps the goto for a do-while(0) steer (nohit). goto-hand kept (Q0591).
- Fade with the static: `swayPhase += 0x1E; swayPhase &= 0xFFF;` full 0 (applied, drops the fadeTimer temp); `swayPhase = (swayPhase + 0x1E) & 0xFFF;` 33; `t = (swayPhase + 0x1E) & 0xFFF; swayPhase = t;` 33.
- Clamp: `MIN(MAX(angleDiff, minLimit), maxDiff)` 5; same without minLimit (`-maxDiff`) 5; the two ternaries in one expression 5. Two-line clamp with the clampedDiff temp kept (ordinary C).
- Static renamed D_807FC624 -> swayPhase (fdiff 0). quality sweep: 0 hits; variants scan: only declaration swaps zero.

## Untried ideas
- None for the goto: every structured form either adds a selector re-test (if (0x63), nested switch), duplicates the tail (5065), adds a flag, or swaps in another steer (if (0) / do-while(0) case labels).

## Evidence
- Frame 0x58. Homes in declaration order: camState 0x54, angleA 0x52, angleDiff 0x4e, angleRad 0x48, stepFactor 0x40, scaleFactor 0x3c, maxDiff 0x3a, player 0x34.
- Dispatch: jump table only for 0x7-0x14 (sltiu t7,14 at 0x1798, table at .rodata+0x1e8); 0x63 is `beq v1,at(99)` at 0x1768 -> 0x17b8; 0x4F (0x1788), 0x69 (0x1744 beq -> 0x17e8), 0x6D (0x174c beql -> 0x17ec) reach the tail directly; default `b 0x1834` with `lh v0,0x3a(sp)` (maxDiff) in the delay slot.
- 0x17b8-0x17d0 case 0x63 (stepFactor 0.02 from .rodata+0x220, scaleFactor 15.0 = lui 0x4170) ends `b 0x17e8` with the second swc1 in the delay slot; 0x17d4-0x17e4 case 0x7-0x14 (stepFactor 0.1, maxDiff 100) falls into 0x17e8 `lh t9,0x52(sp)` (angleA).
- 0x17ec subu v1; 0x17f0/0x17f4 sll a0/a1; 0x17f8/0x17fc sra t1/t0. a1 is angleDiff's coloured split piece (-l5: bbs 57-60, stores at the end of each path: 0x1818 path 1, 0x1824 path 2 delay slot, 0x182c path 3). The reload `lh a1,0x4e(sp)` at 0x1834 starts the next piece.
- 0x1654-0x170c: every swayPhase (ex-D_807FC624) access is in a0; the function-local static (uopt isvar S) gives that colouring (Q0857).
