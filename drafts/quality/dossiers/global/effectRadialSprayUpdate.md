# effectRadialSprayUpdate (global, src/global/11BC10.c)

## Sites
global:8071ABDC:other:14c742 other (fixed 2026-11-16): angleDeg was reused for the X velocity (sin * 2.5). Fixed by an `f32 offsetX` local declared right after angleDeg with the unused pads pad3C and pad28 both removed.

## Attempts
2026-11-14 Rereview11BC10b anthropic/claude-opus-5-5:high: separate offsetX local full=9 (4 in the pad3C slot).
2026-11-16 HackeffectInterpolationUpdate2 anthropic/claude-opus-5-5: offsetX at pad3C position (pad3C removed, pad28 kept) 4; after angleDeg 2; after offsetZ 4; pad3C kept + offsetX 11; offsetX before angleDeg + pad28 removed 2; after angleDeg + pad2E removed 4; after angleDeg + pad28 removed 0 -> kept. Redundant (f32)/(f64) casts and `+=`/`*=` forms 0 (`+= -0.63` keeps add.d with the negative constant, Q0376).

## Untried ideas
None for the site.

## Evidence
Pads pad80[4][4], pad40[4][4], pad2E still reproduce the frame; offsetX takes the two removed pads' slots.
