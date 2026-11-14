#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/104F0.h"
#include "proto/global/112080.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/5E2F0.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/90D80.h"
#include "proto/global/A2F10.h"
#include "proto/global/ACDC0.h"
#include "proto/global/B7490.h"
#include "proto/global/C4620.h"
#include "proto/global/C8C10.h"
#include "proto/global/EFDC0.h"
#include "proto/global/FCCD0.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern PlayerState *gActivePlayerState;

// Actor types with more than one component keep per-type pointers from 0x178 on (see Actor in actor.h).
typedef struct ComponentActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ s16 *secondComponent;
    /* 0x17C */ u8 pad17C[4];
    /* 0x180 */ s16 *fourthComponent;
} ComponentActor;

#define COMPONENT_ACTOR ((ComponentActor *)gCurrentActor)

extern PlayerStruct *gPlayerSlots;
extern Actor *gCamActor;
extern s32 gCurrentMap;


void func_806C3F10(u8 startActionId, u8 exitActionId, u8 camPathId) {
    s16 *durationPtr = COMPONENT_ACTOR->secondComponent;

    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourAnimState->flags |= 0x20;
        if (camPathId) {
            camStartPath(gCurrentActor, camPathId, 1);
        } else {
            camSetTargetCutsceneUnscaled(gCamActor, gCurrentActor, 4, 0x800, 0x19, 0, 0xA, 0x14, 0xC, 0, 0.1f);
        }
        gBehaviourExtraState->actorState = 0x27;
        gCurrentActor->state = 0x27;
        gCurrentActor->unk155 = 0;
    }
    {
        s32 d = gBehaviourWorkState->targetY - gBehaviourExtraState->y;

        if (d < 0) {
            *durationPtr = 0;
        } else {
            *durationPtr = d;
        }
    }
    switch (gCurrentActor->state) {
        case 0x27:
            if ((gBehaviourWorkState->flags & 4) && (gBehaviourWorkState->unk25 & 0x7F) == startActionId) {
                if (gPlayerSlots->unk2C0 == 0) {
                    resQueueAttachActor(gCurrentActor, 0x10, 1);
                    gCurrentActor->state = 0x29;
                    gCurrentActor->unk155 = 0;
                    gBehaviourExtraState->actorState = 0x29;
                    gActivePlayerState->stateFlags |= 0x10000;
                    playerStateQueueCallback(0x54, 0, 0);
                    gBehaviourWorkState->flags |= 0x8000;
                } else {
                    resQueueAttachActor(gCurrentActor, 0x10, 0);
                    gCurrentActor->state = 0x28;
                    gCurrentActor->unk155 = 0;
                    gBehaviourExtraState->actorState = 0x28;
                    if (!camPathId) {
                        camSetTarget(gCamActor, gCurrentActor, 4, 0x800, 0x19, 0, 0xA, 0x14, 0xC, 0x78, 0.1f);
                    }
                }
            }
        case 0x28:
            actorAirPatrolStep(2, 0x23D, 0x23E);
            break;
        case 0x26:
        case 0x29:
            if (gBehaviourWorkState->flags & 0x8000) {
                if ((gBehaviourWorkState->flags & 4) && (gBehaviourWorkState->unk25 & 0x7F) == exitActionId) {
                    if (!camPathId) {
                        camSetFollowMode(gCamActor);
                    }
                    camStartPath(gPrimaryPlayerActor, 3, 5);
                    gCurrentActor->state = 0x28;
                    gCurrentActor->unk155 = 0;
                    gBehaviourExtraState->actorState = 0x28;
                    gActivePlayerState->stateFlags &= 0xFFFEFFFF;
                    gBehaviourWorkState->flags &= 0x7FFF;
                } else {
                    if (!camPathId) {
                        camSetTarget(gCamActor, gPrimaryPlayerActor, 4, (s16)(gFrameCounter * 20), 0x1E, 0, 0xA, 0x1E, 0xC, 0, 0.2f);
                    }
                    gPrimaryPlayerActor->yaw = gCurrentActor->yaw;
                    gPrimaryPlayerActor->x = gCurrentActor->x;
                    gPrimaryPlayerActor->y = gCurrentActor->y - 2.0f;
                    gPrimaryPlayerActor->z = gCurrentActor->z;
                    gPrimaryPlayerActor->contactFlags &= 0xFFFE;
                    gPrimaryPlayerActor->attachMode = 0;
                }
            }
            actorAirPatrolStep((gCurrentActor->state == 0x26) ? 0x26 : 2, 0x23D, 0x23E);
            break;
        case 0:
            break;
    }
}


