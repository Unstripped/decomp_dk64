# Cleanup pending (unresolved items only; checked against the tree at the 2026-11-24 close)

Open functions come from `uv run tools/quality.py rank` / `rank --polish` (SKILL §2) or `status --file <f>`. This file keeps what
`rank` cannot show: the `TypesOwner` queue (`.omp/skills/cleanup-unit/types-stream.md`: oldest first, skipping HELD/PARKED items), director rulings, held
names and tooling fixes. Delete an item once it lands (git and `drafts/cleanup/sessions.md` keep the history); a closed decision keeps one outcome line.

## Blocked owner/header changes (`TypesOwner` queue)
- Landed 2026-11-20 (history in sessions.md): batch_14 A EffectNode wobbleRise (f402b9a4, e1f618fa), B JetpacSprite ->
  TextureDescriptor (f2105d5b); batch_15 F ModelAssetEntry -> model.h (c7ef501e), G one LERP in common.h (220c7251), H1/H2 one
  EffectGridAsset extern for D_8071FE08 + C4620 duplicate dropped (7beb5dbd, 6064fcc9), E ACDC0 sPauseKongTables (070a72b3),
  C 450.c data split + 13980/201B0 s8 readers ORIG (2539d1a6), D1/D2 one declared type for gMinigameCoinCount,
  gFaultScreenEnabled, gDemoFixedAnimRate, gDemoPlaybackState, gActorScriptAnimTable (225a8e51, 3da6b8de).
- Landed 2026-11-24b (continue unit, TypesOwner17; history in sessions.md): batch_18 A 7CA80 actor-script table externs take the
  readers' types (d49a5943); B1-B6 + H every effect sprite extern `EffectGridAsset` (42397ff1, d10406bc, 2db9b450, 7e99f449, 231fc47c,
  cb17735e, e9a2bee8; closes the D_80720340 / gEffectSpriteExplosion declaration item); batch_19 A A8400 `gEffectGridAssets`
  `EffectGridAsset *` (01ff4a67), C one VehicleActor in race.h for 936B0 + race/52B0 (570c5e4b), E jetpac/0 BUTTONS_PRESSED
  (9ab2a986); batch_20 RaceParticipant 0x25 / 0x26 split by actor kind: manager hasCpuRival / route, racer boostTimer / boostCharge
  (993213f4 header, 3a7a5351 uses); PlayerStruct heldButtonsPtr -> pressedButtonsPtr (names window 757bd3f2). The ucode-symbol item
  (6710/14CF0 rsp/asp externs) has no remaining externs.
- Landed 2026-11-25 (continue unit, TypesOwner batch_21): C effectCreateAt{ModelNode,ActorBone,Position} take `EffectGridAsset *`
  (ce7829eb); A `effectSetCallback(EffectCallback)` with the cast dropped, 70 11BC10 callbacks + menuSparkleParticleUpdate +
  hudPauseMenuIconUpdate take `u8 *isDone`, 7CA80 `EffectCallback pulseCallback` (aaff5a58; re-review ReviewTypes21).
- Actor.soundSlots[0] (0x6E) is a frame counter in BC3B0 (beep timing, BC3B0.c:172): the shared field name may be too narrow.
- 55B20 file-local MapZone (55B20.c:350): `tris` as `MapTriangle *` would remove 23 casts; a natural rewrite does not match yet.
- 36880 views on `ModelSlot.unk20` (model.h:109 `void *`, ModelKindObj users): blocked on the model.h H1/H2 regeneration (clashes
  with file-local ModelSlot typedefs); actorBoneChainSwingUpdate near-miss hint in the Rev20A report.
- 8F4B0 CutsceneActorState / WeatherActorState merge (same layout, 8F4B0.c:203/485): needs proof that actorCutsceneDispatchEvents
  runs on actor type 0xC (PolishGlobal8F4B0Names 237b3f89).
