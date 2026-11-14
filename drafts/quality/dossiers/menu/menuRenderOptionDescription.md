# menuRenderOptionDescription (menu, src/menu/E550.c)

## Sites
menu:8003292C:dead-if:cbf645 dead-if: the empty inner-loop `if (x)` lengthens and raises the full-width tile induction range so the target colours it before packet ranges.
menu:8003292C:dead-if:f74994 dead-if: the first signed-fade/xo guard is a class-1 allocator boundary after the tile loop.
menu:8003292C:dead-if:f74994#2 dead-if: the duplicate guard preserves xo's range through the row-mask/packet block and its v0/v1 interference.
menu:8003292C:other:4f8c03 other: the consumed `actor` parameter carries the Combine packet without the block-local `_g` home a GBI macro adds.
menu:8003292C:other:bc74f9 other: taking `&off` retains the offset's memory home across the first text draw.
menu:8003292C:other:cd8c4b other: reusing the consumed font-height local orders final-y truncation before the last call's argument setup.

## Attempts
2026-11-09 CleanE550 anthropic/claude-opus-5-5: the cleanup pilot reconstructed packet macros and removed three earlier tags, but retained these six allocator/frame/ugen sites; individual removal and permutation did not match.
2026-11-10 Rev10B anthropic/claude-opus-5-5:low: traced x/xo candidate colouring, macro frame growth, off's memory home, and final-call ugen order; a natural reconstruction scored 1519 and the five-site permutation only reproduced dead guards.
2026-11-11 Rev17L anthropic/claude-opus-5-5:low: isolated register and frame deltas; all five distinct constructs removed together scored 450 and retained no natural match.
2026-11-14 HackmenuRenderOptionDescription openai-codex/gpt-5.6-sol: tested decoded `gDPSetCombineLERP`, a two-iteration tile-index loop, MIN clamp replacement, function- and block-scoped `y2`, block-scoped first-assignment `off`, fixed-coordinate reuse across both text calls, and combined six-site reconstructions; best new individual candidates were Combine score 19 and final-y score 25, while the complete natural rewrite scored 235 -> nohit, original retained.

## Untried ideas
No remaining local ordinary-C rewrite is identified. Replacing the dead ranges with another no-op, array/struct home carrier, volatile qualifier, or cancelled arithmetic would only exchange one hack for another.

## Evidence
The matched target frame is 0xE8. `gDPSetCombineLERP` grows it to 0xF0 and moves the saved actor argument from sp+0xEC to sp+0xF4; its reduced score is 19.
The tile-index rewrite grows the frame to 0xF8 (and the all-natural rewrite to 0x100) rather than reproducing the target's x range.
A block-scoped real `off` keeps the frame at 0xE8, but moves the four string/font homes from target sp+0xCC/0xC8/0xC4/0xC0 to sp+0xD0/0xCC/0xC8/0xC4 and scores 34.
A dedicated final-y local grows the frame to 0xF0 and scores 25; the retained consumed-local dependency is what produces the target's final t6/t7 argument-order ring.
The retained baseline has 417 normalized as1 rows; exhaustive record scan found no improving edit, confirming that the two existing `LAYOUT:` joins already express the target schedule.
