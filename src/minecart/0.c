#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/112080.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/126260.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17800.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/5E2F0.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/936B0.h"
#include "proto/global/9DD70.h"
#include "proto/global/A7710.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"
#include "proto/global/FCCD0.h"
#include "proto/minecart/0.h"





// A track point is a TargetVec3f (mathPickCloserTargetPoint3D's point type).
typedef TargetVec3f MinecartTrackPoint;

typedef struct MinecartCart {
    s16 jumpHeight;
    s16 maxAngleDelta;
    Actor *rider;
    u8 unk8;
    char pad9[3];
    MinecartTrackPoint *prevPoint;
    s16 pointIndex;
    char pad12[2];
    f32 tilt;
    f32 tiltTarget;
    f32 tiltReturnRate;
    f32 tiltRate;
    f32 tiltAccel;
    f32 tiltRateMax;
    f32 junctionBlend;
    u8 *route;
    u8 *routeCursor;
    char pad38[1];
    u8 peakTilt;
    char pad3A[4];
    u8 targetSpeed;
    u8 laneOffset;
    u8 junctionOffset;
    u8 junctionPoint;
    u8 branchSide;
} MinecartCart;

extern PlayerStruct *gPlayerSlots;
extern s16 D_80750AC4;
extern s32 gCurrentMap;



extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;


void minecartTriggerLoss(u8 useCutsceneCam, u8 textIndex) {
    sfxPlayOnFreeSlot(0x143, 0x7FFF, 63.0f, 1.0f, 0, 0);
    textSpawnMarkerChecked(0x81, 0, 0x78, textTableGetString(0x1A, textIndex, 1), 0, 0x28, 8, 8);
    gCurrentActor->parentActor->state = 0;
    sfxAllocateChannel(0x28, 1.0f);
    playerStateQueueCallback(0x44, 0, 0);
    gCurrentActor->state++;
    if (useCutsceneCam != 0) {
        camStartPath(gPrimaryPlayerActor, 5, 5);
    }
}

void minecartTriggerWin(u8 useCutsceneCam, u8 textIndex) {
    u8 *text = textTableGetString(0x1A, textIndex, 1);
    textSpawnMarkerChecked(0x81, 0, 0x78, text, 0, 0x28, 8, 8);
    gCurrentActor->parentActor->state = 0;
    sfxAllocateChannel(0x2A, 1.0f);
    playerStateQueueCallback(0x43, 0, 0);
    gCurrentActor->state++;
    if (useCutsceneCam != 0) {
        camStartPath(gPrimaryPlayerActor, 5, 5);
    }
}

extern void *D_80028C30;
extern u8 D_8072006C[];


void minecartSpawnWheelEffect(MinecartCart *cart, u8 side, u8 probabilityThreshold) {
    if ((randomLcgNext() & 0xFF) >= probabilityThreshold) {
        if (cart->jumpHeight == 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x8A, 0x96, 0x7F, 0x32);
            effectSetSpeed((s32)gCurrentActor);
            effectSetCallback(effectTimedLightIntensityFade);
            D_80028C30 = effectCreateAtActorBone(D_8072006C, 0.4f, gCurrentActor, side + 7, 2);
        }
    }
}

void minecartStepSpeedToTarget(MinecartCart *cart) {
    u32 targetSpeedInt = cart->targetSpeed;
    f32 nextSpeed;
    f32 targetSpeed = targetSpeedInt;

    if (targetSpeed != gCurrentActor->speedXZ) {
        if (gCurrentActor->speedXZ < targetSpeed) {
            nextSpeed = gCurrentActor->speedXZ + 8.0f;
            if (targetSpeed < nextSpeed) {
                gCurrentActor->speedXZ = targetSpeed;
                return;
            }
            gCurrentActor->speedXZ = nextSpeed;
            return;
        }
        if (targetSpeed < gCurrentActor->speedXZ) {
            nextSpeed = gCurrentActor->speedXZ - 8.0f;
            if (nextSpeed < targetSpeed) {
                gCurrentActor->speedXZ = targetSpeed;
                return;
            }
            gCurrentActor->speedXZ = nextSpeed;
        }
    }
}

