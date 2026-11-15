# playerTurnByStickX

## Sites
| key | site | what it does |
|---|---|---|
| cbe8d1 | trailing `if (turn > 1.0f) {}` | keeps the 4096 sub.s (0x1a64) and the 400 compare (0x1a74) alive (Q0200) |
| 3617c0 | `if (delta && delta) {}` | regalloc steer (Q0722) |
| 72ccc1 | triple `!gCurrentActor` test | regalloc steer (Q0722) |
| 149c00 | `if (delta) {}` | yaw/delta register order: v1/a0 at 0x1a08/0x1a1c (Q0722) |

The `aa1df8` `if (1) {}` lines are exhausted, not assigned here.

## Attempts
- **2026-11-14, HackE4090InputA, high:**
  - Clamp spellings without cbe8d1 (plain, ternary, `>=`, MIN order): full=11. Only the 10-word chain 0x1a5c-0x1a80 is missing.
  - All 15 removal subsets were measured:

    | removed | full |
    |---|---|
    | 149c00 | 6 |
    | 3617c0 | 9 |
    | 3617c0 + cbe8d1 | 11 |
    | 3617c0 + 149c00 | 12 |
    | 72ccc1 | 16 |
    | cbe8d1 | 32 |
    | all four | 30 |

  - Scans on the 149c00-free and 3617c0-free bodies found nothing lower.

## Untried ideas
- An original statement that uses the clamped turn and that uopt deletes after branch formation, for example a compiled-out debug print `if (turn ...) PRINTF(...)`. That is speculative; any such source would read as an empty if.

## Evidence
- The clamped turn is dead in the target: both arms of the 400 compare rejoin at 0x1a88.
- The stick term (`lb t2,46(a1)`, `multu`, `div` by 400 at 0x1aa8) never reads turn.
