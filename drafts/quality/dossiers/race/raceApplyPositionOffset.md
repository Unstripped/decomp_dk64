# raceApplyPositionOffset (race, src/race/1770.c)
## Sites
race:80026098:noop-arith:21d1f3: fixed 2026-11-17f (CleanraceApplyPositionOffset): `f32 dist = sqrtf(...)` in the dropped pad word, `offsetDist = gCurrentActor->speedXZ * 0.03 * dist;`; no hack site left.
## Attempts
2026-11-11/12 rounds 16, 17, 22, 23 (opus:low): plain, diagnose, as1probe, permute (see history).
2026-11-14 HackraceApplyPositionOffset opus:high: plain field with every operand order ((speed*0.03)*sqrt, 0.03*speed: 10/23), sqrt and speed product in separate statements or locals (dist local 10, f32 scale local in the pad slot 38, f64 scale 72, offsetDist *= ... 10), f32 speed snapshot local (50, in the pad slot 46), Actor *actor local (38), (f64) casts on either operand (10), dz/dx statement and declaration orders (10-18), dx*dx first in the sqrt (17), no parentheses (27)
2026-11-17 2026-11-17: cleanup CleanraceApplyPositionOffset (opus): cfe ucode census (as1probe ucode --cfe) pun vs plain; dist local holding sqrtf with the speed product written FIRST (`speed * 0.03 * dist`): fdiff 0 both with dist declared last (pad kept, dist at Mmt -24) and with dist in the pad word (pad dropped, Mmt -8; kept). Reverse order `dist * (speed * 0.03)` 10; no dist, `speed * 0.03 * sqrtf(...)` 10. Hack-free permuter from the plain body (900 s, base 70).
## Untried ideas
none (site fixed).
## Evidence
target 0x9cc-0x9d8: cvt.d.s f6 (speedXZ), mul.d f10,f6,f8 (* 0.03), mul.d f18,f10,f16: the speed product is the left operand of the outer product and sqrt (f16) the right.
cfe ucode (t.B): with the punned `*(f32 *)&` load cfe evaluates the speed operand first and parks the sqrtf result in a cfe temp (`cup; lod Rmt $f0; str f32 Mmt -24` ... `mpy f64` (speed*0.03); `lod Mmt -24; cvt f64 f32; mpy f64`), so the mpy is (speed product, sqrt). The plain field emits `lod Rmt $f0; cvt f64 f32` first (a call operand is evaluated first whatever the written order) and the mpy is (sqrt, speed product): 10 lines (f10/f16 swap in the x store too). A named local for the sqrt result gives the pun ucode exactly (dist at Mmt -8 in place of the temp at -24, plus one `.loc`); cfe then keeps the written order of the two plain operands (Q0737, Q1159), so the source order speed-first is the target order.
