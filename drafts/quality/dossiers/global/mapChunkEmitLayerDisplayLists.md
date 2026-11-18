# mapChunkEmitLayerDisplayLists (global, src/global/55B20.c)
## Sites
Terms below use the compute_save formula (36880, 2026-11-18 queue): adjsave = sum((loads + stores) * freq) / bucket(live units), bucket(n) = n for n <= 2, else ((n - 2) >> 2) + 2; freq 10 in the cell loop; an exact tie goes to the lower candidate bit.
- global:80656B98:do-while0:f1ca28 do-while0: the Gfx * parameter p is reused as the MapChunkCell * cell pointer (Q0531). The parameter web is live in the entry blocks, where a1 (chunk) and a2 (layer) arrive, so a0-a2 are forbidden and the cell pointer gets a3 (`addu a3,a1,t9`; `lh a0,0(a3)`; `lbu t4,2(a3)`). A fresh cell local scores 30 / bucket(9 units) = 10.0. That is above the e38ff4 ghost's 20 / bucket(6) = 6.67, so the cell is coloured first and takes the lowest free register, a2. The joined line `node = gMapCells; p = ...; do {` is part of this steer. It keeps `lh a0` before `lw v0`, but the swapped order on the same line scores 7, so it has no LAYOUT evidence (the tag was reworded to FAKE on 2026-11-18).
- global:80656B98:dead-if:e38ff4 dead-if: `if (*(u32 *)&gMapCells == 0) {}`. Any dead read of an unrelated integer global works (gMapCellCount scores 3 in the fresh-cell body, the same as gMapCells). PRE places its uilod in the search preheader (block 21), so it is live over blocks 21..26: 2 points * 10 / bucket(6) = 6.67. It takes a2 with no code. Its empty-if blocks add two loop units to i (14.2 -> 11.83) and to layer*4 (6.2 -> 5.17). Layer counts 19 units in the natural body (12 / bucket(19) = 2.0). The ghost alone (n0_g) or 1bc6dd alone (n0_b) gives 21 units, still 2.0, a tie that layer wins on its lower bit (s8). Both together give 23 units, 12 / bucket(7) = 1.71: inferred, because the trace prints only the split pieces, but consistent with the base colouring layer after the -1. That is below the -1 constant's 10 / bucket(17) = 2.0, so -1 takes s8 and layer is split and left on the stack (`lbu ...,75(sp)` x3).
- global:80656B98:dead-if:1bc6dd dead-if: `if (p == 0) {}` between `gfx = p` and the first packet. It does two jobs.
  (1) Its blocks stop the copy propagation of `gfx = p + 1` into the four switch arms. Each arm then counts 2 uses + 1 def of gfx instead of 1 def (+8 points), so gfx goes from 146 to 154 points / bucket 10, that is 14.6 -> 15.4.
  (2) It adds 2 entry units to layer's live range (see e38ff4).
  Alone it leaves layer at 21 units, 2.0, which ties the -1 and wins on candidate bit 22 < 156 (n0_b).
- global:80656B98:noop-arith:5f4853 noop-arith: `gfx = (Gfx *)((u32)gfx | 0)`. uopt folds the `| 0` but keeps cfe's u32 ucvt, so it is a real def+use of gfx in loop-head block 19: 2 refs * 10 = +20 points (13.4 -> 15.4 with 1bc6dd; 12.6 -> 14.6 in the natural body). gfx must reach >= 15.0 (it wins a tie on its lower bit) to take s0 ahead of the gSPSegment/gSPDisplayList `_g` temps (30 / bucket(2) = 15.0 each, s1/s2). Neither 5f4853 (14.6) nor 1bc6dd (13.4) is enough alone.

## Attempts
2026-11-14 U HackmapChunkEmitLayerDisplayLists opus-5-5 (variants.py try on the named types; full diff lines):
- **f1ca28, MapChunkCell \*cell local:**
  - set after `node = gMapCells`, separate statements: 4 (a2 vs a3 for the cell pointer, plus `lh a0` after `lw v0`);
  - on one LAYOUT line `node = gMapCells; cell = ...; do {`: 3 (only a2 vs a3);
  - declaration first or after gfx: 3; cell set first: 13;
  - while search 87, for search 87, `s16 id` snapshot (Q0601) 87;
  - cell set at the loop top and used for the dl test: 96;
  - pointer walker 95 (108 with all reads through cell); all reads through cell 66; parameter named gfx 35.
