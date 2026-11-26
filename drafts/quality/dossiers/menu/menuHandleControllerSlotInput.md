# menuHandleControllerSlotInput (menu, src/menu/3E10_screens.c)

## Sites
(none left after this round; base keys below were the four recomputed-press FAKEs)
- menu:8002ADC8:other:0ecac8 (other): -0xF0 arm `& 0x10` test, `andi t6,v0,0x10` @0x3660 reads the v0 CSE of `(buttons ^ D_80033858) & buttons` (uopt cand 133); `pressed` is cand 129 in s0 (`move s0,v0` @0x336c), live only to the `menuHandleScrollInput` arg (`move a2,s0` @0x371c). Removed.
- menu:8002ADC8:other:1f5e46 (other): -0xF0 arm `& 0x20` test, `andi t7,v0,0x20` @0x3668. Removed.
- menu:8002ADC8:other:0ecac8#2 (other): -0x1E0 arm `& 0x10` test, `andi t9,v0,0x10` @0x3730. Removed.
- menu:8002ADC8:other:35826e (other): -0x1E0 arm `& 0x20` test, `andi t7,v0,0x20` @0x3738. Removed.

## Attempts
- 2026-11-13 r34 Rev34B (opus xhigh): sweep plain/no rewrite; uopt_trace -l5/-l6: tests read cand 133 v0; permuter best=0 only re-inserts the re-spelled test.
- 2026-11-13 r34 Rev34C (opus medium): -zdbug5: pressed cand 129 s0; naming pressed at any test joins the s0 web, `andi tX,s0` full=1 each; reconstruct: one pressed local at all tests full=6, no local (E at call too) 312; permuter re-inserts FAKE.
- 2026-11-13 r35 CleanMenu3E10 (opus xhigh): trace cs_base; per-site permuter from pressed variants: no output below base 5; reconstruct: every arm on pressed full=6, newPress local per unkC arm full=14, pressed assigned per arm full=220, edge reused per arm full=304.
- 2026-11-13 r37 CleanMenu3E10: permuter on 35826e best=0; reconstruct natural rewrites leave cand 133 uncoloured.
- 2026-11-14/15 PolishMenu3E10Names, RereviewSmallFiles2: reviews; three `1.0` (double) sfx speed args as `1.0f` full=5 / shift .rodata: kept.
- 2026-11-16 HackmenuHandleControllerSlotInput (opus-5-5): file-scope function-like macro `BUTTONS_PRESSED(cur, prev) (((cur) ^ (prev)) & (cur))` used at every new-press computation in the function: `pressed`, the per-pad `edge` (`BUTTONS_PRESSED(bits, D_8003385C[i])`, xor operand order irrelevant), and the four arm tests -> fdiff OK, 4 FAKEs removed. Also checked: splitting `bits` (1<<j mask vs stick bits) into a separate `bit` local differs only by the t0 spill slot 0x44 -> 0x40 (one extra home, any declaration position) -> bits reuse is natural, untagged.
- 2026-11-25c CleanmenuUpdateElementTargetAndColor (opus-5-5, follow-up, base 86d04c61): R-oildrum three-part census on the untagged `bits` reuse (Q1122). Part 1 holds for s32 `bit` (the `1 << j` role) at every position: before state 31 (state home 132->128), after state/step/rest/i/j/edge/bits/idx 10 (itemCount home 100->96 plus t0 spill 0x44->0x40), after itemCount/cap/lim/mask/pressed 6 (t0 spill 0x44->0x40 at 0x34b0/0x3518/0x3544); `register s32` the same (31/10/6 at before state/after bits/after pressed); block scope in the if block, the for body, or as the for-body initialiser 6. `u8 bit` beside `u8 mask` packs into mask's word (shape 0) but recolours (257, sllv t5->t6 from 0x3148). Part 2 FAILS: `mask |= 1 << j;` with no local fdiffs 0. Part 3 holds (both s32; j loop base 1159-1167 vs i loop base 1203-1217). Result: hidden steer removed, `bits` keeps only the stick-bit role; Q1122 refuted (the split's frame move is real, but the role never needed a local).

## Untried ideas
- (none needed for this function)

## Evidence
- Target: `lw t7,D_80033858; xor t9,t4,t7; and v0,t9,t4` @0x334c-0x3360, `move s0,v0` @0x336c (pressed copy, s0 shared with loop counter i: `move s0,zero` @0x3380), arm tests `andi tX,v0,…` @0x3660/0x3668/0x3730/0x3738, `move a2,s0` @0x371c.
- Q0716 (re-spelled pure expression is its own v0 CSE candidate); guide ido-levers-revisit-7 MenuB note (re-spelled E at each test was the 0-FAKE match).
