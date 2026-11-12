#include "common.h"
#include "actor.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/FCCD0.h"
#include "proto/race/0.h"
#include "proto/race/7BD0.h"
#include "proto/race/A960.h"
struct RaceC_Config;
struct RaceParticipant;
s16 sfxPlayFromActorWithAltitudeCheck(struct Actor *, s16, u8, s16, u8);


typedef struct {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
    u8 unk8;
    u8 pad9[3];
} RaceC_Row;


extern s32 gCurrentMap;
extern Actor *gCurrentActor;
extern Actor *gActivePlayerActor;
extern RaceC_Row D_8002FB10[];
extern RaceC_Row D_8002FB70[];
void actorScriptStart(void *, s32);

void raceOpponentFollowWaypoints(void) {
    f32 speedDelta;
    f32 turnDelta;
    f32 fs0;
    f32 fs1;
    f32 curSpeed;
    f32 oscSpeed;
    ZoneEntry *a0;
    f32 fv0;
    u8 routeRowIdx;
    RaceC_Row *routeRows;
    f32 q;
    s16 v1;

    routeRowIdx = gBehaviourWorkState->unk24;
    if (gCurrentMap == 0x52) {
        routeRows = D_8002FB10;
    } else {
        routeRows = D_8002FB70;
    }
    curSpeed = gCurrentActor->speedXZ;
    oscSpeed = mathSinF((s16)(gCurrentActor->floorSlopeFactor * 11.4)) * 20.0f;
    a0 = &D_807FDCA0->entries[gBehaviourWorkState->unk25];
    fs0 = gCurrentActor->x - a0->x;
    fs1 = gCurrentActor->z - a0->z;
    if (sqrtf(fs1 * fs1 + fs0 * fs0) < (a0 = &D_807FDCA0->entries[gBehaviourWorkState->unk25])->radius) {
        if ((a0->y < gCurrentActor->y ? gCurrentActor->y - a0->y : -(gCurrentActor->y - a0->y)) < 80.0f && gBehaviourWorkState->unk25 < D_807FDCA0->entryCount - 1) {
            RaceC_Row *row = (RaceC_Row *)((u8 *)routeRows + routeRowIdx * 12); // FAKE: byte-offset row address; &routeRows[routeRowIdx] changes the index multiply
            if (row->unk0 == gBehaviourWorkState->unk25) {
                if (row) {}  // FAKE: dead test steers uopt FP callee-saved colouring (fs0/fs1)
                gCurrentActor->accelY = row->unk4;
                if (row->unk8 == 1) {
                    actorScriptStart(gCurrentActor, 0x286);
                    gCurrentActor->speedY = 200.0f;
                    gCurrentActor->state += 1;
                }
                gBehaviourWorkState->unk24 += 1;
            }
            gBehaviourWorkState->unk25++;
            a0 = &D_807FDCA0->entries[gBehaviourWorkState->unk25];
        }
        a0 = &D_807FDCA0->entries[gBehaviourWorkState->unk25];
    }
    speedDelta = (a0->height - gCurrentActor->speedXZ / 10.0f) * 0.8;
    fv0 = (gCurrentActor->y - gActivePlayerActor->y) * 0.25;
    if (fv0 > 6.0f) {
        fv0 = 6.0f;
    }
    if (fv0 < -6.0f) {
        fv0 = -6.0f;
    }
    speedDelta = speedDelta + fv0;
    v1 = (s32)(mathAtan2(-fs0, -fs1) * 4096.0 / 6.2831854820251465);
    v1 = v1 - gCurrentActor->moveYaw;
    if (v1 >= 0x800) {
        v1 = v1 - 4096.0;
    }
    if (v1 < -0x800) {
        v1 = v1 + 4096.0;
    }
    turnDelta = (gCurrentActor->speedXZ * v1) / 10000.0;
    fs0 = mathSinF(gCurrentActor->moveYaw) * curSpeed;
    fs1 = mathCosF(gCurrentActor->moveYaw) * curSpeed;
    if (gCurrentActor->contactFlags & 1) {
        fs0 += mathSinF(gCurrentActor->floorSlopeYaw) * oscSpeed;
        fs1 += mathCosF(gCurrentActor->floorSlopeYaw) * oscSpeed;
    }
    fs0 += mathSinF(gCurrentActor->moveYaw) * speedDelta;
    fs1 += mathCosF(gCurrentActor->moveYaw) * speedDelta;
    fs0 += mathCosF(gCurrentActor->moveYaw) * turnDelta;
    fs1 -= mathSinF(gCurrentActor->moveYaw) * turnDelta;
    curSpeed = sqrtf(fs0 * fs0 + fs1 * fs1);
    fv0 = mathAtan2(fs0, fs1);
    if (gCurrentActor->accelY != -20.0f && gCurrentActor->accelY != -360.0f) {
        gCurrentActor->speedXZ = D_807FDCA0->entries[gBehaviourWorkState->unk25].height * 10.0;
    } else {
        gCurrentActor->speedXZ = curSpeed;
    }
    gCurrentActor->moveYaw = fv0 * 4096.0 / 6.2831854820251465;
    if (gCurrentActor->contactFlags & 1) {
        fv0 = gCurrentActor->speedXZ;
        q = (f32)((fv0 * fv0) / 15000.0);
        gCurrentActor->speedXZ = fv0 - q;
        fv0 = q;
        fv0 = q; // FAKE: repeated copy of q steers the q/fv0 register pair
        if (gCurrentActor->speedXZ < 0.0f) {
            gCurrentActor->speedXZ = 0.0f;
        }
    }
}

