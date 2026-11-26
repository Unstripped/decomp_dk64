# mapChunkTraversePortals (global, src/global/55B20_map_chunk.c)
## Sites
global:80656F14:other:a9fdd0 other (base 86d04c61, line 2108; removed): `id = gMapPortalSlots[i].target;` reused the grid-quad index `id` (i / 2, s1 at 0x61c4-0x61cc) for the target chunk so it stays in s1 (lh s1,4(t3) 0x64fc) without a new frame word; an s32 split grew the frame 0xD8 -> 0xE0.
## Attempts
2026-11-24 Polishglobal55B20c anthropic/claude-opus-5-5:xhigh: separate s32 target local (one position) -> fdiff 1, score 622, frame 0xE0; tagged FAKE.
2026-11-25c CleanmapChunkTraversePortals anthropic/claude-opus-5-5: frame map of the target, then a per-role `s16 target` (the field is s16 `lh`, the callee param is s16) at all 21 declaration positions and `s32 target` at 4 positions via variants.py try -> only `s16 target` declared right after `u8 overlap; u8 emitted;` scores 0 (fdiff exit 0, clint uninit --base exit 0); before overlap 2 (overlap home 0x9B -> 0x99); every other s16 position 89 and s32 85-89 (frame 0xE0). Kept: FAKE removed.
2026-11-25c CleanmapChunkTraversePortals review: emitted-path clip stores reordered from the m2c order (clipRight first) to left/top/right/bottom -> fdiff 0 (as1 still stores the s8-held right first, sw s8,176(sp) 0x6208); variants scan --max 0 of the final body: 232 variants, zeros only equal-codegen respellings; `target` widths u16/u8/s8 -> 1, s32/u32/int -> 89.
## Untried ideas
none open (site fixed).
## Evidence
- frame 0xD8: ra 0x74, s8..s0 0x70..0x50, $f24/$f22/$f20 0x48/0x40/0x38, outgoing args 0x10-0x2C; 0x30-0x37 and 0x78-0x8B never touched.
- named homes, declaration order from the top: id 0xD4, poly 0xD0, i 0xCC (register-only: s1, v0/a0, s2), polyLeft..polyBottom 0xC8..0xBC (address-taken), clipLeft..clipBottom 0xB8..0xAC (sw 0x6208-0x6218), outLeft..outBottom 0xA8..0x9C, u8 overlap 0x9B (sb 0x62d4, lbu 0x64bc), u8 emitted 0x9A (register s4, never stored), 2-byte alignment hole 0x98-0x99, poly0 0x94 (sw 0x6260/0x62dc, lw 0x64b8), found 0x90 (v1), k 0x8C (s0). [homes of register-only locals inferred from cfe declaration order; the fdiff-0 split confirms the hole]
- the new `s16 target` takes the hole 0x98: register-only (s1), never stored, so a dedicated local is no ORIG case for the old reuse (rulings.md:98-101); a per-role local in a hole is ordinary C (rulings.md:22, ACDC0 hudPauseMenuRender slotDy sp+0x154 precedent).
- target chunk: lh s1,4(t3) 0x64fc; gMapChunkEnabled[s1] 0x6508/0x650c; gMapChunks stride 0x1C8 built in s0 0x6510-0x6528; the recursive call re-extends the s16 argument (sll a0,s1,16 0x65c8; sra t2,a0,16 0x65f0; Q0188) with either type.
- uninit (clang): overlap, poly0, clipLeft/Top/Right/Bottom at the final test/mapRectIntersect: original control flow (the target reads poly0 from its home 0x64b8 also on the emitted path), unchanged from the base.
