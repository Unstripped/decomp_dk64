#include "common.h"
#include "actor.h"
#include "sched.h"
#define PROTO_SKIP_mapGetHubWorldIndex // FAKE: callee prototype steer
#include "proto/global/109660.h"
#include "proto/global/10E1D0.h"
#include "proto/global/114270.h"
#include "proto/global/117190.h"
#include "proto/global/126260.h"
#include "proto/global/1295B0.h"
#include "proto/global/1332B0.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/201B0.h"
#include "proto/global/2F550.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/55B20.h"
#include "proto/global/5E2F0.h"
#include "proto/global/68EA0.h"
#include "proto/global/699B0.h"
#include "proto/global/69E60.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/8D3E0.h"
#include "proto/global/8F4B0.h"
#include "proto/global/CC800.h"
#include "proto/global/F56F0.h"


void actorSpawnInitialSet(void) {
    actorSpawn(0xA, 0);
    actorSpawn(0xB, 0);
    actorSpawn(0xC, 0);
    actorSpawn(0xD, 0);
    actorSpawn(0xE, 0);
    actorSpawn(0xF, 0);
}

void actorVolumeTriggersUpdate(void) {
    volumeTriggerUpdateAll();
}

void actorSpawnNodesUpdate(void) {
    func_80727678();
    spawnNodesUpdate();
}
typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
} LightPosEntry;

extern Actor *gCurrentActor;
extern u8 D_807FC621;
extern u8 D_807FC622;
extern u8 D_807501C0[][3];
extern LightPosEntry D_80750194[];


void lightUpdateFromActorLighting(u8 *outR, u8 *outG, u8 *outB) {
    f32 pad;
    f32 dirX;
    f32 dirY;
    f32 dirZ;
    s32 lightIndex;
    u8 idx;

    if (gCurrentActor->flags & 4) {
        switch (D_807FC622) {
        case 0:
            *outR = 0xFF;
            *outG = 0xFF;
            *outB = 0xFF;
            break;
        case 1:
            if (!(gFrameCounter & 0xF)) {
                goto set_color;
            }
            break;
        case 2:
            if (!(gFrameCounter & 3)) {
set_color:
                idx = (u32)(mathCosF(gFrameCounter * 200) * 4.0f + 4.0f);
                *outR = D_807501C0[idx][0];
                *outG = D_807501C0[idx][1];
                *outB = D_807501C0[idx][2];
            }
            break;
        }

        if ((D_807FC621 & 0x80) && (lightIndex = D_807FC621 & 0x7F)) {
            D_807FC621 = lightIndex;
            dirX = (f32)D_80750194[D_807FC621 - 1].unk8;
            dirY = (f32)D_80750194[D_807FC621 - 1].unkA;
            dirZ = (f32)D_80750194[D_807FC621 - 1].unkC;
            if (D_807FC622 != 0) {
                dirX += 80.0f * mathSinF(gFrameCounter * 400);
                dirZ += 80.0f * mathCosF(gFrameCounter * 200);
            }
            lightSetFovAngles((f32)(u32)D_80750194[D_807FC621 - 1].unk0, (f32)(u32)D_80750194[D_807FC621 - 1].unk1);
            lightAdd((f32)D_80750194[D_807FC621 - 1].unk2, (f32)D_80750194[D_807FC621 - 1].unk4, (f32)D_80750194[D_807FC621 - 1].unk6, dirX, dirY, dirZ, 0.0f, 1, *outR, *outG, *outB);
        }
    }
}

extern s8 D_8074452C;
extern u16 D_80744734[];
extern s32 gCurrentMap;

