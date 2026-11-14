# actorCutsceneDispatchEvents (global, src/global/8F4B0.c)

## Sites
- da5663 / 2c5186 (one coupled proto-steer): a local `s32` return declaration of mapGetHubWorldIndex. With the header's u8 return, the frame grows 0x68 -> 0x70 (an extra home for the narrowed result).
- f3d39c: `if (D_80744700 == 0) {}` in case 0x1C. The target has no access there (0xcb4-0xcc4); the test only reshapes uopt blocks (event-array base t0, -1/0xFF temps).

## Attempts
- 2026-11-14 U HackactorCutsceneDispatchEvents (:high):
  - Return width isolated: s32 (u8,u8), u32 (u8,u8) and s32 (s32,s32) all match; any u8 return fails.
  - Owner retype bundle: 3C10.c OK, 8 callers OK, 6 callers fail -> blocked (header-request.md).
  - World locals of s32/u8/u32/s16/u16 at the call sites with the shared u8 prototype: all fdiff 1.
  - Untagged byte pun `((u8 *)eventData)[1]` fixed as `eventData[0]`.

## Untried ideas
- Re-spell the six failing callers of mapGetHubWorldIndex (36880, 478F0, 9DD70, ACDC0, B5EC0, C2A90) so they match with an s32 return, then retire both steers here.

## Evidence
- 3C10.o mapGetHubWorldIndex: `lbu v1` (0x12c, 0x17c) or `li v1,7`, then `move v0,v1`; no narrowing.
- 8F4B0 target: addiu sp,-104; case 0xB uses `sll t4,v0,1` (0xac0) and case 0x18 uses `move a0,v0` (0xca4), with no andi on either.
