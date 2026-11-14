# eepromCopySlot (global, src/global/104F0.c)
## Sites
global:8060BA14:noop-arith:57b6f7 noop-arith: stride = stride | 0 extends the stride web past dst (stride v0, quotient t8, original a3, replacement v1) (KEPT)
## Attempts
2026-11-10..12 Clean104F0 / CleanGlobal104F0 / Rev16H: traces, permutes (dead stride stores)
2026-11-14 HackeepromClearSlotData opus-5-5:high: src/dst table-base initialisers (16, shape 0: register naming only), size = stride / 8 without reassigning (24), stride >> 3 (27), orders (15-20)
## Untried ideas
combine the base-pointer form with a stride use after memcpy that is real code (none found)
## Evidence
0x26c-0x2cc: lh v0 D_807ECEA0, stride arithmetic in v0, sra t8; multu t8,a3 (original) then t8,v1 (replacement); a2 = t8 (size).
