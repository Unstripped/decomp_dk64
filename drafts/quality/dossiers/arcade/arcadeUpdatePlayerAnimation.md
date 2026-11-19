# arcadeUpdatePlayerAnimation (arcade, src/arcade/0.c)
## Sites
- arcade:8002B390:dead-if:edb3d1 (was 104665; re-keyed by the gArcadeGameOver rename) (kept): removal 5 (&D_8004A764 address web {513|0} takes v0 instead of v1 at 0x7684/0x7694/0x769c/0x76f4/0x770c). Mechanism (2026-11-18 trace): the guard is bb1-bb3 of the state == 2 arm; its two reads of D_8004A764 are one CSE candidate (uilod{513}, lr 24, reg 1 = v0) and put bb1 into the address web (lr 182 = bb1, bb63, bb64), so the web interferes with that value and gets forbidden [1 4 5 7 17 18] -> reg 2 (v1). Removed, the web is bb60/bb61 only (forbidden [17 18], neighbours 113 col / 180 &D_8004BCD0 / 215 const 1) -> lowest free reg 1 (v0).
  2026-11-18 (CleanarcadeDrawStage3Background): sweep classify class 2 (same-value lever); no real use of D_8004A764 in the
  state == 2 arm (target 0x7404-0x740c), so the `x && x` test stays `// FAKE`.
## Attempts
- 2026-11-14 opus:high: switch / inverted 76; u32 snapshot 5; D_8004A764 snapshot 50.
- 2026-11-17 2026-11-17: cleanup HackarcadeDrawStage4Background2 HackarcadeDrawStage4Background2 anthropic/claude-opus-5-5: `ArcadeEntity *ent` pointer local for every `D_8004BCD0[entIndex]` 158; state 8 inverted (`if (D_8004C71B != 0)` first, else-if 48.0f, else-if D_8004A764 == 0) 37; return-free if/else-if chain 7; `else if (D_8004A764 == 0)` 5; bare `!D_8004C71B` / `!D_8004A764` 5; variants scan of the removed form (55) best 5. Casts: `(f64)` on animTimer / 4.5, five `(f32)` int-to-float and the `(s32)` on val are not needed (fdiff 0): dropped; `val & 1` / `val & 3` instead of re-truncating animTimer 136.
- 2026-11-18 2026-11-17: cleanup CleanarcadeUpdatePlayerAnimation CleanarcadeUpdatePlayerAnimation anthropic/claude-opus-5-5: `u8 *spawned = &D_8004A764` for both accesses (Q1154, in the C71B == 0 arm or at the top) 51 (copy-propagated to direct ulod/ustr of the symbol: `lbu t8,%lo(D_8004A764)(t8)`, `sb t9,%lo(D_8004A764)(at)`, no address web); spawn loops as do-while 5, outer while with init in the if 5; spawn-loop `ArcadeEntity *ent = &D_8004BCD0[slot]` 5; `switch (state)` for the 2/3/5/8 chain 160; hand classify (Q0908) of the guard: `if (1) {}`, `if (val && val) {}`, `if (b && b) {}`, `if (D_8004C710 && D_8004C710) {}`, single `if (D_8004A764) {}`, `if (D_8004A764 == 0) {}`, `(void)D_8004A764;` all 5; variants scan of the removed form best 5; permuter 900 s -j 2 hack-free from the removed form: base 30, best 0 only via `if (!D_8004C6E4 && !D_8004C6E4) {}` before `D_8004A764 = 1` (a dead guard moved onto another global, variants try full=0, not kept).
- 2026-11-18 2026-11-18: cleanup CleanarcadeDrawStage3Background CleanarcadeDrawStage3Background anthropic/claude-opus-5-5 (base 2291c741):
  - real-use search in the state == 2 arm (brief: look for the real D_8004A764 read): the target arm 0x7404-0x740c holds only
    `lui v0 / lw v0,%lo(D_8004C710)` and its test; D_8004A764 relocates only at 0x7684/0x7694; any real read, compare or
    store there emits code, so the only codeless spellings are empty tests (no ugen record: C0EE0 2026-11-18; dropped after
    colouring: 13980), which are steers. No real use exists.
  - `D_8004A764++` in place of `D_8004A764 = 1`: 51. uopt -l5: the read becomes a two-use value (uilod{513} lr 108,
    uadd{1458}{1}) in bb60/61, coloured reg 1 (v0: `lbu v0,0(v1)` at 0x769c/0x76f4), so the web {513|0} lr 215 gets
    forbidden [1 17 18] -> reg 2 (v1, the target 0x7684/0x7694/0x770c), but the store needs `addiu t8,v0,1` (0x7704)
    instead of `li t9,1` (0x76f8). Confirms the lever: one two-use D_8004A764 value inside the web; a real second use costs code.
  - early-return spawn (`if (D_8004A764 != 0) { return; }` then the unguarded spawn loop): 5, codegen identical to the removal.
  - permuter 900 s -j 2 (hack-free weights) from the `D_8004A764++` body: base 455, best 295 only via a dead
    `if (!entIndex && !entIndex && !entIndex) {}` at the top of the state 8 arm (a dead guard: steer), no zero.
  - review: locals renamed val -> frame (the truncated animTimer that selects the frame), b -> dirBit (facing bit 1 copied
    to bit 0); redundant parentheses dropped in the state-5 test: fdiff 0.
