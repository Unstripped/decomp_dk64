# Fake-match pass: overlays

Scope: `src/{arcade,bonus,boss,critter,jetpac,menu,minecart,multiplayer,race}/*.c` (40 files, ~35k lines). Branch `fake-match/overlays`, 109 commits on top of `development`. Every commit was made by `tools/merge_gate.sh --commit` after a full-ROM `GATE_OK`. No files outside the scope changed.

## Summary

|Overlay|Candidate rows|Fixed|Suspicious, left alone|Needs human (candidate outcome)|Needs-human table rows|
|---|---|---|---|---|---|
|arcade|35|14|8|13|13|
|bonus|58|33|13|12|14|
|boss|43|23|19|1|13|
|menu|47|21|21|5|5|
|jetpac / critter / minecart|79|38|33|8|9|
|race / multiplayer|55|28|22|5|3|
|**total**|**317**|**157**|**116**|**44**|**57**|

Counts are rows in the per-overlay candidate tables below. One row can cover several sites: a whole file's byte offsets, or every pad local in a function. Rows marked "partly fixed" count as fixed. Fixers did not tag outcomes the same way: boss, for example, marked most items in its Needs-human table as "suspicious-left-alone" in its candidate table. The last column therefore counts rows in each overlay's Needs-human table, each a construct that natural C failed to reproduce after the attempts listed there. The regex pre-scan (`if`-empty blocks, `;;`, self-assign, `register`, `volatile`, `goto`, comma operators, byte offsets, pad locals) found 71 empty-`if` hits, 4 `if (0/1) {}`, 2 `do {} while (0)`, 5 `;;`, 1 self-assign, 2 `register`, 13 `volatile`, 25 `goto`, 312 byte-offset casts and 402 function-local pad declarations. Each fixer then reviewed its files function by function.

### Caveats

- **Arcade commit `9208726` is batched.** It bundles about a dozen arcade fixes (listed under it in the arcade Fixed table) and was gated as a whole: the ROM matched. Every later arcade commit covers one function.
- **Edits to parked code are not checksum-verified.** In arcade, the empty-guard removals in `func_8002CD64` and `func_8002D6FC` (commits `ede301d`, `81fae8f`) are inside `#ifdef NON_MATCHING` blocks. The matching build never compiles those blocks, so the gate only syntax-checks them. The same applies to the struct-access conversions in jetpac's parked functions and to race `func_80028AD0`. Other fixers deliberately left parked blocks alone.
- **Bonus globals are still untyped.** `D_807FBB40`, `D_807FBB44`, `D_807FBB4C` and `D_807FD580` are declared `void *` in `include/`, which is outside this scope. bonus and some race files now reach them through file-local struct views and cast macros (`LA`, `LB`, `BCAM`, `LR3*`) instead of byte offsets. The proper fix is typed declarations in `include/`, recorded under Needs human.
- **Menu was not finished.** The fixer hit its request budget, so the 3E10.c pad-local pass and the `textDrawStringVtx` / `menuSetElementCoordinates` cleanup were not attempted. Those pads are recorded as suspicious, left alone.
- **No new hacks were introduced.** I scanned every added line of the branch diff for `volatile`, `register`, empty `if`, `;;`, `^ 0` and `while (0)`. All 7 `volatile` hits are existing hacks re-typed after a struct fix (jetpac/1A60 `unk30` ×4, critter/0.c `speed`, multiplayer/0.c `sp20` type rename); no new instance appears. Two existing `volatile`s are gone: `volatile s32 pad4C` (bonus/0.c) and `Actor_3340 *volatile sp34` (critter/3340.c).

## Fixed

### arcade

| function | construct removed | natural form | commit |
|---|---|---|---|
| (batch, before per-function rule) | multiple | see rows below | 9208726 |
| ├ arcadeUpdatePlayerAnimation | `^0`, `t`, `ptr` | `((s32)unk10 & 3) == 2` | 9208726 |
| ├ arcadeGameplayLoop/arcadeSpawnStage2Enemies/func_8002EEB8 | `D_8004BCE9[x<<5]` | `D_8004BCD0[x].unk19` | 9208726 |
| ├ func_8002E158, func_80030B08 | `*(f32*)((u8*)&D_8004BCD4 + (p<<5))` | `D_8004BCD0[p].unk4` | 9208726 |
| ├ arcadeCheckStage4Ladders, arcadeDrawNameRegistration | `D_8004BCD4/F4/CEC` | `D_8004BCD0[n]` field | 9208726 |
| ├ arcadeDrawStage4Background | do-while + `(i^0)` | `for` loops | 9208726 |
| ├ func_80030C70, func_80030210, arcadeRenderEntity, arcadeDrawHud guard, `_sprintf`/`arcadeDrawString` `char*`, Gfx** prototypes, D_8004A318 | see above | | 9208726 |
| arcadeDrawBackground | K&R def + empty-arg protos | ANSI def | b6fd425 |
| arcadeDrawLadder | K&R | ANSI | e888f06 |
| arcadeDrawStage1/2/3/4Ladders | K&R | ANSI | b712401, 17d4d06, 9430ed6, edcec7c |
| arcadeDrawGirderSpan | K&R; `if`+do-while; casts | ANSI; `for` | 509fa51, 22e1608, 8e10c2c |
| arcadeCheckStage3Collision | `(ArcadeLift*)` casts, `D_8004BCD0` end | `end = &D_8004BC88[6]` | d20c4a0 |
| arcadeDrawStage1Background | redundant casts | | aee6bcf |
| arcadeDrawStage4Background | redundant casts | | 8dbb920 |
| arcadeDrawNameRegistration | `char *p` alias | use `buf` | 0445f5b |
| func_8002CD64 (parked) | 4 empty guards | removed | ede301d |
| func_8002D6FC (parked) | 2 empty guards | removed | 81fae8f |
| arcadeSpawnStage3Entities | `p = …; *p = …;` lines | one per line | 37cd6b5 |
| arcadeSpawnStage1Entities | multi-statement lines | split (partial) | 7bce133, 0038079 |

The first commit 9208726 batched about a dozen fixes before your reminder; every later one is one function per gate.

### bonus

| function | construct removed | natural form | commit |
|---|---|---|---|
| func_80024E38, bonusRenderCounterHud | byte offsets | file-local `LB3bSnd`, `LB3bInput` and `LB3bState` plus `LB`/`LP`/`LC`/`LD` macros | e0e65e5 |
| bonusControllerUpdate | empty `pv` guard, `volatile` pad | both deleted (`pv` alias itself stays) | 75abe23 |
| bonusControllerUpdate | `(char *)` casts | `char *` locals and local prototypes returning `char *` | c1b3c29 |
| bonusControllerUpdate | `(s32)D_807FBB40` | `camStartPath(void *, …)` | e7a2063 |
| 12A0.c (nine functions, see table 1) | byte offsets, empty if/else, `(u8 **)`/`(s32)` casts | typed `LB3Actor`/`LB3Obj`/`BonusEActor`/`LB3PlayerActor`; `if (!((x) % 32))`; `bonusGetReelSymbol(LB3Obj *, u8)` | 6ce2c5e |
| bonusReelGameUpdate | `(s32)&D_80720CF0` | `func_80714CC0(void *, …)` with `void *D_8074E880[]` | 75dd76b |
| bonusRenderScoreHud, bonusScoreHudUpdate | byte offsets, byte-pointer trick | `BonusEActor9 *arg1`; `(u8)hud->unk4` | 88a25f9 |
| bonusDespawnTarget, bonusTargetUpdate | `u8 *`/`s32 *` casts | `Struct_174` with `unk4[4]` and `unk9`; `bonusDespawnTarget(Struct_174 *, Struct_71B4 *)` | 37e2773 |
| bonusAimAndFire, three sfx call sites | float bit patterns, `(f64)` cast, double literal | `func_806CC190(s16, s16, f32)`, `sfxPlayFromActorDirect(…, f32, …)`; `3.1415927f` | cf876ba |
| bonusTargetGameUpdate, bonusPopupGameUpdate | `D_807FD580` byte offset, `(Struct_71B4 *)t0`, `(u8 *)e` | `BCAM->unk104`; `Actor_BB44 *e`; `t0` typed `Struct_71B4 *` | 83f6164 |
| bonusRenderTargetGameHud, bonusRenderPopupGameHud, bonusRenderCrosshair, bonusSpawnTarget, bonusTargetGameUpdate | casts, copy locals, K&R declaration | typed `Actor_74A0 *arg1`; `arg4->unk0[arg3]`; `idx = (…% 0xFF) % 8` | 96437dd |
| bonusTargetUpdate, bonusTargetGameUpdate, bonusRenderCrosshair | duplicated ternary, `(u32)`/`(f32)` casts | `step = … ? 2 : 1`; narrowed `func_8068C5A8` prototype | 5887f45 |
| func_8002A398, func_80029B9C | `D_807FD580` offset, `(n+n+n)*12` offsets, `(u8 *)t0 + 5`, `[0x26]` | `BB_CAMCTX->unk104`; `*D_807F5FD4 + (n + n + n) + 1`; `(u8)t0->unk4`; `Struct_7548.unk26` | af05b6f |
| func_8002A398 | `(LargeB1_Sub178 *)` cast | `BB2->unk178` is now `void *` | 02ab438 |
| func_80029B9C | redundant self forward declaration | removed | 32b8597 |
| func_80029E54, func_8002A010, func_80028E3C, bonusPopupSpawnActors | byte offsets, split `if (i != 6)`, `f32 c`, wrong `s5` type | `scale = (i != 6) ? 0.25f : 0.04f`; `Point3f *pt`; `BB_C->unkE6 += p40->unkC`; `Actor_BB44 *s5` | df06d9a |
| func_8002CC08 | `WRITE_GFX`/`BDCC_ANIM_TEX`, `(s32)(f32)(x * 4.0)` | `gDPPipeSync`/`gDPSetCombineMode`/`gDPSetRenderMode`/`gSPDisplayList`/`gSPMatrix` | 38c8fbc |
| func_8002BF98 | byte offsets, `(void *)` stores, `(&arr[i])->` | `temp_s5->unk2A[i]`, `BCAM->unk104`, `temp_s0->unk0 = LB4A` | 7e34544 |
| func_8002AD10, func_8002B920, func_8002C8EC | `(f32 *)…+9`, `&= 0xFFFF7FFF`, loop init | `Point3f *p`; `&= ~0x8000`; `for (var_v0 = 0; …)` | 2c7a1b8 |
| func_8002CC08, func_8002B920, func_8002BF98, func_8002AD10 | redundant `(u16)`/`(s16)`/void-pointer casts | removed | bbe4d81 |

### boss

| function | construct removed | natural form | commit |
|---|---|---|---|
| func_800254D0, func_80024FA8 (0.c) | `register`, unused `cur`, byte offset | plain local; `arg3[i] != 0xFF`; `D_807FDC90->unk28` | 60ac00e |
| bossRoundFrame, bossSpawnParticleRing (3840.c) | `(u8*)s0+N`, `sp4C` alias | `&s0->unk4`, `&s0->unk8`; `(s16)arg0` | cf41f18 |
| func_800292B0 (52B0.c) | `zero` local | `0.0f` literals | 95874a4 |
| func_8002A92C, bossSpawnSparkles (6240.c) | `r1` temp, redundant breaks and casts | inlined `randomNonNegative()`; single `break` | 32f21f5 |
| bossSpawnSparkles (6240.c) | `s32 pad[1]` | deleted | 82af293 |
| bossAnimFrameBounceStep, func_8002C5F4 (8520.c) | 3× `goto done`, `rand` temp | if/else; inline `randomNonNegative()` | 5af78d0 |
| func_8002D230 (9230.c) | byte offset ×2 | `D_807FDC90->unk28` | 80a1e70 |
| func_8002DE04 (9C60.c) | byte offset ×2 | `D_807FDC90->unk28` | b30741d |
| func_8002EA7C (A7A0.c) | byte offset ×2, block-local `tbl` | `D_807FDC90->unk28`; reuse `sp28` | ce93504 |
| func_80030EC4 (C920.c) | byte offset ×2 | `D_807FDC90->unk28` | f64c25a |
| bossInterpolateWaypoints (F0D0.c) | raw `+0xE6`, `Boss2D_*` casts | `D_807FBB40->unkE6`, `D_807FDCA0->unk14[i].unkN` | 3b35e9e |
| func_800254D0 (0.c) | m2c casts, `U` suffixes, `*(unk15+sp74)` | `sp74[temp_s1->unk15++]`, plain literals | 6aa0438 |
| func_800254D0 (0.c) | `(s16)(s32)` | `(s16)` | e778a9c |
| func_8002A240 (6240.c) | `(s16)(s32)`, `(f64)(u32)`, `(u8)(u32)` | plain float conversions | 52d20f0 |
| func_80030D50 (C920.c) | `(s16)(s32)` | `(s16)` | 4abe888 |
| bossInterpolateWaypoints (F0D0.c) | `(s16)(s32)` | `(s16)` | f9e2d72 |

### menu