- REOPENED (user 2026-11-24, FAKE queue never terminal): B5EC0 72fa9a actorTrackBoneTowardTarget proto-steer: TERMINAL (director RQ3 2026-11-20): FAKE kept; owner prototype (u8, s32)
  rejected (a1 = sel by residence only: B5EC0.o `move a1,a0` 0x9c0, jal 0x9d8; owner +0x8 `andi a1,a0,0xff`; 37 callers by
  residence). Re-measured 2026-11-20 (Cleanfunc_806B13B4b, 900d6b5c): EXHAUSTED.
- effectSetSpeed(s32) receives an actor pointer (race/1770.c:330 `(s32)gCurrentActor`) and an index (boss/0): owner type review.
  HELD 2026-11-25 (batch_21 B): 156 call sites, 137 numeric (79 literals, 58 expressions incl. float sums the s32 prototype
  converts), 19 pointers; a pointer type raises W712 on the ints. 0x35C is a union {speed, target, data, pair}; keep s32.
- 36880 TexImageCmdSpan as a Gfx[] view (2026-11-14b; batch_19 D, no change): the span reads naturally as `Gfx` (texAddr 0x04 =
  span[0].words.w1 of the G_SETTIMG, tileSizeW0 0x30 = span[6].words.w0 of the G_SETTILESIZE), but retiring it is not local:
  dlFindTextureCommands is non-static (its proto names `struct TexImageCmdSpan **` twice: PROTO_SKIP stand-in + gen + stage), the
  TexAnimCmdSet fields change type, three functions change (the 2072-2095 compares, the 2907-2917 stores) and one store is an ORIG
  line (2910 `dst = &...->tileSizeW0`, key changes). Plan: one callee-prototype part with views fixed + review for the 3; measure first.
- 13980 `extern u32 gFramebuffers[]` -> `u16 *gFramebuffers[]` (Polishglobal13980Rereview 3c2f89d7): blocked on 136820's
  `faultFontInit(s32, s32, s32)` prototype.
- 478F0 reads `D_807505AE[5]` (now `sPauseKongTables.unlockFlag[5]`) when sHubItemsCycle is 20, past the 5-entry table: original
  behaviour (TypesOwner14); keep, note only.
- jetpac 0x8002BA80 Gfx split: the `jetpacInitPending` splat label (jetpac/0.c:404) spans a gSPEndDisplayList.
- HeapBlock allocated-block tag (HOLD, director; .scratch/CleanheapRegisterSurvivor/header-request.md): byte 0x0B is the low byte
  of `next` while free and the tag while allocated (0 normal, 1 locked, 2 survives an overlay load). Every access is a byte view
  (`((u8 *)p)[0xB]` in heapInitGeneralPool, heapInitBlockPool, heapReleasePool, heapFree, heapFreeDeferred,
  heapRegister/UnregisterSurvivor; `ptr[-5]` in heapLockBlock/heapUnlockBlock). An anonymous union adds cfe W838 + W649 per
  declaration; a named one rewrites all 28 `->next` in 15050.c. Only as a file-wide polish/types pass.
- REOPENED (user 2026-11-24, FAKE queue never terminal): 7130 D_80770DD9 (undefined_syms.us.txt:341) stays while 7130.c:853 stores through it (FAKE linker alias of D_80770DD8[1]).

## Closed or held by ruling (reopen only with the new evidence named)
- Callee-declaration ORIGs confirmed with no shared route (Polish26Protos 2026-11-26, probes .scratch/Polish26Protos/owner/): boss/0
  actorMoveWithinZone (owner (u8, f32, f32, s32, f32) fails 12E800 itself + B1F60/BA790/BDEE0), F0D0/2C910 csModelStateSetFirstByte
  ((s16,u8) vs (s32,s16): owners (s16,s32)/(s32,s32)/(s32,s16) each fail 42630, F0D0 or 2C910), 42630 effectSetDepth (s8 owner fails
  478F0/80150/89250/9DD70, s32 also 119370), 42630 hudSpawnCountdownTimer (4-param owner changes A7710's arg homes; 3-arg callers stop
  compiling). The protos-mismatch polish debt (5 of 6; jetpac/0 flagGet ruled below) is permanent unless an owner type changes.
