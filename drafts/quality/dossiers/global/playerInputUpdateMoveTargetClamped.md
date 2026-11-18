# playerInputUpdateMoveTargetClamped (global, src/global/E4090.c)

## Sites
- global:806E07F8:dead-if:c1ad5d dead-if: `if (dist > 1.0f) {}` after `dist = dist * (0.25 + 0.75 * (speedXZ / targetSpeed));`. It is the only reader of the scaled dist. uopt counts it as a use, so it keeps the scale chain and the 400 clamp: lw/lwc1 0x14f8-0x1504, div.s 0x1510, cvt.d.s 0x1528/0x152c, mul.d 0x1530, add.d 0x1534, mul.d 0x1538, cvt.s.d $f0 0x153c, and the 400 compare/mov.s at 0x14d8-0x14f4. The guard's own compare is never emitted. Without it, the 400 clamp and the scale disappear (full=95, text=93, shape=30). Only the 2048 compare and the 4096 wrap stay.

## Attempts
- 2026-11-09 .. 11-13, rounds 1/2/4/6/11/16/35, low/xhigh: remove, plain, cond, classify (class 2), recipe, uopt_trace (colouring 12 vs 14 assigned), four permuter runs (every best=0 adds a dead copy of the dist scaling or of the 4096 recompute). Details are in the history file.
- 2026-11-18, unit "2026-11-17: cleanup CleanplayerInputUpdateMoveTargetClamped", CleanplayerInputUpdateMoveTargetClamped, anthropic/claude-opus-5-5. All scores are `variants.py try` full= values; base = 0, removal = 95.
  - Q0908 classification by hand. `if (1) {}`, `if (moveYaw) {}`, `if (delta > 0) {}` and `if (moveYaw && gCurrentActor) {}` all score 95, the same as removal, so this is not a block split. `if (dist) {}` scores 0, so it is a same-value use.
  - Readers that score 0 are all dead:
    - `rate = dist;` into an unused local
    - `dist = dist;`: uopt deletes the self-copy (t.O has nothing at line 896) but keeps the chain
    - `if (dist < 1.0f) { dist = 1.0f; }`: uopt deletes the store and leaves the same `les`/`fjp` as the base
    - `dist = (dist > 1.0f) ? dist : 1.0f;`
    - `if ((dist = dist * (...)) > 1.0f) {}` (the 36B0 lever)
  - Compiled-out debug residue scores 95 (the chain is deleted):
    - `if (0) { mathAngleStepToward(&gCurrentActor->yaw, moveYaw, dist); }`
    - `if (0) { gCurrentActor->speedXZ = dist; }`
    - `while (0) { ... }`
    - `if (0) { osSyncPrintf("dist %f\n", dist); }`

    A constant-false debug block is folded before liveness, so it cannot be the origin of the kept chain.
  - Real uses:
    - dist as the turn argument (`mathAngleStepToward(..., dist)`): 73.
    - The guard after the call: 4. dist then lives across the jal: `swc1 $f0,28(sp)` in the delay slot and the frame grows to 32.
  - Other forms, both 95:
    - the chain stored into a separate dead local (`rate = dist * (...)`, as Q1029 says)
    - `dist *= ...` alone (the 7CA80 lever)
  - Stage of the dropped compare (as1probe keep, base). uopt's t.O still has `ldc f32 1.0 / lod $f0 / les f32 / fjp lab1 15 / lab 15` at line 896. ugen's t.s emits nothing for line 896, and only the 2048 and 400 `c.lt.s` remain. So ugen drops the empty compare with its jump-to-next. The removal copy shows the same thing for the 400 compare: uopt deletes the dead `dist = 400.0f` and keeps `les`/`fjp lab 14`, and ugen drops it.
  - Review: `else { if ... else if ... }` flattened to an else-if chain. The deadzone tests are now symmetric: `stickX/stickY > 0x1E` for `>= 0x1F`, and `> -0x1E` for `>= -0x1D`. fdiff 0. Copy sweep: 0 hits; c1ad5d classify class 2, cond no flips, recipe/remove nohit.

## Untried ideas
- None that could reach a codeless real use. The target has no consumer of the value (see Evidence), so any body that scores 0 needs a dead reader of dist. Q0200/Q1026/Q1029 say the same.
- Proposal to the lead (not applied): retag c1ad5d as `// ORIG: the target computes the scaled dist at 0x14f8-0x153c (div.s 0x1510 .. cvt.s.d $f0 0x153c) and never reads it`. This conflicts with ladder.md 627052: the offset must show the tagged line's OWN operations, and the guard's c.lt.s/bc1f are absent. Under the standing rule the site stays FAKE. DIRECTOR RULING (2026-11-17f, turn 125): ORIG retag REFUSED. An ORIG tag cites the tagged line's own operations, and the guard's c.lt.s/bc1f are absent (same as 627052). c1ad5d stays FAKE; this proposal is kept here as evidence only.

## Evidence
- Frame 24: only ra at 20(sp). No stack slot holds dist.
- dist is computed as follows:
  - abs: subu v0 0x1498, blez 0x149c, cvt.s.w $f0 0x14ac/0x14b8.
  - 2048 compare 0x14bc, 4096 wrap sub.s 0x14d4, 400 compare 0x14e4, mov.s 0x14f4.
  - Scale: div.s $f4,$f16,$f18 0x1510; cvt.d.s 0x1528 (ratio) and 0x152c (dist); mul.d 0x1530; add.d 0x1534; mul.d 0x1538; cvt.s.d $f0,$f8 0x153c.
- $f0 is never read after 0x153c, and the jal mathAngleStepToward at 0x1554 clobbers it.
- The call arguments carry nothing from dist:
  - a0 = addiu a3,230 (0x1524, &yaw)
  - a1 = lh 238(a3) (0x148c, moveYaw)
  - a2 = (s16)(turnRate / 4): lh 72(v0) 0x1520, bgez/sra/addiu/sra 0x1540-0x154c, sll 0x1550, sra in the delay slot 0x1558
- From 0x155c to jr ra at 0x1854 there is no float instruction, no compare of dist and no store of it.
- The brief's 0x1548 for the cvt.s.d is 0x153c. 0x1540-0x1558 is the turnRate/4 rounding.
