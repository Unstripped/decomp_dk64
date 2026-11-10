#include "common.h"
#include "actor.h"
#define PROTO_SKIP_actorScriptStart // PROTO: The number of arguments doesn't agree with the number in the
#define PROTO_SKIP_effectFreeAndUnlink // FAKE: callee prototype steer
#define PROTO_SKIP_func_806FDAB8 // FAKE: callee prototype steer
#define PROTO_SKIP_func_8072881C // FAKE: callee prototype steer
#define PROTO_SKIP_playerKongStopSoundByState // FAKE: callee prototype steer
#define PROTO_SKIP_sfxPlayOnFreeSlot // FAKE: callee prototype steer
#include "proto/bonus/12A0.h"
#include "proto/bonus/2690.h"
#include "proto/global/100180.h"
#include "proto/global/1025E0.h"
#include "proto/global/112080.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/1295B0.h"
#include "proto/global/131B0.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/5E2F0.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/90D80.h"
#include "proto/global/936B0.h"
#include "proto/global/A7710.h"
#include "proto/global/C4620.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"
#include "proto/global/F56F0.h"

typedef struct {
    f32 pad0;
    f32 unk4;
} Struct_4_Unk0;

typedef struct {
    Struct_4_Unk0 *unk0;
    char pad4[0x30];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    char pad40[0x64 - 0x40];
    u16 unk64;
    char pad66[2];
    s32 unk68;
} Struct_4;

typedef struct Struct_7548 {
    s16 unk0;
    char pad2[2];
    s32 unk4[5];
    u8 unk18[5];
    char pad1D;
    s16 unk1E;
    s16 unk20;
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u8 unk25;
    u8 unk26;
} Struct_7548;
// Actor storage beyond the 0x178-byte Actor view (bonus actors keep a second payload pointer here).
typedef struct BonusActorExt {
    Actor actor;
    void *unk178;
    s16 *unk17C;
} BonusActorExt;

extern Actor *gCurrentActor;

void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);  // FAKE: callee prototype steer

extern u16 D_807FD63C;
struct Struct_71B4;
typedef struct Struct_174 {
    struct Struct_71B4 *unk0;
    u8 unk4[4];
    u8 unk8;
    u8 unk9;
    char padA[7];
    u8 unk11;
    char pad12[0xA];
    u8 unk1C;
} Struct_174;


typedef struct Struct_71B4 {
    Actor *unk0[6];
    char pad18[3];
    u8 unk1B;
    u8 unk1C;
    char pad1D[3];
    s16 unk20;
    s16 unk22;
    char pad24;
    u8 unk25;
    char pad26;
    u8 unk27;
    u8 unk28;
    u8 unk29;
    char pad2A[2];
    f32 unk2C;
} Struct_71B4;
typedef struct {
    s16 unk0;
    char pad2[6];
    s8 unk8[6];
    char padE[8];
    s16 unk16;
} Struct_T0;

typedef struct {
    Actor *unk0;
    u8 unk4;
} Struct_Sp50;
typedef struct {
    char pad[0x23];
    u8 unk23;
    u8 unk24[2];
    u8 unk26[2];
    s16 unk28;
} Struct_CC08_174;
typedef struct {
    char pad[6];
    s16 unk6;
} Struct_AAA4_174;

typedef struct Actor_AAA4_Target {
    char pad[0x4];
    void *unk4;
    char pad8[0x50];
    s32 unk58;
    char pad5C[0x7C - 0x5C];
    f32 unk7C;
    f32 unk80;
    char pad84[0x174 - 0x84];
    struct {
        char pad[4];
        u8 unk4;
    } *unk174;
} Actor_AAA4_Target;

typedef struct {
    Actor_AAA4_Target *actor;
    s32 pad;
} ActorEntry_B930;

extern ActorEntry_B930 gActiveActors[];
extern u16 gActiveActorCount;
extern s16 D_8002D900;
typedef struct {
    f32 unk0;
    f32 unk4;
    char pad8[0x10];
    s16 unk18;
    char pad1A[0x10];
    s16 unk2A;
    s8 unk2C;
    u8 unk2D;
} Struct_B920_S2;

typedef struct Actor_B920 Actor_B920;

typedef struct {
    Actor_B920 *unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    s16 unkE;
} Struct_B920_S1;

struct Actor_B920 {
    char pad[4];
    Struct_4 *unk4;
    char pad8[0x74];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x5E];
    s16 unkE6;
    char padE8[0x40];
    s16 unk128;
    char pad12A[0x2A];
    u8 unk154;
    char pad155[0x1F];
    Struct_B920_S2 *unk174;
};

typedef struct {
    f32 x, y, z;
} Point3f;
extern Point3f **D_807F5FD4;

extern u8 D_807FBB85;
void func_8072881C(s32, void *, void *, void *);
void func_806FDAB8(u8, f32);  // FAKE: callee prototype steer

extern u8 D_1000118[];
extern u8 D_2000180[];
extern u8 D_20000C0[];
extern u32 gFrameCounter;
extern u8 gCurrentPlayerIndex;
extern s16 D_8002D8CA;
extern s16 D_8002D8D4[];
extern s16 D_8002D8E0[];
extern s16 gScreenWidth;
extern s16 gScreenHeight;
void playerKongStopSoundByState(void *, s16 *);
extern f32 D_8002D90C;
f32 mathCosF(s16);
f32 mathSinF(s16);
extern u8 D_8071FFD4[];
void effectFreeAndUnlink(s32); // FAKE: callee prototype steer

extern Actor *gSpawnedActor;
void actorScriptStart();

Gfx *bonusRenderCrosshair(Gfx *gdl, Actor *actor) {
    Struct_7548 *bonusExt = actor->customState;
    s16 crosshairX = bonusExt->unk1E;
    s16 crosshairY = bonusExt->unk20;
    s32 pad;

    gDPPipeSync(gdl++);
    gDPSetCombineMode(gdl++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPDisplayList(gdl++, D_1000118);
    gSPMatrix(gdl++, D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, crosshairX - 0x34, crosshairY - 0x34, 3.2f, 3.2f, 0xE1, 0.0f);
    gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, crosshairX + 0x34, crosshairY - 0x34, 3.2f, 3.2f, 0x13B, 0.0f);
    gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, crosshairX + 0x34, crosshairY + 0x34, 3.2f, 3.2f, 0x2D, 0.0f);
    gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, crosshairX - 0x34, crosshairY + 0x34, 3.2f, 3.2f, 0x87, 0.0f);
    return gdl;
}

