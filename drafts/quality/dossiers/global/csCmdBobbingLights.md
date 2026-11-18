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

- 2026-11-17 CleancsCmdStepSequenceProgress (cleanup session 2026-11-17f), strength-3 attempt:
  - Mechanism corrected by `as1probe ucode --cfe` (11BC10 rule: a right operand holding a subscript or explicit `*` load goes first only while the statement's ucode stack is empty):
    - `t * (p[1].y - p[0].y) + p[0].y` (p local or direct `gMinecartTrackPoints[1][k]`, sn local or call inline): the outer addend `p[0].y` is emitted first (`ilod; cvt f64 f32` before the blend), then the product in source order (t, p1, p0, sub). The mul.d is already right; uopt numbers `ucvt p0` before the umpy and orders the commutative uadd {cvt p0}{product}: `add.d $f10,$f6,$f4` against the target's `add.d $f10,$f4,$f6` (0x8F0), and lights 2/3 follow with a rotated FP ring. That is the whole 18.
    - `p[0].y + t * (p[1].y - p[0].y)`: the product goes first on the empty stack, so its right operand dy goes first (`p0; p1; swp; sub; cvt` before t): the ring rotates from 0x8C4 (cvt.d.s $f10 for $f4): 18.
    - So the target ucode needs all three point reads free of subscripts and `*`, and their offsets folded from one base (`lwc1 4(s0)`, `lwc1 16(s0)`).
  - Direct element reads + call inline (68EA0 lever), no p or sn local: 18 (only the outer add.d order above). Addend-first form: 18.
  - Per-point pointer locals `lo = &gMinecartTrackPoints[1][k]; hi = &gMinecartTrackPoints[1][k + 1];` (or `= G[1] + k`, either assignment order) with `(sn * 0.5 + 0.5) * (hi->y - lo->y) + lo->y` and direct `gMinecartTrackPoints[1][k].x/.z` in lightAdd: 11. Every FP register and the add.d/mul.d order now match; the residue is the element addresses not folded (Q0874): `addiu v0,s0,12; lwc1 $f10,4(v0)` for `lwc1 $f10,16(s0)` (0x8D8), lights 2/3 `addiu v1,s0,24; addiu v0,s0,36` (and 48/60). `hi = lo + 1`: 53; `p = G[1]; lo = &p[k]; hi = &p[k+1]`: 51; lightAdd through `lo->x`: 89.
  - Value locals after a blend local: `t = mathSinF(..) * 0.5 + 0.5` (f64), then `y1`/`y0` f32 locals: 33-36 (y1 becomes a coloured variable, $f12 for the ring's $f10); y0 local + direct p1 read: 18; struct copies `TargetVec3f lo = G[1][k]`: 153.
  - Kept form with `p = gMinecartTrackPoints[1]` only before each lerp and direct `gMinecartTrackPoints[1][k].x/.z` reads in lightAdd: 51, so the six `p =` reloads are load-bearing (one pointer local for every access).
  - `variants.py scan` of the direct-read/inline-call body (18) and of the pointer-local body (11): no zero.
  - Block-scoped `TargetVec3f *lo = &G[1][k], *hi = &G[1][k + 1];` per light: 11 (same unfolded addresses); block-scoped `lo = G[1] + k` with `(lo + 1)->y`: 53.
  - Hack-free-weights permuter 900 s -j 2 from the direct-read/inline-call body (variants 18), baseline 125: best 100 (variants 13), 3 outputs, all mixing per-light forms: one light written addend first fixes its add.d order but rotates the FP ring by three from 0x8C4 (cvt.d.s $f10 for $f4), the other lights keep `add.d $f6,$f18,$f8` (0x990). No zero. nohit.
- 2026-11-18 CleancsCmdCameraVectorTargetUpdateb anthropic/claude-opus-5-5 (cleanup session 2026-11-18):
  - Two-statement lerp with f64 locals per light: `t = sn * 0.5 + 0.5` (or `t = mathSinF(..) * 0.5 + 0.5`, with p loaded
    before or after t), then `rise = t * (p[k + 1].y - p[k].y)` and `fy = rise + p[k].y` or `fy = p[k].y + rise`: 38 each.
    - The instruction order now matches 0x8c4-0x8f0: cvt sn, mul.d, lwc1 p0/p1, sub.s, add.d t, cvt dy, cvt p0, mul.d, add.d.
    - t and rise become coloured variables, so rise takes $f2 and p0 takes $f12 (the target has $f2).
    - Both commutative ops flip: `mul.d $f2,$f8,$f18` (dy * t) for the target `mul.d $f4,$f8,$f18` at 0x8ec, and
      `add.d $f6,$f4,$f2` (p0 + rise) for `add.d $f10,$f4,$f6` at 0x8f0.
    - A local operand is ordered by its own load in the statement, not by the earlier umpy. The operand-order lever needs
      inline expressions, not locals.
  - sweep at the base: 0 hits (plain, recipe).

## Untried ideas
- A spelling that reads the three y values without a subscript or `*` and still folds their offsets into one base: only `(base + k)->y` is known. A file-local six-point view (`tl->p3.y`) would fold too, but it is a view.
- The struct-pair view (`{TargetVec3f lo, hi;}`) still needs `(pair + 1)` or a pair pointer variable per light (addiu shape, as for lo/hi).
## Evidence
- Target 0x8C4 cvt.d.s $f4,$f0 / 0x8CC mul.d $f6,$f4,$f20 / 0x8E0 add.d $f8,$f6,$f20: the blend is allocated first.
- 0x8D8 lwc1 $f10,16(s0) / 0x8DC sub.s $f16 / 0x8E4 cvt.d.s $f18: dy is allocated second.
- 0x8EC mul.d $f4,$f8,$f18: blend × dy. 0x8F0 add.d $f10,$f4,$f6: product + p0.
- uopt isop order in the matching build: ucvt sn(26), umpy(27), uadd t(28), uilod p1(29), uilod p0(30), usub, ucvt, umpy{140}{1179}(33), ucvt p0(34), uadd{64}{731}(35).
