# raceSteerTowardTargetWaypoint (race, src/race/6650.c)

## Sites
- d6529e: one-element threshold array. KEPT.
- c64523: `work = distToWaypoint`. KEPT.
- 11f5b9: `if (gCurrentActor->x) {}`. KEPT.
- b8545a: `if (waypointRadius) {}`. KEPT.

## Attempts
- 2026-11-14 U HackraceSteerTowardTargetWaypoint: removing hacks singly scores 41/31/42/42; all four together 37. Natural tails 37-103 (see the ledger).

## Untried ideas
- What makes the threshold memory-resident with no array (an address-taken use the original may have had, e.g. a debug print compiled out). Not found.

## Evidence
- 0xd64/0xd68 `swc1 $f4,84(sp)` / `lwc1 $f6,84(sp)`: the threshold stores to and reloads from memory.
- 0xc14 `mov.s $f2,$f0` (distToWaypoint); 0xcd0 spill to 88(sp); 0xd5c reload into $f8.
- 0xd3c `mov.s $f18,$f16` (steerAngle copy of angleDelta).
