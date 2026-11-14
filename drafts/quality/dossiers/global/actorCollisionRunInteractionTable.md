# actorCollisionRunInteractionTable (global, src/global/7A510.c)
## Sites (kept)
- 6c7f1e: the `if (1) { found = 0; }` block swaps actorB and the gActorGlobalState base (s0/s1).
- 29a3dd: the `((s8 *)entry)[5]` read sets the bnel operand order (one instruction).
## Attempts
- 2026-11-14 opus:high (full=):
  - found = 0 placements: 14
  - one-case switch on event: 9/10
  - default-first switch: 22-23
  - break without a flag: 29
  - only the pun removed: 1
## Untried ideas
- A permuter run from the one-case switch form.
