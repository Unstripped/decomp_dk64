# Cleanup pending (unresolved items only; checked against the tree at f13156f0, 2026-11-18)

Open functions come from `uv run tools/quality.py rank` / `rank --polish` (SKILL §2) or `status --file <f>`. This file keeps what
`rank` cannot show: the `TypesOwner` queue (`.omp/skills/cleanup-unit/types-stream.md`: oldest first, skipping HELD/PARKED items), director rulings, held
names and tooling fixes. Delete an item once it lands (git and `drafts/cleanup/sessions.md` keep the history); a closed decision keeps one outcome line.

## Blocked owner/header changes (`TypesOwner` queue)
- NEXT batch (director 2026-11-18: one batch, not now): (1) PlayerState 0x220..0x228 -> `f32 unk220[3]` removes 478F0
  csCmdCameraVectorTargetUpdate abbd3b. Request .scratch/CleancsCmdCameraVectorTargetUpdateb/header-request.md; patches
  fix/actor_h.patch + fix/D5E10.patch + fix/E4090.patch, copies fix/{478F0,D5E10,E4090}.c at 2291c741, shadow_fdiff.sh. Users
  D5E10 playerInputHandleBButtonPunch/func_806DF280, E4090 playerInputCheckBButtonTarget. Field TYPE change: measure the
  PlayerState stale cost first, gate with the 478F0 body. (2) JetpacSprite (jetpac.h) == TextureDescriptor (render.h) field for
  field: merge them, then retype dlAppendTextureLoad's `void *texture` (callers arcade/0.c, jetpac/1460.c:151; CleandlAppendTextureLoadb).
- Actor.soundSlots[0] (0x6E) is a frame counter in BC3B0 (beep timing, BC3B0.c:172): the shared field name may be too narrow.
- 55B20 file-local MapZone (55B20.c:350): `tris` as `MapTriangle *` would remove 23 casts; a natural rewrite does not match yet.
- 36880 views on `ModelSlot.unk20` (model.h:109 `void *`, ModelKindObj users): blocked on the model.h H1/H2 regeneration (clashes
  with file-local ModelSlot typedefs); actorBoneChainSwingUpdate near-miss hint in the Rev20A report.
- 8F4B0 CutsceneActorState / WeatherActorState merge (same layout, 8F4B0.c:203/485): needs proof that actorCutsceneDispatchEvents
  runs on actor type 0xC (PolishGlobal8F4B0Names 237b3f89).
- B5EC0 72fa9a actorTrackBoneTowardTarget proto-steer (owner 1295B0 takes one u8): no owner decision yet (audit 2026-11-14, M1-M11).
- effectSetSpeed(s32) receives an actor pointer (race/1770.c:330 `(s32)gCurrentActor`) and an index (boss/0): owner type review.
- Not run (2026-11-14b): RaceParticipant 0x25/0x26 racer-side aliases (boostTimer/boostPending; manager names hasCpuRival/route);
  one shared VehicleActor (936B0.c:575) / RaceCompetitorActor (race/52B0.c:35) in race.h; 36880 TexImageCmdSpan as a Gfx[] view
  (G_SETTIMG/G_SETTILESIZE, file scope); jetpac/0.c:442 open-coded BUTTONS_PRESSED; CC800 `heldButtonsPtr` holds
  &gPadPressedButtons[i] (pressed, not held: field rename).
- 13980 `extern u32 gFramebuffers[]` -> `u16 *gFramebuffers[]` (Polishglobal13980Rereview 3c2f89d7): blocked on 136820's
  `faultFontInit(s32, s32, s32)` prototype.
- ucode symbols: 6710.c/14CF0.c D_80760590, D_805FB000, D_805FB0D0, func_80741310 are the rsp/asp symbols include/PR/ucode.h
  declares (aspMainDataStart, rspbootTextStart/End, aspMainTextStart; `long long[]`): replace the externs (rename.py refuses
  names in scope).
- ACDC0 `s16 D_807505A4[10]` (ACDC0.c:122) is two s16[5] tables: split it (touches undefined_syms, 478F0/FCCD0).
- One shared lerp macro for 201B0 `CAM_LERP` (201B0.c:286) and 478F0 `LERP` (478F0.c:2908); gTextFontSheets `void **` -> `u8 **`
  (100180.c:79, Polishglobal100180).
