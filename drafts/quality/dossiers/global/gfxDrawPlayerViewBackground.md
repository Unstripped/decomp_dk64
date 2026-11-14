# gfxDrawPlayerViewBackground (global, src/global/109660.c)
## Sites
global:8070835C:dead-if:7a2e85 (`if (gGfxBufferIndex == 0) {}` before the 0xBE test): REMOVED.
- The dead read only closed a basic block, so that `!(flags & 2)` stays in a1 and the draw flag in a2.
- A one-case `switch (gCurrentMap) { case 0xBE: forceClear = 0; break; default: forceClear = 1; break; }` gives the same block split (Q0523).
## Attempts
- round 10/17/34 (opus, opus:low, opus:medium): remove/cond (a1/a2 swap); permute best=0 only with a do {} while (0); classify class 1; `|=` rewrites.
- 2026-11-14 HackgfxDrawSkySprite (opus), variants.py try (lines off):

  | variant | lines off |
  |---|---|
  | dead-if removed | 7 |
  | ternary | 7 |
  | function-scope forceClear | 7 |
  | = 1 initialiser plus if | 8 |
  | = 1 initialiser plus switch | 8 |
  | if/else on != | 12 |
  | != 0xBE expression | 14 |
  | clearView computed after forceClear | 24 |
  | single \|= expression | 82 |
  | switch with default | 0 |

## Untried ideas
none (fixed).
## Evidence
fdiff 0 and raw words equal with the switch form.
