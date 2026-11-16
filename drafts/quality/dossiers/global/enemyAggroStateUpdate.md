# enemyAggroStateUpdate (global, src/global/12E800.c)

## Sites
- global:8072C918:dead-if:627052 dead-if: `if (ang != 0) {}` after behaviourCheckTargetCollisionMode. It keeps ang (t2) live across both calls: spilled at sh t2,74(sp) 0x2f1c and again at 0x2fb0. Without the use, the whole ang computation (subu 0x2ed8/0x2ee8) disappears and the function shifts by 214 diff lines.
- global:8072C918:other:49d7fe other: `me = (Actor *)C1B40->secondComponent; if (dist < *(s16 *)me)`. Reusing `me` for the 0x178 component kept the pointer in its register (t8 at 0x3134 instead of v1).
- global:8072C918:noop-arith:97a9f3 noop-arith: `(ret ^ 0) == gBehaviourWorkState->unk36` gives `beq t5,v0` at 0x3170 (field lbu t5,54(v1) first). The plain compare gives `beq v0,t5`; colouring is identical (full=1).
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

## Untried ideas
- uopt_trace done: in the plain form, uequ{1181|0}{1521|0} numbers ret (1181) before unk36 (1521); the ^ 0 form wraps ret in a uxor isop numbered after the field. isvar hashes follow 1501 + 16*offset (-20vreg -> 1181), so no in-frame declaration position puts ret after the field. A source-level way to put a codeless isop on ret's side is still missing; every 32-bit no-op cvt folds.
- 97a9f3: ret u8 with `u8 pad1[3]` (slots kept) is 5 lines away: only the `andi a0,v0,0xff` re-mask remains. A way to make uopt trust the u8 call result (no re-mask at the compare and the slti) is untried.
- 627052: no codeless natural use of ang after `type = ret` found; only dead constructs match.

## Evidence
- 0x2ed8 `subu t2,v1,v0` / 0x2ee8 `subu t2,v0,v1`: ang = |moveYaw - unk8| is computed.
- 0x2f1c `sh t2,74(sp)` before the jal zoneCanReachPoint; 0x2f44 `lh t2,74(sp)` after it; 0x2fb0 `sh t2,74(sp)` before the jal behaviourCheckTargetCollisionMode. Nothing reloads 74(sp) later.
- 0x316c `lbu t5,54(v1)` (unk36); 0x3170 `beq t5,v0,31a4`: the field comes first.
