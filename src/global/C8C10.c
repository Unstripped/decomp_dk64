#include "common.h"
#include "actor.h"
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

typedef struct R1C8aSub174 {
    /* 0x00 */ u8 pad0[0x88];
    /* 0x88 */ Actor *unk88;
} R1C8aSub174;

typedef struct R1C8aActor {
    /* 0x000 */ u8 pad0[0xEC];
    /* 0x0EC */ s16 unkEC;
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ s16 unkF0;
    /* 0x0F2 */ u8 padF2[0x82];
    /* 0x174 */ R1C8aSub174 *unk174;
    /* 0x178 */ s16 *unk178;
    /* 0x17C */ u8 pad17C[4];
    /* 0x180 */ s16 *unk180;
} R1C8aActor;

typedef struct R1C8aD580 {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ s32 unk1F4;
} R1C8aD580;

typedef struct R1C8aPlayer {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ R1C8aActor *unk4;
    /* 0x008 */ u8 pad8[0x208];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ u8 pad214[4];
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0xC];
    /* 0x228 */ f32 unk228;
    /* 0x22C */ u8 pad22C[4];
    /* 0x230 */ f32 unk230;
    /* 0x234 */ u8 pad234[0x8C];
    /* 0x2C0 */ u8 unk2C0;
} R1C8aPlayer;

#define R1C8aA ((R1C8aActor *)gCurrentActor)
#define R1C8aD ((R1C8aD580 *)gActivePlayerState)

extern R1C8aPlayer *gPlayerSlots;
extern Actor *gCamActor;
extern s32 gCurrentMap;


void func_806C3F10(u8 startActionId, u8 exitActionId, u8 camPathId) {
    s16 *durationPtr = R1C8aA->unk178;

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
    s16 *heightOffsetPtr = R1C8aA->unk178;
    R1C8aSub174 *sub = gPlayerSlots->unk4->unk174;
    Actor *subActor = sub->unk88;
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
        if (subActor != 0) {
            subActor->yawSpeed = 0;
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

    pad = 0;
    durationPtr = R1C8aA->unk178;
    cooldownPtr = R1C8aA->unk180;
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
            R1C8aD->unk1F4 |= 0x40;
            ang = mathAngleBetweenPointsDeg((s32)gCurrentActor->x, (s32)gCurrentActor->z, (s32)gPrimaryPlayerActor->x, (s32)gPrimaryPlayerActor->z);
            R1C8aA->unkEC = (s16)(ang - mathAngleBetweenPointsDeg((s32)gPlayerSlots->unk228, (s32)gPlayerSlots->unk230, (s32)gPlayerSlots->unk210, (s32)gPlayerSlots->unk218));
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
    R1C8aA->unkF0 = 0;
}

typedef struct LgC4F5CA {
    /* 0x000 */ u8 pad0[0x60];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x1C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x3E];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[8];
    /* 0x0F0 */ s16 unkF0;
    /* 0x0F2 */ u8 padF2[0x38];
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[0x28];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[8];
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 pad15F[9];
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 pad16A[0x16];
    /* 0x180 */ s16 *unk180;
} LgC4F5CA;

typedef struct LgC4F5CG {
    /* 0x000 */ u8 pad0[0x1F4];
    /* 0x1F4 */ u32 unk1F4;
} LgC4F5CG;

#define LgA ((LgC4F5CA *)gCurrentActor)
#define LgB ((LgC4F5CA *)gPrimaryPlayerActor)
#define LgG ((LgC4F5CG *)gActivePlayerState)


