# Cleanup pending (unresolved items only; updated in session 2026-11-20 by Lead20261120, close not yet run: see its dispatch.md)

Open functions come from `uv run tools/quality.py rank` / `rank --polish` (SKILL §2) or `status --file <f>`. This file keeps what
`rank` cannot show: the `TypesOwner` queue (`.omp/skills/cleanup-unit/types-stream.md`: oldest first, skipping HELD/PARKED items), director rulings, held
names and tooling fixes. Delete an item once it lands (git and `drafts/cleanup/sessions.md` keep the history); a closed decision keeps one outcome line.

## Blocked owner/header changes (`TypesOwner` queue)
- EffectNode `wobbleRise` LANDED 2026-11-20 (TypesOwner13 batch_14 Part A: f402b9a4 render.h, e1f618fa 11BC10). Open: the 11BC10
  re-carry (`carry --rev e1f618fa^ src/global/11BC10.c`) waits for the tooling fix "tag added to an anonymous typedef'd record =
  unchanged" (director relays the sha); until then 85 11BC10 functions show OPEN. Part B (JetpacSprite -> TextureDescriptor,
  .scratch/TypesOwner/batch_14/partB*.patch, ledger B_jetpac_1460.txt) is gated only after the header_renames alias fix sha.
- batch_15 (TypesOwner14, 2026-11-20, base 69aa18eb) holds the next items: F F9450 ModelAssetEntry -> model.h, G CAM_LERP/LERP +
  gTextFontSheets, H one extern for D_8071FE08 + C4620 duplicate gBehaviourTargetActor, E ACDC0 D_807505A4 split, C 450.c owner
  types (below), D signedness mismatches (below). Remove each item here when its part lands.
- 450.c data owner types (2026-11-18b polish reports): `u8 D_80744510[28]` / `D_80744530[5]` are blobs hiding gMenuReturnContext (0x80744514),
  D_8074451C, D_80744520, D_80744524[], D_80744534, D_80744538, D_8074453C[5]; `u32 D_80744544` is read as s16 (FCCD0 lh, 3E10
  ^=/|=); `D_80744548`/`D_80744568` u32[8] vs MenuHighScoreEntry[] (3E10); `u8 D_8076A0D0[48]` blob covers gMenuScreenSelection and
  gMenuPlayerCharacterSel read as s8 (3E10 lb). Split/retype in 450.c with every user in one gate.
- Declared signedness/type mismatches (one extern per global): gMinigameCoinCount s16 def (CC800) vs u16 reader (FCCD0 slot 11);
  D_807563B4 u8 def vs extern s8 (3E10); D_80746B60 u8 (17B90) vs s8 (117190); D_807463B8 s8 (F56F0) vs u8 elsewhere;
  gActorScriptAnimTable void * (7CA80) vs u16 * (17B90).
- jetpac: `JetpacSprite` is `typedef TextureDescriptor JetpacSprite;` since 6ed65e63: rename its uses (jetpac/0 1, 1460 4, 1A60 5,
  3480 6, 4FC0 8, jetpac.h 4) to TextureDescriptor in one polish pass; the trailing `0` of the 10-value sprite initialisers fills pad14.
- Actor.soundSlots[0] (0x6E) is a frame counter in BC3B0 (beep timing, BC3B0.c:172): the shared field name may be too narrow.
- 55B20 file-local MapZone (55B20.c:350): `tris` as `MapTriangle *` would remove 23 casts; a natural rewrite does not match yet.
- 36880 views on `ModelSlot.unk20` (model.h:109 `void *`, ModelKindObj users): blocked on the model.h H1/H2 regeneration (clashes
  with file-local ModelSlot typedefs); actorBoneChainSwingUpdate near-miss hint in the Rev20A report.
- 8F4B0 CutsceneActorState / WeatherActorState merge (same layout, 8F4B0.c:203/485): needs proof that actorCutsceneDispatchEvents
  runs on actor type 0xC (PolishGlobal8F4B0Names 237b3f89).
