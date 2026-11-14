# playerWeaponCalculateTrajectory4 (global, src/global/F56F0.c)
## Sites
- global:806F1858:other:3ee789 other (kept): `angle = 4U`; same candidate-order steer as Trajectory7.
  - Target: `lbu v1,0x8e`, `sltiu at,v1,4` at 0xe80, table value `lhu v0` at 0xe9c.
## Attempts
- rounds 3-24: see history.
- 2026-11-14 U HackBoundLocalSizeofB opus:high (variants.py try full=):
  - `angle = sizeof(D_80752F30) / sizeof(D_80752F30[0])` with the extern sized [4]: 0 (not applied: the reuse of angle remains)
  - count local (u16/u32, before/after index): 9
  - literal: 9; inline sizeof: 9; declaration swap: 9
  - table pointer: 9; early return with a block-scoped angle: 9
  - s16 index: 51; no `index >= 0` test: 14
  - variants scan on the literal: 9
## Untried ideas
- Lead decision: accept `angle = ARRAY_COUNT(D_80752F30)` (one temp, two roles, Q0214) as natural, or keep the tag.
## Evidence
- D_80752F30: exactly 4 shorts, 0x80752F30-0x80752F37 (last 0xFA24); next label D_80752F38.
