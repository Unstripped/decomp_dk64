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
    s16 unk20;
    s16 unk22;
    s16 unk24;
    u8 pad26[2];
    f32 unk28;
    u8 pad2C[0x84];
    u8 age;
    u8 alpha;
    u8 frame;
    u8 unkB3;
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
    s32 unkC;
    s32 unk10;
} EffectSpriteTextureSetup;

extern EffectSpriteTextureSetup D_80755264[];
extern void *D_807FD9F0[];
extern u8 D_807FDA18;
extern u8 D_807FDA19;
extern s32 D_807FDA20;
extern s32 D_807FDA24;


void effectSpritePoolSpawn(u8 poolType, s16 mapChunk, f32 scale, s16 spawnX, s32 spawnY, u8 initialAlpha) {
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
        D_807FDA20 = D_80755264[poolType].unkC;
        D_807FDA24 = D_80755264[poolType].unk10;
        D_807FDA28 = 1;
    }
    idx = D_807FDA30[D_807FDA1A]; D_807FDA30[D_807FDA1A] = 0xFF; D_807FDA1A--;  // LAYOUT: one line keeps as1 line-order scheduling; split over three lines the slot pop reorders
    entry = &D_807550E0->entries[idx];
    entry->age = 1;
    entry->x = (f32)spawnX;
    entry->drawX = (f32)spawnX;
    entry->y = (f32)(s16)spawnY;
    entry->scale = scale;
    entry->mapChunk = mapChunk;
    entry->alpha = initialAlpha;
    entry->camYaw = gPlayerSlots->unk2C4;
    entry->camX = gPlayerSlots->camX;
    entry->camZ = gPlayerSlots->camZ;
    entry->unk20 = (randomNonNegative() >> 15) % 32767 % 0xFFF;
    entry->unk22 = (randomNonNegative() >> 15) % 32767 % 360;
    switch (D_807FDA1C) {
    case 3:
        entry->unk28 = (randomNonNegative() >> 15) % 32767 % 100 * 0.02;
        break;
    case 4:
    case 5:
        entry->unk20 = (randomNonNegative() >> 15) % 20 + 5;
        entry->unk28 = (randomNonNegative() >> 15) % 70 + 30;
        entry->unk22 = 0;
        if ((randomNonNegative() >> 15) % 100 > 80) {
            entry->unkB3 = 200;
        } else {
            entry->unkB3 = (randomNonNegative() >> 15) % 32767 % 6 + 5;
        }
        break;
    default:
        entry->unk28 = (randomNonNegative() >> 15) % 32767 % 100 * 0.1;
        break;
    }
    D_807550E0->count++;
}

extern s16 D_807FDA1E;
f32 sinApprox(f32);

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
    diff = gPlayerSlots->unk2C4 - particle->camYaw;
    if (diff > 3.1415927f) {
        diff = 6.2831855f - diff;
    }
    if (diff < -3.1415927f) {
        diff = -6.2831855f - diff;
    }
    particle->x = (f32)((f64)particle->x + ((f64)(diff * 180.0f) - 0.3 * (f64)D_807FDA1E));
    particle->x += 4.0f * dist1 * sinApprox(diff);
    ang = mathAngleBetweenPoints2D(gPlayerSlots->camX, gPlayerSlots->camZ, gPlayerSlots->unk21C, gPlayerSlots->unk224);
    dz = gPlayerSlots->camZ - gPlayerSlots->unk224;
    dx = gPlayerSlots->camX - gPlayerSlots->unk21C;
    dist2 = sqrtf(dz * dz + dx * dx);
    particle->x -= 2.0 * dist2 * mathSinF(mathAngleSignedDistance(gPlayerSlots->unk2C8, ang));
    particle->camYaw = gPlayerSlots->unk2C4;
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
f32 cosApprox(f32);

#define ANGA_CAM ((CamState *)gCamActor->customState)
#define ANGA_DIST(x) ((x) < gPlayerSlots->camY ? gPlayerSlots->camY - (x) : -(gPlayerSlots->camY - (x)))

