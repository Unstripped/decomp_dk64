# dlAppendTextureLoad (global, src/global/1135F0.c)
## Sites
global:8070E8F0:dead-if:9fb5c4 dead-if: `if (width && width) {}` lifts width {944} uopt adjsave 1.92 -> 2.08, tying the D_807550D0 address constant {922} (2.08); the tie goes to the lower candidate number (width 26 < address 418), so width takes $a3 and the address $t0. Without it the address takes $a3 and width $t0 (score 52, 0 shape).
global:8070E8F0:other:3d74d9 other (was 54aed2 `uls = 0;`, merged with 2b8d45 `ult = 0;`): `origin = 0;` constant local passed as uls and ult. uopt only propagates it, so `width - origin + 1` / `origin << 2` stay unfolded (usub/ushl with a propagated 0) in the gDPLoadTextureTile expansions; case 1 then spills only the SetTileSize gfx temp (sp+0x74). Literal 0s fold in cfe: the LoadSync and LoadTile gfx temps spill instead (sp+0x78/0x74 in a 0xb0 frame), score 680.
global:8070E8F0:other:2b8d45 (removed): `ult = 0;` second constant local; one local feeding both arguments is enough, s32 pad[2] keeps the frame 0xc8.
global:8070E8F0:other:41c84f (removed): `lrt = height;` only owned a frame home word (cfe -28) below ult; an unused `s32 pad` in its declaration slot restores every gfx temp home.
## Attempts
2026-11-14 HackdlAppendTextureLoad HackdlAppendTextureLoad anthropic/claude-opus-5-5: u32 width + u32 height locals, nine (u32)width casts dropped -> fdiff 0 (u32 width with s32 height swaps multu operands, 3); kept.
2026-11-14 HackdlAppendTextureLoad: lrt -> height + s32 pad (in place, also first or after type) -> fdiff 0; kept.
2026-11-14 HackdlAppendTextureLoad: ult -> uls (one constant local for both) -> 33 (homes -4); + s32 pad[2] (or a scalar pad before/after) -> fdiff 0; kept, local renamed origin.
2026-11-14 HackdlAppendTextureLoad: uls only / ult only (other literal) -> 680; both literal + pad[3] / pad1..3 -> 680; pad[6] -> 677; const s32 uls = 0, ult = 0 -> 0 (same constant local, not a fix).
2026-11-14 HackdlAppendTextureLoad: dead-if removal with 36 statement/declaration orders of type/height/width -> 52 each; switch on D_807550D0->type -> 85; register width, width % 8 / (width & 7) == 0 spellings, default first, (TextureDescriptor *) store cast -> 52; u8 type -> 55.
2026-11-14 HackdlAppendTextureLoad: reconstruct shapes (all hacks removed): TextureDescriptor *tex for the first reads 713, tex for every read 922, if/else-if chain 693, inverted width tests 726, s16 width/height 971, gfx assigned late 686/689, u8 type 683.
2026-11-14 HackdlAppendTextureLoad: permuter 900 s on the hack-free body and 900 s on the dead-if-only removal (see ledger for base/best).
## Untried ideas
A real second use of width in the entry block that ugen folds away (none found; would lift adjsave by 0.17) (uopt_trace -l 5)
A natural zero carrier other than a constant local for the tile origin (uopt must see a variable, cfe must not fold it) (diagnosis above)
## Evidence
Target frame 0xc8; gfx temp spills at sp+0x94,0x90 (case 1 block), 0x74 (case 1 tile SetTileSize, 0x36c), 0x60,0x5c,0x58, 0x40,0x3c, 0x24,0x20, 0x8,0x4.
Prologue: D_807550D0 address lui/addiu t0 (0x8/0xc), width lh a3,8(a2) at 0x50, height addu t4 at 0x58; LoadTile word0 is the constant lui 0xf400 (uls/ult = 0 folded).
## Permuter
2026-11-14 hack-free body (frame 0xb0): 900 s, base 11244, best 291: only constant temps (new_var = 9, new_var = 0x01 << 12), the same constant-local steer.
2026-11-14 final copy minus the dead test: 900 s, base 265, best 60: only re-inserts if (width && width) inside case arms.