- **e38ff4 removed:** 80 on the base, 82 on the cell base.
- **Reconstruct (natural, no FAKE):** 116; with parameter gfx 110; with while search 121.
- **Permuter:** 905 s on the cell/LAYOUT base: baseline 15, best 15.

2026-11-17 (session 2026-11-17f) CleanmapChunkEmitLayerDisplayLists anthropic/claude-opus-5-5:
- **5f4853:** `gfx = gfx`, `(Gfx *)(u32)gfx`, `(Gfx *)(s32)gfx`, `&gfx[0]`, `gfx + 0` and `(void)gfx` are folded by cfe: 32 each (s0/s1/s2 rotation). `^ 0` scores 0. `if (gfx) {}` 87. The `| 0` matches at any loop-body position.
- **1bc6dd:** guard on `1`, chunk, layer, gMapCellCount, p, gfx: 0; on `gMapChunks`: 2. After the first sync 63; in the loop 134; `(u32)p | 0` copy 97; first packet through p (`gDPPipeSync(p); gfx = p + 1;`) 99.
- **e38ff4 operand classes:**
  - `1` and locals: 74; layer 87; chunk 82; gMapCells[0].id 101;
  - pointer gMapChunks 132; pointer gMapCells 2;
  - unrelated integer globals: 0.
  - Indexed `gMapCells[j]` search without node or ghost: 67.
  - Ghost moved: before the search 76; after the visible test 95; inside the search loop 44-199.
- **f1ca28:**
  - cell local scoped in the loop body, in the else block, or `register`: 3 each;
  - no cell variable at all: 4; cell for the search only 101; for the mask only 8.
- **Reconstruct:** cell-free natural body with Gfx *gfx param 111; with a p -> gfx copy 117.
- **Permuter:** hack-free weights, -j 2, 900 s, from the all-four-removed body (perm_e): baseline 2422, best 1074. The best output only adds a `!chunk` triple guard and a `(long long)` cast.

2026-11-18 (session 2026-11-18) CleanmapChunkEmitLayerDisplayListsb anthropic/claude-opus-5-5 (variants.py try, full diff lines; -l5/-l6 traces in .scratch/CleanmapChunkEmitLayerDisplayListsb/t5_*.txt, t6_*.txt):
- **f1ca28, fresh cell body (a1, score 3), the ghost re-spelled to outrank the cell:**
  - double-use ghosts: `G == G` 75, `(G & G) == 0` 3, `G + G` 38, `G * G` 43, `G < 0` 3, `G ? G : 0` 100;
  - ghost moved: top of the do body 44, found arm 136, else arm 132, before `found = 0` 76, after the visible test 95;
  - non-hoistable ghosts read through node/cell (`node->chunk`, `->parent`, `->seen`, `->unk6`, `cell->pad3`, `cell->dl[0]`): 75 each; `node->id` 47.
- **f1ca28, other forms:**
  - no cell variable with the ghost kept: 4 (a2 vs a3 + lh/lw order);
  - `s16`/`s32 key` snapshot, with or without a cell local: 14;
  - cell defined at the loop top (dl test still via gMapChunks): 99;
  - statement orders with separate lines: found/cell/node 13, cell/found/node 13, cell/node/found 14, node/found/cell 6, found/node/cell 4;
  - joined line swapped (`p = ...; node = gMapCells; do {`) 7; joined statements with `do {` on the next line 2.
- **5f4853/1bc6dd:** with 1bc6dd removed, gfx is 14.6 and takes s2; layer ties the -1 at 2.0 and takes s8 (99). Single loop-head constructs in place of both: `| ((u32)gfx & 0)` 99; two `| 0` statements 82; `if (gfx == 0) {}` + `| 0` 99.
- **1bc6dd + e38ff4 as ONE compound entry test (ghost removed, `if (p == 0) {}` replaced at the same spot):**
  - `p == 0 && chunk == 0`, `p == 0 || chunk == 0`, `p == 0 && p == 0`, `if (p == 0) {} else {}`, `chunk == 0 && layer == 0`, `p != 0 && chunk != 0`: 74 each (shape 0);
  - three terms 82; `1 && 1` 80 (no ghost 80).
  - In the 74 variant every callee-saved register matches: gfx 15.4 in s0, layer uncoloured, -1 in s8. The extra && block gives layer its two missing non-loop units.
  - What is left is the ghost's second job. Without a no-code holder in a2, &gMapChunks[chunk] (adjsave 5.5, target t0) takes a2 (`addu a2,t6,s5` at 0x5dd4) and its uses shift t-registers.
  - Terms reading gMapChunks[chunk] first (`kind == 2 && p == 0`, ...) 78: the dead test makes no block-0 reference, and the address still gets a2.
