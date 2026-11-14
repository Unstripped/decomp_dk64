# camUpdateFollowBlend (global, src/global/201B0.c)
## Sites
- global:80624CA4:other:1b5c98 (kept): dead `dist++` in cases 1/4/5.
  - Its def in a second block makes dist a uopt-coloured variable ($v0); without it dist is a ugen temp ($t0).
## Attempts
- rounds Clean201B0/5/16 (opus:low): plain, diagnose, permute; see history.
- 2026-11-14 opus:high (full=):
  - declaration at 8 positions: 61-65
  - block scope: 61
  - declared at the top: 69
  - a second read in the same block (CSE'd): 61
## Untried ideas
- A real second def or use of dist in another block. No same-meaning value exists in the current cases.
## Evidence
- dist is not read after the increment on the 1/4/5 -> 10/12/13 path.
