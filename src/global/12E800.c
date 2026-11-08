#include "common.h"
#include "actor.h"

extern Actor *gCurrentActor;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern void *gPlayerSlots;

typedef struct D1S10 {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
} D1S10;

typedef struct D1S4 {
    /* 0x00 */ D1S10 *unk0;
} D1S4;

typedef struct D1S174 {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ u32 unk1F0;
    /* 0x1F4 */ u8 pad1F4[4];
    /* 0x1F8 */ u32 unk1F8;
} D1S174;

typedef struct D1Dc90ViewD {
    /* 0x00 */ Struct807FDC98 *unk0;
    /* 0x04 */ Actor *unk4;
    /* 0x08 */ u8 pad8[0xE];
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u16 unk18;
} D1Dc90ViewD;

typedef struct D1Dc98ViewD {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ void *unk1C;
    /* 0x20 */ u8 pad20[0xA];
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ u8 pad2C[0x1A];
    /* 0x46 */ u16 unk46;
} D1Dc98ViewD;

#define D1DC90D ((D1Dc90ViewD *)D_807FDC90)
#define D1DC98D ((D1Dc98ViewD *)D_807FDC98)
typedef struct D1ActorViewE {
    /* 0x00 */ u8 pad0[0xAC];
    /* 0xAC */ f32 unkAC;
    /* 0xB0 */ u8 padB0[0x10];
    /* 0xC0 */ f32 unkC0;
} D1ActorViewE;

#define D1AE ((D1ActorViewE *)gCurrentActor)

extern void *D_807FDCA0;
extern u8 D_807444EC;
extern s32 gCurrentMap;
extern u8 D_807FBB85;
void actorScriptStart(Actor *, s32);
void actorGlobalStateClearEvents(void);
s32 sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);
void sfxStopSlotSound(Actor *, s32);
void collisionClearFlags(void);

void behaviourFrameBegin(void) {
    D_807FDC90 = gCurrentActor->unk174;
    D_807FDC94 = D1DC90D->unk4;
    D_807FDC9C = (Struct807FDC9C *)(D_807FDC98 = D1DC90D->unk0);
    D_807FDCA0 = D1DC98D->unk1C;
    D_807FDC90->unk18++;
    if (gCurrentActor->flags & 0x20000000) {
        if (gCurrentActor->state != 0x37 && gCurrentActor->state != 0x36) {
            if (((D1S4 *)D_807FDC94->unk4)->unk0->unk10 != D1DC90D->unk16) {
                gCurrentActor->flags &= ~0x20000000;
            }
        }
    }
    if (gCurrentActor->collisionFlags & 2) {
        if ((D_807444EC == 1 && (D1DC98D->unk46 & 8)) || (D_807FDC94 != NULL && D_807FDC94->state == 0x42)) {
            if (gCurrentActor->state >= 0x23 && gCurrentActor->state < 0x36) {
                gCurrentActor->unk144 = 1;
                gCurrentActor->state = 0x3A;
                gCurrentActor->unk155[0] = 0;
            }
        }
        if (D_807FBB70.unk1B) {
            if (gCurrentActor->state != 0x39) {
                if (D1DC98D->unk46 & 0x800) {
                    D_807FBB70.unk15 = 1;
                } else {
                    actorGlobalStateClearEvents();
                    gCurrentActor->callbackMask = 0;
                    gCurrentActor->flags &= 0xFFFD7FFF;
                    gCurrentActor->unk144 = 1;
                    gCurrentActor->state = 0x39;
                    gCurrentActor->unk155[0] = 0;
                    actorScriptStart(gCurrentActor, D1DC98D->unk2A);
                    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x16, 0xFF, 0x7F, 0x14);
                    D1AE->unkC0 = -220.0f;
                }
            }
        }
        if ((D1DC98D->unk46 & 0x4000) && (gCurrentActor->contactFlags & 4)) {
            if (gCurrentActor->y + (f32)(u32)gCurrentActor->unk15E < D1AE->unkAC) {
                D_807FBB70.unk15 = 1;
            }
        }
        if (gCurrentMap == 0x30) {
            if (D_807FDC94->collisionFlags & 1) {
                if ((((D1S174 *)D_807FDC94->unk174)->unk1F0 ^ ((D1S174 *)D_807FDC94->unk174)->unk1F8) & 0x100000) {
                    sfxStopSlotSound(gCurrentActor, 0);
                    gCurrentActor->state = 0;
                    gCurrentActor->unk155[0] = 0;
                    D_807FBB85 = 1;
                }
            }
        }
    }
    if (gCurrentActor->actorType != 0xAF && gCurrentActor->state == 0x37 && gCurrentActor->callbackMask != 0) {
        gCurrentActor->callbackMask = 0;
        if (!D_807FBB70.unk1B) {
        }
    }
    collisionClearFlags();
}

typedef struct D1ActorView {
    /* 0x00 */ u8 pad0[0xC0];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ f32 unkC4;
    /* 0xC8 */ f32 unkC8;
} D1ActorView;

#define D1A ((D1ActorView *)gCurrentActor)

void actorApplyGravity(void) {
    D1A->unkC0 = D1A->unkC0 + D1A->unkC4;
    if (D1A->unkC0 < D1A->unkC8) {
        D1A->unkC0 = D1A->unkC8;
    }
}

typedef struct D1Dc90ViewJ {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0xA];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[2];
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ u8 pad20;
    /* 0x21 */ u8 unk21;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ u8 unk24;
} D1Dc90ViewJ;

typedef struct D1Dc98ViewJ {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ u8 pad30[0x16];
    /* 0x46 */ u16 unk46;
} D1Dc98ViewJ;

typedef struct D1ActorViewJ {
    /* 0x00 */ u8 pad0[0x5C];
    /* 0x5C */ u16 unk5C;
    /* 0x5E */ u8 pad5E[0xC];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 pad6C[0x10];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x30];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x28];
    /* 0xE4 */ s16 unkE4;
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[6];
    /* 0xEE */ s16 unkEE;
} D1ActorViewJ;

#define D1AJ ((D1ActorViewJ *)gCurrentActor)
#define D1DC90J ((D1Dc90ViewJ *)D_807FDC90)
#define D1DC98J ((D1Dc98ViewJ *)D_807FDC98)

s32 randomNonNegative(void);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 mathAngleSignedDistance(s16, s16);
s16 mathAngleEaseToward(s16, s16, f32);
void scriptSetActorRampTarget(void *, f32, f32);

void actorTurnTowardTarget(u8 mode, f32 arg1, f32 arg2, u16 flags) {
    s16 *cur = &D1AJ->unkE6;
    s16 *cur2 = &D1AJ->unkEE;
    s16 *tgt = &D1DC90J->unk8;
    f32 spd;
    u8 s;
    s16 dist;
    s32 e;

    switch (mode) {
        case 1:
            if (D1DC90J->unk22-- == 0) {
                s = D1DC90J->unk21;
                *tgt = *cur + ((((randomNonNegative() >> 15) % (s * 2)) - s) << 15) / 0x168;
                D1DC90J->unk22 = D1DC90J->unk23;
                D1DC98J->unk46 &= ~0x2000;
                if (D1AJ->unkE6 & 1) {
                    D1DC90J->unk24 = (randomNonNegative() >> 15) % 0xB4;
                }
            }
            break;
        case 0x24:
            *tgt = mathAngleBetweenPoints2D(D1AJ->unk7C, D1AJ->unk84, arg1, arg2);
            break;
        case 2:
        case 3:
        case 4:
        case 0x15:
        case 0x23:
        case 0x26:
        case 0x33:
        case 0x34:
        case 0x42:
        case 0x45:
        case 0x5B:
            *tgt = mathAngleBetweenPoints2D(arg1, arg2, D1AJ->unk7C, D1AJ->unk84);
            break;
        case 0x10:
            *tgt = mathAngleBetweenPoints2D(D1AJ->unk7C, D1AJ->unk84, arg1, arg2);
            break;
        case 0x35:
            if ((randomNonNegative() >> 15) % 0x1E == 0) {
                D1DC90J->unk24 = (randomNonNegative() >> 15) % 0xB4;
            }
        case 7:
            *tgt = mathAngleBetweenPoints2D(D1DC90J->unkA, D1DC90J->unkE, D1AJ->unk7C, D1AJ->unk84);
            break;
        case 0:
            *tgt = *cur;
            break;
    }
    dist = mathAngleSignedDistance(*tgt, *cur);
    if (!(flags & 0x100) && mode != 0x37) {
        if (flags & 4) {
            spd = (u32)D1DC90J->unk1E;
        } else {
            spd = (D1DC90J->unk1A & 0x80)
                ? (D1DC90J->unk1E / 2)
                : ((u32)D1DC90J->unk1E /
                   (((0.1 < D1AJ->unkB8 / 30.0 ? D1AJ->unkB8 / 30.0 : 0.1) < 2.0)
                        ? (0.1 < D1AJ->unkB8 / 30.0 ? D1AJ->unkB8 / 30.0 : 0.1)
                        : 2.0));
        }
        *cur = mathAngleEaseToward(*cur, *tgt, spd);
        if ((D1AJ->unk6A & 1) || (flags & 0x80) || (D1AJ->unk5C & 0x40)) {
            *cur2 = mathAngleEaseToward(*cur2, *cur, (u32)D1DC90J->unk1F);
        }
    }
    if (flags & 0x40) {
        D1AJ->unkE4 = (((dist > -0x320 ? dist : -0x320) < 0x320 ? (dist > -0x320 ? dist : -0x320) : 0x320) - D1AJ->unkE4) * 0.1 + D1AJ->unkE4;
    }
    if (flags & 4) {
        if (dist != 0) {
            f32 t = dist * D1DC98J->unk2C;
            f32 a = 0.0f < t ? t : -t;

            scriptSetActorRampTarget(gCurrentActor, a > 1.0 ? 1.0 : a, 0.0f);
        }
    }
}

