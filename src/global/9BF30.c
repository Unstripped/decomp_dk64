#include "common.h"
#include "actor.h"

void *heapAlloc(s32);
s32 assetLoad(s32, s32, s32, s32);
extern u8 *D_807FC7C0;

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
extern u8 *gPlayerSlots;

void actorFreeModelNodeList(Actor *);
void actorSetCollisionRadius(Actor *, f32);
void actorAppendModelNode(Actor *, f32, f32, f32, f32, s32);
f32 mathCosF(s16);
f32 mathSinF(s16);
void matrixMakeRotationY(f32 (*)[4], f32);
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

    sub = actor->unk174;
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
                q0 = ((f64)((*((s16 *)(((u8 *)actor) + 0xEE))) - actor->unk15F)) * 0.05;
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
            _g = (Gfx *)(glist++); _g->words.w0 = 0xFD180000; _g->words.w1 = ((s32 *)D_807FC7C0)[idx];
            gDPSetTile(glist++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD); gDPLoadSync(glist++); gDPLoadBlock(glist++, G_TX_LOADTILE, 0, 0, 0x3FF, 0x80); gDPPipeSync(glist++); _g = (Gfx *)(glist++); _g->words.w0 = 0xF5181000; _g->words.w1 = 0x00080200; gDPSetTileSize(glist++, G_TX_RENDERTILE, 0, 0, 0x7C, 0x7C); // FAKE: shared Gfx pointer; one source line steers scheduling

            guScaleF(mtx2, vscale, vscale, vscale);
            matrixMakeRotationY(mtx1, (f32)(((*((s16 *)(gPlayerSlots + 0x2C8))) * 0x168) / 4096));
            guMtxCatF(mtx2, mtx1, mtx2);
            guTranslateF(mtx1, actor->x + vx, actor->y, actor->z + vy);
            guMtxCatF(mtx2, mtx1, mtx2);
            guMtxF2L(mtx2, (Mtx *)(sub->unk4 + (((i * 2) + gGfxBufferIndex) << 6)));
            gSPMatrixShared(glist++, sub->unk4 + (((i * 2) + gGfxBufferIndex) << 6), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
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
        ((s32 *)D_807FC7C0)[i++] = assetLoad(0x19, i + 0x1654, 1, 1);
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

Gfx *projectileRenderSpriteRing(Gfx *glist, Actor *actor);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void actorDespawn(Actor *);
void heapFree(void *);
void projectileSpawnActor107(u8, u8, f32, f32, u8, u8);
void renderCallbacksRegister(void *, void *, u8);
f32 mathCosF(s16);
f32 mathSinF(s16);

void projectileSpriteRingUpdate(void) {
    ProjectileState *sub;
    u8 kind;
    f64 temp;
    f64 max;

    sub = gCurrentActor->unk174;
    if (!(gCurrentActor->flags & 0x10)) {
        *(s16 *)((u8 *)gCurrentActor + 0xEE) = gCurrentActor->unk15F;
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
            max = 32.0;
            if (temp > 32.0) {
                sub->unk0 = max;
            } else {
                sub->unk0 = temp;
            }
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
    void *unk0;
    void *unk4;
    void *unk8;
} ProjectileTriple;

typedef struct ProjectileSubState {
    s32 unk0;
    u8 pad4[0xE];
    u8 unk12;
    u8 unk13;
} ProjectileSubState;

typedef struct ProjectileActor {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[6];
    u16 unk6A;
    u8 pad6C[2];
    s16 unk6E;
    u8 pad70[0xC];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x30];
    f32 unkB8;
    u8 padBC[4];
    f32 unkC0;
    u8 padC4[0x2A];
    s16 unkEE;
    u8 padF0[0xC];
    u8 unkFC;
    u8 padFD[0x27];
    ProjectileConfig *unk124;
    u8 pad128[0x1C];
    u8 unk144;
    u8 pad145[0x10];
    u8 unk155;
    u8 pad156[0x1E];
    ProjectileSubState *unk174;
} ProjectileActor;

extern void *D_807502C0[];
extern u8 D_8071FBA0;
extern u32 gGameFrameCounter;
extern u8 D_807FBB85;
void func_807149FC(s32);
void func_80714998(s32);
void func_807149B8(s32);
void func_807149A8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_8071498C(void (*)(void));
void func_80714950();
s32 randomNonNegative(void);
void actorSetCollisionRadius(Actor *, f32);
void actorAppendModelNode(Actor *, f32, f32, f32, f32, s32);
void actorAppendModelSubNode(Actor *, f32, f32, f32, s32);
void func_8067ACB4(Actor *);
void actorApplyVelocity(Actor *);
void actorUpdateFloorContactAndTilt(Actor *, f32);
void billboardSubmit(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void func_80714C08(void *, f32, Actor *, s32, s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void effectPulseSpinUpdate(void);
void effectRadialSprayUpdate(void);

#define G_ACTOR ((ProjectileActor *)gCurrentActor)

void projectileActorUpdate(void) {
    ProjectileSubState *sub;
    ProjectileTriple spriteTriple;
    s16 particleIdx;

    sub = ((ProjectileActor *)gCurrentActor)->unk174;
    if (!(G_ACTOR->unk60 & 0x10)) {
        spriteTriple = *(ProjectileTriple *)D_807502C0;
        G_ACTOR->unk6A &= (G_ACTOR->unk6E = -2);
        G_ACTOR->unkEE = (s16)((G_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_ACTOR->unkB8 = G_ACTOR->unk124->unk4;
        G_ACTOR->unkC0 = G_ACTOR->unk124->unk8;
        G_ACTOR->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 40.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 30.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        sub->unk13 = (u8)(u32)G_ACTOR->unk124->unk10;
        func_807149FC(-1);
        func_80714998(2);
        func_807149B8(1);
        func_807149A8(0x7D0);
        if (sub->unk13 == 1) {
            func_807149C8(0, 0xFF, 0, 0xC8);
        } else {
            func_807149C8(0xFF, 0xFF, 0xFF, 0xFF);
        }
        if (sub->unk13 == 3) {
            func_8071498C(effectPulseSpinUpdate);
        }
        func_80714C08(((void **)&spriteTriple)[sub->unk13 - 1], G_ACTOR->unk124->unkC, gCurrentActor, 1, 2);
        sub->unk0 = gGameFrameCounter;
        sub->unk12 = 0;
        G_ACTOR->unk60 |= 0x80000;
        G_ACTOR->unk155 = sub->unk13;
    }
    func_8067ACB4(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 4.0f);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x14, 0x14, 1, 0x96, 0x78, 0, 1.0f);
    if ((G_ACTOR->unk6A & 1) || (G_ACTOR->unkFC != 0) || (D_807FBB85 != 0)) {
        if (sub->unk13 == 3) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x16, 0xFF, 0x7F, 0x14);
        }
        if (D_807FBB85 == 0) {
            for (particleIdx = 0; particleIdx < 0xC; particleIdx += 2) {
                func_807149B8(1);
                func_80714950(particleIdx + 0xB000000);
                func_8071498C(effectRadialSprayUpdate);
                func_80714CC0(&D_8071FBA0, (f32)(((f64)((s32)(randomNonNegative() >> 15) % 10) * 0.05) + 0.2),
                    G_ACTOR->unk7C, G_ACTOR->unk80, G_ACTOR->unk84);
            }
        }
        actorDespawn(gCurrentActor);
    }
}

