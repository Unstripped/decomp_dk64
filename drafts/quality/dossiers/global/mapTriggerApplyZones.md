# mapTriggerApplyZones (global, src/global/55B20.c)
## Sites
- global:80654A2C:dead-if:85ff81 `if (!zone->enterCount) {}` in the else arm.
  - The target has no re-read in that arm.
  - Without it: 1 diff. `addiu s1,v1,0x36` instead of `s2` at 0x3cb0: val's base comes from the gMapZones value, not the zone copy.
## Attempts
- rounds 2/9/35 (opus:low): classify, diagnose, permute (re-adds the test).
- 2026-11-14 U: about 70 natural bodies.
  - bare tests, while loops, outer for, one-case switch, block-scoped zone: 1
  - val placement, block-scoped val: 2
  - && done in the zone test: 5
  - pointer vs index induction: 6-7
  - zone assigned before or inside the test: 9-13
  - done = enterCount: 17
  - no idx local: 30
  - two independent ifs on the count: 44
  - early continue: 69-74
  - inverted arms: 74
  - declaration-order scan: 1 at best
## Evidence
- try/trace_base.txt, try/trace_plain.txt (uopt -l 6): candidate 25 is reg 2 in the base and uncoloured without the test
