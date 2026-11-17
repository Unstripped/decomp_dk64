# throwableBarrelUpdate (global, src/global/80150.c)
## Sites
global:8067C71C:goto:ubf033 goto: `goto block_despawn;` ends case 0x95 of the inner actorType switch (case 8) with a jump into the 0x85/default tail; kept (goto-hand kept, Q0591).
## Attempts
2026-11-15 HackthrowableBarrelUpdate HackthrowableBarrelUpdate anthropic/claude-opus-5-5:high: despawn flag local set FALSE in case 0x1A, tail under `if (despawn)` -> variants try full=9 (li v1,1 before the dispatch, sw v1,96(sp) spill across actorSpawn, lw v1 + beqzl before the tail)
2026-11-15 HackthrowableBarrelUpdate HackthrowableBarrelUpdate anthropic/claude-opus-5-5:high: default arm holding an inner `switch (actorType)` (0x95 break / 0x85) then the tail -> full=21 (with or without the last break)
2026-11-15 HackthrowableBarrelUpdate HackthrowableBarrelUpdate anthropic/claude-opus-5-5:high: `if (actorType == 0x1A) {...} else { inner switch; tail }` -> full=21 (with or without the last break)
2026-11-17 HackthrowableBarrelUpdate2 anthropic/claude-opus-5-5 (after b603f25c): case 0x95/0x85/default labels merged into one arm holding `if (actorType == 0x95) {...} else if (actorType == 0x85) D_80029FA0--;` before the tail -> full=21 shape=9; default-arm inner switch re-measured 21 shape=12.
(history: duplicated tail +4 insns/16 bytes; folding 0x95 into default via an actorType test 1005)
## Untried ideas
none that keep one sorted compare chain: every structured spelling either adds the flag web or a second dispatch.
## Evidence
0x1f48-0x1f6c: one compare chain li at,26/beq; li at,133/beq 0x2040; li at,149/beq 0x1ff0; b 0x2054 (default).
0x1ff0-0x203c: case 0x95 body ends `b 0x2054` (swc1 floorY in the delay slot).
0x2040-0x2050: case 0x85 `D_80029FA0--` falls through into 0x2054.
0x2054-0x2060: the single shared tail jal tagBarrelDespawnEffects; jal actorDespawn; then lw s0 + b 0x2198.
