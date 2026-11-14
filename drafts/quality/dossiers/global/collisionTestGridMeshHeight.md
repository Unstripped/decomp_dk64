# collisionTestGridMeshHeight (global, src/global/6AD90.c)

## Sites
- 69efd5: dead `if (floorY && floorY) {}`. REMOVED.
  - `hit = 1` now sits after the D_807F94AF block, right before the bestY update.

## Attempts
- 2026-11-14 U HackcollisionTestGridMeshHeight: fixed. See the ledger for line counts.

## Evidence
- In the target, hit is stored from s8 at 0x9f(sp).
  - With `hit = 1` at the top of the arm, it is stored via `li t9,1` (24 lines).