void minecartPlayerCartUpdate(u8 initTrackSegment, u8 *trackTable, s16 maxAngleDelta, u8 maxTiltLimit) {
    s32 pad94;
    PlayerState *playerState;
    MinecartCart *cart;
    s32 flags;
    s32 pad0, pad1, pad2, pad3, pad4, pad5, pad6, pad7, pad8;
    f32 nodePos[3];

    cart = gCurrentActor->customState;
    playerState = gPlayerSlots->actor->customState;
    flags = gCurrentActor->flags;
    if (!(flags & 0x10)) {
        gCurrentActor->flags = flags | 0x1400;
        if (gCurrentMap == 6 || gCurrentMap == 0x37 || gCurrentMap == 0x6A) {
            slotQueueUpdate(0xB, 1, 0);
            D_80750AC4 = 0;
        }
    }
    if (cart->rider == NULL) {
        cart->rider = gPlayerSlots->actor;
        cart->unk8 = 0;
    }
    switch (gCurrentActor->state) {
    case 0:
        if ((cart->rider->x - gCurrentActor->x) * (cart->rider->x - gCurrentActor->x) +
            (cart->rider->y - gCurrentActor->y) * (cart->rider->y - gCurrentActor->y) +
            (cart->rider->z - gCurrentActor->z) * (cart->rider->z - gCurrentActor->z) < 400.0f) {
            cart->routeCursor = trackTable;
            cart->pointIndex = initTrackSegment;
            cart->route = trackTable;
            playerStateQueueCallback(0x45, gCurrentActor, cart->unk8);
            gCurrentActor->state++;
        } else {
            actorUpdateModelMatrix(gCurrentActor, 0);
            break;
        }
    case 1:
        minecartFollowTrack(cart, maxAngleDelta, maxTiltLimit);
        camSetTargetScaled(playerState->camActor, gCurrentActor, 4, 0x800, 0x28, 0, 5, 0x19, 0x14, 0, 0.15f);
        gCurrentActor->state++;
        break;

    case 2:
        actorGetNodePos(gCurrentActor, 9, &cart->rider->x, &cart->rider->y, &cart->rider->z);
        gCurrentActor->state++;
        if (gCurrentActor->yawSpeed == 0 && gCurrentMap != 6) {
            gCurrentActor->yawSpeed = 2;
        }
        /* fallthrough */
    case 3:
    case 5:
        if (gCurrentActor->yawSpeed == 0 && camIsCutsceneActive() != 0) {
            gCurrentActor->yawSpeed = 1;
        }
        if (gCurrentActor->yawSpeed == 1 && gCurrentActor->unk155 == 0) {
            if (camIsCutsceneActive() != 0) {
                playerState->stateFlags |= 8;
            } else {
                camSetTargetScaled(playerState->camActor, gCurrentActor, 4, 0x800, 0x28, 0, 5, 0x19, 0x14, 0, 0.15f);
                playerState->stateFlags &= ~8;
                cart->targetSpeed = 0x3C;
                gCurrentActor->unk155++;
            }
        }
        actorSpawnNodeEffectFacingCamera(6, 0xFF);
        minecartStepSpeedToTarget(cart);
        minecartFollowTrack(cart, maxAngleDelta, maxTiltLimit);
        actorGetNodePos(gCurrentActor, 5, &nodePos[0], &nodePos[1], &nodePos[2]);
        commandQueuePush(gCurrentActor, nodePos[0], nodePos[1], nodePos[2], 0xFF, 0xFF, 0xFF, 0xFF, 0);
        commandQueuePush(cart->rider, nodePos[0], nodePos[1], nodePos[2], 0xFF, 0xFF, 0xFF, 0xFF, 0);
        break;

    default:
        break;
    }
}

extern PlayerState *gActivePlayerState;