void func_806C4F5C(void) {
    s32 pad;
    s16 *cooldownPtr;
    f32 dx;
    f32 dy;
    f32 dz;

    cooldownPtr = LgA->unk180;
    behaviourFrameBegin();
    if (!(LgA->unk60 & 0x10)) {
        LgA->unk154 = 0x1E;
        behaviourSetAnimIds(0x244, 0x244, 0x246);
        LgA->unk15E = (u32)LgA->unk15E / 2.0;
    }
    LgG->unk1F4 &= ~0x40;
    switch (LgA->unk154) {
        case 0:
        case 14:
        case 15:
        case 30:
            actorScriptedCommandUpdate();
            if (currentActorTestClearFlag() != 0) {
                csModelStateSetFirstByte(0x2D, 0x14);
                LgA->unk12A = 0x3E8;
                gBehaviourAnimState->flags |= 0x24;
                resQueueAttachActor(gCurrentActor, 0xF, 0);
                actorScriptStart(gCurrentActor, 0x244);
                LgA->unk154 = 0x27;
                gBehaviourWorkState->unk2E = 0xF0;
            }
            break;
        case 39:
            LgG->unk1F4 |= 0x40;
            actorAirPatrolStep(2, 0x244, 0x246);
            if ((gBehaviourWorkState->flags & 4) && ((gBehaviourWorkState->unk25 & 0x7F) == 3)) {
                LgA->unk154 = 0x28;
                LgA->unk155 = 0;
                actorScriptStart(gCurrentActor, 0x244);
            }
            break;
        case 40:
            LgG->unk1F4 |= 0x40;
            switch (LgA->unk155) {
                case 0:
                case 1:
                case 2:
                    if (LgA->unkA4 + 10.0f < LgA->unk80) {
                        LgA->unk80 -= 2.0f;
                    }
                    dx = LgB->unk7C - LgA->unk7C;
                    dy = LgB->unk80 - LgA->unk80;
                    dz = LgB->unk84 - LgA->unk84;
                    if (dx * dx + dy * dy + dz * dz < 6400.0f) {
                        LgA->unk155 = 3;
                        camStartPath(gCurrentActor, 0x1A, 1);
                        actorScriptStart(gCurrentActor, 0x245);
                    } else if (gBehaviourWorkState->unk2E != 0) {
                        gBehaviourWorkState->unk2E--;
                    } else {
                        LgA->unk154 = 0x29;
                        LgA->unk155 = 0;
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
                        LgA->unk154 = 2;
                        LgA->unk155 = 0;
                        slotQueueSetDisplayMode(5, 0, 1);
                        actorScriptStart(gCurrentActor, 0x244);
                    }
                    break;
            }
            behaviourUpdateShadowAlpha();
            break;
        case 41:
            if (LgA->unkF0 == 0) {
                camStartPath(gCurrentActor, 0x1C, 1);
                LgA->unkF0++;
            } else if (camIsCutsceneActive() == 0) {
                if (LgA->unk168 == 0) {
                    func_806C4EB4();
                    hudSpawnTextScreen(3);
                    LgA->unk154 = 0x2A;
                    LgA->unk155 = 0;
                } else if (LgA->unkF0 == 1) {
                    csModelStateSetFirstByte(0xEB, 0xA);
                    LgA->unkF0++;
                }
                LgA->unk80 += 3.0f;
                gBehaviourWorkState->unk2E++;
                if (gBehaviourWorkState->unk2E >= 0x83) {
                    gBehaviourAnimState->flags &= 0xFFFB;
                    func_806C4EB4();
                    LgA->unk154 = 0x3C;
                }
            }
            behaviourUpdateShadowAlpha();
            break;
        case 42:
            func_80724A20();
            break;
        case 48:
            LgA->unkE6 = 0xA82;
            LgB->unkE6 = 0xA82;
            zoneEntryGetPosition(8, 2, &LgA->unk7C, &LgA->unk80, &LgA->unk84);
            actorClearMovementFlags(gPrimaryPlayerActor);
            zoneEntryGetPosition(8, 2, &LgB->unk7C, &LgB->unk80, &LgB->unk84);
            LgB->unk80 -= 25.0f;
            LgA->unk154 = 0x28;
            LgA->unk155 = 0;
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

typedef struct LgC55E0A {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ActorSub4 *sub4;
    /* 0x008 */ u8 pad8[0x58];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x5C];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[0x40];
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[0x28];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x12];
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 pad16A[0x16];
    /* 0x180 */ s16 *unk180;
} LgC55E0A;

