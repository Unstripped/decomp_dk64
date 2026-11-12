#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "proto/global/10130.h"
#include "proto/global/10E1D0.h"
#include "proto/global/117190.h"
#include "proto/global/1295B0.h"
#include "proto/global/131B0.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/201B0.h"
#include "proto/global/2C700.h"
#include "proto/global/2C910.h"
#include "proto/global/450.h"
#include "proto/global/55B20.h"
#include "proto/global/5650.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/90D80.h"
#include "proto/global/CEAE0.h"
#include "proto/global/E4090.h"
#include "proto/global/F56F0.h"

typedef struct CamSplineKeyPosLook {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 unk8;
    /* 0xA */ s16 unkA;
    /* 0xC */ u8 unkC;
    /* 0xD */ s8 unkD;
} CamSplineKeyPosLook; // size = 0xE

typedef struct CamSplineKeyPos {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ s8 unk7;
} CamSplineKeyPos; // size = 0x8

typedef struct CamPathPointPos {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 unk8;
    /* 0xA */ s16 unkA;
    /* 0xC */ u8 unkC;
    /* 0xD */ u8 unkD;
} CamPathPointPos;

typedef struct CamPathPointSpline {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ void *unk4;
} CamPathPointSpline;

typedef struct CamPathPoint {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ union {
        CamPathPointPos pos;
        CamPathPointSpline spline;
        s32 args[3];
    } u;
} CamPathPoint; // size = 0x14

typedef struct CamPathList {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ s16 *unk4;
    /* 0x8 */ s16 *unk8;
} CamPathList; // size = 0xC

typedef struct CamPathSeg {
    /* 0x00 */ s16 a[3];
    /* 0x06 */ s16 b[3];
    /* 0x0C */ s16 c[3];
} CamPathSeg; // size = 0x12

typedef struct CamPathHead {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ CamPathSeg *unk4;
} CamPathHead; // size = 0x8

typedef struct CamZoneEntryFull {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
} CamZoneEntryFull; // size = 0x1C

typedef struct CamPathData {
    /* 0x00 */ CamPathHead unk0[24];
    /* 0xC0 */ s16 unkC0;
    /* 0xC2 */ u8 padC2[2];
    /* 0xC4 */ CamZoneEntryFull *unkC4;
    /* 0xC8 */ s8 *unkC8;
    /* 0xCC */ s16 unkCC;
    /* 0xCE */ u8 padCE[2];
    /* 0xD0 */ CamPathList *unkD0;
    /* 0xD4 */ s16 unkD4;
    /* 0xD6 */ u8 padD6[2];
    /* 0xD8 */ CamPathPoint *unkD8;
} CamPathData;

extern u8 gGameMode;
extern u8 D_807463B8;
extern u8 gSplitScreenMode;
extern s32 gFrameCounter;
extern s32 gCurrentMap;
extern u8 gScreenRenderFlags;
extern u8 sHudDisabled;

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern s32 gGlobalOverlayFlags;
extern s32 gGlobalCutsceneFlags;
extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;

typedef struct CamCueStep {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
    /* 0x6 */ u16 unk6;
} CamCueStep; // size = 0x8

// .bss 0x807F5B10-0x807F5D30
CamPathData gCamMapPaths;
CamPathData gCamGlobalPaths;
f32 D_807F5CCC;
s16 D_807F5CD0;
s16 gCamZoneMinX;
s16 gCamZoneMinZ;
s16 gCamZoneMaxX;
s16 gCamZoneGridWidth;
s16 gCamZoneGroupCount;
u64 gCamCueStartTime;
Actor *gCamPathLookActor;
s16 gCamPathFramesLeft;
s16 gCamPathLookAhead;
u16 gCamPathStep;
u16 gCamPathNode;
u16 gCamPathFlags;
u8 D_807F5CF6;
u16 gCamPathLoopStep;
u8 gCamPathLookNode;
f32 D_807F5CFC;
f32 D_807F5D00;
s16 gCamPathStartX;
s16 gCamPathStartY;
s16 gCamPathStartZ;
s16 gCamPathStartYaw;
Actor *gCamPathActor;
Actor *gCamActor;
u8 gCamCueIndex;
f32 D_807F5D18;
f32 D_807F5D1C;
f32 D_807F5D20;
f32 D_807F5D24;
f32 D_807F5D28;
f32 D_807F5D2C;

// .data 0x807476A0-0x80747750
f32 gCamEyeBlendRate = 0.0f;
f32 gCamFocusBlendRate = 0.0f;
f32 gCamTargetDist = 0.0f;
f32 D_807476AC = 0.0f;
f32 D_807476B0 = 0.0f;
u8 D_807476B4 = 0;
s16 gCamFreezeBelowY = 0;
s16 gCamFreezeYAbove = 0;
s16 *gCamZoneGroups = NULL;
u64 gCamPathTimeDelta = 0;
u64 gCamPathLastTime = 0;
u8 gCamPathLoopCount = 0;
s16 gCamRollStart = 0;
s16 gCamRollEnd = 0;
s16 gCamRollFramesLeft = 0;
s16 gCamRollFrames = 0;
u8 gCamPathLengthRequested = 0;
s16 gCamPathFrameCount = 0;
s16 gCamPathIndex = 0;
s16 gCamPathStartIndex = 0;
CamPathData *gCamActivePaths = &gCamMapPaths;
CamPathData *gCamGlobalPathsPtr = &gCamGlobalPaths;
s16 *gCamZoneSorted = NULL;
CamCueStep gCamCueTable[9] = {
    { 0x14B4, 0xAC, 0x00 },
    { 0x20B7, 0x98, 0x00 },
    { 0x3C55, 0xAC, 0x01 },
    { 0x45CE, 0x99, 0x07 },
    { 0x4F60, 0x98, 0x08 },
    { 0x672A, 0xAB, 0x00 },
    { 0x1869F, 0x00, 0x00 },
    { 0 },
    { 0 },
};

f32 sinApprox(f32);
f32 sqrtf(f32);

#define CAM_LERP(a, b, t) ((a) + ((b) - (a)) * (t))

u8 camCueTimerIsRunning(void) {
    return gCamCueStartTime != 0;
}


void camCueTimerTick(void) {
    u64 t = OS_CYCLES_TO_USEC(osGetTime() - gCamCueStartTime) / 10000;

    if ((u32)t >= gCamCueTable[gCamCueIndex].unk0) {
        menuTransitionToMap(gCamCueTable[gCamCueIndex].unk4, gCamCueTable[gCamCueIndex].unk5);
        if (++gCamCueIndex >= 6) {
            gCamCueStartTime = 0;
        }
    }
}

void camResetPlayerViewports(s16 playerIndex) {
    gPlayerSlots[playerIndex].unk2D0 = gPlayerSlots[playerIndex].unk2C4;
    gPlayerSlots[playerIndex].unk2E9 = 0x18;
}

void camSnapToTargetHeight(Actor *cam) {
    CamState *st = cam->customState;

    cam->x = st->unk0->x;
    cam->y = st->unk0->y + 170.0f;
    cam->z = st->unk0->z;
    st->unkF3 = 7;
}

void func_8061B650(Actor *cam) {
    CamState *st = cam->customState;

    st->unkF3 = 9;
}

void camApplySway(CamState *state, f32 *posX, f32 *posY, f32 *posZ, f32 ampXZ, f32 ampY, f32 freqXZ, f32 freqY) {
    f32 pad;
    f32 sinYaw;

    sinYaw = mathSinF(state->unkB2 + 0x400);
    *posX += ampXZ * mathSinF((u32)gFrameCounter * freqXZ) * sinYaw;
    sinYaw = mathCosF(state->unkB2 + 0x400);
    *posZ += ampXZ * mathSinF((u32)gFrameCounter * freqXZ) * sinYaw;
    *posY += ampY * mathSinF((u32)gFrameCounter * freqY);
}

void camSampleFloorHeight(Actor *camActor, CamState *state, f32 sampleX, f32 sampleZ) {
    f32 floorY = 99999.0f;

    state->unkFA = 0;
    collisionCheckActorFloor(camActor, sampleX, floorY, sampleZ, &floorY);
    state->unkFA = collisionGetFloorHeight(&state->unk90);
}

void camSetSettleMode(CamState *st, u8 mode) {
    st->unkF7 = mode;
}

typedef struct CamFloorHit {
    /* 0x0 */ f32 height;
    /* 0x4 */ s16 angle;
    /* 0x6 */ u8 flags;
    /* 0x7 */ u8 unk7;
} CamFloorHit; // size = 0x8

extern u8 sCamFloorHitCount;
extern CamFloorHit sCamFloorHits[];

void camSortFloorHits(void) {
    s16 i;
    s16 j;
    CamFloorHit tmp;

    for (i = 1; i < sCamFloorHitCount; i++) {
        if (10000.0f < sCamFloorHits[i - 1].height) {
            sCamFloorHits[i - 1].flags = 0;
        }
        j = i;
        tmp = sCamFloorHits[i];
        while ((j > 0 && tmp.height < sCamFloorHits[j - 1].height) || (tmp.height == sCamFloorHits[j - 1].height && (sCamFloorHits[j - 1].flags & 1))) {
            sCamFloorHits[j] = sCamFloorHits[j - 1];
            j--;
        }
        if (j != i) {
            sCamFloorHits[j] = tmp;
        }
    }
}

#define CAM_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define CAM_MAX(a, b) (((a) < (b)) ? (b) : (a))

u8 camFloorSnap(Actor *camActor, CamState *camState, f32 targetDist, f32 *outHeight, f32 stepFactor, u8 snapMode) {
    Actor *floorActor = camState->unk0;
    f32 floorY;
    f32 ceilY;
    u8 ret;
    f32 bonus;
    u8 flags;
    u8 cnt;
    s16 i;
    s16 pad;
    s16 slopeAngle;
    f32 lim;
    s32 pad2;
    s32 pad3;
    f64 ramp;

    ret = 0;
    if (1) { // FAKE: empty block boundary delays the floorActor load (Q0502)
    }
    ceilY = -32768.0f;
    floorY = 32767.0f;
    camState->unkFA = 0;
    cnt = 0;
    if (collisionCheckActorFloor(camActor, targetDist, floorY, stepFactor, &floorY)) {
        camSortFloorHits();
        if (sCamFloorHitCount == 1 || *outHeight < sCamFloorHits[0].height) {
            flags = sCamFloorHits[0].flags;
            floorY = sCamFloorHits[0].height;
            slopeAngle = sCamFloorHits[0].angle;
            cnt = 1;
        } else {
            for (i = 0; i < sCamFloorHitCount; i++) {
                flags = sCamFloorHits[i].flags;
                if (flags & 2) {
                    if (*outHeight < sCamFloorHits[i].height || (ceilY != camState->unkC && camState->unkC < *outHeight)) {
                        ceilY = sCamFloorHits[i].height;
                        break;
                    }
                }
                if (!(flags & 4) && (flags & 1) && sCamFloorHits[i].angle >= 0x1F5) {
                    floorY = sCamFloorHits[i].height;
                    cnt++;
                    slopeAngle = sCamFloorHits[i].angle;
                }
            }
        }
        bonus = 15.0f;
        if (gCurrentMap == 0x30 && (u32)gFrameCounter > 0x3C) {
            ramp = CAM_MIN(1.0, ((u32)gFrameCounter - 0x3C) * 0.01);
            bonus += 10.0 * ramp;
        }
        if ((gGlobalOverlayFlags & 8) && !(flags & 8)) {
            lim = CAM_MAX((mathSinF(slopeAngle + 0x800) + 1.0f) * 100.0f, bonus);
        } else {
            lim = bonus;
        }
        if (camState->unk18 < lim) {
            camState->unk18 = lim;
        } else {
            camState->unk18 = camState->unk18 + (lim - camState->unk18) * 0.05;
        }
        if (*outHeight < floorY + camState->unk18) {
            ret = 1;
            if (floorY - *outHeight < 35.0 || (sCamFloorHitCount == 1 && slopeAngle >= 0x1F5 && floorY - *outHeight < 80.0)) {
                *outHeight = floorY + camState->unk18;
                camState->unkAC |= 0x800;
                ret = 2;
            } else if (!(camState->unkAC & 0x82000) && !snapMode && !(gGlobalOverlayFlags & 1) &&
                       ((floorActor->speedY < -300.0f && floorActor->state != 0x59) || floorActor->state == 0x15 || floorActor->state == 0x16)) {
                camFindClearYaw(camActor, -2.0f, camState->unkB2 + 0x800, 0);
            } else if ((gGlobalOverlayFlags & 1) || sCamFloorHitCount < 2 || (camState->unkAC & 0x80000)) {
                ret = 0;
            }
        } else {
            camState->unkAC &= ~0x800;
        }
    } else {
        if (!(gGlobalCutsceneFlags & 0x80)) {
            floorY = 32767.0f;
        }
    }
    camState->unkFA = collisionGetFloorHeight(&camState->unk90);
    if (snapMode) {
        camState->unkA = camState->unk8;
        if (ceilY != -32768.0f && floorY < ceilY) {
            camState->unk8 = ceilY - floorY;
        } else {
            camState->unk8 = 0;
        }
        if (!(gGlobalCutsceneFlags & 0x20) && camState->unkF5 == 0) {
            u8 ceilMargin;

            if (floorActor->state == 0x63) {
                ceilMargin = 0x14;
            } else {
                ceilMargin = 10;
            }
            if (camState->unk8 != 0) {
                if (floorY + camState->unk8 - ceilMargin < *outHeight) {
                    *outHeight = floorY + camState->unk8 - ceilMargin;
                }
            }
        }
        if (floorActor->state == 0x44 || floorActor->state == 0x57 || floorActor->state == 0x59) {
            camState->unkC = -32768.0f;
        } else {
            camState->unkC = ceilY;
        }
    }
    if (snapMode) {
        if (!(camState->unkAC & 0x82000)) {
            if (floorY == 32767.0f || (sCamFloorHitCount == 1 && cnt == 0)) {
                camState->unkA0 -= 10.0f;
                camState->unkB2 = floorActor->yaw;
            }
        }
    }
    return ret;
}

void camUpdatePlayerYaw(CamState *st) {
    gPlayerSlots[st->unkFB].unk2C4 = mathAngleBetweenPointsRad(gPlayerSlots[st->unkFB].camX, gPlayerSlots[st->unkFB].camZ, gPlayerSlots[st->unkFB].focusX, gPlayerSlots[st->unkFB].focusZ);
    st->unkA8 = gPlayerSlots[st->unkFB].unk2C4;
    switch (D_807463B8) {
        case 0:
            gPlayerSlots[st->unkFB].unk2C8 = st->unkA8 * 4096.0 / 6.2831855f;
            break;
        case 2:
            func_8060B55C(&gPlayerSlots[st->unkFB].unk2C8);
            break;
        case 3:
            gPlayerSlots[st->unkFB].unk2C8 = st->unkA8 * 4096.0 / 6.2831855f;
            break;
    }
    if (gPlayerSlots[st->unkFB].unk2E9 != 0) {
        gPlayerSlots[st->unkFB].unk2E9--;
    }
}

s32 camSetFlags(Actor *cam, s32 flags) {
    CamState *s = cam->customState;
    s32 v = s->unkAC | flags;
    s->unkAC = v;
    return v;
}

void camClearFlags(Actor *cam, s32 flags) {
    CamState *st = cam->customState;

    st->unkAC &= ~flags;
}

void camSetFixedView(Actor *cam, f32 eyeX, f32 eyeY, f32 eyeZ, f32 focusX, f32 focusY, f32 focusZ, u8 force) {
    CamState *s = cam->customState;

    if (gGameMode == 1 && force) {
        camEndPath(cam);
    }
    if (gGameMode != 1 || force) {
        s->unkAC |= 0x80000000;
    }
    s->unk20 = eyeX;
    s->unk24 = eyeY;
    s->unk28 = eyeZ;
    s->unk2C = focusX;
    s->unk30 = focusY;
    s->unk34 = focusZ;
}

void camApplyFixedView(Actor *cam) {
    CamState *s = cam->customState;

    gPlayerSlots[s->unkFB].camX = s->unk20;
    gPlayerSlots[s->unkFB].camY = s->unk24;
    gPlayerSlots[s->unkFB].camZ = s->unk28;
    gPlayerSlots[s->unkFB].focusX = s->unk2C;
    gPlayerSlots[s->unkFB].focusY = s->unk30;
    gPlayerSlots[s->unkFB].focusZ = s->unk34;
}

void camSetTargetFocusActor(Actor *cam, Actor *target) {
    CamState *s = cam->customState;
    s->unk44.unk4 = target;
}

void camSetTarget(Actor *camActor, Actor *targetActor, u8 mode, s16 angleY, s16 dist, s16 angleX, s16 offsetX, s16 offsetY, s16 offsetZ, s16 duration, f32 stepRatio) {
    CamState *s = camActor->customState;
    CamTargetBlock *p = &s->unk44;

    if (targetActor != NULL) {
        p->unk0 = targetActor;
        p->unk4 = targetActor;
        p->unk8 = angleY;
        p->unkA = dist;
        p->unkC = angleX;
        p->unkE = offsetX;
        p->unk10 = offsetY;
        p->unk12 = offsetZ;
        p->unk14 = duration;
        p->unk18 = stepRatio;
        if (s->unkF3 == 3) {
            func_806EAB44(gPrimaryPlayerActor, 0);
        }
        s->unkF3 = mode;
    } else {
        camReturnToFollow(camActor, s->unk0);
    }
}

void camSetTargetCutsceneUnscaled(Actor *camActor, Actor *targetActor, u8 mode, s16 angleY, s16 dist, s16 angleX, s16 offsetX, s16 offsetY, s16 offsetZ, s16 duration, f32 stepRatio) {
    f32 saved = targetActor->sub4->scaleY;

    if (gGameMode == 1) {
        camEndPath(camActor);
    }
    sHudDisabled = 0;
    gScreenRenderFlags |= 0x10;
    targetActor->sub4->scaleY = 0.15f;
    camSetTargetScaled(camActor, targetActor, mode, angleY, dist, angleX, offsetX, offsetY, offsetZ, duration, stepRatio);
    targetActor->sub4->scaleY = saved;
    gGlobalPauseFlags &= ~1;
}

