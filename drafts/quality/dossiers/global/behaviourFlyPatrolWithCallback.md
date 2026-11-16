# behaviourFlyPatrolWithCallback (global, src/global/B7490.c)
## Sites
- global:806B42A8:comma:e1de6f `(0, gBehaviourExtraState->y)`: FIXED 2026-11-15. The target emits y's load first (lh t6,0(t2)/lh t8,6(v0) at 0x1cd8/0x1ce0). cfe always puts a bare local deref `*heightTarget` first in the commutative add, whatever the source order. With the Actor 0x178 component typed `FlyPatrolComponent { s16 hoverHeight; }`, cfe keeps source order, so `gBehaviourExtraState->y + patrol->hoverHeight` matches.
- global:806B42A8:other:9203db trailing `if (!gCurrentActor->state) {}`: kept. It emits no code; the target has nothing after `jal actorUpdateModelMatrix`. The dead use keeps the `&gCurrentActor` constant (uopt candidate 154) live across the call blocks, which gives adjsave < 0 and leaves it uncoloured. Without the dead use, the constant is coloured into t0 and rematerialised after each call.
## Attempts
- rounds 4/9/16 (opus:low): plain/diagnose/permute x3 per site. The permuter only swaps in other dead steers (Q0634).
- 2026-11-14 U HackbehaviourFlyPatrolWithCallback:
  - e1de6f:
    - operand order, no cast, `>` compare: 2 r each
    - named sum/operand locals and st reuse: 75-76 r
    - `(f32)*heightTarget + y`: 104 r
    - as1probe scan: nothing
    - variants scan: all 2
  - 9203db: second-switch respellings: 127-142 r
- 2026-11-15 U HackbehaviourFlyPatrolWithCallback2 (opus:high):
  - e1de6f:
    - `heightTarget[0]` either order: 10
    - no-cast y-first: 10
    - struct field h-first: 10
    - struct field y-first: OK (applied)
  - 9203db:
    - Q0908 guards on unrelated locals/globals (st, callback, sfxId, targetX, gBehaviourWorkState->timer): 5828-7099. `if (gCurrentActor) {}` gives OK.
    - variants scan of the tail-free retyped copy: baseline 211, no improvement.
## Untried ideas
- 9203db: a natural construct that reads `gCurrentActor` after the final call and emits no code. None is known. Any real use emits code, and the target has none.
## Evidence
- frame 0x38. s0 holds the gCurrentActor value and is reloaded after every call.
- uopt -l5:
  - base: candidate 154 ({1002} = `&gCurrentActor`) has zero-use live blocks 4,13,39,52,57,61,71, with adjsave -0.29 and -0.43 after the split (179).
  - tail-free: candidate 154 covers only use blocks, with adjsave +1.08, and is coloured t0.
- cfe ucode (`as1probe ucode --cfe`):
  - comma form: `lod gBehaviourExtraState; ldc 6; add; ilod` comes before `lod heightTarget; ilod`.
  - plain form: the reverse order.
  - y-first plain form: still emits `*h` first.
- The same component struct also retires the sibling FAKE 831e55 in actorAirPatrolStep, `gBehaviourExtraState->y + patrol->hoverHeight` (fdiff OK). It is applied in this copy, with behaviourEnemyBatUpdate also retyped.
