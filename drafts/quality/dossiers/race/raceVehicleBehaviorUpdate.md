# raceVehicleBehaviorUpdate (race, src/race/1770.c)
## Sites
- race:80026F04:other:553e95 -> race:80026F04:other:c924a2 (kept, respelled).
  - The unk39 timer copy into bumpX is gone; unk39 is now read directly.
  - The 300.0f amplitude now sits in `off`, tagged FAKE: it is a colouring steer (lead decision 2026-11-14).
- race:80026F04:other:c924a2 fixed (2026-11-14 Polishrace1770, base 1afc6500): `off = 300.0f` removed, both
  shake products take the literal `300.0f`; `off` (now only the grid node Y offset) renamed `nodeYOffset`.
## Attempts
- round 22 (opus:low): literal (r1) and own local (r2) both fdiff 1 (shakeAngle spilled to sp+0x72); permute none.
- 2026-11-14 U HackraceVehicleBehaviorUpdate opus:high (variants.py try full=):
  - unk39 direct with the amplitude in: off / bonus / bumpX / bumpY 0, bumpZ 16, new local amp 6
  - unk39 kept in bumpX with the amplitude in another existing local: 22
  - literal with shakeAngle at 9 declaration positions or s32/u16: 22+
  - new function-scope amp local at 6 positions: 2-23
  - block-scoped amplitude: 2 (spill `sw/lw v1` at 68 vs 64)
- 2026-11-14 Polishrace1770 opus:high (variants.py try full=, base 1afc6500): plain literal on the
  stunTimer-direct body 0 (`300.0f` x2, `300` x2, mixed, `300.0f * sin`); whole-file fdiff 0, clint uninit 0.
  Re-adding a `bumpX = stunTimer` float copy with the literal: 24.
## Untried ideas
- None: the site is fixed.
## Evidence
- Target materialises 300.0f twice (`lui at,0x4396` at 0x1ac0 and 0x1ae4), i.e. the constant is propagated;
  shakeAngle lives in s0 (`trunc.w.s` -> `mfc1 s0` at 0x1aa0).
- The sp+0x72 shakeAngle spill seen with the literal belonged to the `bumpX = unk39` float timer copy form;
  once unk39 (stunTimer) is read directly the literal matches. The respell that removed the copy kept the
  amplitude in a local without re-measuring the plain literal.
- Any extra local home pushes the spill area down a word (Q0521).
