#include "common.h"
#include "render.h"
#include "proto/global/1135F0.h"

extern TextureDescriptor *gCurrentTexture;
extern s16 gTextureScaleS;
extern s16 gTextureScaleT;
extern u8 gTextureFlipS;
extern u8 gTextureFlipT;

void dlAppendTextureLoad(Gfx **glistp, void *texture) {
    Gfx *gfx = *glistp;
    u32 width;
    u32 height;
    u8 type;
    s32 origin;
    s32 pad[2];

    gCurrentTexture = texture;
    gTextureScaleS = 0x400;
    gTextureScaleT = 0x400;
    gTextureFlipS = 0;
    gTextureFlipT = 0;
    type = gCurrentTexture->type;
    height = gCurrentTexture->rectHeight + gCurrentTexture->t;
    width = gCurrentTexture->width;
    if (width && width) {}  // FAKE: lifts the uopt adjsave of width from 1.92 to 2.08, tying the gCurrentTexture address constant, so width takes a3 and the address t0 (Q0406)
    origin = 0;  // FAKE: value-named constant local (pre-existing, uls/ult merged): uopt keeps width - origin and origin << 2 unfolded in the gDPLoadTextureTile expansions, so case 1 spills only its SetTileSize gfx temp (sp+0x74); literal 0s fold in cfe, spill the LoadSync and LoadTile temps instead and shrink the frame 0xc8 -> 0xb0 (Q0145, Q0599)

    switch (type) {
    case 1:
        if (!(width & 7)) {
            gDPLoadTextureBlock(gfx++, gCurrentTexture->image, gCurrentTexture->format, G_IM_SIZ_8b, width, height, gCurrentTexture->pal, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureTile(gfx++, gCurrentTexture->image, gCurrentTexture->format, G_IM_SIZ_8b, width, height, origin, origin, width, height, gCurrentTexture->pal, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        }
        break;
    case 2:
        if (!(width & 3)) {
            gDPLoadTextureBlock(gfx++, gCurrentTexture->image, gCurrentTexture->format, G_IM_SIZ_16b, width, height, gCurrentTexture->pal, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureTile(gfx++, gCurrentTexture->image, gCurrentTexture->format, G_IM_SIZ_16b, width, height, origin, origin, width, height, gCurrentTexture->pal, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        }
        break;
    case 3:
        if (!(width & 1)) {
            gDPLoadTextureBlock(gfx++, gCurrentTexture->image, gCurrentTexture->format, G_IM_SIZ_32b, width, height, gCurrentTexture->pal, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureTile(gfx++, gCurrentTexture->image, gCurrentTexture->format, G_IM_SIZ_32b, width, height, origin, origin, width, height, gCurrentTexture->pal, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        }
        break;
    default:
        return;
    }
    *glistp = gfx;
}

void dlSetTextureScaleAndFlip(s16 scaleS, s16 scaleT, u8 flipS, u8 flipT) {
    gTextureScaleS = scaleS;
    gTextureScaleT = scaleT;
    gTextureFlipS = flipS;
    gTextureFlipT = flipT;
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
    if (gCurrentTexture != NULL) {
        fx = screenX * 0.25f;
        fy = screenY * 0.25f;
        ix = fx;
        s = (gCurrentTexture->s - (fx - ix)) * 32.0f;
        iy = fy;
        t = (gCurrentTexture->t - (fy - iy)) * 32.0f;
        sx = 1024.0f / gTextureScaleS;
        sy = 1024.0f / gTextureScaleT;
        x1 = (ix + gCurrentTexture->rectWidth * sx) * 4.0f;
        y1 = (iy + gCurrentTexture->rectHeight * sy) * 4.0f;
        if (gTextureFlipS != 0) {
            s += (gCurrentTexture->rectWidth << 5) - 0x20;
            dsdx = -gTextureScaleS;
        } else {
            dsdx = gTextureScaleS;
        }
        if (gTextureFlipT != 0) {
            t += (gCurrentTexture->rectHeight << 5) - 0x20;
            dtdy = -gTextureScaleT;
        } else {
            dtdy = gTextureScaleT;
        }
        gSPTextureRectangle(dl++, ix * 4, iy * 4, x1, y1, G_TX_RENDERTILE, s, t, dsdx, dtdy);
        *glistp = dl;
    }
}
