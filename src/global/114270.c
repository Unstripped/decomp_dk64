#define PROTO_SKIP_func_8070FCCC
#define PROTO_SKIP_func_8071006C
#define PROTO_SKIP_func_80710174
#define PROTO_SKIP_func_807102AC
#define PROTO_SKIP_func_807103E0
#define PROTO_SKIP_effectSpritePoolSpawn
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

void effectSpritePoolSpawn(u8, s16, f32, s16, s16, u8);
u8 func_8070FCCC(struct M114aAngle *);
u8 func_8071006C(struct M114aAngle *);
u8 func_80710174(struct M114aAngle *);
u8 func_807102AC(struct M114aAngle *);
u8 func_807103E0(struct M114aAngle *);

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
    s16 unk20;
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

extern EffectSpritePoolHeader *D_807550E0;
extern PlayerStruct *gPlayerSlots;

extern u8 D_807FDA1A;
extern u8 D_807FDA1C;
extern u8 D_807FDA28;
extern u8 D_807FDA30[];

void effectSpritePoolReset(void) {
    s16 i;

    D_807550E0->count = 0;
    D_807FDA1C = 6;
    for (i = 0; i < 0x80; i++) {
        D_807FDA30[i] = i;
    }
    D_807FDA1A = 0x7F;
    D_807FDA28 = 0;
}


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

extern EffectSpriteTextureSetup D_80755264[];
extern void *D_807FD9F0[];
extern u8 D_807FDA18;
extern u8 D_807FDA19;
extern Vtx *D_807FDA20;
extern u8 (*D_807FDA24)(EffectSpriteParticle *particle);


void effectSpritePoolSpawn(u8 poolType, s16 mapChunk, f32 scale, s16 spawnX, s16 spawnY, u8 initialAlpha) {
    EffectSpriteParticle *entry;
    s16 i;
    s32 idx;

    if (D_807550E0->count >= 0x80) {
        return;
    }
    if (D_807550E0->count == 0 && D_807FDA28 == 0) {
        D_807550E0->entries = heapAlloc(0x5C00);
        heapClearBlock(D_807550E0->entries);
        D_807FDA1C = poolType;
        for (i = 0; i < D_80755264[poolType].count; i++) {
            D_807FD9F0[i] = assetLoad(D_80755264[poolType].type != 0 ? 0x19 : 7, D_80755264[poolType].images[i], 1, 1);
        }
        D_807FDA18 = D_80755264[poolType].width;
        D_807FDA19 = D_80755264[poolType].height;
        D_807FDA20 = D_80755264[poolType].vertices;
        D_807FDA24 = D_80755264[poolType].update;
        D_807FDA28 = 1;
    }
    idx = D_807FDA30[D_807FDA1A];
    D_807FDA30[D_807FDA1A--] = 0xFF;
    entry = &D_807550E0->entries[idx];
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
    entry->unk20 = (randomNonNegative() >> 15) % 32767 % 0xFFF;
    entry->angle = (randomNonNegative() >> 15) % 32767 % 360;
    switch (D_807FDA1C) {
    case 3:
        entry->sway = (randomNonNegative() >> 15) % 32767 % 100 * 0.02;
        break;
    case 4:
    case 5:
        entry->unk20 = (randomNonNegative() >> 15) % 20 + 5;
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
    D_807550E0->count++;
}

extern s16 D_807FDA1E;

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
    particle->x += diff * 180.0f - 0.3 * D_807FDA1E;
    particle->x += 4.0f * dist1 * sinApprox(diff);
    ang = mathAngleBetweenPoints2D(gPlayerSlots->camX, gPlayerSlots->camZ, gPlayerSlots->eyeX, gPlayerSlots->eyeZ);
    dz = gPlayerSlots->camZ - gPlayerSlots->eyeZ;
    dx = gPlayerSlots->camX - gPlayerSlots->eyeX;
    dist2 = sqrtf(dz * dz + dx * dx);
    particle->x -= 2.0 * dist2 * mathSinF(mathAngleSignedDistance(gPlayerSlots->unk2C8, ang));
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

extern Actor *gCamActor;
extern Actor *gPrimaryPlayerActor;
extern u32 gGlobalCutsceneFlags;
extern f32 D_807FD9EC;
extern u8 sEffectImpactPuffConfig;

#define CAM_Y_DISTANCE(y) ((y) < gPlayerSlots->camY ? gPlayerSlots->camY - (y) : -(gPlayerSlots->camY - (y)))

u8 func_8070FCCC(EffectSpriteParticle *particle) {
    f32 fallSpeed;
    f32 invScale;
    f32 bound;
    s32 isUnderMaxAge;
    f32 angle;
    f32 jitter;

    if (((CamState *)gCamActor->customState)->unkFA != 0 && gPlayerSlots->camY < ((CamState *)gCamActor->customState)->unk90 + 3.0f) {
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
            effectSetLifetime(particle->mapChunk);
            effectSetFlags(4);
            effectCreateAtPosition(&sEffectImpactPuffConfig, 0.3f, gPlayerSlots->camX - sinApprox(angle) * jitter, bound + 1.0, gPlayerSlots->camZ - cosApprox(angle) * jitter);
        }
        return 1;
    }
    return D_807FD9EC < particle->y;
}

