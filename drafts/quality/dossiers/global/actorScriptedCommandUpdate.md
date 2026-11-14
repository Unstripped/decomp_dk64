# actorScriptedCommandUpdate (global, src/global/C4620.c)
## Sites
global:806BFBF4:other:705ecd / fbe240 / 636c29 / fbe240#2 other: cmd->param2 - (0 - D_80747904[cmd->param1]) keeps the ugen ring (case 3: param1 t5, table t4, param2 t3 at 0x720-0x734); plain spellings re-ring the whole function (KEPT)
global:806BFBF4:dead-if:396b8d dead-if: extra 254 reference -> one-case switch on particlePath (FIXED)
global:806BFBF4:other:c7755a other: * 3u index -> ScriptColor RGB table (FIXED)
global:806BFBF4:other:5d59f1 other: s32 node temp is a typed single-use local of the callee param type (FIXED, tag dropped)
## Attempts
2026-11-10..12 CleanGlobalC4620 / Rev16H / Rev17N / Rev20A opus-5-5:low: reconstructs (899, 6243, 5225), as1probe per site, permutes (no natural output)
2026-11-14 HackactorScriptedCommandUpdate opus-5-5:high: switch on particlePath (0), ScriptColor table + the other user converted (0), node checks (direct 30, block scope 13, u8 31, tag dropped), ring: anim local per case (484-697), plain/operand/cast spellings (546-599)
## Untried ideas
ring sites: none natural found; every spelling without the (0 - x) form re-rings the entry block
## Evidence
Case 3 at 0x6fc-0x784: lh t5,4(s0) (param1), lui t4 D_80747904, lh t3,6(s0) (param2), addu a1,t3,t4; second call reloads (lh t1/t9, lhu t5). D_80747B00 is read with *3 indexing by actorScriptedCommandUpdate and actorSpawnParticlesAlongNodeLoop only.
