# camCalculateTargetDistanceAndAngles (global, src/global/201B0.c)
## Sites
- global:8061D6A8:other:60a290: RESOLVED as ORIG (the cam->unk0->z re-read).
## Attempts
- rounds 5/16 (opus:low): diagnose, permute; see history.
- 2026-11-14 opus:high (full=):
  - actor->z: 3
  - cam->unk0 for z and x: 3
  - y through cam->unk0 too: 5-27
## Evidence
- 0x22e4 `lw t6,0(s1)`: reloads cam->unk0 after the sqrtf call.
- 0x22f0 `lwc1 $f10,0x84(t6)`: z through the reloaded pointer.
- 0x22f4 `lwc1 $f6,0x7c(s0)`: x from the actor local.
