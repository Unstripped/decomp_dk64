# camComputeEyeFocus (global, src/global/201B0.c)

## Sites
- global:80622B24:other:a9e334 (removed): `if (gGameMode != 1U)` kept the constant 1 out of the `gGameMode == 1` expression web; signed 1 became `li t3,1` + `bne t3,t0` where the target has `li at,1` + `beq t0,at` at 0x7818. Fixed by the switch (gGameMode) mode dispatch.
- global:80622B24:other:975402 (retagged ORIG): empty `if (gPlayerCount >= 2 && gSplitScreenMode != 0) {}` in case 0x36; the target runs its loads and compares at 0x7904-0x792c (Q0646, Q0561).
- global:80622B24:goto:u57554, #2..#5 (kept, Q0591): five entries into the single calc_look block 0x88f4-0x89b8 (orbit bne at 0x8028; b at 0x80a0, 0x81bc, 0x825c, 0x8284; case 5 falls in).
- global:80622B24:goto:u71b9c (kept, Q0591): case 0x59 `bnez` at 0x926c into the check_target block 0x92c4 that default reaches after its zoom (0x92a8-0x92c0).
- global:80622B24:goto:u78dc1 / u08a68 (open): `goto look_set` / `goto look_done` and the two consecutive labels after the type switch. Without them uopt colours type's ucvt candidate (244, piece 1028) in t0; the target leaves it uncoloured and reloads `lw t8,92(sp)` / `lw t7,92(sp)` at 0x89bc-0x89c4.

## Attempts
- 2026-11-15 U HackcamComputeEyeFocus2 anthropic/claude-opus-5-5:high: `switch (gGameMode) { case 1: ...; break; case 0: ...; break; }` in place of `if (gGameMode != 0) { if (gGameMode == 1) {...} } else {...}`, signed `gGameMode != 1` -> fdiff 0 (a9e334 removed). With 1U kept the switch alone is also 0.
- same: one-case `switch (gGameMode) { default: ...; case 1: break; }` for the 1U test -> 513 (constant fixed, but gGameMode's t0 range ends and type takes t0); `!(gGameMode == 1)` -> 638 (same as signed).
- same: 975402 compiled without the guard -> 1928 insns, only the guard's 11 insns plus 2 delay-slot copies disappear -> retagged `// ORIG:`.
- same: look labels: both gotos -> break 515 (517 on the switch base); look_done dropped 517 (519); default: break at end/start, explicit case 6/7/8/0xC: break, else-if tail instead of return, break inside the type 16 then-block -> 515; `if (p->type != 16) goto calc_look` -> 516; return -> break in the new case 1 -> 0 with labels, 517 without.
- same: variants scan (swap/float/width/declswap, 191-193 variants) of both label-free bodies: no zero; best `angle` s16 -> u16 at 246/248 (emits lhu, not a match).
- same: duplicated calc_look in case 1 -> 1287; duplicated check_target in case 0x59 -> 117; case 0x59 -> default fallthrough with `if (target->state != 0x59)` around the zoom -> 66 (adds li at,89 + beq).

## Untried ideas
- A natural construct adding two empty join blocks between the type switch end and `if (type == 7)` (what the labels do in the uopt -l 6 piece arithmetic), e.g. a nested statement both arms of which end at the switch end (guide ido-uopt-statics-and-live-ranges, live-range splitting).
- The `angle` width lever (u16 brings the label-free form from 515 to 246) combined with a change that restores `lh` for the orbit angle.

## Evidence
- 0x7c78-0x7c88: gGameMode reloaded into t0, `beqz t0 -> 0x8e10` (mode 0 code after the mode 1 code), `li at,1; bnel t0,at -> epilogue`.
- 0x7818: `li at,1; beq t0,at,0x7c80` (the `!= 1` test, t0 = gGameMode loaded at 0x76bc / 0x777c).
- 0x7904-0x792c: case 0x36 `lbu gPlayerCount; slti at,t4,2; bnezl; lbu gSplitScreenMode; beqzl; b` all to 0x7ab4.
- 0x7ebc-0x7ec4: type switch bounds check `sltiu at,t3,17; beqz at,0x89bc` (no default, out-of-range goes to the post-switch join).
- 0x8028: orbit `bne t7,at(16),0x88f4`; type 16 look block ends `b 0x89bc` at 0x8060.
- 0x89bc-0x89c8: `lw t8,92(sp); li at,7; lw t7,92(sp); bne t8,at,0x8dac` (type spilled as a word temp, reloaded at the join).
- 0x926c: case 0x59 `bnez t6,0x92c4`; default zoom 0x92a8-0x92c0 falls into 0x92c4.
