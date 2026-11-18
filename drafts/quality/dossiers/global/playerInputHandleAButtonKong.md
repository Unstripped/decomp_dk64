# playerInputHandleAButtonKong (global, src/global/E4090.c)
## Sites
global:806E3040:dead-if:f3ad1c dead-if (FIXED 2026-11-17f): `if (!gCurrentActor) {}` after actorScriptStartByIndex(gCurrentActor, 0x1A) in the state 0x1D arm. It added a use of the &gCurrentActor address constant (uopt const 916) in the post-call block: adjsave 1.33 -> 1.67 above &gActivePlayerState 676 (1.50), so 916 took v1 and 676 a2. Without it the two swap (full=23).
## Attempts
2026-11-09..2026-11-13 CleanE4090/CleanOrch/ReReview/ReRead/CleanGlobalE4090/Rev16F/Rev26A (opus-5-5 low/xhigh): removal 23; permuter best=0 only moved the test (end of block, after the unk155 store, into the 0x3E arm) or added if (1) {}; hand shapes if/else with one jumpTimer tail 890 -> nohit
2026-11-17 2026-11-17: cleanup CleanplayerInputHandleAButtonJump CleanplayerInputHandleAButtonJump anthropic/claude-opus-5-5: classified (Q0908): if (1) {} 23, label 23, if (!gCurrentPlayerIndex) {} 27, if (!gActivePlayerState) {} 36, if (!gCurrentActor->unk155) {} 0 -> availability class on the gCurrentActor global, not a block split
2026-11-17 same unit: variants.py scan of the removed body: 5 variants, best 23 (no hit); original && condition with if/else arms (no return) 23
2026-11-17 same unit: entry condition as three guard returns (unk280 - jumpTimer >= 0xF; gPlayerCharacterId[gCurrentPlayerIndex] == 6; (contactFlags & 1) && floorSlopeFactor != 0.0f) with return or if/else arms -> fdiff 0 (FIXED, if/else kept); the contact/slope guard alone inside the remaining && `if` also 0
## Untried ideas
none left for this function (no hack sites)
## Evidence
Target (expected E4090.o, function at 0x3cb0): &gActivePlayerState in a2 (0x3ce0/0x3cf0, 0x3d04/0x3d08), &gCurrentActor in v1 (0x3d40/0x3d44), loaded gCurrentActor in v0 (0x3d50) reused for both state stores (0x3d9c/0x3da0). No gCurrentActor load after the 0x1A call (0x3de0-0x3dfc): the dead test was never executed.
uopt -l5 on the fixed copy: 916 live bbs 6,10,12 (+7,9), adjsave 2.00; 676 1.50; colouring 645->v0, 916->v1, 165->a0, 676->a2.
