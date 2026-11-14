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
## Untried ideas
- a uopt -l 6 comparison of the sum web's candidate bit with and without the kill