void minecartUpdateHeadlight(void) {
    f32 lightAim[3];
    f32 lightPos[3];

    if (gActivePlayerState->stateFlags & 0x10000002) {
        actorGetNodePos(gCurrentActor, 2, &lightPos[0], &lightPos[1], &lightPos[2]);
        actorGetNodePos(gCurrentActor, 1, &lightAim[0], &lightAim[1], &lightAim[2]);
    } else {
        actorGetNodePos(gCurrentActor, 1, &lightPos[0], &lightPos[1], &lightPos[2]);
        actorGetNodePos(gCurrentActor, 2, &lightAim[0], &lightAim[1], &lightAim[2]);
    }
    lightSetDistanceThreshold(0xC8);
    lightSetFovAngles(20.0f, 40.0f);
    lightAdd(lightPos[0], lightPos[1], lightPos[2], lightAim[0], lightAim[1], lightAim[2], 0.0f, 1, 0xFF, 0xFF, 0xFF);
}

extern u8 D_80028C34[];
extern u8 D_80028C3C[];

void minecartUpdateHeadlightAndSpeed(void) {
    MinecartCart *cart = gCurrentActor->customState;

    if (!(gCurrentActor->flags & 0x10)) {
        cart->tiltAccel = 0.1f;
        cart->tiltRateMax = 5.0f;
    }
    minecartPlayerCartUpdate(1, (gCurrentMap == 6) ? D_80028C34 : D_80028C3C, 0x7FFF, 0x23);
    minecartUpdateHeadlight();
}

extern s16 D_807502D0;
extern f32 D_807502F8;
extern s16 D_80750338;
extern u8 D_80028C40[];

void minecartUpdatePhysics(void) {
    s32 pad0;
    s32 pad1;
    s16 prevVertPos;
    MinecartCart *cart;

    f32 scaleFactor = gCurrentActor->sub4->scaleY * 0.16666666675;
    cart = gCurrentActor->customState;
    prevVertPos = cart->jumpHeight;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->terminalSpeedY = D_807502D0;
        cart->tiltAccel = 3.0f;
        cart->tiltRateMax = 12.0f;
    }
    if (cart->pointIndex == 0x90) {
        gCurrentActor->speedXZ = 130.0f;
        gCurrentActor->accelY = D_807502F8 * 0.6;
        if (cart->jumpHeight == 0) {
            gCurrentActor->speedY = D_80750338 * 1.6;
        }
    } else {
        gCurrentActor->accelY = D_807502F8;
    }
    cart->jumpHeight += gCurrentActor->speedY * scaleFactor;
    actorApplyGravity();
    if (cart->jumpHeight < 0) {
        cart->jumpHeight = 0;
        if (prevVertPos != 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x8B, 0xFF, 0x7F, 0x1E);
        }
    }
    minecartPlayerCartUpdate(3, D_80028C40, cart->maxAngleDelta, 0x19);
    if (gPrimaryPlayerActor->chunkIndex != 0x12 && gPrimaryPlayerActor->chunkIndex != 0xB) {
        minecartUpdateHeadlight();
    }
    if (gCurrentActor->state != 0) {
        actorGetNodePos(gCurrentActor, 9, &cart->rider->x, &cart->rider->y, &cart->rider->z);
    }
}



extern s32 D_807F5FD0;
extern u8 D_80028C48[];
extern u8 D_80028C50[];

