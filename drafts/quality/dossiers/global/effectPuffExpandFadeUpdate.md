# effectPuffExpandFadeUpdate (global, src/global/11BC10.c)

## Sites
global:8071B89C:other:1ccab9 other (fixed 2026-11-16): `divisor = 4.0f` local kept `div.s`. Fixed by dividing by the int literal: `scale = (f32)timer / 4 * 3.0;`.

## Attempts
2026-11-14 Rereview11BC10b anthropic/claude-opus-5-5:high: literal 4.0f gives full=2.
2026-11-16 HackeffectInterpolationUpdate2 anthropic/claude-opus-5-5: `/ 4.0f` 2, `/ 4.0` 6, `(f32)4` 0 (odd spelling), s16/s32 limit local in clamp and divide 13, f32 limit 21, int literal `/ 4` 0 (with `>= 5` or `> 4` clamp, with or without the f64 cast chain) -> kept `(f32)timer / 4 * 3.0` with `timer > 4`.

## Untried ideas
None.

## Evidence
0x49a8-0x49c0: `lui at,0x4080; mtc1 at,$f8` then `div.s $f10,$f6,$f8`: cfe folds only a float-literal power-of-two divisor into a multiply (Q0240); an int literal converted by the usual arithmetic conversions is not folded.
