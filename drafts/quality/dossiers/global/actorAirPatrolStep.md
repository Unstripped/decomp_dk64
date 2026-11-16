# actorAirPatrolStep (global, src/global/B7490.c)

## Sites
- 831e55 `y - (0 - *heightPtr)`: FIXED 2026-11-15 (HackbehaviourFlyPatrolWithCallback2).
  - The target evaluates *heightPtr before y, but adds them in the order y + h (`addu t2,t9,t1`).
  - cfe always puts a bare local deref `*heightPtr` first in a commutative add, whatever the source order. A struct field keeps the source order.
  - Fix: the Actor 0x178 component is typed `FlyPatrolComponent` (shared with behaviourFlyPatrolWithCallback and behaviourEnemyBatUpdate), and the sum is written `gBehaviourExtraState->y + patrol->hoverHeight`. fdiff OK.

## Attempts
- 2026-11-14 U HackactorAirPatrolStep: see the ledger for line counts.
- 2026-11-15 U HackbehaviourFlyPatrolWithCallback2: component struct with a y-first field sum. fdiff OK.

## Untried ideas
- None. No open sites.

## Evidence
- Target:
  - 0x22e0 `lh t1,0(v0)`
  - 0x22e4 `lh t9,6(t8)`
  - 0x22f4 `addu t2,t9,t1`
  - 0x22fc `sh t2,50(sp)`
