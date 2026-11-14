# projectileSpriteRingUpdate (global, src/global/9BF30.c)
## Sites
- global:80697988:dead-if:c17942 `if (gCurrentActor) {}`: REMOVED (this unit).
  - Without it, &gCurrentActor stays in s1 for the whole function: 18 r + 9 |, with the prologue shifted.
  - The target re-materialises lui/addiu v0/a1 inside the kind == 1 block (0x86c, 0x89c).
  - A one-case `switch (kind) { case 1: ... }` supplies the same blocks.
- global:80697988:other:692110 `kind = sub->unk11;`: puts the dispatch byte in a0 (lbu 0x77c/0x844) instead of v0.
## Attempts
- round 28 (opus:low): 692110 diagnose (v0/a0), permute best=0 by a steer swap.
- 2026-11-14 U HackprojectileSpriteRingUpdate, scored with variants.py try (full=):
  - shape grid (18 bodies): one-case switch = 0 with or without the dead test; if/else without the test 61-65; full switch over unk11 178
  - kind spellings on the switch form:
    - no kind, assign-in-test, kind in both tests, s32: 4 each
    - s16: 38
    - early read: 22-59
## Untried ideas
- 692110: a natural second use of the byte that raises its priority (the permuter only found steers).
## Evidence
- frame 0x38
- sub spilled at 0x34(sp)
- gCurrentActor reloaded through s0 after every call
