# textDrawStringVtx (global, src/global/100180.c)
## Sites
- global:806FC530:dead-if:ae146d dead-if: REMOVED. `if (w4) {}` split the indexed vp[k] vertex block so v0 held yoff+y+h4-1 (0x148c) and then gx+w (0x149c).
- global:806FC530:other:d481a0 other: REMOVED. The 4x trailing `vp++` kept vp in s1 and gx in s2 (`vp += 4` swaps them).
- global:806FC530:other:1e50d1 other: REMOVED (2026-11-15). Real gbi macros replace TEXT_GFX_CMD; the 0xc8 frame comes from declaration placement (see Evidence).
- global:806FC530:dead-store:cdb041 / cdb041#2 dead-store (kept): `i = count /= 4` makes the `i-- > 0` entry compare read count (copy-propagated), so it fuses into `blez t7` (0x1560) / `blez t5` (0x1728), and keeps count in s8 with the counter in a3.
## Attempts
- rounds 9-32 (opus:low) and HacktextDrawStringVtx (opus:high, 2026-11-14): see quality history and drafts/quality/dossiers/global/textDrawStringVtx.md.
- 2026-11-14 U HacktextDrawStringVtxB anthropic/claude-opus-5-5:high: 128-variant grid of the per-vertex vp-> walk (variants.py try).
  - Grid dimensions:
    - vertex 1 ob[1]: own store, chained into vertex 0, or separate in vertex 0
    - vertex-0 one-line layout: ob / tc / both / none
    - dead if: kept or dropped
    - ob store order in vertices 1-3
  - Six variants score 0, all with the dead if dropped and the tc one-liner present.
  - Chosen: vertex 1 stores its own ob[1]; vertex-0 tc stays on its LAYOUT line; vertex 2 ob0,ob1; vertex 3 ob1,ob0. fdiff 0.
  - Without the tc one-liner: 2. Vertex 3 in ob0,ob1 order: 2. Every variant keeping the dead if: > 0.
  - Count dead stores with the new walk: i = count / 4 in both loops 321, first loop only 321, second loop only 31. Count counter (c2) with the walk: 8.
  - Reconstruct (gbi _g + count counter + no pads) with the walk: 95, the same as gbi + c2 with the old block.
- 2026-11-15 U HacktextDrawStringVtx2 anthropic/claude-opus-5-5:high:
  - 1e50d1 fixed (fdiff 0). Frame census first: target homes are line -1, idx -2, ch -3, startX -6, strStart -12, batch -28, leftPad -29, center -30, started -31, yoff -69, h4 -74, w -78, h -80 (offsets from sp+0xc8). The shared cfe temp (`?:` and `i-- > 0`) sits at -104 (sp+0x60), and spills start at sp+0x5c.
  - The fix uses real macros: gDPSetTextureFilter(G_TF_BILERP), gSPMatrix (NOPUSH|LOAD|PROJECTION and NOPUSH|LOAD|MODELVIEW), gDPPipeSync, gDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA), gDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA_PRIM2), gSPVertex and gSP1Quadrangle.
  - Function-level declarations, in order: line idx ch startX strStart i vp len batch leftPad center started count. The 8 setup and line-start `_g` homes land at -40..-68.
  - yoff, w4, h4, gx, w and h are declared in the `ch != 0x20` block, so they come after those homes at -69..-80. The 5 vertex, quad and final `_g` homes land at -84..-100.
  - glyph and tmp are inline. Any 6th word gives frame 0xd0: glyph+tmp in the block, or tmp in the block with if/else and no cfe temp.
  - `x = x + fw*4 - leftPad - w4` gives `addu t7,v0,t6` at 0x162c. `x += fw*4 - leftPad - w4` gives the target `t6,v0` order.
  - The variant files are in b/ (v1..v7, s1..s7). If/else instead of `?:` removes the cfe temp but rotates s3/s4/s5 (139+).
  - cdb041 / cdb041#2 tried on the new body:
    - `i = count / 4` at both sites: 321. Site 1 only: 321. Site 2 only: 31.
    - `count /= 4; while (count-- > 0)`: 8. The entry test becomes `slt`+`beqz` and the counter goes to s8.
    - `i = count / 4; count = 0;` before the loop: 322.
    - `for (i = count / 4 - 1; i >= 0; i--)`: 329.
    - `while (--i >= 0)`: 324.
    - `while (i > 0) { i--; }`: 802.
    - `for (i = count / 4; i > 0; i--)` with `(i - 1) * 4`: 792.
    - `for (i = count; i > 0; i -= 4)`: 210.
## Untried ideas
- cdb041 / cdb041#2: only the copy-propagated compare (`i` a copy of a variable that the decrement does not change) gives the fused `blez`. Untested: a natural reason for such a copy (a separate quad-count variable that does not cost a frame word).
## Evidence
- Vertex block 0x1478-0x1500.
- Store order: vp0 ob0 0, ob1 2, then vp1 ob1 0x12 (same v0), ob2 4, tc1 0xa, tc0 8. Then vp1 0x10/0x14/0x18/0x1a; vp2 0x20/0x22/0x24/0x28/0x2a; vp3 0x32 before 0x30, then 0x34/0x38/0x3a.
- Frame layout (2026-11-15): a declaration in the `ch != 0x20` block is placed after every `_g` home parsed before that block. cfe temps go below all locals, and one shared temp serves every `?:` and post-decrement compare.
- `addiu s1,s1,64` sits in the delay slot of `beqz s7` at 0x1500.
