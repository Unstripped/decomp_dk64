# playerRefillHealth (global, src/global/117190.c)
## Sites
- global:80712830:dead-if:0b7e5e (kept): the dead read of playerIndex after `jal healthRefill` keeps the a1 home in the call's delay slot and reloads it eagerly.
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
## Untried ideas
- none from the local asm: the target needs a use of playerIndex in the block right after `jal healthRefill`, and no natural statement there reads it
## Evidence
- `andi a0,a1,0xff` before `jal healthRefill` (0x3b4)
- `sw a1,52(sp)` in the delay slot (0x3b8)
- `lw a1,52(sp)` at 0x3c4
- `move a0,a1` in the delay slot of `jal mapExecuteDeathTransition` (0x49c/0x4a0)
- plain removal instead: `sw a1,52(sp)` at entry, `lbu a0,55(sp)` in the delay slot, `lw a0,52(sp)` for mapExecuteDeathTransition