typedef struct RaceC_Config {
    u8 pad0[4];
    RaceParticipant *unk4;
    u8 pad8[0x18 - 0x8];
    union {
        s32 w;
        struct {
            s16 hi;
            s16 rewardFlag;
        } h;
    } unk18;
    s32 requiredCoins;
} LargeR4_Cfg;

extern u16 D_80750AC4;

int raceCheckCoinRequirement(RaceParticipant *controller, LargeR4_Cfg *config) {
    return controller->unk36 != 0 && flagGet(config->unk18.h.rewardFlag, 0) == 0 && D_80750AC4 >= config->requiredCoins;
}


typedef struct RaceOpponentActor {
    Actor base;
    RaceParticipant *unk178;
    LargeR4_Cfg *unk17C;
} RaceOpponentActor;


extern Actor *gPrimaryPlayerActor;
extern u16 D_80750AC8;
extern s32 D_8002FB94[];


void actorApplyGravity(void);
void actorApplyVelocity(void *);
void actorApproachTargetSpeed(u16);
void actorSetTargetSpeed(void *, s32);
void actorStepPhysics(void *, s16, s16);
void camResumePath(void);
u16 camStartPath(void *, s16, u8);
void currentActorClearFlag(void);
s32 currentActorTestClearFlag(void);
void csModelStateSetFirstByte(s16, s16);
f32 sqrtf(f32);
void actorUpdateFloorContactAndTilt(void *, f32);
void billboardSubmit(Actor *, s16, s16, s16, s16, s16, u8, s16, u8, s16, f32);
s32 playerIsDamageOrKnockbackState(void);
void hudSpawnTextScreen(u8);
void mathAngleStepToward(s16 *, s16, s16);
s32 playerStateQueueCallback(s16, void *, u8);
void sfxStopSlotSound(Actor *, u8);

