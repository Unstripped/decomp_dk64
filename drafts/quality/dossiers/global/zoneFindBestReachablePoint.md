# zoneFindBestReachablePoint (global, src/global/1295B0.c)

## Sites
global:80725ED4:other:ccceec other: comma expressions `(d = X, best < d)` / `(d = Y, d < best)` in the two short-circuit arms of the best-point test (line 381). They computed d (a0) only inside each arm; the target does exactly that (no steer). Removed: the arms are now `(d = X) > best` / `(d = Y) < best`.

## Attempts
2026-11-14 cleanup HackzoneFindBestReachablePoint anthropic/claude-opus-5-5:high: embedded assignment `(d = X) > best` and `best < (d = X)` (all three operand orders) -> fdiff 0; flag form `better = 0; if (mode & 1) { d = X; if (best < d) better = 1; } if (!better && (mode & 2)) {...} if (better)` -> full=130; `better = best < d` flag form -> full=91. Dropping the (s32) casts on segmentIntersectsCircle2D args and on the distance expressions -> fdiff 0. Applied: embedded assignment, no casts, decimal literals.

## Untried ideas
none open (site removed).

## Evidence
- 0x1640 `andi v0,s6,0x1` (mode & 1) computed once, spilled to sp+0x50 at 0x1698, reloaded at 0x174C for the first arm test (CSE of the `best` init test and the loop test).
- 0x1750 `beqz t3` skips arm 1; 0x1758-0x179C target-actor squared distance (lwc1 0x7C/0x84 of gBehaviourTargetActor, cvt.s.w of e->x/e->z, trunc.w.s) into a0; 0x17A0 `slt at,s3,a0` (best < d), `bnez` to the update block 0x1804.
- 0x17AC `beqzl t6` (mode & 2) skips arm 2; 0x17B4-0x17F0 actor squared distance into a0; 0x17F8 `slt at,a0,s3` (d < best).
- 0x180C `move s3,a0` (best = d); e->x reused from v1 loaded in whichever arm ran.
