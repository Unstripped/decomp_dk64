# collisionCheckTriangleContainsPointXZ (global, src/global/6AD90.c)
## Sites
global:80669E04:other:0fc400 `for (i = 0, sideC = 0; i < 3; i++)`: dead `sideC = 0` makes sideC (home sp+0x74, M -84) uopt candidate 38 so it takes a0 and sideP (cand 103) a1. Until 2026-11-16b it was hidden inside the `// LAYOUT:` comment of `i = 0; sideC = 0; do {` and no site counted it.
global:80669E04:noop-arith:58f1bd `a = (tri->x[1] + tri->x[2]) * 0.5;`: a holds the x edge midpoint (f2, never stored), later the side product (x - ox) * dz. A separate local gives the same instructions but adds an f64 slot. The kind is noop-arith only because the tool matches `* 0` in `* 0.5`.
global:80669E04:noop-arith:3aa4ac `b = (tri->z[1] + tri->z[2]) * 0.5;`: the same for z (f12).
## Attempts
2026-11-09 CleanD5E10 opus:low: w1 -> pad.
2026-11-14 PolishGlobal6AD90Names opus:high: params tri/x/z.
2026-11-16b HackcollisionCheckTriangleContainsPointXZ opus:high:
- loop: the sibling fix `for (i = 0, sideC = 0; i < 3; i++)` replaces `i = 0; sideC = 0; do { ... i++; ... } while (i != 3);` with its LAYOUT join: fdiff 0. The (f64) casts on the a/b midpoints dropped: fdiff 0.
- dead init, value classification (Q0908): `sideC = 1`, `sideC = -1` and the chained `sideC = i = 0` all fdiff 0, so it is a first-appearance lever and any dead value works. `sideP = 0` in the header: 10. `i = sideC = 0`: 11 (steals the v0 of i). No init: 10 (sideP cand 100 a0, sideC cand 106 a1; the cfe switch temp M -96 takes index 38). The sideC test before the sideP test: 122. c computed before a/b: 95. c and its sideC test before a/b: 92.
- a/b: hx/hz declared before a: 6 lines (frame 0xd8 only, args at sp+0xdc/0xe0). After i, or in place of pad: 33. f32 edge-sum locals sumX/sumZ (`cx = (tri->x[0] + sumX * 0.5) * 0.5`) in 4 declaration places: 58-69. The frame stays 0xc8, but the spill homes move 4 bytes down and the sum takes f2 instead of f4. The same with c inlined: 151.
- reconstruct (natural, as the box sibling): midX/midZ, px/pz, ternary sides, no init, no pad: 43. The same with the dead init kept: 33.
- variants scan: 48 variants, zeros only neutral (swaps, `0.0f`, outside u8/u16, pad widths, 7 decl swaps).
## Untried ideas
A spelling that drops one f64 local above dx without changing code. A real reason for the reuse (an older layout with fewer f64 locals).
## Evidence
Frame 0xc8. Homes in declaration order: cx 0xc0, cz 0xb8, a 0xb0, b 0xa8, dx 0xa0, dz 0x98, ox 0x90, oz 0x88, c 0x80, sideP 0x7c, outside 0x78, sideC 0x74, i 0x70, pad 0x6c; switch temp 0x68; spill homes 0x44-0x64 and an f64 at 0x38.
dx/dz/ox/oz are loaded uninitialised (ldc1 f12,0xa0 / f14,0x98 / f16,0x90 / f18,0x88 at 0x3e18-0x3e28) and stored back at 0x3fc4-0x3fd0. These four homes are fixed, so exactly four f64 slots sit above them and 28 bytes (c + 5 words) below.
Midpoints: add.s f4,f16,f18 at 0x3da8, mul.d f2 at 0x3dc8 (a), mul.d f12 at 0x3ddc (b). The homes of a (0xb0) and b (0xa8) are never accessed, so the own-home ORIG rule does not apply.
-zdbug:6 with init: outside (0) v1, i (35) v0, sideC (38) a0, sideP (103) a1. Without the init: sideP (100) a0, sideC (106) a1.
