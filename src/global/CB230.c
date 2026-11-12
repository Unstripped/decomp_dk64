#include "common.h"
#include "actor.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/5E2F0.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/A7710.h"
#include "proto/global/CB230.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern u8 gBossFightPhase;

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

#define R1V ((R1C8CBActor *)gCurrentActor)

f32 sqrtf(f32);

extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;

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
            dx = e->x - gPrimaryPlayerActor->x;
            dy = e->y - gPrimaryPlayerActor->y;
            dz = e->z - gPrimaryPlayerActor->z;
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
            dx = gCurrentActor->x - gPrimaryPlayerActor->x;
            dy = gCurrentActor->y - gPrimaryPlayerActor->y;
            dz = gCurrentActor->z - gPrimaryPlayerActor->z;
            if (dx * dx + dy * dy + dz * dz > 40000.0f && (gCurrentActor->flags & 0x100)) {
                actorGetNodePos(gCurrentActor, 2, B, &B[1], &B[2]);
            } else {
                B[0] = gPrimaryPlayerActor->x;
                B[1] = gPrimaryPlayerActor->y;
                B[2] = gPrimaryPlayerActor->z;
            }
            lightSetFovAngles(30.0f, 80.0f);
            break;
        case 0xF9:
            A[0] = gCurrentActor->x;
            A[1] = gCurrentActor->y;
            A[2] = gCurrentActor->z;
            B[0] = mathSinF(gCurrentActor->yaw) * 40.0f + gCurrentActor->x;
            B[1] = gCurrentActor->y - 20.0f;
            B[2] = mathCosF(gCurrentActor->yaw) * 40.0f + gCurrentActor->z;
            lightSetFovAngles(20.0f, 40.0f);
            break;
    }
    p->unk0 = mathSinF(gFrameCounter * 130) * 35.0 + 220.0;
    lightAdd(A[0], A[1], A[2], B[0], B[1], B[2], 0.0f, 1, ((u8 *)p)[1], ((u8 *)p)[1], ((u8 *)p)[1]);
}

void func_806C6884(s16 yOffset, s16 stopDist, u16 flags) {
    u16 dist;
    f32 dx;
    f32 dz;

    behaviourFrameBegin();
    dx = gCurrentActor->x - gBehaviourTargetActor->x;
    dz = gCurrentActor->z - gBehaviourTargetActor->z;
    dist = (u16)sqrtf(dx * dx + dz * dz);
    if (!(gCurrentActor->flags & 0x10)) {
        R1C8CBSub178 *p = R1V->unk178;
        gCurrentActor->renderFlags |= 4;
        gCurrentActor->flags |= 0x800000;
        gCurrentActor->tintR = 0xFF;
        gCurrentActor->tintG = 0xFF;
        gCurrentActor->tintB = 0xFF;
        p->unk2 = 0;
        p->unk0 = 0xFF;
        gBehaviourAnimState->unk3C = 1.0f;
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
    actorPitchEaseTowardPoint(0x23, yOffset, gBehaviourTargetActor->x, gBehaviourTargetActor->y + yOffset * 3.0, gBehaviourTargetActor->z, 0x1E, 3.3f, 100.0f, flags | 0x2000);
    gCurrentActor->y += 0.5 * mathSinF(gFrameCounter * 40);
    actorUpdateNearestSpotlight();
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void func_806C6B50(void) {
    gCurrentActor->waterY = 99999.0f;
    func_806C6884(0, 0xA, 0x44);
    func_8072881C(0, &gBehaviourWorkState->unk28);
}

void func_806C6BA0(void) {
    func_806C6884(0xA, 0x14, 0x240);
}

extern Actor *gSpawnedActor;

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
        gBehaviourWorkState->scale = gCurrentActor->sub4->scaleY;
        gBehaviourWorkState->unk2E = 0x96;
        gBehaviourAnimState->flags |= 0x60;
        hudSpawnCountdownTimer(0xDC, 0x2A, 0x64);
        actorSetStateTwo(gSpawnedActor);
    }
    if (gBehaviourWorkState->flags & 0x80) {
        gCurrentActor->flags |= 0x400;
    } else {
        gCurrentActor->flags &= ~0x400;
    }
    func_8072881C(0, &gBehaviourWorkState->unk28);
    switch (R1V->unk154) {
        case 0:
            if (gBehaviourWorkState->timer != 0) {
                ratio = (f32)gBehaviourWorkState->timer / (f32)gBehaviourWorkState->unk2E;
                actorGetNodePos(gCurrentActor, 2, &x, &y, &z);
                actorSetUniformScale(gPrimaryPlayerActor, ratio * 0.13 + 0.02);
                gPrimaryPlayerActor->x += (x - gPrimaryPlayerActor->x) * 0.05;
                gPrimaryPlayerActor->y += (y - gPrimaryPlayerActor->y) * 0.05;
                gPrimaryPlayerActor->z += (z - gPrimaryPlayerActor->z) * 0.05;
                gBehaviourWorkState->timer--;
                if (gBehaviourWorkState->timer == 0) {
                    mapSaveSlotAndTransition(0x33, 0, 0, 1);
                }
            }
            break;
        case 0x27:
            if (gBehaviourWorkState->unk2E != 0) {
                gCurrentActor->y += 2.0f;
                gBehaviourWorkState->unk2E--;
                actorSetUniformScale(gCurrentActor, gBehaviourWorkState->scale + (0.01 - gBehaviourWorkState->scale) * (gBehaviourWorkState->unk2E / 150.0));
            } else {
                R1V->unk154 = 2;
                R1V->unk155 = 0;
            }
            break;
        case 2:
            if (gBossFightPhase == 4) {
                actorScriptStart(gCurrentActor, 0);
                scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
                R1V->unk154 = 0;
                R1V->unk155 = 0;
                camRequestPathLength();
                gBehaviourWorkState->timer = camStartPath(gCurrentActor, 0x18, 1) - 0x1E;
                gBehaviourWorkState->unk2E = gBehaviourWorkState->timer;
                gCurrentActor->unk144 = 1;
            } else {
                switch (R1V->unk155) {
                    case 5:
                        actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->targetSpeed);
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
                        if (R1V->unk11C->unk154 == 5 || gPrimaryPlayerActor->actorType != 3) {
                            actorScriptStart(gCurrentActor, 0x2BA);
                            scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
                            csModelStateSetFirstByte(0x33, 0);
                            actorDespawn((Actor *)R1V->unk11C);
                            R1V->unk155 = 1;
                        }
                        actorPitchEaseTowardPoint(2, 0, gBehaviourWorkState->targetX, gBehaviourWorkState->targetY, gBehaviourWorkState->targetZ, 0x46, 30.0f, 100.0f, 0x200);
                        patrolPathStep(2, 0);
                        break;
                    case 1:
                        behaviourFadeOutWithinZone(5);
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
