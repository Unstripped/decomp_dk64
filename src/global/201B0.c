#include "common.h"
#include "actor.h"

typedef struct CamState {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[0x34];
    /* 0x44 */ s32 unk44;
    /* 0x48 */ u8 pad48[0x24];
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ u8 pad70[0x24];
    /* 0x94 */ f32 unk94;
    /* 0x98 */ f32 unk98;
    /* 0x9C */ u8 pad9C[4];
    /* 0xA0 */ f32 unkA0;
    /* 0xA4 */ u8 padA4[8];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ u8 padB0[0x10];
    /* 0xC0 */ s32 unkC0;
    /* 0xC4 */ u8 padC4[4];
    /* 0xC8 */ s16 unkC8;
    /* 0xCA */ s16 unkCA;
    /* 0xCC */ u8 padCC[0x23];
    /* 0xEF */ u8 unkEF;
    /* 0xF0 */ u8 padF0[2];
    /* 0xF2 */ u8 unkF2;
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4[7];
    /* 0xFB */ u8 unkFB;
    /* 0xFC */ u8 unkFC;
} CamState;

typedef struct CamActor {
    /* 0x000 */ u8 pad0[0x6A];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x1C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x3C];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[0x6A];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[9];
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ f64 unk160;
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 pad16A[0xA];
    /* 0x174 */ CamState *unk174;
} CamActor;

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
    } u;
} CamPathPoint; // size = 0x14

typedef struct CamPathList {
    /* 0x0 */ u8 pad0[4];
    /* 0x4 */ s16 *unk4;
    /* 0x8 */ u8 pad8[4];
} CamPathList; // size = 0xC

typedef struct CamPathCount {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u8 pad2[6];
} CamPathCount; // size = 0x8

typedef struct CamPathData {
    /* 0x00 */ CamPathCount unk0[0x1A];
    /* 0xD0 */ CamPathList *unkD0;
    /* 0xD4 */ u8 padD4[4];
    /* 0xD8 */ CamPathPoint *unkD8;
} CamPathData;

typedef struct Struct807FC924 {
    /* 0x000 */ u8 pad0[0x27C];
    /* 0x27C */ f32 unk27C;
    /* 0x280 */ u8 pad280[0x70];
} Struct807FC924; // size = 0x2F0

extern u8 D_807444EC;
extern u8 D_807463B8;
extern u8 D_80750AB8;
extern s32 D_8076A064;
extern s32 D_8076A0A8;
extern u8 D_8076A0B1;
extern u8 D_8076A0B3;

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern s32 D_807FBB60;
extern s32 D_807FBB64;
extern s32 D_807FBB68;
extern Struct807FC924 *D_807FC924;
extern u8 D_807FC928;

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
void *gCamPathLookActor;
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
void *gCamPathActor;
CamActor *gCamActor;
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