| function | construct removed | natural form | commit |
|---|---|---|---|
| menuDispatchAction | `register`; byte-offset 0x154/0x174 accesses in 0.c | plain `u8 var_v1`, `D_807FBB40->unk154` | 654e865 |
| menuUpdateProgressGrid | double `idx += 1` | `D_80033228[idx++]`, `[idx++]`, `[idx]`, then `idx++` | 654e865 |
| menuDrawProgressGrid | `*(s8*)&D_80033258` | `extern s8 D_80033258` | 654e865 |
| menuUpdateLightFadeActor | `0xFFFFFFCF` | `~0x30` | 4adea98 |
| menuCheckBitgridOtherSlots | `do { ... } while (0)` wrapper | plain `for` loop | baefbb5 |
| menuResetSubmenuState | `s8*` byte offsets | `Struct_80025D14*` with `unkF`/`unkB` | baefbb5 |
| func_80026874 | K&R definition, `goto`/`default: done:` | ANSI 2-param prototype, `break` then shared tail | 41055ae |
| func_80026B28 | `0xBFFFFFFF` mask, `+0x10` offset | `~0x40000000`, `arg0->unk10` | 41055ae |
| 1AF0.c handlers | macros and byte offsets (`unk12`, `unk154/155`, `unk174`, `D_807FC924->unk4`) | struct fields, `u8 *arg1`, pointer `camStartPath` arg | 908c6f8 |
| func_80025B64, func_80025FB4 | unused locals | removed | 748c9fe |
| 3E10.c (31 guards) | empty `if` guards | deleted (one kept, see section 4) | 5d2f521 |
| menuLoadHighScores, menuSaveHighScores | comma loop, `temp_s0` alias | `D_80744548[i].unk0 = ...(i)` | 4b93433 |
| 25 menu actor handlers + menuBossReplayHandleInput | `*(T**)((u8*)arg0 + 0x174)`, K&R | `MenuScreenActor *arg0`, `arg0->unk174` | 38b13cd |
| func_80028834, menuFormatOptionValues, menuUpdateStateDispatch | offsets on `D_807FBB4C`, `D_807FC924`, `D_807ECDEC`, `D_80033F28`, `temp_t0` | struct fields, `D_80033F28[n]` | 0edc806 |

### jetpac / critter / minecart

| function | construct removed | natural form | commit |
|---|---|---|---|
| jetpacGridAddSprite | `if (1) {}` ×3, `i = 2` index trick | `src` pointer plus `for (i = 0; i < 4; i++)` copy loop | f7e1156 |
| jetpacPlaySound | one-line `do/while` with `D_80770E14` sentinel | `for (i = arg0; i < 7; i++)` | 7487aaf |
| jetpacStateSelection, jetpacStateGameplay, jetpacStatePause | `J0aG` cast macro | `jetpacGame.field` | 7487aaf |
| jetpacUpdatePlayerMovement | byte-offset ledge reads | `jetpacGame.ledges[idx].unk28/unk20/unk4` | f2ddd81 |
| jetpacUpdatePlayerMovement, jetpacFireLaser | `J0a2A` and `J1bActor` casts | `JetpacActor *arg0` | f2ddd81 |
| jetpacDrawLaser, jetpacUpdateExplosion, jetpacDrawPlayer | `(s32)color` casts | `u8 *` | 7a14928 |
| jetpacItemsUpdate, jetpacPlaceRocketOnPad/AboveScreen, jetpacBoxOverlapsItems, jetpacDrawItem, func_800285DC, func_800289EC, jetpacUpdateRocketFlight | `(u8 *)&jetpacGame + unk344 * 0x194 + 0x1C/0x30` | `jetpacGame.players[active_player].items[…]` | 1afd014 |
| jetpacSpawnBonusItem, jetpacSpawnFuelPod, jetpacSetRocketSpriteFrames | `(u8 *)arg0 + 0x144/0x148` | `unk144`, `bonus`, `items[3]` | 1afd014 |
| jetpacDrawItem | `*(s32 *)((u8 *)arg0 + 0x20)`, `p` pointer loop, `*(s32 *)&sp58 = …` | `arg0->unk20`, `arg0->sprites[i]`, `J3Color` | 1afd014 |
| jetpacCheckPlayerHit, jetpacBounceOffLedge, jetpacSpawnActor, jetpacKillActorInBox, func_80029F7C | `J4Global` / `J4Global2` casts, `unk1C[2]` raw player array | `jetpacGame.player`, `jetpacGame.ledges[]`, `JetpacPlayer->stage/score` | 78e54a2 |
| jetpacStateGameplay, jetpacStateTakeoff | `((J0aItem *)&sp1C->pad14[…])`, `unk148`, `unk18C` | `sp1C->items[…]`, `sp1C->bonus.unk44(&sp1C->bonus)` | 31e4962 |
| jetpacGridAddSprite, jetpacGridDraw | `pad8[3] + unkB`, `*(s32 *)&item->pad8[0]` | `item->unk8` | 8c20a95 |
| func_80027DC0 | `volatile` local `sp34` | plain local | 13da18b |
| func_80027448 | `J0B2_A` / `J0B2_P` macros over a second struct | direct field access on `Actor_3340` | 13da18b |
| critterDrawWord, critterRenderText, critterShowText, critterUpdateText | `(arg1 + arg3)[0x810]`, `!= (0, 0)`, `*(s16 **)(arg1 + 8)`, `arg4` as loop counter | `TextData` fields, `timers[]`, `mtx[][]`, `i` loop var | c64f41c |
| minecartPlayerCartUpdate | `goto case_1` | if/else with fall-through | 1ca1dc6 |
| func_800280BC, func_8002835C | `goto case_1` + `case_1:` label | fall-through | 1ca1dc6 |
| minecart/0.c, all cart functions | four overlapping cart views, `MC` macro, `pad_2C` | one `MinecartCart` | fce656a |
| critter/0 (sub-agent) | `goto end`, `u8 pad;`, `(0, col)`, redundant `{}`, `var_s3 = NULL;`, redundant casts | see sub-agent report; `idx >= zoneIdx → idx++`, `gDPSetPrimColor(…)` | 25efbf2, 5f649be |
| minecart/25F0 (sub-agent) | per-use casts, CB/CD/C4C/MC macros, comma conditions, duplicated clamps, `AllocSub` byte arithmetic, unused locals | `MIN`/`MAX`, plain expanded conditions, structs | 419d2a6, edf7d96, d93b889, 6d05586, 048c66b |

### race / multiplayer

| function | construct removed | natural form | commit |
|---|---|---|---|
| func_80027920 | `do{}while(0)`, `arg2` reuse | separate `end` local, plain `while` | d00dc8b |
| func_8002B180 | self-assign clamp | `x = (x < 650.0f) ? x : 650.0f` | bb2580b |
| func_8002B180, func_8002AE9C, func_806F4D70 caller | `BBV` byte-view cast | `D_807FBB40->unkXX` with f32 fields | 225c3d1 |
| func_8002A0AC | `goto tail` | `default:` last, fall through from `case 0x2A0` | b0502fd |
| func_800294A8 | byte-offset loop, comma `for` | `RC_A->unk6E[i]`, `RaceC_State *s1`, `u8` proto | 2c986d4 |
| func_800292B0, func_800292D0, func_8002A0AC | raw offsets, `s16 (*)[5]` cast | `RaceC_Actor`/`RaceC_State`/`RaceC_Waypoint` fields | a20c71c |
| func_8002CBEC | empty if/else, `goto next`, `var_v0`/`var_v1` reuse | `for` + `continue`, `red`/`blue` locals | ec50bf3 |
| func_8002E8EC, func_8002E644 | `goto end`, `four` temp | if/else-if chain with one `return`, literal `4` | 411229e |
| func_8002D778, func_8002DA68 | `list0`, `i = 0`, `(&pa->unk4->unk34)[k]`, block temp | `f32 unk34[3]`, function-scope `temp_fa0` | 0075491 |
| func_8002C2E8 | `*((u8 *)arg1 + 0x44)` | `arg1->unk44` | b485761 |
| raceUpdateStandings, func_8002D148, func_8002D224 | redundant `q =`, local extern, `temp_s4` | plain `for` over `arg0` | 63c6372 |
| func_8002DDA0 | uninitialised read, `pad3C` | declaration order `u8 i; f32 ret; s32 found;` | 37b003b |
| func_8002B610, func_8002B6F4, func_8002AE6C | constant temps, `[0x35]`, `+0x174` | inlined constants, typed params | 541f000 |
| func_8002F784 | `!cur && !cur` guard, empty if/else on `first` | `if (!first) { acc += … }` | 8a21234 |
| MpMapEntry users | `+8` offsets, pointer casts | `entry->items`, `->count`, `->ids[i]` | 0a3b15b |
| mpFindModelSlotByType | missing return | `return modelSlotFindByType(…)` | 2fb049d |
| A960.c, all functions | raw offsets, `p += pidx`, `& 0xFF` | struct fields, `u8` return | 278dd35, d0f9058, 99e0dc3 |
| race/1770.c, all 13 functions | raw offsets, `LR3*` macros, double casts | struct fields | f6b6e41 |
| race/36B0.c, all functions | raw offsets, comma operator, `u32` casts, `*(s32 *)` float pun | struct fields, ternary `sign` | 841a2a6, e025f6a, 1aa4c24 |
| multiplayer/0.c, all functions | raw offsets, duplicate views, redundant casts | unified structs | eafc863, 0280156 |

## Type/struct fixes

### arcade

| type | file | functions affected | commit |
|---|---|---|---|
| `_sprintf(char *,…)`, `arcadeDrawString/textDrawString(…, char *)` | arcade/0.c | arcadeDrawNameRegistration, arcadeDrawHud | 9208726 |
| `func_8070E8F0/8070F2FC(Gfx **,…)`, `arcadeDrawLadder(Gfx **,…)`, `Gfx *sp4C/sp60` | arcade/0.c | all background/ladder/entity renderers | 9208726 |
| `D_8004A318` → flat `s32[]` | arcade/0.c | arcadeSpawnStage2Enemies | 9208726 |
| `ArcadeInput` (D_807ECDE8) | arcade/0.c | arcadeUpdatePlayerEntity | not committed (regalloc mismatch) |

### bonus

| type | file | functions affected | commit |
|---|---|---|---|
| `LB3bSnd` (new), `LB3bInput` (new), `LB3bState.unk8` added, `LB3bActor.unk178` now `void *` | 0.c | func_80024E38, bonusRenderCounterHud, bonusControllerUpdate | e0e65e5 |
| `LB3Obj`, `LB3Actor`, `LB3Player`, `LB3PlayerActor`, `BonusEObj`, `BonusEActor` consolidated at file top; `BonusEObj.unk0` is `LB3Actor *`; `unkF0`, `unk15F`, `unk18` and `unk7C/80/84` added | 12A0.c | every function in the file | 6ce2c5e |
| `BonusEActor9` moved above its first use | 9010.c | bonusRenderScoreHud | 88a25f9 |
| `Struct_174` gets `unk4[4]` and `Struct_71B4*` `unk0`; `Struct_71B4` named; `BonusB_Sub84C0` removed | 2690.c | bonusTargetUpdate, bonusDespawnTarget | 37e2773 |
| `BonusB2_Sub178` removed into `Struct_71B4` (`unk20`, `unk27`, `unk29` added); `BonusB_Cam` added; `Struct_174.unk1C` | 2690.c | bonusTargetGameUpdate, bonusSpawnTarget, bonusPopupGameUpdate | 83f6164 |
| `Struct_6940_174`, `BonusA_Actor6940`, `BonusA_ActorCF0` removed into `Struct_7548` (`unk24`, `unk25`); `Actor_74A0.unk178`; `BonusB2_Sub174`/`BonusB_Sub7F14` replaced by `Struct_7548`; `BonusB_Actor7F14` removed | 2690.c | render, target and popup functions | 96437dd |
| `BonusB_Cam104`/`BB_CAMCTX` (new); `Struct_7548.unk26` used | 2690.c | func_8002A398, func_80029B9C | af05b6f |
| `Struct_T0` reused as the `unk178` view | 2690.c | func_80029E54 | df06d9a |
| `LargeB4Spawn.unk0` typed; `BonusC_AD10_S.unk0` retyped | 2690.c | func_8002BF98, func_8002AD10 | 7e34544, 2c7a1b8 |

### boss

| type | file | functions affected | commit |
|---|---|---|---|
| `Boss3B_DC90`: add `u8 unk28[4]` | 0.c | func_800254D0 | 60ac00e |
| `Boss2F_9230_DC90`: add `u8 unk28[4]` | 9230.c | func_8002D230 | 80a1e70 |
| `Boss2F_9C60_DC90`: `u8 unk28` changed to `u8 unk28[4]` | 9C60.c | func_8002DE04 | b30741d |
| `BossWorkState`: add `u8 unk28[4]` | A7A0.c | func_8002EA7C | ce93504 |
| `BossD_DC90`: add `u8 unk28[4]` | C920.c | func_80030EC4 | f64c25a |
| `BossE_F0D0_Actor`: add `s16 unkE6` | F0D0.c | bossInterpolateWaypoints | 3b35e9e |
| `BossE_F0D0_SubStruct`: `unk0` now points at new `BossE_F0D0_SubSub0` | F0D0.c | bossInterpolateWaypoints | 3b35e9e |
| `Boss2D_SubSub0`, `Boss2D_SubStruct`, `Boss2D_Node`: removed | F0D0.c | bossInterpolateWaypoints | 3b35e9e |

### menu

| type | file | functions affected | commit |
|---|---|---|---|
| `MenuRenderActor` (+`unk154`, `unk174`) | 0.c | menuUpdateProgressGrid, menuDrawProgressGrid | 654e865 |
| `Struct_80025D14` (+`unkC`, `unk10`, `unk12`) | 1AF0.c | menuResetSubmenuState, func_80025FB4, func_800262A8, func_80026B28, menuUpdateTransformedWidgets | baefbb5, 908c6f8 |
| `Struct_BB40_58` (+`unk154/155/174`), `MenuWidgetState` unified, `MenuM1_C924` (+`unk4`) | 1AF0.c | func_80026874, func_800270E0, widget fns | 908c6f8 |
| `MenuScreenActor` (`void *unk174`, moved to top), `Menu3R1_Struct174` moved up | 3E10.c | the ~25 handler functions | 38b13cd, 0edc806 |
| `Menu3B_Struct_C924` (+`unk270/274/298`), `MenuStickAxis`, `MenuDispatch174`, `MenuPositionedActor` (+`unk154/155`) | 3E10.c | menuUpdateStateDispatch, func_80028834 | 0edc806 |

### jetpac / critter / minecart