typedef struct D1Tbl8075EB80 {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 pad16[2];
} D1Tbl8075EB80; // size = 0x18

typedef struct D1Dc98ViewC {
    /* 0x00 */ u8 pad0[0x30];
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[0x10];
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 pad45;
    /* 0x46 */ u16 unk46;
} D1Dc98ViewC;

#define D1DC98C ((D1Dc98ViewC *)D_807FDC98)

extern D1Tbl8075EB80 D_8075EB80[];
void billboardSubmit(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);

void func_8072A450(void) {
    u8 a;
    u8 b;
    u8 c;
    D1Tbl8075EB80 *e;
    ActorSub4 *sub;

    if (!(gCurrentActor->flags & 0x1000000) && (gCurrentActor->flags & 4)) {
        if (!(D1DC98C->unk46 & 0x100)) {
            a = (u32)((f64)gCurrentActor->unk128 * 0.7);
            sub = gCurrentActor->unk4;
            e = &D_8075EB80[D1DC98C->unk44];
            b = (u32)(sub->unk34 * (u32)e->unk14 * D1DC98C->unk30);
            c = (u32)(sub->unk3C * (u32)e->unk15 * D1DC98C->unk30);
            billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, b, c, 1, 0x12C, a, gCurrentActor->yaw, 1.0f);
        }
    }
}


typedef struct D1ActorView3 {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ ActorSub4 *unk4;
    /* 0x08 */ u8 pad8[0x54];
    /* 0x5C */ u16 unk5C;
    /* 0x5E */ u8 pad5E[0x1E];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x24];
    /* 0xAC */ f32 unkAC;
    /* 0xB0 */ u8 padB0[0x10];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ u8 padC4[0x2C];
    /* 0xF0 */ s16 unkF0;
    /* 0xF2 */ u8 padF2[0x6C];
    /* 0x15E */ u8 unk15E;
} D1ActorView3;

#define D1A3 ((D1ActorView3 *)gCurrentActor)
#define D1A3_154 (*(u8 *)((u8 *)gCurrentActor + 0x154))

extern u8 D_80720120[];
extern u16 D_80744508;
s32 func_80666A94();
s32 func_80666AA0();
s32 func_80714CC0(void *, f32, f32, f32, f32);

void func_8072A714(void) {
    if (D1A3->unk5C & 2) {
        if (func_80666A94() || func_80666AA0()) {
            if (func_80666AA0()) {
                func_80714CC0(&D_80720120, D1A3->unk4->unk38 * 6.66666666999999968, D1A3->unk7C, D1A3->unk80, D1A3->unk84);
            }
            D1A3_154 = 0x40;
            D_80744508++;
        }
    }
}

typedef struct D1Dc90View {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 pad0E[0xC];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[0x1C];
    /* 0x38 */ u8 unk38;
} D1Dc90View;

#define D1DC90 ((D1Dc90View *)D_807FDC90)

typedef struct D1ActorView2 {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ f32 unk90;
} D1ActorView2;

#define D1A2 ((D1ActorView2 *)gCurrentActor)

void actorUpdateStationaryTimer(void) {
    if (!(D1DC90->unk1A & 0x40)) {
        if (D1A2->unk7C == D1A2->unk88 && D1A2->unk84 == D1A2->unk90) {
            D1DC90->unk38++;
            if (D1DC90->unk38 >= 0x1F) {
                D1DC90->unk1A |= 0x40;
            }
        } else {
            D1DC90->unk38 = 0;
        }
    }
}

f32 func_80612794(s16);
u32 actorMoveWithinZone(u8, f32, f32, u16, f32);

void func_8072A86C(s16 arg0, f32 arg1, f32 arg2, f32 arg3, u16 arg4) {
    D1A3->unkC0 = func_80612794(D1A3->unkF0) * -arg3;
    actorMoveWithinZone(arg0, arg1, arg2, (arg4 & 0xFFFF) | 0x1080, 0.5 * (u32)D1A3->unk15E);
}

typedef struct D1ActorView4 {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x60];
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ u8 padEA[6];
    /* 0xF0 */ s16 unkF0;
} D1ActorView4;

#define D1A4 ((D1ActorView4 *)gCurrentActor)

f32 mathCalculatePitchAngle(f32, f32, f32, f32, f32, f32, s32);

void func_8072A920(s16 arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4, u8 arg5, f32 arg6, f32 arg7, u16 arg8) {
    D1A4->unkE8 = mathAngleEaseToward(D1A4->unkE8, (s16)(s32)(mathCalculatePitchAngle(arg2, arg3, arg4, D1A4->unk7C, D1A4->unk80, D1A4->unk84, arg5) * 2048.0 / 3.14159274101257324), arg6);
    D1A4->unkF0 = mathAngleEaseToward(D1A4->unkF0, (s16)(s32)(mathCalculatePitchAngle(arg2, (f32)arg1 + arg3, arg4, D1A4->unk7C, D1A4->unk80, D1A4->unk84, arg5) * 2048.0 / 3.14159274101257324), arg6);
    func_8072A86C(arg0, arg2, arg4, arg7, arg8);
}

typedef struct D1Dc9cView {
    /* 0x00 */ u8 pad0[6];
    /* 0x06 */ s16 unk6;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ s16 unkA;
} D1Dc9cView;

#define D1DC9C ((D1Dc9cView *)D_807FDC9C)


void func_8072AA80(void) {
    s16 lim;
    s32 rnd;
    s32 base;

    if (D1DC9C->unkA != 0) {
        lim = D1DC9C->unk6 + D1A3->unk15E + D1DC9C->unkA;
    } else {
        lim = (s32)(s16)D1A3->unkAC - D1A3->unk15E;
    }
    rnd = (randomNonNegative() >> 15) % 0x7FFF;
    base = D1DC9C->unk6 + D1A3->unk15E;
    D1DC90->unkC = rnd % (lim - base + 1) + base;
}

typedef struct E3Actor {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ ActorSub4 *unk4;
    /* 0x08 */ u8 pad8[0x34];
    /* 0x3C */ u8 pad3C[0x20];
    /* 0x5C */ u16 unk5C;
    /* 0x5E */ u8 pad5E[0x1E];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 pad94[0x10];
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ u8 padA8[0x10];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ u8 padC4[0x22];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[6];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[0xC];
    /* 0xFC */ u8 unkFC;
    /* 0xFD */ u8 unkFD;
} E3Actor;

typedef struct E3Dc90 {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s16 unk8;
    /* 0x0A */ u8 padA[6];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[4];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ u8 pad1E[4];
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
} E3Dc90;

typedef struct E3Dc98 {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ u8 pad38[0xE];
    /* 0x46 */ u16 unk46;
} E3Dc98;

typedef struct E3DcA0 {
    /* 0x00 */ u8 pad0[0x19];
    /* 0x19 */ u8 unk19;
} E3DcA0;

#define E3A ((E3Actor *)gCurrentActor)
#define E3C90 ((E3Dc90 *)D_807FDC90)
#define E3C98 ((E3Dc98 *)D_807FDC98)
#define E3CA0 ((E3DcA0 *)D_807FDCA0)

