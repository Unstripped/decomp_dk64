# actorCollisionProcessHit (global, src/global/7A510.c)
## Sites (kept)
- b8c7d3: the phase byte re-read through interactions keeps the entry induction in $s1 (Q0589).
## Attempts
- 2026-11-14 opus:high (full=):
  - entry->phase: 40; hitPhase: 53; indexed: 85; no locals: 108
  - typed interactions pointer: same scores
## Views
- FindTableEntry returning `CollisionInteractionEntry *` would retire the casts (codegen unchanged: same scores).
