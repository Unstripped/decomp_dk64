# hudPauseMenuRefreshTotals (global, src/global/ACDC0.c)
## Sites
global:806ABE3C:other:be71d9 other: first two terms via gPlayerInventoryTable[0].kong[k], loop from 2 via e (FIXED: plain nested for loops; IDO unrolls the 14-iteration loop with 2 peeled terms)
## Attempts
2026-11-10..12 CleanGlobalACDC0 / Rev16K / Rev17M (low, medium): all through e (row pointer a3/t0), for loops (975/810), permutes (masks)
2026-11-14 HackhudPauseMenuUpdate opus-5-5:high: for k / for i index loops (0, applied); e-walker forms 18-30; index loops for the two LAYOUT flag loops (11, 49) not applied
## Untried ideas
none for be71d9
## Evidence
0x3dcc-0x3e1c: lhu 66/68(a1) peeled, 4-wide body over v0 = a2+4 with v1 2..14 step 4, outer a1/a2 += 94 to a3 = table + 470.
