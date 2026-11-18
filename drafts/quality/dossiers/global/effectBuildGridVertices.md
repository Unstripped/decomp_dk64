# effectBuildGridVertices (global, src/global/119370.c)
## Sites
- global:8071509C:dead-if:8a8d82 (copy key; replaces base c40fbc + 99d137) `if (node->width == 0 || node->height == 0) {}`: numbers the ucvt(node->width) web bit 10 and ucvt(node->height) bit 14, ahead of the x store destination (bit 17), so width colours a1, height a2, x a3, startX t0 (unconstrained colouring in bit order). Availability class (Q0908 class 2): only same-value reads work.
- global:8071509C:dead-store:9acc0b `node = effect->grid;` (second): kills ilod(node+9) availability after the guard read, so height is loaded inside each mode arm (0xa64 / 0xa90) instead of once at entry; it must sit after the guard and before the x statement (the x statement re-reads node->width after it, so ilod(node+8) stays available for the first-row guard `blez a1` at 0xac0).
- (base) global:8071509C:dead-if:c40fbc `if (node->width == 0) {}` and global:8071509C:dead-if:99d137 `if (node->height == 0) {}`: merged into 8a8d82 by 2026-11-17 CleaneffectBuildGridVertices (Q1187).
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
- 2026-11-17 U HackeffectBuildGridVertices2: no matching removal. Initial width/height locals feeding initial positions with loop bounds reloaded score 80: height is hoisted to a3 and vertex index moves v1 to t0. Per-arm cellHeight locals with both guards retained and kill removed score 82 (s16) or 27 (s32), both hoisting height. A switch replacing mode if scores 3, with height hoisted before the branch. A corner-bit inner loop reconstruction without the steers scores 141, adding an 8-byte frame and saving s0.
  - as1probe on the no-kill candidate (full=3) tested 1,445 single record edits; only deleting the hoisted `lbu $6,9($2)` reduced the score, to 2 with 115 instructions against 117, so it is not a C-level match.
- 2026-11-17 U CleaneffectBuildGridVertices (session 2026-11-17f), variants.py try (full=):
  - FIXED (3 -> 2 sites): the two dead tests merged into one two-term guard (Q1187): `if (node->width == 0 || node->height == 0) {}` + kill = 0 (fdiff OK); `node->width != 0 && node->height != 0` and `> 0 && > 0` with the kill also 0; `node->width && node->height` 74, `!node->width || !node->height` 74. uopt -l 6 numbering identical to the base (width 10 a1, height 14 a2, x 17 a3, startX 24 t0, mode 28 t1, y 31 t2, cellH 33 t3, row 40 t4, column 46 t5, vertex 51 a2).
  - merged guard without the kill: `&&` 3 (lbu a2,9(v0) hoisted to entry, arm loads gone), `||` 10 (empty-if branches beqzl/bnezl emitted with PRE-inserted height loads).
  - kill positions with the merged guard: per mode arm `node = effect->grid;` 1 (the arm stores also kill ilod(node+8): extra lbu a1,8(v0) at the row head before blez a1); after startX = x 52 (node moves v0 -> v1, vertexIndex v1 -> a1); before vertexIndex = 0 44 and guard before vertexIndex 44 (vertexIndex numbered after the dims).
  - guard reads through effect->grid with a single node store: 84-91 (ilod(ilod(effect+0x330)+k) are separate candidates); mixed node/effect->grid terms 79-128.
  - lever F56F0 (named field locals): s16 `width = node->width;` + `x = -(width * node->cellW) / 2` + height dead test + kill = 1 (width var bit 9 and ucvt 12 both a1, ahead of x 18; the kill after the local load kills ilod(node+8) so the first-row guard reloads lbu a1,8(v0) at the row head); s32 width local 2 (also multu t6,a1 operand order), u8/u16 79-80, u32 81; width local with no height read 109; kill before the width local 109. Height locals (s16/s32) at entry: 43-156 (the height var and its ucvt are two candidates and the ucvt web is available at the arms and the row guard, so the load stays at entry).
  - loop spellings with the merged header: `&effect->vertices[vertexIndex]` 0 (cosmetic), for loop with vertex set before it 39, vertex set per cell 26.
  - permuter (hack-free weights, -j 2, 900 s) from the all-removed body: base 450, best 320 in 57 outputs (y = effect->mode reused ahead of the x statement: steer), no zero.
