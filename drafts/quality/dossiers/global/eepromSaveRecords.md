# eepromSaveRecords (global, src/global/104F0.c)
## Sites
- 6b7e71 dead-if: `if (a) {}` keeps the narrowed CRC source index `a` as a variable (v1: `mflo v1; andi t4,v1,0xffff; move v1,t4` at 0x1c08-0x1c10, ahead of b's `multu t5,t3` at 0x1c14), supplies the extra 8-byte frame word (4216 vs 4208), and leaves the -8 web in s4 / `&D_807ECEA0` in s7 (0x1b28/0x1b38).
- 081ad7 dead-if: `if (D_807ECEA0) {}` after bzero adds one block to the `&D_807ECEA0` candidate's range so the -8 constant wins the exact 2.6 adjsave tie (Q0900): s4 = -8, s7 = `&D_807ECEA0`.
- a1ca65 dead-if: the unsigned -64 use after the calls stretches the arm-0 unsigned mask web across calls so it stays uncoloured (`li at,-64` at 0x1c64/0x1c88).
- 3c3a54 dead-if (EXHAUSTED): the direct u16 `sector` read raises the variable (s1) above its widening (s4, `move s4,s1` at 0x1dc8, `slti at,s4,256` at 0x1e2c).

## Attempts
- Earlier attempts through HackeepromSaveRecords7: see drafts/quality/dossiers/global/eepromSaveRecords.md and `uv run tools/quality.py history eepromSaveRecords`.
- 2026-11-17 2026-11-17: cleanup HackeepromSaveRecords8 HackeepromSaveRecords8 anthropic/claude-opus-5-5:high: re-scored at 468537da: single removals 6b7e71 179/164, 081ad7 46/30, a1ca65 118/118, 3c3a54 117/125, all four 172/157; quality sweep 55 checks 0 hits.
- 2026-11-17 2026-11-17: cleanup HackeepromSaveRecords8: 6b7e71 removed + `s32 pad` after contReadPending = 173/158. On that base: b before a, `height * i`, `height * (i + 1)`, `&workingData[a]`, `workingData + a`, `*D_807ECEA0` for `D_807ECEA0[0]`: all 173; `u32 crc` temp or `u8 *data` pointer local: 177; the loop byte offset held in idx/sector 173 (179 without pad), in offset/j 68; variants scan best `i` s8/s16 67, `a` s32/u32 68 (both drop target narrowings).
- 2026-11-17 2026-11-17: cleanup HackeepromSaveRecords8: 6b7e71 removed, `height -= 4;` before the CRC call (kills height between a's def and its use) = 154: `a` stays the v1 variable computed ahead of b's multu exactly as 0x1bf4-0x1c1c, but len becomes `addiu v0,v0,-4; andi a1,v0,0xffff` (target `addiu a1,v0,-4; andi t8,a1,0xffff; move a1,t8` at 0x1bfc-0x1c04) and the s4/s7 tie is unchanged. `a = i * (height /= 8)` 179, `a = i * (height / 8); height /= 8;` 234.
- 2026-11-17 2026-11-17: cleanup HackeepromSaveRecords8: 6b7e71 permuter on the pad-corrected base (HACK_PASSES zeroed), 900 s: 3048 -> 195, only through `s32 *new_var = &height` for every CRC-loop height read (address-taken height blocks a's copy propagation) plus a new dead `if ((workingData && workingData) && workingData) {}` in arm 0; no natural form.
- 2026-11-17 2026-11-17: cleanup HackeepromSaveRecords8: 081ad7 removed: variants scan all 46; `sizeof(workingData)` for every 0x800 (memcpy, bzero, write-start size) 46; bzero/write-start size only 92; `*D_807ECEA0` spelling 46.
- 2026-11-17 2026-11-17: cleanup HackeepromSaveRecords8: a1ca65 removed: unsigned `~0x3FU` in the bzero expression 85 (the unsigned web is coloured s3, splitting the signed -64 web); unsigned mask in the CRC-loop height 139; variants scan best `height` u8/u16 44 (drops the target's s32 height).
- 2026-11-17 2026-11-17: cleanup HackeepromSaveRecords8: 3c3a54 removed: `offset = (u32)sector << 3` (or `(u32)sector * 8`) = 3/4: the variable is coloured s1 and both sll at 0x1db0/0x1db4 read it, but the widening loses its offset use, so `move s4,s1` (0x1dc8) disappears and the loop test reads `slti at,s1,256`. `sector * 8`, `sector * sizeof(u64)`, `(u32)` on the loop init alone: 117. `sector` as the write-loop variable (no idx) 68.
- 2026-11-17 2026-11-17: cleanup HackeepromSaveRecords8: reconstruct hack-free: plain 172, + pad 166, + pad + `idx = sector` before the poll 178, + pad + `(u32)sector << 3` 169, `idx` hoist without pad 184.

## Untried ideas
- 6b7e71: a natural kill of `height` (or `i`) between a's def and the call that leaves height unchanged for the len argument (the `height -= 4` kill reproduces a's v1 variable and order; only the len register chain differs).
- 3c3a54: a widening read of `sector` (cvt) in the header/bzero region together with `(u32)sector << 3`, so the widening keeps a second use and stays coloured s4.
- 081ad7: a real post-bzero block in `&D_807ECEA0`'s range (none of the target's post-bzero code reads it).

## Evidence
- Target frame 4216; `contReadPending` home 92(sp); `workingData`/`savedData` sp+2144/sp+96.
- 0x1b28/0x1b38: `&D_807ECEA0` s7, -8 s4 (exact adjsave tie, Q0900).
- 0x1bf4-0x1c1c: CRC loop: `multu s0,t3` (a) issued before `move v0,t3` (height), a narrowed into v1 as a variable, len narrowed through a1 (`andi t8,a1; move a1,t8`), b's `multu t5,t3` with t5 = i + 1 computed at 0x1bd0.
- 0x1c64/0x1c88: arm 0 reloads unsigned -64 through `at` (signed -64 web s3 is live across arm 0 and used again at 0x1d5c/0x1d70, so arm 0's masks are a different, uncoloured candidate).
- 0x1db0/0x1db4: two separate `sll ..,s1,3` (address and size); 0x1dc8 `move s4,s1`; 0x1e2c `slti at,s4,256`; 0x1e38 `andi s2,s1,0xffff` in the loop-entry block after the halted check.
