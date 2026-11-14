# critterBattleArenaUpdate (critter, src/critter/5110.c)
## Sites
- critter:80029118:other:649ae8 other: D_807FCC40[2] read vs D_807FCC44 clear. Both are gPlayerInventoryTable+0x2F4 (0x807FCC44). Two symbols give two lui pairs (0x48 `lhu v1,%lo+4(v1)`, 0x5c `sh zero,%lo(at)`); one symbol shares a base in a3.
- critter:80029118:other:1fa591 other: REMOVED (this unit). The plain argument is fdiff 0. The target reads the unset sp+0x77 on the default path (0x1c0 -> 0x1ec), so clint's NEW UNINIT is the original flow (Q0752).
- critter:80029118:dead-if:68dc48 dead-if: the dead read raises rewardFlag's priority so it is coloured into v0. The target loads the unset home with `lw v0,0x70(sp)` on the default path (0x4dc).
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
## Untried ideas
- 649ae8: a header carve that gives 0x807FCC40-0x807FCC48 (unk2F0..unk2F8) a natural name that is read through one object and written through another. No natural candidate: the read and the clear hit the same field.
- 68dc48: a real second use of rewardFlag that emits no code (none found). A uopt -l 6 trace of the removed copy to compare rewardFlag's priority against the colouring threshold.
## Evidence
- frame `addiu sp,sp,-144`
- challengeState in s0 (lw s0,0x174(t6) at 0x34)
- gCurrentActor CSE temp spilled at sp+0x30
- mapChallengeIdx home sp+0x74 (sw at 0x1cc-0x1e0, lbu 0x77 at 0x1ec)
- rewardFlag home sp+0x70 (v0, lw on the default path at 0x4dc)
- returnMap/returnExit at sp+0x3c/0x38
- map switches are compare chains at 0x78, 0x190 and 0x4b0
