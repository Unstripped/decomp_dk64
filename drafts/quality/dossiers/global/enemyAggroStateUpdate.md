# enemyAggroStateUpdate (global, src/global/12E800.c)

## Sites
- global:8072C918:dead-if:627052 dead-if: `if (ang != 0) {}` after behaviourCheckTargetCollisionMode. It keeps ang (t2) live across both calls: spilled at sh t2,74(sp) 0x2f1c and again at 0x2fb0. Without the use, the whole ang computation (subu 0x2ed8/0x2ee8) disappears and the function shifts by 214 diff lines.
- global:8072C918:noop-arith:ad854e (was 97a9f3 until 2026-11-17f) noop-arith: `(ret ^ 0) != unk36 && (hasTarget == 0 || (s32)ret >= 7)` (the empty-then `if ((ret ^ 0) == unk36) {} else if (...)` respelled as one `&&` test, 0). The uxor makes the $v0 side an isop; uopt keeps an op-vs-op compare in reversed source order, so the unk36 load (right) is the first operand: `beq t5,v0` at 0x3170. The plain compare (var vs op) gives `beq v0,t5` (full=1).
- global:8072C918:other:ec05fc other (pre-existing, tagged 2026-11-17f): case 0x35 `near = (unk20-- == 0); if (near)` reuses near (s32, home 64(sp), t4) for the countdown flag (sltiu t4,v0,1 at 0x34b0). A dedicated local leaves near uncoloured (candidate 27 split into -ve-save pieces), so every near test reloads 64(sp): 185-221.
- global:8072C918:other:49d7fe (fixed 2026-11-14): `me = (Actor *)C1B40->secondComponent; if (dist < *(s16 *)me)`, now the typed `range` local.
- global:8072C918:other:c57b42, 5bba72, 1ad395, 5bba72#2 (fixed 2026-11-15, now `// ORIG:`): the `near & 0xFF` tests. The target really masks the s32 flag (sw/lw slot 64(sp), register t4) at every one of these tests: andi t9,t4,0xff at 0x305c/0x3080, andi t7,t4,0xff at 0x3168, 0x32d8, 0x33f4/0x341c. The case 0x35 reuse (`near = (unk20-- == 0); if (near)`, sltiu t4 / beqz t4 at 0x34b0) has no mask, so the mask belongs to the source tests.

## Attempts
- 2026-11-10 .. 11-12, rounds 4/6/16/17, low/high/xhigh: removals, plain, cond, classify, recipe, permute, and reconstruct with all three removed. See the history file. Nothing matched; Q0602 says the three are coupled.
- 2026-11-14 HackenemyAggroStateUpdate, opus-5-5:xhigh:
  - **49d7fe:**
    - typed snapshot `s16 *range;` declared after `me`, `range = C1B40->secondComponent; if (dist < *range)` -> full=0: **fixed**.
    - The same local declared first: full=39.
    - `C1B40->secondComponent[0]` read directly: full=97.
  - **97a9f3** (with range applied; the rows below give the score of each spelling of the compare):

    | spelling | full |
    |---|---|
    | `ret == unk36` | 1 |
    | `unk36 == ret` | 1 |
    | `type == unk36` | 94 |
    | `unk36 == type` | 95 |
    | `(s32)ret ==` either way | 1 |
    | `if (ret != unk36 && (...))` | 1 |
    | the two-ifs nested form, either compare side | 1 |
    | `ret >= 7` without the cast | 2 |
    | ret as u8 or u16 | 22 |
    | ret as s16 | 257 |
    | ret as s32 | 36 |
    | `type` only | 5 |
    | `type = ret = call` | 1 |
    | `type = call; ret = type` | 1 |

    Also: `(u32)` on either side (Q0715) full=1; `(u8)ret` or `ret & 0xFF` full=94. variants scan on the ret_plain copy: 57 recipes, best full=1. Permuter, 900 s on the ret_plain copy (`perm_ret`): base 10, best 10, 25130 iterations, no improvement.
  - **627052:**
    - Removal alone: full=214, with or without the range fix. Every combination with the ret rewrites: full >= 215.
    - The target computes and spills ang but never tests it (no branch on t2 in the function), so the tagged dead test `if (ang != 0) {}` has no counterpart in the target. The worker retagged it `// ORIG:`; the lead (Lead10) rejected that, and it stays FAKE as diagnose nohit.
  - **reconstruct:** the natural body (range local, plain compare, ang use kept) scores full=1. The only difference left is the beq operand order at 0x3170.
