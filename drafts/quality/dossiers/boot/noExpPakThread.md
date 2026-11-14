# noExpPakThread (boot, src/boot/1630.c)

## Sites
- 880d3e: dead `x = 0;` after the 64-wide copy loop. KEPT.
  - Without a later definition of the column counter, uopt unrolls the loop by 4.
  - The target's loop is scalar (byte offset in v0, `slti at,v0,128`).

## Attempts
- 2026-11-14 U HacknoExpPakThread: loop-shape, pointer, width and order variants all fail (33-69 lines).
  - Reusing the later vsync `count` as the column counter: 10 lines, stack slot only. It is a steer, so not applied.

## Untried ideas
- None natural.

## Evidence
- Target 0x16c-0x184: `addu t1,a0,v0; lh; addiu v0,2; slti at,v0,128; addiu v1,2; bnez; sh t2,254(v1)`.
