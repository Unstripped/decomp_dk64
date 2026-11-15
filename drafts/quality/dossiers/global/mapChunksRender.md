# mapChunksRender (global, src/global/55B20.c)
## Sites
- a1232a / 19cc66: the PROTO_SKIP define plus a local s32 last-parameter declaration (kept).
## Evidence
- **Call sites:** both mapChunksRender call sites store flag with `sw s5,0x1c(sp)` (0x5620, 0x5ac4) under either declaration, with no andi.
- **Owner:** renderEntryListBuildDisplayList reads the argument as a byte: `lbu s5,0xaf(sp)` at 0x904.
- **So:** the declaration has no visible operation of its own, and the ORIG rule does not apply. The s32 declaration only colours the -1 layer sentinel into s8 (`li s8,-1` at 0x5100).
