# arcadeDrawHud (arcade, src/arcade/0.c)
## Sites
- arcade:800319D4:other:2c43a5: fixed 2026-11-17 (function-local `static s32 sFrameCount`, lead carve 463d64ab).
- arcade:800319D4:other:216e1c (kept, FAKE): the lives-loop counter `i` (a3, home 148(sp)) also holds the clamped bonus
  timer (`move a3,v0` / `move a3,zero` at 0xdf08/0xdf0c, `move a2,a3` in the `_sprintf` delay slot 0xdf14). The frame
  cost of a separate local can be cancelled (buf[0x4C], Q0986), so the remaining evidence is colour order: the clamp
  blocks lengthen the range of i, so the IV i*32+864 (cand 34) colours v0 first and i (cand 26) gets a3. Register
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
- 2026-11-17 2026-11-17: cleanup CleanarcadeDrawHud CleanarcadeDrawHud anthropic/claude-opus-5-5 (base 87ed9ed8):
  - Q0986 lever: `u8 buf[0x50]` -> `u8 buf[0x4C]` with the dedicated local declared between g and buf keeps the whole
    frame (buf 64, _g 60, n 59, spill 52, frame 152) and every instruction address.
    `u8 bonus` 13 (text 13, reloc 0): only colours differ: i -> v0, IV -> v1 in the lives loop (0xdad4-0xdb1c),
    clamp `andi v1,v0,0xff` / `move v1,zero` at 0xdf08/0xdf0c, `move a2,v1` 0xdf14.
    `s32 bonus` if/else 25, `<= 0` arms 25, ternary into bonus 25, copy-then-clamp `< 0` / `<= 0` 26: bonus colours a2
    directly and the else arm `move a2,zero` is hoisted to 0xdef4 (target: `move a3,v0` / `move a3,zero` + `move a2,a3`).
    `s8 bonus` 52. Other placements with buf[0x4C]: after i 53, first 53, after buf 64.
    Inline ternary with buf[0x4C] 66, with `s32 pad` between g and buf 29 (the ternary temp still takes a slot).
  - uopt_trace (u8 body): i (cand 26) colours first -> reg 1 (v0), IV (cand 34) -> reg 2 (v1), bonus (cand 80) -> v1;
    base: IV 34 first -> v0, i 26 -> a3 (reg 6).
  - Q1228 (16-aligned .data): data placement only, no lever on the a3 colouring.
  - FAKE note respelled with the colour-order evidence (code unchanged, fdiff 0).
## Untried ideas
- none natural: the frame objection is gone (buf[0x4C]), but no separate-local spelling gives the clamp the colour of
  the lives counter; only one variable spanning the loop and the clamp lowers its priority below the IV (Q0739/Q1204 mechanism).
## Evidence
- uopt_trace base: IV i*32+864 (cand 34) coloured v0 first, then var i (cand 26, M -4) a3. Inline ternary: i -> v0,
  IV -> v1, ternary temp (cand 80, M -100) -> a2.
- frame 152: i 148, g 144, buf 64-143, gDPSetScissor `_g` 60 (never stored), n 59 (`sb t6,59(sp)` 0xdf4c), uopt spill 52
  (IV `sw v0,52(sp)` 0xdaf4, n copy `sw t7,52(sp)` 0xdfbc), ra 44, outgoing args 16-36.
- lives loop: `move a3,zero` 0xdad4, `sw a3,148(sp)` in the jal delay slot 0xdafc, `lw a3,148(sp)` 0xdb00 (counter homed
  across dlAppendTextureRectangle), `addiu a3,a3,1` 0xdb10.
- clamp: `lb v0,gArcadeBonusTimer` 0xdef0, `blez v0` 0xdefc, `move a3,v0` 0xdf08, `move a3,zero` 0xdf0c, `move a2,a3` 0xdf14.
- target tail: `lui t7,%hi(D_8004A83C)` 0xe1f4, `lui at` 0xe1f8, `lw t7` 0xe200, `sw t8` 0xe214 (static sFrameCount).
