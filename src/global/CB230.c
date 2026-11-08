#include "common.h"
#include "actor.h"

extern Actor *gCurrentActor;
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

#define R1V ((R1C8CBActor *)gCurrentActor)

f32 sqrtf(f32);
void behaviourFrameBegin(void);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void actorSetTargetSpeed(Actor *, s32);
void func_8072A920(s32, s32, f32, f32, f32, s32, f32, f32, s32);
s32 func_8072881C(s32, void *);
void actorUpdateModelMatrix(Actor *, s32);

extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
extern u32 gFrameCounter;
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
        if (e->actorType == 0xF0 || e->actorType == 0xF9) {
            dx = e->x - D_807FBB4C->x;
            dy = e->y - D_807FBB4C->y;
            dz = e->z - D_807FBB4C->z;
            d = dx * dx + dy * dy + dz * dz;
            if (d < best) {
                best = d;
                found = e;
            }
        }
    }
    if (found != gCurrentActor) {
        gCurrentActor->state = 0x40;
        return;
    }
    switch (gCurrentActor->actorType) {
        case 0xF0:
            if (gCurrentActor->flags & 0x100) {
                actorGetNodePos(gCurrentActor, 1, A, &A[1], &A[2]);
            } else {
                A[0] = gCurrentActor->x;
                A[1] = gCurrentActor->y;
                A[2] = gCurrentActor->z;
            }
            dx = gCurrentActor->x - D_807FBB4C->x;
            dy = gCurrentActor->y - D_807FBB4C->y;
            dz = gCurrentActor->z - D_807FBB4C->z;
            if (dx * dx + dy * dy + dz * dz > 40000.0f && (gCurrentActor->flags & 0x100)) {
                actorGetNodePos(gCurrentActor, 2, B, &B[1], &B[2]);
            } else {
                B[0] = D_807FBB4C->x;
                B[1] = D_807FBB4C->y;
                B[2] = D_807FBB4C->z;
            }
            lightSetFovAngles(30.0f, 80.0f);
            break;
        case 0xF9:
            A[0] = gCurrentActor->x;
            A[1] = gCurrentActor->y;
            A[2] = gCurrentActor->z;
            B[0] = func_80612794(gCurrentActor->yaw) * 40.0f + gCurrentActor->x;
            B[1] = gCurrentActor->y - 20.0f;
            B[2] = func_80612790(gCurrentActor->yaw) * 40.0f + gCurrentActor->z;
            lightSetFovAngles(20.0f, 40.0f);
            break;
    }
    p->unk0 = func_80612794(gFrameCounter * 130) * 35.0 + 220.0;
    lightAdd(A[0], A[1], A[2], B[0], B[1], B[2], 0.0f, 1, ((u8 *)p)[1], ((u8 *)p)[1], ((u8 *)p)[1]);
}

