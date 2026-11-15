# arcadeDrawStage4Background (arcade, src/arcade/0.c)
## Sites
arcade:80027A38:other:6c82de (was 2d946b) other: `step = 1` constant local; uopt keeps it a vreg, so `x += step * 0x20` / `i += step` hide the increments from EQ_INEQ: x exits stay `slti at,s3,K; bnezl` (0x3b54, 0x3b80, 0x3ca4, 0x3d10), i exits `slti at,s0,27; bnez; nop` (0x3bd8) and `slti at,s0,28; bnezl` (0x3ce4).
arcade:80027A38:noop-arith:2f10ba (was 7cf1c7) noop-arith: `(y ^ 0) != 0x87` gives uneq{135}{uxor} so the inner exit is `bnel s2,s0` at 0x3e34 (s2 = 135 hoisted at 0x3de0, s0 = y); plain y gives uneq{y}{135} -> `bnel s0,s2`.
arcade:80027A38:other:35daef (`one = 1`) REMOVED.
## Attempts
2026-11-14 HackarcadeDrawStage4Background HackarcadeDrawStage4Background anthropic/claude-opus-5-5:high: frame-slot budget -> fixed `one`: frame 0x78 = two 4-byte locals declared before glist (0x6c(sp)); the second is a real inner-loop `y`; single `step = 1` drives both x (`* 0x20`) and i increments; all loops as `for`; `i * 0x20 + 0xC0`. fdiff OK, uninit 0, fake 3 -> 2.
2026-11-14 same: ^0 with separate y: plain/for/while/do-while, const-first, >, >=, step-scaled decrement, decl orders, y widths u32/s16/u16/s8/u8, copy local, (u32) cast, 0x87U, subtract-compare, negate, break forms, LFTR index forms (unrolled, 58+): all `bnel s0,s2` or worse.
2026-11-14 same: literal steps with y: x literal text=6, i literal text=5, both text=11.
## Untried ideas
- An isop left operand that ugen folds away other than `^ 0` arising naturally (e.g. a field/array read uopt CSEs to the register) for the inner exit. (source: Q0474/Q0488 operand-order levers)
- A data-derived step (sizeof idiom, Q0780) if a table length or texture stride ever proves 1 or 0x20.
## Evidence
Frame: `addiu sp,sp,-120`; glist home 0x6c(sp) (sw t7 at 0x3ae8, lw t9 at 0x3e54); declaring a sixth scalar gives -0x80; any declaration order with exactly two scalars before glist keeps 0x6c.
Literal-step EQ_INEQ rewrites only loops whose bound gets a callee-saved register (0x3b80 li s0,0x440; 0x3ca4 li s0,0x420; 0x3bd8 li at,27; 0x3ce4 li s1,28); loops at 0x3b54 and 0x3d10 stay slti even with literal steps.
Inner exit: target `bnel s2,s0` at 0x3e34, s2 = 135 (li at 0x3de0), s0 = y (li 159 at 0x3df0, addiu -8 at 0x3e30).
