# modelEmittersUpdate (global, src/global/68EA0.c)
## Sites
- global:8066466C:dead-store:de559d `dx = gModelEmitters[i].modelId;`: kills dx after the sum, so the sum gets its own candidate ($f14). Without it: $f6/$f8, 3 r.
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
## Untried ideas
- none at C level known: something must redefine dz/dx/dy (or make sum's def unpropagatable) between the sum and the compare, and the target has no such real use
