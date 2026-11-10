#include "common.h"
#include "actor.h"
#define PROTO_SKIP_func_80711F90 // FAKE: callee prototype steer
#define PROTO_SKIP_mapGetHubWorldIndex // FAKE: callee prototype steer
#define PROTO_SKIP_mapSetTransitionExtraCounter // FAKE: callee prototype steer
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

extern s32 gFrameCounter;
extern Actor *gCurrentActor;
extern u8 D_807FC621;
extern u8 D_807FC622;
extern u8 D_807501C0[][3];
extern LightPosEntry D_80750194[];

f32 mathCosF(s16);
f32 mathSinF(s16);

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
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1[3];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 unk21;
} CutsceneActorState;
typedef struct {
    char pad[0x100];
    u32 unk100;
    char pad104[0x1F0 - 0x104];
    u32 stateFlags;
} CutscenePlayerContext;
typedef struct {
    char pad[0x1F0];
    u32 stateFlags;
} CutscenePlayerFlags;
typedef struct {
    char pad[0x4];
    Actor *unk4;
} CutscenePlayerEntry;
typedef struct {
    char pad[0xC4];
    f32 unkC4;
} PlayerActorC4;
struct ActorPlayerPos;

void mapSetTransitionExtraCounter(u8); // FAKE: callee prototype steer
s32 mapGetHubWorldIndex(u8, s32); // FAKE: callee prototype steer
void func_80711F90(f32, s16, f32, s16, f32); // FAKE: callee prototype steer

