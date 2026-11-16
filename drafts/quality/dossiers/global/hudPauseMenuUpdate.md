# hudPauseMenuUpdate (global, src/global/ACDC0.c)

## Sites

global:806A8158:dead-if:a7bed8 dead-if: FIXED (HackhudPauseMenuUpdate2, merged with the ACDC0 .data carve): `sPauseSaveCooldown` is a function-local `static s8`; every access keeps its own lui/%lo pair, so the dead entry read is gone.
global:806A8158:dead-if:3a273f (older key of the same site).
global:806A8158:other:ceaa13 other: FIXED (HackhudPauseMenuUpdate3). `x = gGlobalOverlayFlags & 1` reused the stick local x (v0). Writing `(gGlobalOverlayFlags & 1)` in both tests gives the same code: uopt CSEs the lw at 0x89c and `andi t7,v0,1` at 0x8a4 into v0 (`move v0,t7` at 0x8ac).
global:806A8158:other:65898b other: KEPT FAKE (diagnose nohit). The map switch selector reuses i (a1): `move a1,v0` at 0xb8. A separate local grows the frame 0x58 -> 0x60.
global:806A8158:other:38b069 other: KEPT FAKE (diagnose nohit). The page switch selector reuses i (a1): `lb a1,18(s0)` at 0x61c (and 0x4d0/0x4e4); compares at 0x624-0x63c. A separate local grows the frame.
global:806A8158:other:df709b other: KEPT FAKE (diagnose nohit). The credits flag reuses i (a1): `sltiu a1,a0,1` at 0x814 and `sltu a1,zero,v0` at 0x82c. A separate local grows the frame.
global:806A8158:other:af58f9 other: KEPT FAKE (diagnose nohit). The carousel step reuses i (a1): `move a1,v1` at 0xc88; clamps at 0xca4/0xcd0. A separate local grows the frame.
global:806A8158:other:205ad7 other: KEPT FAKE (diagnose nohit). The step limit reuses flag (a0): `move a0,t5` at 0xc94. A separate local grows the frame.
global:806A8158:other:98a7ae other: KEPT FAKE (diagnose nohit). The half span reuses flag (a0): `sra t9,a0,1` / `move a0,t9` at 0xdbc/0xdc0. A separate local grows the frame.
Director ruling (2026-11-15): these six cannot be ORIG. ladder.md needs a store of the role value to the variable's own home slot, and none of the six has one. Only i's loop role stores to sp+0x50 (0x1a8/0x1fc); flag's home sp+0x48 is never stored.

## Attempts

2026-11-10..12 (low, medium): as1probe, permutes (self-assignment, *0 fold)
2026-11-14 HackhudPauseMenuUpdate opus-5-5:high: end respellings (29-34), snapshot locals (58-64), pointer local (48), mid test as !x / switch / <= 0 (29-30)
2026-11-14 PermBatch1114c opus-5-5:high: permbatch 900 s hack-free weights (nohit)
2026-11-15 HackhudPauseMenuUpdate2 anthropic/claude-opus-5-5:high: `static s8 sPauseSaveCooldown = 0;` at the top of the function, extern and dead read removed (fixed after the .data carve).
2026-11-15 HackhudPauseMenuUpdate2 review: dropped the redundant `(f64)` in the carouselProgress divisor (text words equal).
2026-11-15 PolishglobalACDC0Rereview: tagged the 7 register-reuse sites; a dedicated local per site, each alone -> nohit.
2026-11-15 HackhudPauseMenuUpdate3 HackhudPauseMenuUpdate3 anthropic/claude-opus-5-5:low (variants.py try full= scores):
- One dedicated local per site, each alone: map 47 (`switch (gCurrentMap)` 16), page 38 (`switch (hud->page)` 7; s32/s8/u8/s16, declared first or after i, all 38), credits 44, overlay 31, step 33, limit 50, half 42. Every dedicated local grows the frame 0x58 -> 0x60.
- Block-scoped step 33 and block-scoped credits 44: same frame growth.
- Overlay mask written out in both tests, no local: 0 -> fdiff OK (APPLIED).
- `?:` MIN/MAX steps using flag as the limit: 23. Limit inlined into the `?:`: 140. `(D_807FC83A >> 1)` at every use: 52.
- `i = hubWorld == 8 && menuGetTimerFlag() [!= 0]`: 16.
- stickY merged into x (frees one slot): 16 on its own; with a page local 19, a step local 14, a credits local 28.
- Reconstruct (all six role locals together, overlay fixed, Q0602): 84; with `?:` steps 109; also with the stick merge 117.

## Untried ideas

- A ladder rule that accepts frame capacity plus uopt_trace register identity as proof of an original reused local (queued for the lead as an IDO finding). Under that rule the six sites would be ORIG.

## Evidence

Frame 0x58: the 9 declared locals take sp+0x34..0x54 in declaration order. Homes in use: i sp+0x50 (0x1a8/0x1fc), diff sp+0x4c (0xd94), moved sp+0x44 (0x4a4), buttons sp+0x40 (0x4b4), hubWorld sp+0x38 (0x824/0x88c). The register-only locals are hud (s0), flag (a0), x (v0) and stickY (v1); their slots are sp+0x54, 0x48, 0x3c and 0x34. Below them, sp+0x28 holds the uopt loop temp v1. One more declared local (any scope, any width) makes the frame 0x60, which was measured for every role.
uopt_trace (-zdbug:6) candidate table: hud -4vreg = bit 0 -> reg 14 (s0); i -8vreg = bit 5 -> reg 4 (a1), unsplit; diff -12vreg = bit 355 -> reg 7 (t0); flag -16vreg = bit 170 -> reg 3 (a0); x -28vreg = bit 292 -> reg 1 (v0); hubWorld -32vreg = bit 239 -> reg 5 (a2); stickY -36vreg = bit 200 -> reg 2 (v1). moved (-20vreg) and buttons (-24vreg) are not coloured and live in their homes. Each variable is one live range and so gets one register. The a1 roles (loop counter, map selector, page selector, credits flag, step) are therefore one variable, and so are the a0 roles (page-change flag, step limit, stick flag, half span) (Q0162, Q0896).
0x260/0x264 `lui at` / `sb zero,%lo(sPauseSaveCooldown)(at)` (init), 0x798-0x7e8 cooldown test and `li t8,45` store, 0xf64-0xf8c decrement and clamp: every access has its own lui/%lo pair, as for a function-local static (Q0947).
Data order: ACDC0 file-scope data 0x807504E0-0x807505D4, then the statics sPauseSaveCooldown (hudPauseMenuUpdate), sTotalsPageIcons (hudPauseMenuBuildPage) and sOptionShades (hudDrawTwoOptionMenu).
