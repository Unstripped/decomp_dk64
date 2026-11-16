# camComputeEyeFocus (global, src/global/201B0.c)

## Sites
- global:80622B24:other:a9e334 (removed): `if (gGameMode != 1U)` kept the constant 1 out of the `gGameMode == 1` expression web; signed 1 became `li t3,1` + `bne t3,t0` where the target has `li at,1` + `beq t0,at` at 0x7818. Fixed by the switch (gGameMode) mode dispatch.
- global:80622B24:other:975402 (retagged ORIG): empty `if (gPlayerCount >= 2 && gSplitScreenMode != 0) {}` in case 0x36; the target runs its loads and compares at 0x7904-0x792c (Q0646, Q0561).
- global:80622B24:goto:u57554, #2..#5 (kept, Q0591): five entries into the single calc_look block 0x88f4-0x89b8 (orbit bne at 0x8028; b at 0x80a0, 0x81bc, 0x825c, 0x8284; case 5 falls in).
- global:80622B24:goto:u71b9c (kept, Q0591): case 0x59 `bnez` at 0x926c into the check_target block 0x92c4 that default reaches after its zoom (0x92a8-0x92c0).
- global:80622B24:goto:u78dc1 / u08a68 (open, nohit): `goto look_set` / `goto look_done` and the two consecutive labels after the type switch. Without them uopt colours type's ucvt candidate (bit 245 in the -l 5 table, `ucvt{M -11vreg}`) in t0; the target leaves it uncoloured and reloads `lw t8,92(sp)` / `lw t7,92(sp)` at 0x89bc-0x89c4.

## Attempts
- 2026-11-15 U HackcamComputeEyeFocus2 anthropic/claude-opus-5-5:high: `switch (gGameMode) { case 1: ...; break; case 0: ...; break; }` in place of `if (gGameMode != 0) { if (gGameMode == 1) {...} } else {...}`, signed `gGameMode != 1` -> fdiff 0 (a9e334 removed). With 1U kept the switch alone is also 0.
- same: one-case `switch (gGameMode) { default: ...; case 1: break; }` for the 1U test -> 513 (constant fixed, but gGameMode's t0 range ends and type takes t0); `!(gGameMode == 1)` -> 638 (same as signed).
- same: 975402 compiled without the guard -> 1928 insns, only the guard's 11 insns plus 2 delay-slot copies disappear -> retagged `// ORIG:`.
- same: look labels: both gotos -> break 515 (517 on the switch base); look_done dropped 517 (519); default: break at end/start, explicit case 6/7/8/0xC: break, else-if tail instead of return, break inside the type 16 then-block -> 515; `if (p->type != 16) goto calc_look` -> 516; return -> break in the new case 1 -> 0 with labels, 517 without.
- same: variants scan (swap/float/width/declswap, 191-193 variants) of both label-free bodies: no zero; best `angle` s16 -> u16 at 246/248 (emits lhu, not a match).
- same: duplicated calc_look in case 1 -> 1287; duplicated check_target in case 0x59 -> 117; case 0x59 -> default fallthrough with `if (target->state != 0x59)` around the zoom -> 66 (adds li at,89 + beq).
- 2026-11-15 U HackcamComputeEyeFocus3 anthropic/claude-opus-5-5:high: -l 5 piece arithmetic of the type ucvt candidate (bit 245). Base piece 1029: 5 uses (bb127 = pre-switch `type == 7` at 0x7e38, bb185 = post-switch `type == 7`, bb203-205 = `!= 8/0xC/6`) and 5 reload blocks (bb127; bb174 = calc_look entry; bb183 = switch exit, preds case 4 break bb165 + 9 dispatch edges from bb136; bb184 = look_set, pred case-16 look block bb143; bb185 = look_done, pred calc_look join bb182) -> adjsave 0 -> not colored. Label-free piece 1033: same 5 uses, 3 reloads (bb127, bb174, bb183 = exit merged with the test) -> adjsave 2/7 = 0.286 -> assigned t0. A natural form needs two more reload-point joins (empty blocks with a call-path pred) before the `type == 7` test, or two fewer uses.
- same: tail `switch (type) { case 8: case 0xC: case 6: break; default: <6 stores>; break; }` to fold the three compare uses: label-free 520; on the label base 4 (cfe emits the compares sorted 6, 8, 12; target order is 8, 12, 6 at 0x8dac-0x8dc0).
- same: orbit arm as `switch (p->type) { case 16: <look>; break; default: goto calc_look; } break;` (inner switch exit as the extra join) -> 517.
- same: angle lever: `u16 angle` with `(s16)angle` at the two sin/cos uses -> 443; `u16 angle` with `(s16)` on the mathAngleLerp store -> 248 (lhu kept). The label-free u16 trace still assigns the type piece (t0), so width only moves unrelated temps.
- same: post-switch `if (type == 7) {...; return;}` as `switch (type) { case 7: ...; return; }` (case/exit labels as extra blocks) on the label-free body -> 927 (text 846).

## Untried ideas
- None left that is natural C: the empty joins could only come from nested statements whose ends coincide with the switch exit; every such wrapper (if, loop, switch) emits its own test, and code-free wrappers (`do {} while (0)`, `for (;;) { ...; break; }`) are hacks.

## Evidence
- 0x7c78-0x7c88: gGameMode reloaded into t0, `beqz t0 -> 0x8e10` (mode 0 code after the mode 1 code), `li at,1; bnel t0,at -> epilogue`.
- 0x7818: `li at,1; beq t0,at,0x7c80` (the `!= 1` test, t0 = gGameMode loaded at 0x76bc / 0x777c).
- 0x7904-0x792c: case 0x36 `lbu gPlayerCount; slti at,t4,2; bnezl; lbu gSplitScreenMode; beqzl; b` all to 0x7ab4.
- 0x7ebc-0x7ec4: type switch bounds check `sltiu at,t3,17; beqz at,0x89bc` (no default, out-of-range goes to the post-switch join).
- 0x8028: orbit `bne t7,at(16),0x88f4`; type 16 look block ends `b 0x89bc` at 0x8060.
- 0x89bc-0x89c8: `lw t8,92(sp); li at,7; lw t7,92(sp); bne t8,at,0x8dac` (type spilled as a word temp, reloaded at the join).
- 0x8dac-0x8dc0: `li at,8; beq t7; li at,12; beq t7; li at,6; beq t7` (source order of `type != 8 && type != 0xC && type != 6`, t7 loaded once at 0x89c4).
- 0x926c: case 0x59 `bnez t6,0x92c4`; default zoom 0x92a8-0x92c0 falls into 0x92c4.
