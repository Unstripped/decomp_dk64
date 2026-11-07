#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;

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

extern struct R1135bTexture *D_807550D0;
extern s16 D_807FD9D0;
extern s16 D_807FD9D2;
extern u8 D_807FD9D4;
extern u8 D_807FD9D5;

#define L8F0_TEXTURE ((L8F0Texture *)D_807550D0)

void dlAppendTextureLoad(Gfx **glistp, void *texture) {
    Gfx *gfx = *glistp;
    s32 width;
    s32 height;
    s32 type;
    s32 uls;
    s32 ult;
    s32 lrt;

    D_807550D0 = texture;
    D_807FD9D0 = 0x400;
    D_807FD9D2 = 0x400;
    D_807FD9D4 = 0;
    D_807FD9D5 = 0;
    type = L8F0_TEXTURE->type;
    height = L8F0_TEXTURE->height + L8F0_TEXTURE->extraHeight;
    width = L8F0_TEXTURE->width;
    if (width && width) {}  // FAKE: raises width's uopt priority (width a3, D_807550D0 address t0)
    uls = 0;  // FAKE: uls/ult/lrt only add three named frame homes and steer uopt (tile corner args)
    ult = 0;
    lrt = height;

    switch (type) {
    case 1:
        if (!(width & 7)) {
            gDPLoadTextureBlock(gfx++, L8F0_TEXTURE->image, L8F0_TEXTURE->format, G_IM_SIZ_8b, (u32)width, height, L8F0_TEXTURE->unk4, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureTile(gfx++, L8F0_TEXTURE->image, L8F0_TEXTURE->format, G_IM_SIZ_8b, (u32)width, height, uls, ult, (u32)width, lrt, L8F0_TEXTURE->unk4, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        }
        break;
    case 2:
        if (!(width & 3)) {
            gDPLoadTextureBlock(gfx++, L8F0_TEXTURE->image, L8F0_TEXTURE->format, G_IM_SIZ_16b, (u32)width, height, L8F0_TEXTURE->unk4, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureTile(gfx++, L8F0_TEXTURE->image, L8F0_TEXTURE->format, G_IM_SIZ_16b, (u32)width, height, uls, ult, (u32)width, lrt, L8F0_TEXTURE->unk4, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        }
        break;
    case 3:
        if (!(width & 1)) {
            gDPLoadTextureBlock(gfx++, L8F0_TEXTURE->image, L8F0_TEXTURE->format, G_IM_SIZ_32b, (u32)width, height, L8F0_TEXTURE->unk4, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureTile(gfx++, L8F0_TEXTURE->image, L8F0_TEXTURE->format, G_IM_SIZ_32b, (u32)width, height, uls, ult, (u32)width, lrt, L8F0_TEXTURE->unk4, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        }
        break;
    default:
        return;
    }
    *glistp = gfx;
}

#undef L8F0_TEXTURE



void dlSetTextureScaleAndFlip(s16 scaleS, s16 scaleT, s8 flipS, s8 flipT) {
    D_807FD9D0 = scaleS;
    D_807FD9D2 = scaleT;
    D_807FD9D4 = flipS;
    D_807FD9D5 = flipT;
}

typedef struct R1135bTexture {
    s32 image;
    u8 pad4[4];
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
    s16 unk10;
    s16 unk12;
} R1135bTexture;

extern R1135bTexture *D_807550D0;

void dlAppendTextureRectangle(Gfx **glistp, s16 screenX, s16 screenY) {
    Gfx *dl;
    f32 fx;
    f32 fy;
    f32 sx;
    f32 sy;
    s32 ix;
    s32 iy;
    s32 s;
    s32 t;
    s16 x1;
    s16 y1;
    s16 dsdx;
    s16 dtdy;

    dl = *glistp;
    if (D_807550D0 != NULL) {
        fx = (f32)screenX * 0.25f;
        fy = (f32)screenY * 0.25f;
        ix = (s32)fx;
        s = (s32)(((f32)D_807550D0->unk10 - (fx - (f32)ix)) * 32.0f);
        iy = (s32)fy;
        t = (s32)(((f32)D_807550D0->unk12 - (fy - (f32)iy)) * 32.0f);
        sx = 1024.0f / (f32)D_807FD9D0;
        sy = 1024.0f / (f32)D_807FD9D2;
        x1 = (s32)(((f32)ix + ((f32)D_807550D0->unkA * sx)) * 4.0f);
        y1 = (s32)(((f32)iy + ((f32)D_807550D0->unkC * sy)) * 4.0f);
        if (D_807FD9D4 != 0) {
            s += (D_807550D0->unkA << 5) - 0x20;
            dsdx = -D_807FD9D0;
        } else {
            dsdx = D_807FD9D0;
        }
        if (D_807FD9D5 != 0) {
            t += (D_807550D0->unkC << 5) - 0x20;
            dtdy = -D_807FD9D2;
        } else {
            dtdy = D_807FD9D2;
        }
        gSPTextureRectangle(dl++, ix * 4, iy * 4, x1, y1, G_TX_RENDERTILE, s, t, dsdx, dtdy);
        *glistp = dl;
    }
}
