# csCondEval (global, src/global/42630.c)
## Sites
- fixed 2026-11-16 (HackcsCondEval3): 3f5f75 (case 0x17), by a block-scoped `s32 arg = cond->arg[1];` read for the compare.
- fixed 2026-11-16 (HackcsCondEval2): 1d104b (case 0x31) and 10621e (case 0x4), by the CsCond view (below).
## Attempts
- rounds 4-34 (opus:low): plain, swapped order, permute (best=0 only via `(*cmd).b` / `((0, cmd))->a` twins); see history.
- 2026-11-14 U HackcsCondEval opus:high (full=):
  - snapshot locals for either operand: 189-205
  - != with swapped arms: 145/188
  - ret = (field == arg): 167/217
- 2026-11-16 HackcsCondEval2 opus:high (deadsweep full=):
  - s16 * local view of a CsCmd param: 211; `s16 *cmd` param (whole function): 192, then
    `(cmd[1] << 16) + cmd[2]` in 0x26/0x27/0x16 (csCmdExec order): 2, `cmd[1] & actorLookupClass()` in 0x10: 1.
  - CsCond {s16 op; s16 arg[3]} param (CsNode.unk2 retyped, cutscene.h hunk): same 1 line, 0x17 `bne t7,a1`.
  - 0x17 with the indexed read: both source orders, `if (x)`, `(s16)`/`(s32)` casts, `p->actor->` without `a`,
    `!= 0` vs bare, `||`/else-if forms (shape 2/5), snapshot locals k/h/sAnim/count (14..1073): never 0.
  - permuter 900 s on the CsCond body (base 10): best 10.
  - case 0x1: `k = unk48[arg1] - arg0; if (k == 0)` -> plain `==` matches with the unused s32 kept (frame size): `pad`.
- 2026-11-16d HackcsCondEval3 opus (variants.py try full=, base 1e5bb5b5, u8 gPlayerCharacterId[] in actor.h):
  - re-scored: plain indexed 0x17 both orders, bare `if (x)`: 1; `||`: 3; else-if: 6; `continue` form: 3;
    `(s32)`/`(u32)` cast on either operand, `(s16)` on the field: 1. The types change moved nothing.
  - snapshot `k = cond->arg[1]` before the test (`if (k != 0)`/`if (k)`), any width, function or block
    scope: 1061 (k becomes a register variable, whole-function recolour); same replacing `s32 pad`: 1061.
  - snapshot of `a->unk155` into a local (u8/s16/s32/u32): 52-56.
  - snapshot of the arg INSIDE the `!= 0` block, used only by the compare: s32/int/u32 -> 0 (both
    source orders, block scope or declared last among the locals); s16 -> 54, u16 -> 2; declared
    after `s32 pad` (mid list) -> 4. Kept: block-scoped `s32 arg`.
## Untried ideas
- none for csCondEval sites (no FAKE left).
## Evidence
- CsCmd {u16 op; s16 a, b, c} at 0/2/4/6: the field types match, so the pun is not a type fix.
- Named field reads (CsCmd.a/b) are canonicalised to the left compare/addu operand; indexed reads
  (cond->arg[n], or an s16 *) keep the right operand except a CSE'd value in a loop (0x17, a1 at 0x1eb0).
- Target: 0x188c `bne` field,arg (0x4), 0x1808 field,arg (0x31), 0x1ec0 arg(a1),field (0x17).
- 0x17: the s32 `arg` local (copy of the CSE'd lh 4(s0), a1) is the LEFT bne operand at 0x1ec0;
  casts of either operand do not reorder it, only the assignment to an int-width local does.
