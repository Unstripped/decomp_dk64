# slotQueueGetMaxValue (global, src/global/FCCD0.c)
## Sites
- global:806F8EDC:other:1cabff: REMOVED. The redundant `if (bits)` guard around the instrument-level do-while kept `player` in a1. The fix: declare `bits` s32 (it was u8) and write a plain `while (rest != 0)` loop.
## Attempts
- 2026-11-14 U HackslotQueueGetMaxValue (opus:high):
  - plain `while (rest != 0)` with u8 bits: fdiff 17. The only change is that `player` moves from a1 to a2 (reload `lw a1,28(sp)` at 0xf28 and its uses).
  - `for (rest = bits; rest != 0; rest >>= 1)`: 21 (u8) and 4 (s32).
  - no `rest` (shift bits itself): 55.
  - variants scan on the while body: `bits` u8 -> s16/s32/u32 = 0. s32 was kept: Q0370, u8 field-load temps become separate candidates.
## Untried ideas
- none
## Evidence
- The case 7 guard `beqz a0,117c` at 0x1164 is the while loop entry test (IDO rotation, Q0083), with `move v0,a0` (rest = bits) in the delay slot.
- The loop is at 0x116c-0x1178: `sra t5,v0,1` / `addiu v1,v1,1` / `bnez t5`.