- jetpac/6E00 jetpacDrawString W709 (4b47a2): `const void *str` DECLINED (R3, director 2026-11-26: erases the char/u8 distinction like
  the rejected `(const u8 *)str` cast); `retype kept` recorded (669af42e). textDrawString `const char *` stays fdiff 1 (lbu -> lb).
- Return widths: keep `u8 mapGetHubWorldIndex(u8, u8)` (OwnerHubWorldIndexWidthPlan: C2A90 func_806BE09C uses v0 unmasked) and
  `u8 flagGet(s16, u8)` (OwnerFlagGetWidthPlan: no option passes all 49 files; jetpac/0's pair is ORIG, 0x11d4).
- ACDC0 split labels D_807FC82A..D_807FC838 KEPT (OwnerCollectibleCountsView 0c2a5e64; ACDC0.c:75): folding them into actor.h's
  `D_807FC828[9]` makes hudPauseMenuRefreshTotals 16 bytes shorter.
- loadOverlay keeps splat label `D_80744474` (= gFramebuffers[1], 15050.c): the fold makes the shared base a coloured address (t1)
  and drops the target's two `lui at` (0x1b0-0x1c4), 12 lines (CleanloadOverlay 2026-11-25).
- proxPathAdd/proxPathSetSegment keep `Actor *` (OwnerProxPathIdParam; ledgers f3f3f306/956c2dfa/48c9b6b0): `s32 id` fails 36880
  modelSlotBuildProxPaths (frame 0xD8 -> 0xD0); the target homes id once at sp+0x98 and reloads it, so 36880.c:790/794's
  `(Actor *)id` casts are original.
- 1332B0 volumeTriggerUpdate keeps `extern void *gPlayerSlots` (1332B0.c:11) for its PlayerSlot stride view (Q0606, views blocked).
- PlayerStruct.rect[4] (sched.h) scissor-field rename HELD: named fields flip textBoxRender's `|` chain order (Q1082).
- HeapBlock u64 view for 15050's 14 `// ORIG:` pair puns DECLINED (TypesOwner9 batch_9 part J): no hack site gained, alignment
  4 -> 8 (clint TYPES LAYOUT BAD), defeats `--header-carve`, reopened 15 functions. Retry only with a new form.
- REOPENED (user 2026-11-24, FAKE queue never terminal): CollisionBoxTri shared struct (collision.h) DROPPED (TypesOwner5 batch_5 Part A; probes .scratch/TypesOwner/batch_5/partA_req/,
  partA_alt/): scalar x0..z2 needs a pun in 70FD0, x[3]/y[3]/z[3] fails fdiff in 6AD90. Reopen only with a shape that fdiffs in both.
- REOPENED (user 2026-11-24, FAKE queue never terminal): FE40 0b7e03/#2 PERMANENT DEBT (director 2026-11-17d, `retype kept`, ledger 70e3f1e4): `void *dst` is polymorphic; `u8 *dst`
  raises W709 at 9 caller args (5A50 4, 6AD90 5) and gunzip's `void **outBufPtr` needs a pun. Probes .scratch/PolishglobalFE40/.
- REOPENED (user 2026-11-24, FAKE queue never terminal): 11BC10 effectInterpolationUpdate 6e5dc3 DECLINED (director; CleaneffectInterpolationUpdate, merge 45e10058): an `f32 *` interp
  with enum slot indices matches (.scratch/CleaneffectInterpolationUpdate/render_interp_f32.patch, typed_standin_11BC10.c) but is a
  view chosen for codegen. Retry only with new type evidence.
- REOPENED (user 2026-11-24, FAKE queue never terminal): D1 TERMINAL (director 2026-11-18): the menu/3E10 `(void *)(s32)&D_80721444` cast family (menuInitMainScreen 5,
  menuInitAdventureFileSelect 3, 3E10.c:738) keeps `void *` + 9 FAKE casts: an `s32` asset parameter on menuSpawnUiElementEffect
  costs W712 0 -> 68, a `u8 *asset` local scores full=28 (.scratch/TypesOwner/batch_12/partR_plan.md,
  .scratch/Lead20261118/probe3E10; recorded 9f83bf7c). RQ1 2026-11-20: stale rungs re-measured only (CleanmenuInitMainScreenb,
  02ea6af1), nohit, EXHAUSTED; terminal debt.
- REOPENED (user 2026-11-24, FAKE queue never terminal): D2 HOLD (director 2026-11-18): ACDC0 hudPauseMenuUpdate, 4 FAKE (c127b7 page and db430c credits reuse sel; 6151e7 limit and
  32c920 half reuse flag, pinned by register colouring; .scratch/CleanhudPauseMenuUpdate/dossier_global_hudPauseMenuUpdate.md, merge
  54a784f8). RQ2 2026-11-20: re-measured on the merged body (02ea6af1), no new lever (page 7 = cfe's shared switch temp takes v0;
  every split grows the frame 0x58 -> 0x60), EXHAUSTED. A lever not in the dossier goes to the director with offsets before any
  FAKE change. Frame-capacity ORIG declined (ladder.md home-slot rule).
- REOPENED (user 2026-11-24, FAKE queue never terminal): 7130 70c91e `if (D_80770DC8) {}`: CLOSED 2026-11-18b (CleansfxUpdateLevelAmbientc, ec3c9426): Q1470 lands the function-local
  static at 0x80770DC8 only with N = 160 (mod 256) extra numbered definitions; no natural count. Reopen only with another lever.
- REOPENED (user 2026-11-24, FAKE queue never terminal): 80150 tagBarrelActorUpdate 71b822 empty `default: break;`: FAKE (2026-11-18c M19, 9de100e7): the not-2 edge `bne` 0x58fc goes straight
  to the latch 0x5928, no own block, so the empty-default rule keeps it a steer (already tagged).
- 6AD90 f64 midpoint reuse a2d087 (box) and 3aa4ac (collisionCheckTriangleContainsPointXZ): M21 (2026-11-18c, 47fa703b) kept them FAKE
  because an eleventh f64 does not fit the 96-byte local area. M21 superseded by the census rule (2026-11-25c): the same frame fact is
  census part 1, parts 2-3 hold, both untagged (CleancollisionCheckTriangleContainsPointXZ, dossiers). Closed.
- REOPENED (user 2026-11-24, FAKE queue never terminal): 9DD70 actorCheckAlwaysFalse e999c8 `case 6: case 7:` stays ONE FAKE (R8, director 2026-11-18c): no 6/7 compare in the target
  (0x16e0-0x1754); no restore of the pre-merge sites c56038/0641d2.
- Names kept (director 2026-11-14): collisionGetFloorTriangleNormal (proposal collisionCheckLedgeGrab: .scratch/close/renames.md row 105);
  collisionGetFloorHeight was renamed collisionGetWaterSurface at the 2026-11-24 close (eb53794b) on new evidence (it returns
  sWaterSurfaceHit and writes sWaterSurfaceY, names from the continue-unit windows): director to confirm, else `rename.py func global
  collisionGetWaterSurface collisionGetFloorHeight`. Rejected: Actor.unk155 -> subState/stateTimer, D_807FF0F2 ->
  gAudioHeadphonesEnabled (inferred), Actor.unk15F -> hudMode (C8C10: 0x80 flag + 0x7F phase counter), D_80035B38 ->
  gBossSavedPlayerUnk144 (address-shaped; boss/DAA0 saves gPrimaryPlayerActor->unk144 there).

## Hack items
- 2026-11-24b: the close knowledge commit 0a899c80 reopened faultDrawRegs, csModelIdTableReset, hudPauseMenuUpdate and
  enemyGridStateStep; the post-close re-measure (ReMeasureKnow24b, db9779c7 + ledgers 633e5116 / dfac70e2) fixed hudPauseMenuUpdate
  c127b7 + db430c (switches on gCurrentMap / hud->page, `credits = hubWorld == 8 && menuGetTimerFlag() != 0;`), retagged cc0f6b /
  706cd2 ORIG (R4) and kept the rest. Its findings were filed in 1dadd028 (Q1635, Q1636, Q1582 correction).
- Polish follow-ups (ReviewTypes21 2026-11-25, re-read at aaff5a58; nothing edited): 11BC10 effectShrinkOffsetUpdate K&R `s8 *isDone`
  -> `u8 *` (only caller passes u8 *); effectTimedLightIntensityFade `(void *)effect` vs sMinecartWheelEffect: declare it
  `EffectNode *` here and in minecart/0_player_cart.c:97; timedLightOrbitUpdate ends at `&gLightSlotNext` (= &gRaceSparkEffects[4];
  race/1770 declares it u8): `extern ...[4]` + `--reloc-ok`; timedEffectCountdownTick single-use `u8 newAlpha` (try the direct
  store, else tag); effectWobbleRiseUpdate swayX/swayZ and effectWobbleScaleUpdate `wave` reused for an unrelated role (split or
  tag); K&R effectPlayerDistanceFadeUpdate/effectFadeInSinkUpdate/effectSinkBySpeedUpdate; 8 uncalled-by-C callbacks keep old
  second-parameter types (effectInterpolationUpdate & 5 more `s8 *`, effectRandomDriftVelocityUpdate `void *`,
  effectScaleYFromSpeedUpdate `s32`) for a later types batch.
- Polish note (2026-11-24b EmuGlobalsU5): the callers of the 6AD90 water probe that sets D_807F9468 / D_807F946C discard its
  `outHasWater` / `outWaterY` outputs, so those parameter names look wrong; no replacement name proposed (needs a reader of the
  function's real outputs). Not dispatched: a param rename is a body change.
- Polish follow-ups (ReviewTypes22 2026-11-25c, read at c7b5a10f; nothing edited): jetpac/1A60 jetpacIsSpawnDelay (551-557) has an
  untagged missing return (target returns `ret` in v0: `sltiu v0` 0x158c, `beqz v0` 0x1590, `jr ra` 0x15a8; same shape as the
  F56F0:687 `// ORIG: no final return`): tag it ORIG; 15 no-op casts in 1A60 (84, 128-137, 250, 253, 256, 261, 264, 563; all removed
  still fdiff 0); jetpacGetEntityCenterX/Y (3060:76-82) read only head fields: a `JetpacHead *` parameter drops the
  `(JetpacActor *)&jetpacGame.player` cast (4FC0:519; callers 4FC0:464/518/526), matches with a proto regen; JetpacItem
  (0x08-0x37) and JetpacLedge (0x00-0x2F) share the JetpacHead layout (embed needs evidence first); `extern JetpacState
  jetpacPlayer` is declared in 0_game.c:22 and 1A60:431 (move to jetpac.h); jetpacSnapActorToGrid also restarts the jetman
  explosion (name too narrow).
- R-oildrum census (2026-11-25c, Q1666) outcomes, each census in the function's dossier: untagged 3E10 menuUpdateElementTargetAndColor
  `t`/`stepOrScale`, ACDC0 hudPauseMenuIconUpdate (6), BA790 chaserEnemyStep (2), 6AD90 ContainsPointXZ twins, 55B20
  map(Node)TriangleContainsPoint, arcade/0 arcadeUpdateOilDrumEntity `n`, DAA0 bossSpawnerUpdate `z`; fixed by a no-local form 3E10
  menuHandleControllerSlotInput `bits`, D5E10 playerStateLandRecover `f`; 11BC10 wobble reuses split into pad words (swayX ->
  waveX ORIG). Census FAILED (stay FAKE; do not re-run without a new spelling): 12E800 enemyAggroStateUpdate `near` (frame-keeping
  narrow split), D5E10 playerStateSurfaceTreadWater `target`, arcade/0 arcadeSpawnStage4Enemies `i` and arcadeDrawHud `i` (the
  latter fails only if `buf[0x50]` is not fixed: both readings in its dossier), ACDC0 hudPauseMenuRender (6) and hudPauseMenuUpdate (2),
  DAA0 bossSpawnerUpdate `i`/`j` (register-only).
- ACDC0 hudPauseMenuRender a97e00 `(it->entries + j)->x` member spelling: stays FAKE unless its own addu order is target-proven at a
  cited offset and nothing else (the mul.s operand flip) depends on the spelling (director 2026-11-25c).
- REOPENED (user 2026-11-24, FAKE queue never terminal): Continue unit 1 (2026-11-21): the four stale reviews and every knowledge/rename-staled hack rung were re-measured (ReviewU1/U2,
  Hack* workers): reviewed 4,270/4,270, sites open 1; FAKE 168 -> 163 (80150 volatile via bare truth tests Q1585, 36880
  modelPendingQueueInsert 4 -> 2, 7130 sfxUpdateLevelAmbient 4 -> 2 via a per-block element pointer Q1586). Every other rank
  function is EXHAUSTED; re-dispatch only with a lever named in the brief (continue-unit SKILL §3: lever-transfer lists).
  7CA80 actorAllocate's `ALIGN8_U16` `(u16)` stays FAKE (director: reachable headerSize <= 0x188, the cast never changes the value).
- FCCD0 slotQueueDrawLabel f22aa7: the text[4] route is closed by R11 (coins F9450.c:621 item 0xB7 and the slot 9 sum are uncapped);
  a fix needs another free frame word for the int-width selector (dossier).
- Polish proposals (2026-11-18c reports): 136820 gFaultFramebuffer s32 -> u16 * with faultFontInit's first parameter (after the
  13980/136820 gFramebuffers[] s32/u32 unification).
- Polish proposals (2026-11-20 reports, hack-function bodies, ordinary-C only with fresh rungs re-run): redundant casts in 3E10
  menuDrawHighScoreTable `(s16)(posY * 4.0)`, menuUpdateElementTargetAndColor five `(f32)`, 1295B0 zoneCheckActorInside two
  `(f64)` + seven `(f32)` (each fdiff 0 in a probe copy, Polishglobal42630d); 70FD0 420f8c FAKE comments still say unk140.
- Polish proposal (2026-11-24 M17, untested): one function-like macro for 6AD90's six plane-parameter computations
  `0.0 - (((x * nx) + (ny * -1000.0) + (nzTerm * z) + d) / (ny * 2000.0))` (collisionTestStaticMeshFloor 876/880,
  collisionTestDynamicActorFloor 1315/1324/1328, collisionTestActorBoxFloor 1699); needs fdiff (a macro is one source line).

## Held names
Continue unit 1 (2026-11-20/21, names windows 4b47df82..741670df, union carves e14a06d4) landed ~1,360 names, including every
field list above it (PlayerState, PlayerStruct, RaceParticipant, JetpacItem, CamState, CsState, ModelSlot, RenderEntry,
SchedStruct, SpawnNode, BehaviourWorkState, ActorGlobalState, ActorCallbackNode, Actor 0x144/0x155/0x72/0xA8) and the 2026-11-20
global/function proposals (gArcadeEntities, gArcadeScreenMode, gMainLoopWatchdog, gWatchdogPaused, camComputeFirstPersonEyeFocus,
...). Field renames now carry (quality.py carry + --header-carve): they no longer reopen reviews. What is still unnamed:
`uv run tools/debt.py names`; queue and procedure: `.omp/skills/continue-unit/names.md`. Still held (evidence or ruling missing):
- Cross-segment aliases: D_80741F40, D_80760840 (D_80029FA0 / D_8002FBB0 / D_80028C30 took their overlay names by ruling R3,
  8ffd3b5b). 2026-11-24b emulator residue: `drafts/cleanup/names-queue.md` "Held" lines (EmuFieldsU5, EmuGlobalsU5).
- D_80753354 (s16 per-kong turn rate; gKongTurnRate is CEAE0's other table), D_8076A0A6 (copy of gPadPressedButtons[0]),
  D_807FC952 (= gPlayerInventoryTable[0].kong[0].weaponFlags; cannot fold), race/0 D_8002FB10/D_8002FB70 route tables (D_80750650 is
  gEnemyGridLeaping since f79601f5).
- Function renames: playerCheckLandingSfx -> playerCheckLandingSlide, effectSpawnDebrisParticles/effectActorCheckGroundScaleSpawn
  (water ripple, less certain), gMenuBonusTimer -> gHelmTimer, csSetActorScaleFadeByType / actorSetInteractionTimer (both set
  Actor.collisionMode, NamesActorBytes), csIsPlayerState4OrC (tests gPlayerSlots->camChunk, NamesRaceSched).
- Fields: PlayerState unk78/unk7C/unk80, Actor 0xE4 pitch <-> 0xE8 roll swap, HudIconState unk10 offsetX / unk18 wanderTargetX
  (ACDC0 file-local, HackACDC0). Unit 2 held with evidence (reports NamesFieldsA/B): PVoice_s.unk8C + N_ChanState.unk13/unk31
  (the `fxDelay` label itself is unconfirmed; needs what ucode opcode 0 does), MapBspNode unkC/10/14/18 (four leaf display lists,
  nothing distinguishes them), KongInventory.unk5 (no C writer), write-only / zero-init fields (list in agent://NamesFieldsB).
- Ruling (user, 2026-11-21): scratch globals reused by the original get their dominant role's name plus a declaration comment on
  the reuse (gSfxPan, gSfxRightLevel, 7130.c, c4202469). Per-type scratch fields (Actor.unk15F / unkEC) get one named union
  member per role, single-function roles included (UnionActorU2, e9dfa60d: 17 members; the fairy and text-actor zero writes
  keep unk15F / unkEC). Continue unit 2 windows 7/8 (33b2cc20, c2c718a0) landed 62 fields and 318 globals, including the
  previously held D_807F7140 (gCsModelUpdateCount) and D_807FF0F2 (gAudioNarrowPanEnabled, behaviour-named).
- Rulings (user, 2026-11-23): index-distinguished predicates take the game's own index in the name when the index is game data
  (`actorHitTargetNode1`..`5`: the target's collision node number); a parameter whose RSP command is a no-op is named for what
  the code does with it plus a comment on the dead effect (`rspFxLevel`); externals-only identifications (Rare's `n_aspMain`)
  are not used: repo-derived names instead (`gAudioUcodeText`/`gAudioUcodeData`). All applied in names window 13 (5e1dd1e6).

## Tooling fixes (open)
- None open from 2026-11-20: 73393b44 (noop-arith literal), bd5da4f3 (alias respelling), 49c6d3c4 (tag added in place), d84d0487
  (macro renamed to an identical macro), 25fcab9a (knowledge staleness by author date), 4c63a269 (carry skips duplicates),
  994b805b (AGENTS.md) landed; the six 2026-11-18c items closed with 928f8144, 827859da, ed51d26d, 12452351, f29f1c5d, 827913fc.
  2026-11-24b: carry re-stamps typedef/record renames (a075dea7, ToolsCarryTypeRenames). Still open: names_window.py has no
  typedef or local rename mode (the 2026-11-24 queue's `[type]`/`[local]` lines were gated by hand, dcc777e3).
- 2026-11-25c landed: 15f27049 (recipe rung scores every variant, `--max 0`), d9b6c1b1 (fakehunt stops its child jobs on hosts
  without ps/SIGKILL), 39d2c5aa (report --baseline / clint layout --base export REV without git archive of invalid paths).
  2026-11-26 landed (Tools26): 3eb5c399 (sweep check cache, `sweep --func`/`--no-cache`), 5b1f35c0 (fdiff/cwarn `--shadow` when the
  copy is the src), cb6c08ce (objdiff HI16/LO16 pairing by relocation-table order across switch paths).
  2026-11-27 landed (Tools27): e7b2bc4c (fdiff/objdiff FUNC prints that function's diff only, tools/asmdiff_func.py), 5ac42a0f
  (LF writers; fdiff.sh/cwarn refuse CRLF copies), 40b1d4bd (names_window carries per file and reports a failed carry).