extern Actor *gCurrentActor;
extern u8 D_807FBDC4;
extern ActorGlobalState gActorGlobalState;
extern s16 D_807FDCBC;
extern s16 D_807FDCB8;
extern s32 gGlobalPauseFlags;
extern void *gPrimaryPlayerActor;
extern CutscenePlayerContext *gActivePlayerState;
extern struct ActorPlayerPos *gPlayerSlots;
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
    f32 pad;
    s16 *eventData;
    s32 sfxVolume;
    s32 pathFlag;
    s16 paramA;
    s16 mode;

    csState = (CutsceneActorState *)gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        csState->unk0 = 0;
        csState->unk1A = -1;
        csState->unk21 = 0;
        lightGetColor(&csState->unkC, &csState->unk10, &csState->unk14, 0);
    }

    for (i = 0; i < D_807FBDC4; i++) {
        eventData = gActorGlobalState.unk278[i];
        switch (gActorGlobalState.unk258[i]) {
        case 0xFF:
            csState->unk1E = 0;
            csState->unk0 = 0xFF;
            break;
        case 0xF:
            lightSetOverrideColor((f64)eventData[0] / 255.0, (f64)eventData[1] / 255.0, (f64)eventData[2] / 255.0);
            break;
        case 0xE:
            csState->unkC = (f64)eventData[0] / 255.0;
            csState->unk10 = (f64)eventData[1] / 255.0;
            csState->unk14 = (f64)eventData[2] / 255.0;
            csState->unk1A = eventData[3];
            break;
        case 0x10:
            csState->unk1C = eventData[3];
            csState->unk1E = csState->unk1C;
            break;
        case 0x1:
            if ((gCurrentMap != 0x30) || !(gActivePlayerState->stateFlags & 0x200000)) {
                csState->unk0 = eventData[0];
                csState->unk1A = eventData[1];
                csState->unk4 = (f64)(f32)eventData[2] / 100.0;
                csState->unk8 = eventData[3];
            }
            break;
        case 0x2:
            if ((gCurrentMap != 0x30) || !(gActivePlayerState->stateFlags & 0x200000)) {
                csState->unk0 = 0xFF;
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
                playerWaypointPathStartLineFromActor(gPrimaryPlayerActor, D_807FDCB8, D_807FDCBC, 0x46);
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
                func_805FF9AC(eventData[0], eventData[1], 0, 0);
                playerWaypointPathStartLineFromActor(gPrimaryPlayerActor, D_807FDCB8, D_807FDCBC, 0x46);
            }
            break;
        case 0x5:
            if (!(gGlobalPauseFlags & 0x400)) {
                mapTransitionExitCurrent(eventData[0], eventData[1]);
                playerWaypointPathStartLineFromActor(gPrimaryPlayerActor, D_807FDCB8, D_807FDCBC, 0x46);
            }
            break;
        case 0x6:
            gActivePlayerState->unk100 = 1;
            playerRespawnResetPhysics(eventData[0]);
            break;
        case 0x7:
            if (!(gGlobalPauseFlags & 0x400)) {
                func_805FF9AC(eventData[0], eventData[1], eventData[2], 2);
                playerWaypointPathStartLineFromActor(gPrimaryPlayerActor, D_807FDCB8, D_807FDCBC, 0x46);
            }
            break;
        case 0x8:
            if (!(gGlobalPauseFlags & 0x400)) {
                mapTransitionToPreviousOrExit();
                playerWaypointPathStartLineFromActor(gPrimaryPlayerActor, D_807FDCB8, D_807FDCBC, 0x46);
            }
            break;
        case 0x19:
            mapTransitionToMenuOrPrevious();
            break;
        case 0x9:
            mapSetTransitionExtraCounter(((u8 *)eventData)[1]);
            break;
        case 0xA:
            ((CutscenePlayerFlags *)((CutscenePlayerEntry *)gPlayerSlots)->unk4->customState)->stateFlags |= 0x40000800;
            break;
        case 0xB:
            mapRequestTransition(D_80744700[mapGetHubWorldIndex(gCurrentWorldId, 0)], D_8076A0AC);
            playerWaypointPathStartLineFromActor(gPrimaryPlayerActor, D_807FDCB8, D_807FDCBC, 0x46);
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
            if (((Actor *)gPrimaryPlayerActor)->speedXZ > 250.0f) {
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
            ((PlayerActorC4 *)gActivePlayerActor)->unkC4 = (f64)eventData[0] / 10.0;
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
            ((CutscenePlayerFlags *)((CutscenePlayerEntry *)gPlayerSlots)->unk4->customState)->stateFlags |= 0x80000000;
            break;
        case 0x1B:
            mapChunkSetFlagBit3(eventData[1]);
            break;
        }
    }

    if (csState->unk1E != 0) {
        csState->unk1E--;
        pad = (f32)csState->unk1E / (f32)csState->unk1C;
        lightLerpColors(csState->unkC, csState->unk10, csState->unk14, pad, csState->unk1A);
        if (csState->unk1E == 0) {
            lightSetTargetColor(csState->unkC, csState->unk10, csState->unk14, csState->unk1A);
        }
    }

    switch (csState->unk0) {
    case 0x6:
        func_80711BD0(csState->unk4, csState->unk8, csState->unk1A, 4);
        break;
    case 0x7:
        func_80711BD0(csState->unk4, csState->unk8, csState->unk1A, 5);
        break;
    case 0x5:
        func_80711BD0(csState->unk4, csState->unk8, csState->unk1A, 3);
        break;
    case 0x1:
        func_80711950(csState->unk4, csState->unk8, csState->unk1A);
        break;
    case 0x4:
        func_80711F90(csState->unk4, csState->unk8, 1.0f, csState->unk1A, 4.0f);
        break;
    case 0x3:
        if (((randomNonNegative() >> 15) % 50) == 15) {
            D_807FC620 = 1;
        }
        /* fallthrough */
    case 0x2:
        if (csState->unk21 != 0) {
            csState->unk21--;
        }
        if (D_807FC620 != 0) {
            csState->unk18 = 0x28;
            D_807FC620 = 0;
        }
        if (csState->unk18 != 0) {
            if ((csState->unk18 == 0x28) || (((randomNonNegative() >> 15) % 10) == 5)) {
                lightSetColor(1.0f, 1.0f, 1.0f, csState->unk1A);
                if ((D_80750190 == 0) && (csState->unk21 == 0)) {
                    sfxVolume = 0x46;
                    if (gCurrentMap == 0x57) {
                        sfxVolume = 0x2D;
                    }
                    sfxPlayWithRandomPan(0x9C, (u8)sfxVolume, 0x7F, 0x1E, (randomNonNegative() >> 15) % 3);
                    if (gCurrentMap == 0x6F) {
                        csState->unk21 = 0x50;
                    } else {
                        csState->unk21 = 0x32;
                    }
                }
                csState->unk1E = (csState->unk1E >= 5) ? csState->unk1E : 4;
                csState->unk1C = csState->unk1E;
            }
            csState->unk18--;
        }
        func_80711410(csState->unk4, csState->unk8, 1.0f, csState->unk1A, 1.0f);
        break;
    case 0xFF:
        if (effectSpritePoolFadeOut() != 0) {
            csState->unk0 = 0;
        }
        break;
    }

    actorUpdateEntryEmitters();
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
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1[3];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19[3];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
} Actor174;