| type | file | functions affected | commit |
|---|---|---|---|
| `JetpacGlobal` (absorbs `J0aGlobalView`), `JetpacPlayer.unk44C` | jetpac/0.c | jetpacStateSelection, jetpacStateGameplay | 7487aaf |
| `JetpacActor` (absorbs `J1bActor`, `J0a2Actor`), `JetpacPlayer`, `JetpacGame` (ledges, player), `J0a2Ledge` | jetpac/1A60.c | jetpacUpdatePlayerMovement, jetpacFireLaser, jetpacUpdatePlayerDeath, jetpacInitPlayer | f2ddd81 |
| `JetpacPlayer`, `JetpacItem`, `JetpacLedge`, `JetpacGlobal` (replace `J3Item`, `J3Inner`, `JetpacInner`, `J3Global`, `UnkStruct_80028340`) | jetpac/3480.c | the player/item/ledge functions | 1afd014 |
| `JetpacGlobal` (`players`, `ledges`, `player`), `J4Ledge` | jetpac/4FC0.c | jetpacCheckPlayerHit, jetpacBounceOffLedge, jetpacSpawnActor, jetpacKillActorInBox, func_80029F7C | 78e54a2 |
| `JetpacPlayer` (`items[4]`, `bonus`), `J0aItem` | jetpac/0.c | jetpacStateGameplay, jetpacStateTakeoff, jetpacStartStage | 31e4962 |
| `JetpacCellItem.unk8`, `u8 *` colour arg | jetpac/1460.c | jetpacGridAddSprite, jetpacGridDraw | 8c20a95 |
| `Actor_3340` (absorbs `J0b2Actor`, `J0b2Sub`) | critter/3340.c | func_80027448, func_80027DC0 | 13da18b |
| `TextData` (+ `timers`, `mtx`, `text`) | critter/4840.c | all four text functions | c64f41c |
| `MinecartCart` | minecart/0.c | minecartPlayerCartUpdate, minecartFollowTrack, minecartApplyJunction, minecartSpawnWheelEffect, and others | fce656a |
| `CritterObj`, `CritterGroup(s)`, `CritterZone`, `CritterZoneShape`, `CritterViewer`, `CritterPlayer`, `CritterZoneRow` | critter/0.c | every function | 5f649be |
| `Actor_25F0`, `PlayerState_25F0`, `MinecartCart`, `MinecartTargetState`, `ModelSub_25F0` | minecart/25F0.c | every function | 419d2a6, edf7d96 |

### race / multiplayer

| type | file | functions affected | commit |
|---|---|---|---|
| `Actor_BB40` position fields s32 to f32; `Race2B180View` deleted; `mathAngleDiscrete` and `func_806F4D70` prototypes corrected | 6650.c | func_8002B180, func_8002AE9C | 225c3d1 |
| `RaceC_*` structs moved to the top; `unk27`, `unk36`, `RaceC_Waypoint`, `unk178`/`unk17C` retyped | 52B0.c | func_800292B0, func_800292D0, func_800294A8, func_8002A0AC | a20c71c |
| `RaceSub4.unk34[3]`, `RaceUnknown174.unk44` | 7BD0.c | func_8002D778, func_8002DA68, func_8002DC24, func_8002C2E8 | 0075491, b485761 |
| `MpMapEntry { unk0, count, items, ids[4] }`; `MpSpawnPointTable`, `MpMapEntryIds`, `MpSpawnPos` deleted | multiplayer/0.c | func_80025654, mpUpdateItemSpawns, func_80025F84, mpUpdate | 0a3b15b |
| `RaceActor`, `RaceActorState`, `RaceWaypoint`, `RaceRoute`, `RaceRouteTable`, `RaceTracker`, `RacePlayerPos` | A960.c | all | 278dd35 |
| `RaceActor`, `RacePathState`, `RaceParticipant`, `RaceAuxState`, `RaceNodeActor` | 1770.c | all 13 functions | f6b6e41 |
| `RaceActor` (with the 0x174 `view` union `RaceViewA`/`RaceViewB`), `RaceCursor`, `RaceState`, `RaceAux`, `Point3f **D_807F5FD4` | 36B0.c | all | 841a2a6 |
| `MpControllerActor`, `MpControllerState`, `MpActor`, `MpKongState`, `MpPlayer`, `MpScore`, `MpViewport`, `MpSettings`, `MpFlagState` | multiplayer/0.c | all | eafc863 |

## Needs human

### arcade

| function | construct | what I tried |
|---|---|---|
| arcadeUpdatePlayerAnimation | `D_8004A764 && D_8004A764` guard | removal swaps v0/v1 for D_8004A764 address |
| arcadeUpdatePlayerEntity | `D_8004BC84 == 0`, `D_8004BC80 && D_8004BC80` guards; `sp44` pun; stick/button byte offsets | removal diffs; f32 prototype for n_alSndpPostEvent breaks callers; ArcadeInput struct with u8/s8 fields |
| arcadeSpawnStage2Enemies | `if (D_8004BCD0) {}` | removal drops a hoisted `lui` |
| func_8002EEB8 | 3× `D_80040540 == 0` guards | removed individually and together: branch/li scheduling changes |
| arcadeDrawHud | `D_8004A83C == 0` guard; scissor via `p = (char*)g++` | `gDPSetScissor`, macro, field-assign variants, all decl permutations: loses one stack slot (0x34 vs 0x30) |
| arcadeFinishStageIntro | `(u8*)&D_8004BCD4 - 4` loop | `D_8004BCD0..&D_8004C6D0` loop changes regalloc |
| arcadeSpawnStage1Entities | `float new_var`; `i = D_8004C71F & 0` | direct `i = 0x24`: breaks everything downstream; first multi-statement line must stay joined (IDO line-based scheduling) |
| arcadeSpawnStage3Entities | `i = D_8004C71F & 0` | same |
| arcadeDrawStage4Background | `step`, `one` locals; `(i ^ 0)` | inlining either changes the loop bound/register |
| arcadeCheckStage3Collision | `(s32)&D_8004BCAC`, `for(;;)`+break | do-while forms and typed pointers all differ |
| func_8002F82C / FE28 / 80030044 | `== (0, 2)`; `x == x*0`; `tmp = 0` | `== 2`, `== 0`, `!`, ternary, temp: all alter sra/sltiu scheduling |
| func_80030A04 | `new_var` reuse | 3 rewrites change FP register assignment |
| arcadeCheckGameOver | `D_8004C720 = 0` inside loop | hoisting changes code |

### bonus

| function | construct | what I tried |
|---|---|---|
| bonusControllerUpdate | `pv = &sp6F; *pv == 3` | Deleting `pv` keeps `sp6F` in a register and grows the frame (0x78 → 0x80). A declared-but-unused `pv` is dropped and changes nothing. A `u8 sp6E[2]` array fixes the frame but shrinks text by 16 bytes. |
| bonusControllerUpdate | `goto tail` / `goto render` | Duplicating the tail changes size. A pre-switch `if (sp6F == 14)` plus fall-through keeps size but changes the switch dispatch. |
| bonusReelGameUpdate | `s32 two = 2` divisor | `2.0f`, `2` and `2.0` all change the code. |
| bonusResetAmmo | `p = (s32)D_8071A038`, `(s32 *)arg0 + i`, `(u8 *)arg0 + i` | A typed alias local, typed temps, inline `(Struct_7548 *)arg0` casts and swapped declaration order. The closest form is one s5/s6 register swap away. |
| bonusAimAndFire | `u8 sp40[1]` | A plain `u8` moves the stack slot from 0x40 to 0x43. |
| func_80029B9C | `if (p2) {}` | All six orderings of the p0/p1/p2 loads with and without the `actor` alias, `p2->unk26[0]` in the condition and a `Struct_7548 *st` temp. Each swaps v0/v1 (9 diffs). |
| func_8002A398 | `if (u) {}` | No guard, `u` declared separately or at function scope, `n` loaded first, inline forms, `n * 3`, `n+n+n`, direct `D_8002D904` read. Each swaps u/n between v0 and v1 (about 9 diffs). |
| func_8002A398 | `((s8 *)&D_8002D900)[4] = (u16)(1 - n)` | `D_8002D904 = …` gives different code. `D_8002D8C0 + 4` gives TEXT OK (exit 3) only, so I did not commit it. |
| func_8002CC08 | `do {} while (0)` in `case 7:` | `break`, `return`, moving the case, `default:`, dropping it and an if-chain. Each changes the epilogue or leaves a 4-byte ghost slot. |
| func_8002AAA4 | `new_var` alias | Direct `temp_v1->unk174->unk4 = 8` and `s32 pad`. Both flip the loop-count register. |
| func_8002B920, func_8002C8EC | `var_v0 = 1` as loop exit | A real `break` grows text by 16 bytes. Moving the `var_v0 = 0` init into the `for` breaks the second function. |
| func_8002BF98 | dead store `temp_s0->unkC = 2` | Removing it changes the code. The init loop in `for (i = 0; i < 1; i++)` form also breaks. |
| func_80029E54 | `X = &D_8002D8CA - 1` | `(&D_8002D8CA)[i - 2]` changes the address and offset layout. |
| include/ (not edited) | `D_807FBB40`/`D_807FBB44`/`D_807FBB4C`/`D_807FD580` are untyped `void *` | Out of scope; file-local views and macros stand in for a real typed declaration. |

### boss

| function | construct | what I tried |
|---|---|---|
| func_8002FF74 (B100.c) | `case 0x29: if (BOSS_ACTOR->unk155 == 0) {}` | Replacing it with a bare `break;` is 32 bytes short. The original emits `lbu unk155; bnezl; move a0,s0; b; move a0,s0`, which only an actual read of `unk155` reproduces. No natural body fits; probably a stripped body. |
| bossScriptStep (3840.c) | 4× `goto block_16` | No goto-free form without duplicating the shared tail. I tried the pointer-temp change on `case 0x5C` instead: it fails. |
| func_80029468 (52B0.c) | `goto block_28` | Merging cases 0x28/0x2A/0x46 into one case with an if/else (`!= 0x46` first, then `== 0x46` first): both build 16 bytes larger. |
| func_80030EC4 (C920.c) | `unk155 = 0; unk155 = 1;` | Dropping the dead store: `.text` and `.rodata` mismatch. |
| func_80030D50 (C920.c) | repeated `sp20 = sin(...)` | Single compute: `.text` 48 bytes short. |
| func_80024000, func_800253AC (0.c) | `(void*)(s32)&sym` cast | Passing `&sym` directly leaves the relocations mismatching. |
| func_80024000 (0.c) | `sp48 = D_8003598C` struct copy in the loop | Indexing the global directly: `.text` 16 bytes short. |
| func_800336C0 (F0D0.c) | `(f32)(f64)sp24` | Plain `sp24`: `.text` 16 bytes short. |
| bossSetRandomObjectPair (F0D0.c) | `(val = arr[idx])` in the loop condition | Hoisting the assignment into the loop body: `.text` 32 bytes short. |
| func_8002C520 (8520.c) | `f32 pad`, `sinVal`, `fArg1` | Dropped `fArg1`, dropped `sinVal`, dropped the pad (3 separate attempts): all fail on `.text`. |
| bossPhaseTick (A7A0.c) | `(other = …)` inside the `if` | Two hoisted forms both fail. |
| bossAttachActor (9C60.c), func_8002E9B8 and func_8002EA14 (A7A0.c), `case 0x5C` (3840.c) | single-use `sp1C` / `p` pointer temps | Inlining the field reads after the calls changes the output. |
| Pad locals in func_8002413C, func_800254D0, case 0x2C `pad` (0.c), func_80030D50 (C920.c), func_8002D230 (9230.c), func_8002DE04 (9C60.c) | `s32 pad` / `pad[N]` | Removed once each: same `.text` size but the stack layout differs, so they reproduce the original slots. Left as frame padding. |

### menu

| function | construct | what I tried |
|---|---|---|
| func_80032550 (E550.c) | `do { if (...) {...} } while (0)` | plain `if`, combined `&&` condition, nested `if`s; all differ in branch-likely and register use |
| func_80026B28 (1AF0.c) | `sp2C = -1; if (sp2C) {}` | init at declaration, init reordered, init before `sp24`; all fail, the empty guard is required |
| menuHandleSoundOptionsInput (3E10.c) | `if (D_80033F28 && D_80033F28) {}` | removed it; `D_807550C8` register changes in `func_8002CB18` |
| menuInit (3E10.c) | `for (D_8076A0D0[0] = 0, i = 0; ...)` | store hoisted before the `for`; fails |
| menuSetElementCoordinates (3E10.c) | `four`/`d1`/`d2` temps, byte-offset stores | `D_80033F68[arg1] = arg2 * 4.0f - 32.0;` etc. fails; not committed |

### jetpac / critter / minecart

| function | construct | what I tried |
|---|---|---|
| jetpacUpdateExplosion | `volatile s32 frame` | Plain `s32 frame` shifts the float constant loads and the stack layout (4504 differing lines). Adding a `pad` local also failed. |
| jetpacUpdatePlayerMovement | `(*(volatile s32 *)&J0a2A->unk30)` ×4 and the `u` temp | Plain reads give 400 differing lines. Dropping `u` and branching on `arg0->unk30` gives 2255 differing lines. Each is paired with the `u = unk30` assignments across all five branches. |
| jetpacCheckAabbOverlapWrapped, jetpacIsOverRocket | `volatile int` return type (cfe warns it has no effect) | Plain `s32` plus the if/return form, `&&` expression and ternary variants for IsOverRocket mismatch (~410-470 diff lines); the `if/return` variants for Wrapped mismatch (956-1220 lines). |
| jetpacUpdateRocketFlight | `if (!t) {}` | Removal alone, a split loop, `item[i]` indexing and a different post-increment order all mismatch (270 to 1730 diff lines). The guard is only retained because the matching one-liner (statements on one source line) reproduces the scheduling. |
| jetpacInitLedge | comma expression `arg0->unk28 = (arg0->unk24 = …, arg2 + 12)` | Splitting into two statements, swapping the order, and hoisting from the `unk1C/unk20` stores all mismatch (20 to 50 diff lines in the store order). |
| critterSteerToTarget | `*(volatile f32 *)&obj->speed - old` | Removing `volatile` changes the reload after the store, in both the raw and struct versions. `obj->speed += spd; obj->accel = obj->speed - old;` picks a different register (`f2` vs `f0`). |
| critterSteerToTarget | `(u8)use_y` | Dropping the cast, or declaring `u8 use_y`, changes the frame size. |
| minecartSetTargetAheadOfPlayer | `s32` return type with no `return` | Changing to `void` matches in the function itself but moves register allocation in the caller (22 diff lines). |
| minecartFollowerChildBehaviour | `s16 v` read-modify-write of `sp68->unk2C` | `if (v != 0)` and a case-6 `v` form give 708 diff lines; the `unk2C--` form is off by 10 lines of register allocation. |

