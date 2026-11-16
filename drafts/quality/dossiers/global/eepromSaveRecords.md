# eepromSaveRecords (global, src/global/104F0.c)
## Sites
- 77df56 (other): FIXED 2026-11-14. The laundered `q` was standing in for a volatile read. The poll pointer is now `volatile u8 *contReadPending = gContReadPending;` with `while (*contReadPending != 0) sleepMilliseconds(1.0f);`. The volatile load is not folded (lui/addiu t2 + lbu t3,0(t2) at 0x1dcc-0x1dd4), and the loop reloads the pointer from its home 92(sp) into s0 (0x1de8).
- 6b7e71 (dead-if `if (a) {}`): lowers the priority of the &D_807ECEA0 lda web (uopt bit 179) below the signed -8 web (bit 181). Target colouring order: 180 (-64) s3, 181 (-8) s4, 179 (&D_807ECEA0) s7.
- 575291 (dead-store `offset = 0`): kills offset between the a/b defs and the trailing CRC call, so b (s2, 0x1cf8-0x1d28) and a (v1, andi at 0x1cfc) stay variables instead of b's expression being copy-propagated into the store index.
- 081ad7 (dead-if `if (D_807ECEA0) {}`): the same 179/181 lever as 6b7e71. It also decides whether the D_807467C4 or the D_807467E4 lda web gets s7.
- a1ca65 (dead-if, unsigned -64 use after the calls): stretches the U -64 web of the recordsOnly == 0 arm across calls, so that web stays uncoloured (li at,-64 at 0x1c64/0x1c88).
- 3c3a54 (dead-if `if ((u32)sector) {}`, class 1, kept): a direct read of u16 sector. Without it the variable loses its register (home sh 4210(sp)). With it the variable is s1 and its widening s4 (`move s4,s1` at 0x1dc8).
## Attempts
- rounds 5/13 (opus:low), Rev13A/Rev16H, 2026-11-14 first pass (opus:high): see history.
- 2026-11-14 U HackeepromSaveRecords anthropic/claude-opus-5-5:high:
  - poll pointer as volatile u8 * (while, while bare, if/do-while) -> 0 (kept; fdiff 0)
  - void * / s8 * / u32 * poll pointers -> 39; direct poll on the global with no pointer -> 224 (the lda web is coloured into s0 and the 92(sp) home disappears)
  - offset reused for the CRC result (offset = crc; store) -> 66; b before a -> 66; separate u32/s32 crc local -> 129; offset = strlen(...) used in bzero -> 137
  - CRC loop respellings without if (a): &workingData[a], workingData + a, one-statement height, *(u32 *)(workingData + b * 4), (u16)(height - 4), CRC via offset -> all 179
  - extern volatile s8 D_807467C4 (as F600.c declares it): 081ad7 removal -> 68; extern volatile s8 gMainThreadHalted -> 46
  - arm 0 with 0xFFFFFFC0/0xFFFFFFF8 -> 118; (u32) start -> 118; arm 0 as one expression -> 104
  - memcpy size: sizeof(u64) / 8U / sizeof(workingData) -> 83; (u32)sector << 3 -> 52
  - reconstruct (volatile base, every dead if removed, CRC through offset) -> 118; without 081ad7, a1ca65 and 575291 only -> 158
- 2026-11-15 U HackeepromSaveRecords2 anthropic/claude-opus-5-5:high:
  - sweep on the base copy: 0 hits (3c3a54 classify kept class 1).
  - same-TU data defined in the copy (D_807467C0 = D_80757020, D_807467C4/CC/E0/E4, gEepromCurrentSlot, D_807467E8 and the function-pointer table D_807467D0 = {eepromReadAllSectors, eepromSaveRecordsAll, eepromSaveRecordsOffset, eepromValidateSaveSlots}; Q0552 hypothesis), at the top of the file or in place of the externs: every single removal scores the same as without the data (6b7e71 179, 575291 125, 081ad7 46, a1ca65 118, 3c3a54 117); the all-removed function text is byte-identical with and without the data. The function has no switch `jr`, so the as1 address-taken CFG edge of Q0552 cannot arise, and uopt colouring does not see the data.
  - 575291 respellings that redefine offset in place instead of the dead store: `offset = (u16)(((offset + 0x40) / 4) - 1)` as the index 83; `offset = ...; b = offset` 84; `b = offset = ...` 84; `offset += 0x40; b = offset / 4 - 1` 117; `offset += 0x40; offset /= 4; b = offset - 1` 113; `b = offset + 0x40; b = b / 4 - 1` 138; a separate `size = sizeof(workingData)` local for the 0x800 terms of bzero/memcpy 129; `offset = 0x800` set just before bzero 66. Only the permuter form (offset = 0x800 at the dead-store point, a constant-holding kill) is 0: a hack swap.
  - uopt -zdbug:5 with all four dead ifs removed: the &D_807ECEA0 lda web (cand 179; uses bb1, bb7 loop, bb10 arm 0, bb11 arm 1, bb15 bzero) and the signed -8 web (cand 181; bb1 x2, bb7, bb11, bb15) have the same 15-block range and tie at adjsave 2.6. The tie goes to the lower candidate number, and 179 is numbered first because its lda is the first leaf of the sprintf expression (constants are numbered in ucode first-appearance order: 176 &gContReadPending, 177 const 2, 178 &D_807EDEAC, 179 &D_807ECEA0, 180 -64, 181 -8, 182 &sEepromSlotBuffer). With `if (a) {}` and `if (D_807ECEA0) {}`, 179 drops to 2.333 (its range runs one block past bzero) and 181 (2.6) wins s4 as in the target.
  - 6b7e71: `a = height * i` and `b = ((height * (i + 1)) / 4) - 1` -> 179 (no change). `sector = 0` moved to the end of arm 0: neutral with all tags (0), 179/46/118 with 6b7e71/081ad7/3c3a54 removed.
  - 081ad7: a named `s16 *modelCount = D_807ECEA0;` local for every D_807ECEA0[0] read -> 74 with both dead ifs, 202 without them, 202 without if (a) only, 74 without if (D_807ECEA0) only.
