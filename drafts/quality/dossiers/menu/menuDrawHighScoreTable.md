# menuDrawHighScoreTable (menu, src/menu/3E10_screens.c)

## Sites
menu:8002F284:other:9c13a4 other: `i = 0;` reuses the s16 loop counter `i` as the message-drawn flag. The one candidate (uopt bit 25, -228vreg) is coloured s2 for both roles, so the flag lives in a callee-saved register although none of its values crosses a call. The test `i != 0` is the candidate expression bit 40 (`uneq`) in v0 (`sltu v0,zero,s2` 0x761c), and the loop init `move s2,zero` sits in the `beqz` delay slot (0x7628).

## Attempts
2026-11-09..2026-11-18 (59 events, see `quality.py history menuDrawHighScoreTable`): separate showMsg/hasMsg/drawn flag (s32 in the pad slot, s32/s16 after i, s16 in place, in the pad slot) fdiff 1 / frame 0x148 -> 0x150, s-register rotation; permuter best=0 only by reverting to the i reuse (Q0634); retypes for the cfe warnings fixed.
2026-11-19 2026-11-18c CleanmenuDrawHighScoreTable: split flag set after the calls 62-71 (flag v1, i s1, dl s2); set before each `_sprintf` 44; initialised before a call 37 (s0, init before jal 0x758c); variants.py scan no zero; bare `if (i)` 0 (neutral, not applied).
2026-11-25c CleanmenuUpdateElementTargetAndColor anthropic/claude-opus-5-5: lead levers checked on the target. Q1646 precondition holds (one local holds a call-free 0/1 flag and the range-limited loop counter) and predicts the measured split result: the counter keeps s2, the flag drops to v1. Q1623/Q1630/Q1635 (`flag = a && b;`) precondition fails: the target sets the flag by constant stores on the two `_sprintf` paths (`li s2,1` 0x75f0, 0x7618), never as a value of the row compares (`bltz v1` 0x75d4, `bne v1,at` 0x75f4 each guard one call). Measured anyway in the pad slot: `drawn = row >= 0 || row == -2;` before the calls 61 (shape 35); `drawn = row >= 0; if (drawn) ... else if (row == -2) { ...; drawn = 1; }` 39 (shape 13). Q1596 (definition-order tie) needs both webs to compete for one register; the call-free flag never competes for a callee-saved one.

## Untried ideas
none with a natural-C route: every split puts the call-free flag in a caller-saved register (Q1566, Q1646) or moves its init across a call; only one candidate spanning both roles gives s2 (Q1055).

## Evidence
- 0x758c `jal menuComputeElementPosition` (2nd), then 0x75b4 `move s2,zero` (flag = 0), 0x75b0 `lb v1,sMenuHighScoreEditRow`, 0x75d4 `bltz v1`.
- 0x75e4 `jal _sprintf`, 0x75ec `b 0x761c`, 0x75f0 `li s2,1` (delay slot); 0x7610 `jal _sprintf`, 0x7618 `li s2,1`.
- 0x761c `sltu v0,zero,s2`, 0x7624 `beqz v0,0x7654`, 0x7628 `move s2,zero` (loop init in the delay slot).
- loop: 0x76fc `addiu s5,s2,1` (i + 1 for "%d." and the increment), 0x7864 `sll s2,s5,16` / 0x7878 `move s2,t2`, frame 0x148 with s0-s8 all saved (no free callee-saved register for a separate call-crossing flag).
