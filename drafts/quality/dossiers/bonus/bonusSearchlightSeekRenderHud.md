# bonusSearchlightSeekRenderHud (bonus, src/bonus/2690.c)

## Sites
bonus:8002CC08:do-while0:e9a088 do-while0 (FIXED 2026-11-17): the empty `do {} while (0)` in `case 7:` let cfe's
nested-call temp for `textDrawAnimated(...)` (an argument of `hudDrawRollingCounter`) reuse the switch-selector temp
word (-48vreg, sp+0x58). Without it that temp takes a fresh -52vreg (sp+0x54) and the three uopt spill stores move
down one word (`sw v1,0x50 -> 0x4c`, `sw v0,0x54 -> 0x50`, `sw t0,0x4c -> 0x48`, first at 0x6724). Fixed by
un-nesting the call into two `gdl = f(gdl, ...)` statements: no nested-call temp, so the frame matches with the steer gone.

## Attempts
2026-11-10 round 8 CleanBonus2690 opus-5-5:low: remove/cond/pad local at each of 7 declaration positions -> nohit
2026-11-11 round 10 Rev10F opus-5-5:xhigh: permute -> best=0 only by restoring the do/while(0)
2026-11-11 round 16 Rev16H opus-5-5:low: drop do/while (case 7: break) -> fdiff 1 (spills one word lower); permute best=0 only with `if (1) {}`
2026-11-11 round 17 Rev17N opus-5-5:low: removed; uopt colouring unchanged; permute best=0 swaps in `if (subExt->unk23) {}`
2026-11-13 round 36 CleanBonus2690 opus-5-5:xhigh: permute on `case 7: break` -> dead `if (!actor) {}` before case 1 (Q0712, Q0720)
2026-11-17 cleanup CleanbonusSearchlightSeekRenderHud anthropic/claude-opus-5-5: `case 7: break;` + un-nested
  `gdl = textDrawAnimated(gdl, ...); gdl = hudDrawRollingCounter(gdl, ...);` -> fdiff 0 (variants.py try full=0).
  Also scored: un-nest keeping the do/while 0; case 7 moved after case 0/1 (un-nested) 0; `case 7` removed 134
  (127 un-nested: the target compares 7); `case 7` last without un-nesting 8.

## Untried ideas
none left for this function (no hack sites remain).

## Evidence
- Frame 136; gdl home sp+0x88 (P 0vreg), subExt spilled sp+0x84 (-4), projX/projY sp+0x80/0x7C, state -16,
  screenX/screenY sh at sp+0x76/0x74 (-18/-20), six gbi `_g` homes -24..-44, switch selector temp -48.
- Spill stores of the s16 sprite coords: `sw v1,80(sp)` 0x6724, `sw v0,84(sp)` 0x672C, `sw t0,76(sp)` 0x67A8.
- Switch dispatch is a compare chain on `lbu v1,340(s0)` (0x68D8): 0 and 1 -> 0x6904, `li at,7; beql v1,at` at
  0x68F0/0x68F4 -> epilogue, default `b` -> epilogue: case 7 is a real compared value.
- `(f32)(projX * 4.0)`: `mul.d` by 4.0 then `cvt.s.d` (0x6614/0x6620) then `trunc.w.s` (0x662C/0x6638): the f32 casts
  are the target's conversions.
- uopt -l5 census (`isvar M ... vreg`): base 11 M vregs, -48 written twice (selector and `ustr -48 <- R2` nested
  result); `case 7: break` 12 (adds -52 = nested result); fixed copy 11, -48 selector only; un-nested with the
  do/while kept 11 (do/while then has no effect).
