# flagUpdateRangeCompletion (global, src/global/135D30.c)
## Sites
- global:807311C4:other:f4d609: REMOVED. The `0x21U` bound is now `sizeof(D_80756024) / sizeof(D_80756024[0])`, with the extern sized [0x21].
## Attempts
- rounds 29-30 (low/medium): literal bound LFTRs to an end pointer; permute only respelled the unsigned bound.
- 2026-11-14 opus:high (full=):
  - inline sizeof: 0 (applied)
  - sizeof(FlagRange): 0
  - u32 count local: 0
  - s32 count local: 22
## Evidence
- D_80756024: 0x21 x 8 bytes = 0x80756024-0x8075612B, then 4 bytes of padding before 136820.c's D_80756130.
