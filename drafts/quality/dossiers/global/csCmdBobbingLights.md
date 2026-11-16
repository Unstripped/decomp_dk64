# csCmdBobbingLights (global, src/global/478F0.c)
## Sites
- global:80643440:noop-arith:9d8298 / b4e5ff / 7aae48 (base, removed): `(0, (sn * 0.5 + 0.5))` comma on the blend factor.
  - It made cfe emit the blend t before dy, so uopt's umpy became {t}{cvt dy}.
  - That gives the target FP numbering: light 1 at 0x8C4-0x8F0 (cvt.d.s $f4, mul.d $f6, add.d $f8, sub.s $f16, cvt.d.s $f18, mul.d $f4,$f8,$f18); light 2 at 0x964+ (cvt.d.s $f8, mul.d $f18, ...).
- global:80643440:other:b584f0 (copy only): the `TRACK_PAIR_LERP_Y` macro reads its points as `((pt) + 1)->y` / `(pt)->y`.
  - This pointer spelling keeps cfe's source-order emission.
  - Tagged as one spelling steer (68EA0 tags the `(base + i)->` spelling the same way).
## Attempts
- 2026-11-09..14, Clean478F0 / Clean42630 / Rev16K / Rev17L / CleanGlobal478F0 / OwnerMinecartTrackPoints (opus low/xhigh/high).
  - Removing the comma, operand swaps, sn/2.0, (sn+1)*0.5, f64 sn, f64 casts, 0.5f, an f64 t temp, factor-first `t * dy`: 18+ lines each.
  - Permuter best=0 only with an embedded assignment, a self-assignment or a copy-temp index (hack swaps).
- 2026-11-15, HackcsCmdBobbingLights (opus):
  - uopt_trace comparison of the comma build and the comma-free build: the only isop difference is the order of `umpy{140}{1179}` against `umpy{1179}{140}`, plus its creation order.
  - Everything below scored 18 (ucvt dy emitted first): `p[k]` lerp spellings, factor first or last, f64/f32 t locals before or after p, y0 local, nop (global inline).
    - The call inlined into the blend gives the right umpy order but loads p before the call: 39.
    - y0/y1 or dy f32 locals: 32-42.
    - 3-iteration loop: 156 (not unrolled).
    - Per-light `p = gMinecartTrackPoints[1] + k`: 10-26 (addiu shape).
  - `t * ((p + k + 1)->y - (p + k)->y) + (p + k)->y` on all three lights: fdiff 0. Every block needs both reads as `->`; any single block in `p[k].` form costs 1-15 lines.
  - Kept as the macro `TRACK_PAIR_LERP_Y(pt, t)`, called with p, p + 2, p + 4: fdiff OK, 3 FAKE -> 1.
  - `variants.py scan` on the best arrow-free body (t * (p[b].y - p[a].y) + p[a].y): 22 variants, no zero.
  - sweep: 0 hits.
- 2026-11-15, HackcsCondDepositItem (opus high):
  - Two-point macro `LERP_Y(a, b, t) ((t) * ((b)->y - (a)->y) + (a)->y)` called with `&p[0], &p[1]` (and 2/3, 4/5): 18 lines, so cfe weighs `(&p[k])->y` like `p[k].y`.
  - The same macro called with `p, p + 1` / `p + 2, p + 3` / `p + 4, p + 5`: 0. It is the same `(p + k)->` pointer steer in another spelling, so it was not kept.
  - Struct-value macro on `p[k]`, float `LERP(p[k].y, p[k + 1].y, t)`: 18 each.
  - sweep: 0 hits.
- 2026-11-16 HackcsCmdStepSequenceProgress3 anthropic/claude-opus-5-5:high:
  - No p local, `gMinecartTrackPoints[1]` read directly at every use: the arrow macro on `gMinecartTrackPoints[1] + k` 18, `t * (G[1][k+1].y - G[1][k].y) + G[1][k].y` 18.
  - Mechanism (Q0860 extends to `+`): cfe emits a subscripted right operand of `+` before the left product, so every `p[k].y` form loads p0 first; `->` is not counted as a subscript, which is why the arrow form keeps source order.

## Untried ideas
- A hack-free spelling that keeps `p[k].y`. The cfe weight function that ranks the subscript form above the `->` form is still unexplained (a cfe source/ucode dump would settle it).
- A file-local pair struct view (`{TargetVec3f lo, hi;}`). It was avoided because a view is itself a cleanup cost.
## Evidence
- Target 0x8C4 cvt.d.s $f4,$f0 / 0x8CC mul.d $f6,$f4,$f20 / 0x8E0 add.d $f8,$f6,$f20: the blend is allocated first.
- 0x8D8 lwc1 $f10,16(s0) / 0x8DC sub.s $f16 / 0x8E4 cvt.d.s $f18: dy is allocated second.
- 0x8EC mul.d $f4,$f8,$f18: blend × dy. 0x8F0 add.d $f10,$f4,$f6: product + p0.
- uopt isop order in the matching build: ucvt sn(26), umpy(27), uadd t(28), uilod p1(29), uilod p0(30), usub, ucvt, umpy{140}{1179}(33), ucvt p0(34), uadd{64}{731}(35).
