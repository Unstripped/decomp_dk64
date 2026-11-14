# camUpdateFollowTargetDistance (global, src/global/201B0.c)
## Sites
- global:8061D1FC:other:d38760: RESOLVED (untagged). `sel = cam->unkF0` is a typed snapshot local; code unchanged.
## Attempts
- round 5 (opus:low): plain, diagnose, permute; see history.
- 2026-11-14 U HackcamUpdateFollowTargetDistance opus:high (variants.py try full=):
  - snapshot before the != 0 test: s32/u32 21, u8 10, s16 52
  - at the original place: s32/u32 0, s16 16, u8 89
## Evidence
- One load, `lbu a0,240(v0)` at 0x1e4c, feeds three uses:
  - the != 0 test (0x1e50)
  - the unkEF compare (`beq a0,v1`, 0x1e58)
  - the call argument (0x1e5c-0x1e68)