void camSetTargetCutscene(Actor *camActor, Actor *targetActor, u8 mode, s16 angleY, s16 dist, s16 angleX, s16 offsetX, s16 offsetY, s16 offsetZ, s16 duration, f32 stepRatio) {
    if (gGameMode == 1) {
        camEndPath(camActor);
    }
    sHudDisabled = 0;
    gScreenRenderFlags |= 0x10;
    camSetTarget(camActor, targetActor, mode, angleY, dist, angleX, offsetX, offsetY, offsetZ, duration, stepRatio);
}

void camSetTargetScaled(Actor *camActor, Actor *targetActor, u8 mode, s16 angleY, s16 dist, s16 angleX, s16 offsetX, s16 offsetY, s16 offsetZ, s16 duration, f32 stepRatio) {
    CamState *s = camActor->customState;
    CamTargetBlock *p = &s->unk44;
    f32 scale;

    if (targetActor != NULL) {
        scale = targetActor->sub4->scaleY / 0.15;
        p->unk0 = targetActor;
        p->unk4 = targetActor;
        p->unk8 = angleY;
        p->unkA = dist * scale;
        p->unkC = angleX;
        p->unkE = offsetX * scale;
        p->unk10 = offsetY * scale;
        p->unk12 = offsetZ * scale;
        p->unk14 = duration;
        p->unk18 = stepRatio;
        if (s->unkF3 == 3) {
            func_806EAB44(gPrimaryPlayerActor, 0);
        }
        s->unkF3 = mode;
        gGlobalPauseFlags |= 0x2000;
        camResetPlayerViewports(s->unkFB);
    } else {
        camReturnToFollow(camActor, s->unk0);
    }
}

s16 camPathGetLength(s16 startPath) {
    s16 total;
    s16 path;
    s16 i;
    u8 pad;
    u8 found;
    s16 count;
    s16 saved;
    s16 first;
    s16 idx;
    f32 eyeX;
    f32 eyeY;
    f32 eyeZ;
    f32 focusX;
    f32 focusY;
    f32 focusZ;

    total = 0;
    first = 0;
    path = startPath;
    do {
        found = 0;
        count = gCamActivePaths->unkD0[path].unk0;
        for (i = 0; i < count; i++) {
            idx = gCamActivePaths->unkD0[path].unk4[i];
            switch (gCamActivePaths->unkD8[idx].unk1) {
                case 6:
                    break;
                case 0xD:
                    if ((gCamActivePaths->unkD8[idx].u.args[0] & 0xFF) == 8) {
                        path = (u32)gCamActivePaths->unkD8[idx].u.args[1] >> 16;
                        found = 1;
                    }
                    break;
                case 0xE:
                    break;
                default:
                    if (first == 0) {
                        saved = gCamPathLookActor->yawSpeed;
                        first = 1;
                        eyeX = gPlayerSlots->camX;
                        eyeY = gPlayerSlots->camY;
                        eyeZ = gPlayerSlots->camZ;
                        focusX = gPlayerSlots->focusX;
                        focusY = gPlayerSlots->focusY;
                        focusZ = gPlayerSlots->focusZ;
                        D_807F5CFC = 1.0f;
                        D_807F5D00 = 0.0f;
                        gCamPathIndex = path;
                        gCamPathStep = i;
                        camLoadPathPoint();
                        camComputeEyeFocus(gCamActor, &eyeX, &eyeY, &eyeZ, &focusX, &focusY, &focusZ, gCamPathLookActor);
                        gCamPathStep = 0;
                        gCamPathIndex = startPath;
                        gCamPathStartX = eyeX;
                        gCamPathStartY = eyeY;
                        gCamPathStartZ = eyeZ;
                        gCamPathStartYaw = mathAngleBetweenPoints2D(focusX, focusZ, eyeX, eyeZ);
                        gCamPathFlags |= 0x20;
                        gCamPathFramesLeft = 0;
                        gCamPathLookActor->yawSpeed = saved;
                    }
                    total += gCamActivePaths->unkD0[path].unk8[i];
                    break;
            }
        }
    } while (found);
    return total;
}

void camPausePath(void) {
    if (!(gCamPathFlags & 2)) {
        gCamPathFlags |= 0x40;
    } else {
        gCamPathFlags &= ~2;
    }
}

void camResumePath(void) {
    if (gCamPathFlags & 0x40) {
        gCamPathFlags &= ~0x40;
    } else {
        gCamPathFlags |= 2;
    }
}

u8 camIsPathPaused(void) {
    return (gCamPathFlags & 0x40) != 0;
}

u8 camIsCutsceneActive(void) {
    return gGameMode == 1 || (gScreenRenderFlags & 0x10) != 0;
}

u8 camIsPathFlag4Active(void) {
    return (gCamPathFlags & 4) != 0;
}

u8 camIsPlayingPath(u8 pathIndex) {
    return gGameMode == 1 && pathIndex == gCamPathStartIndex;
}

void camRestartPath(void) {
    gCamPathIndex = gCamPathStartIndex;
    gCamPathStep = 0;
    camLoadPathPoint();
}

u8 camIsFollowingActive(void) {
    CamState *s = gCamActor->customState;
    return s->unkF3 == 3 || s->unkF3 == 0xB;
}

void camRequestPathLength(void) {
    gCamPathLengthRequested = 1;
}

extern Actor *gSpawnedActor;
extern u8 D_80770DC9;
extern u8 gPlayerCharacterId[];
extern PlayerState *gActivePlayerState;

void func_80029140(s16 *);

u16 camStartPath(Actor *actor, s16 pathIndex, u8 flags) {
    u16 ret = 0;

    if (gGameMode == 1 && (gCamPathFlags & 0x80)) {
        return 0;
    }
    if ((flags & 4) && gCurrentMap != 0) {
        gCamActivePaths = &gCamGlobalPaths;
    } else {
        gCamActivePaths = &gCamMapPaths;
    }
    if (actorSpawn(0xAD, 0) != 0) {
        gCamPathActor = gSpawnedActor;
        gSpawnedActor->unk144 = 1;
    } else {
        return 0;
    }
    if (!(flags & 4)) {
        if (gGlobalOverlayFlags & 1) {
            func_80029140(&pathIndex);
        }
    }
    if (actor != NULL) {
        gCamPathLookActor = actor;
    } else {
        gCamPathLookActor = gPlayerSlots->actor;
    }
    gGameMode = 1;
    if (!(flags & 8)) {
        gScreenRenderFlags |= 0x10;
        sHudDisabled = 0;
    }
    gCamPathLastTime = osGetTime();
    gCamPathIndex = pathIndex;
    gCamPathStartIndex = pathIndex;
    gCamPathFlags = flags;
    gCamPathLookNode = 0;
    gCamPathLoopCount = 0;
    gCamRollFramesLeft = 0;
    gCamPathFramesLeft = 0;
    gCamPathStep = 0;
    gCamPathNode = 0;
    gCamPathLookAhead = 0;
    gCamPathFrameCount = 0;
    D_807F5CF6 = D_80770DC9;
    gGlobalPauseFlags |= 0x2000;
    gGlobalPauseFlags &= ~0x1001;
    gPrimaryPlayerActor->speedXZ = 0.0f;
    if (gPlayerCharacterId[0] == 7) {
        gPrimaryPlayerActor->speedY = 0.0f;
    }
    gPrimaryPlayerActor->flags |= 0x400;
    gActivePlayerState->actionTimer = 0;
    gCamActor->pitch = 0;
    currentActorClearFlag();
    if (gCamPathLengthRequested != 0) {
        ret = camPathGetLength(pathIndex);
    }
    gCamPathLengthRequested = 0;
    if (pathIndex == 0 && gCurrentMap == 0x99) {
        setRandomSeed(0x8E32B6F7);
        gCamCueStartTime = osGetTime();
        gCamCueIndex = 0;
    } else if (transitionGetState() == 0) {
        gCamCueStartTime = 0;
    }
    return ret;
}

void camGetPathStartPose(s16 *outX, s16 *outY, s16 *outZ, s16 *outYaw) {
    if (gCamPathFlags & 0x20) {
        *outX = gCamPathStartX;
        *outY = gCamPathStartY;
        *outZ = gCamPathStartZ;
        *outYaw = gCamPathStartYaw;
        gCamPathFlags &= 0xFFDF;
    }
}

void camSetPathLookAhead(s16 distance) {
    gCamPathLookAhead = distance;
}

void camSetPathLookActor(Actor *actor, s16 node) {
    if (actor != NULL) {
        gCamPathLookActor = actor;
    } else {
        gCamPathLookActor = gPlayerSlots->actor;
    }
    gCamPathLookNode = node;
}

void camClearActorRefs(void *actor) {
    CamState *cam = gCamActor->customState;

    if (actor == gCamPathLookActor) {
        camSetPathLookActor(NULL, 0);
    }
    if (actor == cam->unk4) {
        cam->unk4 = NULL;
        cam->unkAC &= ~0x10004;
    }
    if (actor == cam->unk0) {
        cam->unk0 = gPrimaryPlayerActor;
    }
}

void camNoop201B0(void) {
}

void camUpdateFollowHeight(CamState *cam) {
    Actor *actor = cam->unk0;

    if (actor->floorY != cam->unk70) {
        if (cam->unkAC & 0x100) {
            cam->unk70 = cam->unk6C = actor->y;
            gGlobalPauseFlags |= 0x2000;
        } else if (actor->state == 0x59) {
            cam->unk70 = actor->unkA8;
        } else {
            cam->unk70 = actor->floorY;
        }
    }
    switch (actor->state) {
        case 0x00:
        case 0x15:
        case 0x16:
        case 0x1E:
        case 0x20:
        case 0x22:
        case 0x2A:
        case 0x31:
        case 0x35:
        case 0x59:
        case 0x5B:
        case 0x5C:
        case 0x63:
        case 0x6E:
            cam->unk6C = cam->unkDC;
            break;
        case 0x17:
        case 0x19:
        case 0x1C:
        case 0x1D:
        case 0x29:
        case 0x3E:
        case 0x41:
        case 0x4C:
        case 0x61:
            if (cam->unk70 < cam->unk6C && actor->peakY - actor->y > 50.0f) {
                cam->unk6C = cam->unk6C + (cam->unk70 - cam->unk6C) * 0.3;
            }
            break;
        case 0x44:
        case 0x52:
        case 0x53:
        case 0x54:
            cam->unk6C = cam->unk70;
            break;
        default:
            if (cam->unk70 < cam->unk6C) {
                cam->unk6C = cam->unk6C + (cam->unk70 - cam->unk6C) * 0.3;
            }
            break;
    }
    if (cam->unk6C <= cam->unk70) {
        cam->unk6C = cam->unk6C + (cam->unk70 - cam->unk6C) * 0.8;
    }
}

extern s8 D_807FD63F[];

void camUpdateFollowTargetDistance(Actor *camActor) {
    CamState *cam = camActor->customState;
    f32 target = D_807FD63F[cam->unkFB * 0x34] * 0.5;
    s32 sel;

    if (!(cam->unkAC & 0x2000) && !(gGlobalOverlayFlags & 0x40)) {
        if (cam->unk8 != 0 && cam->unk8 < 0x9B && cam->unkEF != 0) {
            if (cam->unkA == 0 || cam->unkA >= 0x9B) {
                cam->unkF0 = cam->unkEE;
            }
            camSetZoomLevel(camActor, 1);
            cam->unkAC |= 8;
        } else if (cam->unkA != 0 && cam->unkA < 0x9B) {
            if (cam->unkEF != 0) {
                if (cam->unkF0 != 0) {
                    sel = cam->unkF0; // FAKE: s32 copy of unkF0 (codegen)
                    if (cam->unkEF != sel) {
                        camSetZoomLevel(camActor, sel);
                    }
                }
                cam->unkAC &= ~8;
            }
        }
    }
    cam->unk98 = cam->unk98 + (((target > 20.0f) ? target : ((target < -20.0f) ? target : 0.0f)) - cam->unk98) * 0.05;
    cam->unkA0 = cam->unkA0 + (cam->unkA4 - cam->unkA0) * 0.2;
    if (cam->unkAC & 0x10) {
        camActor->distToFloor = camActor->distToFloor + (300.0f - camActor->distToFloor) * 0.2;
    } else {
        camActor->distToFloor = camActor->distToFloor + (cam->unkB8 - camActor->distToFloor) * 0.2;
    }
    if (cam->unkB0 != 0 && cam->unkF3 != 2) {
        if (cam->unkB0 > 0) {
            cam->unkB2 += 0x66;
            cam->unkB0 -= 9;
            if (cam->unkB0 < 0) {
                cam->unkB0 = 0;
            }
        } else {
            cam->unkB2 -= 0x66;
            cam->unkB0 += 9;
            if (cam->unkB0 > 0) {
                cam->unkB0 = 0;
            }
        }
    } else if (cam->unkF3 == 2) {
        cam->unkB0 = 0;
        cam->unkF1 = 0;
    }
}

extern s32 gGameFrameCounter;

void camEndPath(Actor *camActor) {
    CamState *cam = camActor->customState;

    if (gGameMode == 1) {
        if (gCamPathFlags & 4) {
            gCamActivePaths = &gCamMapPaths;
        }
        sfxSetMode(0);
        gGameMode = 0;
        gScreenRenderFlags &= ~0x10;
        if (!(gCamPathFlags & 8)) {
            sHudDisabled = 0xFF;
        }
        actorDespawn(gCamPathActor);
        gGlobalPauseFlags |= 0x1000;
        cam->unkAC |= 0x40000;
        cam->unkC = -32768.0f;
        if (gCamPathFlags & 1) {
            gGlobalPauseFlags |= 0x2000;
            camResetPlayerViewports(cam->unkFB);
        }
        gPlayerSlots[cam->unkFB].fov = 45.0f;
        camActor->pitch = 0;
        D_80770DC9 = D_807F5CF6;
        gGameFrameCounter += 99999;
        timerQueuePurgeFlagged();
        gGameFrameCounter -= 99999;
        gCamPathFlags = 0;
        gCamPathTimeDelta = 0;
        gPrimaryPlayerActor->flags &= ~0x400;
    }
}

void camCalculateTargetDistanceAndAngles(CamState *cam) {
    Actor *actor = cam->unk0;
    f32 yaw;

    gCamTargetDist = sqrtf((cam->unk8C - actor->z) * (cam->unk8C - actor->z) +
                       (cam->unk84 - actor->x) * (cam->unk84 - actor->x));
    D_807476AC = sqrtf(
        (cam->unk84 - (actor->x + cam->unk94 * mathSinF(actor->yaw))) *
            (cam->unk84 - (actor->x + cam->unk94 * mathSinF(actor->yaw))) +
        (cam->unk8C - (actor->z + cam->unk94 * mathCosF(actor->yaw))) *
            (cam->unk8C - (actor->z + cam->unk94 * mathCosF(actor->yaw))));
    D_807476B0 = mathAtan2(actor->y - cam->unk88,
                               sqrtf((cam->unk0->z - cam->unk8C) * (cam->unk0->z - cam->unk8C) + // FAKE: re-reads cam->unk0 instead of actor (codegen)
                                     (actor->x - cam->unk84) * (actor->x - cam->unk84)));
    yaw = mathAtan2(cam->unk6C - cam->unk88,
                        sqrtf((actor->z - cam->unk8C) * (actor->z - cam->unk8C) +
                              (actor->x - cam->unk84) * (actor->x - cam->unk84)));
    if (D_807476B0 > 3.1415927f) {
        D_807476B0 -= 3.1415927f;
    } else {
        D_807476B0 += 3.1415927f;
    }
    if (yaw > 3.1415927f) {
        yaw -= 3.1415927f;
    } else {
        yaw += 3.1415927f;
    }
    D_807476B0 -= yaw;
}

void camLoadPathPoint(void) {
    gCamPathActor->yawSpeed = 0;
    gCamPathActor->splineT = 0.0;
    gCamPathNode = gCamActivePaths->unkD0[gCamPathIndex].unk4[gCamPathStep];
    gCamPathFramesLeft = gCamActivePaths->unkD0[gCamPathIndex].unk8[gCamPathStep];
    playerWaypointSnapInput();
}

void camSetPath(u8 pathIndex) {
    gCamPathIndex = pathIndex;
    gCamPathStep = 0;
    camLoadPathPoint();
}

extern u8 D_8076AEE0;
extern f32 gScreenFadeRate;

void camLoopPathStep(u8 loopStep, u8 loopCount) {
    if (gCamPathLoopCount != 0) {
        gCamPathLoopCount--;
        if (gCamPathLoopCount != 0) {
            gCamPathStep = gCamPathLoopStep;
            camLoadPathPoint();
        }
    } else {
        gCamPathLoopCount = loopCount;
        gCamPathLoopStep = loopStep;
        gCamPathStep = loopStep;
        camLoadPathPoint();
    }
}

void screenFadeOutCompleteCallback(s32 unused0, s32 unused1, s32 unused2) {
    D_8076AEE0 = 0;
    gScreenFadeRate = -0.8f;
}

void screenFadeInStartCallback(s32 unused0, s32 unused1, s32 unused2) {
    gScreenRenderFlags |= 0x40;
    D_8076AEE0 = 0;
    gScreenFadeRate = 0.8f;
    timerQueueAdd(screenFadeOutCompleteCallback, 0x8000003C, 0, 0, 0);
}

void camResumePathCallback(s32 unused0, s32 unused1, s32 unused2) {
    camResumePath();
}

void camSetRollBlend(s16 startDeg, s16 endDeg, u16 frames) {
    gCamRollFramesLeft = frames;
    gCamRollFrames = frames;
    gCamRollStart = startDeg * 4096 / 360;
    gCamRollEnd = endDeg * 4096 / 360;
}

void camSnapBehindTarget(Actor *camActor) {
    CamState *cam = camActor->customState;

    camFindClearYaw(camActor, -1.0f, cam->unk0->yaw, 0);
    cam->unkF5 = 0xF;
    cam->unkF6 = 0xF;
    gGlobalPauseFlags &= ~0x2000;
    cam->unkAC &= ~0x100000;
}

extern u32 gFrameDelta;

f32 cosApprox(f32);

#define CAM_PATH_NODE (gCamActivePaths->unkD8[gCamPathNode])
#define CAM_PATH_STEP_LIST (gCamActivePaths->unkD0[gCamPathIndex])

