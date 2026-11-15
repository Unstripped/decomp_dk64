# Pending after cleanup round 38 (campaign paused by the user)

State after the round-38 close (knowledge commit 7a7ec5c6, Q0754-Q0759): 192 OPEN functions in 117 files. Since then the campaign runs as a rolling queue (SKILL.md §2): a future session starts with `uv run tools/quality.py rank --limit 40` (function hack queue) and `rank --polish` (file polish queue); coverage first. The "Blocked owner/header changes" below are the `TypesOwner` queue (types-stream.md). Audited 2026-11-14 at 7a453f41 (PlanPendingAudit: DONE entries removed; evidence and verdicts in .scratch/PlanPendingAudit/audit.md), re-checked at 74533125: DY ca506697 fixed global/0 f71305 and 450 2e505d (M2, M3), DZ 2e019041 closed every 42630 proto site as ORIG (89a542, M10).

## Blocked owner/header changes
- Owner return-width redesigns (closed, kept as the reason the steer pairs stay): (a) keep `u8 mapGetHubWorldIndex(u8, u8)`
  (OwnerHubWorldIndexWidthPlan: C2A90 func_806BE09C uses v0 unmasked, so the original return is u8); 8F4B0 da5663/2c5186 and
  FCCD0 da5663/06d21a stay FAKE. (b) keep `u8 flagGet(s16, u8)` (OwnerFlagGetWidthPlan: no option passes all 49 files); 80150
  c1a42b/b5496b stay FAKE, jetpac/0's pair is ORIG (0x11d4).
