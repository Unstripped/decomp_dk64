# healthHudDraw (global, src/global/10D2D0.c)

## Sites
- **global:807085D0:other:43016c** (`f32 animParams[22]`): FIXED (2026-11-15). The array is gone.
- **global:807085D0:other:76bae8** (x/y assigned in the argument list): FIXED (2026-11-15). x/y are now separate statements.

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

**2026-11-15 U HackhealthHudDraw2 (anthropic/claude-opus-5-5:high): both sites fixed, fdiff 0.**
- Named f32 alpha/cx/baseY scalars (s1) reproduce the 2026-11-14 result: spill temps at 0x9c/0x98/0x94.
- Inline repeated `fade * 511.0f` and `centerX` (no named alpha/cx), and baseY written inline: frame 0xf8; alpha -92, cx -96 and scaleX -24 all right relative to the frame top, but baseY lands at -100.
- Adding an `s16` baseY local holding `fade * 200.0` gives the 2-word gap before the hoisted `(f32)baseY` spill temp. Declared after the f32 locals it adds a word (frame 0x100, everything 4 too low, score 36). Declared right after `centerX` or `phase`, it sits in the free -12 halfword and matches.
- With that layout, all of these match on their own and together:
  - x/y as separate statements, in either order, or no x/y locals at all;
  - `for (i = 0; ...; i++)` with baseY assigned before the loop or at the top;
  - every `(f32)`/`(f64)`/`(s32)`/`(u32)` conversion cast dropped;
  - `80.0f`/`255.0f` ternary constants.
- Inline/named combinations of alpha/cx/baseY with f32 locals score 78-3905.

## Untried ideas
- none for these sites.

## Evidence
**Target homes:** 0x94 (hoisted `(f32)baseY`), 0xa0 (centerX conversion), 0xa4 (`fade * 511.0f`, reloaded every iteration) and 0xe8 (scaleX, declared home -24). Frame 0x100.
- Hoisted CSE/loop-invariant spill temps are allocated below every declared local, `_g` home and cfe ternary temp (Q0456, Q0880).
- An array element is a memory variable at its own offset, so `f32[22]` with [0]/[3]/[4]/[21] mimicked that layout.