void func_806C43A8(void) {
    s32 sfx = 0;

    switch (gCurrentMap) {
        case 6:
            sfx = 3;
            break;
        case 0x6A:
            sfx = 0x6A;
            break;
        case 0x37:
            sfx = 0x4A;
            break;
    }
    if (sfx != 0) {
        sfxAllocateChannel(sfx, 1.0f);
    }
}

extern s16 D_80750AC8;


void func_806C4414(s32 defaultPathId, s32 lowCountPathId, s32 rewardPathId, s32 initialCutsceneId, s32 rewardCutsceneId, s32 targetCount, s32 rewardFlag) {
    s16 *heightOffsetPtr = COMPONENT_ACTOR->secondComponent;
    PlayerState *playerState = gPlayerSlots->actor->customState;
    Actor *attachedActor = playerState->actor;
    s32 pathId;

    D_80750AC8 = targetCount;
    lightAdd(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f, 0.0f, 0.0f, 80.0f, 0, 0xFF, 0xFF, 0xFF);
    if (!(gCurrentActor->flags & 0x10)) {
        pathId = -1;
        if (flagGet(rewardFlag, 0) != 0 || func_807142D8() != 0) {
            if (initialCutsceneId == gBehaviourExtraState->id) {
                func_806C43A8();
            }
            gCurrentActor->state = 0x40;
            return;
        }
        func_80724CA4(1, 1);
        if (initialCutsceneId == gBehaviourExtraState->id) {
            pathId = defaultPathId;
        } else {
            playerStateQueueCallback(0x46, 0, 0);
            if (slotQueueGetValue(0xB, 0) < targetCount) {
                gCurrentActor->unk15F = 0;
                pathId = lowCountPathId;
            } else {
                if (flagGet(rewardFlag, 0) == 0) {
                    pathId = rewardPathId;
                }
                gCurrentActor->unk15F = 0x80;
            }
        }
        *heightOffsetPtr = 0xF;
        if (pathId >= 0) {
            camStartPath(0, (s16)pathId, 1);
        }
        if (attachedActor != NULL) {
            attachedActor->yawSpeed = 0;
        }
    }
    if (rewardCutsceneId == gBehaviourExtraState->id && (gCurrentActor->unk15F & 0x80) && gBehaviourWorkState->timer == 0x5A && flagGet(rewardFlag, 0) == 0) {
        actorSpawnNodeEntryAtActor(0x2D, rewardFlag);
        sfxAllocateChannel(0x14, 1.0f);
    }
    actorPlaceAttachedChildren(-0x1E);
    func_80724E48(0);
    gCurrentActor->yaw = (gBehaviourTargetActor->yaw + 0x800) & 0xFFF;
    gCurrentActor->x = mathSinF(gCurrentActor->moveYaw) * 12.0f + gBehaviourTargetActor->x;
    gCurrentActor->z = mathCosF(gCurrentActor->moveYaw) * 15.0f + gBehaviourTargetActor->z;
    gCurrentActor->y = gBehaviourTargetActor->y + (f32)*heightOffsetPtr + mathSinF(gFrameCounter * 100) * 5.0f;
    gCurrentActor->moveYaw += 0x3C;
    switch (gCurrentActor->unk15F & 0x7F) {
        case 0:
            if (!(gCurrentActor->flags & 0x2000000)) {
                gBehaviourWorkState->timer = 0x1E;
            } else {
                gCurrentActor->unk15F++;
            }
            break;
        case 1:
            if (gCurrentActor->flags & 0x2000000) {
                gBehaviourWorkState->timer = 0x1E;
            } else {
                gCurrentActor->unk15F++;
                if (rewardCutsceneId == gBehaviourExtraState->id) {
                    if (slotQueueGetValue(0xB, 0) >= targetCount) {
                        gBehaviourWorkState->timer = 0x78;
                    }
                }
            }
            break;
    }
    if (gBehaviourWorkState->timer != 0) {
        gBehaviourWorkState->timer--;
    }
    if (gBehaviourWorkState->timer == 0) {
        if (++*heightOffsetPtr >= 0x3D) {
            gCurrentActor->state = 0x40;
            func_806C43A8();
            if (rewardCutsceneId == gBehaviourExtraState->id) {
                if (flagGet(rewardFlag, 0) != 0 || slotQueueGetValue(0xB, 0) >= targetCount) {
                    mapCheckAutoTransition();
                } else {
                    hudSpawnTextScreen(1);
                }
            }
        }
    }
}

