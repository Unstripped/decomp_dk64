# csCondEval (global, src/global/42630.c)
## Sites (kept)
- global:8063EA14:other:1d104b (case 0x31): `((s16 *)cmd)[2]` keeps unk48[cmd->c] as the left bne operand (0x1808).
- global:8063EA14:other:10621e (case 0x4): `((s16 *)cmd)[1]` keeps unk44[cmd->b] as the left bne operand (0x188c).
## Attempts
- rounds 4-34 (opus:low): plain, swapped order, permute (best=0 only via `(*cmd).b` / `((0, cmd))->a` twins); see history.
- 2026-11-14 U HackcsCondEval opus:high (full=):
  - snapshot locals for either operand: 189-205
  - != with swapped arms: 145/188
  - ret = (field == arg): 167/217
## Untried ideas
- Reading cmd through an `s16 *` alias for the whole function (cutscene commands as s16 arrays): too wide for this item.
## Evidence
- CsCmd {u16 op; s16 a, b, c} at 0/2/4/6: the field types match, so the pun is not a type fix.