- critter/5110 D_807FCC44 split label stays tagged (5110.c:57, Q0687 table-base CSE); D_807FCC40 retired (5adcdc9b).
- ACDC0: D_807FC828..D_807FC838 are one s16[9] collectible-count table; declaring the array changes codegen (text 16 bytes smaller), kept as separate symbols (ACDC0.c:73-78).
- 2F550 MapViewEntries proposal (.scratch/Rev24/header-request.md), held. With it, 55B20 could drop MapChunkArg; renderEntryListBuildDisplayList last parameter s32 vs u8 (owner 35000) blocks the 55B20 mapChunksRender proto-steer (a1232a/19cc66).
- Actor.soundSlots[0] (0x6E) is a frame counter in BC3B0 (beep timing, BC3B0.c:173-176): the shared field name may be too narrow (header owner).
- 55B20 MapZone.tris as MapTriangle * would remove 23 casts (a natural rewrite does not match yet; 55B20.c:352/1468).
- proxPathAdd/proxPathSetSegment -> `s32 id` (optional, ACTIONABLE; like 89ad9a91's proxPathSetEnabled/SetEndBehavior/RemoveActor) would drop 36880's `(Actor *)id` casts (36880.c:792/796); owner 133A90 + caller bundle.
- jetpac/4FC0 `extern JetpacPlayerActor jetpacPlayer` (4FC0.c:44): JetpacState raises its cfe 1 -> 2 (round-34 measurement; 3480 and 1A60 already use JetpacState).
- jetpac/1A60 jetpacUpdatePlayerMovement volatile 1d4065 / 1d4065#2: blocked. Director REJECTED `volatile s32 flying` in jetpac.h JetpacPlayerActor: it only moves a codegen-only volatile into a shared header and hides it. Both sites stay tagged `blocked` (HackjetpacUpdatePlayerMovement, 2026-11-14; evidence .scratch/HackjetpacUpdatePlayerMovement/).
- File-scope view MODEL_TRANSFORM_SLOT0/SLOT (36880.c:1629-1630) and the 36880 views on `ModelSlot.unk20` (model.h:109 `void *`) are blocked on the model.h H1/H2 regeneration (clashes with file-local ModelSlot typedefs). actorBoneChainSwingUpdate near-miss hint in the Rev20A report.
- Optional (types queue, ACTIONABLE): HeapBlock u64 view (heap.h) so 15050's 14 `*(u64 *)blk = 0` / `((u64 *)q)[i]` puns, now `// ORIG:`
  (HackloadOverlay, merge b4eccb1b: target 64-bit pair stores/copies), become typed 64-bit accesses; fdiff each, keep the ORIG
  comments' offsets.
- 1332B0 volumeTriggerUpdate PlayerSlot stride view of gPlayerSlots kept (Q0606, views blocked; 1332B0.c:11 `extern void *gPlayerSlots`, 172-185). Every other file declares `PlayerStruct *gPlayerSlots` (13b5f3b8) except A8400 (ScreenBounds view, next entry).
- PlayerStruct 0x270 s16 bounds carve (ACTIONABLE): actor.h has no scissorUlx..Lry fields; A8400's ScreenBounds (A8400.c:165-174) and MapBounds (447-455, SPRITE_BOUNDS) views read them. Round-16 list still open: playerStateQueueCallback arity (F56F0 14204c, race/6650 8cc620), n_alSndpPostEvent.
- 1025E0 `func_806FDAB8` first param: owner retype to u8, u16 and s32 all fdiff 1 (round 29, CleanBonus2690 retype/owner_*.fdiff), so bonus/2690's local u8 declaration steer (689f58, e3027b) stays. Not actionable.
- gCamActor extern stays `void *` in boss/8520 (8520.c:122) and B100 (B100.c:46) (retyping raises cfe); C920 is `Actor *` (e1dbb7d5). gFrameCounter/gGlobalPauseFlags single shared type.
- boss/0 and ACDC0 (ACTIONABLE): proto-steer `consolidate` rungs staled by the round-18 Actor 0xEC union need fresh agent runs: boss/0 ea31b7 (actorMoveWithinZone, boss/0.c:369), ACDC0 6bd641/01af71 (renderRotatedSprite, now defined in 90D80.c:157).
- Data ownership (HacktransitionSetAudioVolume, 2026-11-14, ledger a001e1ac): carve the .data region of 14C9E0 around D_807550A4
  (today an extern in 10E1D0.c:566; no 14C9E0.c exists) into its owning C file; that enables a Q0498 function-local `static` retry for transitionSetAudioVolume's dead-if 86665d.
- A8400 file-local views of the resqueue.h types (ACTIONABLE): SpriteModel (A8400.c:19), SpriteObjectSlot (263), SpriteFrameNode (436), SpriteActorData (441) -> include/resqueue.h ResGlyph fields. ResQueueActorState's fields are all named (resqueue.h:40-74).
- 8F4B0 CutsceneActorState / WeatherActorState merge (same layout, 8F4B0.c:204/490; needs proof actorCutsceneDispatchEvents runs on actor type 0xC; PolishGlobal8F4B0Names 237b3f89).
- Shared PulseState (ACTIONABLE): BB300's file-local PulseSwayState/PulseSwayActor (BB300.c:20-28) and A6280's file-local PulseState (A6280.c:30) describe the same Actor 0x178 component; one shared type (owner item, check the layouts agree).
- gPlayerPadState header extern (ACTIONABLE): every view and split label is retired (edbcff4c, 2d9d6f67, d873dee6, 7a453f41); add `extern PadInputState gPlayerPadState[];` to actor.h and delete the 12 file-local externs (bonus/2690, 103AB0, 70FD0, 7BBD0, 80150, CC800, CEAE0, D5E10, E4090, F56F0, menu/0, race/7BD0).
- Warning/proto-steer sites with no owner decision yet (audit 2026-11-14, missing blockers M1-M11):
  - 90D80 hudDrawRollingCounter 8c076a: same `retype kept` as f2ca09 (ledger 53b46930) but the record is stale; re-record.
  - 55B20 mapChunksApplyLights W709 5cddbb/b2bbaf (`u8 hit` passed to lightCollectVolumesInBounds' `s8 *`, owner 5E2F0) and W712 18cdf5/#2 (local s32 declaration of func_8065C990).
  - Proto-steers never consolidated or stale: 1025E0 2ed6ea/69fe0c (textGetCharAdvance), 2C910 30698d/41f288/145e04 (textSpawnMarkerChecked + K&R textSpawnSubtitle), 36880 81fdd2/1045f7 (renderReplaceSegment6Commands, playerSlotMatchesSizeMask), B5EC0 72fa9a (actorTrackBoneTowardTarget, consolidate never tried), race/6650 8cc620/3db41f (playerStateQueueCallback, sfxStopSlotSound).
  - Proto-type views: 103AB0 e73d86 (lensFlareDrawSource takes a file-local type), F56F0 14204c (playerStateQueueCallback arity).


## Round-34 leftovers
- Names not applied: MpSettings.unk0 / func_80714608 (mode vs gameMode unclear); func_806C9974 -> playerAddHealthDelta (Rev34C proposal, round-35 names step). Proposals not applied at the 2026-11-14 consolidation (director: keep the existing names for now): collisionGetFloorHeight -> collisionGetWaterHeight, collisionGetFloorTriangleNormal -> collisionCheckLedgeGrab (PolishGlobal6AD90Names; evidence .scratch/close/renames.md rows 104/105). Rejected: Actor.unk155 -> subState (one boss file's evidence for 66 files), D_807FF0F2 -> gAudioHeadphonesEnabled (inferred), Actor.unk15F -> hudMode (C8C10 uses unk15F as a 0x80 flag plus a 0x7F phase counter).
- global/6710 func_80601EE4: noop-arith 8e31ef/8e31ef#2 OPEN next=plain (diagnose nohit HackSmallLeftovers 437b28d1; plain/recipe rungs stale, sweep).

## OPEN functions

The per-file list is `uv run tools/quality.py rank` (full) or `status --file <f>`; the round-34 close snapshot is `.scratch/r34_post_knowledge.txt`.