void minecartReverseTrackBehaviour(void) {
    s32 padA;
    f32 scaleFactor;
    s16 prevVertPos;
    s16 i;
    s16 j;
    s16 n;
    MinecartTrackPoint tmp;
    MinecartCart *cart;

    scaleFactor = gCurrentActor->sub4->scaleY * 0.16666666675;
    cart = gCurrentActor->customState;
    prevVertPos = cart->jumpHeight;
    if (!(gCurrentActor->flags & 0x10)) {
        actorSetUniformScale(gPrimaryPlayerActor, 0.12f);
        gCurrentActor->accelY = D_807502F8;
        gCurrentActor->terminalSpeedY = D_807502D0;
        cart->tiltAccel = 0.1f;
        cart->tiltRateMax = 5.0f;
    }
    cart->jumpHeight += gCurrentActor->speedY * scaleFactor;
    actorApplyGravity();
    if (cart->jumpHeight < 0) {
        cart->jumpHeight = 0;
        if (prevVertPos != 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x8B, 0xFF, 0x7F, 0x1E);
        }
    }
    if (gPrimaryPlayerActor->contactFlags & 0x100) {
        gPrimaryPlayerActor->contactFlags &= ~0x100;
        gCurrentActor->yawSpeed = 2;
    }
    minecartPlayerCartUpdate(1, D_80028C48, 0x7FFF, 0x23);
    minecartUpdateHeadlight();
    if (*cart->routeCursor >= 7 && camIsCutsceneActive() != 0 && gCurrentActor->state != 5) {
        gCurrentActor->speedXZ = 300.0f;
    }
    if (gCurrentActor->state == 4) {
        for (i = 0; i < D_807F5FD0; i++) {
            n = gMinecartTrackPoints[i + 1] - gMinecartTrackPoints[i];
            for (j = 0; j < n / 2; j++) {
                tmp = gMinecartTrackPoints[i][j];
                gMinecartTrackPoints[i][j] = gMinecartTrackPoints[i][n - j - 1];
                gMinecartTrackPoints[i][n - j - 1] = tmp;
            }
        }
        cart->routeCursor = D_80028C50;
        cart->pointIndex = 2;
        gCurrentActor->state = 5;
        cart->prevPoint = 0;
    }
    if (gCurrentActor->state != 0) {
        actorGetNodePos(gCurrentActor, 9, &cart->rider->x, &cart->rider->y, &cart->rider->z);
    }
}

typedef struct MinecartElem {
    u8 atPoint;
    u8 nextTrack;
    u8 startPoint;
    u8 track;
} MinecartElem;



void minecartApplyJunction(MinecartCart *cart, MinecartElem **junctionTable, u8 minTrack, u8 maxTrack) {
    u8 i = 0;
    s32 found = 0;
    u8 curTrack = *cart->routeCursor;

    for (; i < 4 && found == 0; i++) {
        if (((cart->branchSide == 1 && i < 2) || (cart->branchSide == 2 && i >= 2))) {
            MinecartElem *elem = &junctionTable[curTrack - minTrack][i];

            if (curTrack >= minTrack && curTrack <= maxTrack && cart->pointIndex == elem->atPoint) {
                heapFree(cart->route);
                found = 1;
                cart->route = heapAlloc(3);
                cart->routeCursor = cart->route;
                cart->route[0] = elem->track;
                cart->routeCursor[1] = elem->nextTrack;
                cart->routeCursor[2] = 0xFF;
                cart->junctionPoint = elem->startPoint;
                cart->pointIndex = 1;
            }
        }
    }
}

extern MinecartElem *D_80028C20[];