void camUpdate(Actor *camActor, f32 *eyeX, f32 *eyeY, f32 *eyeZ, f32 *focusX, f32 *focusY, f32 *focusZ, f32 *upX,
                   f32 *upY, f32 *upZ) {
    CamState *st = camActor->customState;
    s32 done;
    s32 *args;
    u16 stepArg;
    Actor *target = st->unk0;
    f32 len;
    u64 now;
    f32 yaw;
    f32 pitch;
    f32 cosPitch;

    D_807F5CD0 = target->waterY - target->floorY;
    st->unk9E = mathAngleEaseToward(st->unk9E, target->yaw, 4.0f);
    if ((target->flags & 0x200) && !(st->unkAC & 0x100)) {
        actorGetNodePos(target, 8, &st->unkD8, &st->unkDC, &st->unkE0);
    } else {
        st->unkD8 = target->x;
        st->unkDC = target->y;
        st->unkE0 = target->z;
    }
    len = sqrtf((target->z - st->unkD4) * (target->z - st->unkD4) +
                ((target->x - st->unkCC) * (target->x - st->unkCC) + (target->y - st->unkD0) * (target->y - st->unkD0)));
    st->unk10 = (len * 40.0f) * (gFrameDelta * 0.5);
    if (st->unkF1 != 0) {
        st->unkF1--;
    }
    if (st->unkF5 != 0) {
        st->unkF5--;
    }
    if (st->unkF6 != 0) {
        st->unkF6--;
    }
    if (st->unkF7 != 0) {
        st->unkF7--;
    }
    camUpdateFollowHeight(st);
    camUpdateFollowTargetDistance(camActor);
    camActor->roll = mathAngleEaseToward(camActor->roll, target->roll, 20.0f);
    camUpdatePlayerYaw(st);
    switch (gGameMode) {
    case 0:
        if (!(st->unkAC & 0x100)) {
            if (0.0f < gScreenFadeRate) {
                if (func_807142D8() == 0) {
                    return;
                }
            }
            if (st->unkF3 == 9) {
                return;
            }
            if (target->state == 0x54 && target->unk155 < 3) {
                return;
            }
            if (target->state == 0x52 && target->unk155 < 8) {
                return;
            }
            if (target->state == 0x53 && target->unk155 < 3) {
                return;
            }
            if (target->state == 0x42) {
                if (gActivePlayerState->hitActorType != 0x11 && gActivePlayerState->hitActorType != 0x60 &&
                    gActivePlayerState->hitActorType != 0x49) {
                    return;
                }
            }
            if (target->state == 0x43) {
                return;
            }
        }
        camCalculateTargetDistanceAndAngles(st);
        if (st->unkAC & 0x80000000) {
            camApplyFixedView(camActor);
        } else {
            camComputeEyeFocus(camActor, &camActor->x, &camActor->y, &camActor->z, &st->unk78, &st->unk7C,
                          &st->unk80, target);
            if ((gGlobalPauseFlags & 0x2000) || (st->unkAC & 0x100000)) {
                if (st->unkAC & 0x100000) {
                    st->unkAC &= ~0x100000;
                    st->unk84 = *eyeX = camActor->x = st->unk38;
                    st->unk88 = *eyeY = camActor->y = st->unk3C;
                    st->unk8C = *eyeZ = camActor->z = st->unk40;
                    sfxStartAreaAmbient();
                } else {
                    st->unk84 = *eyeX = camActor->x;
                    st->unk88 = *eyeY = camActor->y;
                    st->unk8C = *eyeZ = camActor->z;
                }
                *focusX = st->unk78;
                *focusY = st->unk7C;
                *focusZ = st->unk80;
                gGlobalPauseFlags ^= 0x2000;
            } else {
                camUpdateFollow(camActor, eyeX, eyeY, eyeZ, focusX, focusY, focusZ);
            }
        }
        break;
    case 1:
        now = osGetTime();
        gCamPathTimeDelta = now - gCamPathLastTime;
        gCamPathLastTime = now;
        if (camCueTimerIsRunning() != 0) {
            camCueTimerTick();
        }
        camSampleFloorHeight(camActor, st, *eyeX, *eyeZ);
        if (gCamPathFlags & 0x40) {
            camApplySway(st, eyeX, eyeY, eyeZ, 0.2f, 0.1f, 50.0f, 40.0f);
        } else {
            if (gCamRollFramesLeft != 0) {
                gCamRollFramesLeft--;
                len = (f32)gCamRollFramesLeft / (f32)gCamRollFrames;
                camActor->pitch = gCamRollEnd + (gCamRollStart - gCamRollEnd) * len;
            }
            gCamPathFrameCount++;
            do {
                done = 0;
                if (gCamPathFramesLeft == 0) {
                    camLoadPathPoint();
                    gCamPathStep++;
                    if (CAM_PATH_STEP_LIST.unk0 < gCamPathStep) {
                        if (gCamPathFlags & 0x10) {
                            if (!(gPrimaryPlayerActor->contactFlags & 0x100)) {
                                gPrimaryPlayerActor->contactFlags |= 0x100;
                            }
                        } else {
                            camEndPath(camActor);
                        }
                    } else {
                        stepArg = CAM_PATH_STEP_LIST.unk8[gCamPathStep - 1];
                        args = &CAM_PATH_NODE.u.args[0];
                        switch (CAM_PATH_NODE.unk1) {
                            case 10:
                            case 15:
                            case 16:
                            case 17:
                                gGlobalPauseFlags |= 0x2000;
                                break;
                            case 12:
                                sfxAllocateChannel(*(u16 *)args, 1.0f);
                                if (gCamPathFramesLeft == 0) {
                                    camLoadPathPoint();
                                    gCamPathFramesLeft = 0;
                                    done = 1;
                                }
                                break;
                            case 11:
                                if (gCamPathFlags & 4) {
                                    gCamActivePaths = &gCamMapPaths;
                                }
                                camEndPath(camActor);
                                st->unkAC &= ~0x40000;
                                if (st->unkF3 != 0xB && st->unkF3 != 3) {
                                    st->unk6C = st->unk70 = gPrimaryPlayerActor->y;
                                    len = sqrtf((*eyeX - gPrimaryPlayerActor->x) * (*eyeX - gPrimaryPlayerActor->x) +
                                                (*eyeZ - gPrimaryPlayerActor->z) * (*eyeZ - gPrimaryPlayerActor->z));
                                    st->unkA4 = st->unkA0 = len;
                                    st->unkB2 = mathAngleBetweenPoints2D(gPrimaryPlayerActor->x, gPrimaryPlayerActor->z, *eyeX, *eyeZ);
                                    camActor->distToFloor = st->unkB8 = *eyeY - gPrimaryPlayerActor->y;
                                    st->unk84 = *eyeX;
                                    st->unk88 = *eyeY;
                                    st->unk8C = *eyeZ;
                                    *focusX = *eyeX + (*focusX - *eyeX) * 0.1;
                                    *focusY = *eyeY + (*focusY - *eyeY) * 0.1;
                                    *focusZ = *eyeZ + (*focusZ - *eyeZ) * 0.1;
                                    st->unk78 = *focusX;
                                    st->unk7C = *focusY;
                                    st->unk80 = *focusZ;
                                    if (gGlobalOverlayFlags & 1) {
                                        camSetZoomLevel(camActor, 2);
                                    } else {
                                        camSetZoomForDistance(camActor, (s16)st->unkA0);
                                    }
                                    st->unk94 = st->unkA0 / 3.0;
                                    camStartBlendRamp(st, 0x1E);
                                    st->unkF3 = 1;
                                    gGlobalPauseFlags &= ~0x2000;
                                    camCalculateTargetDistanceAndAngles(st);
                                }
                                break;
                            case 14:
                                timerQueueAdd(screenFadeInStartCallback, stepArg + 0x80000000, 0, 0, 0);
                                camLoadPathPoint();
                                gCamPathFramesLeft = 0;
                                done = 1;
                                break;
                            case 13:
                                if (stepArg != 0) {
                                    timerQueueAdd(camPathCommandDispatch, stepArg + 0x80000000, args[0], args[1], args[2]);
                                } else {
                                    camPathCommandDispatch(args[0], args[1], args[2]);
                                }
                                camLoadPathPoint();
                                gCamPathFramesLeft = 0;
                                done = 1;
                                break;
                            case 6:
                                gCamPathLookAhead = stepArg;
                                camLoadPathPoint();
                                gCamPathFramesLeft = 0;
                                done = 1;
                                break;
                        }
                    }
                }
            } while (done != 0);
            if (gGameMode != 0) {
                D_807F5CFC = CAM_PATH_STEP_LIST.unk8[gCamPathStep - 1];
                if (D_807F5CFC != 1.0f) {
                    D_807F5D00 = (f32)(gCamPathFramesLeft - 1) / (D_807F5CFC - 1.0f);
                } else {
                    D_807F5D00 = 0.0f;
                }
                if (gCamPathFramesLeft > 0) {
                    gCamPathFramesLeft--;
                }
                switch (CAM_PATH_NODE.unk1) {
                    case 4:
                    case 5:
                        gCamPathActor->x = gCamPathLookActor->x;
                        gCamPathActor->y = gCamPathLookActor->y;
                        gCamPathActor->z = gCamPathLookActor->z;
                        if (gCamPathLookActor->eyeHeight >= 0x15) {
                            gCamPathActor->eyeHeight = 0x14;
                        } else {
                            gCamPathActor->eyeHeight = gCamPathLookActor->eyeHeight;
                        }
                        gCamPathActor->yaw = gCamPathLookActor->yaw;
                        camComputeEyeFocus(camActor, eyeX, eyeY, eyeZ, &st->unk78, &st->unk7C, &st->unk80,
                                      gCamPathActor);
                        *focusX = st->unk78;
                        *focusY = st->unk7C;
                        *focusZ = st->unk80;
                        break;
                    case 8:
                    case 12:
                        break;
                    default:
                        gCamFocusBlendRate = 0.3f;
                        camComputeEyeFocus(camActor, eyeX, eyeY, eyeZ, &st->unk78, &st->unk7C, &st->unk80,
                                      gCamPathLookActor);
                        if (CAM_PATH_NODE.unk1 != 7 && CAM_PATH_NODE.unk1 != 0xF && CAM_PATH_NODE.unk1 != 0x11) {
                            camUpdateFocusPos(camActor, (0.0f != gCamPathLookActor->distToFloor) ? 0.3 : 0.1, focusX, focusY, focusZ);
                        }
                        if ((gGlobalPauseFlags & 0x2000) || CAM_PATH_NODE.unk1 == 7 || CAM_PATH_NODE.unk1 == 0xF ||
                            CAM_PATH_NODE.unk1 == 0x11) {
                            gGlobalPauseFlags &= ~0x2000;
                            *focusX = st->unk78;
                            *focusY = st->unk7C;
                            *focusZ = st->unk80;
                        }
                        break;
                }
                if (st->unkF2 != 0) {
                    camApplyShake(st, eyeX, eyeY, eyeZ, st->unkC0, 0);
                }
            }
        }
    }
    st->unkAC &= 0x7FFDAF0F;
    if (gGlobalOverlayFlags & 0x8000) {
        st->unkAC |= 4;
    } else if (!(st->unkAC & 0x10000)) {
        st->unkAC &= ~4;
    }
    if (st->unkF2 != 0) {
        camApplyShake(st, focusX, focusY, focusZ, (s32)(st->unkC0 * 0.333), 1);
    }
    if (!(st->unkAC & 0x100)) {
        camPolarFromPoints(&yaw, &pitch, *focusX, *focusY, *focusZ, *eyeX, *eyeY, *eyeZ);
        cosPitch = cosApprox(pitch);
        *upY = mathCosF(camActor->pitch);
        *upX = mathSinF(camActor->pitch) * cosApprox(yaw) * cosPitch;
        *upZ = mathSinF(camActor->pitch) * sinApprox(yaw) * cosPitch;
        camActor->unkEC = camActor->pitch;
    }
    st->unkCC = target->x;
    st->unkD0 = target->y;
    st->unkD4 = target->z;
}

void camResetAllPlayers(void) {
    u8 i;

    for (i = 0; i < gPlayerCount; i++) {
        if (gPlayerSlots[i].unk0) {
            camResetPlayer(gPlayerSlots[i].actor, i);
        }
    }
}

void camResetPlayer(Actor *player, u8 playerIndex) {
    PlayerState *ps = player->customState;
    CamState *st = ps->camActor->customState;
    Actor *cam = ps->camActor;

    gCamActivePaths = &gCamMapPaths;
    st->unk0 = player;
    st->unkFB = playerIndex;
    st->unk60 = 5.0f;
    if (gGameMode == 1) {
        camEndPath(cam);
    }
    st->unkB2 = (cam->unk15F != 0) ? (cam->unk15F / 255.0) * 4095.0 : player->yaw;
    cam->unk15F = 0;
    gGlobalPauseFlags |= 0x2000;
    st->unkF3 = 1;
    st->unk9E = player->yaw;
    camSetZoomLevel(cam, gCurrentMap == 0x9A ? 1 : ((gGlobalOverlayFlags & 1) ? 3 : 2));
    st->unkEE = st->unkEF;
    st->unkA0 = st->unkA4;
    cam->distToFloor = st->unkB8;
    st->unkE8 = 0;
    st->unkEA = st->unkE8;
    st->unkAC |= 0x100;
    st->unkB0 = 0;
    st->unk6C = 123456.0f;
    st->unk70 = 123456.0f;
    st->unkC = -32768.0f;
    player->chunkIndex = mapChunkFindByPosition(player->x, player->y, player->z, 0);
    camUpdate(cam, &gPlayerSlots[playerIndex].camX, &gPlayerSlots[playerIndex].camY, &gPlayerSlots[playerIndex].camZ,
                  &gPlayerSlots[playerIndex].focusX, &gPlayerSlots[playerIndex].focusY, &gPlayerSlots[playerIndex].focusZ,
                  &gPlayerSlots[playerIndex].upX, &gPlayerSlots[playerIndex].upY, &gPlayerSlots[playerIndex].upZ);
    st->unkAC &= ~0x100;
    cam->prevX = gPlayerSlots[playerIndex].camX;
    cam->prevY = gPlayerSlots[playerIndex].camY;
    cam->prevZ = gPlayerSlots[playerIndex].camZ;
}

void camApplyShake(CamState *st, f32 *x, f32 *y, f32 *z, s32 range, u8 decay) {
    s32 r = randomNonNegative();

    if (range == 0) {
        range = 1;
    }
    *x = *x + ((r % range) - (range >> 1)) * 0.01;
    *y = *y + (((r / 100) % range) - (range >> 1)) * 0.01;
    *z = *z + (((r / 10000) % range) - (range >> 1)) * 0.01;
    if (decay) {
        st->unkF2--;
        st->unkC0 = st->unkC0 - st->unkC0 * 0.111;
        st->unkC0++;
    }
}

void camStartShakeFromPoint(Actor *cam, u8 frames, u16 strength, f32 srcX, f32 srcY, f32 srcZ, f32 innerRadius, f32 outerRadius) {
    f32 dx = srcX - cam->x;
    f32 dy = srcY - cam->y;
    f32 dz = srcZ - cam->z;
    f32 dist = sqrtf(dx * dx + dy * dy + dz * dz);

    if (!(outerRadius < dist)) {
        if (dist < innerRadius) {
            camStartShake(cam, frames, strength);
        } else {
            camStartShake(cam, frames, (u16)(strength * ((outerRadius - dist) / (outerRadius - innerRadius))));
        }
    }
}

void camStartShake(Actor *camActor, u8 frames, u16 strength) {
    CamState *cam = camActor->customState;

    if (gGameMode == 1) {
        strength >>= 2;
    }
    if (frames >= cam->unkF2) {
        cam->unkF2 = frames;
    }
    if (strength * 100 >= cam->unkC0) {
        cam->unkC0 = strength * 100;
    }
    rumbleRequest(cam->unkFB, (strength * 9 >= 0x100) ? 0xFF : strength * 9, frames + 1);
}

void camStartBlendRamp(CamState *st, s16 frames) {
    if (frames >= 0xB) {
        st->unkEA = st->unkE8 = frames;
    }
}

void func_8061F18C(Actor *camActor, f32 targetX, f32 targetY, f32 targetZ) {
    CamState *cam;
    s16 ang;
    s16 pad;
    s16 diff;
    s16 pad2;
    f32 dist;
    f64 r;

    cam = camActor->customState;
    ang = mathAngleBetweenPoints2D(cam->unk0->x, cam->unk0->z, targetX, targetZ);
    diff = mathAngleDistance(ang, mathAngleBetweenPoints2D(cam->unk0->x, cam->unk0->z, camActor->prevX, camActor->prevZ));
    dist = sqrtf((targetX - camActor->prevX) * (targetX - camActor->prevX)
               + (targetY - camActor->prevY) * (targetY - camActor->prevY)
               + (targetZ - camActor->prevZ) * (targetZ - camActor->prevZ));
    r = diff * 0.0009765625;
    camStartBlendRamp(cam, (s16)((r < 1.0 ? 1.0 : r) * dist));
}

void camClosestPointOnSegment(f32 px, f32 py, f32 pz, f32 ax, f32 ay, f32 az, f32 bx, f32 by, f32 bz, f32 *outX, f32 *outY, f32 *outZ) {
    f32 distQ;
    f32 distP;
    f32 len2;
    f32 t;

    len2 = (ax - bx) * (ax - bx) + (ay - by) * (ay - by) + (az - bz) * (az - bz);
    if (len2 == 0.0f) {
        *outX = ax;
        *outY = ay;
        *outZ = az;
        return;
    }
    distQ = (bx - px) * (bx - px) + (by - py) * (by - py) + (bz - pz) * (bz - pz);
    distP = (ax - px) * (ax - px) + (ay - py) * (ay - py) + (az - pz) * (az - pz);
    t = (distP + len2 - distQ) / (2 * len2);
    if (t >= 1.0f || distQ == 0.0f) {
        *outX = bx;
        *outY = by;
        *outZ = bz;
    } else if (t <= 0.0f || distP == 0.0f) {
        *outX = ax;
        *outY = ay;
        *outZ = az;
    } else {
        *outX = (bx - ax) * t + ax;
        *outY = (by - ay) * t + ay;
        *outZ = (bz - az) * t + az;
    }
}

