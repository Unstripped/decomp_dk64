# actorCollisionFindTableEntry (global, src/global/7A510.c)
## Sites
- global:80675E3C:dead-store:3c9cea: REMOVED. The search loop now exits on `!match && pattern != 0` instead of a dead def plus break.
## Attempts
- 2026-11-14 opus:high (full=):
  - while-condition form: 0 (applied)
  - return in loop: 7
  - index loop: 9
  - break forms / initialiser: 16
## Evidence
- entries in $s2 with a single epilogue `move v0,s2`.