- **Guard inside a branch (1bc6dd moved after the kind compare, so &gMapChunks[chunk] is defined in entry block 0 where layer arrives in a2):**
  - &gMapChunks[chunk] goes back to t0 and layer stays uncoloured;
  - but cellCount (4.4, target t1) takes a2 instead, and the arms no longer stop the copy propagation of p + 8 (gfx s2);
  - then/else placement scores the same: simple guard 102 (50 with the ghost), compound 54 (50 with the ghost), three terms 65.
- **Natural reconstructs:**
  - cell local + continues (N0) 117: gfx 12.6 below the `_g` temps' 15.0 and i's 14.2 (gfx takes s3); layer 12 / bucket(19) = 2.0 ties the -1's 2.0 and wins on bit 22 (andi s8,a2,0xff);
  - nested ifs instead of continues (Q0948): 117-118, with no extra units for layer;
  - K&R definition: 123;
  - parameter gfx with a loop pointer `dl = gfx; ... gfx = dl;`: 97. dl gets 20.33 and takes s0, but the copy blocks make the parameter interfere with dl (move s0,s1 / move s1,s0), and layer stays in s8.
- **variants.py scan:** base: only neutral zeros (compare swaps, found widths, declaration swaps); fresh-cell body: best 4, no zero.
- **Permuter:** hack-free weights, -j 2, 900 s (18.7k iterations), from the fresh-cell body with the ghost removed (perm_a6, 1bc6dd and | 0 kept): baseline 1768, best 320.
  - The best output only re-inserts a dead test on an array address, `if (!gMapChunks[chunk].cells[i].dl) {}`, between the visible and mask tests. As C that is 41 lines; `!cell->dl` 75; before the visible test 97.
  - The 330 output adds a value-named zero local and `if (!_g) {}`.

## Untried ideas
- Natural code adding about 4 non-loop units to layer's live range (pushing it to bucket 7) while the -1 stays at 17 units or fewer, for example a real dispatch between `gfx = p` and the first packet. Only dead control flow is known to give one (camFloorSnap map, 2026-11-17f).
- A natural +16..20 points of gfx in the cell loop with no code (two refs at freq 10). Every cfe-folded spelling loses the ucvt (17f).
- A cell variable live at function entry without the parameter web. None was found: callers pass three arguments (a3 is never set at 0x5498/0x5558/0x5710/0x57d0), so a fourth parameter is not possible.

## Evidence
- Target 0x5efc `addu a3,a1,t9` and 0x5f00 `lh a0,0(a3)` (before `lw v0,gMapCells`), then 0x5f38 `lbu t4,2(a3)`: the cell pointer is in a3, and a2 is unused in the loop (its only use is the entry home store `sw a2,72(sp)` at 0x5da4).
- Target 0x5ec4 `li s8,-1` hoists the dl sentinel. `layer` reloads from its home at 0x5de8, 0x5eb0 and 0x5f2c (`lbu ...,75(sp)`).
- Target 0x5db8/0x5dbc: the first gDPPipeSync is written through a0; gfx lives in s0 (`addiu s0,a0,8` at 0x5de0). Arm packets use s1 (`move s1,s0` in the switch delay slots 0x5df0-0x5e10).
- Callee-saved order in the target: gfx s0 > gSPSegment `_g` s1 > gSPDisplayList `_g` s2 > i s3 > layer*4 s4 > chunk*456 s5 > 0xE7000000 s6 > &gMapChunks s7 > -1 s8; layer uncoloured.
- Base trace: gfx 154 points / 10 = 15.4; `_g` temps 15.0; i 11.83; p web 8.25 (forbidden 1-5,14,17 -> a3); ghost 6.67 (-> a2); -1 2.0 (-> s8); layer split, -9.33 and 0.0, uncoloured.
