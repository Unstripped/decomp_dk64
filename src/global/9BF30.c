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

extern void **D_807FC7C0;

typedef struct ActorTrailState {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 pad2;
    /* 0x03 */ u8 pad3;
    /* 0x04 */ u8 *unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
} ActorTrailState;

extern Gfx D_1000118;
extern Mtx D_2000000;
extern Mtx D_2000200;
extern Gfx D_80750280;
extern u8 gGfxBufferIndex;
extern PlayerStruct *gPlayerSlots;

// Writes G_MTX through the function-scope _g pointer to avoid gbi.h's block-local phantom stack slot
#define gSPMatrixShared(pkt, m, p) { _g = (Gfx *)(pkt); _g->words.w0 = (_SHIFTL(G_MTX, 24, 8) | _SHIFTL(((sizeof(Mtx) - 1) / 8), 19, 5) | _SHIFTL(((p) ^ G_MTX_PUSH), 0, 8)); _g->words.w1 = (u32)(m); }

Gfx *projectileRenderSpriteRing(Gfx *glist, Actor *actor) {
    ActorTrailState *sub;
    f32 mtx2[4][4];
    f32 mtx1[4][4];
    s16 i;
    s16 stepAngle;
    f64 q0;
    f64 q1;
    f64 q2;
    f64 q3;
    f32 f;
    s32 idx;
    f32 collisionRadius;
    f32 vx;
    f32 vz;
    f32 vy;
    f32 vscale;
    Gfx *_g;

    sub = actor->customState;
    stepAngle = 0x1000 / sub->unk0;
    idx = (((sub->unk10++) % 16) + actor->yawSpeed) & 0xFF;

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
        switch (sub->unk11) {
        case 0:
            collisionRadius = (f32)(((f64)sub->unk8) * 10.0);
            break;
        case 1:
            collisionRadius = (f32)((((f64)sub->unk8) * 0.15) * 2048.0);
            break;
        }
        actorSetCollisionRadius(actor, collisionRadius);
    }

    i = 0;
    if (sub->unk0 > 0) {
        do {
            switch (sub->unk11) {
            case 0:
                vx = mathSinF(i * stepAngle) * sub->unk8;
                vy = mathCosF(i * stepAngle) * sub->unk8;
                vscale = 1.0f;
                vz = 0.0f;
                break;
            case 1:
                q0 = ((f64)(actor->moveYaw - actor->unk15F)) * 0.05;
                q1 = (1.0 < q0) ? (1.0) : (q0);
                f = (f32)((q1 * 0.028999999999999998) + 0.001);
                vscale = 130.0f * f;
                vz = 1500.0f * f;
                vx = mathSinF(actor->yaw + 0x400) * ((f * sub->unk8) * ((f32)(0x800 - ((s16)(i * stepAngle)))));
                vy = mathCosF(actor->yaw + 0x400) * ((f * sub->unk8) * ((f32)(0x800 - ((s16)(i * stepAngle)))));
                break;
            }
            if (actor->unk15F != 0) {
                actorAppendModelNode(actor, vx, vz, vy, (f32)(((f64)vscale) * 80.0), -1);
            }
            _g = (Gfx *)(glist++); _g->words.w0 = 0xFD180000; _g->words.w1 = (u32)D_807FC7C0[idx];
            gDPSetTile(glist++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD); gDPLoadSync(glist++); gDPLoadBlock(glist++, G_TX_LOADTILE, 0, 0, 0x3FF, 0x80); gDPPipeSync(glist++); _g = (Gfx *)(glist++); _g->words.w0 = 0xF5181000; _g->words.w1 = 0x00080200; gDPSetTileSize(glist++, G_TX_RENDERTILE, 0, 0, 0x7C, 0x7C); // LAYOUT: same-line texture block statements steer as1 scheduling

            guScaleF(mtx2, vscale, vscale, vscale);
            matrixMakeRotationY(mtx1, (f32)((gPlayerSlots->unk2C8 * 0x168) / 4096));
            guMtxCatF(mtx2, mtx1, mtx2);
            guTranslateF(mtx1, actor->x + vx, actor->y, actor->z + vy);
            guMtxCatF(mtx2, mtx1, mtx2);
            guMtxF2L(mtx2, (Mtx *)(sub->unk4 + (((i * 2) + gGfxBufferIndex) << 6)));
            gSPMatrixShared(glist++, sub->unk4 + (((i * 2) + gGfxBufferIndex) << 6), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH); // FAKE: gSPMatrix through the function-scope _g (shared Gfx pointer)
            gSPVertex(glist++, osVirtualToPhysical(&D_80750280), 4, 0);
            gSP2Triangles(glist++, 0, 1, 2, 0, 0, 2, 3, 0);
            gDPPipeSync(glist++);
            i++;
        } while (i < sub->unk0);
    }
    return glist;
}



void loadModelAssetTable(void) {
    s16 i;
    s16 j;

    i = 0;
    D_807FC7C0 = heapAlloc(0xC0);
    for (j = 0; j < 0x30; j++) {
        D_807FC7C0[i++] = assetLoad(0x19, i + 0x1654, 1, 1);
    }
}

extern Actor *gCurrentActor;

typedef struct ProjectileState {
    s16 unk0;
    u8 pad2;
    u8 pad3;
    u8 *unk4;
    f32 unk8;
    f32 unkC;
    u8 unk10;
    u8 unk11;
} ProjectileState;