- 2026-11-15 HackenemyAggroStateUpdate2, opus-5-5:high:
  - **masks:** near's width with the masks removed (plain): s32/u32 157, u8/u16 222, s8/s16 208; masked u8/u16 221, s8/s16 53, u32 0. The target has the andi at each test (offsets above), so all four were retagged `// ORIG:` (fixed). Masks removed together with the dead if: 223; with the plain compare as well: 223; masks removed + plain compare only: 157.
  - **97a9f3:** uopt trace at base: `uequ{1521|0}{7|0}` with `uxor{1181|0}{0|1}` as candidate 7. Tried a local for unk36 in the compare block: u8 declared before ret 94 (still `beq v0,a0`), after ret 150, s32/u32 150, in the pad0 slot 94, assigned inline 94. Copy local of ret used only in the compare: 58-176. ret `int` 36, `unsigned int`/`unsigned` 1, `unsigned char`/`unsigned short` 22. ret u8 does give `beq t5,a0` (field first) but adds `andi a0,v0,0xff` and shifts the frame slots by 4. Callee `behaviourCheckTargetCollisionMode` retyped `u32` (PROTO_SKIP stand-in) keeps the callee byte-identical but the caller plain compare is still 1; `s32`/`int` returns break the callee.
  - **627052:** ternary `ang = (a < b) ? b - a : a - b;` 0 with the dead if, 214 without; `ang = b - a; if (ang < 0) ang = -ang;` 250; ang s32 209, u16 189; dead store `pad0 = ang;` 236 (s16 pad0 247). Q0589 use-count levers do not apply: without a use after the second call the whole ang computation disappears.
  - Review: `pad0` is needed (removed: 33). The case 0x35 reuse of `near` is needed (inline or a separate local: 185-221; target uses t4 there).
- 2026-11-16 HackenemyAggroStateUpdate3, opus-5-5:high:
  - **627052, Q0908 classification:** class (ii), same-value only. With the same guard line at 767: `1`/ret/type/me/playerState 214, near 213, aggroDist 203, hasTarget 221, dist 237. Only an ang test matches.
    - Position: just before `type = ret` 14; inside case 0x35 0; at the function end 219.
    - Still-dead forms that match (0): `ang ? 0 : 0;`, `ang && 0;`, `if (ang != 0);`, `if (ang) {} else {}`. Dropped by cfe (214): `(void)(ang != 0);`, `switch (ang) {}`, `switch (ang) { default: break; }`.
  - **97a9f3:** ugen emits (var, load) for a register var against a field load (Q0343), so `beq t5,v0` needs a codeful isop on ret's side (the `^ 0` uxor, or the u8 ucvt).
    - ret declared first: 3 (playerState slot 84 -> 68, still `beq v0,t5`). ret declared last: 1.
    - Field-side casts (u16/s16/u32/s32/u8/int), `gBehaviourWorkState[0].unk36` and `*&gBehaviourWorkState->unk36`: all 1.
    - ret `unsigned int` with `(u32)`/`(s32)`/`(int)` on either side: 1. The no-op cvts fold (`(s32)ret` trace: `uequ{1181|0}{61|0}`, ret still left).
    - `BehaviourWorkState *ws` local: 58 (frame 88 -> 96, still `beq v0,t5`).
    - unk36 value local: `int`/`s32` declared last gives the field-first `beq a0,v0`, but the frame grows 88 -> 96 and the value sits in a0 (150). `u32`/`u8` declared last: `beq v0,a0` (150). `s16`/`u16`/`short` in the 72(sp) gap or `u8`/`s8`/`char` in the 76(sp) gap: 94 (`beq v0,a0`, value in a0).
    - ret `u8` followed by `u8 pad1[3]` keeps every frame slot: 5. The beq is field-first (`beq t5,a0`), but the call result is re-masked (`andi a0,v0,0xff`, `slti at,a0,7`).
  - sweep on the copy: 0 hits. Review: no edits.