s32 func_8070FCCC(EffectSpriteParticle *particle) {
    f32 inc;
    f32 nv;
    f32 bound;
    s32 isUnderMaxAge;
    f32 angle;
    f32 jitter;

    if (ANGA_CAM->unkFA != 0 && gPlayerSlots->camY < ANGA_CAM->unk90 + 3.0f) {
        bound = gPrimaryPlayerActor->waterY;
    } else {
        bound = ANGA_DIST(gPrimaryPlayerActor->unkA8) < ANGA_DIST(gPrimaryPlayerActor->waterY) ? gPrimaryPlayerActor->unkA8 : gPrimaryPlayerActor->waterY;
    }
    effectSpriteParticleTrackCamera(particle);
    effectSpriteParticleWrapX(particle);
    isUnderMaxAge = particle->age < 0x10;
    particle->age++;
    particle->drawX = particle->x;
    if (isUnderMaxAge == 0) {
        if (particle->alpha >= 0x50) {
            particle->alpha -= 0x50;
        }
    }
    nv = (f32)((1.0 / ((f64)particle->scale * 4.0)) * 60.0);
    inc = (f32)((f64)((30.0f - (nv - 30.0f)) + 30.0f) * 0.25);
    inc = inc > 5.0 ? inc : 5.0;
    particle->y += inc;
    if (particle->alpha < 0x50) {
        if ((randomNonNegative() >> 15) % 0x80 >= 0x56) {
            if (ANGA_DIST(bound) < 50.0f) {
                angle = ((randomNonNegative() >> 15) % 60 - 30) * 0.017453292f + gPlayerSlots->unk2C4;
                jitter = (randomNonNegative() >> 15) % 0x82;
                if ((gGlobalCutsceneFlags & 8) == 0) {
                    effectSetDepth(1);
                    effectSetCallback(&effectRandomYRotDecalUpdate);
                    effectSetLifetime(particle->mapChunk);
                    effectSetFlags(4);
                    effectCreateAtPosition(&sEffectImpactPuffConfig, 0.3f, gPlayerSlots->camX - sinApprox(angle) * jitter, (f32)((f64)bound + 1.0), gPlayerSlots->camZ - cosApprox(angle) * jitter);
                }
                return 1;
            }
        }
    }
    return (D_807FD9EC < particle->y) & 0xFF;
}

#undef ANGA_CAM
#undef ANGA_DIST



s32 func_8071006C(EffectSpriteParticle *particle) {
    s32 isDone;
    f32 riseStep;
    s32 age;
    u8 curAlpha;

    effectSpriteParticleTrackCamera(particle);
    effectSpriteParticleWrapX(particle);
    age = particle->age;
    isDone = (s32)age < 0xF;
    particle->age = (u8)(age + 1);
    particle->drawX = particle->x;
    age = 0x50;  // FAKE: value-named constant local; age reused as the 0x50 fade step keeps one register for both
    if (isDone == 0) {
        curAlpha = particle->alpha;
        if (curAlpha >= 0x50) {
            particle->alpha = (u8)(curAlpha - age);
        }
    }
    riseStep = (f32)((1.0 / ((f64)particle->scale * 4.0)) * 60.0);
    isDone = 0;
    particle->y = (f32)((f64)particle->y + ((f64)((30.0f - (riseStep - 30.0f)) + 30.0f) * 0.2));
    if (particle->y > 240.0f) {
        isDone = 1;
    }
    if (isDone == 0) {
        isDone = particle->alpha < 0x50;
    }
    return isDone & 0xFF;
}

s32 func_80710174(EffectSpriteParticle *particle) {
    f32 sway;
    s32 isDone;
    f32 riseStep;
    s32 age;
    u8 curAlpha;

    effectSpriteParticleTrackCamera(particle);
    sway = mathSinF(particle->unk20);
    particle->x += sway * particle->unk28;
    effectSpriteParticleWrapX(particle);
    particle->drawX = particle->x;
    riseStep = (f32)((1.0 / ((f64)particle->scale * 4.0)) * 8.0);
    age = particle->age;
    isDone = age < 0x3D;
    particle->unk20 = (s16)(particle->unk20 + 0x14);
    particle->age = (u8)(age + 1);
    particle->y = (f32)((f64)particle->y + ((f64)((10.0f - (riseStep - 10.0f)) + 10.0f) * 0.25));
    age = 0xA;  // FAKE: value-named constant local; age reused as the 0xA fade step keeps one register for both
    if (isDone == 0) {
        curAlpha = particle->alpha;
        if (curAlpha >= 0xA) {
            particle->alpha = (u8)(curAlpha - age);
        }
    }
    isDone = 0;
    if (particle->y > 240.0f) {
        isDone = 1;
    }
    if (isDone == 0) {
        isDone = particle->alpha < 0xA;
    }
    return isDone & 0xFF;
}

