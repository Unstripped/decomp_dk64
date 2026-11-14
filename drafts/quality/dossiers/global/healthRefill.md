# healthRefill (global, src/global/10D2D0.c)

## Sites
- **global:80709464:other:31f258: FIXED.**
  - `stats = &gPlayerInventoryTable[playerIndex]; stats->health = stats->melons * healthGetPerMelon(); stats->healthDelta = 0;`

## Attempts
**2026-11-14 U Hack10D2D0HealthStats.** 108-body grid plus 11 more:

| Form | Mismatches |
|---|---|
| any `perMelon` local, either operand order | 1 (`multu t9,v0` vs `v0,t9`; uopt canonicalises commutative operands) |
| sibling `limit = melons * limit` idiom | 2-7 |
| call folded into the multiply, delta cleared before | 26 |
| call folded into the multiply, delta cleared after | 0 (kept) |

## Untried ideas
- none

## Evidence
**Target 0xe94-0xee0:**
- The call comes first.
- Then the stats address from the reloaded playerIndex (lbu 27(sp)).
- Then `lbu melons`, `sb zero 765`, `multu v0,t9`, `sb 763`.
