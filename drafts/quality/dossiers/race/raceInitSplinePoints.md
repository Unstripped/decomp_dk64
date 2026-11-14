# raceInitSplinePoints (race, src/race/1770.c)
## Sites
race:8002597C:other:45977d: kept; see Evidence.
## Attempts
2026-11-11/12 rounds 16, 17, 22, 23 (opus:low): plain, diagnose, as1probe, permute (see history).
2026-11-14 HackraceApplyPositionOffset opus:high: all 30 declaration positions of separate size/next locals (best 2: home 40), block-scoped next pointer (2), an s32 pad in every declaration position (5: frame grows), size as s32 (6), loop pointer assignment orders (6), tbl[2][i] indexing without next (193)
## Untried ideas
none recorded.
## Evidence
separate u32 size and RaceAPoint3f *next locals give identical code except the byte-length spill across the memcpy jal: sw/lw a2,40(sp) instead of 44(sp) at 0x2c4/0x2d4; the shared u32 slot puts the length home at 44. No declaration order of the two separate locals reaches 44
