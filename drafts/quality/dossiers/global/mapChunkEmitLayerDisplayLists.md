# mapChunkEmitLayerDisplayLists (global, src/global/55B20.c)
## Sites
- global:80656B98:do-while0:f1ca28 do-while0: the Gfx * parameter p is reused as the MapChunkCell * cell pointer (Q0531). The parameter web has a0-a2 forbidden (layer arrives in a2 at entry), so the cell pointer gets a3 (`addu a3,a1,t9`; `lh a0,0(a3)`; `lbu t4,2(a3)`) and a2 is left to the e38ff4 ghost load.
- global:80656B98:dead-if:e38ff4 dead-if: `if (*(u32 *)&gMapCells == 0) {}`. Any dead read of an unrelated integer global works (gMapCellCount, D_807F5DE8, `*(u32 *)&gMapChunks`). Its uilod (cand 101 {190|1}) takes a2 without code, and its block split leaves `layer` (cand 25) live through call blocks 19/20/35 (adjsave -9.33, uncoloured, so `lbu ...,75(sp)` reloads). The -1 sentinel (cand 158) then gets s8 (`li s8,-1`).
- global:80656B98:dead-if:1bc6dd dead-if: `if (p == 0) {}`. A pure no-code uopt block boundary between `gfx = p` and the first packet: `if (1) {}`, `chunk`, `layer`, `gMapCellCount`, `gfx` all match at the same spot.
- global:80656B98:noop-arith:5f4853 noop-arith: `gfx = (Gfx *)((u32)gfx | 0)`. uopt folds the `| 0` but keeps cfe's u32 ucvt, so `gfx = ucvt(gfx)` is a real def+use of gfx (cand 0) in loop-head block 19. That raises adjsave 13.4 -> 15.4, and gfx takes s0 before the packet pointers (cands 112/123).

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

## Untried ideas
- A natural no-code uopt label right after `gfx = p` for 1bc6dd. The camFloorSnap 2026-11-17f map found only dead control flow gives one.
- Anything that forbids a2 for a fresh cell local without a parameter web. Its live range would have to reach function entry, or a higher-priority candidate would have to hold a2 across the search with no code (today that is the e38ff4 ghost load).

## Evidence
- Target 0x5efc `addu a3,a1,t9` and 0x5f00 `lh a0,0(a3)` (before `lw v0,gMapCells`), then 0x5f38 `lbu t4,2(a3)`: the cell pointer is in a3, and a2 is unused in the loop.
- Target 0x5ec4 `li s8,-1` hoists the dl sentinel. `layer` reloads from its home at 0x5de8, 0x5eb0 and 0x5f2c (`lbu ...,75(sp)`).
- Target 0x5db8/0x5dbc: the first gDPPipeSync is written through a0; gfx lives in s0 (`addiu s0,a0,8` at 0x5de0).
- Level-5 traces (.scratch/CleanmapChunkEmitLayerDisplayLists/t5_*.txt):
  - base: p cand 2 adjsave 8.25 reg 6, with forbidden 1-5,14,17; ghost uilod cand 101 6.67 reg 5; layer cand 25 -9.33 uncoloured; -1 cand 158 reg 22.
  - fresh cell: cand 88 adjsave 10 reg 5.
