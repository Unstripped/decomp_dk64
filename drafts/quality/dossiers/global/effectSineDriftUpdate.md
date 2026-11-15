# effectSineDriftUpdate (global, src/global/11BC10.c)

## Sites
global:8071B44C:other:6881fc other: `speed = 0.35f; effect->y += speed * 0.5;` keeps lwc1 0.35f (rodata, 0x457c) -> cvt.d.s $f8 (0x458c) -> mul.d by 0.5 (0x4594) -> add.d into y. Now `// ORIG:` with these offsets (not a site).

## Attempts
2026-11-14 PolishGlobal11BC10Views opus-5-5:high: plain nohit (tagged the untagged steer).
2026-11-14 PolishGlobal11BC10Views2 opus-5-5:high: diagnose nohit (cfe folds every literal spelling).
2026-11-15 HackeffectSineHorizontalDriftUpdate2 opus-5-5:high: variants.py try: `0.35f * 0.5`, `(f32)0.35 * 0.5` -> full=29 text=29; `f32 riseSpeed;` after speed -> 0; `f32 speed = 0.35f;` -> 0. FAKE -> ORIG (cited offsets); fdiff 0, clint uninit 0.

## Untried ideas
none open for this site.

## Evidence
expected/build/src/global/11BC10.o: 0x4578 lui/0x457c lwc1 $f6,680(.rodata) = 0.35f; 0x458c cvt.d.s $f8,$f6; 0x4594 mul.d by 0.5 ($f10/$f11 = 0x3fe0...); 0x45a0 add.d into y. Same idiom as effectSineHorizontalDriftUpdate and untagged effectUpwardDriftUpdate.
