# Pending after cleanup round 38 (campaign paused by the user)

State after the round-38 close (knowledge commit 7a7ec5c6, Q0754-Q0759): 192 OPEN functions in 117 files. Since then the campaign runs as a rolling queue (SKILL.md §2): a future session starts with `uv run tools/quality.py rank --limit 40` (function hack queue) and `rank --polish` (file polish queue); coverage first. The "Blocked owner/header changes" below are the `TypesOwner` queue (types-stream.md). Audited 2026-11-14 at 7a453f41 (PlanPendingAudit: DONE entries removed; evidence and verdicts in .scratch/PlanPendingAudit/audit.md), re-checked at 74533125: DY ca506697 fixed global/0 f71305 and 450 2e505d (M2, M3), DZ 2e019041 closed every 42630 proto site as ORIG (89a542, M10).

## Blocked owner/header changes
- Owner return-width redesigns (closed): (a) keep `u8 mapGetHubWorldIndex(u8, u8)` (OwnerHubWorldIndexWidthPlan: C2A90
  func_806BE09C uses v0 unmasked, so the original return is u8); the 8F4B0 da5663/2c5186 and FCCD0 da5663/06d21a steer pairs
  are FIXED since 2026-11-15c (dce6f570, cf977754: u8 local/prototype + caller mask removal). (b) keep `u8 flagGet(s16, u8)`
  (OwnerFlagGetWidthPlan: no option passes all 49 files); 80150 c1a42b/b5496b stay FAKE, jetpac/0's pair is ORIG (0x11d4).
- critter/5110 D_807FCC44 split label stays tagged (5110.c:57, Q0687 table-base CSE); D_807FCC40 retired (5adcdc9b).
- ACDC0 split labels D_807FC82A..D_807FC838 KEPT (OwnerCollectibleCountsView, 0c2a5e64): the table is now one shared `extern s16 D_807FC828[9]` in actor.h (ACDC0, 3E10 and 117190 read it, [0] included), but folding ACDC0's [1]-[8] labels into it makes hudPauseMenuRefreshTotals 16 bytes shorter (.text 20880 vs 20896), so ACDC0 keeps them (ACDC0.c:73-80).
- 2F550 MapViewEntries proposal (.scratch/Rev24/header-request.md), held. With it, 55B20 could drop MapChunkArg. (The 35000 owner block on mapChunksRender is RESOLVED: bare `if (flag)` tests + shared u8 prototype, HackmapChunksRender c83bca1f.)
- Actor.soundSlots[0] (0x6E) is a frame counter in BC3B0 (beep timing, BC3B0.c:173-176): the shared field name may be too narrow (header owner).
- 55B20 MapZone.tris as MapTriangle * would remove 23 casts (a natural rewrite does not match yet; 55B20.c:352/1468).
- proxPathAdd/proxPathSetSegment keep `Actor *` (audit A1 CLOSED, kept; OwnerProxPathIdParam, ledgers f3f3f306/956c2dfa/48c9b6b0): with `s32 id`, 133A90 and 9CE20 match (9CE20 needs `(s32)gCurrentActor` x2), but 36880 modelSlotBuildProxPaths fails (frame 0xD8 -> 0xD0, 38 diff rows, also with `(s32)id`). The target sign-extends id once (sll/sra at 0x1584/0x1588), homes it at sp+0x98 (0x15c0) and reloads it for both calls (0x16b0/0x17c0), so 36880's two `(Actor *)id` casts (36880.c:792/796) are original. The `s32` siblings (89ad9a91) match their callers' value types.
- jetpac/4FC0 `extern JetpacPlayerActor jetpacPlayer` (4FC0.c:44): JetpacState raises its cfe 1 -> 2 (round-34 measurement; 3480 and 1A60 already use JetpacState).
- jetpac/1A60 jetpacUpdatePlayerMovement volatile 1d4065 / 1d4065#2: blocked. Director REJECTED `volatile s32 flying` in jetpac.h JetpacPlayerActor: it only moves a codegen-only volatile into a shared header and hides it. Both sites stay tagged `blocked` (HackjetpacUpdatePlayerMovement, 2026-11-14; evidence .scratch/HackjetpacUpdatePlayerMovement/).
- 36880 views on `ModelSlot.unk20` (model.h:109 `void *`, ModelKindObj users) are blocked on the model.h H1/H2 regeneration (clashes with file-local ModelSlot typedefs); the MODEL_TRANSFORM_SLOT0/SLOT views are gone (0bc29f13). actorBoneChainSwingUpdate near-miss hint in the Rev20A report.
- HeapBlock u64 view for 15050's 14 `// ORIG:` 64-bit pair puns: MEASURED AND DECLINED (TypesOwner9 batch_9 part J, 2026-11-17): an
  anonymous union with `u64 dwords[2]` fdiffs but gains no hack site (the 14 lines are already ORIG), raises HeapBlock's alignment 4 -> 8
  (clint TYPES LAYOUT BAD), defeats `--header-carve` and reopened 15 functions with 0 carried. Not to be retried without a new form.
