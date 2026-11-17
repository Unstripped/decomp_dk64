# collisionCheckTriangleContainsPointXZ (global, src/global/6AD90.c)
## Sites
global:80669E04:noop-arith:3aa4ac `b = (tri->z[1] + tri->z[2]) * 0.5;`: b holds the z edge midpoint (f12, mul.d at 0x3ddc, never stored), later the side product (z - oz) * dx. A separate hz gives the same instructions but needs an eleventh f64 slot the frame does not have (0xc8 -> 0xd0). The kind is noop-arith only because the tool matches `* 0` in `* 0.5`.
Fixed 2026-11-16d: global:80669E04:noop-arith:58f1bd (a reused for the x midpoint, now a dedicated hx) and global:80669E04:other:0fc400 (dead `sideC = 0` init, gone with the sideP/sideC locals), by the box sibling's final shape (d78151a9).
## Attempts
2026-11-09 CleanD5E10 opus:low: w1 -> pad.
2026-11-14 PolishGlobal6AD90Names opus:high: params tri/x/z.
2026-11-16b HackcollisionCheckTriangleContainsPointXZ opus:high:
- loop: the sibling fix `for (i = 0, sideC = 0; i < 3; i++)` replaces `i = 0; sideC = 0; do { ... i++; ... } while (i != 3);` with its LAYOUT join: fdiff 0. The (f64) casts on the a/b midpoints dropped: fdiff 0.
- dead init, value classification (Q0908): `sideC = 1`, `sideC = -1` and the chained `sideC = i = 0` all fdiff 0, so it is a first-appearance lever and any dead value works. `sideP = 0` in the header: 10. `i = sideC = 0`: 11 (steals the v0 of i). No init: 10 (sideP cand 100 a0, sideC cand 106 a1; the cfe switch temp M -96 takes index 38). The sideC test before the sideP test: 122. c computed before a/b: 95. c and its sideC test before a/b: 92.
- a/b: hx/hz declared before a: 6 lines (frame 0xd8 only, args at sp+0xdc/0xe0). After i, or in place of pad: 33. f32 edge-sum locals sumX/sumZ (`cx = (tri->x[0] + sumX * 0.5) * 0.5`) in 4 declaration places: 58-69. The frame stays 0xc8, but the spill homes move 4 bytes down and the sum takes f2 instead of f4. The same with c inlined: 151.
- reconstruct (natural, as the box sibling): midX/midZ, px/pz, ternary sides, no init, no pad: 43. The same with the dead init kept: 33.
- variants scan: 48 variants, zeros only neutral (swaps, `0.0f`, outside u8/u16, pad widths, 7 decl swaps).
2026-11-16d HackcollisionCheckTriangleContainsPointXZ2 opus:high:
- the box sibling's exact final shape: `if (((b <= a) ? 1 : -1) != ((c >= 0.0) ? 1 : -1))` in place of sideP/sideC and their if/else blocks, `for (i = 0; i < 3; i++)` with no dead init, `f64 hx` declared after c for the x midpoint, pad removed: fdiff 0 (58f1bd and 0fc400 fixed).
- hz on that shape: block-scoped hx/hz before the loop (with a/b/c in a loop-body block, or hx/hz alone in a block): 14 lines, frame 0xd0 (cfe gives block locals their own slots, no overlap). c inlined into the ternary with hx/hz named: 86 (decls after oz) / 89 (hx/hz first). One axis inlined: `cz = (tri->z[0] + (tri->z[1] + tri->z[2]) * 0.5) * 0.5` with hx named, 2 statement orders: 148/164; cx inlined with hz named: 116/136. cz refined in place (`cz = mid; cz = (z0 + cz) * 0.5`) with hx named: 173. One f64 `mid` reused for both axes: 186.
- frame probes: `s32 pad` after i: 19 (no slack in the 96-byte area); `s32 pad[2]`: 14 (frame 0xd0). `u8 outside`: fdiff 0 (frees no slot). Reusing a or c for the z midpoint instead of b: fdiff 0 (same reuse, no gain).
## Untried ideas
None that keeps the switch: ten f64 + outside + i + the cfe switch temp fill the 96-byte area exactly (Q0296, Q0714), so a named hz always costs 8 bytes. Dropping the switch temp needs an if-chain (188 on the box sibling) or gotos.
## Evidence
Frame 0xc8. Homes in declaration order: cx 0xc0, cz 0xb8, a 0xb0, b 0xa8, dx 0xa0, dz 0x98, ox 0x90, oz 0x88, c 0x80, hx 0x78, outside, i, then the cfe switch temp; spill homes 0x44-0x64 and an f64 at 0x38.
dx/dz/ox/oz are loaded uninitialised (ldc1 f12,0xa0 / f14,0x98 / f16,0x90 / f18,0x88 at 0x3e18-0x3e28) and stored back at 0x3fc4-0x3fd0. These four homes are fixed, so exactly four f64 slots sit above them.
Midpoints: add.s f4,f16,f18 at 0x3da8, mul.d f2 at 0x3dc8 (x), mul.d f12 at 0x3ddc (z). The homes of a (0xb0) and b (0xa8) are never accessed, so the own-home ORIG rule does not apply.
Sign test: c.le.d f2,f0 at 0x3f74 -> a1 = 1/-1, c.le.d f8(0.0),f20 at 0x3f94 -> a0 = 1/-1, beq a0,a1 at 0x3fac.