#undef CAM_Y_DISTANCE



u8 func_8071006C(EffectSpriteParticle *particle) {
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

u8 func_80710174(EffectSpriteParticle *particle) {
    s32 isUnderMaxAge;
    f32 invScale;

    effectSpriteParticleTrackCamera(particle);
    particle->x += mathSinF(particle->unk20) * particle->sway;
    effectSpriteParticleWrapX(particle);
    particle->drawX = particle->x;
    invScale = 1.0 / (particle->scale * 4.0) * 8.0;
    isUnderMaxAge = particle->age < 0x3D;
    particle->unk20 += 0x14;
    particle->age++;
    particle->y += ((10.0f - (invScale - 10.0f)) + 10.0f) * 0.25;
    if (!isUnderMaxAge && particle->alpha >= 0xA) {
        particle->alpha -= 0xA;
    }
    return particle->y > 240.0f || particle->alpha < 0xA;
}

u8 func_807102AC(EffectSpriteParticle *particle) {
    s32 isUnderMaxAge;
    f32 invScale;

    effectSpriteParticleTrackCamera(particle);
    particle->x += mathSinF(particle->unk20) * particle->sway;
    effectSpriteParticleWrapX(particle);
    particle->drawX = particle->x;
    invScale = 1.0 / (particle->scale * 3.0) * 8.0;
    isUnderMaxAge = particle->age < 0x6F;
    particle->y += ((10.0f - (invScale - 10.0f)) + 10.0f) * 0.07;
    particle->unk20 += 0x32;
    particle->age++;
    if (!isUnderMaxAge && particle->alpha >= 0xA) {
        particle->alpha -= 0xA;
    }
    return D_807FD9EC < particle->y || particle->alpha < 0xA;
}


u8 func_807103E0(EffectSpriteParticle *particle) {
    f32 absScale;

    effectSpriteParticleTrackCamera(particle);
    particle->x += mathSinF(particle->angle * 0.5) * (f32)(particle->sway * 0.05);
    effectSpriteParticleWrapX(particle);
    particle->drawX = particle->x;
    particle->y += (1.0 + mathSinF(particle->angle)) * (f32)(1.0 + particle->unk20 * 0.08);
    particle->angle += 0x64;
    particle->tilt = (mathSinF(particle->angle * 0.5) * 0.5 + 0.5) * (particle->tiltRange * 4 - -particle->tiltRange * 4) + -particle->tiltRange * 4;
    absScale = particle->scale > 0.0f ? particle->scale : -particle->scale;
    if (absScale * 140.0f < particle->y && particle->alpha >= 0xA) {
        particle->alpha -= 0xA;
    }
    return D_807FD9EC < particle->y || particle->alpha < 0xA;
}


Gfx *effectSpritePoolLoadTexture(Gfx *glist, u8 textureIndex) {
    switch (D_80755264[D_807FDA1C].texSize) {
    case 1:
        gDPLoadTextureBlock(glist++, D_807FD9F0[textureIndex], D_80755264[D_807FDA1C].format, G_IM_SIZ_8b, D_807FDA18, D_807FDA19, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case 2:
        gDPLoadTextureBlock(glist++, D_807FD9F0[textureIndex], D_80755264[D_807FDA1C].format, G_IM_SIZ_16b, D_807FDA18, D_807FDA19, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case 3:
        gDPLoadTextureBlock(glist++, D_807FD9F0[textureIndex], D_80755264[D_807FDA1C].format, G_IM_SIZ_32b, D_807FDA18, D_807FDA19, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    }
    return glist;
}



extern PlayerState *gActivePlayerState;
extern EffectSpriteParticle *D_807FDAB0;
extern s16 D_807FDAB4;
extern u8 gGfxBufferIndex;
extern u8 D_807FDA1B;
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
    s16 i;
    u16 count = D_807550E0->count;
    u16 processed = 0;
    EffectSpriteParticle *entry;
    CamState *camState = gCamActor->customState;

    skipTimer = 0;
    skipNearPlayer = 0;

    if ((gPrimaryPlayerActor->state == 3) || (gPrimaryPlayerActor->state == 5)) {
        f32 rem = (gCamActor->distToFloor > 180.0f) ? 0.0f : 180.0f - gCamActor->distToFloor;
        if (count == 0) {}  // FAKE: deadsweep dead statement (steers uopt: count's temp slot)
        D_807FD9EC = rem * 0.02 * 240.0;
    } else {
        D_807FD9EC = 240.0f;
    }
    if ((gPrimaryPlayerActor->state == 0x42) && ((gActivePlayerState->hitActorType == 0x62) || (gActivePlayerState->hitActorType == 0x88))) {
        skipTimer = 1;
    }
    if ((camState->unkFA != 0) && (gPlayerSlots->camY < camState->unk90 + 3.0f)) {
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
    i = 0x80;  // FAKE: set before the unrelated texture if; moving it next to the loop changes the entry guard
    if (D_80755264[D_807FDA1C].count == 1) {
        glist = effectSpritePoolLoadTexture(glist, 0);
    }
    while (--i >= 0 && processed != count) {
        entry = &D_807550E0->entries[i];
        D_807FDAB0 = entry;
        D_807FDAB4 = D_807FDA1E;
        if ((entry->age != 0) && ((entry->mapChunk == -1) || mapChunkContainsPoint(entry->drawX, entry->y, entry->mapChunk)) && !skipNearPlayer && !skipTimer) {
            gDPSetPrimColor(glist++, 0, 0, D_807FDA1B, D_807FDA1B, D_807FDA1B, entry->alpha);
            if (D_807FDA1C == 4) {
                switch (entry->unk20) {
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
            } else if (D_80755264[D_807FDA1C].count >= 2) {
                glist = effectSpritePoolLoadTexture(glist, entry->frame++ % D_80755264[D_807FDA1C].count);
            }
            scaleSize = entry->scale * 4.0;
            guScaleF(mtxScale, scaleSize, scaleSize > 0.0 ? scaleSize : -scaleSize, 1.0f);
            switch (D_807FDA1C) {
            case 3:
                entry->angle += entry->sway;
                matrixMakeRotationZ(mtxTemp, entry->angle);
                break;
            case 4:
                matrixMakeRotationZ(mtxTemp, entry->tilt);
                break;
            default:
                matrixMakeRotationZ(mtxTemp, D_807FDA1E);
                break;
            }
            guMtxCatF(mtxScale, mtxTemp, mtxScale);
            guTranslateF(mtxTemp, entry->drawX * 4.0, entry->y * 4.0, -50.0f);
            guMtxCatF(mtxScale, mtxTemp, mtxScale);
            guMtxF2L(mtxScale, &entry->mtx[gGfxBufferIndex]);
            gSPMatrix(glist++, &entry->mtx[gGfxBufferIndex], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            gSPVertex(glist++, osVirtualToPhysical(D_807FDA20), 4, 0);
            gSP2Triangles(glist++, 0, 1, 2, 0, 0, 2, 3, 0);
            gDPPipeSync(glist++);
        }
        if (entry->age != 0) {
            processed++;
            if (D_807FDA24(entry) != 0 || entry->scale < 0.01) {
                entry->age = 0;
                D_807FDA30[++D_807FDA1A] = i;
                D_807550E0->count--;
            }
        }
    }
    return glist;
}


extern f32 *gChunkLightR;
extern u8 D_8077058C[];

void func_80711410(f32 density, s16 windAngle, f32 alpha, s16 mapChunk, f32 scale) {
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
        D_807FDA1E = cosApprox(gPlayerSlots->camYaw) * windAngle;
        calcAlpha = densityVal * 255 / 3.9;
        clampedAlpha = calcAlpha > 255.0 ? 255.0 : calcAlpha;
        D_8077058C[0] = clampedAlpha * alphaVal;
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
        D_807FDA1B = *gChunkLightR * 100.0f + 100.0f;
        for (idx = 0; idx < count; idx++) {
            randX = (randomNonNegative() >> 15) % 32767 % 320;
            effectSpritePoolSpawn(0, mapChunk, ((f32)((randomNonNegative() >> 15) % 32767 % 125 / 800.0) + 0.1) * 2.5 * scale, randX, -10, 90.0f * scale);
        }
        if (D_807550E0->count != 0) {
            renderCallbacksRegister(&effectSpriteRenderPool, NULL, 1);
        }
    }
}


void func_80711950(f32 density, s16 windAngle, s16 mapChunk) {
    u32 random;
    s32 count;
    s32 i;
    f32 value;

    if (gGlobalPauseFlags & 0x10) {
        D_807FDA1E = cosApprox(gPlayerSlots->camYaw) * windAngle;
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
        D_807FDA1B = 0xFF;
        for (i = 0; i < count; i++) {
            random = randomLcgNext() / 10000;
            value = random % 125 / 1000.0;
            random = randomLcgNext() / 10000;
            effectSpritePoolSpawn(1, mapChunk, value + 0.075, random % 320, -10, 200);
        }
        if (D_807550E0->count != 0) {
            renderCallbacksRegister(&effectSpriteRenderPool, NULL, 1);
        }
    }
}




extern u8 D_807212E0;

void func_80711BD0(f32 density, s16 windAngle, s16 mapChunk, u8 poolType) {
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
        D_807FDA1E = cosApprox(gPlayerSlots->camYaw) * windAngle;
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
        D_807FDA1B = 0xFF;
        for (idx = 0; idx < count; idx++) {
            randScale = (randomNonNegative() >> 15) % 32767 % 80 * 0.005;
            scaleVal = randScale;
            if (D_807FDA1C != 3) {
                scaledVal = randScale * 3.0;
                scaleVal = (scaledVal > 0.3 ? scaledVal : 0.3) < 2.0 ? (scaledVal > 0.3 ? scaledVal : 0.3) : 2.0;
            }
            scaleVal += 0.2;
            if (D_807FDA1C == 4 && (randomNonNegative() >> 15) % 100 >= 0x33) {
                scaleVal *= -1.0f;
            }
            effectSpritePoolSpawn(poolType, mapChunk, scaleVal, randomLcgNext() / 10000 % 320, -10, 0xC8);
        }
        if (D_807550E0->count != 0) {
            renderCallbacksRegister(&effectSpriteRenderPool, NULL, 1);
        }
    }
}


void func_80711F90(f32 density, s16 windAngle, f32 unused, s16 mapChunk, f32 scale) {
    f32 randX;
    s32 idx;
    s32 count;

    D_807FDA1E = cosApprox(gPlayerSlots->camYaw) * windAngle;
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
    D_807FDA1B = 0xFF;
    for (idx = 0; idx < count; idx++) {
        randX = (randomNonNegative() >> 15) % 32767 % 320;
        effectSpritePoolSpawn(2, mapChunk, ((f32)((randomNonNegative() >> 15) % 32767 % 125 / 800.0) + 0.1) * 2.5 * scale, randX, -10, 0xFF);
    }
    if (D_807550E0->count != 0) {
        renderCallbacksRegister(&effectSpriteRenderPool, NULL, 1);
    }
}


s32 effectSpritePoolFadeOut(void) {
    s16 i;
    EffectSpritePoolHeader *pool;

    pool = D_807550E0;
    if (pool->count != 0) {
        D_8077058C[0] *= 0.9;
        renderCallbacksRegister(&effectSpriteRenderPool, NULL, 1);
        return 0;
    }
    if (D_807FDA1C != 6) {
        D_8077058C[0] = 0;
        heapFreeDeferred(pool->entries);
        for (i = 0; i < D_80755264[D_807FDA1C].count; i++) {
            assetFreeBuffer(D_807FD9F0[i], 0x34A, 0x64);
        }
        D_807FDA1C = 6;
        D_807FDA28 = 0;
        return 1;
    }
    // FAKE: no final return; fall-through path (pool->count == 0 && D_807FDA1C == 6) returns pool (D_807550E0) in v0 implicitly
}