- 2026-11-19 2026-11-18c: cleanup CleanarcadeDrawStage3Backgroundb CleanarcadeDrawStage3Backgroundb anthropic/claude-opus-5-5 (base a3d0ef71, renamed body):
  - re-run: removal 5, single `if (gArcadeGameOver) {}` 5, `if (gArcadeGameOver == 0) {}` 5: count-sensitive here (unlike the
    3E10 same-value read). uopt -l6: base web {513|0} lr 182 reg 2 (v1) beside guard value uilod{513} lr 24 reg 1 (v0); removed
    lr 214 reg 1; single lr 182 reg 1 (one read is no CSE candidate).
  - NEW: `u8 lives = gArcadeSpareLives` with `gArcadeSpareLives = lives - 1` 11 (block-scoped 11), `s32 lives` 5 (target keeps
    `lbu v0,0(v1)` 0x7670 / `addiu t4,v0,-1` 0x767c); `u8 over = gArcadeGameOver` read before the `> 48.0f` test 61 (extra lbu).
    variants scan of the removed form best 5.
## Untried ideas
- none from the local asm: in the target every v0 (reg 1) candidate lives in bb0 (dirBit), bb1-2 (D_8004C710 value), the frame & 3 switch blocks, bb77-79 or bb80. The removed web (bb60/bb61) shows no v0, bb61 leads into the call loop and nothing after the loop (bb68/bb70/epilogue at 0x7878) reads v0, so no live-through v0 value can reach it; the web cannot include bb50/bb69 either (&D_8004C71B shares v1 there). Only a construct that emits no code and still holds v0 inside the web gives v1: a dead `D_8004A764 && D_8004A764` read in a v0 block (extends the web) or any dead two-use read inside bb60/bb61 (the 2026-11-18 permuter zero: `if (!D_8004C6E4 && !D_8004C6E4) {}` before `D_8004A764 = 1`); a real two-use read (`D_8004A764++`) costs an add. The FAKE stays unless the real source of such a dead read turns up.
## Evidence
- target: `lui v1,%hi(D_8004A764)` 0x7684, `addiu v1,v1,%lo` 0x7694 (v1 held &D_8004C71B from 0x7658, used 0x7670 and 0x77a4), `lbu t8,0(v1)` 0x769c/0x76f4, `sb t9,0(v1)` 0x770c; no D_8004A764 reloc anywhere else in the function; no v0 use between 0x767c and the jal at 0x7720.
- trace (-l 5, 2026-11-18): base web {513|0} lr 182 bbs [1, 63, 64] forbidden [1 4 5 7 17 18] reg 2, guard value uilod{513} lr 24 bbs [1, 2] reg 1; removed: lr 214 bbs [60, 61] forbidden [17 18] reg 1; &D_8004C71B {391|0} lr 209 bbs [50, 69] forbidden [1 17] (D_8004C71B value lr 93 in v0) reg 2. Coloring picks the lowest non-forbidden register (Q0523: ranges sharing no block never interfere).
- single-term guard trace (2026-11-18): `if (D_8004A764) {}` keeps bb1 in the web (lr 182 bbs [1, 62, 63]) but its value is no candidate (single use), forbidden [4 5 7 17 18] -> reg 1 (v0), full=5.
