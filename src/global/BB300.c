#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#define PROTO_SKIP_behaviourUpdateContactAndState // ORIG: hides the one-parameter prototype; the target passes a1 = sel (move a1,a0 at 0xa28) that the owner never reads (12E800 homes only a0 at 0x1ce0), see the declaration below
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

// Second component (Actor+0x178) of the pulsing actor kinds: actorUpdatePulseIntensity ramps the light (A6280 PulseState names),
// func_806B6DB0 keeps a yaw sway there.
typedef struct PulseSwayState {
    /* 0x0 */ u8 intensity;
    /* 0x1 */ u8 phase;
    /* 0x2 */ s16 yawSway; // +-0x8C on a sharp turn, added to yaw and decayed by 1% per frame
} PulseSwayState;

typedef struct PulseSwayActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ PulseSwayState *pulse;
} PulseSwayActor;

extern Actor *gSpawnedActor;
extern s16 D_807502E0;
extern f32 D_807502E8;


void actorUpdatePulseIntensity(u8 active) {
    PulseSwayState *p = ((PulseSwayActor *)gCurrentActor)->pulse;
    s32 pad1;
    BoneRotation *q = gCurrentActor->sub4->boneRotations;
    s32 pad2;
    f32 f;
    f32 x;

    if (!active) {
        p->intensity += -p->intensity * 0.2;
        p->phase = 0;
    } else {
        switch (p->phase) {
            case 0:
                p->phase = 1;
                break;
            case 1:
                p->intensity += 0x32;
                if (p->intensity >= 0xCE) {
                    p->intensity = 0xFF;
                    p->phase = 2;
                }
                break;
            case 2:
                p->intensity -= 0x50;
                if (p->intensity >= 0x64 && p->intensity < 0xB4) {
                    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x16C, 0xFF, 0xA0, 6);
                }
                if (p->intensity < 0x50) {
                    p->intensity = 0;
                    p->phase = 0;
                }
                break;
        }
    }
    x = (u32)p->intensity / 255.0;
    f = 8000.0f * x;
    q->rotX = (u32)-f;
    q[1].bone = 3;
    q++;
    q->weight = 0x7F;
    q->rotX = (u32)f;
    q->rotY = 0;
    q->rotZ = 0;
}

void behaviourUpdateContactAndState(); // ORIG: target loads a1 = sel before the two-argument call (lbu a0,340(s0) at 0xa20, move a1,a0 at 0xa28, default branch at 0xa34 to jal at 0xf70 in func_806B6DB0) while the owner never reads a1 (12E800 0x1ccc homes only a0, sw a0,64(sp) at 0x1ce0): the original TU had no prototype in scope

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

extern s32 gCurrentMap;

void func_806B6DB0(s32 aggroRange) {
    PulseSwayState *p;
    s16 diff;
    u8 near;
    Actor *tgt;
    s32 sel;

    p = ((PulseSwayActor *)gCurrentActor)->pulse;
    if (gCurrentActor->moveYaw < gCurrentActor->yaw) {
        diff = gCurrentActor->yaw - gCurrentActor->moveYaw;
    } else {
        diff = gCurrentActor->moveYaw - gCurrentActor->yaw;
    }
    near = ((gCurrentActor->x - gBehaviourTargetActor->x) * (gCurrentActor->x - gBehaviourTargetActor->x) + (gCurrentActor->z - gBehaviourTargetActor->z) * (gCurrentActor->z - gBehaviourTargetActor->z)) < 2500.0f;
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourAnimState->unk34 = 1.0f;
        func_80724CA4(2, 2);
        gCurrentActor->speedXZ = gBehaviourExtraState->targetSpeed;
    }
    if ((gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.unk15 != 0) && gCurrentActor->state != 0x37) {
        tgt = gActorGlobalState.targetActor;
        gCurrentActor->speedY = 200.0f;
        behaviourCalculateDamageForce(tgt, 0x236);
        if ((tgt != NULL && tgt->actorType == 0x29) || (gCurrentMap == 0x10 && gBehaviourExtraState->id < 0x11)) {
            gBehaviourWorkState->flags |= 1;
        }
    }
    sel = gCurrentActor->state;
    if (sel == 0x23 && gCurrentActor->speedXZ > 90.0f && diff >= 0x1F5 && diff < 0xE0C) {
        diff = gCurrentActor->moveYaw - gCurrentActor->yaw;
        if (diff < 0 || diff >= 0x801) {
            p->yawSway = 0x8C;
        } else {
            p->yawSway = -0x8C;
        }
        actorSetBehaviourState(0x14, 0xA, 0x235);
        sel = gCurrentActor->state;
    }
    switch (sel) {
    case 0x14:
        switch (gCurrentActor->unk155) {
        case 0:
            gBehaviourWorkState->timer = 0x1E;
            gCurrentActor->unk155++;
            break;
        case 1:
            if (gBehaviourWorkState->timer != 0) {
                gCurrentActor->yaw += p->yawSway;
                p->yawSway += -p->yawSway * 0.01;
                gBehaviourWorkState->timer--;
                if (!(gFrameCounter & 3)) {
                    behaviourSpawnDropParticle();
                }
            } else {
                gCurrentActor->unk155 = 2;
            }
            break;
        case 2:
            sfxStopSlotSound(gCurrentActor, 0);
            actorSetBehaviourState(1, gBehaviourExtraState->targetSpeed, 0x232);
            gCurrentActor->moveYaw = gCurrentActor->yaw;
            break;
        }
        actorTrackBoneTowardTarget(5);
        actorUpdatePulseIntensity(0);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x300, 0.0f);
        break;
    case 1:
        if ((randomNonNegative() >> 15) % 1000 >= 0x3E3) {
            gCurrentActor->state = 0x11;
            gCurrentActor->unk155 = 0;
        }
    case 0x10:
    case 0x23:
        func_8072881C(0, &gBehaviourWorkState->unk28);
        actorTrackBoneTowardTarget((u8)(gCurrentActor->state == 1 ? 2 : 0));
        actorUpdatePulseIntensity(near);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x400, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        func_8072881C(0, &gBehaviourWorkState->unk28);
        actorTrackBoneTowardTarget((u8)(gCurrentActor->state == 0x35 ? 2 : 3));
        actorUpdatePulseIntensity(0);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0x400, 0.0f);
        break;
    case 0x11:
        func_8072881C(0, &gBehaviourWorkState->unk28);
        actorUpdatePulseIntensity(0);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 2, 0.0f);
        switch (gCurrentActor->unk155) {
        case 1:
            break;
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x234);
            gCurrentActor->unk155++;
            break;
        case 2:
            actorSetBehaviourState(1, gBehaviourExtraState->targetSpeed, 0x232);
            break;
        }
        break;
    case 0x37:
        switch (gCurrentActor->unk155) {
        case 0:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x20, 0.0f);
            break;
        case 1:
            sfxSpawnTableNodes(gCurrentActor);
            gCurrentActor->speedY = 100.0f;
            gCurrentActor->unk155++;
        /* fallthrough */
        case 2:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x20, 0.0f);
            break;
        case 3:
            if (gBehaviourWorkState->flags & 1) {
                gCurrentActor->unk155++;
            } else {
                func_806B6C88(gBehaviourExtraState->unkD, mathAngleBetweenPoints2D(gBehaviourTargetActor->x, gBehaviourTargetActor->z, gCurrentActor->x, gCurrentActor->z));
                gCurrentActor->unk155 = 5;
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
    /* fallthrough */
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
    /* fallthrough */
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
