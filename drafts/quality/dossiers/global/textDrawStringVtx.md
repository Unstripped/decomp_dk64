# textDrawStringVtx (global, src/global/100180.c)
## Sites
- global:806FC530:dead-if:ae146d dead-if: REMOVED. `if (w4) {}` split the indexed vp[k] vertex block so v0 held yoff+y+h4-1 (0x148c) and then gx+w (0x149c).
- global:806FC530:other:d481a0 other: REMOVED. The 4x trailing `vp++` kept vp in s1 and gx in s2 (`vp += 4` swaps them).
- global:806FC530:other:1e50d1 other (kept, not this item): TEXT_GFX_CMD function-scope Gfx temps hold the stack layout (unused 0xb0-0xb8 / 0x84-0xa8 in the 0xc8 frame).
- global:806FC530:dead-store:cdb041 / cdb041#2 dead-store (kept, not this item): `i = count /= 4` keeps count in s8 and the quad counter in scratch a3 (0x1564, 0x172c).
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
## Untried ideas
- cdb041 / cdb041#2: the count-counter form (full=8) remains the closest; see the earlier dossier.
- 1e50d1: block-scoped `_g` slot placement in IDO 5.3 (earlier dossier).
## Evidence
- Vertex block 0x1478-0x1500.
- Store order: vp0 ob0 0, ob1 2, then vp1 ob1 0x12 (same v0), ob2 4, tc1 0xa, tc0 8. Then vp1 0x10/0x14/0x18/0x1a; vp2 0x20/0x22/0x24/0x28/0x2a; vp3 0x32 before 0x30, then 0x34/0x38/0x3a.
- `addiu s1,s1,64` sits in the delay slot of `beqz s7` at 0x1500.