void minecartPlayerCartJunctionBehaviour(void) {
    MinecartCart *cart;
    PlayerState *playerState;
    f32 diff;
    f32 scale;

    cart = gCurrentActor->customState;
    playerState = gPrimaryPlayerActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        cart->route = heapAlloc(3);
        cart->route[0] = 0x10;
        cart->route[1] = 0xFF;
        cart->tiltAccel = 3.0f;
        cart->tiltRateMax = 12.0f;
        gCurrentActor->yawSpeed = 3;
        playerState->stateFlags |= 8;
        camStartPath(gCurrentActor, 0, 1);
        actorScriptStart(gCurrentActor, 0);
    }
    if (gCurrentActor->state != 5 && gCurrentActor->state != 6) {
        diff = (gPlayerSlots->camY - gCurrentActor->y) - 100.0f;
        scale = (f32)(((f64)diff / 650.0 * 0.15) + .15);
        actorSetUniformScale(gCurrentActor, scale);
        actorSetUniformScale(gPrimaryPlayerActor, scale);
    }
    if (playerState->stateFlags & 8) {
        cart->targetSpeed = 3;
    }
    if (gCurrentActor->state < 5) {
        minecartPlayerCartUpdate(0x16, cart->route, 0, 0x19);
    }
    if (camIsCutsceneActive() == 0) {
        camSetFixedView(playerState->camActor, 322.0f, 900.0f, 268.0f, 325.0f, -9000.0f, 500.0f, 0);
    }
    switch (gCurrentActor->state) {
    case 1:
    case 2:
    case 3:
        if (gCurrentActor->sub4->animId == 0x292) {
            minecartTriggerWin(1, 0x14);
            gCurrentActor->state = 5;
        } else if (gCurrentActor->parentActor != NULL && gCurrentActor->parentActor->state == 5) {
            func_80726EE0(0);
            minecartTriggerLoss(1, 0xE);
            gCurrentActor->state = 5;
            break;
        }
        minecartApplyJunction(cart, D_80028C20, 0x10, 0x13);
        actorGetNodePos(gCurrentActor, 9, &cart->rider->x, &cart->rider->y, &cart->rider->z);
        return;
    case 4:
        gCurrentActor->state = 3;
        cart->routeCursor--;
        break;
    case 5:
        actorSetUniformScale(gCurrentActor, 0.15f);
        actorSetUniformScale(gPrimaryPlayerActor, 0.225f);
        gCurrentActor->pitch = 0;
        gCurrentActor->state++;
        break;
    case 10:
        sfxAllocateChannel(0x5A, 1.0f);
        hudSpawnCountdownTimer(0x78, 0x78, (gCurrentMap == 0x4D) ? 0x1E : (gCurrentMap == 0x81) ? 0x2D : 0x3C);
        hudCountdownTimerStart(gCurrentActor->parentActor);
        playerState->stateFlags &= ~8;
        gCurrentActor->state = 3;
        break;
    }
}


void minecartRampTiltRate(MinecartCart *cart) {
    f32 maxRate = cart->tiltRateMax;
    cart->tiltRate += cart->tiltAccel;
    if (maxRate < cart->tiltRate) {
        cart->tiltRate = maxRate;
    }
}


