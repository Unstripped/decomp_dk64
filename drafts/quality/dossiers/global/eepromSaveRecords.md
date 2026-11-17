# eepromSaveRecords (global, src/global/104F0.c)
## Sites
- 6b7e71 dead-if: `if (a) {}` keeps the narrowed CRC source index as a variable, supplies the extra 8-byte frame word, and puts the -8 web in s4 ahead of the `&D_807ECEA0` web in s7.
- 081ad7 dead-if: `if (D_807ECEA0) {}` supplies a post-bzero block that preserves the same s4/s7 colouring order.
- a1ca65 dead-if: the unsigned -64 use after calls keeps the arm-0 mask web uncoloured, preserving `li at,-64` at 0x1c64/0x1c88.
- 3c3a54 dead-if: the direct u16 `sector` read keeps the variable in s1 and its widening in s4 across the controller poll.

## Attempts
- Earlier attempts through HackeepromSaveRecords6: volatile controller poll fixed; dead `offset = 0` replaced by real `offset = sector << 3`; same-TU data, loop forms, width changes, pointer/size locals, arm rewrites, frame pads, permuter runs, and sibling-style reconstructions did not retire the four remaining sites. See the tracked dossier/history for the complete matrix.
- 2026-11-17 cleanup HackeepromSaveRecords7 anthropic/claude-opus-5-5: re-scored after `gContReadPending` became a shared scalar. Individual removals: 6b7e71 full/text 179/164; 081ad7 46/30; a1ca65 118/118; 3c3a54 117/125.
- 2026-11-17 cleanup HackeepromSaveRecords7: 6b7e71 removed with every CRC-height term as an inline has-ilod global expression plus `s32 pad` after `contReadPending` -> 48/32; s4/s7 still swap.
- 2026-11-17 cleanup HackeepromSaveRecords7: moved real `offset = sector << 3` to replace 081ad7's post-bzero block -> 138/123. Moved it after `osWritebackDCacheAll` with a1ca65 removed and 081ad7 retained -> 124/124.
- 2026-11-17 cleanup HackeepromSaveRecords7: refined `offset = sector`, used `offset << 3` in memcpy, and used `offset` as the post-poll write-loop initializer with 3c3a54 removed -> 36/36; sector is s0 rather than target s1 and the post-poll narrowing reads s0.
- 2026-11-17 cleanup HackeepromSaveRecords7: hack-free reconstruction combining inline has-ilod CRC-height reads, frame pad, refined offset, and offset loop init -> 156/149/8.

## Untried ideas
- 6b7e71: a target-semantic second use of `a` that still emits the target's independent second `multu`; all known `b`-from-`a` forms change that multiply.
- 081ad7: a real post-bzero control-flow/store block other than the position-sensitive write-start offset redefinition.
- a1ca65: a natural post-call computation that genuinely uses an unsigned 0x3f alignment mask while still reducing to the target's two `sector << 3` operations.
- 3c3a54: a real post-poll direct use of u16 `sector` that preserves the target's late `andi s2,s1,0xffff`; the natural refined-offset role gets close but changes the source register.

## Evidence
- Target frame is 4216; `contReadPending` home is 92(sp), `workingData`/`savedData` are sp+2144/sp+96.
- 0x1b28/0x1b38: target `&D_807ECEA0` is s7 and -8 is s4. Removal of either 6b7e71 or 081ad7 reverses them.
- 0x1c64/0x1c88: target reloads unsigned -64 through `at`; removing a1ca65 colours that mask web.
- 0x1db0/0x1db4: target separately executes the two `sector << 3` operations for memcpy addresses/size.
- 0x1dc8: target widens sector with `move s4,s1`; after the poll the write-loop init narrows with `andi s2,s1,0xffff`.
