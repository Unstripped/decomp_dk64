# renderModelQuadGfx (global, src/global/36880.c)

## Changes
- The definition gains an unused 8th parameter, `s32 unused`. This matches the renderModelAnimatedSlot convention.
- 2026-11-15: the dead `if (0) { modelKongVisibilityCheck(0, &useLight, 0); }` is gone; the three useLight tests are bare (`if (useLight)`, `if (useLight && obj->unk5A == 0)`). The object is byte-identical.

## Sites
global:80637B6C:other:a3730f (removed): the dead address-taking call kept the stack-passed u8 useLight in memory (lbu t6,655(sp) at each test) instead of a ucvt candidate coloured $s4 (lbu s4,655(sp) hoisted at 0x5ff0, extra sw s4,0x40(sp)).

## Attempts
2026-11-09..14 (Clean36880, Rev10A..Rev37, permuter 605 s): removal alone 122-3924; s32 useLight via stand-in proto full=4; no permuter zero. See history.
2026-11-15 HackmodelSlotsStepSegmentCommands anthropic/claude-opus-5-5:high: dead call removed + all three `useLight != 0` -> bare `useLight` -> full=0, fdiff 0 (kept). Only the two `if (useLight != 0) {` flipped: also 0; only the `&& obj->unk5A` test flipped: 1113.

## Untried ideas
(none open)

## Evidence
Target 0x5ff0 lbu t6,655(sp); 0x60c0 lbu t6,655(sp); 0x6100 lbu t6,655(sp); 0x6538 lbu t9,655(sp): no register holds useLight. Sibling renderModelAnimatedSlot (same parameter list) writes bare `if (useLight)` and reloads lbu t6/t0/t7,335(sp) per use with no steer. Q0596 (K&R/narrow u8 parameter: bare test vs != 0 differ), Q0817 (stack-passed u8 ucvt candidate).
