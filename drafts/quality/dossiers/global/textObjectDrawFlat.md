# textObjectDrawFlat / textObjectDrawRotated (global, src/global/100180.c)
## Sites
- global:806FCC88:dead-if:78c984 and global:806FD094:dead-if:985a1a: REMOVED (this unit). Each dead read added one uopt block (28 vs 27) between vp[0] and vp[1]. Without it, the quad temps swap:
  - gx+gw: v1 -> v0
  - gw*2-1: v0 -> t2
  - -(gh*2): t2 -> v1
  These are at 0x1a50-0x1ab0 (Flat) and 0x1eb0-0x1f10 (Rotated); 8 r each.
## Attempts
- round 10 (opus:low): remove/cond nohit, classify kept class 1, review splits.
- 2026-11-14 U HacktextObjectDrawFlat, scored with variants.py try (full=):
  - removal alone: 8 (pure register renames)
  - other natural shapes: named w2/h2 66/58, glyph pointer 42/36, elem pointer 46/40, gbi without dl++ 153/139, vp[k] per-vertex order 11
  - variants scan of both removed copies: nothing below 8
  - per-vertex vp-> walk with vp++: 6, then 2 with vertices 2/3 storing ob[1] first, then 0 with the vp[0] ob stores on one line (both twins)
  - as1probe keep on the removed copy: full=8. The difference is uopt colouring, not as1.
## Untried ideas
- none for these sites. The one remaining LAYOUT line (vp[0] ob stores) is kept: splitting it moves `negu a1,a0` one slot (full=2).
## Evidence
- target quad block:
  - two gbi temps first: v0 = gSPMatrix, v1 = gDPPipeSync
  - then gx+gw in v1 (0x1a50), gw*2-1 in v0 (0x1a60), -(gh*2) in t2 (0x1a68)
  - vertex 2 stores sh t2,0x22 before sh v0,0x20; vertex 3 stores sh t2,0x32 before sh a1,0x30
