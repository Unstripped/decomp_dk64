#include "common.h"
#include "actor.h"
#include "sched.h"

#include "proto/global/114270.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17800.h"
#include "proto/global/55B20.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/90D80.h"
#include "proto/global/CEAE0.h"

typedef struct M114aAngle {
    s16 mapChunk;
    u8 pad2[2];
    f32 x;
    f32 drawX;
    f32 y;
    f32 scale;
    f32 camYaw;
    f32 camX;
    f32 camZ;
    s16 phase; // sway angle (pool types 1, 3); types 4 and 5 re-roll it as a 5..24 variant (fall speed, texture)
    s16 angle;
    s16 tilt;
    u8 pad26[2];
    f32 sway;
    u8 pad2C[4];
    Mtx mtx[2];
    u8 age;
    u8 alpha;
    u8 frame;
    u8 tiltRange;
    u8 padB4[4];
} EffectSpriteParticle;

typedef struct EffectSpritePoolHeader {
    u16 count;
    u8 pad2[2];
    EffectSpriteParticle *entries;
} EffectSpritePoolHeader;

typedef struct EffectSpriteTextureSetup {
    u8 count;
    u8 type;
    u8 pad2[2];
    u16 *images;
    u8 format;
    u8 texSize;
    u8 width;
    u8 height;
    Vtx *vertices;
    u8 (*update)(EffectSpriteParticle *particle);
} EffectSpriteTextureSetup;

extern EffectSpritePoolHeader D_807FD9E0;

