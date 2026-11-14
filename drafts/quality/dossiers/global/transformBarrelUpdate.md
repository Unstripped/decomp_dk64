# transformBarrelUpdate (global, src/global/80150.c)
## Sites
- global:8067E784:other:da1976 other: REMOVED. `s16 entryCount = 8` kept the bound in a3 (`li a3,8` at 0x334c, `slt at,a1,a3` at 0x33f4).
- Other sites (516e63, a9a41f, 0f5fc9, 4925be, 2ba6be): not in this item, untouched.
## Attempts
- 2026-11-14 U HackBoundLocalSizeofB opus:high (variants.py try full=):
  - `s16 entryCount = sizeof(D_8074E7BC) / sizeof(D_8074E7BC[0])` with the extern sized [8]: 0 (applied; also with sizeof(TransformBarrelEntry))
  - inline sizeof: 11
## Untried ideas
- (other sites) see their own history.
## Evidence
- D_8074E7BC: 8 three-byte {map, listId, count} entries, 0x8074E7BC-0x8074E7D3; next label D_8074E7D4.
