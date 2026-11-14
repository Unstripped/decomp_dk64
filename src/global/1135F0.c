#include "common.h"
#include "render.h"
#include "proto/global/1135F0.h"

extern TextureDescriptor *D_807550D0;
extern s16 D_807FD9D0;
extern s16 D_807FD9D2;
extern u8 D_807FD9D4;
extern u8 D_807FD9D5;

void dlAppendTextureLoad(Gfx **glistp, void *texture) {
    Gfx *gfx = *glistp;
    u32 width;
    u32 height;
    u8 type;
    s32 origin;
    s32 pad[2];

    D_807550D0 = texture;
    D_807FD9D0 = 0x400;
    D_807FD9D2 = 0x400;
    D_807FD9D4 = 0;
    D_807FD9D5 = 0;
    type = D_807550D0->type;
    height = D_807550D0->rectHeight + D_807550D0->t;
    width = D_807550D0->width;
    if (width && width) {}  // FAKE: lifts the uopt adjsave of width from 1.92 to 2.08, tying the D_807550D0 address constant, so width takes a3 and the address t0 (Q0406)
    origin = 0;  // FAKE: value-named constant local (pre-existing, uls/ult merged): uopt keeps width - origin and origin << 2 unfolded in the gDPLoadTextureTile expansions, so case 1 spills only its SetTileSize gfx temp (sp+0x74); literal 0s fold in cfe, spill the LoadSync and LoadTile temps instead and shrink the frame 0xc8 -> 0xb0 (Q0145, Q0599)

    switch (type) {
    case 1:
        if (!(width & 7)) {
            gDPLoadTextureBlock(gfx++, D_807550D0->image, D_807550D0->format, G_IM_SIZ_8b, width, height, D_807550D0->pal, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureTile(gfx++, D_807550D0->image, D_807550D0->format, G_IM_SIZ_8b, width, height, origin, origin, width, height, D_807550D0->pal, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        }
        break;
    case 2:
        if (!(width & 3)) {
            gDPLoadTextureBlock(gfx++, D_807550D0->image, D_807550D0->format, G_IM_SIZ_16b, width, height, D_807550D0->pal, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureTile(gfx++, D_807550D0->image, D_807550D0->format, G_IM_SIZ_16b, width, height, origin, origin, width, height, D_807550D0->pal, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        }
        break;
    case 3:
        if (!(width & 1)) {
            gDPLoadTextureBlock(gfx++, D_807550D0->image, D_807550D0->format, G_IM_SIZ_32b, width, height, D_807550D0->pal, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureTile(gfx++, D_807550D0->image, D_807550D0->format, G_IM_SIZ_32b, width, height, origin, origin, width, height, D_807550D0->pal, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        }
        break;
    default:
        return;
    }
    *glistp = gfx;
}

void dlSetTextureScaleAndFlip(s16 scaleS, s16 scaleT, u8 flipS, u8 flipT) {
    D_807FD9D0 = scaleS;
    D_807FD9D2 = scaleT;
    D_807FD9D4 = flipS;
    D_807FD9D5 = flipT;
}

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
        fx = screenX * 0.25f;
        fy = screenY * 0.25f;
        ix = fx;
        s = (D_807550D0->s - (fx - ix)) * 32.0f;
        iy = fy;
        t = (D_807550D0->t - (fy - iy)) * 32.0f;
        sx = 1024.0f / D_807FD9D0;
        sy = 1024.0f / D_807FD9D2;
        x1 = (ix + D_807550D0->rectWidth * sx) * 4.0f;
        y1 = (iy + D_807550D0->rectHeight * sy) * 4.0f;
        if (D_807FD9D4 != 0) {
            s += (D_807550D0->rectWidth << 5) - 0x20;
            dsdx = -D_807FD9D0;
        } else {
            dsdx = D_807FD9D0;
        }
        if (D_807FD9D5 != 0) {
            t += (D_807550D0->rectHeight << 5) - 0x20;
            dtdy = -D_807FD9D2;
        } else {
            dtdy = D_807FD9D2;
        }
        gSPTextureRectangle(dl++, ix * 4, iy * 4, x1, y1, G_TX_RENDERTILE, s, t, dsdx, dtdy);
        *glistp = dl;
    }
}
