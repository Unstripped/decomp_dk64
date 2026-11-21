#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17800.h"
#include "proto/global/61AA0.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/90D80.h"
#include "proto/global/936B0.h"
#include "proto/global/9BF30.h"

// This TU's .data (0x80750280-0x807502CC + 4-byte TU pad); the projectile sprites are sprite sheets of
// 124780.c.
Vtx gSpriteRingQuadVtx[4] = {
    {{ { -16, 0, 0 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } }},
    {{ { 15, 0, 0 }, 0, { 1984, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } }},
    {{ { 15, 31, 0 }, 0, { 1984, 1984 }, { 0xFF, 0xFF, 0xFF, 0xFF } }},
    {{ { -16, 31, 0 }, 0, { 0, 1984 }, { 0xFF, 0xFF, 0xFF, 0xFF } }},
};
extern EffectGridAsset gEffectSpriteSmokeCloud, D_8071FE3C, gEffectSpriteGooGreen;

typedef struct ProjectileTriple {
    EffectGridAsset *sprite[3];
} ProjectileTriple;

ProjectileTriple sProjectileSprites = { { &gEffectSpriteSmokeCloud, &D_8071FE3C, &gEffectSpriteGooGreen } };

extern void **gSpriteRingTextures;

typedef struct ProjectileState {
    /* 0x00 */ s16 spriteCount;
    /* 0x02 */ u8 pad2;
    /* 0x03 */ u8 pad3;
    /* 0x04 */ Mtx *matrices; // two per sprite (double-buffered by gGfxBufferIndex)
    /* 0x08 */ f32 radius;
    /* 0x0C */ f32 speed;
    /* 0x10 */ u8 frame;
    /* 0x11 */ u8 ringType;
} ProjectileState;

extern Gfx D_1000118;
extern Mtx D_2000000;
extern Mtx D_2000200;
extern u8 gGfxBufferIndex;
extern PlayerStruct *gPlayerSlots;

