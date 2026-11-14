# projectileRenderSpriteRing (global, src/global/9BF30.c)
## Sites
- global:80697230:other:e23d19 (final key 153bd8): gSPMatrixShared through the function-scope _g. A gbi block _g moves the idx*4 spill from 0x7c to 0x78 (0x274/0x45c).
## Attempts
- round 28 (opus:low): gbi gSPMatrix (spill shift), permute.
- 2026-11-14 U:
  - gDPLoadTextureBlock + gbi: frame 0x1a0
  - dropping q3/q2/pads: frame fixed, but the f32 homes are 8 higher
  - 321-layout brute force: no match
  - Mtx * local for both uses: 3808 bytes
  - Mtx-array indexing: adopted (view fix, fdiff 0)
## Untried ideas
- where IDO places block-scoped gbi `_g` homes relative to the function-scope f32 locals (a probe TU), to fit the target's 0x7c spill.
## Evidence
- frame 0x198
- mtx2 0x154, mtx1 0x114, i 0x110
- f32 homes 0xd4-0xe4
- spill 0x7c
- 8-byte f64 slots for the q's
