# jetpacStateGameOver (jetpac, src/jetpac/0.c)

## Sites
- c1a42b + ef3c2a: one file-level flagGet declaration that returns non-u8. It is needed only by jetpacUpdateStateAndInput (target `andi t9,v0,0xff` at 0x11d4), not by jetpacStateGameOver.

## Attempts
- 2026-11-14 U HackjetpacStateGameOver: under the header prototype, a per-function asm compare shows jetpacStateGameOver at 0 lines and jetpacUpdateStateAndInput at 97. The following all fdiff 0:
  - `s32 flagGet(s16, u8)`
  - `u32 ...`
  - `s16 ...`
  - `s32 flagGet()`

## Untried ideas
- An owner change of flagGet's return width across 49 files (header-request.md).
- Moving the declaration into jetpacUpdateStateAndInput (it is still a steer, and that function is not in this item).

## Evidence
- 135D30.o flagGet ends with `andi v0,t8,0x1`.
- Jetpac target at 0xd84 is `beqz v0` (jetpacStateGameOver); at 0x11d4 it is `andi t9,v0,0xff` (jetpacUpdateStateAndInput).