void raceOpponentBehaviourUpdate(void) {
    f32 dx;
    f32 dz;
    s16 ang16;
    s32 tmp;
    ZoneEntry *e;
    u8 rowIdx;
    RaceParticipant *controller;
    LargeR4_Cfg *config;
    Actor *kid;
    RaceParticipant *child;
    RaceC_Row *routeRows;
    s32 flag;
    f32 fv1;
    s32 sel;
    u32 x;
    s32 y;
    f32 dist;
    u16 angU; // FAKE: u16 raw copy of the angle (ring temp, no sll/sra); steers t-register allocation

    controller = ((RaceOpponentActor *)gCurrentActor)->unk178;
    config = ((RaceOpponentActor *)gCurrentActor)->unk17C;
    kid = controller->actor;
    child = NULL;
    if (gCurrentMap == 0x52) {
        routeRows = D_8002FB10;
    } else {
        routeRows = D_8002FB70;
    }
    if (kid != NULL) {
        child = kid->customState;
    }
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unk144 = 0x1C;
        gCurrentActor->flags |= 0x10400;
        gCurrentActor->flags &= 0xFFFDFFFF;
        gCurrentActor->state = 0;
        gCurrentActor->unk155 = 0;
        gCurrentActor->speedXZ = 0.0f;
        gCurrentActor->accelY = -20.0f;
        gCurrentActor->terminalSpeedY = -900.0f;
        gCurrentActor->drawDistance = 0x7D0;
        gBehaviourWorkState->unk35 = 0;
        gBehaviourWorkState->timer = 0x64;
        gBehaviourWorkState->timer = 0;
        gBehaviourWorkState->unk24 = 0;
        gCurrentActor->flags2 &= 0xFFBF;
        if (gCurrentMap == 0x52) {
            config->requiredCoins = D_80750AC8 = 0x32;
            config->unk18.w = 0x103;
            flag = 0x65;
        } else {
            config->requiredCoins = D_80750AC8 = 0x32;
            config->unk18.w = 0x4B;
            flag = 0x66;
        }
        if (flagGet(flag, 2) == 0 && flagGet(config->unk18.h.rewardFlag, 0) == 0) {
            camStartPath(gCurrentActor, 0, 1);
            currentActorClearFlag();
            flagSet(flag, 1, 2);
        } else {
            controller->unk35 = 3;
        }
    }
    rowIdx = gBehaviourWorkState->unk24;
    if (child != NULL && controller->unk34 < 3 && gActorGlobalState.bossFightPhase == 4) {
        playerStateQueueCallback(0x33, gCurrentActor, 0);
    }
    if (controller->unk34 < 3 && gCurrentActor->state == 2 && gActorGlobalState.bossFightPhase == 5) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1CA, 0xFF, 0x7F, 0xA);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x209, 0xFF, 0x7F, 0xA);
        gCurrentActor->speedXZ = 0.0f;
        gCurrentActor->state = 0x14;
        gCurrentActor->accelY = -40.0f;
        gCurrentActor->speedY = 400.0f;
    }
    if (playerIsDamageOrKnockbackState() != 0) {
        gCurrentActor->interactionType = 1;
    } else {
        gCurrentActor->interactionType = 2;
    }
    switch (gCurrentActor->state) {
    case 20:
        gCurrentActor->roll = (gCurrentActor->roll - 0xC8) & 0xFFF;
        if ((gCurrentActor->contactFlags & 1) && gCurrentActor->speedY <= 0.0f) {
            gCurrentActor->state = 2;
            gCurrentActor->roll = 0;
        }
        break;
    case 0:
        if (child != NULL && child->unk1C == 0) {
            gCurrentActor->state = gCurrentActor->state + 1;
            gCurrentActor->unk155 = 0;
            gCurrentActor->contactFlags |= 0x200;
        }
        break;
    case 1:
        if (controller->unk34 == 2) {
            if (gCurrentMap == 0x52) {
                actorSetTargetSpeed(gCurrentActor, 0x10E);
            } else {
                actorSetTargetSpeed(gCurrentActor, 0xAA);
            }
            gBehaviourWorkState->unk35 = 0xA;
            actorScriptStart(gCurrentActor, 0x282);
            gCurrentActor->state = gCurrentActor->state + 1;
            break;
        }
    case 2:
        actorApproachTargetSpeed(0);
        dx = gCurrentActor->x - D_807FDCA0->entries[gBehaviourWorkState->unk25].x;
        dz = gCurrentActor->z - D_807FDCA0->entries[gBehaviourWorkState->unk25].z;
        dist = sqrtf(dz * dz + dx * dx);
        if (dist < D_807FDCA0->entries[gBehaviourWorkState->unk25].radius) {
            fv1 = gCurrentActor->y;
            if (D_807FDCA0->entries[gBehaviourWorkState->unk25].y < fv1) {
                dist = fv1 - D_807FDCA0->entries[gBehaviourWorkState->unk25].y;
            } else {
                dist = -(fv1 - D_807FDCA0->entries[gBehaviourWorkState->unk25].y);
            }
            if (dist < 80.0f) {
                if (gBehaviourWorkState->unk25 < D_807FDCA0->entryCount - 1) {
                    if (D_807FDCA0->entries[gBehaviourWorkState->unk25].height == 0) {
                        actorScriptStart(gCurrentActor, 0x283);
                        gCurrentActor->state = gCurrentActor->state + 1;
                    }
                    if (gBehaviourWorkState->unk25 == routeRows[rowIdx].unk0) {
                        gCurrentActor->accelY = routeRows[rowIdx].unk4;
                        gBehaviourWorkState->unk24 = gBehaviourWorkState->unk24 + 1;
                    }
                    gBehaviourWorkState->unk25++;
                }
            }
        }
        ang16 = angU = (s32)(mathAtan2(-dx, -dz) * 4096.0 / 6.2831854820251465);
        mathAngleStepToward(&gCurrentActor->yaw, (angU + angU - gCurrentActor->moveYaw) & 0xFFF, 0x32);
        mathAngleStepToward(&gCurrentActor->moveYaw, ang16, 0xF);
        if (gBehaviourWorkState->unk25 == routeRows[gBehaviourWorkState->unk24].unk0 && routeRows[gBehaviourWorkState->unk24].unk8 == 2 && controller->unk34 == 3) {
            if (controller->unk36 == 1) {
                gCurrentActor->state = 0xA;
            } else {
                gCurrentActor->state = 9;
            }
            actorScriptStart(gCurrentActor, 0);
            gCurrentActor->unk155 = 0;
        }
        break;
    case 3:
        actorApproachTargetSpeed(0x200);
        break;
    case 4:
        actorApproachTargetSpeed(0x200);
        gCurrentActor->speedY = 200.0f;
        gCurrentActor->state = gCurrentActor->state + 1;
        break;
    case 5:
        actorApproachTargetSpeed(0x200);
        break;
    case 6:
        if (gBehaviourWorkState->unk2E != 0) {
            gBehaviourWorkState->unk2E = gBehaviourWorkState->unk2E - 1;
        } else if (gCurrentActor->hasArcBounds != 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xFF, 0x46, 0x7F, 2);
            gBehaviourWorkState->unk2E = 0x14;
        }
        if (gBehaviourWorkState->unk25 == routeRows[gBehaviourWorkState->unk24].unk0 && routeRows[gBehaviourWorkState->unk24].unk8 == 1) {
            fv1 = (f32)(gCurrentActor->moveYaw - gCurrentActor->yaw);
            if (fv1 > 2048.0f) {
                fv1 -= 4096.0f;
            }
            if (fv1 < -2048.0f) {
                fv1 += 4096.0f;
            }
            if (fv1 > 50.0f) {
                fv1 = 50.0f;
            }
            if (fv1 < -50.0f) {
                fv1 = -50.0f;
            }
            gBehaviourWorkState->timer = (s32)((f32)gBehaviourWorkState->timer + fv1);
            gBehaviourWorkState->timer = (s32)(gBehaviourWorkState->timer - gBehaviourWorkState->timer * 0.3);
        } else {
            if ((gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1)) {
                actorScriptStart(gCurrentActor, 0x285);
                gCurrentActor->accelY = -20.0f;
            }
            fv1 = (f32)(gCurrentActor->moveYaw - gCurrentActor->floorSlopeYaw);
            if (fv1 > 2048.0f) {
                fv1 -= 4096.0f;
            }
            if (fv1 < -2048.0f) {
                fv1 += 4096.0f;
            }
            gBehaviourWorkState->timer = (s32)(gBehaviourWorkState->timer + (fv1 * gCurrentActor->speedXZ) / 8000.0);
            if (gBehaviourWorkState->timer > 500) {
                gBehaviourWorkState->timer = 500;
            }
            if (gBehaviourWorkState->timer < -500) {
                gBehaviourWorkState->timer = -500;
            }
        }
        gCurrentActor->yaw = (gCurrentActor->yaw + gBehaviourWorkState->timer) & 0xFFF;
        raceOpponentFollowWaypoints();
        break;
    case 7:
        if (gCurrentMap == 0xE) {
            actorSetTargetSpeed(gCurrentActor, 0xB4);
        }
        raceOpponentFollowWaypoints();
        break;
    case 8:
        gCurrentActor->state = 2;
        gCurrentActor->yaw = gCurrentActor->moveYaw;
        break;
    case 9:
        gBehaviourWorkState->unk35 = 8;
        actorSetTargetSpeed(gCurrentActor, 0);
        actorApproachTargetSpeed(0x200);
        if (gCurrentActor->unk155 == 0) {
            actorScriptStart(gCurrentActor, 0x287);
            gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
        }
        break;
    case 10:
        x = gCurrentActor->unk155;
        switch (x) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            gBehaviourWorkState->unk35 = 8;
            gCurrentActor->unk155 = 1;
            break;
        case 1:
            if (gCurrentActor->speedXZ == 0.0f) {
                gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
            }
            break;
        case 2:
            gBehaviourWorkState->unk35 = 0;
            actorScriptStart(gCurrentActor, 0x288);
            gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
            break;
        }
        actorApproachTargetSpeed(0x200);
        break;
    }
    switch (controller->unk34) {
    case 0:
        y = controller->unk35;
        if (y) {} // FAKE: dead test, steers y/sel copy order
        sel = controller->unk35;
        if (sel) {} // FAKE: dead test, steers y/sel copy order
        switch (sel) {
        case 0:
            if (gCurrentActor->flags & 0x02000000) {
                controller->unk35 = controller->unk35 + 1;
                y = controller->unk35;
            }
            break;
        case 1:
            if (!(gCurrentActor->flags & 0x02000000)) {
                camResumePath();
                controller->unk35 = controller->unk35 + 1;
                y = controller->unk35;
            }
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                controller->unk35 = controller->unk35 + 1;
            }
            y = controller->unk35;
            break;
        }
        if (y < 3) {
            raceSetIntroCutscenePhase(kid);
        }
        break;

    case 1:
        if (controller->unk35 == 0) {
            slotQueueUpdate(0xB, 1, 0);
            controller->unk35 = controller->unk35 + 1;
        }
        break;
    case 3:
        if (controller->unk35 == 0) {
            flag = 0x55;
            if (gPrimaryPlayerActor->contactFlags & 0x200) {
                flag = 0x56;
            }
            playerStateQueueCallback(flag, NULL, 0);
            controller->unk35 = controller->unk35 + 1;
        }
        break;
    case 4:
        if (controller->unk35 == 0) {
            slotQueueCancel(0xB, 0);
            controller->unkD0 = 0;
            if (flagGet(config->unk18.h.rewardFlag, 0) == 0) {
                tmp = D_8002FB94[raceCheckLapCompletionThreshold(controller, config->unk4, config->requiredCoins)];
                camStartPath(gCurrentActor, tmp, 1);
                currentActorClearFlag();
            } else {
                mapCheckAutoTransition();
            }
            controller->unk35 = controller->unk35 + 1;
        }
        break;
    case 5:
        tmp = controller->unk35;
        switch (tmp) {
        case 0:
            if (flagGet(config->unk18.h.rewardFlag, 0) == 0) {
                sfxStopSlotSound(gActivePlayerActor, 0);
                playerStateQueueCallback(0x55, NULL, 0);
                gCurrentActor->speedXZ = 0.0f;
                if (raceCheckCoinRequirement(controller, config) != 0) {
                    gCurrentActor->state = 0xA;
                    gCurrentActor->unk155 = 0;
                } else {
                    gCurrentActor->state = 9;
                    gCurrentActor->unk155 = 0;
                }
            }
            controller->unk35 = controller->unk35 + 1;
            break;
        case 1:
            if (gCurrentActor->flags & 0x02000000) {
                controller->unk35 = tmp + 1;
            }
            break;
        case 2:
            if (!(gCurrentActor->flags & 0x02000000)) {
                camResumePath();
                if (raceCheckCoinRequirement(controller, config) == 0) {
                    controller->unk35 = 4;
                }
                controller->unk35 = controller->unk35 + 1;
                gCurrentActor->unk15F = 0;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                if (gCurrentMap == 0xE) {
                    csModelStateSetFirstByte(0x48, 0xA);
                } else {
                    csModelStateSetFirstByte(1, 0xA);
                }
                controller->unk35 = controller->unk35 + 1;
            }
            break;
        case 4:
            if (flagGet(config->unk18.h.rewardFlag, 0) != 0) {
                controller->unk35 = controller->unk35 + 1;
            }
            break;
        case 5:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                if (flagGet(config->unk18.h.rewardFlag, 0) != 0) {
                    mapCheckAutoTransition();
                } else {
                    hudSpawnTextScreen(1);
                }
                controller->unk35 = controller->unk35 + 1;
            }
            break;
        }
        break;
    }
    actorApplyGravity();
    actorStepPhysics(gCurrentActor, gCurrentActor->moveYaw, gCurrentActor->moveYaw);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0xE, 0xE, 1, 0x96, 0x78, 0, 1.0f);
    if (controller->unk34 == 2) {
        raceUpdateLapAndWaypointTracker(controller);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