### race / multiplayer

| function | construct | what I tried |
|---|---|---|
| race/6650.c func_8002B180 | `if (BBV->unk7C) {}`, `if (var_fv1) {}`, `f32 sp54[1]` | Removing either empty if changes the `sqrtf` result register ($f2 to $f16) and the later float allocation. A fully natural rewrite lost the `s32` to `f32` to `s16` round trip and the stack home of `sp58`. A scalar `sp54` drops the stack spill. The f32 type fix did not remove the need for them. |
| race/7BD0.c func_8002D778 | `if (!t->unk1C && !t->unk1C && !t->unk1C) {}` | Removal alone changes the `lhu` temp from v1 to v0 in case 4. Adding `(u32)` to that case, or removing the `(u32)` casts elsewhere, is worse. |
| multiplayer/0.c func_80025654 | `MpSpawnPoint * volatile sp20` | A plain local goes to s0 instead of the stack home, so the code is 16 bytes smaller. Also tried typing `MpMapEntry` so the volatile reads `->items`. |

## Suspicious names noticed (not changed)

### arcade

`D_8004C720` (set in a clear loop), `sp44`/`sp4C`/`sp60`/`sp28`/`sp38` locals used as real variables, `arcadeUpdatePlayerEntity` macros `E`/`P`, `L_tail2`, `new_var`, `D_8004BC88`/`D_8004BCAC` (lift array, also declared as `ArcA1_Bar` under NON_MATCHING, which now produces a harmless cfe 709 warning in the -DNON_MATCHING compile).

### bonus

- Register- or address-derived names: `sp6F`, `sp6E`, `sp68`, `sp67`, `sp60`, `sp54`, `pad5C`/`pad58`/`pad50`/`pad4C`, `sp4C` in `0.c`/`12A0.c`.
- `sp50`, `sp48`, `sp44`, `sp40`, `sp3C`, `var_a3`, `temp_v1`, `temp_a1`, `s2`, `s3`, `s5`, `v0`, `t3c`, `t0`, `p40`, `new_var`, `fv0`/`fv1`/`ft5`, `temp_s5`, `temp_s0`, `e1..e3`, `d1..d3` in `2690.c`.
- `BonusB_Par8E3C`, `BonusB_Sub8E3C`, `BonusC_9E54_S`, `Struct_174`, `Struct_7548`, `Struct_71B4` are address-derived type names.
- `D_8002D900`, `D_8002D904`, `D_8002D8C0`, `D_8002D8CA` look wrongly split: the real data appears to be a 6-entry table at `D_8002D8C8` plus a combined byte and short object.
- `unk2A[1]`, `unk2A[2]` and `unk2D[2]` arrays are only ever indexed to 0.
- `bonusReelNextRound(LB3Obj *arg0)` has an unused parameter, but callers need it to set `a0`.
- ok-fine notes recorded: `notes/ido-fake-match-removal-bonus-0-12A0-9010`, `-bonus-2690` and `-bonus-2690-tail`.

### boss

- `52B0.c`: `pad48` is used as a real temp (clamped velocity).
- `3840.c`: `block_16` label and `sp2E` (used as the return value).
- `52B0.c`: `block_28` label.
- `A7A0.c`, `C920.c`: `sp178` names a local after the actor offset 0x178.
- `0.c`: `sp6E`/`sp6F` locals; `Boss2A_Struct_*_4300` / `_4FA8` repeated cast typedefs for the same globals.
- `0.c`: `pad_top` / `pad_mid` / `pad_bot` / `pad` (see Needs human).
- `6240.c`: `sp7E`/`sp7F` are flag locals.
- `8520.c`: `BossA_Struct_807FDC90.unk28` is an `s32` flags field, while other overlays use `D_807FDC90->unk28` as a buffer.
- `C920.c`: `func_80030920(s32 arg0)` is called as `func_80030920((s32)sp178)` but `arg0` is unused.
- `F0D0.c`: `bossSetRandomObjectPair` repeats `D_80035BDC[idx]` six times.

I also wrote a short note on these findings to ok-fine as `notes/ido-fake-match-removal-boss`. Remaining fake-match checks on boss code beyond the above would need a human reading the NON_MATCHING blocks.

### menu

- `func_800262A8`, `func_80025FB4`, `func_80026874`, `func_80026B28`, `func_80026DAC`, `func_800270E0`, `func_80030894`: unnamed.
- `menuApplyPurchase`: second parameter is unused.
- `menuDecodeAddressConstant`: anti-piracy obfuscation.
- `sp2C`/`sp24`/`sp3C`/`sp44`, `a`/`b`/`c`/`d`: stack-offset names on ordinary locals in 1AF0.c and 3E10.c.
- `menuCheckSaveFile(u8 arg0)`: K&R, left untouched.
- `D_807FBB44`/`D_807FBB4C`/`D_807FBB40`: the same actor global re-viewed through different local structs in several files.

### jetpac / critter / minecart

- `JetpacPlayer.unkC`, `unk144`, `unk1C` (jetpac/0.c, 3480.c) are not yet named.
- `JetpacLedge` has `unk0/unk4/unk8/unkC` and `unk1C…unk30` and no semantic names; `unk30` is the width in 8-pixel tiles.
- `JetpacActor.unk14` (state, 0-4), `unk18` (direction), `unk44` (score value), `unk48` (update callback) have no names.
- `jetpacGame` fields `unk790` (frame counter), `unk78C` (state id), `unk794` (frame delay) are unnamed.
- `func_80027728`, `func_80027EC0`, `func_80025700`, `func_80028E88` are parked and still carry splat names.
- `D_8002F060` (player colour, actually `jetpacGame.player.color`), `D_8002F054` (player y), `D_8002F064` (state) are absolute names for fields of `jetpacGame.player`; I did not rename them.
- In critter/0: `func_80026A5C` and `func_80026904` (steer callbacks), `func_8002601C` (zone activation), `CritterZoneShape.unk0…unk10`, `CritterZone.unk6/unk28`, `CritterObj.turnRate`.
- `Struct_DC90`, `Struct_DC9C`, `StructBB70` in minecart/25F0 keep splat-style names.
- `MinecartCart` in minecart/25F0.c is a separate, smaller struct from the one in minecart/0.c (they are not shared across files).

The sub-agents also recorded their findings in ok-fine notes `notes/ido-fake-match-removal-critter-0` and `notes/ido-fake-match-removal-minecart-25F0`.

### race / multiplayer

- `race/6650.c`: `func_8002B180` locals `var_ft5`, `var_fv1`, `pad` (really the owner struct), `sp_angle`; typedefs `Struct_sp5C`, `Struct_sp58`, `Struct_sp54`, `Struct_arg0`.
- `race/7BD0.c`: `RaceUnknown174` and `RaceStruct3` describe the same per-participant state yet are used interchangeably through casts, and the `unk88` actor pointer overlaps the matrix array at 0x50.
- `race/1770.c`: `func_80026F04` pad (the comment that its stack home is needed is kept).
- `race/52B0.c`: `RaceC_*` structs duplicate `Actor_BB40`, `Struct_sp58` and others in `6650.c`; `sp2C`, `sp34` are reused temporaries.
- `multiplayer/0.c`: `mpUpdateItemSpawns` has an unused `sp80`.

## Appendix: full candidate tables

### arcade

| file:function | line (orig) | construct | conf | outcome |
|---|---|---|---|---|
| arcadeUpdatePlayerAnimation | 2244 | `if (D_8004A764 && D_8004A764) {}` | high | needs-human (removal swaps v0/v1) |
| arcadeUpdatePlayerAnimation | 2344 | `(t ^ 0) == 2` + reused `t`, `ptr` alias | high | **fixed** |
| arcadeUpdatePlayerEntity | 2379 | `if (D_8004BC84 == 0) {}` | high | needs-human (removal changes code) |
| arcadeUpdatePlayerEntity | 2598 | `if (D_8004BC80 && D_8004BC80) {}` | high | needs-human |
| arcadeUpdatePlayerEntity | 2372 | `f32 sp44` + `*(s32 *)&sp44` punning | med | suspicious-left-alone (changing callee to f32 broke matching) |
| arcadeUpdatePlayerEntity | many | `D_807ECDE8[2/3]`, `*(u16*)D_807ECDE8` byte offsets | med | tried `ArcadeInput` struct: regalloc differs; left alone |
| func_8002CD64 (parked) | 2713/2729/2732/2791 | 4 empty guards | high | **fixed** (removed) |
| func_8002CD64 (parked) | 2725 | `goto L_tail2` | med | suspicious-left-alone (parked, not matched) |
| func_8002D6FC (parked) | 2912/2929 | 2 empty guards | high | **fixed** |
| arcadeSpawnStage2Enemies | 4047 | `if (D_8004BCD0) {}` | high | needs-human |
| func_8002EEB8 | 3328/3355/3366 | `if (D_80040540 == 0) {}` ×3 | high | needs-human |
| arcadeDrawHud | 4160 | `if (D_8004A83C == 0) {}` | high | needs-human |
| arcadeDrawHud | 4303 | `if (&D_8004BBF0[0] != 0) {}` | high | **fixed** |
| arcadeDrawHud | 4150 | `p = (char*)g++; ((Gfx*)p)->words…` scissor via aliased `p` | med | needs-human |
| arcadeFinishStageIntro | 643 | `for(;;)` over `(u8*)&D_8004BCD4 - 4` | med | needs-human |
| arcadeInitTitleScreen | 404 | `for (e = …;;)` + break | low | suspicious-left-alone |
| arcadeSpawnStage1Entities | 1304,1319 | `float new_var`, `i = D_8004C71F & 0; i = i + 0x24` | high | needs-human |
| arcadeSpawnStage1Entities | 1332 | multi-statement lines | med | **partly fixed** |
| arcadeSpawnStage3Entities | 1483,1485.. | same `& 0`; `p = …; *p = …;` | med | `;`-lines fixed; `& 0` suspicious |
| arcadeCheckStage3Collision | 1862-1876 | `(ArcadeLift*)` casts, `(s32)&D_8004BCAC`, `; ;` | med | **fixed** (casts, `end`); `(s32)&D_8004BCAC` and `for(;;)` left (needs-human) |
| arcadeDrawStage4Background | 1224 | `step`/`one` locals, `(i ^ 0)` | high | **fixed** do-whiles→for; `step`, `one`, `^ 0` remain (needs-human) |
| func_800275E8 (parked) | 1187 | `for (bar…;;)` | low | suspicious-left-alone |
| arcadeCheckStage4Ladders | 2118 | `D_8004BCD4`/`D_8004BCF4` | med | **fixed** (→ `D_8004BCD0[0/1].unk4`) |
| arcadeRenderEntity | 2159 | stray block `{ f32 scale; …}` | med | **fixed** |
| arcadeDrawBackground etc. | 712-892 | K&R definitions / empty-arg prototypes | med | **fixed** |
| func_8002F82C | 3503 | `== (0, 2)`, `(x/32) == (x/32)*0` | high | needs-human |
| func_8002FE28, func_80030044 | 3549/3584 | `x == x*0`; `tmp = 0; if (… != tmp)` | high | needs-human |
| func_80030C70 | 3807 | comma expr | high | **fixed** |
| func_80030210 | 3611 | `cond` temp | med | **fixed** |
| func_80030A04 | 3767 | `new_var` reused | low | suspicious-left-alone (every rewrite changes FP regs) |
| func_8002EEB8, arcadeDrawHud, arcadeDrawTitleText, arcadeDrawStage2Background, arcadeCheckGameOver, func_800303B8/30880 | — | pad/frame locals (`sp4C`, `sp60`, `sp28`, `n`…), `(u8)` casts | low | suspicious-left-alone (frame padding) |
| arcadeDrawNameRegistration | 4062 | `char *p` alias of `buf` | med | **fixed** |
| arcadeDrawStage1/4Background, GirderSpan | — | redundant `(s16)(s32)` / `(s16)` casts | med | **fixed** |
| arcadeSpawnStage2Enemies | 4037 | `((s32*)D_8004A318)[r*2]` cast | med | **fixed** (flat `s32[]`) |

### bonus

