// func_807105D4 (src/global/114270.c): Stage 2: complete three-case texture display-list switch; semantics and command stream recovered. Fdiff compiles but target needs m2c-style per-packet pointer locals/frame 0x70 and raw multiplication form (current C emits strength-reduced offset and a small frame).
typedef struct L105D4TextureDescriptor {
    u8 unk0[8];
    u8 unk8;
    u8 unk9;
    u8 unkA[0xA];
} L105D4TextureDescriptor;

extern u8 D_80755264[];
extern u32 D_807FD9F0[];
extern u8 D_807FDA18;
extern u8 D_807FDA19;

#define L105D4_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt++); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

Gfx *func_807105D4(Gfx *arg0, s32 arg1) {
    u8 *texture_index;
    L105D4TextureDescriptor *texture;
    s32 width;
    s32 height;
    s32 height_numerator;
    s32 height_denominator;
    s32 dxt;
    u8 index;
    s32 texture_offset;

    texture_index = &D_807FDA1C;
    index = arg1 & 0xFF;
    texture_offset = *texture_index * 0x14;
    texture = (L105D4TextureDescriptor *)(D_80755264 + texture_offset);
    switch (texture->unk9) {
    case 1:
        L105D4_WRITE_GFX(arg0, ((texture->unk8 & 7) << 0x15) | 0xFD000000 | 0x100000, D_807FD9F0[index])
        L105D4_WRITE_GFX(arg0, ((texture->unk8 & 7) << 0x15) | 0xF5000000 | 0x100000, 0x07080200)
        L105D4_WRITE_GFX(arg0, 0xE6000000, 0)
        width = 0x7FF;
        height = (((D_807FDA18 * D_807FDA19) + 1) / 2) - 1;
        if (height < 0x7FF) width = height;
        height = D_807FDA18 / 8;
        height_denominator = height;
        if (height <= 0) height_denominator = 1;
        if (height <= 0) height_numerator = 1; else height_numerator = height;
        dxt = (height_numerator + 0x7FF) / height_denominator;
        L105D4_WRITE_GFX(arg0, 0xF3000000, 0x07000000 | ((width & 0xFFF) << 0xC) | (dxt & 0xFFF))
        L105D4_WRITE_GFX(arg0, 0xE7000000, 0)
        L105D4_WRITE_GFX(arg0, ((texture->unk8 & 7) << 0x15) | 0xF5080000 | ((((D_807FDA18 + 7) / 8) & 0x1FF) << 9), 0x00080200)
        L105D4_WRITE_GFX(arg0, 0xF2000000, ((((D_807FDA18 - 1) * 4) & 0xFFF) << 0xC) | (((D_807FDA19 - 1) * 4) & 0xFFF))
        break;
    case 2:
        L105D4_WRITE_GFX(arg0, ((texture->unk8 & 7) << 0x15) | 0xFD000000 | 0x100000, D_807FD9F0[index])
        L105D4_WRITE_GFX(arg0, ((texture->unk8 & 7) << 0x15) | 0xF5000000 | 0x100000, 0x07080200)
        L105D4_WRITE_GFX(arg0, 0xE6000000, 0)
        width = 0x7FF;
        height = (D_807FDA18 * D_807FDA19) - 1;
        if (height < 0x7FF) width = height;
        height = (D_807FDA18 * 2) / 8;
        height_denominator = height;
        if (height <= 0) height_denominator = 1;
        if (height <= 0) height_numerator = 1; else height_numerator = height;
        dxt = (height_numerator + 0x7FF) / height_denominator;
        L105D4_WRITE_GFX(arg0, 0xF3000000, 0x07000000 | ((width & 0xFFF) << 0xC) | (dxt & 0xFFF))
        L105D4_WRITE_GFX(arg0, 0xE7000000, 0)
        L105D4_WRITE_GFX(arg0, ((texture->unk8 & 7) << 0x15) | 0xF5100000 | (((((D_807FDA18 * 2) + 7) / 8) & 0x1FF) << 9), 0x00080200)
        L105D4_WRITE_GFX(arg0, 0xF2000000, ((((D_807FDA18 - 1) * 4) & 0xFFF) << 0xC) | (((D_807FDA19 - 1) * 4) & 0xFFF))
        break;
    case 3:
        L105D4_WRITE_GFX(arg0, ((texture->unk8 & 7) << 0x15) | 0xFD000000 | 0x180000, D_807FD9F0[index])
        L105D4_WRITE_GFX(arg0, ((texture->unk8 & 7) << 0x15) | 0xF5000000 | 0x180000, 0x07080200)
        L105D4_WRITE_GFX(arg0, 0xE6000000, 0)
        width = 0x7FF;
        height = (D_807FDA18 * D_807FDA19) - 1;
        if (height < 0x7FF) width = height;
        height = (D_807FDA18 * 4) / 8;
        height_denominator = height;
        if (height <= 0) height_denominator = 1;
        if (height <= 0) height_numerator = 1; else height_numerator = height;
        dxt = (height_numerator + 0x7FF) / height_denominator;
        L105D4_WRITE_GFX(arg0, 0xF3000000, 0x07000000 | ((width & 0xFFF) << 0xC) | (dxt & 0xFFF))
        L105D4_WRITE_GFX(arg0, 0xE7000000, 0)
        L105D4_WRITE_GFX(arg0, ((texture->unk8 & 7) << 0x15) | 0xF5180000 | ((((D_807FDA18 * 2) + 7) / 8) & 0x1FF) << 9, 0x00080200)
        L105D4_WRITE_GFX(arg0, 0xF2000000, ((((D_807FDA18 - 1) * 4) & 0xFFF) << 0xC) | (((D_807FDA19 - 1) * 4) & 0xFFF))
        break;
    }
    return arg0;
}
