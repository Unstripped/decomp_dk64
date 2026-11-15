# spawnNodesSetRespawnHold (global, src/global/1295B0.c)
## Sites
global:80726EE0:do-while0:e9a088 do-while0: empty do-while(0) after actorQueueDelayedCallback kept command promoted to s3 (fixed 2026-11-15: loop body under if (!(flags & 0x80)) instead of the early continue)
## Attempts
2026-11-09..14 Clean1295B0 / ActorTypes / QualityTools / Rev17N / PermBatch1114c: proto-steer consolidation, mode-copy removal, removal trace 184->178, permuter 225 zeros all hacks
2026-11-15 HackspawnNodeActorOutOfRangeScaled opus-5-5:high: enclosing if (!(node->flags & 0x80)) block instead of continue (fdiff 0, FAKE removed); u8 mode copy x13 placements (8, s2/s3 swap), Actor local (45), while loop (55), &nodes[i] (47), switch default/case order (39), if-else for the switch (39), nested state-5 if (39)
## Untried ideas
none (site fixed)
## Evidence
Target: andi s3,a0,0xff before the loop, move s1,s3 per pass (switch selector), constants 6/-3/2/1/5 in s8/s7/s6/s5/s4, li t2,7 in the state-6 arm. Removal alone: command reloaded lbu s1,83(sp) per pass and li s8,7 hoisted.