- 1332B0 volumeTriggerUpdate PlayerSlot stride view of gPlayerSlots kept (Q0606, views blocked; 1332B0.c:11 `extern void *gPlayerSlots`, 172-185). Every other file declares `PlayerStruct *gPlayerSlots` (13b5f3b8; A8400 since 26db89ed).
- PlayerStruct 0x270 bounds: CLOSED (TypesOwner9 batch_9 part I, 26db89ed): A8400's ScreenBounds/MapBounds views and SPRITE_BOUNDS retired
  for `PlayerStruct.rect[0..3]` (sched.h). HELD: renaming `rect[4]` to scissor fields flips textBoxRender's `|` chain order back (constant-index
  array reads vs named fields schedule differently, Q1082). Round-16 list still open: playerStateQueueCallback arity (F56F0 14204c, race/6650 8cc620), n_alSndpPostEvent.
- cutscene.h `CsState` / `CsStateFull` describe the same 0xA4 object (Polishglobal42630, b264b7a5): one merged type would retire the casts in
  csStateUpdate (csCmdExec call) and csCondEval (gCsCondTable handlers, 478F0 etc. take `CsState *`). CsState lacks unk51/unk52 (inside
  pad51[0xB]); CsStateFull lacks the unk44/unk48 union and differs in s8/u8 signedness at 0x4F/0x50/0x60/0x67/0x6E-0x71. Types item.
- 1025E0 `func_806FDAB8`: RESOLVED on the caller side (HackbonusTargetGameUpdate 0a7cfd1f: pass the just-stored `game->counterTextId`, Q1139); the owner keeps its s16 parameter.
- gCamActor: one `extern struct Actor *gCamActor` in actor.h (OwnerCamActorExtern e13ffda6; boss/8520 and B100 retyped from `void *` with cfe unchanged; the last file-local copies dropped in 7748c62b). gFrameCounter/gGlobalPauseFlags single shared type.
- ACDC0 renderRotatedSprite proto-steer 6bd641/01af71 kept (HackConsolidateBoss0ACDC0, ledger 9ca52aed): the owner's s32 siz only changes CSE of the literal 2 (li a3,2 -> move a3,s8 at 0x1638/0x16B8). That is register-only evidence, not ORIG. boss/0 ea31b7 is ORIG (70242923).
- Data ownership (HacktransitionSetAudioVolume, 2026-11-14, ledger a001e1ac): carve the .data region of 14C9E0 around D_807550A4
  (today an extern in 10E1D0.c:566; no 14C9E0.c exists) into its owning C file; that enables a Q0498 function-local `static` retry for transitionSetAudioVolume's dead-if 86665d.
- 8F4B0 CutsceneActorState / WeatherActorState merge (same layout, 8F4B0.c:204/490; needs proof actorCutsceneDispatchEvents runs on actor type 0xC; PolishGlobal8F4B0Names 237b3f89).
- Data split (Polishglobal7130, 2026-11-14, ledger cd20bf04): `extern u8 D_807460AE[][2]` (per-sfx range/factor pairs indexed
  by sfx id, 7130.c:943, read in sfxSlotAllocateSource/Actor and sfxUpdateSourceGroups) starts 2 bytes into the
  `AmbientEmitter D_807460AC[]` label (7130.c:462). Settle the boundary in a data-split pass (splat yaml + `make split`).
