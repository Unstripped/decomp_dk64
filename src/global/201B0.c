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

typedef struct CamTimerStep {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
    /* 0x6 */ u16 unk6;
} CamTimerStep; // size = 0x8

// .bss 0x807F5B10-0x807F5D30
CamPathData D_807F5B10;
CamPathData D_807F5BF0;
f32 D_807F5CCC;
s16 D_807F5CD0;
s16 D_807F5CD2;
s16 D_807F5CD4;
s16 D_807F5CD6;
s16 D_807F5CD8;
s16 D_807F5CDA;
u64 D_807F5CE0;
void *D_807F5CE8;
s16 D_807F5CEC;
s16 D_807F5CEE;
u16 D_807F5CF0;
u16 D_807F5CF2;
u16 D_807F5CF4;
u8 D_807F5CF6;
u16 D_807F5CF8;
u8 D_807F5CFA;
f32 D_807F5CFC;
f32 D_807F5D00;
s16 D_807F5D04;
s16 D_807F5D06;
s16 D_807F5D08;
s16 D_807F5D0A;
void *D_807F5D0C;
CamActor *D_807F5D10;
u8 D_807F5D14;
f32 D_807F5D18;
f32 D_807F5D1C;
f32 D_807F5D20;
f32 D_807F5D24;
f32 D_807F5D28;
f32 D_807F5D2C;

