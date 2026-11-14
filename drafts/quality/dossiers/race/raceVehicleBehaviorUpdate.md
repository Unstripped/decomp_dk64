# raceVehicleBehaviorUpdate (race, src/race/1770.c)
## Sites
- race:80026F04:other:553e95 -> race:80026F04:other:c924a2 (kept, respelled).
  - The unk39 timer copy into bumpX is gone; unk39 is now read directly.
  - The 300.0f amplitude now sits in `off`, tagged FAKE: it is a colouring steer (lead decision 2026-11-14).
## Attempts
- round 22 (opus:low): literal (r1) and own local (r2) both fdiff 1 (shakeAngle spilled to sp+0x72); permute none.
- 2026-11-14 U HackraceVehicleBehaviorUpdate opus:high (variants.py try full=):
  - unk39 direct with the amplitude in: off / bonus / bumpX / bumpY 0, bumpZ 16, new local amp 6
  - unk39 kept in bumpX with the amplitude in another existing local: 22
  - literal with shakeAngle at 9 declaration positions or s32/u16: 22+
  - new function-scope amp local at 6 positions: 2-23
  - block-scoped amplitude: 2 (spill `sw/lw v1` at 68 vs 64)
## Untried ideas
- A natural form that colours shakeAngle without a constant held in a local. None found: literal 22, new local 2-23.
## Evidence
- Target materialises 300.0f twice (`lui at,0x4396`), i.e. the constant is propagated; the variable only affects colouring order.
- Any extra local home pushes the spill area down a word (Q0521).