void func_8061F4B0(u8 *zoneFlags) {
    u8 i;
    u8 *p;
    s32 v;

    for (i = 0; i < 6; i++) {
        v = (0, zoneFlags)[i]; // FAKE: comma keeps addu a1,a0,v0 operand order
        p = zoneFlags + i;
        if (v != 0) {
            gCamActivePaths->unkC4[v - 1].unk18 |= p[6] & 0xF;
        }
    }
}

void camSetZoneWeight(u8 zoneIndex, u8 weight) {
    gCamMapPaths.unkC4[zoneIndex].unk18 = weight;
}

typedef struct CamZonePair {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
} CamZonePair;

extern f32 gScreenFadeProgress;

#define CAM_ZONE_GROUP ((CamZonePair *)gCamZoneGroups)
#define CAM_ZONE_SORT ((CamZonePair *)gCamZoneSorted)

s32 camEvaluateZones(Actor *camActor, f32 *eyeX, f32 *eyeY, f32 *eyeZ, f32 *focusX, f32 *focusY, f32 *focusZ) {
    CamZoneEntryFull *e;
    s16 ret;
    u8 type0;
    u8 spread;
    u16 rad;
    s16 padR;
    s16 weight;
    s16 i;
    f32 distSq;
    CamState *st;
    Actor *tgt;
    f32 x;
    f32 z;
    f32 y;
    s16 cell;
    s16 k;
    CamZoneEntryFull *best;
    s16 bestIdx;
    s16 padA;
    u8 type;
    u8 hadFlag;
    u8 mode;
    u8 bestType0;
    u8 handled;
    s16 pos[3];
    u8 padB1;
    u8 padB2;
    u8 padB3;
    u8 linkId;
    s16 ang0;
    s16 ang1;
    PlayerState *targetState;
    s32 ang2;
    f32 factor;
    f32 outX;
    f32 outY;
    f32 outZ;

    st = camActor->customState;
    tgt = st->unk0;
    targetState = tgt->customState;
    x = tgt->x;
    y = tgt->y + targetState->unk10C;
    z = tgt->z;
    weight = 0;
    bestIdx = 0;
    handled = 0;
    linkId = 0xFF;
    if (st->unkAC & 0x2000) {
        hadFlag = 1;
    } else {
        hadFlag = 0;
    }
    st->unkAC &= ~0x2000;
    cell = (s32)(z - gCamZoneMinZ) / 400 * gCamZoneGridWidth + (s32)(x - gCamZoneMinX) / 400;
    if (cell < 0) {
        return 0;
    }
    if (gCamZoneGroupCount > 0) {
        i = 0;
        do {
            if (camIsCellNeighbour(cell, CAM_ZONE_GROUP[i].unk0) != 0) {
                k = CAM_ZONE_GROUP[i].unk2;
                if (k < CAM_ZONE_GROUP[i + 1].unk2) {
                    do {
                        e = &gCamActivePaths->unkC4[gCamZoneSorted[k * 2]];
                        spread = e->unk1A;
                        pos[0] = e->unk10;
                        pos[1] = e->unk12;
                        pos[2] = e->unk14;
                        rad = e->unk19 * 4;
                        mode = e->unk1B;
                        type0 = e->unk16;
                        if (e->unk16 == 5) {
                            linkId = e->unk0;
                            e = &gCamActivePaths->unkC4[e->unk0];
                        }
                        type = e->unk16;
                        if (k == st->unkC4 && type == 8) {
                            if (e->unk18 >= 0xF) {
                                rad = rad * (e->unk18 - 0xD);
                            }
                        }
                        switch (mode) {
                            case 1:
                            case 2:
                                distSq = (x - pos[0]) * (x - pos[0]) + (z - pos[2]) * (z - pos[2]);
                                break;
                            case 0:
                                distSq = (x - pos[0]) * (x - pos[0]) + (y - pos[1]) * (y - pos[1]) + (z - pos[2]) * (z - pos[2]);
                                break;
                        }
                        if (tgt->chunkIndex == gCamActivePaths->unkC8[gCamZoneSorted[k * 2]] || type == 8 ||
                            gCamActivePaths->unkC8[gCamZoneSorted[k * 2]] == -1) {
                            if ((mode == 2 && distSq < (f32)(rad * rad) && weight < e->unk18 && !((s16)(s32)y < pos[1]) &&
                                 pos[1] + spread * 2 >= (s16)(s32)y) ||
                                (mode != 2 && distSq < (f32)(rad * rad) && weight < e->unk18)) {
                                switch (type) {
                                    case 4:
                                        handled = 1;
                                        if (k != st->unkC6) {
                                            camReturnToFollow(camActor, tgt);
                                        }
                                        st->unkC6 = k;
                                        st->unkC4 = -1;
                                        break;
                                    case 0:
                                        handled = 1;
                                        if (k != st->unkC6) {
                                            func_8061F4B0((u8 *)e);
                                        }
                                        st->unkC6 = k;
                                        break;
                                    case 1:
                                    case 2:
                                    case 3:
                                    case 7:
                                    case 8:
                                    case 9:
                                        if (e->unk17 & 0x20) {
                                            if (!(st->unkAC & 0x40000)) {
                                                break;
                                            }
                                        }
                                        if (e->unk17 & 0x10) {
                                            if (!((tgt->state == 0x54 && tgt->unk155 >= 3) ||
                                                  (tgt->state == 0x52 && tgt->unk155 >= 8) ||
                                                  (tgt->state == 0x53 && tgt->unk155 >= 3))) {
                                                break;
                                            }
                                        }
                                        if ((e->unk17 & 2) && (e->unk17 & 4)) {
                                            break;
                                        }
                                        if (e->unk17 & 8) {
                                            if (e->unk17 & 4) {
                                                break;
                                            }
                                            if (gScreenFadeProgress == 0.0f) {
                                                break;
                                            }
                                        }
                                        if (!(st->unkAC & 2) && !(e->unk17 & 1)) {
                                            if (!(gFrameCounter & 8) && gPlayerCount == 1) {
                                                renderCallbacksRegister(renderBonusTargetMarker, camActor, 3);
                                            }
                                            break;
                                        }
                                        if (!(e->unk17 & 0x38) && gPlayerCount == 1) {
                                            renderCallbacksRegister(renderBonusTargetMarker, camActor, 3);
                                        }
                                    default:
                                        best = e;
                                        bestIdx = k;
                                        weight = (s16)e->unk18;
                                        st->unkEC = e->unk17;
                                        bestType0 = type0;
                                        break;
                                }
                            }
                        }
                        k++;
                    } while (k < CAM_ZONE_GROUP[i + 1].unk2);
                }
            }
            i++;
        } while (i < gCamZoneGroupCount);
    }
    if (weight != 0) {
        ret = 1;
        if (bestType0 != 5) {
            linkId = 0xFF;
        }
        type = best->unk16;
        if (bestIdx != st->unkC4 || st->unkF3 != 2) {
            switch (type) {
            case 8:
                ang0 = mathAngleBetweenPoints2D(best->unk0, best->unk4, best->unk6, best->unkA);
                if (gCamTargetDist > 10.0f) {
                    ang1 = mathAngleBetweenPoints2D(tgt->x, tgt->z, *eyeX, *eyeZ);
                } else {
                    ang1 = st->unkB2;
                }
                ang2 = ang0 + 0x800;
                if (mathAngleDistance(ang1, ang0) < mathAngleDistance(ang1, ang2)) {
                    st->unkB2 = ang0;
                } else {
                    st->unkB2 = ang2;
                }
                break;
            case 9:
                ang0 = mathAngleBetweenPoints2D(tgt->x, tgt->z, best->unk0, best->unk4);
                ang1 = mathAngleBetweenPoints2D(tgt->x, tgt->z, best->unk6, best->unkA);
                if (mathAngleDistance(ang0, st->unkB2) < mathAngleDistance(ang1, st->unkB2)) {
                    st->unkF9 = 0;
                } else {
                    st->unkF9 = 1;
                }
                break;
            }
        }
        switch (type) {
            case 7:
                if (tgt->state != 0x20) {
                    ang1 = mathAngleBetweenPoints2D(best->unk10, best->unk14, tgt->x, tgt->z);
                    *eyeX = best->unk10 - mathSinF(ang1) * best->unk0;
                    *eyeZ = best->unk14 - mathCosF(ang1) * best->unk0;
                    *eyeY = st->unk6C + camActor->distToFloor;
                    st->unkC8 = 0;
                    st->unkCA = 0;
                }
                break;
            case 6:
                if (hadFlag == 0) {
                    st->unkF1 = 0xB;
                }
                ret = 0;
                st->unkAC |= ((u8 *)best)[2] | 0x2000;
                if (((u8 *)best)[0] != 0) {
                    st->unkA4 = ((u8 *)best)[0];
                    st->unkB8 = ((u8 *)best)[1];
                }
                break;
            case 1:
                *eyeX = best->unk0;
                *eyeY = best->unk2;
                *eyeZ = best->unk4;
                st->unkC8 = best->unk6;
                st->unkCA = best->unk8;
                break;
            case 9:
                *eyeX = ((CamZoneEntryFull *)((s16 *)best + st->unkF9 * 3))->unk0;
                *eyeY = ((CamZoneEntryFull *)((s16 *)best + st->unkF9 * 3))->unk2;
                *eyeZ = ((CamZoneEntryFull *)((s16 *)best + st->unkF9 * 3))->unk4;
                st->unkC8 = 0;
                st->unkCA = 0;
                break;
            case 2:
                camClosestPointOnSegment(x, y, z, best->unk0, best->unk2, best->unk4, best->unk6, best->unk8, best->unkA, eyeX, eyeY, eyeZ);
                st->unkC8 = best->unkC;
                st->unkCA = best->unkE;
                break;
            case 8:
                camComputeFollowPos(camActor, tgt, &outX, &outY, &outZ, -1.0f);
                camClosestPointOnSegment(outX, outY, outZ, best->unk0, best->unk2, best->unk4, best->unk6, best->unk8, best->unkA, eyeX, eyeY, eyeZ);
                st->unkC8 = 0;
                st->unkCA = 0;
                break;
            case 3:
                st->unkC8 = best->unk8;
                st->unkCA = best->unkA;
                factor = sqrtf((z - best->unk4) * (z - best->unk4) + ((x - best->unk0) * (x - best->unk0) + (y - best->unk2) * (y - best->unk2)));
                factor = (best->unk6 / factor > 1.0) ? 1.0 : best->unk6 / factor;
                *eyeX = (best->unk0 - x) * factor + x;
                *eyeY = (best->unk2 - st->unk6C) * factor + st->unk6C;
                *eyeZ = (best->unk4 - z) * factor + z;
                break;
        }
        if (!(st->unkAC & 0x8000) && ret != 0 && (bestIdx != st->unkC4 || st->unkF3 != 2) &&
            (linkId == 0xFF || (linkId != 0xFF && (linkId != st->unkFD || st->unkF3 != 2) && !(gGlobalPauseFlags & 0x2000)))) {
            if (D_807463B8 == 3) {
                gGlobalPauseFlags |= 0x2000;
            } else if (!(st->unkAC & 0x100)) {
                func_8061F18C(camActor, *eyeX, *eyeY, *eyeZ);
            }
        }
        if ((st->unkAC & 0x8000) || gScreenFadeProgress > 27.0f || (best->unk17 & 0x38)) {
            gGlobalPauseFlags |= 0x2000;
            st->unkAC &= 0xFFFF7FFF;
        }
        if (handled == 0) {
            st->unkC6 = -1;
        }
        st->unkFD = linkId;
        st->unkC4 = bestIdx;
        st->unkED = type;
        return ret;
    }
    if (st->unkAC & 0x40000) {
        camFindClearYaw(camActor, 0.0f, st->unkB2, 0);
    }
    if (hadFlag != 0 && !(st->unkAC & 0x2000)) {
        camSetZoomForDistance(camActor, gCamTargetDist);
    }
    if (st->unkF3 == 2) {
        if (st->unkEC & 0xA) {
            gCamActivePaths->unkC4[gCamZoneSorted[st->unkC4 * 2]].unk17 |= 4;
        }
        if (st->unkED != 8 || mathAngleDistance(st->unkB2, tgt->yaw) >= 0x400) {
            st->unkB2 = mathAngleBetweenPoints2D(tgt->x, tgt->z, *eyeX, *eyeZ);
        }
        if (gCamTargetDist > 150.0f) {
            camSetSettleMode(st, 0xF);
        }
    }
    if (handled == 0) {
        st->unkC6 = -1;
    }
    st->unkC4 = -1;
    st->unkEC = 0;
    st->unkFD = 0xFF;
    st->unkAC &= ~2;
    return 0;
}

void camFindClearYaw(Actor *camActor, f32 unused, s16 yaw, u8 failCount) {
    Actor *tgt;
    s32 pad;
    s16 cnt;
    s16 saved;
    s16 out1;
    s16 out0;
    f32 x;
    f32 y;
    f32 z;
    s16 base;
    u8 sawCol;
    u8 again;
    u8 hit;
    u8 dir;
    u8 found;
    s16 step;
    CamState *cam;
    f32 f;

    cam = camActor->customState;
    tgt = cam->unk0;
    cnt = 0;
    out0 = 0xFFF;
    out1 = 0;
    base = cam->unkB2 = yaw;
    found = 0;
    dir = 0;
    step = 0x80;
    f = 1.0f;
    if (cam->unkAC & 0x80000) {
        return;
    }
    if (cam->unkAC & 0x12000) {
        return;
    }
    if (cam->unkF3 != 1 && cam->unkF3 != 5) {
        return;
    }
    if (gGlobalCutsceneFlags & 2) {
        return;
    }
    if (cam->unkFF >= 4) {
        return;
    }
    if (tgt->actorType == 5) {
        if (gPlayerSlots[cam->unkFB].unk2C0 != 1) {
            f = 0.333f;
        }
    }
    camSetZoomLevel(camActor, 1);
    cam->unkB8 = 10.0f;
    camActor->distToFloor = 10.0f;
    cam->unkA0 = 5.0f;
    cam->unkAC |= 0x80000;
    do {
        again = 0;
        sawCol = camComputeFollowPos(camActor, cam->unk0, &x, &y, &z, -1.0f) == 1;
        while (cam->unkA0 < f * 100.0f && !sawCol && (hit = collisionTestSphere(x, y, z, 10.0f * f, &out1, &out0, 1, 0xBC)) == 0) {
            saved = cam->unkB2;
            cam->unkA0 += 10.0f * f;
            camActor->distToFloor += f * 3.0f;
            sawCol = camComputeFollowPos(camActor, cam->unk0, &x, &y, &z, -1.0f) == 1;
            cam->unkB2 = saved;
        }
        if (hit) {
            cam->unkA0 -= f * 10.0f;
            camActor->distToFloor -= f * 3.0f;
        }
        if (f * 60.0f < cam->unkA0 && !sawCol) {
            found = 1;
        } else if ((hit || sawCol) && cnt < 0x1000) {
            again = 1;
            cam->unkB2 = ((dir ? -1 : 1) * step + base) & 0xFFF;
            dir = dir ^ 1;
            if (!dir) {
                step += 0x80;
            }
            cam->unkA0 = 5.0f;
            cam->unkB8 = 10.0f;
            camActor->distToFloor = 10.0f;
            cnt += 0x80;
        }
    } while (again);
    if (found || (cnt < 0x1000 && !sawCol)) {
        cam->unkA4 = cam->unkA0;
        camSetZoomForDistance(camActor, cam->unkA0);
    } else {
        cam->unkFF += failCount;
        x = gPlayerSlots->unk21C;
        y = gPlayerSlots->unk220;
        z = gPlayerSlots->unk224;
        camSetZoomLevel(camActor, 1);
        cam->unkA0 = cam->unkA4;
        camActor->distToFloor = cam->unkB8;
        cam->unkB2 = base;
    }
    cam->unkB0 = 0;
    cam->unkAC |= 0x100000;
    cam->unk38 = x;
    cam->unk3C = y;
    cam->unk40 = z;
    cam->unkEE = cam->unkEF;
    cam->unkAC &= ~0x80000;
    cam->unkC = -32768.0f;
    gGlobalPauseFlags |= 0x2000;
    camActor->speedXZ = 0.0f;
}

extern u8 D_807FB606;

u8 camResolveWallCollision(Actor *camActor, f32 prevX, f32 prevZ, f32 *eyeX, f32 eyeY, f32 *eyeZ, f32 maxPush) {
    CamState *st = camActor->customState;
    s16 arcMin;
    s16 arcMax;
    u8 pad;
    s16 pushYaw;
    s16 pushDist;
    f32 v;

    arcMin = 0;
    arcMax = 0xFFF;
    camActor->hasArcBounds = 0;
    st->unkFC = 0;
    v = 0.0f;
    v += 0.2 * ((180.0f < st->unkA0) ? 180.0f : st->unkA0);
    if (st->unkF5 != 0) {
        v -= 0.1 * st->unkF5;
    } else {
        v -= 0.1 * st->unkF1;
    }
    if (collisionTestSphere(*eyeX, eyeY, *eyeZ, v, &arcMin, &arcMax, 1, 0xBC)) {
        if (D_807FB606 != 0) {
            st->unkFC = 2;
            pushYaw = (camActor->moveYaw + 0x800) & 0xFFF;
            pushDist = 0;
        } else {
            s16 arcMid;
            s16 t;

            arcMid = mathAngleArcMidpoint(arcMin, arcMax);
            prevX += 0.5 * mathSinF(arcMid);
            prevZ += 0.5 * mathCosF(arcMid);
            st->unkFC = 1;
            mathAngleClampToArc(camActor->moveYaw, camActor->moveYaw, arcMin, arcMax, &pushYaw);
            t = func_80672134(arcMin, arcMax, camActor->yaw, 100);
            if (t < maxPush) {
                pushDist = t;
            } else {
                pushDist = maxPush;
            }
        }
        camActor->hasArcBounds = 1;
        *eyeX = mathSinF(pushYaw) * pushDist + prevX;
        *eyeZ = mathCosF(pushYaw) * pushDist + prevZ;
        if (st->unkF5 != 0) {
            st->unkA0 -= 5.0f;
        } else {
            st->unkB2 = mathAngleBetweenPoints2D(st->unk0->x, st->unk0->z, *eyeX, *eyeZ);
        }
        st->unkF1 = 0;
        camActor->unkF2 = pushYaw;
        if (!(st->unkAC & 0x2008) && !(gGlobalOverlayFlags & 1) && D_807476AC < st->unkA0) {
            camSetZoomForDistance(camActor, D_807476AC);
        }
    } else {
        if (!(st->unkAC & 0x2000)) {
            if (st->unkEF != st->unkEE) {
                camSetZoomLevel(camActor, st->unkEE);
            }
        }
        st->unk1C = 0.0f;
    }
    return camActor->hasArcBounds;
}

