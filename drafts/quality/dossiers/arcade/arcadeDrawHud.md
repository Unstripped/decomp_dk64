# arcadeDrawHud (arcade, src/arcade/0_game.c)
## Sites
- arcade:800319D4:other:2c43a5: fixed 2026-11-17 (function-local `static s32 sFrameCount`, lead carve 463d64ab).
- arcade:800319D4:other:216e1c (kept, FAKE): the lives-loop counter `i` (a3, home 148(sp)) also holds the clamped bonus
  timer (`move a3,v0` / `move a3,zero` at 0xdf08/0xdf0c, `move a2,a3` in the `_sprintf` delay slot 0xdf14). The frame
  cost of a separate local can be cancelled (buf[0x4C], Q0986), so the remaining evidence is colour order and the a3
  preference: split, the counter and the IV i*32+864 tie exactly (adjsave 15.5) and the counter wins by definition
  order (Q1551); joined, the clamp blocks drop i to 11.33 so the IV takes v0, and the clamp web's `_sprintf` a2
  preference (bb 82 pref 5), forbidden by the loop's `li a2,76`, puts the whole of i in a3 (Q0162). Register
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
- 2026-11-19 2026-11-18c: cleanup CleanarcadeDrawStage3Backgroundb CleanarcadeDrawStage3Backgroundb anthropic/claude-opus-5-5 (base a3d0ef71, renamed body):
  - re-run: dedicated `u8 bonus` with buf[0x4C] 13 (text 13), `s32 bonus` 25. uopt -l6 base: IV (cand 34) -> v0 first, i (26) -> a3;
    u8 split: i 26 -> v0, IV 34 -> v1, bonus 80 -> v1.
  - NEW (split the other way): a dedicated lives-loop counter `life` with i kept for the clamp, buf[0x4C]: after g 25 (life 26 -> v0,
    IV -> v1, clamp i 80 -> a2), first 53, block-scoped around the loop 64 (31 with buf[0x50]).
  - ORIG test (rulings reused-local): the counter is homed at 148(sp) (`sw a3` 0xdafc, `lw a3` 0xdb00) but the clamp never is
    (0xdf08/0xdf0c/0xdf14 register only): stays FAKE.
- 2026-11-21 2026-11-21: continue unit 2 LeverArcade anthropic/claude-opus-5-5 (base fd085ca0, lever Q1590 exact tie / definition order):
  - uopt -l5 split (`s32 bonus` between g and buf, buf[0x4C]) 25: i (cand 26, bb 3-6) = IV (cand 34, bb 4-6) = adjsave 15.5,
    exact tie won by i (earlier bit) -> i v0, IV v1. Base: i bb 3-6 + 80-82, 11.33 < IV 15.5.
  - tie flipped by definition order: position local `x` initialised before the counter
    (`for (x = 0x360, i = 0; ...; i++, x += 0x20)`, buf[0x48]) 24: x (cand 26) and i (cand 29) both 15.5, x -> v0, but i -> v1
    (forbidden [1 3 4 5], no preference), bonus (cand 83) -> a2 (bb 82 pref 5), x homed 0x88(sp) instead of the uopt spill 0x34.
    `i = 0, x = 0x360` order 26.
  - dedicated bonus with an extra def before the IV: `bonus = 0;` before the loop + else arm 25 (dead def deleted = split);
    `bonus = 0;` before the loop, no else arm 15 (bonus uncoloured: `sw zero,0x8c(sp)` before the loop, `sw v0`/`lw a2,0x8c(sp)`).
  - `i = 0;` hoisted before dlSetTextureScaleAndFlip 28 (i homed 0x94 across the call).
  - sweep (plain/recipe) nohit; clint uninit 0 new; cwarn 0.
- 2026-11-24 2026-11-24: cleanup CleanarcadeDrawHudb anthropic/claude-opus-5-5 (base 24c8cb63, re-measure after the
  05c5a664 file-scope edits; body unchanged):
  - re-run, same numbers: u8 bonus buf[0x4C] 13, s32 bonus 25, life after g 25, x-first buf[0x48] 24, `bonus = 0;` no
    else 15, inline ternary buf[0x50] 29 / buf[0x4C] 66, block-scoped u8 buf[0x50] 15. Traces unchanged (now bits 27/35
    for i/IV; earlier notes 26/34): base IV v0 first, i a3; split exact 15.5 tie, i v0, IV v1, bonus a2.
  - new: variants.py scan of the u8 and s32 split copies (widths of i/bonus/n incl. int/u32/unsigned int, declswaps,
    truth/swap/branch/arith): best is the u8 baseline 13, no zero. Block-scoped u8/s32 bonus with buf[0x4C] 91/64,
    block-scoped int with buf[0x50] 31, `register s32` / `int` / `u32` bonus with buf[0x4C] 25.
  - permuter 900 s -j 2 (hack-free weights) from the u8 bonus + buf[0x4C] body: base 457, four zeros, every one puts the
    clamp back into i and fills the freed slot with a new steer (constant local, `&g` alias, volatile pad, `&gArcadeTexWidth`
    alias); best non-zero 136 also reuses i.
  - only 148(sp) stores in the function: the loop's `sw a3` 0xdafc (+ `lw` 0xdb00): stays FAKE.
