# healthHudDraw (global, src/global/10D2D0.c)

## Sites
- **global:807085D0:other:43016c** (`f32 animParams[22]`): KEPT.
- **global:807085D0:other:76bae8** (x/y assigned in the argument list): KEPT.

## Attempts
**2026-11-14 U Hack10D2D0HealthStats, 43016c.**
- Four f32 scalars, no pads: only two spill homes differ. alpha lands at 0x9c instead of 0xa4, and centerX at 0x98 instead of 0xa0. baseY (0x94) and scaleX (0xe8) are already right.
- The scalars become spill temps allocated bottom-up from 0x94. The target has the unused array words [1]/[2] at 0x98/0x9c.
- 360 declaration-order x pad bodies: best 13. Any pad grows the frame.

**76bae8.**
- Separate statements: 25 / 59 / 155.
- Only one of x/y inside the argument list: best 23.
- s32 x/y: 132-142.
- Repeated expressions in the second call: 135.

## Untried ideas
- A natural 0x58-byte local type with f32 at 0/0xC/0x10/0x54: none exists in include/; a file-local struct view would be the same hack.

## Evidence
**Target homes:** animParams[0] at 0x94, [3] at 0xa0, [4] at 0xa4 (reloaded every iteration), [21] at 0xe8. Frame 0x100.