void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
f32 func_80612790(s16);
f32 func_80612794(s16);
f32 sinApprox(f32);
void camApplySway(CamState *, f32 *, f32 *, f32 *, f32, f32, f32, f32);
void camSampleFloorHeight(CamActor *, CamState *, f32, f32);
void camApplyShake(CamState *, f32 *, f32 *, f32 *, s32, s32);
void camStartBlendRamp(CamState *, s32);
void camClosestPointOnSegment(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *);
s32 func_8061F53C(CamActor *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
u8 camComputeFollowPos(CamActor *, CamActor *, f32 *, f32 *, f32 *, f32);
void camComputeFocusPos(CamState *, f32 *, f32 *, f32 *);
void camComputeFocusPosOffset(CamState *, f32 *, f32 *, f32 *, f32);
u8 camSetZoomLevel(CamActor *, s16);
void camSetZoomForDistance(CamActor *, s16);
void camReturnToFollow(CamActor *, CamActor *);
void camComputeTargetEyePos(CamActor *, f32 *, f32 *, f32 *);
void camComputeTargetFocusPos(CamState *, f32 *, f32 *, f32 *);
void func_806228BC(CamActor *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
f32 camAngleLerpRad(f32, f32, f32);
s16 camClampEyeAngle(CamState *, f32 *, f32 *, f32, f32, f32);
f32 splineEvalCubic(f64, f32, f32, f32, f32);
s32 func_8062773C(CamActor *);
s16 mathAngleLerp(s16, s16, f32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
f32 mathCalculatePitchAngle(f32, f32, f32, f32, f32, f32, s32);
void renderBonusTargetMarker();
void renderCallbacksRegister(void *, void *, s32);
f32 sqrtf(f32);

#define CAM_LERP(a, b, t) ((a) + ((b) - (a)) * (t))

u8 camCueTimerIsRunning(void) {
    return gCamCueStartTime != 0;
}

extern u64 __ll_mul(u64, u64);
extern u64 __ull_div(u64, u64);
void func_80712524(s32, s32);

void camCueTimerTick(void) {
    u64 t = __ull_div(__ull_div(__ll_mul(osGetTime() - gCamCueStartTime, 0x40), 0xBB8), 0x2710);

    if ((u32)t >= gCamCueTable[gCamCueIndex].unk0) {
        func_80712524(gCamCueTable[gCamCueIndex].unk4, gCamCueTable[gCamCueIndex].unk5);
        if (++gCamCueIndex >= 6) {
            gCamCueStartTime = 0;
        }
    }
}

typedef struct CamPlayerRec {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0xC];
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ u8 pad234[0x50];
    /* 0x284 */ f32 unk284;
    /* 0x288 */ u8 pad288[0x38];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 pad2C1[3];
    /* 0x2C4 */ f32 unk2C4;
    /* 0x2C8 */ s16 unk2C8;
    /* 0x2CA */ u8 pad2CA[6];
    /* 0x2D0 */ f32 unk2D0;
    /* 0x2D4 */ u8 pad2D4[0x15];
    /* 0x2E9 */ u8 unk2E9;
    /* 0x2EA */ u8 pad2EA[6];
} CamPlayerRec; // size = 0x2F0

void func_8061B5C4(s16 arg0) {
    ((CamPlayerRec *)D_807FC924)[arg0].unk2D0 = ((CamPlayerRec *)D_807FC924)[arg0].unk2C4;
    ((CamPlayerRec *)D_807FC924)[arg0].unk2E9 = 0x18;
}

typedef struct CamStateTargetMode {
    /* 0x00 */ CamActor *unk0;
    /* 0x04 */ u8 pad4[0xEF];
    /* 0xF3 */ u8 unkF3;
} CamStateTargetMode;

void func_8061B610(CamActor *arg0) {
    CamStateTargetMode *st = (CamStateTargetMode *)arg0->unk174;

    arg0->unk7C = st->unk0->unk7C;
    arg0->unk80 = st->unk0->unk80 + 170.0f;
    arg0->unk84 = st->unk0->unk84;
    st->unkF3 = 7;
}

void func_8061B650(CamActor *arg0) {
    CamState *st = arg0->unk174;

    st->unkF3 = 9;
}

typedef struct CamStateYaw {
    /* 0x00 */ u8 pad0[0xB2];
    /* 0xB2 */ s16 unkB2;
} CamStateYaw;

void camApplySway(CamState *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 sp1C;
    f32 sp18;

    sp18 = func_80612794(((CamStateYaw *)arg0)->unkB2 + 0x400);
    *arg1 += arg4 * func_80612794((u32)D_8076A064 * arg6) * sp18;
    sp18 = func_80612790(((CamStateYaw *)arg0)->unkB2 + 0x400);
    *arg3 += arg4 * func_80612794((u32)D_8076A064 * arg6) * sp18;
    *arg2 += arg5 * func_80612794((u32)D_8076A064 * arg7);
}

u8 collisionCheckActorFloor(Actor *, f32, f32, f32, f32 *);
u8 collisionGetFloorHeight(f32 *);

typedef struct CamStateFloor {
    /* 0x00 */ u8 pad0[0x90];
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 pad94[0x66];
    /* 0xFA */ u8 unkFA;
} CamStateFloor;

void camSampleFloorHeight(CamActor *arg0, CamState *arg1, f32 arg2, f32 arg3) {
    f32 sp24 = 99999.0f;

    ((CamStateFloor *)arg1)->unkFA = 0;
    collisionCheckActorFloor((Actor *)arg0, arg2, sp24, arg3, &sp24);
    ((CamStateFloor *)arg1)->unkFA = collisionGetFloorHeight(&((CamStateFloor *)arg1)->unk90);
}

typedef struct CamStateSettle {
    /* 0x00 */ u8 pad0[0xF7];
    /* 0xF7 */ u8 unkF7;
} CamStateSettle;

void func_8061B840(CamStateSettle *arg0, u8 arg1) {
    arg0->unkF7 = arg1;
}

typedef struct CamFloorHit {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
} CamFloorHit; // size = 0x8

extern u8 D_807F9510;
extern CamFloorHit D_807F94C0[];

void camSortFloorHits(void) {
    s16 i;
    s16 j;
    CamFloorHit tmp;

    for (i = 1; i < D_807F9510; i++) {
        if (10000.0f < D_807F94C0[i - 1].unk0) {
            D_807F94C0[i - 1].unk6 = 0;
        }
        j = i;
        tmp = D_807F94C0[i];
        while ((j > 0 && tmp.unk0 < D_807F94C0[j - 1].unk0) || (tmp.unk0 == D_807F94C0[j - 1].unk0 && (D_807F94C0[j - 1].unk6 & 1))) {
            D_807F94C0[j] = D_807F94C0[j - 1];
            j--;
        }
        if (j != i) {
            D_807F94C0[j] = tmp;
        }
    }
}

typedef struct CamFloorActor {
    /* 0x00 */ u8 pad0[0xC0];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ u8 padC4[0x22];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[0x6C];
    /* 0x154 */ u8 unk154;
} CamFloorActor;

typedef struct CamFloorState {
    /* 0x00 */ CamFloorActor *unk0;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[8];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[0x74];
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 pad94[0xC];
    /* 0xA0 */ f32 unkA0;
    /* 0xA4 */ u8 padA4[8];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ u8 padB0[2];
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ u8 padB4[0x41];
    /* 0xF5 */ u8 unkF5;
    /* 0xF6 */ u8 padF6[4];
    /* 0xFA */ u8 unkFA;
} CamFloorState;

#define CAM_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define CAM_MAX(a, b) (((a) < (b)) ? (b) : (a))

void camFindClearYaw(CamActor *, f32, s16, u8);

u8 camFloorSnap(void *arg0, void *arg1, f32 arg2, f32 *arg3, f32 arg4, s32 arg5) {
    CamFloorActor *X = ((CamFloorState *)arg1)->unk0;
    f32 sp78;
    f32 sp74;
    u8 ret;
    f32 bonus;
    u8 flags;
    u8 cnt;
    s16 i;
    s16 pad;
    s16 sp64;
    f32 lim;
    s32 pad2;
    s32 pad3;
    f64 new_var;

    ret = 0;
    if (1) {
    }
    sp74 = -32768.0f;
    sp78 = 32767.0f;
    ((CamFloorState *)arg1)->unkFA = 0;
    cnt = 0;
    if (collisionCheckActorFloor((Actor *)arg0, arg2, sp78, arg4, &sp78)) {
        camSortFloorHits();
        if (D_807F9510 == 1 || *arg3 < D_807F94C0[0].unk0) {
            flags = D_807F94C0[0].unk6;
            sp78 = D_807F94C0[0].unk0;
            sp64 = D_807F94C0[0].unk4;
            cnt = 1;
        } else {
            for (i = 0; i < D_807F9510; i++) {
                flags = D_807F94C0[i].unk6;
                if (flags & 2) {
                    if (*arg3 < D_807F94C0[i].unk0 || (sp74 != ((CamFloorState *)arg1)->unkC && ((CamFloorState *)arg1)->unkC < *arg3)) {
                        sp74 = D_807F94C0[i].unk0;
                        break;
                    }
                }
                if (!(flags & 4) && (flags & 1) && D_807F94C0[i].unk4 >= 0x1F5) {
                    sp78 = D_807F94C0[i].unk0;
                    cnt++;
                    sp64 = D_807F94C0[i].unk4;
                }
            }
        }
        bonus = 15.0f;
        if (D_8076A0A8 == 0x30 && (u32)D_8076A064 > 0x3C) {
            new_var = CAM_MIN(1.0, ((u32)D_8076A064 - 0x3C) * 0.01);
            bonus += 10.0 * new_var;
        }
        if ((D_807FBB64 & 8) && !(flags & 8)) {
            lim = CAM_MAX((func_80612794(sp64 + 0x800) + 1.0f) * 100.0f, bonus);
        } else {
            lim = bonus;
        }
        if (((CamFloorState *)arg1)->unk18 < lim) {
            ((CamFloorState *)arg1)->unk18 = lim;
        } else {
            ((CamFloorState *)arg1)->unk18 = ((CamFloorState *)arg1)->unk18 + (lim - ((CamFloorState *)arg1)->unk18) * 0.05;
        }
        if (*arg3 < sp78 + ((CamFloorState *)arg1)->unk18) {
            ret = 1;
            if (sp78 - *arg3 < 35.0 || (D_807F9510 == 1 && sp64 >= 0x1F5 && sp78 - *arg3 < 80.0)) {
                *arg3 = sp78 + ((CamFloorState *)arg1)->unk18;
                ((CamFloorState *)arg1)->unkAC |= 0x800;
                ret = 2;
            } else if (!(((CamFloorState *)arg1)->unkAC & 0x82000) && !*((u8 *)&arg5 + 3) && !(D_807FBB64 & 1) &&
                       ((X->unkC0 < -300.0f && X->unk154 != 0x59) || X->unk154 == 0x15 || X->unk154 == 0x16)) {
                camFindClearYaw((CamActor *)arg0, -2.0f, ((CamFloorState *)arg1)->unkB2 + 0x800, 0);
            } else if ((D_807FBB64 & 1) || D_807F9510 < 2 || (((CamFloorState *)arg1)->unkAC & 0x80000)) {
                ret = 0;
            }
        } else {
            ((CamFloorState *)arg1)->unkAC &= ~0x800;
        }
    } else {
        if (!(D_807FBB68 & 0x80)) {
            sp78 = 32767.0f;
        }
    }
    ((CamFloorState *)arg1)->unkFA = collisionGetFloorHeight(&((CamFloorState *)arg1)->unk90);
    if (*((u8 *)&arg5 + 3)) {
        ((CamFloorState *)arg1)->unkA = ((CamFloorState *)arg1)->unk8;
        if (sp74 != -32768.0f && sp78 < sp74) {
            ((CamFloorState *)arg1)->unk8 = sp74 - sp78;
        } else {
            ((CamFloorState *)arg1)->unk8 = 0;
        }
        if (!(D_807FBB68 & 0x20) && ((CamFloorState *)arg1)->unkF5 == 0) {
            u8 v1;

            if (X->unk154 == 0x63) {
                v1 = 0x14;
            } else {
                v1 = 10;
            }
            if (((CamFloorState *)arg1)->unk8 != 0) {
                if (sp78 + ((CamFloorState *)arg1)->unk8 - v1 < *arg3) {
                    *arg3 = sp78 + ((CamFloorState *)arg1)->unk8 - v1;
                }
            }
        }
        if (X->unk154 == 0x44 || X->unk154 == 0x57 || X->unk154 == 0x59) {
            ((CamFloorState *)arg1)->unkC = -32768.0f;
        } else {
            ((CamFloorState *)arg1)->unkC = sp74;
        }
    }
    if (*((u8 *)&arg5 + 3)) {
        if (!(((CamFloorState *)arg1)->unkAC & 0x82000)) {
            if (sp78 == 32767.0f || (D_807F9510 == 1 && cnt == 0)) {
                ((CamFloorState *)arg1)->unkA0 -= 10.0f;
                ((CamFloorState *)arg1)->unkB2 = X->unkE6;
            }
        }
    }
    return ret;
}

typedef struct CamStateViewAngle {
    /* 0x00 */ u8 pad0[0xA8];
    /* 0xA8 */ f32 unkA8;
    /* 0xAC */ u8 padAC[0x4F];
    /* 0xFB */ u8 unkFB;
} CamStateViewAngle;

f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
void func_8060B55C();

void camUpdatePlayerYaw(CamStateViewAngle *arg0) {
    ((CamPlayerRec *)D_807FC924)[arg0->unkFB].unk2C4 = mathAngleBetweenPointsRad(((CamPlayerRec *)D_807FC924)[arg0->unkFB].unk210, ((CamPlayerRec *)D_807FC924)[arg0->unkFB].unk218, ((CamPlayerRec *)D_807FC924)[arg0->unkFB].unk228, ((CamPlayerRec *)D_807FC924)[arg0->unkFB].unk230);
    arg0->unkA8 = ((CamPlayerRec *)D_807FC924)[arg0->unkFB].unk2C4;
    switch (D_807463B8) {
        case 0:
            ((CamPlayerRec *)D_807FC924)[arg0->unkFB].unk2C8 = arg0->unkA8 * 4096.0 / 6.2831855f;
            break;
        case 2:
            func_8060B55C((u8 *)&D_807FC924[arg0->unkFB] + 0x2C8);
            break;
        case 3:
            ((CamPlayerRec *)D_807FC924)[arg0->unkFB].unk2C8 = arg0->unkA8 * 4096.0 / 6.2831855f;
            break;
    }
    if (((CamPlayerRec *)D_807FC924)[arg0->unkFB].unk2E9 != 0) {
        ((CamPlayerRec *)D_807FC924)[arg0->unkFB].unk2E9--;
    }
}

s32 camSetFlags(CamActor *arg0, s32 arg1) {
    CamState *s = arg0->unk174;
    s32 v = s->unkAC | arg1;
    s->unkAC = v;
    return v;
}

void camClearFlags(CamActor *arg0, s32 arg1) {
    arg0->unk174->unkAC &= ~arg1;
}

typedef struct CamTargetBlock {
    /* 0x00 */ CamActor *unk0;
    /* 0x04 */ CamActor *unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[2];
    /* 0x18 */ f32 unk18;
} CamTargetBlock;

typedef struct CamTargetState {
    /* 0x00 */ CamActor *unk0;
    /* 0x04 */ u8 pad4[0x1C];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ u8 pad38[0xC];
    /* 0x44 */ CamTargetBlock unk44;
    /* 0x60 */ u8 pad60[0x4C];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ u8 padB0[0x43];
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4[7];
    /* 0xFB */ u8 unkFB;
} CamTargetState;

void camEndPath();

void camSetFixedView(CamActor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7) {
    CamTargetState *s = (CamTargetState *)arg0->unk174;

    if (D_807444EC == 1 && arg7) {
        camEndPath(arg0);
    }
    if (D_807444EC != 1 || arg7) {
        s->unkAC |= 0x80000000;
    }
    s->unk20 = arg1;
    s->unk24 = arg2;
    s->unk28 = arg3;
    s->unk2C = arg4;
    s->unk30 = arg5;
    s->unk34 = arg6;
}

void camApplyFixedView(CamActor *arg0) {
    CamTargetState *s = (CamTargetState *)arg0->unk174;

    ((CamPlayerRec *)D_807FC924)[s->unkFB].unk210 = s->unk20;
    ((CamPlayerRec *)D_807FC924)[s->unkFB].unk214 = s->unk24;
    ((CamPlayerRec *)D_807FC924)[s->unkFB].unk218 = s->unk28;
    ((CamPlayerRec *)D_807FC924)[s->unkFB].unk228 = s->unk2C;
    ((CamPlayerRec *)D_807FC924)[s->unkFB].unk22C = s->unk30;
    ((CamPlayerRec *)D_807FC924)[s->unkFB].unk230 = s->unk34;
}

void camSetTargetFocusActor(CamActor *arg0, CamActor *arg1) {
    CamTargetState *s = (CamTargetState *)arg0->unk174;
    s->unk44.unk4 = arg1;
}

void func_806EAB44();

void camSetTarget(CamActor *arg0, CamActor *arg1, u8 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, f32 arg10) {
    CamTargetState *s = (CamTargetState *)arg0->unk174;
    CamTargetBlock *p = &s->unk44;

    if (arg1 != NULL) {
        p->unk0 = arg1;
        p->unk4 = arg1;
        p->unk8 = arg3;
        p->unkA = arg4;
        p->unkC = arg5;
        p->unkE = arg6;
        p->unk10 = arg7;
        p->unk12 = arg8;
        p->unk14 = arg9;
        p->unk18 = arg10;
        if (s->unkF3 == 3) {
            func_806EAB44(D_807FBB4C, 0);
        }
        s->unkF3 = arg2;
    } else {
        camReturnToFollow(arg0, s->unk0);
    }
}

typedef struct CamActorModelScale {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ f32 unk38;
} CamActorModelScale;

typedef struct CamActorModelRef {
    /* 0x0 */ u8 pad0[4];
    /* 0x4 */ CamActorModelScale *unk4;
} CamActorModelRef;

void camSetTargetScaled(CamActor *, CamActor *, u8, s16, s16, s16, s16, s16, s16, s16, f32);

void camSetTargetCutsceneUnscaled(CamActor *arg0, CamActor *arg1, u8 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, f32 arg10) {
    f32 saved = ((CamActorModelRef *)arg1)->unk4->unk38;

    if (D_807444EC == 1) {
        camEndPath(arg0);
    }
    D_8076A0B3 = 0;
    D_8076A0B1 |= 0x10;
    ((CamActorModelRef *)arg1)->unk4->unk38 = 0.15f;
    camSetTargetScaled(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
    ((CamActorModelRef *)arg1)->unk4->unk38 = saved;
    D_807FBB60 &= ~1;
}

void camSetTargetCutscene(CamActor *arg0, CamActor *arg1, u8 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, f32 arg10) {
    if (D_807444EC == 1) {
        camEndPath(arg0);
    }
    D_8076A0B3 = 0;
    D_8076A0B1 |= 0x10;
    camSetTarget(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
}

void func_8061B5C4(s16);

void camSetTargetScaled(CamActor *arg0, CamActor *arg1, u8 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, f32 arg10) {
    CamTargetState *s = (CamTargetState *)arg0->unk174;
    CamTargetBlock *p = &s->unk44;
    f32 scale;

    if (arg1 != NULL) {
        scale = ((CamActorModelRef *)arg1)->unk4->unk38 / 0.15;
        p->unk0 = arg1;
        p->unk4 = arg1;
        p->unk8 = arg3;
        p->unkA = arg4 * scale;
        p->unkC = arg5;
        p->unkE = arg6 * scale;
        p->unk10 = arg7 * scale;
        p->unk12 = arg8 * scale;
        p->unk14 = arg9;
        p->unk18 = arg10;
        if (s->unkF3 == 3) {
            func_806EAB44(D_807FBB4C, 0);
        }
        s->unkF3 = arg2;
        D_807FBB60 |= 0x2000;
        func_8061B5C4(s->unkFB);
    } else {
        camReturnToFollow(arg0, s->unk0);
    }
}

typedef struct CamPathPointWords {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u32 unk4;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u8 padC[8];
} CamPathPointWords; // size = 0x14

typedef struct CamPathStepList {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ s16 *unk4;
    /* 0x8 */ s16 *unk8;
} CamPathStepList; // size = 0xC

typedef struct CamPathDataLists {
    /* 0x00 */ u8 pad0[0xD0];
    /* 0xD0 */ CamPathStepList *unkD0;
    /* 0xD4 */ u8 padD4[4];
    /* 0xD8 */ CamPathPointWords *unkD8;
} CamPathDataLists;

#define CAM_PATH_LISTS ((CamPathDataLists *)gCamActivePaths)

void camLoadPathPoint(void);
void camComputeEyeFocus(CamActor *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, CamActor *);

s16 camPathGetLength(s16 arg0) {
    s16 total;
    s16 path;
    s16 i;
    u8 unused;
    u8 found;
    s16 count;
    s16 saved;
    s16 first;
    s16 idx;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;

    total = 0;
    first = 0;
    path = arg0;
    do {
        found = 0;
        count = CAM_PATH_LISTS->unkD0[path].unk0;
        for (i = 0; i < count; i++) {
            idx = CAM_PATH_LISTS->unkD0[path].unk4[i];
            switch (CAM_PATH_LISTS->unkD8[idx].unk1) {
                case 6:
                    break;
                case 0xD:
                    if ((CAM_PATH_LISTS->unkD8[idx].unk4 & 0xFF) == 8) {
                        path = CAM_PATH_LISTS->unkD8[idx].unk8 >> 16;
                        found = 1;
                    }
                    break;
                case 0xE:
                    break;
                default:
                    if (first == 0) {
                        saved = ((CamActor *)gCamPathLookActor)->unk168;
                        first = 1;
                        sp94 = ((CamPlayerRec *)D_807FC924)->unk210;
                        sp90 = ((CamPlayerRec *)D_807FC924)->unk214;
                        sp8C = ((CamPlayerRec *)D_807FC924)->unk218;
                        sp88 = ((CamPlayerRec *)D_807FC924)->unk228;
                        sp84 = ((CamPlayerRec *)D_807FC924)->unk22C;
                        sp80 = ((CamPlayerRec *)D_807FC924)->unk230;
                        D_807F5CFC = 1.0f;
                        D_807F5D00 = 0.0f;
                        gCamPathIndex = path;
                        gCamPathStep = i;
                        camLoadPathPoint();
                        camComputeEyeFocus(gCamActor, &sp94, &sp90, &sp8C, &sp88, &sp84, &sp80, gCamPathLookActor);
                        gCamPathStep = 0;
                        gCamPathIndex = arg0;
                        gCamPathStartX = sp94;
                        gCamPathStartY = sp90;
                        gCamPathStartZ = sp8C;
                        gCamPathStartYaw = mathAngleBetweenPoints2D(sp88, sp80, sp94, sp8C);
                        gCamPathFlags |= 0x20;
                        gCamPathFramesLeft = 0;
                        ((CamActor *)gCamPathLookActor)->unk168 = saved;
                    }
                    total += CAM_PATH_LISTS->unkD0[path].unk8[i];
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
    return D_807444EC == 1 || (D_8076A0B1 & 0x10) != 0;
}

u8 func_8061CB80(void) {
    return (gCamPathFlags & 4) != 0;
}

extern s16 gCamPathStartIndex;

u8 camIsPlayingPath(u8 arg0) {
    return D_807444EC == 1 && arg0 == gCamPathStartIndex;
}

void camLoadPathPoint();

void camRestartPath(void) {
    gCamPathIndex = gCamPathStartIndex;
    gCamPathStep = 0;
    camLoadPathPoint();
}

extern CamActor *gCamActor;

u8 func_8061CC00(void) {
    CamState *s = gCamActor->unk174;
    return s->unkF3 == 3 || s->unkF3 == 0xB;
}

extern u8 gCamPathLengthRequested;

void camRequestPathLength(void) {
    gCamPathLengthRequested = 1;
}

extern CamPathData gCamGlobalPaths;
extern CamPathData gCamMapPaths;
extern void *gCamPathActor;
extern Actor *D_807FBB44;
extern u8 gCamPathLoopCount;
extern s16 gCamPathFrameCount;
extern u8 D_80770DC9;
extern u8 D_807F5CF6;
extern u8 D_8074E77C[];
extern u8 gCamCueIndex;
typedef struct CamPlayerStateClear {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
} CamPlayerStateClear;
extern CamPlayerStateClear *D_807FD580;

s32 actorSpawn(s32, s32);
void func_80029140(s16 *);
void currentActorClearFlag(void);
s16 camPathGetLength(s16);
void setRandomSeed(s32);
s32 func_8070B318(void);

u16 camStartPath(void *arg0, s16 arg1, u8 arg2) {
    u16 ret = 0;

    if (D_807444EC == 1 && (gCamPathFlags & 0x80)) {
        return 0;
    }
    if ((arg2 & 4) && D_8076A0A8 != 0) {
        gCamActivePaths = &gCamGlobalPaths;
    } else {
        gCamActivePaths = &gCamMapPaths;
    }
    if (actorSpawn(0xAD, 0) != 0) {
        gCamPathActor = D_807FBB44;
        D_807FBB44->unk144 = 1;
    } else {
        return 0;
    }
    if (!(arg2 & 4)) {
        if (D_807FBB64 & 1) {
            func_80029140(&arg1);
        }
    }
    if (arg0 != NULL) {
        gCamPathLookActor = arg0;
    } else {
        gCamPathLookActor = *(void **)((u8 *)D_807FC924 + 4);
    }
    D_807444EC = 1;
    if (!(arg2 & 8)) {
        D_8076A0B1 |= 0x10;
        D_8076A0B3 = 0;
    }
    gCamPathLastTime = osGetTime();
    gCamPathIndex = arg1;
    gCamPathStartIndex = arg1;
    gCamPathFlags = arg2;
    gCamPathLookNode = 0;
    gCamPathLoopCount = 0;
    gCamRollFramesLeft = 0;
    gCamPathFramesLeft = 0;
    gCamPathStep = 0;
    gCamPathNode = 0;
    gCamPathLookAhead = 0;
    gCamPathFrameCount = 0;
    D_807F5CF6 = D_80770DC9;
    D_807FBB60 |= 0x2000;
    D_807FBB60 &= ~0x1001;
    D_807FBB4C->unkB8 = 0.0f;
    if (D_8074E77C[0] == 7) {
        D_807FBB4C->unkC0 = 0.0f;
    }
    D_807FBB4C->unk60 |= 0x400;
    D_807FD580->unk10 = 0;
    gCamActor->unkE4 = 0;
    currentActorClearFlag();
    if (gCamPathLengthRequested != 0) {
        ret = camPathGetLength(arg1);
    }
    gCamPathLengthRequested = 0;
    if (arg1 == 0 && D_8076A0A8 == 0x99) {
        setRandomSeed(0x8E32B6F7);
        gCamCueStartTime = osGetTime();
        gCamCueIndex = 0;
    } else if (func_8070B318() == 0) {
        gCamCueStartTime = 0;
    }
    return ret;
}

void camGetPathStartPose(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3) {
    if (gCamPathFlags & 0x20) {
        *arg0 = gCamPathStartX;
        *arg1 = gCamPathStartY;
        *arg2 = gCamPathStartZ;
        *arg3 = gCamPathStartYaw;
        gCamPathFlags &= 0xFFDF;
    }
}

void camSetPathLookAhead(s16 arg0) {
    gCamPathLookAhead = arg0;
}

typedef struct CamPlayerRecActorPtr {
    /* 0x0 */ u8 pad0[4];
    /* 0x4 */ void *unk4;
} CamPlayerRecActorPtr;

void camSetPathLookActor(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        gCamPathLookActor = arg0;
    } else {
        gCamPathLookActor = ((CamPlayerRecActorPtr *)D_807FC924)->unk4;
    }
    gCamPathLookNode = arg1;
}

typedef struct CamFollowState CamFollowState;

typedef struct CamFollowActor {
    /* 0x000 */ u8 pad0[0x7C];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x14];
    /* 0x09C */ f32 unk9C;
    /* 0x0A0 */ u8 padA0[4];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ f32 unkA8;
    /* 0x0AC */ u8 padAC[8];
    /* 0x0B4 */ f32 unkB4;
    /* 0x0B8 */ u8 padB8[0x2C];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[0x6C];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x1F];
    /* 0x174 */ CamFollowState *unk174;
} CamFollowActor;

struct CamFollowState {
    /* 0x00 */ CamFollowActor *unk0;
    /* 0x04 */ void *unk4;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[0x5C];
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ u8 pad74[0x10];
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ u8 pad90[4];
    /* 0x94 */ f32 unk94;
    /* 0x98 */ f32 unk98;
    /* 0x9C */ u8 pad9C[4];
    /* 0xA0 */ f32 unkA0;
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ u8 padA8[4];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ u8 padB4[4];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x20];
    /* 0xDC */ f32 unkDC;
    /* 0xE0 */ u8 padE0[0xE];
    /* 0xEE */ u8 unkEE;
    /* 0xEF */ u8 unkEF;
    /* 0xF0 */ u8 unkF0;
    /* 0xF1 */ u8 unkF1;
    /* 0xF2 */ u8 padF2;
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4[7];
    /* 0xFB */ u8 unkFB;
};

void camClearActorRefs(void *arg0) {
    CamFollowState *cam = ((CamFollowActor *)gCamActor)->unk174;

    if (arg0 == gCamPathLookActor) {
        camSetPathLookActor(NULL, 0);
    }
    if (arg0 == cam->unk4) {
        cam->unk4 = NULL;
        cam->unkAC &= ~0x10004;
    }
    if (arg0 == cam->unk0) {
        cam->unk0 = (CamFollowActor *)D_807FBB4C;
    }
}

void func_8061D058(void) {
}

void camUpdateFollowHeight(CamFollowState *cam) {
    CamFollowActor *actor = cam->unk0;
    f32 temp;

    if (actor->unkA4 != cam->unk70) {
        if (cam->unkAC & 0x100) {
            temp = actor->unk80;
            cam->unk6C = temp;
            cam->unk70 = temp;
            D_807FBB60 |= 0x2000;
        } else if (actor->unk154 == 0x59) {
            cam->unk70 = actor->unkA8;
        } else {
            cam->unk70 = actor->unkA4;
        }
    }
    switch (actor->unk154) {
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
            if (cam->unk70 < cam->unk6C && actor->unk9C - actor->unk80 > 50.0f) {
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

void func_8061D1FC(CamFollowActor *arg0) {
    CamFollowState *cam = arg0->unk174;
    f32 target = D_807FD63F[cam->unkFB * 0x34] * 0.5;
    s32 sel;

    if (!(cam->unkAC & 0x2000) && !(D_807FBB64 & 0x40)) {
        if (cam->unk8 != 0 && cam->unk8 < 0x9B && cam->unkEF != 0) {
            if (cam->unkA == 0 || cam->unkA >= 0x9B) {
                cam->unkF0 = cam->unkEE;
            }
            camSetZoomLevel((CamActor *)arg0, 1);
            cam->unkAC |= 8;
        } else if (cam->unkA != 0 && cam->unkA < 0x9B) {
            if (cam->unkEF != 0) {
                if (cam->unkF0 != 0) {
                    sel = cam->unkF0;
                    if (cam->unkEF != sel) {
                        camSetZoomLevel((CamActor *)arg0, (s16)sel);
                    }
                }
                cam->unkAC &= ~8;
            }
        }
    }
    cam->unk98 = cam->unk98 + (((target > 20.0f) ? target : ((target < -20.0f) ? target : 0.0f)) - cam->unk98) * 0.05;
    cam->unkA0 = cam->unkA0 + (cam->unkA4 - cam->unkA0) * 0.2;
    if (cam->unkAC & 0x10) {
        arg0->unkB4 = arg0->unkB4 + (300.0f - arg0->unkB4) * 0.2;
    } else {
        arg0->unkB4 = arg0->unkB4 + (cam->unkB8 - arg0->unkB4) * 0.2;
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

extern s32 D_8076A068;

void actorDespawn(void *);
void sfxSetMode();
void timerQueuePurgeFlagged(void);

void camEndPath(CamFollowActor *arg0) {
    CamFollowState *cam = arg0->unk174;

    if (D_807444EC == 1) {
        if (gCamPathFlags & 4) {
            gCamActivePaths = &gCamMapPaths;
        }
        sfxSetMode(0);
        D_807444EC = 0;
        D_8076A0B1 &= 0xFFEF;
        if (!(gCamPathFlags & 8)) {
            D_8076A0B3 = 0xFF;
        }
        actorDespawn(gCamPathActor);
        D_807FBB60 |= 0x1000;
        cam->unkAC |= 0x40000;
        cam->unkC = -32768.0f;
        if (gCamPathFlags & 1) {
            D_807FBB60 |= 0x2000;
            func_8061B5C4(cam->unkFB);
        }
        D_807FC924[cam->unkFB].unk27C = 45.0f;
        arg0->unkE4 = 0;
        D_80770DC9 = D_807F5CF6;
        D_8076A068 += 0x1869F;
        timerQueuePurgeFlagged();
        D_8076A068 += 0xFFFE7961;
        gCamPathFlags = 0;
        gCamPathTimeDelta = 0;
        D_807FBB4C->unk60 &= ~0x400;
    }
}

f32 func_80611BB4(f32, f32);

void func_8061D6A8(CamFollowState *cam) {
    CamFollowActor *actor = cam->unk0;
    f32 yaw;

    gCamTargetDist = sqrtf((cam->unk8C - actor->unk84) * (cam->unk8C - actor->unk84) +
                       (cam->unk84 - actor->unk7C) * (cam->unk84 - actor->unk7C));
    D_807476AC = sqrtf(
        (cam->unk84 - (actor->unk7C + cam->unk94 * func_80612794(actor->unkE6))) *
            (cam->unk84 - (actor->unk7C + cam->unk94 * func_80612794(actor->unkE6))) +
        (cam->unk8C - (actor->unk84 + cam->unk94 * func_80612790(actor->unkE6))) *
            (cam->unk8C - (actor->unk84 + func_80612790(actor->unkE6) * cam->unk94)));
    D_807476B0 = func_80611BB4(actor->unk80 - cam->unk88,
                               sqrtf((cam->unk0->unk84 - cam->unk8C) * (cam->unk0->unk84 - cam->unk8C) +
                                     (actor->unk7C - cam->unk84) * (actor->unk7C - cam->unk84)));
    yaw = func_80611BB4(cam->unk6C - cam->unk88,
                        sqrtf((actor->unk84 - cam->unk8C) * (actor->unk84 - cam->unk8C) +
                              (actor->unk7C - cam->unk84) * (actor->unk7C - cam->unk84)));
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


void func_806F3DB0(void);

typedef struct CamPathStepListRaw {
    /* 0x0 */ u8 pad0[4];
    /* 0x4 */ s16 *unk4;
    /* 0x8 */ s16 *unk8;
} CamPathStepListRaw;

void camLoadPathPoint(void) {
    ((CamActor *)gCamPathActor)->unk168 = 0;
    ((CamActor *)gCamPathActor)->unk160 = 0.0;
    gCamPathNode = gCamActivePaths->unkD0[gCamPathIndex].unk4[gCamPathStep];
    gCamPathFramesLeft = ((CamPathStepListRaw *)&gCamActivePaths->unkD0[gCamPathIndex])->unk8[gCamPathStep];
    func_806F3DB0();
}

void camSetPath(u8 arg0) {
    gCamPathIndex = arg0;
    gCamPathStep = 0;
    camLoadPathPoint();
}

extern u16 gCamPathLoopStep;
extern u8 D_8076AEE0;
extern f32 gScreenFadeRate;

void camResumePath(void);

void camLoopPathStep(u8 arg0, u8 arg1) {
    if (gCamPathLoopCount != 0) {
        gCamPathLoopCount--;
        if (gCamPathLoopCount != 0) {
            gCamPathStep = gCamPathLoopStep;
            camLoadPathPoint();
        }
    } else {
        gCamPathLoopCount = arg1;
        gCamPathLoopStep = arg0;
        gCamPathStep = arg0;
        camLoadPathPoint();
    }
}

void func_8061D9EC(s32 arg0, s32 arg1, s32 arg2) {
    D_8076AEE0 = 0;
    gScreenFadeRate = -0.8f;
}

void timerQueueAdd(void *, s32, s32, s32, s32);

void func_8061DA14(s32 arg0, s32 arg1, s32 arg2) {
    D_8076A0B1 |= 0x40;
    D_8076AEE0 = 0;
    gScreenFadeRate = 0.8f;
    timerQueueAdd(func_8061D9EC, 0x8000003C, 0, 0, 0);
}

void camResumePathCallback(s32 arg0, s32 arg1, s32 arg2) {
    camResumePath();
}

extern s16 gCamRollStart;
extern s16 gCamRollEnd;
extern s16 gCamRollFrames;

void camSetRollBlend(s16 arg0, s16 arg1, u16 arg2) {
    gCamRollFramesLeft = arg2;
    gCamRollFrames = arg2;
    gCamRollStart = arg0 * 4096 / 360;
    gCamRollEnd = arg1 * 4096 / 360;
}

typedef struct CamResetState {
    /* 0x00 */ CamActor *unk0;
    /* 0x04 */ u8 pad4[8];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[0x50];
    /* 0x60 */ f32 unk60;
    /* 0x64 */ u8 pad64[8];
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ u8 pad74[0x2A];
    /* 0x9E */ s16 unk9E;
    /* 0xA0 */ f32 unkA0;
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ u8 padA8[4];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ u8 padB4[4];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x2C];
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ s16 unkEA;
    /* 0xEC */ u8 padEC[2];
    /* 0xEE */ u8 unkEE;
    /* 0xEF */ u8 unkEF;
    /* 0xF0 */ u8 padF0[3];
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4;
    /* 0xF5 */ u8 unkF5;
    /* 0xF6 */ u8 unkF6;
    /* 0xF7 */ u8 padF7[4];
    /* 0xFB */ u8 unkFB;
} CamResetState;


void camSnapBehindTarget(CamActor *arg0) {
    CamResetState *cam = (CamResetState *)arg0->unk174;

    camFindClearYaw(arg0, -1.0f, cam->unk0->unkE6, 0);
    cam->unkF5 = 0xF;
    cam->unkF6 = 0xF;
    D_807FBB60 &= ~0x2000;
    cam->unkAC &= ~0x100000;
}

typedef struct CamUpdateTarget {
    /* 0x00 */ u8 pad0[0x60];
    /* 0x60 */ s32 unk60;
    /* 0x64 */ u8 pad64[0x18];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x1C];
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ u8 padA8[4];
    /* 0xAC */ f32 unkAC;
    /* 0xB0 */ u8 padB0[4];
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ u8 padB8[0x2E];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ u8 padEA[0x6A];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[8];
    /* 0x15E */ u8 unk15E;
} CamUpdateTarget;

typedef struct CamUpdateState {
    /* 0x00 */ CamUpdateTarget *unk0;
    /* 0x04 */ u8 pad4[0xC];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[0x26];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ u8 pad44[0x28];
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ u8 pad74[4];
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ u8 pad90[4];
    /* 0x94 */ f32 unk94;
    /* 0x98 */ u8 pad98[6];
    /* 0x9E */ s16 unk9E;
    /* 0xA0 */ f32 unkA0;
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ u8 padA8[4];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ u8 padB0[2];
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ u8 padB4[4];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ s32 unkC0;
    /* 0xC4 */ u8 padC4[8];
    /* 0xCC */ f32 unkCC;
    /* 0xD0 */ f32 unkD0;
    /* 0xD4 */ f32 unkD4;
    /* 0xD8 */ f32 unkD8;
    /* 0xDC */ f32 unkDC;
    /* 0xE0 */ f32 unkE0;
    /* 0xE4 */ u8 padE4[0xD];
    /* 0xF1 */ u8 unkF1;
    /* 0xF2 */ u8 unkF2;
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4;
    /* 0xF5 */ u8 unkF5;
    /* 0xF6 */ u8 unkF6;
    /* 0xF7 */ u8 unkF7;
} CamUpdateState;

typedef struct CamUpdateCam {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x2C];
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ u8 padB8[0x2C];
    /* 0xE4 */ s16 unkE4;
    /* 0xE6 */ u8 padE6[2];
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ u8 padEA[2];
    /* 0xEC */ s16 unkEC;
    /* 0xEE */ u8 padEE[0x86];
    /* 0x174 */ CamUpdateState *unk174;
} CamUpdateCam;

typedef struct CamPathStepListU16 {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ s16 *unk4;
    /* 0x8 */ u16 *unk8;
} CamPathStepListU16; // size = 0xC

typedef struct CamPlayerStateCheck {
    /* 0x00 */ u8 pad0[0xBC];
    /* 0xBC */ s16 unkBC;
} CamPlayerStateCheck;

struct CamResetCam;
struct CamEyeActor;
extern u32 D_80744478;

s16 func_806CC190(s16, s16, f32);
s32 func_807142D8(void);
void sfxAllocateChannel(u16, f32);
void sfxStartAreaAmbient(void);
void func_80627F04(s32, s32, s32);
void camPolarFromPoints(f32 *, f32 *, f32, f32, f32, f32, f32, f32);
void camUpdateFollow(struct CamEyeActor *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
void camUpdateFocusPos(struct CamEyeActor *, f32, f32 *, f32 *, f32 *);
f32 cosApprox(f32);

#define CAM_UPDATE_CAM ((CamUpdateCam *)arg0)
#define CAM_PATH_NODE (gCamActivePaths->unkD8[gCamPathNode])
#define CAM_PATH_NODE_WORD(i) (((s32 *)&CAM_PATH_NODE.u)[i])
#define CAM_PATH_STEP_LIST (((CamPathStepListU16 *)gCamActivePaths->unkD0)[gCamPathIndex])

void camUpdate(struct CamResetCam *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6, f32 *arg7,
                   f32 *arg8, f32 *arg9) {
    CamUpdateState *st = CAM_UPDATE_CAM->unk174;
    s32 done;
    s32 *w;
    u16 t0;
    CamUpdateTarget *X = st->unk0;
    f32 len;
    u64 now;
    f32 sp84;
    f32 sp80;
    f32 fs;

    D_807F5CD0 = X->unkAC - X->unkA4;
    st->unk9E = func_806CC190(st->unk9E, X->unkE6, 4.0f);
    if ((X->unk60 & 0x200) && !(st->unkAC & 0x100)) {
        actorGetNodePos(X, 8, &st->unkD8, &st->unkDC, &st->unkE0);
    } else {
        st->unkD8 = X->unk7C;
        st->unkDC = X->unk80;
        st->unkE0 = X->unk84;
    }
    len = sqrtf((X->unk84 - st->unkD4) * (X->unk84 - st->unkD4) +
                ((X->unk7C - st->unkCC) * (X->unk7C - st->unkCC) + (X->unk80 - st->unkD0) * (X->unk80 - st->unkD0)));
    st->unk10 = (len * 40.0f) * (D_80744478 * 0.5);
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
    camUpdateFollowHeight((CamFollowState *)st);
    func_8061D1FC((CamFollowActor *)arg0);
    CAM_UPDATE_CAM->unkE8 = func_806CC190(CAM_UPDATE_CAM->unkE8, X->unkE8, 20.0f);
    camUpdatePlayerYaw((CamStateViewAngle *)st);
    switch (D_807444EC) {
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
            if (X->unk154 == 0x54 && X->unk155 < 3) {
                return;
            }
            if (X->unk154 == 0x52 && X->unk155 < 8) {
                return;
            }
            if (X->unk154 == 0x53 && X->unk155 < 3) {
                return;
            }
            if (X->unk154 == 0x42) {
                if (((CamPlayerStateCheck *)D_807FD580)->unkBC != 0x11 && ((CamPlayerStateCheck *)D_807FD580)->unkBC != 0x60 &&
                    ((CamPlayerStateCheck *)D_807FD580)->unkBC != 0x49) {
                    return;
                }
            }
            if (X->unk154 == 0x43) {
                return;
            }
        }
        func_8061D6A8((CamFollowState *)st);
        if (st->unkAC & 0x80000000) {
            camApplyFixedView((CamActor *)arg0);
        } else {
            camComputeEyeFocus((CamActor *)arg0, &CAM_UPDATE_CAM->unk7C, &CAM_UPDATE_CAM->unk80, &CAM_UPDATE_CAM->unk84, &st->unk78, &st->unk7C,
                          &st->unk80, (CamActor *)X);
            if ((D_807FBB60 & 0x2000) || (st->unkAC & 0x100000)) {
                if (st->unkAC & 0x100000) {
                    st->unkAC &= ~0x100000;
                    st->unk84 = *arg1 = CAM_UPDATE_CAM->unk7C = st->unk38;
                    st->unk88 = *arg2 = CAM_UPDATE_CAM->unk80 = st->unk3C;
                    st->unk8C = *arg3 = CAM_UPDATE_CAM->unk84 = st->unk40;
                    sfxStartAreaAmbient();
                } else {
                    st->unk84 = *arg1 = CAM_UPDATE_CAM->unk7C;
                    st->unk88 = *arg2 = CAM_UPDATE_CAM->unk80;
                    st->unk8C = *arg3 = CAM_UPDATE_CAM->unk84;
                }
                *arg4 = st->unk78;
                *arg5 = st->unk7C;
                *arg6 = st->unk80;
                D_807FBB60 ^= 0x2000;
            } else {
                camUpdateFollow((struct CamEyeActor *)arg0, arg1, arg2, arg3, arg4, arg5, arg6);
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
        camSampleFloorHeight((CamActor *)arg0, (CamState *)st, *arg1, *arg3);
        if (gCamPathFlags & 0x40) {
            camApplySway((CamState *)st, arg1, arg2, arg3, 0.2f, 0.1f, 50.0f, 40.0f);
        } else {
            if (gCamRollFramesLeft != 0) {
                gCamRollFramesLeft--;
                len = (f32)gCamRollFramesLeft / (f32)gCamRollFrames;
                CAM_UPDATE_CAM->unkE4 = gCamRollEnd + (gCamRollStart - gCamRollEnd) * len;
            }
            gCamPathFrameCount++;
            do {
                done = 0;
                if (gCamPathFramesLeft == 0) {
                    camLoadPathPoint();
                    gCamPathStep++;
                    if (CAM_PATH_STEP_LIST.unk0 < gCamPathStep) {
                        if (gCamPathFlags & 0x10) {
                            if (!(D_807FBB4C->unk6A & 0x100)) {
                                D_807FBB4C->unk6A |= 0x100;
                            }
                        } else {
                            camEndPath((CamFollowActor *)arg0);
                        }
                    } else {
                        t0 = CAM_PATH_STEP_LIST.unk8[gCamPathStep - 1];
                        w = (s32 *)&CAM_PATH_NODE.u;
                        switch (CAM_PATH_NODE.unk1) {
                            case 10:
                            case 15:
                            case 16:
                            case 17:
                                D_807FBB60 |= 0x2000;
                                break;
                            case 12:
                                sfxAllocateChannel(*(u16 *)w, 1.0f);
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
                                camEndPath((CamFollowActor *)arg0);
                                st->unkAC &= ~0x40000;
                                if (st->unkF3 != 0xB && st->unkF3 != 3) {
                                    st->unk6C = st->unk70 = D_807FBB4C->unk80;
                                    len = sqrtf((*arg1 - D_807FBB4C->unk7C) * (*arg1 - D_807FBB4C->unk7C) +
                                                (*arg3 - D_807FBB4C->unk84) * (*arg3 - D_807FBB4C->unk84));
                                    st->unkA4 = st->unkA0 = len;
                                    st->unkB2 = mathAngleBetweenPoints2D(D_807FBB4C->unk7C, D_807FBB4C->unk84, *arg1, *arg3);
                                    CAM_UPDATE_CAM->unkB4 = st->unkB8 = *arg2 - D_807FBB4C->unk80;
                                    st->unk84 = *arg1;
                                    st->unk88 = *arg2;
                                    st->unk8C = *arg3;
                                    *arg4 = *arg1 + (*arg4 - *arg1) * 0.1;
                                    *arg5 = *arg2 + (*arg5 - *arg2) * 0.1;
                                    *arg6 = *arg3 + (*arg6 - *arg3) * 0.1;
                                    st->unk78 = *arg4;
                                    st->unk7C = *arg5;
                                    st->unk80 = *arg6;
                                    if (D_807FBB64 & 1) {
                                        camSetZoomLevel((CamActor *)arg0, 2);
                                    } else {
                                        camSetZoomForDistance((CamActor *)arg0, (s16)st->unkA0);
                                    }
                                    st->unk94 = st->unkA0 / 3.0;
                                    camStartBlendRamp((CamState *)st, 0x1E);
                                    st->unkF3 = 1;
                                    D_807FBB60 &= ~0x2000;
                                    func_8061D6A8((CamFollowState *)st);
                                }
                                break;
                            case 14:
                                timerQueueAdd(func_8061DA14, t0 + 0x80000000, 0, 0, 0);
                                camLoadPathPoint();
                                gCamPathFramesLeft = 0;
                                done = 1;
                                break;
                            case 13:
                                if (t0 != 0) {
                                    timerQueueAdd(func_80627F04, t0 + 0x80000000, w[0], w[1], w[2]);
                                } else {
                                    func_80627F04(w[0], w[1], w[2]);
                                }
                                camLoadPathPoint();
                                gCamPathFramesLeft = 0;
                                done = 1;
                                break;
                            case 6:
                                gCamPathLookAhead = t0;
                                camLoadPathPoint();
                                gCamPathFramesLeft = 0;
                                done = 1;
                                break;
                        }
                    }
                }
            } while (done != 0);
            if (D_807444EC != 0) {
                D_807F5CFC = ((s16 *)CAM_PATH_STEP_LIST.unk8)[gCamPathStep - 1];
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
                        ((CamUpdateTarget *)gCamPathActor)->unk7C = ((CamUpdateTarget *)gCamPathLookActor)->unk7C;
                        ((CamUpdateTarget *)gCamPathActor)->unk80 = ((CamUpdateTarget *)gCamPathLookActor)->unk80;
                        ((CamUpdateTarget *)gCamPathActor)->unk84 = ((CamUpdateTarget *)gCamPathLookActor)->unk84;
                        if (((CamUpdateTarget *)gCamPathLookActor)->unk15E >= 0x15) {
                            ((CamUpdateTarget *)gCamPathActor)->unk15E = 0x14;
                        } else {
                            ((CamUpdateTarget *)gCamPathActor)->unk15E = ((CamUpdateTarget *)gCamPathLookActor)->unk15E;
                        }
                        ((CamUpdateTarget *)gCamPathActor)->unkE6 = ((CamUpdateTarget *)gCamPathLookActor)->unkE6;
                        camComputeEyeFocus((CamActor *)arg0, arg1, arg2, arg3, &st->unk78, &st->unk7C, &st->unk80,
                                      (CamActor *)gCamPathActor);
                        *arg4 = st->unk78;
                        *arg5 = st->unk7C;
                        *arg6 = st->unk80;
                        break;
                    case 8:
                    case 12:
                        break;
                    default:
                        gCamFocusBlendRate = 0.3f;
                        camComputeEyeFocus((CamActor *)arg0, arg1, arg2, arg3, &st->unk78, &st->unk7C, &st->unk80,
                                      (CamActor *)gCamPathLookActor);
                        if (CAM_PATH_NODE.unk1 != 7 && CAM_PATH_NODE.unk1 != 0xF && CAM_PATH_NODE.unk1 != 0x11) {
                            camUpdateFocusPos((struct CamEyeActor *)arg0, (0.0f != ((CamUpdateTarget *)gCamPathLookActor)->unkB4) ? 0.3 : 0.1, arg4, arg5, arg6);
                        }
                        if ((D_807FBB60 & 0x2000) || CAM_PATH_NODE.unk1 == 7 || CAM_PATH_NODE.unk1 == 0xF ||
                            CAM_PATH_NODE.unk1 == 0x11) {
                            D_807FBB60 &= ~0x2000;
                            *arg4 = st->unk78;
                            *arg5 = st->unk7C;
                            *arg6 = st->unk80;
                        }
                        break;
                }
                if (st->unkF2 != 0) {
                    camApplyShake((CamState *)st, arg1, arg2, arg3, st->unkC0, 0);
                }
            }
        }
    }
    st->unkAC &= 0x7FFDAF0F;
    if (D_807FBB64 & 0x8000) {
        st->unkAC |= 4;
    } else if (!(st->unkAC & 0x10000)) {
        st->unkAC &= ~4;
    }
    if (st->unkF2 != 0) {
        camApplyShake((CamState *)st, arg4, arg5, arg6, (s32)(st->unkC0 * 0.333), 1);
    }
    if (!(st->unkAC & 0x100)) {
        camPolarFromPoints(&sp84, &sp80, *arg4, *arg5, *arg6, *arg1, *arg2, *arg3);
        fs = cosApprox(sp80);
        *arg8 = func_80612790(CAM_UPDATE_CAM->unkE4);
        *arg7 = func_80612794(CAM_UPDATE_CAM->unkE4) * cosApprox(sp84) * fs;
        *arg9 = func_80612794(CAM_UPDATE_CAM->unkE4) * sinApprox(sp84) * fs;
        CAM_UPDATE_CAM->unkEC = CAM_UPDATE_CAM->unkE4;
    }
    st->unkCC = X->unk7C;
    st->unkD0 = X->unk80;
    st->unkD4 = X->unk84;
}

typedef struct CamPlayerRecEntry {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 pad1[3];
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ u8 pad8[0x2E8];
} CamPlayerRecEntry;

void camResetPlayer(Actor *, u8);

void camResetAllPlayers(void) {
    u8 i;

    for (i = 0; i < D_807FC928; i++) {
        if (((CamPlayerRecEntry *)D_807FC924)[i].unk0) {
            camResetPlayer(((CamPlayerRecEntry *)D_807FC924)[i].unk4, i);
        }
    }
}


typedef struct CamResetCam {
    /* 0x00 */ u8 pad0[0x88];
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 pad94[0x20];
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ u8 padB8[0xA7];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ u8 pad160[0x14];
    /* 0x174 */ CamResetState *unk174;
} CamResetCam;

typedef struct CamPlayerCamLink {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ CamResetCam *unk104;
} CamPlayerCamLink;

typedef struct CamPlayerRecUp {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0xC];
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ u8 pad234[0xC];
    /* 0x240 */ f32 unk240;
    /* 0x244 */ f32 unk244;
    /* 0x248 */ f32 unk248;
    /* 0x24C */ u8 pad24C[0xA4];
} CamPlayerRecUp;

void camUpdate(CamResetCam *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
s16 mapChunkFindByPosition(f32, f32, f32, s32);

#define CAM_PLAYER_REC(i) ((CamPlayerRecUp *)&D_807FC924[i])

void camResetPlayer(Actor *arg0, u8 arg1) {
    CamPlayerCamLink *ps = arg0->unk174;
    CamResetState *st = ps->unk104->unk174;
    CamResetCam *cam = ps->unk104;

    gCamActivePaths = &gCamMapPaths;
    st->unk0 = (CamActor *)arg0;
    st->unkFB = arg1;
    st->unk60 = 5.0f;
    if (D_807444EC == 1) {
        camEndPath((CamFollowActor *)cam);
    }
    if (cam->unk15F != 0) {
        st->unkB2 = (cam->unk15F / 255.0) * 4095.0;
    } else {
        st->unkB2 = (f64)arg0->unkE6;
    }
    cam->unk15F = 0;
    D_807FBB60 |= 0x2000;
    st->unkF3 = 1;
    st->unk9E = arg0->unkE6;
    camSetZoomLevel((CamActor *)cam, (s16)(D_8076A0A8 == 0x9A ? 1 : ((D_807FBB64 & 1) ? 3 : 2)));
    st->unkEE = st->unkEF;
    st->unkA0 = st->unkA4;
    cam->unkB4 = st->unkB8;
    st->unkE8 = 0;
    st->unkEA = st->unkE8;
    st->unkAC |= 0x100;
    st->unkB0 = 0;
    st->unk6C = 123456.0f;
    st->unk70 = 123456.0f;
    st->unkC = -32768.0f;
    *(s16 *)arg0->unk12C = mapChunkFindByPosition(arg0->unk7C, arg0->unk80, arg0->unk84, 0);
    camUpdate(cam, &CAM_PLAYER_REC(arg1)->unk210, &CAM_PLAYER_REC(arg1)->unk214, &CAM_PLAYER_REC(arg1)->unk218,
                  &CAM_PLAYER_REC(arg1)->unk228, &CAM_PLAYER_REC(arg1)->unk22C, &CAM_PLAYER_REC(arg1)->unk230,
                  &CAM_PLAYER_REC(arg1)->unk240, &CAM_PLAYER_REC(arg1)->unk244, &CAM_PLAYER_REC(arg1)->unk248);
    st->unkAC &= ~0x100;
    cam->unk88 = ((CamPlayerRecUp *)D_807FC924)[arg1].unk210;
    cam->unk8C = ((CamPlayerRecUp *)D_807FC924)[arg1].unk214;
    cam->unk90 = ((CamPlayerRecUp *)D_807FC924)[arg1].unk218;
}

s32 randomNonNegative(void);

void camApplyShake(CamState *arg0, f32 *arg1, f32 *arg2, f32 *arg3, s32 arg4, s32 arg5) {
    s32 r = randomNonNegative();

    if (arg4 == 0) {
        arg4 = 1;
    }
    *arg1 = *arg1 + (f64)((r % arg4) - (arg4 >> 1)) * 0.01;
    *arg2 = *arg2 + (f64)(((r / 100) % arg4) - (arg4 >> 1)) * 0.01;
    *arg3 = *arg3 + (f64)(((r / 10000) % arg4) - (arg4 >> 1)) * 0.01;
    if ((u8)arg5) {
        arg0->unkF2--;
        arg0->unkC0 = arg0->unkC0 - arg0->unkC0 * 0.111;
        arg0->unkC0++;
    }
}

void camStartShake(CamActor *, u8, u16);

void camStartShakeFromPoint(CamActor *arg0, u8 arg1, u16 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 dx = arg3 - arg0->unk7C;
    f32 dy = arg4 - arg0->unk80;
    f32 dz = arg5 - arg0->unk84;
    f32 dist = sqrtf(dx * dx + dy * dy + dz * dz);

    if (!(arg7 < dist)) {
        if (dist < arg6) {
            camStartShake(arg0, arg1, arg2);
        } else {
            camStartShake(arg0, arg1, (u16)(arg2 * ((arg7 - dist) / (arg7 - arg6))));
        }
    }
}

void func_8060E7EC(u8, u8, s32);

void camStartShake(CamActor *arg0, u8 arg1, u16 arg2) {
    CamState *cam;

    cam = arg0->unk174;
    if (D_807444EC == 1) {
        arg2 = (u32)arg2 >> 2;
    }
    if (arg1 >= cam->unkF2) {
        cam->unkF2 = arg1;
    }
    if (arg2 * 100 >= cam->unkC0) {
        cam->unkC0 = arg2 * 100;
    }
    func_8060E7EC(cam->unkFB, (arg2 * 9 >= 0x100) ? 0xFF : arg2 * 9, arg1 + 1);
}

typedef struct CamStateBlendRamp {
    /* 0x00 */ u8 pad0[0xE8];
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ s16 unkEA;
} CamStateBlendRamp;

void camStartBlendRamp(arg0, arg1) CamState *arg0; s16 arg1; {
    if (arg1 >= 0xB) {
        ((CamStateBlendRamp *)arg0)->unkE8 = arg1;
        ((CamStateBlendRamp *)arg0)->unkEA = ((CamStateBlendRamp *)arg0)->unkE8;
    }
}

s16 mathAngleDistance(s16, s16);

typedef struct CamActorEyePos {
    /* 0x00 */ u8 pad0[0x88];
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ f32 unk90;
} CamActorEyePos;

typedef struct CamStateTarget {
    /* 0x00 */ CamActor *unk0;
} CamStateTarget;

void func_8061F18C(CamActor *arg0, f32 arg1, f32 arg2, f32 arg3) {
    CamStateTarget *cam;
    s16 ang;
    s16 pad;
    s16 diff;
    s16 pad2;
    f32 dist;
    f64 r;

    cam = (CamStateTarget *)arg0->unk174;
    ang = mathAngleBetweenPoints2D(cam->unk0->unk7C, cam->unk0->unk84, arg1, arg3);
    diff = mathAngleDistance(ang, mathAngleBetweenPoints2D(cam->unk0->unk7C, cam->unk0->unk84, ((CamActorEyePos *)arg0)->unk88, ((CamActorEyePos *)arg0)->unk90));
    dist = sqrtf((arg1 - ((CamActorEyePos *)arg0)->unk88) * (arg1 - ((CamActorEyePos *)arg0)->unk88)
               + (arg2 - ((CamActorEyePos *)arg0)->unk8C) * (arg2 - ((CamActorEyePos *)arg0)->unk8C)
               + (arg3 - ((CamActorEyePos *)arg0)->unk90) * (arg3 - ((CamActorEyePos *)arg0)->unk90));
    r = diff * 0.0009765625;
    camStartBlendRamp((CamState *)cam, (s16)((r < 1.0 ? 1.0 : r) * dist));
}

void camClosestPointOnSegment(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 *arg9, f32 *argA, f32 *argB) {
    f32 distQ;
    f32 distP;
    f32 len2;
    f32 t;

    len2 = (arg3 - arg6) * (arg3 - arg6) + (arg4 - arg7) * (arg4 - arg7) + (arg5 - arg8) * (arg5 - arg8);
    if (len2 == 0.0f) {
        *arg9 = arg3;
        *argA = arg4;
        *argB = arg5;
        return;
    }
    distQ = (arg6 - arg0) * (arg6 - arg0) + (arg7 - arg1) * (arg7 - arg1) + (arg8 - arg2) * (arg8 - arg2);
    distP = (arg3 - arg0) * (arg3 - arg0) + (arg4 - arg1) * (arg4 - arg1) + (arg5 - arg2) * (arg5 - arg2);
    t = (distP + len2 - distQ) / (2 * len2);
    if (t >= 1.0f || distQ == 0.0f) {
        *arg9 = arg6;
        *argA = arg7;
        *argB = arg8;
    } else if (t <= 0.0f || distP == 0.0f) {
        *arg9 = arg3;
        *argA = arg4;
        *argB = arg5;
    } else {
        *arg9 = (arg6 - arg3) * t + arg3;
        *argA = (arg7 - arg4) * t + arg4;
        *argB = (arg8 - arg5) * t + arg5;
    }
}

typedef struct CamPathZoneBytes {
    /* 0x00 */ u8 pad0[0xC4];
    /* 0xC4 */ u8 *unkC4;
} CamPathZoneBytes;

void func_8061F4B0(u8 *arg0) {
    u8 i;
    u8 *p;
    s32 v;
    u8 *q;

    for (i = 0; i < 6; i++) {
        v = (0, arg0)[i];
        p = arg0 + i;
        if (v != 0) {
            q = ((CamPathZoneBytes *)gCamActivePaths)->unkC4 + v * 0x1C;
            q[-4] |= p[6] & 0xF;
        }
    }
}

typedef struct CamZoneEntry {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[3];
} CamZoneEntry;

extern CamZoneEntry *D_807F5BD4;

void camSetZoneWeight(u8 arg0, u8 arg1) {
    D_807F5BD4[arg0].unk18 = arg1;
}

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

typedef struct CamPathZones {
    /* 0x00 */ u8 pad0[0xC4];
    /* 0xC4 */ CamZoneEntryFull *unkC4;
    /* 0xC8 */ s8 *unkC8;
} CamPathZones;

typedef struct CamZoneVec3s {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} CamZoneVec3s;

typedef struct CamZonePair {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
} CamZonePair;

typedef struct CamZoneTargetSub {
    /* 0x000 */ u8 pad0[0x10C];
    /* 0x10C */ s8 unk10C;
} CamZoneTargetSub;

typedef struct CamZoneTarget {
    /* 0x000 */ u8 pad0[0x7C];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x5E];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[0x44];
    /* 0x12C */ s16 unk12C;
    /* 0x12E */ u8 pad12E[0x26];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x1E];
    /* 0x174 */ CamZoneTargetSub *unk174;
} CamZoneTarget;

typedef struct CamZoneState {
    /* 0x00 */ CamZoneTarget *unk0;
    /* 0x04 */ u8 pad4[0x68];
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ u8 pad70[0x34];
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ u8 padA8[4];
    /* 0xAC */ u32 unkAC;
    /* 0xB0 */ u8 padB0[2];
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ u8 padB4[4];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[8];
    /* 0xC4 */ s16 unkC4;
    /* 0xC6 */ s16 unkC6;
    /* 0xC8 */ s16 unkC8;
    /* 0xCA */ s16 unkCA;
    /* 0xCC */ u8 padCC[0x20];
    /* 0xEC */ u8 unkEC;
    /* 0xED */ u8 unkED;
    /* 0xEE */ u8 padEE[3];
    /* 0xF1 */ u8 unkF1;
    /* 0xF2 */ u8 padF2;
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4[5];
    /* 0xF9 */ u8 unkF9;
    /* 0xFA */ u8 padFA[3];
    /* 0xFD */ u8 unkFD;
} CamZoneState;

typedef struct CamZoneActor {
    /* 0x00 */ u8 pad0[0xB4];
    /* 0xB4 */ f32 unkB4;
} CamZoneActor;

extern f32 gScreenFadeProgress;
s32 camIsCellNeighbour(s16, s16);

#define CAM_ZONE_GROUP ((CamZonePair *)gCamZoneGroups)
#define CAM_ZONE_SORT ((CamZonePair *)gCamZoneSorted)
#define CAM_ZONE_PATH ((CamPathZones *)gCamActivePaths)

s32 func_8061F53C(CamActor *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
    CamZoneEntryFull *e;
    s16 ret;
    u8 type0;
    u8 spread;
    u16 rad;
    s16 padR;
    s16 weight;
    s16 i;
    f32 distSq;
    CamZoneState *st;
    CamZoneTarget *tgt;
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
    CamZoneTargetSub *sub;
    s32 ang2;
    f32 factor;
    f32 outX;
    f32 outY;
    f32 outZ;

    st = (CamZoneState *)arg0->unk174;
    tgt = st->unk0;
    sub = tgt->unk174;
    x = tgt->unk7C;
    y = tgt->unk80 + sub->unk10C;
    z = tgt->unk84;
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
                        e = &CAM_ZONE_PATH->unkC4[gCamZoneSorted[k * 2]];
                        spread = e->unk1A;
                        pos[0] = e->unk10;
                        pos[1] = e->unk12;
                        pos[2] = e->unk14;
                        rad = e->unk19 * 4;
                        mode = e->unk1B;
                        type0 = e->unk16;
                        if (e->unk16 == 5) {
                            linkId = e->unk0;
                            e = &CAM_ZONE_PATH->unkC4[e->unk0];
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
                        if (tgt->unk12C == CAM_ZONE_PATH->unkC8[gCamZoneSorted[k * 2]] || type == 8 ||
                            CAM_ZONE_PATH->unkC8[gCamZoneSorted[k * 2]] == -1) {
                            if ((mode == 2 && distSq < (f32)(rad * rad) && weight < e->unk18 && !((s16)(s32)y < pos[1]) &&
                                 pos[1] + spread * 2 >= (s16)(s32)y) ||
                                (mode != 2 && distSq < (f32)(rad * rad) && weight < e->unk18)) {
                                switch (type) {
                                    case 4:
                                        handled = 1;
                                        if (k != st->unkC6) {
                                            camReturnToFollow(arg0, (CamActor *)tgt);
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
                                            if (!((tgt->unk154 == 0x54 && tgt->unk155 >= 3) ||
                                                  (tgt->unk154 == 0x52 && tgt->unk155 >= 8) ||
                                                  (tgt->unk154 == 0x53 && tgt->unk155 >= 3))) {
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
                                            if (!(D_8076A064 & 8) && D_807FC928 == 1) {
                                                renderCallbacksRegister(renderBonusTargetMarker, arg0, 3);
                                            }
                                            break;
                                        }
                                        if (!(e->unk17 & 0x38) && D_807FC928 == 1) {
                                            renderCallbacksRegister(renderBonusTargetMarker, arg0, 3);
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
                    ang1 = mathAngleBetweenPoints2D(tgt->unk7C, tgt->unk84, *arg1, *arg3);
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
                ang0 = mathAngleBetweenPoints2D(tgt->unk7C, tgt->unk84, best->unk0, best->unk4);
                ang1 = mathAngleBetweenPoints2D(tgt->unk7C, tgt->unk84, best->unk6, best->unkA);
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
                if (tgt->unk154 != 0x20) {
                    ang1 = mathAngleBetweenPoints2D(best->unk10, best->unk14, tgt->unk7C, tgt->unk84);
                    *arg1 = best->unk10 - func_80612794(ang1) * best->unk0;
                    *arg3 = best->unk14 - func_80612790(ang1) * best->unk0;
                    *arg2 = st->unk6C + ((CamZoneActor *)arg0)->unkB4;
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
                *arg1 = best->unk0;
                *arg2 = best->unk2;
                *arg3 = best->unk4;
                st->unkC8 = best->unk6;
                st->unkCA = best->unk8;
                break;
            case 9:
                *arg1 = ((CamZoneEntryFull *)((s16 *)best + st->unkF9 * 3))->unk0;
                *arg2 = ((CamZoneEntryFull *)((s16 *)best + st->unkF9 * 3))->unk2;
                *arg3 = ((CamZoneEntryFull *)((s16 *)best + st->unkF9 * 3))->unk4;
                st->unkC8 = 0;
                st->unkCA = 0;
                break;
            case 2:
                camClosestPointOnSegment(x, y, z, best->unk0, best->unk2, best->unk4, best->unk6, best->unk8, best->unkA, arg1, arg2, arg3);
                st->unkC8 = best->unkC;
                st->unkCA = best->unkE;
                break;
            case 8:
                camComputeFollowPos(arg0, (CamActor *)tgt, &outX, &outY, &outZ, -1.0f);
                camClosestPointOnSegment(outX, outY, outZ, best->unk0, best->unk2, best->unk4, best->unk6, best->unk8, best->unkA, arg1, arg2, arg3);
                st->unkC8 = 0;
                st->unkCA = 0;
                break;
            case 3:
                st->unkC8 = best->unk8;
                st->unkCA = best->unkA;
                factor = sqrtf((z - best->unk4) * (z - best->unk4) + ((x - best->unk0) * (x - best->unk0) + (y - best->unk2) * (y - best->unk2)));
                factor = (best->unk6 / factor > 1.0) ? 1.0 : best->unk6 / factor;
                *arg1 = (best->unk0 - x) * factor + x;
                *arg2 = (best->unk2 - st->unk6C) * factor + st->unk6C;
                *arg3 = (best->unk4 - z) * factor + z;
                break;
        }
        if (!(st->unkAC & 0x8000) && ret != 0 && (bestIdx != st->unkC4 || st->unkF3 != 2) &&
            (linkId == 0xFF || (linkId != 0xFF && (linkId != st->unkFD || st->unkF3 != 2) && !(D_807FBB60 & 0x2000)))) {
            if (D_807463B8 == 3) {
                D_807FBB60 |= 0x2000;
            } else if (!(st->unkAC & 0x100)) {
                func_8061F18C(arg0, *arg1, *arg2, *arg3);
            }
        }
        if ((st->unkAC & 0x8000) || gScreenFadeProgress > 27.0f || (best->unk17 & 0x38)) {
            D_807FBB60 |= 0x2000;
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
        camFindClearYaw(arg0, 0.0f, st->unkB2, 0);
    }
    if (hadFlag != 0 && !(st->unkAC & 0x2000)) {
        camSetZoomForDistance(arg0, gCamTargetDist);
    }
    if (st->unkF3 == 2) {
        if (st->unkEC & 0xA) {
            CAM_ZONE_PATH->unkC4[gCamZoneSorted[st->unkC4 * 2]].unk17 |= 4;
        }
        if (st->unkED != 8 || mathAngleDistance(st->unkB2, tgt->unkE6) >= 0x400) {
            st->unkB2 = mathAngleBetweenPoints2D(tgt->unk7C, tgt->unk84, *arg1, *arg3);
        }
        if (gCamTargetDist > 150.0f) {
            func_8061B840((CamStateSettle *)st, 0xF);
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

// Needs top-block prototype changes: `void camSetZoomLevel(CamActor *, s16);` (call site passes plain 1, hoisted const gives sll/sra) and `u8 camComputeFollowPos(CamActor *, CamActor *, f32 *, f32 *, f32 *, f32);` (asm returns lbu v0).
typedef struct CamFindYawTarget {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
} CamFindYawTarget;

typedef struct CamFindYawState {
    /* 0x00 */ CamActor *unk0;
    /* 0x04 */ u8 pad4[8];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[0x28];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ u8 pad44[0x5C];
    /* 0xA0 */ f32 unkA0;
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ u8 padA8[4];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ u8 padB4[4];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x32];
    /* 0xEE */ u8 unkEE;
    /* 0xEF */ u8 unkEF;
    /* 0xF0 */ u8 padF0[3];
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4[7];
    /* 0xFB */ u8 unkFB;
    /* 0xFC */ u8 padFC[3];
    /* 0xFF */ u8 unkFF;
} CamFindYawState;

typedef struct CamActorHeightSpeed {
    /* 0x00 */ u8 pad0[0xB4];
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ f32 unkB8;
} CamActorHeightSpeed;

typedef struct CamPlayerRecSaved {
    /* 0x000 */ u8 pad0[0x21C];
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
    /* 0x228 */ u8 pad228[0x98];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 pad2C1[0x2F];
} CamPlayerRecSaved; // size = 0x2F0

s32 collisionTestSphere(f32, f32, f32, f32, void *, void *, s32, s32);

void camFindClearYaw(CamActor *arg0, f32 arg1, s16 arg2, u8 arg3) {
    CamFindYawTarget *tgt;
    s32 ret;
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
    CamFindYawState *cam;
    f32 f;

    cam = (CamFindYawState *)arg0->unk174;
    tgt = (CamFindYawTarget *)cam->unk0;
    cnt = 0;
    out0 = 0xFFF;
    out1 = 0;
    cam->unkB2 = arg2;
    base = cam->unkB2;
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
    if (D_807FBB68 & 2) {
        return;
    }
    if (cam->unkFF >= 4) {
        return;
    }
    if (tgt->unk58 == 5) {
        if (((CamPlayerRecSaved *)D_807FC924)[cam->unkFB].unk2C0 != 1) {
            f = 0.333f;
        }
    }
    camSetZoomLevel(arg0, 1);
    cam->unkB8 = 10.0f;
    ((CamActorHeightSpeed *)arg0)->unkB4 = 10.0f;
    cam->unkA0 = 5.0f;
    cam->unkAC |= 0x80000;
    do {
        again = 0;
        sawCol = camComputeFollowPos(arg0, cam->unk0, &x, &y, &z, -1.0f) == 1;
        while (cam->unkA0 < f * 100.0f && !sawCol && (ret = collisionTestSphere(x, y, z, 10.0f * f, &out1, &out0, 1, 0xBC), hit = ret, ret == 0)) {
            saved = cam->unkB2;
            cam->unkA0 += 10.0f * f;
            ((CamActorHeightSpeed *)arg0)->unkB4 += f * 3.0f;
            sawCol = camComputeFollowPos(arg0, cam->unk0, &x, &y, &z, -1.0f) == 1;
            cam->unkB2 = saved;
        }
        if (hit) {
            cam->unkA0 -= f * 10.0f;
            ((CamActorHeightSpeed *)arg0)->unkB4 -= f * 3.0f;
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
            ((CamActorHeightSpeed *)arg0)->unkB4 = 10.0f;
            cnt += 0x80;
        }
    } while (again);
    if (found || (cnt < 0x1000 && !sawCol)) {
        cam->unkA4 = cam->unkA0;
        camSetZoomForDistance(arg0, (s16)cam->unkA0);
        goto done;
    }
    cam->unkFF += arg3;
    x = ((CamPlayerRecSaved *)D_807FC924)->unk21C;
    y = ((CamPlayerRecSaved *)D_807FC924)->unk220;
    z = ((CamPlayerRecSaved *)D_807FC924)->unk224;
    camSetZoomLevel(arg0, 1);
    cam->unkA0 = cam->unkA4;
    ((CamActorHeightSpeed *)arg0)->unkB4 = cam->unkB8;
    cam->unkB2 = base;
done:
    cam->unkB0 = 0;
    cam->unkAC |= 0x100000;
    cam->unk38 = x;
    cam->unk3C = y;
    cam->unk40 = z;
    cam->unkEE = cam->unkEF;
    cam->unkAC &= ~0x80000;
    cam->unkC = -32768.0f;
    D_807FBB60 |= 0x2000;
    ((CamActorHeightSpeed *)arg0)->unkB8 = 0.0f;
}

typedef struct CamWallState {
    /* 0x00 */ CamActor *unk0;
    /* 0x04 */ u8 pad4[0x18];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[0x80];
    /* 0xA0 */ f32 unkA0;
    /* 0xA4 */ u8 padA4[8];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ u8 padB0[2];
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ u8 padB4[0x3A];
    /* 0xEE */ u8 unkEE;
    /* 0xEF */ u8 unkEF;
    /* 0xF0 */ u8 padF0;
    /* 0xF1 */ u8 unkF1;
    /* 0xF2 */ u8 padF2[3];
    /* 0xF5 */ u8 unkF5;
    /* 0xF6 */ u8 padF6[6];
    /* 0xFC */ u8 unkFC;
} CamWallState;

typedef struct CamWallActor {
    /* 0x00 */ u8 pad0[0xE6];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[6];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[2];
    /* 0xF2 */ s16 unkF2;
    /* 0xF4 */ u8 padF4[8];
    /* 0xFC */ u8 unkFC;
} CamWallActor;

extern u8 D_807FB606;
extern f32 D_807476AC;
s16 mathAngleArcMidpoint(s16, s16);
void mathAngleClampToArc(s16, s16, s16, s16, void *);
s16 func_80672134(s16, s16, s16, s16);

u8 camResolveWallCollision(CamActor *arg0, f32 arg1, f32 arg2, f32 *arg3, f32 arg4, f32 *arg5, f32 arg6) {
    CamWallState *st = (CamWallState *)arg0->unk174;
    s16 sp4A;
    s16 sp48;
    u8 pad;
    s16 sp44;
    s16 sp42;
    f32 v;

    sp4A = 0;
    sp48 = 0xFFF;
    ((CamWallActor *)arg0)->unkFC = 0;
    st->unkFC = 0;
    v = 0.0f;
    v += 0.2 * ((180.0f < st->unkA0) ? 180.0f : st->unkA0);
    if (st->unkF5 != 0) {
        v -= 0.1 * st->unkF5;
    } else {
        v -= 0.1 * st->unkF1;
    }
    if (collisionTestSphere(*arg3, arg4, *arg5, v, &sp4A, &sp48, 1, 0xBC)) {
        if (D_807FB606 != 0) {
            st->unkFC = 2;
            sp44 = (((CamWallActor *)arg0)->unkEE + 0x800) & 0xFFF;
            sp42 = 0;
        } else {
            s16 sp3A;
            s16 t;

            sp3A = mathAngleArcMidpoint(sp4A, sp48);
            arg1 += 0.5 * func_80612794(sp3A);
            arg2 += 0.5 * func_80612790(sp3A);
            st->unkFC = 1;
            mathAngleClampToArc(((CamWallActor *)arg0)->unkEE, ((CamWallActor *)arg0)->unkEE, sp4A, sp48, &sp44);
            t = func_80672134(sp4A, sp48, ((CamWallActor *)arg0)->unkE6, 100);
            if ((f32)t < arg6) {
                sp42 = t;
            } else {
                sp42 = arg6;
            }
        }
        ((CamWallActor *)arg0)->unkFC = 1;
        *arg3 = func_80612794(sp44) * sp42 + arg1;
        *arg5 = func_80612790(sp44) * sp42 + arg2;
        if (st->unkF5 != 0) {
            st->unkA0 -= 5.0f;
        } else {
            st->unkB2 = mathAngleBetweenPoints2D(((CamActor *)st->unk0)->unk7C, ((CamActor *)st->unk0)->unk84, *arg3, *arg5);
        }
        st->unkF1 = 0;
        ((CamWallActor *)arg0)->unkF2 = sp44;
        if (!(st->unkAC & 0x2008) && !(D_807FBB64 & 1) && D_807476AC < st->unkA0) {
            camSetZoomForDistance(arg0, D_807476AC);
        }
    } else {
        if (!(st->unkAC & 0x2000)) {
            if (st->unkEF != st->unkEE) {
                camSetZoomLevel(arg0, st->unkEE);
            }
        }
        st->unk1C = 0.0f;
    }
    return ((CamWallActor *)arg0)->unkFC;
}

typedef struct CamStepState {
    /* 0x00 */ CamActor *unk0;
    /* 0x04 */ u8 pad4[0xAE];
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ u8 padB4[0x40];
    /* 0xF4 */ u8 unkF4;
    /* 0xF5 */ u8 padF5[0xA];
    /* 0xFF */ u8 unkFF;
} CamStepState;

typedef struct CamActorLimits {
    /* 0x000 */ u8 pad0[0x114];
    /* 0x114 */ s16 unk114;
    /* 0x116 */ s16 unk116;
    /* 0x118 */ s16 unk118;
    /* 0x11A */ s16 unk11A;
} CamActorLimits;

typedef struct CamActorSpeed {
    /* 0x00 */ u8 pad0[0xB8];
    /* 0xB8 */ f32 unkB8;
} CamActorSpeed;

s32 func_80620F00(CamActor *arg0, u8 arg1, u8 arg2) {
    CamStepState *st = (CamStepState *)arg0->unk174;
    CamActor *actor;
    f32 diff;
    u8 x;
    u8 y;
    u8 z;
    u8 w;
    CamActorLimits *st2;

    actor = st->unk0;
    diff = gCamTargetDist - ((CamPlayerRec *)D_807FC924)[((CamState *)st)->unkFB].unk284;
    st2 = (CamActorLimits *)actor->unk174;
    x = 40.0f < gCamTargetDist && (f32)st2->unk114 < diff;
    y = (f32)st2->unk118 < diff;
    z = (f32)st2->unk11A < diff;
    w = (f32)st2->unk116 < diff;
    if (arg2 && !y && !z) {
        x = 0;
    }
    if (x != 0) {
        if (arg1 && ((CamActorSpeed *)actor)->unkB8 != 0.0f) {
            if (y && !z) {
                st->unkB2 += 0x32;
                func_8061B840((CamStateSettle *)st, 0xA);
            } else if (z && !y) {
                st->unkB2 -= 0x32;
                func_8061B840((CamStateSettle *)st, 0xA);
            }
        }
        st->unkF4++;
        if (w && st->unkF4 >= 0x15) {
            actor = st->unk0;
            st->unkF4 = 0;
            if (((CamActorSpeed *)actor)->unkB8 != 0.0f && actor->unk154 != 0x59) {
                camFindClearYaw(arg0, 0.0f, st->unkB2, 1);
            } else {
                camFindClearYaw(arg0, 0.0f, actor->unkE6, 1);
            }
        }
        return 1;
    } else {
        st->unkFF = 0;
        st->unkF4 = 0;
    }
    return 0;
}

typedef struct CamAutoRotateActor {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[0x5C];
    /* 0xB8 */ f32 unkB8;
} CamAutoRotateActor;

extern s8 D_80744530;

u8 camShouldAutoRotate(s32 arg0, CamState *arg1, CamActor *arg2) {
    return arg2->unk154 == 0x5B
        || ((D_807FBB64 & 0x4000004) && ((CamAutoRotateActor *)arg2)->unkB8 != 0.0f)
        || (D_807FBB64 & 0x8000000)
        || (arg1->unkAC & 4)
        || ((arg1->unkAC & 8) && ((CamAutoRotateActor *)arg2)->unkB8 != 0.0f)
        || (D_80744530 == 1 && ((CamAutoRotateActor *)arg2)->unkB8 != 0.0f && func_807142D8() == 0)
        || arg1->unkF3 == 0xA
        || arg1->unkF3 == 0xD
        || arg1->unkF3 == 5
        || arg1->unkF3 == 0xC
        || (arg1->unkFC != 0 && ((CamAutoRotateActor *)arg2)->unkB8 != 0.0f)
        || arg2->unk154 == 0x6E
        || ((CamAutoRotateActor *)arg2)->unk58 == 8;
}

typedef struct CamFollowPosActor CamFollowPosActor;

typedef struct CamFollowPosPlayer {
    /* 0x000 */ u8 pad0[0x130];
    /* 0x130 */ CamFollowPosActor *unk130;
    /* 0x134 */ u8 pad134[0xBC];
    /* 0x1F0 */ s32 unk1F0;
} CamFollowPosPlayer;

typedef struct CamFollowPosState {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ CamFollowPosActor *unk4;
    /* 0x08 */ u8 pad8[4];
    /* 0x0C */ u8 padC[6];
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[0x56];
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ u8 pad70[0x20];
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 pad94[4];
    /* 0x98 */ f32 unk98;
    /* 0x9C */ s16 unk9C;
    /* 0x9E */ s16 unk9E;
    /* 0xA0 */ f32 unkA0;
    /* 0xA4 */ u8 padA4[8];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ u8 padB0[2];
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ u8 padB4[0xC];
    /* 0xC0 */ s32 unkC0;
    /* 0xC4 */ u8 padC4[0x18];
    /* 0xDC */ f32 unkDC;
    /* 0xE0 */ u8 padE0[8];
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ u8 padEA[5];
    /* 0xEF */ u8 unkEF;
    /* 0xF0 */ u8 padF0;
    /* 0xF1 */ u8 unkF1;
    /* 0xF2 */ u8 unkF2;
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4[8];
    /* 0xFC */ u8 unkFC;
} CamFollowPosState;

struct CamFollowPosActor {
    /* 0x000 */ u8 pad0[0x58];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0xE];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0xE];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[4];
    /* 0x08C */ f32 unk8C;
    /* 0x090 */ u8 pad90[0xC];
    /* 0x09C */ f32 unk9C;
    /* 0x0A0 */ f32 unkA0;
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[4];
    /* 0x0AC */ f32 unkAC;
    /* 0x0B0 */ u8 padB0[4];
    /* 0x0B4 */ f32 unkB4;
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[0x28];
    /* 0x0E4 */ u8 padE4[2];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[0x6A];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x1F];
    /* 0x174 */ void *unk174;
};

extern u8 D_80750AB4;
extern f32 gScreenFadeProgress;

s32 actorTableContains(void *);
s32 func_805FCA64(void);
u8 camFloorSnap(void *, void *, f32, f32 *, f32, s32);
void camTurnYawToward();

#define TGT ((CamFollowPosActor *)arg1)
#define CA ((CamFollowPosActor *)arg0)
u8 camComputeFollowPos(CamActor *arg0, CamActor *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 arg5) {
    CamFollowPosState *cam = (CamFollowPosState *)arg0->unk174;
    CamFollowPosPlayer *ply = (CamFollowPosPlayer *)arg1->unk174;
    f32 x;
    f32 y;
    f32 z;
    s16 sp72;
    u8 sp71;
    s16 sp6E;
    s16 diff;
    f32 sp68;
    f32 sp64;
    s32 var_v0;
    s32 var_v0_2;
    s16 sp5A;
    s16 e6;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;

    sp71 = 0;
    y = 0.0f;
    sp68 = cam->unkA0;
    sp64 = cam->unk6C;
    if ((ply->unk1F0 & 0x800000) && (TGT->unk6A & 1) && !(TGT->unk6C & 1)) {
        ply->unk1F0 &= ~0x800000;
    }
    if ((D_807FBB64 & 1) && (cam->unkAC & 4) && !(cam->unkAC & 0x4000) && cam->unkF3 != 0xA) {
        sp72 = (s32)TGT->unkB8;
        if (cam->unk12 != 0 && cam->unk4 != NULL) {
            sp6E = mathAngleBetweenPoints2D(cam->unk12 + (cam->unk4->unk7C - cam->unk12) * 0.35,
                                            cam->unk14 + (cam->unk4->unk84 - cam->unk14) * 0.35,
                                            TGT->unk7C, TGT->unk84);
        } else {
            if (cam->unk4 != NULL) {
                sp6E = mathAngleBetweenPoints2D(cam->unk4->unk7C, cam->unk4->unk84, TGT->unk7C, TGT->unk84);
            } else {
                sp6E = TGT->unkE6;
            }
        }
    } else {
        switch (TGT->unk154) {
            case 0x57:
            case 0x58:
                actorGetNodePos(arg1, 0xC, &sp54, &sp50, &sp4C);
                actorGetNodePos(arg1, 1, &sp48, &sp44, &sp40);
                sp5A = mathAngleBetweenPoints2D(sp54, sp4C, sp48, sp40) & 0xFE00;
                if (actorTableContains(ply->unk130) != 0) {
                    e6 = ply->unk130->unkE6;
                    if (sp5A < e6) {
                        diff = e6 - sp5A;
                    } else {
                        diff = sp5A - e6;
                    }
                    if (diff > 0x400 && diff < 0xC18) {
                        sp6E = (e6 + 0x92C) & 0xFFF;
                    } else {
                        sp6E = (e6 + 0x12C) & 0xFFF;
                    }
                } else {
                    sp6E = TGT->unkE6;
                }
                sp72 = 5;
                break;
            case 0x5B:
                sp72 = 0x64;
                sp6E = TGT->unkE6;
                break;
            default:
                sp72 = (s32)TGT->unkB8;
                if (cam->unkAC & 0x4000) {
                    sp6E = (TGT->unkE6 + 0x800) & 0xFFF;
                } else {
                    sp6E = TGT->unkE6;
                }
                break;
        }
    }
    if (arg5 >= 0.0f && cam->unkF3 != 2) {
        if (D_80750AB4 == 1) {
            if (TGT->unk154 == 0x4F) {
                func_80620F00(arg0, 0, 1);
            } else if (TGT->unk154 == 0x59 || TGT->unk154 == 0x4E || TGT->unk154 == 0x6E) {
                func_80620F00(arg0, 0, 0);
            } else if (func_805FCA64() != 0 && cam->unkF1 == 0) {
                if (TGT->unk58 != 8 && TGT->unk58 != 9 && ((u8 *)D_807FC924)[0x2C0] != 2) {
                    if (TGT->unk154 != 0xE && TGT->unk154 != 0x42 && TGT->unk154 != 0x57 && TGT->unk154 != 0x48 &&
                        TGT->unk154 != 0x49 && TGT->unk154 != 0x4C && TGT->unk154 != 0x47 && TGT->unk154 != 0x3E &&
                        !(cam->unkAC & 0x12000) && !(D_807FBB68 & 2) && TGT->unk154 != 0x58 && TGT->unk154 != 0x63 &&
                        TGT->unk154 != 0x52 && TGT->unk154 != 0x54 && TGT->unk154 != 0x53 && TGT->unk154 != 0x40 &&
                        TGT->unk154 != 0x4F) {
                        func_80620F00(arg0, var_v0 = (TGT->unkB8 != 0.0f ? 1 : 0), 0);
                    }
                }
            }
        }
        if (!(cam->unkAC & 0x100) && gScreenFadeProgress == 0.0f && 2.0 * cam->unkA0 < D_807476AC && cam->unkE8 == 0 &&
            cam->unkF3 != 5 && !(D_807FBB68 & 2) && !(D_807FBB64 & 0x2001)) {
            camFindClearYaw(arg0, -1.0f, cam->unkB2, 0);
        } else {
            if (cam->unkFC != 0 && cam->unkA0 * 1.2 < D_807476AC) {
                if (*arg3 - (cam->unk90 < cam->unk6C ? cam->unk6C : cam->unk90) > 50.0f && cam->unkEF >= 2) {
                    camSetZoomLevel(arg0, 1);
                    CA->unkB4 = CA->unkB4 - 120.0f;
                } else {
                    CA->unkB4 = CA->unkB4 + 5.0;
                }
            } else if (cam->unkFC == 2) {
                CA->unkB4 = CA->unkB4 + 20.0f;
            }
        }
    }
    if (cam->unkF3 != 2 && camShouldAutoRotate((s32)arg0, (CamState *)cam, arg1) != 0) {
        camTurnYawToward(cam, sp72, sp6E);
    }
    switch (TGT->unk154) {
        case 0x63:
            if (D_807FBB68 & 2) {
                sp68 = 100.0f;
                y = y + ((TGT->unk80 + 30.0f) + (TGT->unk80 - TGT->unkA4) * 0.5);
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
                y += TGT->unk80 + CA->unkB4;
            }
            break;
        case 0x59:
            if (D_807FBB68 & 2) {
                y += cam->unk6C + CA->unkB4;
            } else if ((cam->unkAC & 0x2000) && !(TGT->unk6A & 0x80)) {
                y += TGT->unk80 - cam->unk98;
            } else {
                y += TGT->unk8C + 10.0f;
            }
            break;
        case 0x4E:
        case 0x7E:
        case 0x80:
        case 0x82:
            y += TGT->unk80 + (CA->unkB4 < 30.0f ? 30.0f : CA->unkB4);
            break;
        case 0x37:
        case 0x43:
        case 0x4F:
        case 0x7F:
        case 0x81:
            y += TGT->unk80;
            if ((D_807FBB64 & 0x20) && D_807F5CD0 >= 0xC9) {
                y += 80.0f * func_80612794(CA->unkE8);
            }
            break;
        case 0x21:
            y += TGT->unkA0;
            break;
        case 0x19:
            if (ply->unk1F0 & 0x800000) {
                y += TGT->unk80 + CA->unkB4;
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
                if (TGT->unk9C - TGT->unk80 > 50.0f) {
                    sp64 = cam->unkDC;
                }
        default:
                if (TGT->unk6A & 2) {
                    if (sp64 < TGT->unkAC) {
                        sp64 = TGT->unkAC;
                    }
                }
                y += sp64 + CA->unkB4;
            }
            break;
    }
    if (ply->unk1F0 & 0x200) {
        cam->unk9C = 0x3C;
    }
    if (cam->unk9C != 0) {
        cam->unk9C = cam->unk9C - 1;
        y += 130.0f;
    }
    x = TGT->unk7C - func_80612794(cam->unkB2) * sp68;
    z = TGT->unk84 - func_80612790(cam->unkB2) * sp68;
    if (arg5 > 0.0f) {
        x += arg5 * func_80612794(cam->unk9E);
        z += arg5 * func_80612790(cam->unk9E);
    }
    if (cam->unkF2 != 0) {
        camApplyShake((CamState *)cam, &x, &y, &z, cam->unkC0, 0);
    }
    *arg2 = x;
    *arg3 = y;
    *arg4 = z;
    if (cam->unkF3 != 0xC) {
        sp71 = camFloorSnap(arg0, cam, *arg2, &y, *arg4, var_v0_2 = (arg5 >= 0.0f ? 0 : 1));
        if (sp71 != 0 || y < *arg3) {
            *arg3 = y;
        }
    }
    return sp71;
}
#undef TGT
#undef CA

typedef struct CamFocusState {
    /* 0x00 */ CamActor *unk0;
    /* 0x04 */ CamActor *unk4;
    /* 0x08 */ u8 pad8[0x64];
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ u8 pad70[0x6C];
    /* 0xDC */ f32 unkDC;
} CamFocusState;

extern f32 D_807476B0;

void camComputeFocusPos(CamState *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    CamActor *actor = ((CamFocusState *)arg0)->unk0;
    f32 f;
    f32 y;
    s16 idx;

    f = (actor->unk154 == 0x5B || actor->unk154 == 0x59 || actor->unk154 == 0x57 || actor->unk154 == 0x58 || actor->unk154 == 0x3E) ? 0.11 : 0.17;
    y = 0.0f;
    if (actor->unk15E > 0x14) {
        idx = 0x14;
    } else {
        idx = actor->unk15E;
    }
    if (D_807476B0 >= 0.0f) {
        y = CAM_MIN(1.0, (f < D_807476B0 ? D_807476B0 - f : 0.0f) * 2);
    } else if (D_807476B0 < -0.1) {
        y = 0.0 - CAM_MAX(CAM_MIN((D_807476B0 - f) + 0.3, 0.0) * 2, -1.0);
    }
    if (((CamFocusState *)arg0)->unk4 != NULL) {
        *arg1 = ((CamFocusState *)arg0)->unk4->unk7C + (actor->unk7C - ((CamFocusState *)arg0)->unk4->unk7C) * 0.9;
        *arg3 = ((CamFocusState *)arg0)->unk4->unk84 + (actor->unk84 - ((CamFocusState *)arg0)->unk4->unk84) * 0.9;
    } else {
        *arg1 = actor->unk7C;
        *arg3 = actor->unk84;
    }
    *arg2 = ((((CamFocusState *)arg0)->unkDC + idx) - (((CamFocusState *)arg0)->unk6C + idx)) * y + (((CamFocusState *)arg0)->unk6C + idx);
}

typedef struct CamStateYawOffset {
    /* 0x00 */ u8 pad0[0x9E];
    /* 0x9E */ s16 unk9E;
} CamStateYawOffset;

void camComputeFocusPosOffset(CamState *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4) {
    camComputeFocusPos(arg0, arg1, arg2, arg3);
    *arg1 += arg4 * func_80612794(((CamStateYawOffset *)arg0)->unk9E);
    *arg3 += arg4 * func_80612790(((CamStateYawOffset *)arg0)->unk9E);
}

typedef struct CamZoomEntry {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 unk2;
} CamZoomEntry;

typedef struct CamZoomState {
    /* 0x00 */ u8 pad0[0xA4];
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ u8 padA8[0x10];
    /* 0xB8 */ f32 unkB8;
} CamZoomState;

extern CamZoomEntry D_80747B60[][4];

u8 camSetZoomLevel(CamActor *arg0, s16 arg1) {
    CamState *st = arg0->unk174;
    u8 old;
    s16 v;

    v = (D_8074E77C[st->unkFB] * 2 + (((CamPlayerRec *)D_807FC924)[st->unkFB].unk2C0 != 1)) + 7;
    old = st->unkEF;
    if ((st->unkAC & 0x2000) && arg1 > 1) {
        arg1 = 1;
    }
    if ((D_807FBB64 & 0x10) && arg1 > 1) {
        arg1 = 1;
    }
    if (D_8076A0A8 == 0x9A) {
        v = 0;
    } else if (D_807FBB68 & 2) {
        v = 2;
    } else if ((D_807FBB64 & 1) && D_8076A0A8 != 0x6F) {
        v = 3;
    } else if (D_807FBB64 & 0x80) {
        v = 4;
    } else if (st->unkAC & 0x20000) {
        v = 5;
    } else if (D_807FBB64 & 0x4000000) {
        v = 6;
    } else if (st->unkF3 == 5 || st->unkF3 == 0xC || st->unkF3 == 0xA) {
        v = 1;
    }
    ((CamZoomState *)st)->unkA4 = D_80747B60[v][arg1].unk2;
    ((CamZoomState *)st)->unkB8 = D_80747B60[v][arg1].unk0;
    st->unkEF = arg1;
    return old;
}

void camSetZoomForDistance(CamActor *arg0, s16 arg1) {
    CamState *st = arg0->unk174;
    s16 idx;
    s16 best;
    s16 i;

    idx = D_8074E77C[st->unkFB] * 2 + (((CamPlayerRec *)D_807FC924)[st->unkFB].unk2C0 != 1) + 7;
    best = 1;
    if (D_8076A0A8 == 0x9A) {
        idx = 0;
    } else if (D_807FBB68 & 2) {
        idx = 2;
    } else if ((D_807FBB64 & 1) && D_8076A0A8 != 0x6F) {
        idx = 3;
    } else if (D_807FBB64 & 0x80) {
        idx = 4;
    } else if (st->unkAC & 0x20000) {
        idx = 5;
    } else if (D_807FBB64 & 0x4000000) {
        idx = 6;
    } else if (st->unkF3 == 5 || st->unkF3 == 0xC || st->unkF3 == 0xA) {
        idx = 1;
    }
    for (i = 2; i < 4; i++) {
        if (arg1 >= D_80747B60[idx][i].unk2) {
            best = i;
        }
    }
    camSetZoomLevel(arg0, best);
}

typedef struct CamPlayerActorSlot {
    /* 0x00 */ u8 pad0[0x6E];
    /* 0x6E */ s16 unk6E;
} CamPlayerActorSlot;

typedef struct CamReturnState {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[0x34];
    /* 0x44 */ s32 unk44;
    /* 0x48 */ u8 pad48[0x68];
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ u8 padB4[0x39];
    /* 0xED */ u8 unkED;
    /* 0xEE */ u8 padEE[5];
    /* 0xF3 */ u8 unkF3;
} CamReturnState;

extern CamPlayerActorSlot *D_807FBB48;
void sfxStopSlotSound(void *, s32);
void camReturnToFollow(CamActor *arg0, CamActor *arg1) {
    CamReturnState *s;
    s32 pad1;
    s32 pad2;
    u8 pad3;
    u8 prev;

    s = (CamReturnState *)arg0->unk174;
    prev = s->unkF3;

    if (D_807FBB48->unk6E != -1) {
        sfxStopSlotSound(D_807FBB48, 0);
    }
    s->unk44 = 0;
    s->unkB0 = 0;
    s->unkF3 = 1;
    s->unkC = -32768.0f;
    switch (prev) {
        case 3:
        case 0xB:
            camStartBlendRamp((CamState *)s, 0xA);
            s->unkB2 = arg1->unkE6;
            break;
        case 2:
            if (s->unkED == 8) {
                if (mathAngleDistance(s->unkB2, arg1->unkE6) < 0x400) {
                    camSnapBehindTarget(arg0);
                }
            }
            s->unkED = 0xFF;
        default:
            camStartBlendRamp((CamState *)s, 0x14);
            break;
    }
}

void camSetFollowMode(CamActor *arg0) {
    CamState *st = arg0->unk174;

    st->unk44 = 0;
    st->unkF3 = 1;
}

typedef struct CamOrbitTarget {
    /* 0x000 */ u8 pad0[0x6A];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0xE];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x5E];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[0x6A];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x1F];
    /* 0x174 */ void *unk174;
} CamOrbitTarget;

typedef struct CamPlayerFlagsU32 {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ u32 unk1F0;
} CamPlayerFlagsU32;

typedef struct CamOrbitBlock {
    /* 0x00 */ CamOrbitTarget *unk0;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ s16 unk14;
} CamOrbitBlock;

typedef struct CamOrbitState {
    /* 0x00 */ CamOrbitTarget *unk0;
    /* 0x04 */ u8 pad4[0x40];
    /* 0x44 */ CamOrbitBlock s44;
    /* 0x5C */ u8 pad5C[0x9F];
    /* 0xFB */ u8 unkFB;
} CamOrbitState;

void camComputeTargetEyePos(CamActor *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    CamOrbitState *st = (CamOrbitState *)arg0->unk174;
    CamOrbitBlock *p = &st->s44;
    s16 angle;
    CamPlayerFlagsU32 *tgtState;
    s8 mult;
    s32 pad;

    angle = (p->unk0->unkE6 + p->unk8) & 0xFFF;
    tgtState = (CamPlayerFlagsU32 *)st->unk0->unk174;
    mult = 1;
    if (st->unk0->unk154 == 0x21 || st->unk0->unk154 == 0x38) {
        return;
    }
    *arg1 = func_80612794(angle) * p->unkA + p->unk0->unk7C;
    *arg3 = func_80612790(angle) * p->unkA + p->unk0->unk84;
    *arg2 = p->unk0->unk80 + p->unk10;
    if (D_8076A0A8 == 6 || D_8076A0A8 == 0xE || D_8076A0A8 == 0x37 || D_8076A0A8 == 0x6A) {
        if (tgtState->unk1F0 & 0x10000002) {
            mult = -1;
        }
        *arg2 += (mult * p->unkA) * func_80612794(p->unk0->unkE8);
    }
    if (p->unk14 != 0) {
        p->unk14--;
        if (p->unk14 == 0 || (!(st->unk0->unk6C & 1) && (st->unk0->unk6A & 1))) {
            p->unk0 = 0;
            camResetPlayer((Actor *)st->unk0, st->unkFB);
            D_807FBB60 |= 0x2000;
            if (D_8076A0B1 & 0x10) {
                D_8076A0B1 &= ~0x10;
                D_8076A0B3 = 0xFF;
            }
        }
    }
}

typedef struct CamFocusBlock {
    /* 0x00 */ CamActor *unk0;
    /* 0x04 */ CamActor *unk4;
    /* 0x08 */ u8 pad8[4];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[2];
    /* 0x12 */ s16 unk12;
} CamFocusBlock;

typedef struct CamFocusBlockState {
    /* 0x00 */ u8 pad0[0x44];
    /* 0x44 */ CamFocusBlock s44;
} CamFocusBlockState;

void camComputeTargetFocusPos(CamState *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    CamFocusBlock *p;
    s16 angle;

    p = &((CamFocusBlockState *)arg0)->s44;
    angle = (p->unk0->unkE6 + p->unkC) & 0xFFF;
    *arg1 = func_80612794(angle) * p->unkE + p->unk4->unk7C;
    *arg3 = func_80612790(angle) * p->unkE + p->unk4->unk84;
    *arg2 = p->unk4->unk80 + p->unk12;
}

typedef struct CamHeadTarget {
    /* 0x000 */ u8 pad0[0x7C];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x6C];
    /* 0x0F4 */ s16 unkF4;
    /* 0x0F6 */ s16 unkF6;
    /* 0x0F8 */ u8 padF8[4];
    /* 0x0FC */ u8 unkFC;
    /* 0x0FD */ u8 padFD[0x57];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[9];
    /* 0x15E */ u8 unk15E;
} CamHeadTarget;

typedef struct CamHeadState {
    /* 0x00 */ CamHeadTarget *unk0;
    /* 0x04 */ u8 pad4[0xAE];
    /* 0xB2 */ s16 unkB2;
} CamHeadState;

typedef struct CamActorHeight {
    /* 0x00 */ u8 pad0[0xB4];
    /* 0xB4 */ f32 unkB4;
} CamActorHeight;


void func_806228BC(CamActor *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
    CamHeadState *st = (CamHeadState *)arg0->unk174;
    CamHeadTarget *tgt = st->unk0;
    s16 angle;
    s32 h;

    *arg1 = tgt->unk7C;
    if (tgt->unk154 == 3 || tgt->unk154 == 5) {
        h = tgt->unk15E < 0xF ? 0xF : tgt->unk15E;
        *arg2 = h + tgt->unk80;
    } else if (D_8076A0A8 == 0x30) {
        h = tgt->unk15E < 0x16 ? 0x16 : tgt->unk15E;
        *arg2 = h + tgt->unk80;
    } else {
        h = tgt->unk15E < 0xA ? 0xA : tgt->unk15E;
        *arg2 = h + tgt->unk80;
    }
    *arg3 = tgt->unk84;
    if (tgt->unkFC != 0) {
        angle = mathAngleArcMidpoint(tgt->unkF4, tgt->unkF6);
        *arg1 += 5.0 * func_80612794(angle);
        *arg3 += 5.0 * func_80612790(angle);
    }
    *arg4 = tgt->unk7C - func_80612794(st->unkB2) * 50.0f;
    *arg5 = tgt->unk80 - (((CamActorHeight *)arg0)->unkB4 - 138.0f);
    *arg6 = tgt->unk84 - func_80612790(st->unkB2) * 50.0f;
}

f32 camAngleLerpRad(f32 arg0, f32 arg1, f32 arg2) {
    f32 diff = arg0 - arg1;

    if (diff > 3.1415927f) {
        arg1 += 6.2831855f;
    } else if (diff < -3.1415927f) {
        arg0 += 6.2831855f;
    }
    return arg0 + (arg1 - arg0) * arg2;
}

void camComputeEyeFocus(CamActor *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6, CamActor *arg7) {
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

    cam = arg0->unk174;
    p = &gCamActivePaths->unkD8[gCamPathNode];
    savedX = *arg1;
    savedY = *arg2;
    savedZ = *arg3;
    if (D_807444EC == 1 && (p->unk1 == 4 || p->unk1 == 5)) {
        count = (p->u.spline.unk0 - 1 < 0) ? 0 : p->u.spline.unk0 - 1;
        arg7->unk160 = CAM_LERP(count, 0, D_807F5D00);
        arg7->unk168 = arg7->unk160;
        arg7->unk160 -= arg7->unk168;
    } else {
        count = (gCamActivePaths->unk0[arg7->unk15F].unk0 - 1 < 0) ? 0 : gCamActivePaths->unk0[arg7->unk15F].unk0 - 1;
    }
    idx[0] = (arg7->unk168 - 1 < 0) ? 0 : arg7->unk168 - 1;
    idx[1] = arg7->unk168;
    idx[2] = (arg7->unk168 + 1 >= count) ? count : arg7->unk168 + 1;
    idx[3] = (arg7->unk168 + 2 >= count) ? count : arg7->unk168 + 2;
    if (D_807444EC != 1U) {
        if (cam->unkF3 == 3 || cam->unkF3 == 0xB) {
            if (arg7->unk154 != 2 && arg7->unk154 != 3 && arg7->unk154 != 4 && arg7->unk154 != 5 &&
                arg7->unk154 != 0x64 && arg7->unk154 != 0x65) {
                func_8062773C(arg0);
                D_807FBB60 |= 0x2000;
            }
        } else {
            switch (arg7->unk154) {
                case 0x36:
                    if (D_807FC928 >= 2 && D_80750AB8 != 0) {
                    }
                    break;
                case 0x57:
                case 0x58:
                    if (cam->unkF3 == 1) {
                        camStartBlendRamp(cam, 0x50);
                        cam->unkF3 = 0xC;
                        camSetZoomLevel(arg0, 2);
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
                    if (!(D_807FBB64 & 0x80) && cam->unkF3 != 0xD && cam->unkF3 != 2) {
                        cam->unkF3 = 0xD;
                        camStartBlendRamp(cam, 0x1E);
                    }
                    break;
                default:
                    if (cam->unkF3 == 0xA || cam->unkF3 == 0xC || cam->unkF3 == 0xD) {
                        camSetZoomForDistance(arg0, cam->unkA0);
                        camStartBlendRamp(cam, 0x14);
                        cam->unkF3 = 1;
                        cam->unk6C = arg7->unk80;
                    }
                    break;
            }
        }
        if (cam->unkF3 != 6 && cam->unkF3 != 9 && (!(D_8076A0B1 & 0x10) || D_807463B8 == 3) &&
            cam->unkF3 != 8 && cam->unkF3 != 7 && cam->unkEF != 0) {
            if (func_8061F53C(arg0, arg1, arg2, arg3, arg4, arg5, arg6) != 0) {
                cam->unkF3 = 2;
            } else if (cam->unk44 != 0) {
                cam->unkF3 = 4;
            } else if (cam->unkF3 == 3 || cam->unkF3 == 2) {
                camReturnToFollow(arg0, arg7);
            } else if (cam->unkF3 == 5) {
                switch (arg7->unk154) {
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
                        camSetZoomForDistance(arg0, gCamTargetDist);
                        cam->unkF3 = 1;
                        cam->unkAC |= 0x20;
                        cam->unkC = -32768.0f;
                        break;
                }
            }
        }
        cam->unkAC &= ~0x40000;
    }
    if (D_807444EC != 0) {
        if (D_807444EC == 1) {
            type = p->unk1;
            if (type == 7) {
                list = gCamActivePaths->unkD0[gCamPathIndex].unk4;
                p = &gCamActivePaths->unkD8[list[gCamPathStep]];
                if (p->unk1 == 8 || p->unk1 == 0xC) {
                    p = &gCamActivePaths->unkD8[list[gCamPathStep + 1]];
                }
                if (D_807F5CFC == gCamPathFramesLeft + 1) {
                    D_807F5D18 = *arg1;
                    D_807F5D1C = *arg2;
                    D_807F5D20 = *arg3;
                    D_807F5D24 = *arg4;
                    D_807F5D28 = *arg5;
                    D_807F5D2C = *arg6;
                }
            } else if (D_807F5CFC == gCamPathFramesLeft + 1) {
                D_807F5D24 = *arg4 - *arg1;
                D_807F5D28 = *arg5 - *arg2;
                D_807F5D2C = *arg6 - *arg3;
            }
            if (type == 7) {
                arg7->unk168 = 0;
                arg7->unk160 = 0.0;
                idx[0] = 0;
                idx[1] = 0;
                t = 1.0f;
                idx[2] = (arg7->unk168 + 1 >= count) ? count : arg7->unk168 + 1;
                idx[3] = (arg7->unk168 + 2 >= count) ? count : arg7->unk168 + 2;
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
                    posX = func_80612794(arg7->unkE6 - angle) * dist + arg7->unk7C;
                    posZ = func_80612790(arg7->unkE6 - angle) * dist + arg7->unk84;
                    posY = arg7->unk80 + height;
                    D_807FC924[cam->unkFB].unk27C = CAM_LERP(pos->unkD, pos->unkC, t);
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
                    dz = arg7->unk84 - pos->unk4;
                    dx = arg7->unk7C - pos->unk0;
                    dy = arg7->unk80 - pos->unk2;
                    ratio = pos->unk6 / sqrtf(dz * dz + (dx * dx + dy * dy));
                    scale = (ratio > 1.0) ? 1.0 : ratio;
                    posX = (pos->unk0 - arg7->unk7C) * scale + arg7->unk7C;
                    posY = (pos->unk2 - arg7->unkA4) * scale + arg7->unkA4;
                    posZ = (pos->unk4 - arg7->unk84) * scale + arg7->unk84;
                    goto calc_look;
                case 3:
                    camClosestPointOnSegment(arg7->unk7C, arg7->unk80, arg7->unk84, p->u.pos.unk0, p->u.pos.unk2, p->u.pos.unk4,
                                  p->u.pos.unk0 + p->u.pos.unk6, p->u.pos.unk2 + p->u.pos.unk8,
                                  p->u.pos.unk4 + p->u.pos.unkA, &posX, &posY,
                                  &posZ);
                    goto calc_look;
                case 17:
                    posX = *arg1;
                    posY = *arg2;
                    posZ = *arg3;
                    goto calc_look;
                case 4:
                    e0 = &((CamSplineKeyPosLook *) p->u.spline.unk4)[idx[0]];
                    e1 = &((CamSplineKeyPosLook *) p->u.spline.unk4)[idx[1]];
                    e2 = &((CamSplineKeyPosLook *) p->u.spline.unk4)[idx[2]];
                    e3 = &((CamSplineKeyPosLook *) p->u.spline.unk4)[idx[3]];
                    posX = splineEvalCubic(arg7->unk160, e0->unk0, e1->unk0, e2->unk0, e3->unk0);
                    posY = splineEvalCubic(arg7->unk160, e0->unk2, e1->unk2, e2->unk2, e3->unk2);
                    posZ = splineEvalCubic(arg7->unk160, e0->unk4, e1->unk4, e2->unk4, e3->unk4);
                    lookX = splineEvalCubic(arg7->unk160, e0->unk6, e1->unk6, e2->unk6, e3->unk6);
                    lookY = splineEvalCubic(arg7->unk160, e0->unk8, e1->unk8, e2->unk8, e3->unk8);
                    lookZ = splineEvalCubic(arg7->unk160, e0->unkA, e1->unkA, e2->unkA, e3->unkA);
                    D_807FC924[cam->unkFB].unk27C =
                        splineEvalCubic(arg7->unk160, e0->unkC, e1->unkC, e2->unkC, e3->unkC);
                    if (gCamRollFramesLeft == 0) {
                        arg0->unkE4 =
                            splineEvalCubic(arg7->unk160, e0->unkD, e1->unkD, e2->unkD, e3->unkD) / 127.0 * 2048.0;
                    }
                    break;
                case 5:
                    k0 = &((CamSplineKeyPos *) p->u.spline.unk4)[idx[0]];
                    k1 = &((CamSplineKeyPos *) p->u.spline.unk4)[idx[1]];
                    k2 = &((CamSplineKeyPos *) p->u.spline.unk4)[idx[2]];
                    k3 = &((CamSplineKeyPos *) p->u.spline.unk4)[idx[3]];
                    posX = splineEvalCubic(arg7->unk160, k0->unk0, k1->unk0, k2->unk0, k3->unk0);
                    posY = splineEvalCubic(arg7->unk160, k0->unk2, k1->unk2, k2->unk2, k3->unk2);
                    posZ = splineEvalCubic(arg7->unk160, k0->unk4, k1->unk4, k2->unk4, k3->unk4);
                    D_807FC924[cam->unkFB].unk27C =
                        splineEvalCubic(arg7->unk160, k0->unk6, k1->unk6, k2->unk6, k3->unk6);
                    if (gCamRollFramesLeft == 0) {
                        arg0->unkE4 =
                            splineEvalCubic(arg7->unk160, k0->unk7, k1->unk7, k2->unk7, k3->unk7) / 127.0 * 2048.0;
                    }
                calc_look:
                    if (!gCamPathLookNode) {
                        lookX = func_80612794(arg7->unkE6) * gCamPathLookAhead + arg7->unk7C;
                        lookZ = func_80612790(arg7->unkE6) * gCamPathLookAhead + arg7->unk84;
                        if (arg7->unk15E != 0) {
                            lookY = arg7->unk80 + arg7->unk15E;
                        } else {
                            lookY = arg7->unk80;
                        }
                    } else {
                        actorGetNodePos(gCamPathLookActor, gCamPathLookNode, &lookX, &lookY, &lookZ);
                    }
                    goto look_done;
            }
        look_set: /* two consecutive labels: the empty block keeps uopt from colouring type across the switch */
        look_done:
            if (type == 7) {
                blend = func_80612794(D_807F5D00 * 1024.0f + 3072.0f) + 1.0;
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
                *arg1 = CAM_LERP(posX, D_807F5D18, blend);
                *arg2 = CAM_LERP(posY, D_807F5D1C, blend);
                *arg3 = CAM_LERP(posZ, D_807F5D20, blend);
                *arg4 = *arg1 + func_80612794(yaw) * dist2D;
                *arg6 = *arg3 + func_80612790(yaw) * dist2D;
                *arg5 = *arg2 + sinApprox(pitch) * dist3D;
                return;
            }
            if (type != 8 && type != 0xC && type != 6) {
                *arg1 = posX;
                *arg2 = posY;
                *arg3 = posZ;
                *arg4 = lookX;
                *arg5 = lookY;
                *arg6 = lookZ;
            }
        }
    } else {
        switch (cam->unkF3) {
            case 4:
            case 6:
                camComputeTargetFocusPos(cam, arg4, arg5, arg6);
                camComputeTargetEyePos(arg0, arg1, arg2, arg3);
                camSampleFloorHeight(arg0, cam, *arg1, *arg3);
                break;
            case 8:
                camComputeFocusPos(cam, arg4, arg5, arg6);
                camComputeTargetEyePos(arg0, arg1, arg2, arg3);
                break;
            case 7:
                camComputeFocusPos(cam, arg4, arg5, arg6);
                break;
            case 2:
                camComputeFocusPosOffset(cam, arg4, arg5, arg6, D_807476B4);
                if (D_8076A0A8 == 0xD6) {
                    *arg5 += 50.0f;
                }
                if (cam->unkC8 != 0 || cam->unkCA != 0) {
                    camClampEyeAngle(cam, arg4, arg6, *arg1, *arg3,
                                  (s32) sqrtf((*arg1 - *arg4) * (*arg1 - *arg4) + (*arg3 - *arg6) * (*arg3 - *arg6)));
                }
                if (cam->unkF2 != 0) {
                    camApplyShake(cam, arg1, arg2, arg3, cam->unkC0, 0);
                }
                camSampleFloorHeight(arg0, cam, *arg1, *arg3);
                break;
            case 3:
            case 11:
                func_806228BC(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
                if (cam->unkF2 != 0) {
                    camApplyShake(cam, arg1, arg2, arg3, cam->unkC0, 0);
                }
                camSampleFloorHeight(arg0, cam, *arg1, *arg3);
                break;
            case 5:
            case 10:
            case 12:
                *arg4 = arg7->unk7C;
                *arg6 = arg7->unk84;
                if ((arg7->unk154 == 0x37 || arg7->unk154 == 0x43 || arg7->unk154 == 0x4F || arg7->unk154 == 0x7F ||
                     arg7->unk154 == 0x81) &&
                    (D_807FBB64 & 0x20) && D_807F5CD0 >= 0xC9) {
                    *arg5 = func_80612794(arg0->unkE8) * -20.0f + arg7->unk80;
                } else {
                    *arg5 = arg7->unk80;
                }
                camComputeFollowPos(arg0, arg7, arg1, arg2, arg3, 0.0f);
                break;
            case 13:
                *arg4 = arg7->unk7C;
                *arg5 = ((arg7->unk15E >= 21) ? 20 : arg7->unk15E) + arg7->unk80;
                *arg6 = arg7->unk84;
                camComputeFollowPos(arg0, arg7, arg1, arg2, arg3, 30.0f);
                break;
            case 1:
                zoom = 0.0f;
                yOffset = 0.0f;
                switch (arg7->unk154) {
                    case 0x3E:
                        break;
                    case 0x6E:
                    case 0x6F:
                        yOffset = D_807FBB40->unk15E;
                        break;
                    case 0x52:
                    case 0x54:
                        yOffset = D_807FBB40->unk15E;
                        break;
                    case 0x59:
                        if (D_807FBB68 & 2) {
                            goto check_target;
                        }
                        if ((cam->unkAC & 0x2000) && !(arg7->unk6A & 0x80)) {
                            yOffset = cam->unk98 + -10.0f;
                        }
                        break;
                    default:
                        zoom = cam->unkA0 / 3.0;
                    check_target:
                        if (D_807FBB64 & 1) {
                            if (cam->unkEF >= 2) {
                                yOffset = 30.0f;
                            }
                            if (cam->unkAC & 0x10000) {
                                renderCallbacksRegister(renderBonusTargetMarker, arg0, 3);
                                zoom = cam->unkA0 / 10.0;
                            }
                        }
                        break;
                }
                if (cam->unkFC != 0) {
                    zoom = 0.0f;
                }
                cam->unk94 += (zoom - cam->unk94) * 0.1;
                camComputeFocusPosOffset(cam, arg4, arg5, arg6, cam->unk94);
                camComputeFollowPos(arg0, arg7, arg1, arg2, arg3, cam->unk94);
                if (D_8076A0A8 == 0x57) {
                    camApplySway(cam, arg1, arg2, arg3, 3.0f, 5.0f, 40.0f, 60.0f);
                }
                *arg5 += yOffset;
                break;
        }
        if (gCamFreezeBelowY != 0 && arg7->unk80 < gCamFreezeBelowY) {
            *arg1 = savedX;
            *arg2 = savedY;
            *arg3 = savedZ;
        } else if (gCamFreezeYAbove != 0 && gCamFreezeYAbove < arg7->unk80) {
            *arg2 = savedY;
        }
    }
}

typedef struct CamYawTarget {
    /* 0x000 */ u8 pad0[0x58];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0xF8];
    /* 0x154 */ u8 unk154;
} CamYawTarget;

typedef struct CamYawState {
    /* 0x00 */ CamYawTarget *unk0;
    /* 0x04 */ u8 pad4[0xA8];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ u8 padB0[2];
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ u8 padB4[0x3F];
    /* 0xF3 */ u8 unkF3;
} CamYawState;

void camTurnYawToward(arg0, arg1, arg2) CamYawState *arg0; s16 arg1; s16 arg2; {
    s16 diff;
    u16 dist;
    f32 scale;
    f32 limit;
    u16 wrap;

    diff = arg2 - arg0->unkB2;
    dist = diff > 0 ? diff : -diff;
    wrap = dist >= 0x801 ? 0x1000 - dist : dist;
    limit = arg1 / 3000.0f * wrap + 5.7f;
    if ((((arg0->unkAC & 4) || arg0->unk0->unk58 == 8) && !(569.0f <= dist && dist <= 3527.0f)) ||
        (D_807FBB64 & 0x8000) || arg0->unk0->unk154 == 0x82) {
        scale = D_807F5CCC;
    } else {
        switch (arg0->unkF3) {
            case 1:
            case 5:
                if (569.0f <= dist && dist <= 3527.0f) {
                    scale = func_80612790((s16)((dist - 569.0f) / 2958.0f * 4096.0f)) * 0.5f + 0.5f;
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
            arg0->unkB2 = arg0->unkB2 + limit;
        } else {
            arg0->unkB2 = arg0->unkB2 - limit;
        }
    }
    arg0->unkB2 &= 0xFFF;
}

typedef struct CamPlayerFlagsS32 {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ s32 unk1F0;
} CamPlayerFlagsS32;

typedef struct CamBlendActor {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[0xE];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 pad6C[0x10];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x30];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x54];
    /* 0x110 */ u8 unk110;
    /* 0x111 */ u8 pad111[0x43];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x1F];
    /* 0x174 */ struct CamBlendState *unk174;
} CamBlendActor;

typedef struct CamBlendState {
    /* 0x00 */ CamBlendActor *unk0;
    /* 0x04 */ u8 pad4[0xC];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[0x32];
    /* 0x44 */ CamTargetBlock unk44;
    /* 0x60 */ u8 pad60[0x24];
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[4];
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ u8 pad90[0x1C];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ u8 padB2[0x36];
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ s16 unkEA;
    /* 0xEC */ u8 padEC[5];
    /* 0xF1 */ u8 unkF1;
    /* 0xF2 */ u8 padF2;
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4[2];
    /* 0xF6 */ u8 unkF6;
    /* 0xF7 */ u8 unkF7;
    /* 0xF8 */ u8 unkF8;
} CamBlendState;

struct CamEyeActor;

void camUpdateFollowBlend(struct CamEyeActor *arg0) {
    CamBlendState *st = ((CamBlendActor *)arg0)->unk174;
    CamBlendActor *X = st->unk0;
    CamPlayerFlagsS32 *xs = (CamPlayerFlagsS32 *)X->unk174;
    CamTargetBlock *tgt = &st->unk44;
    f32 scale;
    f32 k;
    f32 base;
    s32 dist;
    f64 m;
    f64 m2;
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
            if (X->unk110 == 1) {
                dz = X->unk84 - st->unk8C;
                dx = X->unk7C - st->unk84;
                dist = dz * dz + dx * dx;
                m = dist * 0.001;
                m2 = (m > 1.0) ? 1.0 : m;
                gCamEyeBlendRate = m2 * -0.8 + 1.0;
            } else {
                gCamEyeBlendRate = 0.2f;
            }
            gCamFocusBlendRate = 0.3f;
            break;
        case 2:
            gCamEyeBlendRate = 0.3f;
            if (X->unk154 == 0x62) {
                gCamFocusBlendRate = 0.05f;
            } else if (!(st->unkAC & 0x80)) {
                gCamFocusBlendRate = 0.3f;
            }
            break;
        case 1:
            if (st->unkB0 != 0 || st->unkF1 != 0 || D_8076A0A8 == 0x27 || st->unkF6 != 0) {
                gCamEyeBlendRate = 0.3f;
                gCamFocusBlendRate = 0.3f;
            } else if (st->unkF7 != 0) {
                gCamEyeBlendRate = 0.2f;
                gCamFocusBlendRate = 0.2f;
            } else if ((st->unkAC & 4) || X->unk58 == 8) {
                gCamEyeBlendRate = 0.1f;
                gCamFocusBlendRate = 0.2f;
            } else if (X->unk154 == 0x22) {
                gCamEyeBlendRate = 0.4f;
                gCamFocusBlendRate = 0.2f;
            } else if (X->unk154 == 0xE || X->unk154 == 0x59) {
                gCamEyeBlendRate = 0.1f;
                gCamFocusBlendRate = 0.08f;
            } else {
                base = 0.03f;
                if (((CamBlendActor *)arg0)->unkB8 != 0.0f) {
                    k = st->unk10 / ((CamBlendActor *)arg0)->unkB8;
                } else {
                    k = 0.0f;
                }
                k = (k / 20.0 > 1.0) ? 1.0 : k / 20.0;
                if (st->unkF8 != 0) {
                    k += (1.0 - k) * ((u32)(--st->unkF8) / 30.0);
                }
                if ((xs->unk1F0 << 8) < 0 || X->unk154 == 0x1E || X->unk154 == 0x1C || X->unk154 == 0x20 || X->unk154 == 0x1B || X->unk154 == 0x1A || X->unk154 == 0x6E || X->unk154 == 0x3E) {
                    if (!(X->unk6A & 1)) {
                        base = 0.3f;
                    }
                }
                gCamEyeBlendRate = base + (0.6 - base) * k;
                gCamFocusBlendRate = base + (0.4 - base) * k;
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
            /* matching: a second use of `dist` here makes uopt colour it $v0 (a plain temp gets $t0) */
            dist++;
            case 10:
            case 12:
            case 13:
                scale = func_80612794((s16)((1.0 - (f32)st->unkE8 / (f32)st->unkEA) * 1024.0)) * 0.8 + 0.2;
                break;
            case 2:
                scale = func_80612794((s16)((1.0 - (f32)st->unkE8 / (f32)st->unkEA) * 1024.0)) * 0.9 + 0.1;
                break;
        }
        st->unkE8--;
        gCamEyeBlendRate *= scale;
        gCamFocusBlendRate *= scale;
    }
}

f32 camApproachFloat(f32 arg0, f32 arg1, f32 arg2) {
    if (arg0 < arg1) {
        arg0 += arg2;
        if (arg1 < arg0) {
            arg0 = arg1;
        }
    } else {
        arg0 -= arg2;
        if (arg0 < arg1) {
            arg0 = arg1;
        }
    }
    return arg0;
}

typedef struct CamEyeActor CamEyeActor;

typedef struct CamEyeState {
    /* 0x00 */ CamEyeActor *unk0;
    /* 0x04 */ u8 pad4[0xC];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[0x4E];
    /* 0x60 */ f32 unk60;
    /* 0x64 */ u8 pad64[0x20];
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ u8 pad90[0x1C];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ u8 padB2[0x1E];
    /* 0xD0 */ f32 unkD0;
    /* 0xD4 */ u8 padD4[0x10];
    /* 0xE4 */ f32 unkE4;
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ u8 padEA[7];
    /* 0xF1 */ u8 unkF1;
    /* 0xF2 */ u8 padF2;
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4[2];
    /* 0xF6 */ u8 unkF6;
} CamEyeState;

struct CamEyeActor {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x30];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x2A];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[6];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[2];
    /* 0xF2 */ s16 unkF2;
    /* 0xF4 */ u8 padF4[8];
    /* 0xFC */ u8 unkFC;
    /* 0xFD */ u8 padFD[0x13];
    /* 0x110 */ u8 unk110;
    /* 0x111 */ u8 pad111[0x63];
    /* 0x174 */ CamEyeState *unk174;
};

void camUpdateFollowBlend(CamEyeActor *);
f32 camApproachFloat(f32, f32, f32);
void camUpdateFocusPos(CamEyeActor *, f32, f32 *, f32 *, f32 *);
void camUpdateEyePos(CamEyeActor *, f32, f32 *, f32 *, f32 *);

#define CAM_ABSDIFF(a, b) (((a) < (b)) ? (b) - (a) : (a) - (b))
#define CAM_FOLLOW_SPEED_RAW (CAM_ABSDIFF(st->unkD0, X->unk80) * 0.08)
#define CAM_FOLLOW_SPEED (CAM_FOLLOW_SPEED_RAW > 0.03 ? CAM_FOLLOW_SPEED_RAW : 0.03)

void camUpdateFollow(CamEyeActor *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
    s32 unused;
    CamEyeState *st = arg0->unk174;
    CamEyeActor *X = st->unk0;
    f32 dist;
    f32 spd;
    f32 t;

    spd = CAM_FOLLOW_SPEED < 1.0 ? CAM_FOLLOW_SPEED : 1.0;
    camUpdateFollowBlend(arg0);
    st->unkE4 = st->unkE4 + (spd - st->unkE4) * 0.1;
    dist = sqrtf((arg0->unk84 - st->unk8C) * (arg0->unk84 - st->unk8C) +
                 (arg0->unk7C - st->unk84) * (arg0->unk7C - st->unk84));
    if (dist < 0.1) {
        dist = 0.0f;
    }
    if (arg0->unkB8 < dist) {
        arg0->unkB8 = camApproachFloat(arg0->unkB8, dist, st->unk60);
    } else {
        arg0->unkB8 = dist;
    }
    arg0->unkEE = mathAngleBetweenPoints2D(arg0->unk7C, arg0->unk84, st->unk84, st->unk8C);
    arg0->unkE6 = arg0->unkEE;
    if (st->unkB0 != 0 || st->unkF1 != 0 || D_8076A0A8 == 0x27 || st->unkF6 != 0 || st->unkE8 != 0 ||
        (st->unkAC & 0x100) || st->unkF3 != 1) {
        st->unkE4 = t = gCamEyeBlendRate;
    } else {
        t = (st->unkE4 > 1.0) ? 1.0 : st->unkE4;
    }
    camUpdateEyePos(arg0, t, arg1, arg2, arg3);
    if (X->unk110 == 1 && st->unk10 != 0) {
        camUpdateFocusPos(arg0, 0.5f, arg4, arg5, arg6);
    } else if (st->unkF3 == 1) {
        camUpdateFocusPos(arg0, t, arg4, arg5, arg6);
    } else {
        camUpdateFocusPos(arg0, gCamFocusBlendRate, arg4, arg5, arg6);
    }
}



void camUpdateEyePos(CamEyeActor *arg0, f32 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    CamEyeState *st = arg0->unk174;
    s16 ang;
    f32 savedX;
    f32 savedZ;
    f32 spare;
    f32 clampY;

    if (arg0->unkFC) {
        ang = arg0->unkF2;
    } else {
        ang = arg0->unkEE;
    }
    savedX = st->unk84;
    savedZ = st->unk8C;
    switch (st->unkF3) {
        case 1:
        case 5:
        case 10:
        case 12:
        case 13:
            st->unk84 += gCamEyeBlendRate * arg0->unkB8 * func_80612794(ang);
            st->unk8C += gCamEyeBlendRate * arg0->unkB8 * func_80612790(ang);
            st->unk88 = (arg0->unk80 - st->unk88) * arg1 + st->unk88;
            if (st->unkF3 != 12 && !(D_807FBB68 & 2)) {
                camResolveWallCollision((CamActor *)arg0, savedX, savedZ, &st->unk84, st->unk88, &st->unk8C, gCamEyeBlendRate * arg0->unkB8);
            }
            *arg2 = *arg2 + (st->unk84 - *arg2) * 0.3;
            *arg3 = *arg3 + (st->unk88 - *arg3) * 0.3;
            *arg4 = *arg4 + (st->unk8C - *arg4) * 0.3;
            if (st->unkF3 != 12) {
                clampY = (*arg3 < st->unk0->unk80) ? st->unk0->unk80 : *arg3;
                if (camFloorSnap(arg0, st, *arg2, &clampY, *arg4, 1) != 0 || clampY < *arg3) {
                    *arg3 = clampY;
                }
            }
            break;
        default:
            st->unk84 = *arg2 = *arg2 + (arg0->unk7C - *arg2) * gCamEyeBlendRate;
            st->unk88 = *arg3 = *arg3 + (arg0->unk80 - *arg3) * gCamEyeBlendRate;
            st->unk8C = *arg4 = *arg4 + (arg0->unk84 - *arg4) * gCamEyeBlendRate;
            break;
    }
}

extern s16 gCamZoneMinX;
extern s16 gCamZoneMinZ;
extern s16 gCamZoneGridWidth;

typedef struct CamFocusTarget {
    /* 0x00 */ u8 pad0[0x78];
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
} CamFocusTarget;

void camUpdateFocusPos(CamEyeActor *arg0, f32 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    CamFocusTarget *st = (CamFocusTarget *)arg0->unk174;

    *arg2 = *arg2 + (st->unk78 - *arg2) * gCamFocusBlendRate;
    *arg3 = *arg3 + (st->unk7C - *arg3) * arg1;
    *arg4 = *arg4 + (st->unk80 - *arg4) * gCamFocusBlendRate;
}

s32 camIsCellNeighbour(s16 arg0, s16 arg1) {
    s16 i;
    s16 j;

    for (i = -1; i < 2; i++) {
        for (j = -1; j < 2; j++) {
            if (arg0 == arg1 + i * gCamZoneGridWidth + j) {
                return 1;
            }
        }
    }
    return 0;
}

typedef struct CamZoneBound {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 pad12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[6];
} CamZoneBound; // size = 0x1C

typedef struct CamPathZoneBounds {
    /* 0x00 */ u8 pad0[0xC0];
    /* 0xC0 */ s16 unkC0;
    /* 0xC2 */ u8 padC2[2];
    /* 0xC4 */ CamZoneBound *unkC4;
} CamPathZoneBounds;

#define CAM_ZONE_BOUNDS_PATH ((CamPathZoneBounds *)gCamActivePaths)

s16 camGetZoneCell(s32 arg0) {
    CamZoneBound *e = &CAM_ZONE_BOUNDS_PATH->unkC4[arg0];

    return (e->unk10 - gCamZoneMinX) / 400 + (e->unk14 - gCamZoneMinZ) / 400 * gCamZoneGridWidth;
}

void camGetZoneBounds(s16 *arg0, s16 *arg1, s16 *arg2) {
    s16 i;

    *arg0 = 0x7FFF;
    *arg2 = 0x7FFF;
    *arg1 = -0x8000;
    for (i = 0; i < CAM_ZONE_BOUNDS_PATH->unkC0; i++) {
        if (CAM_ZONE_BOUNDS_PATH->unkC4[i].unk10 < *arg0) {
            *arg0 = CAM_ZONE_BOUNDS_PATH->unkC4[i].unk10;
        }
        if (*arg1 < CAM_ZONE_BOUNDS_PATH->unkC4[i].unk10) {
            *arg1 = CAM_ZONE_BOUNDS_PATH->unkC4[i].unk10;
        }
        if (CAM_ZONE_BOUNDS_PATH->unkC4[i].unk14 < *arg2) {
            *arg2 = CAM_ZONE_BOUNDS_PATH->unkC4[i].unk14;
        }
    }
    *arg0 -= 0xC8;
    *arg1 += 0xC8;
    *arg2 -= 0xC8;
}

typedef struct CamPathZoneEntries {
    /* 0x00 */ u8 pad0[0xC0];
    /* 0xC0 */ s16 unkC0;
    /* 0xC2 */ u8 padC2[2];
    /* 0xC4 */ CamZoneEntry *unkC4;
} CamPathZoneEntries;

void *heapAlloc(s32);
void heapFree(void *);

#define CAM_ZONE_ENTRIES_PATH ((CamPathZoneEntries *)gCamActivePaths)

#ifdef NON_MATCHING
void camInitZones(void) {
    s16 i;
    s16 j;
    s16 k;
    s16 key;
    s16 idx;

    camGetZoneBounds(&gCamZoneMinX, &gCamZoneMaxX, &gCamZoneMinZ);
    gCamZoneMaxX = gCamZoneMaxX / 400 * 400 + 400;
    gCamZoneMinX = gCamZoneMinX / 400 * 400;
    gCamZoneGridWidth = (gCamZoneMaxX - gCamZoneMinX) / 400;
    gCamZoneMinZ = gCamZoneMinZ / 400 * 400;
    if (gCamZoneSorted != NULL) {
        heapFree(gCamZoneSorted);
    }
    gCamZoneSorted = heapAlloc(CAM_ZONE_ENTRIES_PATH->unkC0 * 4 + 4);
    for (i = 0; i < CAM_ZONE_ENTRIES_PATH->unkC0; i++) {
        CAM_ZONE_SORT[i].unk0 = i;
        CAM_ZONE_SORT[i].unk2 = camGetZoneCell(i);
    }
    for (i = 1; i < CAM_ZONE_ENTRIES_PATH->unkC0; i++) {
        key = CAM_ZONE_SORT[i].unk2;
        idx = CAM_ZONE_SORT[i].unk0;
        j = i;
        while (j > 0 &&
               (key < CAM_ZONE_SORT[j - 1].unk2 ||
                (key == CAM_ZONE_SORT[j - 1].unk2 &&
                 CAM_ZONE_ENTRIES_PATH->unkC4[CAM_ZONE_SORT[j - 1].unk0].unk18 < CAM_ZONE_ENTRIES_PATH->unkC4[CAM_ZONE_SORT[j].unk0].unk18))) {
            CAM_ZONE_SORT[j].unk0 = CAM_ZONE_SORT[j - 1].unk0;
            CAM_ZONE_SORT[j].unk2 = CAM_ZONE_SORT[j - 1].unk2;
            j--;
        }
        if (j != i) {
            CAM_ZONE_SORT[j].unk0 = idx;
            CAM_ZONE_SORT[j].unk2 = key;
        }
    }
    gCamZoneGroupCount = 1;
    for (i = CAM_ZONE_ENTRIES_PATH->unkC0 - 1; i > 0; i--) {
        if (CAM_ZONE_SORT[i].unk2 != CAM_ZONE_SORT[i - 1].unk2) {
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
    for (i = 1; i < CAM_ZONE_ENTRIES_PATH->unkC0; i++) {
        if (CAM_ZONE_SORT[i].unk2 != CAM_ZONE_SORT[i - 1].unk2) {
            CAM_ZONE_GROUP[k].unk0 = CAM_ZONE_SORT[i].unk2;
            CAM_ZONE_GROUP[k].unk2 = i;
            k++;
        }
    }
    CAM_ZONE_GROUP[k].unk0 = -1;
    CAM_ZONE_GROUP[k].unk2 = CAM_ZONE_ENTRIES_PATH->unkC0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/camInitZones.s")
#endif

typedef struct CamSecondNode {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x5E];
    /* 0xE6 */ s16 unkE6;
} CamSecondNode;

typedef struct CamSecondState {
    /* 0x00 */ CamSecondNode *unk0;
    /* 0x04 */ CamSecondNode *unk4;
    /* 0x08 */ u8 pad8[0xA];
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[0x96];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ u8 padB0[2];
    /* 0xB2 */ s16 unkB2;
} CamSecondState;

CamSecondNode *spawnNodeActivate(s32, s32);

void camSetSecondTarget(CamActor *arg0, s16 arg1, s16 arg2) {
    CamSecondState *st = (CamSecondState *)arg0->unk174;

    st->unk4 = spawnNodeActivate(1, 0);
    if (st->unk4 != NULL) {
        st->unkB2 = mathAngleBetweenPoints2D(st->unk4->unk7C, st->unk4->unk84, st->unk0->unk7C, st->unk0->unk84);
    } else {
        st->unkB2 = st->unk0->unkE6;
    }
    if (arg1 != 0) {
        st->unk12 = arg1;
        st->unk14 = arg2;
        st->unkB2 = mathAngleBetweenPoints2D(arg1, arg2, st->unk0->unk7C, st->unk0->unk84);
    }
    st->unkAC |= 0x10004;
}

void camClearSecondTarget(CamActor *arg0) {
    CamSecondState *st = (CamSecondState *)arg0->unk174;

    st->unk4 = NULL;
    st->unkAC &= ~0x10004;
}

void func_806264DC(void *, CamPathData *, u8);

void camLoadPathTable(void *arg0, CamPathData *arg1, u8 arg2) {
    func_806264DC(arg0, arg1, arg2);
    arg1->unkD8[48].unk1 = 0xE;
    arg1->unkD8[49].unk1 = 0xB;
    arg1->unkD8[50].unk1 = 6;
    arg1->unkD8[51].unk1 = 0x11;
    arg1->unkD8[52].unk1 = 7;
    arg1->unkD8[53].unk1 = 8;
}

void *assetLoad(s32, s32, s32, s32);
void splineSetBasisTension(f32);
void assetFreeBuffer(void *, s32, s32);
void camInitZones(void);

void camInit(void *arg0) {
    void *buf = assetLoad(8, 0, 1, 1);

    splineSetBasisTension(0.5f);
    gCamActivePaths = &gCamMapPaths;
    gCamPathFlags = 0;
    gCamZoneGroups = NULL;
    gCamZoneSorted = NULL;
    camLoadPathTable(arg0, gCamActivePaths, 1);
    camLoadPathTable(buf, gCamGlobalPathsPtr, 0);
    assetFreeBuffer(buf, 0x10B4, 0xC);
    camInitZones();
    D_807476B4 = 0;
    gCamFreezeBelowY = 0;
    gCamFreezeYAbove = 0;
    D_807F5CCC = 6.0f;
    if (D_807FBB64 & 1) {
        D_807F5CCC = 12.0f;
    }
    switch (D_8076A0A8) {
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

void camCopyVec3s(s16 *arg0, s16 *arg1) {
    *arg0++ = *arg1++;
    *arg0++ = *arg1++;
    *arg0++ = *arg1++;
}

void *memcpy(void *, const void *, u32);

void *camCopyPathPayload(u8 *arg0, void *arg1, u16 arg2) {
    memcpy(arg1, arg0 + 4, arg2);
    return arg0 + 4 + arg2;
}

#ifdef NON_MATCHING
typedef struct CamPathSeg {
    /* 0x00 */ s16 a[3];
    /* 0x06 */ s16 b[3];
    /* 0x0C */ s16 c[3];
} CamPathSeg; // size = 0x12

typedef struct CamPathZoneRaw {
    /* 0x00 */ s16 v[14];
} CamPathZoneRaw; // size = 0x1C

typedef struct CamPathKeyPosLookRaw {
    /* 0x00 */ s16 v[7];
} CamPathKeyPosLookRaw; // size = 0xE

typedef struct CamPathKeyPosRaw {
    /* 0x00 */ s16 v[4];
} CamPathKeyPosRaw; // size = 0x8

typedef struct CamPathHeadRaw {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 pad2;
    /* 0x04 */ CamPathSeg *unk4;
} CamPathHeadRaw; // size = 0x8

typedef struct CamPathStepListLoad {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 pad2;
    /* 0x4 */ s16 *unk4;
    /* 0x8 */ s16 *unk8;
} CamPathStepListLoad; // size = 0xC

typedef struct CamPathLoad {
    /* 0x00 */ CamPathHeadRaw heads[24];
    /* 0xC0 */ s16 unkC0;
    /* 0xC2 */ s16 padC2;
    /* 0xC4 */ CamPathZoneRaw *unkC4;
    /* 0xC8 */ s8 *unkC8;
    /* 0xCC */ s16 unkCC;
    /* 0xCE */ s16 padCE;
    /* 0xD0 */ CamPathStepListLoad *unkD0;
    /* 0xD4 */ s16 unkD4;
    /* 0xD6 */ s16 padD6;
    /* 0xD8 */ CamPathPoint *unkD8;
} CamPathLoad;

void *heapAlloc(s32);
void heapClearBlock(void *);
void camCopyVec3s(s16 *, s16 *);

#define CAM_LOAD_SRC ((s16 *)arg0)
#define CAM_LOAD_PATH ((CamPathLoad *)arg1)

void func_806264DC(arg0, arg1, arg2) void *arg0; CamPathData *arg1; volatile u8 arg2; {
    s16 i;
    s16 j;
    s16 cnt;
    s16 *hdr;
    u8 *data;
    CamPathHeadRaw *h;
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
    s32 padg3;
    s32 skip;

    hdr = CAM_LOAD_SRC;
    data = arg0 != NULL ? (u8 *)arg0 + 0x30 : NULL;
    for (i = 0; i < 0x18; i++) {
        h = &CAM_LOAD_PATH->heads[i];
        cnt = h->unk0 = hdr != NULL ? *hdr++ : 0;
        if (arg2 != 0) {
            h->unk4 = heapAlloc(cnt * 0x12U);
            for (j = 0; j < cnt; j++) {
                dst = &h->unk4[j];
                buf = *(CamPathSeg *)data;
                data += 0x12;
                camCopyVec3s(dst->a, buf.a);
                camCopyVec3s(dst->c, buf.c);
                camCopyVec3s(dst->b, buf.b);
            }
        }
    }
    hdr = (s16 *)data;
    cnt = CAM_LOAD_PATH->unkC0 = hdr != NULL ? *hdr++ : 0;
    if (arg2 != 0) {
        CAM_LOAD_PATH->unkC8 = heapAlloc(cnt);
        CAM_LOAD_PATH->unkC4 = heapAlloc(cnt * 0x1CU);
        s = hdr;
        for (i = 0; i < cnt; i++) {
            CAM_LOAD_PATH->unkC8[i] = mapChunkFindByPosition(s[8], s[9], s[10], 0);
            s += 0xE;
            CAM_LOAD_PATH->unkC4[i] = *(CamPathZoneRaw *)(s - 0xE);
        }
        hdr = s;
    }
    i = 0;
    cnt = CAM_LOAD_PATH->unkCC = hdr != NULL ? *hdr++ : 0;
    CAM_LOAD_PATH->unkD0 = heapAlloc(cnt * 0xCU);
    for (i = 0; i < cnt; i++) {
        m = *hdr++;
        k = m;

        CAM_LOAD_PATH->unkD0[i].unk0 = m;
        CAM_LOAD_PATH->unkD0[i].unk4 = heapAlloc(m * 2);
        CAM_LOAD_PATH->unkD0[i].unk8 = heapAlloc(m * 2);
        for (j = 0; j < k; j++) {
            CAM_LOAD_PATH->unkD0[i].unk4[j] = *hdr++;
            CAM_LOAD_PATH->unkD0[i].unk8[j] = *hdr++;
        }
    }
    i = 0;
    cnt = CAM_LOAD_PATH->unkD4 = hdr != NULL ? *hdr++ : 0;
    CAM_LOAD_PATH->unkD8 = heapAlloc(0x6400);
    heapClearBlock(CAM_LOAD_PATH->unkD8);
    rd = (u8 *)hdr;
    if (cnt != 0) {
        do {
            skip = 0;
            pt = &CAM_LOAD_PATH->unkD8[i];
            pt->unk1 = rd[1];
            CAM_LOAD_PATH->unkD8[i].unk0 = rd[0];
            pt = (CamPathPoint *)&pt->u.spline;
            u = (CamPathPointSpline *)pt;
            switch (CAM_LOAD_PATH->unkD8[i].unk1) {
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
                    u->unk4 = heapAlloc(u->unk0 * 0xEU);
                    for (; j < u->unk0; j++) {
                        ((CamPathKeyPosLookRaw *)u->unk4)[j] = *(CamPathKeyPosLookRaw *)s;
                        s += 7;
                    }
                    rd = (u8 *)s;
                    break;
                case 5:
                    s = (s16 *)(rd + 0x14);
                    j = 0;
                    u->unk0 = *(s16 *)(rd + 4);
                    u->unk4 = heapAlloc(u->unk0 * 8U);
                    for (; j < u->unk0; j++) {
                        ((CamPathKeyPosRaw *)u->unk4)[j] = *(CamPathKeyPosRaw *)s;
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
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_806264DC.s")
#endif

s32 camDistance3D(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s64 unused0;
    s64 unused1;
    s64 unused2;

    return sqrtf((s64)(arg0 - arg3) * (arg0 - arg3) + (s64)(arg1 - arg4) * (arg1 - arg4) +
                 (s64)(arg2 - arg5) * (arg2 - arg5));
}

s16 camClampEyeAngle(CamState *arg0, f32 *arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5) {
    s16 ang;
    s16 mid;
    s16 a;
    s16 b;
    s16 c;
    s16 d1;
    s16 d2;
    u8 clamped;

    ang = mathAngleBetweenPoints2D(*arg1, *arg2, arg3, arg4);
    mid = arg0->unkC8 + (arg0->unkCA - arg0->unkC8) * 0.5;
    clamped = 0;
    if (arg0->unkC8 < arg0->unkCA) {
        mid = (mid + 0x800) & 0xFFF;
    }
    a = (arg0->unkC8 - mid) & 0xFFF;
    b = (arg0->unkCA - mid) & 0xFFF;
    c = (ang - mid) & 0xFFF;
    d1 = (c < a) ? a - c : c - a;
    d2 = (c < b) ? b - c : c - b;
    if (a < b) {
        if (a < c && c < b) {
            if (d1 < d2) {
                ang = arg0->unkC8;
            } else {
                ang = arg0->unkCA;
            }
            clamped = 1;
        }
    } else {
        if (c < a && b < c) {
            if (d1 < d2) {
                ang = arg0->unkC8;
            } else {
                ang = arg0->unkCA;
            }
            clamped = 1;
        }
    }
    if (arg5 < 40.0f) {
        ang = mathAngleLerp(mid, ang, arg5 / 40.0);
        gCamFocusBlendRate = arg5 / 40.0 * 0.25 + 0.05;
        if (!clamped) {
            arg5 = (arg5 > 1.0) ? arg5 : 1.0;
        }
        arg0->unkAC |= 0x80;
    }
    *arg1 = func_80612794(ang) * arg5 + arg3;
    *arg2 = func_80612790(ang) * arg5 + arg4;
    return ang;
}

typedef struct CamPlayerRecView {
    /* 0x000 */ u8 pad0[8];
    /* 0x008 */ Mtx m8[2];
    /* 0x088 */ Mtx m88[2];
    /* 0x108 */ u8 pad108[0x80];
    /* 0x188 */ u16 unk188;
    /* 0x18A */ u8 pad18A[0xE6];
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ u8 pad274[4];
    /* 0x278 */ s16 unk278;
    /* 0x27A */ s16 unk27A;
    /* 0x27C */ u8 pad27C[0x74];
} CamPlayerRecView; // size = 0x2F0

extern u8 D_807444FC;
void camTransformPoint(Mtx *, f32, f32, f32, f32, f32 *, f32 *, f32 *, f32 *);

s32 camProjectToScreen(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, Mtx *arg5, f32 arg6, u8 arg7) {
    f32 w;
    f32 scale;

    w = 1.0f;
    if (arg5 != NULL) {
        camTransformPoint(arg5, arg0, arg1, arg2, w, &arg0, &arg1, &arg2, &w);
    }
    camTransformPoint(&((CamPlayerRecView *)D_807FC924)[arg7].m8[D_807444FC], arg0, arg1, arg2, w, &arg0, &arg1, &arg2, &w);
    if (0.0 <= arg2) {
        *arg3 = 16384.0f;
        *arg4 = 16384.0f;
        return 1;
    }
    camTransformPoint(&((CamPlayerRecView *)D_807FC924)[arg7].m88[D_807444FC], arg0, arg1, arg2, w, &arg0, &arg1, &arg2, &w);
    scale = ((CamPlayerRecView *)D_807FC924)[arg7].unk188 / 65535.0;
    arg0 *= scale;
    arg1 *= scale;
    w *= scale;
    arg0 /= w;
    arg1 /= w;
    arg0 = ((CamPlayerRecView *)D_807FC924)[arg7].unk278 * 0.5 * arg0;
    arg1 = ((CamPlayerRecView *)D_807FC924)[arg7].unk27A * 0.5 * arg1;
    arg0 = ((CamPlayerRecView *)D_807FC924)[arg7].unk270 + ((CamPlayerRecView *)D_807FC924)[arg7].unk278 * 0.5 + arg0;
    arg1 = ((CamPlayerRecView *)D_807FC924)[arg7].unk272 + ((CamPlayerRecView *)D_807FC924)[arg7].unk27A * 0.5 + arg1;
    arg1 = (((CamPlayerRecView *)D_807FC924)[arg7].unk27A - (arg1 - ((CamPlayerRecView *)D_807FC924)[arg7].unk272)) + ((CamPlayerRecView *)D_807FC924)[arg7].unk272;
    if (16384.0f <= (arg0 > 0.0f ? arg0 : -arg0)) {
        arg0 = ((0.0f <= arg0) ? 1 : -1) << 14;
    }
    if (16384.0f <= (arg1 > 0.0f ? arg1 : -arg1)) {
        arg1 = ((0.0f <= arg1) ? 1 : -1) << 14;
    }
    arg0 *= arg6;
    arg1 *= arg6;
    *arg3 = arg0;
    *arg4 = arg1;
    return 0;
}

void camTransformPoint(Mtx *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 *arg5, f32 *arg6, f32 *arg7, f32 *arg8) {
    f32 m[4][4];

    guMtxL2F(m, arg0);
    *arg5 = (m[0][0] * arg1 + m[1][0] * arg2 + m[2][0] * arg3) + m[3][0];
    *arg6 = (m[0][1] * arg1 + m[1][1] * arg2 + m[2][1] * arg3) + m[3][1];
    *arg7 = (m[0][2] * arg1 + m[1][2] * arg2 + m[2][2] * arg3) + m[3][2];
    *arg8 = (m[0][3] * arg1 + m[1][3] * arg2 + m[2][3] * arg3) + m[3][3];
}

f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);

void camPolarFromPoints(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    *arg0 = mathAngleBetweenPointsDeg(arg5, arg7, arg2, arg4) * 0.017453292f;
    *arg1 = func_80611BB4(arg3 - arg6, sqrtf((arg2 - arg5) * (arg2 - arg5) + (arg4 - arg7) * (arg4 - arg7)));
}

void func_8062754C(f32 arg0) {
    s16 i;

    camClosestPointOnSegment(((CamPlayerRec *)D_807FC924)->unk228, ((CamPlayerRec *)D_807FC924)->unk22C, ((CamPlayerRec *)D_807FC924)->unk230, 517.0f, 312.0f, 346.0f, 347.0f, 312.0f, 494.0f, &((CamPlayerRec *)D_807FC924)->unk210, &((CamPlayerRec *)D_807FC924)->unk214, &((CamPlayerRec *)D_807FC924)->unk218);
    ((CamPlayerRec *)D_807FC924)->unk210 = (((CamPlayerRec *)D_807FC924)->unk210 - ((CamPlayerRec *)D_807FC924)->unk228) * arg0 + ((CamPlayerRec *)D_807FC924)->unk228;
    ((CamPlayerRec *)D_807FC924)->unk214 = (((CamPlayerRec *)D_807FC924)->unk214 - ((CamPlayerRec *)D_807FC924)->unk22C) * arg0 + ((CamPlayerRec *)D_807FC924)->unk22C;
    ((CamPlayerRec *)D_807FC924)->unk218 = (((CamPlayerRec *)D_807FC924)->unk218 - ((CamPlayerRec *)D_807FC924)->unk230) * arg0 + ((CamPlayerRec *)D_807FC924)->unk230;
    for (i = 1; i < D_807FC928; i++) {
        ((CamPlayerRec *)D_807FC924)[i].unk210 = ((CamPlayerRec *)D_807FC924)->unk210;
        ((CamPlayerRec *)D_807FC924)[i].unk214 = ((CamPlayerRec *)D_807FC924)->unk214;
        ((CamPlayerRec *)D_807FC924)[i].unk218 = ((CamPlayerRec *)D_807FC924)->unk218;
    }
}

f32 func_806276AC(void) {
    s16 i;

    for (i = 0; i < D_807FC928;) {
        ((CamPlayerRec *)D_807FC924)[i].unk228 = 586.0f;
        ((CamPlayerRec *)D_807FC924)[i].unk22C = 205.0f;
        ((CamPlayerRec *)D_807FC924)[i].unk230 = 584.0f;
        i++;
    }
    return 1.0f;
}

typedef struct CamResumeState {
    /* 0x00 */ CamActor *unk0;
    /* 0x04 */ u8 pad4[0x74];
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ u8 pad84[0x10];
    /* 0x94 */ f32 unk94;
    /* 0x98 */ u8 pad98[8];
    /* 0xA0 */ f32 unkA0;
    /* 0xA4 */ u8 padA4[0xE];
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ s16 unkB4;
    /* 0xB6 */ u8 padB6[2];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x34];
    /* 0xF0 */ u8 unkF0;
    /* 0xF1 */ u8 unkF1;
    /* 0xF2 */ u8 padF2;
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4[7];
    /* 0xFB */ u8 unkFB;
} CamResumeState;

void camRestoreYaw(CamActor *);

s32 func_8062773C(CamActor *arg0) {
    CamResumeState *st = (CamResumeState *)arg0->unk174;
    s16 ang;

    ang = st->unkB2 + 0x800;
    if (st->unkF0 != 0) {
        camSetZoomLevel(arg0, st->unkF0);
    } else {
        camSetZoomLevel(arg0, 1);
    }
    ((CamActorHeight *)arg0)->unkB4 = st->unkB8;
    st->unkF1 = 0xB;
    st->unkF3 = 1;
    camRestoreYaw(arg0);
    st->unk94 = st->unkA0 / 3.0;
    D_807FC924[st->unkFB].unk27C = 45.0f;
    st->unk78 = st->unk0->unk7C;
    st->unk7C = st->unk0->unk80 + st->unk0->unk15E;
    st->unk80 = st->unk0->unk84;
    func_8061B840((CamStateSettle *)st, 0xB);
    sfxStopSlotSound(st->unk0, 0);
    st->unk0->unk6A &= ~0x2000;
    return ang;
}

void camSaveYaw(CamActor *arg0) {
    CamResumeState *st = (CamResumeState *)arg0->unk174;

    st->unkB4 = st->unkB2;
}

void camRestoreYaw(CamActor *arg0) {
    CamResumeState *st = (CamResumeState *)arg0->unk174;

    st->unkB2 = st->unkB4;
    arg0->unk15F = (f64)st->unkB2 / 4095.0 * 255.0;
}

void camStartPathNearWall(CamActor *arg0, u8 arg1, u8 arg2, u8 arg3) {
    s16 sp2E;
    s16 sp2C;

    if (collisionTestSphere(arg0->unk7C, arg0->unk80, arg0->unk84, 80.0f, &sp2E, &sp2C, 1, 0xBC)) {
        arg0->unkE6 = mathAngleBetweenPoints2D(((CamPlayerRec *)D_807FC924)->unk210, ((CamPlayerRec *)D_807FC924)->unk218, arg0->unk7C, arg0->unk84);
        camStartPath(arg0, arg2, arg3);
    } else {
        camStartPath(arg0, arg1, arg3);
    }
}
