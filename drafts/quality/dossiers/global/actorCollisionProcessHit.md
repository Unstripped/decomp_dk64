# actorCollisionProcessHit

## Sites
- global:80675810:other:d9962d
- global:80675810:other:818f85

## Attempts
- 2026-11-14 HackSentinelSwitchChains opus:high: switch on entry->chain alone 37; with phase as entry->phase 40, interactions[i].phase 85, hitPhase 53; same without the switch: entry->phase 40, hitPhase 53
- 2026-11-14 HackSentinelSwitchChains opus:high: switch (entry->chain) {case 0: case 2:} combined with each entry spelling and each phase spelling

## Untried ideas
- none from the switch lever: the target's compares rule it out (see Evidence)

## Evidence
- the chain test is lbu v0,10(s1) at 0x24c, beqzl v0 at 0x254, bnel v0,2 at 0x25c; a switch (entry->chain) {case 0: case 2:} gives the same compares but swaps the s0/s1 colouring of &gActorGlobalState and entry (37 lines), so it does not carry the phase re-read's removal
- switch form measured with the entry address respelt: &interactions[i] or interactions + i with the switch 37 (unchanged from the switch alone), with phase also respelt 40-54
