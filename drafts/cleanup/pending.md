# Cleanup pending (unresolved items only; checked against the tree at the 2026-11-20 close)

Open functions come from `uv run tools/quality.py rank` / `rank --polish` (SKILL §2) or `status --file <f>`. This file keeps what
`rank` cannot show: the `TypesOwner` queue (`.omp/skills/cleanup-unit/types-stream.md`: oldest first, skipping HELD/PARKED items), director rulings, held
names and tooling fixes. Delete an item once it lands (git and `drafts/cleanup/sessions.md` keep the history); a closed decision keeps one outcome line.

## Blocked owner/header changes (`TypesOwner` queue)
- Landed 2026-11-20 (history in sessions.md): batch_14 A EffectNode wobbleRise (f402b9a4, e1f618fa), B JetpacSprite ->
  TextureDescriptor (f2105d5b); batch_15 F ModelAssetEntry -> model.h (c7ef501e), G one LERP in common.h (220c7251), H1/H2 one
  EffectGridAsset extern for D_8071FE08 + C4620 duplicate dropped (7beb5dbd, 6064fcc9), E ACDC0 sPauseKongTables (070a72b3),
  C 450.c data split + 13980/201B0 s8 readers ORIG (2539d1a6), D1/D2 one declared type for gMinigameCoinCount,
  gFaultScreenEnabled, gDemoFixedAnimRate, gDemoPlaybackState, gActorScriptAnimTable (225a8e51, 3da6b8de).
- 7CA80 script tables: `extern void *gActorScriptIndexTable` (7CA80.c:533) vs `u16 *` in 19A00.c:284, 80150.c:116, E4090.c:1304 (bss
  in asm, no C definition), and `extern void *gActorScriptSoundTable` (7CA80.c:535) vs `s16 *` in 19A00.c:1495: one declared type
  each, every user in one gate; then actorInit casts directly (TypesOwner14, PolishglobalD1Reread 2026-11-20).
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
- 478F0 reads `D_807505AE[5]` (now `sPauseKongTables.unlockFlag[5]`) when sHubItemsCycle is 20, past the 5-entry table: original
  behaviour (TypesOwner14); keep, note only.
- jetpac 0x8002BA80 Gfx split: the `jetpacInitPending` splat label (jetpac/0.c:404) spans a gSPEndDisplayList.
- jetpac shared head (PARKED; CleanjetpacUpdatePlayerMovement, ledger 7d1cc6e8): embed one 0x30-byte head struct in JetpacActor
  and JetpacPlayerActor. `player->head.x` compiles like the plain body; only a `head = &player->head` local used for EVERY head
  access matches, so it retires 1A60 ba285d only if that local is ruled ordinary C (`.omp/skills/cleanup-unit/rulings.md` pointer-local precedent: 450
  firstSetupFlag). It touches every head-field access of JetpacPlayerActor.
- HeapBlock allocated-block tag (HOLD, director; .scratch/CleanheapRegisterSurvivor/header-request.md): byte 0x0B is the low byte
  of `next` while free and the tag while allocated (0 normal, 1 locked, 2 survives an overlay load). Every access is a byte view
  (`((u8 *)p)[0xB]` in heapInitGeneralPool, heapInitBlockPool, heapReleasePool, heapFree, heapFreeDeferred,
  heapRegister/UnregisterSurvivor; `ptr[-5]` in heapLockBlock/heapUnlockBlock). An anonymous union adds cfe W838 + W649 per
  declaration; a named one rewrites all 28 `->next` in 15050.c. Only as a file-wide polish/types pass.
- 7130 D_80770DD9 (undefined_syms.us.txt:341) stays while 7130.c:853 stores through it (FAKE linker alias of D_80770DD8[1]).
- Declaration consistency: D_80720340 `u8`/`u8[]`/`s32` (478F0, 80150, 936B0, 9DD70, B6C50, race/1770; held name gSmokePuffSprite:
  unify the type first).

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
- Continue unit 1 (2026-11-21): the four stale reviews and every knowledge/rename-staled hack rung were re-measured (ReviewU1/U2,
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
- Re-derive from the asm alone, fresh copies started from m2c output (not the current bodies; workers do not read the current C
  of these functions): 0_init `mainThreadHalt` (0x805FB5C4), 450_main_loop `mainSystemInit` (0x805FBC5C) and
  `mainResetEngineState` (0x805FBE04). Acceptance: fdiff exit 0, then the usual gate. Prerequisite: matched functions have no
  `.s` for `tools/m2c.py`; `tools/restore_split_asm.sh 5535bf19 dk64.global.us.yaml` puts back the ROM split's
  `asm/global/nonmatchings/**/func_805FB5C4.s` etc. (names at that commit are `func_<VRAM>`; the next `make split` removes them).

## Held names
Continue unit 1 (2026-11-20/21, names windows 4b47df82..741670df, union carves e14a06d4) landed ~1,360 names, including every
field list above it (PlayerState, PlayerStruct, RaceParticipant, JetpacItem, CamState, CsState, ModelSlot, RenderEntry,
SchedStruct, SpawnNode, BehaviourWorkState, ActorGlobalState, ActorCallbackNode, Actor 0x144/0x155/0x72/0xA8) and the 2026-11-20
global/function proposals (gArcadeEntities, gArcadeScreenMode, gMainLoopWatchdog, gWatchdogPaused, camComputeFirstPersonEyeFocus,
...). Field renames now carry (quality.py carry + --header-carve): they no longer reopen reviews. What is still unnamed:
`uv run tools/debt.py names`; queue and procedure: `.omp/skills/continue-unit/names.md`. Still held (evidence or ruling missing):
- Cross-segment aliases: D_80029FA0 (critter names it critterArenaTargetsLeft; global code uses it), D_80741F40, D_80760840.
- D_80753354 (s16 per-kong turn rate; gKongTurnRate is CEAE0's other table), D_8076A0A6 (copy of gPadPressedButtons[0]),
  D_807FC952 (= gPlayerInventoryTable[0].kong[0].weaponFlags; cannot fold), race/0 D_8002FB10/D_8002FB70 route tables, D_80750650.
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

