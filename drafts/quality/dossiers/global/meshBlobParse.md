# meshBlobParse (global, src/global/10E1D0.c)
## Sites
global:80709890:dead-if:d04805 dead-if: `if (blob && blob) {}` after the 3rd heapAlloc; block split so walker p (loop 1) is not in the call block and gets $v0 (addiu v0,a3,4 at 0x474). FIXED (index loop).
global:80709890:noop-arith:9afbfd noop-arith: `+ ((s32)blob->vertices * 0)`; extra ucvt/umpy use lifts blob+0x2C adjsave 3 -> 4 to tie columnCounts (a0 at 0x440). FIXED (index loop).
global:80709890:noop-arith:b08e97 noop-arith: `+ ((s32)blob->cells * 0)`; same for cells (a1 at 0x450, columnCounts a3 at 0x468). FIXED (index loop).
global:80709890:dead-if:220b46 dead-if: `if (gFbTileTable && gFbTileTable) {}` before loop 2; block split so b+12 is a candidate in a0 (0x4d0) and q gets $v0 (0x4dc). FIXED (index loop).
global:80709890:dead-if:99be94 dead-if: `if (r == 0) {}` in loop 3; loop-weighted use of r so walkers beat the -32vreg condition temp for $v0. FIXED (index loop).
## Attempts
2026-11-11 round 11 CleanGlobal10E1D0 opus-5-5:low: sweep remove/cond/classify, plain, diagnose, shared permuter run, for-loop reconstruct -> fdiff 1.
2026-11-12 round 17 CleanGlobal2DE90 / Rev17L opus-5-5:low: uopt diagnoses (bits 27/28, 34/35, 93), joint permuter run, natural rewrite score 2239 / 402 -> nohit; sweep re-run.
2026-11-14 HackmeshBlobParse opus-5-5:high:
- single removals: d04805 11, mul0 pair 8, 99be94 23, 220b46 46, all five 57 (variants.py try).
- pointer-fixup locals (vertices/cells/columnCounts locals, 6 orders) 8..65; s32/u32 casts, &x[i] spellings, operand order 8; typed fields (f32 *, MeshVertex *, MeshEntry *) 8 -> no change to the tie.
- screenVerts[2] alloc loop (not unrolled, call in loop) 143+ diff lines; unused label, scoped block, do-while(0), for-init placement 11..20.
- moving the d04805 split below columnCounts (mv2) 7: makes vertices/cells/columnCounts tie at 3.0 but p (a0) and vertices (v1) wrong.
- loop-2/loop-3 walker spellings (q2a-g 46, r1-r8 23+), shared walker p for loops 1+3 (p ties the condition temp at 22, temp wins on bit order) 23.
- index-form counting loops: `count = 0; while (a[count++] != 0) {}` for loop 1 alone with d04805 removed -> 0. 96-way combo (hacks x loop forms): all five hacks removed with loops 1-3 in index form -> fdiff 0.
- final: index loops 1-3, loop 4 as a plain while, `b->counts + k` / `(s32)(b->indices + k) + sum * 2`, MeshBlobTail.entries typed MeshEntry * -> fdiff 0, uninit pre-existing only, 0 FAKEs.
- rejected: merged NULL guards (5), `tail` rename (clint flags the pre-existing read as NEW), header retype to MeshVertex */MeshEntry * (matches, but adds a cast per line).
## Untried ideas
none open for this function (all sites fixed). Optional: MeshBlobHeader/MeshRangeView/MeshInfo are one 0x24 layout seen through three views; merging them touches meshComputeVertexRanges and meshDrawTextured (file-scope, other rungs).
## Evidence
0x3fc-0x428: three heapAlloc calls (0x708, vertexCount*16 x2); 0x440 addiu a0,s0,0x2c; 0x450 addu a1,a0,t4; 0x468 addu a3,a1,t6; 0x470-0x498 loop 1 (v1 word, v0 cursor, a2 count from 1); 0x4c8-0x500 loop 2 (a0 = b+12 stored at 8(t2), v0 cursor stride 28); 0x504 multu a2,t1 (t1=28 hoisted); 0x508 reload b->entries; 0x514 move v1,zero (loop-4 byte offset) before loop 3; 0x524-0x544 loop 3 against t0=-1 (cursor v0, k a3); 0x548-0x5a4 loop 4 (pretest beql on counts[0]); 0x5ac sw t2,32(sp) spill of b across the outEnd test.
uopt -l 5 (final): cursors are uixa candidates bits 39/71/89 (adjsave 15.5, $v0); count++ condition temp -20vreg adjsave 22 ($v1); blob+0x2C/cells/columnCounts bits 17/20/24 all adjsave 3.0 -> a0/a1/a3 in bit order.
