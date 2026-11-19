# transformBarrelUpdate

## Sites

| key | status | what it was / is |
|---|---|---|
| 2ba6be | removed | `if (gPlayerCharacterId) {}` in the sound block. It made the sfxAllocateChannel block reload `sound` from its stack home (`lh a0,98(sp)` at 0x3f84). Without it the copy reuses t9 from the `sound != 0` test. |
| 4925be | removed | dead `gPrimaryPlayerActor->actorType == 9` compare. |
| 516e63 | removed | `if (gPrimaryPlayerActor) {}` in the init block. |
| a9a41f | removed | customState snapshot assigned inside the test. |
| 0f5fc9 | kept | `*(u16 *)&interactionType = 1`: the store's constant becomes the unsigned 1 (uopt `{1\|0}`, the web of the u8 `unk144 = 1` stores) instead of the signed `{1\|1}`. With a signed store the `{1\|1}` range starts at the 0x3914 store and spans the jump table to case 4 and case 20, so it is coloured t4 (11) for the whole switch (Q0449). |

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

**2026-11-17 HacktransformBarrelUpdate (claude-opus-5-5):**

| attempt | result |
|---|---|
| uopt trace, plain vs base | plain: `{1\|1}` range 462 split out 529, assigned uopt 11 (t4); base: `{1\|1}` range 463 split out 531, assigned uopt 6 (a3, case 20 loop only) |
| plain store + `hide` u32 or u8 | 364 |
| plain store + `unk2C0 != 1U` | **0** (the compare 1 leaves the `{1\|1}` web; same steer as the permuter `& 0xFFFFFFFF` hint, so not natural: every other `unk2C0` compare in src is plain `!= 1`) |
| plain store + `hide` u32/u8 + `unk2C0 != 1U` | 0 (hide width does not matter) |
| plain store + case 20 `volumeTriggerQueueOp[i] == 1U` | 393; with `unk2C0 != 1U` too: 118 |
| plain store + `unk2C0 != 1` as nested `switch` / `== 1` then `break` / `!(== 1)` | 354 each |

**2026-11-18 2026-11-18: cleanup CleantagBarrelActorUpdate CleantagBarrelActorUpdate (anthropic/claude-opus-5-5):**

| attempt | result |
|---|---|
| review: `ret` held the actorListFindIdByActor list id and then the flag id (unrelated roles); dedicated `s32 listId` + block-scoped `s32 flag` | 10 (one more word moves the case 3 `sound` home sp+98 -> sp+94); top-level flag at any position 8-16; s16 flag or s8 flag ~374; s16 listId >= 16; `sound` hoisted to the top level 74 |
| riderState folded into activePlayerState to pay for the word | 8 (rider pointer v1 + spill sp+128 instead of s0) |
| `i` folded into `entry` | >= 29 |
| **split + `u8 hide; s16 channel;` (Q1198 packing: hide is a 0/1 flag, channel holds the same sound ids as the s16 `sound`)** | **0 (kept)**; each width alone 0 without the split, both together without the split 74 |
| 0f5fc9 plain store on the new body | 364 (base body 354) |
| plain store + bare `if (allowed)` / `if (hide)` | 354 each (base body) |
| plain store + u8 allowed bare / u8 hide bare | 356 / 364 |
| plain store + `unk2C0 != 1U` on the new body | 0 (Q1180 bridge; a steer) |
| uopt -l5 base vs plain | base {1\|1} piece 531 = bb 247 only (adjsave 5.0, uopt 6 a3); plain piece 529 = bbs 85/87/89 (0x3914 store path) + 196 (case 4 compare) + 247 (adjsave 0.818) coloured uopt 11 t4 |
| variants scan of the plain copy (new body) | best 149 (`step` u8), no zero |

**2026-11-19 2026-11-18c: cleanup CleanthrowableBarrelUpdateb CleanthrowableBarrelUpdateb (anthropic/claude-opus-5-5), base a3d0ef71 body (diagnose re-run after the stale rung):**

| attempt | result |
|---|---|
| 0f5fc9 plain store | 364 (text 366, shape 33): the uopt-coloured {1\|1} web takes a t register out of the ugen ring, temps shift from the refill loop on (`lbu t5` -> `t6`) |
| plain store + u8 `slotMode` local for `gPlayerSlots[playerIndex].unk2C0` in case 4 (Q0601) | 308 (the store gets its own `li t4,1`, but 0x84/0x81 move t4/a2 -> a2/a0 in the allowed chain and `li t4,1` is re-materialised after both stores) |
| variants scan of that body (swap/float/width/declswap, 190 variants) | best 212 (`queued` s8, a steer), no zero |
| per-role case-4 PlayerState (`riderState`, or a block-local `targetState`, instead of the reused `playerState`) | 451 / 445 plain store, 454 / 448 with the pun |
| plain store + case 20 `switch (volumeTriggerQueueOp[i]) { case 1: ... }` (Q0959 lever) | 364 (unchanged) |
| ORIG check | the store is `li t5,1` 0x3914 + `sh t5,306(t6)` 0x3928: `sh` proves the 16-bit width only; signedness is a uopt web effect, every target load of 0x132 is `lh` -> the u16 view stays FAKE |

## Untried ideas
- 0f5fc9: closed as a header case: interactionType is s16 in actor.h and all 11 target loads of 0x132 are `lh` (C920, 42630, 7A510 x2, 9DD70, A6280, A8400 x2, B1F60, C2A90 x2).
- 0f5fc9: what bridges is the case 4 `unk2C0 != 1` compare (0x4218 `li at,1`, 0x421c `beq t6,at`): any spelling that makes that compare unsigned matches (1U, `& 0xFFFFFFFF`). A natural reason for an unsigned compare there (a real unsigned field or operand) has not been found; `unk2C0` is `lbu` everywhere (u8).

## Evidence
- 0x3f84 `lh a0,98(sp)` (sound reload in the beq delay slot before `jal sfxAllocateChannel`).
- a9a41f: `lw v0,372(a3)` follows the actorType tests.