- 2026-11-17 HackenemyAggroStateUpdate4, opus-5-5:high:
  - **97a9f3:** uopt trace (plain): `uequ{1181|0}{1521|0}` where 1521 = `ucvt{61}` of `ucvt{319}` (the u8 field widened twice). In case 0x10 the compare is `uneq{61}{1217}` with 1217 = `ucvt(type)`: both sides isops, so the field comes first there with no code on type's side. In 0x23 ret is a plain var, and Q0343 puts the var first.
    - Parameter reuse for ret: `aggroDist` 53 (`beq v1,t5`, still var-first; P vars are 906+16*offset), `chaseScriptId` 237.
    - `(*gBehaviourWorkState).unk36` (Q0488 `(*st).f` lever), either side: 1. With ret s32/int: 36 (ret moves to v1 via `move v1,v0`). With ret u8/u16: 22.
    - `register u32 ret` 1. `unsigned long ret` 1. `!(ret != unk36)` 1. `(ret == unk36) ? 1 : 0` 64.
    - Value local `cur = unk36; if (ret == cur)` (or `cur == ret`), s32 or u8, in pad0's place / first / last / after ret: 94-126.
  - **627052:** angle wrap `if (ang > 0x800) { ang = 0x1000 - ang; }` (also `>=`, and `& 0xFFF` on the result) at the guard line: full=0. It is still a dead use, though: the store is dead, and the target never branches on ang. It would swap one dead construct for another, so it was not adopted. The same wrap right after the ang computation: 201.
  - sweep on the copy: 0 hits. Review: no edits.
- 2026-11-17f CleanenemyAggroStateUpdate (unit "2026-11-17: cleanup CleanenemyAggroStateUpdate"), opus-5-5:
  - **97a9f3 -> ad854e:** uopt trace at base: the compare operand is the `$v0` return-register var (`isvar R 0 2vreg`, hash 1485): `uxor{1485}{0}` / `uequ{1521}{7|3}` (bits 194/195). ret (-20vreg, 1181) is copy-propagated and never stored, so declaration-position numbering (Q1027) never reaches the final compare.
    - Op-vs-op compares keep reversed source order (not candidate order, refines Q0474): `unk36 == (ret ^ 0)` gives `uequ{7}{1521}` and `beq v0,t5` (1); `(ret << 0)` on the left 0, on the right 1.
    - `| 0` and `& 0xFFFFFFFF` fold after the ordering into ret own var: `uequ{1521}{1181}`, `move a1,v0` after the jal, `beq t5,a1` (4). `+ 0` / `- 0` fold first (1). `<< 0`, `>> 0`, `* 1`, `/ 1` survive codeless like `^ 0` (0). s32 ret with the uxor: 36.
    - Callee return width (PROTO_SKIP stand-in): u16 keeps the callee (0), caller 1 with ret u32 and 22 with ret u16 (andi re-mask); s16 breaks the callee (5; caller 34/115); u32 0/1.
    - Control flow: `if ((ret ^ 0) == unk36) {} else if (A) {...}` respelled `if ((ret ^ 0) != unk36 && A) {...}` (0; the nested form is 0 too). New key ad854e. Plain on the new body: 1; variants scan of it: 57 variants, best 1.
  - **627052:** lever (e) (Q1187/Q0932) fails: with the plain compare, `if (ang != 0 && ret != 0) {}` or `if (ret != 0 && ang != 0) {}` keeps ang but leaves `beq v0,t5` (1): the beq order is set inside the compare, not by ret liveness. The ang test inside the 0x23 compare arm: 46 (with or without the uxor). `register s16 ang` without the guard: 214. Removal on the new body 214.
  - **ec05fc (new, pre-existing, now tagged):** case 0x35 reuses `near` for the `unk20-- == 0` flag. A dedicated local: u8 in the pad0 slot 185, s8 188, u16 193, s16 196; s32 declared last, block-scoped, or the inline `if (unk20-- == 0)` 221. Trace: near (cand 27, -24vreg) is coloured t4 whole with the reuse; without it, it splits into pieces 213/225/228/232 (-ve save) and each test reloads `lw 64(sp)` (0x305c, 0x3164, 0x32d8). The reuse never stores to 64(sp) after the def, so ORIG does not apply (register sharing only).
  - **permute (hack-free weights, -j 2, 900 s):** all-removed body (ang guard and uxor removed, near reuse kept), `perm_allrm`: base 3580, best 310. Every best output reuses ang for an unrelated value (`ang = 0xFF` with `near & ang` in 0x23/0x33, `(s32)ret >= (ang = 7)`, `ang = targetX` in case 7); none keeps the behaviour.
    - Natural body with all three removed (dedicated s32 `expired`, pad0 dropped), `perm_rec3`: base 6759, best 2806. The best outputs again reuse ang (`ang = near` before case 4, `ang = chaseScriptId` before case 0x23) or respell `dist < 0x1388` as `(dist + 1) <= 0x1388`; none puts near back in t4.
  - **reconstruct:** the natural body (no ang guard, plain `ret != unk36 && (...)`, a dedicated s32 `expired` local for case 0x35, pad0 dropped): 217; expired in the pad0 slot 214; near reuse kept 215.
  - sweep on the copy: 0 hits. Review: the empty-then compare respelled, the near reuse tagged; casts=1 kept (`(s32)ret >= 7`: the target does a signed `slti at,v0,7` at 0x317c).