s32 mathAngleDistance(s16, s16);
void func_8067ACB4(Actor *);
void actorTurnTowardTarget(u8, f32, f32, u16);
void collisionSetQueryMode(s32);
void actorStepPhysics(Actor *, s16, s16);
void actorApplyVelocityCustom(Actor *, f32, f32);
void actorUpdateFloorContactAndTilt(Actor *, f32);
void actorApproachTargetSpeed(u16);
void actorApplyVelocity(Actor *);
u8 collisionCheckActorFloor(Actor *, f32, f32, f32, f32 *);
s32 polygonContainsPoint2D(s16, s16, void *);
s32 zoneCheckActorInside(Actor *, f32, f32, void *, s16 *);
f32 func_80612790(s16);

u32 actorMoveWithinZone(u8 arg0, f32 arg1, f32 arg2, u16 arg3, f32 arg4) {
    f32 area;
    s16 sp52;
    s16 *sp4C;
    f32 dd0;
    f32 dd1;
    u8 sp43;

    area = gCurrentActor->unk4->unk38 / 0.15;
    sp43 = 0;
    sp4C = &E3C90->unk8;
    E3C90->unk1C = E3C90->unk1A;
    E3C90->unk1A &= 0xBD7F;
    if ((E3A->unk7C - arg1) * (E3A->unk7C - arg1) + (E3A->unk84 - arg2) * (E3A->unk84 - arg2) < 1600.0f * area) {
        E3C90->unk1A |= 0x80;
        if (mathAngleDistance(*sp4C, E3A->unkE6) >= 0x191) {
            E3A->unkB8 *= E3C98->unk34;
        }
    }
    func_8067ACB4(gCurrentActor);
    if (E3A->unkB8 != 0.0f || (arg3 & 4)) {
        actorTurnTowardTarget(arg0, arg1, arg2, arg3);
    }
    if (!(arg3 & 0x1001)) {
        actorApplyGravity();
    }
    if (!(E3C98->unk46 & 0x200)) {
        collisionSetQueryMode(2);
    }
    if (E3CA0->unk19 == 1 && (arg0 != 0x37 || !(E3C98->unk46 & 0x10))) {
        collisionSetQueryMode(1);
    }
    if (arg3 & 0x4000) {
        E3A->unkFC = 0;
    }
    if (arg0 != 0x37 && !(E3C90->unk1A & 2)) {
        actorStepPhysics(gCurrentActor, E3A->unkEE, E3A->unkE6);
    }
    if (arg3 & 2) {
        if (!(arg3 & 1)) {
            actorApplyVelocityCustom(gCurrentActor, 0, E3A->unkC0);
        }
        actorUpdateFloorContactAndTilt(gCurrentActor, arg4);
        if (!(arg3 & 0x2000)) {
            func_8072A714();
        }
        if (!(arg3 & 0x10)) {
            func_8072A450();
        }
        return 0;
    }
    if (!(arg3 & 0x20)) {
        actorApproachTargetSpeed(arg3);
    }
    if (arg3 & 0x800) {
        actorApplyVelocityCustom(gCurrentActor, 0, E3A->unkC0);
    } else if (arg3 & 1) {
        actorApplyVelocityCustom(gCurrentActor, E3A->unkB8, 0);
    } else {
        actorApplyVelocity(gCurrentActor);
    }
    if (!(arg3 & 8)) {
        actorUpdateFloorContactAndTilt(gCurrentActor, arg4);
    } else if (E3CA0->unk19 != 1 && (arg3 & 0x10)) {
        collisionCheckActorFloor(gCurrentActor, E3A->unk7C, E3A->unk8C, E3A->unk84, &E3A->unkA4);
    }
    if (!(arg3 & 0x2000)) {
        func_8072A714();
    }
    if (!(arg3 & 0x10)) {
        func_8072A450();
    }
    E3A->unkFC = 0;
    E3A->unkFD = 0;
    if ((E3C98->unk46 & 0x20) || (E3A->unk5C & 0x40)) {
        return 0;
    }
    if (arg0 == 0x37 && (E3C98->unk46 & 0x10)) {
        if (polygonContainsPoint2D(E3A->unk7C, E3A->unk84, D_807FDCA0) == 0) {
            E3A->unkB8 = ((E3A->unkB8 >= 0.0f) ? 1 : -1) * 30;
            return 0;
        }
        E3C90->unk1A |= 0x4000;
        if (0) {
        }
        return 0;
    }
    if (polygonContainsPoint2D(E3A->unk7C, E3A->unk84, D_807FDCA0) != 0) {
        E3C90->unk1A |= 0x4000;
        if (zoneCheckActorInside(gCurrentActor, E3A->unk88, E3A->unk90, D_807FDCA0, &sp52) == 0) {
            if (polygonContainsPoint2D(func_80612794(E3A->unkEE) * E3A->unkB8 + E3A->unk7C, func_80612790(E3A->unkEE) * E3A->unkB8 + E3A->unk84, D_807FDCA0) == 0) {
                if (E3C90->unk22-- == 0) {
                    *sp4C += 0x800;
                    *sp4C &= 0xFFF;
                    E3C90->unk22 = E3C90->unk23 * 4;
                }
            }
        } else if (arg0 == 0x37 || arg0 == 0) {
            E3A->unkB8 = 0.0f;
            E3A->unk7C = E3C90->unk10;
            E3A->unk84 = E3C90->unk14;
            return 0;
        }
        E3C90->unk10 = E3A->unk7C;
        E3C90->unk14 = E3A->unk84;
    } else {
        sp43 = 1;
        E3C90->unk1A |= 0x200;
        E3A->unk7C = E3C90->unk10;
        E3A->unk84 = E3C90->unk14;
        if (E3C90->unk22-- == 0) {
            *sp4C += 0x800;
            *sp4C &= 0xFFF;
            E3C90->unk22 = E3C90->unk23 * 6;
        }
    }
    return sp43;
}

typedef struct D1Unk174 {
    /* 0x00 */ u8 pad0[0x26];
    /* 0x26 */ s16 unk26;
} D1Unk174;

void actorSetTargetSpeed(Actor *arg0, s32 arg1) {
    D1Unk174 *s = arg0->unk174;
    s->unk26 = arg1;
}

typedef struct D1Dc98ViewB {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
} D1Dc98ViewB;

typedef struct D1Sub4B {
    /* 0x00 */ u8 pad0[0x48];
    /* 0x48 */ f32 unk48;
} D1Sub4B;

typedef struct D1ActorViewB {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ D1Sub4B *unk4;
    /* 0x08 */ u8 pad8[0x62];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 pad6C[0x4C];
    /* 0xB8 */ f32 unkB8;
} D1ActorViewB;

#define D1AB ((D1ActorViewB *)gCurrentActor)
#define D1DC98B ((D1Dc98ViewB *)D_807FDC98)


void actorUpdateAnimSpeedFromSpeed(u16 arg0) {
    f32 t;

    t = (D1AB->unkB8 * D1DC98B->unk38 > 3.0) ? 3.0 : D1AB->unkB8 * D1DC98B->unk38;
    if (D1AB->unk6A & 4) {
        t *= 0.5;
    }
    if (!(D1DC98B->unk3C < t)) {
        t = D1DC98B->unk3C;
    }
    if (!((arg0 & 0x400) && t < 1.0)) {
        if (!(arg0 & 0x200) && t != D1AB->unk4->unk48) {
            scriptSetActorRampTarget(gCurrentActor, t, 0.0f);
        }
    }
}

typedef struct D1Dc90ViewB {
    /* 0x00 */ u8 pad0[0x26];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ u8 pad28[0xD];
    /* 0x35 */ u8 unk35;
} D1Dc90ViewB;

#define D1DC90B ((D1Dc90ViewB *)D_807FDC90)

extern u32 gFrameCounter;
void func_8072DAA4();

void actorApproachTargetSpeed(u16 arg0) {
    s32 spd;
    f32 tgt;

    spd = D1DC90B->unk26;
    if (D1AB->unkB8 < -60.0f) {
        if ((D1AB->unk6A & 1) && (gFrameCounter % 5) == 0) {
            func_8072DAA4();
        }
    }
    tgt = spd;
    if (tgt != D1AB->unkB8) {
        if (D1AB->unkB8 < tgt) {
            D1AB->unkB8 = (tgt < D1AB->unkB8 + (u32)D1DC90B->unk35) ? tgt : D1AB->unkB8 + (u32)D1DC90B->unk35;
        } else if (tgt < D1AB->unkB8) {
            D1AB->unkB8 = (D1AB->unkB8 - (u32)D1DC90B->unk35 < tgt) ? tgt : D1AB->unkB8 - (u32)D1DC90B->unk35;
        }
    }
    actorUpdateAnimSpeedFromSpeed(arg0);
}

void actorSetBehaviourState(u8 arg0, s16 arg1, s32 arg2) {
    D1A3_154 = arg0;
    *((u8 *)gCurrentActor + 0x155) = 0;
    if (arg2 != D1A3->unk4->animId) {
        actorScriptStart(gCurrentActor, arg2);
    }
    actorSetTargetSpeed(gCurrentActor, arg1);
}