s32 cutsceneTriggerCheck(s16 cutsceneId) {
    s16 entryCutscene;
    s32 found;
    s32 i;
    s16 flagId;
    s32 spawnType;
    s32 extraParam;

    entryCutscene = -1;
    i = 0;
    found = 0;
    while (!found && i < 8) {
        if (gCurrentMap == D_80744734[i]) {
            found = 1;
        } else {
            i++;
        }
    }

    if (found) {
        flagId = i + 0x1C5;
        if (flagGet(flagId, 0) == 0) {
            extraParam = 0;
            switch (cutsceneId) {
            case 0x7:
                spawnType = 0x1C;
                entryCutscene = 0xF;
                break;
            case 0x26:
                spawnType = 0x1C;
                entryCutscene = 0x10;
                break;
            case 0x1A:
                spawnType = 0x1C;
                entryCutscene = 0x11;
                break;
            case 0x1E:
                spawnType = 0x1C;
                entryCutscene = 0x12;
                break;
            case 0x30:
                spawnType = 0x1C;
                entryCutscene = 0x13;
                break;
            case 0x48:
                spawnType = 0x1C;
                entryCutscene = 0x14;
                break;
            case 0x57:
                spawnType = 0x1C;
                entryCutscene = 0x15;
                extraParam = 0x15;
                break;
            case 0x11:
                spawnType = 0x1C;
                entryCutscene = 0x16;
                break;
            }
            if (entryCutscene != -1) {
                flagSet(flagId, 1, 0);
                if (D_8074452C != 0) {
                    mapRequestTransition(cutsceneId, extraParam);
                    return 1;
                }
                menuTransitionToMap(spawnType, entryCutscene);
                return 1;
            }
        }
    }
    return 0;
}

typedef struct {
    /* 0x00 */ u8 weatherMode;
    /* 0x01 */ u8 unk1[3];
    /* 0x04 */ f32 density;
    /* 0x08 */ s16 windAngle;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ f32 colorR;
    /* 0x10 */ f32 colorG;
    /* 0x14 */ f32 colorB;
    /* 0x18 */ u8 flashTimer;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ s16 mapChunk;
    /* 0x1C */ s16 fadeDuration;
    /* 0x1E */ s16 fadeTimer;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 sfxCooldown;
} CutsceneActorState;

s32 mapGetHubWorldIndex(u8, s32); // FAKE: callee prototype steer

extern Actor *gCurrentActor;
extern s16 gVolumeTriggerFiredZ;
extern s16 gVolumeTriggerFiredX;
extern Actor *gPrimaryPlayerActor;
extern PlayerState *gActivePlayerState;
extern PlayerStruct *gPlayerSlots;
extern u16 D_80744700[];
extern u8 gCurrentWorldId;
extern s32 D_8076A0AC;
extern Actor *gActivePlayerActor;
extern u8 D_807FC621;
extern u8 D_807FC622;
extern u16 D_807ECD48;
extern u16 D_8076A0A6;
extern u8 D_80750190;
extern u8 D_807FC620;

