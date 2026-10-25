// func_8070E8F0 (src/global/1135F0.c): stage 3: direct F3DEX2 texture macros with palette field +4; 3232 bytes vs 3200 and frame 0xB0 vs target 0xC8; no usable semantic permutation
#include "common.h"

typedef struct L8F0Texture {
    void *image;
    u32 unk4;
    s16 width;
    u8 padA[2];
    s16 height;
    u8 format;
    u8 type;
    u8 pad10[2];
    s16 extraHeight;
} L8F0Texture;

extern void *D_807550D0;
extern s16 D_807FD9D0;
extern s16 D_807FD9D2;
extern u8 D_807FD9D4;
extern u8 D_807FD9D5;

#define L8F0_TEXTURE ((L8F0Texture *)D_807550D0)

void func_8070E8F0(Gfx **arg0, void *arg1) {
    Gfx *gfx = *arg0;
    s32 width;
    s32 height;
    s32 type;

    D_807550D0 = arg1;
    D_807FD9D0 = 0x400;
    D_807FD9D2 = 0x400;
    D_807FD9D4 = 0;
    D_807FD9D5 = 0;
    type = L8F0_TEXTURE->type;
    height = L8F0_TEXTURE->height + L8F0_TEXTURE->extraHeight;
    width = L8F0_TEXTURE->width;

    switch (type) {
    case 1:
        if (!(width & 7)) {
            gDPLoadTextureBlock(gfx++, L8F0_TEXTURE->image, L8F0_TEXTURE->format, G_IM_SIZ_8b, (u32)width, height, L8F0_TEXTURE->unk4, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureTile(gfx++, L8F0_TEXTURE->image, L8F0_TEXTURE->format, G_IM_SIZ_8b, (u32)width, height, 0, 0, (u32)width - 1, height - 1, L8F0_TEXTURE->unk4, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        }
        break;
    case 2:
        if (!(width & 3)) {
            gDPLoadTextureBlock(gfx++, L8F0_TEXTURE->image, L8F0_TEXTURE->format, G_IM_SIZ_16b, (u32)width, height, L8F0_TEXTURE->unk4, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureTile(gfx++, L8F0_TEXTURE->image, L8F0_TEXTURE->format, G_IM_SIZ_16b, (u32)width, height, 0, 0, (u32)width - 1, height - 1, L8F0_TEXTURE->unk4, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        }
        break;
    case 3:
        if (!(width & 1)) {
            gDPLoadTextureBlock(gfx++, L8F0_TEXTURE->image, L8F0_TEXTURE->format, G_IM_SIZ_32b, (u32)width, height, L8F0_TEXTURE->unk4, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureTile(gfx++, L8F0_TEXTURE->image, L8F0_TEXTURE->format, G_IM_SIZ_32b, (u32)width, height, 0, 0, (u32)width - 1, height - 1, L8F0_TEXTURE->unk4, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        }
        break;
    }
    *arg0 = gfx;
}

#undef L8F0_TEXTURE