void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void actorAddPulsingLight(void) {
    u32 phase;
    f32 x;
    f32 base;

    func_80612794((s16)(((gFrameCounter % 0xFFF) * 4) % 0xFFF));
    func_80612790((s16)(((gFrameCounter % 0xFFF) * 4) % 0xFFF));
    phase = (gFrameCounter * 4) % 150;
    base = 100.0f;
    if (phase > 75) {
        x = (f32)(phase - 75) + base;
    } else {
        x = base + 50.0 - phase;
    }
    lightAdd(D1A3->unk7C, D1A3->unk80 + 10.0f, D1A3->unk84, 0.0f, 0.0f, 0.0f, x, 0, 0xFF, 0xFF, 0xFF);
}



void behaviourSetAnimIds(s16 arg0, s16 arg1, s16 arg2) {
    D_807FDC98->animId0 = arg0;
    D_807FDC98->animId1 = arg1;
    D_807FDC98->animId2 = arg2;
}

typedef struct F1Dc90 {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0xA];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[6];
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 pad23;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 pad25;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ u8 pad28[4];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ u8 pad30[9];
    /* 0x39 */ u8 unk39;
} F1Dc90;

typedef struct F1Dc98 {
    /* 0x00 */ u8 pad0[0x26];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ u8 pad2C[0xC];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0xA];
    /* 0x46 */ u16 unk46;
} F1Dc98;

typedef struct F1Dc9c {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ u8 padA[2];
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 padE[2];
    /* 0x10 */ u8 unk10;
} F1Dc9c;

typedef struct F1Act {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ ActorSub4 *unk4;
    /* 0x08 */ u8 pad8[0x58];
    /* 0x60 */ u32 unk60;
    /* 0x64 */ u8 pad64[6];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 pad6C[2];
    /* 0x6E */ s16 unk6E;
    /* 0x70 */ u8 pad70[2];
    /* 0x72 */ s16 unk72;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ u8 pad78[4];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 pad94[0x24];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x2A];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[0x14];
    /* 0xFC */ u8 unkFC;
    /* 0xFD */ u8 padFD[0x2B];
    /* 0x128 */ s16 unk128;
    /* 0x12A */ u8 pad12A[8];
    /* 0x132 */ s16 unk132;
    /* 0x134 */ u8 pad134[4];
    /* 0x138 */ u32 unk138;
    /* 0x13C */ u8 pad13C[4];
    /* 0x140 */ ActorSub140 *unk140;
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0xF];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[9];
    /* 0x15F */ u8 unk15F;
} F1Act;

#define F1A ((F1Act *)gCurrentActor)
#define F1S90 ((F1Dc90 *)D_807FDC90)
#define F1S98 ((F1Dc98 *)D_807FDC98)
#define F1S9C ((F1Dc9c *)D_807FDC9C)

s32 zoneFindBestReachablePoint(s32, Actor *, void *, s16 *, s16 *, s16 *);
s32 pathPlaybackStart(void *, s32, s32, f32, f32, f32, s32);
void pathPlaybackSetSpeed(s32, u8);
void pathPlaybackSetLooping(s32, s32);
void pathPlaybackSetLoopLimit(s32, s32);
void pathPlaybackSetActive(s32, s32);
void pathPlaybackAdvance(s32);
void pathPlaybackGetPosition(s32, f32 *, f32 *, f32 *);
void func_80724E48(u8);
void func_8072DC7C(u8);
void actorSetDefaultState(s32);
void func_8072E320(f32);
u8 sfxSlotAllocateActor(Actor *, s16, u8, u8, u8, f32, s8);
void actorQueueDelayedCallback();
void func_8071498C(void *);
void func_80714950(s32);
void func_807149B8(s32);
void func_80717D4C(void);
extern u8 D_8071FC58[];

void func_8072B7CC(s32 arg0) {
    func_8067ACB4(gCurrentActor);
    switch (F1A->unk154) {
        case 9:
            F1S98->unk46 |= 0x2040;
            F1S98->unk46 &= 0xFFF7;
            F1S90->unk22 = 0x64;
            F1A->unk154 = 1;
            F1A->unk155 = 0;
            F1A->unkB8 = (f32)(((randomNonNegative() >> 0xF) % 50) + 0x3C);
            break;
        case 8:
            switch (F1A->unk155) {
                case 0:
                    F1A->unk15F = pathPlaybackStart(gCurrentActor, F1S9C->unk2, 0, 0.0f, 0.0f, 0.0f, 0);
                    pathPlaybackSetSpeed(F1A->unk15F, (u32)((f64)(u32)F1S9C->unkC * 0.1));
                    pathPlaybackSetLooping(F1A->unk15F, 1);
                    pathPlaybackSetLoopLimit(F1A->unk15F, -1);
                    pathPlaybackSetActive(F1A->unk15F, 1);
                    F1A->unk155++;
                case 1:
                    pathPlaybackAdvance(F1A->unk15F);
                    pathPlaybackGetPosition(F1A->unk15F, &F1A->unk7C, &F1A->unk80, &F1A->unk84);
                    if (F1S98->unk38 != 0.0f) {
                        F1A->unkB8 = sqrtf(((F1A->unk7C - F1A->unk88) * (F1A->unk7C - F1A->unk88)) + ((F1A->unk80 - F1A->unk8C) * (F1A->unk80 - F1A->unk8C)) + ((F1A->unk84 - F1A->unk90) * (F1A->unk84 - F1A->unk90))) * 40.0f;
                        actorUpdateAnimSpeedFromSpeed(0);
                        func_8072E320(6.0f);
                    } else {
                        func_8072E320(0.0f);
                    }
                    break;
            }
            break;
        case 0x1C:
            switch (F1A->unk155) {
                case 0:
                    if (zoneFindBestReachablePoint(2, gCurrentActor, D_807FDCA0, &F1S90->unkA, &F1S90->unkC, &F1S90->unkE) == 0) {
                        F1A->unk154 = F1S9C->unk10;
                        F1A->unk155 = 0;
                        break;
                    }
                    F1A->unk155 = 1;
                case 1:
                    func_8072A920(2, 0, (f32)F1S90->unkA, (f32)F1S90->unkC, (f32)F1S90->unkE, 0x1E, 3.3f, 100.0f, 0x2240);
                    if (((F1A->unk84 - (f32)F1S90->unkE) * (F1A->unk84 - (f32)F1S90->unkE)) + (((F1A->unk7C - (f32)F1S90->unkA) * (F1A->unk7C - (f32)F1S90->unkA)) + ((F1A->unk80 - (f32)F1S90->unkC) * (F1A->unk80 - (f32)F1S90->unkC))) < 225.0f) {
                        actorScriptStart(gCurrentActor, F1S98->unk26);
                        F1A->unk155 = 2;
                    }
                    break;
                case 2:
                    if (((randomNonNegative() >> 0xF) % 1000) >= 0x3E4) {
                        actorScriptStart(gCurrentActor, F1S98->unk2A);
                        F1A->unk155 = 3;
                    }
                    break;
                case 4:
                    actorSetDefaultState(F1S98->unk28);
                    break;
            }
            break;
        case 0x39:
            scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
            switch (F1A->unk155) {
                case 0:
                    actorMoveWithinZone(0, 0.0f, 0.0f, 0x202, 0.0f);
                    F1A->unk4->unk38 = (f32)((f64)F1A->unk4->unk38 * 0.7);
                    F1A->unk4->unk34 = (f32)((f64)F1A->unk4->unk34 * 1.07);
                    F1A->unk4->unk3C = (f32)((f64)F1A->unk4->unk3C * 1.07);
                    if ((f64)F1A->unk4->unk38 < 0.01) {
                        F1A->unk155 = 1;
                    }
                    break;
                case 1:
                    func_8072DC7C(0xA);
                    break;
                case 2:
                    F1A->unk154 = 0x40;
                    D_80744508++;
                    break;
            }
            break;
        case 0:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x202, 0.0f);
            if (F1A->unk155 == 0) {
                actorSetTargetSpeed(gCurrentActor, 0);
                actorScriptStart(gCurrentActor, F1S98->unk26);
                F1A->unk155 = 1;
            }
            func_80724E48(0);
            break;
        case 0x19:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x202, 0.0f);
            if (((s16)F1S90->unk2C % 15) == 0) {
                F1S90->unk24 = (randomNonNegative() >> 0xF) % 180;
            }
            func_80724E48(2);
            switch (F1A->unk155) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    actorScriptStart(gCurrentActor, F1S98->unk26);
                    F1A->unk155 = 1;
                    break;
                case 1:
                    if (F1S90->unk2C != 0) {
                        F1S90->unk2C = F1S90->unk2C - 1;
                    } else {
                        actorSetDefaultState(F1S98->unk28);
                    }
                    break;
            }
            break;
        case 0x17:
            if ((F1A->unk6A & 1) || (F1A->unkFC != 0)) {
                actorSetTargetSpeed(gCurrentActor, F1S9C->unkD);
                F1A->unkB8 = (f32)F1S90->unk26;
                F1S90->unk1A &= 0xFFFD;
                F1A->unk154 = 0x23;
                F1A->unk155 = 0;
                actorScriptStart(gCurrentActor, F1S98->unk2A);
            } else {
                F1A->unkE6 = (f32)F1A->unkE6 + (F1A->unkB8 * 2);
                actorMoveWithinZone(0x17, 0.0f, 0.0f, (F1S90->unk1A & 2) ? 0x1020 : 0x20, 0.0f);
            }
            break;
        case 0x3A:
            if (F1A->unk155 == 0) {
                if (D_807FBB85 == 0) {
                    scriptSetActorRampTarget(gCurrentActor, 0.0f, 8.0f);
                    actorSetTargetSpeed(gCurrentActor, 0);
                }
                F1A->unk155 = F1A->unk155 + 1;
            } else if ((D_807444EC == 0) && (D_807FDC94->state != 0x42)) {
                F1A->unk132 = 1;
                F1A->unk144 = 0x24;
                F1A->unk154 = F1S9C->unk10;
                F1A->unk155 = 0;
                actorScriptStart(gCurrentActor, F1S98->unk28);
                scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
                actorSetTargetSpeed(gCurrentActor, F1S9C->unkC);
            }
            break;
        case 0x16:
            if (F1A->unk155 == 0) {
                F1A->unk155 = F1A->unk155 + 1;
            } else {
                F1A->unkE6 += 0x64;
                if (gFrameCounter & 1) {
                    F1A->unk80 += 1.0f;
                }
                if (D_807FBB4C->state != 0x67) {
                    actorQueueDelayedCallback(gCurrentActor, 0, 8, 0, 0, 0, 1);
                }
            }
            break;
        case 0x36:
            switch (F1A->unk155) {
                case 0:
                    F1A->unk60 &= 0xFFFD7FFF;
                    F1A->unk138 &= 0xFFFF7FFF;
                    F1A->unk128 = 0;
                    F1S90->unk39 = 0x5A;
                    F1S90->unk2E = F1A->unk4->unk38 * (f32)F1A->unk140->unkC;
                    F1A->unk80 -= (f32)F1S90->unk2E;
                    F1A->unk72 = 0;
                    F1A->unk155++;
                    break;
                case 1:
                    func_8071498C(func_80717D4C);
                    func_807149B8(1);
                    func_80714950(-0x28 - (((randomNonNegative() >> 0xF) % 10000) % 120));
                    func_80714CC0(D_8071FC58, 0.5f, (f32)((((randomNonNegative() >> 0xF) % 20) + F1S9C->unk4) - 0xA), (f32)F1S9C->unk6, (f32)((((randomNonNegative() >> 0xF) % 20) + F1S9C->unk8) - 0xA));
                    if (F1S90->unk39 != 0) {
                        f32 t;

                        F1S90->unk39 = F1S90->unk39 - 1;
                        t = (f32)(u32)F1S90->unk39 / 90.0f;
                        F1A->unk80 = (f32)F1S9C->unk6 + ((f32)((F1S9C->unk6 - F1S90->unk2E) - F1S9C->unk6) * t);
                        if (F1A->unk6E == -1) {
                            F1A->unk6E = sfxSlotAllocateActor(gCurrentActor, 0x131, 0, 0, 0xFF, 1.0f, 0);
                        }
                        F1A->unk74 = (f32)F1S9C->unk6 - F1A->unk80;
                        F1A->unk72 = F1A->unk72 + 1;
                        F1A->unkE6 = (f32)F1A->unkE6 + (((f32)F1S9C->unk6 - F1A->unk80) * 60.0f);
                        F1A->unk128 = (-255.0f * t) + 255.0f;
                    } else {
                        sfxStopSlotSound(gCurrentActor, 0);
                        F1A->unk154 = F1S9C->unk10;
                        F1A->unk155 = 0;
                        F1A->unk60 |= 0x28000;
                        F1A->unk138 |= 0x8000;
                        F1A->unk128 = 0xFF;
                        F1A->unk80 = (f32)F1S9C->unk6;
                    }
                    break;
            }
            break;
        case 0x3D:
            actorSetBehaviourState(0x3F, 0, arg0);
            break;
        case 0x3E:
            actorSetBehaviourState(1, F1S9C->unkC, arg0);
            break;
        case 0x3F:
            func_80724E48(0);
            break;
    }
}

