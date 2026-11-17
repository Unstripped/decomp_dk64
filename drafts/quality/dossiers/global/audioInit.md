# audioInit (global, src/global/5A50.c)

## Sites
- 48ba3e: the comma `(arg = player, player == NULL)`. FIXED 2026-11-17 (HackaudioInit).
  - Now `if (D_8076BF38[i] == NULL || (arg = player) == NULL) { arg = gSeqPlayers[i]; }`: an embedded
    assignment whose value the target tests (`bnez v0`, `move a0,v0` in its delay slot), ordinary C per the ladder
    and Q0863.

## Attempts
- 2026-11-14 U Hackfunc_80601678: player reuse 2 lines (best). See the ledger.
- 2026-11-17 HackaudioInit: in-condition assignment `(arg = player) == NULL` -> fdiff 0, uninit 0, warn 0.

## Untried ideas
- None; no sites left.

## Evidence
- 0x28c..0x2a8: `lw t3; sw v0; beqzl t3 (lw a0,0(s0)); bnez v0 (move a0,v0); lw a0,0(s0)`.
