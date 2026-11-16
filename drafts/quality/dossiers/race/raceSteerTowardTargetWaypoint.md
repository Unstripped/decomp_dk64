# raceSteerTowardTargetWaypoint (race, src/race/6650.c)

## Sites
All five removed on 2026-11-16 (copy `.scratch/HackraceSteerTowardTargetWaypoint/6650.c`, base a7a3de0d, fdiff 0):
- d6529e other (one-element threshold array): removed. The scalar threshold keeps `swc1 $f4,84(sp)` / `lwc1 $f6,84(sp)` (0xd64/0xd68) when its rhs reads `D_807FDCA0->entries[idx].radius` inline and no radius local exists.
- 11f5b9 / b8545a other (empty guards on `gCurrentActor->x` and `waypointRadius`): removed. They compensated for the radius local.
- c64523 other (`work = distToWaypoint`, angle temp reused): removed. `zoneDist = distToWaypoint - entries[idx].radius` stays a real variable in $f12.
- 0a1b37 other (dz reused for the span): removed. A separate `zoneWidth` local takes $f14 and the frame slot of the old radius local.

## Attempts
- 2026-11-14 U HackraceSteerTowardTargetWaypoint: removing hacks singly scores 41/31/42/42; all four together 37. Natural tails 37-103.
- 2026-11-15 U HackraceSteerTowardTargetWaypoint2: statement-order lever, guard subsets, two-element `dist[2]` 25, Q0558 threshold spellings with a radius local 41-43, permuter 900 s on the array-kept body (best 276).
- 2026-11-15 U HackraceSteerTowardTargetWaypoint3: lever 1 n/a, `static const` scale (Q1003), radius read moved into the arm 32, guard-operand probe (block splits).
- 2026-11-16 U HackraceSteerTowardTargetWaypoint anthropic/claude-opus-5-5:high: FIXED.
  - Local reuse grid (threshold/angle/arm temps over dx, dz, targetVel, work, new locals; 246 bodies, all hacks removed): all 37.
  - Scalar threshold with `register` 41, nested scope 47, `volatile` 28 (adds an arm reload at 0xd7c), `if (&waypointThreshold) {}` 48-49.
  - Separate angle local (any declaration slot) or inline `(s16)(f32)mathAngleDiscrete(...)`: 26/5. Only $f12/$f16 swap between work and the angleDelta conversion. Both have adjsave 1.5 and colour in candidate-bit order. `ucvt{v0}` is one candidate for both call returns, and its bit is assigned at the first call. The variable that receives mathAngleDiscrete gets the bit just before it.
  - In-place angle (`angleDelta = mathAngleDiscrete(...); angleDelta = mathAngleSignedDistance((s16)angleDelta, ...)`) with `work = dx*dx + dz*dz; dist = sqrtf(work)` gives 0 with the array, guards, copy and dz reuse kept.
  - From there, threshold = `entries[idx].radius * 1.2f` and both arm statements reading `entries[idx].radius` inline, with no radius local: 0 with the scalar threshold. Then guards, copy and sum temp all drop (0). A separate span local in the freed slot also gives 0.
  - Redundant `(f32)`/`(s16)` casts dropped (0).

## Untried ideas
- None open for this function.

## Evidence
- 0xd34 `lbu t8,7(t1)` / 0xd44 `cvt.s.w $f2`: one radius load after the calls. It is the CSE of the three inline `entries[idx].radius` reads in the threshold and arm, coloured $f2.
- 0xd64/0xd68 `swc1 $f4,84(sp)` / `lwc1 $f6,84(sp)`: scalar threshold store/reload. Its rhs ilod has count 1 in its block (Q0558), and the range is uncoloured.
- 0xd7c `sub.s $f12,$f8,$f2` (zoneDist), 0xd88 `sub.s $f14,$f6,$f2` (zoneWidth): rhs ilods keep both as variables.
- 0xd2c `cvt.s.w $f16` / 0xd3c `mov.s $f18,$f16`: angle, then steerAngle = angle.
- Frame: nine f32 locals before managerData (homes 100..68). The old radius local slot (96) now holds zoneWidth.
