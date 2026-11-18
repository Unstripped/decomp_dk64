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
- 2026-11-17 CleanmapChunksApplyLights (anthropic/claude-opus-5-5), uopt ucode (as1probe keep + ucode) and new bodies:
  - mechanism: uopt's output is identical in both forms at the enter arm (`lod Adt Rmt $s2; ldc 0x36; add; str $s1`). With the test, uopt
    colours cand 25 (the raw u8 ilod of enterCount, live bb4 + bb15) to $v1: `ilod u8 86; str u32 Rmt $v1; lod $v1; cvt; str $v0`, and the
    else arm reads `lod u32 Rmt $v1; tjp` to the next label (deleted by ugen). ugen never materialises $v1, but the str ends its
    v1 == s2 copy tracking (from `move s2,v1` at 0x3c94), so the later `lod $s2` stays s2 at 0x3cb0. Without it ugen keeps substituting v1.
  - `else if (zone->enterCount == 0)` / `else if (!zone->enterCount)`: 22 (a real branch around the exit loop)
  - `> 0` / `>= 1` count tests: 2; `!= 0U`: 1
  - `j = 0` once before the count test, both loops `for (; ...)`: 6
  - `done = 1` after the enter loop: 2; exit arm `done = 0;`: 16
  - `mapCellSetFlag(*val, done)` in the enter loop: 1; in both loops: 62
  - enter loop as `j = 0; while (j < zone->enterCount)`: 1
  - variants.py scan of the removal copy: 31 variants, best 1
  - permuter 900 s from the removal body, hack-free weights: base 5, 8 outputs at 0, all re-insert the dead test: in the else arm, or as
    `if (zone->enterCount) {}` just before the `!= 0` test inside `!done` (then cand 25 is live from that block into the test block)
  - readability: while loop -> `for (i = 0; ...)`, `!= 0` -> `!= NULL` on gMapZones[idx] (fdiff 0, removal still 1)
## Untried ideas
none with evidence: the target needs an invisible uopt write of $v1 (a second-block use of the raw u8 enterCount while it is still available, i.e.
before the first store/call of either arm), and every live C use of it there adds code.
## Evidence
- try/trace_base.txt, try/trace_plain.txt (uopt -l 6): candidate 25 is reg 2 in the base and uncoloured without the test
- 2026-11-17 uopt -l 5: cand 25 {1284|0} uilod{426} live bb 4 (firstisstr) and bb 15 (deadout) only with the test; absent without it
- 0x3c98 `lbu v0,86(v1)` loads enterCount through the gMapZones value (v1), and 0x3cb0 `addiu s1,s2,54` builds val from the zone copy (s2). The plain body builds val from v1.
