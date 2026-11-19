#include "common.h"
#include "render.h"
#include "proto/global/1135F0.h"

TextureDescriptor *gCurrentTexture = NULL;
extern s16 gTextureScaleS;
extern s16 gTextureScaleT;
extern u8 gTextureFlipS;
extern u8 gTextureFlipT;

void dlAppendTextureLoad(Gfx **glistp, TextureDescriptor *texture) {
    Gfx *gfx = *glistp;
    u32 width;
    u32 height;
    s32 uls;
    s32 ult;
    u32 lrs;
    u32 lrt;

    gCurrentTexture = texture;
    gTextureScaleS = 0x400;
    gTextureScaleT = 0x400;
    gTextureFlipS = 0;
    gTextureFlipT = 0;
    height = gCurrentTexture->rectHeight + gCurrentTexture->t;
    width = gCurrentTexture->width;
    uls = ult = 0;  // FAKE: constant tile-origin locals (pre-existing): defined in block 0 and propagated only by uopt, their loads in each tile path (uls in the first SetTile, uls/ult in LoadTile) reach the 20-load cut (varreflimit, Q0556) so uopt splits the tile block inside LoadTile: its gfx temp spans both nodes (a1) and only the SetTileSize gfx temp spills (sp+0x74); literal 0s (or the same assignment inside the tile branch, folded locally) move the cut past LoadTile and spill the LoadSync and LoadTile temps instead (sp+0x84/0x80, score 547-680) (Q0145, Q0599, Q0764)
    lrs = width; lrt = height;  // FAKE: copy locals for the tile lower-right corner (gDPLoadTextureTile lrs/lrt): after copy propagation each case counts one more width use in its second tile node (LoadTile to SetTileSize), raising width from 23/12 to 26/12 over the gCurrentTexture address (25/12) so width keeps a3 and the address t0; without them the two swap (score 52) (replaces a dead width test, Q0938) (Q0406, Q0523)

    switch (gCurrentTexture->type) {
    case 1:
        if (!(width & 7)) {
            gDPLoadTextureBlock(gfx++, gCurrentTexture->image, gCurrentTexture->format, G_IM_SIZ_8b, width, height, gCurrentTexture->pal, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureTile(gfx++, gCurrentTexture->image, gCurrentTexture->format, G_IM_SIZ_8b, width, height, uls, ult, lrs, lrt, gCurrentTexture->pal, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        }
        break;
    case 2:
        if (!(width & 3)) {
            gDPLoadTextureBlock(gfx++, gCurrentTexture->image, gCurrentTexture->format, G_IM_SIZ_16b, width, height, gCurrentTexture->pal, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureTile(gfx++, gCurrentTexture->image, gCurrentTexture->format, G_IM_SIZ_16b, width, height, uls, ult, lrs, lrt, gCurrentTexture->pal, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        }
        break;
    case 3:
        if (!(width & 1)) {
            gDPLoadTextureBlock(gfx++, gCurrentTexture->image, gCurrentTexture->format, G_IM_SIZ_32b, width, height, gCurrentTexture->pal, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureTile(gfx++, gCurrentTexture->image, gCurrentTexture->format, G_IM_SIZ_32b, width, height, uls, ult, lrs, lrt, gCurrentTexture->pal, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
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
