# playerInputUpdate

## Sites
- **`global:806DF6D4:dead-if:acdcca`** (`if (gPlayerPadState) {}` before fn[16]) is REMOVED.
  - It stood in for a use of the &gPlayerPadState address constant at the tail. The natural reads supply that use.

## Attempts
- **2026-11-14, HackE4090InputA, anthropic/claude-opus-5-5:high.** Removed acdcca together with the view: the 11 `D_807FD63A[i].heldButtons` reads plus the first store became `gPlayerPadState[gCurrentPlayerIndex].heldButtons`.
  - Result: RELOC-EQUIV OK.
  - Raw diff (`acdcca_rawproof.diff`): 11 LO16 immediates 0 -> 0x2A, symbol D_807FD63A -> gPlayerPadState. HI16 words are identical; no other word differs.
- **Each half alone** (round 35, and re-measured here):
  - acdcca removed with the view kept: full=445.
  - The view respelled with acdcca kept: round-35 views nohit.

## Untried ideas
None left. The function is hack-free.

## Evidence
- D_807FD63A = 0x807FD63A = gPlayerPadState (0x807FD610) + 0x2A (PadInputState.heldButtons).
- Target lhu/sh via `%lo(D_807FD63A)` at 0x3a4, 0x8a4, 0x8e8, 0x944, 0x9a0, 0x9fc, 0xa58, 0xa98, 0xad8, 0xb18, 0xb58.
