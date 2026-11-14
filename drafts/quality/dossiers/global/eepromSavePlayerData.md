# eepromSavePlayerData (global, src/global/104F0.c)

## Sites
- 79c76c: dead `if (value && value) {}`. REMOVED.
  - It added a block before the outer loop, so the `i` counter coloured after `entry` (target: i in s8, entry in s7).
  - The plain `for` loops add the same pre-test blocks (Q0523).

## Attempts
- 2026-11-14 U HackeepromSavePlayerData:
  - All three loops as for loops: fdiff 0 (kept).
  - Only the j loop as a for: fdiff 0.
  - `i = 0` moved before the 0x10 store: 2 lines (move scheduled before the jal; as1probe found no fix).
  - Outer-loop-only for/while: 11 lines. entry moved: 12. Declaration order: 11.

## Untried ideas
- None.

## Evidence
- Target: `move s7,s2` (entry) at the gfxSetupFrameViewports return; `move s8,zero` (i) after the 0x10 call.
