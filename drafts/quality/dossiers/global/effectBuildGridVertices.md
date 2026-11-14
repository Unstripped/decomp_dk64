# effectBuildGridVertices (global, src/global/119370.c)
## Sites
- global:8071509C:dead-if:c40fbc `if (node->width == 0) {}`: makes ucvt(node->width) candidate bit 10, ahead of the x store destination (bit 17), so width colours a1 (unconstrained colouring in bit order).
- global:8071509C:dead-if:99d137 `if (node->height == 0) {}`: makes height bit 14, so it colours a2.
- global:8071509C:dead-store:9acc0b `node = effect->grid;` (second): without it the height load is hoisted to the top (0xa40), where the target loads it inside each mode arm (0xa64 / 0xa90).
## Attempts
- rounds 5 and 17 (opus:low): 8 keep/remove combinations; reconstruct with natural nested loops (990 lines); permuter (row = ...); diagnose traces.
- 2026-11-14 U HackeffectBuildGridVertices (opus:high), scored with variants.py try (full=):
  - body:
    - per-vertex walking body: 0 with the tags kept (now the copy's body)
    - index-form cells: 31
    - per-row pointer with += 4: 16
    - per-vertex with vertexIndex += 4 at the end: 5
    - per-vertex with vertex++ before vertexIndex++: 12
  - tags:
    - all removed: 74 (71 register renames)
    - keep both dead tests, drop the kill: 3 (one hoisted lbu)
    - other combinations: 49-97
  - header statement orders: 74-140
  - per-arm effect->grid reads: 122-160
  - uopt -l 6 candidate bits: base width 10, height 14, x 17; all-removed x 9, width 12, height 28
## Untried ideas
- A natural expression use of node->width/height ahead of the x store that emits no code. No candidate found: any real early-out emits branches the target does not have.
- Named width/height locals are ruled out: the target reloads width and height inside the loops (0xbb8 lbu a1,8(v0), 0xbcc lbu a2,9(v0)) because the vertex stores may alias the node.
## Evidence
- one lw v0,0x330(a0) for effect->grid
- mode lbu 0x36f(a0) re-read in each vertex arm (0xb10, 0xb68)
- cellW/cellH re-read per use (lh 12/14(v0))
- vertex cursor a2 = effect + 0x28 + 16*v1 set per row (0xac8)
- the cursor steps +32 and v1 +2 at 0xb14/0xb18, then +16/+1 twice, with tc[1] stored at -6(a2) after each step