EffectSpritePoolHeader *gEffectSpritePool = &D_807FD9E0;
Vtx D_807550E8[4] = {
    {{{ -8, -16, -10 }, 0, { 0, 1984 }, { 0, 0, 0, 0 } }},
    {{{ 7, -16, -10 }, 0, { 960, 1984 }, { 0, 0, 0, 0 } }},
    {{{ 7, 15, -10 }, 0, { 960, 0 }, { 0, 0, 0, 0 } }},
    {{{ -8, 15, -10 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
};
Vtx D_80755128[4] = {
    {{{ -32, -32, -10 }, 0, { 0, 4032 }, { 0, 0, 0, 0 } }},
    {{{ 31, -32, -10 }, 0, { 4032, 4032 }, { 0, 0, 0, 0 } }},
    {{{ 31, 31, -10 }, 0, { 4032, 0 }, { 0, 0, 0, 0 } }},
    {{{ -32, 31, -10 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
};
Vtx D_80755168[4] = {
    {{{ -22, -22, -10 }, 0, { 0, 2752 }, { 0, 0, 0, 0 } }},
    {{{ 21, -22, -10 }, 0, { 2752, 2752 }, { 0, 0, 0, 0 } }},
    {{{ 21, 21, -10 }, 0, { 2752, 0 }, { 0, 0, 0, 0 } }},
    {{{ -22, 21, -10 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
};
Vtx D_807551A8[4] = {
    {{{ -16, -16, -10 }, 0, { 0, 1984 }, { 0, 0, 0, 0 } }},
    {{{ 15, -16, -10 }, 0, { 1984, 1984 }, { 0, 0, 0, 0 } }},
    {{{ 15, 15, -10 }, 0, { 1984, 0 }, { 0, 0, 0, 0 } }},
    {{{ -16, 15, -10 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
};
Vtx D_807551E8[4] = {
    {{{ -16, -8, -10 }, 0, { 0, 960 }, { 0, 0, 0, 0 } }},
    {{{ 15, -8, -10 }, 0, { 1984, 960 }, { 0, 0, 0, 0 } }},
    {{{ 15, 7, -10 }, 0, { 1984, 0 }, { 0, 0, 0, 0 } }},
    {{{ -16, 7, -10 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
};
u16 D_80755228[10] = { 0x173D, 0x173E, 0x173F, 0x1740, 0x1741, 0x1742, 0x1743, 0x1744, 0x1745, 0x1746 };
u16 D_8075523C[2] = { 0x143B, 0 };
u16 D_80755240[2] = { 0x52C, 0 };
u16 D_80755244[8] = { 0x3BB, 0x3BC, 0x3BD, 0x3BE, 0x3BF, 0x3C0, 0x3C1, 0x3C2 };
u16 D_80755254[2] = { 0x173B, 0 };
u16 D_80755258[6] = { 0x1735, 0x1736, 0x1737, 0x1738, 0x1739, 0x173A };
EffectSpriteTextureSetup gEffectSpriteTextureSetups[6] = {
    { 1, 1, { 0, 0 }, D_8075523C, 3, 1, 16, 32, D_807550E8, effectSpriteParticleUpdateRain },
    { 1, 1, { 0, 0 }, D_80755240, 3, 1, 64, 64, D_80755128, effectSpriteParticleUpdateSnow },
    { 8, 0, { 0, 0 }, D_80755244, 0, 2, 44, 44, D_80755168, effectSpriteParticleUpdateBanana },
    { 1, 1, { 0, 0 }, D_80755254, 3, 1, 64, 64, D_80755128, effectSpriteParticleUpdateFluff },
    { 10, 1, { 0, 0 }, D_80755228, 0, 2, 32, 32, D_807551A8, effectSpriteParticleUpdateFlutter },
    { 6, 1, { 0, 0 }, D_80755258, 0, 3, 32, 16, D_807551E8, effectSpriteParticleUpdateFlutter },
};

extern PlayerStruct *gPlayerSlots;

extern u8 gEffectSpriteFreeTop;
extern u8 gEffectSpritePoolType;
extern u8 gEffectSpritePoolLoaded;
extern u8 gEffectSpriteFreeSlots[];

void effectSpritePoolReset(void) {
    s16 i;

    gEffectSpritePool->count = 0;
    gEffectSpritePoolType = 6;
    for (i = 0; i < 0x80; i++) {
        gEffectSpriteFreeSlots[i] = i;
    }
    gEffectSpriteFreeTop = 0x7F;
    gEffectSpritePoolLoaded = 0;
}

extern void *gEffectSpriteTextures[];
extern u8 gEffectSpriteTexWidth;
extern u8 gEffectSpriteTexHeight;
extern Vtx *gEffectSpriteVertices;
extern u8 (*gEffectSpriteUpdate)(EffectSpriteParticle *particle);


void effectSpritePoolSpawn(u8 poolType, s16 mapChunk, f32 scale, s16 spawnX, s16 spawnY, u8 initialAlpha) {
    EffectSpriteParticle *entry;
    s16 i;
    s32 idx;

    if (gEffectSpritePool->count >= 0x80) {
        return;
    }
    if (gEffectSpritePool->count == 0 && gEffectSpritePoolLoaded == 0) {
        gEffectSpritePool->entries = heapAlloc(0x80 * sizeof(EffectSpriteParticle));
        heapClearBlock(gEffectSpritePool->entries);
        gEffectSpritePoolType = poolType;
        for (i = 0; i < gEffectSpriteTextureSetups[poolType].count; i++) {
            gEffectSpriteTextures[i] = assetLoad(gEffectSpriteTextureSetups[poolType].type != 0 ? 0x19 : 7, gEffectSpriteTextureSetups[poolType].images[i], 1, 1);
        }
        gEffectSpriteTexWidth = gEffectSpriteTextureSetups[poolType].width;
        gEffectSpriteTexHeight = gEffectSpriteTextureSetups[poolType].height;
        gEffectSpriteVertices = gEffectSpriteTextureSetups[poolType].vertices;
        gEffectSpriteUpdate = gEffectSpriteTextureSetups[poolType].update;
        gEffectSpritePoolLoaded = 1;
    }
    idx = gEffectSpriteFreeSlots[gEffectSpriteFreeTop];
    gEffectSpriteFreeSlots[gEffectSpriteFreeTop--] = 0xFF;
    entry = &gEffectSpritePool->entries[idx];
    entry->age = 1;
    entry->x = spawnX;
    entry->drawX = spawnX;
    entry->y = spawnY;
    entry->scale = scale;
    entry->mapChunk = mapChunk;
    entry->alpha = initialAlpha;
    entry->camYaw = gPlayerSlots->camYaw;
    entry->camX = gPlayerSlots->camX;
    entry->camZ = gPlayerSlots->camZ;
    entry->phase = (randomNonNegative() >> 15) % 32767 % 0xFFF;
    entry->angle = (randomNonNegative() >> 15) % 32767 % 360;
    switch (gEffectSpritePoolType) {
    case 3:
        entry->sway = (randomNonNegative() >> 15) % 32767 % 100 * 0.02;
        break;
    case 4:
    case 5:
        entry->phase = (randomNonNegative() >> 15) % 20 + 5;
        entry->sway = (randomNonNegative() >> 15) % 70 + 30;
        entry->angle = 0;
        if ((randomNonNegative() >> 15) % 100 > 80) {
            entry->tiltRange = 200;
        } else {
            entry->tiltRange = (randomNonNegative() >> 15) % 32767 % 6 + 5;
        }
        break;
    default:
        entry->sway = (randomNonNegative() >> 15) % 32767 % 100 * 0.1;
        break;
    }
    gEffectSpritePool->count++;
}

extern s16 gEffectSpriteWindAngle;

void effectSpriteParticleTrackCamera(EffectSpriteParticle *particle) {
    f32 diff;
    f32 dist1;
    f32 dz;
    f32 dx;
    s16 ang;
    f32 dist2;

    dz = gPlayerSlots->camZ - particle->camZ;
    dx = gPlayerSlots->camX - particle->camX;
    dist1 = sqrtf(dz * dz + dx * dx);
    particle->camX = gPlayerSlots->camX;
    particle->camZ = gPlayerSlots->camZ;
    diff = gPlayerSlots->camYaw - particle->camYaw;
    if (diff > 3.1415927f) {
        diff = 6.2831855f - diff;
    }
    if (diff < -3.1415927f) {
        diff = -6.2831855f - diff;
    }
    particle->x += diff * 180.0f - 0.3 * gEffectSpriteWindAngle;
    particle->x += 4.0f * dist1 * sinApprox(diff);
    ang = mathAngleBetweenPoints2D(gPlayerSlots->camX, gPlayerSlots->camZ, gPlayerSlots->eyeX, gPlayerSlots->eyeZ);
    dz = gPlayerSlots->camZ - gPlayerSlots->eyeZ;
    dx = gPlayerSlots->camX - gPlayerSlots->eyeX;
    dist2 = sqrtf(dz * dz + dx * dx);
    particle->x -= 2.0 * dist2 * mathSinF(mathAngleSignedDistance(gPlayerSlots->camYawInt, ang));
    particle->camYaw = gPlayerSlots->camYaw;
}


void effectSpriteParticleWrapX(EffectSpriteParticle *particle) {
    if (315.0f < particle->x) {
        particle->x = particle->x - 315.0f + 2.0f;
    }
    if (particle->x < 2.0f) {
        particle->x = 315.0f - particle->x;
    }
    particle->x = (s32)particle->x % 320;
}


extern Actor *gPrimaryPlayerActor;
extern u32 gGlobalCutsceneFlags;
extern f32 gEffectSpriteBottomY;
extern u8 sEffectImpactPuffConfig;

#define CAM_Y_DISTANCE(y) ((y) < gPlayerSlots->camY ? gPlayerSlots->camY - (y) : -(gPlayerSlots->camY - (y)))

u8 effectSpriteParticleUpdateRain(EffectSpriteParticle *particle) {
    f32 fallSpeed;
    f32 invScale;
    f32 bound;
    s32 isUnderMaxAge;
    f32 angle;
    f32 jitter;

    if (((CamState *)gCamActor->customState)->hasWater != 0 && gPlayerSlots->camY < ((CamState *)gCamActor->customState)->waterY + 3.0f) {
        bound = gPrimaryPlayerActor->waterY;
    } else {
        bound = CAM_Y_DISTANCE(gPrimaryPlayerActor->unkA8) < CAM_Y_DISTANCE(gPrimaryPlayerActor->waterY) ? gPrimaryPlayerActor->unkA8 : gPrimaryPlayerActor->waterY;
    }
    effectSpriteParticleTrackCamera(particle);
    effectSpriteParticleWrapX(particle);
    isUnderMaxAge = particle->age < 0x10;
    particle->age++;
    particle->drawX = particle->x;
    if (!isUnderMaxAge && particle->alpha >= 0x50) {
        particle->alpha -= 0x50;
    }
    invScale = 1.0 / (particle->scale * 4.0) * 60.0;
    fallSpeed = ((30.0f - (invScale - 30.0f)) + 30.0f) * 0.25;
    fallSpeed = fallSpeed > 5.0 ? fallSpeed : 5.0;
    particle->y += fallSpeed;
    if (particle->alpha < 0x50 && (randomNonNegative() >> 15) % 0x80 >= 0x56 && CAM_Y_DISTANCE(bound) < 50.0f) {
        angle = ((randomNonNegative() >> 15) % 60 - 30) * 0.017453292f + gPlayerSlots->camYaw;
        jitter = (randomNonNegative() >> 15) % 0x82;
        if (!(gGlobalCutsceneFlags & 8)) {
            effectSetDepth(1);
            effectSetCallback(&effectRandomYRotDecalUpdate);
            effectSetChunkFilter(particle->mapChunk);
            effectSetFlags(4);
            effectCreateAtPosition(&sEffectImpactPuffConfig, 0.3f, gPlayerSlots->camX - sinApprox(angle) * jitter, bound + 1.0, gPlayerSlots->camZ - cosApprox(angle) * jitter);
        }
        return 1;
    }
    return gEffectSpriteBottomY < particle->y;
}

#undef CAM_Y_DISTANCE



u8 effectSpriteParticleUpdateBanana(EffectSpriteParticle *particle) {
    s32 isUnderMaxAge;
    f32 invScale;

    effectSpriteParticleTrackCamera(particle);
    effectSpriteParticleWrapX(particle);
    isUnderMaxAge = particle->age < 0xF;
    particle->age++;
    particle->drawX = particle->x;
    if (!isUnderMaxAge && particle->alpha >= 0x50) {
        particle->alpha -= 0x50;
    }
    invScale = 1.0 / (particle->scale * 4.0) * 60.0;
    particle->y += ((30.0f - (invScale - 30.0f)) + 30.0f) * 0.2;
    return particle->y > 240.0f || particle->alpha < 0x50;
}

u8 effectSpriteParticleUpdateSnow(EffectSpriteParticle *particle) {
    s32 isUnderMaxAge;
    f32 invScale;

    effectSpriteParticleTrackCamera(particle);
    particle->x += mathSinF(particle->phase) * particle->sway;
    effectSpriteParticleWrapX(particle);
    particle->drawX = particle->x;
    invScale = 1.0 / (particle->scale * 4.0) * 8.0;
    isUnderMaxAge = particle->age < 0x3D;
    particle->phase += 0x14;
    particle->age++;
    particle->y += ((10.0f - (invScale - 10.0f)) + 10.0f) * 0.25;
    if (!isUnderMaxAge && particle->alpha >= 0xA) {
        particle->alpha -= 0xA;
    }
    return particle->y > 240.0f || particle->alpha < 0xA;
}

u8 effectSpriteParticleUpdateFluff(EffectSpriteParticle *particle) {
    s32 isUnderMaxAge;
    f32 invScale;

    effectSpriteParticleTrackCamera(particle);
    particle->x += mathSinF(particle->phase) * particle->sway;
    effectSpriteParticleWrapX(particle);
    particle->drawX = particle->x;
    invScale = 1.0 / (particle->scale * 3.0) * 8.0;
    isUnderMaxAge = particle->age < 0x6F;
    particle->y += ((10.0f - (invScale - 10.0f)) + 10.0f) * 0.07;
    particle->phase += 0x32;
    particle->age++;
    if (!isUnderMaxAge && particle->alpha >= 0xA) {
        particle->alpha -= 0xA;
    }
    return gEffectSpriteBottomY < particle->y || particle->alpha < 0xA;
}


u8 effectSpriteParticleUpdateFlutter(EffectSpriteParticle *particle) {
    f32 absScale;

    effectSpriteParticleTrackCamera(particle);
    particle->x += mathSinF(particle->angle * 0.5) * (f32)(particle->sway * 0.05);
    effectSpriteParticleWrapX(particle);
    particle->drawX = particle->x;
    particle->y += (1.0 + mathSinF(particle->angle)) * (f32)(1.0 + particle->phase * 0.08);
    particle->angle += 0x64;
    particle->tilt = (mathSinF(particle->angle * 0.5) * 0.5 + 0.5) * (particle->tiltRange * 4 - -particle->tiltRange * 4) + -particle->tiltRange * 4;
    absScale = particle->scale > 0.0f ? particle->scale : -particle->scale;
    if (absScale * 140.0f < particle->y && particle->alpha >= 0xA) {
        particle->alpha -= 0xA;
    }
    return gEffectSpriteBottomY < particle->y || particle->alpha < 0xA;
}


Gfx *effectSpritePoolLoadTexture(Gfx *glist, u8 textureIndex) {
    switch (gEffectSpriteTextureSetups[gEffectSpritePoolType].texSize) {
    case 1:
        gDPLoadTextureBlock(glist++, gEffectSpriteTextures[textureIndex], gEffectSpriteTextureSetups[gEffectSpritePoolType].format, G_IM_SIZ_8b, gEffectSpriteTexWidth, gEffectSpriteTexHeight, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case 2:
        gDPLoadTextureBlock(glist++, gEffectSpriteTextures[textureIndex], gEffectSpriteTextureSetups[gEffectSpritePoolType].format, G_IM_SIZ_16b, gEffectSpriteTexWidth, gEffectSpriteTexHeight, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case 3:
        gDPLoadTextureBlock(glist++, gEffectSpriteTextures[textureIndex], gEffectSpriteTextureSetups[gEffectSpritePoolType].format, G_IM_SIZ_32b, gEffectSpriteTexWidth, gEffectSpriteTexHeight, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    }
    return glist;
}



extern PlayerState *gActivePlayerState;
extern EffectSpriteParticle *D_807FDAB0;
extern s16 D_807FDAB4;
extern u8 gGfxBufferIndex;
extern u8 gEffectSpriteBrightness;
extern Gfx D_1000020[];
extern Gfx D_1000118[];
extern Mtx D_20000C0;


Gfx *effectSpriteRenderPool(Gfx *glist, Actor *actor) {
    f64 scaleSize;
    f32 mtxScale[4][4];
    f32 mtxTemp[4][4];
    f64 pad;
    u8 skipNearPlayer;
    u8 skipTimer;
    s16 i = 0x80;
    u16 count = gEffectSpritePool->count;
    u16 processed = 0;
    EffectSpriteParticle *entry;
    CamState *camState = gCamActor->customState;

    skipTimer = 0;
    skipNearPlayer = 0;

    if ((gPrimaryPlayerActor->state == 3) || (gPrimaryPlayerActor->state == 5)) {
        f32 rem = (gCamActor->distToFloor > 180.0f) ? 0.0f : 180.0f - gCamActor->distToFloor;
        if (count == 0) {}  // FAKE: numbers ucvt(count) ahead of the texture-if candidates, so its loop spill temp is 0x64(sp), not 0x5c
        gEffectSpriteBottomY = rem * 0.02 * 240.0;
    } else {
        gEffectSpriteBottomY = 240.0f;
    }
    if ((gPrimaryPlayerActor->state == 0x42) && ((gActivePlayerState->hitActorType == 0x62) || (gActivePlayerState->hitActorType == 0x88))) {
        skipTimer = 1;
    }
    if ((camState->hasWater != 0) && (gPlayerSlots->camY < camState->waterY + 3.0f)) {
        skipNearPlayer = 1;
    }
    gDPPipeSync(glist++);
    gSPDisplayList(glist++, D_1000118);
    gSPDisplayList(glist++, D_1000020);
    gSPMatrix(glist++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPTexture(glist++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(glist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetTextureFilter(glist++, G_TF_BILERP);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    if (gEffectSpriteTextureSetups[gEffectSpritePoolType].count == 1) {
        glist = effectSpritePoolLoadTexture(glist, 0);
    }
    while (--i >= 0 && processed != count) {
        entry = &gEffectSpritePool->entries[i];
        D_807FDAB0 = entry;
        D_807FDAB4 = gEffectSpriteWindAngle;
        if ((entry->age != 0) && ((entry->mapChunk == -1) || mapChunkContainsPoint(entry->drawX, entry->y, entry->mapChunk)) && !skipNearPlayer && !skipTimer) {
            gDPSetPrimColor(glist++, 0, 0, gEffectSpriteBrightness, gEffectSpriteBrightness, gEffectSpriteBrightness, entry->alpha);
            if (gEffectSpritePoolType == 4) {
                switch (entry->phase) {
                case 8:
                case 10:
                case 12:
                    glist = effectSpritePoolLoadTexture(glist, ((entry->frame++ >> 2) % 8) + 2);
                    break;
                case 15:
                case 18:
                case 22:
                    glist = effectSpritePoolLoadTexture(glist, 0);
                    break;
                default:
                    glist = effectSpritePoolLoadTexture(glist, 1);
                    break;
                }
            } else if (gEffectSpriteTextureSetups[gEffectSpritePoolType].count >= 2) {
                glist = effectSpritePoolLoadTexture(glist, entry->frame++ % gEffectSpriteTextureSetups[gEffectSpritePoolType].count);
            }
            scaleSize = entry->scale * 4.0;
            guScaleF(mtxScale, scaleSize, scaleSize > 0.0 ? scaleSize : -scaleSize, 1.0f);
            switch (gEffectSpritePoolType) {
            case 3:
                entry->angle += entry->sway;
                matrixMakeRotationZ(mtxTemp, entry->angle);
                break;
            case 4:
                matrixMakeRotationZ(mtxTemp, entry->tilt);
                break;
            default:
                matrixMakeRotationZ(mtxTemp, gEffectSpriteWindAngle);
                break;
            }
            guMtxCatF(mtxScale, mtxTemp, mtxScale);
            guTranslateF(mtxTemp, entry->drawX * 4.0, entry->y * 4.0, -50.0f);
            guMtxCatF(mtxScale, mtxTemp, mtxScale);
            guMtxF2L(mtxScale, &entry->mtx[gGfxBufferIndex]);
            gSPMatrix(glist++, &entry->mtx[gGfxBufferIndex], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            gSPVertex(glist++, osVirtualToPhysical(gEffectSpriteVertices), 4, 0);
            gSP2Triangles(glist++, 0, 1, 2, 0, 0, 2, 3, 0);
            gDPPipeSync(glist++);
        }
        if (entry->age != 0) {
            processed++;
            if (gEffectSpriteUpdate(entry) != 0 || entry->scale < 0.01) {
                entry->age = 0;
                gEffectSpriteFreeSlots[++gEffectSpriteFreeTop] = i;
                gEffectSpritePool->count--;
            }
        }
    }
    return glist;
}


extern f32 *gChunkLightR;
extern u8 gAmbientAudioLevels[];

void weatherSpawnRain(f32 density, s16 windAngle, f32 alpha, s16 mapChunk, f32 scale) {
    f32 randX;
    f64 calcAlpha;
    f64 densityVal;
    f64 alphaVal;
    f64 clampedAlpha;
    s32 idx;
    s32 count;

    if (gGlobalPauseFlags & 0x10) {
        densityVal = density;
        alphaVal = alpha;
        gEffectSpriteWindAngle = cosApprox(gPlayerSlots->camYaw) * windAngle;
        calcAlpha = densityVal * 255 / 3.9;
        clampedAlpha = calcAlpha > 255.0 ? 255.0 : calcAlpha;
        gAmbientAudioLevels[0] = clampedAlpha * alphaVal;
        if (densityVal < 1.0) {
            density *= 100.0f;
            if ((randomNonNegative() >> 15) % 32767 % 100 < density) {
                count = 1;
            } else {
                count = 0;
            }
        } else {
            count = density;
        }
        gEffectSpriteBrightness = *gChunkLightR * 100.0f + 100.0f;
        for (idx = 0; idx < count; idx++) {
            randX = (randomNonNegative() >> 15) % 32767 % 320;
            effectSpritePoolSpawn(0, mapChunk, ((f32)((randomNonNegative() >> 15) % 32767 % 125 / 800.0) + 0.1) * 2.5 * scale, randX, -10, 90.0f * scale);
        }
        if (gEffectSpritePool->count != 0) {
            renderCallbacksRegister(&effectSpriteRenderPool, NULL, 1);
        }
    }
}


void weatherSpawnSnow(f32 density, s16 windAngle, s16 mapChunk) {
    u32 random;
    s32 count;
    s32 i;
    f32 value;

    if (gGlobalPauseFlags & 0x10) {
        gEffectSpriteWindAngle = cosApprox(gPlayerSlots->camYaw) * windAngle;
        if (density < 1.0) {
            density *= 100.0f;
            random = randomLcgNext() / 10000;
            if ((s32)(random % 100) < density) {
                count = 1;
            } else {
                count = 0;
            }
        } else {
            count = density;
        }
        gEffectSpriteBrightness = 0xFF;
        for (i = 0; i < count; i++) {
            random = randomLcgNext() / 10000;
            value = random % 125 / 1000.0;
            random = randomLcgNext() / 10000;
            effectSpritePoolSpawn(1, mapChunk, value + 0.075, random % 320, -10, 200);
        }
        if (gEffectSpritePool->count != 0) {
            renderCallbacksRegister(&effectSpriteRenderPool, NULL, 1);
        }
    }
}




extern u8 D_807212E0;

void weatherSpawnDriftParticles(f32 density, s16 windAngle, s16 mapChunk, u8 poolType) {
    f32 randScale;
    f32 scaleVal;
    f64 scaledVal;
    s32 idx;
    s32 count;

    if (gGlobalPauseFlags & 0x10) {
        if (poolType == 3 && (randomNonNegative() >> 15) % 1000 >= 0x3DA) {
            effectSetDuration(-1);
            effectSetCallback(&effectSwayRiseUpdate);
            effectEnableFade();
            effectCreateAtPosition(&D_807212E0, (randomNonNegative() >> 15) % 100 * 0.01 + 0.4, (randomNonNegative() >> 15) % 320, 0.0f, -5.0f);
        }
        gEffectSpriteWindAngle = cosApprox(gPlayerSlots->camYaw) * windAngle;
        if (density < 1.0) {
            density *= 100.0f;
            if ((s32)(randomLcgNext() / 10000 % 100) < density) {
                count = 1;
            } else {
                count = 0;
            }
        } else {
            count = density;
        }
        gEffectSpriteBrightness = 0xFF;
        for (idx = 0; idx < count; idx++) {
            randScale = (randomNonNegative() >> 15) % 32767 % 80 * 0.005;
            scaleVal = randScale;
            if (gEffectSpritePoolType != 3) {
                scaledVal = randScale * 3.0;
                scaleVal = (scaledVal > 0.3 ? scaledVal : 0.3) < 2.0 ? (scaledVal > 0.3 ? scaledVal : 0.3) : 2.0;
            }
            scaleVal += 0.2;
            if (gEffectSpritePoolType == 4 && (randomNonNegative() >> 15) % 100 >= 0x33) {
                scaleVal *= -1.0f;
            }
            effectSpritePoolSpawn(poolType, mapChunk, scaleVal, randomLcgNext() / 10000 % 320, -10, 0xC8);
        }
        if (gEffectSpritePool->count != 0) {
            renderCallbacksRegister(&effectSpriteRenderPool, NULL, 1);
        }
    }
}


void weatherSpawnBananas(f32 density, s16 windAngle, f32 unused, s16 mapChunk, f32 scale) {
    f32 randX;
    s32 idx;
    s32 count;

    gEffectSpriteWindAngle = cosApprox(gPlayerSlots->camYaw) * windAngle;
    if (density < 1.0) {
        density *= 100.0f;
        if ((randomNonNegative() >> 15) % 32767 % 100 < density) {
            count = 1;
        } else {
            count = 0;
        }
    } else {
        count = density;
    }
    gEffectSpriteBrightness = 0xFF;
    for (idx = 0; idx < count; idx++) {
        randX = (randomNonNegative() >> 15) % 32767 % 320;
        effectSpritePoolSpawn(2, mapChunk, ((f32)((randomNonNegative() >> 15) % 32767 % 125 / 800.0) + 0.1) * 2.5 * scale, randX, -10, 0xFF);
    }
    if (gEffectSpritePool->count != 0) {
        renderCallbacksRegister(&effectSpriteRenderPool, NULL, 1);
    }
}


s32 effectSpritePoolFadeOut(void) {
    s16 i;
    EffectSpritePoolHeader *pool;

    pool = gEffectSpritePool;
    if (pool->count != 0) {
        gAmbientAudioLevels[0] *= 0.9;
        renderCallbacksRegister(&effectSpriteRenderPool, NULL, 1);
        return 0;
    }
    if (gEffectSpritePoolType != 6) {
        gAmbientAudioLevels[0] = 0;
        heapFreeDeferred(pool->entries);
        for (i = 0; i < gEffectSpriteTextureSetups[gEffectSpritePoolType].count; i++) {
            assetFreeBuffer(gEffectSpriteTextures[i], 0x34A, 0x64);
        }
        gEffectSpritePoolType = 6;
        gEffectSpritePoolLoaded = 0;
        return 1;
    }
    // ORIG: no final return; when pool->count == 0 && gEffectSpritePoolType == 6 the target branches past li v0,1 (0x2efc) to the epilogue (beq t0,at,0x2f00 at 0x2e64; jr ra at 0x2f18) with no $v0 write, so it returns pool from lw v0,%lo(gEffectSpritePool)(v0) at 0x2d4c
}