typedef struct {
    char pad0[0x20];
    u8 unk20;
    char pad21;
    s16 unk22;
    u8 unk24;
    u8 unk25;
} BonusA_6940_178;
Gfx *bonusRenderTargetGameHud(Gfx *gdl, Actor *actor) {
    Struct_7548 *bonusExt = actor->customState;
    BonusA_6940_178 *targetExt = ((BonusActorExt *)actor)->unk178;
    s32 pad1[4];
    s32 textStr;
    s32 pad2[6];
    s32 textX;
    s32 pad3[4];
    s32 textX2;

    if (actor->state == 0) {
        if (bonusExt->unk26 != 0) {
            gdl = bonusRenderCrosshair(gdl, actor);
        }
    }
    gSPDisplayList(gdl++, D_1000118);
    gDPPipeSync(gdl++);
    gDPSetPrimColor(gdl++, 0, 0, 200, 200, 200, 255);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetRenderMode(gdl++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    gSPMatrix(gdl++, D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (actor->state != 1) {
        gdl = hudDrawRollingCounter(textDrawAnimated(gdl, targetExt->unk25, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, &targetExt->unk20, targetExt->unk22, &targetExt->unk24);
    }
    if (bonusExt->unk25 != 0) {
        textX = gScreenWidth >> 1;
        textStr = textTableGetString(0x1A, 6, 1);
        gDPPipeSync(gdl++);
        gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, bonusExt->unk25);
        gDPSetCombineLERP(gdl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        textX -= textGetStringWidth(1, textStr) >> 1;
        gdl = textDrawStringVtx(gdl, 1, textX << 2, (gScreenHeight - textGetFontHeight(1)) * 2, textStr, 1);
        bonusExt->unk25 -= (bonusExt->unk25 < 8) ? bonusExt->unk25 : 8;
    }
    if (bonusExt->unk24 != 0) {
        textX2 = gScreenWidth >> 1;
        textStr = textTableGetString(0x1A, 8, 1);
        gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, bonusExt->unk24);
        gDPSetCombineLERP(gdl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        textX2 -= textGetStringWidth(1, textStr) >> 1;
        gdl = textDrawStringVtx(gdl, 1, textX2 << 2, (textGetFontHeight(1) + gScreenHeight) * 2, textStr, 1);
        bonusExt->unk24 -= (bonusExt->unk24 < 8) ? bonusExt->unk24 : 8;
    }
    return gdl;
}

typedef struct {
    char pad0[5];
    u8 unk5;
    char pad6[2];
    s16 unk8;
} BonusA_CF0_Inner;
typedef struct {
    char pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x174 - 0x88];
    BonusA_CF0_Inner *unk174;
} BonusA_CF0_S1;
typedef struct {
    char pad0[4];
    BonusA_CF0_S1 *unk4;
} BonusA_CF0_Link;
typedef struct {
    char pad0[0x174];
    BonusA_CF0_Link *unk174;
} BonusA_CF0_Actor;
typedef struct {
    BonusA_CF0_Actor *unk0[6];
} BonusA_CF0_List;

Gfx *bonusRenderPopupGameHud(Gfx *gdl, Actor *actor) {
    Struct_7548 *bonusExt = actor->customState;
    BonusA_CF0_List *popupList = ((BonusActorExt *)actor)->unk178;
    s32 hasSetupGfx = 0;
    s32 textX;
    s32 textStr;
    s32 i;
    BonusA_CF0_S1 *targetActor;
    BonusA_CF0_Inner *targetInner;
    BonusA_CF0_Actor *popupActor;
    BonusA_CF0_Link *popupLink;

    if (actor->state == 0) {
        if (bonusExt->unk26 != 0) {
            gdl = bonusRenderCrosshair(gdl, actor);
        }
    }
    if (bonusExt->unk25 != 0) {
        textX = gScreenWidth >> 1;
        textStr = textTableGetString(0x1A, 6, 1);
        gDPPipeSync(gdl++);
        gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, bonusExt->unk25);
        gDPSetCombineLERP(gdl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        textX -= textGetStringWidth(1, textStr) >> 1;
        gdl = textDrawStringVtx(gdl, 1, textX << 2, (gScreenHeight - textGetFontHeight(1)) * 2, textStr, 1);
        bonusExt->unk25 -= (bonusExt->unk25 < 8) ? bonusExt->unk25 : 8;
    }
    if (bonusExt->unk24 != 0) {
        textX = gScreenWidth >> 1;
        textStr = textTableGetString(0x1A, 7, 1);
        gDPPipeSync(gdl++);
        gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, bonusExt->unk24);
        gDPSetCombineLERP(gdl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        textX -= textGetStringWidth(1, textStr) >> 1;
        gdl = textDrawStringVtx(gdl, 1, textX << 2, (textGetFontHeight(1) + gScreenHeight) * 2, textStr, 1);
        bonusExt->unk24 -= (bonusExt->unk24 < 8) ? bonusExt->unk24 : 8;
    }
    for (i = 0; i < 6; i++) {
        popupActor = popupList->unk0[i];
        popupLink = popupActor->unk174;
        targetActor = popupLink->unk4;
        targetInner = targetActor->unk174;
        if (targetInner->unk5 != 0 && actor->state == 0) {
            if (targetInner->unk8 < 0) {
                targetInner->unk8 = gfxResourceCreate(1, textTableGetString(0x1A, 9, 1), 9, targetActor->unk7C * 0.25, targetActor->unk80 * 0.25, targetActor->unk84 * 0.25);
            }
            if (hasSetupGfx == 0) {
                gSPDisplayList(gdl++, D_1000118);
                gDPPipeSync(gdl++);
                gDPSetCombineMode(gdl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetPrimColor(gdl++, 0, 0, 255, 255, 255, 255);
                gDPSetRenderMode(gdl++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
                gSPSetGeometryMode(gdl++, G_SHADE | G_SHADING_SMOOTH);
                gDPSetCycleType(gdl++, G_CYC_1CYCLE);
                gSPMatrix(gdl++, D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                hasSetupGfx = 1;
            }
            gdl = textDrawAnimated(gdl, targetInner->unk8, 9, targetActor->unk7C, targetActor->unk80 + 20.0f, targetActor->unk84, 0.1f);
        } else if (targetInner->unk8 >= 0) {
            gfxResourceFree(targetInner->unk8);
            targetInner->unk8 = -1;
        }
    }
    return gdl;
}

void bonusSpawnTarget(s16 x, s16 y, s16 z, u8 slotIndex, Struct_71B4 *gameCtx) {
    u8 targetType;
    Struct_174 *targetExt;

    if (gameCtx->unk28 < ((randomNonNegative() >> 0xF) % 100)) {
        targetType = 1;
    } else {
        targetType = 0;
    }
    if (actorSpawn(0xBA, targetType ? 0x32 : 0x33) != 0) {
        targetExt = gSpawnedActor->customState;
        actorScriptStart(gSpawnedActor, targetType ? 0x211 : 0x20F);
        scriptSetActorRampTarget(gSpawnedActor, gameCtx->unk2C, 0.0f);
        gSpawnedActor->x = x;
        gSpawnedActor->y = y - 0x19;
        gSpawnedActor->z = z;
        gSpawnedActor->yaw = 0xC00;
        targetExt->unk9 = slotIndex;
        targetExt->unk8 = targetType;
        targetExt->unk0 = gameCtx;
        gameCtx->unk0[slotIndex] = gSpawnedActor;
    }
}

void bonusDespawnTarget(Struct_174 *targetExt, Struct_71B4 *gameCtx) {
    gameCtx->unk0[targetExt->unk9] = 0;
    actorDespawn(gCurrentActor);
}

void bonusResetAmmo(void *ammoData) {
    s16 i;
    s16 y;
    u8 *ammoFlag;
    s32 *ammoSlot;
    s32 p;
    y = 0x118;
    for (i = 0; i < 5; i++) {
        p = (s32)effectSpriteMatrixUpdate;
        ammoSlot = (s32 *)ammoData + i;
        if (ammoSlot[1] != 0) {
            effectFreeAndUnlink(ammoSlot[1]);
        }
        ammoFlag = (u8 *)ammoData + i;
        ammoFlag[0x18] = 0;
        effectEnableFade();
        effectSetDuration(-1);
        effectSetMode(2);
        effectSetParam(i * 3);
        effectSetCallback((void *)p);
        effectSetSpeed(ammoFlag + 0x18);
        ammoSlot[1] = effectCreateAtPosition(D_8071FFD4, 1.0f, (f32) y, 210.0f, -10.0f);
        y -= 0x1E;
    }
    sfxPlayOnFreeSlot(0x3E4, 0x7FFF, 63.0f, 1.0f, 5, 0);
}

void bonusFireProjectile(f32 targetX, f32 targetY, f32 targetZ) {
    sfxPlayOnFreeSlot(0x59, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
    projectileSetTargetCoords(gCurrentActor->x, gCurrentActor->y - 10.0f, gCurrentActor->z);
    projectileAimAndSpawn(0x23, 1, 0.6f, targetX, targetY, targetZ, 385.0f, gCurrentActor);
}

u8 bonusAimAndFire(f32 aimX, f32 aimY, f32 aimZ) {
    Struct_7548 *bonusExt = gCurrentActor->customState;
    f32 screenX;
    f32 screenY;
    s16 ammoIndex;
    f32 distance;
    u8 fireStatus[1];

    fireStatus[0] = 0;
    bonusExt->unk26 = 1;
    camProjectToScreen(aimX, aimY, aimZ, &screenX, &screenY, 0, 4.0f, 0);
    bonusExt->unk1E = screenX;
    bonusExt->unk20 = screenY;
    gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, mathAngleBetweenPoints2D(aimX, aimZ, gCurrentActor->x, gCurrentActor->z), 10.0f);
    distance = sqrtf((gCurrentActor->x - aimX) * (gCurrentActor->x - aimX) + (gCurrentActor->z - aimZ) * (gCurrentActor->z - aimZ));
    gCurrentActor->roll = mathAngleEaseToward(gCurrentActor->roll, (s32)(mathAtan2(gCurrentActor->y - aimY, distance) * 2048.0 / 3.1415927f + 150.0), 5.0f);
    if ((D_807FD63C & 0xE000) != 0) {
        if (gCurrentActor->state == 0) {
            fireStatus[0] = 1;
            if (bonusExt->unk22 != 0) {
                if (bonusExt->unk23 != 0 && bonusExt->unk18[0] == 0) {
                    bonusFireProjectile(aimX, aimY, aimZ);
                    bonusExt->unk23--;
                    effectFreeAndUnlink(bonusExt->unk4[bonusExt->unk23]);
                    rumbleRequest(0, 0xFF, 3);
                    bonusExt->unk4[bonusExt->unk23] = 0;
                    for (ammoIndex = 0; ammoIndex < bonusExt->unk23; ammoIndex++) {
                        bonusExt->unk18[ammoIndex] = 10;
                    }
                } else if (bonusExt->unk23 == 0) {
                    if (gCurrentActor->unk155 == 0) {
                        fireStatus[0] = 2;
                        gCurrentActor->unk155 = 1;
                    }
                }
            } else if (bonusExt->unk23 < 5) {
                bonusExt->unk23 = 5;
                bonusResetAmmo(bonusExt);
                gCurrentActor->unk155 = 0;
            }
        }
    }
    return fireStatus[0];
}

typedef struct {
    char pad0[0x2E];
    s8 unk2E;
    s8 unk2F;
    u8 unk30;
    u8 unk31;
} BonusB_Ctrl;

extern s32 gCurrentMap;
extern void *gActivePlayerState;
typedef struct {
    char pad0[0x104];
    void *unk104;
} BonusB_Cam104;
#define BB_CAMCTX ((BonusB_Cam104 *)gActivePlayerState)

typedef struct {
    char pad0[0x104];
    void *unk104;
} BonusB_Cam;

#define BCAM ((BonusB_Cam *)gActivePlayerState)

extern BonusB_Ctrl gPlayerPadState;
extern u8 gGameMode;


void bonusTargetGameUpdate(void) {
    Struct_7548 *t3c = gCurrentActor->customState;
    Struct_71B4 *t0 = ((BonusActorExt *)gCurrentActor)->unk178;
    Point3f *p;
    f32 ang;
    u8 c;
    s32 r;
    u8 idx;

    if (!(gCurrentActor->flags & 0x10)) {
        c = gfxResourceCreate(1, textTableGetString(0x1A, 2, 1), 8, 0.0f, 0.0f, 0.0f);
        t0->unk25 = c;
        func_806FDAB8(c, 0.0f);
        t3c->unk23 = 5;
        t3c->unk0 = -2;
        t3c->unk22 = 0;
        playerStateQueueCallback(0x48, 0, 0);
        camSetTarget(BCAM->unk104, gCurrentActor, 4, 0x800, -7, 0, 0x16, 0x2C, 4, 0, 0.05f);
        camStartPath(0, 0, 1);
        gCurrentActor->roll = 0x310;
        switch (gCurrentMap) {
        case 0xA:
            t0->unk27 = 0x55;
            t0->unk28 = 0x46;
            t0->unk2C = 0.85f;
            t0->unk20 = 0x12;
            t0->unk22 = t0->unk20;
            t0->unk29 = 0x3C;
            break;
        case 0x73:
            t0->unk27 = 0x5A;
            t0->unk28 = 0x46;
            t0->unk2C = 1.0f;
            t0->unk20 = 0x16;
            t0->unk22 = t0->unk20;
            t0->unk29 = 0x3C;
            break;
        case 0x74:
            t0->unk27 = 0x57;
            t0->unk28 = 0x50;
            t0->unk2C = 1.2f;
            t0->unk20 = 0x19;
            t0->unk22 = t0->unk20;
            t0->unk29 = 0x3C;
            break;
        case 0x75:
            t0->unk27 = 0x5C;
            t0->unk28 = 0x50;
            t0->unk2C = 1.3f;
            t0->unk20 = 0x1C;
            t0->unk22 = t0->unk20;
            t0->unk29 = 0x3C;
            break;
        }
    }
    if (t3c->unk0 > 0) {
        t3c->unk22 = 0;
        if (gCurrentActor->state == 0 && (gPlayerPadState.unk30 >= 0x1F || gPlayerPadState.unk31 >= 0x1F)) {
            ang = mathAtan2(gPlayerPadState.unk2F, gPlayerPadState.unk2E) / 6.2831855f * 8.0 + 5.5;
            if (9.0f < ang) {
                ang -= 8.0f;
            }
            t3c->unk22 = ang;
        }
        p = *D_807F5FD4 + t3c->unk22;
        if (bonusAimAndFire(p->x, p->y, p->z) == 2) {
            t3c->unk25 = 0xFF;
            sfxPlayOnFreeSlot(0x3BC, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
        switch (gCurrentActor->state) {
        case 0:
            if ((gCurrentActor->parentActor)->state == 5) {
                gCurrentActor->state = 0xFF;
            }
            if (t0->unk22 == 0) {
                bonusEndWin(0, 0);
                camStartPath(0, 1, 0x11);
                gCurrentActor->state = 1;
            } else if (t0->unk27 < (randomNonNegative() >> 0xF) % 100) {
                r = (randomNonNegative() >> 0xF) % 0xFF;
                idx = r % 8;
                if (t0->unk0[idx] == 0) {
                    p = *D_807F5FD4 + idx + 1;
                    bonusSpawnTarget(p->x, p->y, p->z, idx, t0);
                }
            }
            if ((gCurrentActor->parentActor)->state == 4 && (gCurrentActor->parentActor)->unk155 != 0xFF) {
                gCurrentActor->state = 0xFE;
            }
            break;
        case 0xFE:
            t3c->unk24 = 0xFF;
            sfxPlayOnFreeSlot(0x142, 0x7FFF, 63.0f, 1.0f, 0, 0);
            gCurrentActor->state = 0;
            break;
        case 0xFF:
            bonusEndLose(0, 5);
            camStartPath(0, 1, 0x11);
            gCurrentActor->state = 1;
            break;
        }
    } else {
        switch (t3c->unk0) {
        case -2:
            if (gGameMode != 1) {
                t3c->unk0++;
                hudSpawnCountdownTimer(0xDC, 0x2A, t0->unk29);
                resQueueAttachActor(gCurrentActor, 0, 1);
            }
            break;
        case -1:
            if (!(gCurrentActor->flags & 0x2000000)) {
                t3c->unk0 = 1;
                actorSetStateTwo((void *)gCurrentActor->parentActor);
                bonusResetAmmo(t3c);
                sfxAllocateChannel(8, 1.0f);
            }
            break;
        }
    }
    if (t3c->unk0 >= -1) {
        renderCallbacksRegister(bonusRenderTargetGameHud, gCurrentActor, 3);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct BonusB_Sub178 {
    Actor *unk0[6];
    char pad18[2];
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    char pad1D[3];
    f32 unk20;
} BonusB_Sub178;


void bonusPopupGameUpdate(void) {
    Struct_7548 *t0 = gCurrentActor->customState;
    BonusB_Sub178 *s38 = ((BonusActorExt *)gCurrentActor)->unk178;
    Point3f *p;
    f32 y;
    f32 z;

    if (!(gCurrentActor->flags & 0x10)) {
        t0->unk23 = 5;
        t0->unk0 = -2;
        playerStateQueueCallback(0x48, 0, 0);
        camSetTarget(BCAM->unk104, gCurrentActor, 4, 0x800, 0x1A, 0, 0x1F, 0x15, 0x10, 0, 0.05f);
        camStartPath(0, 0, 1);
        gCurrentActor->roll = 0x9A;
        switch (gCurrentMap) {
        case 0x12:
            s38->unk20 = 0.5f;
            s38->unk1A = 0x2D;
            s38->unk1B = 0x1E;
            s38->unk1C = 0x46;
            break;
        case 0x76:
            s38->unk20 = 0.8f;
            s38->unk1A = 0x2D;
            s38->unk1B = 0x14;
            s38->unk1C = 0x46;
            break;
        case 0x77:
            s38->unk20 = 1.0f;
            s38->unk1A = 0x3C;
            s38->unk1B = 0x14;
            s38->unk1C = 0x46;
            break;
        case 0x78:
            s38->unk20 = 1.5f;
            s38->unk1A = 0x3C;
            s38->unk1B = 0x14;
            s38->unk1C = 0x46;
            break;
        }
        bonusPopupSpawnActors(s38);
    }
    if (gCurrentActor->state == 0) {
        gCurrentActor->unk15F = 1;
    } else {
        gCurrentActor->unk15F = 0;
    }
    if (t0->unk0 > 0) {
        t0->unk22 = 0;
        if (gCurrentActor->state == 0 && (gPlayerPadState.unk30 >= 0x1F || gPlayerPadState.unk31 >= 0x1F)) {
            if (gPlayerPadState.unk2F > 0) {
                if (gPlayerPadState.unk2E < -0x28) {
                    t0->unk22 = 1;
                } else if (gPlayerPadState.unk2E >= 0x29) {
                    t0->unk22 = 3;
                } else {
                    t0->unk22 = 2;
                }
            } else if (gPlayerPadState.unk2E < -0x28) {
                t0->unk22 = 4;
            } else if (gPlayerPadState.unk2E >= 0x29) {
                t0->unk22 = 5;
            } else {
                t0->unk22 = 6;
            }
        }
        p = *D_807F5FD4 + t0->unk22;
        y = p->y;
        z = p->z;
        if (t0->unk22 != 0) {
            y += 27.0f;
            z -= 8.0f;
        }
        switch (bonusAimAndFire(p->x, y, z)) {
        case 1:
            if (t0->unk22) {
                Actor *e = s38->unk0[t0->unk22 - 1];
                if (((Struct_174 *)e->customState)->unk1C == 0) {
                    ((Struct_174 *)e->customState)->unk1C = 6;
                }
            }
            break;
        case 2:
            t0->unk25 = 0xFF;
            sfxPlayOnFreeSlot(0x3BC, 0x7FFF, 63.0f, 1.0f, 0, 0);
            break;
        }
        switch (gCurrentActor->state) {
        case 0:
            if ((gCurrentActor->parentActor)->state == 5) {
                gCurrentActor->state = 0xFF;
            }
            if ((gCurrentActor->parentActor)->state == 4 && (gCurrentActor->parentActor)->unk155 != 0xFF) {
                gCurrentActor->state = 0xFE;
            }
            break;
        case 2:
            bonusEndLose(0, 1);
            camStartPath(0, 1, 0x11);
            gCurrentActor->state = 1;
            gCurrentActor->unk155 = 0;
            break;
        case 0xFE:
            t0->unk24 = 0xFF;
            gCurrentActor->state = 0;
            break;
        case 0xFF:
            bonusEndWin(0, 0);
            camStartPath(0, 1, 0x11);
            gCurrentActor->state = 1;
            gCurrentActor->unk155 = 1;
            break;
        }
    } else {
        switch (t0->unk0) {
        case -2:
            if (gGameMode != 1) {
                t0->unk0++;
                hudSpawnCountdownTimer(0xDC, 0x2A, s38->unk1A);
                resQueueAttachActor(gCurrentActor, 0, 2);
            }
            break;
        case -1:
            if (!(gCurrentActor->flags & 0x2000000)) {
                t0->unk0 = 1;
                actorSetStateTwo((void *)gCurrentActor->parentActor);
                bonusResetAmmo(t0);
                sfxAllocateChannel(8, 1.0f);
            }
            break;
        }
    }
    if (t0->unk0 >= -1) {
        renderCallbacksRegister(bonusRenderPopupGameHud, gCurrentActor, 3);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void bonusTargetUpdate(void) {
    Struct_174 *sub = gCurrentActor->customState;
    Struct_71B4 *p = sub->unk0;
    s32 step;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unk144 = 0x24;
    }
    func_8072881C(0, sub->unk4, sub, p);
    switch (gCurrentActor->state) {
    case 0:
        if (D_807FBB85 != 0) {
            if (p->unk22 - ((sub->unk8 != 0) ? 2 : 1) < 0) {
                p->unk22 = 0;
            } else {
                step = (sub->unk8 != 0) ? 2 : 1;
                p->unk22 -= step;
            }
            func_806FDAB8(p->unk25, 3.1415927f);
            actorScriptStart(gCurrentActor, (sub->unk8 != 0) ? 0x212 : 0x210);
            gCurrentActor->state = 1;
            gCurrentActor->unk155 = 0;
        } else if (gCurrentActor->unk155 != 0) {
            bonusDespawnTarget(sub, p);
        }
        break;
    case 1:
        if (gCurrentActor->unk155 != 0) {
            bonusDespawnTarget(sub, p);
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct {
    void *unk0;
    void *unk4;
    char pad8[9];
    u8 unk11;
} BonusB_Sub8648;

typedef struct {
    void *unk0;
    char pad4[2];
    u8 unk6;
    char pad7;
    s16 unk8;
} BonusB_Sub8648b;

void bonusPopupSpawnActors(BonusB_Sub178 *popupState) {
    s32 i;
    BonusB_Sub8648 *s2;
    Actor *s5;
    Point3f *s3;

    for (i = 1; i != 7; i++) {
        if (actorSpawn(0x12C, 0x15) != 0) {
            s2 = (BonusB_Sub8648 *)gSpawnedActor->customState;
            s2->unk0 = gCurrentActor;
            s2->unk11 = (((randomNonNegative() >> 0xF) % 0x7FFF) % (popupState->unk1C - popupState->unk1B + 1)) + popupState->unk1B;
            s3 = *D_807F5FD4 + i;
            actorScriptStart(gSpawnedActor, 0x1F5);
            gSpawnedActor->x = s3->x;
            gSpawnedActor->y = s3->y;
            gSpawnedActor->z = s3->z;
            gSpawnedActor->flags |= 0x1000;
            gSpawnedActor->yaw = 0x800;
            popupState->unk0[i - 1] = gSpawnedActor;
            s5 = gSpawnedActor;
            if (actorSpawn(0x12D, 0x16) != 0) {
                BonusB_Sub8648b *v0 = (BonusB_Sub8648b *)gSpawnedActor->customState;
                v0->unk0 = s5;
                v0->unk6 = i - 1;
                s2->unk4 = gSpawnedActor;
                v0->unk8 = -1;
            }
        }
    }
}

typedef struct {
    s8 unk0;
    u8 unk1;
    u16 unk2;
    s16 unk4;
    s16 unk6;
} BonusVtxEntry;

typedef struct {
    char pad0[0x1C];
    BonusVtxEntry *unk1C;
} BonusVtxModel;

typedef struct {
    char pad0[0x20];
    f32 unk20;
} BonusVtxInfo;

typedef struct {
    char pad0[4];
    u8 unk4;
    u8 unk5;
} BonusVtxSub;

typedef struct BonusVtxActor BonusVtxActor;
struct BonusVtxActor {
    char pad0[4];
    BonusVtxModel *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x82];
    s16 unkE6;
    char padE8[0x5C];
    u8 unk144;
    char pad145[0xF];
    u8 unk154;
    u8 unk155;
    char pad156[0x1E];
    void *unk174;
    BonusVtxInfo *unk178;
};

typedef struct {
    BonusVtxActor *unk0;
    BonusVtxActor *unk4;
    f32 unk8;
    f32 unkC;
    s8 unk10;
    u8 unk11;
    char pad12[2];
    f32 unk14;
    f32 unk18;
    u8 unk1C;
} BonusVtxLink;
#define BONUS_VTX_ACTOR ((BonusVtxActor *)gCurrentActor)

extern u8 gBossFightPhase;

void bonusActorUpdateVertexPositions(void) {
    BonusVtxLink *link = BONUS_VTX_ACTOR->unk174;
    s16 *timerPtr = link->unk0->unk174;
    BonusVtxInfo *vtxInfo = link->unk0->unk178;
    BonusVtxSub *sub;
    BonusVtxEntry *chk;
    s32 vb[2];
    f32 invScale;
    BonusVtxEntry *p;
    f32 fx;
    f32 fy;
    f32 zOffset;
    s32 i;
    if (!(BONUS_VTX_ACTOR->unk60 & 0x10)) {
        BONUS_VTX_ACTOR->unk144 = 0x24;
        link->unkC = 275.0f;
        link->unk8 = 275.0f;
        link->unk10 = link->unk11;
        BONUS_VTX_ACTOR->unk4->unk1C = heapAlloc(0x38);
        heapClearBlock(BONUS_VTX_ACTOR->unk4->unk1C);
    }
    sub = link->unk4->unk174;
    if (gBossFightPhase == 4 && sub->unk4 == 0 && link->unk10 == -1) {
        link->unk8 = 275.0f;
        link->unk10 = link->unk11;
        sub->unk5 = 0;
    }
    if (*timerPtr > 0 && link->unk0->unk154 == 0) {
        if (sub->unk4 == 0) {
            if (link->unk10 >= 0) {
                link->unk10--;
            }
            if (link->unk10 < 0) {
                link->unk8 -= vtxInfo->unk20;
            }
        } else {
            link->unk8 += 40.0f;
            link->unk0->unk154 = 2;
        }
    }
    link->unkC = link->unkC + (link->unk8 - link->unkC) * 0.3;
    if (sub->unk4 != 0) {
        if (link->unk14 < 1.0f) {
            link->unk14 += 0.1f;
        } else if (link->unk14 > 1.0f) {
            link->unk14 = 1.0f;
        }
    } else if (link->unk1C != 0) {
        link->unk1C--;
        if (link->unk1C == 0) {
            actorScriptStart(gCurrentActor, 0x1F6);
        }
    }
    chk = BONUS_VTX_ACTOR->unk4->unk1C;
    if (chk != 0) {
        vb[1] = 0;
        vb[0] = (s32)chk;
        invScale = 1.0f - ((link->unkC - 40.0f) / 235.0f);
        fx = mathSinF(link->unk4->unkE6) * (5000.0f * invScale + 150.0f);
        fy = mathCosF(link->unk4->unkE6) * (5000.0f * invScale + 150.0f);
        zOffset = link->unk14 * 128.0f + -128.0f;
        if (fx < 0.0f) {
            fx = 65535.0f + fx;
        }
        if (fy < 0.0f) {
            fy = 65535.0f + fy;
        }
        i = 4;
        p = (BonusVtxEntry *)(vb[1] * 8 + vb[0]);
        for (; i < 7; i++) {
            p->unk1 = i;
            p->unk0 = (s32)zOffset;
            p->unk2 = (u32)fx;
            p->unk4 = 0;
            p->unk6 = (u32)fy;
            if (fx > 32767.0f) {
                fx = fx + (65535.0f - fx) * 0.5;
            } else {
                fx = fx * 0.5;
            }
            if (fy > 32767.0f) {
                fy = fy + (65535.0f - fy) * 0.5;
            } else {
                fy = fy * 0.5;
            }
            p++;
        }
        switch (BONUS_VTX_ACTOR->unk155) {
        case 0:
            link->unk18 = link->unk18 + (invScale - link->unk18) * 0.1;
            break;
        case 1:
        case 2:
            link->unk18 = link->unk18 + (0.0 - link->unk18) * 0.1;
            break;
        }
        p->unk0 = (s32)(link->unk18 * -128.0f);
        p->unk1 = 0xE;
        p->unk2 = 0x61A8;
        p->unk4 = 0;
        p->unk6 = 0;
        p++;
        i = 0xC;
        do {
            p->unk0 = (s32)(link->unk18 * -128.0f);
            p->unk1 = i;
            i++;
            p += 2;
            p[-2].unk2 = 0xD8F0;
            p[-2].unk4 = 0;
            p[-2].unk6 = 0;
        } while (i < 0xD);
        p->unk0 = 0;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct {
    char pad0[0xC];
    f32 unkC;
    s8 unk10;
} BonusB_Par8E3C;

typedef struct {
    char pad0[0x174];
    BonusB_Par8E3C *unk174;
} BonusB_Parent8E3C;

typedef struct {
    BonusB_Parent8E3C *unk0;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    char pad7[5];
    f32 unkC;
} BonusB_Sub8E3C;

extern s16 D_8002D8C0[];

void bonusTurtleTroubleTurtleUpdate(void) {
    BonusB_Sub8E3C *t0 = gCurrentActor->customState;
    BonusB_Par8E3C *p40 = t0->unk0->unk174;
    f32 temp;
    f64 v;
    s16 idx;
    s32 a0;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->yaw = (randomNonNegative() >> 0xF) % 4096;
        gCurrentActor->accelY = -10.0f;
        gCurrentActor->contactFlags &= 0xFFFE;
        controllerAnimSetStateIfChanged(gCurrentActor, 0x688, 0.0f, 0.0f);
        scriptSetActorRampTarget(gCurrentActor, 1.0, 0.0f);
    }
    if (p40->unk10 == -1 && t0->unk4 == 0) {
        if (p40->unkC < 220.0f) {
            if (t0->unk5 == 0) {
                a0 = 0x7F;
                t0->unk5 = 1;
                idx = t0->unk6 % 3;
                if (t0->unk6 / 3 != 0) {
                    idx = 2 - idx;
                    a0 = 0x64;
                }
                idx = D_8002D8C0[idx];
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, idx, 0xFF, a0, 0, 0, 0.0f, 0);
            }
            if (p40->unkC < 40.0f) {
                t0->unk4 = 1;
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x1ED, 0xFF, 0x7F, 0, 0, 0.0f, 0);
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x76, 0xFF, 0x7F, 0x1E);
                gCurrentActor->moveYaw = gCurrentActor->yaw;
                gCurrentActor->speedXZ = 10.0f;
                actorScriptStart(t0->unk0, 0x1F7);
            }
        }
    }
    if (t0->unk4 == 0) {
        actorGetNodePos(t0->unk0, 1, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
    } else {
        if ((gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1)) {
            gCurrentActor->speedY = t0->unkC * -0.8f;
            v = -t0->unkC * 1.5;
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xFF, (u8)((255.0 < v) ? 255.0 : v), 0x7F, 0xA);
        }
        gCurrentActor->speedY = gCurrentActor->speedY + gCurrentActor->accelY;
        t0->unkC = gCurrentActor->speedY;
        actorUpdatePrevContactFlags(gCurrentActor);
        actorApplyVelocity(gCurrentActor);
        actorUpdateFloorContactAndTilt(gCurrentActor, 0);
    }
    gCurrentActor->yaw += p40->unkC;
    if (gCurrentActor->yaw >= 0x1000) {
        gCurrentActor->yaw -= 0x1000;
    }
    temp = 30000.0f / p40->unkC;
    gCurrentActor->pitch = mathSinF(gCurrentActor->yaw) * -temp;
    gCurrentActor->roll = mathCosF(gCurrentActor->yaw) * temp;
    temp = temp * 0.006666667f;
    temp = (temp < 1.0f) ? 1.0f : ((temp > 2.5f) ? 2.5f : temp);
    scriptSetActorRampTarget(gCurrentActor, temp, 0.0f);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct {
    s16 unk0;
    char pad2[2];
    f32 unk4;
    s8 unk8[6];
    s16 unkE;
    char pad10;
    u8 unk11;
    u8 unk12;
    char pad13;
    s16 unk14;
    s16 unk16;
} BonusLightFlashState;

extern s8 D_8002D8F4;
extern s16 D_8002D8F8;
extern s16 D_8002D8FC;
extern s16 D_8002D8EC[];

void bonusLightFlashGameUpdate(void) {
    Struct_7548 *t1 = gCurrentActor->customState;
    BonusLightFlashState *t0 = ((BonusActorExt *)gCurrentActor)->unk178;
    Point3f *p;
    f32 y;
    f32 z;
    s32 pad;
    s32 i;
    s32 j;
    s32 r;
    u8 c;
    s16 d;

    if (!(gCurrentActor->flags & 0x10)) {
        t1->unk23 = 5;
        t1->unk0 = -2;
        switch (gCurrentMap) {
        case 0x65:
            t0->unk16 = 0xA;
            D_8002D8F4 = 0x30;
            break;
        case 0x8D:
            t0->unk16 = 0xF;
            D_8002D8F4 = 0x30;
            break;
        case 0x8E:
            t0->unk16 = 5;
            D_8002D8F4 = 0x1E;
            break;
        case 0x8F:
            t0->unk16 = 0xA;
            D_8002D8F4 = 0x1E;
            break;
        }
        t0->unk14 = t0->unk16;
        t0->unkE = 0x3C;
        t0->unk12 = 0;
        c = gfxResourceCreate(1, textTableGetString(0x1A, 2, 1), 8, 0.0f, 0.0f, 0.0f);
        t0->unk11 = c;
        func_806FDAB8(c, 0.0f);
        t0->unk0 = 0x3C;
        t0->unk4 = 1.0f;
        playerStateQueueCallback(0x48, 0, 0);
        camSetTarget(BCAM->unk104, gCurrentActor, 4, 0x800, 0x1A, 0, 0x1F, 0x15, 0x10, 0, 0.05f);
        camStartPath(0, 0, 1);
        gCurrentActor->roll = 0x9A;
        gCurrentActor->flags |= 0x800000;
        gCurrentActor->tintR = 0xFF;
        gCurrentActor->tintG = 0xFF;
        gCurrentActor->tintB = 0xFF;
        i = 0;
        do {
            t0->unk8[i] = i | 0x80;
        } while (++i < 6);
        bonusLightFlashSpawnTargets(gCurrentActor);
    }
    if (t1->unk0 > 0) {
        if (gCurrentActor->state == 0) {
            t0->unk0 -= 1;
        } else {
            t0->unk0 = 0x3C;
        }
        if (t0->unk0 > 0) {
            t0->unk4 = t0->unk4 + 0.2f;
        } else {
            t0->unk4 = t0->unk4 - 0.2f;
        }
        if (t0->unk4 > 1.0) {
            t0->unk4 = 1.0f;
        }
        if (t0->unk4 < 0.0) {
            t0->unk4 = 0.0f;
        }
        lightSetColor(t0->unk4, t0->unk4, t0->unk4, 0);
        if (t0->unk4 == 0.0f) {
            j = (s16)(D_8002D8F8 - 1);
            ((s16 *)&D_8002D8F4)[2] = j;
            if (j <= 0) {
                sfxPlayOnFreeSlot(0x1A1, 0x7FFF, 63.0f, 1.0f, 0x50, 0);
                j = randomLcgNext() & 3; if (gCurrentActor->state && gCurrentActor->state) {} if (j == 9) {} D_8002D8F8 = j + 2; // FAKE/LAYOUT: dead tests make j a coloured candidate (andi v1) and burn one ring temp (addiu t4); one line keeps the lw t0 reload below the sh
            }
            d = D_8002D8FC + 1;
            ((s16 *)&D_8002D8F4)[4] = d;
            if (d == 0xE) {
                sfxPlayOnFreeSlot(D_8002D8EC[randomLcgNext() & 3], 0x7FFF, 63.0f, 1.0f, 0x14, 0);
            }
        } else {
            if (randomFloat() < 0.5f) { D_8002D8FC = 0; }
            else { d = -100; if (d) {} D_8002D8FC = d | 0; } // FAKE/LAYOUT: dead test and |0 keep d colored in v0; preserve this line.
            j = 1; if (j) {} D_8002D8F8 = j | 0; // FAKE/LAYOUT: dead test and |0 keep j colored in v1; preserve this line.
        }
        if (t0->unk0 < -0x1E) {
            t0->unk0 = D_8002D8F4;
            i = 0;
            do {
                t0->unk8[i] = -1;
                i++;
            } while (i < 6);
            for (i = 0; i != 6; i++) {
                j = i;
                r = ((((((((randomLcgNext() & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 7; // FAKE: restore the temporary ring after coloring the two constants.
                while (r >= 0) {
                    if (t0->unk8[j] == -1) {
                        r -= 1;
                        if (r >= 0) {
                            j += 1;
                        }
                    } else {
                        j += 1;
                    }
                    if (j >= 6) {
                        j = 0;
                    }
                }
                t0->unk8[j] = i | 0x80;
            }
        }
        t1->unk22 = 0;
        if (gCurrentActor->state == 0 && (gPlayerPadState.unk30 >= 0x1F || gPlayerPadState.unk31 >= 0x1F)) {
            if (gPlayerPadState.unk2F > 0) {
                if (gPlayerPadState.unk2E < -0x28) {
                    t1->unk22 = 1;
                } else if (gPlayerPadState.unk2E >= 0x29) {
                    t1->unk22 = 3;
                } else {
                    t1->unk22 = 2;
                }
            } else if (gPlayerPadState.unk2E < -0x28) {
                t1->unk22 = 4;
            } else if (gPlayerPadState.unk2E >= 0x29) {
                t1->unk22 = 5;
            } else {
                t1->unk22 = 6;
            }
        }
        p = *D_807F5FD4 + t1->unk22;
        y = p->y;
        z = p->z;
        if (t1->unk22 != 0) {
            y += 27.0f;
            z -= 8.0f;
        }
        switch (bonusAimAndFire(p->x, y, z)) {
        case 1:
            break;
        case 2:
            t1->unk25 = 0xFF;
            sfxPlayOnFreeSlot(0x3BC, 0x7FFF, 63.0f, 1.0f, 0, 0);
            break;
        }
        switch (gCurrentActor->state) {
        case 0:
            if (t0->unk14 == 0) {
                gCurrentActor->state = 2;
            }
            if ((gCurrentActor->parentActor)->state == 5) {
                gCurrentActor->state = 1;
            }
            break;
        case 1:
            bonusEndLose(0, 1);
            camStartPath(0, 1, 0x11);
            gCurrentActor->state = 3;
            break;
        case 2:
            bonusEndWin(0, 0);
            camStartPath(0, 1, 0x11);
            gCurrentActor->state = 3;
            break;
        }
    } else {
        switch (t1->unk0) {
        case -2:
            if (gGameMode != 1) {
                t1->unk0++;
                hudSpawnCountdownTimer(0xDC, 0x2A, ((u8 *)t0)[0xF]);
                resQueueAttachActor(gCurrentActor, 0, 9);
            }
            break;
        case -1:
            if (!(gCurrentActor->flags & 0x2000000)) {
                t1->unk0 = 1;
                actorSetStateTwo((void *)gCurrentActor->parentActor);
                bonusResetAmmo(t1);
                sfxAllocateChannel(8, 1.0f);
            }
            break;
        }
    }
    renderCallbacksRegister(func_80029B9C, gCurrentActor, 3);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct {
    char pad0[3];
    u8 unk3;
    char pad4[2];
    char unk6[2];
    char unk8[2];
    s16 unkA;
} BonusC_9B9C_A;

typedef struct {
    char pad0[0x11];
    u8 unk11;
    char unk12[2];
    char unk14[2];
    s16 unk16;
} BonusC_9B9C_B;

typedef struct {
    char pad0[0x25];
    u8 unk25;
    char unk26[2];
    char unk28[2];
    s16 unk2A;
} BonusC_9B9C_C;

Gfx *func_80029B9C(Gfx *gdl, Actor *srcActor) {
    Actor *actor;
    BonusC_9B9C_B *p0;
    BonusC_9B9C_A *p1;
    BonusC_9B9C_C *p2;

    p2 = (void *)srcActor->customState;
    p0 = ((BonusActorExt *)srcActor)->unk178;
    if (p2) { // FAKE: empty guard steers regalloc
    }
    p1 = ((BonusActorExt *)srcActor)->unk178;
    actor = srcActor;

    if (actor->actorType != 0x7E && actor->state == 0 && ((Struct_7548 *)actor->customState)->unk26 != 0) {
        gdl = bonusRenderCrosshair(gdl, (void *)srcActor);
    }
    gSPDisplayList(gdl++, &D_1000118);
    gDPPipeSync(gdl++);
    gDPSetPrimColor(gdl++, 0, 0, 200, 200, 200, 255);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetRenderMode(gdl++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    gSPMatrix(gdl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    switch (actor->actorType) {
    case 0x7D:
        if (actor->state != 3) {
            gdl = hudDrawRollingCounter(textDrawAnimated(gdl, p0->unk11, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, p0->unk14, p0->unk16, p0->unk12);
        }
        break;
    case 0x7C:
        if (actor->state != 3) {
            gdl = hudDrawRollingCounter(textDrawAnimated(gdl, p1->unk3, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, p1->unk8, p1->unkA, p1->unk6);
        }
        break;
    case 0x7E:
        switch (actor->state) {
        case 7:
            break;
        case 0:
        case 1:
        case 2:
            gdl = hudDrawRollingCounter(textDrawAnimated(gdl, p2->unk25, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, p2->unk28, p2->unk2A, p2->unk26);
            break;
        }
        break;
    }
    return gdl;
}

typedef struct {
    void *unk0;
    u8 unk4;
} BonusC_9E54_S;

void bonusLightFlashSpawnTargets(void *ownerActor) {
    Actor *a = ownerActor;
    s32 i;
    s16 *X = &D_8002D8CA - 1;
    Struct_T0 *base = ((BonusActorExt *)a)->unk178;

    for (i = 1; i != 7; i++) {
        if (actorSpawn(0x147, X[i - 1]) != 0) {
            BonusC_9E54_S *subExt = (BonusC_9E54_S *)gSpawnedActor->customState;
            s16 *actorProp = ((BonusActorExt *)gSpawnedActor)->unk17C;
            Point3f *pt;
            f32 scale;

            *actorProp = X[i - 1];
            subExt->unk0 = a;
            subExt->unk4 = i - 1;
            pt = *D_807F5FD4 + (base->unk8[subExt->unk4] & 0x7F) + 1;
            gSpawnedActor->x = pt->x;
            gSpawnedActor->y = pt->y;
            gSpawnedActor->z = pt->z;
            gSpawnedActor->state = 0;
            gSpawnedActor->flags |= 0x1000;
            gSpawnedActor->yaw = 0x800;
            if (i != 6) {
                playerKongStopSoundByState(gSpawnedActor, actorProp);
                actorScriptStart(gSpawnedActor, D_8002D8D4[i - 1]);
            }
            scale = (i != 6) ? 0.25f : 0.04f;
            gSpawnedActor->sub4->scaleX = scale;
            gSpawnedActor->sub4->scaleY = scale;
            gSpawnedActor->sub4->scaleZ = scale;
        }
    }
}

void bonusLightFlashTargetUpdate(void) {
    f32 scale;
    Struct_Sp50 *subExt;
    Actor *owner;
    Struct_T0 *base;
    f32 lightR;
    f32 lightG;
    f32 lightB;
    Point3f *p;
    s8 isHit;
    s8 flags;

    subExt = (Struct_Sp50 *)gCurrentActor->customState;
    owner = subExt->unk0;
    base = (Struct_T0 *)((BonusActorExt *)owner)->unk178;
    if (!(gCurrentActor->flags & 0x10)) {
        if (subExt->unk4 != 5) {
            actorClearAllNodeFlags(gCurrentActor);
            actorAppendModelNode(gCurrentActor, 0.0f, 50.0f, 0.0f, 80.0f, -1);
        }
        gCurrentActor->unk144 = 0x24;
    }
    p = *D_807F5FD4 + (base->unk8[subExt->unk4] & 0x7F) + 1;
    gCurrentActor->x = p->x;
    gCurrentActor->y = p->y;
    gCurrentActor->z = p->z;
    lightGetColor(&lightR, &lightG, &lightB, 0);
    if (lightR < 0.1f) {
        gCurrentActor->unk144 = 0;
    } else {
        gCurrentActor->unk144 = 0x24;
    }
    isHit = 0;
    if (D_807FBB85 == 1 && base->unk0 >= -9) {
        isHit = 1;
    }
    if (subExt->unk4 != 5) {
        flags = base->unk8[subExt->unk4];
        if (flags & 0x80) {
            base->unk8[subExt->unk4] = flags & 0x7F;
            actorScriptStart(gCurrentActor, D_8002D8D4[subExt->unk4]);
        } else if (lightR < 0.05f && ((Struct_4 *)gCurrentActor->sub4)->unk68 != 0) {
            actorScriptStart(gCurrentActor, 0);
        }
        if (isHit != 0) {
            actorScriptStart(gCurrentActor, D_8002D8E0[subExt->unk4]);
            sfxPlayOnFreeSlot(0x2A2, 0x7FFF, 63.0f, 1.0f, 0, 0);
            if (base->unk16 != 0) {
                base->unk16 += 1;
            }
        }
        func_806BF920();
    } else {
        gCurrentActor->flags |= 0x1000;
        gCurrentActor->yaw += 0x12C;
        if (base->unk0 < -0x1C) {
            gCurrentActor->state = 0;
        }
        scale = gCurrentActor->sub4->scaleX;
        if (gCurrentActor->state == 1) {
            scale = scale - 0.005;
            if (scale < 0.0) {
                scale = 0.0f;
            }
        } else {
            scale = 0.04f;
        }
        gCurrentActor->sub4->scaleX = scale;
        gCurrentActor->sub4->scaleY = scale;
        gCurrentActor->sub4->scaleZ = scale;
        if (isHit != 0) {
            sfxPlayOnFreeSlot(0x2A1, 0x7FFF, 63.0f, 1.0f, 0, 0);
            base->unk0 = 0;
            base->unk16 -= 1;
            gCurrentActor->state = 1;
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct {
    s16 unk0;
    char pad2;
    u8 unk3;
    s16 unk4;
    u8 unk6;
    char pad7;
    s16 unk8;
    s16 unkA;
} LargeB1_Sub178;

extern s8 D_8002D904;

void bonusPerilPathPanicGameUpdate(void) {
    Struct_7548 *t3c = gCurrentActor->customState;
    LargeB1_Sub178 *t0 = ((BonusActorExt *)gCurrentActor)->unk178;
    Point3f *p;
    f32 y;
    f32 z;
    s32 n;
    s32 i;

    if (!(gCurrentActor->flags & 0x10)) {
        t3c->unk23 = 5;
        t3c->unk0 = -2;
        D_8002D904 = 0;
        switch (gCurrentMap) {
        case 0x90:
            t0->unkA = 6;
            D_8002D900 = 0x15;
            break;
        case 0x91:
            t0->unkA = 8;
            D_8002D900 = 0x12;
            break;
        case 0x92:
            t0->unkA = 0xA;
            D_8002D900 = 0xF;
            break;
        case 0x93:
            t0->unkA = 0xC;
            D_8002D900 = 0xC;
            break;
        }
        t0->unk4 = 0x3C;
        t0->unk6 = 0;
        t0->unk8 = t0->unkA;
        t0->unk3 = gfxResourceCreate(1, textTableGetString(0x1A, 4, 1), 8, 0.0f, 0.0f, 0.0f);
        func_806FDAB8(t0->unk3, 0.0f);
        t0->unk0 = 0x1E;
        playerStateQueueCallback(0x48, 0, 0);
        camSetTarget(BB_CAMCTX->unk104, gCurrentActor, 4, 0x800, 0x1A, 0, 0x1F, 0x15, 0x10, 0, 0.05f);
        camStartPath(0, 0, 1);
        gCurrentActor->roll = 0x9A;
        for (i = 1; i != 7; i++) {
            if (actorSpawn(0x148, 0x21) != 0) {
                BonusC_9E54_S *u = (BonusC_9E54_S *)gSpawnedActor->customState;

                u->unk0 = gCurrentActor;
                u->unk4 = i;
                p = *D_807F5FD4 + i;
                gSpawnedActor->x = p->x;
                gSpawnedActor->y = p->y;
                gSpawnedActor->z = p->z + 45.0;
                gSpawnedActor->state = 0;
                gSpawnedActor->yaw = 0x800;
                gSpawnedActor->sub4->scaleX = 0.45f;
                gSpawnedActor->sub4->scaleY = 0.45f;
                gSpawnedActor->sub4->scaleZ = 0.45f;
            }
        }
    }
    if (t3c->unk0 > 0) {
        if (t0->unk0 > 0) {
            t0->unk0--;
        } else {
            if (actorSpawn(0x149, 0x3D) != 0) {
                BonusC_9E54_S *u = (BonusC_9E54_S *)gSpawnedActor->customState;

                n = D_8002D904;
                u->unk0 = gCurrentActor;
                p = *D_807F5FD4 + (n + n + n) + 1;
                gSpawnedActor->x = p->x + 50.0;
                gSpawnedActor->y = p->y + 12.0;
                gSpawnedActor->z = p->z - 5.0;
                gSpawnedActor->yaw = -0x400;
                gSpawnedActor->sub4->scaleX = 0.08f;
                if (u) {} // FAKE: empty guard steers regalloc
                gSpawnedActor->sub4->scaleY = 0.08f;
                gSpawnedActor->sub4->scaleZ = 0.08f;
            }
            n = D_8002D904;
            t0->unk0 = 0x5A;
            ((s8 *)&D_8002D900)[4] = (u16)(1 - n);
        }
        t3c->unk22 = 0;
        if (gCurrentActor->state == 0 && (gPlayerPadState.unk30 >= 0x1F || gPlayerPadState.unk31 >= 0x1F)) {
            if (gPlayerPadState.unk2F > 0) {
                if (gPlayerPadState.unk2E < -0x28) {
                    t3c->unk22 = 1;
                } else if (gPlayerPadState.unk2E >= 0x29) {
                    t3c->unk22 = 3;
                } else {
                    t3c->unk22 = 2;
                }
            } else if (gPlayerPadState.unk2E < -0x28) {
                t3c->unk22 = 4;
            } else if (gPlayerPadState.unk2E >= 0x29) {
                t3c->unk22 = 5;
            } else {
                t3c->unk22 = 6;
            }
        }
        p = *D_807F5FD4 + t3c->unk22;
        y = p->y;
        z = p->z;
        if (t3c->unk22 != 0) {
            y += 27.0f;
            z -= 8.0f;
        }
        switch (bonusAimAndFire(p->x, y, z)) {
        case 1:
            break;
        case 2:
            t3c->unk25 = 0xFF;
            sfxPlayOnFreeSlot(0x3BC, 0x7FFF, 63.0f, 1.0f, 0, 0);
            break;
        }
        switch (gCurrentActor->state) {
        case 0:
            if (t0->unk8 == 0) {
                gCurrentActor->state = 2;
            }
            if ((gCurrentActor->parentActor)->state == 5) {
                gCurrentActor->state = 1;
            }
            break;
        case 1:
            bonusEndLose(0, 1);
            camStartPath(0, 1, 0x11);
            gCurrentActor->state = 3;
            break;
        case 2:
            bonusEndWin(0, 0);
            camStartPath(0, 1, 0x11);
            gCurrentActor->state = 3;
            break;
        }
    } else {
        switch (t3c->unk0) {
        case -2:
            if (gGameMode != 1) {
                t3c->unk0++;
                hudSpawnCountdownTimer(0xDC, 0x2A, (u8)t0->unk4);
                resQueueAttachActor(gCurrentActor, 0, 0xB);
            }
            break;
        case -1:
            if (!(gCurrentActor->flags & 0x2000000)) {
                t3c->unk0 = 1;
                actorSetStateTwo((void *)gCurrentActor->parentActor);
                bonusResetAmmo(t3c);
                sfxAllocateChannel(8, 1.0f);
            }
            break;
        }
    }
    renderCallbacksRegister(func_80029B9C, gCurrentActor, 3);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct {
    char pad[4];
    u8 unk4;
} BonusC_AAA4_T;

void bonusPerilPathPanicKlaptrapUpdate(void) {
    Struct_AAA4_174 *actorExt;
    Actor_AAA4_Target *targetActor;
    f32 dx;
    f32 dz;
    s32 animScript;
    Struct_4_Unk0 *animSub;
    Struct_4 *modelData;
    BonusC_AAA4_T *targetExt;
    s32 i;

    actorExt = (Struct_AAA4_174 *)gCurrentActor->customState;
    modelData = (Struct_4 *)gCurrentActor->sub4;
    animSub = modelData->unk0;
    if (!(gCurrentActor->flags & 0x10)) {
        actorScriptStart(gCurrentActor, 0x239);
        gCurrentActor->unk144 = 0x24;
        modelData = (Struct_4 *)gCurrentActor->sub4;
    }
    animScript = modelData->unk64;
    if (animScript == 0x239) {
        for (i = 0; i < gActiveActorCount; i++) {
            targetActor = gActiveActors[i].actor;
            if (targetActor->unk58 == 0x149) {
                dx = targetActor->unk7C - gCurrentActor->x;
                dz = targetActor->unk80 - gCurrentActor->y;
                if (dx < 5.0 && dx > -5.0 && dz < 20.0f && dz > -20.0) {
                    targetExt = (BonusC_AAA4_T *)targetActor->unk174;
                    targetExt->unk4 = 8;
                    actorScriptStart(gCurrentActor, 0x23B);
                }
            }
        }
    }
    if ((animScript == 0x239 || animScript == 0x23B || (animScript == 0x238 && animSub != NULL && animSub->unk4 > 48.0f)) && D_807FBB85 == 1) {
        actorScriptStart(gCurrentActor, 0x23C);
        actorExt->unk6 = ((randomLcgNext() & 7) + 6) * D_8002D900;
    }
    if (animScript == 0x23A) {
        actorExt->unk6 -= 1;
        if (actorExt->unk6 == 0) {
            actorScriptStart(gCurrentActor, 0x238);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct {
    char pad0[0xA];
    s16 unkA;
} BonusC_AD10_B;

typedef struct {
    Actor *unk0;
    s8 unk4;
} BonusC_AD10_S;

void bonusPerilPathPanicFairyUpdate(void) {
    s32 pad;
    BonusC_AD10_S *subExt;
    Actor *owner;
    BonusC_AD10_B *ownerExt;
    Point3f *p;

    subExt = (BonusC_AD10_S *)gCurrentActor->customState;
    owner = subExt->unk0;
    ownerExt = ((BonusActorExt *)owner)->unk178;
    if (!(gCurrentActor->flags & 0x10)) {
        actorScriptStart(gCurrentActor, 0x2B5, ownerExt);
    }
    if (subExt->unk4 == 0 || subExt->unk4 >= 5) {
        gCurrentActor->x = gCurrentActor->x - 1.5;
    }
    p = *D_807F5FD4 + 3;
    if (gCurrentActor->x < p->x - 50.0) {
        if (ownerExt->unkA > 0) {
            ownerExt->unkA -= 1;
        }
        actorDespawn(gCurrentActor);
    }
    if (subExt->unk4 != 0) {
        subExt->unk4 -= 1;
        if (subExt->unk4 < 4) {
            if (subExt->unk4 == 3) {
                sfxPlayOnFreeSlot(0x2D2, 0x7FFF, 63.0f, 7.12f, 0, 1);
            }
            gCurrentActor->sub4->scaleX *= 0.8f;
            gCurrentActor->sub4->scaleY *= 0.8f;
            gCurrentActor->sub4->scaleZ *= 0.8f;
        }
        if (subExt->unk4 == 0) {
            actorDespawn(gCurrentActor);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct {
    char pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    char pad21C[0x7C];
    u16 *unk298;
    char pad29C[0x2C];
    s16 unk2C8;
    char pad2CA[0x26];
} LargeB4Player;

typedef struct {
    char pad0[2];
    s8 unk2;
    s8 unk3;
} LargeB4Ctrl;

extern Actor *gPrimaryPlayerActor;
extern LargeB4Player *gPlayerSlots;
extern LargeB4Ctrl *D_807ECDEC;
typedef struct {
    char pad0[4];
    f32 unk4;
    char pad8[0x1C];
    f32 unk24;
} LargeB5Anim;

typedef struct {
    LargeB5Anim *unk0;
    char pad4[0x30];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} LargeB5Model;

typedef struct LargeB5Actor {
    char pad0[4];
    LargeB5Model *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x5E];
    s16 unkE6;
    s16 unkE8;
    char padEA[0x32];
    struct LargeB5Actor *unk11C;
    char pad120[0x34];
    u8 unk154;
    u8 unk155;
    char pad156[0x1E];
    struct LargeB5State *unk174;
} LargeB5Actor;

typedef struct LargeB5State {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    char pad1A[2];
    f32 unk1C;
    char pad20[2];
    s16 unk22;
    char pad24;
    u8 unk25;
    u8 unk26;
    char pad27;
    s16 unk28;
    s16 unk2A;
    s8 unk2C;
    s8 unk2D[1];
} LargeB5State;

typedef struct {
    void *unk0;
    f32 unk4;
    f32 unk8;
    char padC[2];
    s16 unkE;
} LargeB5Proj;

#define LB5 ((LargeB5Actor *)gCurrentActor)

void bonusBigBugBashGameUpdate(void) {
    s32 pad0[4];
    f32 fs0;
    f32 fs1;
    f32 diffDelta;
    LargeB5Anim *animData = LB5->unk4->unk0;
    LargeB5State *t = LB5->unk174;
    s32 i;
    u8 c;
    s32 padz;
    LargeB5Proj *p0;
    s16 spawnAngle;

    if (!(LB5->unk60 & 0x10)) {
        gPrimaryPlayerActor->state = 0x77;
        gPrimaryPlayerActor->unk155 = 0;
        t->unk0 = LB5->unk7C + 10.0;
        t->unk4 = LB5->unk84 + 8.0;
        LB5->unk80 = LB5->unk80 + 50.0;
        switch (gCurrentMap) {
        case 0x66:
            t->unk2A = 4;
            break;
        case 0x94:
            t->unk2A = 6;
            break;
        case 0x95:
            t->unk2A = 8;
            break;
        case 0x96:
            t->unk2A = 0xA;
            break;
        }
        t->unk26 = 0;
        t->unk22 = 0x3C;
        t->unk28 = t->unk2A;
        fs0 = 1 * 0.0f;
        c = gfxResourceCreate(1, textTableGetString(0x1A, 2, 1), 8, fs0, fs0, fs0);
        t->unk25 = c;
        func_806FDAB8(c, fs0);
        lightSetColor(1.0f, 1.0f, 1.0f, -1);
        LB5->unkE8 = 0;
        LB5->unkE6 = 0x800;
        controllerAnimSetStateIfChanged(gCurrentActor, 0x5FB, 0.0f, 0.0f);
        LB5->unk4->unk34 = 0.2f;
        LB5->unk4->unk38 = 0.2f;
        LB5->unk4->unk3C = 0.2f;
        camStartPath(0, 0, 1);
        LB5->unk154 = 3;
        t->unk1C = 0.0f;
        t->unk10 = 0.0f;
        t->unk14 = 0.0f;
        t->unk8 = 0.0f;
        t->unkC = 0.0f;
        actorSpawn(0x14C, 0x55);
        p0 = (LargeB5Proj *)gSpawnedActor->customState;
        p0->unk0 = gCurrentActor;
        t->unk2C = 0x3C;
        i = 0;
        do {
            t->unk2D[i] = 1;
            i++;
        } while (i != 1);
    }
    for (i = 0; i < 1; i++) {
        if (t->unk2D[i] > 0) {
            t->unk2D[i] -= 1;
            if (t->unk2D[i] == 0 && actorSpawn(0x14A, 0x53) != 0) {
                LargeB5Proj *s0 = (LargeB5Proj *)gSpawnedActor->customState;

                s0->unk0 = gCurrentActor;
                s0->unk4 = gSpawnedActor->x;
                s0->unk8 = gSpawnedActor->z;
                s0->unkE = 2;
                spawnAngle = mathAngleBetweenPoints2D(t->unk0, t->unk4, LB5->unk7C, LB5->unk84) + 0x800;
                s0->unk4 = mathSinF(spawnAngle) * 70.0 + t->unk0;
                s0->unk8 = mathCosF(spawnAngle) * 70.0 + t->unk4;
                if (t->unk2C == 0) {
                    gSpawnedActor->x = s0->unk4;
                    gSpawnedActor->y = LB5->unk80 - 30.0;
                    gSpawnedActor->z = s0->unk8;
                } else {
                    gSpawnedActor->x = t->unk0 - 30.0;
                    gSpawnedActor->z = t->unk0;
                    gSpawnedActor->y = LB5->unk80 - 30.0;
                }
            }
        }
    }
    if (t->unk2C != 0) {
        t->unk2C -= 1;
    }
    t->unk18 += 0x19;
    if (LB5->unk154 < 2) {
        f32 fv0;
        f32 fv1;

        fs1 = mathSinF(gPlayerSlots[gCurrentPlayerIndex].unk2C8);
        fv0 = mathCosF(gPlayerSlots[gCurrentPlayerIndex].unk2C8);
        fs0 = D_807ECDEC->unk2 * 0.04f;
        fv1 = D_807ECDEC->unk3 * 0.04f;

        diffDelta = (fs0 * fv0 - fv1 * fs1) - t->unk10;
        t->unk10 += diffDelta * 0.125f;
        t->unk14 += ((fs0 * fs1 + fv1 * fv0) - t->unk14) * 0.25f;
        t->unk8 += t->unk10;
        t->unkC -= t->unk14;
    }
    switch (LB5->unk154) {
    case 0: {
        f32 prev = t->unk1C;

        t->unk1C += (-diffDelta * 4.0f - t->unk1C) * 0.125f;
        if (t->unk1C < 0.0f) {
            if (t->unk1C < -8.0f) {
                t->unk1C = -8.0f;
            }
            if (prev >= 0.0f) {
                controllerAnimSetStateIfChanged(gCurrentActor, 0x5FC, 0.0f, 0.0f);
            }
            if (animData != NULL) {
                controllerApplyMotionWindow(gCurrentActor, animData, -t->unk1C);
            }
        } else {
            if (t->unk1C > 8.0f) {
                t->unk1C = 8.0f;
            }
            if (prev < 0.0f) {
                controllerAnimSetStateIfChanged(gCurrentActor, 0x5FB, 0.0f, 0.0f);
            }
            if (animData != NULL) {
                controllerApplyMotionWindow(gCurrentActor, animData, t->unk1C);
            }
        }
        if (t->unk28 == 0) {
            LB5->unk154 = 5;
        }
        if (LB5->unk11C->unk154 == 5) {
            LB5->unk154 = 6;
        }
        if (LB5->unk154 == 0 && (*gPlayerSlots[gCurrentPlayerIndex].unk298 & 0xE000)) {
            sfxPlayOnFreeSlot(0x25, 0x7FFF, 63.0f, 0.51f, 0, 0);
            controllerAnimSetStateIfChanged(gCurrentActor, 0x5FD, 0.0f, 1.0f);
            LB5->unk154 = 1;
        }
        break;
    }
    case 1:
    case 2:
        if (animData->unk4 > 10.0f && animData->unk4 < 14.0f) {
            LB5->unk154 = 2;
        } else {
            LB5->unk154 = 1;
        }
        if (animData->unk24 == 0.0f) {
            controllerAnimSetStateIfChanged(gCurrentActor, 0x5FC, 0.0f, 1.0f);
            LB5->unk154 = 0;
            t->unk1C = 0.0f;
        }
        break;
    case 3:
        if (gGameMode != 1) {
            LB5->unk154 = 4;
            hudSpawnCountdownTimer(0xDC, 0x2A, ((u8 *)&t->unk22)[1]);
            resQueueAttachActor(gCurrentActor, 0, 0xA);
        }
        break;
    case 4:
        if (!(LB5->unk60 & 0x2000000)) {
            LB5->unk154 = 0;
            actorSetStateTwo(LB5->unk11C);
            sfxAllocateChannel(8, 1.0f);
        }
        break;
    case 5:
    case 6:
        if (LB5->unk154 == 6) {
            bonusEndLose(0, 1);
        } else {
            bonusEndWin(0, 0);
        }
        camStartPath(0, 1, 0x11);
        LB5->unk154 = 7;
        break;
    }
    {
        f32 d;

        fs0 = t->unk8 * 0.85;
        fs1 = t->unkC - 40.0;
        d = sqrtf(fs0 * fs0 + fs1 * fs1);

        if (d > 80.0f) {
            diffDelta = 80.0f / d;
            d = 0.0f;  // FAKE: kills uopt store-forwarding of the 80/d value so it stays in stack slot
            t->unk8 = (fs0 * diffDelta) / 0.85;
            t->unkC = (fs1 * diffDelta) + 40.0;
        }
    }
    LB5->unk7C = mathSinF(t->unk18) * 5.0 + (t->unk0 + t->unk8 * 0.8);
    LB5->unk84 = 2.0 * mathCosF((s16)(t->unk18 * 2)) + (t->unk4 + t->unkC * 0.9);
    gPrimaryPlayerActor->x = t->unk0 + t->unk8 * 0.5f;
    gPrimaryPlayerActor->y = LB5->unk80;
    gPrimaryPlayerActor->z = t->unk4 + t->unkC * 0.5f;
    renderCallbacksRegister(func_80029B9C, gCurrentActor, 3);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct {
    char pad0[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} BonusDModel;

typedef struct {
    Actor *unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    s16 unkE;
} BonusDB920Link;

typedef struct {
    f32 unk0;
    f32 unk4;
    char pad8[0x10];
    s16 unk18;
    char pad1A[0x10];
    s16 unk2A;
    s8 unk2C;
    s8 unk2D[2];
} BonusDB920Tgt;

void bonusBigBugBashFlyUpdate(void) {
    BonusDB920Link *flyExt = gCurrentActor->customState;
    Actor *targetActor = flyExt->unk0;
    BonusDB920Tgt *targetExt = targetActor->customState;
    f32 flySpeed;
    f32 wanderRadius;
    f32 dx;

    if (!(gCurrentActor->flags & 0x10)) {
        actorScriptStart(gCurrentActor, 0x32F);
        gCurrentActor->sub4->scaleX = 0.06f;
        gCurrentActor->sub4->scaleY = 0.06f;
        gCurrentActor->sub4->scaleZ = 0.06f;
        sfxPlayActorSound(gCurrentActor, 0x10E, 0x3C, 1, 0, 0xFF, 1.0f, 0);
    }
    if (gCurrentActor->state == 0) {
        if (targetExt->unk2C == 0) {
            if (flyExt->unkC > 0) {
                if (flyExt->unkC == 0x28) {
                    sfxPlayFromActorDirect(gCurrentActor, 0x801, 0xFF, 3.0f, 2, 0);
                }
                flyExt->unkC--;
                flySpeed = 5.0f;
            } else {
                flySpeed = 3.0f;
            }
            gCurrentActor->yaw -= mathAngleSignedDistance(mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, flyExt->unk4, flyExt->unk8) + 0x800, gCurrentActor->yaw) >> 3;
            gCurrentActor->x += mathSinF(gCurrentActor->yaw) * flySpeed;
            gCurrentActor->z += mathCosF(gCurrentActor->yaw) * flySpeed;
            flyExt->unkE--;
            if (flyExt->unkE <= 0) {
                s16 angle;

                if (flyExt->unkC > 0) {
                    flyExt->unkE = (randomLcgNext() & 7) + 0xA;
                } else {
                    flyExt->unkE = (randomLcgNext() & 0x3F) + 0xF;
                }
                angle = mathAngleBetweenPoints2D(targetExt->unk0, targetExt->unk4, flyExt->unk4, flyExt->unk8);
                angle += ((randomLcgNext() & 7) << 8) + 0x400;
                wanderRadius = randomFloat() * 70.0;
                flyExt->unk4 = mathSinF(angle) * wanderRadius + targetExt->unk0;
                flyExt->unk8 = mathCosF(angle) * wanderRadius + targetExt->unk4;
            }
        } else {
            if (targetExt->unk2C == 0x28) {
                sfxPlayFromActorDirect(gCurrentActor, 0x801, 0xFF, 3.0f, 2, 0);
            }
            gCurrentActor->y = mathSinF(targetExt->unk18) * 5.0 + (targetActor->y - 30.0);
        }
    } else {
        gCurrentActor->alpha -= 4;
        if (gCurrentActor->alpha < 5) {
            gCurrentActor->alpha = 0;
            actorDespawn(gCurrentActor);
        }
    }
    if (targetActor->state == 2) {
        f32 dz;
        dx = mathSinF(targetActor->yaw) * 65.0f + targetActor->x;
        dz = mathCosF(targetActor->yaw) * 65.0f + targetActor->z;
        dx -= gCurrentActor->x;
        dz -= gCurrentActor->z;
        if (gCurrentActor->state == 0) {
            if (dx < 12.0 && dx > -12.0 && dz < 12.0 && dz > -12.0) {
                s32 i;

                sfxStopSlotSound(gCurrentActor, 0);
                actorScriptStart(gCurrentActor, 0x331);
                if (targetExt->unk2A != 0) {
                    targetExt->unk2A--;
                }
                for (i = 0; i < 1; i++) {
                    if (targetExt->unk2D[i] == 0) {
                        targetExt->unk2D[i] = 0x1E;
                        i = 1;
                    }
                }
                gCurrentActor->state = 1;
                sfxPlayFromActorDirect(gCurrentActor, 0x16, 0xFF, 1.0f, 0x14, 0);
                gCurrentActor->alpha = 0xFF;
                gCurrentActor->flags &= ~0x8000;
            } else if (dx * dx + dz * dz < 900.0f) {
                flyExt->unkC = 0x3C;
                flyExt->unkE = 1;
            }
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct {
    char pad0[4];
    f32 unk4;
    char pad8[8];
    s16 unk10;
} BonusDBE44Anim;

typedef struct {
    BonusDBE44Anim *unk0;
    char pad4[0x30];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} BonusDBE44Model;

typedef struct {
    Actor *unk0;
} BonusDBE44Link;

void bonusBigBugBashSwatterShadowUpdate(void) {
    BonusDBE44Link *link = gCurrentActor->customState;
    Actor *targetActor = link->unk0;
    BonusDBE44Anim *selfAnim = ((BonusDBE44Model *)gCurrentActor->sub4)->unk0;
    BonusDBE44Anim *targetAnim = ((BonusDBE44Model *)targetActor->sub4)->unk0;
    s16 animId;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->roll = 0;
        gCurrentActor->yaw = 0x800;
        controllerAnimSetStateIfChanged(gCurrentActor, 0x5FB, 0, 0);
        gCurrentActor->sub4->scaleX = 0.2f;
        gCurrentActor->sub4->scaleY = 0.2f;
        gCurrentActor->sub4->scaleZ = 0.2f;
    }
    gCurrentActor->x = targetActor->x;
    gCurrentActor->y = targetActor->y - 35.0;
    gCurrentActor->z = targetActor->z;
    if (selfAnim != NULL) {
        if (targetAnim != NULL) {
            animId = targetAnim->unk10;
            if (animId == 0x5FD) {
                animId = 0x5FE;
            }
            if (animId != selfAnim->unk10) {
                controllerAnimSetStateIfChanged(gCurrentActor, animId, 0, 0);
            }
            controllerApplyMotionWindow(gCurrentActor, selfAnim, targetAnim->unk4);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u8 pad25;
    s16 unk26;
    s16 unk28;
    s8 unk2A[1];
} LargeB4Sub;

typedef struct {
    Actor *unk0;
    s16 unk4;
    char pad6[2];
    f32 unk8;
    s16 unkC;
} LargeB4Spawn;


void bonusSearchlightSeekGameUpdate(void) {
    f32 cosAngle;
    f32 sinAngle;
    f32 targetOffsetZ;
    f32 scale;
    f32 targetOffsetX;
    f32 velX;
    f32 stickY;
    LargeB4Sub *subExt = gCurrentActor->customState;
    LargeB4Spawn *spawnExt;
    s32 i;
    s32 pad;
    s16 spawnAngle;
    if (!(gCurrentActor->flags & 0x10)) {
        gPrimaryPlayerActor->state = 0x77;
        gPrimaryPlayerActor->unk155 = 0;
        gPrimaryPlayerActor->unk144 = 1;
        subExt->unk0 = 1.0f;
        subExt->unk4 = gCurrentActor->x;
        subExt->unk8 = gCurrentActor->z;
        switch (gCurrentMap) {
            case 0x67:
                subExt->unk28 = 4;
                D_8002D90C = 1.0f;
                break;
            case 0x8A:
                subExt->unk28 = 6;
                D_8002D90C = 1.3f;
                break;
            case 0x8B:
                subExt->unk28 = 8;
                D_8002D90C = 1.6f;
                break;
            case 0x8C:
                subExt->unk28 = 0xA;
                D_8002D90C = 1.9f;
                break;
        }
        subExt->unk24 = 0;
        subExt->unk26 = subExt->unk28;
        subExt->unk20 = 0x3C;
        subExt->unk23 = gfxResourceCreate(1, textTableGetString(0x1A, 2, 1), 8, 0.0f, 0.0f, 0.0f);
        func_806FDAB8(subExt->unk23, 0.0f);
        gCurrentActor->sub4->scaleX = 0.33f;
        gCurrentActor->sub4->scaleY = 0.33f;
        gCurrentActor->sub4->scaleZ = 0.33f;
        camSetTarget(BCAM->unk104, gCurrentActor, 4, 0x800, 0x1A, 0, 0x1F, 0x15, 0x10, 0, 0.05f);
        camStartPath(0, 0, 1);
        gCurrentActor->state = 3;
        subExt->unk14 = 0.0;
        subExt->unk18 = 0.0;
        subExt->unkC = 0.0;
        subExt->unk10 = 0.0;
        subExt->unk0 = 1.0;
        i = 0;
        do {
            subExt->unk2A[i] = 1;
            i++;
        } while (i != 1);
    }
    for (i = 0; i < 1; i++) {
        if (subExt->unk2A[i] > 0) {
            subExt->unk2A[i] -= 1;
            if (subExt->unk2A[i] == 0 && actorSpawn(0x14B, 0x21) != 0) {
                spawnExt = (LargeB4Spawn *)gSpawnedActor->customState;
                spawnExt->unk0 = gCurrentActor;
                spawnExt->unkC = 2;
                spawnExt->unkC = (randomLcgNext() & 0x3F) + 0xF;
                spawnExt->unk4 = randomLcgNext() & 0xF;
                spawnExt->unk8 = randomFloat() * 40.0 + 15.0;
                spawnAngle = spawnExt->unk4 * 0xC8 - 0x578;
                gSpawnedActor->x = mathSinF(spawnAngle) * spawnExt->unk8 + subExt->unk4;
                gSpawnedActor->y = gCurrentActor->y;
                gSpawnedActor->z = mathCosF(spawnAngle) * spawnExt->unk8 + subExt->unk8;
            }
        }
    }
    subExt->unk1C += 0x19;
    if (gCurrentActor->state == 0 || gCurrentActor->state == 1) {
        subExt->unk0 = subExt->unk0 - 0.03333333333333333;
        if (subExt->unk0 < 0.0) {
            subExt->unk0 = 0.0;
        }
    } else {
        subExt->unk0 = subExt->unk0 + 0.03333333333333333;
        if (subExt->unk0 > 1.0) {
            subExt->unk0 = 1.0;
        }
    }
    lightSetColor(subExt->unk0, subExt->unk0, subExt->unk0, -1);
    switch (gCurrentActor->state) {
        case 0: {
            cosAngle = mathSinF(gPlayerSlots[gCurrentPlayerIndex].unk2C8);
            sinAngle = mathCosF(gPlayerSlots[gCurrentPlayerIndex].unk2C8);
            velX = subExt->unk14;
            targetOffsetZ = subExt->unk18;
            targetOffsetX = D_807ECDEC->unk2 * 0.06f;
            stickY = D_807ECDEC->unk3 * 0.06f;
            velX = ((targetOffsetX * sinAngle) - (stickY * cosAngle)) - velX;
            subExt->unk14 = subExt->unk14 + velX * 0.155f;
            subExt->unk18 = subExt->unk18 + ((targetOffsetX * cosAngle + stickY * sinAngle) - targetOffsetZ) * 0.25f;
            subExt->unkC = subExt->unkC + subExt->unk14;
            subExt->unk10 = subExt->unk10 - subExt->unk18;
            if (subExt->unk26 == 0) {
                gCurrentActor->state = 5;
            }
            if ((gCurrentActor->parentActor)->state == 5) {
                gCurrentActor->state = 6;
            }
            if (subExt->unk1E > 0) {
                subExt->unk1E = subExt->unk1E - 1;
            }
            if (subExt->unk1E <= 0 && (*gPlayerSlots[gCurrentPlayerIndex].unk298 & 0xE000)) {
                sfxPlayOnFreeSlot(0x59, 0x7FFF, 63.0f, 1.0, 0x1E, 0);
                targetOffsetZ = mathSinF(gPlayerSlots->unk2C8) * 30.0f + gPlayerSlots->unk210;
                scale = gPlayerSlots->unk214 - 25.0f;
                targetOffsetX = mathCosF(gPlayerSlots->unk2C8) * 30.0f + gPlayerSlots->unk218;
                projectileSetTargetCoords(targetOffsetZ, scale, targetOffsetX);
                projectileAimAndSpawn(0x23, 1, 0.8f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 625.0f, gCurrentActor);
                subExt->unk1E = 0x1E;
            }
            break;
        }
        case 3:
            if (gGameMode != 1) {
                gCurrentActor->state = 4;
                hudSpawnCountdownTimer(0xDC, 0x2A, (u8)subExt->unk20);
                resQueueAttachActor(gCurrentActor, 0, 0xC);
            }
            break;
        case 4:
            if (!(gCurrentActor->flags & 0x02000000)) {
                gCurrentActor->state = 0;
                actorSetStateTwo((void *)gCurrentActor->parentActor);
                sfxAllocateChannel(8, 1.0);
            }
            break;
        case 5:
        case 6:
            if (gCurrentActor->state == 6) {
                bonusEndLose(0, 1);
            } else {
                bonusEndWin(0, 0);
            }
            camStartPath(0, 1, 0x11);
            gCurrentActor->state = 7;
            break;
    }
    targetOffsetZ = subExt->unkC;
    targetOffsetX = subExt->unk10;
    sinAngle = sqrtf(targetOffsetZ * targetOffsetZ + targetOffsetX * targetOffsetX);
    if (sinAngle > 110.0f) {
        scale = 110.0f / sinAngle;
        subExt->unkC = targetOffsetZ * scale;
        subExt->unk10 = targetOffsetX * scale;
    }
    gCurrentActor->x = mathSinF(subExt->unk1C) * 5.0 + (subExt->unk4 + subExt->unkC);
    gCurrentActor->z = mathCosF(subExt->unk1C * 2) * 2.0 + (subExt->unk8 + subExt->unk10);
    gPrimaryPlayerActor->x = subExt->unk4 + subExt->unkC * 0.5f;
    gPrimaryPlayerActor->y = gCurrentActor->y;
    gPrimaryPlayerActor->z = subExt->unk8 + subExt->unk10 * 0.5f;
    renderCallbacksRegister(func_8002CC08, gCurrentActor, 3);
    lightAdd(gCurrentActor->x, gCurrentActor->y + 25.0, gCurrentActor->z, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 25.0f, 1, 0xFF, 0xFF, 0xFF);
}


typedef struct {
    char pad0[4];
    f32 unk4;
    f32 unk8;
    char padC[0x1C];
    s16 unk28;
    s8 unk2A[2];
} BonusDC8ECTgt;

typedef struct {
    Actor *unk0;
    s16 unk4;
    char pad6[2];
    f32 unk8;
    s16 unkC;
} BonusDC8ECLink;

void bonusSearchlightSeekTargetUpdate(void) {
    s32 e1, e2, e3;
    f32 speed;
    s32 d1, d2, d3;
    f32 targetX, targetZ;
    s16 angle;
    s32 i;
    Actor *targetOwner;
    BonusDC8ECLink *spawnLink = gCurrentActor->customState;
    BonusDC8ECTgt *targetExt;

    targetOwner = spawnLink->unk0;
    targetExt = targetOwner->customState;

    if (!(gCurrentActor->flags & 0x10)) {
        actorScriptStart(gCurrentActor, 0x232);
        gCurrentActor->unk144 = 0x24;
        gCurrentActor->sub4->scaleX = 0.25f;
        gCurrentActor->sub4->scaleY = 0.25f;
        gCurrentActor->sub4->scaleZ = 0.25f;
    }
    if (gCurrentActor->state == 0) {
        speed = D_8002D90C;
        angle = spawnLink->unk4 * 0xC8 - 0x578;
        targetX = mathSinF(angle) * spawnLink->unk8 + targetExt->unk4;
        targetZ = mathCosF(angle) * spawnLink->unk8 + targetExt->unk8;
        gCurrentActor->yaw -= mathAngleSignedDistance(mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, targetX, targetZ) + 0x800, gCurrentActor->yaw) >> 5;
        gCurrentActor->x += mathSinF(gCurrentActor->yaw) * speed;
        gCurrentActor->z += mathCosF(gCurrentActor->yaw) * speed;
        spawnLink->unkC--;
        if (spawnLink->unkC <= 0) {
            spawnLink->unkC = (randomLcgNext() & 0x3F) + 0xF;
            spawnLink->unk4 += (randomLcgNext() & 0xF) + 3;
            spawnLink->unk8 = 40.0 * randomFloat() + 10.0;
        }
        if (D_807FBB85 == 1) {
            gCurrentActor->alpha = 0xFF;
            gCurrentActor->flags &= ~0x8000;
            actorScriptStart(gCurrentActor, 0x332);
            gCurrentActor->state = 1;
            sfxPlayOnFreeSlot(0x16, 0x7FFF, 63.0f, 1.0f, 0, 0);
            i = 0;
            if (targetExt->unk28 != 0) {
                targetExt->unk28--;
            }
            for (; i < 1; i++) {
                if (targetExt->unk2A[i] == 0) {
                    targetExt->unk2A[i] = 0x1E;
                    i = 1;
                }
            }
        }
    } else {
        gCurrentActor->alpha -= 4;
        if (gCurrentActor->alpha < 5) {
            gCurrentActor->alpha = 0;
            actorDespawn(gCurrentActor);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

Gfx *func_8002CC08(Gfx *gdl, Actor *actor) {
    Struct_CC08_174 *subExt;
    f32 projX;
    f32 projY;
    s32 state;
    s16 screenX;
    s16 screenY;

    subExt = (Struct_CC08_174 *)actor->customState;
    camProjectToScreen(actor->x, actor->y, actor->z, &projX, &projY, 0, 1.0f, gCurrentPlayerIndex);
    screenX = (f32)(projX * 4.0);
    screenY = (f32)(projY * 4.0);
    gDPPipeSync(gdl++);
    gDPSetCombineMode(gdl++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPDisplayList(gdl++, D_1000118);
    gSPMatrix(gdl++, D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    state = actor->state;
    if (state == 0 || state == 1) {
        gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, screenX - 0x34, screenY - 0x34, 3.2f, 3.2f, 0xE1, 0.0f);
        gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, screenX + 0x34, screenY - 0x34, 3.2f, 3.2f, 0x13B, 0.0f);
        gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, screenX + 0x34, screenY + 0x34, 3.2f, 3.2f, 0x2D, 0.0f);
        gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, screenX - 0x34, screenY + 0x34, 3.2f, 3.2f, 0x87, 0.0f);
    }
    gSPMatrix(gdl++, D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    switch (actor->state) {
    case 7:
        do {
        } while (0); // FAKE: empty do/while(0) steers branch codegen
        break;
    case 0:
    case 1:
        gdl = hudDrawRollingCounter(textDrawAnimated(gdl, subExt->unk23, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, &subExt->unk26, subExt->unk28, &subExt->unk24);
        break;
    }
    return gdl;
}