s32 func_807102AC(EffectSpriteParticle *particle) {
    f32 sway;
    s32 isDone;
    f32 riseStep;
    s32 age;
    u8 curAlpha;

    effectSpriteParticleTrackCamera(particle);
    sway = mathSinF(particle->unk20);
    particle->x += sway * particle->unk28;
    effectSpriteParticleWrapX(particle);
    particle->drawX = particle->x;
    riseStep = (f32)((1.0 / ((f64)particle->scale * 3.0)) * 8.0);
    age = particle->age;
    isDone = age < 0x6F;
    particle->y = (f32)((f64)particle->y + ((f64)((10.0f - (riseStep - 10.0f)) + 10.0f) * 0.07));
    particle->unk20 = (s16)(particle->unk20 + 0x32);
    particle->age = (u8)(age + 1);
    age = 0xA;  // FAKE: value-named constant local; age reused as the 0xA fade step keeps one register for both
    if (isDone == 0) {
        curAlpha = particle->alpha;
        if (curAlpha >= 0xA) {
            particle->alpha = (u8)(curAlpha - age);
        }
    }
    isDone = 0;
    if (D_807FD9EC < particle->y) {
        isDone = 1;
    }
    if (isDone == 0) {
        isDone = particle->alpha < 0xA;
    }
    return isDone & 0xFF;
}


