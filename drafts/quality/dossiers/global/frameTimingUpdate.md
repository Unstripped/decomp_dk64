# frameTimingUpdate (global, src/global/5230.c)

## Sites
- global:80600674:dead-if:59db80: the dead read `if (gFrameDelta && gFrameDelta) {}` in the 1-8 sample loop. It added blocks to the loop, which lowered the adjsave of the D_8076AF00 base constant (Q0523), so uopt left it uncoloured and rematerialised `lui`/`addiu D_8076AF00` per access (target 0x214, 0x260, 0x2a8...). Without it, the base is hoisted into s1 and the frame grows 8 -> 16. REMOVED.

## Attempts
- 2026-11-14 U HackframeTimingUpdate:
  - uopt -l5: cand 162 (const {906}) has adjsave 1.667 and is coloured in s1 without the dead read; with MAX/MIN it has 1.333 and is uncoloured.
  - Results (fdiff full lines):
    - `MAX(max, x)` / `MIN(min, x)`: 0.
    - Operands swapped, or `>`/`<` ternaries: 25.
    - Sample read once into a local: 209.
    - `(idx - 1) & 7`: 169.
    - `--idx < 0`: 60.
    - gFrameDelta in a local: 60.

## Untried ideas
- Retire the SCHED284 view with a volatile `retraceCount` field (header-request.md).

## Evidence
- Target: frame 8 (only s0 saved); the loop is unrolled by 4 with a remainder; max is in a1, min in a2, the sample in s0.
