# playerInputHandleAButtonJump (global, src/global/E4090.c)
## Sites
global:806E1BA4:dead-if:c7739c dead-if (FIXED 2026-11-17f): `if (!gActivePlayerState->targetSpeed) {}` after the post-call jumpTimer store. It gave the &gActivePlayerState address constant (uopt const 676) 2 uses in the post-call block, so its adjsave rose 1.50 -> 1.75 above the gActivePlayerState pointer load {165|0} held from the timing block to the targetSpeed store (1.50, cand 6, which wins ties). 676 then took v1 and {165|0} a0. Without the test, {165|0} takes v1, 676 a2, &gCurrentActor a3, &gCurrentCharacterIndex t0 (full=57).
## Attempts
2026-11-09..2026-11-13 CleanE4090/CleanOrch/ReReview/ReRead/CleanGlobalE4090/Rev26A (opus-5-5 low/xhigh): removal 57, permuter best=0 only moved or re-spelled the dead test (if (1) {} around the speed block, if (!gActivePlayerState) {} at the head of the jump block, do {} while (0) after the store chain), bare block and ternary failed fdiff -> nohit (history: quality.py history)
2026-11-17 2026-11-17: cleanup CleanplayerInputHandleAButtonJump CleanplayerInputHandleAButtonJump anthropic/claude-opus-5-5: classified (Q0908): if (1) {} 57, label 57, if (!gCurrentActor) {} 21, if (!gCurrentCharacterIndex) {} 76, if (!gActivePlayerState) {} 0, if (!gActivePlayerState->jumpTimer) {} 0 -> availability class on the gActivePlayerState global, not a block split
2026-11-17 same unit: variants.py scan of the removed body: 3 variants, best 57 (no hit)
2026-11-17 same unit: entry condition as guard clauses `if (unk280 - jumpTimer >= 0xF) return; if ((contactFlags & 1) && floorSlopeFactor != 0.0f) return;` -> fdiff 0 (FIXED). Timing guard alone (contact/slope test kept in an `if` body) 57; nested ifs 57; contact/slope guard alone inside the timing `if` 0
## Untried ideas
none left for this function (no hack sites)
## Evidence
Target (expected E4090.o, function at 0x2814): &gActivePlayerState in v1 (lui/addiu at 0x2840/0x2850 and 0x2864/0x2868), loaded pointer in a0 (0x286c) and reused for the targetSpeed store (0x28dc swc1 $f8,56(a0)); &gCurrentActor a2 (0x287c/0x2880); &gCurrentCharacterIndex a3 (0x2898/0x289c). No load of targetSpeed after the call (0x297c-0x2994: only the jumpTimer store): the dead test was never executed.
uopt -l5 on the fixed copy: 676 live bbs 1,2,7,10,11 (+4..5,8..9), adjsave 2.00 (post-call block 11 now in its range); {165|0} 1.50; &gCurrentActor 916 1.33; colouring 645->v0, 676->v1, 165->a0, 916->a2, 1492->a3.
Sibling playerInputHandleAButtonState0 (same timing/targetSpeed start, no INPUT_MIN) keeps the && form and has the loaded pointer in v1 and &gActivePlayerState in a3: the guard form is what the Jump target needs.