s32 func_807103E0(EffectSpriteParticle *particle) {
    f32 scaleY;
    f32 absScaleY;
    s32 isDone;

    effectSpriteParticleTrackCamera(particle);
    particle->x += mathSinF((s16)(s32)(particle->unk22 * 0.5)) * (f32)(particle->unk28 * 0.05);
    effectSpriteParticleWrapX(particle);
    particle->drawX = particle->x;
    particle->y += (1.0 + (f64)mathSinF(particle->unk22)) * (f64)(f32)(1.0 + particle->unk20 * 0.08);
    particle->unk22 += 0x64;
    particle->unk24 = (s16)(s32)((mathSinF((s16)(s32)(particle->unk22 * 0.5)) * 0.5 + 0.5) * (f64)(particle->unkB3 * 4 - -particle->unkB3 * 4) + (f64)(-particle->unkB3 * 4));
    scaleY = particle->scale;
    if (scaleY > 0.0f) {
        absScaleY = scaleY;
    } else {
        absScaleY = -scaleY;
    }
    if ((absScaleY * 140.0f) < particle->y) {
        if (particle->alpha >= 0xA) {
            particle->alpha -= 0xA;
        }
    }
    isDone = 0;
    if (D_807FD9EC < particle->y) {
        isDone = 1;
    }
    if (isDone == 0) {
        isDone = particle->alpha < 0xA;
    }
    return isDone & 0xFF;
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
extern void *D_807FDAB0;
extern s16 D_807FDAB4;
extern u8 gGfxBufferIndex;
extern u8 D_807FDA1B;
extern u8 D_1000020, D_1000118, D_20000C0;


Gfx *effectSpriteRenderPool(Gfx *glist, Actor *actor) {
    f64 scaleSize;
    f32 mtxScale[4][4];
    f32 mtxTemp[4][4];
    f64 posX;
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
        D_807FD9EC = (f32)((f64)rem * 0.02 * 240.0);
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
    gSPDisplayList(glist++, &D_1000118);
    gSPDisplayList(glist++, &D_1000020);
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
        if ((entry->age != 0) && ((entry->mapChunk == -1) || mapChunkContainsPoint((s16)entry->drawX, (s16)entry->y, entry->mapChunk)) && !skipNearPlayer && !skipTimer) {
            gDPSetPrimColor(glist++, 0, 0, D_807FDA1B, D_807FDA1B, D_807FDA1B, entry->alpha);
            if (D_807FDA1C == 4) {
                switch (entry->unk20) {
                case 8: case 10: case 12: glist = effectSpritePoolLoadTexture(glist, ((entry->frame++ >> 2) % 8) + 2); break;
                case 15: case 18: case 22: glist = effectSpritePoolLoadTexture(glist, 0); break;
                default: glist = effectSpritePoolLoadTexture(glist, 1); break;
                }
            } else if (D_80755264[D_807FDA1C].count >= 2) {
                glist = effectSpritePoolLoadTexture(glist, entry->frame++ % D_80755264[D_807FDA1C].count);
            }
            scaleSize = (f64)entry->scale * 4.0;
            guScaleF(mtxScale, (f32)scaleSize, (f32)(scaleSize > 0.0 ? scaleSize : -scaleSize), 1.0f);
            switch (D_807FDA1C) {
            case 3:
                entry->unk22 = (s16)((f32)entry->unk22 + entry->unk28);
                matrixMakeRotationZ(mtxTemp, (f32)entry->unk22);
                break;
            case 4:
                matrixMakeRotationZ(mtxTemp, (f32)entry->unk24);
                break;
            default:
                matrixMakeRotationZ(mtxTemp, (f32)D_807FDA1E);
                break;
            }
            guMtxCatF(mtxScale, mtxTemp, mtxScale);
            guTranslateF(mtxTemp, (f32)((f64)entry->drawX * 4.0), (f32)((f64)entry->y * 4.0), -50.0f);
            guMtxCatF(mtxScale, mtxTemp, mtxScale);
            guMtxF2L(mtxScale, (Mtx *)((u8 *)entry + (gGfxBufferIndex << 6) + 0x30));
            gSPMatrix(glist++, (u8 *)entry + (gGfxBufferIndex << 6) + 0x30, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            gSPVertex(glist++, osVirtualToPhysical((void *)D_807FDA20), 4, 0);
            gSP2Triangles(glist++, 0, 1, 2, 0, 0, 2, 3, 0);
            gDPPipeSync(glist++);
        }
        if (entry->age != 0) {
            processed++;
            if ((((s32 (*)(EffectSpriteParticle *))D_807FDA24)(entry) != 0) || ((f64)entry->scale < 0.01)) {
                entry->age = 0;
                D_807FDA30[D_807FDA1A = D_807FDA1A + 1] = i;
                D_807550E0->count--;
            }
        }
    }
    return glist;
}


extern s32 gGlobalPauseFlags;
extern u8 D_807FDA1B;
extern f32 *D_8076A0B4;
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
        densityVal = (f64)density;
        alphaVal = (f64)alpha;
        D_807FDA1E = (s16)(s32)(cosApprox(gPlayerSlots->unk2C4) * (f32)windAngle);
        calcAlpha = (densityVal * 255) / 3.9;
        if (calcAlpha > 255.0) {
            clampedAlpha = 255.0;
        } else {
            clampedAlpha = calcAlpha;
        }
        D_8077058C[0] = (u8)(u32)(clampedAlpha * alphaVal);
        if (densityVal < 1.0) {
            density *= 100.0f;
            if ((f32)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 100) < density) {
                count = 1;
            } else {
                count = 0;
            }
        } else {
            count = (s32)density;
        }
        D_807FDA1B = (u8)(u32)((*D_8076A0B4 * 100.0f) + 100.0f);
        for (idx = 0; idx < count; idx++) {
            randX = (f32)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 320);
            effectSpritePoolSpawn(0, mapChunk, (f32)(((f64)(f32)((f64)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 125) / 800.0) + 0.1) * 2.5 * (f64)scale), (s16)(s32)randX, -10, 90.0f * scale);
        }
        if (D_807550E0->count != 0) {
            renderCallbacksRegister(&effectSpriteRenderPool, 0, 1);
        }
    }
}


