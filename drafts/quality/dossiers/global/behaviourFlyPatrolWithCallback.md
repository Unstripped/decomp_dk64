# behaviourFlyPatrolWithCallback (global, src/global/B7490.c)
## Sites
- global:806B42A8:comma:e1de6f `(0, gBehaviourExtraState->y)`: FIXED 2026-11-15. The target emits y's load first (lh t6,0(t2)/lh t8,6(v0) at 0x1cd8/0x1ce0). cfe always puts a bare local deref `*heightTarget` first in the commutative add, whatever the source order. With the Actor 0x178 component typed `FlyPatrolComponent { s16 hoverHeight; }`, cfe keeps source order, so `gBehaviourExtraState->y + patrol->hoverHeight` matches.
- global:806B42A8:other:9203db trailing `if (!gCurrentActor->state) {}`: FIXED 2026-11-17 (CleanbehaviourFlyPatrolWithCallback). The dead use was only needed because of the m2c selector local `st`. Read `gCurrentActor->state` inline in the boss-phase test and in both switches, and drop `st`: the `&gCurrentActor` constant then stays uncoloured with no trailing use, and the whole object fdiffs OK.
## Attempts
- rounds 4/9/16 (opus:low): plain/diagnose/permute x3 per site. The permuter only swaps in other dead steers (Q0634).
- 2026-11-14 U HackbehaviourFlyPatrolWithCallback:
  - e1de6f:
    - operand order, no cast, `>` compare: 2 r each
    - named sum/operand locals and st reuse: 75-76 r
    - `(f32)*heightTarget + y`: 104 r
    - as1probe scan: nothing
    - variants scan: all 2
  - 9203db: second-switch respellings (first switch still on `st`): 127-142 r
- 2026-11-15 U HackbehaviourFlyPatrolWithCallback2 (opus:high):
  - e1de6f:
    - `heightTarget[0]` either order: 10
    - no-cast y-first: 10
    - struct field h-first: 10
    - struct field y-first: OK (applied)
  - 9203db:
    - Q0908 guards on unrelated locals/globals (st, callback, sfxId, targetX, gBehaviourWorkState->timer): 5828-7099. `if (gCurrentActor) {}` gives OK.
    - variants scan of the tail-free retyped copy: baseline 211, no improvement.
- 2026-11-17 U CleanbehaviourFlyPatrolWithCallback (opus:xhigh). Scores are `variants.py try` full diff on the tail-free body (211 baseline):
  - 9203db, lever (a), CSE'd second reads:
    - `switch (st = gCurrentActor->state)`: 211
    - second switch on the inline read with `patrolPathStep(st, 1)`: 224
    - boss test `gCurrentActor->state != 0x37` with `st` kept for the switch: 217
    - These leave the {1002} candidate at adjsave 1.077 (or 1.000), coloured t0.
  - 9203db, lever (b): a same-block `Actor *actor = gCurrentActor` for the final call gives 211. A dead `if (!gCurrentActor->state) {}` at the join before the final call also gives 211.
  - 9203db, `st` removed:
    - only the first switch inline (with or without the in-arm `st` reload): 223
    - boss test and first switch inline (`st` only in the second switch): OK
    - `st` removed entirely: OK (applied)
  - The cast-free `(s16)`/`(f32)` conversions, `unk155++` and `yaw +=` fdiff OK (applied in review).
  - 9203db, permuter with hack-free weights from the tail-free body (-j 2, 900 s, baseline 5261): best=0, but both zeros (output-0-1/0-2) only add a dead `if (gCurrentActor) {}` after `patrolPathStep` inside the case 2/3 arm. That is the same dead-use steer one jal earlier (Q0634): nohit.
## Untried ideas
- none for this function: it has no hack sites left.
## Evidence
- frame 0x38. s0 holds the gCurrentActor value and is reloaded after every call (`lui s0`/`lw s0,%lo(s0)`, e.g. 0x1b98/0x1b9c, 0x20b4/0x20b8). No register ever holds `&gCurrentActor`.
- uopt -l5/-l6, candidate {1002} = `&gCurrentActor`:
  - base (trailing dead test): zero-use live blocks 4,13,39,52,57,61,71. Adjsave is -0.29, and -0.43 after the split (179). Not coloured.
  - tail-free with `st`: the candidate appears in 13 blocks (15 uses: blocks 12 and 37 have 2 each). needreglod is set only at block 0, giving adjsave 14/13 = +1.077. It is coloured t0 at priority 10, ahead of targetX, targetZ and patrol (48/52/0), which move from t0/t1/t2 to t1/t2/t3. Code: `lui t0`/`addiu t0` at entry and after each call, then `lw s0,0(t0)`.
  - `st` removed: block 7 (label 175, the join holding the boss-phase test) loses its {1002} appearance, and block 12 drops to one use. The range splits 143 -> 168 -> 173 -> 174. Every piece has adjsave 0.0 (for example, the 143 piece has uses at 0,26,32,44,45 and needreglod at 0,4,13,26,45), so none is coloured. Every access rematerialises `lui s0/lw s0`, as in the target.
  - Switch inline but `st = gCurrentActor->state` still stored at the join: adjsave 1.000, still coloured t0 (223).
- cfe ucode (`as1probe ucode --cfe`):
  - comma form: `lod gBehaviourExtraState; ldc 6; add; ilod` comes before `lod heightTarget; ilod`.
  - plain form: the reverse order.
  - y-first plain form: still emits `*h` first.
- The same component struct also retires the sibling FAKE 831e55 in actorAirPatrolStep, `gBehaviourExtraState->y + patrol->hoverHeight` (fdiff OK).
