#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#define PROTO_SKIP_behaviourUpdateContactAndState // PROTO: The number of arguments doesn't agree with the number in the
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/35000.h"
#include "proto/global/69E60.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/AA960.h"
#include "proto/global/BB300.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;

typedef struct BB300Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ActorSub4 *sub4;
    /* 0x008 */ u8 pad8[0x9C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x10];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[8];
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ f32 unkC8;
    /* 0x0CC */ u8 padCC[0x1A];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x1F];
    /* 0x174 */ void *unk174;
    /* 0x178 */ u8 *unk178;
} BB300Actor;

#define BB300A ((BB300Actor *)gCurrentActor)

extern Actor *gSpawnedActor;
extern s16 D_807502E0;
extern f32 D_807502E8;


void actorUpdatePulseIntensity(u8 active) {
    u8 *p = BB300A->unk178;
    s32 pad1;
    BoneRotation *q = BB300A->sub4->boneRotations;
    s32 pad2;
    f32 f;
    f32 x;
    u32 a;

    if (!active) {
        p[0] = -p[0] * 0.2 + (u32)p[0];
        p[1] = 0;
    } else {
        switch (p[1]) {
            case 0:
                p[1] = 1;
                break;
            case 1:
                p[0] += 0x32;
                if (p[0] >= 0xCE) {
                    p[0] = 0xFF;
                    p[1] = 2;
                }
                break;
            case 2:
                p[0] -= 0x50;
                a = p[0];
                if (p[0] >= 0x64 && (s32)a < 0xB4) {
                    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x16C, 0xFF, 0xA0, 6);
                    a = p[0];
                }
                if ((s32)a < 0x50) {
                    p[0] = 0;
                    p[1] = 0;
                }
                break;
        }
    }
    x = (u32)p[0] / 255.0;
    f = 8000.0f * x;
    q->rotX = (u32)-f;
    q[1].bone = 3;
    q++;
    q->weight = 0x7F;
    q->rotX = (u32)f;
    q->rotY = 0;
    q->rotZ = 0;
}

void behaviourUpdateContactAndState();

void func_806B6958(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourWorkState->unk35 = gBehaviourWorkState->unk35 * 2;
        gBehaviourWorkState->timer = 0xD2;
        gBehaviourWorkState->unk1F = (u32)gBehaviourWorkState->unk1F * 1.5;
        gBehaviourWorkState->unk1E = (u32)gBehaviourWorkState->unk1E * 1.5;
    }
    if (gBehaviourWorkState->timer != 0) {
        gBehaviourWorkState->timer = gBehaviourWorkState->timer - 1;
    }
    if (gBehaviourWorkState->timer % 30 == 0) {
        gBehaviourWorkState->unk1F = gBehaviourWorkState->unk1F - 1;
        gBehaviourWorkState->unk1E = gBehaviourWorkState->unk1E - 1;
    }
    if (gActorGlobalState.bossFightPhase == 4) {
        func_80724C2C(-0x96);
    }
    if (gBehaviourWorkState->timer == 0 || gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.unk15 != 0) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x3B2, 0xFF, 0x7F, 0x1E);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x3B7, 0xFF, 0x7F, 0x1E);
        effectSpawnRing();
        actorDespawn(gCurrentActor);
    }
    if (gCurrentActor->state == 0x23) {
        actorMoveWithinZone(0x23, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
    } else {
        behaviourUpdateContactAndState(0x237);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806B6C88(s16 speed, s16 angle) {
    if (actorSpawn(0xD3, 0x24) != 0) {
        gSpawnedActor->state = 0x23;
        actorScriptStart(gSpawnedActor, 0x237);
        gSpawnedActor->yaw = angle;
        gSpawnedActor->moveYaw = gSpawnedActor->yaw;
        actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, gCurrentActor->sub4->scaleY);
        gSpawnedActor->floorY = gCurrentActor->floorY;
        gSpawnedActor->accelY = D_807502E8;
        gSpawnedActor->terminalSpeedY = D_807502E0;
        gSpawnedActor->speedXZ = 0.0f;
        actorSetTargetSpeed(gCurrentActor, speed * 1.25);
        memcpy(gSpawnedActor->customState, gCurrentActor->customState, 0x3C);
    }
}

typedef struct BB300Sub178 {
    /* 0x0 */ s16 pad0;
    /* 0x2 */ s16 unk2;
} BB300Sub178;

// Second view of the current actor (gCurrentActor): same object as BB300Actor, but unk178 is typed as BB300Sub178.
typedef struct BB300ActorAlt {
    /* 0x000 */ u8 pad0[0xC0];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x22];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x22];
    /* 0x178 */ BB300Sub178 *unk178;
} BB300ActorAlt;

extern s32 gFrameCounter;
extern s32 gCurrentMap;