void actorCutsceneDispatchEvents(void) {
    CutsceneActorState *csState;
    s32 i;
    f32 lerpT;
    s16 *eventData;
    s32 sfxVolume;
    s32 pathFlag;
    s16 paramA;
    s16 mode;

    csState = (CutsceneActorState *)gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        csState->weatherMode = 0;
        csState->mapChunk = -1;
        csState->sfxCooldown = 0;
        lightGetColor(&csState->colorR, &csState->colorG, &csState->colorB, 0);
    }

    for (i = 0; i < gActorGlobalState.volumeTriggerQueueCount; i++) {
        eventData = gActorGlobalState.volumeTriggerQueueId[i];
        switch (gActorGlobalState.volumeTriggerQueueOp[i]) {
        case 0xFF:
            csState->fadeTimer = 0;
            csState->weatherMode = 0xFF;
            break;
        case 0xF:
            lightSetOverrideColor((f64)eventData[0] / 255.0, (f64)eventData[1] / 255.0, (f64)eventData[2] / 255.0);
            break;
        case 0xE:
            csState->colorR = (f64)eventData[0] / 255.0;
            csState->colorG = (f64)eventData[1] / 255.0;
            csState->colorB = (f64)eventData[2] / 255.0;
            csState->mapChunk = eventData[3];
            break;
        case 0x10:
            csState->fadeDuration = eventData[3];
            csState->fadeTimer = csState->fadeDuration;
            break;
        case 0x1:
            if ((gCurrentMap != 0x30) || !(gActivePlayerState->stateFlags & 0x200000)) {
                csState->weatherMode = eventData[0];
                csState->mapChunk = eventData[1];
                csState->density = (f64)(f32)eventData[2] / 100.0;
                csState->windAngle = eventData[3];
            }
            break;
        case 0x2:
            if ((gCurrentMap != 0x30) || !(gActivePlayerState->stateFlags & 0x200000)) {
                csState->weatherMode = 0xFF;
            }
            break;
        case 0x3:
            if (!(gGlobalPauseFlags & 0x400)) {
                if (eventData[2] != 0) {
                    transitionSetState(2);
                    screenSetTransitionFadeType(0);
                }
                paramA = eventData[0];
                if (paramA == 0x11) {
                    if (cutsceneTriggerCheck(paramA) == 0) {
                        mapRequestTransition(eventData[0], eventData[1]);
                    }
                } else {
                    mapRequestTransition(paramA, eventData[1]);
                }
                playerWaypointPathStartLineFromActor(gPrimaryPlayerActor, gVolumeTriggerFiredX, gVolumeTriggerFiredZ, 0x46);
            }
            break;
        case 0x15:
            if (!(gGlobalPauseFlags & 0x400)) {
                mapRequestTransitionFast(eventData[0], eventData[1]);
            }
            break;
        case 0x4:
            if (!(gGlobalPauseFlags & 0x400)) {
                mode = eventData[2];
                if (mode != 0) {
                    if (mode == 1) {
                        transitionSetState(2);
                    }
                    screenSetTransitionFadeType(0);
                }
                mapSaveSlotAndTransition(eventData[0], eventData[1], 0, 0);
                playerWaypointPathStartLineFromActor(gPrimaryPlayerActor, gVolumeTriggerFiredX, gVolumeTriggerFiredZ, 0x46);
            }
            break;
        case 0x5:
            if (!(gGlobalPauseFlags & 0x400)) {
                mapTransitionExitCurrent(eventData[0], eventData[1]);
                playerWaypointPathStartLineFromActor(gPrimaryPlayerActor, gVolumeTriggerFiredX, gVolumeTriggerFiredZ, 0x46);
            }
            break;
        case 0x6:
            gActivePlayerState->respawnTimer = 1;
            playerRespawnResetPhysics(eventData[0]);
            break;
        case 0x7:
            if (!(gGlobalPauseFlags & 0x400)) {
                mapSaveSlotAndTransition(eventData[0], eventData[1], eventData[2], 2);
                playerWaypointPathStartLineFromActor(gPrimaryPlayerActor, gVolumeTriggerFiredX, gVolumeTriggerFiredZ, 0x46);
            }
            break;
        case 0x8:
            if (!(gGlobalPauseFlags & 0x400)) {
                mapTransitionToPreviousOrExit();
                playerWaypointPathStartLineFromActor(gPrimaryPlayerActor, gVolumeTriggerFiredX, gVolumeTriggerFiredZ, 0x46);
            }
            break;
        case 0x19:
            mapTransitionToMenuOrPrevious();
            break;
        case 0x9:
            mapSetTransitionExtraCounter(eventData[0]);
            break;
        case 0xA:
            ((PlayerState *)gPlayerSlots->actor->customState)->stateFlags |= 0x40000800;
            break;
        case 0xB:
            mapRequestTransition(D_80744700[mapGetHubWorldIndex(gCurrentWorldId, 0)], D_8076A0AC);
            playerWaypointPathStartLineFromActor(gPrimaryPlayerActor, gVolumeTriggerFiredX, gVolumeTriggerFiredZ, 0x46);
            break;
        case 0xC:
            if (eventData[1] != 0) {
                pathFlag = 0;
            } else {
                pathFlag = 0x8000;
            }
            playerWaypointPathStartPacked(gPrimaryPlayerActor, 0, eventData[0] + pathFlag, 0);
            break;
        case 0xD:
            if (gPrimaryPlayerActor->speedXZ > 250.0f) {
                sfxPlayFromActorWithAltitudeCheck(gPrimaryPlayerActor, eventData[0], 0xFF, 0x7F, 0x1E);
            }
            break;
        case 0x16:
            sfxAllocateChannel(eventData[0], 1.0f);
            break;
        case 0x17:
            sfxStopChannel(eventData[0], 0);
            break;
        case 0x11:
            gActivePlayerActor->accelY = (f64)eventData[0] / 10.0;
            break;
        case 0x12:
            gActivePlayerActor->contactFlags |= 0x200;
            break;
        case 0x13:
            gActivePlayerActor->contactFlags &= ~0x200;
            break;
        case 0x14:
            D_807FC621 = eventData[0];
            D_807FC622 = eventData[1];
            if (D_807FC622 != 0) {
                commandSetColor(0x35, 0x18, 0x28);
                commandSetParameters(0x320, 0x82, 0, 0x64, 0x64, 0x64);
            }
            break;
        case 0x18:
            mapTransitionToWorldHub(mapGetHubWorldIndex(gCurrentWorldId, 0));
            break;
        case 0x1C:
            if (D_80744700 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            D_8076A0A6 = D_807ECD48;
            break;
        case 0x1A:
            ((PlayerState *)gPlayerSlots->actor->customState)->stateFlags |= 0x80000000;
            break;
        case 0x1B:
            mapChunkSetFlagBit3(eventData[1]);
            break;
        }
    }

    if (csState->fadeTimer != 0) {
        csState->fadeTimer--;
        lerpT = (f32)csState->fadeTimer / (f32)csState->fadeDuration;
        lightLerpColors(csState->colorR, csState->colorG, csState->colorB, lerpT, csState->mapChunk);
        if (csState->fadeTimer == 0) {
            lightSetTargetColor(csState->colorR, csState->colorG, csState->colorB, csState->mapChunk);
        }
    }

    switch (csState->weatherMode) {
    case 0x6:
        func_80711BD0(csState->density, csState->windAngle, csState->mapChunk, 4);
        break;
    case 0x7:
        func_80711BD0(csState->density, csState->windAngle, csState->mapChunk, 5);
        break;
    case 0x5:
        func_80711BD0(csState->density, csState->windAngle, csState->mapChunk, 3);
        break;
    case 0x1:
        func_80711950(csState->density, csState->windAngle, csState->mapChunk);
        break;
    case 0x4:
        func_80711F90(csState->density, csState->windAngle, 1.0f, csState->mapChunk, 4.0f);
        break;
    case 0x3:
        if (((randomNonNegative() >> 15) % 50) == 15) {
            D_807FC620 = 1;
        }
        /* fallthrough */
    case 0x2:
        if (csState->sfxCooldown != 0) {
            csState->sfxCooldown--;
        }
        if (D_807FC620 != 0) {
            csState->flashTimer = 0x28;
            D_807FC620 = 0;
        }
        if (csState->flashTimer != 0) {
            if ((csState->flashTimer == 0x28) || (((randomNonNegative() >> 15) % 10) == 5)) {
                lightSetColor(1.0f, 1.0f, 1.0f, csState->mapChunk);
                if ((D_80750190 == 0) && (csState->sfxCooldown == 0)) {
                    sfxVolume = 0x46;
                    if (gCurrentMap == 0x57) {
                        sfxVolume = 0x2D;
                    }
                    sfxPlayWithRandomPan(0x9C, (u8)sfxVolume, 0x7F, 0x1E, (randomNonNegative() >> 15) % 3);
                    if (gCurrentMap == 0x6F) {
                        csState->sfxCooldown = 0x50;
                    } else {
                        csState->sfxCooldown = 0x32;
                    }
                }
                csState->fadeTimer = (csState->fadeTimer >= 5) ? csState->fadeTimer : 4;
                csState->fadeDuration = csState->fadeTimer;
            }
            csState->flashTimer--;
        }
        func_80711410(csState->density, csState->windAngle, 1.0f, csState->mapChunk, 1.0f);
        break;
    case 0xFF:
        if (effectSpritePoolFadeOut() != 0) {
            csState->weatherMode = 0;
        }
        break;
    }

    modelEmittersUpdate();
    particleSpawnPathTrail();
    D_807FC621 |= 0x80;
}


