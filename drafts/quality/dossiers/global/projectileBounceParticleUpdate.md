# projectileBounceParticleUpdate (global, src/global/936B0.c)

## Sites
global:806919E0:other:9121f0 other: line 1172 `dx = dx * dx; // FAKE: dx/dy reused as the running sum ...` in the
`unkEC == 0` camera-distance test. Steers ugen's block-local FP registers: one variable {dx, dx², sum} in $f0 and
one {dy, dz} in $f2 (target 0x35cc-0x3604). Register-only reuse: neither value ever touches its home (dx/dy homes are
never stored; the only FP homes in the frame are scale at 100(sp) and the spill at 72(sp)), so the own-home ORIG rule
does not apply and the tag stays.

## Attempts
2026-11-14 PolishGlobal936B0Names opus:high: dz local (block or function scope), inline sum: 35 rows (frame +8, reordered sum).
2026-11-15 HackprojectileBounceParticleUpdate2 anthropic/claude-opus-5-5:high: diagnose (variants.py try, deadsweep score):
- frame census: total named locals <= 7 keeps the 120 frame, 8 gives 128 at every declaration position of dx/dy/dz
  (function scope before/after each outer local, block scope). Dropping `radius` (use `radiusPick` directly in both
  calls) is codegen-neutral except scale's home 100 -> 104 (3 rows), so `radius` is real.
- `radius = state->param != 0 ? 200U : 60U` without radiusPick: 57-71 rows (radiusPick is real).
- three distinct deltas + inline sum, any order (`dz*dz + (dy*dy + dx*dx)`, `dy*dy + dx*dx + dz*dz`), radius dropped: 33-40 text.
- distinct dist sum var: `dist = dx*dx; dist = dy*dy + dist; dist = dz*dz + dist` (g6/g7) and `+=` (c3): uopt
  forward-substitutes the whole chain into one expression: 35-42 rows.
- dx, dy locals + inline z square (t1/t2): 30-37.
- all-inline squares into one `dist` local (f2b/h3/h4): 8 rows (dist in $f0 right, but the deltas are ring temps
  $f2/$f12/$f14, target $f0/$f2/$f2).
- symmetric scratch `d` + `dist` (c1/e5/e6/n1-n3, incl. `dist = 0.0f` start): 12 rows (d first-appears, takes $f0; dist $f2).
- `dist = SQ(x)` + scratch d for y/z (ma/mb 18-variant matrix of `+=`/`d*d + dist`/`dist + d*d`): 2-4 rows (dx temp
  $f12 instead of $f0); still a d reuse, no gain.
- dx self-squared in place but separate dy, dz (p2, `dx = dx*dx; ... dz = ...`): dz takes $f12 not dy's $f2 and is
  scheduled early: 8 rows. So {dy, dz} must be one variable and {dx, sum} one variable; both are reuses.
- 3-iteration loop over `(&x)[i]`: not unrolled, 132 rows.
- permuter (900 s, -j 2, hack-free weights) from the natural three-local block form: see ledger.

## Untried ideas
- none natural left: the target needs exactly two block-local FP variables with the sum sharing the x-delta's
  register (Q0318 assign-back keeps the result in the variable's register).

## Evidence
target 0x35cc sub.s $f0 (dx); 0x35d8 sub.s $f2 (dy); 0x35dc mul.s $f0,$f0,$f0; 0x35e8 mul.s $f16,$f2,$f2;
0x35f0 sub.s $f2 (dz into dy's register); 0x3600 add.s $f0,$f16,$f0; 0x3604 add.s $f0,$f6,$f0; frame 0x78, scale home 100(sp).
