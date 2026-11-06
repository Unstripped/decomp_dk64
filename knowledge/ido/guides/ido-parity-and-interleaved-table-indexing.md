---
title: "IDO: parity extraction and interleaved float-table indexing"
description: "Destructive counter updates and table element types resolve a six-instruction register-allocation near-match without codegen hacks."
origin: "ok-fine dk64/notes/ido-parity-and-interleaved-table-indexing"
---
# Parity extraction and table element types

Two natural C changes resolved the stage-6 near-match in `spriteLinearInterpolateFrame` (205 instructions, 820 bytes). The old park had correct frame/control flow but six differing instructions; the final function needs no FAKE or LAYOUT constructs.[^source][^roadmap]

- Extract `k = t & 1` before `t >>= 1`, then test and index with the updated `t`. Keeping the unshifted counter and repeating `t >> 1` instead allocated the half-index to `$a0`; the destructive update gives parity in `$a0` and the half-index in `$t9` after as1 removes a forwarding move. A direct `* frac` then also gives the target floating-point operand order, without the old dead `(x0 = frac)` assignment.[^source]
- Represent the interleaved two-component table as `f32[]`, with `f32 *e = &table[t * 2]` and accesses `e[0]`, `e[2]`, `e[1]`, `e[3]`. An array of eight-byte structs calculates the same byte address but uses different ugen scratch registers. Float-element indexing fixes the final `$t1/$t2` versus `$t2/$t4` difference. Both operand scale and pointee type matter even when the resulting instruction shape is unchanged.[^source]
- Prefer the flat declaration to walking a cast float pointer through an array declared as structs: it makes the accessed scalar array explicit and removes the unnecessary local pair typedef.[^source]

Whole-object comparison reported TEXT OK; isolated and local full-ROM checks passed. A temporary ASan/UBSan harness exercised 4,366 synthetic cases covering interpolation and its cutoff, fade clamping, phase advancement, line wrapping, and asset initialization. This is a C smoke check, not emulator gameplay coverage.[^roadmap]

## Sources

[^source]: src/global/CBEA0.c @ 9b5df9026bd8
[^roadmap]: ROADMAP.md @ 9b5df9026bd8
