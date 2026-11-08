#include "common.h"
#include "actor.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern ActorGlobalState gActorGlobalState;
extern u8 gBossFightPhase;

typedef struct BB300Quad {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
} BB300Quad;

typedef struct BB300Sub4 {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ BB300Quad *unk1C;
} BB300Sub4;

typedef struct BB300Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ BB300Sub4 *unk4;
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

#define BB300A44 ((BB300Actor *)gSpawnedActor)
#define BB300A ((BB300Actor *)gCurrentActor)

extern Actor *gSpawnedActor;
extern s16 D_807502E0;
extern f32 D_807502E8;

s32 actorSpawn(s32, s32);
void actorScriptStart(void *, s32);
void actorCopyPoseAndScale(void *, void *, f32);
void actorSetTargetSpeed(void *, s32);
void *memcpy(void *, const void *, unsigned int);
void behaviourFrameBegin(void);
void func_80724C2C(s32);
void func_806B6DB0();
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);

void actorUpdatePulseIntensity(u8 active) {
    u8 *p = BB300A->unk178;
    s32 pad1;
    BB300Quad *q = BB300A->unk4->unk1C;
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
    q->unk2 = (u32)-f;
    q[1].unk1 = 3;
    q++;
    q->unk0 = 0x7F;
    q->unk2 = (u32)f;
    q->unk4 = 0;
    q->unk6 = 0;
}

typedef struct BB300View90 {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0xA];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[2];
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ u8 pad20[0xC];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 pad2E[7];
    /* 0x35 */ u8 unk35;
} BB300View90;

#define BB300S90 ((BB300View90 *)gBehaviourWorkState)

void effectSpawnRing();
void actorDespawn(Actor *);
void actorUpdateModelMatrix(void *, s32);
s32 actorMoveWithinZone(s32, f32, f32, s32, f32);
void func_8072B7CC();