- 2026-11-15 U HackeepromSaveRecords3 anthropic/claude-opus-5-5:high (base 53ceee82, after f6b761ee):
  - sweep on the copy: 0 hits (3c3a54 classify kept class 1).
  - 575291 real kills of offset feeding the CRC source: `offset = a` -> 66, `offset &= 0xFFFF` (a dropped) -> 66, `offset = (u16)offset` (a dropped) -> 66, `offset = (s32)a` with `workingData + offset` -> 66. Each one keeps b in s2. But the u16 narrowing of a sinks below the b chain (andi t8 instead of andi v1 at 0x1cfc), and the CRC source becomes `addu a0,s5,t8`. b before a without a kill -> 125. variants scan on the 575291-removed copy: best is b as s32/u32 at 100.
  - 6b7e71+081ad7 removed (179): the sprintf masks written mask-first (`~0x3F & x`, `~7 & x`), one at a time or all four together -> 179 unchanged, so operand order does not renumber the candidates. A height local ahead of the sprintf -> 83: &D_807ECEA0 still gets s4 and -8 gets s7, and the 92(sp) home moves to 84(sp). The same with all tags kept -> 206. With only 6b7e71 removed -> 83. With only 081ad7 removed -> 238.
  - CRC loop as `i = 0; do {} while (i < 4)` (Q0767): 52 with every tag kept, and also 52 with 081ad7 removed (the dead read becomes inert, but the s4/s7 swap and a latch reorder at 0x1c54 remain). With both dead ifs removed -> 182. With all five removed -> 188.
  - a1ca65 removed with the j write loop as do-while -> 118 (no change).
  - 3c3a54 removed: byte-offset memcpy (`D_807ED6A8 + sector * 8`, ...) -> 115; `idx = sector` hoisted out of the for header -> 117; do-while j loop -> 117. The byte-offset memcpy with every tag kept -> 45 (the (u64 *) views stay).
  - reconstruct on the current file (all five removed): 187. b as s32 -> 176. Arm 0 as one signed expression -> 170; both together -> 171. A tail that mirrors the loop (`height = 0x40`, b and the CRC size from height) -> 187.
  - kept: the two redundant `(s32)` casts in arm 0 were dropped (`offset = ((offset & ~7U) * 4) + 0x3F; offset &= ~0x3FU;`): fdiff 0.
## Untried ideas
- A real kill of offset between `b = ...` and the CRC store that keeps `a` (the u16 andi v1,v0,0xffff at 0x1cfc) ahead of the b chain. Narrowing kills (offset = a / &= 0xFFFF / (u16)offset / (s32)a) fix b but sink a's andi (66), so the kill must not be built from a or from offset's narrowing. (2026-11-15 HackeepromSaveRecords3)
- A natural extra block or use that lowers the adjsave of the &D_807ECEA0 web (bit 179) below that of the -8 web (bit 181), or a source change that numbers -8 before &D_807ECEA0. Operand order inside the sprintf argument cannot do it: cfe/ugen canonicalise the commutative `and`. The -8 has to appear in an earlier statement. The hack-free webs tie exactly at 2.6, so any epsilon in 181's favour is enough. Nothing in the target after bzero reads D_807ECEA0. (uopt trace)
- A height local ahead of the sprintf scores 83 with both 179/181 dead ifs removed (179 without it). Combine it with a block lever that only 179's range sees. (2026-11-15 HackeepromSaveRecords3)
## Evidence
- 0x1ad8-0x1af4: &gContReadPending is stored at 92(sp) in the entry block (pointer local home). 0x1dcc-0x1dd4: unfolded volatile first poll load. 0x1de8: `lw s0,92(sp)` loop reload.
- 0x1d54: `li s2,2048` the 0x800 constant of bzero/memcpy is coloured into s2 after the final CRC (b's s2 is dead after the store at 0x1d30).
- 0x1db0/0x1db4: two separate `sll ...,s1,3` for the memcpy addresses and the size (sector << 3 is not CSE'd).
- eepromThreadMain (104F0.c) dispatches D_807467D0[] = {eepromReadAllSectors, eepromSaveRecordsAll, eepromSaveRecordsOffset, eepromValidateSaveSlots} (asm/global/data/14A1F0.data.s:2351). This data (and D_807467C0 = D_80757020 = "7.2", the first 104F0 .rodata string) belongs to the 104F0 TU, but the [0x14A1F0, data] segment is still unsplit asm; defining it in C does not change eepromSaveRecords.
- controllerUpdate/controllerGetReadData (F600.c) clear gContReadPending on the main thread and test D_807467C4.
- uopt -zdbug:6: bits 180/181/179 = -64 / -8 / &D_807ECEA0 webs (s3/s4/s7 in the target).
