# actorAirPatrolStep (global, src/global/B7490.c)

## Sites
- 831e55: `y - (0 - *heightPtr)`. KEPT.
  - The target evaluates *heightPtr before y, but adds them in the order y + h (`addu t2,t9,t1`).
  - Natural sums evaluate y first. The snapshot local fixes the evaluation order but adds a coloured web.

## Attempts
- 2026-11-14 U HackactorAirPatrolStep: see the ledger for line counts.

## Untried ideas
- None natural.

## Evidence
- Target 0x22e0 `lh t1,0(v0)`, 0x22e4 `lh t9,6(t8)`, 0x22f4 `addu t2,t9,t1`, 0x22fc `sh t2,50(sp)`.