s32 func_80620F00(Actor *camActor, u8 allowNudge, u8 requireSide) {
    CamState *st = camActor->customState;
    s32 pad;
    f32 diff;
    u8 pastLimit;
    u8 pastLeft;
    u8 pastRight;
    u8 pastRetry;
    PlayerState *targetState;

    diff = gCamTargetDist - gPlayerSlots[st->unkFB].unk284;
    targetState = st->unk0->customState;
    pastLimit = 40.0f < gCamTargetDist && targetState->depthCenter < diff;
    pastLeft = targetState->depthLeft < diff;
    pastRight = targetState->depthRight < diff;
    pastRetry = targetState->unk116 < diff;
    if (requireSide && !pastLeft && !pastRight) {
        pastLimit = 0;
    }
    if (pastLimit != 0) {
        if (allowNudge && st->unk0->speedXZ != 0.0f) {
            if (pastLeft && !pastRight) {
                st->unkB2 += 0x32;
                camSetSettleMode(st, 0xA);
            } else if (pastRight && !pastLeft) {
                st->unkB2 -= 0x32;
                camSetSettleMode(st, 0xA);
            }
        }
        st->unkF4++;
        if (pastRetry && st->unkF4 >= 0x15) {
            st->unkF4 = 0;
            if (st->unk0->speedXZ != 0.0f && st->unk0->state != 0x59) {
                camFindClearYaw(camActor, 0.0f, st->unkB2, 1);
            } else {
                camFindClearYaw(camActor, 0.0f, st->unk0->yaw, 1);
            }
        }
        return 1;
    } else {
        st->unkFF = 0;
        st->unkF4 = 0;
    }
    return 0;
}

extern s8 D_80744530;

u8 camShouldAutoRotate(Actor *camActor, CamState *st, Actor *target) {
    return target->state == 0x5B
        || ((gGlobalOverlayFlags & 0x4000004) && target->speedXZ != 0.0f)
        || (gGlobalOverlayFlags & 0x8000000)
        || (st->unkAC & 4)
        || ((st->unkAC & 8) && target->speedXZ != 0.0f)
        || (D_80744530 == 1 && target->speedXZ != 0.0f && func_807142D8() == 0)
        || st->unkF3 == 0xA
        || st->unkF3 == 0xD
        || st->unkF3 == 5
        || st->unkF3 == 0xC
        || (st->unkFC != 0 && target->speedXZ != 0.0f)
        || target->state == 0x6E
        || target->actorType == 8;
}

extern u8 gViewportCount;
extern f32 gScreenFadeProgress;

u8 camComputeFollowPos(Actor *camActor, Actor *target, f32 *outX, f32 *outY, f32 *outZ, f32 lookAhead) {
    CamState *cam = camActor->customState;
    PlayerState *targetState = target->customState;
    f32 x;
    f32 y;
    f32 z;
    s16 turnSpeed;
    u8 ret;
    s16 targetYaw;
    s16 diff;
    f32 dist;
    f32 baseY;
    s32 pad[2];
    s16 nodeYaw;
    s16 otherYaw;
    f32 nodeAX;
    f32 nodeAY;
    f32 nodeAZ;
    f32 nodeBX;
    f32 nodeBY;
    f32 nodeBZ;

    ret = 0;
    y = 0.0f;
    dist = cam->unkA0;
    baseY = cam->unk6C;
    if ((targetState->stateFlags & 0x800000) && (target->contactFlags & 1) && !(target->prevContactFlags & 1)) {
        targetState->stateFlags &= ~0x800000;
    }
    if ((gGlobalOverlayFlags & 1) && (cam->unkAC & 4) && !(cam->unkAC & 0x4000) && cam->unkF3 != 0xA) {
        turnSpeed = target->speedXZ;
        if (cam->unk12 != 0 && cam->unk4 != NULL) {
            targetYaw = mathAngleBetweenPoints2D(cam->unk12 + (cam->unk4->x - cam->unk12) * 0.35,
                                            cam->unk14 + (cam->unk4->z - cam->unk14) * 0.35,
                                            target->x, target->z);
        } else {
            if (cam->unk4 != NULL) {
                targetYaw = mathAngleBetweenPoints2D(cam->unk4->x, cam->unk4->z, target->x, target->z);
            } else {
                targetYaw = target->yaw;
            }
        }
    } else {
        switch (target->state) {
            case 0x57:
            case 0x58:
                actorGetNodePos(target, 0xC, &nodeAX, &nodeAY, &nodeAZ);
                actorGetNodePos(target, 1, &nodeBX, &nodeBY, &nodeBZ);
                nodeYaw = mathAngleBetweenPoints2D(nodeAX, nodeAZ, nodeBX, nodeBZ) & 0xFE00;
                if (actorTableContains(targetState->pathOwner) != 0) {
                    otherYaw = targetState->pathOwner->yaw;
                    if (nodeYaw < otherYaw) {
                        diff = otherYaw - nodeYaw;
                    } else {
                        diff = nodeYaw - otherYaw;
                    }
                    if (diff > 0x400 && diff < 0xC18) {
                        targetYaw = (otherYaw + 0x92C) & 0xFFF;
                    } else {
                        targetYaw = (otherYaw + 0x12C) & 0xFFF;
                    }
                } else {
                    targetYaw = target->yaw;
                }
                turnSpeed = 5;
                break;
            case 0x5B:
                turnSpeed = 0x64;
                targetYaw = target->yaw;
                break;
            default:
                turnSpeed = target->speedXZ;
                if (cam->unkAC & 0x4000) {
                    targetYaw = (target->yaw + 0x800) & 0xFFF;
                } else {
                    targetYaw = target->yaw;
                }
                break;
        }
    }
    if (lookAhead >= 0.0f && cam->unkF3 != 2) {
        if (gViewportCount == 1) {
            if (target->state == 0x4F) {
                func_80620F00(camActor, 0, 1);
            } else if (target->state == 0x59 || target->state == 0x4E || target->state == 0x6E) {
                func_80620F00(camActor, 0, 0);
            } else if (hudCanRender() != 0 && cam->unkF1 == 0) {
                if (target->actorType != 8 && target->actorType != 9 && gPlayerSlots->unk2C0 != 2) {
                    if (target->state != 0xE && target->state != 0x42 && target->state != 0x57 && target->state != 0x48 &&
                        target->state != 0x49 && target->state != 0x4C && target->state != 0x47 && target->state != 0x3E &&
                        !(cam->unkAC & 0x12000) && !(gGlobalCutsceneFlags & 2) && target->state != 0x58 && target->state != 0x63 &&
                        target->state != 0x52 && target->state != 0x54 && target->state != 0x53 && target->state != 0x40 &&
                        target->state != 0x4F) {
                        func_80620F00(camActor, target->speedXZ != 0.0f ? 1 : 0, 0);
                    }
                }
            }
        }
        if (!(cam->unkAC & 0x100) && gScreenFadeProgress == 0.0f && 2.0 * cam->unkA0 < D_807476AC && cam->unkE8 == 0 &&
            cam->unkF3 != 5 && !(gGlobalCutsceneFlags & 2) && !(gGlobalOverlayFlags & 0x2001)) {
            camFindClearYaw(camActor, -1.0f, cam->unkB2, 0);
        } else {
            if (cam->unkFC != 0 && cam->unkA0 * 1.2 < D_807476AC) {
                if (*outY - (cam->unk90 < cam->unk6C ? cam->unk6C : cam->unk90) > 50.0f && cam->unkEF >= 2) {
                    camSetZoomLevel(camActor, 1);
                    camActor->distToFloor -= 120.0f;
                } else {
                    camActor->distToFloor += 5.0;
                }
            } else if (cam->unkFC == 2) {
                camActor->distToFloor += 20.0f;
            }
        }
    }
    if (cam->unkF3 != 2 && camShouldAutoRotate(camActor, cam, target) != 0) {
        camTurnYawToward(cam, turnSpeed, targetYaw);
    }
    switch (target->state) {
        case 0x63:
            if (gGlobalCutsceneFlags & 2) {
                dist = 100.0f;
                y += target->y + 30.0f + (target->y - target->floorY) * 0.5;
            } else {
        case 0x0:
        case 0x1A:
        case 0x1B:
        case 0x22:
        case 0x2A:
        case 0x31:
        case 0x35:
        case 0x3E:
        case 0x57:
        case 0x58:
        case 0x5A:
        case 0x5B:
        case 0x5C:
        case 0x6E:
        case 0x6F:
                y += target->y + camActor->distToFloor;
            }
            break;
        case 0x59:
            if (gGlobalCutsceneFlags & 2) {
                y += cam->unk6C + camActor->distToFloor;
            } else if ((cam->unkAC & 0x2000) && !(target->contactFlags & 0x80)) {
                y += target->y - cam->unk98;
            } else {
                y += target->prevY + 10.0f;
            }
            break;
        case 0x4E:
        case 0x7E:
        case 0x80:
        case 0x82:
            y += target->y + (camActor->distToFloor < 30.0f ? 30.0f : camActor->distToFloor);
            break;
        case 0x37:
        case 0x43:
        case 0x4F:
        case 0x7F:
        case 0x81:
            y += target->y;
            if ((gGlobalOverlayFlags & 0x20) && D_807F5CD0 >= 0xC9) {
                y += 80.0f * mathSinF(camActor->roll);
            }
            break;
        case 0x21:
            y += target->prevPeakY;
            break;
        case 0x19:
            if (targetState->stateFlags & 0x800000) {
                y += target->y + camActor->distToFloor;
            } else {
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x20:
        case 0x29:
        case 0x41:
        case 0x42:
        case 0x4C:
        case 0x61:
                if (target->peakY - target->y > 50.0f) {
                    baseY = cam->unkDC;
                }
        default:
                if (target->contactFlags & 2) {
                    if (baseY < target->waterY) {
                        baseY = target->waterY;
                    }
                }
                y += baseY + camActor->distToFloor;
            }
            break;
    }
    if (targetState->stateFlags & 0x200) {
        cam->unk9C = 0x3C;
    }
    if (cam->unk9C != 0) {
        cam->unk9C--;
        y += 130.0f;
    }
    x = target->x - mathSinF(cam->unkB2) * dist;
    z = target->z - mathCosF(cam->unkB2) * dist;
    if (lookAhead > 0.0f) {
        x += lookAhead * mathSinF(cam->unk9E);
        z += lookAhead * mathCosF(cam->unk9E);
    }
    if (cam->unkF2 != 0) {
        camApplyShake(cam, &x, &y, &z, cam->unkC0, 0);
    }
    *outX = x;
    *outY = y;
    *outZ = z;
    if (cam->unkF3 != 0xC) {
        ret = camFloorSnap(camActor, cam, *outX, &y, *outZ, lookAhead >= 0.0f ? 0 : 1);
        if (ret != 0 || y < *outY) {
            *outY = y;
        }
    }
    return ret;
}

void camComputeFocusPos(CamState *st, f32 *outX, f32 *outY, f32 *outZ) {
    Actor *actor = st->unk0;
    f32 f;
    f32 y;
    s16 idx;

    f = (actor->state == 0x5B || actor->state == 0x59 || actor->state == 0x57 || actor->state == 0x58 || actor->state == 0x3E) ? 0.11 : 0.17;
    y = 0.0f;
    if (actor->eyeHeight > 0x14) {
        idx = 0x14;
    } else {
        idx = actor->eyeHeight;
    }
    if (D_807476B0 >= 0.0f) {
        y = CAM_MIN(1.0, (f < D_807476B0 ? D_807476B0 - f : 0.0f) * 2);
    } else if (D_807476B0 < -0.1) {
        y = 0.0 - CAM_MAX(CAM_MIN((D_807476B0 - f) + 0.3, 0.0) * 2, -1.0);
    }
    if (st->unk4 != NULL) {
        *outX = st->unk4->x + (actor->x - st->unk4->x) * 0.9;
        *outZ = st->unk4->z + (actor->z - st->unk4->z) * 0.9;
    } else {
        *outX = actor->x;
        *outZ = actor->z;
    }
    *outY = ((st->unkDC + idx) - (st->unk6C + idx)) * y + (st->unk6C + idx);
}

void camComputeFocusPosOffset(CamState *st, f32 *outX, f32 *outY, f32 *outZ, f32 offset) {
    camComputeFocusPos(st, outX, outY, outZ);
    *outX += offset * mathSinF(st->unk9E);
    *outZ += offset * mathCosF(st->unk9E);
}

typedef struct CamZoomEntry {
    /* 0x0 */ u16 height;
    /* 0x2 */ u16 distance;
} CamZoomEntry;

extern CamZoomEntry sCamZoomTable[][4];

u8 camSetZoomLevel(Actor *cam, s16 level) {
    CamState *st = cam->customState;
    u8 old;
    s16 zoomSet;

    zoomSet = (gPlayerCharacterId[st->unkFB] * 2 + (gPlayerSlots[st->unkFB].unk2C0 != 1)) + 7;
    old = st->unkEF;
    if ((st->unkAC & 0x2000) && level > 1) {
        level = 1;
    }
    if ((gGlobalOverlayFlags & 0x10) && level > 1) {
        level = 1;
    }
    if (gCurrentMap == 0x9A) {
        zoomSet = 0;
    } else if (gGlobalCutsceneFlags & 2) {
        zoomSet = 2;
    } else if ((gGlobalOverlayFlags & 1) && gCurrentMap != 0x6F) {
        zoomSet = 3;
    } else if (gGlobalOverlayFlags & 0x80) {
        zoomSet = 4;
    } else if (st->unkAC & 0x20000) {
        zoomSet = 5;
    } else if (gGlobalOverlayFlags & 0x4000000) {
        zoomSet = 6;
    } else if (st->unkF3 == 5 || st->unkF3 == 0xC || st->unkF3 == 0xA) {
        zoomSet = 1;
    }
    st->unkA4 = sCamZoomTable[zoomSet][level].distance;
    st->unkB8 = sCamZoomTable[zoomSet][level].height;
    st->unkEF = level;
    return old;
}

void camSetZoomForDistance(Actor *cam, s16 distance) {
    CamState *st = cam->customState;
    s16 zoomSet;
    s16 best;
    s16 i;

    zoomSet = gPlayerCharacterId[st->unkFB] * 2 + (gPlayerSlots[st->unkFB].unk2C0 != 1) + 7;
    best = 1;
    if (gCurrentMap == 0x9A) {
        zoomSet = 0;
    } else if (gGlobalCutsceneFlags & 2) {
        zoomSet = 2;
    } else if ((gGlobalOverlayFlags & 1) && gCurrentMap != 0x6F) {
        zoomSet = 3;
    } else if (gGlobalOverlayFlags & 0x80) {
        zoomSet = 4;
    } else if (st->unkAC & 0x20000) {
        zoomSet = 5;
    } else if (gGlobalOverlayFlags & 0x4000000) {
        zoomSet = 6;
    } else if (st->unkF3 == 5 || st->unkF3 == 0xC || st->unkF3 == 0xA) {
        zoomSet = 1;
    }
    for (i = 2; i < 4; i++) {
        if (distance >= sCamZoomTable[zoomSet][i].distance) {
            best = i;
        }
    }
    camSetZoomLevel(cam, best);
}

extern Actor *gActivePlayerActor;
void camReturnToFollow(Actor *camActor, Actor *targetActor) {
    CamState *s;
    s32 pad1;
    s32 pad2;
    u8 pad3;
    u8 prev;

    s = camActor->customState;
    prev = s->unkF3;

    if (gActivePlayerActor->soundSlots[0] != -1) {
        sfxStopSlotSound(gActivePlayerActor, 0);
    }
    s->unk44.unk0 = NULL;
    s->unkB0 = 0;
    s->unkF3 = 1;
    s->unkC = -32768.0f;
    switch (prev) {
        case 3:
        case 0xB:
            camStartBlendRamp(s, 0xA);
            s->unkB2 = targetActor->yaw;
            break;
        case 2:
            if (s->unkED == 8) {
                if (mathAngleDistance(s->unkB2, targetActor->yaw) < 0x400) {
                    camSnapBehindTarget(camActor);
                }
            }
            s->unkED = 0xFF;
        default:
            camStartBlendRamp(s, 0x14);
            break;
    }
}

void camSetFollowMode(Actor *camActor) {
    CamState *st = camActor->customState;

    st->unk44.unk0 = NULL;
    st->unkF3 = 1;
}

void camComputeTargetEyePos(Actor *camActor, f32 *outX, f32 *outY, f32 *outZ) {
    CamState *st = camActor->customState;
    CamTargetBlock *p = &st->unk44;
    s16 angle;
    PlayerState *targetState;
    s8 mult;
    s32 pad;

    angle = (p->unk0->yaw + p->unk8) & 0xFFF;
    targetState = st->unk0->customState;
    mult = 1;
    if (st->unk0->state == 0x21 || st->unk0->state == 0x38) {
        return;
    }
    *outX = mathSinF(angle) * p->unkA + p->unk0->x;
    *outZ = mathCosF(angle) * p->unkA + p->unk0->z;
    *outY = p->unk0->y + p->unk10;
    if (gCurrentMap == 6 || gCurrentMap == 0xE || gCurrentMap == 0x37 || gCurrentMap == 0x6A) {
        if (targetState->stateFlags & 0x10000002) {
            mult = -1;
        }
        *outY += (mult * p->unkA) * mathSinF(p->unk0->roll);
    }
    if (p->unk14 != 0) {
        p->unk14--;
        if (p->unk14 == 0 || (!(st->unk0->prevContactFlags & 1) && (st->unk0->contactFlags & 1))) {
            p->unk0 = NULL;
            camResetPlayer(st->unk0, st->unkFB);
            gGlobalPauseFlags |= 0x2000;
            if (gScreenRenderFlags & 0x10) {
                gScreenRenderFlags &= ~0x10;
                sHudDisabled = 0xFF;
            }
        }
    }
}

