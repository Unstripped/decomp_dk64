# effectSineHorizontalDriftUpdate (global, src/global/11BC10.c)

## Sites
global:8071B2EC:other:6881fc other: `speed = 0.35f; effect->y += speed * 0.5;` keeps lwc1 0.35f (rodata, 0x4444) -> cvt.d.s $f4 (0x4454) -> mul.d by 0.5 (lui 0x3fe0, 0x445c) -> add.d into y. Now `// ORIG:` with these offsets (not a site).

## Attempts
2026-11-14 PolishGlobal11BC10Views opus-5-5:high: plain nohit (tagged the untagged steer).
2026-11-14 PolishGlobal11BC10Views2 opus-5-5:high: diagnose nohit (cfe folds every literal spelling).
2026-11-15 HackeffectSineHorizontalDriftUpdate2 opus-5-5:high: variants.py try: `0.35f * 0.5`, `(f32)0.35 * 0.5`, `(f64)0.35f * 0.5` -> full=45 text=45; separate `f32 riseSpeed;` declared before speed -> 3; declared after speed -> 0; `f32 speed = 0.35f;` initialiser -> 0; `speed / 2.0` -> 0. Conclusion: an f32 object holding 0.35f is the target's own op; reusing `speed` is not the steer. FAKE -> ORIG (cited offsets); fdiff 0, clint uninit 0.

## Untried ideas
none open for this site.

## Evidence
expected/build/src/global/11BC10.o: 0x4440 lui/0x4444 lwc1 $f18,664(.rodata) = 0.35f; 0x4454 cvt.d.s $f4,$f18; 0x4448/0x444c/0x4450 0.5 double built in $f6/$f7; 0x445c mul.d; 0x4468 add.d with cvt.d.s(y). allocation reloaded from 900(s0) at 0x442c, 0x44b0, 0x44e4, 0x450c (the (MotionState *) casts on void * are per use, kept). Sibling effectUpwardDriftUpdate uses the same `speed = 0.35f; y += speed * 0.5;` form untagged.
