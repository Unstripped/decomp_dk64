# lensFlareDrawSource (global, src/global/103AB0.c)

## Sites
global:80701098:other:37e973 (other): raw G_TEXTURE (0xD7000002/0x80008000) + G_SETCOMBINE
  (0xFC119623/0xFF2FFFFF) words instead of gSPTexture/gDPSetCombineMode; the two macro
  `_g` block homes need two words of frame that the target spends on named locals.

## Attempts
2026-11-15 global HacklensFlareDrawSource2 anthropic/claude-opus-5-5:high: frame census, then
  gSPTexture + gDPSetCombineMode with pad2[2] dropped and the three register-only floats
  (facing, colorScale, alphaScale) declared between i and screenY; first with
  G_CC_MODULATEIDECALA_PRIM -> fdiff 1 (only the combine words differ: 0xFC11FE23/0xFFFFF3F9),
  then G_CC_MODULATEIA_PRIM (decoded from 0xFC119623/0xFF2FFFFF: TEXEL0*PRIMITIVE both
  cycles, colour and alpha) -> fdiff 0. Site removed.

## Untried ideas
(none; site fixed)

## Evidence
Target frame 0x1C0 (addiu sp,sp,-448 at 0x22e8). Saved regs sp+0x30..0x7F; double spill
temps sp+0x80/0x88/0x90; struct-return CSE temps sp+0xC4 (addiu s0,sp,196 at 0x25b8) and
sp+0xD0 (addiu s5,sp,208 at 0x23c8); three existing `_g` homes sp+0xDC..0xE4.
Named locals: axisEnd 0x1B4, axisSpan 0x1A8, viewDir 0x19C, srcDir 0x190, pos 0x184,
eye 0x178, at 0x16C, src 0x160, pad1 0x10C..0x15F, screenX 0x108 (addiu s3,sp,264 at
0x2780), i 0x104, pad2 0xFC/0x100, facing 0xF8, screenY 0xF4 (addiu s4,sp,244 at 0x277c),
alpha 0xF0 (swc1 $f18,240 at 0x2380; lwc1 at 0x2a1c/0x2d2c), colorScale 0xEC,
alphaScale 0xE8. Only screenX, screenY and alpha are memory-resident among the scalars:
no sp access to 0xE8/0xEC/0xF8/0xFC/0x100. So the 8 bytes of pad2 plus the homes of the
register-only floats are interchangeable: any order that keeps screenY at 0xF4 and alpha
at 0xF0 with 3 words between i and screenY frees the bottom 2 words for the macro `_g`s.
