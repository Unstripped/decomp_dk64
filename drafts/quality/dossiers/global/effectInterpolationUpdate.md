# effectInterpolationUpdate (global, src/global/11BC10.c)

## Sites
global:807186C8:other:6e5dc3 other (kept, FAKE): `(*effect->interp).progress` in the lerp loop keeps `mul.s $f16,$f14,$f12` (progress `lwc1 $f14,0(t6)` first, diff `$f12` second) at 0x1948 and 0x197c; any `p->progress` gives `mul.s $f16,$f12,$f14` (full=15).

## Attempts
2026-11-14 HackeffectInterpolationUpdate anthropic/claude-opus-5-5:high: typed EffectNode union member interp, arrow vs deref-dot, snapshot local, commutative operand orders, compound assignments, unrolled loop, as1probe keep/scan -> nohit.
2026-11-16 HackeffectInterpolationUpdate2 anthropic/claude-opus-5-5: arrow 15; progress * diff 15; named f32 progress local in the loop 48, at function scope 48; product stored whole into a temp (`t = diff * p->progress; result = end + t`) 56-58; product into result[] then `+= end` 69/77; diff local 56-58; `diff * p + end` 26; `p * diff + end` 11; `end - (end - start) * p` 28; `(p->progress)` 15; view cast through allocation 15; `* 1.0f` 15; s16/u8 index 66, u32 15; do-while 15; one-line for 15. `p[0].progress` 0 and `(&p->progress)[0]` 0 (same deref steer as `(*p)`).
2026-11-16 same: retired the `((EffectInterpolationState *)effect->allocation)->increment` view cast (`effect->interp->increment += 0.001`, fdiff 0) and the 0.975 scale casts (`*= 0.975`, fdiff 0).

## Untried ideas
uopt_trace of the umpy candidate order for `p->f` vs `(*p).f` to locate where uopt reassociates (Q1130); only useful if a different natural expression shape exists.
Any loop restructure keeping the unrolled 3-iteration shape (named temps all break the unroll, shape 42-64).

## Evidence
0x1930-0x1994: unrolled loop, `lw t6,900(s0)` reloads effect->interp every iteration (no pointer local), `sub.s $f12,$f12,$f18` (start - end) then `lwc1 $f14,0(t6)`, `mul.s $f16,$f14,$f12`, `add.s $f14,$f16,$f18` (product + end).
