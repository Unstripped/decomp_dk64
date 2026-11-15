# bonusControllerUpdate

## Sites
- bonus:80024158:other:31a06c

## Attempts
- 2026-11-14 HackSentinelSwitchChains opus:high: switch (challengeType) {case 0: case 1: case 2: case 0x10:} for the first test: 53 lines with pv kept, 65 with pv removed (pv removal alone: 12)

## Untried ideas
- none from the switch lever: the target's compares rule it out (see Evidence)

## Evidence
- the first case-0 test is a real || chain in source order: lbu v0,111(sp) at 0xb20, beq v0,1 at 0xb2c, beqz v0 at 0xb34, beq v0,2 at 0xb3c, bne v0,0x10 at 0xb44; a switch changes that compare structure
