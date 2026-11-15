# bossPickWaypointStep (boss, src/boss/F0D0.c)

## Sites
boss:800330D0:dead-if:c9db6d dead-if: `if (waypointIndices[2] - val == 0) {}` CSEd the sub into $v0 ahead of the real test and set the ugen ring from 0x23c. FIXED (2026-11-14, HackbossMainStep).
boss:800330D0:other:2a75cb other: `waypointIndices[2] - val == 0 || ...` kept the load as the first beq operand (target 0x220 beq t7,t2; plain `==` gave beq t2,t7). FIXED (2026-11-14, HackbossMainStep).

## Attempts
2026-11-11 Rev16F opus-5-5:xhigh: uopt_trace copy vs variant (identical colours, ugen differs from 0x23c); both lines as `waypointIndices[2] == val` -> 1 diff (beq t2,t7); permute 660s best 0 only via `((0, val))` (rejected)
2026-11-12 Rev17L opus-5-5:low: sweep; CleanBossF0D0 permute best=10 with the site respelled
2026-11-14 PolishBossF0D0Names opus-5-5:high: parameter type/name only
2026-11-15 PermBatch1114: hack-free weights, no zero
2026-11-14 HackbossMainStep opus-5-5:high: with the u8 * array: `p[2] == val` / `val == p[2]` both 1 (cfe emits the add+ilod first in either order); `start_val == val` 2; early-return form `if (p[2] != val && val != start_val) return val;` 7; named u8 local for p[2] 25-78
2026-11-14 HackbossMainStep opus-5-5:high: parameter retyped to BossWaypointState * (typedef moved above, stand-in PROTO_SKIP + declaration): hack kept -> fdiff 0; `waypoints->previous == val` 1; `val == waypoints->previous` -> fdiff 0 (both FAKE lines gone)

## Untried ideas
none open for this function (no sites left)

## Evidence
cfe ucode for `p[2] == val` and `val == p[2]`: `lod p; ldc 2; add; ilod u8 off 0; cvt; lod val; cvt; equ` (array load first either way). uopt output: `lod a1 (cvt val); lod s0; ilod u8 off 2; cvt; equ` -> beq t2,t7. With `val == waypoints->previous` cfe emits `lod val; cvt; lod p; ldc 2; add; ilod u8 off 0; cvt; equ` (source order kept for the struct field, same add+ilod tree) and uopt outputs `lod s0; ilod u8 off 2; cvt; lod a1; equ` -> beq t7,t2 (0x220), as in the target.
Callers: only bossMainStep (3 calls); no other file declares or calls it.
