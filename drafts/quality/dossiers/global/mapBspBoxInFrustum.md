# mapBspBoxInFrustum (global, src/global/2F550.c)
## Sites
- global:8062DBDC:dead-if:6bc043: REMOVED. The in1/in2/behind initialisations now sit after the inside-box `return 1`, right before the plane loop.
## Attempts
- rounds CleanD5E10/9/17/35 (opus:low): diagnose, classify, permute (dead-test moves only).
- 2026-11-14 U HackmapBspBoxInFrustum opus:high (variants.py try full=):
  - initialisations after the early return: 0 (applied)
  - chained or reversed initialisations: 5
  - guard removed alone: 11
  - 119 declaration orders: 11+
  - in1 && in2 forms: 11+
## Evidence
- The guard compensated for the zero webs' first appearance: the stores sat before the `return 1` test, ahead of the arg4 cvt candidates.
