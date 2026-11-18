# playerRefillHealth (global, src/global/117190.c)

## Sites
global:80712830:dead-if:0b7e5e dead-if (FIXED 2026-11-17): the dead read of playerIndex after `jal healthRefill` kept the
a1 home in the call's delay slot and reloaded it eagerly. It stood in for the second argument of
`func_80026D40` (multiplayer `mpRespawnPlayer(Actor *, s32)` at 0x80026D40), which the file declared as `(void *)`.

## Attempts
- rounds 2/16/32 (opus:low): diagnose, permute (only steer swaps reach 0).
- 2026-11-14 opus:high:
  - no cast: 5
  - u8/s32 local: 13
  - u8 parameter (stand-in prototype): entry home + lbu, worse
- 2026-11-16 HackplayerRefillHealth2 opus:high (after `gGlobalOverlayFlags` became u32, batch_8 part F): nothing changed.
  - plain removal: 5; no cast: 5; u8/s32 local: 13
  - u32 `flags` local for both mask tests: 5
  - else-if chain instead of early returns: 5
  - `playerIndex & 0xFF` arg: 25
  - `Actor *p` local: 13; dropping `pad`: 9
  - variants scan of the plain body (31 swap/width/declswap edits): best 5
- 2026-11-17 2026-11-17: cleanup CleanmenuDrawBlinkingPromptText CleanmenuDrawBlinkingPromptText anthropic/claude-opus-5-5:
  - sweep re-run at the base: no hit (class 2).
  - FIX: file declaration `void func_80026D40(void *);` -> `void func_80026D40(Actor *, s32);` and the call
    `func_80026D40(player, playerIndex);` (callee arity from src/multiplayer/0.c mpRespawnPlayer; CEAE0.c also passes 2 args):
    whole-object fdiff 0 without the dead test.
  - `(u8)` cast on the healthRefill argument dropped (the healthRefill(u8) prototype converts): fdiff 0.
  - `pad` still needed: without it 4.
## Untried ideas
- none: the function has no hack site left.
## Evidence
- `andi a0,a1,0xff` before `jal healthRefill` (0x3b4)
- `sw a1,52(sp)` in the delay slot (0x3b8)
- `lw a1,52(sp)` at 0x3c4
- `jal func_80026D40` at 0x48c with only `move a0,a2` in its slot (a1 already holds playerIndex)
- `move a0,a1` in the delay slot of `jal mapExecuteDeathTransition` (0x49c/0x4a0)
- plain removal instead: `sw a1,52(sp)` at entry, `lbu a0,55(sp)` in the delay slot, `lw a0,52(sp)` for mapExecuteDeathTransition
- uopt -l6: with the real use playerIndex (cand 0) is coloured whole; without any use after the call it splits (0/41) and
  both pieces get negative savings.
