# collisionTestActorBoxFloor (global, src/global/6AD90.c)
## Sites
- global:8066A08C:dead-store:ff3fab `dy02 = 0.0;`: the dead-store kill described in ido-levers-revisit-7 (Coll entry). It stops uopt forwarding nz's expression into d. Target: d in $f0 at 0x41dc-0x41e4, spilled at 0x108(sp).
## Attempts
- CleanD5E10, Rev16G, Rev17L (opus:low): remove/cond/diagnose/permute.
- 2026-11-14 U, scored with variants.py try (full=):
  - plain removal: 11
  - d operand orders: 11-122
  - nx/ny/nz statement orders: 19-46+
  - casts all/none: 11
  - block-scoped temporaries: 20
  - d/nz inside the ny test: 305+
  - nz inlined into d: 12
  - variants scan of the removal: 11 at best
## Untried ideas
- an expression whose copy-forward exceeds uoptcopy's 10-variable-leaf limit (no natural spelling found)