// .data 0x807476A0-0x80747750
f32 D_807476A0 = 0.0f;
f32 D_807476A4 = 0.0f;
f32 D_807476A8 = 0.0f;
f32 D_807476AC = 0.0f;
f32 D_807476B0 = 0.0f;
u8 D_807476B4 = 0;
s16 D_807476B8 = 0;
s16 D_807476BC = 0;
s16 *D_807476C0 = NULL;
u64 D_807476C8 = 0;
u64 D_807476D0 = 0;
u8 D_807476D8 = 0;
s16 D_807476DC = 0;
s16 D_807476E0 = 0;
s16 D_807476E4 = 0;
s16 D_807476E8 = 0;
u8 D_807476EC = 0;
s16 D_807476F0 = 0;
s16 D_807476F4 = 0;
s16 D_807476F8 = 0;
CamPathData *D_807476FC = &D_807F5B10;
CamPathData *D_80747700 = &D_807F5BF0;
s16 *D_80747704 = NULL;
CamTimerStep D_80747708[9] = {
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
void func_8061B660(CamState *, f32 *, f32 *, f32 *, f32, f32, f32, f32);
void func_8061B7E0(CamActor *, CamState *, f32, f32);
void func_8061EDA0(CamState *, f32 *, f32 *, f32 *, s32, s32);
void func_8061F164(CamState *, s32);
void func_8061F2B8(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *);
s32 func_8061F53C(CamActor *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
u8 func_8062133C(CamActor *, CamActor *, f32 *, f32 *, f32 *, f32);
void func_80621E9C(CamState *, f32 *, f32 *, f32 *);
void func_8062210C(CamState *, f32 *, f32 *, f32 *, f32);
u8 func_8062217C(CamActor *, s16);
void func_80622334(CamActor *, s16);
void func_806224CC(CamActor *, CamActor *);
void func_806225D4(CamActor *, f32 *, f32 *, f32 *);
void func_806227F0(CamState *, f32 *, f32 *, f32 *);
void func_806228BC(CamActor *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
f32 func_80622ABC(f32, f32, f32);
s16 func_80626CAC(CamState *, f32 *, f32 *, f32, f32, f32);
f32 splineEvalCubic(f64, f32, f32, f32, f32);
s32 func_8062773C(CamActor *);
s16 mathAngleLerp(s16, s16, f32);
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);
f32 mathCalculatePitchAngle(f32, f32, f32, f32, f32, f32, s32);
void renderBonusTargetMarker();
void renderCallbacksRegister(void *, void *, s32);
f32 sqrtf(f32);

#define CAM_LERP(a, b, t) ((a) + ((b) - (a)) * (t))

u8 func_8061B4B0(void) {
    return D_807F5CE0 != 0;
}

extern u64 __ll_mul(u64, u64);
extern u64 __ull_div(u64, u64);
void func_80712524(s32, s32);

void func_8061B4E4(void) {
    u64 t = __ull_div(__ull_div(__ll_mul(osGetTime() - D_807F5CE0, 0x40), 0xBB8), 0x2710);

    if ((u32)t >= D_80747708[D_807F5D14].unk0) {
        func_80712524(D_80747708[D_807F5D14].unk4, D_80747708[D_807F5D14].unk5);
        if (++D_807F5D14 >= 6) {
            D_807F5CE0 = 0;
        }
    }
}

typedef struct CamAPlayer {
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

u8 collisionCheckActorFloor(Actor *, f32, f32, f32, f32 *);
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

typedef struct CamB9Act {
    /* 0x00 */ u8 pad0[0xC0];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ u8 padC4[0x22];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[0x6C];
    /* 0x154 */ u8 unk154;
} CamB9Act;

typedef struct CamB9St {
    /* 0x00 */ CamB9Act *unk0;
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
} CamB9St;

#define CAMB9_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define CAMB9_MAX(a, b) (((a) < (b)) ? (b) : (a))

void func_80620628(CamActor *, f32, s16, u8);

u8 func_8061B9B0(void *arg0, void *arg1, f32 arg2, f32 *arg3, f32 arg4, s32 arg5) {
    CamB9Act *X = ((CamB9St *)arg1)->unk0;
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
    ((CamB9St *)arg1)->unkFA = 0;
    cnt = 0;
    if (collisionCheckActorFloor((Actor *)arg0, arg2, sp78, arg4, &sp78)) {
        func_8061B84C();
        if (D_807F9510 == 1 || *arg3 < D_807F94C0[0].unk0) {
            flags = D_807F94C0[0].unk6;
            sp78 = D_807F94C0[0].unk0;
            sp64 = D_807F94C0[0].unk4;
            cnt = 1;
        } else {
            for (i = 0; i < D_807F9510; i++) {
                flags = D_807F94C0[i].unk6;
                if (flags & 2) {
                    if (*arg3 < D_807F94C0[i].unk0 || (sp74 != ((CamB9St *)arg1)->unkC && ((CamB9St *)arg1)->unkC < *arg3)) {
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
            new_var = CAMB9_MIN(1.0, ((u32)D_8076A064 - 0x3C) * 0.01);
            bonus += 10.0 * new_var;
        }
        if ((D_807FBB64 & 8) && !(flags & 8)) {
            lim = CAMB9_MAX((func_80612794(sp64 + 0x800) + 1.0f) * 100.0f, bonus);
        } else {
            lim = bonus;
        }
        if (((CamB9St *)arg1)->unk18 < lim) {
            ((CamB9St *)arg1)->unk18 = lim;
        } else {
            ((CamB9St *)arg1)->unk18 = ((CamB9St *)arg1)->unk18 + (lim - ((CamB9St *)arg1)->unk18) * 0.05;
        }
        if (*arg3 < sp78 + ((CamB9St *)arg1)->unk18) {
            ret = 1;
            if (sp78 - *arg3 < 35.0 || (D_807F9510 == 1 && sp64 >= 0x1F5 && sp78 - *arg3 < 80.0)) {
                *arg3 = sp78 + ((CamB9St *)arg1)->unk18;
                ((CamB9St *)arg1)->unkAC |= 0x800;
                ret = 2;
            } else if (!(((CamB9St *)arg1)->unkAC & 0x82000) && !*((u8 *)&arg5 + 3) && !(D_807FBB64 & 1) &&
                       ((X->unkC0 < -300.0f && X->unk154 != 0x59) || X->unk154 == 0x15 || X->unk154 == 0x16)) {
                func_80620628((CamActor *)arg0, -2.0f, ((CamB9St *)arg1)->unkB2 + 0x800, 0);
            } else if ((D_807FBB64 & 1) || D_807F9510 < 2 || (((CamB9St *)arg1)->unkAC & 0x80000)) {
                ret = 0;
            }
        } else {
            ((CamB9St *)arg1)->unkAC &= ~0x800;
        }
    } else {
        if (!(D_807FBB68 & 0x80)) {
            sp78 = 32767.0f;
        }
    }
    ((CamB9St *)arg1)->unkFA = collisionGetFloorHeight(&((CamB9St *)arg1)->unk90);
    if (*((u8 *)&arg5 + 3)) {
        ((CamB9St *)arg1)->unkA = ((CamB9St *)arg1)->unk8;
        if (sp74 != -32768.0f && sp78 < sp74) {
            ((CamB9St *)arg1)->unk8 = sp74 - sp78;
        } else {
            ((CamB9St *)arg1)->unk8 = 0;
        }
        if (!(D_807FBB68 & 0x20) && ((CamB9St *)arg1)->unkF5 == 0) {
            u8 v1;

            if (X->unk154 == 0x63) {
                v1 = 0x14;
            } else {
                v1 = 10;
            }
            if (((CamB9St *)arg1)->unk8 != 0) {
                if (sp78 + ((CamB9St *)arg1)->unk8 - v1 < *arg3) {
                    *arg3 = sp78 + ((CamB9St *)arg1)->unk8 - v1;
                }
            }
        }
        if (X->unk154 == 0x44 || X->unk154 == 0x57 || X->unk154 == 0x59) {
            ((CamB9St *)arg1)->unkC = -32768.0f;
        } else {
            ((CamB9St *)arg1)->unkC = sp74;
        }
    }
    if (*((u8 *)&arg5 + 3)) {
        if (!(((CamB9St *)arg1)->unkAC & 0x82000)) {
            if (sp78 == 32767.0f || (D_807F9510 == 1 && cnt == 0)) {
                ((CamB9St *)arg1)->unkA0 -= 10.0f;
                ((CamB9St *)arg1)->unkB2 = X->unkE6;
            }
        }
    }
    return ret;
}

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

s32 func_8061C2C4(CamActor *arg0, s32 arg1) {
    CamState *s = arg0->unk174;
    s32 v = s->unkAC | arg1;
    s->unkAC = v;
    return v;
}

void func_8061C2D8(CamActor *arg0, s32 arg1) {
    arg0->unk174->unkAC &= ~arg1;
}

typedef struct CamBTarget {
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
} CamBTarget;

typedef struct CamBState {
    /* 0x00 */ CamActor *unk0;
    /* 0x04 */ u8 pad4[0x1C];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ u8 pad38[0xC];
    /* 0x44 */ CamBTarget unk44;
    /* 0x60 */ u8 pad60[0x4C];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ u8 padB0[0x43];
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4[7];
    /* 0xFB */ u8 unkFB;
} CamBState;

typedef struct CamBPlayer {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0xC];
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ u8 pad234[0xBC];
} CamBPlayer; // size = 0x2F0

void func_8061D4E4();

void func_8061C2F0(CamActor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7) {
    CamBState *s = (CamBState *)arg0->unk174;

    if (D_807444EC == 1 && arg7) {
        func_8061D4E4(arg0);
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

void func_8061C39C(CamActor *arg0) {
    CamBState *s = (CamBState *)arg0->unk174;

    ((CamBPlayer *)D_807FC924)[s->unkFB].unk210 = s->unk20;
    ((CamBPlayer *)D_807FC924)[s->unkFB].unk214 = s->unk24;
    ((CamBPlayer *)D_807FC924)[s->unkFB].unk218 = s->unk28;
    ((CamBPlayer *)D_807FC924)[s->unkFB].unk228 = s->unk2C;
    ((CamBPlayer *)D_807FC924)[s->unkFB].unk22C = s->unk30;
    ((CamBPlayer *)D_807FC924)[s->unkFB].unk230 = s->unk34;
}

void func_8061C458(CamActor *arg0, CamActor *arg1) {
    CamBState *s = (CamBState *)arg0->unk174;
    s->unk44.unk4 = arg1;
}

void func_806EAB44();

void func_8061C464(CamActor *arg0, CamActor *arg1, u8 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, f32 arg10) {
    CamBState *s = (CamBState *)arg0->unk174;
    CamBTarget *p = &s->unk44;

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
        func_806224CC(arg0, s->unk0);
    }
}

typedef struct CamBTgtSub {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ f32 unk38;
} CamBTgtSub;

typedef struct CamBTgt {
    /* 0x0 */ u8 pad0[4];
    /* 0x4 */ CamBTgtSub *unk4;
} CamBTgt;

void func_8061C6A8(CamActor *, CamActor *, u8, s16, s16, s16, s16, s16, s16, s16, f32);

void func_8061C518(CamActor *arg0, CamActor *arg1, u8 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, f32 arg10) {
    f32 saved = ((CamBTgt *)arg1)->unk4->unk38;

    if (D_807444EC == 1) {
        func_8061D4E4(arg0);
    }
    D_8076A0B3 = 0;
    D_8076A0B1 |= 0x10;
    ((CamBTgt *)arg1)->unk4->unk38 = 0.15f;
    func_8061C6A8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
    ((CamBTgt *)arg1)->unk4->unk38 = saved;
    D_807FBB60 &= ~1;
}

void func_8061C600(CamActor *arg0, CamActor *arg1, u8 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, f32 arg10) {
    if (D_807444EC == 1) {
        func_8061D4E4(arg0);
    }
    D_8076A0B3 = 0;
    D_8076A0B1 |= 0x10;
    func_8061C464(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
}

void func_8061B5C4(s16);

void func_8061C6A8(CamActor *arg0, CamActor *arg1, u8 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, f32 arg10) {
    CamBState *s = (CamBState *)arg0->unk174;
    CamBTarget *p = &s->unk44;
    f32 scale;

    if (arg1 != NULL) {
        scale = ((CamBTgt *)arg1)->unk4->unk38 / 0.15;
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
        func_806224CC(arg0, s->unk0);
    }
}

typedef struct CamBPt {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u32 unk4;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u8 padC[8];
} CamBPt; // size = 0x14

typedef struct CamBList {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ s16 *unk4;
    /* 0x8 */ s16 *unk8;
} CamBList; // size = 0xC

typedef struct CamBPathData {
    /* 0x00 */ u8 pad0[0xD0];
    /* 0xD0 */ CamBList *unkD0;
    /* 0xD4 */ u8 padD4[4];
    /* 0xD8 */ CamBPt *unkD8;
} CamBPathData;

#define CAMB_PATH ((CamBPathData *)D_807476FC)

void func_8061D898(void);
void func_80622B24(CamActor *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, CamActor *);

s16 func_8061C804(s16 arg0) {
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
        count = CAMB_PATH->unkD0[path].unk0;
        for (i = 0; i < count; i++) {
            idx = CAMB_PATH->unkD0[path].unk4[i];
            switch (CAMB_PATH->unkD8[idx].unk1) {
                case 6:
                    break;
                case 0xD:
                    if ((CAMB_PATH->unkD8[idx].unk4 & 0xFF) == 8) {
                        path = CAMB_PATH->unkD8[idx].unk8 >> 16;
                        found = 1;
                    }
                    break;
                case 0xE:
                    break;
                default:
                    if (first == 0) {
                        saved = ((CamActor *)D_807F5CE8)->unk168;
                        first = 1;
                        sp94 = ((CamBPlayer *)D_807FC924)->unk210;
                        sp90 = ((CamBPlayer *)D_807FC924)->unk214;
                        sp8C = ((CamBPlayer *)D_807FC924)->unk218;
                        sp88 = ((CamBPlayer *)D_807FC924)->unk228;
                        sp84 = ((CamBPlayer *)D_807FC924)->unk22C;
                        sp80 = ((CamBPlayer *)D_807FC924)->unk230;
                        D_807F5CFC = 1.0f;
                        D_807F5D00 = 0.0f;
                        D_807476F4 = path;
                        D_807F5CF0 = i;
                        func_8061D898();
                        func_80622B24(D_807F5D10, &sp94, &sp90, &sp8C, &sp88, &sp84, &sp80, D_807F5CE8);
                        D_807F5CF0 = 0;
                        D_807476F4 = arg0;
                        D_807F5D04 = sp94;
                        D_807F5D06 = sp90;
                        D_807F5D08 = sp8C;
                        D_807F5D0A = mathAngleBetweenPoints2D(sp88, sp80, sp94, sp8C);
                        D_807F5CF4 |= 0x20;
                        D_807F5CEC = 0;
                        ((CamActor *)D_807F5CE8)->unk168 = saved;
                    }
                    total += CAMB_PATH->unkD0[path].unk8[i];
                    break;
            }
        }
    } while (found);
    return total;
}

void func_8061CAD8(void) {
    if (!(D_807F5CF4 & 2)) {
        D_807F5CF4 |= 0x40;
    } else {
        D_807F5CF4 &= ~2;
    }
}

void func_8061CB08(void) {
    if (D_807F5CF4 & 0x40) {
        D_807F5CF4 &= ~0x40;
    } else {
        D_807F5CF4 |= 2;
    }
}

u8 func_8061CB38(void) {
    return (D_807F5CF4 & 0x40) != 0;
}

u8 func_8061CB50(void) {
    return D_807444EC == 1 || (D_8076A0B1 & 0x10) != 0;
}

u8 func_8061CB80(void) {
    return (D_807F5CF4 & 4) != 0;
}

extern s16 D_807476F8;

u8 func_8061CB98(u8 arg0) {
    return D_807444EC == 1 && arg0 == D_807476F8;
}

void func_8061D898();

void func_8061CBCC(void) {
    D_807476F4 = D_807476F8;
    D_807F5CF0 = 0;
    func_8061D898();
}

extern CamActor *D_807F5D10;

u8 func_8061CC00(void) {
    CamState *s = D_807F5D10->unk174;
    return s->unkF3 == 3 || s->unkF3 == 0xB;
}

extern u8 D_807476EC;

void func_8061CC30(void) {
    D_807476EC = 1;
}

extern CamPathData D_807F5BF0;
extern CamPathData D_807F5B10;
extern void *D_807F5D0C;
extern Actor *D_807FBB44;
extern u8 D_807476D8;
extern s16 D_807476F0;
extern u8 D_80770DC9;
extern u8 D_807F5CF6;
extern u8 D_8074E77C[];
extern u8 D_807F5D14;
typedef struct CamC_Struct807FD580 {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
} CamC_Struct807FD580;
extern CamC_Struct807FD580 *D_807FD580;

s32 actorSpawn(s32, s32);
void func_80029140(s16 *);
void currentActorClearFlag(void);
s16 func_8061C804(s16);
void setRandomSeed(s32);
s32 func_8070B318(void);

u16 func_8061CC40(void *arg0, s16 arg1, u8 arg2) {
    u16 ret = 0;

    if (D_807444EC == 1 && (D_807F5CF4 & 0x80)) {
        return 0;
    }
    if ((arg2 & 4) && D_8076A0A8 != 0) {
        D_807476FC = &D_807F5BF0;
    } else {
        D_807476FC = &D_807F5B10;
    }
    if (actorSpawn(0xAD, 0) != 0) {
        D_807F5D0C = D_807FBB44;
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
        D_807F5CE8 = arg0;
    } else {
        D_807F5CE8 = *(void **)((u8 *)D_807FC924 + 4);
    }
    D_807444EC = 1;
    if (!(arg2 & 8)) {
        D_8076A0B1 |= 0x10;
        D_8076A0B3 = 0;
    }
    D_807476D0 = osGetTime();
    D_807476F4 = arg1;
    D_807476F8 = arg1;
    D_807F5CF4 = arg2;
    D_807F5CFA = 0;
    D_807476D8 = 0;
    D_807476E4 = 0;
    D_807F5CEC = 0;
    D_807F5CF0 = 0;
    D_807F5CF2 = 0;
    D_807F5CEE = 0;
    D_807476F0 = 0;
    D_807F5CF6 = D_80770DC9;
    D_807FBB60 |= 0x2000;
    D_807FBB60 &= ~0x1001;
    D_807FBB4C->unkB8 = 0.0f;
    if (D_8074E77C[0] == 7) {
        *(f32 *)D_807FBB4C->unkC0 = 0.0f;
    }
    D_807FBB4C->unk60 |= 0x400;
    D_807FD580->unk10 = 0;
    D_807F5D10->unkE4 = 0;
    currentActorClearFlag();
    if (D_807476EC != 0) {
        ret = func_8061C804(arg1);
    }
    D_807476EC = 0;
    if (arg1 == 0 && D_8076A0A8 == 0x99) {
        setRandomSeed(0x8E32B6F7);
        D_807F5CE0 = osGetTime();
        D_807F5D14 = 0;
    } else if (func_8070B318() == 0) {
        D_807F5CE0 = 0;
    }
    return ret;
}

void func_8061CF24(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3) {
    if (D_807F5CF4 & 0x20) {
        *arg0 = D_807F5D04;
        *arg1 = D_807F5D06;
        *arg2 = D_807F5D08;
        *arg3 = D_807F5D0A;
        D_807F5CF4 &= 0xFFDF;
    }
}

void func_8061CF80(s16 arg0) {
    D_807F5CEE = arg0;
}

typedef struct CamDPlayer {
    /* 0x0 */ u8 pad0[4];
    /* 0x4 */ void *unk4;
} CamDPlayer;

void func_8061CF90(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        D_807F5CE8 = arg0;
    } else {
        D_807F5CE8 = ((CamDPlayer *)D_807FC924)->unk4;
    }
    D_807F5CFA = arg1;
}

typedef struct CamDState CamDState;

typedef struct CamDActor {
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
    /* 0x174 */ CamDState *unk174;
} CamDActor;

struct CamDState {
    /* 0x00 */ CamDActor *unk0;
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

void func_8061CFCC(void *arg0) {
    CamDState *cam = ((CamDActor *)D_807F5D10)->unk174;

    if (arg0 == D_807F5CE8) {
        func_8061CF90(NULL, 0);
    }
    if (arg0 == cam->unk4) {
        cam->unk4 = NULL;
        cam->unkAC &= ~0x10004;
    }
    if (arg0 == cam->unk0) {
        cam->unk0 = (CamDActor *)D_807FBB4C;
    }
}

void func_8061D058(void) {
}

void func_8061D060(CamDState *cam) {
    CamDActor *actor = cam->unk0;
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

void func_8061D1FC(CamDActor *arg0) {
    CamDState *cam = arg0->unk174;
    f32 target = D_807FD63F[cam->unkFB * 0x34] * 0.5;
    s32 sel;

    if (!(cam->unkAC & 0x2000) && !(D_807FBB64 & 0x40)) {
        if (cam->unk8 != 0 && cam->unk8 < 0x9B && cam->unkEF != 0) {
            if (cam->unkA == 0 || cam->unkA >= 0x9B) {
                cam->unkF0 = cam->unkEE;
            }
            func_8062217C((CamActor *)arg0, 1);
            cam->unkAC |= 8;
        } else if (cam->unkA != 0 && cam->unkA < 0x9B) {
            if (cam->unkEF != 0) {
                if (cam->unkF0 != 0) {
                    sel = cam->unkF0;
                    if (cam->unkEF != sel) {
                        func_8062217C((CamActor *)arg0, (s16)sel);
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

void func_8061D4E4(CamDActor *arg0) {
    CamDState *cam = arg0->unk174;

    if (D_807444EC == 1) {
        if (D_807F5CF4 & 4) {
            D_807476FC = &D_807F5B10;
        }
        sfxSetMode(0);
        D_807444EC = 0;
        D_8076A0B1 &= 0xFFEF;
        if (!(D_807F5CF4 & 8)) {
            D_8076A0B3 = 0xFF;
        }
        actorDespawn(D_807F5D0C);
        D_807FBB60 |= 0x1000;
        cam->unkAC |= 0x40000;
        cam->unkC = -32768.0f;
        if (D_807F5CF4 & 1) {
            D_807FBB60 |= 0x2000;
            func_8061B5C4(cam->unkFB);
        }
        D_807FC924[cam->unkFB].unk27C = 45.0f;
        arg0->unkE4 = 0;
        D_80770DC9 = D_807F5CF6;
        D_8076A068 += 0x1869F;
        timerQueuePurgeFlagged();
        D_8076A068 += 0xFFFE7961;
        D_807F5CF4 = 0;
        D_807476C8 = 0;
        D_807FBB4C->unk60 &= ~0x400;
    }
}

f32 func_80611BB4(f32, f32);

void func_8061D6A8(CamDState *cam) {
    CamDActor *actor = cam->unk0;
    f32 yaw;

    D_807476A8 = sqrtf((cam->unk8C - actor->unk84) * (cam->unk8C - actor->unk84) +
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


#ifdef NON_MATCHING
void func_806F3DB0(u16, void *);

typedef struct CamDPathList {
    /* 0x0 */ u8 pad0[4];
    /* 0x4 */ s16 *unk4;
    /* 0x8 */ s16 *unk8;
} CamDPathList;

void func_8061D898(void) {
    ((CamActor *)D_807F5D0C)->unk168 = 0;
    ((CamActor *)D_807F5D0C)->unk160 = 0.0;
    D_807F5CF2 = D_807476FC->unkD0[D_807476F4].unk4[D_807F5CF0];
    D_807F5CEC = ((CamDPathList *)&D_807476FC->unkD0[D_807476F4])->unk8[D_807F5CF0];
    func_806F3DB0(D_807F5CF0, &D_807F5D0C);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061D898.s")
#endif

void func_8061D934(u8 arg0) {
    D_807476F4 = arg0;
    D_807F5CF0 = 0;
    func_8061D898();
}

extern u16 D_807F5CF8;
extern u8 D_8076AEE0;
extern f32 D_807FD88C;

void func_8061CB08(void);

void func_8061D968(u8 arg0, u8 arg1) {
    if (D_807476D8 != 0) {
        D_807476D8--;
        if (D_807476D8 != 0) {
            D_807F5CF0 = D_807F5CF8;
            func_8061D898();
        }
    } else {
        D_807476D8 = arg1;
        D_807F5CF8 = arg0;
        D_807F5CF0 = arg0;
        func_8061D898();
    }
}

void func_8061D9EC(s32 arg0, s32 arg1, s32 arg2) {
    D_8076AEE0 = 0;
    D_807FD88C = -0.8f;
}

void timerQueueAdd(void *, s32, s32, s32, s32);

void func_8061DA14(s32 arg0, s32 arg1, s32 arg2) {
    D_8076A0B1 |= 0x40;
    D_8076AEE0 = 0;
    D_807FD88C = 0.8f;
    timerQueueAdd(func_8061D9EC, 0x8000003C, 0, 0, 0);
}

void func_8061DA84(s32 arg0, s32 arg1, s32 arg2) {
    func_8061CB08();
}

extern s16 D_807476DC;
extern s16 D_807476E0;
extern s16 D_807476E8;

void func_8061DAAC(s16 arg0, s16 arg1, u16 arg2) {
    D_807476E4 = arg2;
    D_807476E8 = arg2;
    D_807476DC = arg0 * 4096 / 360;
    D_807476E0 = arg1 * 4096 / 360;
}

typedef struct CamEState {
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
} CamEState;


void func_8061DB64(CamActor *arg0) {
    CamEState *cam = (CamEState *)arg0->unk174;

    func_80620628(arg0, -1.0f, cam->unk0->unkE6, 0);
    cam->unkF5 = 0xF;
    cam->unkF6 = 0xF;
    D_807FBB60 &= ~0x2000;
    cam->unkAC &= ~0x100000;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061DBD4.s")

typedef struct CamEPlayerEntry {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 pad1[3];
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ u8 pad8[0x2E8];
} CamEPlayerEntry;

void func_8061EB04(Actor *, u8);

void func_8061EA78(void) {
    u8 i;

    for (i = 0; i < D_807FC928; i++) {
        if (((CamEPlayerEntry *)D_807FC924)[i].unk0) {
            func_8061EB04(((CamEPlayerEntry *)D_807FC924)[i].unk4, i);
        }
    }
}


typedef struct CamECam {
    /* 0x00 */ u8 pad0[0x88];
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 pad94[0x20];
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ u8 padB8[0xA7];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ u8 pad160[0x14];
    /* 0x174 */ CamEState *unk174;
} CamECam;

typedef struct CamEPlayerState {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ CamECam *unk104;
} CamEPlayerState;

typedef struct CamEPlayerRec {
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
} CamEPlayerRec;

void func_8061DBD4(CamECam *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
s16 func_806531B8(f32, f32, f32, s32);

#define CAMEREC(i) ((CamEPlayerRec *)&D_807FC924[i])

void func_8061EB04(Actor *arg0, u8 arg1) {
    CamEPlayerState *ps = arg0->unk174;
    CamEState *st = ps->unk104->unk174;
    CamECam *cam = ps->unk104;

    D_807476FC = &D_807F5B10;
    st->unk0 = (CamActor *)arg0;
    st->unkFB = arg1;
    st->unk60 = 5.0f;
    if (D_807444EC == 1) {
        func_8061D4E4((CamDActor *)cam);
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
    func_8062217C((CamActor *)cam, (s16)(D_8076A0A8 == 0x9A ? 1 : ((D_807FBB64 & 1) ? 3 : 2)));
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
    *(s16 *)arg0->unk12C = func_806531B8(arg0->unk7C, arg0->unk80, arg0->unk84, 0);
    func_8061DBD4(cam, &CAMEREC(arg1)->unk210, &CAMEREC(arg1)->unk214, &CAMEREC(arg1)->unk218,
                  &CAMEREC(arg1)->unk228, &CAMEREC(arg1)->unk22C, &CAMEREC(arg1)->unk230,
                  &CAMEREC(arg1)->unk240, &CAMEREC(arg1)->unk244, &CAMEREC(arg1)->unk248);
    st->unkAC &= ~0x100;
    cam->unk88 = ((CamEPlayerRec *)D_807FC924)[arg1].unk210;
    cam->unk8C = ((CamEPlayerRec *)D_807FC924)[arg1].unk214;
    cam->unk90 = ((CamEPlayerRec *)D_807FC924)[arg1].unk218;
}

s32 randomNonNegative(void);

void func_8061EDA0(CamState *arg0, f32 *arg1, f32 *arg2, f32 *arg3, s32 arg4, s32 arg5) {
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

void func_8061F0B0(CamActor *, u8, u16);

void func_8061EF4C(CamActor *arg0, u8 arg1, u16 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 dx = arg3 - arg0->unk7C;
    f32 dy = arg4 - arg0->unk80;
    f32 dz = arg5 - arg0->unk84;
    f32 dist = sqrtf(dx * dx + dy * dy + dz * dz);

    if (!(arg7 < dist)) {
        if (dist < arg6) {
            func_8061F0B0(arg0, arg1, arg2);
        } else {
            func_8061F0B0(arg0, arg1, (u16)(arg2 * ((arg7 - dist) / (arg7 - arg6))));
        }
    }
}

void func_8060E7EC(u8, u8, s32);

void func_8061F0B0(CamActor *arg0, u8 arg1, u16 arg2) {
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

typedef struct CamFView {
    /* 0x00 */ u8 pad0[0xE8];
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ s16 unkEA;
} CamFView;

void func_8061F164(arg0, arg1) CamState *arg0; s16 arg1; {
    if (arg1 >= 0xB) {
        ((CamFView *)arg0)->unkE8 = arg1;
        ((CamFView *)arg0)->unkEA = ((CamFView *)arg0)->unkE8;
    }
}

s32 mathAngleDistance(s16, s16);

typedef struct CamFAct {
    /* 0x00 */ u8 pad0[0x88];
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ f32 unk90;
} CamFAct;

typedef struct CamFLink {
    /* 0x00 */ CamActor *unk0;
} CamFLink;

void func_8061F18C(CamActor *arg0, f32 arg1, f32 arg2, f32 arg3) {
    CamFLink *cam;
    s16 ang;
    s16 pad;
    s16 diff;
    s16 pad2;
    f32 dist;
    f64 r;

    cam = (CamFLink *)arg0->unk174;
    ang = mathAngleBetweenPoints2D(cam->unk0->unk7C, cam->unk0->unk84, arg1, arg3);
    diff = mathAngleDistance(ang, mathAngleBetweenPoints2D(cam->unk0->unk7C, cam->unk0->unk84, ((CamFAct *)arg0)->unk88, ((CamFAct *)arg0)->unk90));
    dist = sqrtf((arg1 - ((CamFAct *)arg0)->unk88) * (arg1 - ((CamFAct *)arg0)->unk88)
               + (arg2 - ((CamFAct *)arg0)->unk8C) * (arg2 - ((CamFAct *)arg0)->unk8C)
               + (arg3 - ((CamFAct *)arg0)->unk90) * (arg3 - ((CamFAct *)arg0)->unk90));
    r = diff * 0.0009765625;
    func_8061F164((CamState *)cam, (s16)((r < 1.0 ? 1.0 : r) * dist));
}

void func_8061F2B8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 *arg9, f32 *argA, f32 *argB) {
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

typedef struct CamFPath {
    /* 0x00 */ u8 pad0[0xC4];
    /* 0xC4 */ u8 *unkC4;
} CamFPath;

void func_8061F4B0(u8 *arg0) {
    u8 i;
    u8 *p;
    s32 v;
    u8 *q;

    for (i = 0; i < 6; i++) {
        v = (0, arg0)[i];
        p = arg0 + i;
        if (v != 0) {
            q = ((CamFPath *)D_807476FC)->unkC4 + v * 0x1C;
            q[-4] |= p[6] & 0xF;
        }
    }
}

typedef struct CamFSlot {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[3];
} CamFSlot;

extern CamFSlot *D_807F5BD4;

void func_8061F510(u8 arg0, u8 arg1) {
    D_807F5BD4[arg0].unk18 = arg1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_8061F53C.s")

// Needs top-block prototype changes: `void func_8062217C(CamActor *, s16);` (call site passes plain 1, hoisted const gives sll/sra) and `u8 func_8062133C(CamActor *, CamActor *, f32 *, f32 *, f32 *, f32);` (asm returns lbu v0).
typedef struct CamFTgt {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
} CamFTgt;

typedef struct CamFCam {
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
} CamFCam;

typedef struct CamFActB {
    /* 0x00 */ u8 pad0[0xB4];
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ f32 unkB8;
} CamFActB;

typedef struct CamFPlayer {
    /* 0x000 */ u8 pad0[0x21C];
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
    /* 0x228 */ u8 pad228[0x98];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 pad2C1[0x2F];
} CamFPlayer; // size = 0x2F0

s32 func_80671E00(f32, f32, f32, f32, void *, void *, s32, s32);

void func_80620628(CamActor *arg0, f32 arg1, s16 arg2, u8 arg3) {
    CamFTgt *tgt;
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
    CamFCam *cam;
    f32 f;

    cam = (CamFCam *)arg0->unk174;
    tgt = (CamFTgt *)cam->unk0;
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
        if (((CamFPlayer *)D_807FC924)[cam->unkFB].unk2C0 != 1) {
            f = 0.333f;
        }
    }
    func_8062217C(arg0, 1);
    cam->unkB8 = 10.0f;
    ((CamFActB *)arg0)->unkB4 = 10.0f;
    cam->unkA0 = 5.0f;
    cam->unkAC |= 0x80000;
    do {
        again = 0;
        sawCol = func_8062133C(arg0, cam->unk0, &x, &y, &z, -1.0f) == 1;
        while (cam->unkA0 < f * 100.0f && !sawCol && (ret = func_80671E00(x, y, z, 10.0f * f, &out1, &out0, 1, 0xBC), hit = ret, ret == 0)) {
            saved = cam->unkB2;
            cam->unkA0 += 10.0f * f;
            ((CamFActB *)arg0)->unkB4 += f * 3.0f;
            sawCol = func_8062133C(arg0, cam->unk0, &x, &y, &z, -1.0f) == 1;
            cam->unkB2 = saved;
        }
        if (hit) {
            cam->unkA0 -= f * 10.0f;
            ((CamFActB *)arg0)->unkB4 -= f * 3.0f;
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
            ((CamFActB *)arg0)->unkB4 = 10.0f;
            cnt += 0x80;
        }
    } while (again);
    if (found || (cnt < 0x1000 && !sawCol)) {
        cam->unkA4 = cam->unkA0;
        func_80622334(arg0, (s16)cam->unkA0);
        goto done;
    }
    cam->unkFF += arg3;
    x = ((CamFPlayer *)D_807FC924)->unk21C;
    y = ((CamFPlayer *)D_807FC924)->unk220;
    z = ((CamFPlayer *)D_807FC924)->unk224;
    func_8062217C(arg0, 1);
    cam->unkA0 = cam->unkA4;
    ((CamFActB *)arg0)->unkB4 = cam->unkB8;
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
    ((CamFActB *)arg0)->unkB8 = 0.0f;
}

typedef struct CamAT38St {
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
} CamAT38St;

typedef struct CamAT38Act {
    /* 0x00 */ u8 pad0[0xE6];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[6];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[2];
    /* 0xF2 */ s16 unkF2;
    /* 0xF4 */ u8 padF4[8];
    /* 0xFC */ u8 unkFC;
} CamAT38Act;

extern u8 D_807FB606;
extern f32 D_807476AC;
s16 func_80672A70(s16, s16);
void func_80672680(s16, s16, s16, s16, void *);
s16 func_80672134(s16, s16, s16, s16);

u8 func_80620B38(CamActor *arg0, f32 arg1, f32 arg2, f32 *arg3, f32 arg4, f32 *arg5, f32 arg6) {
    CamAT38St *st = (CamAT38St *)arg0->unk174;
    s16 sp4A;
    s16 sp48;
    u8 pad;
    s16 sp44;
    s16 sp42;
    f32 v;

    sp4A = 0;
    sp48 = 0xFFF;
    ((CamAT38Act *)arg0)->unkFC = 0;
    st->unkFC = 0;
    v = 0.0f;
    v += 0.2 * ((180.0f < st->unkA0) ? 180.0f : st->unkA0);
    if (st->unkF5 != 0) {
        v -= 0.1 * st->unkF5;
    } else {
        v -= 0.1 * st->unkF1;
    }
    if (func_80671E00(*arg3, arg4, *arg5, v, &sp4A, &sp48, 1, 0xBC)) {
        if (D_807FB606 != 0) {
            st->unkFC = 2;
            sp44 = (((CamAT38Act *)arg0)->unkEE + 0x800) & 0xFFF;
            sp42 = 0;
        } else {
            s16 sp3A;
            s16 t;

            sp3A = func_80672A70(sp4A, sp48);
            arg1 += 0.5 * func_80612794(sp3A);
            arg2 += 0.5 * func_80612790(sp3A);
            st->unkFC = 1;
            func_80672680(((CamAT38Act *)arg0)->unkEE, ((CamAT38Act *)arg0)->unkEE, sp4A, sp48, &sp44);
            t = func_80672134(sp4A, sp48, ((CamAT38Act *)arg0)->unkE6, 100);
            if ((f32)t < arg6) {
                sp42 = t;
            } else {
                sp42 = arg6;
            }
        }
        ((CamAT38Act *)arg0)->unkFC = 1;
        *arg3 = func_80612794(sp44) * sp42 + arg1;
        *arg5 = func_80612790(sp44) * sp42 + arg2;
        if (st->unkF5 != 0) {
            st->unkA0 -= 5.0f;
        } else {
            st->unkB2 = mathAngleBetweenPoints2D(((CamActor *)st->unk0)->unk7C, ((CamActor *)st->unk0)->unk84, *arg3, *arg5);
        }
        st->unkF1 = 0;
        ((CamAT38Act *)arg0)->unkF2 = sp44;
        if (!(st->unkAC & 0x2008) && !(D_807FBB64 & 1) && D_807476AC < st->unkA0) {
            func_80622334(arg0, D_807476AC);
        }
    } else {
        if (!(st->unkAC & 0x2000)) {
            if (st->unkEF != st->unkEE) {
                func_8062217C(arg0, st->unkEE);
            }
        }
        st->unk1C = 0.0f;
    }
    return ((CamAT38Act *)arg0)->unkFC;
}

typedef struct CamAMain {
    /* 0x00 */ CamActor *unk0;
    /* 0x04 */ u8 pad4[0xAE];
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ u8 padB4[0x40];
    /* 0xF4 */ u8 unkF4;
    /* 0xF5 */ u8 padF5[0xA];
    /* 0xFF */ u8 unkFF;
} CamAMain;

typedef struct CamA114 {
    /* 0x000 */ u8 pad0[0x114];
    /* 0x114 */ s16 unk114;
    /* 0x116 */ s16 unk116;
    /* 0x118 */ s16 unk118;
    /* 0x11A */ s16 unk11A;
} CamA114;

typedef struct CamAActB8 {
    /* 0x00 */ u8 pad0[0xB8];
    /* 0xB8 */ f32 unkB8;
} CamAActB8;

s32 func_80620F00(CamActor *arg0, u8 arg1, u8 arg2) {
    CamAMain *st = (CamAMain *)arg0->unk174;
    CamActor *actor;
    f32 diff;
    u8 x;
    u8 y;
    u8 z;
    u8 w;
    CamA114 *st2;

    actor = st->unk0;
    diff = D_807476A8 - ((CamAPlayer *)D_807FC924)[((CamState *)st)->unkFB].unk284;
    st2 = (CamA114 *)actor->unk174;
    x = 40.0f < D_807476A8 && (f32)st2->unk114 < diff;
    y = (f32)st2->unk118 < diff;
    z = (f32)st2->unk11A < diff;
    w = (f32)st2->unk116 < diff;
    if (arg2 && !y && !z) {
        x = 0;
    }
    if (x != 0) {
        if (arg1 && ((CamAActB8 *)actor)->unkB8 != 0.0f) {
            if (y && !z) {
                st->unkB2 += 0x32;
                func_8061B840((CamAV *)st, 0xA);
            } else if (z && !y) {
                st->unkB2 -= 0x32;
                func_8061B840((CamAV *)st, 0xA);
            }
        }
        st->unkF4++;
        if (w && st->unkF4 >= 0x15) {
            actor = st->unk0;
            st->unkF4 = 0;
            if (((CamAActB8 *)actor)->unkB8 != 0.0f && actor->unk154 != 0x59) {
                func_80620628(arg0, 0.0f, st->unkB2, 1);
            } else {
                func_80620628(arg0, 0.0f, actor->unkE6, 1);
            }
        }
        return 1;
    } else {
        st->unkFF = 0;
        st->unkF4 = 0;
    }
    return 0;
}

typedef struct CamAB8 {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[0x5C];
    /* 0xB8 */ f32 unkB8;
} CamAB8;

extern s8 D_80744530;
s32 func_807142D8(void);

u8 func_80621174(s32 arg0, CamState *arg1, CamActor *arg2) {
    return arg2->unk154 == 0x5B
        || ((D_807FBB64 & 0x4000004) && ((CamAB8 *)arg2)->unkB8 != 0.0f)
        || (D_807FBB64 & 0x8000000)
        || (arg1->unkAC & 4)
        || ((arg1->unkAC & 8) && ((CamAB8 *)arg2)->unkB8 != 0.0f)
        || (D_80744530 == 1 && ((CamAB8 *)arg2)->unkB8 != 0.0f && func_807142D8() == 0)
        || arg1->unkF3 == 0xA
        || arg1->unkF3 == 0xD
        || arg1->unkF3 == 5
        || arg1->unkF3 == 0xC
        || (arg1->unkFC != 0 && ((CamAB8 *)arg2)->unkB8 != 0.0f)
        || arg2->unk154 == 0x6E
        || ((CamAB8 *)arg2)->unk58 == 8;
}

typedef struct CamLActor CamLActor;

typedef struct CamLPlayer {
    /* 0x000 */ u8 pad0[0x130];
    /* 0x130 */ CamLActor *unk130;
    /* 0x134 */ u8 pad134[0xBC];
    /* 0x1F0 */ s32 unk1F0;
} CamLPlayer;

typedef struct CamLState {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ CamLActor *unk4;
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
} CamLState;

struct CamLActor {
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
extern f32 D_807FD888;

s32 actorTableContains(void *);
s32 func_805FCA64(void);
u8 func_8061B9B0(void *, void *, f32, f32 *, f32, s32);
void func_80624978();

#define TGT ((CamLActor *)arg1)
#define CA ((CamLActor *)arg0)
u8 func_8062133C(CamActor *arg0, CamActor *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 arg5) {
    CamLState *cam = (CamLState *)arg0->unk174;
    CamLPlayer *ply = (CamLPlayer *)arg1->unk174;
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
        if (!(cam->unkAC & 0x100) && D_807FD888 == 0.0f && 2.0 * cam->unkA0 < D_807476AC && cam->unkE8 == 0 &&
            cam->unkF3 != 5 && !(D_807FBB68 & 2) && !(D_807FBB64 & 0x2001)) {
            func_80620628(arg0, -1.0f, cam->unkB2, 0);
        } else {
            if (cam->unkFC != 0 && cam->unkA0 * 1.2 < D_807476AC) {
                if (*arg3 - (cam->unk90 < cam->unk6C ? cam->unk6C : cam->unk90) > 50.0f && cam->unkEF >= 2) {
                    func_8062217C(arg0, 1);
                    CA->unkB4 = CA->unkB4 - 120.0f;
                } else {
                    CA->unkB4 = CA->unkB4 + 5.0;
                }
            } else if (cam->unkFC == 2) {
                CA->unkB4 = CA->unkB4 + 20.0f;
            }
        }
    }
    if (cam->unkF3 != 2 && func_80621174((s32)arg0, (CamState *)cam, arg1) != 0) {
        func_80624978(cam, sp72, sp6E);
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
        func_8061EDA0((CamState *)cam, &x, &y, &z, cam->unkC0, 0);
    }
    *arg2 = x;
    *arg3 = y;
    *arg4 = z;
    if (cam->unkF3 != 0xC) {
        sp71 = func_8061B9B0(arg0, cam, *arg2, &y, *arg4, var_v0_2 = (arg5 >= 0.0f ? 0 : 1));
        if (sp71 != 0 || y < *arg3) {
            *arg3 = y;
        }
    }
    return sp71;
}
#undef TGT
#undef CA

typedef struct CamAFollow {
    /* 0x00 */ CamActor *unk0;
    /* 0x04 */ CamActor *unk4;
    /* 0x08 */ u8 pad8[0x64];
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ u8 pad70[0x6C];
    /* 0xDC */ f32 unkDC;
} CamAFollow;

extern f32 D_807476B0;

#define CAM_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define CAM_MAX(a, b) (((a) < (b)) ? (b) : (a))

void func_80621E9C(CamState *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    CamActor *actor = ((CamAFollow *)arg0)->unk0;
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
        y = CAMB9_MIN(1.0, (f < D_807476B0 ? D_807476B0 - f : 0.0f) * 2);
    } else if (D_807476B0 < -0.1) {
        y = 0.0 - CAM_MAX(CAM_MIN((D_807476B0 - f) + 0.3, 0.0) * 2, -1.0);
    }
    if (((CamAFollow *)arg0)->unk4 != NULL) {
        *arg1 = ((CamAFollow *)arg0)->unk4->unk7C + (actor->unk7C - ((CamAFollow *)arg0)->unk4->unk7C) * 0.9;
        *arg3 = ((CamAFollow *)arg0)->unk4->unk84 + (actor->unk84 - ((CamAFollow *)arg0)->unk4->unk84) * 0.9;
    } else {
        *arg1 = actor->unk7C;
        *arg3 = actor->unk84;
    }
    *arg2 = ((((CamAFollow *)arg0)->unkDC + idx) - (((CamAFollow *)arg0)->unk6C + idx)) * y + (((CamAFollow *)arg0)->unk6C + idx);
}

typedef struct CamA9E {
    /* 0x00 */ u8 pad0[0x9E];
    /* 0x9E */ s16 unk9E;
} CamA9E;

void func_8062210C(CamState *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4) {
    func_80621E9C(arg0, arg1, arg2, arg3);
    *arg1 += arg4 * func_80612794(((CamA9E *)arg0)->unk9E);
    *arg3 += arg4 * func_80612790(((CamA9E *)arg0)->unk9E);
}

typedef struct CamAEntry {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 unk2;
} CamAEntry;

typedef struct CamAMode {
    /* 0x00 */ u8 pad0[0xA4];
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ u8 padA8[0x10];
    /* 0xB8 */ f32 unkB8;
} CamAMode;

extern CamAEntry D_80747B60[][4];

u8 func_8062217C(CamActor *arg0, s16 arg1) {
    CamState *st = arg0->unk174;
    u8 old;
    s16 v;

    v = (D_8074E77C[st->unkFB] * 2 + (((CamAPlayer *)D_807FC924)[st->unkFB].unk2C0 != 1)) + 7;
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
    ((CamAMode *)st)->unkA4 = D_80747B60[v][arg1].unk2;
    ((CamAMode *)st)->unkB8 = D_80747B60[v][arg1].unk0;
    st->unkEF = arg1;
    return old;
}

typedef struct CamC2P {
    /* 0x000 */ u8 pad0[0x2C0];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 pad2C1[0x2F];
} CamC2P; // size = 0x2F0

void func_80622334(CamActor *arg0, s16 arg1) {
    CamState *st = arg0->unk174;
    s16 idx;
    s16 best;
    s16 i;

    idx = D_8074E77C[st->unkFB] * 2 + (((CamC2P *)D_807FC924)[st->unkFB].unk2C0 != 1) + 7;
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
    func_8062217C(arg0, best);
}

typedef struct CamC6E {
    /* 0x00 */ u8 pad0[0x6E];
    /* 0x6E */ s16 unk6E;
} CamC6E;

typedef struct CamC224 {
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
} CamC224;

extern CamC6E *D_807FBB48;
void sfxStopSlotSound(void *, s32);
void func_806224CC(CamActor *arg0, CamActor *arg1) {
    CamC224 *s;
    s32 pad1;
    s32 pad2;
    u8 pad3;
    u8 prev;

    s = (CamC224 *)arg0->unk174;
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
            func_8061F164((CamState *)s, 0xA);
            s->unkB2 = arg1->unkE6;
            break;
        case 2:
            if (s->unkED == 8) {
                if (mathAngleDistance(s->unkB2, arg1->unkE6) < 0x400) {
                    func_8061DB64(arg0);
                }
            }
            s->unkED = 0xFF;
        default:
            func_8061F164((CamState *)s, 0x14);
            break;
    }
}

void func_806225C0(CamActor *arg0) {
    CamState *st = arg0->unk174;

    st->unk44 = 0;
    st->unkF3 = 1;
}

typedef struct CamCTgt {
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
} CamCTgt;

typedef struct CamC1F0 {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ u32 unk1F0;
} CamC1F0;

typedef struct CamC44b {
    /* 0x00 */ CamCTgt *unk0;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ s16 unk14;
} CamC44b;

typedef struct CamCSt {
    /* 0x00 */ CamCTgt *unk0;
    /* 0x04 */ u8 pad4[0x40];
    /* 0x44 */ CamC44b s44;
    /* 0x5C */ u8 pad5C[0x9F];
    /* 0xFB */ u8 unkFB;
} CamCSt;

void func_806225D4(CamActor *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    CamCSt *st = (CamCSt *)arg0->unk174;
    CamC44b *p = &st->s44;
    s16 angle;
    CamC1F0 *tgtState;
    s8 mult;
    s32 pad;

    angle = (p->unk0->unkE6 + p->unk8) & 0xFFF;
    tgtState = (CamC1F0 *)st->unk0->unk174;
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
            func_8061EB04((Actor *)st->unk0, st->unkFB);
            D_807FBB60 |= 0x2000;
            if (D_8076A0B1 & 0x10) {
                D_8076A0B1 &= ~0x10;
                D_8076A0B3 = 0xFF;
            }
        }
    }
}

typedef struct CamC44 {
    /* 0x00 */ CamActor *unk0;
    /* 0x04 */ CamActor *unk4;
    /* 0x08 */ u8 pad8[4];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[2];
    /* 0x12 */ s16 unk12;
} CamC44;

typedef struct CamCState {
    /* 0x00 */ u8 pad0[0x44];
    /* 0x44 */ CamC44 s44;
} CamCState;

void func_806227F0(CamState *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    CamC44 *p;
    s16 angle;

    p = &((CamCState *)arg0)->s44;
    angle = (p->unk0->unkE6 + p->unkC) & 0xFFF;
    *arg1 = func_80612794(angle) * p->unkE + p->unk4->unk7C;
    *arg3 = func_80612790(angle) * p->unkE + p->unk4->unk84;
    *arg2 = p->unk4->unk80 + p->unk12;
}

typedef struct CamC8Tgt {
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
} CamC8Tgt;

typedef struct CamC8St {
    /* 0x00 */ CamC8Tgt *unk0;
    /* 0x04 */ u8 pad4[0xAE];
    /* 0xB2 */ s16 unkB2;
} CamC8St;

typedef struct CamC8Act {
    /* 0x00 */ u8 pad0[0xB4];
    /* 0xB4 */ f32 unkB4;
} CamC8Act;


void func_806228BC(CamActor *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
    CamC8St *st = (CamC8St *)arg0->unk174;
    CamC8Tgt *tgt = st->unk0;
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
        angle = func_80672A70(tgt->unkF4, tgt->unkF6);
        *arg1 += 5.0 * func_80612794(angle);
        *arg3 += 5.0 * func_80612790(angle);
    }
    *arg4 = tgt->unk7C - func_80612794(st->unkB2) * 50.0f;
    *arg5 = tgt->unk80 - (((CamC8Act *)arg0)->unkB4 - 138.0f);
    *arg6 = tgt->unk84 - func_80612790(st->unkB2) * 50.0f;
}

f32 func_80622ABC(f32 arg0, f32 arg1, f32 arg2) {
    f32 diff = arg0 - arg1;

    if (diff > 3.1415927f) {
        arg1 += 6.2831855f;
    } else if (diff < -3.1415927f) {
        arg0 += 6.2831855f;
    }
    return arg0 + (arg1 - arg0) * arg2;
}

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

#ifdef NON_MATCHING
typedef struct CamC9Tgt {
    /* 0x000 */ u8 pad0[0x58];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0xF8];
    /* 0x154 */ u8 unk154;
} CamC9Tgt;

typedef struct CamC9St {
    /* 0x00 */ CamC9Tgt *unk0;
    /* 0x04 */ u8 pad4[0xA8];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ u8 padB0[2];
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ u8 padB4[0x3F];
    /* 0xF3 */ u8 unkF3;
} CamC9St;

void func_80624978(arg0, arg1, arg2) CamC9St *arg0; s16 arg1; s16 arg2; {
    s16 diff;
    u16 dist;
    f32 scale;
    f32 limit;
    u16 wrap;

    diff = arg2 - arg0->unkB2;
    dist = diff > 0 ? diff : -diff;
    if (dist >= 0x801) {
        wrap = 0x1000 - dist;
    } else {
        wrap = dist;
    }
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
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80624978.s")
#endif

typedef struct CamB2XState {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ s32 unk1F0;
} CamB2XState;

typedef struct CamB2Player {
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
    /* 0x174 */ struct CamB2Cam *unk174;
} CamB2Player;

typedef struct CamB2Cam {
    /* 0x00 */ CamB2Player *unk0;
    /* 0x04 */ u8 pad4[0xC];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[0x32];
    /* 0x44 */ CamBTarget unk44;
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
} CamB2Cam;

struct CamE2Player;

void func_80624CA4(struct CamE2Player *arg0) {
    CamB2Cam *st = ((CamB2Player *)arg0)->unk174;
    CamB2Player *X = st->unk0;
    CamB2XState *xs = (CamB2XState *)X->unk174;
    CamBTarget *tgt = &st->unk44;
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
            D_807476A0 = 1.0f;
            D_807476A4 = 1.0f;
            break;
        case 4:
        case 8:
            D_807476A0 = tgt->unk18;
            D_807476A4 = tgt->unk18;
            break;
        case 3:
        case 11:
            if (X->unk110 == 1) {
                dz = X->unk84 - st->unk8C;
                dx = X->unk7C - st->unk84;
                dist = dz * dz + dx * dx;
                m = dist * 0.001;
                m2 = (m > 1.0) ? 1.0 : m;
                D_807476A0 = m2 * -0.8 + 1.0;
            } else {
                D_807476A0 = 0.2f;
            }
            D_807476A4 = 0.3f;
            break;
        case 2:
            D_807476A0 = 0.3f;
            if (X->unk154 == 0x62) {
                D_807476A4 = 0.05f;
            } else if (!(st->unkAC & 0x80)) {
                D_807476A4 = 0.3f;
            }
            break;
        case 1:
            if (st->unkB0 != 0 || st->unkF1 != 0 || D_8076A0A8 == 0x27 || st->unkF6 != 0) {
                D_807476A0 = 0.3f;
                D_807476A4 = 0.3f;
            } else if (st->unkF7 != 0) {
                D_807476A0 = 0.2f;
                D_807476A4 = 0.2f;
            } else if ((st->unkAC & 4) || X->unk58 == 8) {
                D_807476A0 = 0.1f;
                D_807476A4 = 0.2f;
            } else if (X->unk154 == 0x22) {
                D_807476A0 = 0.4f;
                D_807476A4 = 0.2f;
            } else if (X->unk154 == 0xE || X->unk154 == 0x59) {
                D_807476A0 = 0.1f;
                D_807476A4 = 0.08f;
            } else {
                base = 0.03f;
                if (((CamB2Player *)arg0)->unkB8 != 0.0f) {
                    k = st->unk10 / ((CamB2Player *)arg0)->unkB8;
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
                D_807476A0 = base + (0.6 - base) * k;
                D_807476A4 = base + (0.4 - base) * k;
            }
            break;
        case 7:
            D_807476A0 = 0.05f;
            D_807476A4 = 0.05f;
            break;
        case 5:
            D_807476A0 = 0.2f;
            D_807476A4 = 0.2f;
            break;
        case 10:
            D_807476A0 = 0.3f;
            D_807476A4 = 0.3f;
            break;
        case 12:
            D_807476A0 = 0.6f;
            D_807476A4 = 0.6f;
            break;
        case 13:
            D_807476A0 = 0.2f;
            D_807476A4 = 0.2f;
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
        D_807476A0 *= scale;
        D_807476A4 *= scale;
    }
}

f32 func_806252CC(f32 arg0, f32 arg1, f32 arg2) {
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

typedef struct CamE2Player CamE2Player;

typedef struct CamE2Cam {
    /* 0x00 */ CamE2Player *unk0;
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
} CamE2Cam;

struct CamE2Player {
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
    /* 0x174 */ CamE2Cam *unk174;
};

void func_80624CA4(CamE2Player *);
f32 func_806252CC(f32, f32, f32);
void func_80625994(CamE2Player *, f32, f32 *, f32 *, f32 *);
void func_806256D0(CamE2Player *, f32, f32 *, f32 *, f32 *);

#define CAME2_ABSD(a, b) (((a) < (b)) ? (b) - (a) : (a) - (b))
#define CAME2_M1 (CAME2_ABSD(st->unkD0, X->unk80) * 0.08)
#define CAME2_MAX (CAME2_M1 > 0.03 ? CAME2_M1 : 0.03)

void func_80625320(CamE2Player *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
    s32 unused;
    CamE2Cam *st = arg0->unk174;
    CamE2Player *X = st->unk0;
    f32 dist;
    f32 spd;
    f32 t;

    spd = CAME2_MAX < 1.0 ? CAME2_MAX : 1.0;
    func_80624CA4(arg0);
    st->unkE4 = st->unkE4 + (spd - st->unkE4) * 0.1;
    dist = sqrtf((arg0->unk84 - st->unk8C) * (arg0->unk84 - st->unk8C) +
                 (arg0->unk7C - st->unk84) * (arg0->unk7C - st->unk84));
    if (dist < 0.1) {
        dist = 0.0f;
    }
    if (arg0->unkB8 < dist) {
        arg0->unkB8 = func_806252CC(arg0->unkB8, dist, st->unk60);
    } else {
        arg0->unkB8 = dist;
    }
    arg0->unkEE = mathAngleBetweenPoints2D(arg0->unk7C, arg0->unk84, st->unk84, st->unk8C);
    arg0->unkE6 = arg0->unkEE;
    if (st->unkB0 != 0 || st->unkF1 != 0 || D_8076A0A8 == 0x27 || st->unkF6 != 0 || st->unkE8 != 0 ||
        (st->unkAC & 0x100) || st->unkF3 != 1) {
        st->unkE4 = t = D_807476A0;
    } else {
        t = (st->unkE4 > 1.0) ? 1.0 : st->unkE4;
    }
    func_806256D0(arg0, t, arg1, arg2, arg3);
    if (X->unk110 == 1 && st->unk10 != 0) {
        func_80625994(arg0, 0.5f, arg4, arg5, arg6);
    } else if (st->unkF3 == 1) {
        func_80625994(arg0, t, arg4, arg5, arg6);
    } else {
        func_80625994(arg0, D_807476A4, arg4, arg5, arg6);
    }
}



void func_806256D0(CamE2Player *arg0, f32 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    CamE2Cam *st = arg0->unk174;
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
            st->unk84 += D_807476A0 * arg0->unkB8 * func_80612794(ang);
            st->unk8C += D_807476A0 * arg0->unkB8 * func_80612790(ang);
            st->unk88 = (arg0->unk80 - st->unk88) * arg1 + st->unk88;
            if (st->unkF3 != 12 && !(D_807FBB68 & 2)) {
                func_80620B38((CamActor *)arg0, savedX, savedZ, &st->unk84, st->unk88, &st->unk8C, D_807476A0 * arg0->unkB8);
            }
            *arg2 = *arg2 + (st->unk84 - *arg2) * 0.3;
            *arg3 = *arg3 + (st->unk88 - *arg3) * 0.3;
            *arg4 = *arg4 + (st->unk8C - *arg4) * 0.3;
            if (st->unkF3 != 12) {
                clampY = (*arg3 < st->unk0->unk80) ? st->unk0->unk80 : *arg3;
                if (func_8061B9B0(arg0, st, *arg2, &clampY, *arg4, 1) != 0 || clampY < *arg3) {
                    *arg3 = clampY;
                }
            }
            break;
        default:
            st->unk84 = *arg2 = *arg2 + (arg0->unk7C - *arg2) * D_807476A0;
            st->unk88 = *arg3 = *arg3 + (arg0->unk80 - *arg3) * D_807476A0;
            st->unk8C = *arg4 = *arg4 + (arg0->unk84 - *arg4) * D_807476A0;
            break;
    }
}

extern s16 D_807F5CD2;
extern s16 D_807F5CD4;
extern s16 D_807F5CD8;

typedef struct CamE2State {
    /* 0x00 */ u8 pad0[0x78];
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
} CamE2State;

void func_80625994(CamE2Player *arg0, f32 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    CamE2State *st = (CamE2State *)arg0->unk174;

    *arg2 = *arg2 + (st->unk78 - *arg2) * D_807476A4;
    *arg3 = *arg3 + (st->unk7C - *arg3) * arg1;
    *arg4 = *arg4 + (st->unk80 - *arg4) * D_807476A4;
}

s32 func_806259FC(s16 arg0, s16 arg1) {
    s16 i;
    s16 j;

    for (i = -1; i < 2; i++) {
        for (j = -1; j < 2; j++) {
            if (arg0 == arg1 + i * D_807F5CD8 + j) {
                return 1;
            }
        }
    }
    return 0;
}

typedef struct CamE2Bound {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 pad12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[6];
} CamE2Bound; // size = 0x1C

typedef struct CamE2PathView {
    /* 0x00 */ u8 pad0[0xC0];
    /* 0xC0 */ s16 unkC0;
    /* 0xC2 */ u8 padC2[2];
    /* 0xC4 */ CamE2Bound *unkC4;
} CamE2PathView;

#define CAME2_PATH ((CamE2PathView *)D_807476FC)

s16 func_80625A80(s32 arg0) {
    CamE2Bound *e = &CAME2_PATH->unkC4[arg0];

    return (e->unk10 - D_807F5CD2) / 400 + (e->unk14 - D_807F5CD4) / 400 * D_807F5CD8;
}

void func_80625B3C(s16 *arg0, s16 *arg1, s16 *arg2) {
    s16 i;

    *arg0 = 0x7FFF;
    *arg2 = 0x7FFF;
    *arg1 = -0x8000;
    for (i = 0; i < CAME2_PATH->unkC0; i++) {
        if (CAME2_PATH->unkC4[i].unk10 < *arg0) {
            *arg0 = CAME2_PATH->unkC4[i].unk10;
        }
        if (*arg1 < CAME2_PATH->unkC4[i].unk10) {
            *arg1 = CAME2_PATH->unkC4[i].unk10;
        }
        if (CAME2_PATH->unkC4[i].unk14 < *arg2) {
            *arg2 = CAME2_PATH->unkC4[i].unk14;
        }
    }
    *arg0 -= 0xC8;
    *arg1 += 0xC8;
    *arg2 -= 0xC8;
}

#ifdef NON_MATCHING
typedef struct CamE3Pair {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
} CamE3Pair;

typedef struct CamE3Ent {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[3];
} CamE3Ent; // size = 0x1C

typedef struct CamE3Path {
    /* 0x00 */ u8 pad0[0xC0];
    /* 0xC0 */ s16 unkC0;
    /* 0xC2 */ u8 padC2[2];
    /* 0xC4 */ CamE3Ent *unkC4;
} CamE3Path;

void *func_80610FE8(s32);
void heapFree(void *);

#define CAME3_PATH ((CamE3Path *)D_807476FC)
#define CAME3_SORT ((CamE3Pair *)D_80747704)
#define CAME3_GROUP ((CamE3Pair *)D_807476C0)

void func_80625C30(void) {
    s16 i;
    s16 j;
    s16 k;
    s16 key;
    s16 idx;

    func_80625B3C(&D_807F5CD2, &D_807F5CD6, &D_807F5CD4);
    D_807F5CD6 = D_807F5CD6 / 400 * 400 + 400;
    D_807F5CD2 = D_807F5CD2 / 400 * 400;
    D_807F5CD8 = (D_807F5CD6 - D_807F5CD2) / 400;
    D_807F5CD4 = D_807F5CD4 / 400 * 400;
    if (D_80747704 != NULL) {
        heapFree(D_80747704);
    }
    D_80747704 = func_80610FE8(CAME3_PATH->unkC0 * 4 + 4);
    for (i = 0; i < CAME3_PATH->unkC0; i++) {
        CAME3_SORT[i].unk0 = i;
        CAME3_SORT[i].unk2 = func_80625A80(i);
    }
    for (i = 1; i < CAME3_PATH->unkC0; i++) {
        key = CAME3_SORT[i].unk2;
        idx = CAME3_SORT[i].unk0;
        j = i;
        while (j > 0 &&
               (key < CAME3_SORT[j - 1].unk2 ||
                (key == CAME3_SORT[j - 1].unk2 &&
                 CAME3_PATH->unkC4[CAME3_SORT[j - 1].unk0].unk18 < CAME3_PATH->unkC4[CAME3_SORT[j].unk0].unk18))) {
            CAME3_SORT[j].unk0 = CAME3_SORT[j - 1].unk0;
            CAME3_SORT[j].unk2 = CAME3_SORT[j - 1].unk2;
            j--;
        }
        if (j != i) {
            CAME3_SORT[j].unk0 = idx;
            CAME3_SORT[j].unk2 = key;
        }
    }
    D_807F5CDA = 1;
    for (i = CAME3_PATH->unkC0 - 1; i > 0; i--) {
        if (CAME3_SORT[i].unk2 != CAME3_SORT[i - 1].unk2) {
            D_807F5CDA++;
        }
    }
    if (D_807476C0 != NULL) {
        heapFree(D_807476C0);
    }
    D_807476C0 = func_80610FE8(D_807F5CDA * 4 + 4);
    CAME3_GROUP[0].unk0 = CAME3_SORT[0].unk2;
    CAME3_GROUP[0].unk2 = 0;
    k = 1;
    for (i = 1; i < CAME3_PATH->unkC0; i++) {
        if (CAME3_SORT[i].unk2 != CAME3_SORT[i - 1].unk2) {
            CAME3_GROUP[k].unk0 = CAME3_SORT[i].unk2;
            CAME3_GROUP[k].unk2 = i;
            k++;
        }
    }
    CAME3_GROUP[k].unk0 = -1;
    CAME3_GROUP[k].unk2 = CAME3_PATH->unkC0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80625C30.s")
#endif

typedef struct CamE3Node {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x5E];
    /* 0xE6 */ s16 unkE6;
} CamE3Node;

typedef struct CamE3State {
    /* 0x00 */ CamE3Node *unk0;
    /* 0x04 */ CamE3Node *unk4;
    /* 0x08 */ u8 pad8[0xA];
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[0x96];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ u8 padB0[2];
    /* 0xB2 */ s16 unkB2;
} CamE3State;

CamE3Node *spawnNodeActivate(s32, s32);

void func_80626110(CamActor *arg0, s16 arg1, s16 arg2) {
    CamE3State *st = (CamE3State *)arg0->unk174;

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

void func_806261CC(CamActor *arg0) {
    CamE3State *st = (CamE3State *)arg0->unk174;

    st->unk4 = NULL;
    st->unkAC &= ~0x10004;
}

void func_806264DC(void *, CamPathData *, u8);

void func_806261EC(void *arg0, CamPathData *arg1, u8 arg2) {
    func_806264DC(arg0, arg1, arg2);
    arg1->unkD8[48].unk1 = 0xE;
    arg1->unkD8[49].unk1 = 0xB;
    arg1->unkD8[50].unk1 = 6;
    arg1->unkD8[51].unk1 = 0x11;
    arg1->unkD8[52].unk1 = 7;
    arg1->unkD8[53].unk1 = 8;
}

void *func_8066B0F8(s32, s32, s32, s32);
void splineSetBasisTension(f32);
void assetFreeBuffer(void *, s32, s32);
void func_80625C30(void);

void func_80626264(void *arg0) {
    void *buf = func_8066B0F8(8, 0, 1, 1);

    splineSetBasisTension(0.5f);
    D_807476FC = &D_807F5B10;
    D_807F5CF4 = 0;
    D_807476C0 = NULL;
    D_80747704 = NULL;
    func_806261EC(arg0, D_807476FC, 1);
    func_806261EC(buf, D_80747700, 0);
    assetFreeBuffer(buf, 0x10B4, 0xC);
    func_80625C30();
    D_807476B4 = 0;
    D_807476B8 = 0;
    D_807476BC = 0;
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
            D_807476B8 = 0x1F4;
            break;
        case 0x36:
            D_807476B8 = 0xFA;
            break;
        case 0x6E:
            D_807476B8 = 0x226;
            break;
        case 0xBA:
            D_807476B8 = 0xFA;
            break;
        case 0xBB:
        case 0xBC:
            D_807476B8 = 0x12C;
            break;
        case 0x27:
            D_807F5CCC = 10.0f;
            break;
        case 0x2D:
            D_807476BC = 0x78;
            break;
    }
    D_807476C8 = 0;
    D_807476D0 = 0;
}

void func_80626478(s16 *arg0, s16 *arg1) {
    *arg0++ = *arg1++;
    *arg0++ = *arg1++;
    *arg0++ = *arg1++;
}

void *memcpy(void *, const void *, u32);

void *func_8062649C(u8 *arg0, void *arg1, u16 arg2) {
    memcpy(arg1, arg0 + 4, arg2);
    return arg0 + 4 + arg2;
}

#ifdef NON_MATCHING
typedef struct CamF2Seg {
    /* 0x00 */ s16 a[3];
    /* 0x06 */ s16 b[3];
    /* 0x0C */ s16 c[3];
} CamF2Seg; // size = 0x12

typedef struct CamF2Bnd {
    /* 0x00 */ s16 v[14];
} CamF2Bnd; // size = 0x1C

typedef struct CamF2E {
    /* 0x00 */ s16 v[7];
} CamF2E; // size = 0xE

typedef struct CamF2Q {
    /* 0x00 */ s16 v[4];
} CamF2Q; // size = 0x8

typedef struct CamF2Head {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 pad2;
    /* 0x04 */ CamF2Seg *unk4;
} CamF2Head; // size = 0x8

typedef struct CamF2List {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 pad2;
    /* 0x4 */ s16 *unk4;
    /* 0x8 */ s16 *unk8;
} CamF2List; // size = 0xC

typedef struct CamF2Path {
    /* 0x00 */ CamF2Head heads[24];
    /* 0xC0 */ s16 unkC0;
    /* 0xC2 */ s16 padC2;
    /* 0xC4 */ CamF2Bnd *unkC4;
    /* 0xC8 */ s8 *unkC8;
    /* 0xCC */ s16 unkCC;
    /* 0xCE */ s16 padCE;
    /* 0xD0 */ CamF2List *unkD0;
    /* 0xD4 */ s16 unkD4;
    /* 0xD6 */ s16 padD6;
    /* 0xD8 */ CamPathPoint *unkD8;
} CamF2Path;

void *func_80610FE8(s32);
void heapClearBlock(void *);
void func_80626478(s16 *, s16 *);

void func_806264DC(void *arg0v, CamPathData *arg1v, u8 arg2) {
    s16 *arg0 = arg0v;
    CamF2Path *arg1 = (CamF2Path *)arg1v;
    s16 i;
    s16 j;
    s16 cnt;
    s16 *hdr;
    u8 *data;
    CamF2Head *h;
    CamF2Seg *dst;
    CamPathPoint *pt;
    s16 *s;
    u8 *rd;
    s32 padf1;
    s32 padf2;
    s32 padf3;
    s32 padf4;
    s32 padf5;
    CamF2Seg buf;
    CamPathSpline *u;
    s16 m;
    s16 k;
    s32 padg1;
    s32 padg2;
    s32 padg3;
    s32 skip;

    hdr = arg0;
    data = arg0 != NULL ? (u8 *)arg0 + 0x30 : NULL;
    for (i = 0; i < 0x18; i++) {
        h = &arg1->heads[i];
        cnt = h->unk0 = hdr != NULL ? *hdr++ : 0;
        if (arg2 != 0) {
            h->unk4 = func_80610FE8(cnt * 0x12U);
            for (j = 0; j < cnt; j++) {
                dst = &h->unk4[j];
                buf = *(CamF2Seg *)data;
                data += 0x12;
                func_80626478(dst->a, buf.a);
                func_80626478(dst->c, buf.c);
                func_80626478(dst->b, buf.b);
            }
        }
    }
    hdr = (s16 *)data;
    cnt = arg1->unkC0 = hdr != NULL ? *hdr++ : 0;
    if (arg2 != 0) {
        arg1->unkC8 = func_80610FE8(cnt);
        arg1->unkC4 = func_80610FE8(cnt * 0x1CU);
        s = hdr;
        for (i = 0; i < cnt; i++) {
            arg1->unkC8[i] = func_806531B8(s[8], s[9], s[10], 0);
            s += 0xE;
            arg1->unkC4[i] = *(CamF2Bnd *)(s - 0xE);
        }
        hdr = s;
    }
    i = 0;
    cnt = arg1->unkCC = hdr != NULL ? *hdr++ : 0;
    arg1->unkD0 = func_80610FE8(cnt * 0xCU);
    for (i = 0; i < cnt; i++) {
        m = *hdr++;
        k = m;

        arg1->unkD0[i].unk0 = m;
        arg1->unkD0[i].unk4 = func_80610FE8(m * 2);
        arg1->unkD0[i].unk8 = func_80610FE8(m * 2);
        for (j = 0; j < k; j++) {
            arg1->unkD0[i].unk4[j] = *hdr++;
            arg1->unkD0[i].unk8[j] = *hdr++;
        }
    }
    i = 0;
    cnt = arg1->unkD4 = hdr != NULL ? *hdr++ : 0;
    arg1->unkD8 = func_80610FE8(0x6400);
    heapClearBlock(arg1->unkD8);
    rd = (u8 *)hdr;
    if (cnt != 0) {
        do {
            skip = 0;
            pt = &arg1->unkD8[i];
            pt->unk1 = rd[1];
            arg1->unkD8[i].unk0 = rd[0];
            pt = (CamPathPoint *)&pt->u.spline;
            u = (CamPathSpline *)pt;
            switch (arg1->unkD8[i].unk1) {
                case 13:
                    rd = func_8062649C(rd, u, 0xC);
                    break;
                case 12:
                    rd = func_8062649C(rd, u, 2);
                    break;
                case 10:
                case 15:
                case 16:
                    rd = func_8062649C(rd, u, 0xE);
                    break;
                case 1:
                    rd = func_8062649C(rd, u, 6);
                    break;
                case 2:
                    rd = func_8062649C(rd, u, 8);
                    break;
                case 3:
                    rd = func_8062649C(rd, u, 0xC);
                    break;
                case 4:
                    s = (s16 *)(rd + 0x20);
                    j = 0;
                    u->unk0 = *(s16 *)(rd + 4);
                    u->unk4 = func_80610FE8(u->unk0 * 0xEU);
                    for (; j < u->unk0; j++) {
                        ((CamF2E *)u->unk4)[j] = *(CamF2E *)s;
                        s += 7;
                    }
                    rd = (u8 *)s;
                    break;
                case 5:
                    s = (s16 *)(rd + 0x14);
                    j = 0;
                    u->unk0 = *(s16 *)(rd + 4);
                    u->unk4 = func_80610FE8(u->unk0 * 8U);
                    for (; j < u->unk0; j++) {
                        ((CamF2Q *)u->unk4)[j] = *(CamF2Q *)s;
                        s += 4;
                    }
                    rd = (u8 *)s;
                    break;
                default:
                    rd = func_8062649C(rd, u, 0);
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

s32 func_80626BC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s64 unused0;
    s64 unused1;
    s64 unused2;

    return sqrtf((s64)(arg0 - arg3) * (arg0 - arg3) + (s64)(arg1 - arg4) * (arg1 - arg4) +
                 (s64)(arg2 - arg5) * (arg2 - arg5));
}

#ifdef NON_MATCHING
s16 func_80626CAC(CamState *arg0, f32 *arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5) {
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
        D_807476A4 = arg5 / 40.0 * 0.25 + 0.05;
        if (!clamped) {
            arg5 = (arg5 > 1.0) ? 1.0 : arg5;
        }
        arg0->unkAC |= 0x80;
    }
    *arg1 = func_80612794(ang) * arg5 + arg3;
    *arg2 = func_80612790(ang) * arg5 + arg4;
    return ang;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/201B0/func_80626CAC.s")
#endif

typedef struct CamAVp {
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
} CamAVp; // size = 0x2F0

extern u8 D_807444FC;
void func_80627388(Mtx *, f32, f32, f32, f32, f32 *, f32 *, f32 *, f32 *);

s32 func_80626F8C(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, Mtx *arg5, f32 arg6, u8 arg7) {
    f32 w;
    f32 scale;

    w = 1.0f;
    if (arg5 != NULL) {
        func_80627388(arg5, arg0, arg1, arg2, w, &arg0, &arg1, &arg2, &w);
    }
    func_80627388(&((CamAVp *)D_807FC924)[arg7].m8[D_807444FC], arg0, arg1, arg2, w, &arg0, &arg1, &arg2, &w);
    if (0.0 <= arg2) {
        *arg3 = 16384.0f;
        *arg4 = 16384.0f;
        return 1;
    }
    func_80627388(&((CamAVp *)D_807FC924)[arg7].m88[D_807444FC], arg0, arg1, arg2, w, &arg0, &arg1, &arg2, &w);
    scale = ((CamAVp *)D_807FC924)[arg7].unk188 / 65535.0;
    arg0 *= scale;
    arg1 *= scale;
    w *= scale;
    arg0 /= w;
    arg1 /= w;
    arg0 = ((CamAVp *)D_807FC924)[arg7].unk278 * 0.5 * arg0;
    arg1 = ((CamAVp *)D_807FC924)[arg7].unk27A * 0.5 * arg1;
    arg0 = ((CamAVp *)D_807FC924)[arg7].unk270 + ((CamAVp *)D_807FC924)[arg7].unk278 * 0.5 + arg0;
    arg1 = ((CamAVp *)D_807FC924)[arg7].unk272 + ((CamAVp *)D_807FC924)[arg7].unk27A * 0.5 + arg1;
    arg1 = (((CamAVp *)D_807FC924)[arg7].unk27A - (arg1 - ((CamAVp *)D_807FC924)[arg7].unk272)) + ((CamAVp *)D_807FC924)[arg7].unk272;
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

void func_80627388(Mtx *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 *arg5, f32 *arg6, f32 *arg7, f32 *arg8) {
    f32 m[4][4];

    guMtxL2F(m, arg0);
    *arg5 = (m[0][0] * arg1 + m[1][0] * arg2 + m[2][0] * arg3) + m[3][0];
    *arg6 = (m[0][1] * arg1 + m[1][1] * arg2 + m[2][1] * arg3) + m[3][1];
    *arg7 = (m[0][2] * arg1 + m[1][2] * arg2 + m[2][2] * arg3) + m[3][2];
    *arg8 = (m[0][3] * arg1 + m[1][3] * arg2 + m[2][3] * arg3) + m[3][3];
}

f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);

void func_80627490(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    *arg0 = mathAngleBetweenPointsDeg(arg5, arg7, arg2, arg4) * 0.017453292f;
    *arg1 = func_80611BB4(arg3 - arg6, sqrtf((arg2 - arg5) * (arg2 - arg5) + (arg4 - arg7) * (arg4 - arg7)));
}

void func_8062754C(f32 arg0) {
    s16 i;

    func_8061F2B8(((CamAPlayer *)D_807FC924)->unk228, ((CamAPlayer *)D_807FC924)->unk22C, ((CamAPlayer *)D_807FC924)->unk230, 517.0f, 312.0f, 346.0f, 347.0f, 312.0f, 494.0f, &((CamAPlayer *)D_807FC924)->unk210, &((CamAPlayer *)D_807FC924)->unk214, &((CamAPlayer *)D_807FC924)->unk218);
    ((CamAPlayer *)D_807FC924)->unk210 = (((CamAPlayer *)D_807FC924)->unk210 - ((CamAPlayer *)D_807FC924)->unk228) * arg0 + ((CamAPlayer *)D_807FC924)->unk228;
    ((CamAPlayer *)D_807FC924)->unk214 = (((CamAPlayer *)D_807FC924)->unk214 - ((CamAPlayer *)D_807FC924)->unk22C) * arg0 + ((CamAPlayer *)D_807FC924)->unk22C;
    ((CamAPlayer *)D_807FC924)->unk218 = (((CamAPlayer *)D_807FC924)->unk218 - ((CamAPlayer *)D_807FC924)->unk230) * arg0 + ((CamAPlayer *)D_807FC924)->unk230;
    for (i = 1; i < D_807FC928; i++) {
        ((CamAPlayer *)D_807FC924)[i].unk210 = ((CamAPlayer *)D_807FC924)->unk210;
        ((CamAPlayer *)D_807FC924)[i].unk214 = ((CamAPlayer *)D_807FC924)->unk214;
        ((CamAPlayer *)D_807FC924)[i].unk218 = ((CamAPlayer *)D_807FC924)->unk218;
    }
}

f32 func_806276AC(void) {
    s16 i;

    for (i = 0; i < D_807FC928;) {
        ((CamAPlayer *)D_807FC924)[i].unk228 = 586.0f;
        ((CamAPlayer *)D_807FC924)[i].unk22C = 205.0f;
        ((CamAPlayer *)D_807FC924)[i].unk230 = 584.0f;
        i++;
    }
    return 1.0f;
}

typedef struct CamA3St {
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
} CamA3St;

typedef struct CamA3Act {
    /* 0x00 */ u8 pad0[0xB4];
    /* 0xB4 */ f32 unkB4;
} CamA3Act;

void func_80627888(CamActor *);

s32 func_8062773C(CamActor *arg0) {
    CamA3St *st = (CamA3St *)arg0->unk174;
    s16 ang;

    ang = st->unkB2 + 0x800;
    if (st->unkF0 != 0) {
        func_8062217C(arg0, st->unkF0);
    } else {
        func_8062217C(arg0, 1);
    }
    ((CamA3Act *)arg0)->unkB4 = st->unkB8;
    st->unkF1 = 0xB;
    st->unkF3 = 1;
    func_80627888(arg0);
    st->unk94 = st->unkA0 / 3.0;
    D_807FC924[st->unkFB].unk27C = 45.0f;
    st->unk78 = st->unk0->unk7C;
    st->unk7C = st->unk0->unk80 + st->unk0->unk15E;
    st->unk80 = st->unk0->unk84;
    func_8061B840((CamAV *)st, 0xB);
    sfxStopSlotSound(st->unk0, 0);
    st->unk0->unk6A &= ~0x2000;
    return ang;
}

void func_80627878(CamActor *arg0) {
    CamA3St *st = (CamA3St *)arg0->unk174;

    st->unkB4 = st->unkB2;
}

void func_80627888(CamActor *arg0) {
    CamA3St *st = (CamA3St *)arg0->unk174;

    st->unkB2 = st->unkB4;
    arg0->unk15F = (f64)st->unkB2 / 4095.0 * 255.0;
}

void func_80627948(CamActor *arg0, u8 arg1, u8 arg2, u8 arg3) {
    s16 sp2E;
    s16 sp2C;

    if (func_80671E00(arg0->unk7C, arg0->unk80, arg0->unk84, 80.0f, &sp2E, &sp2C, 1, 0xBC)) {
        arg0->unkE6 = mathAngleBetweenPoints2D(((CamAPlayer *)D_807FC924)->unk210, ((CamAPlayer *)D_807FC924)->unk218, arg0->unk7C, arg0->unk84);
        func_8061CC40(arg0, arg2, arg3);
    } else {
        func_8061CC40(arg0, arg1, arg3);
    }
}
