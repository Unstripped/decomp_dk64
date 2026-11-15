# slotQueueStateMoveToTarget (global, src/global/FCCD0.c)
## Sites
- global:806FA7BC:proto-steer:bb89d9: REMOVED.
  - The call really passes 3 arguments: a1 = *value (lhu 0x28c4), a2 = shown (lhu 0x28b8), consumed by jal 0x28cc.
  - The callee has 1 parameter, with no home stores.
  - The fix is a K&R definition of slotQueueGetCountStep, delivered as a stand-in bundle.
- global:806FA7BC:dead-if:34e891: *value is loaded before the null test (beqz delay slot 0x28c4); the NULL path reuses it at 0x295c.
- global:806FA7BC:other:8d84c1: REMOVED.
  - The sign is written as a ternary: `((target - shown) >= 0 ? 1 : -1) * step`.
  - The first |d| is now the min-if condition itself, so there is no absd local.
- global:806FA7BC:other:419496 (was e971d0): `dist` copy temp in the min-if: `dist = |d|; step = dist;`.
  - The |d| recomputation is the target's own code (a second blez/negu at 0x28f8), so it is written as a repeated ternary.
  - The temp is still needed: the target computes the second |d| into v0, then does move a3,v0 at 0x2908.
## Attempts
- round 3 (opus:low): consolidate (1-arg proto / 3-arg definition), diagnose, permute.
- 2026-11-14 U HackslotQueueStateFadeIn:
  - 3-parameter definition: the callee gains sw a1/a2 homes (fdiff 1)
  - K&R definition: OK (fixed)
  - 34e891 removed: 9 r + 1
  - x / named load before the test: 2 r (n's move scheduled above the branch); u16 named load: 7 r
  - variants scan and as1probe scan: nothing better
- 2026-11-14 U HackslotQueueGetMaxValue (opus:high), reconstruct of the step arithmetic:
  - min-if on a ternary |d|, `step = |d|` directly, sign ternary, unused absd/dist removed: 8.
    - With absd/dist still declared: 15, because the frame grows from 88 to 96.
  - same with a `diff = target - shown` local: 3. The only difference left is that the second |d| goes into a3 directly instead of v0 + move a3,v0.
  - other ABS spellings (<, >=, <=) and `step > |d|`: 3-12.
  - MIN-style `step = c ? |d| : step`: 32-39. A whole-expression MIN*sign: 46-53.
  - casts (u32)/(s16), `0 - d`, `d * -1`: 3-43. `step = dist = |d|`: 14.
  - variants scan of the diff-local body: nothing below 8.
  - `dist = |d|; step = dist;` (no diff local): 0, applied, tagged.
  - sign ternary with the old if/else absd kept: 18.
  - 34e891 on the new body:
    - removed: 13. Call args (slot, target, shown): 12.
    - target (and shown) assigned before the test: 4.
    - value-local null test: 11. Bare `if (value)`: 4.
    - as1probe scan of target-before-test: the best edit is to delete record 220 (move s0,a1 above the beq), which gives full=1.
  - permuter, 900 s, base 201 (diff local, target/shown before the test, no dead if): best 80. The best output only adds a copy temp for the second |d|, the same as dist, so the copy temp is confirmed as needed.
## Untried ideas
- 34e891: C that reads *value as an expression before the test (not assigned to target; s0 copy stays after the branch) without a dead if.
- 419496: a spelling where the second |d| is a separate value from step without a pure copy local.
## Evidence
- frame 0x58
- slot*0x30 spilled at 0x30(sp)
- flag homed at 0x4f(sp)
- d = s0 - s1 in v1 (0x28d4). First |d| in a0 (0x28e4/0x28e8). Step in a3 from v0 at 0x28dc.
- Second |d| in v0 (0x28fc/0x2904), then move a3,v0 (0x2908).
- Sign: li a0,-1 (0x28f4), bltz v1 / li a0,1 (0x290c/0x2918), then multu a0,a3 (0x291c).