| file | function | line (original) | construct | confidence | outcome |
|---|---|---|---|---|---|
| 0.c | bonusControllerUpdate | 375 | `if (!pv && !pv && !pv) {}` | high | fixed |
| 0.c | bonusControllerUpdate | 147 | `volatile s32 pad4C` | high | fixed |
| 0.c | bonusControllerUpdate | 414 | `pv = &sp6F; *pv == 3` alias | high | needs-human |
| 0.c | bonusControllerUpdate | 182, 305, 309 | `goto tail` / `goto render` | medium | suspicious-left-alone |
| 0.c | bonusControllerUpdate | 143-146 | `pad5C`, `pad58`, `pad50`, `pad4C` | low | suspicious-left-alone (frame padding; removing any breaks the match) |
| 0.c | bonusControllerUpdate | 224-263 | `(char *)sp68/sp60/sp54` casts | medium | fixed |
| 0.c | bonusControllerUpdate | 399 | `(s32)D_807FBB40` cast | medium | fixed |
| 0.c | bonusControllerUpdate | 301-334 | clamp ternary repeated three times with a call inside | low | suspicious-left-alone |
| 0.c | func_80024E38 | 498-587 | byte offsets on `D_807FBB40`/`D_807FBB4C`/`D_807FDC9C`/`D_807FD580` | medium | fixed |
| 0.c | bonusRenderCounterHud | 14, 22-23 | byte offsets on `arg1` | medium | fixed |
| 12A0.c | bonusReelGameUpdate | 324 | empty-then `if (…%32) {} else {…}` | high | fixed |
| 12A0.c | bonusRenderReelHud, bonusSpawnReel, bonusGetReelSymbol, bonusReelNextRound, bonusInitActors, bonusEndWin, bonusEndLose, bonusReelGameUpdate | 10-82, 170, 298, 313, 430-444 | byte offsets and casts on `D_807FBB40`/`D_807FBB44`/`D_807FBB4C` | medium | fixed |
| 12A0.c | bonusReelGameUpdate | 264, 306, 310, 353, 357 | `(u8 **)obj`, `(s32)obj` casts | medium | fixed |
| 12A0.c | bonusReelGameUpdate | 229 | `(s32)&D_80720CF0` | medium | fixed |
| 12A0.c | bonusReelGameUpdate | 167-169 | `s32 two = 2` used only as `(f32)two` divisor | medium | needs-human |
| 12A0.c | bonusReelNextRound | 68 | unused param `arg0` | low | suspicious-left-alone |
| 12A0.c | bonusReelUpdate | 414 | `6.2831854820251465` literal | low | suspicious-left-alone |
| 9010.c | bonusRenderScoreHud | 31, 49 | byte offsets on `arg1` | medium | fixed |
| 9010.c | bonusScoreHudUpdate | 140, 144 | `*((u8 *)&hud->unk4 + 1)` | medium | fixed |
| 9010.c | bonusScoreHudUpdate | 168 | `s32 shift = 0; if (..) shift = 1;` | low | suspicious-left-alone (single-expression form changes the code) |
| 2690.c | bonusDespawnTarget, bonusTargetUpdate | 475, 952-977 | `u8 *`/`s32 *` casts | medium | fixed |
| 2690.c | bonusResetAmmo | 480-505 | `p = (s32)D_8071A038`, `(s32 *)arg0 + i`, `(u8 *)arg0 + i` | medium | needs-human |
| 2690.c | bonusAimAndFire | 519 | `u8 sp40[1]` used as a scalar | medium | needs-human (a plain `u8` moves the slot from 0x40 to 0x43) |
| 2690.c | bonusAimAndFire | 526-528 | `0x41200000`/`0x40A00000` float bits, `3.1415927410125732`, `(f64)` | medium | fixed |
| 2690.c | func_8002BF98 etc. | 1701-1762 | `0x40400000`/`0x3F800000` float bits for `sfxPlayFromActorDirect` | medium | fixed |
| 2690.c | bonusTargetGameUpdate, bonusPopupGameUpdate, func_8002A398, func_8002BF98 | 642, 803, 1415, 1972 | `*(void **)((u8 *)D_807FD580 + 0x104)` | medium | fixed |
| 2690.c | bonusTargetGameUpdate | 660-706 | `ang2` copy local, `r`/`idx` pair, `(u32)`/`(f32)` casts | medium | fixed |
| 2690.c | bonusTargetGameUpdate | 709 | `(Struct_71B4 *)t0` call cast | medium | fixed |
| 2690.c | bonusSpawnTarget | 452-472 | `((void **)arg4)[arg3]`, redundant `(f32)` casts | medium | fixed |
| 2690.c | bonusTargetUpdate | 956-965 | duplicated ternary plus `step` if/else | medium | fixed |
| 2690.c | bonusPopupGameUpdate | 867-870 | `((u8 *)e)->unk174[0x1C]` byte offset | medium | fixed |
| 2690.c | bonusRenderTargetGameHud, bonusRenderPopupGameHud | 313, 398 | `(Actor_74A0 *)arg1` casts | medium | fixed |
| 2690.c | bonusRenderCrosshair | 216 | stale K&R forward declaration | low | fixed |
| 2690.c | bonusRenderCrosshair | 270 | `s32 pad;` | low | suspicious-left-alone (frame padding) |
| 2690.c | bonusRenderCrosshair | 278-281 | `(u16)`/`(s16)` casts at `func_8068C5A8` calls | medium | fixed |
| 2690.c | bonusRenderTargetGameHud | 303-308 | `pad1[4]`, `pad2[6]`, `pad3[4]` around `sp64`/`sp48`/`sp34` | low | suspicious-left-alone (frame padding) |
| 2690.c | bonusRenderPopupGameHud | 393-394 | single-use `temp_v0`/`temp_v1` chain | medium | suspicious-left-alone (collapsing it moves regalloc to t2/t3) |
| 2690.c | bonusPopupGameUpdate | 772-773 | `y`/`z` temps | low | suspicious-left-alone |
| 2690.c | func_80029B9C | 1197 | `if (p2) {}` | high | needs-human |
| 2690.c | func_80029B9C | 1190-1192 | `((u8 *)actor->unk174)[0x26]`, `actor = arg1` alias, `p0`/`p1` both `= arg1->unk178`, redundant self forward declaration | medium | `[0x26]` and forward declaration fixed; `actor` alias and `p0`/`p1` suspicious-left-alone |
| 2690.c | func_8002A398 | 1451 | `if (u) {}` | high | needs-human |
| 2690.c | func_8002A398 | 1253-1305 | `D_807FD580+0x104`, `(n+n+n)*12` byte offsets, `(u8 *)t0 + 5`, `& 0xFFFF` on `s8` store, `(LargeB1_Sub178 *)` cast | medium | fixed (the `s8` store became `(u16)(1 - n)`, still an odd cast) |
| 2690.c | func_8002A398 | 1304 | `((s8 *)&D_8002D900)[4] = …` | medium | needs-human (`D_8002D904 = …` changes the code) |
| 2690.c | func_80029E54 | 1241-1259 | `void *a`, `(Actor_BB44 *)a` casts, `s8 *base`, `(base+8)[…]`, two `if (i != 6)` blocks | medium | fixed |
| 2690.c | func_80029E54 | 1240 | `X = &D_8002D8CA - 1` | low | suspicious-left-alone |
| 2690.c | func_8002A010 | 1259-1304 | `(f32 *)((u8 *)*D_807FD5FD4 + …)`, `f32 *p`, `u4` alias | medium | fixed |
| 2690.c | func_8002A010 | 1289-1291 | `v = sp50->unk0` alias, `var_a3` flag set via `= 0; if (…) = 1;` | medium | suspicious-left-alone (inlining gives 96–135 diffs) |
| 2690.c | func_80028E3C | 1091 | `f32 c` temp, `(f32)BB_C->unkE6 + …`, `f64 v`, `1.0` double for an f32 param | medium | `c` and `unkE6` fixed; `v` and the double literal suspicious-left-alone |
| 2690.c | bonusPopupSpawnActors | 1004-1022 | `s5` typed as the wrong struct with a cast, `s5` alias of `D_807FBB44`, `(BonusB_Sub8648 *)` casts | medium | wrong type fixed; alias and casts suspicious-left-alone |
| 2690.c | func_8002AAA4 | 1543 | `new_var` single-use alias | medium | needs-human |
| 2690.c | func_8002AD10 | 1593-1608 | unused `Actor_74A0 *a`, `(f32 *)*D_807F5FD4 + 9`, casts | medium | fixed (the unused local is now `s32 pad`; removing it shifts the frame) |
| 2690.c | func_8002B920 | 1708, 1755, 1764 | `(s16)` casts, `var_v0 = 1` loop exit, `&= 0xFFFF7FFF` | medium | casts and mask fixed; loop exit needs-human |
| 2690.c | func_8002C8EC | 2107-2151 | six unused `e1..e3`/`d1..d3`, `var_v0 = 1` loop exit, `&= 0xFFFF7FFF` | medium | mask fixed; locals suspicious-left-alone (frame padding); loop exit needs-human |
| 2690.c | func_8002BF98 | 1921-2080 | `D_807FD580+0x104`, `(u8 *)temp_s5 + 0x21`, `p[0x2A]` loops, `*(void **)temp_s0`, `(&D_807FC924[..])->`, `(s16)` cast | medium | fixed |
| 2690.c | func_8002BF98 | 1989, 1921 | dead store `unkC = 2`; `sp84..sp74` reused for unrelated values | medium | needs-human / suspicious-left-alone |
| 2690.c | func_8002CC08 | 2168-2199 | `WRITE_GFX`/`BDCC_ANIM_TEX` macros, `(s32)(f32)(sp80 * 4.0)`, `(s16)`/`(u16)` arg casts | high | fixed |
| 2690.c | func_8002CC08 | 2204 | `do {} while (0)` in `case 7:` | high | needs-human |
| 2690.c | func_8002BE44 | all | none found | n/a | clean |

No `goto`, `register` or `volatile` locals remain anywhere in `src/bonus` except the two `goto`s kept in `bonusControllerUpdate`.

### boss

| file | function | line | construct | confidence | outcome |
|---|---|---|---|---|---|
| 0.c | func_800254D0 | 768 | `register Boss3B_178 *temp_s1` | high | fixed |
| 0.c | func_80024FA8 | 480-504 | unused `u8 cur` assigned in the `do…while` condition | high | fixed |
| 0.c | func_800254D0 | 809 | `(u8*)D_807FDC90 + 0x28` | medium | fixed |
| 0.c | func_800254D0 | many | `U` literal suffixes, `(u8)` and `(s32)(s32)` casts, `*(unk15 + sp74)` plus separate `+1` | medium | fixed |
| 0.c | func_800254D0 | 898 | `(s16)(s32)` casts | medium | fixed |
| 3840.c | bossRoundFrame | 623-624 | `(u8*)s0 + 4` / `+ 8` | medium | fixed |
| 3840.c | bossSpawnParticleRing | 476-480 | `sp4C = (s16)arg0` alias | medium | fixed |
| 52B0.c | func_800292B0 | 31 | `f32 zero = 0.0f` local used as an argument | medium | fixed |
| 6240.c | bossSpawnSparkles | 243 | single-use temp `r1` | medium | fixed |
| 6240.c | func_8002A92C | 506/515 | redundant `break;` | medium | fixed |
| 6240.c | func_8002A92C | 393-395 | redundant `(u8)` casts | medium | fixed |
| 6240.c | func_8002A240 | 166/175 | `(s16)(s32)` and `(f64)(u32)` casts | medium | fixed |
| 6240.c | bossSpawnSparkles | 241 | `s32 pad[1]` | low | fixed (pad removed) |
| 8520.c | bossAnimFrameBounceStep | 101/104/109 | 3× `goto done` | high | fixed (if/else) |
| 8520.c | func_8002C5F4 | 61-70 | reused temp `rand` | medium | fixed |
| 9230.c | func_8002D230 | 288-289 | `(u8*)D_807FDC90 + 0x28` ×2 | medium | fixed |
| 9C60.c | func_8002DE04 | 376-377 | `(u8*)D_807FDC90 + 0x28` ×2 | medium | fixed |
| A7A0.c | func_8002EA7C | 359-360 | `(u8*)D_807FDC90 + 0x28` ×2 | medium | fixed |
| A7A0.c | func_8002EA7C | 326-329 | block-local `u8 *tbl` instead of reusing `sp28` | medium | fixed |
| C920.c | func_80030EC4 | 467-468 | `(u8*)D_807FDC90 + 0x28` ×2 | medium | fixed |
| C920.c | func_80030D50 | 116/118 | `(s16)(s32)` casts | medium | fixed |
| F0D0.c | bossInterpolateWaypoints | 164-175 | `*(s16*)((u8*)D_807FBB40 + 0xE6)` plus `Boss2D_*` cast types | medium | fixed (struct fix) |
| F0D0.c | bossInterpolateWaypoints | 161 | `(s16)(s32)` cast | medium | fixed |
| B100.c | func_8002FF74 | 709 | `if (BOSS_ACTOR->unk155 == 0) {}` | high | needs-human |
| 0.c | func_8002413C, func_800254D0, case 0x2C `s32 pad`, func_80024000 `sp48` | 114, 761-767, 1073, 29-34 | pad locals / struct-copy local | low | suspicious-left-alone (frame padding) |
| 0.c | func_80024000, func_800253AC | 38, 576 | `(void*)(s32)&sym` int cast around an address | medium | suspicious-left-alone |
| 3840.c | bossScriptStep | 264/369/375/385/392 | 4× `goto block_16` | medium | suspicious-left-alone |
| 3840.c | bossScriptStep | 253-257 | `u8 *p = BA40->unk17C` temp | medium | suspicious-left-alone |
| 52B0.c | func_80029468 | 321/339 | `goto block_28` into the nested switch | medium | suspicious-left-alone |
| 52B0.c | func_80029468 | 168 | `pad48` (used as a real temp, misnamed) | low | suspicious-left-alone |
| 52B0.c | func_800293C0 | 49 | `randomNonNegative();` with discarded result | low | suspicious-left-alone |
| 8520.c | func_8002C520 | 31-36 | `f32 pad`, `sinVal`, `fArg1` | low | suspicious-left-alone |
| 9230.c | func_8002D230 | 91 | `s32 pad40` | low | suspicious-left-alone (frame padding) |
| 9C60.c | func_8002DE04 | 176 | `s32 pad34` | low | suspicious-left-alone (frame padding) |
| 9C60.c | bossAttachActor | 54 | single-use `sp1C` pointer | medium | suspicious-left-alone |
| A7A0.c | bossPhaseTick | 85 | assignment inside the `if` condition (`other = …`) | medium | suspicious-left-alone |
| A7A0.c | func_8002E9B8, func_8002EA14 | 113/129 | single-use `sp1C` pointer | medium | suspicious-left-alone |
| C920.c | func_80030EC4 | 282-284 | dead store `unk155 = 0` before `unk155 = 1` | high | suspicious-left-alone |
| C920.c | func_80030D50 | 112-117 | `pad[1]` and duplicate `sp20 = sin(...)` | medium | suspicious-left-alone |
| C920.c | func_80030920 | 64 | unused param `arg0`, caller passes `(s32)sp178` | low | suspicious-left-alone |
| C920.c | func_80030EC4 | 242 | `s16 sp50[3]` out-array | low | suspicious-left-alone |
| F0D0.c | func_800336C0 | 177 | `(f32)(f64)sp24` round trip | medium | suspicious-left-alone |
| F0D0.c | bossSetRandomObjectPair | 202-216 | `(val = arr[idx])` inside the loop condition | medium | suspicious-left-alone |