- B5EC0 72fa9a actorTrackBoneTowardTarget proto-steer: TERMINAL (director RQ3 2026-11-20): FAKE kept; owner prototype (u8, s32)
  rejected (a1 = sel by residence only: B5EC0.o `move a1,a0` 0x9c0, jal 0x9d8; owner +0x8 `andi a1,a0,0xff`; 37 callers by
  residence). Re-measured 2026-11-20 (Cleanfunc_806B13B4b, 900d6b5c): EXHAUSTED.
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
  .scratch/Lead20261118/probe3E10; recorded 9f83bf7c). RQ1 2026-11-20: stale rungs re-measured only (CleanmenuInitMainScreenb,
  02ea6af1), nohit, EXHAUSTED; terminal debt.
- D2 HOLD (director 2026-11-18): ACDC0 hudPauseMenuUpdate, 4 FAKE (c127b7 page and db430c credits reuse sel; 6151e7 limit and
  32c920 half reuse flag, pinned by register colouring; .scratch/CleanhudPauseMenuUpdate/dossier_global_hudPauseMenuUpdate.md, merge
  54a784f8). RQ2 2026-11-20: re-measured on the merged body (02ea6af1), no new lever (page 7 = cfe's shared switch temp takes v0;
  every split grows the frame 0x58 -> 0x60), EXHAUSTED. A lever not in the dossier goes to the director with offsets before any
  FAKE change. Frame-capacity ORIG declined (ladder.md home-slot rule).
- Hack queue stop (director 2026-11-20): no re-dispatch of EXHAUSTED rank functions without a concrete new lever named in the
  brief (new type evidence or tool route); SKILL §7.
- 7130 70c91e `if (D_80770DC8) {}`: CLOSED 2026-11-18b (CleansfxUpdateLevelAmbientc, ec3c9426): Q1470 lands the function-local
  static at 0x80770DC8 only with N = 160 (mod 256) extra numbered definitions; no natural count. Reopen only with another lever.
- 80150 tagBarrelActorUpdate 71b822 empty `default: break;`: FAKE (2026-11-18c M19, 9de100e7): the not-2 edge `bne` 0x58fc goes straight
  to the latch 0x5928, no own block, so the empty-default rule keeps it a steer (already tagged).
- 6AD90 f64 midpoint reuse a2d087 (box) and 3aa4ac (collisionCheckTriangleContainsPointXZ) stay FAKE (2026-11-18c M21, 47fa703b): the
  local area is exactly 96 bytes (88 of f64 + int i + the switch temp); an eleventh f64 fits only by byte-packing the ints (22 lines of
  width code). Reopen only with a shape that keeps both the frame and int widths.
- 9DD70 actorCheckAlwaysFalse e999c8 `case 6: case 7:` stays ONE FAKE (R8, director 2026-11-18c): no 6/7 compare in the target
  (0x16e0-0x1754); no restore of the pre-merge sites c56038/0641d2.
- Names kept (director 2026-11-14): collisionGetFloorHeight, collisionGetFloorTriangleNormal (proposals collisionGetWaterHeight,
  collisionCheckLedgeGrab: .scratch/close/renames.md rows 104/105). Rejected: Actor.unk155 -> subState/stateTimer, D_807FF0F2 ->
  gAudioHeadphonesEnabled (inferred), Actor.unk15F -> hudMode (C8C10: 0x80 flag + 0x7F phase counter), D_80035B38 ->
  gBossSavedPlayerUnk144 (address-shaped; boss/DAA0 saves gPrimaryPlayerActor->unk144 there).

## Hack items
- 2026-11-20: coverage restored (48 next=review reviewed, M1-M5); OPEN before the close: 7CA80 actorAllocate (CleanactorAllocatec:
  two `(u16)((headerSize + 7) & 0xFFF8)` CSE casts are value casts chosen for codegen; lead probe with both dropped = same code,
  registers renamed 0x340-0x3b4; tag + ladder) and the 11BC10 re-carry above.
