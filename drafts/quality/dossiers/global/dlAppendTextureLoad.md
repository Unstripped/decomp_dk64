# dlAppendTextureLoad (global, src/global/1135F0.c)
## Sites
global:8070E8F0:other:231eab other (was 3d74d9 `origin = 0;`, before that 54aed2 `uls = 0;` + 2b8d45 `ult = 0;`): `uls = ult = 0;` constant tile-origin locals passed as uls/ult of gDPLoadTextureTile. uopt only propagates them, so `width - uls + 1` / `uls << 2` stay unfolded (usub/ushl with a propagated 0); case 1 then spills only the SetTileSize gfx temp (sp+0x74). Literal 0s fold in cfe: the LoadSync and LoadTile gfx temps spill instead (sp+0x84/0x80), score 547 with s32 pad[2] holding the 0xc8 frame.
global:8070E8F0:dead-if:9fb5c4 (removed 2026-11-15): `if (width && width) {}`. Without it width {944} 23/12 = 1.92 lost to the gCurrentTexture address {922} 25/12 = 2.08, and the switch selector temp, now starting in block 0, interfered with texture (a1) / glistp (a0) and took t1 from the 0x400 constant. Replaced by the tile-rectangle locals `lrs = width; lrt = height;` (two block-0 uses, the words of the old s32 pad[2]) and `switch (gCurrentTexture->type)` without a `type` local.
global:8070E8F0:other:2b8d45 (removed): `ult = 0;` second constant local (merged, now re-split as `uls = ult = 0`).
global:8070E8F0:other:41c84f (removed): `lrt = height;` redundant copy replaced by a pad; lrt is back as one of the four tile-rectangle locals.
## Attempts
2026-11-14 HackdlAppendTextureLoad HackdlAppendTextureLoad anthropic/claude-opus-5-5: u32 width + u32 height locals, nine (u32)width casts dropped -> fdiff 0 (u32 width with s32 height swaps multu operands, 3); kept.
2026-11-14 HackdlAppendTextureLoad: lrt -> height + s32 pad (in place, also first or after type) -> fdiff 0; kept.
2026-11-14 HackdlAppendTextureLoad: ult -> uls (one constant local for both) -> 33 (homes -4); + s32 pad[2] (or a scalar pad before/after) -> fdiff 0; kept, local renamed origin.
2026-11-14 HackdlAppendTextureLoad: uls only / ult only (other literal) -> 680; both literal + pad[3] / pad1..3 -> 680; pad[6] -> 677; const s32 uls = 0, ult = 0 -> 0 (same constant local, not a fix).
2026-11-14 HackdlAppendTextureLoad: dead-if removal with 36 statement/declaration orders of type/height/width -> 52 each; switch on D_807550D0->type -> 85; register width, width % 8 / (width & 7) == 0 spellings, default first, (TextureDescriptor *) store cast -> 52; u8 type -> 55.
2026-11-14 HackdlAppendTextureLoad: reconstruct shapes (all hacks removed): TextureDescriptor *tex for the first reads 713, tex for every read 922, if/else-if chain 693, inverted width tests 726, s16 width/height 971, gfx assigned late 686/689, u8 type 683.
2026-11-14 HackdlAppendTextureLoad: permuter 900 s on the hack-free body and 900 s on the dead-if-only removal (see ledger for base/best).
2026-11-15 HackdlAppendTextureLoad2 HackdlAppendTextureLoad2 anthropic/claude-opus-5-5: dead test removed (variants try scores): plain 55; + u32 lrs = width (pad -> 1 word) 33; + lrs = width, lrt = height in the pad[2] words 3 (only li 0x400 t1 -> t2); + s32/u32/s16 type 0 (u8 3, s8 1); lrs = origin + width 640; s32 lrs/lrt 3; declaration and statement orders 0.
2026-11-15 HackdlAppendTextureLoad2: separate uls/ult locals with type local 29; with switch (gCurrentTexture->type) and no type local 0 (kept: uls, ult, lrs, lrt, no pad); uls = ult = 0 chained 0; u32 uls/ult 0; s16 uls/ult 33; s32 lrs/lrt 3.
2026-11-15 HackdlAppendTextureLoad2: zero origin as literal on the new body: uls, ult or both literal (pad[2], pad first, declarations kept) 547.
## Untried ideas
A natural zero carrier other than a constant local for the tile origin (uopt must see a variable, cfe must not fold it) (diagnosis above)
## Evidence
Target frame 0xc8; gfx temp spills at sp+0x94,0x90 (case 1 block), 0x74 (case 1 tile SetTileSize, 0x36c), 0x60,0x5c,0x58, 0x40,0x3c, 0x24,0x20, 0x8,0x4.
Prologue: gCurrentTexture address lui/addiu t0 (0x8/0xc), li t1,0x400 (0x14), width lh a3,8(a2) at 0x50, height addu t4 at 0x58; LoadTile word0 is the constant lui 0xf400 (uls/ult = 0 folded).
uopt_trace -l 5 (no dead test, pad[2] body): width {944} cand 25 savings 23 / divisor 12; address {922} cand 414 savings 25 / 12; ties break by candidate number. The selector temp {1391} (adjsave 2.0) colours before the 0x400 constant {1024} (1.0): with the dispatch in block 0 it is forbidden a0/a1 and takes t1.
## Permuter
2026-11-14 hack-free body (frame 0xb0): 900 s, base 11244, best 291: only constant temps (new_var = 9, new_var = 0x01 << 12), the same constant-local steer.
2026-11-14 final copy minus the dead test: 900 s, base 265, best 60: only re-inserts if (width && width) inside case arms.