### menu

| file | function | line | construct | confidence | outcome |
|---|---|---|---|---|---|
| 0.c | menuDispatchAction | 445 | `register u8 var_v1` | high | fixed |
| 0.c | menuUpdateProgressGrid | 551,554 | byte offsets 0x174/0x154 | medium | fixed |
| 0.c | menuUpdateProgressGrid | 585-593 | `idx += 1; idx += 1`, `idx-2` offsets | medium | fixed |
| 0.c | menuDrawProgressGrid | 633,695 | byte offset, `*(s8*)&D_80033258` cast | medium | fixed |
| 0.c | menuDispatchAction | 441,443 | pad locals `pad`, `pad2` | low | suspicious, left alone (frame padding; frame size 0x30 becomes 0x28 without them) |
| 0.c | menuDrawProgressGrid | 627,637 | pad `pad`, `sp12B` | low | suspicious, left alone (frame padding; `sp12B` is a real flag) |
| E550.c | func_80032550 | 47-53 | `do { } while (0)` around one `if` | high | needs-human |
| E550.c | menuUpdateLightFadeActor | 83 | `0xFFFFFFCF` mask | low | fixed (`~0x30`) |
| E550.c | menuUpdateLightFadeActor | 88-89 | `cur = unk15F; if (unk15F != 0xFF)` | medium | suspicious, left alone (`if (cur != 0xFF)` breaks the match) |
| E550.c | func_8003292C | 133 | `#ifdef NON_MATCHING` park | n/a | not touched |
| 1AF0.c | menuCheckBitgridOtherSlots | 23-30 | `do { ... } while (0)` wrapper | high | fixed |
| 1AF0.c | func_80026874 | 517-520 | K&R definition with a 3-arg call through an unprototyped declaration | medium | fixed |
| 1AF0.c | func_80026874 | 576,580 | `goto done` into `default:` | high | fixed |
| 1AF0.c | func_80026874, func_800270E0 | 543,898 | `0xFFFEFFCF` mask | low | fixed (`~0x10030`) in func_80026874; the func_800270E0 literal was not rewritten |
| 1AF0.c | func_80026B28 | 613-614 | `sp2C = -1; if (sp2C) {}` | high | needs-human |
| 1AF0.c | func_80026B28 | 638-639 | `*((u8*)arg0+0x10)`, `*(u8*)&D_807FCC4C`, duplicated `sp28 = 9` | medium | partly fixed (field access, no cast); duplicated `sp28 = 9` left alone (hoisting it breaks the match) |
| 1AF0.c | func_800262A8, func_80026B28 | 355,356,614 | `((u8*)arg1)[...]` cast with `void *arg1` | medium | suspicious, left alone (typing `arg1` as `u8*` breaks the match at 4 sites) |
| 1AF0.c | macros `M1S`, `M1A`, `M3A`, `M1B_C924`, `M1_UNK12`, `M1_ARG1`, `M1B_ARG1`, `MenuM1_State`, `MenuScriptActor`, `MenuM1b_C924` | various | cast macros and byte offsets (0xC, 0x12, 0x154/155, 0x174) | medium | fixed |
| 1AF0.c | func_80025B64 | 65 | unused `s32 step` | low | fixed (removed) |
| 1AF0.c | func_80025FB4 | 210 | unused `*e` | low | fixed (removed) |
| 1AF0.c | func_80026250 | 291-298 | falls off the end of a non-void function (result left in v0) | high | suspicious, left alone (explicit `return` or `&&` chain changes the register) |
| 1AF0.c | func_80026DAC | 740-747 | `case 3:` label inside `if` block | medium | suspicious, left alone (splitting the cases changes size by +32 bytes) |
| 1AF0.c | func_80026DAC | 727 | `(u8)sp24` cast | medium | suspicious, left alone (removing it changes `lbu` to `lw`) |
| 1AF0.c | func_80025FB4 | 249 | `D_80750AC8 = (arg0->unk4 = ...)` chained assignment | low | suspicious, left alone (splitting it changes register allocation) |
| 1AF0.c | func_800270E0 | 784 | pad local `pad` | low | suspicious, left alone (frame padding; removal fails the match) |
| 1AF0.c | menuUpdateTransformedWidgets | 1101 | `cnt` reused for font height and clamp | medium | suspicious, left alone (using `d` fails) |
| 1AF0.c | menuCheckControllerAntiPiracy | 936 | `s32 pad[4]` | low | suspicious, left alone (part of the checksum routine) |
| 1AF0.c | menuApplyPurchase | 125 | unused `arg1` (type fixed to `u8*`) | low | suspicious, left alone |
| 3E10.c | 17 single-line empty guards (lines 227-3449) | various | `if (G && G) {}` / `if (G) {}` | high | fixed |
| 3E10.c | 7 multi-line empty guards (`y == 0x7FFF` ×6, `arg0`) | various | `if (c) {\n}` | high | fixed |
| 3E10.c | menuHandleSoundOptionsInput | ~1816 | `if (D_80033F28 && D_80033F28) {}` | high | needs-human |
| 3E10.c | menuLoadHighScores, menuSaveHighScores | 2233-2270 | comma-operator `for` header, `u8 temp_s0 = i` alias | medium | fixed |
| 3E10.c | func_8002E8B8 | 2203 | `for (p = D_80033988; i != 5; i++, p++)` | medium | suspicious, left alone (indexed form `D_80033988[i]` breaks the match) |
| 3E10.c | menuInit | 2721 | `for (D_8076A0D0[0] = 0, i = 0; ...)` comma init | medium | needs-human |
| 3E10.c | func_8003155C | 3455 | `volatile s32 ret` | high | suspicious, left alone (inside `#ifdef NON_MATCHING`) |
| 3E10.c | ~25 functions | various | `*(T**)((u8*)arg0 + 0x174)` | medium | fixed (`MenuScreenActor->unk174`) |
| 3E10.c | func_80028834 | 373,377 | `D_807FBB4C + 0x154/0x155`, `temp_s0[0x17]` | medium | fixed (struct fields; `*(s8*)D_8076A0D1` cast kept because the original reads signed) |
| 3E10.c | menuFormatOptionValues | 1691-1712 | `D_80033F28` byte offsets 0x80/0x84/0x94/0xA0 | medium | fixed (`D_80033F28[0x20]` etc.) |
| 3E10.c | menuUpdateStateDispatch | 2837-2883 | `D_807FC924 + 0x298`, `temp_t0 + 0xC/0xE/0x12/0x17` | medium | fixed |
| 3E10.c | menuUpdateStateDispatch | 2852-2859 | `*((s8*)D_807ECDEC + 2/3)` | medium | fixed |
| 3E10.c | func_80030894 | 3069 | `*((s8*)arg0 + 0x15)` on a `void*` shared by many struct types | medium | suspicious, left alone |
| 3E10.c | func_8002C634 | 1349 | K&R definition | medium | suspicious, left alone (inside `#ifdef NON_MATCHING`) |
| 3E10.c | menuCheckSaveFile | ~3806 | K&R `u8 arg0` | low | not attempted |
| 3E10.c | menuSetElementCoordinates | 2562 | single-use `four`/`d1`/`d2` temps, byte-offset stores, `s32` stands in for `Gfx*` | medium | needs-human (natural body fails fdiff) |
| 3E10.c | draw functions and `textDrawStringVtx` | 355,973,1155-1231,2948-2968 | `(s32)arg1` / `(Gfx *)` casts from `s32` prototypes | medium | not attempted (budget) |
| 3E10.c | ~50 functions | scan list at 129-3791 | pad locals (`padCC`, `sp120`, ...) | low | suspicious, left alone (frame padding; no pad-local removal attempted in 3E10.c) |
| 3E10.c | non-parked functions | various | `#ifdef NON_MATCHING` blocks with raw offsets (`menuDrawFileSummary`, `menuInitFileSummary`, `func_8002C634`, ...) | n/a | not touched (parked) |

### jetpac / critter / minecart

