# eepromSaveRecords (global, src/global/104F0.c)
## Sites
- 77df56 (other): FIXED 2026-11-14. The laundered `q` was standing in for a volatile read. The poll pointer is now `volatile u8 *contReadPending = D_807ECD08;` with `while (*contReadPending != 0) sleepMilliseconds(1.0f);`. The volatile load is not folded (lui/addiu t2 + lbu t3,0(t2) at 0x1dcc-0x1dd4), and the loop reloads the pointer from its home 92(sp) into s0 (0x1de8).
- 6b7e71 (dead-if `if (a) {}`): lowers the priority of the &D_807ECEA0 lda web (uopt bit 179) below the signed -8 web (bit 181). Target colouring order: 180 (-64) s3, 181 (-8) s4, 179 (&D_807ECEA0) s7.
- 575291 (dead-store `offset = 0`): kills offset between the a/b defs and the trailing CRC call, so b (s2) and a (v1, andi at 0x1cfc) stay variables.
- 081ad7 (dead-if `if (D_807ECEA0) {}`): the same 179/181 lever as 6b7e71. It also decides whether the D_807467C4 or the D_807467E4 lda web gets s7.
- a1ca65 (dead-if, unsigned -64 use after the calls): stretches the U -64 web of the recordsOnly == 0 arm across calls, so that web stays uncoloured (li at,-64 at 0x1c64/0x1c88).
- 3c3a54 (dead-if `if ((u32)sector) {}`, class 1): a direct read of u16 sector. Without it the variable loses its register (home sh 4210(sp)). With it the variable is s1 and its widening s4 (`move s4,s1` at 0x1dc8).
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
## Untried ideas
- A natural extra block or use that lowers the adjsave of the &D_807ECEA0 web (bit 179) below that of the -8 web (bit 181). Nothing in the target after bzero reads D_807ECEA0. (uopt trace)
- A real kill of offset between `b = ...` and the trailing CRC call argument that is not a dead store (the CRC-result reuse kills it only after the argument is evaluated).
## Evidence
- 0x1ad8-0x1af4: &D_807ECD08 is stored at 92(sp) in the entry block (pointer local home). 0x1dcc-0x1dd4: unfolded volatile first poll load. 0x1de8: `lw s0,92(sp)` loop reload.
- eepromThreadMain (104F0.c) dispatches D_807467D0[] = {eepromReadAllSectors, eepromSaveRecordsAll, eepromSaveRecordsOffset, eepromValidateSaveSlots} (asm/global/data/14A1F0.data.s:2351). controllerUpdate/controllerGetReadData (F600.c) clear D_807ECD08 on the main thread and test D_807467C4.
- uopt -zdbug:6: bits 180/181/179 = -64 / -8 / &D_807ECEA0 webs (s3/s4/s7 in the target).