void func_806B6958(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        BB300S90->unk35 = BB300S90->unk35 * 2;
        BB300S90->unk2C = 0xD2;
        BB300S90->unk1F = (u32)BB300S90->unk1F * 1.5;
        BB300S90->unk1E = (u32)BB300S90->unk1E * 1.5;
    }
    if (BB300S90->unk2C != 0) {
        BB300S90->unk2C = BB300S90->unk2C - 1;
    }
    if (BB300S90->unk2C % 30 == 0) {
        BB300S90->unk1F = BB300S90->unk1F - 1;
        BB300S90->unk1E = BB300S90->unk1E - 1;
    }
    if (gActorGlobalState.unk200 == 4) {
        func_80724C2C(-0x96);
    }
    if (BB300S90->unk2C == 0 || gActorGlobalState.unk200 == 9 || gActorGlobalState.unk15 != 0) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x3B2, 0xFF, 0x7F, 0x1E);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x3B7, 0xFF, 0x7F, 0x1E);
        effectSpawnRing();
        actorDespawn(gCurrentActor);
    }
    if (gCurrentActor->state == 0x23) {
        actorMoveWithinZone(0x23, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
    } else {
        func_8072B7CC(0x237);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806B6C88(s16 speed, s16 angle) {
    if (actorSpawn(0xD3, 0x24) != 0) {
        BB300A44->unk154 = 0x23;
        actorScriptStart(gSpawnedActor, 0x237);
        BB300A44->unkE6 = angle;
        BB300A44->unkEE = BB300A44->unkE6;
        actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, gCurrentActor->sub4->scaleY);
        BB300A44->unkA4 = BB300A->unkA4;
        BB300A44->unkC4 = D_807502E8;
        BB300A44->unkC8 = D_807502E0;
        BB300A44->unkB8 = 0.0f;
        actorSetTargetSpeed(gCurrentActor, speed * 1.25);
        memcpy(BB300A44->unk174, BB300A->unk174, 0x3C);
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

typedef struct BB300View98 {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ f32 unk34;
} BB300View98;

typedef struct BB300View9C {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 padE[5];
    /* 0x13 */ u8 unk13;
} BB300View9C;

extern s32 gFrameCounter;
extern s32 gCurrentMap;

s32 randomNonNegative(void);
void actorUpdatePulseIntensity(u8);
void func_80724CA4(s32, s32);
void func_80724E48();
void func_8072881C(s32, void *);
void actorSetBehaviourState();
void enemyAggroStateUpdate(s32, s32, s32);
void patrolPathStep(s32, s32);
void func_8072D714(s32, s32);
void func_8072DAA4();
void func_8072DC7C(s32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void sfxSpawnTableNodes(Actor *);
void sfxStopSlotSound(Actor *, s32);

void func_806B6DB0(s32 aggroRange) {
    BB300Sub178 *p;
    s16 diff;
    u8 near;
    s32 tgt;
    s32 sel;

    p = ((BB300ActorAlt *)gCurrentActor)->unk178;
    if (((BB300ActorAlt *)gCurrentActor)->unkEE < gCurrentActor->yaw) {
        diff = gCurrentActor->yaw - ((BB300ActorAlt *)gCurrentActor)->unkEE;
    } else {
        diff = ((BB300ActorAlt *)gCurrentActor)->unkEE - gCurrentActor->yaw;
    }
    near = ((gCurrentActor->x - gBehaviourTargetActor->x) * (gCurrentActor->x - gBehaviourTargetActor->x) + (gCurrentActor->z - gBehaviourTargetActor->z) * (gCurrentActor->z - gBehaviourTargetActor->z)) < 2500.0f;
    if (!(gCurrentActor->flags & 0x10)) {
        ((BB300View98 *)gBehaviourAnimState)->unk34 = 1.0f;
        func_80724CA4(2, 2);
        gCurrentActor->speedXZ = ((BB300View9C *)gBehaviourExtraState)->unkC;
    }
    if ((gActorGlobalState.unk200 == 9 || gActorGlobalState.unk15 != 0) && gCurrentActor->state != 0x37) {
        tgt = gActorGlobalState.unk1FC;
        ((BB300ActorAlt *)gCurrentActor)->unkC0 = 200.0f;
        func_8072D714(tgt, 0x236);
        if ((tgt != 0 && ((Actor *)tgt)->actorType == 0x29) || (gCurrentMap == 0x10 && ((BB300View9C *)gBehaviourExtraState)->unk13 < 0x11)) {
            BB300S90->unk1A |= 1;
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
            BB300S90->unk2C = 0x1E;
            ((BB300ActorAlt *)gCurrentActor)->unk155 += 1;
            break;
        case 1:
            if (BB300S90->unk2C != 0) {
                gCurrentActor->yaw += p->unk2;
                p->unk2 += -p->unk2 * 0.01;
                BB300S90->unk2C -= 1;
                if (!(gFrameCounter & 3)) {
                    func_8072DAA4();
                }
            } else {
                ((BB300ActorAlt *)gCurrentActor)->unk155 = 2;
            }
            break;
        case 2:
            sfxStopSlotSound(gCurrentActor, 0);
            actorSetBehaviourState(1, ((BB300View9C *)gBehaviourExtraState)->unkC, 0x232);
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
        func_8072881C(0, (u8 *)gBehaviourWorkState + 0x28);
        func_80724E48((u8)(gCurrentActor->state == 1 ? 2 : 0));
        actorUpdatePulseIntensity(near);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x400, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        func_8072881C(0, (u8 *)gBehaviourWorkState + 0x28);
        func_80724E48((u8)(gCurrentActor->state == 0x35 ? 2 : 3));
        actorUpdatePulseIntensity(0);
        actorMoveWithinZone(gCurrentActor->state, BB300S90->unkA, BB300S90->unkE, 0x400, 0.0f);
        break;
    case 0x11:
        func_8072881C(0, (u8 *)gBehaviourWorkState + 0x28);
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
            actorSetBehaviourState(1, ((BB300View9C *)gBehaviourExtraState)->unkC, 0x232);
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
            if (BB300S90->unk1A & 1) {
                ((BB300ActorAlt *)gCurrentActor)->unk155 += 1;
            } else {
                func_806B6C88(((BB300View9C *)gBehaviourExtraState)->unkD, mathAngleBetweenPoints2D(gBehaviourTargetActor->x, gBehaviourTargetActor->z, gCurrentActor->x, gCurrentActor->z));
                ((BB300ActorAlt *)gCurrentActor)->unk155 = 5;
            }
            break;
        case 4:
            func_8072DC7C(5);
            break;
        case 5:
            gCurrentActor->state = 0x40;
            break;
        }
        break;
    case 0x16:
        BB300S90->unk1A |= 1;
    default:
        func_8072B7CC(0x232, sel);
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
    if (gBossFightPhase == 4) {
        func_80724C2C(-0x64);
    }
    func_806B6DB0(0x2710);
}

void func_806B7660(void) {
    behaviourFrameBegin();
    if (gBossFightPhase == 4) {
        func_80724C2C(-0x64);
    }
    func_806B6DB0(0x2710);
}
