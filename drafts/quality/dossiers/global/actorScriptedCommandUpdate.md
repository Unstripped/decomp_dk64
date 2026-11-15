# actorScriptedCommandUpdate (global, src/global/C4620.c)
## Sites
global:806BFBF4:other:741d57 / e3371e / 4119fa / e3371e#2 other: cmd->param2 - (0 - sScriptAnimBase[cmd->param1]) kept the ugen ring (case 3: param1 t5, table t4, param2 t3 at 0x720-0x734) (FIXED 2026-11-15: ScriptCommand args[2] view, sScriptAnimBase[cmd->args[0]] + cmd->args[1])
global:806BFBF4:dead-if:396b8d dead-if: extra 254 reference -> one-case switch on particlePath (FIXED)
global:806BFBF4:other:c7755a other: * 3u index -> ScriptColor RGB table (FIXED)
global:806BFBF4:other:5d59f1 other: s32 node temp is a typed single-use local of the callee param type (FIXED, tag dropped)
## Attempts
2026-11-10..12 CleanGlobalC4620 / Rev16H / Rev17N / Rev20A opus-5-5:low: reconstructs (899, 6243, 5225), as1probe per site, permutes (no natural output)
2026-11-14 HackactorScriptedCommandUpdate opus-5-5:high: switch on particlePath (0), ScriptColor table + the other user converted (0), node checks (direct 30, block scope 13, u8 31, tag dropped), ring: anim local per case (484-697), plain/operand/cast spellings (546-599)
2026-11-15 HackactorScriptedCommandUpdate2 opus-5-5:high: variants try: param2 + T / T + param2 / *(T + i) + param2 all 599; T + cmd[0].param2 and T + (*cmd).param2 0 (hidden steers, not kept); typed view ScriptCommand { u16 opcode; s16 args[2]; } with T[cmd->args[0]] + cmd->args[1] fdiff 0 (args[1] + T order 599). All four ring FAKEs removed.
## Untried ideas
none: function has no hack sites left
## Evidence
Case 3 at 0x6fc-0x784: lh t5,4(s0) (param1), lui t4 sScriptAnimBase, lh t3,6(s0) (param2), addu a1,t3,t4; second call reloads (lh t1/t9, lhu t5). cfe emits the right operand of + first when it contains an array element (constant-index member array cmd->args[1] counts; plain member cmd->param2 does not), so the table-first source order gives the target's param2-first evaluation.