- jetpac 0x8002BA80 Gfx split: the `jetpacInitPending` splat label (jetpac/0.c:404) spans a gSPEndDisplayList.
- jetpac shared head (PARKED; CleanjetpacUpdatePlayerMovement, ledger 7d1cc6e8): embed one 0x30-byte head struct in JetpacActor
  and JetpacPlayerActor. `player->head.x` compiles like the plain body; only a `head = &player->head` local used for EVERY head
  access matches, so it retires 1A60 ba285d only if that local is ruled ordinary C (`.omp/skills/cleanup-unit/rulings.md` pointer-local precedent: 450
  firstSetupFlag). It touches every head-field access of JetpacPlayerActor.
- F9450 ModelAssetEntry (0x30, map model asset table 9; identical copies in 36880.c:33-49 and F9450.c, modelAssetGetSubtables):
  move it to include/model.h and drop both copies (merge_drafts prunes identical typedefs). DEFERRED (director turn 164); evidence
  .scratch/PolishglobalF9450/header-request.md. gridBuildNodeLists / gridCollectActorsInRange keep `views blocked` until it lands.
- HeapBlock allocated-block tag (HOLD, director; .scratch/CleanheapRegisterSurvivor/header-request.md): byte 0x0B is the low byte
  of `next` while free and the tag while allocated (0 normal, 1 locked, 2 survives an overlay load). Every access is a byte view
  (`((u8 *)p)[0xB]` in heapInitGeneralPool, heapInitBlockPool, heapReleasePool, heapFree, heapFreeDeferred,
  heapRegister/UnregisterSurvivor; `ptr[-5]` in heapLockBlock/heapUnlockBlock). An anonymous union adds cfe W838 + W649 per
  declaration; a named one rewrites all 28 `->next` in 15050.c. Only as a file-wide polish/types pass.
- 7130 D_80770DD9 (undefined_syms.us.txt:341) stays while 7130.c:853 stores through it (FAKE linker alias of D_80770DD8[1]).
- Declaration consistency: 13980 `extern s8 D_80744510` (lb 0x620) vs 450.c:142 `u8 D_80744510[28]`; gMinigameCoinCount `s16`
  (bonus/0, 450, minecart/0, race/1770, race/A960) vs `u16` (FCCD0, race/0); D_80720340 `u8`/`u8[]`/`s32` (478F0, 80150, 936B0,
  9DD70, B6C50, race/1770; held name gSmokePuffSprite: unify the type first).