void func_806C4904(void) {
    func_806C4414(0, 1, 2, 0xF, 0x10, 0x32, 0x18);
}

void func_806C4948(void) {
    func_806C4414(6, 7, 8, 0x10, 0xE, 0x32, 0xD7);
}

void func_806C498C(void) {
    func_806C4414(1, 2, 3, 4, 5, 0x19, 0x13E);
}


void func_806C49D0(void) {
    behaviourFrameBegin();
    switch (gCurrentMap) {
        case 0x26:
            func_806C3F10(2, 6, 0);
            break;
        case 6:
            func_806C4904();
            break;
        case 0x37:
            func_806C4948();
            break;
        case 0x6A:
            func_806C498C();
            break;
        case 0x30:
            if (gBehaviourExtraState->id == 6) {
                func_806C3F10(2, 7, 0x1A);
            } else {
                func_806C3F10(2, 3, 0);
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern u8 gPlayerCharacterId;
extern Actor *gSpawnedActor;


u8 func_806C4AC4(u16 spawnCooldown, u16 maxSpawns) {
    u8 ret = 0;
    s32 pad;
    s16 *cooldownPtr;
    s16 *durationPtr;
    f32 ang;

    durationPtr = COMPONENT_ACTOR->secondComponent;
    cooldownPtr = COMPONENT_ACTOR->fourthComponent;
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourAnimState->flags |= 0x20;
        gCurrentActor->speedXZ = (f32)(u32)gBehaviourExtraState->targetSpeed;
    }
    {
        s32 d = gBehaviourWorkState->targetY - gBehaviourExtraState->y;

        if (d < 0) {
            *durationPtr = 0;
        } else {
            *durationPtr = d;
        }
    }
    switch (gCurrentActor->state) {
        case 0x37:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x22, 0.0f);
            break;
        case 2:
        case 0x26:
            gActivePlayerState->stateFlags2 |= 0x40;
            ang = mathAngleBetweenPointsDeg((s32)gCurrentActor->x, (s32)gCurrentActor->z, (s32)gPrimaryPlayerActor->x, (s32)gPrimaryPlayerActor->z);
            gCurrentActor->unkEC = (s16)(ang - mathAngleBetweenPointsDeg((s32)gPlayerSlots->focusX, (s32)gPlayerSlots->focusZ, (s32)gPlayerSlots->camX, (s32)gPlayerSlots->camZ));
            actorAirPatrolStep(gCurrentActor->state, gBehaviourAnimState->animId1, gBehaviourAnimState->animId2);
            gCurrentActor->unk15F = maxSpawns - gBehaviourWorkState->timer + 1;
            if (gActorGlobalState.unk0 != 0) {
                if (gCurrentActor->unk15F != gActorGlobalState.unk1[0]) {
                    ret = 1;
                } else {
                    gBehaviourWorkState->timer--;
                    if (gBehaviourWorkState->timer == 0) {
                        ret = 2;
                    }
                }
            }
            if (gPlayerCharacterId != 1) {
                ret = 1;
            }
            if (*cooldownPtr != 0) {
                (*cooldownPtr)--;
            } else if (gCurrentActor->yawSpeed < maxSpawns) {
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x1DD, 0xFF, 0x7F, 0x14, 0x14, 0.0f, 0);
                actorSpawn(0x18, 0);
                gCurrentActor->yawSpeed++;
                gSpawnedActor->unk15F = gCurrentActor->yawSpeed;
                gSpawnedActor->x = gCurrentActor->x;
                gSpawnedActor->y = gCurrentActor->y - 10.0f;
                gSpawnedActor->z = gCurrentActor->z;
                gSpawnedActor->yaw = gCurrentActor->yaw;
                gSpawnedActor->parentActor = gCurrentActor;
                *cooldownPtr = spawnCooldown;
            }
            renderCallbacksRegister(actorDrawAnimatedEffect, gCurrentActor, 3);
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
    return ret;
}


void func_806C4E8C(void) {
    slotQueueSetDisplayMode(5, 0, 0);
}


void func_806C4EB4(void) {
    csModelStateSetFirstByte(0x2C, 0xB);
    func_806C4E8C();
}


void func_806C4EE0(u8 subAction, u8 stateValue) {
    gBehaviourWorkState->unk2E = 0;
    resQueueSetValue(1);
    resQueueAttachActor(gCurrentActor, 0xF, subAction);
    gCurrentActor->state = 0x29;
    gCurrentActor->unk155 = 0;
    gCurrentActor->yawSpeed = stateValue;
    gCurrentActor->movePitch = 0;
}

void func_806C4F5C(void) {
    s32 pad;
    s16 *cooldownPtr;
    f32 dx;
    f32 dy;
    f32 dz;

    cooldownPtr = COMPONENT_ACTOR->fourthComponent;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->state = 0x1E;
        behaviourSetAnimIds(0x244, 0x244, 0x246);
        gCurrentActor->eyeHeight = (u32)gCurrentActor->eyeHeight / 2.0;
    }
    gActivePlayerState->stateFlags2 &= ~0x40;
    switch (gCurrentActor->state) {
        case 0:
        case 14:
        case 15:
        case 30:
            actorScriptedCommandUpdate();
            if (currentActorTestClearFlag() != 0) {
                csModelStateSetFirstByte(0x2D, 0x14);
                gCurrentActor->drawDistance = 0x3E8;
                gBehaviourAnimState->flags |= 0x24;
                resQueueAttachActor(gCurrentActor, 0xF, 0);
                actorScriptStart(gCurrentActor, 0x244);
                gCurrentActor->state = 0x27;
                gBehaviourWorkState->unk2E = 0xF0;
            }
            break;
        case 39:
            gActivePlayerState->stateFlags2 |= 0x40;
            actorAirPatrolStep(2, 0x244, 0x246);
            if ((gBehaviourWorkState->flags & 4) && ((gBehaviourWorkState->unk25 & 0x7F) == 3)) {
                gCurrentActor->state = 0x28;
                gCurrentActor->unk155 = 0;
                actorScriptStart(gCurrentActor, 0x244);
            }
            break;
        case 40:
            gActivePlayerState->stateFlags2 |= 0x40;
            switch (gCurrentActor->unk155) {
                case 0:
                case 1:
                case 2:
                    if (gCurrentActor->floorY + 10.0f < gCurrentActor->y) {
                        gCurrentActor->y -= 2.0f;
                    }
                    dx = gPrimaryPlayerActor->x - gCurrentActor->x;
                    dy = gPrimaryPlayerActor->y - gCurrentActor->y;
                    dz = gPrimaryPlayerActor->z - gCurrentActor->z;
                    if (dx * dx + dy * dy + dz * dz < 6400.0f) {
                        gCurrentActor->unk155 = 3;
                        camStartPath(gCurrentActor, 0x1A, 1);
                        actorScriptStart(gCurrentActor, 0x245);
                    } else if (gBehaviourWorkState->unk2E != 0) {
                        gBehaviourWorkState->unk2E--;
                    } else {
                        gCurrentActor->state = 0x29;
                        gCurrentActor->unk155 = 0;
                        gBehaviourWorkState->unk2E = 0;
                        resQueueSetValue(1);
                        resQueueAttachActor(gCurrentActor, 0xF, 2);
                    }
                    break;
                case 3:
                    if (camIsCutsceneActive() == 0) {
                        csModelStateSetFirstByte(0x2C, 0x1E);
                        *cooldownPtr = 0x78;
                        gBehaviourWorkState->timer = 0xA;
                        gCurrentActor->state = 2;
                        gCurrentActor->unk155 = 0;
                        slotQueueSetDisplayMode(5, 0, 1);
                        actorScriptStart(gCurrentActor, 0x244);
                    }
                    break;
            }
            behaviourUpdateShadowAlpha();
            break;
        case 41:
            if (gCurrentActor->movePitch == 0) {
                camStartPath(gCurrentActor, 0x1C, 1);
                gCurrentActor->movePitch++;
            } else if (camIsCutsceneActive() == 0) {
                if (gCurrentActor->yawSpeed == 0) {
                    func_806C4EB4();
                    hudSpawnTextScreen(3);
                    gCurrentActor->state = 0x2A;
                    gCurrentActor->unk155 = 0;
                } else if (gCurrentActor->movePitch == 1) {
                    csModelStateSetFirstByte(0xEB, 0xA);
                    gCurrentActor->movePitch++;
                }
                gCurrentActor->y += 3.0f;
                gBehaviourWorkState->unk2E++;
                if (gBehaviourWorkState->unk2E >= 0x83) {
                    gBehaviourAnimState->flags &= 0xFFFB;
                    func_806C4EB4();
                    gCurrentActor->state = 0x3C;
                }
            }
            behaviourUpdateShadowAlpha();
            break;
        case 42:
            func_80724A20();
            break;
        case 48:
            gCurrentActor->yaw = 0xA82;
            gPrimaryPlayerActor->yaw = 0xA82;
            zoneEntryGetPosition(8, 2, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
            actorClearMovementFlags(gPrimaryPlayerActor);
            zoneEntryGetPosition(8, 2, &gPrimaryPlayerActor->x, &gPrimaryPlayerActor->y, &gPrimaryPlayerActor->z);
            gPrimaryPlayerActor->y -= 25.0f;
            gCurrentActor->state = 0x28;
            gCurrentActor->unk155 = 0;
            actorScriptStart(gCurrentActor, 0x244);
            gBehaviourWorkState->unk25 = 2;
            slotQueueSetDisplayMode(5, 0, 1);
            break;
    }
    switch (func_806C4AC4(0x78, 0xA)) {
        case 1:
            func_806C4EE0(2, 0);
            break;
        case 2:
            func_806C4EE0(3, 1);
            break;
    }
    func_8072881C(0, &gBehaviourWorkState->unk28);
}

void func_806C55D8(void) {
}

void func_806C55E0(void) {
    s32 pad;
    s16 *cooldownPtr;

    cooldownPtr = COMPONENT_ACTOR->fourthComponent;
    behaviourFrameBegin();
    if (!(gActivePlayerState->stateFlags & 0x100000)) {
        gCurrentActor->state = 0x40;
        return;
    }
    if (!(gCurrentActor->flags & 0x10)) {
        behaviourSetAnimIds(0x357, 0x357, 0x359);
        gBehaviourAnimState->flags |= 0x20;
        gCurrentActor->state = 0x1E;
        gCurrentActor->drawDistance = 0x3E8;
        func_80728950(0);
    }
    switch (gCurrentActor->state) {
        case 0x1E:
            effectSpawnSmoke(1);
            func_80724A20();
            break;
        case 0x27:
            switch (gCurrentActor->unk155) {
                case 0:
                    if (camIsCutsceneActive() == 0) {
                        currentActorAnimSetFrame(0, 0);
                        camStartPath(gCurrentActor, 0x13, 1);
                        gCurrentActor->unk155++;
                    }
                    break;
                case 1:
                    if (currentActorTestClearFlag() != 0) {
                        actorScriptStart(gCurrentActor, 0x354);
                        gCurrentActor->unk155++;
                    }
                    break;
                case 3:
                    resQueueAttachActor(gCurrentActor, 0x15, 0);
                    gCurrentActor->unk155++;
                    break;
                case 4:
                    if (!(gCurrentActor->flags & 0x2000000)) {
                        camResumePath();
                        gCurrentActor->state = 0x28;
                    }
                    break;
            }
            break;
        case 0x28:
            if (gPrimaryPlayerActor->state == 0x63) {
                if ((gCurrentActor->x - gPrimaryPlayerActor->x) * (gCurrentActor->x - gPrimaryPlayerActor->x) + (gCurrentActor->z - gPrimaryPlayerActor->z) * (gCurrentActor->z - gPrimaryPlayerActor->z) < 10000.0f) {
                    camStartPath(gCurrentActor, 0x15, 1);
                    resQueueAttachActor(gCurrentActor, 0x15, 1);
                    gCurrentActor->state = 0x29;
                    gCurrentActor->unk155 = 0;
                }
            }
            break;
        case 0x29:
            switch (gCurrentActor->unk155) {
                case 0:
                    if (!(gCurrentActor->flags & 0x2000000)) {
                        actorScriptStart(gCurrentActor, 0x358);
                        gCurrentActor->unk155 = 1;
                    }
                    break;
                case 2:
                    camResumePath();
                    gBehaviourAnimState->flags |= 0x24;
                    gCurrentActor->state = 2;
                    slotQueueSetDisplayMode(5, 0, 1);
                    slotQueueUpdate(5, 1, 0);
                    *cooldownPtr = 0x78;
                    gBehaviourWorkState->timer = 0x10;
                    gCurrentActor->yawSpeed = 0;
                    actorScriptStart(gCurrentActor, 0x357);
                    break;
            }
            break;
        case 0x2A:
            switch (gCurrentActor->unk155) {
                case 0:
                    gCurrentActor->pitch = 0;
                    gCurrentActor->roll = 0;
                    if (!(gCurrentActor->flags & 0x2000000)) {
                        camResumePath();
                        func_806C4E8C();
                        if (gCurrentActor->sub4->animId == 0x35A && gPrimaryPlayerActor->state == 0x63) {
                            hudSpawnTextScreen(4);
                            gCurrentActor->unk155 = 3;
                        } else {
                            gCurrentActor->unk155++;
                            gCurrentActor->flags &= ~0x8000;
                        }
                    }
                    break;
                case 1:
                    behaviourFadeOutWithinZone(5);
                    break;
                case 2:
                    gCurrentActor->state = 0x3C;
                    break;
                case 3:
                    func_80724A20();
                    break;
            }
            break;
        case 0x30:
            actorScriptStart(gCurrentActor, 0x355);
            actorSetPositionFromPoint(gCurrentActor, gBehaviourExtraState);
            gBehaviourWorkState->unk25 = 0;
            gCurrentActor->yawSpeed = 0;
            actorClearMovementFlags(gPrimaryPlayerActor);
            gPrimaryPlayerActor->y = gCurrentActor->y;
            gPrimaryPlayerActor->x = mathSinF(gCurrentActor->yaw) * 50.0f + gCurrentActor->x;
            gPrimaryPlayerActor->z = mathCosF(gCurrentActor->yaw) * 50.0f + gCurrentActor->z;
            gPrimaryPlayerActor->yaw = mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, gPrimaryPlayerActor->x, gPrimaryPlayerActor->z);
            camStartPath(gCurrentActor, 0x15, 1);
            resQueueAttachActor(gCurrentActor, 0x15, 1);
            gCurrentActor->state = 0x29;
            gCurrentActor->unk155 = 0;
            break;
    }
    gActivePlayerState->stateFlags2 &= ~0x40;
    switch (func_806C4AC4(0x78, 0x10)) {
        case 1:
            actorSetPositionFromPoint(gCurrentActor, gBehaviourExtraState);
            resQueueAttachActor(gCurrentActor, 0x15, 2);
            actorScriptStart(gCurrentActor, 0x35A);
            gCurrentActor->state = 0x2A;
            gCurrentActor->unk155 = 0;
            camStartPath(gCurrentActor, 0x16, 1);
            break;
        case 2:
            actorSetPositionFromPoint(gCurrentActor, gBehaviourExtraState);
            resQueueAttachActor(gCurrentActor, 0x15, 3);
            actorScriptStart(gCurrentActor, 0x35B);
            gCurrentActor->state = 0x2A;
            gCurrentActor->unk155 = 0;
            camStartPath(gCurrentActor, 0x14, 1);
            break;
    }
    if (gCurrentActor->state != 0x1E) {
        func_8072881C(0, &gBehaviourWorkState->unk28);
    }
}

