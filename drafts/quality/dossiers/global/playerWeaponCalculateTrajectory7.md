# playerWeaponCalculateTrajectory7 (global, src/global/F56F0.c)
## Sites
- global:806F1768:other:b7ba3b other (kept):
  - `angle = 7U` gives angle (the table value) an earlier candidate bit than index, so the value takes v0 and index v1.
  - The range check itself is folded to sltiu.
## Attempts
- rounds 3-24: see history (permute best=0 only by constant-in-angle forms).
- 2026-11-14 U HackBoundLocalSizeofB opus:high (variants.py try full=):
  - literal: 10
  - separate u16/u32 count local: 10
  - inline sizeof: 10
  - with a hypothetical `D_80752F20[7]`, `angle = sizeof(D_80752F20) / sizeof(D_80752F20[0])`: 0
## Untried ideas
- If the lead accepts the angle = sizeof reuse (Q0214) as natural, it applies here only once the table's 7-entry size is proven.
## Evidence
- D_80752F20 is 16 bytes: 0, F830, F448, EC78, E890, E890, F448, 0000.
- That is 7 entries plus 4-byte alignment padding, or 8 entries; the data cannot tell them apart.