void func_806B6DB0(s32 aggroRange) {
    BB300Sub178 *p;
    s16 diff;
    u8 near;
    Actor *tgt;
    s32 sel;

    p = ((BB300ActorAlt *)gCurrentActor)->unk178;
    if (((BB300ActorAlt *)gCurrentActor)->unkEE < gCurrentActor->yaw) {
        diff = gCurrentActor->yaw - ((BB300ActorAlt *)gCurrentActor)->unkEE;
    } else {
        diff = ((BB300ActorAlt *)gCurrentActor)->unkEE - gCurrentActor->yaw;
    }
    near = ((gCurrentActor->x - gBehaviourTargetActor->x) * (gCurrentActor->x - gBehaviourTargetActor->x) + (gCurrentActor->z - gBehaviourTargetActor->z) * (gCurrentActor->z - gBehaviourTargetActor->z)) < 2500.0f;
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourAnimState->unk34 = 1.0f;
        func_80724CA4(2, 2);
        gCurrentActor->speedXZ = gBehaviourExtraState->targetSpeed;
    }
    if ((gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.unk15 != 0) && gCurrentActor->state != 0x37) {
        tgt = gActorGlobalState.targetActor;
        ((BB300ActorAlt *)gCurrentActor)->unkC0 = 200.0f;
        behaviourCalculateDamageForce(tgt, 0x236);
        if ((tgt != NULL && tgt->actorType == 0x29) || (gCurrentMap == 0x10 && gBehaviourExtraState->id < 0x11)) {
            gBehaviourWorkState->flags |= 1;
        }
    }
    sel = gCurrentActor->state;
    if (sel == 0x23 && gCurrentActor->speedXZ > 90.0f && diff >= 0x1F5 && diff < 0xE0C) {
        diff = ((BB300ActorAlt *)gCurrentActor)->unkEE - gCurrentActor->yaw;
        if (diff < 0 || diff >= 0x801) {
            p->unk2 = 0x8C;
        } else {
            p->unk2 = -0x8C;
        }
        actorSetBehaviourState(0x14, 0xA, 0x235);
        sel = gCurrentActor->state;
    }
    switch (sel) {
    case 0x14:
        switch (((BB300ActorAlt *)gCurrentActor)->unk155) {
        case 0:
            gBehaviourWorkState->timer = 0x1E;
            ((BB300ActorAlt *)gCurrentActor)->unk155 += 1;
            break;
        case 1:
            if (gBehaviourWorkState->timer != 0) {
                gCurrentActor->yaw += p->unk2;
                p->unk2 += -p->unk2 * 0.01;
                gBehaviourWorkState->timer -= 1;
                if (!(gFrameCounter & 3)) {
                    behaviourSpawnDropParticle();
                }
            } else {
                ((BB300ActorAlt *)gCurrentActor)->unk155 = 2;
            }
            break;
        case 2:
            sfxStopSlotSound(gCurrentActor, 0);
            actorSetBehaviourState(1, gBehaviourExtraState->targetSpeed, 0x232);
            ((BB300ActorAlt *)gCurrentActor)->unkEE = gCurrentActor->yaw;
            break;
        }
        func_80724E48(5);
        actorUpdatePulseIntensity(0);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x300, 0.0f);
        break;
    case 1:
        if ((randomNonNegative() >> 15) % 1000 >= 0x3E3) {
            gCurrentActor->state = 0x11;
            ((BB300ActorAlt *)gCurrentActor)->unk155 = 0;
        }
    case 0x10:
    case 0x23:
        func_8072881C(0, &gBehaviourWorkState->unk28);
        func_80724E48((u8)(gCurrentActor->state == 1 ? 2 : 0));
        actorUpdatePulseIntensity(near);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x400, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        func_8072881C(0, &gBehaviourWorkState->unk28);
        func_80724E48((u8)(gCurrentActor->state == 0x35 ? 2 : 3));
        actorUpdatePulseIntensity(0);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0x400, 0.0f);
        break;
    case 0x11:
        func_8072881C(0, &gBehaviourWorkState->unk28);
        actorUpdatePulseIntensity(0);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 2, 0.0f);
        switch (((BB300ActorAlt *)gCurrentActor)->unk155) {
        case 1:
            break;
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x234);
            ((BB300ActorAlt *)gCurrentActor)->unk155 += 1;
            break;
        case 2:
            actorSetBehaviourState(1, gBehaviourExtraState->targetSpeed, 0x232);
            break;
        }
        break;
    case 0x37:
        switch (((BB300ActorAlt *)gCurrentActor)->unk155) {
        case 0:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x20, 0.0f);
            break;
        case 1:
            sfxSpawnTableNodes(gCurrentActor);
            ((BB300ActorAlt *)gCurrentActor)->unkC0 = 100.0f;
            ((BB300ActorAlt *)gCurrentActor)->unk155 += 1;
        case 2:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x20, 0.0f);
            break;
        case 3:
            if (gBehaviourWorkState->flags & 1) {
                ((BB300ActorAlt *)gCurrentActor)->unk155 += 1;
            } else {
                func_806B6C88(gBehaviourExtraState->unkD, mathAngleBetweenPoints2D(gBehaviourTargetActor->x, gBehaviourTargetActor->z, gCurrentActor->x, gCurrentActor->z));
                ((BB300ActorAlt *)gCurrentActor)->unk155 = 5;
            }
            break;
        case 4:
            behaviourFadeOutWithinZone(5);
            break;
        case 5:
            gCurrentActor->state = 0x40;
            break;
        }
        break;
    case 0x16:
        gBehaviourWorkState->flags |= 1;
    default:
        behaviourUpdateContactAndState(0x232, sel);
        break;
    }
    sel = gCurrentActor->state;
    switch (sel) {
    case 0x37:
    case 0x40:
        break;
    case 2:
    case 3:
        patrolPathStep(gCurrentActor->state, 1);
    default:
        enemyAggroStateUpdate(aggroRange, 0x232, 0x233);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806B75F4(void) {
    behaviourFrameBegin();
    func_806B6DB0(0x2710);
}

void func_806B761C(void) {
    behaviourFrameBegin();
    if (gActorGlobalState.bossFightPhase == 4) {
        func_80724C2C(-0x64);
    }
    func_806B6DB0(0x2710);
}

void func_806B7660(void) {
    behaviourFrameBegin();
    if (gActorGlobalState.bossFightPhase == 4) {
        func_80724C2C(-0x64);
    }
    func_806B6DB0(0x2710);
}
