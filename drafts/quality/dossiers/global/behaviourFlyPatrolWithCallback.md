# behaviourFlyPatrolWithCallback (global, src/global/B7490.c)
## Sites
- global:806B42A8:comma:e1de6f `(0, gBehaviourExtraState->y)`: the target loads lh t6,0(t2) then lh t8,6(v0) (0x1cd8/0x1ce0). The plain form swaps the names (2 r). This is fixed before as1.
- global:806B42A8:other:9203db trailing `if (!gCurrentActor->state) {}`: without it uopt caches &gCurrentActor in t0 for the whole function. The target re-materialises lui/lw s0 each time.
## Attempts
- rounds 4/9/16 (opus:low): plain/diagnose/permute x3 per site. The permuter only swaps in other dead steers (Q0634).
- 2026-11-14 U HackbehaviourFlyPatrolWithCallback:
  - e1de6f:
    - operand order, no cast, `>` compare: 2 r each
    - named sum/operand locals and st reuse: 75-76 r
    - `(f32)*heightTarget + y`: 104 r
    - as1probe scan (3804 edits): nothing
    - variants scan: all 2
  - 9203db: second-switch respellings (direct, st argument, if, default arm): 127-142 r
  - target tail: no load after actorUpdateModelMatrix
## Untried ideas
- e1de6f: a uopt -l 6 comparison of the two lh temps' creation order (the plain form has the same trace length per round 9).
- 9203db: find what in uopt's address-CSE cost makes one extra gCurrentActor reference after the last call flip &gCurrentActor caching off.
## Evidence
- frame 0x38; s0 = gCurrentActor value, reloaded after every call
- heightTarget spilled at 0x34
