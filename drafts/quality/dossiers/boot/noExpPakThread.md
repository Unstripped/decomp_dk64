# noExpPakThread (boot, src/boot/1630.c)

## Sites
- 880d3e: dead `x = 0;` after the 64-wide copy loop. FIXED (2026-11-18c, director ruling).
  - Without a later definition of the column counter, uopt unrolls the loop by 4.
  - The target's loop is scalar (byte offset in v0, `slti at,v0,128`).
  - The definition must sit in the loop exit's extended basic block: any block reached through single-predecessor edges
    (outer latch, code after the nest, the `osTvType == 0` hang arm, the vsync counter init). The only definition the
    target executes there is the vsync counter init `move s0,zero` at 0x204.
  - Fix: the column counter `x` is also the vsync frame counter (`x = 0` at 0x204, `x++` at 0x224, reset at 0x268).
    `count` is deleted and `pad` becomes `pad[2]`, which keeps the 0x80 frame and `fb` at sp+0x5c. The director ruled
    this ordinary C (Q1224: consecutive counters, each reset at its loop start, no other role).

## Attempts
- 2026-11-14 U HacknoExpPakThread: loop-shape, pointer, width and order variants all fail (33-69 lines).
  - Reusing the later vsync `count` as the column counter: 10 lines, stack slot only. It is a steer, so not applied.
- 2026-11-17 U CleannoExpPakThread: 24 bodies scored with `variants.py try`; 16 of them traced with uopt `-l 5`.
  - Without a later definition, the inner loop at BB 6 gets `EQ_INEQ` and `UNROLLING 4 times`.
  - A later read of x (`count = x;`, `osViBlack(x)`, `if (x) {}`) does not stop them (68-103 lines).
  - A later definition stops both at every position in the exit's extended block: byte-identical object (fdiff 0).
    Tested positions: latch `x = y`, `x = 0` after the nest, `x++` after the nest, `x = 0` before `noExpPakDrawScreen()`,
    `x = 0` in the hang arm, `count = x = 0`, and x as the vsync counter with `count` left unused.
  - A definition before the nest (`x = 0;`) or inside the vsync `while (1)` (after its header merge) does not stop them (68).
  - Same-role reuse (Q1224) cannot apply: no later counted loop exists. The vsync wait rewritten as a counted
    `do { recv; x++; } while (x < delay.ticks[cur])` puts `x = 0` after the `while (1)` header merge: unrolled (79);
    the do-while alone with `count` scores 18 (s2/s3 swap). The clear loop sharing its `i` with the column loop is unrolled (66).
  - Also unrolled: `register s32 x` 68, `x != 64` 68, `x <= 63` 68, a dst row pointer 71, the increment-clause reset
    `for (x = 0, y = 0; y < 64; y++, x = 0) for (; x < 64; x++)` 35 (x is no longer known 0 at entry).
  - variants scan of the removal body: 39 variants, best 33 (`x` s8/s16); no zero.
  - Permuter (hack-free weights, -j 2, 900 s) from the removal body: base 1637, best 400, 949 outputs.
    - The best (output-400-1) adds `x = 5;` after the nest and passes x as the `osCreateMesgQueue` count.
    - That is the same later-definition lever. Transplanted it gives fdiff 0, but it is a constant-valued local
      reused for an unrelated quantity (steer), so it was not applied.
- 2026-11-19 U CleannoExpPakThreadb (anthropic/claude-opus-5-5): diagnose re-run on the current body, plus new forms.
  - uopt `-l 5` of the removal copy: `EQ_INEQ at BB 6` and `UNROLLING at BB 6 4 times to BB 27` (68 lines).
    With the store, only the clear loop (BB 2) unrolls. The sweep (remove/cond/recipe nohit) and the variants scan
    (39 variants, best 33 with `x` as s8/s16) give the same results as before.
  - Natural spellings that add no later def are all unrolled (EQ_INEQ + UNROLLING at the column loop):
    2D array views `((u16 (*)[320])0x80100000)[y + 60][x + 128] = ((s16 (*)[64])0x80280000)[63 - y][x]` 61,
    block-scope column local 68.
  - EQ_INEQ is not limited to unit stride: a byte-offset IV `x < 128; x += 2` is still EQ_INEQ + UNROLLING at BB 6 (75).
  - A bound held in a local initialised at its declaration, in pad's slot (`s32`/`s16`/`s8 width = 64`), is
    constant-propagated before EQ_INEQ: EQ_INEQ + UNROLLING at BB 7 (88). The Q0765/Q0257 bound-local lever does not apply here.
  - A live def `x = osTvType; if (x == 0)` stops both: the loop at 0x150-0x194 is identical. But x is coloured to `a3` for
    the osTvType load at 0x1d4 (target: temp `t8`), which shifts the temp ring (17 lines). It is also an unrelated-local reuse (steer).
  - After the director's ruling, applied x as the vsync counter with `count` deleted and `pad[2]`: fdiff 0, clint uninit 0,
    cwarn 0, sweep reports no sites. The FAKE count goes 1 -> 0.

## Untried ideas
- None left: the site is fixed.

## Evidence
- The only definition in the column loop's exit extended block that the target executes is `move s0,zero` at 0x204 (vsync count init).
- Target 0x16c-0x184: `addu t1,a0,v0; lh; addiu v0,2; slti at,v0,128; addiu v1,2; bnez; sh t2,254(v1)`.
- The clear loop at 0x118-0x140 is unrolled by 4 (`bne v0,a0`, a0 = 0x80125800): its `i` has no later definition.
- Reduced-TU scoring (`deadsweep score`, `variants.py try`) of the matching base gives full=1: one extra `nop`
  before the unreachable epilogue at 0x280. Here full=1 means a match; fdiff of the full copy gives exit 0.
