# playerInputStepTurnFacingAngle (global, src/global/E4090.c)
## Sites
- global:806E65BC:other:f86253 `ang ^= 0;`: fixed 2026-11-16 (HackplayerInputStepTurnFacingAngle2): `ang -= stickX / 2; gCurrentActor->yaw = (s16)ang & 0xFFF;`.
## Attempts
- CleanE4090, Rev16J (opus:low): plain, diagnose, permute.
- 2026-11-14 U, scored with variants.py try (full=):
  - bare-vs-!=0 tests: 16 (6 combined with the pad pointer)
  - pad pointer used only for the stickAbsX test (best_pad): 6
    - the remaining diff: target hoists `li a2,0x10` (the first call's 3rd argument) to 0x727c, before the test; ang then takes v0
  - pad-pointer grid (864 bodies): 6 at best
  - ang width / placement: 16 or worse
  - block-scoped argument locals: 6
  - target initialiser: 41+
  - rollStep `?:`: 18
- 2026-11-16 HackplayerInputStepTurnFacingAngle2 (opus:high), uopt -l 6 + variants.py try:
  - trace: base colours ang (candidate 0) second, reg 1 (v0); best_pad colours the pad pointer first and ang late into a2, so `li a2,0x10` cannot move above the test. The li hoist is a consequence of ang's register, not a constant web.
  - an in-place store to ang inside the block gives the same web split as the xor: `ang -= stickX/2;` then
    - `yaw = (s16)ang & 0xFFF` (s32 ang): 0 (applied)
    - `yaw = ang & 0xFFF` / `(u16)ang & 0xFFF` / `(u16)(ang & 0xFFF)`: 41-43 (scratch ring one temp behind: subu t5 vs t6 at 0x72a8)
    - s16 ang, `yaw = ang & 0xFFF`: 2 (rollStep spill 0x1a vs 0x18: slots go by declaration order); plus an unused `s16 pad;` after ang or target: 0
    - pad-pointer combinations: 65
  - base without xor, cast (s16) or none on `(ang - X)`: 54
## Evidence
- target 0x7264 `lh v0,0xe6(v1)` (ang in v0), 0x727c `li a2,0x10`, 0x72a8 `subu t6,v0,t4`, 0x731c `sh t1,0x18(sp)` (rollStep spill).
