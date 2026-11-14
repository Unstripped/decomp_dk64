# renderEntryListBuildDisplayList (global, src/global/35000.c)

## Sites
- 069be1: the PROTO_SKIP define plus the local void * declaration. FIXED.
  - renderModelQuadGfx really takes 8 arguments; the 8th, s32, is unused.
  - The shared prototype applies.

## Evidence
- Caller 0xa24..0xa44: `sw t0(=1),20(sp)`, `sw s6(layer),24(sp)`, `sw s5(playerIndex),28(sp)`.
- Callee frame 632: reads only 655(sp) and 658(sp).