- 2026-11-18 U CleaneffectBuildGridVerticesb (session 2026-11-18), variants.py try (full=):
  - sweep 21 checks, 0 hits (8a8d82 classify class 2, cond/recipe/remove nohit; 9acc0b cond/recipe/remove nohit).
  - guard as real control flow: early-out `if (node->width == 0 || node->height == 0) { return; }` without the kill 9; uopt -l 6 numbering and colouring identical to the target (width 10 a1, height 14 a2, x 17 a3, startX 24 t0, mode 28 t1, y 31 t2, cellH 33 t3, row 40 t4, column 46 t5, vertex 51 a2), the only differences being beqz a1 / beqz a2 + 2 nops after lbu a1,8(v0) and one entry lbu a2,9(v0) instead of the arm loads (0xa64/0xa90). With the kill kept 70; early return + kill in the x statement 70; outer `if (node->width != 0 && node->height != 0) { body }` 9.
  - x-less headers without the tags: startX-only (`startX = -(node->width * node->cellW) / 2;`, x first stored at the row start) 78 (startX bit 9 a1, width ucvt 12 a2, mode 19, y 22, height ucvt 25); the same with both tags 39; chained `startX = x = ...` 74 (= all-removed).
  - one-construct kill merges: `x = -((node = effect->grid)->width * node->cellW) / 2;` with the guard 0 (the same redundant store inside the expression: respelling, base spelling kept); kill as the guard's body `if (...) { node = effect->grid; }` 11 (beqzl a1 / bnezl a2 with re-inserted lbu a1,8 / a2,9 on the joined paths, height at entry); `(node->width == 0 || node->height == 0) | ((node = effect->grid) == NULL)` as one test 65.
  - confirmation (not new): guard through `effect->grid->` with the only node store after it, no kill, 91.
## Untried ideas
- A natural statement that stores `node` (or makes ilod(node+9) unavailable) between the guard read and the x statement without code; none found: the target has no store or call before the mode branch, and a kill anywhere later also kills the width web for the first-row guard. One-construct merges (kill in the x statement, in the guard body, in the guard test) tried 2026-11-18.
- A ucode-order construct that numbers ucvt(node->height) before the x store without an early read (cfe statement order is source order for every form tried; uopt numbers a store's variable before its right-hand side, so the dims must appear in an earlier condition: the guard, or real control flow, which emits branches).
- The target numbers exactly like a real early-out `if (node->width == 0 || node->height == 0) return;` with no branch: the original was probably a check whose body compiled to nothing (a debug macro); no C form found that keeps the numbering without the empty if.
## Evidence
- one lw v0,0x330(a0) for effect->grid
- mode lbu t1,0x36f(a0) hoisted to 0xa30 and reused at the row end (0xbd8); reloaded with height and cellH on the inner-loop exit (0xbcc-0xbd4)
- width lbu a1,8(v0) at 0xa38 feeds the first-row guard blez a1 at 0xac0; reloaded at 0xbb8 for the loop test
- height lbu a2,9(v0) inside each mode arm (0xa64 / 0xa90), used by the row guard blez a2 at 0xab4
- cellW/cellH re-read per use (lh 12/14(v0))
- vertex cursor a2 = effect + 0x28 + 16*v1 set per row (0xac8)
- the cursor steps +32 and v1 +2 at 0xb14/0xb18, then +16/+1 twice, with tc[1] stored at -6(a2) after each step
