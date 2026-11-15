# bonusControllerUpdate

## Sites
- bonus:80024158:other:31a06c (FIXED 2026-11-15): `pv = &challengeType; if (*pv == 3)` replaced by `if (challengeType == 3)` plus an untagged unused `s32 pad44;` declared after `sfxId`
- bonus:80024158:goto:uef380 (kept, Q0591): `goto tail;` from case 15 into the case 14 -> 0/4/13 textTableGetString(0x1A, 2, 1) block
- bonus:80024158:goto:u4da95 (kept, Q0591): `goto render;` from the case 0 chain into the case 2 render block
- bonus:80024158:goto:u4da95#2 (kept, Q0591): `goto render;` from cases 7/8 into the same render block

## Attempts
- 2026-11-14 HackSentinelSwitchChains opus:high: switch (challengeType) {case 0: case 1: case 2: case 0x10:} for the first test: 53 lines with pv kept, 65 with pv removed (pv removal alone: 12)
- 2026-11-15 HackbonusControllerUpdate2 opus:high: pv removed -> 12 lines, all the spill temp at sp+0x3c instead of sp+0x38 (frame 0x78 and challengeType sp+0x6F unchanged on the current body); pv replaced by unused `s32 pad44` after sfxId -> fdiff 0 (fixed)
- 2026-11-15 HackbonusControllerUpdate2 opus:high: uef380 case 15 prework hoisted before the switch as `if (challengeType == 15) {...}` with case 15 joining the 0/4/13 labels -> fdiff 1 (kept)
- 2026-11-15 HackbonusControllerUpdate2 opus:high: u4da95 render block duplicated into the case 0 arm only -> fdiff 1, text +32; u4da95#2 duplicated into the 7/8 arm only -> fdiff 1, text +32 (kept)

## Untried ideas
- none: the three gotos are Q0591 shared tails (single jal per tail in the target)

## Evidence
- the first case-0 test is a real || chain in source order: lbu v0,111(sp) at 0xb20, beq v0,1 at 0xb2c, beqz v0 at 0xb34, beq v0,2 at 0xb3c, bne v0,0x10 at 0xb44; a switch changes that compare structure
- uopt -l 5 local offsets (frame 0x78): i -2, counter -8, challengeType -9 (isvar M, not a vreg with pv), targetCount -10, messageText -16, hasMessage -17, triggerKind -18, endOnTrigger -19, msgBuf -24, msgBufCount -36, sfxId -48, pv/pad44 -52, cfe ternary temps -56/-60; spilltemps start below at -64 (sp+0x38)
- without the -52 word the cfe temps and the spill temp move up 4 (spill sp+0x3c); challengeType is reloaded from sp+0x6F at every use either way (lbu at 0x28c, 0x488, 0x78c, 0x9cc, 0x9d8, 0xa8c, 0xaa8, 0xab4, 0xb20)
- uef380: single jal textTableGetString at 0x2fc (block 0x2f4-0x30c); case 15's block 0x314-0x35c ends `b 0x2f8` (delay slot li a0,0x1a)
- u4da95/#2: single jal renderCallbacksRegister at 0x968 in the block at 0x94c/0x950; entered by the case 2 fall-through, beq/b 0x94c from the case 0 chain (0x7f8, 0x824, 0x82c) and b 0x950 from cases 7/8 (0x83c)
