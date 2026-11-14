#include "common.h"
#include "actor.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/12E800.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/5E2F0.h"
#include "proto/global/61AA0.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/80150.h"
#include "proto/global/89250.h"
#include "proto/global/8F4B0.h"
#include "proto/global/AA960.h"
#include "proto/global/BA790.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;

// Actor whose second component (0x178) points to an s16 countdown (func_806B640C).
typedef struct CountdownActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ s16 *countdown;
} CountdownActor;

extern u8 gGameMode;
extern s16 D_80770628[];
extern s16 D_80770710[];
extern Actor *gCamActor;
extern u8 D_80720630;


s32 func_806B5A90(s32 aggroRange, s32 unused) {
    u8 ret;
    s16 yawDiff;
    s32 step;
    f32 lightRadius;
    s32 x;
    u32 alpha;
    s16 q;
    s32 size;

    ret = 0;
    if (gCurrentActor->moveYaw < gCurrentActor->yaw) {
        yawDiff = gCurrentActor->yaw - gCurrentActor->moveYaw;
    } else {
        yawDiff = gCurrentActor->moveYaw - gCurrentActor->yaw;
    }
    if (gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.unk15 != 0) {
        if (gCurrentActor->state != 0x37 && gCurrentActor->state != 0x38) {
            switch (gCurrentActor->actorType) {
            case 0xAF:
                if (gGameMode == 1) {
                    if (gCurrentActor->flags & 4) {
                        gCurrentActor->state = 0x38;
                        gCurrentActor->unk155 = 0;
                    } else {
                        behaviourSetFloorAndState40();
                    }
                } else {
                    gCurrentActor->state = 0x37;
                    gCurrentActor->unk155 = 0;
                }
                break;
            case 0xB6:
                sfxSpawnTableNodes(gCurrentActor);
                tagBarrelDespawnEffects();
                behaviourSetFloorAndState40();
                break;
            }
        }
    }
    if (yawDiff >= 0x1F5 && yawDiff < 0xE0C) {
        func_80685210(0.5f, 0x32, (gFrameCounter & 1) + 2);
        gCurrentActor->speedXZ /= 2;
        if (gCurrentActor->soundSlots[0] == -1) {
            sfxPlayActorSound(gCurrentActor, 0x122, 0, 0, 0, 0xFF, 1.0f, 0);
        }
    } else {
        if (gCurrentActor->soundSlots[0] != -1 && D_80770710[D_80770628[gCurrentActor->soundSlots[0]]] == 0x122) {
            sfxStopSlotSound(gCurrentActor, 0);
        }
    }
    switch (gCurrentActor->state) {
    case 0x33:
        if (gActorGlobalState.bossFightPhase == 2) {
            gCurrentActor->speedY = 150.0f;
            gCurrentActor->moveYaw = gActorGlobalState.targetActor->moveYaw;
        }
        if (gCurrentActor->unk155) {
            x = 0;
        } else {
            x = 2;
        }
        actorMoveWithinZone(0x33, gBehaviourTargetActor->x, gBehaviourTargetActor->z, x, 6.0f);
        if (gCurrentActor->actorType == 0xB6) {
            enemyAggroStateUpdate(aggroRange, 0x24E, 0x24D);
        }
        break;
    case 0:
    case 4:
        sfxStopSlotSound(gCurrentActor, 0);
        if (gCurrentActor->unk155 == 0) {
            actorUpdateFloorContactAndTilt(gCurrentActor, 6.0f);
            gCurrentActor->unk155 = 1;
        }
        if (gGameMode != 1) {
            if (gCurrentActor->actorType == 0xB6) {
                x = 0x24D;
            } else {
                x = 0x24C;
            }
            enemyAggroStateUpdate(aggroRange, 0x24E, x);
        }
        if (gCurrentActor->state == 0x33) {
            ret = 1;
            gCurrentActor->speedXZ = gBehaviourExtraState->unkD;
            q = mathAngleBetweenPoints2D(gBehaviourTargetActor->x, gBehaviourTargetActor->z, gCurrentActor->x, gCurrentActor->z);
            gCurrentActor->yaw = q;
            gCurrentActor->moveYaw = q;
        }
        break;
    case 0x38:
        switch (gCurrentActor->unk155) {
        case 1:
            break;
        case 0:
            actorScriptStart(gCurrentActor, 0x24B);
            gCurrentActor->unk155++;
            break;
        case 2:
            tagBarrelSpawnActorSmokePuffs(0, 1);
            behaviourSetFloorAndState40();
            break;
        }
        break;
    case 0x37:
        step = gCurrentActor->unk155;
        if (step >= 2) {
            if (step - 0x82 < 0) {
                x = 0;
            } else {
                x = step - 0x82;
            }
            if (step * 6 >= 0x23) {
                size = 0x22;
            } else {
                size = (step * 6) & 0xFF;
            }
            q = size;
            alpha = (u32)((1.0 - (f64)x * 0.03125) * 230.0) & 0xFF;
            if (alpha != 0) {
                billboardSubmit(gCurrentActor, 0x3C3, 0x40, 0x40, q, q, 1, 0x96, alpha, 0, 1.0f);
            } else {
                behaviourSetFloorAndState40();
            }
            step = gCurrentActor->unk155;
            if (step >= 0x17) {
                x = 0x16;
            } else {
                x = step;
            }
            lightRadius = ((22.0 - (f64)x) / 20.0) * 200.0;
            if (lightRadius > 130.0) {
                lightRadius = 200.0f;
            }
            lightAdd(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f, 0.0f, 0.0f, lightRadius, 0, 0xFF, 0xFF, 0xFF);
            step = gCurrentActor->unk155;
        }
        if (step < 4) {
            actorMoveWithinZone(0x33, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x20, 6.0f);
            step = gCurrentActor->unk155;
        }
        switch (step) {
        case 0:
            actorScriptStart(gCurrentActor, 0x24B);
            gCurrentActor->unk155++;
            break;
        case 2:
            sfxSpawnTableNodes(gCurrentActor);
            tagBarrelSpawnActorSmokePuffs(1, 1);
            actorSetNodeFlag(gCurrentActor, 3);
            camStartShakeFromPoint(gCamActor, 5, 0x14, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 200.0f, 400.0f);
            gCurrentActor->unk155++;
            break;
        case 4:
            sfxStopSlotSound(gCurrentActor, 0);
            gCurrentActor->moveYaw = gCurrentActor->yaw;
            sfxPlayActorSound(gCurrentActor, 0x136, 0, 0, 0, 0xFF, 1.0f, 0);
            effectSetDuration(5);
            effectSetDepth(1);
            effectSetColor(0xFF, 0xFF, 0xFF, 1);
            effectSetMode(1);
            effectSetScale(-0.4f, 0.4f);
            effectSetCallback(effectSparkSpawnUpdate);
            effectCreateAtPosition(&D_80720630, 0.3f, gCurrentActor->x, gCurrentActor->floorY + 7.0f, gCurrentActor->z);
            gCurrentActor->flags &= ~4;
            gCurrentActor->unk155++;
            break;
        case 1:
        case 3:
            break;
        case 5:
            gCurrentActor->callbackMask = 0;
            actorClearNodeFlag(gCurrentActor, 3);
        /* fallthrough */
    default:
            gCurrentActor->unk155++;
            break;
        }
        break;
    default:
        behaviourUpdateContactAndState(0x24E);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
    return ret;
}


void func_806B63E0(void) {
    behaviourFrameBegin();
    func_806B5A90(0x2710, 0);
}

extern u8 gGameMode;
extern s32 gCurrentMap;


void func_806B640C(void) {
    s16 *countdown = ((CountdownActor *)gCurrentActor)->countdown;
    s16 i;
    s32 state;
    s32 aggroRange;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        actorClearNodeFlag(gCurrentActor, 3);
        *countdown = -gBehaviourExtraState->unkAWide;
    }
    if (gGameMode == 1) {
        for (i = 0; i < gActorGlobalState.volumeTriggerQueueCount; i++) {
            if (gActorGlobalState.volumeTriggerQueueOp[i] == 3) {
                gCurrentActor->unk144 = 0x24;
                actorScriptStart(gCurrentActor, 0x24F);
            }
        }
        lightUpdateFromActorLighting(&gCurrentActor->tintR, &gCurrentActor->tintG, &gCurrentActor->tintB);
    }
    state = gCurrentActor->state;
    if (state != 0x37 && state != 0x38) {
        if (*countdown > 0) {
            (*countdown)--;
            if (*countdown == 0xA) {
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x150, 0xFF, 0x7F, 0x1E, 0x32, 0.3f, 0);
            }
            if (*countdown == 0) {
                gActorGlobalState.bossFightPhase = 9;
            }
        }
    }
    if (gCurrentMap == 6) {
        aggroRange = 0x9C40;
    } else {
        aggroRange = 0x2710;
    }
    if (func_806B5A90(aggroRange, *countdown) != 0) {
        *countdown = -*countdown;
    }
}
