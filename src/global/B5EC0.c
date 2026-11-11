#include "common.h"
#include "actor.h"
#define PROTO_SKIP_actorMoveWithinZone // FAKE: callee prototype steer
#define PROTO_SKIP_func_80724E48 // PROTO: The number of arguments doesn't agree with the number in the
#define PROTO_SKIP_patrolPathStep // FAKE: callee prototype steer
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/89250.h"
#include "proto/global/8CA50.h"
#include "proto/global/AA960.h"
#include "proto/global/B5EC0.h"
#include "proto/global/CEAE0.h"

extern Actor *gCurrentActor;
extern s32 sEffectSparkConfig;

typedef struct B5EC0Sub4 {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} B5EC0Sub4;

// File-local view of the current actor (gCurrentActor) for fields Actor lacks or types differently.
typedef struct B5EC0Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ B5EC0Sub4 **unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x54];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x22];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x42];
    /* 0x132 */ s16 unk132;
    /* 0x134 */ s16 unk134;
    /* 0x136 */ u8 pad136[2];
    /* 0x138 */ u32 unk138;
    /* 0x13C */ u8 pad13C[0x18];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[9];
    /* 0x15F */ u8 unk15F;
} B5EC0Actor;

typedef struct B5EC0View94 {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ f32 unk84;
} B5EC0View94;

void actorSpawnGroundEffectAtNode(u8 nodeIndex) {
    f32 x;
    f32 y;
    f32 z;

    actorGetNodePos(gCurrentActor, nodeIndex, &x, &y, &z);
    effectSpawnScatterRandom(&sEffectSparkConfig, 0, 1.0f, 3, 5, 0x28, x, gCurrentActor->floorY, z);
    actorSpawnEffectChild(x, gCurrentActor->floorY, z, 0.05f, 0.04f, gCurrentActor, 0);
}

void func_806B1290(void) {
    if (gBehaviourWorkState->stepCount >= 0x65
        && (((gBehaviourWorkState->flags & 0x80) && (randomNonNegative() >> 15) % 1000 >= 0x3D5)
            || ((randomNonNegative() >> 15) % 1000 >= 0x3DF && (gCurrentActor->flags & 0x100)))) {
        ((B5EC0Actor *)gCurrentActor)->unk154 = 0x28;
        ((B5EC0Actor *)gCurrentActor)->unk155 = 0;
    }
}

void func_806B1348(void) {
    if (gBehaviourWorkState->stepCount >= 0x65 && gActorGlobalState.bossFightPhase == 2 && behaviourIsTargetWithinAngle(0x2710) != 0) {
        gCurrentActor->state = 0x27;
        gCurrentActor->unk155 = 0;
    }
}

extern s32 gCurrentMap;

void func_80724E48();
void actorMoveWithinZone(s32, f32, f32, s32, f32); // FAKE: callee prototype steer
void patrolPathStep(s32, s32); // FAKE: callee prototype steer