void camComputeTargetFocusPos(CamState *st, f32 *outX, f32 *outY, f32 *outZ) {
    CamTargetBlock *p;
    s16 angle;

    p = &st->unk44;
    angle = (p->unk0->yaw + p->unkC) & 0xFFF;
    *outX = mathSinF(angle) * p->unkE + p->unk4->x;
    *outZ = mathCosF(angle) * p->unkE + p->unk4->z;
    *outY = p->unk4->y + p->unk12;
}

void func_806228BC(Actor *camActor, f32 *eyeX, f32 *eyeY, f32 *eyeZ, f32 *focusX, f32 *focusY, f32 *focusZ) {
    CamState *st = camActor->customState;
    Actor *tgt = st->unk0;
    s16 angle;
    s32 h;

    *eyeX = tgt->x;
    if (tgt->state == 3 || tgt->state == 5) {
        h = tgt->eyeHeight < 0xF ? 0xF : tgt->eyeHeight;
        *eyeY = h + tgt->y;
    } else if (gCurrentMap == 0x30) {
        h = tgt->eyeHeight < 0x16 ? 0x16 : tgt->eyeHeight;
        *eyeY = h + tgt->y;
    } else {
        h = tgt->eyeHeight < 0xA ? 0xA : tgt->eyeHeight;
        *eyeY = h + tgt->y;
    }
    *eyeZ = tgt->z;
    if (tgt->hasArcBounds != 0) {
        angle = mathAngleArcMidpoint(tgt->arcYawMin, tgt->arcYawMax);
        *eyeX += 5.0 * mathSinF(angle);
        *eyeZ += 5.0 * mathCosF(angle);
    }
    *focusX = tgt->x - mathSinF(st->unkB2) * 50.0f;
    *focusY = tgt->y - (camActor->distToFloor - 138.0f);
    *focusZ = tgt->z - mathCosF(st->unkB2) * 50.0f;
}

f32 camAngleLerpRad(f32 a, f32 b, f32 t) {
    f32 diff = a - b;

    if (diff > 3.1415927f) {
        b += 6.2831855f;
    } else if (diff < -3.1415927f) {
        a += 6.2831855f;
    }
    return a + (b - a) * t;
}

void camComputeEyeFocus(Actor *camActor, f32 *eyeX, f32 *eyeY, f32 *eyeZ, f32 *focusX, f32 *focusY, f32 *focusZ, Actor *target) {
    CamState *cam;
    s16 *list;
    s16 count;
    u8 type;
    CamPathPointPos *pos;
    f32 dz;
    f32 dx;
    f32 dy;
    CamPathPoint *p;
    f32 savedX;
    f32 savedY;
    f32 savedZ;
    f32 pad0;
    u8 idx[4];
    f32 posX;
    f32 posY;
    f32 posZ;
    f32 lookX;
    f32 lookY;
    f32 lookZ;
    f32 scale;
    f32 t;
    s32 pad1;
    f32 dist;
    f32 height;
    s16 angle;
    s16 angleD;
    s16 angleT;
    f64 ratio;
    s32 pad2;
    CamSplineKeyPosLook *e0;
    CamSplineKeyPosLook *e1;
    CamSplineKeyPosLook *e2;
    CamSplineKeyPosLook *e3;
    CamSplineKeyPos *k0;
    CamSplineKeyPos *k1;
    CamSplineKeyPos *k2;
    CamSplineKeyPos *k3;
    f32 blend;
    s16 yaw;
    f32 pitchD;
    f32 pitchT;
    s32 pad4;
    f32 pitch;
    f32 dist2D;
    f32 dist3D;
    f32 zoom;
    s32 pad5;
    f32 yOffset;

    cam = camActor->customState;
    p = &gCamActivePaths->unkD8[gCamPathNode];
    savedX = *eyeX;
    savedY = *eyeY;
    savedZ = *eyeZ;
    if (gGameMode == 1 && (p->unk1 == 4 || p->unk1 == 5)) {
        count = (p->u.spline.unk0 - 1 < 0) ? 0 : p->u.spline.unk0 - 1;
        target->splineT = CAM_LERP(count, 0, D_807F5D00);
        target->yawSpeed = target->splineT;
        target->splineT -= target->yawSpeed;
    } else {
        count = (gCamActivePaths->unk0[target->unk15F].unk0 - 1 < 0) ? 0 : gCamActivePaths->unk0[target->unk15F].unk0 - 1;
    }
    idx[0] = (target->yawSpeed - 1 < 0) ? 0 : target->yawSpeed - 1;
    idx[1] = target->yawSpeed;
    idx[2] = (target->yawSpeed + 1 >= count) ? count : target->yawSpeed + 1;
    idx[3] = (target->yawSpeed + 2 >= count) ? count : target->yawSpeed + 2;
    if (gGameMode != 1U) { // FAKE: unsigned 1 keeps this constant out of the gGameMode == 1 tests' web (codegen)
        if (cam->unkF3 == 3 || cam->unkF3 == 0xB) {
            if (target->state != 2 && target->state != 3 && target->state != 4 && target->state != 5 &&
                target->state != 0x64 && target->state != 0x65) {
                func_8062773C(camActor);
                gGlobalPauseFlags |= 0x2000;
            }
        } else {
            switch (target->state) {
                case 0x36:
                    if (gPlayerCount >= 2 && gSplitScreenMode != 0) { // FAKE: empty guard keeps real global loads/compares (Q0561)
                    }
                    break;
                case 0x57:
                case 0x58:
                    if (cam->unkF3 == 1) {
                        camStartBlendRamp(cam, 0x50);
                        cam->unkF3 = 0xC;
                        camSetZoomLevel(camActor, 2);
                    }
                    break;
                case 0x43:
                case 0x4E:
                case 0x4F:
                case 0x7F:
                case 0x81:
                    if (cam->unkF3 == 1 || cam->unkF3 == 0xC) {
                        camStartBlendRamp(cam, 0x50);
                        cam->unkF3 = 5;
                        cam->unkAC |= 0x40;
                    }
                    break;
                case 0x63:
                    if (cam->unkF3 != 0xA && cam->unkF3 != 2) {
                        cam->unkF3 = 0xA;
                        camStartBlendRamp(cam, 0x1E);
                    }
                    break;
                case 0x62:
                    if (!(gGlobalOverlayFlags & 0x80) && cam->unkF3 != 0xD && cam->unkF3 != 2) {
                        cam->unkF3 = 0xD;
                        camStartBlendRamp(cam, 0x1E);
                    }
                    break;
                default:
                    if (cam->unkF3 == 0xA || cam->unkF3 == 0xC || cam->unkF3 == 0xD) {
                        camSetZoomForDistance(camActor, cam->unkA0);
                        camStartBlendRamp(cam, 0x14);
                        cam->unkF3 = 1;
                        cam->unk6C = target->y;
                    }
                    break;
            }
        }
        if (cam->unkF3 != 6 && cam->unkF3 != 9 && (!(gScreenRenderFlags & 0x10) || D_807463B8 == 3) &&
            cam->unkF3 != 8 && cam->unkF3 != 7 && cam->unkEF != 0) {
            if (camEvaluateZones(camActor, eyeX, eyeY, eyeZ, focusX, focusY, focusZ) != 0) {
                cam->unkF3 = 2;
            } else if (cam->unk44.unk0 != NULL) {
                cam->unkF3 = 4;
            } else if (cam->unkF3 == 3 || cam->unkF3 == 2) {
                camReturnToFollow(camActor, target);
            } else if (cam->unkF3 == 5) {
                switch (target->state) {
                    case 0x37:
                    case 0x43:
                    case 0x4E:
                    case 0x4F:
                    case 0x51:
                    case 0x7F:
                    case 0x81:
                    case 0x82:
                        break;
                    default:
                        camSetZoomForDistance(camActor, gCamTargetDist);
                        cam->unkF3 = 1;
                        cam->unkAC |= 0x20;
                        cam->unkC = -32768.0f;
                        break;
                }
            }
        }
        cam->unkAC &= ~0x40000;
    }
    if (gGameMode != 0) {
        if (gGameMode == 1) {
            type = p->unk1;
            if (type == 7) {
                list = gCamActivePaths->unkD0[gCamPathIndex].unk4;
                p = &gCamActivePaths->unkD8[list[gCamPathStep]];
                if (p->unk1 == 8 || p->unk1 == 0xC) {
                    p = &gCamActivePaths->unkD8[list[gCamPathStep + 1]];
                }
                if (D_807F5CFC == gCamPathFramesLeft + 1) {
                    D_807F5D18 = *eyeX;
                    D_807F5D1C = *eyeY;
                    D_807F5D20 = *eyeZ;
                    D_807F5D24 = *focusX;
                    D_807F5D28 = *focusY;
                    D_807F5D2C = *focusZ;
                }
            } else if (D_807F5CFC == gCamPathFramesLeft + 1) {
                D_807F5D24 = *focusX - *eyeX;
                D_807F5D28 = *focusY - *eyeY;
                D_807F5D2C = *focusZ - *eyeZ;
            }
            if (type == 7) {
                target->yawSpeed = 0;
                target->splineT = 0.0;
                idx[0] = 0;
                idx[1] = 0;
                t = 1.0f;
                idx[2] = (target->yawSpeed + 1 >= count) ? count : target->yawSpeed + 1;
                idx[3] = (target->yawSpeed + 2 >= count) ? count : target->yawSpeed + 2;
            } else {
                t = D_807F5D00;
            }
            switch (p->unk1) {
                case 10:
                case 15:
                case 16:
                    pos = &p->u.pos;
                    dist = CAM_LERP(pos->unk6, pos->unk4, t);
                    height = CAM_LERP(pos->unkA, pos->unk8, t);
                    angle = mathAngleLerp(pos->unk2, pos->unk0, t);
                    posX = mathSinF(target->yaw - angle) * dist + target->x;
                    posZ = mathCosF(target->yaw - angle) * dist + target->z;
                    posY = target->y + height;
                    gPlayerSlots[cam->unkFB].fov = CAM_LERP(pos->unkD, pos->unkC, t);
                    if (p->unk1 == 16) {
                        lookX = posX + D_807F5D24;
                        lookY = posY + D_807F5D28;
                        lookZ = posZ + D_807F5D2C;
                    } else {
                        goto calc_look;
                    }
                    goto look_set;
                case 1:
                    posX = p->u.pos.unk0;
                    posY = p->u.pos.unk2;
                    posZ = p->u.pos.unk4;
                    goto calc_look;
                case 2:
                    pos = &p->u.pos;
                    dz = target->z - pos->unk4;
                    dx = target->x - pos->unk0;
                    dy = target->y - pos->unk2;
                    ratio = pos->unk6 / sqrtf(dz * dz + (dx * dx + dy * dy));
                    scale = (ratio > 1.0) ? 1.0 : ratio;
                    posX = (pos->unk0 - target->x) * scale + target->x;
                    posY = (pos->unk2 - target->floorY) * scale + target->floorY;
                    posZ = (pos->unk4 - target->z) * scale + target->z;
                    goto calc_look;
                case 3:
                    camClosestPointOnSegment(target->x, target->y, target->z, p->u.pos.unk0, p->u.pos.unk2, p->u.pos.unk4,
                                  p->u.pos.unk0 + p->u.pos.unk6, p->u.pos.unk2 + p->u.pos.unk8,
                                  p->u.pos.unk4 + p->u.pos.unkA, &posX, &posY,
                                  &posZ);
                    goto calc_look;
                case 17:
                    posX = *eyeX;
                    posY = *eyeY;
                    posZ = *eyeZ;
                    goto calc_look;
                case 4:
                    e0 = &((CamSplineKeyPosLook *) p->u.spline.unk4)[idx[0]];
                    e1 = &((CamSplineKeyPosLook *) p->u.spline.unk4)[idx[1]];
                    e2 = &((CamSplineKeyPosLook *) p->u.spline.unk4)[idx[2]];
                    e3 = &((CamSplineKeyPosLook *) p->u.spline.unk4)[idx[3]];
                    posX = splineEvalCubic(target->splineT, e0->unk0, e1->unk0, e2->unk0, e3->unk0);
                    posY = splineEvalCubic(target->splineT, e0->unk2, e1->unk2, e2->unk2, e3->unk2);
                    posZ = splineEvalCubic(target->splineT, e0->unk4, e1->unk4, e2->unk4, e3->unk4);
                    lookX = splineEvalCubic(target->splineT, e0->unk6, e1->unk6, e2->unk6, e3->unk6);
                    lookY = splineEvalCubic(target->splineT, e0->unk8, e1->unk8, e2->unk8, e3->unk8);
                    lookZ = splineEvalCubic(target->splineT, e0->unkA, e1->unkA, e2->unkA, e3->unkA);
                    gPlayerSlots[cam->unkFB].fov =
                        splineEvalCubic(target->splineT, e0->unkC, e1->unkC, e2->unkC, e3->unkC);
                    if (gCamRollFramesLeft == 0) {
                        camActor->pitch =
                            splineEvalCubic(target->splineT, e0->unkD, e1->unkD, e2->unkD, e3->unkD) / 127.0 * 2048.0;
                    }
                    break;
                case 5:
                    k0 = &((CamSplineKeyPos *) p->u.spline.unk4)[idx[0]];
                    k1 = &((CamSplineKeyPos *) p->u.spline.unk4)[idx[1]];
                    k2 = &((CamSplineKeyPos *) p->u.spline.unk4)[idx[2]];
                    k3 = &((CamSplineKeyPos *) p->u.spline.unk4)[idx[3]];
                    posX = splineEvalCubic(target->splineT, k0->unk0, k1->unk0, k2->unk0, k3->unk0);
                    posY = splineEvalCubic(target->splineT, k0->unk2, k1->unk2, k2->unk2, k3->unk2);
                    posZ = splineEvalCubic(target->splineT, k0->unk4, k1->unk4, k2->unk4, k3->unk4);
                    gPlayerSlots[cam->unkFB].fov =
                        splineEvalCubic(target->splineT, k0->unk6, k1->unk6, k2->unk6, k3->unk6);
                    if (gCamRollFramesLeft == 0) {
                        camActor->pitch =
                            splineEvalCubic(target->splineT, k0->unk7, k1->unk7, k2->unk7, k3->unk7) / 127.0 * 2048.0;
                    }
                calc_look:
                    if (!gCamPathLookNode) {
                        lookX = mathSinF(target->yaw) * gCamPathLookAhead + target->x;
                        lookZ = mathCosF(target->yaw) * gCamPathLookAhead + target->z;
                        if (target->eyeHeight != 0) {
                            lookY = target->y + target->eyeHeight;
                        } else {
                            lookY = target->y;
                        }
                    } else {
                        actorGetNodePos(gCamPathLookActor, gCamPathLookNode, &lookX, &lookY, &lookZ);
                    }
                    goto look_done;
            }
        look_set: /* two consecutive labels: the empty block keeps uopt from colouring type across the switch */
        look_done:
            if (type == 7) {
                blend = mathSinF(D_807F5D00 * 1024.0f + 3072.0f) + 1.0;
                angleD = mathAngleBetweenPoints2D(D_807F5D24, D_807F5D2C, D_807F5D18, D_807F5D20);
                angleT = mathAngleBetweenPoints2D(lookX, lookZ, posX, posZ);
                pitchD = mathCalculatePitchAngle(D_807F5D18, D_807F5D1C, D_807F5D20, D_807F5D24, D_807F5D28,
                                                 D_807F5D2C, 0);
                pitchT = mathCalculatePitchAngle(posX, posY, posZ, lookX, lookY, lookZ, 0);
                yaw = mathAngleLerp(angleT, angleD, blend);
                pitch = camAngleLerpRad(pitchT, pitchD, blend);
                dist2D = CAM_LERP(sqrtf((lookX - posX) * (lookX - posX) + (lookZ - posZ) * (lookZ - posZ)),
                                  sqrtf((D_807F5D24 - D_807F5D18) * (D_807F5D24 - D_807F5D18) +
                                        (D_807F5D2C - D_807F5D20) * (D_807F5D2C - D_807F5D20)),
                                  blend);
                dist3D = CAM_LERP(sqrtf((lookX - posX) * (lookX - posX) + (lookY - posY) * (lookY - posY) +
                                        (lookZ - posZ) * (lookZ - posZ)),
                                  sqrtf((D_807F5D24 - D_807F5D18) * (D_807F5D24 - D_807F5D18) +
                                        (D_807F5D28 - D_807F5D1C) * (D_807F5D28 - D_807F5D1C) +
                                        (D_807F5D2C - D_807F5D20) * (D_807F5D2C - D_807F5D20)),
                                  blend);
                *eyeX = CAM_LERP(posX, D_807F5D18, blend);
                *eyeY = CAM_LERP(posY, D_807F5D1C, blend);
                *eyeZ = CAM_LERP(posZ, D_807F5D20, blend);
                *focusX = *eyeX + mathSinF(yaw) * dist2D;
                *focusZ = *eyeZ + mathCosF(yaw) * dist2D;
                *focusY = *eyeY + sinApprox(pitch) * dist3D;
                return;
            }
            if (type != 8 && type != 0xC && type != 6) {
                *eyeX = posX;
                *eyeY = posY;
                *eyeZ = posZ;
                *focusX = lookX;
                *focusY = lookY;
                *focusZ = lookZ;
            }
        }
    } else {
        switch (cam->unkF3) {
            case 4:
            case 6:
                camComputeTargetFocusPos(cam, focusX, focusY, focusZ);
                camComputeTargetEyePos(camActor, eyeX, eyeY, eyeZ);
                camSampleFloorHeight(camActor, cam, *eyeX, *eyeZ);
                break;
            case 8:
                camComputeFocusPos(cam, focusX, focusY, focusZ);
                camComputeTargetEyePos(camActor, eyeX, eyeY, eyeZ);
                break;
            case 7:
                camComputeFocusPos(cam, focusX, focusY, focusZ);
                break;
            case 2:
                camComputeFocusPosOffset(cam, focusX, focusY, focusZ, D_807476B4);
                if (gCurrentMap == 0xD6) {
                    *focusY += 50.0f;
                }
                if (cam->unkC8 != 0 || cam->unkCA != 0) {
                    camClampEyeAngle(cam, focusX, focusZ, *eyeX, *eyeZ,
                                  (s32) sqrtf((*eyeX - *focusX) * (*eyeX - *focusX) + (*eyeZ - *focusZ) * (*eyeZ - *focusZ)));
                }
                if (cam->unkF2 != 0) {
                    camApplyShake(cam, eyeX, eyeY, eyeZ, cam->unkC0, 0);
                }
                camSampleFloorHeight(camActor, cam, *eyeX, *eyeZ);
                break;
            case 3:
            case 11:
                func_806228BC(camActor, eyeX, eyeY, eyeZ, focusX, focusY, focusZ);
                if (cam->unkF2 != 0) {
                    camApplyShake(cam, eyeX, eyeY, eyeZ, cam->unkC0, 0);
                }
                camSampleFloorHeight(camActor, cam, *eyeX, *eyeZ);
                break;
            case 5:
            case 10:
            case 12:
                *focusX = target->x;
                *focusZ = target->z;
                if ((target->state == 0x37 || target->state == 0x43 || target->state == 0x4F || target->state == 0x7F ||
                     target->state == 0x81) &&
                    (gGlobalOverlayFlags & 0x20) && D_807F5CD0 >= 0xC9) {
                    *focusY = mathSinF(camActor->roll) * -20.0f + target->y;
                } else {
                    *focusY = target->y;
                }
                camComputeFollowPos(camActor, target, eyeX, eyeY, eyeZ, 0.0f);
                break;
            case 13:
                *focusX = target->x;
                *focusY = ((target->eyeHeight >= 21) ? 20 : target->eyeHeight) + target->y;
                *focusZ = target->z;
                camComputeFollowPos(camActor, target, eyeX, eyeY, eyeZ, 30.0f);
                break;
            case 1:
                zoom = 0.0f;
                yOffset = 0.0f;
                switch (target->state) {
                    case 0x3E:
                        break;
                    case 0x6E:
                    case 0x6F:
                        yOffset = gCurrentActor->eyeHeight;
                        break;
                    case 0x52:
                    case 0x54:
                        yOffset = gCurrentActor->eyeHeight;
                        break;
                    case 0x59:
                        if (gGlobalCutsceneFlags & 2) {
                            goto check_target;
                        }
                        if ((cam->unkAC & 0x2000) && !(target->contactFlags & 0x80)) {
                            yOffset = cam->unk98 + -10.0f;
                        }
                        break;
                    default:
                        zoom = cam->unkA0 / 3.0;
                    check_target:
                        if (gGlobalOverlayFlags & 1) {
                            if (cam->unkEF >= 2) {
                                yOffset = 30.0f;
                            }
                            if (cam->unkAC & 0x10000) {
                                renderCallbacksRegister(renderBonusTargetMarker, camActor, 3);
                                zoom = cam->unkA0 / 10.0;
                            }
                        }
                        break;
                }
                if (cam->unkFC != 0) {
                    zoom = 0.0f;
                }
                cam->unk94 += (zoom - cam->unk94) * 0.1;
                camComputeFocusPosOffset(cam, focusX, focusY, focusZ, cam->unk94);
                camComputeFollowPos(camActor, target, eyeX, eyeY, eyeZ, cam->unk94);
                if (gCurrentMap == 0x57) {
                    camApplySway(cam, eyeX, eyeY, eyeZ, 3.0f, 5.0f, 40.0f, 60.0f);
                }
                *focusY += yOffset;
                break;
        }
        if (gCamFreezeBelowY != 0 && target->y < gCamFreezeBelowY) {
            *eyeX = savedX;
            *eyeY = savedY;
            *eyeZ = savedZ;
        } else if (gCamFreezeYAbove != 0 && gCamFreezeYAbove < target->y) {
            *eyeY = savedY;
        }
    }
}

