# raceInitSplinePoints (race, src/race/1770.c)
## Sites
- race:8002597C:other:45977d: FIXED.
  - The memcpy length is now written inline as `count * sizeof(TargetVec3f)`. uopt CSEs it into a spill temp at 44(sp), which is where the target keeps the length.
  - `src` is now a `TargetVec3f *`, the second memcpy source is `src + count`, and `next` holds tbl[2].
  - 0 casts left.
## Attempts
- rounds 16, 17, 22, 23 (opus:low) and HackraceApplyPositionOffset (opus:high): separate size/next locals (2, length home at 40), permutes.
- 2026-11-14 U, scored with variants.py try (full=):
  - named size local in a block scope or disjoint scopes: 2
  - inline `count * 12`: 9
  - inline `sizeof` with `next` declared after tbl: 0 (applied)
  - `TargetVec3f *src` with `src + count`: 0 (applied)
## Evidence
- copy.diff
