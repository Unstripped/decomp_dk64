#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern u8 D_807FBD70;

typedef struct R1C8CBSub178 {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u8 unk2;
} R1C8CBSub178;

typedef struct R1C8CBActor {
    /* 0x000 */ u8 pad0[0x11C];
    /* 0x11C */ struct R1C8CBActor *unk11C;
    /* 0x120 */ u8 pad120[0xA];
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[4];
    /* 0x130 */ u8 unk130;
    /* 0x131 */ u8 unk131;
    /* 0x132 */ u8 pad132[0x22];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x22];
    /* 0x178 */ R1C8CBSub178 *unk178;
} R1C8CBActor;

typedef struct R1C8CBState {
    /* 0x00 */ u8 pad0[0x1A];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[0xC];
    /* 0x28 */ u8 unk28[4];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ f32 unk30;
} R1C8CBState;

typedef struct R1C8CBView98 {
    /* 0x00 */ u8 pad0[0x3C];
    /* 0x3C */ f32 unk3C;
} R1C8CBView98;

#define R1V ((R1C8CBActor *)D_807FBB40)

f32 sqrtf(f32);
void func_80729B00(void);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void func_8072B324(Actor *, s32);
void func_8072A920(s32, s32, f32, f32, f32, s32, f32, f32, s32);
s32 func_8072881C(s32, void *);
void func_806319C4(Actor *, s32);

extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
extern u32 D_8076A064;
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
f32 func_80612790(s16);
f32 func_80612794(s16);
void lightSetFovAngles(f32, f32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, u8, u8, u8, u8);

void actorUpdateNearestSpotlight(void) {
    R1C8CBSub178 *p;
    s32 best;
    Actor *found;
    s16 i;
    Actor *e;
    f32 B[3];
    f32 A[3];
    f32 dx;
    f32 dy;
    f32 dz;
    s32 d;

    p = R1V->unk178;
    found = NULL;
    best = 999999;
    for (i = 0; i < gActiveActorCount; i++) {
        e = gActiveActors[i].actor;
        if (e->unk58 == 0xF0 || e->unk58 == 0xF9) {
            dx = e->unk7C - D_807FBB4C->unk7C;
            dy = e->unk80 - D_807FBB4C->unk80;
            dz = e->unk84 - D_807FBB4C->unk84;
            d = dx * dx + dy * dy + dz * dz;
            if (d < best) {
                best = d;
                found = e;
            }
        }
    }
    if (found != D_807FBB40) {
        D_807FBB40->unk154 = 0x40;
        return;
    }
    switch (D_807FBB40->unk58) {
        case 0xF0:
            if (D_807FBB40->unk60 & 0x100) {
                actorGetNodePos(D_807FBB40, 1, A, &A[1], &A[2]);
            } else {
                A[0] = D_807FBB40->unk7C;
                A[1] = D_807FBB40->unk80;
                A[2] = D_807FBB40->unk84;
            }
            dx = D_807FBB40->unk7C - D_807FBB4C->unk7C;
            dy = D_807FBB40->unk80 - D_807FBB4C->unk80;
            dz = D_807FBB40->unk84 - D_807FBB4C->unk84;
            if (dx * dx + dy * dy + dz * dz > 40000.0f && (D_807FBB40->unk60 & 0x100)) {
                actorGetNodePos(D_807FBB40, 2, B, &B[1], &B[2]);
            } else {
                B[0] = D_807FBB4C->unk7C;
                B[1] = D_807FBB4C->unk80;
                B[2] = D_807FBB4C->unk84;
            }
            lightSetFovAngles(30.0f, 80.0f);
            break;
        case 0xF9:
            A[0] = D_807FBB40->unk7C;
            A[1] = D_807FBB40->unk80;
            A[2] = D_807FBB40->unk84;
            B[0] = func_80612794(D_807FBB40->unkE6) * 40.0f + D_807FBB40->unk7C;
            B[1] = D_807FBB40->unk80 - 20.0f;
            B[2] = func_80612790(D_807FBB40->unkE6) * 40.0f + D_807FBB40->unk84;
            lightSetFovAngles(20.0f, 40.0f);
            break;
    }
    p->unk0 = func_80612794(D_8076A064 * 130) * 35.0 + 220.0;
    lightAdd(A[0], A[1], A[2], B[0], B[1], B[2], 0.0f, 1, ((u8 *)p)[1], ((u8 *)p)[1], ((u8 *)p)[1]);
}

void func_806C6884(s16 arg0, s16 arg1, u16 arg2) {
    u16 dist;
    f32 dx;
    f32 dz;

    func_80729B00();
    dx = D_807FBB40->unk7C - D_807FDC94->unk7C;
    dz = D_807FBB40->unk84 - D_807FDC94->unk84;
    dist = (u16)sqrtf(dx * dx + dz * dz);
    if (!(D_807FBB40->unk60 & 0x10)) {
        R1C8CBSub178 *p = R1V->unk178;
        D_807FBB40->unk64 |= 4;
        D_807FBB40->unk60 |= 0x800000;
        D_807FBB40->unk16A = 0xFF;
        D_807FBB40->unk16B = 0xFF;
        D_807FBB40->unk16C = 0xFF;
        p->unk2 = 0;
        p->unk0 = 0xFF;
        ((R1C8CBView98 *)D_807FDC98)->unk3C = 1.0f;
        if (D_807FBB40->unk58 == 0xF0) {
            sfxPlayActorSound(D_807FBB40, 0x132, 0, 0, 0, 0xA0, 1.0f, 0);
        }
    }
    if (dist - arg1 < 0) {
        dist = 0;
    } else {
        dist = dist - arg1;
    }
    func_8072B324(D_807FBB40, (s32)((u32)dist * 2.0));
    func_8072A920(0x23, arg0, D_807FDC94->unk7C, D_807FDC94->unk80 + arg0 * 3.0, D_807FDC94->unk84, 0x1E, 3.3f, 100.0f, arg2 | 0x2000);
    D_807FBB40->unk80 += 0.5 * func_80612794(D_8076A064 * 40);
    actorUpdateNearestSpotlight();
    func_806319C4(D_807FBB40, 0);
}


