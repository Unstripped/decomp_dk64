# arcadeDrawHud (arcade, src/arcade/0.c)
## Sites
- arcade:800319D4:other:2c43a5 (kept): removal 7 (the trailing increment pointerizes).
- arcade:800319D4:other:216e1c (pre-existing, now tagged 2026-11-17): the lives counter `i` (a3, home 148(sp)) reused for the clamped bonus timer (move a3,v0 / move a3,zero at 0xdf08/0xdf0c; register sharing only).
## Attempts
- 2026-11-14 opus:high: += 1 / = +1 both 7; increment moved earlier 17.
- 2026-11-17 2026-11-17: cleanup HackarcadeDrawStage4Background2 HackarcadeDrawStage4Background2 anthropic/claude-opus-5-5: D_8004A83C as a function-local static (`static s32 sFrameCount = 0;`, Q1125/Q0922): guard gone, fdiff TEXT OK (code and extern relocs match; own .data differs). Needs the lead data carve `[0x26790, .data, 0]` defining D_8004A790..D_8004A82C in C (IDO .data is 16-aligned; 0xB0 bytes verified against rom 0x26790-0x26840). Bonus timer in a dedicated local: after buf 31, after g 70, before i 98, block-scoped 31, `< 0` clamp 32, inline ternary 29; ternary + guard removed 36.
## Untried ideas
- land the 0x26790 .data carve (bundle .scratch/HackarcadeDrawStage4Background2/carve/), then re-measure the bonus-timer local with the static in place (ternary with the static: 37).
## Evidence
- target tail: `lui t7,%hi(D_8004A83C)` 0xe1f4, `lui at,%hi(D_8004A83C)` 0xe1f8, `lw t7,%lo(t7)` 0xe200, `sw t8,%lo(at)` 0xe214: separate lui/%lo per access (static signature, Q0761).
- D_8004A83C = 0 is the last .data word (rom 0x2683C) before .rodata (0x26840); nearest 16-aligned label start is D_8004A790.
