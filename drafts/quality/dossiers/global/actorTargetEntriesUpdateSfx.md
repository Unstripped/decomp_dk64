# actorTargetEntriesUpdateSfx (global, src/global/68AA0.c)

## Sites
- 0e5c38: dead `if (D_807F9420 == 0) {}` at the loop top. REMOVED. An early `continue` on the type filter supplies the same extra block (Q0523).

## Attempts
- 2026-11-14 U HackactorTargetEntriesUpdateSfx: the early continue gives fdiff 0. Other forms, in fdiff lines:
  - Plain removal: 17.
  - Entry pointer local: 47.
  - Base snapshot local: 44.
  - Inner loop as a for: 13.

## Untried ideas
- None.

## Evidence
- Target: `andi s5,a1` (volume) and the D_807F9420 base in s4. Without the extra block they shift to s4/s6.