| file | function | line (orig) | construct | conf | outcome |
|---|---|---|---|---|---|
| jetpac/1460 | jetpacGridAddSprite | 103-105 | `if (1) {}` ×3 | high | fixed |
| jetpac/1460 | jetpacGridAddSprite | 108 | `cell->color[i = 2] = …[i]` | high | fixed |
| jetpac/1460 | func_80025700 (parked) | 105, 181-224 | `if (!x) {}` ×~8 | high | parked code, left alone: removing them changes the object |
| jetpac/1460 | JetpacCellItem | 59-60 | `pad8[3]` + `unkB`, `*(s32 *)&item->pad8[0]` | med | fixed (real `unk8` field) |
| jetpac/0 | jetpacStateGameplay | 304 | empty guard on `((J0aItem *)&sp1C->pad14[...])->unk44` | high | suspicious, left alone: removing it changes the codegen, even with the struct fixed |
| jetpac/0 | jetpacStateGameplay | 304, 310 | `pad14[unk10 * 0x4C]` byte-offset indexing | med | fixed (`items[4]`, `bonus`) |
| jetpac/0 | `J0aGlobalView` / `J0aG` | 226-241 | second overlapping view of `jetpacGame` | med | fixed |
| jetpac/0 | jetpacPlaySound | 427 | one-line loop over a pointer with `D_80770E14` end sentinel | med | fixed (`for` loop) |
| jetpac/0 | func_80025168 (parked) | 535 | `if (0) {}` | high | parked code, left alone: removing it changes the object |
| jetpac/0 | func_80025168 (parked) | 512 | `volatile s32 *p` | high | parked, left alone (it is the reload hack for the parked function) |
| jetpac/0 | jetpacSetSoundPitch | 433 | `s32 *p = &arg1; … *p` | med | suspicious, left alone: removal mismatches |
| jetpac/0 | jetpacSetState | 445 | `s32 pad;` | low | suspicious, left alone (frame padding) |
| jetpac/0 | jetpacRunFrame | 102 | `u8 *sp28` single-use temp | low | suspicious, left alone: inlining mismatches |
| jetpac/0 | jetpacPlaySound | 428 | `*(s16 *)((u8 *)D_8002BA52 + arg0 * 4)` | med | suspicious, left alone: `D_8002BA52[arg0 * 2]` mismatches |
| jetpac/1A60 | jetpacUpdateExplosion | 83 | `volatile s32 frame` | high | needs-human |
| jetpac/1A60 | jetpacUpdatePlayerMovement | 415, 418, 439, 442 | `(*(volatile s32 *)&J0a2A->unk30)` ×4, plus the `u` temp | high | needs-human |
| jetpac/1A60 | jetpacUpdatePlayerMovement | 467-476 | byte-offset ledge access via `jetpacGame + idx * 0x34 + 0x370/0x378` | med | fixed (`jetpacGame.ledges[idx]`) |
| jetpac/1A60 | J0a2Actor, J1bActor, J0a2Player, J1bGameView | – | four overlapping views of actor/player | med | fixed |
| jetpac/1A60 | func_80025700 callers | 100, 242, 286, 543-557 | `(s32)color` pointer casts | med | fixed (`u8 *`) |
| jetpac/1A60 | jetpacUpdateLaser | 139 | `s32 pad1;` | low | suspicious, left alone (frame padding) |
| jetpac/1A60 | jetpacDrawPlayer | 547 | `s32 pad; pad = 0;` | low | suspicious, left alone: removal mismatches |
| jetpac/1A60 | jetpacDrawPlayer | 533, 537, 538, 540 | `*(s32 *)&D_8002F060[4]`, `color` temp, `*(f32 *)&jetpacPlayer` | low | suspicious, left alone: replacements mismatch |
| jetpac/1A60 | jetpacFireLaser | 284 | K&R definition | low | suspicious, left alone (needed for arg handling) |
| jetpac/3060 | jetpacCheckAabbOverlapWrapped, jetpacIsOverRocket | 64, 71 | `volatile int` return type | high | needs-human |
| jetpac/3480 | `J3Item`, `J3Inner`, `JetpacInner`, `UnkStruct_80028340`, `J3Global` | – | five overlapping views of player/ledge | med | fixed |
| jetpac/3480 | jetpacItemsUpdate, func_800285DC, jetpacPlaceRocketOnPad/AboveScreen, func_800289EC, jetpacBoxOverlapsItems, jetpacDrawItem, jetpacSpawnBonusItem/FuelPod, jetpacSetRocketSpriteFrames | – | `(u8 *)&jetpacGame + active * 0x194 + 0x1C/0x30` offset math, `(u8 *)arg0 + 0x20` | med | fixed |
| jetpac/3480 | jetpacDrawItem | 277 | `if (D_8002F3C0) {}` | high | suspicious, left alone: removal mismatches |
| jetpac/3480 | jetpacUpdateRocketFlight | 585 | `if (!t) {}` | high | needs-human |
| jetpac/3480 | jetpacUpdateRocketFlight | 546 | statements crammed onto one source line | med | suspicious, left alone: scheduling changes if split |
| jetpac/3480 | jetpacUpdateRocketFlight, func_800289EC | 542, 611 | `s32 pad;` | low | suspicious, left alone (frame padding) |
| jetpac/3480 | jetpacInitLedge | 670 | comma expr `arg0->unk28 = (arg0->unk24 = …, arg2 + 12)` | med | needs-human |
| jetpac/3480 | func_80027728, func_80027EC0, func_80028E88 (parked) | – | offset casts, `if (!k) {}`, scattered temps | med | converted to struct access (object unchanged); the parked pointer-hack temps in func_80028E88 left alone |
| jetpac/4FC0 | jetpacCheckPlayerHit | 129 | `((J4Global *)&jetpacGame)->unk420` | med | fixed (`jetpacGame.player`) |
| jetpac/4FC0 | jetpacBounceOffLedge | 257 | `((J4Global2 *)&jetpacGame)->ledges` | med | fixed |
| jetpac/4FC0 | jetpacSpawnActor, jetpacKillActorInBox, func_80029F7C | – | `unk1C[2]` raw player array, `p[1]` | med | fixed (`stage`/`score`) |
| jetpac/4FC0 | jetpacCheckPlayerHit, jetpacAllocActor, jetpacSpawnActor | 118, 180, 214 | `pad[7]`, `pad`, `pad[2]` | low | suspicious, left alone (frame padding) |
| jetpac/4FC0 | func_80029640 | 280 | `cnt2 = cnt1 = 0;` | low | suspicious, left alone: other orders mismatch |
| critter/3340 | func_80027DC0 | 316 | `Actor_3340 *volatile sp34` | high | fixed |
| critter/3340 | func_80027448 | 219 | `if (func_806FB418() < sp64) {}` | high | suspicious, left alone: removal or call-only form mismatches |
| critter/3340 | func_80027448 | 20-86 | `J0b2Actor` / `J0B2_A` / `J0B2_P` macro views | med | fixed (merged into `Actor_3340`) |
| critter/3340 | func_80027DC0 | 337, 373 | `var_t5` / `var_t6 = (…) != 0` | low | suspicious, left alone: removal mismatches |
| critter/3340 | func_80028120 (parked) | 518-554 | `if (!k) {}` ×3 | high | parked code, left alone: removing them changes the object |
| critter/4840 | critterDrawWord, critterRenderText, critterShowText, critterUpdateText | – | `(arg1 + arg3)[0x810]`, `!= (0, 0)`, `*(s16 **)(arg1 + 8)`, `arg4` reused as loop var | high | fixed |
| critter/5110 | func_80029118 (parked) | 55, 64, 66 | `pad88`, `pad54`, `pad40[4]`, `*(u8 *)((char *)&sp74 + 3)` | low | parked, left alone (changing it changes the parked object) |
| critter/5110 | func_80029118 (parked) | 135-146 | `critterBitwiseNot(~(s32)osWritebackDCache)` call obfuscation | – | looks like the game's own anti-tamper trick, not a codegen hack |
| critter/0 | critterPickNewZone | 691 | `goto end` | high | fixed (sub-agent) |
| critter/0 | func_80024F28 | 295 | `u8 pad;` | high | fixed (sub-agent) |
| critter/0 | critterRenderGroup | 536 | `(0, col)` comma plus hand-built Gfx words | high | fixed (sub-agent) |
| critter/0 | func_8002427C | 103 | redundant inner `{ }` block | high | fixed (sub-agent) |
| critter/0 | critterDispatchAll | 936 | `var_s3 = NULL;` before the switch | med | fixed (sub-agent) |
| critter/0 | critterSteerToTarget | 824 | `*(volatile f32 *)(arg0 + 0x28)` | high | needs-human |
| critter/0 | critterSteerToTarget | 807, 827, 836 | `(u8)use_y` casts | med | suspicious, left alone |
| critter/0 | critterRenderGroup | 491 | unused `s32 col;` | low | suspicious, left alone (frame padding) |
| critter/0 | func_8002601C (parked) | 643 | `f = (u8)f != 0;` | med | suspicious, left alone (parked) |
| critter/0 | whole file | – | raw `u8 *arg0` offsets everywhere | med | fixed (`CritterObj` and the structs listed in section 3) |
| minecart/0 | minecartPlayerCartUpdate | 236 | `goto case_1` | high | fixed (fall-through) |
| minecart/0 | minecartPlayerCartUpdate | 205, 209 | `pad94`, `pad0…pad8` | low | suspicious, left alone (frame padding) |
| minecart/0 | func_80024914 | 329-332 | `pad0`, `pad1`, `pad_2C` | low | `pad_2C` removed in fce656a (frame unchanged); `pad0`/`pad1` left alone |
| minecart/0 | minecartReverseTrackBehaviour | 405 | `padA` | low | suspicious, left alone (frame padding) |
| minecart/0 | `MinecartStruct_174`, `MinecartTrackCart`, `MinecartStruct_E78`, `MinecartFollowCart`, `MinecartStruct_3E`, `MinecartStruct_20`, `MC` macro | – | overlapping cart views and `((T *)arg0)` macro cast | med | fixed |
| minecart/25F0 | func_800280BC, func_8002835C | 880, 950 | `goto case_1` | high | fixed |
| minecart/25F0 | func_800286EC | 1061 | `goto case_1` | high | suspicious, left alone: removal changes codegen |
| minecart/25F0 | whole file | – | per-use `((T *)D_807FBB40)` casts, CB/CD/C4C/MC macros | med | fixed (sub-agent) |
| minecart/25F0 | func_800286EC | 1065 | comma-expression condition `(dx = …, dz = …, …)` | med | fixed (sub-agent) |
| minecart/25F0 | minecartStartScriptNearPlayer | 782-785 | comma-expression condition | med | fixed (sub-agent) |
| minecart/25F0 | func_80027778 | 736 | `(unkF0--, unkF0 == 0)` | high | fixed (sub-agent) |
| minecart/25F0 | minecartAdjustTargetSpeed | 804-830 | duplicated clamp ifs | high | fixed (sub-agent) |
| minecart/25F0 | func_800286EC | 1031-1084 | duplicated clamp ifs, extra f64 temps | high | fixed (sub-agent) |
| minecart/25F0 | func_8002835C | 967 | `(AllocSub *)((u8 *)sp74->unk34 - 1)` | high | fixed (sub-agent) |
| minecart/25F0 | minecartChooseBranchSide | 790-798 | one-line `if (…) { …; return; }` | med | fixed (sub-agent) |
| minecart/25F0 | minecartFollowerChildBehaviour | 487-488, 707-712 | `(d > 1.0) ? 1.0 : d` clamps | med | fixed (sub-agent) |
| minecart/25F0 | minecartFollowerBehaviour | 97-99 | `u8 sp47;` then separate assignment | low | fixed (sub-agent) |
| minecart/25F0 | minecartSpawnRandomParticle | 345 | `s32 unused;` | med | fixed (sub-agent) |
| minecart/25F0 | func_8002835C | 917 | `s32 pad0, pad1, pad2;` | low | suspicious, left alone (frame padding) |
| minecart/25F0 | func_800286EC | 1010 | `s32 pad;` | low | suspicious, left alone (frame padding) |
| minecart/25F0 | minecartFollowerChildBehaviour | 439, 442-443 | `padA` / `padB` / `padC` | low | suspicious, left alone (frame padding) |
| minecart/25F0 | minecartFollowerChildBehaviour | 453-457, 552-557 | `s16 v` read-modify-write of `sp68->unk2C` | low | needs-human |
| minecart/25F0 | minecartSetTargetAheadOfPlayer | 338 | `s32` return type with no `return` | high | needs-human |

### race / multiplayer

| file | function | line | construct | confidence | outcome |
|---|---|---|---|---|---|
| race/6650.c | func_8002B180 | 417 | `BBV->unkB8 = BBV->unkB8` self-assign | high | fixed |
| race/6650.c | func_8002B180 | 390 | `if (BBV->unk7C) {}` | high | needs-human |
| race/6650.c | func_8002B180 | 403 | `if (var_fv1) {}` | high | needs-human |
| race/6650.c | func_8002B180 | – | `f32 sp54[1]` forced stack home | medium | needs-human |
| race/6650.c | func_8002B180 | – | `Race2B180View` cast, s32 position fields | medium | fixed |
| race/36B0.c | func_80027920 | 98 | `do {} while (0)` plus reused `arg2` | high | fixed |
| race/52B0.c | func_8002A0AC | 438 | `goto tail` | high | fixed |
| race/52B0.c | func_800294A8 | – | byte-offset loop, comma `for`, int-cast pointer | medium | fixed |
| race/52B0.c | func_800292B0/func_800292D0, func_8002A0AC | – | raw offsets, `s16 (*)[5]` casts | medium | fixed |
| race/52B0.c | func_800294A8 | – | `u8 pad53` | low | suspicious-left-alone (frame padding) |
| race/52B0.c | func_8002A0AC | – | `f64 dv` unused | low | suspicious-left-alone (frame padding) |
| race/7BD0.c | func_8002CBEC | 608/619 | empty if/else + `goto next`, `var_v0 ^ 0`, `var_v1` reuse, `var_v0 = 0x40` | high | fixed |
| race/7BD0.c | func_8002E8EC | 1495/1503 | `goto end` | high | fixed |
| race/7BD0.c | func_8002E644 | – | `four = 4` temp | medium | fixed |
| race/7BD0.c | func_8002E644 | – | `sp4A = …; sp4A &= 0xFFF` two-step | low | suspicious-left-alone (merging it changes the code size) |
| race/7BD0.c | func_8002D778 | 1028 | `if (!t->unk1C && !t->unk1C && !t->unk1C) {}` | high | needs-human |
| race/7BD0.c | func_8002D778 | – | `list0` / `i = 0` temps, `(&pa->unk4->unk34)[k]` | medium | fixed |
| race/7BD0.c | func_8002D778 | – | `(u32)t->unk1C ± 1` casts | medium | suspicious-left-alone (they choose the `lhu` temp register) |
| race/7BD0.c | func_8002DA68 | – | block-scoped temp, separate unk34/38/3C fields | medium | fixed |
| race/7BD0.c | func_8002C2E8 | – | `*((u8 *)arg1 + 0x44)` | medium | fixed |
| race/7BD0.c | func_8002D148 | – | local `extern` | medium | fixed |
| race/7BD0.c | raceUpdateStandings | – | redundant `q = &base[j]` | medium | fixed |
| race/7BD0.c | func_8002D224 | – | `temp_s4` copy, do-while | medium | fixed |
| race/7BD0.c | func_8002DDA0 | – | uninitialised `sp38` read plus `pad3C` | high | fixed |
| race/7BD0.c | func_8002BC2C/func_8002BCB0 | – | `(s32)ptr + idx*8`, `(s32 *)&sp54` casts | medium | suspicious-left-alone (operand order and the `RaceUnknown174` / `RaceStruct3` split) |
| race/6650.c | func_8002B610 | – | constant temps `a`, `b`, `c`, `d` | medium | fixed |
| race/6650.c | func_8002B6F4, func_8002AE6C | – | raw `[0x35]`, `+0x174` | medium | fixed |
| race/6650.c | func_8002AE9C | – | repeated `var_s1 = D_807FBB40` reload | medium | suspicious-left-alone (changes register allocation) |
| race/A960.c | func_8002F784 | 424 | `if (!cur && !cur) {}` | high | fixed |
| race/A960.c | func_8002F784 | 427 | `if (first != 0) {} else {…}` | high | fixed (`if (!first)`) |
| race/A960.c | func_8002F784 | – | xor swap | low | suspicious-left-alone (it is in the target asm) |
| race/A960.c | func_8002F784 | – | `if (cur <= end)` guard, `acc *= diff>=0?1:-1` | low | suspicious-left-alone |
| race/A960.c | whole file | – | ~89 raw-offset accesses | medium | fixed |
| race/A960.c | func_8002EDD4 | – | `f32 pad[5]`, `u32 j = i` | low | suspicious-left-alone (frame padding) |
| race/A960.c | func_8002F490 | – | `s32 pad` | low | suspicious-left-alone (frame padding) |
| race/A960.c | raceGetRoute, raceGetWaypoint, raceUpdateWaypointActivation | – | `e = &table->items[idx]` before the null check, separate `u16 val` locals, `dz` reuse | low | suspicious-left-alone (each breaks the match) |
| race/1770.c | whole file (13 functions) | – | raw offsets, `LR3*` macros, redundant casts | medium | fixed |
| race/1770.c | func_80026098 | – | `*(f32 *)&D_807FBB40->unkB8` cast | medium | suspicious-left-alone (plain field flips the `mul.d` operands) |
| race/1770.c | func_8002597C | – | `lo` reused as byte length then table pointer, `src` as `u8 *` | medium | suspicious-left-alone |
| race/1770.c | func_800257A4 (padA/padB/padM), func_80026098, func_800261E0, func_80026D2C (pad), func_80026F04 (pad), func_800274C0 (`pad[3]`) | – | pad locals | low | suspicious-left-alone (frame padding) |
| race/36B0.c | whole file | – | raw offsets, comma operator, `(new_var = temp_v0)`, `u32` casts, `*(s32 *)` float pun | medium | fixed |
| race/36B0.c | func_80027710 | – | `(e2 = …)` inside `sqrtf(…)` | medium | suspicious-left-alone |
| race/36B0.c | func_80028440 | – | `+0x6E` byte-offset loop, triple copy before the `unk35` switch | medium | suspicious-left-alone |
| race/36B0.c | func_80027CE8, func_80029054, func_800282D8 | – | `(u8)(… < 0x14)` cast, `temp_v0` temp, `(s32)` around `+157.0` | low | suspicious-left-alone |
| race/36B0.c | func_80027CE8 (pad44), func_800280E8 (`pad[2]`), func_80028440 (`pad70[2]`, `pad38[1]`, `pad30`), func_80027920 (`u8 flag`) | – | pad locals | low | suspicious-left-alone (frame padding; `func_80028AD0` pads are in the `NON_MATCHING` block) |
| multiplayer/0.c | func_80025654 | 665 | `MpSpawnPoint * volatile sp20` | high | needs-human |
| multiplayer/0.c | func_80025654 | – | inner braces, `pos = sp20` re-reads, assignment in condition | medium | fixed |
| multiplayer/0.c | mpFindModelSlotByType | – | missing return, wrong prototype | medium | fixed |
| multiplayer/0.c | MpMapEntry users | – | `+8` offsets, pointer casts | medium | fixed |
| multiplayer/0.c | whole file | – | raw offsets for D_807FBB40, D_807FC924, D_807FC950 | medium | fixed |
| multiplayer/0.c | mpCalcKillScore | – | raw `0x2FE`… offsets | medium | fixed (the `(arg1 << 1)` stays) |
| multiplayer/0.c | mpDrawPlayerScores, mpUpdateScoreEffects, mpUpdate, mpDrawHud | – | shared `temp`, `(void *)(s32)&D_8071F3C0`, `flag`, double store, `t0`/`cond` | low | suspicious-left-alone |
| multiplayer/0.c | mpDropItemsOnHit, mpCreditKill | – | `pad0`/`pad1` | low | suspicious-left-alone (frame padding) |
| multiplayer/0.c | mpUpdateItemSpawns | – | `sp80` unused local | low | suspicious-left-alone |
| multiplayer/0.c | func_80024CA4 | 442/462 | `if (var_s1 == 0) {}`, `if (col) {}` | high | not compiled (`NON_MATCHING`), cannot verify |

