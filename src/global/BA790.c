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

// Actor whose second component (0x178) points to an s16 countdown (explodingChaserUpdate).
typedef struct CountdownActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ s16 *countdown;
} CountdownActor;

extern u8 gGameMode;
extern s16 gSfxSourceVoice[];
extern s16 gSfxVoiceSoundId[];

extern EffectGridAsset D_80720630;


s32 chaserEnemyStep(s32 aggroRange, s32 unused) {
    u8 ret;
    s16 yawDiff;
    s32 step;
    f32 lightRadius;
    s32 x; // ORIG: the case 0x37 fade step and light step spill to this one home (sw v0/zero,64(sp) at 0x494/0x49c/0x4a0, sw t7/v1,64(sp) at 0x618/0x61c, reloaded at 0x4b8/0x620); a separate fade local moves the frame 0x50 -> 0x48
    u32 alpha;
    s16 angle;
    s32 size;

    ret = 0;
    if (gCurrentActor->moveYaw < gCurrentActor->yaw) {
        yawDiff = gCurrentActor->yaw - gCurrentActor->moveYaw;
    } else {
        yawDiff = gCurrentActor->moveYaw - gCurrentActor->yaw;
    }
    if (gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.damaged != 0) {
        if (gCurrentActor->state != 0x37 && gCurrentActor->state != 0x38) {
            switch (gCurrentActor->actorType) {
            case 0xAF:
                if (gGameMode == 1) {
                    if (gCurrentActor->flags & 4) {
                        gCurrentActor->state = 0x38;
                        gCurrentActor->subState = 0;
                    } else {
                        behaviourSetFloorAndState40();
                    }
                } else {
                    gCurrentActor->state = 0x37;
                    gCurrentActor->subState = 0;
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
        effectSpawnSpeedDustAtBone(0.5f, 0x32, (gFrameCounter & 1) + 2);
        gCurrentActor->speedXZ /= 2;
        if (gCurrentActor->soundSlots[0] == -1) {
            sfxPlayActorSound(gCurrentActor, 0x122, 0, 0, 0, 0xFF, 1.0f, 0);
        }
    } else {
        if (gCurrentActor->soundSlots[0] != -1 && gSfxVoiceSoundId[gSfxSourceVoice[gCurrentActor->soundSlots[0]]] == 0x122) {
            sfxStopSlotSound(gCurrentActor, 0);
        }
    }
    switch (gCurrentActor->state) {
    case 0x33:
        if (gActorGlobalState.bossFightPhase == 2) {
            gCurrentActor->speedY = 150.0f;
            gCurrentActor->moveYaw = gActorGlobalState.targetActor->moveYaw;
        }
        if (gCurrentActor->subState) {
            x = 0;
        } else {
            x = 2;
        }
        actorMoveWithinZone(0x33, gBehaviourTargetActor->x, gBehaviourTargetActor->z, x, 6.0f); // FAKE: x reused as the move flags; only the s0 colour shows it (li s0,2 / move s0,zero at 0x298/0x2ac, no store to the home 64(sp)); a moveFlags local (s32 or u16, top or block scope) or the inline ternary gives .text 2912 (target 2928)
        if (gCurrentActor->actorType == 0xB6) {
            enemyAggroStateUpdate(aggroRange, 0x24E, 0x24D);
        }
        break;
    case 0:
    case 4:
        sfxStopSlotSound(gCurrentActor, 0);
        if (gCurrentActor->subState == 0) {
            actorUpdateFloorContactAndTilt(gCurrentActor, 6.0f);
            gCurrentActor->subState = 1;
        }
        if (gGameMode != 1) {
            if (gCurrentActor->actorType == 0xB6) {
                x = 0x24D;
            } else {
                x = 0x24C;
            }
            enemyAggroStateUpdate(aggroRange, 0x24E, x); // FAKE: x reused as the chase script id; only the s0 colour shows it (li s0,588/589 at 0x360/0x370, no store to the home 64(sp)); a chaseScriptId local (top or block scope) or the inline ternary gives .text 2912 (target 2928)
        }
        if (gCurrentActor->state == 0x33) {
            ret = 1;
            gCurrentActor->speedXZ = gBehaviourExtraState->chaseSpeed;
            angle = mathAngleBetweenPoints2D(gBehaviourTargetActor->x, gBehaviourTargetActor->z, gCurrentActor->x, gCurrentActor->z);
            gCurrentActor->yaw = angle;
            gCurrentActor->moveYaw = angle;
        }
        break;
    case 0x38:
        switch (gCurrentActor->subState) {
        case 1:
            break;
        case 0:
            actorScriptStart(gCurrentActor, 0x24B);
            gCurrentActor->subState++;
            break;
        case 2:
            tagBarrelSpawnActorSmokePuffs(0, 1);
            behaviourSetFloorAndState40();
            break;
        }
        break;
    case 0x37:
        step = gCurrentActor->subState;
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
            alpha = (u32)((1.0 - x * 0.03125) * 230.0) & 0xFF;
            if (alpha != 0) {
                billboardSubmit(gCurrentActor, 0x3C3, 0x40, 0x40, size, size, 1, 0x96, alpha, 0, 1.0f);
            } else {
                behaviourSetFloorAndState40();
            }
            step = gCurrentActor->subState;
            if (step >= 0x17) {
                x = 0x16;
            } else {
                x = step;
            }
            lightRadius = (22.0 - x) / 20.0 * 200.0;
            if (lightRadius > 130.0) {
                lightRadius = 200.0f;
            }
            lightAdd(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f, 0.0f, 0.0f, lightRadius, 0, 0xFF, 0xFF, 0xFF);
            step = gCurrentActor->subState;
        }
        if (step < 4) {
            actorMoveWithinZone(0x33, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x20, 6.0f);
            step = gCurrentActor->subState;
        }
        switch (step) {
        case 0:
            actorScriptStart(gCurrentActor, 0x24B);
            gCurrentActor->subState++;
            break;
        case 2:
            sfxSpawnTableNodes(gCurrentActor);
            tagBarrelSpawnActorSmokePuffs(1, 1);
            actorSetNodeFlag(gCurrentActor, 3);
            camStartShakeFromPoint(gCamActor, 5, 0x14, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 200.0f, 400.0f);
            gCurrentActor->subState++;
            break;
        case 4:
            sfxStopSlotSound(gCurrentActor, 0);
            gCurrentActor->moveYaw = gCurrentActor->yaw;
            sfxPlayActorSound(gCurrentActor, 0x136, 0, 0, 0, 0xFF, 1.0f, 0);
            effectSetDuration(5);
            effectSetDepth(1);
            effectSetColor(0xFF, 0xFF, 0xFF, 1);
            effectSetFrameDelay(1);
            effectSetScale(-0.4f, 0.4f);
            effectSetCallback(effectSparkSpawnUpdate);
            effectCreateAtPosition(&D_80720630, 0.3f, gCurrentActor->x, gCurrentActor->floorY + 7.0f, gCurrentActor->z);
            gCurrentActor->flags &= ~4;
            gCurrentActor->subState++;
            break;
        case 1:
        case 3:
            break;
        case 5:
            gCurrentActor->callbackMask = 0;
            actorClearNodeFlag(gCurrentActor, 3);
            /* fallthrough */
        default:
            gCurrentActor->subState++;
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


void chaserEnemyUpdate(void) {
    behaviourFrameBegin();
    chaserEnemyStep(0x2710, 0);
}

extern u8 gGameMode;
extern s32 gCurrentMap;


void explodingChaserUpdate(void) {
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
                gCurrentActor->collisionMode = 0x24;
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
    if (chaserEnemyStep(aggroRange, *countdown) != 0) {
        *countdown = -*countdown;
    }
}
