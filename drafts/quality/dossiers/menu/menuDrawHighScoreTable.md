# menuDrawHighScoreTable (menu, src/menu/3E10.c)

## Sites
menu:8002F284:other:9c13a4 other: `i = 0;` reuses the s16 loop counter `i` as the message-drawn flag. The one candidate (uopt bit 25, -228vreg) is coloured s2 for both roles, so the flag lives in a callee-saved register although none of its values crosses a call. The test `i != 0` is the candidate expression bit 40 (`uneq`) in v0 (`sltu v0,zero,s2` 0x761c), and the loop init `move s2,zero` sits in the `beqz` delay slot (0x7628).

## Attempts
2026-11-09..2026-11-18 (59 events, see `quality.py history menuDrawHighScoreTable`): separate showMsg/hasMsg/drawn flag (s32 in the pad slot, s32/s16 after i, s16 in place, in the pad slot) fdiff 1 / frame 0x148 -> 0x150, s-register rotation; permuter best=0 only by reverting to the i reuse (Q0634); retypes for the cfe warnings fixed.
2026-11-19 2026-11-18c: cleanup CleanmenuDrawHighScoreTable CleanmenuDrawHighScoreTable anthropic/claude-opus-5-5:xhigh: re-run on the 8ec6522c body. sweep: plain/recipe nohit (no rewrite/no removal). uopt -l6 base and split traces; variants.py try:
- split flag, set after the calls (target order): s16/s32/u8 in the pad slot, bare or `!= 0` test -> 62; first or after `state` without pad -> 65; after i / before yPos with pad -> 71, without -> 66. Flag takes v1 (`move v1,zero`, `li v1,1`, `beqz v1`, no `sltu`), i rises to s1, dl drops to s2.
- split flag set before each `_sprintf` -> 44 (49-56 other slots); the same order with i reused -> 41 (the target sets after the call).
- split flag initialised before the 2nd menuComputeElementPosition, before the 1st, after the state load, or as a declaration initialiser -> 37: the flag crosses a call and takes s0, but `move s0,zero` lands before jal 0x758c (target `move s2,zero` 0x75b4 after it).
- variants.py scan (swaps, floats, widths, declswaps) around the 62 and 37 bodies: no zero, best = baseline.
- base with bare `if (i)` -> 0 (neutral; not applied, the reuse stays).

## Untried ideas
none with a natural-C route: every split puts the call-free flag in a caller-saved register (Q0543) or moves its init across a call; only one candidate spanning both roles gives s2 (Q1055).

## Evidence
- 0x758c `jal menuComputeElementPosition` (2nd), then 0x75b4 `move s2,zero` (flag = 0), 0x75b0 `lb v1,sMenuHighScoreEditRow`, 0x75d4 `bltz v1`.
- 0x75e4 `jal _sprintf`, 0x75ec `b 0x761c`, 0x75f0 `li s2,1` (delay slot); 0x7610 `jal _sprintf`, 0x7618 `li s2,1`.
- 0x761c `sltu v0,zero,s2`, 0x7624 `beqz v0,0x7654`, 0x7628 `move s2,zero` (loop init in the delay slot).
- loop: 0x76fc `addiu s5,s2,1` (i + 1 for "%d." and the increment), 0x7864 `sll s2,s5,16` / 0x7878 `move s2,t2`, frame 0x148 with s0-s8 all saved (no free callee-saved register for a separate call-crossing flag).