typedef struct LgC55E0G {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ u32 unk1F0;
    /* 0x1F4 */ u32 unk1F4;
} LgC55E0G;

#define LA ((LgC55E0A *)gCurrentActor)
#define LA4C ((LgC55E0A *)gPrimaryPlayerActor)
#define LG ((LgC55E0G *)gActivePlayerState)


void func_806C55E0(void) {
    s32 pad;
    s16 *cooldownPtr;

    cooldownPtr = LA->unk180;
    behaviourFrameBegin();
    if (!(LG->unk1F0 & 0x100000)) {
        LA->unk154 = 0x40;
        return;
    }
    if (!(LA->unk60 & 0x10)) {
        behaviourSetAnimIds(0x357, 0x357, 0x359);
        gBehaviourAnimState->flags |= 0x20;
        LA->unk154 = 0x1E;
        LA->unk12A = 0x3E8;
        func_80728950(0);
    }
    switch (LA->unk154) {
        case 0x1E:
            effectSpawnSmoke(1);
            func_80724A20();
            break;
        case 0x27:
            switch (LA->unk155) {
                case 0:
                    if (camIsCutsceneActive() == 0) {
                        currentActorAnimSetFrame(0, 0);
                        camStartPath(gCurrentActor, 0x13, 1);
                        LA->unk155++;
                    }
                    break;
                case 1:
                    if (currentActorTestClearFlag() != 0) {
                        actorScriptStart(gCurrentActor, 0x354);
                        LA->unk155++;
                    }
                    break;
                case 3:
                    resQueueAttachActor(gCurrentActor, 0x15, 0);
                    LA->unk155++;
                    break;
                case 4:
                    if (!(LA->unk60 & 0x2000000)) {
                        camResumePath();
                        LA->unk154 = 0x28;
                    }
                    break;
            }
            break;
        case 0x28:
            if (LA4C->unk154 == 0x63) {
                if ((LA->unk7C - LA4C->unk7C) * (LA->unk7C - LA4C->unk7C) + (LA->unk84 - LA4C->unk84) * (LA->unk84 - LA4C->unk84) < 10000.0f) {
                    camStartPath(gCurrentActor, 0x15, 1);
                    resQueueAttachActor(gCurrentActor, 0x15, 1);
                    LA->unk154 = 0x29;
                    LA->unk155 = 0;
                }
            }
            break;
        case 0x29:
            switch (LA->unk155) {
                case 0:
                    if (!(LA->unk60 & 0x2000000)) {
                        actorScriptStart(gCurrentActor, 0x358);
                        LA->unk155 = 1;
                    }
                    break;
                case 2:
                    camResumePath();
                    gBehaviourAnimState->flags |= 0x24;
                    LA->unk154 = 2;
                    slotQueueSetDisplayMode(5, 0, 1);
                    slotQueueUpdate(5, 1, 0);
                    *cooldownPtr = 0x78;
                    gBehaviourWorkState->timer = 0x10;
                    LA->unk168 = 0;
                    actorScriptStart(gCurrentActor, 0x357);
                    break;
            }
            break;
        case 0x2A:
            switch (LA->unk155) {
                case 0:
                    LA->unkE4 = 0;
                    LA->unkE8 = 0;
                    if (!(LA->unk60 & 0x2000000)) {
                        camResumePath();
                        func_806C4E8C();
                        if (LA->sub4->animId == 0x35A && LA4C->unk154 == 0x63) {
                            hudSpawnTextScreen(4);
                            LA->unk155 = 3;
                        } else {
                            LA->unk155++;
                            LA->unk60 &= ~0x8000;
                        }
                    }
                    break;
                case 1:
                    behaviourFadeOutWithinZone(5);
                    break;
                case 2:
                    LA->unk154 = 0x3C;
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
            LA->unk168 = 0;
            actorClearMovementFlags(gPrimaryPlayerActor);
            LA4C->unk80 = LA->unk80;
            LA4C->unk7C = mathSinF(LA->unkE6) * 50.0f + LA->unk7C;
            LA4C->unk84 = mathCosF(LA->unkE6) * 50.0f + LA->unk84;
            LA4C->unkE6 = mathAngleBetweenPoints2D(LA->unk7C, LA->unk84, LA4C->unk7C, LA4C->unk84);
            camStartPath(gCurrentActor, 0x15, 1);
            resQueueAttachActor(gCurrentActor, 0x15, 1);
            LA->unk154 = 0x29;
            LA->unk155 = 0;
            break;
    }
    LG->unk1F4 &= ~0x40;
    switch (func_806C4AC4(0x78, 0x10)) {
        case 1:
            actorSetPositionFromPoint(gCurrentActor, gBehaviourExtraState);
            resQueueAttachActor(gCurrentActor, 0x15, 2);
            actorScriptStart(gCurrentActor, 0x35A);
            LA->unk154 = 0x2A;
            LA->unk155 = 0;
            camStartPath(gCurrentActor, 0x16, 1);
            break;
        case 2:
            actorSetPositionFromPoint(gCurrentActor, gBehaviourExtraState);
            resQueueAttachActor(gCurrentActor, 0x15, 3);
            actorScriptStart(gCurrentActor, 0x35B);
            LA->unk154 = 0x2A;
            LA->unk155 = 0;
            camStartPath(gCurrentActor, 0x14, 1);
            break;
    }
    if (LA->unk154 != 0x1E) {
        func_8072881C(0, &gBehaviourWorkState->unk28);
    }
}

typedef struct R1C8CBCfg {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ Actor *unkC;
    /* 0x10 */ Actor *unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u8 pad18[2];
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s8 unk1E;
} R1C8CBCfg;

typedef struct R1C8CBPlayer {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ u8 pad214[4];
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0x68];
    /* 0x284 */ f32 unk284;
} R1C8CBPlayer;