typedef struct D1Dc90ViewH {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0xA];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[4];
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 pad21[0x16];
    /* 0x37 */ u8 unk37;
} D1Dc90ViewH;

typedef struct D1S174b {
    /* 0x000 */ u8 pad0[0xD4];
    /* 0x0D4 */ s16 unkD4;
    /* 0x0D6 */ u8 padD6[0x11A];
    /* 0x1F0 */ u32 unk1F0;
} D1S174b;

typedef struct D1PlayerView {
    /* 0x000 */ u8 pad0[0x2C0];
    /* 0x2C0 */ u8 unk2C0;
} D1PlayerView;

#define D1DC90H ((D1Dc90ViewH *)D_807FDC90)

extern u8 gPlayerCount;
extern u32 D_807FBB64;

u8 func_8072C670(u8 checkMode, u8 *outTarget) {
    D1S174b *st = D_807FDC94->unk174;
    u8 ret;
    u8 t;

    *outTarget = 1;
    if (gCurrentActor->collisionFlags & 2) {
        if (gCurrentActor->state != 0x15 &&
            ((D_807FDC94->actorType == 6 && ((D1PlayerView *)gPlayerSlots)->unk2C0 == 2 && gPlayerCount == 1) ||
             ((D_807FDC94->collisionFlags & 1) && (st->unk1F0 & 0x10)))) {
            ret = 7;
        } else if (D1DC90H->unk37 == 7 && checkMode != 0 && !(D1DC90H->unk1A & 0x200) && D1DC90H->unk20 == 0) {
            D1DC90H->unk20 = 0x10;
            if (zoneFindBestReachablePoint(0x81, gCurrentActor, D_807FDCA0, &D1DC90H->unkA, &D1DC90H->unkC, &D1DC90H->unkE) == 0) {
                ret = 0x10;
            } else {
                ret = 7;
            }
        } else {
            if (D1DC90H->unk20 != 0) {
                D1DC90H->unk20 = D1DC90H->unk20 - 1;
            }
            if ((D_807FDC94->collisionFlags & 1) && st->unkD4 != 0 && !(D_807FBB64 & 0x100000)) {
                ret = 1;
                *outTarget = 0;
            } else if (D1DC90H->unk1A & 0x400) {
                ret = D1DC90H->unk37;
            } else {
                t = D_807FDC9C->unk10;
                if (t == 7) {
                    ret = 1;
                } else {
                    ret = t;
                }
            }
        }
    } else {
        ret = D_807FDC9C->unk10;
    }
    if (ret == 9) {
        ret = 1;
    }
    return ret;
}

typedef struct D1Dc90ViewG {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0x15];
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 pad26[0x10];
    /* 0x36 */ u8 unk36;
} D1Dc90ViewG;

typedef struct D1Dc9cViewG {
    /* 0x00 */ u8 pad0[0xD];
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 pad0E[3];
    /* 0x11 */ u8 unk11;
} D1Dc9cViewG;

typedef struct D1Dc98ViewG {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ void *unk20;
} D1Dc98ViewG;

#define D1DC90G ((D1Dc90ViewG *)D_807FDC90)
#define D1DC9CG ((D1Dc9cViewG *)D_807FDC9C)
#define D1DC98G ((D1Dc98ViewG *)D_807FDC98)

void func_8072C870(u8 state, u8 subState, s32 param) {
    if (state == 7) {
        if (zoneFindBestReachablePoint(1, gCurrentActor, D_807FDCA0, &D1DC90G->unkA, &D1DC90G->unkC, &D1DC90G->unkE) == 0) {
            state = 0x10;
            actorSetTargetSpeed(gCurrentActor, D1DC9CG->unkD);
        }
    }
    D1DC90G->unk36 = state;
    actorSetBehaviourState(state, subState, param);
}

typedef struct C1Sub4 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
    /* 0x66 */ u8 pad66[0x2];
} C1Sub4; // size = 0x68

