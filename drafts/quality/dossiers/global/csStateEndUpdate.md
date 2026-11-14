# csStateEndUpdate (global, src/global/42630.c)

## Sites
- ff6953: `cs->unk94->x` re-read. REMOVED.
  - The fix takes `actor = cs->unk94` inside the `if (cs->unk94 != NULL)` block.

## Attempts
- 2026-11-14 U HackcsStateEndUpdate: fixed. See the ledger for line counts.

## Evidence
- The target loads unk94 once (0xca4 `lw v1,148(a0)`), keeps the gCsRotY base in a3, and has no v0 user.
- gCsPosX/Y/Z are file-defined consecutive f32 (0x807F621C..24). Each is accessed with its own lui (no shared base), so a struct view is not needed.
