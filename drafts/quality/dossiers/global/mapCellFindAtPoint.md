# mapCellFindAtPoint (global, src/global/55B20.c)
## Sites
- 40ab27: the dead `if (id) {}` (kept).
- 16a986: `if (box && box) {}`, EXHAUSTED.
## Attempts (2026-11-14)

| form | text |
|---|---|
| removal | 55 |
| `box = &gMapCellBoxes[id]` or `gMapCellBoxes + id` | 68 |
| `MapCell *cell` snapshot | 55 |
| s32 id | 55 |
| for-loop form | 55 |

## Evidence
- Q0720: the permuter's zeros only wrap neighbouring statements in a `do {} while (0)`.
