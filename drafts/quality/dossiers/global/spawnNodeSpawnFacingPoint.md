# spawnNodeSpawnFacingPoint (global, src/global/1295B0.c)
## Sites
global:8072752C:other:97e318 other: `dy` reused for the speed argument kept the CSE spills dx*dx/dz*dz at 48/44(sp) (fixed 2026-11-15: s16 speed local)
## Attempts
2026-11-14 Rereview1295B0b opus-5-5:high: s32 speed local after dz, before dx, before yaw, first, or inlined into the call: spills move to 44/40
2026-11-15 HackspawnNodeActorOutOfRangeScaled opus-5-5:high: `s16 speed` declared right after `yaw` (fdiff 0, FAKE removed); s16 speed before yaw (2); dy inlined into the dist sum with s32 speed in its word (4: dz/dy a0/a1 swap), other inlined axes (6-48)
## Untried ideas
none (site fixed)
## Evidence
Frame 72: yaw s16 home 70(sp) (sh v0,70), dist 64 (swc1 $f0,64 across the second sqrtf), dx/dy/dz words 60/56/52 never stored, CSE spills dx*dx 48 / dz*dz 44; the halfword 68 beside yaw is free, so an s16 local there costs no word. spawnNodeSpawnById takes s16 speed; the trunc.w.s result goes straight to the arg slot (sw t3,20(sp)).