- FCCD0 slotQueueDrawLabel f22aa7: the text[4] route is closed by R11 (coins F9450.c:621 item 0xB7 and the slot 9 sum are uncapped);
  a fix needs another free frame word for the int-width selector (dossier).
- Polish proposals (2026-11-18c reports, file-scope edits other functions reach): 80150 `extern s32 D_8071FE08` -> EffectGridAsset
  (better: one shared extern; 478F0/9DD70 declare `u8 D_8071FE08[]`, 19A00/89250/119370 EffectGridAsset);
  C4620 duplicate `extern Actor *gBehaviourTargetActor;` (actor.h:1264 declares it); 136820 gFaultFramebuffer s32 -> u16 * with
  faultFontInit's first parameter (after the 13980/136820 gFramebuffers[] s32/u32 unification).

## Held names (a field rename reopens the review of every touched function: batch them with the next types item, lead review each)
Lists: .scratch/Lead20261118/names17f.txt (17f proposals), names_close.tsv (close submissions; names_applied.tsv applied,
names_failed.txt refused), .scratch/lead_s1115/names.md, .scratch/lead_s1115c/close.md, .scratch/CleanupLead/close-2026-11-16-closed.md.
- PlayerState: unk50 gravityDelayFrames (read D5E10 first), unk78/unk7C/unk80, unkC2 slopeFrames (D5E10/EFDC0 unread), unk11C
  swimStrokeTimer vs stateTimer (EFDC0 unread; 2026-11-18c Polishglobal42630c votes stateTimer: u8 per-state countdown, EFDC0.c:1609
  sets 0x19 before state 0x39, D5E10.c:2260 `unk11C-- == 0`), unk1A0 aimPitch (936B0/CC800/D5E10 unread); every 17f field list
  (PlayerState/PlayerStruct/ActorGlobalState/ModelSlot/ModelAnim*/Jetpac*/HealthHud); PlayerStruct.unk2C0 sizeMode.
- JetpacItem (include/jetpac.h, 2026-11-18c Polishglobal9DD70): unk8 x, unkC y (jetpacDrawRocket passes unk8 / unkC + 52 as the sprite
  x/y; jetpacPlaceRocketAboveScreen sets 168 / -8 + i*16), unk44 update, unk48 draw (templates set them to jetpacRocketItemUpdate /
  jetpacBonusItemUpdate and jetpacDrawItem); dry-run touches jetpac/3480.c (60 positions) and jetpac/0.c (unk44): read them first.
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
- Slash-form and uncertain (17f/18): D_807444A8/AC/B0/B4 letterbox, 10130 func_8060B7C4/7D0 (func_8060B750/6CC named
  demoPlaybackLoad/demoPlaybackReset at the 18b close, 7a1f8709), effectSpawnDebrisParticles/effectActorCheckGroundScaleSpawn/
  effectSpawnActorScale (18c Polishglobal42630c: effectSpawnWaterRipple / effectActorCheckWaterRipple, less certain), gMenuBonusTimer
  -> gHelmTimer, modelAnimEntrySet*, BA790 func_806B5A90 -> explodingChaserUpdate (18c Polishglobal9DD70, moderate: states 0/4 chase via
  enemyAggroStateUpdate/actorMoveWithinZone (0x33), 0x37 explodes; held by the director at the 18c close).

## Tooling fixes (open)
- quality.py noop-arith regex `\* ?0\b` matches float literals (`* 0.1`): ACDC0 hudPauseMenuIconUpdate c4c287 is kind noop-arith
  but is an `other` reuse (CleanhudPauseMenuIconUpdate 2026-11-20); fix `\* ?0(?![.\w])`.
- quality.py header_renames counts a record field type respelled through a same-canonical alias typedef (JetpacSprite ->
  TextureDescriptor: JetpacActor.sprite, JetpacItem.sprites, JetpacCellItem.texture) and respelled data definitions as changed, so
  carry re-opens their users (TypesOwner13 batch_14 Part B: 19 functions).

