# mtxIdentityF (global, src/global/110F00.c)
## Sites
- global:8070CCC4:dead-if:a4d7fc: REMOVED. The two FP constant webs are coloured in creation order: the 1.0f web needs to be first, to take $f0.
## Attempts
- rounds 8/26 (opus:low): remove/cond/classify/permute (the permuter only re-spells the dead test).
- 2026-11-14 U HackmtxIdentityF, scored with variants.py try (full=):
  - old store order (zeros, then diagonal) with these changes: 18 each (register names only)
    - declarations swapped, assignments swapped, initialisers, literals, a chain, a diagonal loop
  - guMtxIdentF-style nested i/j loop: 32
  - row-major: 14
  - column-major: 0 (with or without the one/zero locals)
  - diagonal first: 0
## Evidence
- leaf
- mtc1 zero,$f2 / lui+mtc1 $f0 = 1.0
- 12 zero stores (column order without the diagonal), then 4 diagonal stores (0xac0-0xb00)
