# csCmdCameraVectorTargetUpdate (global, src/global/478F0.c)

## Sites
- global:806496B0:dead-if:a7ed7a (kept): `if (&xs == 0 || &px == 0 || &zo == 0 || &py == 0 || &xo == 0 || &pz == 0) {}`.
  - Address-taking keeps the six floats in declaration-order stack homes: xs 0xa8, px 0xa4, zo 0xa0, py 0x9c, xo 0x98, pz 0x94 (frame 0xd8).
  - Removed, uopt colours them: frame 0xe0, 179 lines.

## Attempts
- 2026-11-09..12, Clean478F0 / ReReview / Rev16K / Rev17L / CleanGlobal478F0 (opus low/xhigh): remove/cond/classify (class 2), Vec3 struct layouts, permuter (best adds `f32 *new_var = &px`). nohit.
- 2026-11-16 HackcsCmdStepSequenceProgress3 anthropic/claude-opus-5-5:high:
  - Local arrays `f32 x[2], y[2], z[2]` ([0] = px/py/pz, [1] = xs/zo/xo) in place of the address test: frame 0xd8 and all six homes match; 47 lines.
    - `f32 v[3][2]`, `*x` for `x[0]`, all 1680 orderings of the setup statements, operand swaps of ex/ez, a `(f64)` cast: 47 or worse.
    - as1probe ucode: uopt output equals the base except three `add` operand orders (ex at 0x6d68, ez, `y[1] = sin * 100.0 + y[0]`).
    - Cause: cfe emits the subscripted right operand of `+` first (Q0860 holds for `+`), also when the left product reads `(*p).f`, `p[0].f`, `(&p->unk220)[0]` or `x[1]`.
  - Local structs (`{f32 pos, start;}` per axis, `pr[3]`, one 6-field struct): uopt scalar-replaces them, 179 like the removal.
  - `cb` local (38 without) and `flag` (55 with `c == 0` in the loop) are load-bearing; ordinary named locals.

## Untried ideas
- An array spelling whose `+` operands are emitted in source order (the left product would need to be a subscript itself).
- A natural callee that took the floats' addresses in the original (none in the target asm).

## Evidence
- Homes: swc1 148/164/156(sp) 0x6d24-0x6d30 (pz px py), xs 168 0x6e18, xo 152 0x6e20, zo 160 0x6e50; `lw a2,164(sp)`/`lw a3,156(sp)` pass px/py at 0x6edc.
- 0x6d34 lwc1 $f18,544(s0); 0x6d3c lwc1 $f6,164(sp); 0x6d68 add.d $f16,$f8,$f10 (product first); pz reload 0x6d6c lwc1 $f10,148(sp).
