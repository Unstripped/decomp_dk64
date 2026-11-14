# actorCollisionCheckNodeSpheres (global, src/global/79890.c)
## Sites
- global:80674E14:dead-if:d43e8d dead-if: REMOVED.
  - `selfX = 0; if (selfX) {}` made selfX first in the IR (candidate bit 6, ahead of selfY's bit 9), so selfX took s7 and selfY s8 while the source loaded scaledY first.
## Attempts
- round 22 (opus): remove nohit, cond nohit, classify kept (class 1).
- 2026-11-14 U HackactorCollisionCheckNodeSpheres anthropic/claude-opus-5-5:high (variants.py try full=):
  - dead pair dropped, Y-first loads: 6 (s7/s8 swapped)
  - 24 load orders without the dead pair: X,Y,Z,R 2 (registers right, X/Y loads in the wrong order); others 6-20
  - 23 declaration orders on X,Y,Z,R: 2-4
  - selfCollision-> reads at each use: 131
  - X,Y,Z,R with X and Y on one line: 0, applied with a LAYOUT comment. The xyz, xyzr and xy+zr joins are also 0; joins yz, zr, or the selfCollision line give 2.
## Untried ideas
- none: site removed.
## Evidence
- Target 0x2b4-0x2e4:
  - `lw t6,0x140(a0)`; selfCollision spilled to 0x78(sp)
  - `lw t8,8(t6)` (Z, spilled to 0x90), then `lw s8,4(t6)` (Y), then `lw s7,0(t6)` (X)
  - `lw t9,0xc(t6)` (radius, spilled to 0x8c)
- uopt -zdbug:6 candidate bits, selfX (home -16) / selfY (home -20):
  - base with the dead pair: 6 / 9
  - dead pair dropped: 10 / 6
  - field order: 6 / 10
- as1probe scan on the field-order body:
  - deleting `.loc 67` (the selfY line) gives 0, i.e. join the two statements onto one line;
  - so does swapping the X/Y load records, but in C that means Y-first statement order, which swaps the registers.