typedef struct C1Act {
    /* 0x00 */ u8 pad0[0x4];
    /* 0x04 */ C1Sub4 *unk4;
    /* 0x08 */ u8 pad8[0x58];
    /* 0x60 */ u32 unk60;
    /* 0x64 */ u8 pad64[0x6];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 pad6C[0x10];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x66];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x1F];
    /* 0x174 */ D1S174 *unk174;
    /* 0x178 */ s16 *unk178;
} C1Act;

typedef struct C1Dc90 {
    /* 0x00 */ u8 pad0[0x8];
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0xA];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[0x4];
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 pad21[0x5];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ u8 pad28[0xE];
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 pad37[0x1];
} C1Dc90;

typedef struct C1Dc98 {
    /* 0x00 */ u8 pad0[0x26];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 pad2A[0x1C];
    /* 0x46 */ u16 unk46;
} C1Dc98;

typedef struct C1Dc9c {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 padE[0x2];
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11[0x3];
} C1Dc9c;

#define C1B40 ((C1Act *)gCurrentActor)
#define C1D90 ((C1Dc90 *)D_807FDC90)
#define C1D98 ((C1Dc98 *)D_807FDC98)
#define C1D9C ((C1Dc9c *)D_807FDC9C)

s32 zoneCanReachPoint(Actor *, s16, s16, s16, void *);
s32 func_8072DE10(u16);

void enemyAggroStateUpdate(s32 arg0, s32 arg1, s32 arg2) {
    D1S174 *st;
    s32 dist;
    u8 pad0;
    u8 type;
    u8 sp4D;
    s16 ang;
    u32 ret;
    s32 near;
    C1Act *me;

    st = D_807FDC94->unk174;
    me = C1B40;
#define SQ(x) ((x) * (x))
    dist = (s32)(SQ(me->unk7C - D_807FDC94->x) + SQ(me->unk80 - D_807FDC94->y) + SQ(me->unk84 - D_807FDC94->z));
    near = dist < arg0;
    if (near == 0) {
        near = (C1D98->unk46 & 4) != 0;
    }
    if (C1D90->unk8 < me->unkEE) {
        ang = me->unkEE - C1D90->unk8;
    } else {
        ang = C1D90->unk8 - me->unkEE;
    }
    if ((zoneCanReachPoint((Actor *)me, D_807FDC94->x, D_807FDC94->y, D_807FDC94->z, D_807FDCA0) != 0) && !(C1D98->unk46 & 0x2000) && !(st->unk1F0 & 0x8000)) {
        C1D90->unk1A |= 0x400;
    } else {
        C1D90->unk1A &= 0xFBFF;
    }
    ret = func_8072C670(dist < 0x1388, &sp4D);
    type = ret;
    if (ang != 0) {
    }
    if (near == 5) {
    }
    if (dist == 3) {
    }
    switch (C1B40->unk154) {
        case 1:
        case 2:
        case 3:
            if (C1B40->unk4->unk64 == C1D98->unk26) {
                actorScriptStart(gCurrentActor, C1D98->unk28);
            }
            if (C1D90->unk26 != C1D9C->unkC) {
                actorSetTargetSpeed(gCurrentActor, C1D9C->unkC);
            }
        case 4:
        case 0x11:
        case 0x19:
            if ((near & 0xFF) && (C1B40->unk60 & 0x100) && (sp4D != 0) && (C1D90->unk1A & 0x400)) {
                if (C1D90->unk1A & 0x800) {
                    if (func_8072DE10(0x2710) != 0) {
                        actorSetBehaviourState(type, C1D9C->unkD, arg2);
                        return;
                    }
                }
                if (!(C1D90->unk1A & 0x800)) {
                    actorSetBehaviourState(type, C1D9C->unkD, arg2);
                    return;
                }
            }
            break;
        case 0x34:
            me = (C1Act *)C1B40->unk178;
            if (dist < *(s16 *)me) {
                actorSetBehaviourState(0x24, 0, arg1);
                return;
            }
        case 0x23:
            if ((ret ^ 0) == C1D90->unk36) { // FAKE: flips beq operand order (field left)
            } else if ((sp4D == 0) || ((s32)ret >= 7)) {
                func_8072C870(type, C1D9C->unkD, arg2);
                return;
            }
            if (near & 0xFF) {
                if (!(C1D90->unk1A & 0x400)) {
                    actorSetBehaviourState(0x35, (s16)(s32)(C1D9C->unkC * 0.667), arg1);
                    C1D90->unk20 = 0x3C;
                    C1D90->unkA = D_807FDC94->prevX;
                    C1D90->unkC = D_807FDC94->prevY;
                    C1D90->unkE = D_807FDC94->prevZ;
                    return;
                }
                if (C1D90->unk26 < C1D9C->unkD) {
                    actorSetBehaviourState(type, C1D9C->unkD, arg2);
                    return;
                }
            } else {
                actorSetBehaviourState(C1D9C->unk10, C1D9C->unkC, arg1);
                return;
            }
            break;
        case 0x33:
            if ((!(near & 0xFF) || !(C1D90->unk1A & 0x400)) && (C1B40->unk6A & 1)) {
                actorSetBehaviourState(C1D9C->unk10, C1D9C->unkC, arg1);
                return;
            }
            break;
        case 7:
            if ((SQ(gCurrentActor->z - C1D90->unkE) + SQ(gCurrentActor->x - C1D90->unkA)) < 400.0f) {
                if (!(C1D90->unk1A & 0x80)) {
                    actorSetDefaultState(C1D98->unk28);
                } else {
                    func_8072C870(7, C1D9C->unkD, arg2);
                }
            }
        case 0x10:
            if (type != C1D90->unk36) {
                func_8072C870(type, C1D9C->unkD, arg2);
            }
            if (near & 0xFF) {
                if (!(C1D90->unk1A & 0x400)) {
                    actorSetBehaviourState(C1D9C->unk10, C1D9C->unkC, arg1);
                    return;
                }
            } else {
                actorSetBehaviourState(C1D9C->unk10, C1D9C->unkC, arg1);
                return;
            }
            break;
        case 0x35:
            if (C1D90->unk1A & 0x400) {
                actorSetBehaviourState(type, C1D9C->unkD, arg2);
                return;
            }
            near = (C1D90->unk20-- == 0);
            if (near) {
                actorSetBehaviourState(C1D9C->unk10, C1D9C->unkC, arg1);
            }
            break;
    }
}

typedef struct D1Pair {
    /* 0x00 */ u8 a;
    /* 0x01 */ u8 b;
} D1Pair;

typedef struct D1Pt {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ s16 pad6[2];
} D1Pt; // size = 0xA

typedef struct D1DcA0View {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ D1Pt *unk14;
} D1DcA0View;

#define D1DCA0 ((D1DcA0View *)D_807FDCA0)

void patrolGetNextWaypointPos(s16 *arg0, s16 *arg1, s16 *arg2) {
    s32 temp;
    u8 idx;
    s32 v;
    u8 new_var;

    new_var = D1DC90G->unk25 & 0x7F;
    temp = new_var + 1;
    idx = (temp < D1DC9CG->unk11) ? (u8)temp : 0;
    v = ((D1Pair *)D1DC98G->unk20)[idx].a;
    *arg0 = D1DCA0->unk14[v].x;
    *arg1 = D1DCA0->unk14[v].y;
    *arg2 = D1DCA0->unk14[v].z;
}


void patrolGetNextWaypointPos(s16 *, s16 *, s16 *);

s32 patrolGetTargetAngle(void) {
    u8 idx;
    u8 key;
    s16 x;
    s16 y;
    s16 z;

    idx = D1DC90G->unk25 & 0x7F;
    key = ((D1Pair *)D1DC98G->unk20)[idx].a;
    patrolGetNextWaypointPos(&x, &y, &z);
    return mathAngleBetweenPoints2D(x, z, D1DCA0->unk14[key].x, D1DCA0->unk14[key].z);
}


typedef struct MiscBPatrolState {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0xA];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[4];
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 pad21[4];
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 pad26[6];
    /* 0x2C */ s16 unk2C;
} MiscBPatrolState;

typedef struct MiscBPatrolWaypoint {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ u8 pad6;
    /* 0x07 */ u8 r;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 pad9;
} MiscBPatrolWaypoint; // size = 0xA

typedef struct MiscBPatrolPathData {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ MiscBPatrolWaypoint *unk14;
} MiscBPatrolPathData;

typedef struct MiscBPatrolActorView {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[0x20];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ u8 pad8C[4];
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 pad94[0x52];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[6];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} MiscBPatrolActorView;

