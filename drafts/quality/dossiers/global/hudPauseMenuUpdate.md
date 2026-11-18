# hudPauseMenuUpdate (global, src/global/ACDC0.c)

## Sites

global:806A8158:dead-if:a7bed8 dead-if: FIXED (HackhudPauseMenuUpdate2, merged with the ACDC0 .data carve): `sPauseSaveCooldown` is a function-local `static s8`; every access keeps its own lui/%lo pair, so the dead entry read is gone.
global:806A8158:dead-if:3a273f (older key of the same site).
global:806A8158:other:ceaa13 other: FIXED (HackhudPauseMenuUpdate3). `x = gGlobalOverlayFlags & 1` reused the stick local x (v0). Writing `(gGlobalOverlayFlags & 1)` in both tests gives the same code: uopt CSEs the lw at 0x89c and `andi t7,v0,1` at 0x8a4 into v0 (`move v0,t7` at 0x8ac).
global:806A8158:other:af58f9 other: FIXED (HackhudPauseMenuUpdate4). `s8 x; s8 stickY;` declared adjacent share sp+0x3c (Q0361/Q0479), which frees sp+0x34 for a dedicated `s32 step;` declared last. Frame 0x58, spill temp sp+0x28, and uopt colours step a1 (bit 353 -> reg 4). Whole-object fdiff OK.
global:806A8158:other:65898b other: FIXED (CleanhudPauseMenuUpdate, 2026-11-17f). The map switch selector reused the loop index i (a1, `move a1,v0` at 0xb8). Frame census: the nested `hudFindLevelSlot(mapGetHubWorldIndex(...))` result was a cfe hidden temp (-41vreg, u8, word sp+0x2c). `hubWorld = mapGetHubWorldIndex(gCurrentWorldId, 1); hud->worldIndex[0] = hudFindLevelSlot(hubWorld);` drops it, and the freed word takes `s32 sel;` declared last (sp+0x30, register-only). i is now the loop index only; `sel = gCurrentMap; switch (sel)` is a selector local at its use. sel also holds the page selector and the credits flag, and uopt colours it a1 (bit 5, forbidden v0 v1 a0 t0 t1). Whole-object fdiff OK.
global:806A8158:other:c127b7 other (was 38b069): KEPT FAKE (diagnose nohit). `sel = hud->page` makes the page switch selector reuse the map selector sel (a1, `lb a1,18(s0)` at 0x61c and the branch-likely delay slots 0x4d0/0x4e4). A dedicated page local is coloured v0 (Q1200), and as an s32 it grows the frame now that sel holds the freed word (38). Open question for the lead: one selector local used for both switch selectors may count as the same role ("a selector local at its use").
global:806A8158:other:db430c other (was df709b): KEPT FAKE (diagnose nohit). `sel = hubWorld == 8` makes the credits flag reuse sel (a1: `sltiu a1,a0,1` at 0x814 and `sltu a1,zero,v0` at 0x82c). A dedicated s32 credits local grows the frame (67). In the free word without sel it keeps 0x58 but swaps a1/a2 with hubWorld (16). s8/u8 add narrowing (194/202, Q1199).
global:806A8158:other:6151e7 other: KEPT FAKE (diagnose nohit). The step limit reuses flag (a0, `move a0,t5` at 0xc94). In the free word, a dedicated limit keeps 0x58 but the flag bools colour v1 instead of a0 (19). With sel in the word it grows the frame (50).
global:806A8158:other:32c920 other: KEPT FAKE (diagnose nohit). The half span reuses flag (a0, `sra t9,a0,1` / `move a0,t9` at 0xdbc/0xdc0). In the free word a dedicated half is coloured v0 (11). With sel in the word it grows the frame (42).
Director ruling (2026-11-15): the remaining sites cannot be ORIG. ladder.md needs a store of the role value to the variable's own home slot, and none of them has one.

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
2026-11-17f CleanhudPauseMenuUpdate anthropic/claude-opus-5-5 (base 7c91e3e9, variants.py try full=):
- Frame census (`uopt_trace -l 5`, `isvar M`): named homes -4..-36vreg (9 words), one cfe switch temp -40vreg (sp+0x30) shared by both switches, and the nested mapGetHubWorldIndex result temp -41vreg (u8, word sp+0x2c). The chained stores at 230 and 413 make no temp.
- Un-nest through hubWorld (same hub-index quantity as at 0x810): 4 alone (the spill moves to sp+0x2c). The word is freed.
- Un-nest plus one s32 role local declared last: map 16, page 7, credits 16, limit 19, half 11 (frame 0x58 kept: colouring only). s8 page in the word 11, `switch (hud->page)` 11, `switch (gCurrentMap)` 20. Scores add up role by role (119 combinations of last32/word8/word16/nolocal/inline, best 7).
- One s32 local for several roles, in the freed word: sel = map+page+credits with i loop-only 0 (fdiff OK, APPLIED). sel = page+credits 0, sel = map+credits 0, sel = map+page 23, span = limit+half 8 (the flag bools move a0 -> v1). A separate loop index j with i keeping map/page/credits 4 (j home sp+0x30 instead of 0x50).
- On the sel shape: page s32 38, s8 page in the word 7, `switch (hud->page)` 7; credits s32 67, s8/u8 in the word 194/202, credits in flag 52/36/45; limit s32 50, s16 in the word 88, inlined 130; half s32 42, s16 in the word 41, inlined 52; sel+span 39; all five dedicated 82.
- variants scan of the final copy: swaps, float suffixes, x/stickY as s16, and the step/sel declswap are neutral zeros. Nothing needed.

