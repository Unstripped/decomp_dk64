# Pending after cleanup round 38 (campaign paused by the user)

State after the round-38 close (knowledge commit 7a7ec5c6, Q0754-Q0759): 192 OPEN functions in 117 files. Since then the campaign runs as a rolling queue (SKILL.md §2): a future session starts with `uv run tools/quality.py rank --limit 40` (function hack queue) and `rank --polish` (file polish queue); coverage first. The "Blocked owner/header changes" below are the `TypesOwner` queue (types-stream.md). Audited 2026-11-14 at 7a453f41 (PlanPendingAudit: DONE entries removed; evidence and verdicts in .scratch/PlanPendingAudit/audit.md), re-checked at 74533125: DY ca506697 fixed global/0 f71305 and 450 2e505d (M2, M3), DZ 2e019041 closed every 42630 proto site as ORIG (89a542, M10).

## Blocked owner/header changes
- Owner return-width redesigns (closed, kept as the reason the steer pairs stay): (a) keep `u8 mapGetHubWorldIndex(u8, u8)`
  (OwnerHubWorldIndexWidthPlan: C2A90 func_806BE09C uses v0 unmasked, so the original return is u8); 8F4B0 da5663/2c5186 and
  FCCD0 da5663/06d21a stay FAKE. (b) keep `u8 flagGet(s16, u8)` (OwnerFlagGetWidthPlan: no option passes all 49 files); 80150
  c1a42b/b5496b stay FAKE, jetpac/0's pair is ORIG (0x11d4).
- critter/5110 D_807FCC44 split label stays tagged (5110.c:57, Q0687 table-base CSE); D_807FCC40 retired (5adcdc9b).
- ACDC0 split labels D_807FC82A..D_807FC838 KEPT (OwnerCollectibleCountsView, 0c2a5e64): the table is now one shared `extern s16 D_807FC828[9]` in actor.h (ACDC0, 3E10 and 117190 read it, [0] included), but folding ACDC0's [1]-[8] labels into it makes hudPauseMenuRefreshTotals 16 bytes shorter (.text 20880 vs 20896), so ACDC0 keeps them (ACDC0.c:73-80).
- 2F550 MapViewEntries proposal (.scratch/Rev24/header-request.md), held. With it, 55B20 could drop MapChunkArg; renderEntryListBuildDisplayList last parameter s32 vs u8 (owner 35000) blocks the 55B20 mapChunksRender proto-steer (a1232a/19cc66).
- Actor.soundSlots[0] (0x6E) is a frame counter in BC3B0 (beep timing, BC3B0.c:173-176): the shared field name may be too narrow (header owner).
- 55B20 MapZone.tris as MapTriangle * would remove 23 casts (a natural rewrite does not match yet; 55B20.c:352/1468).
- proxPathAdd/proxPathSetSegment keep `Actor *` (audit A1 CLOSED, kept; OwnerProxPathIdParam, ledgers f3f3f306/956c2dfa/48c9b6b0): with `s32 id`, 133A90 and 9CE20 match (9CE20 needs `(s32)gCurrentActor` x2), but 36880 modelSlotBuildProxPaths fails (frame 0xD8 -> 0xD0, 38 diff rows, also with `(s32)id`). The target sign-extends id once (sll/sra at 0x1584/0x1588), homes it at sp+0x98 (0x15c0) and reloads it for both calls (0x16b0/0x17c0), so 36880's two `(Actor *)id` casts (36880.c:792/796) are original. The `s32` siblings (89ad9a91) match their callers' value types.
- jetpac/4FC0 `extern JetpacPlayerActor jetpacPlayer` (4FC0.c:44): JetpacState raises its cfe 1 -> 2 (round-34 measurement; 3480 and 1A60 already use JetpacState).
- jetpac/1A60 jetpacUpdatePlayerMovement volatile 1d4065 / 1d4065#2: blocked. Director REJECTED `volatile s32 flying` in jetpac.h JetpacPlayerActor: it only moves a codegen-only volatile into a shared header and hides it. Both sites stay tagged `blocked` (HackjetpacUpdatePlayerMovement, 2026-11-14; evidence .scratch/HackjetpacUpdatePlayerMovement/).
- File-scope view MODEL_TRANSFORM_SLOT0/SLOT (36880.c:1629-1630) and the 36880 views on `ModelSlot.unk20` (model.h:109 `void *`) are blocked on the model.h H1/H2 regeneration (clashes with file-local ModelSlot typedefs). actorBoneChainSwingUpdate near-miss hint in the Rev20A report.
- Optional (types queue, ACTIONABLE): HeapBlock u64 view (heap.h) so 15050's 14 `*(u64 *)blk = 0` / `((u64 *)q)[i]` puns, now `// ORIG:`
  (HackloadOverlay, merge b4eccb1b: target 64-bit pair stores/copies), become typed 64-bit accesses; fdiff each, keep the ORIG
  comments' offsets.
