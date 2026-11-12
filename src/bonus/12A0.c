#include "common.h"
#include "actor.h"
#include "proto/bonus/12A0.h"
#include "proto/global/1025E0.h"
#include "proto/global/112080.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/13A7A0.h"
#include "proto/global/16550.h"
#include "proto/global/166A0.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/90D80.h"
#include "proto/global/9DD70.h"
#include "proto/global/A7710.h"
#include "proto/global/EFDC0.h"


extern Gfx D_1000118;
extern Mtx D_2000080;
extern Mtx D_2000180;

typedef struct LB3Obj {
    Actor *act[4];
    s16 spinPhase;
    s16 spinStep;
    s16 counterShown;
    s16 hitsLeft;
    u8 counterState;
    u8 hitTextId;
    u8 reelsStarted;
    u8 pad1B;
    u8 timerSeconds;
    u8 lastRoundSpeed;
    u8 firstRoundSpeed;
    u8 pad1F;
    struct EffectNode *effect;
} LB3Obj;

typedef struct LB3Player {
    u8 pad0[0x104];
    void *cam;
} LB3Player;

typedef struct BonusEObj {
    Actor *controller;
    s16 spinSpeed;
} BonusEObj;

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gPrimaryPlayerActor;

Gfx *bonusRenderReelHud(Gfx *gdl, Actor *actor) {
    LB3Obj *reelObj = actor->customState;

    gDPPipeSync(gdl++);
    gDPSetPrimColor(gdl++, 0, 0, 200, 200, 200, 255);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPDisplayList(gdl++, &D_1000118);
    gSPMatrix(gdl++, &D_2000080, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gdl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    return hudDrawRollingCounter(
        textDrawAnimated(gdl, reelObj->hitTextId, 8, 30.0f, 36.0f, 0.0f, 1.5f),
        0x26, 0x32, &reelObj->counterShown, reelObj->hitsLeft, &reelObj->counterState);
}

Actor *bonusSpawnReel(s32 type, s16 x, s16 y, s16 z) {
    if (actorSpawn(0xDB, type) != 0) {
        BonusEObj *obj = gSpawnedActor->customState;
        gSpawnedActor->x = x;
        gSpawnedActor->y = y;
        gSpawnedActor->z = z;
        obj->controller = gCurrentActor;
    }
    return gSpawnedActor;
}

extern u8 *D_8002D8B0[];

u8 bonusGetReelSymbol(LB3Obj *obj, u8 reelIndex) {
    return D_8002D8B0[reelIndex][obj->act[reelIndex]->unk15F];
}

extern void *D_8074E880[];

void bonusSpawnEffectBurst(s16 x, s16 y, s16 z, s16 count) {
    s16 i;

    for (i = 0; i < count; i++) {
        effectSetDepth(1);
        effectSetCallback(effectConfettiPhysicsUpdate);
        effectSetSpeed(1);
        effectCreateAtPosition(D_8074E880[(randomNonNegative() >> 15) % 1000 % 3], 0.3f, x, y, z);
    }
}


void bonusReelNextRound(LB3Obj *obj) {
    LB3Player *player = gPrimaryPlayerActor->customState;
    camSetTarget(player->cam, gPrimaryPlayerActor, 4, 0, 0xAA, 0, 0, 0, 0, 0, 0.09f);
    gCurrentActor->state = 3;
    gCurrentActor->unk155 = 1;
    gCurrentActor->yawSpeed = 0;
}

void bonusInitActors(LB3Obj *obj, u8 timerVal) {
    u8 i;

    for (i = 0; i < 4; i++) {
        obj->act[i]->state++;
        obj->act[i]->movePitch = timerVal;
    }
}

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/D_8002DC90.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/D_8002DC98.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/D_8002DCA0.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/D_8002DCA8.s")

extern s32 gCurrentMap;
extern Actor *gActivePlayerActor;
extern u8 gGameMode;
extern struct GfSndState *D_807457E4[];
extern u8 D_80720CF0;

void bonusReelGameUpdate(void) {
    LB3Player *player;
    LB3Obj *obj;
    u8 i;
    s32 two;

    two = 2; // FAKE: value-named constant local makes the divisor a runtime cvt.s.w
    player = gPrimaryPlayerActor->customState;
    obj = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->x = 52.0f;
        gCurrentActor->z = 18.0f;
        obj->hitTextId = gfxResourceCreate(1, "HIT", 8, 0.0f, 0.0f, 0.0f);
        func_806FDAB8(obj->hitTextId, 0.0f);
        obj->hitsLeft = 3;
        obj->counterShown = 3;
        obj->act[0] = bonusSpawnReel(0x90, -0x15, 1, 0x12);
        obj->act[1] = bonusSpawnReel(0x91, -7, 1, 0x12);
        obj->act[2] = bonusSpawnReel(0x92, 7, 1, 0x12);
        obj->act[3] = bonusSpawnReel(0x93, 0x15, 1, 0x12);
        playerStateQueueCallback(0x49, 0, 0);
        camSetTargetScaled(player->cam, gPrimaryPlayerActor, 6, 0, 0xAA, 0, 0, 0, 0, 0, 1.0f);
        camStartPath(0, 1, 1);
        switch (gCurrentMap) {
        case 0x20:
            obj->timerSeconds = 0x2D;
            obj->firstRoundSpeed = 0x20;
            obj->lastRoundSpeed = 0x20;
            break;
        case 0x79:
            obj->timerSeconds = 0x2D;
            obj->firstRoundSpeed = 0x34;
            obj->lastRoundSpeed = 0x20;
            break;
        case 0x7A:
            obj->timerSeconds = 0x28;
            obj->firstRoundSpeed = 0x34;
            obj->lastRoundSpeed = 0x2A;
            break;
        case 0x7B:
            obj->timerSeconds = 0x23;
            obj->firstRoundSpeed = 0x40;
            obj->lastRoundSpeed = 0x37;
            break;
        }
    }
    if (obj->reelsStarted != 0 && gCurrentActor->parentActor->state == 5) {
        gCurrentActor->state = 1;
        gCurrentActor->unk155 = 0;
    }
    switch (gCurrentActor->state) {
    case 0:
        switch (gCurrentActor->unk155) {
        case 0:
            if (gGameMode != 1) {
                resQueueAttachActor(gCurrentActor, 0, 3);
                gCurrentActor->unk155 += 1;
            }
            break;
        case 1:
            if (!(gCurrentActor->flags & 0x02000000)) {
                gCurrentActor->state = 3;
                gCurrentActor->unk155 = 0;
                effectEnableFade();
                effectSetMode(2);
                effectSetDuration(-1);
                obj->effect = effectCreateAtPosition(&D_80720CF0, 1.0f, 40.0f, 200.0f, 5.0f);
            }
            break;
        }
        break;
    case 3:
        switch (gCurrentActor->unk155) {
        case 0:
            hudSpawnCountdownTimer(0xDC, 0x2A, obj->timerSeconds);
            gCurrentActor->unk155 = 1;
        case 1:
            if (obj->act[3]->state == 0) {
                gCurrentActor->state = 2;
            }
            break;
        }
        break;
    case 4:
        switch (gCurrentActor->unk155) {
        case 0:
            obj->spinPhase = 0x400;
            obj->spinStep = 0x40;
            gCurrentActor->unk155 += 1;
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x179, 0xFF, 0x7F, 1);
            if (obj->reelsStarted == 0) {
                obj->reelsStarted = 1;
                actorSetStateTwo(gCurrentActor->parentActor);
                sfxAllocateChannel(8, 1.0f);
            }
            break;
        case 1:
            gCurrentActor->roll = mathSinF(obj->spinPhase) * -1024.0f + 1024.0f;
            obj->spinPhase += obj->spinStep;
            if (obj->spinPhase >= 0x800) {
                obj->spinStep = -0x40;
                bonusInitActors(obj, (u32)((f32)obj->firstRoundSpeed + (f32)(obj->lastRoundSpeed - obj->firstRoundSpeed) * ((f32)(obj->hitsLeft - 1) / two)));
                gCurrentActor->soundSlots[0] = sfxPlayOnFreeSlot(0x24D, 0x7FFF, 64.0f, 1.0f, 0, 0);
                camSetTarget(player->cam, gActivePlayerActor, 4, 0, 0x78, 0, 0, 0, 0, 0, 0.09f);
            } else if (obj->spinPhase < 0x400) {
                gCurrentActor->state = 5;
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 5:
        if (gCurrentActor->yawSpeed == 4) {
            gCurrentActor->state = 7;
            gCurrentActor->unk155 = 0;
            break;
        }
        if (gCurrentActor->unk155 != 0) {
            bonusSpawnEffectBurst(obj->act[gCurrentActor->yawSpeed]->x, obj->act[gCurrentActor->yawSpeed]->y, obj->act[gCurrentActor->yawSpeed]->z + 20.0f, 0xF);
            obj->act[gCurrentActor->yawSpeed]->state += 1;
            gCurrentActor->yawSpeed += 1;
            gCurrentActor->state = 6;
            gCurrentActor->unk155 = 0;
        }
        break;
    case 7:
        if (D_807457E4[gCurrentActor->soundSlots[0]] != 0) {
            n_alSndpStop(D_807457E4[gCurrentActor->soundSlots[0]]);
        }
    case 1:
        if (gCurrentActor->parentActor->state != 5) {
            if (bonusGetReelSymbol(obj, 0) == 0 && bonusGetReelSymbol(obj, 0) == bonusGetReelSymbol(obj, 1) && bonusGetReelSymbol(obj, 1) == bonusGetReelSymbol(obj, 2) && bonusGetReelSymbol(obj, 2) == bonusGetReelSymbol(obj, 3)) {
                func_806FDAB8(obj->hitTextId, 3.1415927f);
                obj->hitsLeft -= 1;
                if (obj->hitsLeft == 0) {
                    gPrimaryPlayerActor->unk155 = 1;
                    bonusEndWin(0, 0);
                    gCurrentActor->state = 8;
                    obj->spinPhase = 0;
                    obj->reelsStarted = 0;
                    camStartPath(0, 0, 0x11);
                } else {
                    textSpawnMarkerChecked(0, 0, 0xB4, textTableGetString(0x1A, 0xB, 1), 0, 0x28, 8, 8);
                    bonusReelNextRound(obj);
                }
            } else {
                textSpawnMarkerChecked(0, 0, 0xB4, textTableGetString(0x1A, 0xC, 1), 0, 0x28, 8, 8);
                bonusReelNextRound(obj);
            }
        } else {
            gPrimaryPlayerActor->unk155 = 2;
            bonusEndLose(0, 1);
            gCurrentActor->state = 9;
            obj->spinPhase = 0;
            obj->reelsStarted = 0;
            camStartPath(0, 0, 0x11);
        }
        break;
    case 8:
        for (i = 0; i < 4; i++) {
            if (!((obj->spinPhase - i * 8 + 0x18) % 32)) {
                bonusSpawnEffectBurst(obj->act[i]->x, obj->act[i]->y, obj->act[i]->z + 20.0f, 0xF);
            }
        }
    case 9:
        obj->spinPhase += 1;
        break;
    }
    if (gCurrentActor->state > 0 && gCurrentActor->state < 8) {
        renderCallbacksRegister(bonusRenderReelHud, gCurrentActor, 3);
    }
    if (gCurrentActor->state >= 8) {
        if (obj->effect != NULL) {
            effectFreeAndUnlink(obj->effect);
            obj->effect = NULL;
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

f32 sinApprox(f32);

void bonusReelUpdate(void) {
    BonusEObj *obj;
    s16 toNextSymbol;

    obj = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->roll = ((randomNonNegative() >> 15) % 6 * 0x3C000) / 360;
    }
    switch (gCurrentActor->state) {
    case 1:
        obj->spinSpeed = -0x18;
        gCurrentActor->state += 1;
        break;
    case 2:
        if (obj->spinSpeed < 0) {
            gCurrentActor->roll += obj->spinSpeed;
            obj->spinSpeed += 2;
        } else {
            gCurrentActor->state += 1;
            obj->spinSpeed = gCurrentActor->movePitch;
        }
        break;
    case 4:
        toNextSymbol = 0x2AB - (gCurrentActor->roll % 0x2AB);
        if (toNextSymbol < obj->spinSpeed) {
            gCurrentActor->state += 1;
            if (obj->controller->state < 8) {
                obj->controller->state = 5;
                obj->controller->unk155 = 0;
            }
            gCurrentActor->splineT = asinApprox((obj->spinSpeed - toNextSymbol) * 0.015625);
            gCurrentActor->yawSpeed = (gCurrentActor->roll + toNextSymbol) & 0xFFF;
            gCurrentActor->unk15F = gCurrentActor->yawSpeed / 0x2AB;
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x17A, 0xFF, 0x7F, 1);
        }
    case 3:
        gCurrentActor->roll += obj->spinSpeed;
        gCurrentActor->roll &= 0xFFF;
        break;
    case 5:
        if (gCurrentActor->splineT < 6.2831854820251465) {
            gCurrentActor->roll = sinApprox(gCurrentActor->splineT) * 90.0 + gCurrentActor->yawSpeed;
            gCurrentActor->splineT = gCurrentActor->splineT + 0.3;
        } else {
            gCurrentActor->roll = gCurrentActor->yawSpeed;
            gCurrentActor->state = 0;
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void bonusEndWin(u8 useCutsceneCam, u8 textIndex) {
    sfxPlayOnFreeSlot(0x143, 0x7FFF, 63.0f, 1.0f, 0, 0);
    textSpawnMarkerChecked(0x81, 0, 0x78, textTableGetString(0x1A, textIndex, 1), 0, 0x28, 8, 8);
    gCurrentActor->parentActor->state = 0;
    sfxAllocateChannel(0x28, 1.0f);
    playerStateQueueCallback(0x44, 0, 0);
    gCurrentActor->state += 1;
    if (useCutsceneCam != 0) {
        camStartPathNearWall(gPrimaryPlayerActor, 5, 0x21, 5);
    }
}

void bonusEndLose(u8 useCutsceneCam, u8 textIndex) {
    gCurrentActor->parentActor->state = 0;
    textSpawnMarkerChecked(0x81, 0, 0x78, textTableGetString(0x1A, textIndex, 1), 0, 0x28, 8, 8);
    sfxAllocateChannel(0x57, 1.0f);
    playerStateQueueCallback(0x43, 0, 0);
    gCurrentActor->state += 1;
    if (useCutsceneCam != 0) {
        camStartPathNearWall(gPrimaryPlayerActor, 5, 0x21, 5);
    }
}
