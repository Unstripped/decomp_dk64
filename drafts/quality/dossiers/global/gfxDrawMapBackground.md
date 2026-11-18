# gfxDrawMapBackground (global, src/global/109660.c)
## Sites
global:80707980:goto:u8a880 / u8a880#2 (`goto fill;` in cases 0xD0 / 0x36): KEPT, Q0591 shared tail (re-verified 2026-11-18 at b83aabe2 and again at 6b1eb78b on the current body, jump-table rows decoded).
## Attempts
- round 10 (opus): nested-switch fill colour (fdiff 1, +4 insns), permute (no zero).
- 2026-11-14 HackgfxDrawSkySprite (opus), variants.py try (lines off): if/else-if colour chain in the default arm 204; colour local with a sentinel-guarded fill block after the switch 322.
- 2026-11-15 HackgfxBuildScrollingBackground2 (anthropic/claude-opus-5-5:high), variants.py try (text rows): merged `case 0xD0: case 0x36: default:` group with the colour as a ternary chain on gCurrentMap 81; the same group with an inner switch on gCurrentMap selecting the colour 204.
- 2026-11-17 HackgfxDrawMapBackground, variants.py try (full rows): `s32 fill` flag set beside each in-arm `gDPSetFillColor` with the fill tail after the switch under `if (fill)` 267 (declared first or last alike); the fill tail written out in all three colour arms 351. Case 0x4/0xB0 merged into one group: 16 bytes short (the target keeps two copies).
- 2026-11-18 "2026-11-17: cleanup CleangfxDrawMapBackground" CleangfxDrawMapBackground (anthropic/claude-opus-5-5), variants.py try (full rows), session levers 3840/15050:
  - `u32 color` local feeding ONE `gDPSetFillColor(dl++, color)` at the fill label (colour arms `color = K; goto fill;`, default `color = 0x10001;`), case 0x50 kept between: 249; same with case 0x50 moved ahead of the colour arms (colour arms next to default): 253. Frame 0x40 -> 0x48 (homes 0x44/0x48/0x4c -> 0x4c/0x50/0x54), colour in t0 across the join (`li t0,-1` in the `b 0x38b4` slot), one `lui t9,0xf700` in the shared tail (15050: the shared block keeps its constants).
  - merged `case 0xD0: case 0x36: default:` ternary re-measured 81 (reload `lw v0,0(a0)` of gCurrentMap, `li at,0xd0; bne` and `li at,0x36; bne` inside the fill arm replace the two arms at 0x382C-0x3864; .text 15456 vs 15472 bytes); variants.py scan of it (53 recipes): best 81.
  - case 0x50 moved ahead of case 0xD0 with the in-arm stores and gotos unchanged: 36 (the 0x50 body leaves 0x3868 and is emitted first: source order = block order, Q0131/3840).
  - permute.py from the goto-free merged-ternary base (hack-free weights, -j 2, 900 s, 15755 iterations): base 3442, best 2930 (ternary sense flip + case 0x30 line join; the merged arm's compares stay), no zero.
  - review respellings: the 0x1E arm `(a || b || c) ? 1 : 0` argument as a bare `||`: 19 (Q0615, load-bearing, ordinary); `camIsCutsceneActive() != 0` bare: 0 (left as is).
- 2026-11-18 "2026-11-18: cleanup CleangfxDrawMapBackgroundb" CleangfxDrawMapBackgroundb (anthropic/claude-opus-5-5), variants.py try + fdiff exit 0 each, goto-free steer forms (never measured here before):
  - `if (0) { case 0x36: gDPSetFillColor(...); }` after the 0xD0 store, then ONE `goto fill;` shared by both colour arms: full=0 (the 0xD0 skip over the dead block lands on the goto and is threaded straight to the tail, `b 0x38f0` at 0x3840).
  - `if (0) { case 0x50: ...; break; default: gDPSetFillColor(dl++, 0x10001); }` after the 0x36 store, `fill:` kept for 0xD0: full=0.
  - both gotos as the two `if (0)` blocks above, no label: full=0.
  - `do { switch (gCurrentMap) { ... } fill tail } while (0);` with the 17 non-fill arm `break`s as `continue` and the colour arms `break`ing into the tail after the switch: full=0 (one shared tail, one exit: the single-level join Q1208 does not cover).
  - all are steers (Q0953/Q1209 Duff, AGENTS do-while(0)); Q1209: a matching Duff form is no evidence against keeping the goto. Both gotos stay goto-hand kept.
  - review re-measures: the 0x1E `(a || b || c) ? 1 : 0` argument as a bare `||`: 19 (load-bearing); `camIsCutsceneActive()` bare: 0 (left as is, ordinary either way).
## Untried ideas
none. Structural count: three in-arm colour prefixes (0x382C, 0x3848, 0x38D4) share one tail (0x38F0); only the arm textually before the tail can fall in, so two forward jumps are needed. `break` targets 0x39D0, which 22 other arm exits share (21 `b 0x39d0` + `beqz t6,0x39d0` at 0x31fc), so the tail cannot be the switch end. Every goto-free jump form is now measured: a second dispatch (compares/inner switch/flag test: Q1156 no threading, 81-351), `do {} while (0)` with continue (0, steer), Duff case labels in `if (0)` (0, steer). A colour local refuted (one F7000000 store instead of three); case order fixed by the target block order.
## Evidence
- Jump table `.rodata+0xac` indexed by gCurrentMap-3 (bound `sltiu 211`, out of range `beqz at,0x38d4` at 0x3098): `.rodata+0x3e0` 0xD0 -> 0x382C, `.rodata+0x178` 0x36 -> 0x3848, `.rodata+0x1e0` 0x50 -> 0x3868, default rows (e.g. `.rodata+0xb4` map 5) -> 0x38D4.
- 0x382C: case 0xD0 `move v0,s0; lui t5,0xf700; li t6,-1; sw t6,4(v0); sw t5,0(v0)`, then `b 0x38f0` at 0x3840 with `addiu s0,s0,8` in the slot.
- 0x3848: case 0x36 `move v0,s0; lui t8,0xffc1; ori t8; lui t7,0xf700; sw t7,0(v0); sw t8,4(v0)`, then `b 0x38f0` at 0x3860 with `addiu s0,s0,8` in the slot.
- 0x3868-0x38D0: case 0x50 (lensFlareAddFromAngle, gfxDrawBackgroundQuad, gfxDrawSkySprite), `b 0x39d0` at 0x38cc.
- 0x38D4: default `move v0,s0; lui t5,0x1; ori; lui t4,0xf700; sw t4,0(v0); sw t5,4(v0); addiu s0,s0,8` (0x38ec), falling into 0x38F0, the one copy of the fill tail (E200001C SetOtherMode 0x38F4-0x3908, E3000A01/0x300000 cycle type 0x3900-0x391c, FillRectangle from the player rect 0x3920-0x39b0, PipeSync 0x39bc/0x39c0, cycle type 0x39c4/0x39c8), falling into the common exit 0x39D0 (gBackgroundBlend = 0, PipeSync, return).
- Fill-flag variant: flag homed at sp+0x3C (frame 0x40 -> 0x50), `sw zero,0x3c(sp)` before the switch, `li t8,1; sw t8,0x3c(sp)` in each colour arm, every arm branches to the post-switch test at 0x38F8.
