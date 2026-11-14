# healthHudUpdateDraw (global, src/global/10D2D0.c)

## Sites
- **global:80708DA4:punned-cast:u07a38: FIXED.**
  - Replaced the `u8 *hud` byte view and the `(HealthStats *)hud` casts with `PlayerInventory *inv = &gPlayerInventoryTable[playerIndex]` and `KongInventory *kong = &inv->kong[idx]`.

## Attempts
- **2026-11-14 U Hack10D2D0HealthStats:** typed spelling, whole-object fdiff OK.
- Retyping healthApplyPendingDelta's 4th parameter to `KongInventory *` with a `newHealth` local grows its frame 0x38 -> 0x40. So `(s32)kong` stays at both calls.

## Untried ideas
- none

## Evidence
- The callee's 4th parameter (a3) is overwritten as newHealth before use, with no separate frame word.