// customState of the cutscene actor run by func_806C5FEC: what it restores when the scene ends.
typedef struct CutsceneRestoreState {
    /* 0x00 */ f32 savedLightR;
    /* 0x04 */ f32 savedLightG;
    /* 0x08 */ f32 savedLightB;
    /* 0x0C */ Actor *helperActor;
    /* 0x10 */ Actor *player;
    /* 0x14 */ s16 savedPitch;
    /* 0x16 */ s16 savedRoll;
    /* 0x18 */ u8 pad18[2];
    /* 0x1A */ s16 lightChunk;
    /* 0x1C */ s16 frameCount;
    /* 0x1E */ s8 phase;
} CutsceneRestoreState;


extern s16 gCurrentLevelIndex;
extern s32 D_8071FB08;
extern s16 D_807FD802;
extern s16 D_807FD804;
extern s16 D_807FD806;
f32 sqrtf(f32);

void func_806C5C20(void) {
    f32 screenX;
    f32 screenY;
    f32 dist;
    s32 outFlag[2];

    behaviourFrameBegin();
    actorClearMovementFlags(gCurrentActor);
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourAnimState->flags |= 0x40;
        gCurrentActor->drawDistance = 0xFA;
        func_80724CA4(2, 1);
    }
    if ((randomNonNegative() >> 15) % 1000 >= 0x3CB) {
        gCurrentActor->speedXZ = gBehaviourExtraState->targetSpeed << 2;
    }
    func_80724E48(6);
    actorMoveWithinZone(1, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x2C9, 0.0f);
    if (!(gFrameCounter & 3)) {
        effectSetDepth(1);
        effectSetCallback(effectShrinkFadeMatrixUpdate);
        effectCreateAtPosition(&D_8071FB08, 1.6f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
    }
    if (!(gActivePlayerState->stateFlags & 0x8000)) {
        dist = sqrtf((gPlayerSlots->camZ - gCurrentActor->z) * (gPlayerSlots->camZ - gCurrentActor->z) +
                     (gPlayerSlots->camX - gCurrentActor->x) * (gPlayerSlots->camX - gCurrentActor->x)) -
               gPlayerSlots->unk284;
        if (D_807FD804 >= 0x8A && D_807FD804 < 0xB1 && D_807FD806 >= 0x61 && D_807FD806 < 0x88 && dist < D_807FD802) {
            if (gActivePlayerState->unk1EC != 1) {
                if (behaviourIsTargetWithinAngle(0x1388) != 0) {
                    actorScriptStart(gCurrentActor, 0x2B6);
                }
            }
            gActivePlayerState->unk1EC = 1;
        } else {
            if (gActivePlayerState->unk1EC != 2) {
                actorScriptStart(gCurrentActor, 0x2B5);
            }
            gActivePlayerState->unk1EC = 2;
        }
    }
    if ((gActivePlayerState->stateFlags & 0x8000) && gActivePlayerState->unk1EC == 1) {
        if (gCurrentActor->state != 0x40) {
            flagSet(spawnFlagLookup(gCurrentLevelIndex, spawnNodeIdForActor(gCurrentActor), outFlag), 1, 0);
            eepromSavePlayerData();
        }
        gCurrentActor->state = 0x40;
    }
    if (gCurrentActor->state != 0x40) {
        sfxAllocateChannel(0x42, 1.0f);
    } else {
        sfxStopChannel(0x42, 0);
    }
    camProjectToScreen(gCurrentActor->x, gCurrentActor->y + 10.0f, gCurrentActor->z, &screenX, &screenY, 0, 1.0f, 0);
    D_807FD804 = screenX;
    D_807FD806 = screenY;
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void func_806C5FEC(void) {
    CutsceneRestoreState *restore;

    restore = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        restore->frameCount = 0;
        gCurrentActor->flags |= 0x400;
    }
    restore->frameCount++;
    switch (restore->phase) {
        case 1:
            if (gPrimaryPlayerActor->unk155 == 3) {
                resQueueAttachActor(gCurrentActor, 0x1E, 3);
                restore->phase = 2;
            } else if (restore->player->state != 0x83) {
                restore->phase = 3;
            }
            break;
        case 2:
            if (!(gCurrentActor->flags & 0x2000000)) {
                restore->phase = 3;
                camResumePath();
            }
            break;
        default:
            if (restore->player->state != 0x83) {
                ((PlayerState *)restore->player->customState)->stateFlags2 &= ~0x10;
                restore->player->flags &= ~0x40000000;
                restore->player->flags |= 1;
                restore->player->roll = restore->savedRoll;
                restore->player->pitch = restore->savedPitch;
                gGlobalPauseFlags |= 0x10030;
                lightSetColor(restore->savedLightR, restore->savedLightG, restore->savedLightB, restore->lightChunk);
                sfxStopChannel(0x3B, 0);
                actorDespawn(restore->helperActor);
                actorDespawn(gCurrentActor);
                return;
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void func_806C61C8(void) {
    f32 x;
    f32 z;
    f32 sinv;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unkEC = 0x3C;
        actorScriptStart(gCurrentActor, 0x23D);
        if (gPrimaryPlayerActor->state == 0xC) {
            actorScriptStartByIndex(gPrimaryPlayerActor, 0x87);
        }
    }
    x = mathSinF(gPrimaryPlayerActor->yaw) * 50.0f + gPrimaryPlayerActor->x;
    z = mathCosF(gPrimaryPlayerActor->yaw) * 50.0f + gPrimaryPlayerActor->z;
    gCurrentActor->yaw = (gPrimaryPlayerActor->yaw + 0x800) & 0xFFF;
    if (gCurrentActor->unkEC == 0x3C) {
        gCurrentActor->x = mathSinF(gCurrentActor->moveYaw) * 10.0f + x;
        gCurrentActor->z = mathCosF(gCurrentActor->moveYaw) * 10.0f + z;
    }
    gCurrentActor->y = mathSinF(gFrameCounter * 100) * 5.0f + (gCurrentActor->unk15F + gPrimaryPlayerActor->y + 3.0f + gCurrentActor->unkEC);
    if (!(gCurrentActor->flags & 0x10)) {
        if (gCurrentActor->movePitch != 0) {
            gCurrentActor->unk15F = 0x14;
            actorSpawnNodeEntryAtActor(0x2D, func_8073195C(gCurrentActor->movePitch));
        }
    }
    if (gCurrentActor->movePitch != 0) {
        actorPlaceAttachedChildren(-0x1E);
    }
    sinv = mathSinF(gFrameCounter * 50);
    gCurrentActor->moveYaw = gCurrentActor->moveYaw + 60.0f * sinv;
    if (gCurrentActor->flags & 0x2000000) {
        gCurrentActor->yawSpeed = 0x14;
    }
    if (gCurrentActor->yawSpeed != 0) {
        gCurrentActor->yawSpeed--;
    }
    if (gCurrentActor->yawSpeed == 0) {
        gCurrentActor->unkEC++;
        if (gCurrentActor->unkEC >= 0x3D) {
            if (gCurrentActor->movePitch != 0) {
                actorAttachChildCallbacks();
            }
            actorDespawn(gCurrentActor);
            camResumePath();
            if (gPrimaryPlayerActor->state == 0xC) {
                actorScriptStartByIndex(gPrimaryPlayerActor, 9);
            }
        }
    } else if (gCurrentActor->unkEC >= 0x10) {
        gCurrentActor->unkEC--;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
