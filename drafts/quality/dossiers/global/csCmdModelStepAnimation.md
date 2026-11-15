# csCmdModelStepAnimation (global, src/global/478F0.c)
## Sites
- global:80649E34:other:4cca3f (base, removed): the `(*st).lastValue` spelling made cfe emit the st load before `cs->unk48[1]`, which gives `beq a0,t1` at 0x72a0.
- global:80649E34:dead-if:9573b6 (base, removed): `if (D_807481F4) {}` before a do-while put `lui v1,%hi(D_807481F4)` ahead of the beq at 0x7298.
## Attempts
- 2026-11-09..15, Clean478F0 / ReReview / Rev17L / RereviewMixedMid2 (opus low/xhigh/high).
  - Removing the dead if from the index do-while: 56 lines (colouring 6 vs 5).
  - Either operand order of plain `st->lastValue`: `beq t1,a0`.
- 2026-11-15, HackcsCondDepositItem (opus high): fixed, 2 FAKE -> 0.
  - The index do-while forms all score 56. A `while (found == 0)` loop with `found = 0; i = 0;` inside the if scores 1, and the dead read is no longer needed. With the inits outside the if it scores 41-44.
  - Pointer walk `s16 *p` (while loop): 20 lines.
    - The frame is 8 bytes short. Unused scalars do take homes: st, found, pad[2], p reaches frame 48.
    - Even then the spill `sw v1,28(sp)` lands before the jal, not in its delay slot. The user pointer gets no `.noalias $3,$sp`, which the strength-reduced index temp gets. So the original used an index.
  - `ucode --cfe`: `(*st).lastValue` is emitted before `cs->unk48[1]`, while `st->lastValue` is emitted after it. Casts on either side, `!(a == b)`, an early-return form and a value local all left it at 1 (Q0860).
  - With `s32 *st` both sides are subscripted, so source order decides. `cs->unk48[1] != st[1]` scores 0, the reverse order scores 1. csCmdStepSequenceProgress uses the same untyped block.
  - `cs->unk48[1]` replaces the `(u8)cs->unk44[2]` pun with no codegen change. The file-local CsPairState is gone.
## Untried ideas
- None open.
## Evidence
- 0x7290 lw t1,4(v1) (st[1]) before 0x7294 lbu a0,73(t9) (cs->unk48[1]); 0x72a0 beq a0,t1.
- 0x7298 lui v1,%hi(D_807481F4) / 0x72a4 addiu in the beq delay slot: the loop preheader of the rotated while.
- ugen of the match: `.noalias $3,$sp` on the strength-reduced pointer; spill `sw v1,28(sp)` in the jal delay slot at 0x72e8.