void func_806B13B4(u8 arg0) {
    s32 v;
    s32 sel;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        if (gCurrentMap == 0x43) {
            gBehaviourExtraState->unkD = 0x82;
            gBehaviourAnimState->flags |= 0x40;
        }
        behaviourSetAnimIds(0x205, 0x203, 0x204);
        func_80724CA4(2, 1);
    }
    sel = gCurrentActor->state;
    if (sel == 0x27) {
        ((B5EC0Actor *)gCurrentActor)->unk132 = 2;
        sel = gCurrentActor->state;
    } else if (sel != 0x32) {
        ((B5EC0Actor *)gCurrentActor)->unk132 = 1;
        sel = gCurrentActor->state;
    }
    if (sel != 0x32 || gActorGlobalState.unk15 != 0) {
        if ((gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.unk15 != 0) && sel != 0x37) {
            if (((B5EC0Actor *)gCurrentActor)->unk134 < -1) {
                behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x20C);
                ((B5EC0Actor *)gCurrentActor)->unkC0 = 250.0f;
            } else {
                behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x20B);
                ((B5EC0Actor *)gCurrentActor)->unkC0 = 200.0f;
            }
            gBehaviourWorkState->unk35 = 2;
            gCurrentActor->callbackMask &= 0xFFFF7FFF;
            sel = gCurrentActor->state;
        } else if (gActorGlobalState.bossFightPhase == 4) {
            behaviourSpawnExplosionAndSound(0x209, 0x31, gActorGlobalState.targetActor);
            sel = gCurrentActor->state;
        } else if (gActorGlobalState.bossFightPhase == 5) {
            behaviourSpawnExplosionAndSound(0x20A, 0x32, gActorGlobalState.targetActor);
            ((B5EC0Actor *)gCurrentActor)->unkC0 = 220.0f;
            gCurrentActor->interactionType = 8;
            sel = gCurrentActor->state;
        }
    }
    sel = gCurrentActor->state;
    switch (sel) {
    case 0x31:
        if (((B5EC0Actor *)gCurrentActor)->unk155 != 0 || (*((B5EC0Actor *)gCurrentActor)->unk4)->unk24 == 0.0f) {
            actorSetDefaultState(0x203);
        }
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4300, 0.0f);
        break;
    case 0x32:
        ((B5EC0Actor *)gCurrentActor)->unkE6 = mathAngleEaseToward(((B5EC0Actor *)gCurrentActor)->unkE6, ((B5EC0Actor *)gCurrentActor)->unkEE, 7.0f);
        switch (((B5EC0Actor *)gCurrentActor)->unk155) {
        case 0:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4300, 0.0f);
            break;
        case 1:
            ((B5EC0Actor *)gCurrentActor)->unk132 = 1;
            actorSetDefaultState(0x203);
            break;
        }
        break;
    case 0x28:
        switch (((B5EC0Actor *)gCurrentActor)->unk155) {
        case 0:
            actorScriptStart(gCurrentActor, 0x20D);
            ((B5EC0Actor *)gCurrentActor)->unk155 = 1;
            break;
        case 2:
            actorSpawnGroundEffectAtNode(1);
            actorSpawnGroundEffectAtNode(2);
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1D5, 0xFF, 0x7F, 1);
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x25A, 0xFF, 0x7F, 1);
            ((B5EC0Actor *)gCurrentActor)->unk155 = 3;
            break;
        case 4:
            actorSetDefaultState(0x203);
            break;
        }
        break;
    case 0x11:
        func_80724E48(5);
        switch (((B5EC0Actor *)gCurrentActor)->unk155) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x205);
            ((B5EC0Actor *)gCurrentActor)->unk155 += 1;
        case 1:
            actorMoveWithinZone(gCurrentActor->state, ((B5EC0View94 *)gBehaviourTargetActor)->unk7C, ((B5EC0View94 *)gBehaviourTargetActor)->unk84, 0x200, 0.0f);
            if (((B5EC0Actor *)gCurrentActor)->unkB8 < 1.0f) {
                ((B5EC0Actor *)gCurrentActor)->unk155 += 1;
            }
            break;
        case 2:
            behaviourUpdateShadowAlpha();
            if ((randomNonNegative() >> 15) % 1000 >= 0x3E4) {
                actorSetDefaultState(0x203);
            }
            break;
        }
        break;
    case 0x27:
        actorMoveWithinZone(gCurrentActor->state, ((B5EC0View94 *)gBehaviourTargetActor)->unk7C, ((B5EC0View94 *)gBehaviourTargetActor)->unk84, 0x200, 0.0f);
        switch (((B5EC0Actor *)gCurrentActor)->unk155) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            if ((randomNonNegative() >> 15) % 1000 >= 0x259) {
                actorScriptStart(gCurrentActor, 0x208);
                ((B5EC0Actor *)gCurrentActor)->unk155 = 5;
            } else {
                actorScriptStart(gCurrentActor, 0x206);
                ((B5EC0Actor *)gCurrentActor)->unk155 = 1;
            }
            break;
        case 1:
            if (gBehaviourWorkState->flags & 0x100) {
                actorClearNodeFlag(gCurrentActor, 2);
                actorClearNodeFlag(gCurrentActor, 3);
            }
            break;
        case 2:
            if (gBehaviourWorkState->flags & 0x100) {
                gBehaviourWorkState->flags &= 0xFEFF;
                actorScriptStart(gCurrentActor, 0x207);
                ((B5EC0Actor *)gCurrentActor)->unk155 = 3;
            } else {
                actorSetDefaultState(0x203);
            }
            break;
        case 3:
            if (gBehaviourWorkState->flags & 0x100) {
                gBehaviourWorkState->flags &= 0xFEFF;
                actorScriptStart(gCurrentActor, 0x208);
                ((B5EC0Actor *)gCurrentActor)->unk155 = 5;
            }
            break;
        case 4:
            actorSetDefaultState(0x203);
            break;
        case 5:
            ((B5EC0Actor *)gCurrentActor)->unk132 = 4;
            break;
        }
        break;
    case 1:
        if (behaviourCheckRandomAnimTrigger() != 0) {
            gCurrentActor->state = 0x11;
            ((B5EC0Actor *)gCurrentActor)->unk155 = 0;
        }
    case 0x10:
    case 0x23:
        if (camIsCutsceneActive() == 0) {
            func_806B1290();
            func_806B1348();
        }
        func_80724E48((u8)(gCurrentActor->state == 1 ? 2 : 0));
        actorMoveWithinZone(gCurrentActor->state, ((B5EC0View94 *)gBehaviourTargetActor)->unk7C, ((B5EC0View94 *)gBehaviourTargetActor)->unk84, 0, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        func_80724E48((u8)(sel == 0x35 ? 2 : 3), sel);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0, 0.0f);
        break;
    case 0x37:
        ((B5EC0Actor *)gCurrentActor)->unkE6 = mathAngleEaseToward(((B5EC0Actor *)gCurrentActor)->unkE6, ((B5EC0Actor *)gCurrentActor)->unkEE, 7.0f);
        switch (((B5EC0Actor *)gCurrentActor)->unk155) {
        case 0:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 1:
            if (arg0 != 0) {
                sfxSpawnTableNodes(gCurrentActor);
            }
            ((B5EC0Actor *)gCurrentActor)->unk155 += 1;
        case 2:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            behaviourFadeOutWithinZone(8);
            break;
        case 3:
            ((B5EC0Actor *)gCurrentActor)->unk154 = 0x40;
            break;
        }
        break;
    case 0x40:
        break;
    default:
        behaviourUpdateContactAndState(0x203);
        break;
    }
    sel = gCurrentActor->state;
    switch (sel) {
    case 0x31:
    case 0x37:
    case 0x40:
        break;
    case 2:
    case 3:
        patrolPathStep(gCurrentActor->state, 1);
    default:
        enemyAggroStateUpdate(0x6400, 0x203, 0x204);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorSetAnimStartFrame(u8 frame) {
    animSetLoopLimit(gCurrentActor, 0, 1);
    animSetFinished(gCurrentActor, 0, 1);
    animSetFrameAndSubframe(gCurrentActor, 0, frame, 0.0f);
}

extern u8 gCurrentWorldId;
extern s32 D_80750600[];


void func_806B1DD4(u8 mode) {
    u8 flag;
    s32 temp;

    if (!(gCurrentActor->flags & 0x10)) {
        flag = 0;
        temp = mapGetWorldIndex(gCurrentWorldId);
        if (temp != 9 && temp != 0xA) {
            temp = mapGetHubWorldIndex(gCurrentWorldId, 1);
            flag = flagGridSumRows(0x1D5, temp, temp, D_80750600[mode]) == 0;
        }
        actorSetAnimStartFrame(flag != 0 ? mode : 5);
        ((B5EC0Actor *)gCurrentActor)->unk15F = flag;
    }
    func_806B13B4(((B5EC0Actor *)gCurrentActor)->unk15F);
}

void b5ec0SetMode4(void) {
    func_806B1DD4(4);
}

void b5ec0SetMode2(void) {
    func_806B1DD4(2);
}

void b5ec0SetMode3(void) {
    func_806B1DD4(3);
}

void b5ec0SetMode0(void) {
    func_806B1DD4(0);
}

void b5ec0SetMode1(void) {
    func_806B1DD4(1);
}
