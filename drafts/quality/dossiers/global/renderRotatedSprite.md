# renderRotatedSprite (global, src/global/90D80.c)
## Sites
none (proto-steers 02809d/0d85ab fixed 2026-11-12; `siz` retyped s32 -> u32 by merge 62d6133d so ACDC0's local u8 declaration could go)
## Attempts
2026-11-10..13 CleanGlobal90D80 / Rev10F / Rev16E / Rev26A / Rev27 / GridSimpleBatch / Rev30B: volatile tex, Vtx * bit-size web, dead D_807FC79E test removed; u16 bpp + s16 tileSize; 103AB0 s32 width/height prototype; (f32)(u32) casts on width/height removed.
2026-11-17e 2026-11-17: cleanup HackhudPauseMenuRender13 HackhudPauseMenuRender13 anthropic/claude-opus-5-5 (base ff2f08b4): review only; 11 redundant (f32) casts dropped (8 vtxSetPosTex texture coordinates, 2 gfxDrawTexturedTileGridSimple x/y, `(f32)(s16)angle` -> `(s16)angle`), fdiff 0, signature unchanged.
## Untried ideas
none (no hack sites)
## Evidence
`siz &= ~0xC000` is `lui at,0xffff; ori at,0x3fff; and t6,a3,at` (0x52c-0x53c): siz is 32-bit in the definition.
vtxSetPosTex takes s16 texture coordinates and gfxDrawTexturedTileGridSimple f32 x/y, so the float/int conversions are implied by the prototypes (103AB0.h).