Gfx *projectileRenderSpriteRing(Gfx *glist, Actor *actor) {
    ProjectileState *sub;
    f32 modelMtx[4][4];
    f32 tmpMtx[4][4];
    s16 i;
    s16 stepAngle;
    s32 texIndex;

    sub = actor->customState;
    stepAngle = 0x1000 / sub->spriteCount;
    texIndex = (sub->frame++ % 16 + actor->yawSpeed) & 0xFF;

    gSPDisplayList(glist++, &D_1000118);
    gSPMatrix(glist++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glist++, &D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPTexture(glist++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombine(glist++, 0x119623, 0xFF2FFFFF);
    gDPSetTextureFilter(glist++, G_TF_BILERP);
    gSPGeometryMode(glist++, 0, G_ZBUFFER);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x00504A50);
    gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);

    actorFreeModelNodeList(actor);

    if (actor->unk15F != 0) {
        f32 collisionRadius;

        switch (sub->ringType) {
        case 0:
            collisionRadius = sub->radius * 10.0;
            break;
        case 1:
            collisionRadius = sub->radius * 0.15 * 2048.0;
            break;
        }
        actorSetCollisionRadius(actor, collisionRadius);
    }

    for (i = 0; i < sub->spriteCount; i++) {
        f32 offsetX;
        f32 offsetY;
        f32 offsetZ;
        f32 spriteScale;
        f64 progress;
        f32 growth;
        f64 clampedProgress;

        switch (sub->ringType) {
        case 0:
            offsetX = mathSinF(i * stepAngle) * sub->radius;
            offsetZ = mathCosF(i * stepAngle) * sub->radius;
            spriteScale = 1.0f;
            offsetY = 0.0f;
            break;
        case 1:
            progress = (actor->moveYaw - actor->unk15F) * 0.05;
            clampedProgress = (progress > 1.0) ? 1.0 : progress;
            growth = clampedProgress * (0.03 - 0.001) + 0.001;
            spriteScale = 130.0f * growth;
            offsetY = 1500.0f * growth;
            offsetX = mathSinF(actor->yaw + 0x400) * (growth * sub->radius * (0x800 - (s16)(i * stepAngle)));
            offsetZ = mathCosF(actor->yaw + 0x400) * (growth * sub->radius * (0x800 - (s16)(i * stepAngle)));
            break;
        }
        if (actor->unk15F != 0) {
            actorAppendModelNode(actor, offsetX, offsetY, offsetZ, spriteScale * 80.0, -1);
        }
        gDPLoadTextureBlock(glist++, gSpriteRingTextures[texIndex], G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        guScaleF(modelMtx, spriteScale, spriteScale, spriteScale);
        matrixMakeRotationY(tmpMtx, (gPlayerSlots->camYawInt * 360) / 4096);
        guMtxCatF(modelMtx, tmpMtx, modelMtx);
        guTranslateF(tmpMtx, actor->x + offsetX, actor->y, actor->z + offsetZ);
        guMtxCatF(modelMtx, tmpMtx, modelMtx);
        guMtxF2L(modelMtx, &sub->matrices[i * 2 + gGfxBufferIndex]);
        gSPMatrix(glist++, &sub->matrices[i * 2 + gGfxBufferIndex], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPVertex(glist++, osVirtualToPhysical(gSpriteRingQuadVtx), 4, 0);
        gSP2Triangles(glist++, 0, 1, 2, 0, 0, 2, 3, 0);
        gDPPipeSync(glist++);
    }
    return glist;
}

void loadModelAssetTable(void) {
    s16 i;
    s16 j;

    i = 0;
    gSpriteRingTextures = heapAlloc(0xC0);
    for (j = 0; j < 0x30; j++) {
        gSpriteRingTextures[i++] = assetLoad(0x19, i + 0x1654, 1, 1);
    }
}

extern Actor *gCurrentActor;

void projectileSpriteRingUpdate(void) {
    ProjectileState *sub;
    f64 wantedCount;

    sub = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->moveYaw = gCurrentActor->unk15F;
        sub->matrices = heapAlloc(0x1000);
        if (gCurrentActor->unk15F != 0) {
            gCurrentActor->collisionMode = 0x24;
        }
        if (sub->ringType == 1) {
            sfxPlayActorSound(gCurrentActor, 0x128, 1, 1, 0, 0xFF, 0.2f, 0);
            sfxPlayActorSound(gCurrentActor, 0x139, 0x3C, 1, 1, 0xFF, 1.0f, 0);
        }
    }
    if (sub->ringType != 0) {
        s32 kind = sub->ringType;

        switch (kind) {
        case 1:
            gCurrentActor->x += sub->speed * mathSinF(gCurrentActor->yaw);
            gCurrentActor->z += sub->speed * mathCosF(gCurrentActor->yaw);
            if (gCurrentActor->unk15F != 0) {
                gCurrentActor->unk15F -= 1;
            } else if (gCurrentActor->yawSpeed == 0x20) {
                gCurrentActor->yawSpeed = 0x10;
                sub->frame = 0;
            } else if (sub->frame >= 0x10) {
                heapFree(sub->matrices);
                actorDespawn(gCurrentActor);
            }
            break;
        }
    } else {
        if (gCurrentActor->unk15F != 0) {
            sub->radius += sub->speed;
            wantedCount = (f64)sub->radius * 0.3;
            sub->spriteCount = (wantedCount > 32.0) ? 32.0 : wantedCount;
        } else {
            sub->radius += (f32)((gCurrentActor->yawSpeed - sub->frame) + 0x10) * (sub->speed * 0.0625);
        }
        if ((sub->frame - gCurrentActor->yawSpeed) >= 0x10) {
            u8 count;

            count = gCurrentActor->unk15F;
            gCurrentActor->unk15F = count - 1;
            if (count) {
                projectileSpawnSpriteRing(0, sub->spriteCount, sub->radius, sub->speed, 0, 0x10);
                if (gCurrentActor->unk15F == 0) {
                    gCurrentActor->yawSpeed = 0x10;
                } else {
                    sub->frame = 0;
                }
            } else {
                heapFree(sub->matrices);
                actorDespawn(gCurrentActor);
            }
        }
    }
    renderCallbacksRegister(projectileRenderSpriteRing, gCurrentActor, 1);
}

typedef struct ProjectileConfig {
    /* 0x00 */ f32 yawRadians;
    /* 0x04 */ f32 speedXZ;
    /* 0x08 */ f32 speedY;
    /* 0x0C */ f32 spriteScale;
    /* 0x10 */ f32 type;
} ProjectileConfig;

typedef struct ProjectileSubState {
    /* 0x00 */ s32 spawnFrame;
    /* 0x04 */ u8 pad4[0xE];
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 type;
} ProjectileSubState;

extern EffectGridAsset D_8071FBA0;

void projectileActorUpdate(void) {
    ProjectileSubState *sub;
    ProjectileTriple spriteTriple;
    s16 particleIdx;

    sub = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        spriteTriple = sProjectileSprites;
        gCurrentActor->soundSlots[0] = -2;
        gCurrentActor->contactFlags &= ~1;
        gCurrentActor->moveYaw = ((ProjectileConfig *)gCurrentActor->spawnData)->yawRadians / 6.2831855f * 4095.0f;
        gCurrentActor->speedXZ = ((ProjectileConfig *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileConfig *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->collisionMode = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 40.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 30.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        sub->type = ((ProjectileConfig *)gCurrentActor->spawnData)->type;
        effectSetDuration(-1);
        effectSetFrameDelay(2);
        effectSetDepth(1);
        effectSetMaxDistance(2000);
        if (sub->type == 1) {
            effectSetColor(0, 0xFF, 0, 0xC8);
        } else {
            effectSetColor(0xFF, 0xFF, 0xFF, 0xFF);
        }
        if (sub->type == 3) {
            effectSetCallback(effectPulseSpinUpdate);
        }
        effectCreateAtActorBone(spriteTriple.sprite[sub->type - 1], ((ProjectileConfig *)gCurrentActor->spawnData)->spriteScale, gCurrentActor, 1, 2);
        sub->spawnFrame = gGameFrameCounter;
        sub->unk12 = 0;
        gCurrentActor->flags |= 0x80000;
        gCurrentActor->unk155 = sub->type;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 4.0f);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x14, 0x14, 1, 0x96, 0x78, 0, 1.0f);
    if ((gCurrentActor->contactFlags & 1) || (gCurrentActor->hasArcBounds != 0) || (gActorGlobalState.damaged != 0)) {
        if (sub->type == 3) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x16, 0xFF, 0x7F, 0x14);
        }
        if (gActorGlobalState.damaged == 0) {
            for (particleIdx = 0; particleIdx < 12; particleIdx += 2) {
                effectSetDepth(1);
                effectSetSpeed(particleIdx + 0xB000000);
                effectSetCallback(effectRadialSprayUpdate);
                effectCreateAtPosition(&D_8071FBA0, (randomNonNegative() >> 15) % 10 * 0.05 + 0.2,
                    gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
        actorDespawn(gCurrentActor);
    }
}

