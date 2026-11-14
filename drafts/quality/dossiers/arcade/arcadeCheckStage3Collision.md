# arcadeCheckStage3Collision (arcade, src/arcade/0.c)

## Sites
- 2607c6: `(s32)` cast on the end pointer. REMOVED.
  - Both scans are now index loops over D_8004BC88 ([0..3) and [3..6)).
  - The D_8004BCAC split label is retired.

## Evidence
- Raw words equal except the LO16 addends at 0x618c and 0x6208 (0x24 on D_8004BC88 vs 0 on D_8004BCAC).