void camTurnYawToward(CamState *st, s16 speed, s16 targetYaw) {
    s16 diff;
    u16 dist;
    f32 scale;
    f32 limit;
    u16 wrap;

    diff = targetYaw - st->unkB2;
    dist = diff > 0 ? diff : -diff;
    wrap = dist >= 0x801 ? 0x1000 - dist : dist;
    limit = speed / 3000.0f * wrap + 5.7f;
    if ((((st->unkAC & 4) || st->unk0->actorType == 8) && !(569.0f <= dist && dist <= 3527.0f)) ||
        (gGlobalOverlayFlags & 0x8000) || st->unk0->state == 0x82) {
        scale = D_807F5CCC;
    } else {
        switch (st->unkF3) {
            case 1:
            case 5:
                if (569.0f <= dist && dist <= 3527.0f) {
                    scale = mathCosF((s16)((dist - 569.0f) / 2958.0f * 4096.0f)) * 0.5f + 0.5f;
                } else if (dist < 0x14) {
                    scale = dist / 20.0f;
                } else {
                    scale = 1.0f;
                }
                break;
            case 10:
                scale = 6.0f;
                break;
            case 12:
                scale = 8.0f;
                break;
            case 13:
                scale = 15.0f;
                break;
            default:
                scale = 1.0f;
                break;
        }
    }
    limit = limit * scale;
    if ((f32)dist < limit) {
        limit = dist;
    }
    if (diff != 0) {
        if ((diff > 0 && dist < 0x800) || (diff < 0 && dist >= 0x800)) {
            st->unkB2 = st->unkB2 + limit;
        } else {
            st->unkB2 = st->unkB2 - limit;
        }
    }
    st->unkB2 &= 0xFFF;
}

void camUpdateFollowBlend(Actor *camActor) {
    CamState *st = camActor->customState;
    Actor *target = st->unk0;
    PlayerState *targetState = target->customState;
    CamTargetBlock *tgt = &st->unk44;
    f32 scale;
    f32 speedRatio;
    f32 base;
    s32 dist;
    f64 distScale;
    f64 clampedScale;
    f32 dz;
    f32 dx;

    switch (st->unkF3) {
        case 6:
        case 9:
            gCamEyeBlendRate = 1.0f;
            gCamFocusBlendRate = 1.0f;
            break;
        case 4:
        case 8:
            gCamEyeBlendRate = tgt->unk18;
            gCamFocusBlendRate = tgt->unk18;
            break;
        case 3:
        case 11:
            if (target->attachMode == 1) {
                dz = target->z - st->unk8C;
                dx = target->x - st->unk84;
                dist = dz * dz + dx * dx;
                distScale = dist * 0.001;
                clampedScale = (distScale > 1.0) ? 1.0 : distScale;
                gCamEyeBlendRate = clampedScale * -0.8 + 1.0;
            } else {
                gCamEyeBlendRate = 0.2f;
            }
            gCamFocusBlendRate = 0.3f;
            break;
        case 2:
            gCamEyeBlendRate = 0.3f;
            if (target->state == 0x62) {
                gCamFocusBlendRate = 0.05f;
            } else if (!(st->unkAC & 0x80)) {
                gCamFocusBlendRate = 0.3f;
            }
            break;
        case 1:
            if (st->unkB0 != 0 || st->unkF1 != 0 || gCurrentMap == 0x27 || st->unkF6 != 0) {
                gCamEyeBlendRate = 0.3f;
                gCamFocusBlendRate = 0.3f;
            } else if (st->unkF7 != 0) {
                gCamEyeBlendRate = 0.2f;
                gCamFocusBlendRate = 0.2f;
            } else if ((st->unkAC & 4) || target->actorType == 8) {
                gCamEyeBlendRate = 0.1f;
                gCamFocusBlendRate = 0.2f;
            } else if (target->state == 0x22) {
                gCamEyeBlendRate = 0.4f;
                gCamFocusBlendRate = 0.2f;
            } else if (target->state == 0xE || target->state == 0x59) {
                gCamEyeBlendRate = 0.1f;
                gCamFocusBlendRate = 0.08f;
            } else {
                base = 0.03f;
                if (camActor->speedXZ != 0.0f) {
                    speedRatio = st->unk10 / camActor->speedXZ;
                } else {
                    speedRatio = 0.0f;
                }
                speedRatio = (speedRatio / 20.0 > 1.0) ? 1.0 : speedRatio / 20.0;
                if (st->unkF8 != 0) {
                    speedRatio += (1.0 - speedRatio) * ((u32)(--st->unkF8) / 30.0);
                }
                if ((targetState->stateFlags & 0x800000) || target->state == 0x1E || target->state == 0x1C || target->state == 0x20 || target->state == 0x1B || target->state == 0x1A || target->state == 0x6E || target->state == 0x3E) {
                    if (!(target->contactFlags & 1)) {
                        base = 0.3f;
                    }
                }
                gCamEyeBlendRate = base + (0.6 - base) * speedRatio;
                gCamFocusBlendRate = base + (0.4 - base) * speedRatio;
            }
            break;
        case 7:
            gCamEyeBlendRate = 0.05f;
            gCamFocusBlendRate = 0.05f;
            break;
        case 5:
            gCamEyeBlendRate = 0.2f;
            gCamFocusBlendRate = 0.2f;
            break;
        case 10:
            gCamEyeBlendRate = 0.3f;
            gCamFocusBlendRate = 0.3f;
            break;
        case 12:
            gCamEyeBlendRate = 0.6f;
            gCamFocusBlendRate = 0.6f;
            break;
        case 13:
            gCamEyeBlendRate = 0.2f;
            gCamFocusBlendRate = 0.2f;
            break;
    }
    if (st->unkE8 != 0) {
        switch (st->unkF3) {
            case 3:
            case 6:
            case 7:
            case 8:
            case 9:
            case 11:
                scale = 1.0f;
                break;
            case 1:
            case 4:
            case 5:
            dist++; // FAKE: dead increment makes uopt colour dist $v0 (else $t0)
            case 10:
            case 12:
            case 13:
                scale = mathSinF((s16)((1.0 - (f32)st->unkE8 / (f32)st->unkEA) * 1024.0)) * 0.8 + 0.2;
                break;
            case 2:
                scale = mathSinF((s16)((1.0 - (f32)st->unkE8 / (f32)st->unkEA) * 1024.0)) * 0.9 + 0.1;
                break;
        }
        st->unkE8--;
        gCamEyeBlendRate *= scale;
        gCamFocusBlendRate *= scale;
    }
}

f32 camApproachFloat(f32 value, f32 target, f32 step) {
    if (value < target) {
        value += step;
        if (target < value) {
            value = target;
        }
    } else {
        value -= step;
        if (value < target) {
            value = target;
        }
    }
    return value;
}

#define CAM_ABSDIFF(a, b) (((a) < (b)) ? (b) - (a) : (a) - (b))
#define CAM_FOLLOW_SPEED_RAW (CAM_ABSDIFF(st->unkD0, target->y) * 0.08)
#define CAM_FOLLOW_SPEED (CAM_FOLLOW_SPEED_RAW > 0.03 ? CAM_FOLLOW_SPEED_RAW : 0.03)

void camUpdateFollow(Actor *camActor, f32 *eyeX, f32 *eyeY, f32 *eyeZ, f32 *focusX, f32 *focusY, f32 *focusZ) {
    s32 pad;
    CamState *st = camActor->customState;
    Actor *target = st->unk0;
    f32 dist;
    f32 spd;
    f32 t;

    spd = CAM_FOLLOW_SPEED < 1.0 ? CAM_FOLLOW_SPEED : 1.0;
    camUpdateFollowBlend(camActor);
    st->unkE4 = st->unkE4 + (spd - st->unkE4) * 0.1;
    dist = sqrtf((camActor->z - st->unk8C) * (camActor->z - st->unk8C) +
                 (camActor->x - st->unk84) * (camActor->x - st->unk84));
    if (dist < 0.1) {
        dist = 0.0f;
    }
    if (camActor->speedXZ < dist) {
        camActor->speedXZ = camApproachFloat(camActor->speedXZ, dist, st->unk60);
    } else {
        camActor->speedXZ = dist;
    }
    camActor->moveYaw = mathAngleBetweenPoints2D(camActor->x, camActor->z, st->unk84, st->unk8C);
    camActor->yaw = camActor->moveYaw;
    if (st->unkB0 != 0 || st->unkF1 != 0 || gCurrentMap == 0x27 || st->unkF6 != 0 || st->unkE8 != 0 ||
        (st->unkAC & 0x100) || st->unkF3 != 1) {
        st->unkE4 = t = gCamEyeBlendRate;
    } else {
        t = (st->unkE4 > 1.0) ? 1.0 : st->unkE4;
    }
    camUpdateEyePos(camActor, t, eyeX, eyeY, eyeZ);
    if (target->attachMode == 1 && st->unk10 != 0) {
        camUpdateFocusPos(camActor, 0.5f, focusX, focusY, focusZ);
    } else if (st->unkF3 == 1) {
        camUpdateFocusPos(camActor, t, focusX, focusY, focusZ);
    } else {
        camUpdateFocusPos(camActor, gCamFocusBlendRate, focusX, focusY, focusZ);
    }
}

void camUpdateEyePos(Actor *camActor, f32 blendY, f32 *eyeX, f32 *eyeY, f32 *eyeZ) {
    CamState *st = camActor->customState;
    s16 ang;
    f32 savedX;
    f32 savedZ;
    f32 pad;
    f32 clampY;

    if (camActor->hasArcBounds) {
        ang = camActor->unkF2;
    } else {
        ang = camActor->moveYaw;
    }
    savedX = st->unk84;
    savedZ = st->unk8C;
    switch (st->unkF3) {
        case 1:
        case 5:
        case 10:
        case 12:
        case 13:
            st->unk84 += gCamEyeBlendRate * camActor->speedXZ * mathSinF(ang);
            st->unk8C += gCamEyeBlendRate * camActor->speedXZ * mathCosF(ang);
            st->unk88 = (camActor->y - st->unk88) * blendY + st->unk88;
            if (st->unkF3 != 12 && !(gGlobalCutsceneFlags & 2)) {
                camResolveWallCollision(camActor, savedX, savedZ, &st->unk84, st->unk88, &st->unk8C, gCamEyeBlendRate * camActor->speedXZ);
            }
            *eyeX = *eyeX + (st->unk84 - *eyeX) * 0.3;
            *eyeY = *eyeY + (st->unk88 - *eyeY) * 0.3;
            *eyeZ = *eyeZ + (st->unk8C - *eyeZ) * 0.3;
            if (st->unkF3 != 12) {
                clampY = (*eyeY < st->unk0->y) ? st->unk0->y : *eyeY;
                if (camFloorSnap(camActor, st, *eyeX, &clampY, *eyeZ, 1) != 0 || clampY < *eyeY) {
                    *eyeY = clampY;
                }
            }
            break;
        default:
            st->unk84 = *eyeX = *eyeX + (camActor->x - *eyeX) * gCamEyeBlendRate;
            st->unk88 = *eyeY = *eyeY + (camActor->y - *eyeY) * gCamEyeBlendRate;
            st->unk8C = *eyeZ = *eyeZ + (camActor->z - *eyeZ) * gCamEyeBlendRate;
            break;
    }
}

void camUpdateFocusPos(Actor *camActor, f32 blendY, f32 *focusX, f32 *focusY, f32 *focusZ) {
    CamState *st = camActor->customState;

    *focusX = *focusX + (st->unk78 - *focusX) * gCamFocusBlendRate;
    *focusY = *focusY + (st->unk7C - *focusY) * blendY;
    *focusZ = *focusZ + (st->unk80 - *focusZ) * gCamFocusBlendRate;
}

s32 camIsCellNeighbour(s16 cell, s16 center) {
    s16 i;
    s16 j;

    for (i = -1; i < 2; i++) {
        for (j = -1; j < 2; j++) {
            if (cell == center + i * gCamZoneGridWidth + j) {
                return 1;
            }
        }
    }
    return 0;
}

s16 camGetZoneCell(s32 zone) {
    CamZoneEntryFull *e = &gCamActivePaths->unkC4[zone];

    return (e->unk10 - gCamZoneMinX) / 400 + (e->unk14 - gCamZoneMinZ) / 400 * gCamZoneGridWidth;
}

void camGetZoneBounds(s16 *outMinX, s16 *outMaxX, s16 *outMinZ) {
    s16 i;

    *outMinX = 0x7FFF;
    *outMinZ = 0x7FFF;
    *outMaxX = -0x8000;
    for (i = 0; i < gCamActivePaths->unkC0; i++) {
        if (gCamActivePaths->unkC4[i].unk10 < *outMinX) {
            *outMinX = gCamActivePaths->unkC4[i].unk10;
        }
        if (*outMaxX < gCamActivePaths->unkC4[i].unk10) {
            *outMaxX = gCamActivePaths->unkC4[i].unk10;
        }
        if (gCamActivePaths->unkC4[i].unk14 < *outMinZ) {
            *outMinZ = gCamActivePaths->unkC4[i].unk14;
        }
    }
    *outMinX -= 0xC8;
    *outMaxX += 0xC8;
    *outMinZ -= 0xC8;
}

