# camUpdateFollowBlend (global, src/global/201B0.c)
## Sites
- global:80624CA4:other:1b5c98 (FIXED 2026-11-17, diagnose fixed): dead `dist++` in cases 1/4/5.
  - It was a use of dist that the case 3/11 def reaches across a join an uninitialised path also reaches, so copy propagation kept the `ustr dist`; the ucvt of `dz*dz+dx*dx` (candidate 46) then had two uses, became a candidate and took reg 1 ($v0, `mfc1 v0` at 0x98bc). Without it 46 had one use: ugen temp $t0, every later t-register shifted by one (61 lines).
  - Real cause: the `dz`/`dx` locals made dist's stored expression ilod-free, so uopt copy-propagated it into the `cvt.d.w` and dist died. Writing the deltas inline (`CAM_SQ(target->z - st->eyeGoalZ) + CAM_SQ(target->x - st->eyeGoalX)`) puts uilod nodes in the expression; `find_replacements` refuses it (has_ilod, Q0510), so `distSq` stays a variable: candidate bit 29 `{1095|0}` -32vreg, adjsave 2.0 (def + use), live only in bb7, coloured uopt 1 = $v0. fdiff 0 with no tag.
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
- 2026-11-17 "2026-11-17: cleanup CleancamUpdateFollowBlend" CleancamUpdateFollowBlend anthropic/claude-opus-5-5 (variants.py try, full=):
  - hack removed, nothing else: 61 (variants.py scan of that body: best 57, s8/s16 width of dist; no zero).
  - lever (a) copy defs: `distScale = dist; distScale *= 0.001;` 61; `distScale = (s32)(dz*dz + dx*dx); distScale *= 0.001;` 61; `distScale = (dist = dz*dz + dx*dx) * 0.001;` 61; `0.001 * dist` 61; clamp refined in place (`clampedScale = distScale; if (clampedScale > 1.0) clampedScale = 1.0;`) 88.
  - `register s32 dist;` 61.
  - diagnostic: unrelated copy `dist = st->unkE8;` feeding the case 10/12/13 sin argument: 67 (steer, rejected anyway).
  - lever (c) not applicable: gCamEyeBlendRate/gCamFocusBlendRate are read by camUpdateFollow, camUpdateEyePos, camUpdateFocusPos and others in 201B0.c.
  - **inline field-load deltas, dz/dx removed: 0.** Spelled with one macro `#define CAM_SQ(x) ((x) * (x))` (Q0716) above the function: 0, fdiff OK. Sum order x-first (`CAM_SQ(x - ...) + CAM_SQ(z - ...)`): 4.
  - permuter from the hack-free removal body (dz/dx kept), hack-free weights, -j 2, 900 s, 32001 iterations: base 315, best 20 (adds an unused `new_var` local), no zero.
## Untried ideas
- None for this function: no hack sites remain.
## Evidence
- Target 0x987c-0x98cc: lwc1 z(132,v1)/eyeGoalZ(140,a1)/x(124,v1)/eyeGoalX(132,a1); sub.s $f0 (z delta) at 0x988c, sub.s $f2 (x delta) at 0x9898; mul.s/add.s; trunc.w.s $f18 at 0x98b8; mfc1 v0 at 0x98bc; mtc1 v0,$f4 at 0x98c4; cvt.d.w at 0x98cc; mul.d by 0.001 (.rodata 0x890) into $f12.
- dist is not read after the cvt.d.w; second-switch cases 1/4/5 and 10/12/13 share one jump-table target (0x9cec), so no code ever existed for the dead increment.
- uopt -l5 at the fix: bit 29 (distSq) adjsave 2.0, interferes with 6 and 0, live bb7, -> 1; bits 33/37 (deltas) adjsave 3.0 live bb7 -> 24/25.
