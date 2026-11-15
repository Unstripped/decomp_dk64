# hudPauseMenuBuildPage (global, src/global/ACDC0.c)

## Sites
global:806AA304:dead-store:9c13a4 dead-store: `i = 0;` inside case 1 `if (sum)` kept the sum loop test (line 964) as `slti at,s0,5` + `bnezl at` (target 0x2a4c/0x2a50) instead of LFTR `li at,5` + `bnel s0,at`. Retired 2026-11-14: `i = idx;` used as the world row of both flagGridIndex calls.
global:806AA304:other:c78da2 other: `(gPlayerInventoryTable[0].kong + i)->` in the case 2 do-while kept the 0x5E row multiplies as shift sequences (sll 2/subu/sll 4/subu/sll 1) and `addu t8,t3,t7; addu v0,t8,t4` (0x2db4). Retired 2026-11-14: named `KongInventory *inv = &gPlayerInventoryTable[0].kong[i];` in place of the unused `s32 pad3`.

## Attempts
2026-11-14 HackhudPauseMenuBuildPage HackhudPauseMenuBuildPage anthropic/claude-opus-5-5:high: remove `i = 0` -> 2 lines (slti/bnezl -> li/bnel at 0x2a4c)
2026-11-14 HackhudPauseMenuBuildPage HackhudPauseMenuBuildPage anthropic/claude-opus-5-5:high: sum loop on j/x/cnt/flag/sum3 instead of i -> 358/381/584/587/10; `if (sum != 0)`, `5 > i`, while form -> 2 each
2026-11-14 HackhudPauseMenuBuildPage HackhudPauseMenuBuildPage anthropic/claude-opus-5-5:high: def of i placement probe: before flagGet, `i = 5`, `i = idx`, after `if (sum) {}`, before `if (sum)` -> 0; at the case 1 break -> 2
2026-11-14 HackhudPauseMenuBuildPage HackhudPauseMenuBuildPage anthropic/claude-opus-5-5:high: `i = idx;` + flagGridIndex(0x1D5, i, ..) and/or flagGridIndex(0x1FD, i, ..) -> 0 (all three combinations); kept the both-calls form
2026-11-14 HackhudPauseMenuBuildPage HackhudPauseMenuBuildPage anthropic/claude-opus-5-5:high: `kong[i].` inline -> 39 (multu by 0x5E everywhere, 873/875 included); operands swapped -> 41; `0x4B <=` -> 39
2026-11-14 HackhudPauseMenuBuildPage HackhudPauseMenuBuildPage anthropic/claude-opus-5-5:high: e2/ent = &kong[i] (or kong + i) before the compare -> 0; at the do-body top -> 8; new `KongInventory *` local added -> 61 (top of decls) / 18 (after pad3); new local replacing pad3 -> 0 (kept, named inv)
2026-11-14 HackhudPauseMenuBuildPage HackhudPauseMenuBuildPage anthropic/claude-opus-5-5:high: review: case 2 do-while -> for (i = 0; i < 5; i++) -> 0 (kept); (f32)(u32) casts on abilityEnergy dropped -> 0 (kept); pad1 or pad2 removed -> 80 each (kept)

## Untried ideas
none open: the function has no tagged sites left.

## Evidence
0x2a1c-0x2a54: sum in t0 spilled at 0x74(sp); loop `slti at,s0,5; bnezl at,2a28` (LFTR suppressed by the later def of i inside the idx != 8 block).
0x2a68/0x2ac8: flagGridIndex result truncated `sll/sra 0x10` (file-local s16 declaration, Q0662).
0x2d8c-0x2e90: 0x3c(sp) holds idx*2 (compared against 0x10); row offset i*0x5E by shifts; D_807505A4[i] strength-reduced to a pointer at 0x38(sp); loop test `li at,5; bne s0,at`.
0x2270-0x22c4 (prologue): kong rows `&kong[playerGetResolvedKongId(0)]` and `&kong[iconObj->kong]` by shift sequences; the `kong[i].` do-while spelling turns these into `li a0,0x5e; multu`.