void enemyAggroEnable(void) {
    D_807FC620 = 1;
}

void enemyAggroResetUnk21(void) {
    D_807FC621 = 0;
    D_807FC622 = 0;
}
typedef struct {
    /* 0x00 */ u8 weatherMode;
    /* 0x01 */ u8 unk1[3];
    /* 0x04 */ f32 density;
    /* 0x08 */ s16 windAngle;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ f32 colorR;
    /* 0x10 */ f32 colorG;
    /* 0x14 */ f32 colorB;
    /* 0x18 */ u8 flashTimer;
    /* 0x19 */ u8 unk19[3];
    /* 0x1C */ s16 fadeDuration;
    /* 0x1E */ s16 fadeTimer;
} WeatherActorState;


void func_8068B830(s16 mode, s16 densityPct, s16 windAngle) {
    Actor *actor;
    WeatherActorState *actorState;

    actorFindActiveByType(0xC, &actor);
    actorState = (WeatherActorState *)actor->customState;
    actorState->weatherMode = mode;
    actorState->density = (f64)(f32)densityPct / 100.0;
    actorState->windAngle = windAngle;
}

void enemyAggroSetIntensityBB(f32 intensity) {
    Actor *actor;
    WeatherActorState *actorState;

    actorFindActiveByType(0xC, &actor);
    actorState = (WeatherActorState *)actor->customState;
    actorState->colorR = intensity;
    actorState->colorG = intensity;
    actorState->colorB = intensity;
    if (actorState->flashTimer == 0) {
        actorState->fadeDuration = 1;
        actorState->fadeTimer = actorState->fadeDuration;
    }
}

