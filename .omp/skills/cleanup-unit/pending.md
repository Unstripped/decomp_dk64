# Pending after cleanup round 30

State at the round-30 knowledge commit (0ebf89ca): 170 OPEN functions in 106 files (next rung: review 82, permute 44, diagnose 27, retype 6, consolidate 6, views 3, reconstruct 2). The knowledge commit (Q0699) staled 6 functions (15 codegen rungs; not re-recorded). Re-review groups Rev30A (7 files, 19 functions) and Rev30B (7 files, 19) in `.scratch/rereview30.md` at e8842b50 were not run. A future session starts here: `uv run tools/quality.py rank`, then SKILL.md §2.

## Blocked owner/header changes
- Cast sweep (round 30): 55B20 MapChunk.lastSeenFrame and 61AA0 BillboardCacheEntry.lastUsedFrame stay s32 (u32 retype fdiff 1). model.h/heap.h frame stamps landed u32 after Rev29.
- boss/3840 `bossSpawnParticleRing` K&R -> `(u16, s16, s16, s16, s16, u8)` (DAA0 header request): callers boss/0, 52B0, 6240, F0D0 need stand-ins.
- boss/DAA0 bossSpawnerUpdate proto-steers c617f1 and 263392 (bossSpawnParticleRing local `(u16, s16, s16, s16, s16, u8)`) wait on a boss/3840 owner retype, or stay (sfx int bit-pattern args).
- 90D80 renderRotatedSprite proto-steer (02809d, 0d85ab) stays: the 103AB0 owner is 32-bit by its own asm (texWidth forwarded in a3 without andi, texHeight read with lw 0x60(sp)); a u8 owner adds andi/lbu. Closed as not applicable (round 29, dbf5cc61: owner texWidth/texHeight u32 instead).
- critter/5110 D_807FCC40/44 split labels stay (round 27, def29e0b): folding them into gPlayerInventoryTable fails because the folded form shares one table base (Q0687); the u8 pun is now `extern u16 D_807FCC40[]`, tagged.
- ACDC0: D_807FC828..D_807FC838 are one s16[9] collectible-count table; declaring the array changes codegen (text 16 bytes smaller), kept as separate symbols.
- 2F550 MapViewEntries proposal (.scratch/Rev24/header-request.md), held.
- Actor.soundSlots[0] (0x6E) is a frame counter in BC3B0 (beep timing): the shared field name may be too narrow (header owner).
- 55B20 MapZone.tris as MapTriangle * would remove 23 casts (a natural rewrite does not match yet); mapChunksRender never reviewed (blocked on 2F550 MapViewEntries + 35000 renderEntryListBuildDisplayList u8).
- arcade/0: tag the same `i += 0x24` hack in arcadeSpawnStage3Entities.
- proxPathAdd/proxPathSetSegment -> `s32 id` (optional) would drop 36880's `(Actor *)id` casts.
- D_807552E4 MpSettings: different views in 117190, CC800, CEAE0, menu/3E10 (shared type needed).
- Shared MapViewEntries (owner 2F550, 0x8 = dl) would let 55B20 drop MapChunkArg; renderEntryListBuildDisplayList last parameter s32 vs u8 (owner 35000) blocks the mapChunksRender proto-steer.
- jetpac/4FC0 `extern JetpacPlayerActor jetpacPlayer`: JetpacState raises its cfe 1 -> 2 (3480 and 1A60 already use JetpacState).
- gActiveActors/gActiveActorCount: file-local externs in 33 files (header move candidate, actor.h).
- 42630 csCmdExec proto-type 89a542 (hudSpawnCountdownTimer arity, owner A7710) and W712 3ae317 (effectCreateAtModelNode, owner 119370); 450 2e505d actorMapModelsSetup. Round 27: 8D3E0 kept actorMapModelsSetup(s32, u8, u8) (not resolved).
- Extern unification left: gPlayerSlots keeps void * in 1025E0, 10E1D0, 11BC10, 12E800, 1332B0, 2C910, F93B0, FCCD0, u8 * in 9BF30, s32 in 9DD70, plus 17 file-local view types (retire the views first).
- File-scope views: PLAYER_VIEWS (450), ModelSlotPosTypeView (936B0), MODEL_TRANSFORM_SLOT (36880), TagBarrelInputPad (80150, needs a shared pad type); actorBoneChainSwingUpdate near-miss hint in the Rev20A report.
- String convention (W709, string literals passed to `u8 *`): jetpac/4FC0 6c4893, global/90D80 renderHitCounterHUD/hudDrawRollingCounter, global/C0EE0 func_806BCF98 are blocked on 100180 `textDrawStringVtx`/`textDrawString` taking `u8 *` (the text API reads unsigned bytes, `*str++`). Decide one convention (e.g. `char *` parameters with an unsigned read) and fix all callers in one batch.
- 1332B0 volumeTriggerUpdate PlayerSlot stride view of gPlayerSlots kept (Q0606, views blocked).
- 11BC10 `effectFallStateInit(Actor *, EffectNode *, u8 *)` (19A00 warnings 5bc221 ×3).
- 119370 `effectCreateAtModelNode(s32 asset, f32, s32, s32, u8)` (42630 warning 3ae317); Rev17P: effectGridFindByTargetId/effectCreate return `EffectGridAsset *`, TimedLightActorView → EffectNode, sEffectPending* names.
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


