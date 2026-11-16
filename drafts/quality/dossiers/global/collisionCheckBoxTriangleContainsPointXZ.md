# collisionCheckBoxTriangleContainsPointXZ (global, src/global/6AD90.c)
## Sites
global:8066A988:noop-arith:a2d087 (was b58281) `b = (tri->z2 + tri->z1) * 0.5;`: b holds the z edge midpoint, later the side product (z - oz) * dx. A separate hz gives the same instructions but needs one more f64 slot than the frame has (0xc8 -> 0xd0).
Fixed 2026-11-16c: global:8066A988:noop-arith:ec388d (a reused for the x midpoint, now a dedicated hx) and global:8066A988:other:0fc400 (dead `sideC = 0` init, gone with the sideP/sideC locals).
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
2026-11-16c HackcollisionCheckBoxTriangleContainsPointXZ2 opus:high:
- sides: `if (((b <= a) ? 1 : -1) != ((c >= 0.0) ? 1 : -1))` in place of the sideP/sideC locals and their if/else blocks: code identical including a1/a0 with no dead init; the local area drops 96 -> 92 (two s32 slots out, one 4-byte cfe ternary temp in). With `s32 pad[2]`: fdiff 0 (both a/b reuses kept).
- then hx in place of the a reuse, declared after c, no pad: fdiff 0 (frame 0xc8). hz as well: frame 0xd0, homes 8 higher (14 lines). The same with hz named and a reused instead of b: fdiff 0.
- cx/cz unnamed (inlined into c, hx/hz named): uopt code motion hoists both out of the loop, frame consistent, but 65 lines: the hoisted expressions get candidate bits after ucvt(x)/ucvt(z) and lose the 16.4 adjsave tie (cx/cz in f26/f28 instead of f22/f24), and the 0.5 constant counts only its 2 source uses in BB0 (savings 2 vs 6), so it lands in f14 instead of f0. Statement orders c/a/b: 84-129. cz alone unnamed: 31 (same two causes); cx alone: 46.
- products inlined into the sign ternary (a/b gone, hx/hz named, pad[2]): 93. if/else-if chain in place of the switch (frees the switch temp): 188 (layout).
## Untried ideas
Any spelling that frees one more f64 slot (8 bytes) of the 96-byte local area without changing code: the area is ten f64 (cx cz a b dx dz ox oz c hx) + outside + i + switch temp + ternary temp.
## Evidence
Frame census: the dx/dz/ox/oz homes are fixed at sp+0xa0/0x98/0x90/0x88 with four f64 slots above them (cx cz a b). Below c the area holds hx, outside, i, the cfe switch temp and the ternary temp: 96 bytes, exactly the target.
Frame 0xc8 (200). Uninitialised loads of dx/dz/ox/oz homes: ldc1 f12,0xa0 / f14,0x98 / f16,0x90 / f18,0x88 at 0x49a4/0x499c/0x49a8/0x49ac, stored back at 0x4b48-0x4b54. Spill homes 0x44-0x64 and an f64 at 0x38.
Midpoints: add.s f4,f16,f18 at 0x492c, mul.d f2 at 0x494c (x), mul.d f12 at 0x4960 (z). Side products f0/f2 then c in f20 in every switch arm.
-zdbug:6 (base): loop pass colours a/b products f0/f2, dx dz ox oz f12-f18, c f20, cx cz f22/f24 (adjsave 16.4, bits 21/28) ahead of ucvt(x)/ucvt(z) f26/f28 (16.4, bits 84/90), ucvt(x0) f30; outer pass 0.5 const (savings 6) f0, x mid f2, z mid f12.