void enemyAggroDespawnBB(void) {
    Actor *actor;
    u8 *ptr;

    actorFindActiveByType(0xC, &actor);
    ptr = actor->customState;
    *ptr = 0xFF;
}


void func_8068B930(void) {
    s32 i;
    s16 *ptr;

    for (i = 0; i < gActorGlobalState.volumeTriggerQueueCount; i++) {
        ptr = gActorGlobalState.volumeTriggerQueueId[i];
        if (gActorGlobalState.volumeTriggerQueueOp[i] == 1) {
            csModelStateSetFirstByte(ptr[0], ptr[1]);
        }
    }
    func_8062BAE4();
}

void func_8068B9B4(void) {
    s32 i;
    s16 *ptr;

    for (i = 0; i < gActorGlobalState.volumeTriggerQueueCount; i++) {
        ptr = gActorGlobalState.volumeTriggerQueueId[i];
        if (gActorGlobalState.volumeTriggerQueueOp[i] == 1) {
            actorListDispatchEvent(ptr[1], ptr);
        }
    }
}



void func_8068BA2C(void) {
    s32 pad;
    CamState *camState;
    PlayerState *playerState;
    s32 hasEvent3;
    s16 i;
    s16 *ptr;
    s32 flags;

    playerState = gActivePlayerActor->customState;
    hasEvent3 = 0;
    camState = playerState->camActor->customState;
    for (i = 0; i < gActorGlobalState.volumeTriggerQueueCount; i++) {
        ptr = gActorGlobalState.volumeTriggerQueueId[i];
        switch ((u32)gActorGlobalState.volumeTriggerQueueOp[i]) {
        case 1:
            flags = (ptr[1] != 0) ? 4 : 0;
            camStartPath(0, ptr[0], flags | 1);
            break;
        case 2:
            func_8072167C(ptr[0], ptr[1], ptr[2], ptr[3]);
            break;
        case 3:
            hasEvent3 = 1;
            if (!(playerState->stateFlags & 0x04000000)) {
                playerState->stateFlags |= 0x04000000;
            }
            break;
        }
    }
    if (hasEvent3 == 0) {
        playerState->stateFlags &= ~0x04000000;
    }
    if (camState->unkAC & 1) {
        lightAdd(gPlayerSlots->camX, gPlayerSlots->camY, gPlayerSlots->camZ, gPlayerSlots->focusX, gPlayerSlots->focusY, gPlayerSlots->focusZ, 0.0f, 1, 0xFF, 0xFF, 0xFF);
    }
}


extern u8 gGameMode;
extern s16 D_807FC624;

