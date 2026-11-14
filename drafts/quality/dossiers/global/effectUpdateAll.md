# effectUpdateAll (global, src/global/119370.c)
## Sites
global:80715270:dead-if:cc3d08 (`if (node2 && node2) {}` in the slot loop): REMOVED.
- The grid walk is now one nested condition instead of two early continues.
- The slot loop sits one block level deeper, and node2 keeps s1 over the slot address (Q0451).
## Attempts
- rounds 5/17/20/32 (opus:low, opus): removal (23 lines off); slots[i]/for rewrites (23); permutes only swap the steer.
- 2026-11-14 HackeffectCreateAtActorBone (opus), variants.py try (lines off):

  | variant | lines off |
  |---|---|
  | nested condition | 0 |
  | one-case switch | 15 |
  | merged continue | 23 |
  | && slot test | 23 |
  | block-scoped node2 | 23 |
  | node2 declared last | 23 |
  | node2 declared first | 27 |
  | named bound n | 33-37 |
  | slot pointer local | 39 |
  | slots snapshot | 40 |
  | age local | 76 |

## Untried ideas
none (fixed).
## Evidence
fdiff 0, objdump raw words equal (standin_119370.c).