## OPEN functions (file (count): function(next rung))
- bonus/2690.c (1): bonusPerilPathPanicGameUpdate(reconstruct); boot/3D20.c (1): vsprintf(diagnose); boss/0.c (2): bossArmydilloAimTowardTarget(diagnose), bossArmydilloStep(review); boss/B100.c (1): bossDogadonStep(review)
- boss/DAA0.c (1): bossFollowerActorUpdate(permute); boss/F0D0.c (2): bossPickWaypointStep(permute), bossSetRandomObjectPair(diagnose); critter/3340.c (1): critterBananaFairyUpdate(diagnose); critter/5110.c (1): critterBattleArenaUpdate(diagnose)
- global/0.c (2): globalInit(retype), mainThreadHalt(review); global/100180.c (2): textBlitGlyph(permute), textDrawStringVtx(diagnose); global/10130.c (2): func_8060B430(review), recordInitPositionBuffers(permute); global/104F0.c (1): eepromClearSlotData(permute)
- global/10D2D0.c (1): healthRefill(permute); global/10E1D0.c (1): meshBlobParse(permute); global/112080.c (2): resParseVariant(diagnose), textLayoutAppendCommandList(review); global/1135F0.c (2): dlAppendTextureLoad(review), dlAppendTextureRectangle(review)
- global/117190.c (2): playerRefillHealth(permute), func_807135B4(permute); global/119370.c (2): effectCreateAtActorBone(permute), effectUpdateAll(diagnose); global/126260.c (1): commandApplyToLight(diagnose); global/127B00.c (1): pathPlaybackAdvance(diagnose)
- global/1292F0.c (2): pathFollowUpdateHeading(review), animationOwnerFreeBuffer(review); global/12E800.c (1): enemyAggroStateUpdate(diagnose); global/1332B0.c (1): volumeTriggerUpdateAll(diagnose); global/137120.c (2): alHeapInit(review), alHeapDBAlloc(review)
- global/13980.c (1): schedHandleRetrace(permute); global/13A750.c (1): alCSPSetBank(review); global/13A7A0.c (1): __n_sndpPostPitch(permute); global/13C920.c (2): configureCSPOutputMode(review), updateCSPOutputChannelMode(review)
- global/13CB30.c (1): alCSPGetState(review)
- global/13CE70.c (3): alCSPSetChlFX1Mix(review), alCSPSetChlPanVolume(review), alCSPSetChlFX2Mix(review)
- global/13CFA0.c (1): alCSPSendMidi(review); global/13D020.c (1): alCSPSetTempo(review); global/13D0B0.c (1): alCSPGetTempo(review); global/13D100.c (1): postCSPChannelCommand(review)
- global/13E0E0.c (2): alLink(review), alUnlink(review); global/13EC00.c (2): alSeqpStop(review), alSeqpSetSeq(review); global/13EC90.c (1): alSeqpSetVol(review); global/141E40.c (1): n_alSynDelete(review)
- global/141EF0.c (1): n_alFxPull(permute); global/1435A0.c (1): n_alSynSetPriority(review)
- global/14CF0.c (3): func_8060FFF0(review), schedSubmitGfxTask(review), func_80610268(review)
- global/16550.c (2): acosApprox(review), asinApprox(review); global/169F0.c (2): truncateFloat(review), floatToS32(review)
- global/16A20.c (3): mathFixedPointInterp(review), acosFixed16(review), asinFixed16(review)
- global/17B40.c (1): floatCeil(review); global/17B90.c (1): gfxSwapGeometryModeCullBits(permute); global/19A00.c (2): projectileTrySpawnFromSlot(diagnose), scriptCmdSpawnFallingEffect(review)
- global/201B0.c (3): camApplySway(review), camFloorSnap(review), camComputeEyeFocus(permute)
- global/2C700.c (2): splineEvalCubic(review), splineSetBasisTension(review); global/2C910.c (2): textSpawnSubtitle(reconstruct), camPathCommandDispatch(review); global/2F550.c (1): mapBspPlaneDistanceCheck(permute); global/35000.c (1): renderEntryListBuildDisplayList(consolidate)
- global/36880.c (2): renderModelAnimatedSlot(consolidate), modelPendingQueueInsert(diagnose); global/42630.c (2): csCondEval(diagnose), csCmdExec(views); global/450.c (2): mainSystemInit(diagnose), mapLoadLevel(retype)
- global/5230.c (3): frameTimingGetMapIndex(review), frameTimingReset(review), frameTimingUpdate(review)
- global/54150.c (2): modelAnimEntryBuildNodeMatrices(retype), modelAnimEntryQueueMatrixCopies(permute)
- global/55B20.c (5): mapChunkUpdateAssetStreaming(review), mapSearchTableReset(review), mapSearchTableAddProbe(review), mapSearchTableUpdateVisibility(review), mapSearchTableGetValue(review)
- global/61AA0.c (6): billboardCacheEvictStale(review), billboardSubmit(permute), matrixCacheInit(review), matrixCacheLookup(review), matrixCacheInsert(review), matrixCacheEvict(review)
- global/63EC0.c (1): effectWaterInitNodes(permute); global/6710.c (2): audioThreadInit(diagnose), audioBuildTask(permute); global/67890.c (1): actorTargetTableLoad(review); global/68960.c (1): mapUpdateFogDistance(review)
- global/68EA0.c (1): modelEmitterSpawnScaledParticle(permute); global/699B0.c (2): particleFindPathIndices(review), particleSpawnPathTrail(review); global/6AD90.c (2): collisionTestGridMeshHeight(permute), dynamicBufferPurgeExpired(review)
- global/70FD0.c (5): collisionInitStaticCache(review), collisionLoadStaticCell(review), modelSlotExpireNextBuffers(review), collisionPurgeExpiredBuffers(review), actorUpdateNodePositions(permute)
- global/7130.c (2): sfxUpdateChannels(permute), sfxCalcDistanceVolumePan(permute)
- global/7A510.c (3): actorCollisionProcessHit(review), actorCollisionRunInteractionTable(diagnose), actorCollisionFindTableEntry(diagnose)
- global/7AF60.c (1): func_80676C10(diagnose); global/7BA00.c (1): actorTriggerPlayerKnockbackSound(review); global/7BBD0.c (1): actorCollisionResolveSurfaceHit(diagnose); global/7CA80.c (1): actorAllocate(permute)
- global/80150.c (2): tagBarrelCheckKongFlag(permute), tagBarrelRenderSelectionHud(review); global/89250.c (1): effectSpawnJointBeam(consolidate); global/8CA50.c (1): animNodeAdvanceTime(permute); global/8F050.c (1): actorConfigLookup(diagnose)
- global/8F4B0.c (1): actorCutsceneDispatchEvents(consolidate)
- global/90D80.c (3): renderRotatedSprite(consolidate), renderHitCounterHUD(retype), hudDrawRollingCounter(retype)
- global/936B0.c (3): func_8068F72C(permute), projectileParticleSpawnerTick(review), projectileHomingParticleUpdate(review)
- global/A2F10.c (1): actorLightPulseUpdate(permute); global/A8400.c (1): textBoxUpdateRows(permute); global/ACDC0.c (1): hudPauseMenuUpdate(permute); global/B1F60.c (1): actorPatrolFollowerUpdate(permute)
- global/B2CE0.c (1): func_806AE588(views); global/B5EC0.c (1): func_806B13B4(review); global/BB300.c (1): func_806B6958(views); global/C0EE0.c (2): enemyGridStateStep(permute), func_806BCF98(retype)
- global/C1E70.c (1): actorNodeRingUpdate(permute); global/C4620.c (2): actorScriptedCommandUpdate(diagnose), func_806C151C(permute); global/CEAE0.c (1): func_806CF580(review); global/D5E10.c (2): playerStateApproachVelocity(permute), playerStateDialogueHold(review)
- global/E4090.c (1): playerTurnByStickX(permute); global/F4C0.c (1): mapActionLookupEntry(review); global/F56F0.c (1): playerStateWaypointAimUpdate(permute); global/F600.c (1): controllerUpdate(diagnose)
- global/F93B0.c (1): mapGetVoidHeightForCharacter(review); global/FE40.c (1): dmaReadAssetDecompress(review); jetpac/0.c (2): jetpacStateGameplay(permute), jetpacStateGameOver(consolidate); jetpac/4FC0.c (2): jetpacActorInitWander(review), jetpacActorUpdateWander(review)
- menu/E550.c (1): menuRenderOptionDescription(permute); minecart/25F0.c (1): minecartUpdateObstacleType3(permute); race/36B0.c (1): raceOpponentCarBehaviorUpdate(diagnose); race/52B0.c (1): raceOpponentRacerBehaviorUpdate(permute)
- race/7BD0.c (2): raceRenderSpeedBoostHud(permute), raceRenderCoinHud(review); race/A960.c (2): raceGetRoute(diagnose), raceUpdateWaypointActivation(diagnose)
