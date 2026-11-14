# playerRefillHealth (global, src/global/117190.c)
## Sites
- global:80712830:dead-if:0b7e5e (kept): the dead read of playerIndex after `jal healthRefill` keeps the a1 home in the call's delay slot and reloads it eagerly.
## Attempts
- rounds 2/16/32 (opus:low): diagnose, permute (only steer swaps reach 0).
- 2026-11-14 opus:high:
  - no cast: 5
  - u8/s32 local: 13
  - u8 parameter (stand-in prototype): entry home + lbu, worse
## Evidence
- `andi a0,a1,0xff` before `jal healthRefill` (0x3b4)
- `sw a1,52(sp)` in the delay slot (0x3b8)
- `lw a1,52(sp)` at 0x3c4
- `move a0,a1` in the delay slot of `jal mapExecuteDeathTransition` (0x49c/0x4a0)
