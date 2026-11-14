# actorUpdateCollisionSpheres (global, src/global/70FD0.c)

## Sites
- 208f26: dead `if (base) {}`. REMOVED.
  - It lowered base's adjsave below the -1 constant's, so -1 took s5 and base s6, as in the target.
  - A switch on node->mtxOffset with `case -1` / `default` gives the same order.

## Attempts
- 2026-11-14 U HackactorUpdateCollisionSpheres:
  - switch form: fdiff 0.
  - Order, declaration, loop-shape and early-return variants: 4 lines each.
  - base computed in the idx arms: 31-51.

## Untried ideas
- None.

## Evidence
- uopt -l5:
  - With the dead read: base (cand 46) 3.0 vs const -1 3.33.
  - Without it: 3.67 vs 3.33.
- Target: `li s5,-1`; base in s6.
