# actorTargetTableLoad (global, src/global/67890.c)
## Sites
- global:80662B90:other:87ac3c `vtxOffset = start[0] * sizeof(Vtx);` with `s32 start[3]`.
  - Target: sw zero,0x18(sp) at 0x8; lw v0,0x18(sp) at 0x98; sll 4.
  - Only 0x18 is used, but the frame (0x28) needs a 12-16-byte local.
## Attempts
- round 25 (opus:medium): plain, diagnose, permute.
- 2026-11-14 U, scored with variants.py try (full=):
  - array [1]/[2]: 2
  - array [4]: 4
  - struct field: 205
  - volatile: 14
  - plain 0: 205
  - per-vertex index: 206
  - for loop: 230
## Untried ideas
- a real 3-word table the original filled (e.g. per-batch vertex starts) if more of the function surfaces elsewhere
