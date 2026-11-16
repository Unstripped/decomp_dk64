# collisionCheckBoxTriangleContainsPointXZ (global, src/global/6AD90.c)
## Sites
global:8066A988:noop-arith:ec388d (was ced301) `a = (tri->x2 + tri->x1) * 0.5;`: a holds the x edge midpoint, later the side product (x - ox) * dz. A separate midpoint local gives the same instructions; it only adds an f64 slot.
global:8066A988:noop-arith:a2d087 (was b58281) `b = (tri->z2 + tri->z1) * 0.5;`: same for z.
global:8066A988:other:0fc400 `for (i = 0, sideC = 0; i < 3; i++)`: dead `sideC = 0` makes sideC the earlier uopt candidate (index 38 vs sideP 105), so the unconstrained colouring gives sideC a0 and sideP a1. Until 2026-11-16 it was hidden inside the `// LAYOUT:` comment of `i = 0; sideC = 0; do {`, so no site counted it.
## Attempts
2026-11-09 CleanD5E10 opus:low: one CollisionBoxTri type; midpoint written x2 + x1.
2026-11-16 Polishglobal6AD90 opus:high: hx/hz role locals (4 declaration places) fdiff 1.
2026-11-16 HackcollisionCheckBoxTriangleContainsPointXZ opus:high:
- a/b: hx/hz at 14 declaration positions: code identical, frame only (0xd8 vs 0xc8, 6-33 lines). Pad removed as well: 0xd0, every spill home 4 lower (33). c inlined with hx/hz, 7 declaration orders: 95-112. Products inlined into the sideP test (a/b gone, midpoints named), 6 statement orders: 85-86. cx/cz refined in place: 34 (one axis only: 173). Inline midpoint in cx/cz: 180.
- (f64) casts on the midpoints dropped: fdiff 0.
- loop: `for (i = 0, sideC = 0; i < 3; i++)` fdiff 0 retires the LAYOUT join. With no sideC init: 10 lines (a0/a1 swap), the same for every loop form (do/for, `i != 3`/`i < 3`), declaration order, ternary sides and `sideP != sideC` (9). An init before `outside = 0`, a declaration initialiser, or `sideC = 0;` on its own line before the loop: 11.
2026-11-16b HackcollisionCheckTriangleContainsPointXZ opus:high:
- reconstruct (natural): midX/midZ, px/pz side products, ternary sides, no dead init, no pad: 43 (frame 0xd0 with spill homes 4 lower, plus the a0/a1 swap). With the dead init kept: 33 (frame only). The original statement layout with midX/midZ after c, no pad, no init: 43.
- a/b: f32 sumX/sumZ locals in place of pad: 65. One shared f64 mid for both axes in place of pad: 185. The same declared before a with pad removed: 191.
- ORIG check (ladder own-home rule): the homes of a (sp+0xb0) and b (sp+0xa8) are never loaded or stored. The only sp accesses are 0x8-0x38, 0x88-0xa0 and 0xcc/0xd0, so the a/b tags stay FAKE.
## Untried ideas
A real reason the original reused a/b (an older layout with fewer f64 locals). Any spelling that frees 16 bytes of the 92-byte local area without changing code.
## Evidence
Frame census: the dx/dz/ox/oz homes are fixed at sp+0xa0/0x98/0x90/0x88. That leaves exactly four f64 slots above them (cx cz a b) and 28 bytes below (c + sideP outside sideC i pad), so separate midpoint locals cannot fit without dropping another f64 local.
Frame 0xc8 (200). Uninitialised loads of dx/dz/ox/oz homes: ldc1 f12,0xa0 / f14,0x98 / f16,0x90 / f18,0x88 at 0x49a4/0x499c/0x49a8/0x49ac, stored back at 0x4b48-0x4b54. Spill homes 0x44-0x64 and an f64 at 0x38. The local area is 92 bytes (cx cz a b dx dz ox oz c, sideP outside sideC i pad) and the cfe switch temp sits below it (M -96 in the trace).
Midpoints: add.s f4,f16,f18 at 0x492c, mul.d f2 at 0x494c (a), mul.d f12 at 0x4960 (b). Side products f0/f2 then c in f20 in every switch arm.
-zdbug:6: unconstrained candidates coloured in index order: outside (0) v1, i (35) v0, sideC (38) a0, sideP (105) a1.
