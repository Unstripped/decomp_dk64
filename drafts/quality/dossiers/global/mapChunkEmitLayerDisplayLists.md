# mapChunkEmitLayerDisplayLists (global, src/global/55B20.c)

## Sites
- **global:80656B98:do-while0:f1ca28 (do-while0)**: the Gfx * parameter p is reused as the MapChunkCell * cell pointer (Q0531). The parameter web keeps its precolour exclusions, so the cell pointer gets a3 (`addu a3,a1,t9`; `lh a0,0(a3)`; `lbu t4,2(a3)`).
- **global:80656B98:dead-if:e38ff4 (dead-if)**: `if (*(u32 *)&gMapCells == 0) {}` keeps `layer` (cand 25) uncoloured, so it is reloaded with `lbu ...,75(sp)`, and the -1 dl sentinel is hoisted into s8 (`li s8,-1`).
- **global:80656B98:dead-if:1bc6dd (dead-if)**: `if (p == 0) {}`. EXHAUSTED.
- **global:80656B98:noop-arith:5f4853 (noop-arith)**: `gfx = (Gfx *)((u32)gfx | 0)`. EXHAUSTED.

## Attempts
2026-11-14 U HackmapChunkEmitLayerDisplayLists opus-5-5 (variants.py try on the named types; full diff lines):
- **f1ca28, MapChunkCell \*cell local:**
  - set after `node = gMapCells`, separate statements: 4. Only a2 vs a3 for the cell pointer, plus `lh a0` scheduled after `lw v0`.
  - same, with `node = gMapCells; cell = ...; do {` on one LAYOUT line: **3**. Only a2 vs a3 is left.
  - declaration first or after gfx: 3 as well.
  - cell set first: 13.
  - while search: 87; for search: 87; `s16 id` snapshot (Q0601): 87.
  - cell set at the loop top and used for the dl test: 96.
  - pointer walker: 95, 108 with all reads through cell; all reads through cell: 66.
  - parameter named gfx: 35.
- **e38ff4 removed:**
  - on the base: 80;
  - on the cell base: 82. The trace shows layer (cand 25) takes reg 22 (`andi s8,a2,0xff`), the -1 constant is not hoisted, and the target's `lbu 75(sp)` reloads disappear.
- **Reconstruct (natural, no FAKE):** 116; with parameter gfx: 110; with while search: 121.
- **Permuter:** 905 s run (`perm/`, `perm_run.log`) on the cell/LAYOUT base: baseline 15, best 15, no zero.

## Untried ideas
None that keep the cell pointer in a3 without reusing a parameter. In the level-5 uopt traces:
- **Original:** the parameter web (cand 2) carries the a0-a2 precolour exclusion (forbidden 1-5, plus 14 and 17) and colours reg 6 (a3) (Q0531).
- **With a fresh MapChunkCell \*cell (cand 88):** forbidden is only 1-4, 14 and 17, so it colours reg 5 (a2), and p (cand 2) drops to reg 3.

## Evidence
- Target 0x5efc `addu a3,a1,t9` and 0x5f00 `lh a0,0(a3)` (before `lw v0,gMapCells`), then 0x5f38 `lbu t4,2(a3)`: the cell pointer is in a3.
- Target 0x5ec4 `li s8,-1` hoists the dl sentinel. `layer` is reloaded from its home at 0x5de8, 0x5eb0 and 0x5f2c (`lbu ...,75(sp)`), which the e38ff4 ghost keeps (traces t6_orig.txt vs t6_l1_noghost.txt).