void projectileSpriteRingUpdate(void) {
    ProjectileState *sub;
    u8 kind;
    f64 temp;

    sub = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->moveYaw = gCurrentActor->unk15F;
        sub->unk4 = heapAlloc(0x1000);
        if (gCurrentActor->unk15F != 0) {
            gCurrentActor->unk144 = 0x24;
        }
        if (sub->unk11 == 1) {
            sfxPlayActorSound(gCurrentActor, 0x128, 1, 1, 0, 0xFF, 0.2f, 0);
            sfxPlayActorSound(gCurrentActor, 0x139, 0x3C, 1, 1, 0xFF, 1.0f, 0);
        }
    }
    kind = sub->unk11;  // FAKE: copy of the dispatch byte; steers uopt register choice (a0 instead of v0)
    if (sub->unk11 != 0) {
        if (kind == 1) {
            if (gCurrentActor) {}  // FAKE: steers uopt: hoists &gCurrentActor into a1 for this block
            gCurrentActor->x += sub->unkC * mathSinF(gCurrentActor->yaw);
            gCurrentActor->z += sub->unkC * mathCosF(gCurrentActor->yaw);
            if (gCurrentActor->unk15F != 0) {
                gCurrentActor->unk15F -= 1;
            } else if (gCurrentActor->yawSpeed == 0x20) {
                gCurrentActor->yawSpeed = 0x10;
                sub->unk10 = 0;
            } else if (sub->unk10 >= 0x10) {
                heapFree(sub->unk4);
                actorDespawn(gCurrentActor);
            }
        }
    } else {
        if (gCurrentActor->unk15F != 0) {
            sub->unk8 += sub->unkC;
            temp = (f64)sub->unk8 * 0.3;
            sub->unk0 = (temp > 32.0) ? 32.0 : temp;
        } else {
            sub->unk8 = sub->unk8 + (f32)((gCurrentActor->yawSpeed - sub->unk10) + 0x10)
                * (sub->unkC * 0.0625);
        }
        if ((sub->unk10 - gCurrentActor->yawSpeed) >= 0x10) {
            u8 count;

            count = gCurrentActor->unk15F;
            gCurrentActor->unk15F = count - 1;
            if (count) {
                projectileSpawnActor107(0, sub->unk0, sub->unk8, sub->unkC, 0, 0x10);
                if (gCurrentActor->unk15F == 0) {
                    gCurrentActor->yawSpeed = 0x10;
                } else {
                    sub->unk10 = 0;
                }
            } else {
                heapFree(sub->unk4);
                actorDespawn(gCurrentActor);
            }
        }
    }
    renderCallbacksRegister(projectileRenderSpriteRing, gCurrentActor, 1);
}

typedef struct ProjectileConfig {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} ProjectileConfig;

typedef struct ProjectileTriple {
    void *sprite[3];
} ProjectileTriple;

typedef struct ProjectileSubState {
    s32 unk0;
    u8 pad4[0xE];
    u8 unk12;
    u8 unk13;
} ProjectileSubState;

extern void *D_807502C0[];
extern u8 D_8071FBA0;

void projectileActorUpdate(void) {
    ProjectileSubState *sub;
    ProjectileTriple spriteTriple;
    s16 particleIdx;

    sub = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        spriteTriple = *(ProjectileTriple *)D_807502C0;
        gCurrentActor->contactFlags &= (gCurrentActor->soundSlots[0] = -2);
        gCurrentActor->moveYaw = (s16)((((ProjectileConfig *)gCurrentActor->spawnData)->unk0 / 6.2831855f) * 4095.0f);
        gCurrentActor->speedXZ = ((ProjectileConfig *)gCurrentActor->spawnData)->unk4;
        gCurrentActor->speedY = ((ProjectileConfig *)gCurrentActor->spawnData)->unk8;
        gCurrentActor->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 40.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 30.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        sub->unk13 = (u8)((ProjectileConfig *)gCurrentActor->spawnData)->unk10;
        effectSetDuration(-1);
        effectSetMode(2);
        effectSetDepth(1);
        effectSetMaxDistance(0x7D0);
        if (sub->unk13 == 1) {
            effectSetColor(0, 0xFF, 0, 0xC8);
        } else {
            effectSetColor(0xFF, 0xFF, 0xFF, 0xFF);
        }
        if (sub->unk13 == 3) {
            effectSetCallback(effectPulseSpinUpdate);
        }
        effectCreateAtActorBone(spriteTriple.sprite[sub->unk13 - 1], ((ProjectileConfig *)gCurrentActor->spawnData)->unkC, gCurrentActor, 1, 2);
        sub->unk0 = gGameFrameCounter;
        sub->unk12 = 0;
        gCurrentActor->flags |= 0x80000;
        gCurrentActor->unk155 = sub->unk13;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 4.0f);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x14, 0x14, 1, 0x96, 0x78, 0, 1.0f);
    if ((gCurrentActor->contactFlags & 1) || (gCurrentActor->hasArcBounds != 0) || (gActorGlobalState.unk15 != 0)) {
        if (sub->unk13 == 3) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x16, 0xFF, 0x7F, 0x14);
        }
        if (gActorGlobalState.unk15 == 0) {
            for (particleIdx = 0; particleIdx < 0xC; particleIdx += 2) {
                effectSetDepth(1);
                effectSetSpeed(particleIdx + 0xB000000);
                effectSetCallback(effectRadialSprayUpdate);
                effectCreateAtPosition(&D_8071FBA0, (f32)(((f64)((s32)(randomNonNegative() >> 15) % 10) * 0.05) + 0.2),
                    gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
        actorDespawn(gCurrentActor);
    }
}

