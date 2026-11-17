# effectSpiralDriftMatrixUpdate (global, src/global/11BC10.c)

## Sites
global:807195D4:other:e3556d other (fixed 2026-11-16): the start angle went through the reused offsetZ local (`cvt.s.w $f0,$f4` at 0x2704 colours with offsetZ's later web). Fixed by a dedicated `f32 angle` local that replaces the `SpiralDriftState *newState` pointer local; the angle store goes through the view cast like the rotation store already did.

## Attempts
2026-11-14 Rereview11BC10a anthropic/claude-opus-5-5:high: tagged; dedicated local or direct store changes the function.
2026-11-16 HackeffectInterpolationUpdate2 anthropic/claude-opus-5-5: direct store `newState->angle = speed * 2` 59 ($f0 -> $f6 colouring); dedicated angle local next to newState 10 at 4 declaration positions (frame 0xb8 -> 0xc0); s32 local 85; pad + direct store 67; reusing offsetX 50; angle local replacing newState (pointer local dropped) 0 -> kept. Also: `(f32) offsetZ` cast was redundant (0); redundant (s32)/(f32)/(f64) casts dropped and `+=` forms (0).

## Untried ideas
A typed union member for SpiralDriftState in EffectNode (render.h, header change) would retire the 7 remaining view casts.

## Evidence
0x26e4-0x2710: heapAlloc result v0 stored to 0x384(s0), `swc1 $f0,0(v0)` (angle through v0, no reload), then `lw t9,0x384(s0)` reload for rotation; frame 0xb8.
