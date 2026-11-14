# raceApplyPositionOffset (race, src/race/1770.c)
## Sites
race:80026098:noop-arith:21d1f3: kept; see Evidence.
## Attempts
2026-11-11/12 rounds 16, 17, 22, 23 (opus:low): plain, diagnose, as1probe, permute (see history).
2026-11-14 HackraceApplyPositionOffset opus:high: plain field with every operand order ((speed*0.03)*sqrt, 0.03*speed: 10/23), sqrt and speed product in separate statements or locals (dist local 10, f32 scale local in the pad slot 38, f64 scale 72, offsetDist *= ... 10), f32 speed snapshot local (50, in the pad slot 46), Actor *actor local (38), (f64) casts on either operand (10), dz/dx statement and declaration orders (10-18), dx*dx first in the sqrt (17), no parentheses (27)
## Untried ideas
none recorded.
## Evidence
target 0x9cc-0x9d8: cvt.d.s f6 (speedXZ), mul.d f10,f6,f8 (* 0.03), mul.d f18,f10,f16: the speed product is the left operand of the outer product and sqrt (f16) the right. uopt orders a commutative umpy by operand number (Q0737), and the punned *(f32 *)& load gives the speed product a different expression number than the plain field, so the plain spelling flips it to mul.d f18,f16,f10 and renames f10/f16 in the x store (10 lines)
