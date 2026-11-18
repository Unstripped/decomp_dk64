# patrolPathStep (global, src/global/12E800.c)
## Sites
global:8072D13C:dead-if:b5948f dead-if (FIXED 2026-11-17): `if (gBehaviourWorkState) {}` at the top of the stuck-actor arm added one block to idx's range (n 33 -> 34, divisor 9 -> 10), dropping idx (M -13vreg) from 19/9 = 2.11 to 1.90 below key (M -3vreg, 2.0) so key coloured first (t2) and idx took t3.
Untagged steer removed in review: `s32 v` held the next index, the next waypoint key and the angle (unrelated quantities).
## Attempts
2026-11-10 round 4 Clean12E800 opus:low: remove/cond nohit, classify kept class 1.
2026-11-10 round 6 ReReview opus:xhigh: diagnose "colouring 28/28 with 3 differing from candidate 12, full=28"; permute best=0 only via `if (D_807FDCA0->entries) {}` (hack swap).
2026-11-11 round 16 Rev16B opus:xhigh: diagnose "uopt -l5: idx adjsave 1.90 with the test, 2.11 without; key 2.0"; permute best=0 `if (1) {}` before the `idx + 1 < pathCount` test (hack swap).
2026-11-14 RereviewW2Behaviour opus:high: `dir = idx; dir &= 0x80` -> `dir = idx & 0x80` (fdiff 0); u8 pad kept (frame).
2026-11-17 2026-11-17: cleanup CleanactorMoveWithinZone CleanactorMoveWithinZone anthropic/claude-opus-5-5: sweep --copy-of 0 hits (classify class 1); removal on the current body full=28 (same idx/key swap). Natural variants scored with variants.py try on the removal: `dir = gBehaviourWorkState->waypointIndex & 0x80; idx = gBehaviourWorkState->waypointIndex & 0x7F;` full=0 (fdiff 0, KEPT: idx savings 19 -> 17, adjsave 17/9 = 1.89 < key 2.0); idx second role as its own local `cur` full=2; per-role split of v (nextIdx/nextKey49) full=59; case-2 ternary full=28; parenthesised stuck condition full=28. Review of v: `next = (idx + 1 < pathCount) ? idx + 1 : 0;` full=0 (KEPT); separate s32 key or angle local after `s32 v` full=35 (frame 56 -> 64, registers identical); u8 nextKey for the 0x49 key full=127; double-read key full=291; `s16 angle` (or u16) declared before the s32 full=0 (KEPT, fills the 2-byte gap at 40(sp)), s32 angle there full=35.
## Untried ideas
none open (function has 0 sites).
## Evidence
0x3658 `lbu t3,37(v1)` (one waypointIndex load; idx t3, `andi t8,t3,0x7f` 0x367c, `move t3,t8` 0x368c); `move ra,t3; andi t7,ra,0x80; move ra,t7` (dir in ra, 0x366c-0x3678); key `lbu t2,0(t0)` 0x3688; `key * 10` spilled to 24(sp) 0x36a8.
Frame 56: type 52(sp), x 50, y 48, z 46, moved 45, nextKey 42 (sb across the jal in type 1, 0x3a6c); 40-41 free before the s32 slot (the s16 angle slot).
Case 0x49 0x3810-0x38ac: `addiu v0,t3,1` (idx + 1, no local needed), next a0, key `lbu v1,0(t7)` 0x3854, angle v0 stored to 238/230(gCurrentActor).
Stuck arm 0x3778-0x37ac: unk20 incremented twice (`sb t6,32(v1)` 0x3784, `sb t7,32(v1)` 0x379c): behaviour.
Type 3: state stored twice (0x37 at 0x3bcc when actorType == 0xAF, 0x40 at 0x3bf0): behaviour.
