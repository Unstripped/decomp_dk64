# playerInputStepTurnFacingAngle (global, src/global/E4090.c)
## Sites
- global:806E65BC:other:f86253 `ang ^= 0;`: keeps ang out of the pad-index web. Without it: 16.
## Attempts
- CleanE4090, Rev16J (opus:low): plain, diagnose, permute.
- 2026-11-14 U, scored with variants.py try (full=):
  - bare-vs-!=0 tests: 16 (6 combined with the pad pointer)
  - pad pointer used only for the stickAbsX test (try/best_pad.c): 6
    - the remaining diff: target hoists `li a2,0x10` (the first call's 3rd argument) to 0x727c, before the test; ang then takes v0
  - pad-pointer grid (864 bodies): 6 at best
  - ang width / placement: 16 or worse
  - block-scoped argument locals: 6
  - target initialiser: 41+
  - rollStep `?:`: 18
## Untried ideas
- what makes uopt hoist the li a2,0x10 constant above the stickAbsX test (compare a uopt -l 6 trace of best_pad vs the base)
