# modelFlagsApplyMapPairs (global, src/global/36880.c)
## Sites
- global:80632E10:other:71651f other: REMOVED. `n = 8` kept the bound in v1 (`li v1,8` at 0x12a8, `slt at,v0,v1` at 0x12bc).
## Attempts
- rounds 1-37: see history (plain/permute/diagnose nohit).
- 2026-11-14 U HackBoundLocalSizeofB opus:high (variants.py try full=):
  - `count = sizeof(D_80747D50) / sizeof(D_80747D50[0])` with the extern sized [8]: 0 (applied; also 0 with sizeof(ModelMapIdPair) or an s16 count)
  - for (i = 0; ...) with count: 5
  - inline sizeof: 50
## Untried ideas
- none: site removed.
## Evidence
- D_80747D50 (asm/global/data/14C9E0.data.s): 8 four-byte {map, id} pairs, 0x80747D50-0x80747D6F; next label gModelSlotCount.
