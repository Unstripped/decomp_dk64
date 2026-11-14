# effectInterpolationUpdate (global, src/global/11BC10.c)
## Sites
global:807186C8:other:77b85f -> 6e5dc3: the progress read in the interpolation loop. The target is `mul.s $f16,$f14,$f12` (progress first). Arrow access swaps the operands; `*(f32 *)` and `(*p).progress` keep them. Now spelt `(*effect->interp).progress` through the typed union member (KEPT).
## Attempts
2026-11-14 HackeffectInterpolationUpdate opus-5-5:high: typed member + arrow 15; product/sum operand orders 11-26; parens/(f32) 15; end - (end - start) * p 28; compound assignments 48/70; delta local 58; snapshot local 54; lerp form 63; unrolled 158; as1probe scan 0 improve
## Untried ideas
A different state layout where progress is not an offset-0 struct member (a union with f32 *) would also need the deref form. None natural found.
## Evidence
Loop copies at expected lines 110/123: `lwc1 $f14,0(t6)` then `mul.s $f16,$f14,$f12`. The ugen records already carry the order (as1probe).