void playerCameraUpdateFromTarget(void) {
    CamState *camState;
    s16 angleA;
    s16 angleB;
    s16 angleDiff;
    f32 angleRad;
    f32 pitchRad;
    f32 stepFactor;
    f32 scaleFactor;
    s16 maxDiff;
    PlayerStruct *player;
    f32 dx;
    f32 dz;
    f32 clampedPitch;
    f32 curAngle;
    s32 stateVal;
    s32 rawDiff;
    s16 angleDiffRaw;
    s32 minLimit;
    s32 clampedDiff;
    s16 fadeTimer;
    camState = gCurrentActor->customState;
    angleDiff = 0;
    maxDiff = 0x1E;
    stepFactor = 0.08f;
    scaleFactor = 8.0f;
    player = &gPlayerSlots[camState->unkFB];
    player->skyRoll = gCurrentActor->unkEC;
    gCurrentActor->unkEC = gCurrentActor->pitch;
    player->camYInt = player->camY;
    angleRad = mathAngleBetweenPointsRad(player->camZ, player->camX, player->focusZ, player->focusX);
    dz = player->focusZ - player->camZ;
    dx = player->focusX - player->camX;
    pitchRad = mathAngleBetweenPointsRad(0.0f, player->camY, sqrtf((dz * dz) + (dx * dx)), player->focusY) + 3.1415927f;
    clampedPitch = pitchRad;
    if (pitchRad > 6.2831855f) {
        clampedPitch = pitchRad - 6.2831855f;
    }
    if (clampedPitch > 3.1415927f) {
        clampedPitch = 3.1415927f - (clampedPitch - 3.1415927f);
    }
    player->bgRotX = 6.2831855f - angleRad;
    player->bgRotY = 6.2831855f - clampedPitch;
    playerGetCharacterIndex(camState->unkFB);
    angleA = mathAngleBetweenPoints2D(player->camX, player->camZ, player->focusX, player->focusZ);
    camUpdate(gCurrentActor, &player->camX, &player->camY, &player->camZ, &player->focusX, &player->focusY, &player->focusZ, &player->upX, &player->upY, &player->upZ);
    angleB = mathAngleBetweenPoints2D(player->camX, player->camZ, player->focusX, player->focusZ);
    if (gPrimaryPlayerActor != camState->unk0) {
        return;
    }
    if ((gCurrentMap == 0x1F) || (gCurrentMap == 0x33)) {
        if (D_807FC624 && D_807FC624) {}  // FAKE: merges the D_807FC624 loads into one uopt candidate whose range holds the mathSinF argument block, so it takes a0 (v1 at 0x167c-0x170c without)
        gCurrentActor->pitch = mathSinF(D_807FC624) * 100.0f;
        if (gCurrentMap == 0x1F) {
            if (D_807FC624 < 0x1E) {
                sfxPlayOnFreeSlot(0x15, 0x7FFF, 64.0f, 1.0f, 10, 128);
            }
            if ((D_807FC624 >= 0x800) && (D_807FC624 < 0x81E)) {
                sfxPlayOnFreeSlot(0x14, 0x7FFF, 64.0f, 1.0f, 10, 128);
            }
        }
        if (gGameMode && gGameMode) {}  // FAKE: extends that D_807FC624 candidate into the fade block (reload at 0x1708 in a0, v0 without); coupled with the test above (removing both costs no more than removing that one)
        fadeTimer = D_807FC624 + 0x1E;
        fadeTimer &= 0xFFF;
        D_807FC624 = fadeTimer;
        return;
    }
    if (gGameMode != 1) {
        rawDiff = 0;  // FAKE: dead store; with the dead read after the switch it spreads rawDiff over the switch blocks (adjsave 2.0 -> 0.8), so angleB is coloured first and gets a1 (a2 at 0x17f4 without)
        stateVal = camState->unk0->state;
        switch (stateVal) {
        case 0x63:
            stepFactor = 0.02f;
            scaleFactor = 15.0f;
            goto calc_angle;
        case 0x7:
        case 0x8:
        case 0x9:
        case 0xA:
        case 0xB:
        case 0xF:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
            maxDiff = 0x64;
            stepFactor = 0.1f;
        case 0x4F:
        case 0x69:
        case 0x6D:
        calc_angle:
            rawDiff = angleA - angleB;
            angleB = rawDiff;
            angleDiffRaw = rawDiff;
            if (angleDiffRaw >= 0x801) {
                angleDiff = angleDiffRaw - 0x1000;
            } else {
                angleDiff = angleB;
                if (angleDiffRaw < -0x800) {
                    angleDiff = (u16)angleDiffRaw + 0x1000; // FAKE: redundant (u16) burns ugen ring temp t4 (target addiu t5,a0,0x1000 at 0x1828; t4 without)
                }
            }
            break;
        }
        if (rawDiff) {}  // FAKE: dead read of rawDiff, pairs with the dead store before the switch (removing both leaves angleB in a2)
        minLimit = -maxDiff;
        clampedDiff = (minLimit < angleDiff) ? angleDiff : minLimit;
        clampedDiff = (clampedDiff < maxDiff) ? ((minLimit < angleDiff) ? angleDiff : minLimit) : maxDiff;
        curAngle = gCurrentActor->pitch;
        gCurrentActor->pitch = (((clampedDiff * scaleFactor) - curAngle) * stepFactor) + curAngle;
    }
}
