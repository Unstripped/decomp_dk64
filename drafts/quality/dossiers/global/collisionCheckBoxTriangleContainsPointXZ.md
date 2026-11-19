# collisionCheckBoxTriangleContainsPointXZ (global, src/global/6AD90.c)
## Sites
global:8066A988:noop-arith:a2d087 (was b58281) `b = (tri->z2 + tri->z1) * 0.5;`: b holds the z edge midpoint (f12, mul.d at 0x4960, never stored), later the side product (z - oz) * dx (f2). A separate hz gives the same instructions but needs an eleventh f64 home: the cfe extent grows 96 -> 104, every uopt spill temp moves 8 lower and the frame grows 0xc8 -> 0xd0.
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
2026-11-17f CleancollisionCheckTriangleContainsPointXZ claude-opus-5-5 (unit "2026-11-17: cleanup CleancollisionCheckTriangleContainsPointXZ"):
- cfe census by -zdbug:6 (base): the two cfe temps are -92 (switch selector ustr{-92}{i} and uequ{-92}{1}/{2}, reused by the first ternary ustr{-92}{1}) and -96 (second ternary), compared by uneq{-92}{-96} (bit 110). So the 2026-11-16c "ternary temp in" is the second ternary; the if-chain frees nothing while both ternaries stay.
- `register f64 hz` on the split body: 14 = plain split (frame 0xd0); `register` keeps the cfe home.
- one product inlined (hx/hz named, no pad, the freed home takes hz): a inline (`b <= (x - ox) * dz`): 93; b inline (`(z - oz) * dx <= a`): 69.
- named f32 vertex locals x0..z2 (the bounding-box sibling shape) with hx/hz, assignments interleaved in candidate order: 85 (frame 0xd0; the six named locals are coloured in the prologue and the 0.5 constant loses f0).
- permuter, hack-free weights, -j 2, 900 s from the hx/hz split body (base 106, best 0): all 14 zeros re-insert the reuse: a/b/c holding the x or z midpoint (10) or hx/hz holding the centre side value with c dropped (4). permute nohit.
- the triangle sibling (same unit) measured the narrow loop counter needed to pack i with a u8 outside: s8/s16 i 10 lines, u8/u16 i 18; the body is the same apart from the field names.
2026-11-18 CleancollisionCheckTriangleWindingF32 opus (unit "2026-11-18: cleanup CleancollisionCheckTriangleWindingF32"), the triangle twin bodies with the box field names, same scores:
- control: the hx/hz split body 14 (frame 0xd0 only).
- c inlined as the FIRST operand of the `!=`, hx/hz named: 116 ((f64)x0 loses f30 and spills to 72(sp), cx/cz f22/f24 -> f24/f26).
- `f64 mid[2]` for both midpoints: 211 (sdc1 stores to the array). `f32 hz`: 141 (cvt.s.d/cvt.d.s pair, frame 0xc0).
2026-11-18c CleancollisionCheckTriangleContainsPointXZb claude-opus-5-5 (unit "2026-11-18c: cleanup CleancollisionCheckTriangleContainsPointXZb"), re-measured on the current body, same scores as the triangle twin:
- control: the hx/hz split still scores 14, sp offsets only (frame 0xc8 -> 0xd0, dx/dz/ox/oz ldc1 at 0x499c-0x49ac and sdc1 at 0x4b48-0x4b54 8 higher).
- function-local `static f64 hz` (Q1125 lever): frame 0xc8 and every home match, but the static store stays: lui at,%hi(.bss) at 0x4954 + sdc1 f12,%lo(.bss)(at) at 0x4984, 16 .bss bytes: 10.
- byte packing, hx/hz named: `u8 outside; s8 sideP; s8 sideC;` set from the two ternaries (or by if/else) removes the -96 ternary temp, but the extent is 100 (i + packed byte word + switch temp): spills 4 lower (swc1 f8 0x58 -> 0x54 at 0x4930), and each s8 side adds sll/sra a2,0x18: 34 (both forms).
- the same with `s8 i`: extent exactly 96, no sp-offset line differs from the target; only width code remains (sll/sra + slti/bnez in place of li t0,3/bne at 0x4b3c, sll/sra per side at 0x4b08/0x4b2c): 22. `u8 i`: 23.
- variants scan from the split body: 31 variants, best 12 (dx/dz/ox/oz declswaps), no zero.
## Untried ideas
None that keeps the switch and an int-width i: 88 bytes of f64 + i (4) + the switch selector temp (4) already fill the 96-byte extent the spill temps fix, so `outside` (or a named side value) has no byte left; byte packing proves the frame then matches exactly (s8 i: zero sp-offset lines) but every narrow type adds its own sll/sra/slti. The inline forms of all eleven values (midpoints, products, c with either `!=` operand order, cx/cz) are measured; an f64 midpoint array, an f32 hz and a function-local static hz fail on their own stores/conversions.
## Evidence
Frame census: cfe homes cx -8, cz -16, a -24, b -32, dx -40 (sp+0xa0), dz -48, ox -56, oz -64 (sp+0x88), c -72, hx -80, outside -84, i -88, cfe temp -92 (switch selector + first ternary), cfe temp -96 (second ternary): 96 bytes, exactly the target. uopt spill temps start right below at -100 (x2 0x64, x1 0x60, z2 0x5c, z1 0x58, x0 0x54, z0 0x44, ucvt(z0) 0x38): any extra referenced local moves them.
Frame 0xc8 (200) = 144 (lowest home 0x38) + 56 (FP saves 0x08-0x38). Uninitialised loads of dx/dz/ox/oz homes: ldc1 f12,0xa0 / f14,0x98 / f16,0x90 / f18,0x88 at 0x49a4/0x499c/0x49a8/0x49ac, stored back at 0x4b48-0x4b54.
Midpoints: add.s f4,f16,f18 at 0x492c, mul.d f2 at 0x494c (x), mul.d f12 at 0x4960 (z). Side products f0/f2 then c in f20 in every switch arm; c.le.d f2,f0 at 0x4af8, c.le.d f8,f20 at 0x4b18, beq a0,a1 at 0x4b30.
-zdbug:6 (base): loop pass colours a/b products f0/f2, dx dz ox oz f12-f18, c f20, cx cz f22/f24 (adjsave 16.4, bits 21/28) ahead of ucvt(x)/ucvt(z) f26/f28 (16.4, bits 84/90), ucvt(x0) f30; outer pass 0.5 const (savings 6) f0, x mid f2, z mid f12.
Byte-packed census (2026-11-18c, hx/hz named, s8 i, u8 outside, s8 sideP/sideC): eleven f64 (88) + one byte word + the switch temp = 96, spills at the target offsets; the s8 sides cost sll/sra of a2 (the shared constant 1) and s8 i costs sll/sra + slti at the loop test.
