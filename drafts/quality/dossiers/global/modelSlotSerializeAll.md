# modelSlotSerializeAll (global, src/global/36880.c)
## Sites
- global:8063B8D8:dead-if:46a703: FIXED.
  - Both table passes now index `gCsVarsDirty[i]`.
  - The pointer walker p and the dead test are gone.
## Attempts
- rounds 4/9/16 (opus:low): diagnose, permute (re-added the test).
- 2026-11-14 U: 120-body variants grid.
  - both passes indexed: 0
  - any pointer walker: nonzero (s5 + move s1,s5)
## Evidence
- copy.diff
