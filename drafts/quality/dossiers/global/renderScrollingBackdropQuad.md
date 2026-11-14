# renderScrollingBackdropQuad (global, src/global/90D80.c)
## Sites
- `global:8068D264:dead-if:d6b2be`: `if (gFrameDelta == 0) {}`, a deadsweep steer. **Fixed** by writing the scroll update as a one-case switch (Q0523).
## Attempts
**Earlier rounds (low model):** remove, cond, classify, recipe, diagnose (uopt_trace), and permute. The permuter reached best=0 only through a dummy label.

**2026-11-14, Hack90D80HitCounter.** All with the dead test removed:

| form | score |
|---|---|
| plain removal | full=57 |
| variants scan | best 57 |
| `scrollStep` computed at its use | 387 |
| one function-level `f64 temp` | 82 |
| tile-size snapshot locals | 122 |
| `gFrameDelta / 2.0` | 57 |
| switch with block-scoped temps | 0, fdiff OK |
| switch with a function-level temp | 13 |
| switch without temps | 39 |

## Evidence
- The target keeps the address of D_8075022C in t1: `lui t1` at 0x12d4 and `addiu t1` at 0x12ec, early. The scroll update reuses it.
- The if/else spelling loses that early address web unless the dead read is there. The switch spelling keeps it.
