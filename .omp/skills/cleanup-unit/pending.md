# Pending after cleanup round 38 (campaign paused by the user)

State after the round-38 close (knowledge commit 7a7ec5c6, Q0754-Q0759): 192 OPEN functions in 117 files. Since then the campaign runs as a rolling queue (SKILL.md §2): a future session starts with `uv run tools/quality.py rank --limit 40` (function hack queue) and `rank --polish` (file polish queue); coverage first. The "Blocked owner/header changes" below are the `TypesOwner` queue (types-stream.md).

## Blocked owner/header changes
- Owner return-width redesigns (2026-11-14): callee returns a zero-extended byte, callers differ per file in their andi narrowing,
  so a u8 -> s32 return needs every caller re-spelled and fdiffed. (a) 3C10 `mapGetHubWorldIndex` u8 -> s32 (retires 8F4B0
  da5663/2c5186, likely FCCD0's steer): 6 callers fail (36880, 478F0, 9DD70, ACDC0, B5EC0, C2A90); evidence .scratch/
  HackactorCutsceneDispatchEvents/. FCCD0 da5663/06d21a (HackslotQueueInit, merge 21900581): ORIG refuted; with the shared
  u8 prototype only bitfieldSet/Clear/HasMappedFlag (pass `map`, not `map & 0xFF`: 0x1428/0x1468/0x14ac) and slotQueueAddValue
  (addu v1 vs a0 at 0x1368, its value-reuse FAKE) differ, so FCCD0 consolidates once slotQueueAddValue is fixed.
  (b) 135D30 `flagGet` u8 -> s32 (retires jetpac/0 c1a42b/ef3c2a): 217 calls in 49 files, not
  measured; jetpacUpdateStateAndInput narrows itself (andi t9,v0,0xff at jetpac 0x11d4); evidence .scratch/HackjetpacStateGameOver/.
- Cast sweep (round 30): 55B20 MapChunk.lastSeenFrame and 61AA0 BillboardCacheEntry.lastUsedFrame stay s32 (u32 retype fdiff 1). model.h/heap.h frame stamps landed u32 after Rev29.
- 90D80 renderRotatedSprite proto-steer (02809d, 0d85ab) stays: the 103AB0 owner is 32-bit by its own asm (texWidth forwarded in a3 without andi, texHeight read with lw 0x60(sp)); a u8 owner adds andi/lbu. Closed as not applicable (round 29, dbf5cc61: owner texWidth/texHeight u32 instead).
- critter/5110 D_807FCC40/44 split labels stay (round 27, def29e0b): folding them into gPlayerInventoryTable fails because the folded form shares one table base (Q0687); the u8 pun is now `extern u16 D_807FCC40[]`, tagged.
- ACDC0: D_807FC828..D_807FC838 are one s16[9] collectible-count table; declaring the array changes codegen (text 16 bytes smaller), kept as separate symbols.
- 2F550 MapViewEntries proposal (.scratch/Rev24/header-request.md), held.
- Actor.soundSlots[0] (0x6E) is a frame counter in BC3B0 (beep timing): the shared field name may be too narrow (header owner).
- 55B20 MapZone.tris as MapTriangle * would remove 23 casts (a natural rewrite does not match yet); mapChunksRender never reviewed (blocked on 2F550 MapViewEntries + 35000 renderEntryListBuildDisplayList u8).
- arcade/0: tag the same `i += 0x24` hack in arcadeSpawnStage3Entities.
- proxPathAdd/proxPathSetSegment -> `s32 id` (optional) would drop 36880's `(Actor *)id` casts.
- Shared MapViewEntries (owner 2F550, 0x8 = dl) would let 55B20 drop MapChunkArg; renderEntryListBuildDisplayList last parameter s32 vs u8 (owner 35000) blocks the mapChunksRender proto-steer.
- jetpac/4FC0 `extern JetpacPlayerActor jetpacPlayer`: JetpacState raises its cfe 1 -> 2 (3480 and 1A60 already use JetpacState).
- gActiveActors/gActiveActorCount: file-local externs in 33 files (header move candidate, actor.h).
- 42630 csCmdExec proto-type 89a542 (hudSpawnCountdownTimer arity, owner A7710) stays blocked. W712 3ae317 fixed in round 31 (119370 effectGridFindByTargetId returns EffectGridAsset *, 8c4e5c7c). 450 2e505d actorMapModelsSetup stays (round 27: 8D3E0 kept actorMapModelsSetup(s32, u8, u8)).
- Extern unification left: gPlayerSlots keeps void * in 1025E0, 10E1D0, 11BC10, 12E800, 1332B0, 2C910, F93B0, FCCD0, u8 * in 9BF30, s32 in 9DD70, plus 17 file-local view types (retire the views first). D_807FD568 is `KongInventory *` in every file (OwnerKongInventoryPtr 0c0021b1 + OwnerModelSlotsViews 4d0a8baf).
- KongInventory field carve (actor.h), unblocked: unk0[1] slamLevel, unk0[2] weaponFlags, unk0[4] instrumentFlags; fdiff all 7 users (19A00, 7CA80, D5E10, 103AB0, 42630, E4090, EFDC0). Evidence and the B-button handler caveat (unk0[2] & 1 gates the instrument/fairy-camera handlers): .scratch/s2026-11-14-types-queue.md, OwnerKongInventoryPtr report.
- File-scope views: PLAYER_VIEWS (450), MODEL_TRANSFORM_SLOT (36880), TagBarrelInputPad (80150, needs a shared pad type); actorBoneChainSwingUpdate near-miss hint in the Rev20A report. ModelSlotPosTypeView (936B0) retired by OwnerModelSlotsViews.
- Optional (types queue): HeapBlock u64 view (heap.h) so 15050's 13 `*(u64 *)blk = 0` / `((u64 *)q)[i]` puns, now `// ORIG:`
  (HackloadOverlay, merge b4eccb1b: target 64-bit pair stores/copies), become typed 64-bit accesses; fdiff each, keep the ORIG
  comments' offsets.
- String convention (W709, string literals passed to `u8 *`): jetpac/4FC0 6c4893, global/90D80 renderHitCounterHUD/hudDrawRollingCounter, global/C0EE0 func_806BCF98 are blocked on 100180 `textDrawStringVtx`/`textDrawString` taking `u8 *` (the text API reads unsigned bytes, `*str++`). Decide one convention (e.g. `char *` parameters with an unsigned read) and fix all callers in one batch.
- 1332B0 volumeTriggerUpdate PlayerSlot stride view of gPlayerSlots kept (Q0606, views blocked).
- 11BC10 `effectFallStateInit(Actor *, EffectNode *, u8 *)` (19A00 warnings 5bc221 ×3).
- 119370 `effectCreateAtModelNode(s32 asset, f32, s32, s32, u8)` (42630 warning 3ae317); Rev17P: effectGridFindByTargetId/effectCreate return `EffectGridAsset *`, TimedLightActorView → EffectNode, sEffectPending* names.
- Owner prototypes to check (HackbossSetRandomObjectPair d376b6df, 3 ORIG call-site declarations): 42630 csModelStateSetFirstByte 2nd param likely u8 (F0D0 passes a plain lbu; 2C910 unprototyped), 7CA80 actorUpdatePrevContactFlags may return s32 (9DD70 textMarkerUpdateMatrix needs a non-void declaration, 0x2d88). Read the owner bodies; a corrected owner signature may retire those ORIG declarations. Detail: .scratch/s2026-11-14-types-queue.md.
- EffectNode follow-ups (PolishGlobal11BC10Views turn 1, eed17d85: render.h has the EffectGrid types and the per-kind 0x35C/0x384 unions; 32 11BC10 callbacks take EffectNode *): boss/0, boss/F0D0 stale declarations and 89250 EffectOwnerView done (OwnerEffectNodeCallers 136214b3). Open: 11BC10 turn 2 (menu session, base ba91d5d1: TimedEffectActorView, 51 functions, 5 stale reviews, diagnose lines for the 4 tagged `speed = 0.35f` sites); 478F0 CsEffView (brief Owner478F0CsEffView at 2312fbfe); 119370 `effectCreateAtPosition` should return `EffectNode *` instead of `void *` (119370.h:85 + callers; 89250 effectSpawnActorScale then drops its `(EffectNode *)` cast).
- SpawnEntry (1295B0.c:79-97) -> include/actor.h with shadowScaleX/Z at 0x14/0x15, retires 12E800's file-local view (PolishGlobal12E800Names fc237550 header-request; brief OwnerSpawnEntryShared at 2312fbfe).
- 201B0 types (PolishGlobal201B0Names dd61e7f3): CamPathPointPos per-type union (blend for types 10/15/16, point for 1-3), CamZoneEntryFull first 16 bytes per zone type, own (index, cell) record for CAM_ZONE_SORT (WorkerB1F60).
- 133A90 ProxPath.owner key type (42630 warnings 0eead6, 2e5ca6); 42630 csCmdExec views (proto-type 89a542).
- 8D3E0 `actorMapModelsSetup(void *, u8, u8)` (450 warning 2e505d).
- 12E800 behaviourUpdateContactAndState second parameter (B2CE0/BB300 proto-type 3544eb views).
- 1025E0 `func_806FDAB8` first param: owner retype to u8, u16 and s32 all fdiff 1 (round 29, CleanBonus2690 retype/owner_*.fdiff), so bonus/2690's local u8 declaration steer (689f58, e3027b) stays. Not actionable.
- gCamActor extern stays `void *` in boss/8520, B100, C920 (retyping raises cfe); gFrameCounter/gGlobalPauseFlags single shared type.
- PlayerStruct 0x270 s16 bounds carve (A8400 ScreenBounds/MapBounds views); round-16 list in run-log (TargetVec3f header, KongInventory, playerStateQueueCallback arity, n_alSndpPostEvent).
- 1445A0 still has its own AuxPVoice/AuxPVoiceEnv/AuxResample views of N_PVoice/ALVoice (follow-up to the audio_synth.h bundles).
- `Actor.unk15F -> hudMode` (A7710 proposal: 6 or 0xB passed as gfxResourceCreate mode): include/ field, other actors' use unchecked.
- 36880 views on `ModelSlot.unk20` (void *) blocked on the model.h H1/H2 regeneration (clashes with file-local ModelSlot typedefs).
- boss/0 and ACDC0: proto-steer `consolidate` rungs staled by the round-18 Actor 0xEC union (4 + 6 functions' sites) need fresh agent runs.
- Data ownership (HacktransitionSetAudioVolume, 2026-11-14, ledger a001e1ac): carve the .data region of 14C9E0 around D_807550A4
  into its owning C file; that enables a Q0498 function-local `static` retry for transitionSetAudioVolume's dead-if 86665d.


## Round-34 leftovers
- Done in round 36 (37ae4167): PadInputState typedef in actor.h (no header extern), E4090/CEAE0/D5E10 on it, CEAE0 reads the s8 attackerSpawnNodeId directly. Still open: CC800 G00Slot34, 103AB0 PlayerSampleInfo, menu/0 MenuControllerPad, 80150 TagBarrelInputPad, 7BBD0 CollisionPadD610 and bonus/2690 BonusB_Ctrl views of gPlayerPadState (each declares its own extern; convert file by file, then add the header extern last), plus the D_807FD63A/63C/618 split-label users in CC800, F56F0, bonus/2690, race/7BD0 (E4090's D_807FD63A is load-bearing, Q0264).
- gMinecartTrackPoints shared declaration (CleanBonus2690 round-36 request): 8 files declare it with different types (bonus/2690, race/36B0, minecart/0, minecart/25F0, 478F0, race/1770, 2F550, race/7BD0); a TargetVec3f ** header extern needs all of them in one batch.
- Round 38 leftovers: C0EE0 func_806BCF98 W709 x2 (string literals into textDrawStringVtx `u8 *`) and 19A00 scriptOpPlaySoundAndShake W709 (be3187) wait on the string-convention batch below; 61AA0/5E2F0 LightTrigger is in render.h (05fdbfdc) but gLightCandidates keeps per-file externs (55B20 and 63EC0 declare it `u8`); D_807ECD58/D_807ECD60 are `OSContPad` in C0EE0 but `u16` in bonus/9010, A8400, ACDC0.
- multiplayer/0 reclassification proposal (Rev34A): mpDrawHud early locals matchOver/paused (10c615, 924c0a) and the mpUpdate flag (c4ac54) may be source structure, not hacks (Q0498/Q0108); tags kept.
- 36880 renderModelQuadGfx owner arity: 35000 passes 8 args against a 7-arg prototype; the target stores the 8th at 0x1C(sp) (Consol34).
- 117190 D_8075E5C0/D_8075E5C2: a 4-byte `{u8 id; u8 pad; u16 maxTime}` entry type would retire the tagged pun 318113 in menuCheckMapTransitionOnLoad (file-scope view, reaches 3 more functions).
- Names not applied: MpSettings.unk0 / func_80714608 (mode vs gameMode unclear); func_806C9974 -> playerAddHealthDelta (Rev34C proposal, round-35 names step).
- global/6710 (round 33): permutes on 442abf and 8e31ef#2 owed (>=600 s). race/7BD0: raceRenderSpeedBoostHud a3016e permute hit to confirm/apply; raceRenderCoinHud permute owed. race/A960: 714c8a permute owed. global/0: globalInit W709 0299c2 needs owner mainThreadLoop(s32) -> void * (450.c stand-in bundle); mainThreadHalt never reviewed. global/54150: W709 777430 retype; 02baa4 permute owed.

## OPEN functions

The per-file list is `uv run tools/quality.py rank` (full) or `status --file <f>`; the round-34 close snapshot is `.scratch/r34_post_knowledge.txt`.
