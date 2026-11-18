# actorMoveWithinZone (global, src/global/12E800.c)
## Sites
global:8072AB74:dead-if:bd5eb8 dead-if (FIXED 2026-11-17): `if (0) {}` between `gBehaviourWorkState->flags |= 0x4000;` and `return 0;` in the `state == 0x37` arm split the store block from the return-0 `v0` write; without it bit 14 (entry `uilod gBehaviourWorkState`) has `v0` forbidden and takes `v1`, const 182 (`&gCurrentActor`) takes `v0` (whole-function v0/v1 swap, full=69).
(retired) proto-steer 72822b / 88492d / ed1131: consolidated in rounds 15-16 (collisionCheckActorFloor s32 return, zoneCheckActorInside 5th param).
View retired 2026-11-17: the file-local `ZoneByteView` / `CURRENT_ZONE_BYTES` (Zone.unk19 read as u8) is gone; include/actor.h `Zone.unk19` is now `u8` (header bundle with this merge, director ruling); both tests read `D_807FDCA0->unk19`.
## Attempts
2026-11-10 round 4 Clean12E800 opus:low: remove/cond nohit, classify kept class 1; consolidate/diagnose/permute on the proto steers (hack swaps).
2026-11-10 round 6 ReReview opus:xhigh: diagnose "colouring 17/17 with 6 differing from candidate 0, full=69"; permute best=0 only via an inserted `if (1) { }` (hack swap); reconstruct nohit (full=120).
2026-11-11 round 15 Rev15B opus:low: diagnose "&gCurrentActor in v1 / gBehaviourWorkState in v0 swapped whole function"; permute best=0 re-adds `if (!centerX) {}`.
2026-11-11 round 16 Rev16B opus:xhigh: diagnose "lui of gBehaviourWorkState fills the bnez delay slot at 0x14e8, 0x4000 sh moves into the b delay slot (fdiff 102)"; permute best=0 re-adds `if (0) {}` + `do {} while (0)`.
2026-11-11 round 16 Rev16J opus:low: permute best=0 `if (1) { ... }` wrapper around the polygonContainsPoint2D test and the 0x4000 store (hack swap).
2026-11-17 2026-11-17: cleanup CleanactorMoveWithinZone CleanactorMoveWithinZone anthropic/claude-opus-5-5: sweep --copy-of 0 hits (classify class 1); removal on the current body full=69; uopt -l5 base vs removal: bit 14 forbidden [3 4 5 6] -> [1 3 4 5 6] (store block = return block); variants: `if (poly == 0) { speed } else { flags |= 0x4000; } return 0;` full=0 (fdiff 0, KEPT), same with `return result;` full=0, `return result;` without the if/else full=69 (no block split), `if (poly != 0) { store } else { speed }` full=23 (block order). Review: Zone.unk19 s8 -> u8 header hunk verified on a shadow include (hdr/12E800.c, 1295B0, boss/6240 OK).
## Untried ideas
none open (function has 0 sites; the view is retired).
## Evidence
0x1074 entry: `lui v1,%hi(gCurrentActor)` at 0x1078 (const &gCurrentActor in v1), `lw v0,0(a2)` (gBehaviourWorkState value in v0).
0x14e4 `bnez v0,0x1534` with `lui s0` (gCurrentActor) in the delay slot; then-arm: `move v0,zero` 0x1524, `b 0x1810` 0x152c, `swc1 $f6,184(s0)` delay.
0x1534-0x154c: `lui v0; lw v0,0(v0); lhu t5,26(v0); ori 0x4000; sh t6,26(v0); b 0x1810; move v0,zero`.
All `return 0` paths branch to the epilogue 0x1810; `return result` loads `lbu v0,67(sp)` at 0x180c.
Zone+0x19 reads: `lbu t5,25(t4)` 0x1228, `lbu t6,25(t5)` 0x13ec (u8: Zone.unk19 is declared u8 since this merge).
