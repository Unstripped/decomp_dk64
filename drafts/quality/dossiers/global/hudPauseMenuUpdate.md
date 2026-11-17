# hudPauseMenuUpdate (global, src/global/ACDC0.c)

## Sites

global:806A8158:dead-if:a7bed8 dead-if: FIXED (HackhudPauseMenuUpdate2, merged with the ACDC0 .data carve): `sPauseSaveCooldown` is a function-local `static s8`; every access keeps its own lui/%lo pair, so the dead entry read is gone.
global:806A8158:dead-if:3a273f (older key of the same site).
global:806A8158:other:ceaa13 other: FIXED (HackhudPauseMenuUpdate3). `x = gGlobalOverlayFlags & 1` reused the stick local x (v0). Writing `(gGlobalOverlayFlags & 1)` in both tests gives the same code: uopt CSEs the lw at 0x89c and `andi t7,v0,1` at 0x8a4 into v0 (`move v0,t7` at 0x8ac).
global:806A8158:other:65898b other: KEPT FAKE (diagnose nohit). The map switch selector reuses i (a1): `move a1,v0` at 0xb8. A separate s32 local grows the frame 0x58 -> 0x60 (47). `switch (gCurrentMap)` keeps 0x58 but colours the selector v0 (16). A u8 map in the packed x/stickY word adds an andi (17).
global:806A8158:other:38b069 other: KEPT FAKE (diagnose nohit). The page switch selector reuses i (a1): `lb a1,18(s0)` at 0x61c (and 0x4d0/0x4e4); compares at 0x624-0x63c. An s8 page in the packed x/stickY word keeps frame 0x58 and every home but is coloured v0 (7); it stays v0 even when credits is split out of i.
global:806A8158:other:df709b other: KEPT FAKE (diagnose nohit). The credits flag reuses i (a1): `sltiu a1,a0,1` at 0x814 and `sltu a1,zero,v0` at 0x82c. An s8/u8 credits local adds sll/sra 0x18 narrowing (171/170). An s32 credits local grows the frame, because step holds the freed word (44).
global:806A8158:other:af58f9 other: FIXED (HackhudPauseMenuUpdate4). `s8 x; s8 stickY;` declared adjacent share sp+0x3c (Q0361/Q0479), which frees sp+0x34 for a dedicated `s32 step;` declared last. Frame 0x58, spill temp sp+0x28, and uopt colours step a1 (bit 353 -> reg 4). Whole-object fdiff OK.
global:806A8158:other:205ad7 other: KEPT FAKE (diagnose nohit). The step limit reuses flag (a0): `move a0,t5` at 0xc94. An s32 limit local grows the frame (50). A u16 step packed into the x/stickY word to free a word scores 35.
global:806A8158:other:98a7ae other: KEPT FAKE (diagnose nohit). The half span reuses flag (a0): `sra t9,a0,1` / `move a0,t9` at 0xdbc/0xdc0. An s32 half local grows the frame (42); with a u16 step packed into the x/stickY word it scores 35.
Director ruling (2026-11-15): the remaining five cannot be ORIG. ladder.md needs a store of the role value to the variable's own home slot, and none of the five has one. Only i's loop role stores to sp+0x50 (0x1a8/0x1fc); flag's home sp+0x48 is never stored.

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
2026-11-17 HackhudPauseMenuUpdate4 anthropic/claude-opus-5-5 (variants.py try full=). New shape: `s8 x; s8 stickY;` packed at sp+0x3c (Q0361), which frees sp+0x34:
- The packing alone scores 4: the spill temp moves from sp+0x28 to 0x2c, because only 8 words are left.
- Packing plus one s32 role local declared last: step 0 (fdiff OK, APPLIED), half 11, page 7, credits 16, map 16, limit 19.
- On the step-fixed shape, with narrow roles in the x/stickY word: s8 page 7 (v0 instead of a1), u8 page 7, page first in the word 7, s8/u8 credits 171/170 (sll/sra narrowing), s8 page+credits 178, u8 map 17, s16 map 359.
- On the step-fixed shape, with a role declared last (frame 0x60): page 38, credits 44, map 47, limit 50, half 42, limit+half 46, page+credits 51 (page still v0).
- A narrow step to free a word: u16 step in the word plus s32 credits/page/map/limit/half 51/42/51/35/35, and s16 step 128/119/128/112/112.
- `switch (gCurrentMap)` on the step-fixed shape: 16, and 23 with an s8 page in the word.
- Reconstruct (all roles: x/stickY/page in one word, plus step/map/credits/limit/half): 82; with `switch (gCurrentMap)` 86.
- Review: the `(f32)` on diff in the carouselProgress division was redundant (0, applied).

## Untried ideas

- A ladder rule that accepts frame capacity plus uopt_trace register identity as proof of an original reused local (queued for the lead as an IDO finding). Under that rule the six sites would be ORIG.

## Evidence

Frame 0x58 (after HackhudPauseMenuUpdate4): hud sp+0x54, i sp+0x50 (0x1a8/0x1fc), diff sp+0x4c (0xd94), flag sp+0x48, moved sp+0x44 (0x4a4), buttons sp+0x40 (0x4b4), s8 x and s8 stickY packed into sp+0x3c (register-only), hubWorld sp+0x38 (0x824/0x88c), step sp+0x34 (register-only). The uopt spill temp sits 3 words below the lowest named local, at sp+0x28 (Q0361). With the 9th word dropped it moves to sp+0x2c, and a 10th word makes the frame 0x60. Any further role local therefore needs a byte in the x/stickY word, and only s8 page fits there without sign-extension code.
uopt_trace (-zdbug:6) on the current copy: hud -4vreg bit 0 -> reg 14 (s0); i -8vreg bit 5 -> reg 4 (a1); diff -12vreg bit 357 -> reg 7 (t0); flag -16vreg bit 170 -> reg 3 (a0); x -25vreg bit 292 -> reg 1 (v0); stickY -26vreg bit 200 -> reg 2 (v1); hubWorld -32vreg bit 239 -> reg 5 (a2); step -36vreg bit 353 -> reg 4 (a1). moved (-20vreg) and buttons (-24vreg) are not coloured. An s8 page in the packed word (-27vreg, bit 189) is coloured reg 1 (v0) before i is reached. In the target, the hud->page loads at 0x4d0 and 0x4e4 (the `hud->page == 0` tests, where i is not used) also go to a1. Inference: the hud->page value is shared with i's register there. The remaining a1 roles (loop counter, map selector, page selector, credits flag) are one variable, and so are the a0 roles (page-change flag, step limit, stick flag, half span) (Q0162, Q0896).
0x260/0x264 `lui at` / `sb zero,%lo(sPauseSaveCooldown)(at)` (init), 0x798-0x7e8 cooldown test and `li t8,45` store, 0xf64-0xf8c decrement and clamp: every access has its own lui/%lo pair, as for a function-local static (Q0947).
Data order: ACDC0 file-scope data 0x807504E0-0x807505D4, then the statics sPauseSaveCooldown (hudPauseMenuUpdate), sTotalsPageIcons (hudPauseMenuBuildPage) and sOptionShades (hudDrawTwoOptionMenu).