void func_80711950(f32 density, s16 windAngle, s16 mapChunk) {
    s32 random;
    s32 count;
    s32 i;
    f32 value;

    if (gGlobalPauseFlags & 0x10) {
        D_807FDA1E = (s16)(cosApprox(gPlayerSlots->unk2C4) * windAngle);
        if (density < 1.0) {
            density *= 100.0f;
            random = randomLcgNext() / 10000;
            if ((f32)(s32)((u32)random % 100U) < density) {
                count = 1;
            } else {
                count = 0;
            }
        } else {
            count = (s32)density;
        }
        D_807FDA1B = 0xFF;
        for (i = 0; i < count; i++) {
            random = randomLcgNext() / 10000;
            value = (f32)((f64)((u32)random % 125U) / 1000.0);
            random = randomLcgNext() / 10000;
            effectSpritePoolSpawn(1, mapChunk, (f32)((f64)value + 0.075), (s16)(s32)((u32)random % 320U), -10, 200);
        }
        if (D_807550E0->count != 0) {
            renderCallbacksRegister(&effectSpriteRenderPool, 0, 1);
        }
    }
}




extern u8 D_807212E0;

void func_80711BD0(f32 density, s16 windAngle, s16 mapChunk, u8 poolType) {
    f32 randScale;
    f32 scaleVal;
    f64 scaledVal;
    s32 randSeed;
    s32 idx;
    s32 count;

    if (gGlobalPauseFlags & 0x10) {
        if ((poolType == 3) && (((s32)(randomNonNegative() >> 0xF) % 1000) >= 0x3DA)) {
            effectSetDuration(-1);
            effectSetCallback(&effectSwayRiseUpdate);
            effectEnableFade();
            randSeed = randomNonNegative();
            effectCreateAtPosition(&D_807212E0, (f32)(((f64)((s32)(randSeed >> 0xF) % 100) * 0.01) + 0.4), (f32)((s32)(randomNonNegative() >> 0xF) % 320), 0.0f, -5.0f);
        }
        D_807FDA1E = (s16)(s32)(cosApprox(gPlayerSlots->unk2C4) * (f32)windAngle);
        if ((f64)density < 1.0) {
            density *= 100.0f;
            if ((f32)(s32)((u32)(randomLcgNext() / 10000U) % 100U) < density) {
                count = 1;
            } else {
                count = 0;
            }
        } else {
            count = (s32)density;
        }
        D_807FDA1B = 0xFF;
        for (idx = 0; idx < count; idx++) {
            randScale = (f32)((f64)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 80) * 0.005);
            scaleVal = randScale;
            if (D_807FDA1C != 3) {
                scaledVal = (f64)randScale * 3.0;
                scaleVal = (f32)((scaledVal > 0.3 ? scaledVal : 0.3) < 2.0 ? (scaledVal > 0.3 ? scaledVal : 0.3) : 2.0);
            }
            scaleVal = (f32)((f64)scaleVal + 0.2);
            if ((D_807FDA1C == 4) && (((s32)(randomNonNegative() >> 0xF) % 100) >= 0x33)) {
                scaleVal *= -1.0f;
            }
            effectSpritePoolSpawn(poolType, mapChunk, scaleVal, (s16)(s32)((u32)(randomLcgNext() / 10000U) % 320U), -10, 0xC8);
        }
        if (D_807550E0->count != 0) {
            renderCallbacksRegister(&effectSpriteRenderPool, 0, 1);
        }
    }
}


void func_80711F90(f32 density, s16 windAngle, f32 unused, s16 mapChunk, f32 scale) {
    f32 randX;
    s32 idx;
    s32 count;

    D_807FDA1E = (s16)(s32)(cosApprox(gPlayerSlots->unk2C4) * (f32)windAngle);
    if ((f64)density < 1.0) {
        density *= 100.0f;
        if ((f32)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 100) < density) {
            count = 1;
        } else {
            count = 0;
        }
    } else {
        count = (s32)density;
    }
    D_807FDA1B = 0xFF;
    for (idx = 0; idx < count; idx++) {
        randX = (f32)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 320);
        effectSpritePoolSpawn(2, mapChunk, (f32)(((f64)(f32)((f64)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 125) / 800.0) + 0.1) * 2.5 * (f64)scale), (s16)(s32)randX, -10, 0xFF);
    }
    if (D_807550E0->count != 0) {
        renderCallbacksRegister(&effectSpriteRenderPool, 0, 1);
    }
}


s32 effectSpritePoolFadeOut(void) {
    s16 i;
    EffectSpritePoolHeader *pool;

    pool = D_807550E0;
    if (pool->count != 0) {
        D_8077058C[0] = (u8)(u32)((f64)(u32)D_8077058C[0] * 0.9);
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

