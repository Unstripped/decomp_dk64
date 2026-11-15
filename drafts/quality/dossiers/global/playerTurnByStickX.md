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
- **2026-11-15, HackplayerTurnByStickX2, opus-5-5:high (E4090 .data carve, Q0552):**
  - Stand-in `.scratch/HackplayerTurnByStickX2/carve_E4090.c` defines E4090's whole .data (0x80750FF0-0x80752C70, `gPlayerInputHandlers[107]` names this function), so its entry label is address-taken in as1.
  - Every single removal (aa1df8 x5, 3617c0, cbe8d1, 72ccc1, 149c00) and the four entry `if (1)` together give a `.text` byte-identical (md5 of `objdump -drz`) to the same removal in the plain copy. The function has no switch `jr`, so Q0552's false switch-to-entry edge cannot form. The carve is not a lever here. (All nine removed under the carve: still differs, .text size changes.)

    | removed (carve) | objdump diff lines |
    |---|---|
    | aa1df8, #2, #3, #4, 3617c0 (each) | 18 |
    | 149c00 | 12 |
    | 72ccc1 | 32 |
    | aa1df8#5 | 142 |
    | entry four `if (1)` | 34 |
    | cbe8d1 | .text shrinks (chain deleted) |


## Untried ideas
- An original statement that uses the clamped turn and that uopt deletes after branch formation, for example a compiled-out debug print `if (turn ...) PRINTF(...)`. That is speculative; any such source would read as an empty if.

## Evidence
- The clamped turn is dead in the target: both arms of the 400 compare rejoin at 0x1a88.
- The stick term (`lb t2,46(a1)`, `multu`, `div` by 400 at 0x1aa8) never reads turn.
