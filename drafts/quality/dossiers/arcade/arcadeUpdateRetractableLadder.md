# arcadeUpdateRetractableLadder (arcade, src/arcade/0_game.c)
## Sites
arcade:80030A04:other:3dd828 other (kept): `f32 step` holds the decremented animTimer read (role 1: `step < 0.0f`,
  lwc1 $f2 +0x44, c.lt.s +0x48; merged with the post-rand reload lwc1 $f2 +0x78 for the `< 200.0f` test +0x88) and then
  the +-0.2 y step (role 2: lwc1 $f0 +0xa0/+0xa4, add.s +0xb4). One declared word: the reuse gives the step variable
  uopt adjsave 2.5 so it colours first ($f0); the timer reload and the y reload then take $f2.
## Attempts
2026-11-24 Polisharcade0e anthropic/claude-opus-5-5:xhigh: pre-existing reuse, tagged (R5); direct field compare or an
  assignment in the test swaps $f0/$f2; a separate never-stored f32 timer local swaps them and grows the frame 0x20 -> 0x28 (Q1609).
2026-11-25c continue-lead-2 CleanarcadeUpdateOilDrumEntity anthropic/claude-opus-5-5 (base 9fb6f661):
  - inline ternary `y += animTimer < 200.0f ? 0.2f : -0.2f` with an f32 timer local (timer read once; re-read after the
    rand store; one read before the ternary; assignment in the test; `animTimer = timer = rand...`) -> 19-22: the inline
    ternary adds a cfe vreg, frame 0x28, and the $f0/$f2 swap.
  - no declared local, direct field compares + inline ternary (`y += ...` or `y = y + (...)`) -> 14: frame 0x20 kept
    (the ternary vreg takes the -4 word), only the $f0/$f2 swap; same with `f32 pad;` -> 19.
  - `f32 step` only for the step, set by if/else (`< 200.0f`, `200.0f > x`, `>= 200.0f` arms swapped), direct field
    compares -> 14 (14/14/14 shape 0/0/1); `y = y + step` -> 14; timer + step locals with if/else -> 19.
  - uopt -l 5 (M1 = step only via if/else): step var adjsave 1.5 (bbs 5,6,7) < timer reload uilod 2.0 and y reload 2.0,
    so the timer reload colours $f0 first, the y reload $f0, step $f2. Base: step var adjsave 2.5 (bbs 1,5,6,7) colours
    first $f0 (reg 24); the timer reload (bit 8) and the y reload (bit 26) interfere with it and take $f2 (reg 25).
  - variants.py scan --max 0 of the hack-free base (direct field compares, `f32 step` only for the ternary step;
    14 lines off: the $f0/$f2 swap), 33 variants -> best 14.
  - permuter 900 s (-j 2, hack-free weights) from that base, base score 80: 8 zero outputs, all re-creating the reuse
    (`step = animTimer;` before the `< 0.0f` test, or `(step = animTimer) < 0.0f`); outputs 18-46 reuse step for the
    y read or add value-named constant locals / alias copies. No hack-free improvement.
  - hidden-reuse check (director item 2026-11-25c): no other local or parameter takes a second value (entIndex never
    reassigned; step is the tagged site). None.
## Untried ideas
- none natural: the frame (0x20) has exactly one cfe word (-4 = 0x1c, untouched) above the v1 spill 0x18, so a timer
  local and a step local (or a timer local plus an inline ternary's vreg) never fit, and every single-role form loses
  the step variable's colouring priority.
## Evidence
0xca0c addiu sp,sp,-32; 0xca14 sw a0,32(sp) (u8 param home); 0xca60/0xca70 sw/lw v1,24(sp) (entity base across
arcadeRand); 0x1c never touched (step's home or a ternary vreg); timer in $f2 (0xca48 lwc1, 0xca4c c.lt.s, 0xca7c
lwc1, 0xca8c c.lt.s), step in $f0 (0xcaa4/0xcaa8 lwc1, 0xcab8 add.s), 97.0 in $f12, 110.0 in $f0, y reloads in $f2.