void func_8068B830(s16 stateVal, s16 pct, s16 timer) {
    Actor *actor;
    Actor174 *actorState;

    actorFindActiveByType(0xC, &actor);
    actorState = (Actor174 *)actor->customState;
    actorState->unk0 = stateVal;
    actorState->unk4 = (f64)(f32)pct / 100.0;
    actorState->unk8 = timer;
}

void enemyAggroSetIntensityBB(f32 intensity) {
    Actor *actor;
    Actor174 *actorState;

    actorFindActiveByType(0xC, &actor);
    actorState = (Actor174 *)actor->customState;
    actorState->unkC = intensity;
    actorState->unk10 = intensity;
    actorState->unk14 = intensity;
    if (actorState->unk18 == 0) {
        actorState->unk1C = 1;
        actorState->unk1E = actorState->unk1C;
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

    for (i = 0; i < D_807FBDC4; i++) {
        ptr = gActorGlobalState.unk278[i];
        if (gActorGlobalState.unk258[i] == 1) {
            csModelStateSetFirstByte(ptr[0], ptr[1]);
        }
    }
    func_8062BAE4();
}

void func_8068B9B4(void) {
    s32 i;
    s16 *ptr;

    for (i = 0; i < D_807FBDC4; i++) {
        ptr = gActorGlobalState.unk278[i];
        if (gActorGlobalState.unk258[i] == 1) {
            actorListDispatchEvent(ptr[1], ptr);
        }
    }
}

typedef struct {
    char pad[0x104];
    Actor *unk104;
    char pad108[0x1F0 - 0x108];
    u32 stateFlags;
} Actor174Player;

typedef struct ActorPlayerPos {
    char pad[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    char pad21C[0xC];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
} ActorPlayerPos;

extern ActorPlayerPos *gPlayerSlots;

void func_8068BA2C(void) {
    s32 pad;
    CamState *camState;
    Actor174Player *s1;
    s32 hasEvent3;
    s16 i;
    s16 *ptr;
    s32 flags;

    s1 = gActivePlayerActor->customState;
    hasEvent3 = 0;
    camState = ((Actor *)s1->unk104)->customState;
    for (i = 0; i < gActorGlobalState.unk254; i++) {
        ptr = gActorGlobalState.unk278[i];
        switch ((u32)gActorGlobalState.unk258[i]) {
        case 1:
            flags = (ptr[1] != 0) ? 4 : 0;
            camStartPath(0, ptr[0], flags | 1);
            break;
        case 2:
            func_8072167C(ptr[0], ptr[1], ptr[2], ptr[3]);
            break;
        case 3:
            hasEvent3 = 1;
            if (!(s1->stateFlags & 0x04000000)) {
                s1->stateFlags |= 0x04000000;
            }
            break;
        }
    }
    if (hasEvent3 == 0) {
        s1->stateFlags &= ~0x04000000;
    }
    if (camState->unkAC & 1) {
        lightAdd(gPlayerSlots->unk210, gPlayerSlots->unk214, gPlayerSlots->unk218, gPlayerSlots->unk228, gPlayerSlots->unk22C, gPlayerSlots->unk230, 0.0f, 1, 0xFF, 0xFF, 0xFF);
    }
}

typedef struct {
    char pad[0xE4];
    s16 unkE4;
    s16 unkE6;
    char padE8[0x4];
    s16 unkEC;
} AimActorAngles;

f32 mathSinF(s16);
extern u8 gGameMode;
extern s16 D_807FC624;

void playerCameraUpdateFromTarget(void) {
    void *targetState;
    s16 angleA;
    s16 pad50[1];
    s16 angleDiff;
    f32 angleRad;
    f32 pad44[1];
    f32 stepFactor;
    f32 scaleFactor;
    s16 maxDiff;
    void *player;
    s32 pad30[1];
    f32 pitchRad;
    f32 dx;
    f32 curAngle;
    f32 dz;
    f32 clampedPitch;
    Actor *actor;
    s16 angleB;
    s32 minLimit;
    s16 angleDiffRaw;
    s32 stateVal;
    s32 dd;
    s16 tmpd;
    u8 pad_v1;
    targetState = gCurrentActor->customState;
    angleDiff = 0;
    maxDiff = 0x1E;
    stepFactor = 0.08f;
    scaleFactor = 8.0f;
    player = (void *)((*(u8 *)((u8 *)targetState + 0xFB) * 0x2F0) + (u8 *)gPlayerSlots);
    *(s16 *)((u8 *)player + 0x2CC) = ((AimActorAngles *)gCurrentActor)->unkEC;
    ((AimActorAngles *)gCurrentActor)->unkEC = ((AimActorAngles *)gCurrentActor)->unkE4;
    *(s16 *)((u8 *)player + 0x2CA) = (s16)(s32)*(f32 *)((u8 *)player + 0x214);
    angleRad = mathAngleBetweenPointsRad(*(f32 *)((u8 *)player + 0x218), *(f32 *)((u8 *)player + 0x210), *(f32 *)((u8 *)player + 0x230), *(f32 *)((u8 *)player + 0x228));
    dz = *(f32 *)((u8 *)player + 0x230) - *(f32 *)((u8 *)player + 0x218);
    dx = *(f32 *)((u8 *)player + 0x228) - *(f32 *)((u8 *)player + 0x210);
    pitchRad = mathAngleBetweenPointsRad(0.0f, *(f32 *)((u8 *)player + 0x214), sqrtf((dz * dz) + (dx * dx)), *(f32 *)((u8 *)player + 0x22C)) + 3.1415927f;
    clampedPitch = pitchRad;
    if (pitchRad > 6.2831855f) {
        clampedPitch = pitchRad - 6.2831855f;
    }
    if (clampedPitch > 3.1415927f) {
        clampedPitch = 3.1415927f - (clampedPitch - 3.1415927f);
    }
    *(f32 *)((u8 *)player + 0x2D4) = 6.2831855f - angleRad;
    *(f32 *)((u8 *)player + 0x2D8) = 6.2831855f - clampedPitch;
    playerGetCharacterIndex(*(u8 *)((u8 *)targetState + 0xFB));
    angleA = mathAngleBetweenPoints2D(*(f32 *)((u8 *)player + 0x210), *(f32 *)((u8 *)player + 0x218), *(f32 *)((u8 *)player + 0x228), *(f32 *)((u8 *)player + 0x230));
    camUpdate(gCurrentActor, (u8 *)player + 0x210, (u8 *)player + 0x214, (u8 *)player + 0x218, (u8 *)player + 0x228, (u8 *)player + 0x22C, (u8 *)player + 0x230, (u8 *)player + 0x240, (u8 *)player + 0x244, (u8 *)player + 0x248);
    angleB = mathAngleBetweenPoints2D(*(f32 *)((u8 *)player + 0x210), *(f32 *)((u8 *)player + 0x218), *(f32 *)((u8 *)player + 0x228), *(f32 *)((u8 *)player + 0x230));
    if (gPrimaryPlayerActor != *(Actor **)targetState) {
        return;
    }
    if ((gCurrentMap == 0x1F) || (gCurrentMap == 0x33)) {
        if (D_807FC624 && D_807FC624) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        ((AimActorAngles *)gCurrentActor)->unkE4 = (s16)(s32)(mathSinF(D_807FC624) * 100.0f);
        if (gCurrentMap == 0x1F) {
            if (D_807FC624 < 0x1E) {
                sfxPlayOnFreeSlot(0x15, 0x7FFF, 64.0f, 1.0f, 10, 128);
            }
            if ((D_807FC624 >= 0x800) && (D_807FC624 < 0x81E)) {
                sfxPlayOnFreeSlot(0x14, 0x7FFF, 64.0f, 1.0f, 10, 128);
            }
        }
        if (gGameMode && gGameMode) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        tmpd = D_807FC624 + 0x1E;
        tmpd &= 0xFFF;
        D_807FC624 = tmpd;
        return;
    }
    if (gGameMode != 1) {
            dd = 0;  // FAKE: lengthens dd's live range so its priority drops below the B variable (angleB gets a1)
            stateVal = (*(Actor **)targetState)->state;
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
                dd = angleA - angleB;
                angleB = dd;
                angleDiffRaw = dd;
                if (angleDiffRaw >= 0x801) {
                    angleDiff = angleDiffRaw - 0x1000;
                } else {
                    angleDiff = angleB;
                    if (angleDiffRaw < -0x800) {
                        angleDiff = (u16)angleDiffRaw + 0x1000; // FAKE: redundant (u16) burns one ugen ring temp
                    }
                }
                break;
            }
            if (dd) {}  // FAKE: dead read of dd after the switch (priority steer)
            minLimit = -maxDiff;
            stateVal = (minLimit < angleDiff) ? angleDiff : minLimit;
            stateVal = (stateVal < maxDiff) ? ((minLimit < angleDiff) ? angleDiff : minLimit) : maxDiff;
            curAngle = (f32)((AimActorAngles *)gCurrentActor)->unkE4;
            ((AimActorAngles *)gCurrentActor)->unkE4 = (s16)(s32)(((((f32)stateVal * scaleFactor) - curAngle) * stepFactor) + curAngle);
    }
}