void func_806C6884(s16 yOffset, s16 stopDist, u16 flags) {
    u16 dist;
    f32 dx;
    f32 dz;

    behaviourFrameBegin();
    dx = gCurrentActor->x - D_807FDC94->x;
    dz = gCurrentActor->z - D_807FDC94->z;
    dist = (u16)sqrtf(dx * dx + dz * dz);
    if (!(gCurrentActor->flags & 0x10)) {
        R1C8CBSub178 *p = R1V->unk178;
        gCurrentActor->unk64 |= 4;
        gCurrentActor->flags |= 0x800000;
        gCurrentActor->unk16A = 0xFF;
        gCurrentActor->unk16B = 0xFF;
        gCurrentActor->unk16C = 0xFF;
        p->unk2 = 0;
        p->unk0 = 0xFF;
        ((R1C8CBView98 *)D_807FDC98)->unk3C = 1.0f;
        if (gCurrentActor->actorType == 0xF0) {
            sfxPlayActorSound(gCurrentActor, 0x132, 0, 0, 0, 0xA0, 1.0f, 0);
        }
    }
    if (dist - stopDist < 0) {
        dist = 0;
    } else {
        dist = dist - stopDist;
    }
    actorSetTargetSpeed(gCurrentActor, (s32)((u32)dist * 2.0));
    func_8072A920(0x23, yOffset, D_807FDC94->x, D_807FDC94->y + yOffset * 3.0, D_807FDC94->z, 0x1E, 3.3f, 100.0f, flags | 0x2000);
    gCurrentActor->y += 0.5 * func_80612794(gFrameCounter * 40);
    actorUpdateNearestSpotlight();
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void func_806C6B50(void) {
    gCurrentActor->unkAC = 99999.0f;
    func_806C6884(0, 0xA, 0x44);
    func_8072881C(0, D_807FDC90->unk28);
}

void func_806C6BA0(void) {
    func_806C6884(0xA, 0x14, 0x240);
}

extern Actor *gSpawnedActor;
void hudSpawnCountdownTimer(s32, s32, u8);
void actorSetStateTwo(Actor *);
void func_805FF9AC(s32, s32, s32, s32);
void actorSetUniformScale(Actor *, f32);
void actorScriptStart(Actor *, s32);
void scriptSetActorRampTarget(Actor *, f32, f32);
void camRequestPathLength(void);
s32 camStartPath(Actor *, s32, s32);
void effectSpawnSparks(s32, s32);
s32 randomNonNegative(void);
void csModelStateSetFirstByte(s32, s32);
void actorDespawn(Actor *);
void patrolPathStep(s32, s32);
void func_8072DC7C(s32);

#define R1S ((R1C8CBState *)D_807FDC90)

void func_806C6BC8(void) {
    f32 ratio;
    f32 x;
    f32 y;
    f32 z;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        R1V->unk12A = 0x7D0;
        R1V->unk130 = 0xFF;
        R1V->unk131 = 0xFF;
        gCurrentActor->flags &= ~0x8000;
        R1V->unk154 = 0x27;
        R1V->unk155 = 0;
        D_807FDC90->scale = gCurrentActor->unk4->unk38;
        R1S->unk2E = 0x96;
        D_807FDC98->unk46 |= 0x60;
        hudSpawnCountdownTimer(0xDC, 0x2A, 0x64);
        actorSetStateTwo(gSpawnedActor);
    }
    if (R1S->unk1A & 0x80) {
        gCurrentActor->flags |= 0x400;
    } else {
        gCurrentActor->flags &= ~0x400;
    }
    func_8072881C(0, R1S->unk28);
    switch (R1V->unk154) {
        case 0:
            if (R1S->unk2C != 0) {
                ratio = (f32)R1S->unk2C / (f32)R1S->unk2E;
                actorGetNodePos(gCurrentActor, 2, &x, &y, &z);
                actorSetUniformScale(D_807FBB4C, ratio * 0.13 + 0.02);
                D_807FBB4C->x += (x - D_807FBB4C->x) * 0.05;
                D_807FBB4C->y += (y - D_807FBB4C->y) * 0.05;
                D_807FBB4C->z += (z - D_807FBB4C->z) * 0.05;
                R1S->unk2C--;
                if (R1S->unk2C == 0) {
                    func_805FF9AC(0x33, 0, 0, 1);
                }
            }
            break;
        case 0x27:
            if (R1S->unk2E != 0) {
                gCurrentActor->y += 2.0f;
                R1S->unk2E--;
                actorSetUniformScale(gCurrentActor, R1S->unk30 + (0.01 - R1S->unk30) * (R1S->unk2E / 150.0));
            } else {
                R1V->unk154 = 2;
                R1V->unk155 = 0;
            }
            break;
        case 2:
            if (D_807FBD70 == 4) {
                actorScriptStart(gCurrentActor, 0);
                scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
                R1V->unk154 = 0;
                R1V->unk155 = 0;
                camRequestPathLength();
                R1S->unk2C = camStartPath(gCurrentActor, 0x18, 1) - 0x1E;
                R1S->unk2E = R1S->unk2C;
                gCurrentActor->unk144 = 1;
            } else {
                switch (R1V->unk155) {
                    case 5:
                        actorSetTargetSpeed(gCurrentActor, D_807FDC9C->unkC);
                        R1V->unk155 = 0;
                        break;
                    case 3:
                        actorSetTargetSpeed(gCurrentActor, 0);
                        actorScriptStart(gCurrentActor, 0x2BB);
                        R1V->unk155 = 4;
                    case 4:
                    case 0:
                        effectSpawnSparks(3, 1);
                        if (R1V->unk155 == 0) {
                            if ((randomNonNegative() >> 15) % 1000 >= 0x3DF) {
                                R1V->unk155 = 3;
                            }
                        }
                        if (R1V->unk11C->unk154 == 5 || D_807FBB4C->actorType != 3) {
                            actorScriptStart(gCurrentActor, 0x2BA);
                            scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
                            csModelStateSetFirstByte(0x33, 0);
                            actorDespawn((Actor *)R1V->unk11C);
                            R1V->unk155 = 1;
                        }
                        func_8072A920(2, 0, D_807FDC90->targetX, D_807FDC90->targetY, D_807FDC90->targetZ, 0x46, 30.0f, 100.0f, 0x200);
                        patrolPathStep(2, 0);
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
    actorUpdateModelMatrix(gCurrentActor, 0);
}