- 2026-11-18 CleanenemyAggroNearFlag (unit "2026-11-17: cleanup CleanenemyAggroNearFlag"), opus-5-5: the C4620 lever (`u8 near`, SQ inline, no delta locals) on the four ORIG masks and ec05fc. No change adopted (copy = base).
  - **u8 near, two-step form** (`near = dist < aggroDist; if (near == 0) near = ...`), masks dropped: 222 (near uncoloured, every test `lbu`); with the inline countdown 331; with a dedicated `u8 expired` 233. Masks kept on a u8 near: 221.
  - **u8 near, `near = dist < aggroDist || (flags & 4)`**, masks dropped, every other local kept: 77; with the inline `if (gBehaviourWorkState->unk20-- == 0)` in case 0x35: 57. The code is then the target code, but the frame grows 88 -> 96: the `||` cfe value temp (Q0122/Q0361) takes a word below the named homes, and that temp is the t4 spill slot. With s32 near and `||`: 74; with the masks kept: 221.
  - **Frame capacity** (`||` form, countdown inline, decl orders): pad0 dropped 33; near in pad0 slot (79) 17 (t4 temp at 56, me 64, range 60). Dropping `me` (gCurrentActor read directly: its CSE temp spills to 60, as in the target) and declaring range block-scoped or function-level: 17, only two sp offsets off (t4 temp 60 vs 64, gCurrentActor temp 56 vs 60: range still owns 64). Dropping `me` AND the range local (`if (dist < *CURRENT_TWO_COMPONENT_ACTOR->secondComponent)`): shape 0, frame 0x58 exact, t4 temp 64 and gCurrentActor 60 as in the target, but the 0x178 pointer becomes a ugen temp (`lw t8,376(a0)` / `lh t5,0(t8)` instead of `lw v1,376(a0)` / `lh t8,0(v1)` at 0x3134/0x3140) and the ring shifts through case 0x23: 97 (operand swap 97, plain ret 97, dead-if removed 225).
    - The named homes must end at 0x44 for the temps to land at 64/60. Above 0x44 the target uses 84 (playerState), 80 (dist), 78 (type), 77 (hasTarget), 74 (ang): only one 4-byte home is left (68). ret (32-bit call result held in $v0 for the 0x23 compare) and the range pointer (uopt-coloured v1) both need one. Without ret (`type = call()`, `type != unk36 && (hasTarget == 0 || type >= 7)`) and with range: 5 (`andi a0,v0,0xff` before the 0x23 compare, `beq t5,a0`, `slti at,a0,7`). ret as u16 with range: 5 (`andi a0,v0,0xffff`). ret as u8 / ang as s8 (variants scan of the me-less copy): 5 / 7. aggroDist reused for the call result: 36 (steer, not adopted).
  - **s32 holder + u8 copy (hybrid H1):** `u8 near` in pad0 slot (79), `s32 cond` in the old near slot (64): `cond = dist < aggroDist; if (cond == 0) cond = ...; near = cond;`, bare `if (near)` tests, case 0x35 `cond = (unk20-- == 0); if (cond)`: **fdiff 0** (whole-object OK). Trace: cond is bit 27 (-24vreg, home 64) coloured t4; near is bit 43 (-9vreg), its store `ustr{1357}{1117}` (bit 45) is never emitted (79 is never written), so each `if (near)` is the u8 truncation of t4: the target per-test `andi t,t4,0xff` (Q0122/C4620 mechanism), and pad0 byte 79 is that u8 home. Not adopted: `near = cond` is a redundant alias and cond is still reused for the countdown (ec05fc twin): FAKE count would rise 3 -> 4. In this body: countdown inline 74, countdown in a dedicated `u8 expired` at 76 (no frame change) 39 (cond uncoloured, tests read `lbu 67(sp)`, the Q0122 `off+3` pattern), countdown on near 39; ang guard removed 214, plain `ret != unk36` 1 (beq v0,t5) -- same as base.
  - **permute** (hack-free weights, -j 2, 900 s) from the me-less, range-inline `||` body (`perm_u8`): base 560, best 26. The best outputs hold the 0x178 value (not the pointer) in a narrow `new_var` local. Rewritten: `s16 range` declared after ang (the free halfword 72, no frame change), `range = *CURRENT_TWO_COMPONENT_ACTOR->secondComponent; if (dist < range)`: **3** (shape 0; only `lw t8,376(a0)` / `lh v1,0(t8)` / `slt at,t1,v1` vs the target `lw v1,376(a0)` / `lh t8,0(v1)` / `slt at,t1,t8` at 0x3134/0x3140: the target colours the pointer, this body the value). Declared after hasTarget 6, after ret 20; s8/u8/u16 widths 3; plain ret on it 4; ang guard removed 215; `playerState` reused for the pointer 63 (steer, not adopted).
  - sweep on the copy: 0 hits. Review: no edits.