## Closed or held by ruling (reopen only with the new evidence named)
- Return widths: keep `u8 mapGetHubWorldIndex(u8, u8)` (OwnerHubWorldIndexWidthPlan: C2A90 func_806BE09C uses v0 unmasked) and
  `u8 flagGet(s16, u8)` (OwnerFlagGetWidthPlan: no option passes all 49 files; jetpac/0's pair is ORIG, 0x11d4).
- ACDC0 split labels D_807FC82A..D_807FC838 KEPT (OwnerCollectibleCountsView 0c2a5e64; ACDC0.c:75): folding them into actor.h's
  `D_807FC828[9]` makes hudPauseMenuRefreshTotals 16 bytes shorter.
- proxPathAdd/proxPathSetSegment keep `Actor *` (OwnerProxPathIdParam; ledgers f3f3f306/956c2dfa/48c9b6b0): `s32 id` fails 36880
  modelSlotBuildProxPaths (frame 0xD8 -> 0xD0); the target homes id once at sp+0x98 and reloads it, so 36880.c:790/794's
  `(Actor *)id` casts are original.
- 1332B0 volumeTriggerUpdate keeps `extern void *gPlayerSlots` (1332B0.c:11) for its PlayerSlot stride view (Q0606, views blocked).
- PlayerStruct.rect[4] (sched.h) scissor-field rename HELD: named fields flip textBoxRender's `|` chain order (Q1082).
- HeapBlock u64 view for 15050's 14 `// ORIG:` pair puns DECLINED (TypesOwner9 batch_9 part J): no hack site gained, alignment
  4 -> 8 (clint TYPES LAYOUT BAD), defeats `--header-carve`, reopened 15 functions. Retry only with a new form.
- CollisionBoxTri shared struct (collision.h) DROPPED (TypesOwner5 batch_5 Part A; probes .scratch/TypesOwner/batch_5/partA_req/,
  partA_alt/): scalar x0..z2 needs a pun in 70FD0, x[3]/y[3]/z[3] fails fdiff in 6AD90. Reopen only with a shape that fdiffs in both.
- FE40 0b7e03/#2 PERMANENT DEBT (director 2026-11-17d, `retype kept`, ledger 70e3f1e4): `void *dst` is polymorphic; `u8 *dst`
  raises W709 at 9 caller args (5A50 4, 6AD90 5) and gunzip's `void **outBufPtr` needs a pun. Probes .scratch/PolishglobalFE40/.
- 11BC10 effectInterpolationUpdate 6e5dc3 DECLINED (director; CleaneffectInterpolationUpdate, merge 45e10058): an `f32 *` interp
  with enum slot indices matches (.scratch/CleaneffectInterpolationUpdate/render_interp_f32.patch, typed_standin_11BC10.c) but is a
  view chosen for codegen. Retry only with new type evidence.
- A8400 textBoxRender scissor d5a412 REFUSED (director turn 162): the plain gDPSetScissor gives fdiff 1; an anonymous union over
  ResQueueActorState.boxLeft..boxBottom (cfe W838/649) or an `f32 box[4]` exists only to steer it. Retry only with another user or
  asset-layout evidence (.scratch/PolishglobalA8400/header-request.md, resqueue.patch hunk 2, shadow/resqueue.h).
- D1 TERMINAL (director 2026-11-18): the menu/3E10 `(void *)(s32)&D_80721444` cast family (menuInitMainScreen 5,
  menuInitAdventureFileSelect 3, 3E10.c:738) keeps `void *` + 9 FAKE casts: an `s32` asset parameter on menuSpawnUiElementEffect
  costs W712 0 -> 68, a `u8 *asset` local scores full=28 (.scratch/TypesOwner/batch_12/partR_plan.md,
  .scratch/Lead20261118/probe3E10; recorded 9f83bf7c).
- D2 HOLD (director 2026-11-18): ACDC0 hudPauseMenuUpdate, 4 FAKE EXHAUSTED (c127b7 page and db430c credits reuse sel; 6151e7
  limit and 32c920 half reuse flag, pinned by register colouring; every variant in
  .scratch/CleanhudPauseMenuUpdate/dossier_global_hudPauseMenuUpdate.md, merge 54a784f8). No dispatch without a new lever;
  frame-capacity ORIG declined (ladder.md home-slot rule).
- 7130 70c91e `if (D_80770DC8) {}` (7130.c:1045): a function-local static lands at 0x80770F38 (IDO .bss first-reference order;
  .scratch/CleansfxUpdateLevelAmbient/carve/carve_7130.txt §4, merge 08e85d18). Retry only with a new .bss-order lever.
- Names kept (director 2026-11-14): collisionGetFloorHeight, collisionGetFloorTriangleNormal (proposals collisionGetWaterHeight,
  collisionCheckLedgeGrab: .scratch/close/renames.md rows 104/105). Rejected: Actor.unk155 -> subState/stateTimer, D_807FF0F2 ->
  gAudioHeadphonesEnabled (inferred), Actor.unk15F -> hudMode (C8C10: 0x80 flag + 0x7F phase counter), D_80035B38 ->
  gBossSavedPlayerUnk144 (address-shaped; boss/DAA0 saves gPrimaryPlayerActor->unk144 there).

## Hack items
- READY, not dispatched (re-set the base at dispatch: .scratch/Lead20261118/items/*.json + mkbrief.py): BDEE0
  behaviourFairyInitPlayerScale goto, jetpac/1460 jetpacGridAddTiledSprite, boot/1630 noExpPakThread, 8F4B0
  lightUpdateFromActorLighting + playerCameraUpdateFromTarget (new agent name: CleanlightUpdateFromActorLightingb was cancelled on
  a model fallback, nothing merged).
- 6AD90 f64 midpoint reuse a2d087 (box) and 3aa4ac (collisionCheckTriangleContainsPointXZ) stay FAKE: the frame holds only ten f64.
- Polish: 103AB0 playerViewDrawScopeCrosshair `(u16)targetKind` is redundant under the ANSI u16 prototype (dd98f7bb).

## Held names (a field rename reopens the review of every touched function: batch them with the next types item, lead review each)
Lists: .scratch/Lead20261118/names17f.txt (17f proposals), names_close.tsv (close submissions; names_applied.tsv applied,
names_failed.txt refused), .scratch/lead_s1115/names.md, .scratch/lead_s1115c/close.md, .scratch/CleanupLead/close-2026-11-16-closed.md.
- PlayerState: unk50 gravityDelayFrames (read D5E10 first), unk78/unk7C/unk80, unkC2 slopeFrames (D5E10/EFDC0 unread), unk11C
  swimStrokeTimer vs stateTimer (EFDC0 unread), unk1A0 aimPitch (936B0/CC800/D5E10 unread); every 17f field list
  (PlayerState/PlayerStruct/ActorGlobalState/ModelSlot/ModelAnim*/Jetpac*/HealthHud); PlayerStruct.unk2C0 sizeMode.
- RaceParticipant: unk1C frameTimer, unk35 (statusStep/finishStep/subPhase), unk3A (route position that wraps and bumps the lap:
  waypointIndex/routePos/checkpoint), unk40 (holds a normal and a squared distance: not "Sq"), unk44 (missesLeft/gateMisses,
  counts down), unk45 (outOfRace/eliminated/disqualified).
- Actor: unkF2 arcPushYaw (69E60/80150 unread), 0xE4 pitch <-> 0xE8 roll swap (HackvehicleUpdateMotion4; confirm across users),
  unk155 (low). ActorGlobalState: unk15 hitType (boss files unread), unk24/25/28/F0/F4 grab/hold and the other 9DD70-only fields,
  unk2C/30/34/36 launchPending/launchSpeedY/launchSpeedXZ/launchYaw (80150 unread).
- CamState unkA0 followDist (a reference inside CAM_MIN: rename every dry-run position by hand), unkA4 followDistGoal (201B0);
  ActorCallbackNode callback (anonymous union: types item), unk4 subtype, unkC ownsPayload, unk10 payload (confirm users);
  ModelSlot unk86 modelKind (63810 unread), unk8C stateFlags; SchedStruct.unk280 tickCount (8 files unread, 91 uses);
  SpawnNode.unk38 animSpeedScale (boss/0, 12E800 unread); KongInventory.unk5; CollisionTriF unk24/unk25 slopeType/surface;
  BehaviourWorkState.unk2E sfxCooldown (dry run touches 11 unread files); MpSettings.unk0 (mode vs gameMode; reader mpIsMatchType).
- Globals: D_80753354 (s16 per-kong turn rate, CC800/E4090; gKongTurnRate is CEAE0's other table: pick a use-based name),
  D_8076A0A6 (copy of gPadPressedButtons[0]), D_80757044/D_80757064 (default high-score tables), D_807FC952
  (= gPlayerInventoryTable[0].kong[0].weaponFlags; cannot fold), D_80744544 gCheatFlags, arcade/0 D_8004BCD0 entity table,
  race/0 D_8002FB10/D_8002FB70 route tables (map 0x52 unnamed), 124780 effect sprite symbol_addrs (needs a split).
- Slash-form and uncertain (17f/18): D_807444A8/AC/B0/B4 letterbox, D_800297F0/D_80029830 critter wing vtx, 10130
  func_8060B750/7C4/7D0/6CC, D_80753A08/A18 head heights, effectSpawnDebrisParticles/effectActorCheckGroundScaleSpawn/
  effectSpawnActorScale, gMenuBonusTimer -> gHelmTimer, modelAnimEntrySet*.

## Tooling fixes (open)
- Shadow headers (sfdiff/fdiff.sh/cwarn `--as`): automatically shadow every include/*.h that quote-includes a shadowed header (cpp
  searches the includer's directory first; EG race.h, EI boss.h).
- `permute.py batch` compiles row copies against the current include/: build each row at its base (or re-snapshot copies whose file
  or reached headers changed). The 2026-11-14 backlog in .scratch/permbatch/ (b1114, b1114b, list.tsv rows 45-97) is stale (7 of
  b1114's 9 sites are gone): regenerate with `quality.py permute-candidates` instead of resuming it.
- quality.py `token_meaning` spells an anonymous member's record type with clang's canonical spelling (it embeds the header path),
  so carry never treats a body touching an anonymous-union field as a pure rename (fix: clint.type_sig, or strip the location as
  clint.UNNAMED does; TypesOwner batch_2 lost 6 review rungs).
- objdiff.py text_matches maps symbol_addrs names to absolute addresses on the expected side only and compares own-.bss relocations
  by raw offset: a carve moving a TU's .bss base shows `fdiff --reloc-ok` exit 1 on a matching ROM (the ROM gate decides: GATE_OK 08e85d18).

## Knowledge
- ok-fine architecture/camera "Remaining hacks" is stale: camComputeEyeFocus keeps 3 gotos (two `goto apply_view`, one
  `goto check_target`, Q0591) plus the six step statics sStepEyeX..sStepLookZ (.scratch/s2026-11-17f-knowledge-queue.md line 32).
