# spawnNodeActorOutOfRangeOrHidden (global, src/global/1295B0.c)
## Sites
global:807280C8:dead-store:6a6ccf dead-store: `dx = 0.0f;` kills uopt store-forwarding of the range compare into the `ret == 0` test; keeps ret a variable (v1, bnezl at 0x3888) and the node param coloured (move a3,a0 at 0x382c, no home)
## Attempts
2026-11-09..11 Clean1295B0 / ActorTypes / Rev17N opus-5-5:low: diagnose (store forwarding, Q0492/Q0499), permute best=0 only via other dead defs (arg1++/--, dz++/--), removal best 160 keeps node home
2026-11-14 HackspawnNodeActorOutOfRangeOrHidden opus-5-5:high: bare tests (17), u8 ret (25), short-circuit return expression (17), sibling form ret = 0; if (cmp) ret = 1 (16, integer rows match, FP order differs) x 6 statement orders x 4 sum orders (16-17), ?:/if-else (17), assignment in condition (17), distance local (17), dx reused for the sum (27), Actor snapshot local (21), one-case switch (22), inline dy load (18), (f32)rangeSq (17), early return (8), as1probe scan 2 rounds on the sibling form (no as1-only fix)
2026-11-15 HackspawnNodeActorOutOfRangeScaled opus-5-5:high: && chain with ret assigned once, ret = cmp; if (ret == 0) ret = A && B && C; (6: compare in v1 and all FP rows match, ret t0 instead of v1; ! spelling / assignment in the if 6, u8 13, split chains 22, ternary 23), far local + short-circuit return (18/19), if (far) return far (8), return ret ? ret : chain (8), ret || chain (17-18); permuter 900 s on the && form best 235 (semantics-breaking outputs only)
## Untried ideas
none natural: every kill of the forwarding is a dead def of a compare operand; the && chain form (6) is the closest hack-free shape, left with ret/temp uncoalesced (t0 vs v1)
## Evidence
Target: FP sum (mul/add) before mtc1 a1 / cvt.s.w at 0x385c/0x386c, c.lt.s, move v1,zero / li v1,1, bnezl v1 at 0x3888; node in a3 (move a3,a0), actor in a2 (lw a2,24(a0)).
uopt -zdbug:5 without the store: compare {518} becomes a candidate (adjsave 3.0, reg 5); node {1114} uncoloured (forbidden 1-6) -> home sw a0,24(sp).