- 2026-11-19 CleanenemyAggroStateUpdateb (unit "2026-11-18c: cleanup CleanenemyAggroStateUpdateb"), opus-5-5: stale rungs re-run on the current body (after the static-data campaign merges and the 7a1f8709 close renames); no change adopted (copy = base).
  - **Re-measured (deadsweep, same numbers as before):** 627052 removed 214 (ang bit 49 loses its only use, the subu/sh t2,74(sp) vanish, near t4 -> t3, playerState t3 -> t2); ad854e plain 1 either side (`uneq{1485}{1521}`: ret is copy-propagated to the R var, var before op); ec05fc inline countdown 221 (near bit 27 splits into 212/224/228/231, all -ve save), s32 `expired` last 221, u8 `expired` after hasTarget (76) 185; all three removed 314.
  - **New forms:** s32 ret without the cast 36 (ret no longer copy-propagated: `move v1,v0` at the dispatch, `beq v1,t5`, the v0/v1 ring swaps through the function); `register s32 near` 221, `u32 near` 221, `if (!unk20--)` 221, assignment-in-test reuse `if ((near = (unk20-- == 0)))` 57; `register s16 *range` on the me-less `||` body 17 (it still takes the named word 64: the `||` temp and the gCurrentActor temp move to 60/56).
  - **M2 table (me-less `||` u8 near, s16 range value at 72, inline countdown):** dead-if + uxor 3, dead-if + plain 4, uxor only 215, neither 216.
  - **permute** (hack-free weights, -j 2, 900 s, 39387 iterations) from the M2 body with the plain compare (`perm_orval`, deadsweep 4): base 30, best 30. The only output at the baseline reuses range for `gBehaviourTargetActor->y` inside the zoneCanReachPoint call (a reuse steer).

