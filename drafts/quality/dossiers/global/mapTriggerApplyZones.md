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
- 2026-11-16 HackmapChunksApplyLights2 (anthropic/claude-opus-5-5:high), classified by operand:
  - `if (1)`, `if (zone)`, `if (val)`, `if (gMapZones[idx]->enterCount)`: 1 (= removal)
  - `if (idx)` 29, `if (done)` 15, `if (zone->exitCount)` 6, `zone->enterCount && zone->enterCount` 5
  - So the guard is the same-value class. It works before or after `val = zone->exitCells`.
  - split enter/exit val locals, 4 declaration orders: 1
  - `else if (zone->exitCount != 0)`: 24
  - test through `gMapZones[idx]`: 22, with the loop bound too: 57
  - enterCells/exitCells through `gMapZones[idx]`: 1/1; exit loop bound through it: 56
  - zone assigned inside `!done`: 5; exit loop `j = zone->enterCount`: 6
## Untried ideas
none with evidence.
## Evidence
- try/trace_base.txt, try/trace_plain.txt (uopt -l 6): candidate 25 is reg 2 in the base and uncoloured without the test
- 0x3c98 `lbu v0,86(v1)` loads enterCount through the gMapZones value (v1), and 0x3cb0 `addiu s1,s2,54` builds val from the zone copy (s2). The plain body builds val from v1.
