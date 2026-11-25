# transformBarrelUpdate (global, src/global/80150_barrels.c)

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

**2026-11-25 continue CleantagBarrelCheckKongFlag (anthropic/claude-opus-5-5), base 594af197 (variants.py try):**

| attempt | result |
|---|---|
| plain store + block-scoped `u8 hide; s16 channel;` in case 4 / `s16 i` in a case-20 block / both | 366 / 370 / 372 (with the pun 10 / 6 / 16: frame slots shift) |
| permuter perm_tb (hack-free weights incl. 12452351, -j 2, 900 s, 3975 iterations) from the plain-store body (setup 4760, run base 4649) | best 10: an `Actor *` alias of gCurrentActor for the allowed-arm `flags \|= 0x8000` plus a value-named constant local for 0x1E (`timer = k`, `timer < k`) |
| plain store + only the 0x1E constant local | 366 |
| plain store + only the alias `Actor *actor = gCurrentActor; actor->flags \|= 0x8000;` (block-scoped in the allowed arm, in the state < 0x14 block, or function-level last) | 10: the codegen matches; only the case-3 `sound` home moves sp+98 -> sp+94 (the alias local takes a frame word); function-level first 72 |
| alias + `sound` moved to function level at each of the 16 declaration slots | 74 each |
| alias + `activePlayerState` dropped (cast `((PlayerState *)player->customState)->actor`) to free its word | 369 (cast alone 435) |
| alias + `i` folded into `entry` / `entry` into `i` | 29 / 29 |
| alias + `itemCount`/`allowed` widths (5 x 5 each for a block-scoped and a function-level alias) | **0** for 22 of 50: block-scoped alias with itemCount s16/u16/u8 and allowed s16/u16/u8/s8 (12; e.g. `u8 itemCount` = moveLevel's u8 type, `lbu a0` at 0x3800, and `u8 allowed`, a 0/1 flag); function-level alias with itemCount s16/u16 and any 8/16-bit allowed, or u8 itemCount with 16-bit allowed (10). s8 itemCount 1/11; function-level u8/u8 10; any s32 10. Without the alias no width pair goes below 364 (plain) |
| alias for both statements of the allowed arm (`actor->interactionType = 1` too) / for the flags RMW in both arms / for every access in both arms | 304 / 4 / 293 (the target reloads gCurrentActor after the flags store: `lw t6,0(t1)` 0x3920 before `sh t5,306(t6)` 0x3928, so the store is not through the local) |
| verdict | `cand_0f5fc9_alias.c` (plain store, u8 itemCount, u8 allowed, alias for the allowed-arm flags RMW only) fdiff 0, but the alias is a single-use re-read of gCurrentActor through another pointer (the 871b3e `p` family): not adopted (hack swap); ruling requested |

## Untried ideas
- 0f5fc9: closed as a header case: interactionType is s16 in actor.h and all 11 target loads of 0x132 are `lh` (C920, 42630, 7A510 x2, 9DD70, A6280, A8400 x2, B1F60, C2A90 x2).
- 0f5fc9: what bridges is the case 4 `unk2C0 != 1` compare (0x4218 `li at,1`, 0x421c `beq t6,at`): any spelling that makes that compare unsigned matches (1U, `& 0xFFFFFFFF`). A natural reason for an unsigned compare there (a real unsigned field or operand) has not been found; `unk2C0` is `lbu` everywhere (u8).
- 0f5fc9: the allowed-arm flags RMW through an `Actor *` local is the codegen lever (2026-11-25). A natural reason for a pointer local holding gCurrentActor that covers exactly that access (and leaves the reloaded interactionType store on gCurrentActor) would close the site together with the natural u8 widths of itemCount/allowed.

## Evidence
- 0x3f84 `lh a0,98(sp)` (sound reload in the beq delay slot before `jal sfxAllocateChannel`).
- a9a41f: `lw v0,372(a3)` follows the actorType tests.
