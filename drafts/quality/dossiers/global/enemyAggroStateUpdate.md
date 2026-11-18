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

## Untried ideas
- ad854e: a natural codeless isop on a 32-bit var written on the left of the compare. Every 32-bit cast folds before ordering (`+ 0`/`- 0` too); `| 0` folds after ordering but splits ret off $v0. Only a narrow var gives a codeless ucvt, and IDO re-masks a narrow var assigned from the int-typed $v0 R var.
- 627052: no codeless natural use of ang after `type = ret` found; only dead constructs match (dead angle-wrap store 2026-11-17; the permuter only finds unrelated reuses of ang, 2026-11-17f).
- ec05fc: a natural extra def/use of near in case 0x35 that keeps near coloured whole in t4 (the target tests only the countdown there).

## Evidence
- 0x2ed8 `subu t2,v1,v0` / 0x2ee8 `subu t2,v0,v1`: ang = |moveYaw - unk8| is computed.
- 0x2f1c `sh t2,74(sp)` before the jal zoneCanReachPoint; 0x2f44 `lh t2,74(sp)` after it; 0x2fb0 `sh t2,74(sp)` before the jal behaviourCheckTargetCollisionMode. Nothing reloads 74(sp) later.
- 0x316c `lbu t5,54(v1)` (unk36); 0x3170 `beq t5,v0,31a4`: the field comes first.
- 0x2fec `andi a3,v0,0xff` (type); ret stays in $v0 through the switch: `slti at,v0,7` at 0x317c and `beq t5,v0` at 0x3170 use the unmasked call result; ret has no home store.
- 0x34b0 `sltiu t4,v0,1` / 0x34b8 `beqz t4`: the case 0x35 countdown flag lives in near register t4; near home 64(sp) is written only by the call-site spills.
- Case 0x10 `beql t9,a3` at 0x33f0: `type != unk36` (ucvt of the u8 var vs the field) already puts the field first with no extra code.
