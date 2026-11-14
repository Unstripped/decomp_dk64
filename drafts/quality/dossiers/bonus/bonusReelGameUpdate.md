# bonusReelGameUpdate (bonus, src/bonus/12A0.c)
## Sites
- bonus:8002570C:other:5c0f2a: FIXED.
  - `s32 startHits = 3` now feeds hitsLeft, counterShown and the divisor `(startHits - 1)`.
  - Target at 0x940: li 2; mtc1; cvt.s.w; div.s.
## Attempts
- round 18/26 (opus:low): plain, diagnose, permute (u8 loop var as divisor; value local / dead test).
- 2026-11-14 U, scored with variants.py try (full=):
  - startHits local: 0 (applied)
  - startHits with the `(f32)` cast: 0
  - startHits initialised on its declaration: 0
  - a `rounds = 2` local next to the use: 183
  - a sizeof(act) count: 183
## Evidence
- copy.diff
