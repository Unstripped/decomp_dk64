# arcadeDrawStage3Background (arcade, src/arcade/0.c)
## Sites
- arcade:800275E8:other:1489cd (kept): the `(s32)` end pointer keeps `addiu s1,s0,84` (end derived from the walker, 0x3884).
## Attempts
- 2026-11-14 opus:high (full=):
  - sized extern [21] with sizeof bound: 18; for walker: 20
  - index loops: 21-22
  - end local in the pad slot: 18-20
## Evidence
- D_8004A7C8: 21 x 4 bytes, next label D_8004A81C.
