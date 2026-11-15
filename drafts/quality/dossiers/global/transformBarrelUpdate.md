# transformBarrelUpdate

## Sites

| key | status | what it was / is |
|---|---|---|
| 2ba6be | removed | `if (gPlayerCharacterId) {}` in the sound block. It made the sfxAllocateChannel block reload `sound` from its stack home (`lh a0,98(sp)` at 0x3f84). Without it the copy reuses t9 from the `sound != 0` test. |
| 4925be | removed | dead `gPrimaryPlayerActor->actorType == 9` compare. |
| 516e63 | removed | `if (gPrimaryPlayerActor) {}` in the init block. |
| a9a41f | removed | customState snapshot assigned inside the test. |
| 0f5fc9 | kept | `*(u16 *)&interactionType = 1`, which keeps the constant 1 web separate (Q0449). |

## Attempts
**2026-11-14 Hack80150CharIdView (claude-opus-5-5):**

| attempt | result |
|---|---|
| array view with 2ba6be kept | OK |
| array view with 2ba6be removed | fdiff 1 (the 0x3f84 reload) |
| `if (sound)`, nested ifs, `(s16)` argument | text 85 |
| s32 sound | 94 |
| u16 sound | 205 |
| **sentinel `switch (gCurrentMap)`** | **0** |
| then 4925be removed | 0 |
| then 516e63 removed | 0 |
| a9a41f nested if | 0 (pre-if assignment 3, block local 10) |
| 0f5fc9 plain store | 360 (scan best 155) |

## Untried ideas
- 0f5fc9: interactionType is s16 in actor.h; check whether the field is really u16 across all users (a header change; 24 files touch it).

## Evidence
- 0x3f84 `lh a0,98(sp)` (sound reload in the beq delay slot before `jal sfxAllocateChannel`).
- a9a41f: `lw v0,372(a3)` follows the actorType tests.
