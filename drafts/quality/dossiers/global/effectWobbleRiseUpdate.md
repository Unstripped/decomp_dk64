# effectWobbleRiseUpdate (global, src/global/11BC10_effect_update.c)
## Sites
(untagged, removed 2026-11-25c) `swayZ` reuse (ReviewTypes21 2026-11-25, drafts/cleanup/pending.md "split or tag"): role 1 = sinApprox(swayRateZ * frame) * 6 z-position sway (base lines 701/703), role 2 = sinApprox(frame * 0.2267) scaleY wobble (base lines 734/736); neither reaches swayZ's home sp+0x38. Now role 2 has its own local `wobbleY` in the freed half of the old `f64 pad` (`f64 pad` -> `f32 pad; f32 wobbleY;`, Q0644).
(untagged -> ORIG 2026-11-25c) `swayX` reuse, renamed `waveX`: role 1 = sinApprox(swayRateX * frame) x-position sway (lines 701/703 of the final copy), role 2 = sinApprox(frame * 0.17) scaleX wobble (lines 734/736); both roles spill to the one home sp+0x3c. Tagged `// ORIG:` on the declaration (rulings.md ORIG section: two values spill to one home, as BA790 `x` sp+64); not a site.
## Attempts
2026-11-25 continue 2026-11-25c CleaneffectWobbleRiseUpdate anthropic/claude-opus-5-5: swayZ role 2 split into `wobbleY`, declarations `f32 pad; f32 wobbleY; f32 swayX; ...` (v/R1.c) and `f32 wobbleY; f32 pad; ...` (v/R1b.c) -> fdiff 0 both (homes unchanged: swayX sp+0x3c, floorY sp+0x30, frame 0x48). Applied R1 form.
2026-11-25 continue 2026-11-25c CleaneffectWobbleRiseUpdate anthropic/claude-opus-5-5: swayX census (R-oildrum, Q1122), measured on the wobbleY-split base (fdiff + objdump -dz of each variant vs expected; every variant has the target instruction stream, 326 insns, and frame 0x48; only sp offsets differ). Part 1, role 2 (scaleX wobble) in its own local `wobbleX`:
- function scope before `pad` (v/X_pos0.c): fdiff 1; floorY home 0x30 -> 0x2c (addiu a2,sp,44 / swc1 at 0x1e3c/0x1e40), role 1 spill 0x3c -> 0x38 (0x1ebc/0x1ef4), role 2 spill 0x3c -> 0x44 (0x20ec/0x2118).
- after `pad` (X_pos1): fdiff 1; floorY -> 0x2c, role 1 -> 0x38, role 2 -> 0x40.
- after `wobbleY`, before `swayX` (X_pos2): fdiff 1; floorY -> 0x2c, role 1 -> 0x38 (role 2 takes 0x3c).
- after `swayX` (X_pos3): fdiff 1; floorY -> 0x2c, role 2 -> 0x38.
- after `swayZ` (X_pos4): fdiff 1; floorY -> 0x2c, role 2 -> 0x34.
- after `riseSpeed` (X_pos5): fdiff 1; floorY -> 0x2c, role 2 -> 0x30.
- after `floorY` (X_pos6): fdiff 1; role 2 -> 0x2c.
- block scope `{ f32 wobbleX; ... }` around lines 734-737 (X_block): fdiff 1; role 2 -> 0x2c.
- `register f32 wobbleX;` before swayX (X_reg): fdiff 1; floorY -> 0x2c, role 1 -> 0x38.
- `register` in the block (X_regblock): fdiff 1; role 2 -> 0x2c.
- pad word taken (Q0644), `f32 wobbleX; f32 wobbleY;` (X_padA): fdiff 1; role 2 -> 0x44. `f32 wobbleY; f32 wobbleX;` (X_padB): role 2 -> 0x40. `wobbleY, swayX, wobbleX, swayZ, ...` (X_padC): role 1 -> 0x40.
Part 2, no local for role 2: `effect->scaleX += sinApprox(frame * 0.17) * 0.03;` after the wobbleY assignment (X_inlineA): fdiff 1, 42 diff lines (0.2267 sine called first, 0.17 product spilled to 0x40); scaleX statement first, then wobbleY (X_inlineB): fdiff 1, 64 diff lines (scaleX store before the second call); scaleY statement first, scaleX inline after (X_inlineC): fdiff 1, 64 diff lines. Direct field write: no field holds the wobble (WobbleRiseState has none; `scaleX +=` already writes the field). Pointer local: n/a (an f32 value).
Part 3: same type f32; role 1 lines 701-703 (asm 0x1e98-0x1f18), role 2 lines 734-736 (asm 0x20c8-0x2160), disjoint (frame/riseSpeed/switch code between).
Result: all three hold AND both roles spill to the one home sp+0x3c (swc1 $f0,60(sp) at 0x1ebc and 0x20ec), so the target-proven class applies: `// ORIG:` on the declaration with the offsets, local renamed role-neutral `swayX -> waveX` (rename.py local).
No earlier ruling kept either site FAKE (both untagged before; ReviewTypes21 review temps=1).
## Untried ideas
- none for the reuses. Not a site, kept as ordinary: riseSpeed read, clamp store, re-read (target reloads lwc1 $f2,4(v0) at 0x1f7c after the swc1 at 0x1f74).
## Evidence
- frame 0x48 (addiu sp,sp,-72 at 0x1ce4); s0 = effect, ra/s0 saved at sp+0x1c/0x18, isDone homed at sp+0x4c (0x1cf0).
- base declaration-order homes: `f64 pad` sp+0x40 (never accessed), swayX sp+0x3c, swayZ sp+0x38 (never accessed), riseSpeed sp+0x34 (never accessed: lives in $f2, 0x1f54/0x1f7c), floorY sp+0x30 (addiu a2,sp,48 at 0x1e3c, swc1 $f10,48(sp) at 0x1e40); sp+0x20..0x2f below the homes (a block-scope or last-declared local lands at 0x2c without growing the frame).
- swayX role 1: sinApprox(swayRateX * frame) (jal 0x1eb4) stored swc1 $f0,60(sp) at 0x1ebc, kept across the second jal sinApprox 0x1edc, reloaded lwc1 $f8,60(sp) at 0x1ef4 (mul.s by 6.0 at 0x1f00, effect->x store 0x1f18).
- swayX role 2: sinApprox(frame * 0.17) (jal 0x20e4) stored swc1 $f0,60(sp) at 0x20ec, kept across jal sinApprox 0x2110, reloaded lwc1 $f16,60(sp) at 0x2118 (mul.d by 0.03 at 0x212c, scaleX store 0x2160).
- swayZ role 1: sinApprox(swayRateZ * frame) returns in $f0 (jal 0x1edc), consumed by mul.s $f6,$f0,$f14 at 0x1f08 (effect->z store 0x1f28); no store to sp+0x38.
- swayZ role 2: sinApprox(frame * 0.2267) returns in $f0 (jal 0x2110), consumed by cvt.d.s $f4,$f0 at 0x214c (scaleY store 0x216c); no store to sp+0x38.
- quirks: Q1122 (frame evidence of a reuse), Q0644 (pad word taken by the split local), Q1035/Q0986/Q1089 (split census background), Q0896 (call-crossing split of one reused local).
