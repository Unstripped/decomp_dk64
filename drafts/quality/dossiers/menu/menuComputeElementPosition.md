# menuComputeElementPosition (menu, src/menu/3E10.c)
## Sites
- `menu:800317E8:other:fa9d5b` (other): `t = 0.0f;` placed mid-body and read only by `if (t != f)`.
  - The target holds the zero in $f16: `mtc1 zero,$f16` right after the sqrtf call.
  - It compares zero-first: `c.eq.s $f16,$f2`.
  - It reuses $f16 for `t < 0.0f` (twice) and `t = 0.0f` (`mov.s $f0,$f16`).
  - **Removed.**
## Attempts
2026-11-14 PolishMenu3E10Names2 (tagger), claude-opus-5-5:high. All fdiff 1:
- `if (f != 0.0f)`, with and without the t store;
- `if (state->scroll != 0.0f)`.

2026-11-14 HackmenuComputeElementPosition, claude-opus-5-5. Scores from `variants.py try`:
- `0.0f != f`: full=1. Only `c.eq.s $f2,$f16` differs: the literal is canonicalised as the second operand.
- `f != 0.0f`: full=1, same difference.
- `f != 0` and `if (f)`: full=30.
- `0.0 != f`: full=44.
- `f > 0.0f`: full=2.
- `f32 t = 0.0f;` as the declaration initialiser, with `if (t != f)`: full=0, fdiff OK. **This is the fix.**
## Untried ideas
- None needed.
## Evidence
- The scroll test compares the zero register first (`c.eq.s $f16,$f2`). Literal compares are always emitted constant-second.
- So the original compared a variable holding zero, which a zero-initialised local reproduces. This matches Q0623, where a float constant is held in a reused local instead of a literal compare.
