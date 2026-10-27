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

typedef struct CamSplineKeyE {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 unk8;
    /* 0xA */ s16 unkA;
    /* 0xC */ u8 unkC;
    /* 0xD */ s8 unkD;
} CamSplineKeyE; // size = 0xE

typedef struct CamSplineKey8 {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ s8 unk7;
} CamSplineKey8; // size = 0x8

typedef struct CamPathPos {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 unk8;
    /* 0xA */ s16 unkA;
    /* 0xC */ u8 unkC;
    /* 0xD */ u8 unkD;
} CamPathPos;

typedef struct CamPathSpline {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ void *unk4;
} CamPathSpline;

typedef struct CamPathPoint {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ union {
        CamPathPos pos;
        CamPathSpline spline;
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
extern f32 D_807476A0;
extern f32 D_807476A4;
extern f32 D_807476A8;
extern u8 D_807476B4;
extern s16 D_807476B8;
extern s16 D_807476BC;
extern s16 D_807476E4;
extern s16 D_807476F4;
extern CamPathData *D_807476FC;
extern u8 D_80750AB8;
extern s32 D_8076A064;
extern s32 D_8076A0A8;
extern u8 D_8076A0B1;
extern u8 D_8076A0B3;
extern s16 D_807F5CD0;
extern void *D_807F5CE8;
extern s16 D_807F5CEC;
extern s16 D_807F5CEE;
extern u16 D_807F5CF0;
extern u16 D_807F5CF2;
extern u16 D_807F5CF4;
extern u8 D_807F5CFA;
extern f32 D_807F5CFC;
extern f32 D_807F5D00;
extern f32 D_807F5D18;
extern f32 D_807F5D1C;
extern f32 D_807F5D20;
extern f32 D_807F5D24;
extern f32 D_807F5D28;
extern f32 D_807F5D2C;
extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern s32 D_807FBB60;
extern s32 D_807FBB64;
extern s32 D_807FBB68;
extern Struct807FC924 *D_807FC924;
extern u8 D_807FC928;

void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
f32 func_80612790(s16);
f32 func_80612794(s16);
f32 sinApprox(f32);
void func_8061B660(CamState *, f32 *, f32 *, f32 *, f32, f32, f32, f32);
void func_8061B7E0(CamActor *, CamState *, f32, f32);
void func_8061EDA0(CamState *, f32 *, f32 *, f32 *, s32, s32);
void func_8061F164(CamState *, s32);
void func_8061F2B8(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *);
s32 func_8061F53C(CamActor *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
void func_8062133C(CamActor *, CamActor *, f32 *, f32 *, f32 *, f32);
void func_80621E9C(CamState *, f32 *, f32 *, f32 *);
void func_8062210C(CamState *, f32 *, f32 *, f32 *, f32);
void func_8062217C(CamActor *, s32);
void func_80622334(CamActor *, s16);
void func_806224CC(CamActor *, CamActor *);
void func_806225D4(CamActor *, f32 *, f32 *, f32 *);
void func_806227F0(CamState *, f32 *, f32 *, f32 *);
void func_806228BC(CamActor *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
f32 func_80622ABC(f32, f32, f32);
void func_80626CAC(CamState *, f32 *, f32 *, f32, f32, f32);
f32 splineEvalCubic(f64, f32, f32, f32, f32);
s32 func_8062773C(CamActor *);
s16 mathAngleLerp(s16, s16, f32);
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);
f32 mathCalculatePitchAngle(f32, f32, f32, f32, f32, f32, s32);
void renderBonusTargetMarker();
void renderCallbacksRegister(void *, void *, s32);
f32 sqrtf(f32);

#define CAM_LERP(a, b, t) ((a) + ((b) - (a)) * (t))

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061B4B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061B4E4.s")

typedef struct CamAPlayer {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ u8 pad214[4];
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0xC];
    /* 0x228 */ f32 unk228;
    /* 0x22C */ u8 pad22C[4];
    /* 0x230 */ f32 unk230;
    /* 0x234 */ u8 pad234[0x90];
    /* 0x2C4 */ f32 unk2C4;
    /* 0x2C8 */ s16 unk2C8;
    /* 0x2CA */ u8 pad2CA[6];
    /* 0x2D0 */ f32 unk2D0;
    /* 0x2D4 */ u8 pad2D4[0x15];
    /* 0x2E9 */ u8 unk2E9;
    /* 0x2EA */ u8 pad2EA[6];
} CamAPlayer; // size = 0x2F0

void func_8061B5C4(s16 arg0) {
    ((CamAPlayer *)D_807FC924)[arg0].unk2D0 = ((CamAPlayer *)D_807FC924)[arg0].unk2C4;
    ((CamAPlayer *)D_807FC924)[arg0].unk2E9 = 0x18;
}

typedef struct CamAState {
    /* 0x00 */ CamActor *unk0;
    /* 0x04 */ u8 pad4[0xEF];
    /* 0xF3 */ u8 unkF3;
} CamAState;

void func_8061B610(CamActor *arg0) {
    CamAState *st = (CamAState *)arg0->unk174;

    arg0->unk7C = st->unk0->unk7C;
    arg0->unk80 = st->unk0->unk80 + 170.0f;
    arg0->unk84 = st->unk0->unk84;
    st->unkF3 = 7;
}

void func_8061B650(CamActor *arg0) {
    CamState *st = arg0->unk174;

    st->unkF3 = 9;
}

typedef struct CamAB2 {
    /* 0x00 */ u8 pad0[0xB2];
    /* 0xB2 */ s16 unkB2;
} CamAB2;

void func_8061B660(CamState *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 sp1C;
    f32 sp18;

    sp18 = func_80612794(((CamAB2 *)arg0)->unkB2 + 0x400);
    *arg1 += arg4 * func_80612794((u32)D_8076A064 * arg6) * sp18;
    sp18 = func_80612790(((CamAB2 *)arg0)->unkB2 + 0x400);
    *arg3 += arg4 * func_80612794((u32)D_8076A064 * arg6) * sp18;
    *arg2 += arg5 * func_80612794((u32)D_8076A064 * arg7);
}

void collisionCheckActorFloor(Actor *, f32, f32, f32, f32 *);
u8 collisionGetFloorHeight(f32 *);

typedef struct CamAFloor {
    /* 0x00 */ u8 pad0[0x90];
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 pad94[0x66];
    /* 0xFA */ u8 unkFA;
} CamAFloor;

void func_8061B7E0(CamActor *arg0, CamState *arg1, f32 arg2, f32 arg3) {
    f32 sp24 = 99999.0f;

    ((CamAFloor *)arg1)->unkFA = 0;
    collisionCheckActorFloor((Actor *)arg0, arg2, sp24, arg3, &sp24);
    ((CamAFloor *)arg1)->unkFA = collisionGetFloorHeight(&((CamAFloor *)arg1)->unk90);
}

typedef struct CamAV {
    /* 0x00 */ u8 pad0[0xF7];
    /* 0xF7 */ u8 unkF7;
} CamAV;

void func_8061B840(CamAV *arg0, u8 arg1) {
    arg0->unkF7 = arg1;
}

typedef struct CamAHit {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
} CamAHit; // size = 0x8

extern u8 D_807F9510;
extern CamAHit D_807F94C0[];

void func_8061B84C(void) {
    s16 i;
    s16 j;
    CamAHit tmp;

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061B9B0.s")

typedef struct CamAA8 {
    /* 0x00 */ u8 pad0[0xA8];
    /* 0xA8 */ f32 unkA8;
    /* 0xAC */ u8 padAC[0x4F];
    /* 0xFB */ u8 unkFB;
} CamAA8;

f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
void func_8060B55C();

void func_8061C0FC(CamAA8 *arg0) {
    ((CamAPlayer *)D_807FC924)[arg0->unkFB].unk2C4 = mathAngleBetweenPointsRad(((CamAPlayer *)D_807FC924)[arg0->unkFB].unk210, ((CamAPlayer *)D_807FC924)[arg0->unkFB].unk218, ((CamAPlayer *)D_807FC924)[arg0->unkFB].unk228, ((CamAPlayer *)D_807FC924)[arg0->unkFB].unk230);
    arg0->unkA8 = ((CamAPlayer *)D_807FC924)[arg0->unkFB].unk2C4;
    switch (D_807463B8) {
        case 0:
            ((CamAPlayer *)D_807FC924)[arg0->unkFB].unk2C8 = arg0->unkA8 * 4096.0 / 6.2831855f;
            break;
        case 2:
            func_8060B55C((u8 *)&D_807FC924[arg0->unkFB] + 0x2C8);
            break;
        case 3:
            ((CamAPlayer *)D_807FC924)[arg0->unkFB].unk2C8 = arg0->unkA8 * 4096.0 / 6.2831855f;
            break;
    }
    if (((CamAPlayer *)D_807FC924)[arg0->unkFB].unk2E9 != 0) {
        ((CamAPlayer *)D_807FC924)[arg0->unkFB].unk2E9--;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061C2C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061C2D8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061C2F0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061C39C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061C458.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061C464.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061C518.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061C600.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061C6A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061C804.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061CAD8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061CB08.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061CB38.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061CB50.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061CB80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061CB98.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061CBCC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061CC00.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061CC30.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061CC40.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061CF24.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061CF80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061CF90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061CFCC.s")

void func_8061D058(void) {
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061D060.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061D1FC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061D4E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061D6A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061D898.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061D934.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061D968.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061D9EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061DA14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061DA84.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061DAAC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061DB64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061DBD4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061EA78.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061EB04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061EDA0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061EF4C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061F0B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061F164.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061F18C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061F2B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061F4B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061F510.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061F53C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80620628.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80620B38.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80620F00.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80621174.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8062133C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80621E9C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8062210C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8062217C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80622334.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_806224CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_806225C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_806225D4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_806227F0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_806228BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80622ABC.s")

void func_80622B24(CamActor *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6, CamActor *arg7) {
    CamState *cam;
    s16 *list;
    s16 count;
    u8 type;
    CamPathPos *pos;
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
    CamSplineKeyE *e0;
    CamSplineKeyE *e1;
    CamSplineKeyE *e2;
    CamSplineKeyE *e3;
    CamSplineKey8 *k0;
    CamSplineKey8 *k1;
    CamSplineKey8 *k2;
    CamSplineKey8 *k3;
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
    p = &D_807476FC->unkD8[D_807F5CF2];
    savedX = *arg1;
    savedY = *arg2;
    savedZ = *arg3;
    if (D_807444EC == 1 && (p->unk1 == 4 || p->unk1 == 5)) {
        count = (p->u.spline.unk0 - 1 < 0) ? 0 : p->u.spline.unk0 - 1;
        arg7->unk160 = CAM_LERP(count, 0, D_807F5D00);
        arg7->unk168 = arg7->unk160;
        arg7->unk160 -= arg7->unk168;
    } else {
        count = (D_807476FC->unk0[arg7->unk15F].unk0 - 1 < 0) ? 0 : D_807476FC->unk0[arg7->unk15F].unk0 - 1;
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
                        func_8061F164(cam, 0x50);
                        cam->unkF3 = 0xC;
                        func_8062217C(arg0, 2);
                    }
                    break;
                case 0x43:
                case 0x4E:
                case 0x4F:
                case 0x7F:
                case 0x81:
                    if (cam->unkF3 == 1 || cam->unkF3 == 0xC) {
                        func_8061F164(cam, 0x50);
                        cam->unkF3 = 5;
                        cam->unkAC |= 0x40;
                    }
                    break;
                case 0x63:
                    if (cam->unkF3 != 0xA && cam->unkF3 != 2) {
                        cam->unkF3 = 0xA;
                        func_8061F164(cam, 0x1E);
                    }
                    break;
                case 0x62:
                    if (!(D_807FBB64 & 0x80) && cam->unkF3 != 0xD && cam->unkF3 != 2) {
                        cam->unkF3 = 0xD;
                        func_8061F164(cam, 0x1E);
                    }
                    break;
                default:
                    if (cam->unkF3 == 0xA || cam->unkF3 == 0xC || cam->unkF3 == 0xD) {
                        func_80622334(arg0, cam->unkA0);
                        func_8061F164(cam, 0x14);
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
                func_806224CC(arg0, arg7);
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
                        func_80622334(arg0, D_807476A8);
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
                list = D_807476FC->unkD0[D_807476F4].unk4;
                p = &D_807476FC->unkD8[list[D_807F5CF0]];
                if (p->unk1 == 8 || p->unk1 == 0xC) {
                    p = &D_807476FC->unkD8[list[D_807F5CF0 + 1]];
                }
                if (D_807F5CFC == D_807F5CEC + 1) {
                    D_807F5D18 = *arg1;
                    D_807F5D1C = *arg2;
                    D_807F5D20 = *arg3;
                    D_807F5D24 = *arg4;
                    D_807F5D28 = *arg5;
                    D_807F5D2C = *arg6;
                }
            } else if (D_807F5CFC == D_807F5CEC + 1) {
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
                    func_8061F2B8(arg7->unk7C, arg7->unk80, arg7->unk84, p->u.pos.unk0, p->u.pos.unk2, p->u.pos.unk4,
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
                    e0 = &((CamSplineKeyE *) p->u.spline.unk4)[idx[0]];
                    e1 = &((CamSplineKeyE *) p->u.spline.unk4)[idx[1]];
                    e2 = &((CamSplineKeyE *) p->u.spline.unk4)[idx[2]];
                    e3 = &((CamSplineKeyE *) p->u.spline.unk4)[idx[3]];
                    posX = splineEvalCubic(arg7->unk160, e0->unk0, e1->unk0, e2->unk0, e3->unk0);
                    posY = splineEvalCubic(arg7->unk160, e0->unk2, e1->unk2, e2->unk2, e3->unk2);
                    posZ = splineEvalCubic(arg7->unk160, e0->unk4, e1->unk4, e2->unk4, e3->unk4);
                    lookX = splineEvalCubic(arg7->unk160, e0->unk6, e1->unk6, e2->unk6, e3->unk6);
                    lookY = splineEvalCubic(arg7->unk160, e0->unk8, e1->unk8, e2->unk8, e3->unk8);
                    lookZ = splineEvalCubic(arg7->unk160, e0->unkA, e1->unkA, e2->unkA, e3->unkA);
                    D_807FC924[cam->unkFB].unk27C =
                        splineEvalCubic(arg7->unk160, e0->unkC, e1->unkC, e2->unkC, e3->unkC);
                    if (D_807476E4 == 0) {
                        arg0->unkE4 =
                            splineEvalCubic(arg7->unk160, e0->unkD, e1->unkD, e2->unkD, e3->unkD) / 127.0 * 2048.0;
                    }
                    break;
                case 5:
                    k0 = &((CamSplineKey8 *) p->u.spline.unk4)[idx[0]];
                    k1 = &((CamSplineKey8 *) p->u.spline.unk4)[idx[1]];
                    k2 = &((CamSplineKey8 *) p->u.spline.unk4)[idx[2]];
                    k3 = &((CamSplineKey8 *) p->u.spline.unk4)[idx[3]];
                    posX = splineEvalCubic(arg7->unk160, k0->unk0, k1->unk0, k2->unk0, k3->unk0);
                    posY = splineEvalCubic(arg7->unk160, k0->unk2, k1->unk2, k2->unk2, k3->unk2);
                    posZ = splineEvalCubic(arg7->unk160, k0->unk4, k1->unk4, k2->unk4, k3->unk4);
                    D_807FC924[cam->unkFB].unk27C =
                        splineEvalCubic(arg7->unk160, k0->unk6, k1->unk6, k2->unk6, k3->unk6);
                    if (D_807476E4 == 0) {
                        arg0->unkE4 =
                            splineEvalCubic(arg7->unk160, k0->unk7, k1->unk7, k2->unk7, k3->unk7) / 127.0 * 2048.0;
                    }
                calc_look:
                    if (!D_807F5CFA) {
                        lookX = func_80612794(arg7->unkE6) * D_807F5CEE + arg7->unk7C;
                        lookZ = func_80612790(arg7->unkE6) * D_807F5CEE + arg7->unk84;
                        if (arg7->unk15E != 0) {
                            lookY = arg7->unk80 + arg7->unk15E;
                        } else {
                            lookY = arg7->unk80;
                        }
                    } else {
                        actorGetNodePos(D_807F5CE8, D_807F5CFA, &lookX, &lookY, &lookZ);
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
                pitch = func_80622ABC(pitchT, pitchD, blend);
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
                func_806227F0(cam, arg4, arg5, arg6);
                func_806225D4(arg0, arg1, arg2, arg3);
                func_8061B7E0(arg0, cam, *arg1, *arg3);
                break;
            case 8:
                func_80621E9C(cam, arg4, arg5, arg6);
                func_806225D4(arg0, arg1, arg2, arg3);
                break;
            case 7:
                func_80621E9C(cam, arg4, arg5, arg6);
                break;
            case 2:
                func_8062210C(cam, arg4, arg5, arg6, D_807476B4);
                if (D_8076A0A8 == 0xD6) {
                    *arg5 += 50.0f;
                }
                if (cam->unkC8 != 0 || cam->unkCA != 0) {
                    func_80626CAC(cam, arg4, arg6, *arg1, *arg3,
                                  (s32) sqrtf((*arg1 - *arg4) * (*arg1 - *arg4) + (*arg3 - *arg6) * (*arg3 - *arg6)));
                }
                if (cam->unkF2 != 0) {
                    func_8061EDA0(cam, arg1, arg2, arg3, cam->unkC0, 0);
                }
                func_8061B7E0(arg0, cam, *arg1, *arg3);
                break;
            case 3:
            case 11:
                func_806228BC(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
                if (cam->unkF2 != 0) {
                    func_8061EDA0(cam, arg1, arg2, arg3, cam->unkC0, 0);
                }
                func_8061B7E0(arg0, cam, *arg1, *arg3);
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
                func_8062133C(arg0, arg7, arg1, arg2, arg3, 0.0f);
                break;
            case 13:
                *arg4 = arg7->unk7C;
                *arg5 = ((arg7->unk15E >= 21) ? 20 : arg7->unk15E) + arg7->unk80;
                *arg6 = arg7->unk84;
                func_8062133C(arg0, arg7, arg1, arg2, arg3, 30.0f);
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
                func_8062210C(cam, arg4, arg5, arg6, cam->unk94);
                func_8062133C(arg0, arg7, arg1, arg2, arg3, cam->unk94);
                if (D_8076A0A8 == 0x57) {
                    func_8061B660(cam, arg1, arg2, arg3, 3.0f, 5.0f, 40.0f, 60.0f);
                }
                *arg5 += yOffset;
                break;
        }
        if (D_807476B8 != 0 && arg7->unk80 < D_807476B8) {
            *arg1 = savedX;
            *arg2 = savedY;
            *arg3 = savedZ;
        } else if (D_807476BC != 0 && D_807476BC < arg7->unk80) {
            *arg2 = savedY;
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80624978.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80624CA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_806252CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80625320.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_806256D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80625994.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_806259FC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80625A80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80625B3C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80625C30.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80626110.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_806261CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_806261EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80626264.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80626478.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8062649C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_806264DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80626BC8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80626CAC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80626F8C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80627388.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80627490.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8062754C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_806276AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8062773C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80627878.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80627888.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80627948.s")