## Final build

Clean rebuild at `HEAD` (`tools/dk make clean; tools/dk make`):

```
build/global.text.bin: OK
build/global.data.bin: OK
build/multiplayer.text.bin: OK
build/multiplayer.data.bin: OK
build/minecart.text.bin: OK
build/minecart.data.bin: OK
build/bonus.text.bin: OK
build/bonus.data.bin: OK
build/race.text.bin: OK
build/race.data.bin: OK
build/critter.text.bin: OK
build/critter.data.bin: OK
build/boss.text.bin: OK
build/boss.data.bin: OK
build/arcade.text.bin: OK
build/arcade.data.bin: OK
build/jetpac.text.bin: OK
build/jetpac.data.bin: OK
build/menu.text.bin: OK
build/menu.data.bin: OK
build/dk64.us.z64: OK
```

## Commits

```
048c66b minecart/25F0.c: += for unk80 blend
6d05586 minecart/25F0.c: natural if/else, MIN, post-init local, rename temps
d93b889 minecart/25F0.c: MIN/MAX instead of duplicated clamp ifs, drop comma expressions and dx/dy/dz temps, drop unused f64 temps
5f649be critter/0: CritterObj/CritterGroup/CritterZone structs replace raw offsets; drop (0,col), use gDPSetPrimColor
edf7d96 minecart/25F0.c: PlayerState_25F0 split from actor view, drop redundant casts and unused locals in minecartSpawnRandomParticle, typed D_8074E880/D_80720120, sfx prototype
0038079 arcade/0.c arcadeSpawnStage1Entities: split entity init over lines (partial)
7bce133 arcade/0.c arcadeSpawnStage1Entities: split last entity init over lines
37cd6b5 arcade/0.c arcadeSpawnStage3Entities: one statement per line
81fae8f arcade/0.c func_8002D6FC (parked): drop empty padding guards
ede301d arcade/0.c func_8002CD64 (parked): drop empty padding guards
0445f5b arcade/0.c arcadeDrawNameRegistration: drop redundant char *p alias of buf
419d2a6 minecart/25F0.c: one Actor_25F0/MinecartCart/MinecartTargetState replace per-use cast views and CB/CD/C4C/MC macros; f32 prototypes for float args; u8 track tables
8dbb920 arcade/0.c arcadeDrawStage4Background: drop redundant (s16)(s32) arg casts
aee6bcf arcade/0.c arcadeDrawStage1Background: drop redundant (s16)(s32) arg casts
8e10c2c arcade/0.c arcadeDrawGirderSpan: drop redundant (s16)(s32) arg casts
22e1608 arcade/0.c arcadeDrawGirderSpan: for loop instead of if + do-while
d20c4a0 arcade/0.c arcadeCheckStage3Collision: drop redundant ArcadeLift casts, end = &D_8004BC88[6]
509fa51 arcade/0.c arcadeDrawGirderSpan: ANSI definition
edcec7c arcade/0.c arcadeDrawStage4Ladders: ANSI definition
9430ed6 arcade/0.c arcadeDrawStage3Ladders: ANSI definition
17d4d06 arcade/0.c arcadeDrawStage2Ladders: ANSI definition
b712401 arcade/0.c arcadeDrawStage1Ladders: ANSI definition
e888f06 arcade/0.c arcadeDrawLadder: ANSI definition and prototype
b6fd425 arcade/0.c arcadeDrawBackground: ANSI definition and prototypes for its callees
32b8597 bonus/2690.c: drop redundant func_80029B9C forward declaration
02ab438 bonus/2690.c func_8002A398: drop redundant t0 cast
df06d9a bonus/2690.c: func_80029E54/func_8002A010/func_80028E3C/bonusPopupSpawnActors: Point3f and struct access, drop casts/temps
31e4962 jetpac/0.c: JetpacPlayer items/bonus arrays replace pad14 cast and unk148/unk18C raw fields
9208726 arcade/0.c: replace byte-offset symbols with struct fields, drop empty guards/comma/no-op xor, char* and Gfx** prototypes, flat D_8004A318
1aa4c24 race/36B0.c func_80027920: ternary sign
e025f6a race/36B0.c: drop comma/u8-cast/int-pun hacks, use ++/narrow prototypes
25efbf2 critter/0: drop goto, unused pad, redundant casts/blocks in cleanup pass
fce656a minecart/0.c: one MinecartCart struct replaces 4 overlapping views and MC macro cast; drop pad_2C
bbe4d81 bonus/2690: drop redundant casts (func_8068C5A8 args, s16 params, AD10 void*)
0280156 multiplayer/0.c: drop redundant casts/decls, simplify func_80025654
2c7a1b8 bonus/2690: func_8002AD10/B920/C8EC natural field access, clear-bit mask
5887f45 bonus/2690: ternary step, drop redundant casts, narrow func_8068C5A8 prototype
f6b6e41 race/1770.c: file-local RaceActor/RacePathState/RaceParticipant structs replace raw offsets; drop LR3* macros and redundant casts
1ca1dc6 minecart: drop goto to the adjacent case label (25F0 x3 funcs, 0.c minecartPlayerCartUpdate)
af05b6f bonus/2690.c: func_8002A398/func_80029B9C: BB_CAMCTX field, struct field for unk26, drop byte-offset casts
96437dd bonus/2690: merge target/popup actor and sub174 views, drop redundant temps/casts
0edc806 menu/3E10.c: struct fields for D_807FC924 input/camera, D_807ECDEC stick, D_807FBB4C 154/155, state dispatch sub-struct; index D_80033F28 text table instead of byte offsets
eafc863 multiplayer/0.c: unify actor/player/score/controller struct views, retype externs
99e0dc3 src/race/A960.c: raceLoadRouteData takes u8 * (no cast)
7e34544 bonus/2690: func_8002BF98 field accesses instead of byte offsets/casts
d0f9058 src/race/A960.c: drop F490 player temps, raceIsFacingWaypoint returns u8
841a2a6 race/36B0.c: real structs (RaceActor/RaceCursor/RaceState/RaceAux), typed waypoint table, drop raw offsets
c64f41c critter/4840.c: TextData struct fields replace byte offsets, drop (0,0) compare and arg4 loop reuse
38b13cd menu/3E10.c: MenuScreenActor unk174 instead of byte-offset loads; ANSI menuBossReplayHandleInput
38c8fbc bonus/2690: func_8002CC08 use gbi macros, drop WRITE_GFX/anim macro
13da18b critter/3340.c: drop volatile actor local, merge J0b2Actor view into Actor_3340
7a14928 jetpac/1A60.c: u8* colour args instead of (s32) pointer casts
8c20a95 jetpac/1460.c: real item flag field and u8* colour arg instead of pad8/s32 casts
278dd35 src/race/A960.c: real structs (RaceRoute/RaceWaypoint/RaceActor/RaceTracker) instead of raw offsets
78e54a2 jetpac/4FC0.c: real JetpacGlobal (players/ledges/player) replace J4Global byte-offset views; player stage/score fields
541f000 race/6650.c: drop constant temps in func_8002B610, type func_8002B6F4/func_8002AE6C args instead of byte offsets
83f6164 bonus/2690: natural camSetTarget/actor field access, merge target struct views
4b93433 menu/3E10.c menuLoadHighScores/menuSaveHighScores: index entries by i instead of pointer/temp aliases
37b003b race/7BD0.c func_8002DDA0: drop uninitialised sp38 read and pad local
1afd014 jetpac/3480.c: real JetpacPlayer/JetpacGlobal (players, ledges) replace byte-offset views; drop J3Item/J3Inner
63c6372 race/7BD0.c: drop redundant q reassign in raceUpdateStandings, local extern in func_8002D148, temp copy/do-while in func_8002D224
5d2f521 menu/3E10.c: remove deadsweep empty guards (all but one in menuHandleSoundOptionsInput path)
b485761 race/7BD0.c func_8002C2E8: RaceUnknown174 unk44 field instead of byte offset
cf876ba bonus/2690.c: float-typed sfx/angle prototypes instead of raw float bit patterns; drop (f64) cast
a20c71c race/52B0.c: typed func_800292B0/func_800292D0, waypoint array and D_807FDC90 field access instead of byte offsets
748c9fe menu/1AF0.c: drop unused locals in func_80025B64 and func_80025FB4
37e2773 bonus/2690.c bonusDespawnTarget/bonusTargetUpdate: typed target state instead of u8*/s32* casts
908c6f8 menu/1AF0.c: replace byte offsets/cast macros with struct fields (unk12, unk154/155, unk174, D_807FC924->unk4), typed u8* flag arg, pointer camStartPath arg
f2ddd81 jetpac/1A60.c: unify actor/player/ledge struct views (drop J0a2/J1b casts, byte-offset ledge access)
2fb049d multiplayer/0.c mpFindModelSlotByType: real prototype, return the call result
88a25f9 bonus/9010.c: typed actor arg in bonusRenderScoreHud; replace byte-pointer trick with (u8) cast
0a3b15b multiplayer/0.c: type MpMapEntry (count/items/ids), drop MpSpawnPointTable/MpMapEntryIds casts and raw +8 offsets
75dd76b bonus/12A0.c bonusReelGameUpdate: drop (s32)&sym cast via pointer-typed prototype
f9e2d72 boss/F0D0.c bossInterpolateWaypoints: drop redundant (s32) cast
4abe888 boss/C920.c func_80030D50: drop redundant (s32) casts
52d20f0 boss/6240.c func_8002A240: drop redundant (s32)/(u32) casts
e778a9c boss/0.c func_800254D0: drop (s32) in (s16)(s32) cast
41055ae menu/1AF0.c: func_80026874 ANSI prototype without goto, use unk10 field, ~mask forms
6ce2c5e bonus/12A0.c: replace byte-offset access with file-local actor structs; drop empty if/else, pointer casts
8a21234 race/A960.c func_8002F784: drop !cur&&!cur empty guard and empty if/else on first
6aa0438 boss/0.c func_800254D0: drop m2c casts/U suffixes, use sp74[unk15++]
82af293 boss/6240.c bossSpawnSparkles: remove unused pad local
411229e race/7BD0.c func_8002E8EC/func_8002E644: drop gotos for if-else chain, drop 'four' temp
3b35e9e boss/F0D0.c: add unkE6/unk0 fields, drop Boss2D cast types and byte offsets
0075491 race/7BD0.c func_8002D778/func_8002DA68: RaceSub4 unk34[3] array, drop list0/i=0 temps and pointer-to-field indexing
f64c25a boss/C920.c: unk28 field instead of byte offset on D_807FDC90
e7a2063 bonus/0.c bonusControllerUpdate: drop (s32) cast on actor pointer arg
ce93504 boss/A7A0.c: unk28 field, reuse sp28 instead of block-local tbl
baefbb5 menu/1AF0.c: drop do-while(0) wrapper in menuCheckBitgridOtherSlots; menuResetSubmenuState takes the state struct
c1b3c29 bonus/0.c bonusControllerUpdate: type string locals as char * (drop casts)
ec50bf3 race/7BD0.c func_8002CBEC: replace empty-if/goto next with for+continue, drop var_v0/var_v1 reuse
75abe23 bonus/0.c bonusControllerUpdate: remove empty pv guard and volatile pad local
b30741d boss/9C60.c: unk28 field instead of byte offset on D_807FDC90
80a1e70 boss/9230.c: unk28 field instead of byte offset on D_807FDC90
7487aaf jetpac/0.c: fold J0aGlobalView into JetpacGlobal, jetpacPlaySound for loop
5af78d0 boss/8520.c: structured bossAnimFrameBounceStep without goto, inline rand temp
32f21f5 boss/6240.c: inline r1 temp, drop redundant breaks and casts
2c986d4 race/52B0.c func_800294A8: use RC_A->unk6E[i] loop, real pointer type for s1, u8 sfxStopSlotSound proto
95874a4 boss/52B0.c func_800292B0: use 0.0f literals instead of zero local
b0502fd race/52B0.c func_8002A0AC: remove goto tail, use switch fallthrough
cf41f18 boss/3840.c: use &s0->unkN instead of byte offsets, drop sp4C alias
225c3d1 race/6650.c: Actor_BB40 position fields f32, drop Race2B180View cast; correct mathAngleDiscrete/func_806F4D70 prototypes
4adea98 menu/E550.c menuUpdateLightFadeActor: write flag mask as ~0x30
60ac00e boss/0.c: drop register on temp_s1, unused cur, byte-offset DC90 arg
e0e65e5 bonus/0.c: use file-local structs instead of byte offsets in func_80024E38, bonusRenderCounterHud
f7e1156 jetpac/1460.c jetpacGridAddSprite: remove if(1) guards and i=2 index hack
bb2580b race/6650.c func_8002B180: replace self-assign clamp with ternary min
654e865 menu/0.c: struct fields for 0x154/0x174, drop register and double increment
d00dc8b race/36B0.c func_80027920: remove empty do-while(0), use separate end local and plain while
```
