# enemyAggroStateUpdate (global, src/global/12E800.c)

## Sites
- global:8072C918:dead-if:627052 dead-if: `if (ang != 0) {}` after behaviourCheckTargetCollisionMode. It keeps ang (t2) live across both calls: spilled at sh t2,74(sp) 0x2f1c and again at 0x2fb0. Without the use, the whole ang computation (subu 0x2ed8/0x2ee8) disappears and the function shifts by 214 diff lines.
- global:8072C918:other:49d7fe other: `me = (Actor *)C1B40->secondComponent; if (dist < *(s16 *)me)`. Reusing `me` for the 0x178 component kept the pointer in its register (t8 at 0x3134 instead of v1).
- global:8072C918:noop-arith:97a9f3 noop-arith: `(ret ^ 0) == gBehaviourWorkState->unk36` gives `beq t5,v0` at 0x3170 (field lbu t5,54(v1) first). The plain compare gives `beq v0,t5`; colouring is identical (full=1).

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

## Untried ideas
- uopt_trace done: in the plain form, uequ{1181|0}{1521|0} numbers ret (1181) before unk36 (1521); the ^ 0 form wraps ret in a uxor isop numbered after the field. A source-level way to number the unk36 load before ret is still missing (Q0474: plain operand order, casts and nesting have no effect).
- Spelling the 0x23 case so that unk36 is loaded into a local that is used elsewhere too. No such use exists today.

## Evidence
- 0x2ed8 `subu t2,v1,v0` / 0x2ee8 `subu t2,v0,v1`: ang = |moveYaw - unk8| is computed.
- 0x2f1c `sh t2,74(sp)` before the jal zoneCanReachPoint; 0x2f44 `lh t2,74(sp)` after it; 0x2fb0 `sh t2,74(sp)` before the jal behaviourCheckTargetCollisionMode. Nothing reloads 74(sp) later.
- 0x316c `lbu t5,54(v1)` (unk36); 0x3170 `beq t5,v0,31a4`: the field comes first.