- 2026-11-25c continue-lead-2 CleanarcadeUpdateOilDrumEntity anthropic/claude-opus-5-5 (base 9fb6f661): R-oildrum
  three-part census (director 2026-11-25c + refinements); bodies in census_hud/ (`bonus` = the clamp role), scores
  `variants.py try`, stack slots from `as1probe keep` t.s (census_hud/census_raw.txt). ORIG test (rulings.md:98-101):
  148(sp) holds only the counter (`sw a3` 0xdafc / `lw a3` 0xdb00); the clamp is register-only (0xdf08/0xdf0c/0xdf14): not ORIG.
## R-oildrum census (target R0: frame 152, counter i 148 (a3), g 144, n 59 (sb/lbu), IV uopt spill 52 (v0))
Part 1, frame proof (separate `bonus` local for the clamped timer; 5 widths x 5 positions x 2 buffer sizes + register):
| buf | positions (all widths s32/s8/u8/s16/u16 unless noted) | scores | stack vs target |
|---|---|---|---|
| 0x50 | first / after i | 87-117 | frame 152, counter or g home moves (144/140), n 59 -> 55, IV spill 52 -> 48 |
| 0x50 | after g | 59-91 | n 59 -> 55, IV spill 52 -> 48 |
| 0x50 | after buf | u8/u16 19, s32 31, s8/s16 52 | n 59 -> 55, IV spill 52 -> 48 |
| 0x50 | block (mode 5/4 block) | u8 15, u16 15, s32 31, s8/s16 52 | n 59 -> 58 (u8/s8) / 57 (halfwords) / 55 (s32), spill 52 or 48 |
| 0x50 | `register s32` after i / after g / block | 98 / 70 / 31 | n 59 -> 55, spill 52 -> 48 |
| 0x4C | after g | u8 13, u16 13, s32 25, reg 25, s8/s16 52 | IDENTICAL (frame 152, i 148, g 144, n 59, spill 52): colours only (counter v0, IV v1); s8/s16 add sign-extension code |
| 0x4C | after buf | u8/u16 53, s32 64, s8/s16 91 | IDENTICAL stack, colours/width code only |
| 0x4C | block | s32 64, reg 64; u8/u16/s8/s16 91-120 | s32/reg IDENTICAL stack; narrow: frame 152 -> 144 |
| 0x4C | first / after i | 41-78 | counter/g homes move (144/140) |
Result: FAILS. buf's 0x50 is m2c's size (longest string 22 chars); with buf[0x4C] a dedicated bonus local after g
(u8/u16/s32/register), after buf or block-scoped s32 keeps the frame and every home and spill; the reuse shows only in
the colouring (Q1256). Register-only evidence (R5 / 12E800 near ruling). If the director treats buf[0x50] as fixed, part 1
holds (every buf[0x50] position moves n or the IV spill), part 2 holds (below) and part 3 holds (counter loop 3921-3923
vs clamp 3995-4001 in the mode-5/4 block, disjoint, both int-valued: s8 gArcadeBonusTimer clamped, u8 life count bound).
Part 2, no-local: `_sprintf(buf, "%02d00", gArcadeBonusTimer > 0 ? gArcadeBonusTimer : 0)` 29 (buf 0x50) / 66 (0x4C);
`_sprintf` in each arm 23 / 101; `static s32 bonus` 16 / 94. All fail.
Hidden-reuse check (director item 2026-11-25c): no untagged unrelated-role reuse. `buf` holds every formatted HUD string
(one role, R9, no census); `g` (display-list cursor), block-scoped `u8 n` (stage count), `glistp` and `sFrameCount` hold
one role each; `i`'s second role is the tagged clamp (216e1c). None.
## Untried ideas
- none natural: the frame objection is gone (buf[0x4C]) and the colour-order tie can be flipped (Q1590/Q1551), but a3 for
  both the lives counter and the clamp comes only from one variable whose clamp web carries the `_sprintf` a2 preference
  while its loop web forbids a2; a dedicated counter has no preference (v1) and a dedicated clamp local takes a2.
## Evidence
- uopt_trace base: IV i*32+864 (cand 34) coloured v0 first, then var i (cand 26, M -4) a3. Inline ternary: i -> v0,
  IV -> v1, ternary temp (cand 80, M -100) -> a2.
- uopt_trace -l5 split: i 26 and IV 34 both adjsave 15.5 (tie -> i v0, IV v1, bonus 80 a2 forbidden [1 3 4], pref 5 at bb 82).
  Base i: forbidden [1 3 4 5], pref 5 (bb 82) -> a3; x_first i: forbidden [1 3 4 5], no pref -> v1.
- frame 152: i 148, g 144, buf 64-143, gDPSetScissor `_g` 60 (never stored), n 59 (`sb t6,59(sp)` 0xdf4c), uopt spill 52
  (IV `sw v0,52(sp)` 0xdaf4, n copy `sw t7,52(sp)` 0xdfbc), ra 44, outgoing args 16-36.
- lives loop: `move a3,zero` 0xdad4, `sw a3,148(sp)` in the jal delay slot 0xdafc, `lw a3,148(sp)` 0xdb00 (counter homed
  across dlAppendTextureRectangle), `addiu a3,a3,1` 0xdb10.
- clamp: `lb v0,gArcadeBonusTimer` 0xdef0, `blez v0` 0xdefc, `move a3,v0` 0xdf08, `move a3,zero` 0xdf0c, `move a2,a3` 0xdf14.
- target tail: `lui t7,%hi(D_8004A83C)` 0xe1f4, `lui at` 0xe1f8, `lw t7` 0xe200, `sw t8` 0xe214 (static sFrameCount).
