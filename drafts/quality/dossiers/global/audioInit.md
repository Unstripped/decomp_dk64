# audioInit (global, src/global/5A50.c)

## Sites
- 48ba3e: the comma `(arg = player, player == NULL)`. KEPT.
  - The target sets arg = player only in the second test's block (`move a0,v0` in the bnez delay slot).

## Attempts
- 2026-11-14 U Hackfunc_80601678: player reuse 2 lines (best). See the ledger.

## Untried ideas
- None natural.

## Evidence
- 0x28c..0x2a8: `lw t3; sw v0; beqzl t3 (lw a0,0(s0)); bnez v0 (move a0,v0); lw a0,0(s0)`.
