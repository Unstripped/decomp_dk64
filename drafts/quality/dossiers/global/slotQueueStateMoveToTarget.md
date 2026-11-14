# slotQueueStateMoveToTarget (global, src/global/FCCD0.c)
## Sites
- global:806FA7BC:proto-steer:bb89d9: REMOVED.
  - The call really passes 3 arguments: a1 = *value (lhu 0x28c4), a2 = shown (lhu 0x28b8), consumed by jal 0x28cc.
  - The callee has 1 parameter, with no home stores.
  - The fix is a K&R definition of slotQueueGetCountStep, delivered as a stand-in bundle.
- global:806FA7BC:dead-if:34e891: *value is loaded before the null test (beqz delay slot 0x28c4); the NULL path reuses it at 0x295c.
## Attempts
- round 3 (opus:low): consolidate (1-arg proto / 3-arg definition), diagnose, permute.
- 2026-11-14 U HackslotQueueStateFadeIn:
  - 3-parameter definition: the callee gains sw a1/a2 homes (fdiff 1)
  - K&R definition: OK (fixed)
  - 34e891 removed: 9 r + 1
  - x / named load before the test: 2 r (n's move scheduled above the branch); u16 named load: 7 r
  - variants scan and as1probe scan: nothing better
## Untried ideas
- 34e891: a natural statement order that keeps `move s1,a2` after the branch while the *value load stays before it.
## Evidence
- frame 0x58
- slot*0x30 spilled at 0x30(sp)
- flag homed at 0x4f(sp)
