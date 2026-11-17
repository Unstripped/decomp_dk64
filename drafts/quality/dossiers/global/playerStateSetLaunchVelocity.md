# playerStateSetLaunchVelocity (global:806ED6B0, src/global/EFDC0.c)

2026-11-17 PolishglobalEFDC0 (base e6b8a8da): re-review after Q0594 extension (b8cbd3fa). No change; fdiff 0.
- Q0594: `playerStatePlayAnimationByDamageType(queuedActor->actorType)` (u32 field, u16 param) = one `lhu a0,0x5A`
  (target 0x2C50): the plain field is right, no pun. Other narrow args: `playerSetKongByActorType(kongId + 2)` s16
  (sll/sra 16 at 0x2CA0), `playerSetSizeMode(actor, sizeMode)` u8 (`andi a1,v0,0xff` at 0x2934, so sizeMode stays
  an int selector), constants to `actorFindByType` u16 / `controllerAnimSetStateRemap` s16 / `slotQueueUpdate` u8.
- Q0218: `sizeMode = actorType == 0x28 ? 0 : 2` — `bne` with `li v0,2` in the delay slot, `move v0,zero` on the taken
  0x28 path: C order matches.
- Case 0x1C/0x6B/0x86 without an actor of type 0x25 falls into the 0x62 block (`beqz v0` → 0x28CC): real shared code.
- `actionTimer = D_807539DC[i] * 0.5` is cvt.d.w/mul.d/trunc.w.d: the double literal is the target's.
- Repeated `gPlayerSlots[gCurrentPlayerIndex].queuedActor` re-loads gCurrentPlayerIndex after each call in the
  target: no pointer local is live there.
- Open: PlayerState.unk50 (frames before playerApplyGravity applies gravity; also D5E10 swim idle countdown).