extern s16 gCurrentLevelIndex;
extern s32 D_8071FB08;
#define R1C8CBP ((R1C8CBPlayer *)gPlayerSlots)
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
        dist = sqrtf((R1C8CBP->unk218 - gCurrentActor->z) * (R1C8CBP->unk218 - gCurrentActor->z) +
                     (R1C8CBP->unk210 - gCurrentActor->x) * (R1C8CBP->unk210 - gCurrentActor->x)) -
               R1C8CBP->unk284;
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
    R1C8CBCfg *p;

    p = (R1C8CBCfg *)gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        p->unk1C = 0;
        gCurrentActor->flags |= 0x400;
    }
    p->unk1C++;
    switch (p->unk1E) {
        case 1:
            if (gPrimaryPlayerActor->unk155 == 3) {
                resQueueAttachActor(gCurrentActor, 0x1E, 3);
                p->unk1E = 2;
            } else if (p->unk10->state != 0x83) {
                p->unk1E = 3;
            }
            break;
        case 2:
            if (!(gCurrentActor->flags & 0x2000000)) {
                p->unk1E = 3;
                camResumePath();
            }
            break;
        default:
            if (p->unk10->state != 0x83) {
                ((PlayerState *)p->unk10->customState)->stateFlags2 &= ~0x10;
                p->unk10->flags &= ~0x40000000;
                p->unk10->flags |= 1;
                p->unk10->roll = p->unk16;
                p->unk10->pitch = p->unk14;
                gGlobalPauseFlags |= 0x10030;
                lightSetColor(p->unk0, p->unk4, p->unk8, p->unk1A);
                sfxStopChannel(0x3B, 0);
                actorDespawn(p->unkC);
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
