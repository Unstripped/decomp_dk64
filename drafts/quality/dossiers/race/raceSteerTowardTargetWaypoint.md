# raceSteerTowardTargetWaypoint (race, src/race/6650.c)

## Sites
- d6529e other: one-element threshold array makes the threshold non-vreg: swc1 $f4,84(sp) / lwc1 $f6,84(sp) at 0xd64/0xd68. KEPT.
- c64523 other: `work = distToWaypoint` (copy-propagated; its position is irrelevant). With it dist's post-call piece stays uncoloured and is loaded into $f8 at 0xd5c. KEPT.
- 11f5b9 other: `if (gCurrentActor->x) {}`. Needed only together with b8545a: without both, steerAngle (home 100) is uncoloured and angleDelta takes $f18. KEPT.
- b8545a other: `if (waypointRadius) {}`. See 11f5b9. KEPT.
- 0a1b37 other: `dz = waypointThreshold[0] - waypointRadius`: the span shares dz's web ($f14 at 0xbe4 and 0xd88). KEPT.

## Attempts
- 2026-11-14 U HackraceSteerTowardTargetWaypoint: removing hacks singly scores 41/31/42/42; all four together 37. Natural tails 37-103 (see the ledger).
- 2026-11-15 U HackraceSteerTowardTargetWaypoint2 anthropic/claude-opus-5-5:high: statement-order lever (Q0468/Q0739 extension): 12 post-call orders of {work copy, steerAngle copy, radius, threshold} x guard subsets: 0 only with both guards and steerAngle before radius; either guard alone = none (42/43/88). dx/dz order and sum order x guard subsets 42-50. Empty `;` block split (Q0698) instead of either guard 42. Array-kept natural body with arm temps 23 (b4, best); quotient `/=` 23; dx reuse 35.
- same agent: two-element `f32 dist[2]` (dist + threshold) 25: dist then stores right after sqrtf instead of living in $f2 until 0xcd0.
- same agent: scalar threshold with the radius ilod in its rhs (Q0558; before/after radius, (f32), chained `(radius = ...) * 1.2f`) still forwarded: 41-43.
- same agent: chained `steerAngle = angleDelta = mathAngleSignedDistance(...)` (and the reverse) 42; steerAngle as ternary 87, else arm 73, `*=` 42.
- same agent: permuter 900 s on the array-kept natural body: base 476, best 276 (dist reassigned in the arm); as natural C 37-65.

## Untried ideas
- What makes the threshold memory-resident with no array (an address-taken use the original may have had, e.g. a debug print compiled out). Not found.
- A real (code-emitting) use that the original might have had in the first arm or after the threshold, which the two guards stand in for: none visible in the target asm.

## Evidence
- 0xd64/0xd68 `swc1 $f4,84(sp)` / `lwc1 $f6,84(sp)`: the threshold stores to and reloads from memory.
- 0xc14 `mov.s $f2,$f0` (distToWaypoint); 0xcd0 spill to 88(sp); 0xd5c reload into $f8 in the join block after the radius u8->f32 fixup (a split/uncoloured post-call piece, Q0561 (4)).
- 0xd2c `cvt.s.w $f16` angleDelta; 0xd3c `mov.s $f18,$f16` (steerAngle copy of angleDelta).
- Locals have declaration-order homes from 100 down (steerAngle 100, radius 96, angleDelta 92, dist 88, threshold 84, ... managerData 64, route 60, targetSpeed 56); 40(sp) is the idx*10 temp.
- uopt -l5 (hacked copy): dz (cand 49) is one long range coloured across the function (reuse); dist (59) adjsave 0.5, split into 190/191/192, post-call pieces uncoloured.