- Warning/proto-steer sites with no owner decision yet (audit 2026-11-14, missing blockers M1-M11):
  - 90D80 hudDrawRollingCounter 8c076a: same `retype kept` as f2ca09 (ledger 53b46930) but the record is stale; re-record.
  - Proto-steers never consolidated or stale: 1025E0, 2C910 (ORIG), 36880 1045f7, race/6650, 55B20, 80150 and bonus/2690 are DONE (2026-11-16c); left: 36880 81fdd2 (renderReplaceSegment6Commands), B5EC0 72fa9a (actorTrackBoneTowardTarget).
  - Proto-type views: 103AB0 e73d86 (lensFlareDrawSource takes a file-local type), F56F0 14204c (playerStateQueueCallback arity).


## Round-34 leftovers
- Names not applied: MpSettings.unk0 (mode vs gameMode unclear; its reader func_80714608 is now mpIsMatchType); func_806C9974 -> playerAddHealthDelta (Rev34C proposal, round-35 names step). Proposals not applied at the 2026-11-14 consolidation (director: keep the existing names for now): collisionGetFloorHeight -> collisionGetWaterHeight, collisionGetFloorTriangleNormal -> collisionCheckLedgeGrab (PolishGlobal6AD90Names; evidence .scratch/close/renames.md rows 104/105). Rejected: Actor.unk155 -> subState (one boss file's evidence for 66 files), D_807FF0F2 -> gAudioHeadphonesEnabled (inferred), Actor.unk15F -> hudMode (C8C10 uses unk15F as a 0x80 flag plus a 0x7F phase counter).

## Session 2026-11-14 close leftovers (Lead12)
- Names held (readers agree on the role, names differ, or the proposer did not read every user): RaceParticipant unk3A (route
  position that wraps and bumps the lap: waypointIndex / routePos / checkpoint), unk40 (holds both a normal and a squared distance:
  nextPointDist / waypointDistance, not "Sq"), unk45 (outOfRace / eliminated / disqualified), unk35 (subPhase / phase), unk44
  (missesLeft / gateMisses, counts down); SpawnNode.unk38 -> animSpeedScale (reaches boss/0 and 12E800, unread by the proposer);
  G01Pos unk7/8/9 -> camMode/spawnKind/flags (one file, CC800); D_807FDCA0 (declared `Zone *`, 30+ users); playerSpawnAllPlayers
  (returns whether any goldenBananas[0..7] of player 0's kong is > 0: needs a name); effectSetSpeed's s32 parameter receives
  actor pointers (race/1770, boss/0): owner type review.
- Permuter rows never run (`.scratch/permbatch/`): b1114 9 rows stopped at the wrap-up (25d017, 208f26, d53555, b16157, 716d92,
  1606fa, f3276d, ff3fab, 93489e) + 9bc6c1 (vsprintf: now permutable with the ladder.md `va_arg` stub); b1114b 8 rows not
  attempted + 2 failed setup (row copies predate the D_807FC828 move to actor.h: re-snapshot them at HEAD); list.tsv rows 45-97
  never batched.
- Open tooling fixes (from the session tooling notes):
  - merge_drafts.py lost-symbol guard: add an override (e.g. `--allow-lost SYM` through merge_gate.sh/merge_record.py) or accept a
    dropped data label inside a symbol the draft defines, so data-to-C moves go through merge_record (DT, EA used the `- -` fallback).
  - Shadow headers (sfdiff/fdiff.sh/cwarn `--as`): automatically shadow every `include/*.h` that quote-includes a shadowed header (cpp
    searches the includer's directory first; EG race.h, EI boss.h).
  - `permute.py batch` setup compiles row copies against the current include/: build each row at its base (or re-snapshot copies
    whose file or reached headers changed) so a header merge does not fail older rows (b1114b, D_807FC828).

## Session 2026-11-14b close leftovers (CleanupLead2)
- Types batches DONE 2026-11-16d (batches 6-8: gTextNumberArg, gRdpOutputBuffer, PLANE_DIST, BUTTONS_PRESSED, gPlayerCharacterId[],
  gContReadPending, D_807ECD48 → gPadPressedButtons[], gGlobalOverlayFlags u32, gActorScriptAsset). Not run: RaceParticipant 0x25/0x26
  racer-side aliases (boostTimer/boostPending); one shared VehicleActor (936B0) / RaceCompetitorActor (52B0) type in race.h; 36880
  TexImageCmdSpan as a Gfx[] view (G_SETTIMG/G_SETTILESIZE, file-scope); jetpac/0.c:443 open-coded BUTTONS_PRESSED; CC800 field
  `heldButtonsPtr` holds &gPadPressedButtons[i] (pressed, not held: field rename).
- Names held: PlayerState.unk11C (swimStrokeTimer vs stateTimer; EFDC0 unread), PlayerState.unkC2 -> slopeFrames (D5E10/EFDC0
  unread by the CEAE0 proposer), ActorGlobalState.unk15 -> hitType (boss files unread), RaceParticipant unk35 (statusStep /
  finishStep / subPhase), unk1C -> frameTimer, D_80757044/D_80757064 (default high-score tables), D_807FC952 (= gPlayerInventoryTable
  [0].kong[0].weaponFlags; cannot fold), KongInventory.unk5, Actor.unk155 -> stateTimer (low confidence, rejected before).
- Open hack leads: camPathCommandDispatch C13 body is full=1 (only `lw` vs `lh a1,58(sp)` at 0x1370; Q0553 note);
  csCmdModelStepAnimation `(*st).lastValue` FAKE may go with `cs->unk48[1]` (CsState 0x48 is u8[2] since 86994bb9);
  arcadeSpawnStage1Entities untried ideas in its dossier; hudPauseMenuRender stays next=consolidate (pending KEPT steers).
- Tooling: quality.py `token_meaning` (rename_map) spells an anonymous member's record type with clang's canonical spelling,
  which embeds the header path (temp tree vs checkout), so carry never treats a body touching an anonymous-union field as a pure
  rename (fix: clint.type_sig or strip the location as clint.UNNAMED does; TypesOwner batch_2 lost 6 review rungs to it).

## Session 2026-11-15 close leftovers (Lead6)
- 7130 .bss carve (DEFERRED; HacksfxUpdateLevelAmbient2 record 235be6c2, `.scratch/HacksfxUpdateLevelAmbient2/carve-request.md`):
  7130 owns 0x80770560-0x80770DF0 (drop chunk `165D50_80770560`), D_8077058D/D_80770DC8 become sfxUpdateLevelAmbient statics,
  retiring dead tests 019582/70c91e (Q0857); check Q0184/Q0439 lui sharing of the `D_8077058C[0..2]` reset (D_8077058C shared
  with 114270.c, 478F0.c).
- 13980 `extern u32 gFramebuffers[]` → `u16 *gFramebuffers[]` (Polishglobal13980Rereview record 3c2f89d7): blocked on the 136820
  faultFontInit prototype.
- hudPauseMenuUpdate (ACDC0): ceaa13 and af58f9 FIXED (af58f9 by `s8 x/stickY` packing + `s32 step`, c6bb1ff1, Q1198); the other 5
  register-reuse steers (65898b 38b069 df709b 6151e7 32c920) EXHAUSTED with frame/colouring evidence (Q1199, Q1200).
- Names held: D_80753354 (s16 per-kong turn rate used by CC800/E4090; `gKongTurnRate` is CEAE0's other table: pick a use-based
  name), PlayerState.unkC2, ActorGlobalState 9DD70-only fields (one file read), arcade/0 D_8004BC80/84 (file-local),
  124780 effect sprite symbol_addrs (needs split), D_807505A4 split into two s16[5]
  (touches undefined_syms, 478F0/FCCD0). `.scratch/lead_s1115/names.md` keeps the evidence.

## Session 2026-11-15c close leftovers (CleanupLead3)
- 7130 .bss carve still DEFERRED (above). Frame-capacity ORIG ladder candidate DECLINED (director): ORIG on a reused local still
  needs the home-slot store; the 7 hudPauseMenuUpdate sites stay FAKE with frame/register evidence as `diagnose nohit`.
- Names held (naming.md shared-field bar / macro refusal; evidence in .scratch/lead_s1115c/close.md and the Polish*/Hack* reports):
  CamState unkA0 followDist (201B0; a reference inside CAM_MIN: rename every dry-run position by hand; unkCC/D0/D4 applied
  2026-11-16 as prevTargetX/Y/Z), Actor.unkF2 arcPushYaw (69E60/80150 unread), SchedStruct.unk280 tickCount
  (8 files unread; 91 uses), ModelSlot.unk86 modelKind (63810 unread), ActorGlobalState unk2C/30/34/36
  launchPending/launchSpeedY/launchSpeedXZ/launchYaw (80150 unread), arcade/0 D_8004BC80/84 sStepTimer/sStepPhase (land with
  the arcadeUpdatePlayerEntity carve), ActorCallbackNode.callback anonymous union (types stream).
- Open hack leftovers: vehicleUpdateMotion 54eada (`u8 fl[4]`, diagnose stale after the 936B0 frame change); never-classified
  dead-if items for the Q0908 classifier: controllerAnimSetFromTable, slotQueueStateFadeIn, playerStateTakeDamagePrep,
  transitionSetAudioVolume, zoneCheckActorInside, schedHandleRetrace (5), enemyGridStateStep (2). 90D80 renderHitCounterHUD
  RESOLVED 2026-11-17d: `(const u8 *)"HIT"` untagged by director ruling (literal typed to the const u8 * text API), bb3590b2.

## Session 2026-11-16 close leftovers (CleanupLead4)
- Names held (evidence in `.scratch/CleanupLead/close.md` and dispatch.md): D_8076A0A6 (copied from gPadPressedButtons[0]);
  D_80760590 / D_805FB000 / D_805FB0D0 / func_80741310 are the rsp/asp ucode symbols that include/PR/ucode.h already
  declares (aspMainDataStart, rspbootTextStart/End, aspMainTextStart): replace the D_ externs with them as a types item
  (ucode.h types are `long long[]`); D_80744544 gCheatFlags, D_80750AC4 gMinigameCoinCount, D_80720340 gSmokePuffSprite
  (extern types disagree: types first); PlayerState.unk1A0 aimPitch (936B0/CC800/D5E10 unread by the E4090 proposer);
  "PlayerSlot.unk2C0 sizeMode" (the only include/ unk2C0 is in sched.h: struct unclear); Actor 0xE4/0xE8 pitch/roll swap
  (confirm across users); ActorGlobalState unk24/25/28/F0/F4 grab/hold names (9DD70-only); Actor.unk155 (low);
  CollisionTriF unk24/unk25 slopeType/surface (with the header request below); D_8004BCD0 arcade entity table (no name yet).
- CollisionBoxTri header request (`.scratch/Polishglobal6AD90/header-request.md`, shared struct in collision.h retiring the
  6AD90 CollisionBoxTri / 70FD0 ActorSub140Tri views): DROPPED in 2026-11-16b batch_5 (TypesOwner5, Part A): scalar
  x0..z2 needs a pun for 70FD0's `&curr->out[j + 3]`; x[3]/y[3]/z[3] matches 70FD0 but fails fdiff in 6AD90
  (collisionTestActorBoxFloor, collisionCheckBoxTriangleContainsPointXZ). Probes: `.scratch/TypesOwner/batch_5/partA_req/`,
  `partA_alt/`. Reopen only with a shape that fdiffs in both files. Retype leftovers: 6AD90 365170 FIXED (batch_5, 95740f93: sizePtr u32 *); FE40 0b7e03/#2
  PERMANENT DEBT by director ruling 2026-11-17d (`retype kept`, ledger 70e3f1e4; sites EXHAUSTED): `void *dst` is genuinely
  polymorphic and `(u8 **)&dst` would be a pointer pun. Measured: `u8 *dst` raises W709 at 9 caller args (5A50 4, 6AD90 5);
  gunzip `void **outBufPtr` needs a cast pun in its body (`+=` on void * is a cfe Error, `= slide + outcnt` fdiff 1, stand-ins
  +8 W709 in 5 files); `u8 *out` local fdiff 1 (target passes dst's home sp+0x6c). Probes `.scratch/PolishglobalFE40/`.

## Session 2026-11-16b close leftovers (CleanupLead6)
- Field names HELD (applying them at close would reopen the reviews of every function they touch; batch them with the next
  types item): CamState.unkA0 followDist (CAM_MIN macro reference: apply the dry-run positions by hand), CamState.unkA4
  followDistGoal (201B0); ActorCallbackNode.unk4 subtype, .unkC ownsPayload, .unk10 payload (actor.h, confirm users);
  Actor 0xE4 pitch <-> 0xE8 roll swap (HackvehicleUpdateMotion4 evidence; confirm across users).
- Types items: one shared lerp macro for 201B0 `CAM_LERP` and 478F0 `LERP`; gTextFontSheets `void **` -> `u8 **`
  (Polishglobal100180).
- ORIG check: 6AD90 f64 midpoint reuse a2d087 (box) and 3aa4ac (collisionCheckTriangleContainsPointXZ) still FAKE (frame holds only ten f64); ec388d and 58f1bd FIXED (d78151a9, b52ccd53: dedicated hx once sign ternaries freed a slot).

## Session 2026-11-17e close leftovers (CleanupLead3; supersedes the 2026-11-17d list)
- Polish: 103AB0 playerViewDrawScopeCrosshair `(u16)targetKind` redundant under the ANSI u16 prototype (dd98f7bb).
- Types items: jetpac 0x8002BA80 Gfx split (gCurrentKongInventory 196d0644, gCsCondFlag 23d2164d and the CsState merge 11134d9a LANDED).
- HELD names: RaceParticipant.unk35 phase; PlayerStruct.rect[4] scissor fields; ModelSlot.unk8C stateFlags; PlayerState.unk50 gravityDelayFrames (D5E10 use first);
  BehaviourWorkState.unk2E sfxCooldown (dry-run touches 11 unread files); race/0 D_8002FB10/D_8002FB70 route tables (map 0x52 unnamed); gMinigameCoinCount (above).

## Session 2026-11-17f leftovers (CleanupLead17f; no TypesOwner this session by director ruling)
- jetpac shared head (CleanjetpacUpdatePlayerMovement, ledger 7d1cc6e8; types item, parked): embed one 0x30-byte head struct in
  `JetpacActor` and `JetpacPlayerActor`. The natural `player->head.x` keeps one base and compiles like the plain body; only a
  local `head = &player->head` used for EVERY head access matches, so it retires 1A60 ba285d only if that pointer local is ruled
  ordinary C (SKILL §5.6 pointer-local precedent: 450 firstSetupFlag). It touches every head-field access of JetpacPlayerActor in jetpac.
- 11BC10 effectInterpolationUpdate 6e5dc3 (CleaneffectInterpolationUpdate, merge 45e10058; DECLINED by director ruling, evidence
  only): retyping EffectNode.interp (include/render.h 0x384) from `struct EffectInterpolationState *` to `f32 *` with enum slot
  indices and `+=` updates matches with plain indexing (whole-object OK on a shadow render.h stand-in:
  `.scratch/CleaneffectInterpolationUpdate/render_interp_f32.patch`, `typed_standin_11BC10.c`). An enum-indexed f32 array that
  replaces a named-field struct is a view chosen for codegen, not a better type: do not retry without new type evidence.
- 7130 whole-TU .data + .bss carve LANDED (CleansfxUpdateLevelAmbient, merge 08e85d18, director turn 75). All 7130 data is now in
  C; the sfxUpdateChannels templates are initialised local arrays; split labels are folded. FAKE 8 -> 8. Leftovers:
  - 70c91e is NOT retired. IDO places a function-local .bss static by first reference, so `static u8 D_80770DC8` lands at
    0x80770F38, not 0x80770DC8 (worker carve_7130.txt section 4). Retry only with a new .bss-order lever.
  - TYPES ITEM (interim by director ruling): undefined_syms.us.txt carries D_80770561 and D_80770DD9, interior labels of
    C-defined objects. Fold the outside externs and drop the lines:
    - CEAE0.c `extern u8 D_80770561;` -> D_80770560[1];
    - DONE: BDEE0.c's D_80770629 byte view became gSfxSourceVoice[slot] (PolishglobalBDEE0, merge c274b360; line dropped);
    - 478F0.c `extern u8 D_8077058C;` is a scalar where 7130/114270 use u8[];
    - D_80770DD9: check for remaining asm users, then drop it.
  - TOOLING (§6): objdiff.py text_matches turns symbol_addrs names into absolute addresses on the expected side only, and
    compares own-.bss relocations by raw offset. A carve that moves a TU's .bss base therefore shows `fdiff --reloc-ok`
    exit 1 even when the ROM matches. The ROM gate was the arbiter (GATE_OK 08e85d18; worker raw-word proof 0 unexplained).
- D_807F5E20 shared-globals types item (from CleanmapBspPlaneSideTest, merge c33bc820): 2F550.c now declares
  `extern f32 D_807F5E20[4][3];` (the 4 frustum corner rows; the D_807F5E24/D_807F5E28 split labels are retired there). 55B20.c
  and 5E2F0.c still declare `extern f32 D_807F5E20[]`. Unify them under the shared-globals rule (one declaration in a header,
  each user's accesses as [i][k]), gating every user and checking objdiff on each. Not touched this session by director
  ruling (turn 78).
- SQ macro duplication (types/shared-header item, from CleanactorShowTextOnceWhenNear, merge 8eefc39a): `#define SQ(x) ((x) *
  (x))` is now defined locally in 5 files (global/12E800.c and C4620.c inside function bodies; 5E2F0.c, 68EA0.c, CEAE0.c), and
  race/36B0.c has its own RB_SQ. Move one definition to a shared header (e.g. include/macros.h, if no SQ exists there), drop the
  local copies, and gate every user; it is a text-only change (expected fdiff 0 everywhere).
- HeapBlock allocated-block tag (types item, director ruling HOLD; from CleanheapRegisterSurvivor, header-request at
  .scratch/CleanheapRegisterSurvivor/header-request.md): byte 0x0B of HeapBlock is the low byte of `next` while a block is
  free, and the allocation tag while it is allocated (0 normal, 1 locked, 2 survives an overlay load). Every access is a byte
  view: `((u8 *)p)[0xB]` in heapInitGeneralPool, heapInitBlockPool, heapReleasePool, heapFree, heapFreeDeferred and
  heapRegister/UnregisterSurvivor, and `ptr[-5]` in heapLockBlock/heapUnlockBlock. An anonymous union over `next` adds cfe
  Warning 838 + 649 per declaration, and a named union rewrites all 28 `->next` in 15050.c to `->u.next`. Do it only as a
  file-wide polish/types pass.
- hudPauseMenuUpdate (src/global/ACDC0.c): the hold was LIFTED for one worker (director turn 178). CleanhudPauseMenuUpdate (merge
  54a784f8) ran the hidden-temp census. The nested mapGetHubWorldIndex result temp owned a frame word; routing the call through
  `hubWorld` freed it for `s32 sel` (the map selector), so 65898b is FIXED and `i` is loop-only. The FAKE count is 5 -> 4, all
  EXHAUSTED: c127b7 page and db430c credits reuse sel; 6151e7 limit and 32c920 half reuse flag. Retry only with a new lever.
  The flag reuse is pinned by register colouring: the bools are a0 only while flag also covers the limit region. The
  dossier lists every measured variant.
- A8400 textBoxRender scissor d5a412 (TypesOwner/hack item; from PolishglobalA8400, director ruling turn 162): the second
  scissor is a hand-expanded G_SETSCISSOR word (WRITE_GFX, uly-first operand order), tagged FAKE (pre-existing). The plain
  `gDPSetScissor(dl++, G_SC_NON_INTERLACE, boxLeft, boxTop, boxRight, boxBottom)` gives fdiff 1 (or/sll flip at
  +0xff4..+0xffc); the macro matches with constant-index array reads `box[0..3]`. REFUSED as proposed: an anonymous
  union/struct over ResQueueActorState.boxLeft..boxBottom (0x44..0x53) - IDO 5.3 emits cfe Warnings 838/649 for anonymous
  members (15050 finding), and a plain `f32 box[4]` replacing the four named fields exists only to steer the scissor
  codegen. Retry only with a new reason for an array (another user or asset layout evidence); only A8400 uses the fields.
  Evidence: .scratch/PolishglobalA8400/header-request.md, resqueue.patch (hunk 2), shadow/resqueue.h.
- F9450 shared records (types items, DEFERRED by director ruling turn 164: no TypesOwner this session; from PolishglobalF9450,
  merge cb19a3d9): F9450.c now carries file-local copies of two records other files define, identical to them (fdiff 0):
  - ModelAssetEntry (0x30, placed model of the map's model asset, table 9; 36880.c:33-49, modelAssetGetSubtables): move to
    include/model.h, then drop 36880.c's and F9450.c's copies (merge_drafts prunes the identical typedefs).
  - DropBounceState (customState of the drop-and-bounce pickups; AA960.c:105-112, actorDropBounceExpireUpdate): move to
    include/actor.h (spell the field `struct EffectNode *`, actor.h does not include render.h), then drop AA960.c's and
    F9450.c's copies (by hand: `EffectNode *` vs `struct EffectNode *` spelling). NEW HEADER REFERENCE (PolishglobalAA960b,
    merge afae36b6): include/proto/global/AA960.h now forward-declares `struct DropBounceState;` and declares
    `effectSpawnAttachedSprite(struct DropBounceState *, void *, f32)`. Both copies keep the tag `struct DropBounceState`, so
    the 19 includers (F9450 among them) compile against it; the move must keep that tag. AA960's 12 wrappers now take
    `DropBounceState *state`.
  Hunks and evidence: .scratch/PolishglobalF9450/header-request.md. gridBuildNodeLists / gridCollectActorsInRange carry
  `views blocked` until it lands.

## Session 2026-11-18 close leftovers (Lead20261118; closed at turn 4 on a provider model fallback)
- NEXT TypesOwner batch (director: one batch, not now): (1) PlayerState 0x220..0x228 `f32 unk220[3]` (removes 478F0
  csCmdCameraVectorTargetUpdate abbd3b; request .scratch/CleancsCmdCameraVectorTargetUpdateb/header-request.md, patches
  fix/actor_h.patch + fix/D5E10.patch + fix/E4090.patch, fix copies fix/{478F0,D5E10,E4090}.c at 2291c741, shadow_fdiff.sh; users D5E10
  playerInputHandleBButtonPunch/func_806DF280, E4090 playerInputCheckBButtonTarget; field TYPE change: measure the PlayerState stale cost
  first, gate with the 478F0 body); (2) JetpacSprite (jetpac.h) == TextureDescriptor (render.h) field for field: merge them, then retype
  dlAppendTextureLoad's `void *texture` (callers arcade/0.c, jetpac/1460.c:151; CleandlAppendTextureLoadb).
- READY hack items, not dispatched (re-set base at dispatch, `.scratch/Lead20261118/items/*.json` + mkbrief.py): BDEE0
  behaviourFairyInitPlayerScale goto, jetpac/1460 jetpacGridAddTiledSprite, boot/1630 noExpPakThread, 8F4B0 lightUpdateFromActorLighting +
  playerCameraUpdateFromTarget (new agent name: CleanlightUpdateFromActorLightingb was cancelled on a model fallback, nothing merged).
- Decl consistency: 13980 `extern s8 D_80744510` (lb 0x620) vs 450.c `u8 D_80744510[28]`. ok-fine: architecture/camera "Remaining
  hacks" (3 camComputeEyeFocus gotos, sStepEyeX..sStepLookZ statics) are stale.
- HELD names (close applied every func_/D_ and function rename of the 17f + 18 lists that rename.py accepted): every struct FIELD
  proposal (17f PlayerState/PlayerStruct/ActorGlobalState/ModelSlot/ModelAnim*/Jetpac*/HealthHud lists, 18 PlayerState unk78/unk7C/unk80;
  a field rename needs a lead review of every touched function); slash-form multi-symbol lists (17f D_807444A8/AC/B0/B4 letterbox,
  D_800297F0/D_80029830 critter wing vtx, D_807F5D80.. wipe, D_807F6178/7C env, 10130 func_8060B750/7C4/7D0/6CC); uncertain/optional
  ones (D_80753A08/A18 head heights, effectSpawnDebrisParticles/effectActorCheckGroundScaleSpawn/effectSpawnActorScale, gMenuBonusTimer ->
  gHelmTimer, modelAnimEntrySet*); D_80035B38 (boss/DAA0, saves gPrimaryPlayerActor->unk144: `gBossSavedPlayerUnk144` refused as
  address-shaped). Lists: `.scratch/Lead20261118/names_close.tsv` (applied: names_applied.tsv).

## OPEN functions: `uv run tools/quality.py rank` (full) or `status --file <f>`; round-34 snapshot `.scratch/r34_post_knowledge.txt`.