#define MISCB_PATROL_STATE ((MiscBPatrolState *)D_807FDC90)
#define MISCB_PATROL_PATH_DATA ((MiscBPatrolPathData *)D_807FDCA0)
#define MISCB_PATROL_ACTOR ((MiscBPatrolActorView *)gCurrentActor)
#define MISCB_PATROL_PAIRS ((D1Pair *)D1DC98G->unk20)

u8 patrolPathStep(u8 arg0, u8 arg1) {
    u8 dir;
    u8 pad;
    u8 key;
    u8 type;
    s16 x;
    s16 y;
    s16 z;
    u8 moved;
    u8 next;
    u8 idx;
    u8 nextKey;
    s32 v;

    idx = MISCB_PATROL_STATE->unk25;
    dir = idx;
    dir &= 0x80;
    idx &= 0x7F;
    key = MISCB_PATROL_PAIRS[idx].a;
    type = MISCB_PATROL_PAIRS[idx].b;
    x = MISCB_PATROL_PATH_DATA->unk14[key].x;
    y = MISCB_PATROL_PATH_DATA->unk14[key].y;
    z = MISCB_PATROL_PATH_DATA->unk14[key].z;
    moved = ((MISCB_PATROL_ACTOR->unk7C - x) * (MISCB_PATROL_ACTOR->unk7C - x)) + ((MISCB_PATROL_ACTOR->unk84 - z) * (MISCB_PATROL_ACTOR->unk84 - z)) <
            (f32)(MISCB_PATROL_PATH_DATA->unk14[key].r * MISCB_PATROL_PATH_DATA->unk14[key].r);
    if ((arg1 & 1) && MISCB_PATROL_ACTOR->unk7C == MISCB_PATROL_ACTOR->unk88 && MISCB_PATROL_ACTOR->unk84 == MISCB_PATROL_ACTOR->unk90) {
        if (D_807FDC90) {} // FAKE: two uopt blocks in idx's live range drop its priority below key's (key t2, idx t3)
        MISCB_PATROL_STATE->unk20++;
        if (MISCB_PATROL_STATE->unk20++ > 0x10) {
            moved = 1;
            MISCB_PATROL_STATE->unk20 = 0;
        }
    } else {
        MISCB_PATROL_STATE->unk20 = 0;
    }
    switch (arg0) {
        case 0x49:
            v = idx + 1;
            next = (v < D1DC9CG->unk11) ? (u8)v : 0;
            v = MISCB_PATROL_PAIRS[next].a;
            v = mathAngleBetweenPoints2D(MISCB_PATROL_PATH_DATA->unk14[v].x, MISCB_PATROL_PATH_DATA->unk14[v].z, x, z);
            MISCB_PATROL_ACTOR->unkEE = v;
            MISCB_PATROL_ACTOR->unkE6 = v;
        case 0x42:
        case 0x5B:
            MISCB_PATROL_STATE->unkA = x;
            MISCB_PATROL_STATE->unkC = y;
            MISCB_PATROL_STATE->unkE = z;
            break;
        case 2:
        case 0x26:
        case 0x60:
            if (moved) {
                if (type == 6) {
                    MISCB_PATROL_STATE->unk25 = MISCB_PATROL_PATH_DATA->unk14[key].unk8;
                } else if (idx + 1 < D1DC9CG->unk11) {
                    MISCB_PATROL_STATE->unk25 = idx + 1;
                } else {
                    MISCB_PATROL_STATE->unk25 = 0;
                }
            } else {
                MISCB_PATROL_STATE->unkA = x;
                MISCB_PATROL_STATE->unkC = y;
                MISCB_PATROL_STATE->unkE = z;
            }
            break;
        case 3:
            if (moved) {
                if (dir) {
                    if (idx > 0) {
                        idx--;
                    } else {
                        idx++;
                        dir = 0;
                    }
                } else if (idx < D1DC9CG->unk11 - 1) {
                    idx++;
                } else {
                    idx--;
                    dir = 0x80;
                }
                MISCB_PATROL_STATE->unk25 = dir | idx;
            } else {
                MISCB_PATROL_STATE->unkA = x;
                MISCB_PATROL_STATE->unkC = y;
                MISCB_PATROL_STATE->unkE = z;
            }
            break;
    }
    idx = MISCB_PATROL_STATE->unk25 & 0x7F;
    if (moved) {
        MISCB_PATROL_STATE->unk1A |= 4;
        switch (type) {
            case 1:
                nextKey = MISCB_PATROL_PAIRS[idx].a;
                v = patrolGetTargetAngle();
                MISCB_PATROL_ACTOR->unkEE = v;
                MISCB_PATROL_ACTOR->unkE6 = v;
                MISCB_PATROL_ACTOR->unk7C = MISCB_PATROL_PATH_DATA->unk14[nextKey].x;
                MISCB_PATROL_ACTOR->unk80 = MISCB_PATROL_PATH_DATA->unk14[nextKey].y;
                MISCB_PATROL_ACTOR->unk84 = MISCB_PATROL_PATH_DATA->unk14[nextKey].z;
                break;
            case 2:
                MISCB_PATROL_ACTOR->unk154 = 0x26;
                MISCB_PATROL_ACTOR->unk155 = 0;
                break;
            case 4:
                MISCB_PATROL_ACTOR->unk154 = 0x19;
                MISCB_PATROL_ACTOR->unk155 = 0;
                MISCB_PATROL_STATE->unk2C = MISCB_PATROL_PATH_DATA->unk14[key].unk8;
                break;
            case 5:
                actorSetTargetSpeed(gCurrentActor, MISCB_PATROL_PATH_DATA->unk14[key].unk8);
                break;
            case 7:
                MISCB_PATROL_ACTOR->unk154 = 0x3B;
                moved = 0;
                break;
            case 8:
                MISCB_PATROL_ACTOR->unk154 = 0x13;
                MISCB_PATROL_ACTOR->unk155 = 0;
                break;
            case 3:
                if (MISCB_PATROL_ACTOR->unk58 == 0xAF) {
                    MISCB_PATROL_ACTOR->unk154 = 0x37;
                    MISCB_PATROL_ACTOR->unk155 = 0;
                }
                D_80744508++;
                MISCB_PATROL_ACTOR->unk154 = 0x40;
                break;
        }
    } else {
        MISCB_PATROL_STATE->unk1A &= 0xFFFB;
    }
    return moved;
}


typedef struct D1ActorViewI {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ActorSub4 *unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[2];
    /* 0x05E */ u8 pad5E[0xC];
    /* 0x06A */ u8 pad6A[0x4E];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[0x2A];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x44];
    /* 0x134 */ s16 unk134;
    /* 0x136 */ u8 pad136[2];
    /* 0x138 */ u32 unk138;
} D1ActorViewI;

#define D1AI ((D1ActorViewI *)gCurrentActor)

void actorSetBehaviourState(u8, s16, s32);
void func_8002D7E8(s16);
void func_8072D9D4(void);

void func_8072D714(D1ActorViewI *arg0, s32 arg1) {
    f64 unused;
    f64 f;
    s32 mask;
    f64 raw;
    f32 rounded;
    f32 x;
    f32 cur;

    mask = 0xFFFF7FFF;
    if (arg0 != NULL) {
        raw = (D1AI->unk134 - 1) * -0.6;
        f = (2.0 < raw) ? 2.0 : raw;
        D1AI->unkEE = (arg0->unkEE + 0x800) & 0xFFF;
        if ((Actor *)arg0 == D_807FDC94) {
            if (mathAngleDistance(arg0->unkEE, arg0->unkE6) > 0x400) {
                D1AI->unkEE += 0x800;
            }
        }
        actorSetBehaviourState(0x37, 0, arg1);
        rounded = (f32)(f + 0.5);
        cur = arg0->unkB8;
        x = 66.0f * rounded;
        D1AI->unkB8 = -(((x < arg0->unkB8 ? arg0->unkB8 : x) < 150.0f) ? (x < arg0->unkB8 ? arg0->unkB8 : x) : 150.0f);
        if (arg0->unk4 != NULL) {
            D1AI->unkB8 = D1AI->unkB8 * (arg0->unk4->unk38 / 0.15);
        }
    } else {
        actorSetBehaviourState(0x37, 0, arg1);
        D1AI->unkB8 = -60.0f;
    }
    D1AI->unk138 &= mask;
    gCurrentActor->flags &= 0xFFFF7FFF;
    if (arg0 == NULL || (Actor *)arg0 == D_807FDC94 || arg0->unk58 == 0x2B) {
        func_8072D9D4();
    }
    D_80744508++;
    if (gCurrentMap == 0xBF) {
        func_8002D7E8(*(s16 *)((u8 *)gCurrentActor + 0x5A));
    }
}

void func_8072D99C(void) {
    gCurrentActor->unk144 = 1;
    gCurrentActor->state = 0x40;
    D_80744508++;
}

