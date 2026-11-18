# playerStateEnterFallOnCheck (global, src/global/D5E10.c)
## Sites
global:806D91A4:dead-if:4a0a6c dead-if: `if (z) {}` after `z = (b == 0)` (b = u16 copy of prevContactFlags) kept the uequ{0}{cvt b} candidate in $v1 from its definition before the step ternary (sltiu v1,a0,1 at 0x8174) to `and t1,v1,v0` at 0x8184; without it the step n took v1 and the compare t1 (7 rows). FIXED 2026-11-17 (no hack left).
## Attempts
2026-11-09..11-14 rounds 1-36 (CleanD5E10, CleanGlobalD5E10, ReReview, Rev16F; opus-5-5 low/xhigh): remove/cond/classify (class 2), `!= 0` / `!z` flips (still dead), permuter runs (only new_var temps, `^ 0`, re-added guards), reconstruct with 10 speed-block rewrites (if/else n, u16/s32/u32 prev, flags+prev locals, landed temp, &&, *=), 16 rewrites with b local (operand order, u16/u32 z, !b, inlined b == 0) -> none removed the guard.
2026-11-17 cleanup CleanplayerStateApproachVelocity (CleanplayerStateApproachVelocity): 700 scored spellings (z width/statement order/operand order, flags local, inline forms). z used in the test with ilod operands 1 row (operand order of the and); `!gCurrentActor->prevContactFlags & gCurrentActor->contactFlags & 1` inline with no b/z locals -> fdiff 0 (whole object). Also dropped the two redundant `(f32)n` casts, `*= 0.25`, `-= decel`, n renamed decel (all fdiff 0).
## Untried ideas
none open (function has no hack site).
## Evidence
- 0x8158/0x815c: lhu v0 = contactFlags (0x6a), lhu a0 = prevContactFlags (0x6c) at the join after the effect block.
- 0x8168-0x817c: decel = (flags & prev & 1) ? 2 : 1 in a2.
- 0x8174: sltiu v1,a0,1 in the beqz delay slot: the !prev value, computed before the decel join.
- 0x8184: and t1,v1,v0 (lnot temp left, flags right); andi t2,t1,1; beqz t2.
- uopt -l6 (fixed body): `!prev` used as a value goes through a cfe hidden temp isvar M -8vreg (cand 17) holding uequ{0|1}{uilod 0x6c}; `(prev == 0)` instead is an isop uequ{0|2}{ucvt} candidate (10 rows). Same mechanism as Q1166 (u8 toggle `f = !f`), here as an operand of a bitwise `&` on a u16 field.
