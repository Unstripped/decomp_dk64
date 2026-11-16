# effectSpiralRiseUpdate (global, src/global/11BC10.c)
## Sites
global:80719C00:other:fccd20 other: `clampedAlpha = 255.0f` reuse plus a one-line statement group: the redefinition of clampedAlpha killed uopt's forwarding of the stored `alpha - clampedAlpha` so `alpha = newState->alphaLevel` stayed a real reload (lwc1 $f0,20(v0) at 0x2dfc), and the shared .loc kept as1's `li t4,1`/`li t2,1` order at 0x2dbc/0x2dc0. REMOVED (2026-11-15).
global:80719C00:other:3658da other: `state = newState;` second pointer with mixed reads, gave `move v0,v1` at 0x2db4. REMOVED (2026-11-15).
## Attempts
2026-11-14 Rereview11BC10b Rereview11BC10b anthropic/claude-opus-5-5:high: tagged both; literal cap -> full=114, a ternary -> 143, one pointer (old head) -> full=27.
2026-11-15 U HackeffectDecelerateDriftUpdate anthropic/claude-opus-5-5:high:
- Q0375 head (field test, `state = heapAlloc(0x18)` inside, `state = effect->allocation` after) with one pointer, fccd20 kept: decl alpha,state,clampedAlpha -> full=3 (spill at 0x18 not 0x1c); state declared first -> fdiff 0.
- separate `maxAlpha` cap local (all 24 decl orders, one-line or multi-line if/else, initialised at decl) -> full=56-68: uopt forwards the stored sub.s into the reload (no lwc1 20(v0)) and recolours $f12/$f2/$f14.
- reuse kept, statements split over lines -> full=2 (li t2,1/li t4,1 swapped); only the if/else needs one line (L1/L3 -> 0).
- `state->alphaLevel -= clampedAlpha` with maxAlpha and an `alpha` reload local -> 11-12 (extra mov.s $f0,$f2); reading the field directly in the MIN and cap -> fdiff 0 with maxAlpha; then a literal ternary `(level > 255.0f) ? 255.0f : level` -> fdiff 0 without any cap local; `MIN(level, maxAlpha)` (reversed compare) -> full=5.
- final: `state->alphaLevel -= MIN(state->alphaLevel, 15.0f); effect->alpha = (state->alphaLevel > 255.0f) ? 255.0f : state->alphaLevel;`, += 0.3 / += 1.5, no (f32)/(u8)(u32)/(s16)(s32) casts -> fdiff 0.
## Untried ideas
none open: function is hack-free.
## Evidence
0x2cfc lw v1,900(a0) + bnezl: null test on the field load; 0x2d98 lw v1,900(a2): reload after the init block; 0x2db4 move v0,v1: v1 for the first alphaLevel read (0x2dcc lwc1 $f0,20(v1)), v0 for the store (0x2df8) and everything after, saved at 0x2f54 sw v0,28(sp). 0x2dfc lwc1 $f0,20(v0): real reload after the compound store. 0x2e1c cvt.w.s $f16,$f12 ($f12 = 255.0 from lui 0x437f) and 0x2ea0 cvt.w.s $f18,$f0: one u32 conversion per ternary arm, sb at 0x2e90/0x2f10. 0x2dbc/0x2dc0 li t4,1 then li t2,1: the two arms' rounding-mode constants hoisted by as1.
