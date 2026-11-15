# menuRenderOptionDescription (menu, src/menu/E550.c)

## Sites
menu:8003292C:dead-if:cbf645 dead-if: the empty inner-loop `if (x)` lengthens and raises the full-width tile induction range so the target colours it before packet ranges.
menu:8003292C:dead-if:f74994 dead-if: the first signed-fade/xo guard is a class-1 allocator boundary after the tile loop: it keeps xo (cand 91, home -16) colouring after the hoisted y<<2 (cand 139, t2) and (y+0x29)<<2 (cand 152, t3), so xo takes t4.
menu:8003292C:dead-if:f74994#2 dead-if: the duplicate guard preserves xo's range through the row-mask/packet block; with both guards xo spans 15 blocks (adjsave 62.8 < 70 of 139/152), without them 8 blocks (adjsave 104).
menu:8003292C:other:4f8c03 other (FIXED 2026-11-15): was the consumed `actor` parameter carrying the second Combine packet. Now `gDPSetCombine(dl++, 0xFF97FF, 0xFF2CFE7F)`.
menu:8003292C:other:bc74f9 other (FIXED 2026-11-15): was `actor = &off` keeping off in memory. Now the loop's screen y and off are one local `yo`.
menu:8003292C:other:cd8c4b other (FIXED 2026-11-15): was `fontHeight = x * 4` reuse. Now `yo += fontHeight * 0.5;` with `x * 4` inline.

## Attempts
2026-11-09 CleanE550 anthropic/claude-opus-5-5: the cleanup pilot reconstructed packet macros and removed three earlier tags, but retained these six allocator/frame/ugen sites; individual removal and permutation did not match.
2026-11-10 Rev10B anthropic/claude-opus-5-5:low: traced x/xo candidate colouring, macro frame growth, off's memory home, and final-call ugen order; a natural reconstruction scored 1519 and the five-site permutation only reproduced dead guards.
2026-11-11 Rev17L anthropic/claude-opus-5-5:low: isolated register and frame deltas; all five distinct constructs removed together scored 450 and retained no natural match.
2026-11-14 HackmenuRenderOptionDescription openai-codex/gpt-5.6-sol: tested decoded `gDPSetCombineLERP`, a two-iteration tile-index loop, MIN clamp replacement, function- and block-scoped `y2`, block-scoped first-assignment `off`, fixed-coordinate reuse across both text calls, and combined six-site reconstructions; best new individual candidates were Combine score 19 and final-y score 25, while the complete natural rewrite scored 235 -> nohit, original retained.
2026-11-14 HackmenuRenderOptionDescription anthropic/claude-opus-5-5:high: frame-home accounting for a macro Combine; final y into address-taken `off` (4: only an extra `sw t0,212(sp)`) and into dead fontHeight/yo/y/alpha (7); `off` carrier/inlined final y without `&off` (28/35); guard removals with xo in the for header (84), `*32`/`*4` rect spellings (205-215), implicit header-xo conversion and outer `for` (18); six-site rewrites 120/114 -> nohit, original retained.
2026-11-15 HackmenuRenderOptionDescription2 anthropic/claude-opus-5-5:high: merged the separate loop `yo` local into `off` (renamed `yo`, 5th declared, home sp+0xD4): 10 declared locals free the word the second `gDPSetCombine` macro `_g` needs (frame stays 0xE8), and the merged variable's t0 range is split to its home across the first hudDrawScaledText (0x93c/0x978), so `&off` goes too -> fdiff 0 (4f8c03, bc74f9 fixed); final y as `yo += fontHeight * 0.5` with `x * 4` inline -> fdiff 0 (cd8c4b fixed); redundant `(s16)` argument casts and explicit float/int conversion casts dropped -> fdiff 0. f74994 first-guard-only uopt_trace (candidate order 139/152/91 vs 91/139/152). Guard removal under the new structure: both guards 18, all three 84; `xo + x` rect spelling 98-101 (frame 0xF0); inner do-while 21/90, outer for 18/84, outer while 22/87, `<` compares 18-20/84-85; header coordinates carried in x/y/xo/yo combinations 7-151; LAYOUT split of `y = 0; do {` 4. Permuter 900 s on the guard-free body (cbf645 kept): base 90, best 90 (24712 iterations).

## Untried ideas
A natural post-loop read or extra loop-region blocks for xo that lowers its adjsave below 70 (the hoisted y-shift candidates) without a dead guard; no ordinary C construct found that adds blocks without emitting code (the target's post-loop is straight-line from 0x7d8 to the end).

## Evidence
The matched target frame is 0xE8: 10 declared locals at -4..-40 (tex, alpha, y, xo, yo@-20=sp+0xD4, x, headerStr@sp+0xCC, descStr1@0xC8, descStr2@0xC4, fontHeight@0xC0) plus 23 GBI `_g` homes; spill temps at sp+0x48/0x50/0x60.
The loop's screen y (t0, mfc1 at 0x5d0; +0x29 spilled to sp+0x48 at 0x634, reloaded 0x7cc) and the description y (`gHiResScale * 200` into t0 at 0x930, `sw t0,212(sp)` 0x93c, `lw t0,212(sp)` 0x978) are the same variable: the post-call piece is a live-range split to its home, not an escaped local.
Final y: `mtc1 t0,$f6; cvt.d.w; add.d` with fontHeight*0.5 (0x988-0x9b0), truncated into a2 at 0x9b8 after the s0 re-extension of x*4 (0x994-0x99c).
xo adjsave (uopt -l 5): 62.8 with both guards (live bb 9,10-13,14,15-18,19,20-21,22,25), 104 without (9,10-13,14,15,19); candidates 139 (y<<2) and 152 ((y+0x29)<<2) are 70.
