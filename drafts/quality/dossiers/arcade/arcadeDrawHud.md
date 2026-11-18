# arcadeDrawHud (arcade, src/arcade/0.c)
## Sites
- arcade:800319D4:other:2c43a5: fixed 2026-11-17 (function-local `static s32 sFrameCount`, lead carve 463d64ab).
- arcade:800319D4:other:216e1c (kept, FAKE): the lives-loop counter `i` (a3, home 148(sp)) also holds the clamped bonus
  timer (`move a3,v0` / `move a3,zero` at 0xdf08/0xdf0c, `move a2,a3` in the `_sprintf` delay slot 0xdf14). Register
  sharing only: the target never stores the clamp to 148(sp), so not ORIG (cfa137 ruling).
## Attempts
- 2026-11-14 opus:high: (2c43a5) += 1 / = +1 both 7; increment moved earlier 17.
- 2026-11-17 2026-11-17: cleanup HackarcadeDrawStage4Background2 HackarcadeDrawStage4Background2 anthropic/claude-opus-5-5:
  D_8004A83C as a function-local static (`static s32 sFrameCount = 0;`, Q1125/Q0922): guard gone (now landed). Bonus
  timer in a dedicated local (pre-carve): after buf 31, after g 70, before i 98, block-scoped 31, `< 0` clamp 32, inline
  ternary 29; ternary + guard removed 36.
- 2026-11-17 2026-11-17: cleanup HackarcadeDrawHud HackarcadeDrawHud anthropic/claude-opus-5-5 (carve body cff1dc07):
  - re-measured: dedicated s32 local after buf 31, last 31, block-scoped 31, after g 70, first 98, before-i 98;
    `t = timer; if (t < 0) / (t <= 0) t = 0;` 32; ternary into t 31; inline ternary 29 (unchanged by the carve).
  - new: dedicated local widths: u8/u16 block-scoped 15 (reloc 0), u8/u16 last 19, s8/s16 52 (clamp in v1 via
    `andi v1,v0,0xff`, n slot 59->58, lives counter still v0).
  - permuter 900 s -j 2 from the block-scoped s32 body: base 871, best 459 (only narrows the local to unsigned char = the u8 variant), no zero.
## Untried ideas
- none natural: the frame is fully packed (below), so a dedicated clamp local or a ternary temp always takes a slot.
  Dropping the gDPSetScissor macro's `_g` slot (hand expansion) would free 60(sp) but is a worse hack.
## Evidence
- uopt_trace base: IV i*32+864 (cand 34) coloured v0 first, then var i (cand 26, M -4) a3. Inline ternary: i -> v0,
  IV -> v1, ternary temp (cand 80, M -100) -> a2.
- frame 152: i 148, g 144, buf 64-143, gDPSetScissor `_g` 60, n 59 (`sb t6,59(sp)` 0xdf4c), IV spill 52 (`sw v0,52(sp)`
  0xdaf4), ra 44; any extra local or ternary temp shifts n and the IV spill by 4 (spill 48).
- lives loop: `sw a3,148(sp)` in the jal delay slot 0xdafc, `lw a3,148(sp)` 0xdb00 (counter homed across
  dlAppendTextureRectangle).
- target tail: `lui t7,%hi(D_8004A83C)` 0xe1f4, `lui at` 0xe1f8, `lw t7` 0xe200, `sw t8` 0xe214 (static sFrameCount).