void camInitZones(void) {
    s16 i;
    s16 j;
    s16 k;
    s16 key;
    s16 idx;
    s16 val;

    camGetZoneBounds(&gCamZoneMinX, &gCamZoneMaxX, &gCamZoneMinZ);
    gCamZoneMaxX = gCamZoneMaxX / 400 * 400 + 400;
    gCamZoneMinX = gCamZoneMinX / 400 * 400;
    gCamZoneGridWidth = (gCamZoneMaxX - gCamZoneMinX) / 400;
    gCamZoneMinZ = gCamZoneMinZ / 400 * 400;
    if (gCamZoneSorted != NULL) {
        heapFree(gCamZoneSorted);
    }
    gCamZoneSorted = heapAlloc((gCamActivePaths->unkC0 * 2 + 2) * sizeof(s16));
    for (i = 0; i < gCamActivePaths->unkC0; i++) {
        gCamZoneSorted[i * 2] = i;
        gCamZoneSorted[i * 2 + 1] = camGetZoneCell(i);
    }
    for (i = 1; i < gCamActivePaths->unkC0; i++) {
        key = gCamZoneSorted[i * 2 + 1];
        idx = gCamZoneSorted[i * 2];
        val = gCamZoneSorted[i * 2 + 1];
        j = i;
        while (j > 0 &&
               (key < gCamZoneSorted[(j - 1) * 2 + 1] ||
                (key == gCamZoneSorted[(j - 1) * 2 + 1] &&
                 gCamActivePaths->unkC4[gCamZoneSorted[(j - 1) * 2]].unk18 < gCamActivePaths->unkC4[gCamZoneSorted[j * 2]].unk18))) {
            gCamZoneSorted[j * 2] = gCamZoneSorted[(j - 1) * 2];
            gCamZoneSorted[j * 2 + 1] = gCamZoneSorted[(j - 1) * 2 + 1];
            j--;
        }
        if (j != i) {
            gCamZoneSorted[j * 2] = idx;
            gCamZoneSorted[j * 2 + 1] = val;
        }
    }
    gCamZoneGroupCount = 1;
    for (i = gCamActivePaths->unkC0 - 1; i > 0; i--) {
        if (gCamZoneSorted[i * 2 + 1] != gCamZoneSorted[(i - 1) * 2 + 1]) {
            gCamZoneGroupCount++;
        }
    }
    if (gCamZoneGroups != NULL) {
        heapFree(gCamZoneGroups);
    }
    gCamZoneGroups = heapAlloc(gCamZoneGroupCount * 4 + 4);
    CAM_ZONE_GROUP[0].unk0 = CAM_ZONE_SORT[0].unk2;
    CAM_ZONE_GROUP[0].unk2 = 0;
    k = 1;
    for (i = 1; i < gCamActivePaths->unkC0; i++) {
        if ((val = gCamZoneSorted[i * 2 + 1]) != gCamZoneSorted[(i - 1) * 2 + 1]) {
            CAM_ZONE_GROUP[k].unk0 = val;
            CAM_ZONE_GROUP[k].unk2 = i;
            k++;
        }
    }
    CAM_ZONE_GROUP[k].unk0 = -1;
    CAM_ZONE_GROUP[k].unk2 = gCamActivePaths->unkC0;
}

void camSetSecondTarget(Actor *cam, s16 targetX, s16 targetZ) {
    CamState *st = cam->customState;

    st->unk4 = spawnNodeActivate(1, 0);
    if (st->unk4 != NULL) {
        st->unkB2 = mathAngleBetweenPoints2D(st->unk4->x, st->unk4->z, st->unk0->x, st->unk0->z);
    } else {
        st->unkB2 = st->unk0->yaw;
    }
    if (targetX != 0) {
        st->unk12 = targetX;
        st->unk14 = targetZ;
        st->unkB2 = mathAngleBetweenPoints2D(targetX, targetZ, st->unk0->x, st->unk0->z);
    }
    st->unkAC |= 0x10004;
}

void camClearSecondTarget(Actor *cam) {
    CamState *st = cam->customState;

    st->unk4 = NULL;
    st->unkAC &= ~0x10004;
}

void camLoadPathTable(void *src, CamPathData *paths, u8 allocate) {
    camLoadPathData(src, paths, allocate);
    paths->unkD8[48].unk1 = 0xE;
    paths->unkD8[49].unk1 = 0xB;
    paths->unkD8[50].unk1 = 6;
    paths->unkD8[51].unk1 = 0x11;
    paths->unkD8[52].unk1 = 7;
    paths->unkD8[53].unk1 = 8;
}

void camInit(void *mapPathSrc) {
    void *buf = assetLoad(8, 0, 1, 1);

    splineSetBasisTension(0.5f);
    gCamActivePaths = &gCamMapPaths;
    gCamPathFlags = 0;
    gCamZoneGroups = NULL;
    gCamZoneSorted = NULL;
    camLoadPathTable(mapPathSrc, gCamActivePaths, 1);
    camLoadPathTable(buf, gCamGlobalPathsPtr, 0);
    assetFreeBuffer(buf, 0x10B4, 0xC);
    camInitZones();
    D_807476B4 = 0;
    gCamFreezeBelowY = 0;
    gCamFreezeYAbove = 0;
    D_807F5CCC = 6.0f;
    if (gGlobalOverlayFlags & 1) {
        D_807F5CCC = 12.0f;
    }
    switch (gCurrentMap) {
        case 0x4E:
        case 0x4F:
        case 0x83:
            D_807476B4 = 0x1E;
            break;
        case 0x25:
        case 0x29:
            gCamFreezeBelowY = 0x1F4;
            break;
        case 0x36:
            gCamFreezeBelowY = 0xFA;
            break;
        case 0x6E:
            gCamFreezeBelowY = 0x226;
            break;
        case 0xBA:
            gCamFreezeBelowY = 0xFA;
            break;
        case 0xBB:
        case 0xBC:
            gCamFreezeBelowY = 0x12C;
            break;
        case 0x27:
            D_807F5CCC = 10.0f;
            break;
        case 0x2D:
            gCamFreezeYAbove = 0x78;
            break;
    }
    gCamPathTimeDelta = 0;
    gCamPathLastTime = 0;
}

void camCopyVec3s(s16 *dst, s16 *src) {
    *dst++ = *src++;
    *dst++ = *src++;
    *dst++ = *src++;
}


void *camCopyPathPayload(u8 *src, void *dst, u16 size) {
    memcpy(dst, src + 4, size);
    return src + 4 + size;
}

void camLoadPathData(void *src, CamPathData *paths, u8 allocate) {
    s16 i;
    s16 j;
    s16 cnt;
    s16 *hdr;
    u8 *data;
    CamPathHead *h;
    CamPathSeg *dst;
    CamPathPoint *pt;
    s16 *s;
    u8 *rd;
    s32 padf1;
    s32 padf2;
    s32 padf3;
    s32 padf4;
    s32 padf5;
    CamPathSeg buf;
    CamPathPointSpline *u;
    s16 m;
    s16 k;
    s32 padg1;
    s32 padg2;
    s16 *zp;
    s32 skip;

    hdr = src;
    data = src != NULL ? (u8 *)src + 0x30 : NULL;
    for (i = 0; i < 0x18; i++) {
        h = &paths->unk0[i];
        cnt = h->unk0 = hdr != NULL ? *hdr++ : 0;
        if (allocate) {
            h->unk4 = heapAlloc(cnt * sizeof(CamPathSeg));
            for (j = 0; j < cnt; j++) {
                dst = &h->unk4[j];
                buf = *(CamPathSeg *)data;
                data += sizeof(CamPathSeg);
                camCopyVec3s(dst->a, buf.a);
                camCopyVec3s(dst->c, buf.c);
                camCopyVec3s(dst->b, buf.b);
            }
        }
    }
    hdr = (s16 *)data;
    cnt = paths->unkC0 = hdr != NULL ? *hdr++ : 0;
    if (allocate) {
        paths->unkC8 = heapAlloc(cnt);
        paths->unkC4 = heapAlloc(cnt * sizeof(CamZoneEntryFull));
        zp = hdr;
        for (i = 0; i < cnt; i++) {
            paths->unkC8[i] = mapChunkFindByPosition(zp[8], zp[9], zp[10], 0);
            paths->unkC4[i] = *(CamZoneEntryFull *)zp;
            zp += 0xE;
        }
        hdr = zp;
    }
    cnt = paths->unkCC = hdr != NULL ? *hdr++ : 0;
    paths->unkD0 = heapAlloc(cnt * sizeof(CamPathList));
    for (i = 0; i < cnt; i++) {
        paths->unkD0[i].unk0 = m = *hdr;
        k = m;
        hdr++; // LAYOUT: increment after the field stores puts addiu s2 after move s3 (as1 order)
        paths->unkD0[i].unk4 = heapAlloc(m * 2);
        paths->unkD0[i].unk8 = heapAlloc(m * 2);
        for (j = 0; j < k; j++) {
            paths->unkD0[i].unk4[j] = *hdr++;
            paths->unkD0[i].unk8[j] = *hdr++;
        }
    }
    i = 0;
    cnt = paths->unkD4 = hdr != NULL ? *hdr++ : 0;
    paths->unkD8 = heapAlloc(0x6400);
    heapClearBlock(paths->unkD8);
    rd = (u8 *)hdr;
    if (cnt != 0) {
        do {
            skip = 0;
            u = &paths->unkD8[i].u.spline;
            paths->unkD8[i].unk1 = rd[1];
            paths->unkD8[i].unk0 = rd[0];
            switch (paths->unkD8[i].unk1) {
                case 13:
                    rd = camCopyPathPayload(rd, u, 0xC);
                    break;
                case 12:
                    rd = camCopyPathPayload(rd, u, 2);
                    break;
                case 10:
                case 15:
                case 16:
                    rd = camCopyPathPayload(rd, u, 0xE);
                    break;
                case 1:
                    rd = camCopyPathPayload(rd, u, 6);
                    break;
                case 2:
                    rd = camCopyPathPayload(rd, u, 8);
                    break;
                case 3:
                    rd = camCopyPathPayload(rd, u, 0xC);
                    break;
                case 4:
                    s = (s16 *)(rd + 0x20);
                    j = 0;
                    u->unk0 = *(s16 *)(rd + 4);
                    u->unk4 = heapAlloc(u->unk0 * sizeof(CamSplineKeyPosLook));
                    for (; j < u->unk0; j++) {
                        ((CamSplineKeyPosLook *)u->unk4)[j] = *(CamSplineKeyPosLook *)s;
                        s += 7;
                    }
                    rd = (u8 *)s;
                    break;
                case 5:
                    s = (s16 *)(rd + 0x14);
                    j = 0;
                    u->unk0 = *(s16 *)(rd + 4);
                    u->unk4 = heapAlloc(u->unk0 * sizeof(CamSplineKeyPos));
                    for (; j < u->unk0; j++) {
                        ((CamSplineKeyPos *)u->unk4)[j] = *(CamSplineKeyPos *)s;
                        s += 4;
                    }
                    rd = (u8 *)s;
                    break;
                default:
                    rd = camCopyPathPayload(rd, u, 0);
                    skip = 1;
                    break;
            }
            if (skip == 0) {
                cnt--;
            }
            i++;
        } while (cnt != 0);
    }
}

s32 camDistance3D(s32 x1, s32 y1, s32 z1, s32 x2, s32 y2, s32 z2) {
    s64 pad0;
    s64 pad1;
    s64 pad2;

    return sqrtf((s64)(x1 - x2) * (x1 - x2) + (s64)(y1 - y2) * (y1 - y2) +
                 (s64)(z1 - z2) * (z1 - z2));
}

s16 camClampEyeAngle(CamState *camState, f32 *eyeX, f32 *eyeZ, f32 focusX, f32 focusZ, f32 dist) {
    s16 ang;
    s16 mid;
    s16 a;
    s16 b;
    s16 c;
    s16 d1;
    s16 d2;
    u8 clamped;

    ang = mathAngleBetweenPoints2D(*eyeX, *eyeZ, focusX, focusZ);
    mid = camState->unkC8 + (camState->unkCA - camState->unkC8) * 0.5;
    clamped = 0;
    if (camState->unkC8 < camState->unkCA) {
        mid = (mid + 0x800) & 0xFFF;
    }
    a = (camState->unkC8 - mid) & 0xFFF;
    b = (camState->unkCA - mid) & 0xFFF;
    c = (ang - mid) & 0xFFF;
    d1 = (c < a) ? a - c : c - a;
    d2 = (c < b) ? b - c : c - b;
    if (a < b) {
        if (a < c && c < b) {
            if (d1 < d2) {
                ang = camState->unkC8;
            } else {
                ang = camState->unkCA;
            }
            clamped = 1;
        }
    } else {
        if (c < a && b < c) {
            if (d1 < d2) {
                ang = camState->unkC8;
            } else {
                ang = camState->unkCA;
            }
            clamped = 1;
        }
    }
    if (dist < 40.0f) {
        ang = mathAngleLerp(mid, ang, dist / 40.0);
        gCamFocusBlendRate = dist / 40.0 * 0.25 + 0.05;
        if (!clamped) {
            dist = (dist > 1.0) ? dist : 1.0;
        }
        camState->unkAC |= 0x80;
    }
    *eyeX = mathSinF(ang) * dist + focusX;
    *eyeZ = mathCosF(ang) * dist + focusZ;
    return ang;
}

extern u8 gGfxBufferIndex;

s32 camProjectToScreen(f32 x, f32 y, f32 z, f32 *screenX, f32 *screenY, Mtx *modelMtx, f32 scaleFactor, u8 playerIndex) {
    f32 w;
    f32 scale;

    w = 1.0f;
    if (modelMtx != NULL) {
        camTransformPoint(modelMtx, x, y, z, w, &x, &y, &z, &w);
    }
    camTransformPoint(&gPlayerSlots[playerIndex].viewMtx[gGfxBufferIndex], x, y, z, w, &x, &y, &z, &w);
    if (0.0 <= z) {
        *screenX = 16384.0f;
        *screenY = 16384.0f;
        return 1;
    }
    camTransformPoint(&gPlayerSlots[playerIndex].projMtx[gGfxBufferIndex], x, y, z, w, &x, &y, &z, &w);
    scale = gPlayerSlots[playerIndex].perspNorm / 65535.0;
    x *= scale;
    y *= scale;
    w *= scale;
    x /= w;
    y /= w;
    x = gPlayerSlots[playerIndex].unk278 * 0.5 * x;
    y = gPlayerSlots[playerIndex].unk27A * 0.5 * y;
    x = gPlayerSlots[playerIndex].rect[0] + gPlayerSlots[playerIndex].unk278 * 0.5 + x;
    y = gPlayerSlots[playerIndex].rect[1] + gPlayerSlots[playerIndex].unk27A * 0.5 + y;
    y = (gPlayerSlots[playerIndex].unk27A - (y - gPlayerSlots[playerIndex].rect[1])) + gPlayerSlots[playerIndex].rect[1];
    if (16384.0f <= (x > 0.0f ? x : -x)) {
        x = ((0.0f <= x) ? 1 : -1) << 14;
    }
    if (16384.0f <= (y > 0.0f ? y : -y)) {
        y = ((0.0f <= y) ? 1 : -1) << 14;
    }
    x *= scaleFactor;
    y *= scaleFactor;
    *screenX = x;
    *screenY = y;
    return 0;
}

void camTransformPoint(Mtx *mtx, f32 x, f32 y, f32 z, f32 w, f32 *outX, f32 *outY, f32 *outZ, f32 *outW) {
    f32 m[4][4];

    guMtxL2F(m, mtx);
    *outX = (m[0][0] * x + m[1][0] * y + m[2][0] * z) + m[3][0];
    *outY = (m[0][1] * x + m[1][1] * y + m[2][1] * z) + m[3][1];
    *outZ = (m[0][2] * x + m[1][2] * y + m[2][2] * z) + m[3][2];
    *outW = (m[0][3] * x + m[1][3] * y + m[2][3] * z) + m[3][3];
}

void camPolarFromPoints(f32 *outYaw, f32 *outPitch, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2) {
    *outYaw = mathAngleBetweenPointsDeg(x2, z2, x1, z1) * 0.017453292f;
    *outPitch = mathAtan2(y1 - y2, sqrtf((x1 - x2) * (x1 - x2) + (z1 - z2) * (z1 - z2)));
}

void func_8062754C(f32 t) {
    s16 i;

    camClosestPointOnSegment(gPlayerSlots->focusX, gPlayerSlots->focusY, gPlayerSlots->focusZ, 517.0f, 312.0f, 346.0f, 347.0f, 312.0f, 494.0f, &gPlayerSlots->camX, &gPlayerSlots->camY, &gPlayerSlots->camZ);
    gPlayerSlots->camX = (gPlayerSlots->camX - gPlayerSlots->focusX) * t + gPlayerSlots->focusX;
    gPlayerSlots->camY = (gPlayerSlots->camY - gPlayerSlots->focusY) * t + gPlayerSlots->focusY;
    gPlayerSlots->camZ = (gPlayerSlots->camZ - gPlayerSlots->focusZ) * t + gPlayerSlots->focusZ;
    for (i = 1; i < gPlayerCount; i++) {
        gPlayerSlots[i].camX = gPlayerSlots->camX;
        gPlayerSlots[i].camY = gPlayerSlots->camY;
        gPlayerSlots[i].camZ = gPlayerSlots->camZ;
    }
}

f32 func_806276AC(void) {
    s16 i;

    for (i = 0; i < gPlayerCount; i++) {
        gPlayerSlots[i].focusX = 586.0f;
        gPlayerSlots[i].focusY = 205.0f;
        gPlayerSlots[i].focusZ = 584.0f;
    }
    return 1.0f;
}

s32 func_8062773C(Actor *cam) {
    CamState *st = cam->customState;
    s16 ang;

    ang = st->unkB2 + 0x800;
    if (st->unkF0 != 0) {
        camSetZoomLevel(cam, st->unkF0);
    } else {
        camSetZoomLevel(cam, 1);
    }
    cam->distToFloor = st->unkB8;
    st->unkF1 = 0xB;
    st->unkF3 = 1;
    camRestoreYaw(cam);
    st->unk94 = st->unkA0 / 3.0;
    gPlayerSlots[st->unkFB].fov = 45.0f;
    st->unk78 = st->unk0->x;
    st->unk7C = st->unk0->y + st->unk0->eyeHeight;
    st->unk80 = st->unk0->z;
    camSetSettleMode(st, 0xB);
    sfxStopSlotSound(st->unk0, 0);
    st->unk0->contactFlags &= ~0x2000;
    return ang;
}

void camSaveYaw(Actor *cam) {
    CamState *st = cam->customState;

    st->unkB4 = st->unkB2;
}

void camRestoreYaw(Actor *cam) {
    CamState *st = cam->customState;

    st->unkB2 = st->unkB4;
    cam->unk15F = st->unkB2 / 4095.0 * 255.0;
}

void camStartPathNearWall(Actor *camActor, u8 openPath, u8 wallPath, u8 flags) {
    s16 arcMin;
    s16 arcMax;

    if (collisionTestSphere(camActor->x, camActor->y, camActor->z, 80.0f, &arcMin, &arcMax, 1, 0xBC)) {
        camActor->yaw = mathAngleBetweenPoints2D(gPlayerSlots->camX, gPlayerSlots->camZ, camActor->x, camActor->z);
        camStartPath(camActor, wallPath, flags);
    } else {
        camStartPath(camActor, openPath, flags);
    }
}