## Untried ideas

- A lead ruling on whether one selector local used for both switch selectors is the same role (SKILL 5.6 "a selector local at its use"). That would make c127b7 ordinary C.
- No further frame word is left: the census shows 10 named words, the switch temp, and the spill temp at capacity. The flag-side roles are colour-bound even with a free word (span 8: flag is a0 only while its range covers the limit region).

## Evidence

Frame 0x58 (final): hud sp+0x54 (s0, register-only), i sp+0x50 (loop index, 0x1a8/0x1fc), diff sp+0x4c (0xd94), flag sp+0x48 (register-only), moved sp+0x44 (0x4a4), buttons sp+0x40 (0x4b4), s8 x and s8 stickY packed into sp+0x3c (register-only), hubWorld sp+0x38 (0x824/0x88c), step sp+0x34 (register-only), sel sp+0x30 (register-only), cfe switch temp -44vreg sp+0x2c, uopt spill temp sp+0x28.
Base census (`uopt_trace -l 5`): bit 9 `{1024|0} isvar M -40vreg` is the switch temp (bit 11 `ustr{1024}{1536}` copies i; compares at bits 14-21 for the map switch and 192-197 for the page switch). Bit 85 `{1008|0} isvar M -41vreg` is the nested call result (bit 87 `ustr{1008}{1485}` from v0). The target passes it as `sll a0,v0,0x18; sra t3,a0,0x18; move a0,t3` at 0x324-0x330. The un-nested hubWorld form compiles to the same words.
Final colouring (`uopt_trace -l 5/6`): i (bit 38) is forbidden [v0 a0 a2] and still gets a1 (reg 4) first. That is the arg-2 preference of textTableGetString (Q0162). sel (bit 5) is forbidden [v0 v1 a0 t0 t1] and gets a1. hubWorld (bit 87) gets a2. A single split-off role is forbidden fewer registers and gets v0 (page, half) or swaps with hubWorld (credits).
0x260/0x264 `lui at` / `sb zero,%lo(sPauseSaveCooldown)(at)` (init), 0x798-0x7e8 cooldown test and `li t8,45` store, 0xf64-0xf8c decrement and clamp: every access has its own lui/%lo pair, as for a function-local static (Q0947).
Data order: ACDC0 file-scope data 0x807504E0-0x807505D4, then the statics sPauseSaveCooldown (hudPauseMenuUpdate), sTotalsPageIcons (hudPauseMenuBuildPage) and sOptionShades (hudDrawTwoOptionMenu).
