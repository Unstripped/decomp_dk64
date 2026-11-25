# mountedBarrelUpdate (global, src/global/936B0_projectile.c)

Was func_8068EF54; the earlier dossier lives at drafts/quality/dossiers/global/func_8068EF54.md (old name) and is
folded in here.

## Sites
- 7a3016: the dead `if (gFrameCounter && gFrameCounter) {}` in the map 0x5C glow block. REMOVED (2026-11-14). The block
  reads the counter once into `u32 frame`, which reproduces the target's v0 load and t3/t5 link reload.
- global:8068EF54:comma:fa33ae `ratio = (0, x > 0.0 ? x : 0.0)`: KEPT. The comma sends the ratio select through cfe's
  shared f64 ternary temp M-208 (the temp case 0x113's inner PICK_MAX also uses), raising M-208 to adjsave 4.67 so it colours
  before the udiv (frame-39)/30.0 (3.33): M-208 $f0 (0x7e4-0x7f0, 0x9ec-0x9f8), udiv $f2 (0x9dc), sparkScale $f2, lightAdd
  0.0f $f16 (0x920) which leaves the ugen FP ring (0x81c mul.d $f18).

## Attempts
- 2026-11-14 U Hackfunc_8068EF54: see the ledger for line counts per spelling.
- 2026-11-15 U HackprojectileSteerTowardTarget2 opus:high (uopt -l6, as1probe keep, variants.py try full=):
  - plain: 106
  - `0.0 < speedY`: 106
  - `<=` with swapped arms: 111; `!(>)`: 111
  - `(f64)` on the compare, an arm, or both: 106
  - int `0` literals: 148
  - block-local `f64 ratio`, initialised or assigned: 193
  - f32 clamp local: 159/184; f32 speedY snapshot: 205
  - clamp inside each effectSpawnActorBone call: 269
  - ratio declared at 7 other positions: 106-193
  - if/else with the zero arm first: 111
- 2026-11-16 U HackprojectileSteerTowardTarget3 opus:high (variants.py try/scan):
  - `(f64)(x > 0.0 ? x : 0.0)` whole-ternary cast: 106. cfe drops the identity CVT, so each arm still stores ratio.
  - `(f64)(0.0 < x ? ...)`: 106
  - f32 select arms (`0.0f` or int `0`) with the double compare: 113 (cvt.d.s after the select)
  - f64 speed snapshot local: 193
  - if/else on `0.0 < speedY`: 106
  - variants.py scan of the plain body: 58 variants, best 106
- 2026-11-17 U HackvehicleUpdateMotion9 anthropic/claude-opus-5-5 (uopt -l5 comma vs plain, variants.py try):
  - priority map: with the comma, M-208 (cand 86) carries the ratio select plus case 0x113's inner PICK_MAX (adjsave 4.67)
    and colours first -> $f0; udiv (cand 138, 3.33) -> $f2; f64 temp M-216 (cand 146) -> $f0; sparkScale M-156 (cand 150,
    2.2) -> $f2; lightAdd 0.0 const (cand 246) forbidden f0/f2/f12/f14 -> $f16. Plain: ratio (M-152) is assigned in each arm,
    M-208 keeps only case 0x113 (cand 138, 3.0) and loses to udiv (cand 135, 3.33 -> $f0): M-208 $f2, M-216 $f2,
    sparkScale $f12, 0.0 const $f2.
  - `0.0L` arm 106; unary `+(...)` 106; `register f64 ratio` 106; parenthesised 106; `ratio = speedY; ratio = ratio > 0.0 ?
    ratio : 0.0` 114.
- 2026-11-25 continue CleanmountedBarrelUpdate anthropic/claude-opus-5-5 (base 9d5aabb3; copy unchanged, fdiff 0; sweep 47
  checks 0 hits; uopt -l6 of the plain body re-confirms the 2026-11-17 map at this base):
  - lever: change cfe temp sharing inside case 0x113 so M-208 outranks udiv with the plain ratio select:
    if/else on `PICK_MAX(..) < 0.49` 119 (with the comma kept 207: the if/else changes case 0x113's own code, so case 0x113
    must stay the nested macro ternary), inverted `>=` arms 124, `PICK_MIN(0.49, PICK_MAX(..))` 113, outer
    `frame < 70.0f ? PICK_MIN(..) : 0.5f` (and `0.5`) 134.
  - value-use probes of the select: void-context `c ? (ratio = a) : (ratio = b)` 106 (the temp value is discarded, same as
    plain), `ratio = (ratio = speedY) > 0.0 ? ratio : 0.0` 114.
  - uncapped variants scan of the plain body (all recipes, 71 variants): best 106.

## Untried ideas
- route the ratio select through the shared f64 ternary temp without the comma: a value use of the select that emits no
  code (every assignment form, cast, unary plus, long-double arm, void-context arm assignment is assigned arm by arm or
  discarded); or lower udiv (cand 135) below 3.0 with case 0x113's code unchanged (its nested macro ternary is fixed by the
  re-evaluated inner select at 0xa10).

## Evidence
- Target glow block: `lui v0,%hi(gFrameCounter); lw v0; subu t1,v0,t5`.
- Target ratio select 0x7d8-0x7f0: `c.lt.d $f12,$f2; bc1fl; mov.d $f0,$f12; b; mov.d $f0,$f2`, then per-arm
  `div.d $f8,$f0,$f6` (0x80c) / `div.d $f6,$f0,$f4` (0x854) with separate rodata copies of 150.0/0.12/0.3 (.rodata 0x10-0x38):
  the scale expression is written twice in the source, the select once before the `& 1` branch.
- Target case 0x113 0x994-0xa38: inner select into $f0 (0x9e8-0x9f8), compare with 0.49 (0xa00), inner select re-evaluated
  in the true arm (0xa10-0xa30, cvt.s.d $f2): the PICK_MIN(PICK_MAX(..)) double evaluation is real code.
- Target spawn arms:
  - 0x81c `mul.d f18,f8,f10`, then 0x820 `ldc1 f8` (0.3)
  - 0x864 `mul.d f10,f6,f8`, then 0x868 `ldc1 f6`
- Plain spawn arms: `mul.d f16` with `ldc1 f6` at 0x814, i.e. f16 is in the ring.
- ugen with the hack: `li.s f16,0.0` for the lightAdd 0.0f arguments; plain gives `li.s f2,0.0`.
- sparkScale is $f2 in the target (0x9b0 mtc1 $f2, 0xa24/0xa30 cvt.s.d $f2); plain gives $f12.