extern u8 D_8071FB34[];

void func_8072D9D4(void) {
    func_80714CC0(&D_8071FB34, 0.55f, D1A3->unk7C, D1A3->unk80 + (u32)D1A3->unk15E * 0.5, D1A3->unk84);
}

typedef struct E2ActorView {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 pad94[0x24];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x10];
    /* 0xCC */ u8 unkCC;
    /* 0xCD */ u8 padCD[0x17];
    /* 0xE4 */ s16 unkE4;
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ u8 padEA[4];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[0x38];
    /* 0x128 */ s16 unk128;
    /* 0x12A */ u8 pad12A[0x2A];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} E2ActorView;

#define E2A ((E2ActorView *)gCurrentActor)

extern Actor *D_807FBD6C;

void func_8072DA60(void) {
    func_80714CC0(&D_8071FB34, 0.55f, D_807FBD6C->x, D_807FBD6C->y, D_807FBD6C->z);
}

void func_80714998(s32);
extern u8 D_8071FF18;
extern void func_80717D4C(void);

void func_8072DAA4(void) {
    func_80714998(2);
    func_807149B8(1);
    func_8071498C(func_80717D4C);
    func_80714950(-0x28 - ((randomNonNegative() >> 15) % 15));
    func_80714CC0(&D_8071FF18, (f32)(((randomNonNegative() >> 15) % 1000) / 2000.0 + 0.5), gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
}

extern u8 gCurrentPlayerIndex;
s32 slotQueueGetValue(s32, u8);
void slotQueueAddValue(s32, u8, s16);
void slotQueueUpdate(s32, s32, s32);
void sfxAllocateChannel(s32, f32);
void actorSpawnNodeEntryScaled(s32, f32, f32, f32, s32, s32, s32, s32);

void func_8072DB68(s32 arg0) {
    u8 cnt;
    s16 i;

    if (slotQueueGetValue(0xB, gCurrentPlayerIndex) >= 4) {
        cnt = 3;
    } else {
        cnt = slotQueueGetValue(0xB, gCurrentPlayerIndex);
    }
    slotQueueAddValue(0xB, gCurrentPlayerIndex, -cnt);
    slotQueueUpdate(0xB, 0, 0);
    sfxAllocateChannel(0x41, 1.0f);
    for (i = 0; i < cnt; i++) {
        actorSpawnNodeEntryScaled(0x36, D_807FBB4C->x, D_807FBB4C->y, D_807FBB4C->z, D_807FBB4C->yaw + i * 200 - 200, 1, -1, 0);
    }
}

void func_8072DC7C(u8 arg0) {
    actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x32, 0.0f);
    E2A->unk128 -= arg0;
    if (E2A->unk128 < 0) {
        E2A->unk155++;
        E2A->unk128 = 0;
    }
}

f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);
s32 camIsCutsceneActive(void);

s32 func_8072DCF4(Actor *arg0, Actor *arg1, u16 arg2) {
    f32 deg = mathAngleBetweenPointsDeg((s32)arg1->x, (s32)arg1->z, (s32)arg0->x, (s32)arg0->z);
    s16 a = (f64)arg0->yaw / 4095.0 * 65536.0;
    f32 t = 360.0 - deg;
    s16 b = (f64)t / 360.0 * 65536.0;
    s32 diff;

    if (a < b) {
        diff = b - a;
    } else {
        diff = a - b;
    }
    if (diff < arg2) {
        if (camIsCutsceneActive() == 0) {
            return 1;
        }
    }
    return 0;
}

s32 func_8072DE10(u16 arg0) {
    return func_8072DCF4(gCurrentActor, D_807FDC94, arg0);
}

void actorSetTargetSpeed(Actor *, s32);

void actorSetDefaultState(s32 arg0) {
    gCurrentActor->state = D_807FDC9C->unk10;
    gCurrentActor->unk155[0] = 0;
    actorScriptStart(gCurrentActor, arg0);
    actorSetTargetSpeed(gCurrentActor, D_807FDC9C->unkC);
}

typedef struct E2Model {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
} E2Model;

typedef struct E2Sub4 {
    /* 0x00 */ E2Model *model;
} E2Sub4;

typedef struct E2D90View {
    /* 0x00 */ u8 pad0[0x16];
    /* 0x16 */ s16 unk16;
} E2D90View;


void func_8072DEA8(void *arg0, u8 arg1, Actor *arg2) {
    f32 b8;

    func_8072D9D4();
    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1CA, 0xFF, 0x7F, 0x14);
    if (arg2 != NULL) {
        if (arg2->collisionFlags & 4) {
            E2A->unkEE = (((E2ActorView *)arg2)->unkEE + 0x800) & 0xFFF;
        } else {
            E2A->unkEE = (arg2->yaw + 0x800) & 0xFFF;
        }
        actorSetBehaviourState(arg1, 0, (s32)arg0);
        b8 = arg2->speedXZ;
        E2A->unkB8 = -(((b8 > 60.0f ? b8 : 60.0f) < 150.0f) ? (b8 > 60.0f ? b8 : 60.0f) : 150.0f);
    } else {
        actorSetBehaviourState(arg1, 0, (s32)arg0);
    }
    if (arg2 == D_807FDC94) {
        ((E2D90View *)D_807FDC90)->unk16 = ((E2Sub4 *)D_807FDC94->unk4)->model->unk10;
        gCurrentActor->flags |= 0x20000000;
    }
}


void func_8072E02C(void) {
    E2A->unkE8 = mathAngleEaseToward(E2A->unkE8, 0, 5.0f);
    E2A->unkE4 = E2A->unkE4 + (-E2A->unkE4) * 0.1;
}

u8 func_8072E0A8(s32 arg0, s16 arg1) {
    u8 close;
    s16 ang;
    s16 diff;

    close = (((D_807FDC94->x - gCurrentActor->x) * (D_807FDC94->x - gCurrentActor->x) + (D_807FDC94->z - gCurrentActor->z) * (D_807FDC94->z - gCurrentActor->z)) < (f32)(arg0 * arg0));
    ang = mathAngleBetweenPoints2D(D_807FDC94->x, D_807FDC94->z, gCurrentActor->x, gCurrentActor->z);
    if (ang < gCurrentActor->yaw) {
        diff = gCurrentActor->yaw - ang;
    } else {
        diff = ang - gCurrentActor->yaw;
    }
    if (diff > 0x800) {
        diff = 0x1000 - diff;
    }
    return diff < arg1 && close && D_807FDC94->state != 0x42;
}

void func_8072E1A4(u8 arg0, Actor *arg1) {
    gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, mathAngleBetweenPoints2D(arg1->x, arg1->z, gCurrentActor->x, gCurrentActor->z), (u32)arg0);
}

u8 actorIsTargetWithinDistance(u16 arg0) {
    f32 dx = gCurrentActor->x - D_807FDC94->x;
    f32 dy = gCurrentActor->y - D_807FDC94->y;
    f32 dz = gCurrentActor->z - D_807FDC94->z;

    return (dx * dx + dy * dy + dz * dz) < (f32)(arg0 * arg0);
}

void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);

void actorGetNodePosOrPosition(Actor *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    if (((E2ActorView *)arg0)->unkCC != 0) {
        actorGetNodePos(arg0, ((E2ActorView *)arg0)->unkCC & 0xFFFFFFFFu, arg1, arg2, arg3);
    } else {
        *arg1 = arg0->x;
        *arg2 = arg0->y;
        *arg3 = arg0->z;
    }
}

#define E2_MAX(a, b) ((a) > (b) ? (a) : (b))
#define E2_MIN(a, b) ((a) < (b) ? (a) : (b))


void func_8072E320(f32 arg0) {
    f32 v;

    E2A->unkEE = E2A->unkE6;
    E2A->unkE6 = mathAngleEaseToward(E2A->unkE6, mathAngleBetweenPoints2D(E2A->unk7C, E2A->unk84, E2A->unk88, E2A->unk90), 3.3f);
    v = E2_MIN(E2_MAX(mathAngleSignedDistance(E2A->unkE6, E2A->unkEE) * arg0, -900.0f), 900.0f);
    E2A->unkE4 = (v - E2A->unkE4) * 0.1 + E2A->unkE4;
    E2A->unkE8 = mathAngleEaseToward(E2A->unkE8, mathCalculatePitchAngle(E2A->unk7C, E2A->unk80, E2A->unk84, E2A->unk88, E2A->unk8C, E2A->unk90, 0x1E) * 2048.0 / 3.1415927f, 3.3f);
}

u8 func_8072E54C(void) {
    return !(D_807FDC98->unk46 & 0x2000) && (((randomNonNegative() >> 15) % 1000) >= 0x3E4);
}