extern struct GfSndState *D_807457E4[];
extern s16 D_80770628[];
extern f32 D_80770B68[];
void minecartFollowTrack(MinecartCart *cart, s16 angleDeltaInput, u8 maxTiltLimit) {
    u8 i;
    u8 cnt;
    s8 prevTiltSign;
    MinecartTrackPoint *targetPt;
    MinecartTrackPoint *prevPrevPt;
    f32 rearTargetPt[3];
    f32 frontTargetPt[3];
    f32 rearNodePos[3];
    f32 frontNodePos[3];
    s32 limit;
    f32 prev;
    s16 waypointAngle;
    s16 n;
    f32 diff;
    f32 predX, predY, predZ;
    f32 stepDist;
    f32 lim;
    f64 t;
    f32 mtxTilt[4][4];
    u8 i2;
    u8 cnt2;
    s16 oldYaw;
    s8 lateralShift;
    u8 trackIndex;
    s16 yawDelta;
    f32 junctionX, junctionY, junctionZ;
    MinecartTrackPoint *q;
    MinecartTrackPoint *p;

    prevPrevPt = cart->prevPoint;
    oldYaw = gCurrentActor->yaw;
    lateralShift = 0;
    trackIndex = (*cart->routeCursor + cart->laneOffset) & 0xFF3F;
    actorUpdatePrevContactFlags(gCurrentActor);
    if (cart->routeCursor != NULL && prevPrevPt == NULL) {
        gCurrentActor->unk144 = 0x24;
        targetPt = &gMinecartTrackPoints[trackIndex][cart->pointIndex++];
        gCurrentActor->x = targetPt->x;
        targetPt++;
        gCurrentActor->y = targetPt[-1].y;
        gCurrentActor->z = targetPt[-1].z;
        gCurrentActor->floorY = targetPt[-1].y;
        gCurrentActor->yaw = mathAngleBetweenPoints2D(targetPt->x, targetPt->z, gCurrentActor->x, gCurrentActor->z);
        gCurrentActor->roll = (s16)(s32)(((f64)mathAtan2(gCurrentActor->y - targetPt->y,
                                sqrtf((gCurrentActor->x - targetPt->x) * (gCurrentActor->x - targetPt->x) + (gCurrentActor->z - targetPt->z) * (gCurrentActor->z - targetPt->z))) * 2048.0) / 3.1415927410125732);
        cart->prevPoint = targetPt - 2;
        sfxPlayActorSound(gCurrentActor, 0x113, 0, 1, 0, 0xFF, 1.0f, 0);
        cart->junctionPoint = 1;
    }
    targetPt = &gMinecartTrackPoints[trackIndex][cart->pointIndex];
    if (cart->pointIndex >= 2) {
        prevPrevPt = targetPt - 2;
    }
    if (gCurrentActor->speedXZ < 0.0f && gCurrentActor->x == targetPt[-1].x && gCurrentActor->z == targetPt[-1].z && cart->pointIndex >= 2) {
        cart->pointIndex--;
        targetPt--;
    }
    actorGetNodePos(gCurrentActor, 3, &frontNodePos[0], &frontNodePos[1], &frontNodePos[2]);
    actorGetNodePos(gCurrentActor, 4, &rearNodePos[0], &rearNodePos[1], &rearNodePos[2]);
    stepDist = (f64)(gCurrentActor->sub4->scaleY * gCurrentActor->speedXZ) * 0.16666666675;
    if (gCurrentMap == 0x4D || gCurrentMap == 0x81 || gCurrentMap == 0x82) {
        stepDist *= 1.8;
    } else {
        if ((2.0 * (f64)mathSinF(gCurrentActor->roll)) + 1.0 < 0.6) {
            t = 0.6;
        } else {
            t = (2.0 * (f64)mathSinF(gCurrentActor->roll)) + 1.0;
        }
        stepDist *= 2.5 * t;
    }
    waypointAngle = mathAngleBetweenPoints2D(targetPt->x, targetPt->z, targetPt[-1].x, targetPt[-1].z);
    if (cart->jumpHeight == 0) {
        D_80770B68[D_80770628[gCurrentActor->soundSlots[0]]] = ((f64)stepDist / 15.0) + 0.7;
    } else {
        D_80770B68[D_80770628[gCurrentActor->soundSlots[0]]] = 0.0f;
    }
    if (gCurrentActor->movePitch != 0) {
        gCurrentActor->movePitch--;
        mathPickCloserTargetPoint3D(frontNodePos[0], frontNodePos[1], frontNodePos[2], targetPt, targetPt + 1, targetPt + 1, targetPt + 2, &frontTargetPt[0], &frontTargetPt[1], &frontTargetPt[2]);
        mathPickCloserTargetPoint3D(rearNodePos[0], rearNodePos[1], rearNodePos[2], targetPt - 1, targetPt, targetPt, targetPt + 1, &rearTargetPt[0], &rearTargetPt[1], &rearTargetPt[2]);
    } else {
        mathPickCloserTargetPoint3D(frontNodePos[0], frontNodePos[1], frontNodePos[2], targetPt - 1, targetPt, targetPt, targetPt + 1, &frontTargetPt[0], &frontTargetPt[1], &frontTargetPt[2]);
        mathPickCloserTargetPoint3D(rearNodePos[0], rearNodePos[1], rearNodePos[2], prevPrevPt, prevPrevPt + 1, targetPt - 1, targetPt, &rearTargetPt[0], &rearTargetPt[1], &rearTargetPt[2]);
    }
    gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, (s16)(f32)mathAngleBetweenPoints2D(frontTargetPt[0], frontTargetPt[2], rearTargetPt[0], rearTargetPt[2]), 1.7f);
    diff = sqrtf((frontTargetPt[0] - rearTargetPt[0]) * (frontTargetPt[0] - rearTargetPt[0]) + (frontTargetPt[2] - rearTargetPt[2]) * (frontTargetPt[2] - rearTargetPt[2]));
    prev = gCurrentActor->roll;
    gCurrentActor->roll = (s16)(s32)(((f64)mathAtan2(rearTargetPt[1] - frontTargetPt[1], diff) * 2048.0) / 3.1415927410125732);
    prev = prev - (f32)gCurrentActor->roll;
    if (prev > 2048.0f) {
        prev -= 4096.0f;
    }
    if (prev <= -2048.0f) {
        prev += 4096.0f;
    }
    if (prev > 25.0f) {
        cnt = 0;
        for (i = 0; i < 0x14; i++) {
            if (D_807457E4[i] != 0) {
                cnt++;
            }
        }
        if (cnt < 5) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x20, 0xFF, 0x7F, 0x14);
        }
    }
    predX = mathSinF(waypointAngle) * stepDist + gCurrentActor->x;
    predZ = mathCosF(waypointAngle) * stepDist + gCurrentActor->z;
    predY = gCurrentActor->floorY;
    if (mathPickCloserTargetPoint3D(predX, predY, predZ, targetPt - 1, targetPt, targetPt, targetPt + 1, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z) != 0) {
        cart->pointIndex++;
    }
    gCurrentActor->y += cart->jumpHeight;
    n = gMinecartTrackPoints[trackIndex + 1] - gMinecartTrackPoints[trackIndex];
    if (D_807F5FD0 == trackIndex + 1) {
        limit = n - 1;
    } else {
        limit = n;
    }
    if (cart->pointIndex >= limit) {
        cart->routeCursor++;
        if (*cart->routeCursor == 0xFF) {
            gCurrentActor->state++;
        }
        if (gActivePlayerState->cartDamage != 0 && cart->rider == gPrimaryPlayerActor) {
            cart->laneOffset = gActivePlayerState->cartDamage;
            gActivePlayerState->cartDamage = 0;
        } else if (gCurrentMap == 0x6A) {
            gCurrentActor->movePitch = 0x1E;
            cart->junctionBlend = 0.0f;
            if (*cart->routeCursor & 0x80) {
                cart->laneOffset = (u32)cart->laneOffset >> 1;
            } else if (!(*cart->routeCursor & 0x40)) {
                cart->laneOffset = 0;
            } else {
                cart->laneOffset = cart->laneOffset << 1;
            }
            if (cart->laneOffset & 0x80) {
                cart->laneOffset = 0;
            }
        } else {
            cart->laneOffset = 0;
        }
        cart->pointIndex = cart->junctionPoint;
        cart->prevPoint = targetPt - 1;
        cart->junctionPoint = 1;
    }
    if (cart->junctionBlend != 0.0f) {
        i = (*cart->routeCursor + cart->junctionOffset) & 0x3F;
        q = &gMinecartTrackPoints[i][cart->pointIndex];
        mathPickCloserTargetPoint3D(predX, predY, predZ, q - 1, q, q, q + 1, &junctionX, &junctionY, &junctionZ);
        gCurrentActor->x += (junctionX - gCurrentActor->x) * cart->junctionBlend;
        gCurrentActor->z += (junctionZ - gCurrentActor->z) * cart->junctionBlend;
        cart->junctionBlend -= 0.06;
        if (cart->junctionBlend < 0.0f) {
            cart->junctionBlend = 0.0f;
        }
    }
    prevTiltSign = (cart->tilt > 0.0f) ? 1 : ((cart->tilt < 0.0f) ? -1 : 0);
    if (angleDeltaInput == 0x7FFF) {
        yawDelta = gCurrentActor->yaw - oldYaw;
        if (yawDelta >= 0x801) {
            yawDelta -= 0x1000;
        }
    } else {
        yawDelta = angleDeltaInput;
    }
    lim = ((f64)maxTiltLimit < (f64)((f32)(yawDelta > 0 ? yawDelta : -yawDelta) * stepDist) * 0.25) ? (f64)maxTiltLimit : (f64)((f32)(yawDelta > 0 ? yawDelta : -yawDelta) * stepDist) * 0.25;
    cart->tiltTarget = (f64)cart->tiltTarget + (f64)(lim - cart->tiltTarget) * 0.2;
    if (yawDelta >= 0x1F && yawDelta < 0x5A) {
        if (cart->tilt < lim) {
            minecartRampTiltRate(cart);
            cart->tilt += cart->tiltRate;
            if (lim < cart->tilt) {
                cart->tilt = lim;
            }
        }
    } else if (yawDelta < -0x1E && yawDelta >= -0x59) {
        if (-lim < cart->tilt) {
            minecartRampTiltRate(cart);
            cart->tilt -= cart->tiltRate;
            if (cart->tilt < -lim) {
                cart->tilt = -lim;
            }
        }
    }
    if (cart->tilt > 1.0f) {
        lateralShift = 0x20;
        minecartSpawnWheelEffect(cart, 1, 0xE6);
    } else if (cart->tilt < -1.0f) {
        lateralShift = -0x20;
        minecartSpawnWheelEffect(cart, 0, 0xE6);
    } else {
        minecartSpawnWheelEffect(cart, gFrameCounter & 1, 0xFA);
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
    if (lateralShift != 0) {
        if (cart->tiltTarget < 10.0f) {
            cart->tiltRate = 0.0f;
            if (cart->tilt > 0.0f) {
                cart->tilt -= cart->tiltReturnRate;
                if (cart->tilt < 0.0f) {
                    cart->tilt = 0.0f;
                }
            } else if (cart->tilt < 0.0f) {
                cart->tilt += cart->tiltReturnRate;
                if (cart->tilt > 0.0f) {
                    cart->tilt = 0.0f;
                }
            }
            cart->tiltReturnRate = ((f64)cart->tiltReturnRate + 0.5 < 10.0) ? (f64)cart->tiltReturnRate + 0.5 : 10.0;
        } else {
            cart->tiltReturnRate = 0.0f;
            cnt2 = 0;
            i2 = 0;
            do {
                if (D_807457E4[i2] != 0) {
                    cnt2++;
                }
                i2++;
            } while (i2 < 0x14);
            if (cnt2 < 5) {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x21, 0xFF, 0x7F, 0x14);
            }
        }
        guTranslateF(gCurrentActor->modelMtx, (f32)lateralShift, 0.0f, 0.0f);
        matrixMakeRotationZ(mtxTilt, cart->tilt);
        guMtxCatF(gCurrentActor->modelMtx, mtxTilt, gCurrentActor->modelMtx);
        guTranslateF(mtxTilt, (f32)-lateralShift, 0.0f, 0.0f);
        guMtxCatF(gCurrentActor->modelMtx, mtxTilt, gCurrentActor->modelMtx);
        actorUpdateModelMatrix(gCurrentActor, 1);
        lim = (cart->tilt > 0.0f) ? cart->tilt : -cart->tilt;
        if ((f32)cart->peakTilt < lim) {
            if (cart->tilt > 0.0f) {
                cart->peakTilt = cart->tilt;
            } else {
                cart->peakTilt = -cart->tilt;
            }
        }
    }
    if (((cart->tilt > 0.0f) ? 1 : ((cart->tilt < 0.0f) ? -1 : 0)) != prevTiltSign) {
        if (cart->peakTilt != 0 && cart->jumpHeight == 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x8B, (cart->peakTilt / maxTiltLimit) * 0x7F + 0x80, 0x7F, 0x1E);
            cart->peakTilt = 0;
        }
    }
    actorUpdateFloorContactAndTilt(gCurrentActor, 0);
}