void func_806C6B50(void) {
    D_807FBB40->unkAC = 99999.0f;
    func_806C6884(0, 0xA, 0x44);
    func_8072881C(0, D_807FDC90->unk28);
}

void func_806C6BA0(void) {
    func_806C6884(0xA, 0x14, 0x240);
}

extern Actor *D_807FBB44;
void func_806A2A10(s32, s32, u8);
void actorSetStateTwo(Actor *);
void func_805FF9AC(s32, s32, s32, s32);
void func_807248B0(Actor *, f32);
void func_80614EBC(Actor *, s32);
void func_80614D00(Actor *, f32, f32);
void func_8061CC30(void);
s32 func_8061CC40(Actor *, s32, s32);
void effectSpawnSparks(s32, s32);
s32 func_80611A44(void);
void func_8063DA40(s32, s32);
void actorDespawn(Actor *);
void func_8072D13C(s32, s32);
void func_8072DC7C(s32);

#define R1S ((R1C8CBState *)D_807FDC90)

void func_806C6BC8(void) {
    f32 ratio;
    f32 x;
    f32 y;
    f32 z;

    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        R1V->unk12A = 0x7D0;
        R1V->unk130 = 0xFF;
        R1V->unk131 = 0xFF;
        D_807FBB40->unk60 &= ~0x8000;
        R1V->unk154 = 0x27;
        R1V->unk155 = 0;
        D_807FDC90->unk30 = D_807FBB40->unk4->unk38;
        R1S->unk2E = 0x96;
        D_807FDC98->unk46 |= 0x60;
        func_806A2A10(0xDC, 0x2A, 0x64);
        actorSetStateTwo(D_807FBB44);
    }
    if (R1S->unk1A & 0x80) {
        D_807FBB40->unk60 |= 0x400;
    } else {
        D_807FBB40->unk60 &= ~0x400;
    }
    func_8072881C(0, R1S->unk28);
    switch (R1V->unk154) {
        case 0:
            if (R1S->unk2C != 0) {
                ratio = (f32)R1S->unk2C / (f32)R1S->unk2E;
                actorGetNodePos(D_807FBB40, 2, &x, &y, &z);
                func_807248B0(D_807FBB4C, ratio * 0.13 + 0.02);
                D_807FBB4C->unk7C += (x - D_807FBB4C->unk7C) * 0.05;
                D_807FBB4C->unk80 += (y - D_807FBB4C->unk80) * 0.05;
                D_807FBB4C->unk84 += (z - D_807FBB4C->unk84) * 0.05;
                R1S->unk2C--;
                if (R1S->unk2C == 0) {
                    func_805FF9AC(0x33, 0, 0, 1);
                }
            }
            break;
        case 0x27:
            if (R1S->unk2E != 0) {
                D_807FBB40->unk80 += 2.0f;
                R1S->unk2E--;
                func_807248B0(D_807FBB40, R1S->unk30 + (0.01 - R1S->unk30) * (R1S->unk2E / 150.0));
            } else {
                R1V->unk154 = 2;
                R1V->unk155 = 0;
            }
            break;
        case 2:
            if (D_807FBD70 == 4) {
                func_80614EBC(D_807FBB40, 0);
                func_80614D00(D_807FBB40, 0.0f, 0.0f);
                R1V->unk154 = 0;
                R1V->unk155 = 0;
                func_8061CC30();
                R1S->unk2C = func_8061CC40(D_807FBB40, 0x18, 1) - 0x1E;
                R1S->unk2E = R1S->unk2C;
                D_807FBB40->unk144 = 1;
            } else {
                switch (R1V->unk155) {
                    case 5:
                        func_8072B324(D_807FBB40, D_807FDC9C->unkC);
                        R1V->unk155 = 0;
                        break;
                    case 3:
                        func_8072B324(D_807FBB40, 0);
                        func_80614EBC(D_807FBB40, 0x2BB);
                        R1V->unk155 = 4;
                    case 4:
                    case 0:
                        effectSpawnSparks(3, 1);
                        if (R1V->unk155 == 0) {
                            if ((func_80611A44() >> 15) % 1000 >= 0x3DF) {
                                R1V->unk155 = 3;
                            }
                        }
                        if (R1V->unk11C->unk154 == 5 || D_807FBB4C->unk58 != 3) {
                            func_80614EBC(D_807FBB40, 0x2BA);
                            func_80614D00(D_807FBB40, 0.0f, 0.0f);
                            func_8063DA40(0x33, 0);
                            actorDespawn((Actor *)R1V->unk11C);
                            R1V->unk155 = 1;
                        }
                        func_8072A920(2, 0, D_807FDC90->unkA, D_807FDC90->unkC, D_807FDC90->unkE, 0x46, 30.0f, 100.0f, 0x200);
                        func_8072D13C(2, 0);
                        break;
                    case 1:
                        func_8072DC7C(5);
                        break;
                    case 2:
                        R1V->unk154 = 0x3B;
                        break;
                }
            }
            break;
    }
    func_806319C4(D_807FBB40, 0);
}
