# modelApplyMapOverrideValue (global, src/global/36880.c)
## Sites
- global:80632F20:other:4997d7 other: REMOVED. `n = 5` kept the bound in v0 (`li v0,5` at 0x13a8, `slt at,v1,v0` at 0x13c0).
## Attempts
- rounds 1-37: see history (35 events; literal bound unrolls; permute best=0 only restores n = 5).
- 2026-11-14 U HackBoundLocalSizeofB opus:high (variants.py try full=):
  - `count = sizeof(D_80747D30) / sizeof(D_80747D30[0])` with the extern sized [5]: 0 (applied; s16 also 0)
  - inline sizeof: 61
## Untried ideas
- none: site removed.
## Evidence
- D_80747D30: 5 six-byte {map, id, val} triples, 0x80747D30-0x80747D4D, then 2 zero bytes of padding before D_80747D50.
