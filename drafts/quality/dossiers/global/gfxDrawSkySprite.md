# gfxDrawSkySprite (global, src/global/109660.c)
## Sites
global:80705F5C:other:1316f1 (hand-expanded gSPMatrix on one line): REMOVED.
- Each gbi macro's block `_g` takes a frame word (Q0353/Q0663).
- Dropping `Gfx *g` (use `dl` throughout) frees exactly one word for the gSPMatrix macro's `_g`.
- Declaring `s16 x, y, z` first keeps every memory-resident home in place: screenX/Y 0x6C/0x68, lightR/G/B 0x60/0x5C/0x58, x at 0x76.
## Attempts
- round 10-17 (opus, opus:low): gSPMatrix(g++) macro (frame 0x80); dl-only form in the original declaration order (homes shifted); permutes best 5/9.
- 2026-11-14 HackgfxDrawSkySprite (opus), variants.py try (lines off):

  | variant | lines off |
  |---|---|
  | dl-only, original declaration order | 12 |
  | dl-only, alpha second | 12 |
  | dl-only, y or z second | 12 |
  | dl-only, x/y/z first | 0 |

## Untried ideas
none (fixed).
## Evidence
Frame 120. Homes: x sh 118(sp) at 0x188c; lightR/G/B passed as sp+96/92/88 at 0x1630-0x1638; screenX/screenY passed as sp+108/104 at 0x18dc/0x18c0.
