# raceSteerTowardTargetWaypoint (race, src/race/6650.c)

## Sites
- d6529e other: one-element threshold array makes the threshold non-vreg: swc1 $f4,84(sp) / lwc1 $f6,84(sp) at 0xd64/0xd68. KEPT.
- c64523 other: `work = distToWaypoint` (copy-propagated; its position is irrelevant). With it dist's post-call piece stays uncoloured and is loaded into $f8 at 0xd5c. KEPT.
- 11f5b9 other: `if (gCurrentActor->x) {}`. Needed only together with b8545a: without both, steerAngle (home 100) is uncoloured and angleDelta takes $f18. The guard operand is irrelevant (`if (idx)`, `if (targetSpeed)`, `if (distToWaypoint)` all match): it is a uopt block split (Q0698-like) that lowers dist's priority. KEPT.
- b8545a other: `if (waypointRadius) {}`. See 11f5b9; `if (idx)`, `if (targetSpeed)`, `if (waypointThreshold[0])` also match, `if (distToWaypoint)` does not (42: adds a dist use). KEPT.
- 0a1b37 other: `dz = waypointThreshold[0] - waypointRadius`: the span shares dz's web ($f14 at 0xbe4 and 0xd88). KEPT.

## Attempts
- 2026-11-14 U HackraceSteerTowardTargetWaypoint: removing hacks singly scores 41/31/42/42; all four together 37. Natural tails 37-103 (see the ledger).
- 2026-11-15 U HackraceSteerTowardTargetWaypoint2 anthropic/claude-opus-5-5:high: statement-order lever (Q0468/Q0739 extension): 12 post-call orders of {work copy, steerAngle copy, radius, threshold} x guard subsets: 0 only with both guards and steerAngle before radius; either guard alone = none (42/43/88). dx/dz order and sum order x guard subsets 42-50. Empty `;` block split (Q0698) instead of either guard 42. Array-kept natural body with arm temps 23 (b4, best); quotient `/=` 23; dx reuse 35.
- same agent: two-element `f32 dist[2]` (dist + threshold) 25: dist then stores right after sqrtf instead of living in $f2 until 0xcd0.
- same agent: scalar threshold with the radius ilod in its rhs (Q0558; before/after radius, (f32), chained `(radius = ...) * 1.2f`) still forwarded: 41-43.
- same agent: chained `steerAngle = angleDelta = mathAngleSignedDistance(...)` (and the reverse) 42; steerAngle as ternary 87, else arm 73, `*=` 42.
- same agent: permuter 900 s on the array-kept natural body: base 476, best 276 (dist reassigned in the arm); as natural C 37-65.
- 2026-11-15 U HackraceSteerTowardTargetWaypoint3 anthropic/claude-opus-5-5:high: lever 1 (template initialiser) does not apply: no lw/sw template copy before 0xd64. A file-scope `static const f32` scale goes to .data (.data +16, .rodata -16) and the scalar threshold is still forwarded: fdiff 1. Radius read moved into the arm so only the threshold rhs reads it before the compare (Q0558): natural body A1 32, with named arm temps A3 32, + work copy A4 47, + radius guard A5 39/53; threshold is coloured $f18 every time. Guard-operand probe: any int/float local in either guard matches except dist in the second (42).

## Untried ideas
- d6529e: lever 1 is n/a (no template). Lever 2: no plain-scalar spelling found that is both unforwarded and uncoloured. The threshold rhs ucvt{1596|0} is CSE'd with the first compare's radius load (cand 64), so Q0558's ilod count is never 1. An uncoloured scalar would also need all six caller-saved FP colours ($f0 $f2 $f12 $f14 $f16 $f18) busy across its range; the base only gets that through the work copy ($f12) and the dz reuse ($f14).
- What makes the threshold memory-resident with no array (an address-taken use the original may have had, e.g. a debug print compiled out). Not found.
- 11f5b9/b8545a: they are block splits, not reads, so a natural replacement needs a code-free uopt block at both positions: the first arm before the increment, and between the threshold store and the compare. Q0698's fix (a two-case `switch`) has no selector here. Untried: a natural construct that ugen removes but uopt keeps as a block.

## Evidence
- 0xd64/0xd68 `swc1 $f4,84(sp)` / `lwc1 $f6,84(sp)`: the threshold stores to and reloads from memory.
- 0xc14 `mov.s $f2,$f0` (distToWaypoint); 0xcd0 spill to 88(sp); 0xd5c reload into $f8 in the join block after the radius u8->f32 fixup (a split/uncoloured post-call piece, Q0561 (4)).
- 0xd2c `cvt.s.w $f16` angleDelta; 0xd3c `mov.s $f18,$f16` (steerAngle copy of angleDelta).
- Locals have declaration-order homes from 100 down (steerAngle 100, radius 96, angleDelta 92, dist 88, threshold 84, ... managerData 64, route 60, targetSpeed 56); 40(sp) is the idx*10 temp.
- uopt -l5 (hacked copy): dz (cand 49) is one long range coloured across the function (reuse); dist (59) adjsave 0.5, split into 190/191/192, post-call pieces uncoloured.
- uopt -l6 (this session): base colours dx $f2, the throttle/steer ilods (cand 118/126) $f0, dz (49) $f14, radius (97) $f2, work (83) $f12, the angleDelta cvt (85) $f16, steerAngle (94) $f18, then dist (59, split 190/191) $f2. Without both guards, dist (59) is coloured whole in $f16 before steerAngle (92, not colored, not splittable).
