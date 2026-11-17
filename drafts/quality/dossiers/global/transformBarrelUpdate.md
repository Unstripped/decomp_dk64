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

**2026-11-17 HackthrowableBarrelUpdate2 (claude-opus-5-5), after b603f25c (u32 gGlobalOverlayFlags):**

| attempt | result |
|---|---|
| 0f5fc9 plain store | 354 (constant 1 joins the J web of case 4 `hide = 1` and the `unk2C0 != 1` compare, hoisted into t4) |
| plain store moved before `flags \|= 0x8000` | 361 |
| else branch: interactionType before alpha | 355 |
| `1U`, `(u16)1`, `(s16)1`, `(u8)1` | 354 (cfe folds to the plain web) |
| store `allowed` instead of 1 | 369 |
| `allowed` s8/u8/s16/u16 / u32 | 356 / 354 |
| `state->timer = cond ? 1 : 0x5A` | 354 |
| width scan on the plain copy: `hide` u8/u16/u32, s8/s16; `channel` | 364, 385; 354-371 (best: `step` u8 155) |

## Untried ideas
- 0f5fc9: closed as a header case: interactionType is s16 in actor.h and all 11 target loads of 0x132 are `lh` (C920, 42630, 7A510 x2, 9DD70, A6280, A8400 x2, B1F60, C2A90 x2).
- 0f5fc9: the steer only has to keep the 0x3914 constant out of the case 4 `hide = 1` J web (target `li v1,1` per arm at 0x4228-0x42a4); a natural case 4 spelling whose `hide` stores are not J constants has not been found.

## Evidence
- 0x3f84 `lh a0,98(sp)` (sound reload in the beq delay slot before `jal sfxAllocateChannel`).
- a9a41f: `lw v0,372(a3)` follows the actorType tests.
