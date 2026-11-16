# spawnNodeActorOutOfRangeOrHidden (global, src/global/1295B0.c)
## Sites
- global:807280C8:dead-store:6a6ccf (was `dx = 0.0f;` after the compare): FIXED (HackspawnNodeActorOutOfRangeScaled2). The squared distance is written inline in the compare, `ret = rangeSq < (camX - x)*(camX - x) + (camY - y)*(camY - y) + (camZ - z)*(camZ - z);`, with no dz/dx/dy locals.
## Attempts
- 2026-11-09..11 Clean1295B0 / ActorTypes / Rev17N opus-5-5:low: diagnose (store forwarding, Q0492/Q0499), permute best=0 only via other dead defs, removal best 160.
- 2026-11-14 HackspawnNodeActorOutOfRangeOrHidden opus-5-5:high: bare tests, u8 ret, short-circuit return, sibling ret = 0; if (cmp) ret = 1 form, statement/sum orders with locals, ?:, distance local, one-case switch, inline dy load (18), early return: 8-27.
- 2026-11-15 HackspawnNodeActorOutOfRangeScaled opus-5-5:high: && chain forms (6, ret t0 vs v1), permuter 900 s on the && form (235).
- 2026-11-16 HackspawnNodeActorOutOfRangeScaled2 opus-5-5:high (variants.py try): 60-body grid (each difference inline or a local x local order x 6 sum orders) on the hack-free sequential form: one inline difference 9-22, x and y inline 1-19, all three inline: z-first sums 6-16, x, y, z order 0 (applied).
## Evidence
- Target: FP sum before mtc1 a1 / cvt.s.w, c.lt.s, move v1,zero / li v1,1, bnezl v1 at 0x3888; node in a3 (move a3,a0, no home), actor in a2.
- With dz/dx/dy locals uopt forwards `ret = cmp` into the `ret == 0` test (Q0499): the compare result gets its own register (a2) and node a home. With the loads inside the compare expression the forwarding does not happen, so no dead def is needed. Likely cause, not traced: the expression now holds memory loads, and Q0510 lists has_ilod as a propagation blocker.