- 1332B0 volumeTriggerUpdate PlayerSlot stride view of gPlayerSlots kept (Q0606, views blocked; 1332B0.c:11 `extern void *gPlayerSlots`, 172-185). Every other file declares `PlayerStruct *gPlayerSlots` (13b5f3b8) except A8400 (ScreenBounds view, next entry).
- PlayerStruct 0x270 s16 bounds carve (ACTIONABLE): actor.h has no scissorUlx..Lry fields; A8400's ScreenBounds (A8400.c:165-174) and MapBounds (447-455, SPRITE_BOUNDS) views read them. Round-16 list still open: playerStateQueueCallback arity (F56F0 14204c, race/6650 8cc620), n_alSndpPostEvent.
- 1025E0 `func_806FDAB8` first param: owner retype to u8, u16 and s32 all fdiff 1 (round 29, CleanBonus2690 retype/owner_*.fdiff), so bonus/2690's local u8 declaration steer (689f58, e3027b) stays. Not actionable.
- gCamActor: one `extern struct Actor *gCamActor` in actor.h (OwnerCamActorExtern e13ffda6; boss/8520 and B100 retyped from `void *` with cfe unchanged; the last file-local copies dropped in 7748c62b). gFrameCounter/gGlobalPauseFlags single shared type.
- ACDC0 renderRotatedSprite proto-steer 6bd641/01af71 kept (HackConsolidateBoss0ACDC0, ledger 9ca52aed): the owner's s32 siz only changes CSE of the literal 2 (li a3,2 -> move a3,s8 at 0x1638/0x16B8). That is register-only evidence, not ORIG. boss/0 ea31b7 is ORIG (70242923).
- Data ownership (HacktransitionSetAudioVolume, 2026-11-14, ledger a001e1ac): carve the .data region of 14C9E0 around D_807550A4
  (today an extern in 10E1D0.c:566; no 14C9E0.c exists) into its owning C file; that enables a Q0498 function-local `static` retry for transitionSetAudioVolume's dead-if 86665d.
- 8F4B0 CutsceneActorState / WeatherActorState merge (same layout, 8F4B0.c:204/490; needs proof actorCutsceneDispatchEvents runs on actor type 0xC; PolishGlobal8F4B0Names 237b3f89).
- Warning/proto-steer sites with no owner decision yet (audit 2026-11-14, missing blockers M1-M11):
  - 90D80 hudDrawRollingCounter 8c076a: same `retype kept` as f2ca09 (ledger 53b46930) but the record is stale; re-record.
  - 55B20 mapChunksApplyLights W712 18cdf5/#2 (local s32 declaration of func_8065C990); its W709 5cddbb/b2bbaf are fixed (lightCollectVolumesInBounds `u8 *outFlag`, OwnerLightCollectOutFlag 09fd75a7).
  - Proto-steers never consolidated or stale: 1025E0 2ed6ea/69fe0c (textGetCharAdvance), 2C910 30698d/41f288/145e04 (textSpawnMarkerChecked + K&R textSpawnSubtitle), 36880 81fdd2/1045f7 (renderReplaceSegment6Commands, playerSlotMatchesSizeMask), B5EC0 72fa9a (actorTrackBoneTowardTarget, consolidate never tried), race/6650 8cc620/3db41f (playerStateQueueCallback, sfxStopSlotSound).
  - Proto-type views: 103AB0 e73d86 (lensFlareDrawSource takes a file-local type), F56F0 14204c (playerStateQueueCallback arity).


## Round-34 leftovers
- Names not applied: MpSettings.unk0 / func_80714608 (mode vs gameMode unclear); func_806C9974 -> playerAddHealthDelta (Rev34C proposal, round-35 names step). Proposals not applied at the 2026-11-14 consolidation (director: keep the existing names for now): collisionGetFloorHeight -> collisionGetWaterHeight, collisionGetFloorTriangleNormal -> collisionCheckLedgeGrab (PolishGlobal6AD90Names; evidence .scratch/close/renames.md rows 104/105). Rejected: Actor.unk155 -> subState (one boss file's evidence for 66 files), D_807FF0F2 -> gAudioHeadphonesEnabled (inferred), Actor.unk15F -> hudMode (C8C10 uses unk15F as a 0x80 flag plus a 0x7F phase counter).
- global/6710 func_80601EE4: noop-arith 8e31ef/8e31ef#2 OPEN next=plain (diagnose nohit HackSmallLeftovers 437b28d1; plain/recipe rungs stale, sweep).

## OPEN functions

The per-file list is `uv run tools/quality.py rank` (full) or `status --file <f>`; the round-34 close snapshot is `.scratch/r34_post_knowledge.txt`.
