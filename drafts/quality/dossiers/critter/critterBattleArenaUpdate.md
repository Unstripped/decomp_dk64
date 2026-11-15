# critterBattleArenaUpdate (critter, src/critter/5110.c)
## Sites
- critter:80029118:other:28c4ff other (was 649ae8): REMOVED (HackcritterBattleArenaUpdate2). The `D_807FCC44 = 0` split-label clear is replaced by `u16 *throwAmmo = &gPlayerInventoryTable[0].throwAmmo;`. The pointer is initialised at its declaration and takes pad88's slot. It is used for the read, the clear and the 0xFE restore. Result: text=0, RELOC-EQUIV OK.
- critter:80029118:other:1fa591 other: REMOVED. The plain argument is fdiff 0. The target reads the unset sp+0x77 on the default path (0x1c0 -> 0x1ec), so clint's NEW UNINIT is the original flow (Q0752).
- critter:80029118:dead-if:68dc48 dead-if: REMOVED (PermBatch1114c). The fix was a named rewardFlag store in the tamper branch (Q0846).
## Attempts
- round 27 (opus:low): u8 pun -> u16 array (tagged); plain mapChallengeIdx (fdiff 0, clint NEW UNINIT); uopt_trace on the dead read; permute x3; table spelling (base CSE).
- 2026-11-14 U HackcritterBattleArenaUpdate (opus:high):
  - 1fa591 removed: asm proof of the original unset read; a default case changes the code (1744 vs 1760, 77 r).
  - 649ae8:
    - D_807FCC44 for read + clear: 3 r + 1 extra addiu
    - typed table for read + both stores: same, plus 2 reloc-only
  - 68dc48:
    - removal: 8 r + 7 |
    - variants scan of the removed copy: 60 variants, best = baseline 19
  - reconstruct, all plain: 11 r + 7 | + 3 extra
  - compare chains confirmed (no jump tables)
  - review: alignment loop -> `while ((s32)alignedBuf & 7) alignedBuf++;` (fdiff 0)
- 2026-11-14 OwnerInventorySplitLabels: read and restore moved to the table spelling (RELOC-EQUIV OK). The steer now sits on the clear only (649ae8 -> 28c4ff).
- 2026-11-15 HackcritterBattleArenaUpdate2 (opus:high), 28c4ff:
  - uopt_trace -l5 with the table spelling on the clear: the gPlayerInventoryTable lda (const 12) gets live range 155 in bb2 with 2 uses, adjsave 1.0. It is coloured into a3.
  - Split label at base: the clear's lda is its own const (14), and its single use is not coloured.
  - variants try (full/text):
    - Clear spelled as `[0].`, `->`, `(&[0])->`, `*&` (with the read as `[0]` or `->`): 7/5 (base CSE).
    - Read without tmp: 120/114.
    - A field pointer or `PlayerInventory *` added as a new local: 28-33 (frame -0x98 only).
    - A field pointer in pad88's or pad2's slot, initialised at its declaration: 2/0. This holds for the clear only, read+clear, read only, and all three accesses.
    - The same pointer assigned inside the block: 7/5 (the web re-forms).
  - Kept: the pointer is used for all three accesses. fdiff --reloc-ok exit 0. clint uninit exit 0 (pre-existing mapChallengeIdx/rewardFlag only). Raw words are equal except the sh at 0x60 (LO16 addend 0x2f4 vs 0, both 0x807FCC44).
## Untried ideas
- none open.
## Evidence
- frame `addiu sp,sp,-144`
- challengeState in s0 (lw s0,0x174(t6) at 0x34)
- gCurrentActor CSE temp spilled at sp+0x30
- throwAmmo read `lui v1; lhu v1,%lo+0x2f4(v1)` at 0x48/0x4c; clear `lui at; sh zero,%lo(at)` at 0x5c/0x60; restore `lui at` 0x510 / `sh a2,%lo+0x2f4(at)` 0x520
- mapChallengeIdx home sp+0x74 (sw at 0x1cc-0x1e0, lbu 0x77 at 0x1ec)
- rewardFlag home sp+0x70 (v0, lw on the default path at 0x4dc)
- returnMap/returnExit at sp+0x3c/0x38
- map switches are compare chains at 0x78, 0x190 and 0x4b0
