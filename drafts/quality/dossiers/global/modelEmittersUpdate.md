# modelEmittersUpdate (global, src/global/68EA0.c)
## Sites
- none (2026-11-17 U3): global:8066466C:dead-store:de559d `dx = gModelEmitters[i].modelId;` removed. The body now has no delta locals:
  `distSq = SQ(eyeX - x) + SQ(eyeY - y) + SQ(eyeZ - z);` with a file-local `#define SQ(x) ((x) * (x))` (same as 12E800.c, 5E2F0.c).
## Attempts
- round 20 (opus): remove/cond/diagnose/permute (the permuter swapped in another dead store).
- 2026-11-14 U, scored with variants.py try (full=):
  - 192-body grid (declaration order, e pointer, f64 sum, modelId local, f literal, early continue): best 3
  - sum operand orders: 3-15
  - no sum local: 3
  - reusing dz: 2
- 2026-11-16d U2 (opus): uopt_trace -l 6 with/without the kill. Only difference: the compare operand. Kill: ucvt{1088} (sum var, cand 46);
  sum cand 35 -> reg 27 ($f14). No kill: copy propagation folds the uadd tree into the compare (ucvt{269}, cand 43); cand 35 still
  reg 27 but its store is dead; the sum goes to ugen temps $f6/$f8. No priority/split/colour change: the kill only stops copy propagation.
  Scored (full=): accumulating sum 4 forms 3; assignment in condition 3; nested if 3; (f64)sum 3; dx = dx*dx+dy*dy 7;
  dz *= dz... 10; dx = sum after the sum 0 (same dead-store steer).
- 2026-11-17 U3 (opus): fixed. The fix makes the sum's def unpropagatable. With the deltas written inline, the sum tree holds ilods, and uopt
  find_replacements does not copy-propagate such a tree (Q0510 has_ilod). distSq stays a var in $f14, and `cvt.d.s $f6,$f14` feeds c.lt.d.
  Only (X*X + Y*Y) + Z*Z matches (score 0). The other 11 inline orders and associations score 4-15. Rejected: in-place sum into dz/dx/dy
  2/6/8 (dz in place coalesces the sum into $f0); a single reused delta local 13-19; one delta inline 13-14; `register` sum 3.
## Evidence
- target 0x5a4 `add.s $f14,$f4,$f18`, 0x5a8 `cvt.d.s $f6,$f14`, 0x5ac `c.lt.d $f6,$f20`. There are no stores between the sum and the compare.
## Untried ideas
- none (site fixed)
