# mapCellFindAtPoint (global, src/global/55B20.c)
## Sites
- global:80652FDC:dead-if:40ab27 dead-if (`if (id) {}` after the id read): a block boundary between the id read (`lh v1,2(v0)` 0x2250, last use of the cell pointer v0) and the box address (`addu v0,a0,t0` 0x2264). Interference is per block (Q0523), so the split lets both take v0, and PRE moves the gMapCellBoxes load (0x2254/0x2258) into the id block as a cross-block a0 candidate, which keeps &gMapCellBoxes from becoming a candidate (removal: &gMapCellBoxes in s6, 12 in s7, id in a0). FIXED 2026-11-17 by an if/else-continue join.
- global:80652FDC:dead-if:16a986 dead-if (`if (box && box) {}` after the box address): exactly 3 extra loop blocks. Divisor ((nlive-2)>>2)+2 (Q0163): i nlive 18 -> 31/6 = 5.17 below the i*28 offset (nlive 17, 31/5 = 6.2), so offset s0 / i s1; outCell nlive 16 (20/5 = 4.0) above chunk nlive 18 (20/6 = 3.33), so outCell s2 / chunk s3. Without it: i/offset tie at 6.2 (i takes s0), and with only 2 extra blocks chunk/outCell tie at 4.0 (chunk takes s2). FIXED 2026-11-17 by an x-range early continue.

## Attempts
| date | unit / agent / model | form | text |
|---|---|---|---|
| 2026-11-14 | Hack55B20TypedMembers | removal | 55 |
| 2026-11-14 | | `box = &gMapCellBoxes[id]` or `gMapCellBoxes + id` | 68 |
| 2026-11-14 | | `MapCell *cell` snapshot | 55 |
| 2026-11-14 | | s32 id | 55 |
| 2026-11-14 | | for-loop form | 55 |
| 2026-11-17 | cleanup CleanmapCellFindAtPoint / anthropic/claude-opus-5-5 | for loop + guard continues on the match and/or box test (40 combinations, dead ifs removed) | 43-96 (uopt LFTR: exit test rebuilt as offset < count*28) |
| 2026-11-17 | same | do-while(++i) + `if (match) { id = c.id; } else { continue; }` | 16 (only i/offset s0/s1 swap) |
| 2026-11-17 | same | same + `if (box && box) {}` kept | 0 |
| 2026-11-17 | same | do-while(++i) + plain guard `if (mismatch) continue;` then id read | 48 |
| 2026-11-17 | same | do-while(++i) + then-continue/else (`if (mismatch) { continue; } else { id = ...; }`), nested positive ifs with else-continue arms, else-if chain of guards | 26 (one block short) |
| 2026-11-17 | same | any of those + `if (!(minX <= x && x <= maxX)) continue;` before the y/z test (also xy guard + z test) | **0 (merged: else-if chain of the two mismatch guards, lead copy per director ruling turn 145; the worker's then-continue/else form and the nested positive ifs also 0, re-measured by the lead)** |
| 2026-11-17 | same | `if (match) { id } else continue;` + x guard | 26 |
| 2026-11-17 | same | guard on the full box test, trailing `else { continue; }` on it, x and y guards | 62 / 62 / 16-26 |
| 2026-11-17 | same | every zero form as a `for` loop | 58-72 (LFTR) |
| 2026-11-17 | same | `box = &gMapCellBoxes[id]` in the zero form | 1 (addu operand order) |
| 2026-11-17 | same | (f32) casts dropped | 0 (kept) |

## Untried ideas
- None open: both sites fixed. The merged match guard is `if (chunk != ..) { continue; } else if (parent != ..) { continue; } else { id = ...; }`; the then-continue/else form and nested positive `if`s with `else { continue; }` arms are equivalent zero spellings.

## Evidence
- Frame 0x58; saved s0-s6, f20/f22/f24; s0 = i*28 (0x2220, `addiu s0,s0,28` 0x2360), s1 = i (0x2214, latch `addiu s1,s1,1` 0x2354, bnel/bc1fl delay slots), s2 = outCell (`lw s2,108(sp)` 0x222c), s3 = chunk (`sll s3,a3,16` 0x21cc), s4 = parent (`lh s4,106(sp)` 0x2228), s5 = &gMapCells (0x2218), s6 = 12 (0x2224).
- gMapCellBoxes reloaded every match (`lui a0`/`lw a0` 0x2254/0x2258), never hoisted; cell pointer and box both v0.
- Every failing compare branches straight to the latch (bnel/bc1fl with the i++ in the delay slot): a continue path through an extra block before the latch (full box guard, trailing else-continue, any for loop) lets uopt LFTR the exit test.
- Q0720: the permuter's zeros only wrap neighbouring statements in a `do {} while (0)`.