## Untried ideas
- ad854e: a natural codeless isop on a 32-bit var written on the left of the compare. Every 32-bit cast folds before ordering (`+ 0`/`- 0` too); `| 0` folds after ordering but splits ret off $v0. Only a narrow var gives a codeless ucvt, and IDO re-masks a narrow var assigned from the int-typed $v0 R var.
- 627052: no codeless natural use of ang after `type = ret` found; only dead constructs match (dead angle-wrap store 2026-11-17; the permuter only finds unrelated reuses of ang, 2026-11-17f).
- ec05fc: a natural extra def/use of near in case 0x35 that keeps near coloured whole in t4 (the target tests only the countdown there). In the `||` u8 body the inline countdown already matches case 0x35; that body only lacks a frame word (see the capacity note, 2026-11-18).
- masks/ec05fc via the `||` u8 body: a natural spelling that keeps the 0x178 POINTER uopt-coloured (v1 at 0x3134) without a named 4-byte home (the s16 value local in halfword 72 is 3 lines: it colours the value instead), or the 0x23 compare on the raw $v0 without a 32-bit ret home. Every pointer-local candidate needs one more word than the target frame has above 0x44 (2026-11-18); a `register` storage class does not drop the home (2026-11-19, 17).
- masks via the hybrid H1 (fdiff 0): a ruling that a `u8` flag copied once from an s32 scratch (`near = cond`) is ordinary C would retire the four ORIG masks and pad0; it still needs cond reused for the countdown (2026-11-18).

## Evidence
- 0x2ed8 `subu t2,v1,v0` / 0x2ee8 `subu t2,v0,v1`: ang = |moveYaw - unk8| is computed.
- 0x2f1c `sh t2,74(sp)` before the jal zoneCanReachPoint; 0x2f44 `lh t2,74(sp)` after it; 0x2fb0 `sh t2,74(sp)` before the jal behaviourCheckTargetCollisionMode. Nothing reloads 74(sp) later.
- 0x316c `lbu t5,54(v1)` (unk36); 0x3170 `beq t5,v0,31a4`: the field comes first.
- 0x2fec `andi a3,v0,0xff` (type); ret stays in $v0 through the switch: `slti at,v0,7` at 0x317c and `beq t5,v0` at 0x3170 use the unmasked call result; ret has no home store.
- 0x34b0 `sltiu t4,v0,1` / 0x34b8 `beqz t4`: the case 0x35 countdown flag lives in near register t4; near home 64(sp) is written only by the call-site spills.
- Case 0x10 `beql t9,a3` at 0x33f0: `type != unk36` (ucvt of the u8 var vs the field) already puts the field first with no extra code.
- Frame 0x58: named homes 84 (playerState, t3), 80 (dist, t1), 78 (type, sb a3), 77 (hasTarget, `addiu a1,sp,77`), 74 (ang, sh t2); word spills 64 (t4: near/countdown) and 60 (gCurrentActor snapshot, `sw t6,60(sp)` at 0x2e3c, reloaded at 0x2e7c/0x2ea0 before the first call); bytes 79 and 76, halfword 72 and word 68 never accessed. A `||` cfe temp and a gCurrentActor CSE temp land at 64/60 only when the named homes end at 0x44 (one 4-byte home below ang).
- Copy propagation of ret depends on its type: `u32 ret` is replaced by the R var 1485 in both 0x23 tests (no `move`, compare on $v0); `s32 ret` (no cast) is kept as its own var, coloured v1 by a `move v1,v0` at the dispatch (36 lines, 2026-11-19).
- With the countdown inline (`if (unk20-- == 0)`), a post-decrement candidate appears at -36vreg (bit 183) and near (bit 27) is split into four uncoloured live ranges; with the reuse, near has one more def/use in case 0x35 and is coloured whole (t4, uopt reg 11).
