# camUpdateFollowBlend (global, src/global/201B0.c)
## Sites
- global:80624CA4:other:1b5c98 (kept, diagnose nohit 2026-11-16): dead `dist++` in cases 1/4/5.
  - It is a use of dist that the case 3/11 def reaches across a join an uninitialised path also reaches, so copy propagation keeps the `ustr dist`; the ucvt of `dz*dz+dx*dx` (candidate 46) then has two uses, becomes a global candidate and is assigned reg 1 ($v0, `mfc1 v0` at 0x98bc). Without it 46 is no candidate: ugen temp $t0, every later t-register shifts by one.
## Attempts
- rounds Clean201B0/5/16 (opus:low): plain, diagnose, permute; see history.
- 2026-11-14 opus:high (full=):
  - declaration at 8 positions: 61-65
  - block scope: 61
  - declared at the top: 69
  - a second read in the same block (CSE'd): 61
- 2026-11-16 U HackcamComputeEyeFocus5 anthropic/claude-opus-5-5:high:
  - dead `dist++` placement map: after the first switch, second-switch case 2, attachMode if/else join, function end -> 0; same block after distScale -> 61; first-switch case 7 (not reached by the def) -> 61.
  - dead defs elsewhere (`s32 dist = 0;`, `dist = 0;` in the attachMode else arm) -> 61.
  - sin arguments through dist (`dist = (1.0 - unkE8/unkEA) * 1024.0; mathSinF(dist)`): both case groups 69, one group 64/68 (separate webs, dist stays t0).
  - clampedScale on `dist * 0.001` in both ternary arms or as if/else -> 61 (copy-propagated).
  - dropping the two `(s16)` casts on the mathSinF arguments -> 0 (implicit conversion to the s16 parameter); kept as explicit angle narrowing.
## Untried ideas
- None that is natural C: the target has no code use of dist after 0x98c4, and only a use reached through an uninitialised-path join colours it.
## Evidence
- dist is not read after the increment on the 1/4/5 -> 10/12/13 path.
