#include "common.h"
#include "actor.h"
#include "sched.h"
#include "render.h"
#include "proto/global/10D2D0.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/1295B0.h"
#include "proto/global/133A90.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/16550.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/8CA50.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/E4090.h"
#include "proto/global/EFDC0.h"
#include "proto/global/F56F0.h"
#include "proto/global/F9450.h"
#include "proto/global/FCCD0.h"

extern Actor *gCurrentActor;
extern Actor *gActivePlayerActor;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern PlayerState *gActivePlayerState;
extern s16 gCurrentCharacterIndex;
extern u16 D_807FD63C;


void playerUpdateSoundEffect0(void) {
    playerUpdateCommon(0);
    playerWeaponSpawnMuzzleFlash(gCurrentActor, 0);
}

void playerUpdateSoundEffect2(void) {
    playerUpdateCommon(0);
    playerWeaponSpawnMuzzleFlash(gCurrentActor, 2);
}

void playerUpdateSoundEffect3(void) {
    playerUpdateCommon(0);
    playerWeaponSpawnMuzzleFlash(gCurrentActor, 3);
}

void playerUpdateSoundEffect4(void) {
    playerUpdateCommon(0);
    playerWeaponSpawnMuzzleFlash(gCurrentActor, 4);
}

void playerUpdateSoundEffect6(void) {
    playerUpdateCommon(0);
    playerWeaponSpawnMuzzleFlash(gCurrentActor, 6);
}

void playerUpdateSoundEffect1(void) {
    playerUpdateCommon(0);
    playerWeaponSpawnMuzzleFlash(gCurrentActor, 1);
}

void playerUpdateSoundEffect7(void) {
    actorOrNodeFlags(gCurrentActor, 3, 8);
    playerUpdateCommon(0);
    playerWeaponSpawnMuzzleFlash(gCurrentActor, 7);
}

void playerUpdateSoundEffect5(void) {
    playerUpdateCommon(0);
    playerWeaponSpawnMuzzleFlash(gCurrentActor, 5);
}

extern s16 gPlayerStateFlags[][4];


void playerCheckAndResetCarriedActor(Actor *actor) {
    u8 state = actor->state;
    s16 flags = gPlayerStateFlags[state][0];

    if (flags & 0x200) {
        func_806EAB44(actor, (u8)(state != 2));
    } else if (flags & 0x100) {
        func_806E9964(gActivePlayerState);
    }
}

Actor *actorResolveKillCreditOwner(Actor *actor) {
    Actor *original = actor;

    if (actor == NULL) {
        return actor;
    }
    switch (actor->collisionFlags) {
        case 4:
            actor = actor->parentActor;
            break;
        case 8:
            actor = actor->parentActor;
            break;
    }
    if (actor != NULL && (actor->collisionFlags == 1 || actor->collisionFlags == 2)) {
        return actor;
    }
    return original;
}

void playerSetRecentAttacker(Actor *attacker, PlayerState *state) {
    s32 clear = 0;
    PlayerState *attackerState;

    if (attacker == NULL) {
        clear = 1;
    } else if (attacker->collisionFlags & 1) {
        attackerState = attacker->customState;
        state->attackerPlayerIndex = attackerState->playerIndex;
        state->attackerSpawnNodeId = 0;
    } else if (attacker->collisionFlags & 2) {
        state->attackerPlayerIndex = -1;
        state->attackerSpawnNodeId = spawnNodeIdForActor(attacker);
    } else {
        clear = 1;
    }
    if (clear != 0) {
        gActivePlayerState->hitSourceSpawnNodeId = 0;
        gActivePlayerState->hitSourcePlayerIndex = -1;
    }
    state->attackTimer = 5;
}

void playerRecordHitSource(Actor *player, Actor *source, s32 strength) {
    PlayerState *state = player->customState;
    PlayerState *sourceState;
    s32 bad;
    s32 ok;

    ok = 0;
    bad = 0;
    if (source == NULL) {
        bad = 1;
    } else if (source->collisionFlags == 1) {
        ok = 1;
        sourceState = source->customState;
        state->hitSourcePlayerIndex = sourceState->playerIndex;
        state->hitSourceSpawnNodeId = 0;
    } else if (source->collisionFlags == 2) {
        state->hitSourceSpawnNodeId = spawnNodeIdForActor(source);
        ok = 1;
        state->hitSourcePlayerIndex = -1;
    } else {
        bad = 1;
    }
    if (bad != 0) {
        state->hitSourceSpawnNodeId = 0;
        state->hitSourcePlayerIndex = -1;
    }
    if (ok != 0) {
        state->hitModelId = source->sub4->model->animId;
        state->hitStrength = strength;
    }
}


extern PlayerStruct *gPlayerSlots;


s32 playerHitSourceIsStale(s32 minStrength) {
    s8 idx = gActivePlayerState->hitSourcePlayerIndex;
    s32 ret = 1;
    Actor *actor = NULL;

    if (idx >= 0) {
        actor = gPlayerSlots[idx].actor;
    } else {
        s8 spawnNodeId = gActivePlayerState->hitSourceSpawnNodeId;

        if (spawnNodeId > 0) {
            actor = spawnNodeActivate(spawnNodeId, 0);
        }
    }
    if (actor != NULL && gActivePlayerState->hitModelId == actor->sub4->model->animId && gActivePlayerState->hitStrength >= minStrength) {
        ret = 0;
    }
    return ret;
}

void playerClearStaleHitSource(void) {
    if (playerHitSourceIsStale(-1) != 0) {
        gActivePlayerState->hitSourcePlayerIndex = -1;
        gActivePlayerState->hitSourceSpawnNodeId = 0;
    }
}

void playerClearCarriedItemState(void) {
    gActivePlayerState->unkC8 = -1;
    sfxStopSlotSound(gCurrentActor, 1);
}


extern s32 gGlobalOverlayFlags;
extern u16 D_807FD63A[][0x1A];

void playerCheckAndClearCarriedItem(void) {
    if (gActivePlayerState->unkC8 != -1 && (flagGet(0x179, 0) == 0 || gCurrentActor->floorSlopeFactor != 0.0f || (gGlobalOverlayFlags & 0x800000) || slotQueueGetValue(5, gActivePlayerState->playerIndex) == 0)) {
        playerClearCarriedItemState();
        gActivePlayerState->unkC8 = -1;
        return;
    }
    if (gActivePlayerState->unkC8 != -1) {
        if (D_807FD63A[gCurrentPlayerIndex][0] & 0x4000) {
            if (gActivePlayerState->unkC8 > 0) {
                if (gActivePlayerState->unkC8 < 0x1E && !(gFrameCounter & 3)) {
                    effectSpawnBurst(0);
                }
                gActivePlayerState->unkC8 = gActivePlayerState->unkC8 - 1;
                if (gActivePlayerState->unkC8 == 0x1E) {
                    sfxPlayActorSound(gCurrentActor, 0x104, 0x3C, 1, 1, 0xFF, 1.0f, 0);
                }
            } else if (!(gFrameCounter & 1)) {
                effectSpawnBurst(1);
            }
        } else {
            if (gActivePlayerState->unkC8 == 0 && (gCurrentActor->contactFlags & 1)) {
                gCurrentActor->state = 0x2D;
                gCurrentActor->unk155 = 0;
                slotQueueUpdate(5, 0, 0);
                slotQueueAddValue(5, gActivePlayerState->playerIndex, (s16)-slotQueueGetCountStep(5));
                actorScriptStartByIndex(gCurrentActor, 0x42);
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF2, 0xFF, 0x7F, 0);
                gCurrentActor->speedXZ = 0.0f;
            }
            playerClearCarriedItemState();
        }
    }
}

void playerUpdateSlopeSlidePhysics(void) {
    if ((gCurrentActor->contactFlags & 0x221) == 1) {
        if (gCurrentActor->floorSlopeFactor != 0.0f) {
            if (!(gCurrentActor->prevContactFlags & 1) || gCurrentActor->floorSlopePitch < 0x226 || (gCurrentActor->unk78[0] == 0xC && gCurrentActor->speedXZ > 40.0f)) {
                gActivePlayerState->unkC2 = 0x32;
            }
            gActivePlayerState->unkC2 = gActivePlayerState->unkC2 + 1;
        } else {
            gActivePlayerState->unkC2 = 0;
        }
    }
}

typedef struct PadInputState {
    /* 0x00 */ u8 pad0[0x2A];
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ s8 unk2E;
    /* 0x2F */ s8 unk2F;
    /* 0x30 */ u8 pad30[4];
} PadInputState;

extern PadInputState gPlayerPadState[];


typedef struct PlayerStateFn {
    /* 0x0 */ void (*fn)(void);
    /* 0x4 */ s32 pad4;
} PlayerStateFn;


extern PlayerStateFn gPlayerStateHandlers[];
extern s32 D_8076A090;
extern s32 D_8076A094;
extern s32 D_8076A098;
extern s32 D_807552E4;
extern s32 gCurrentMap;
extern u8 D_80770561;
extern u8 D_807463B8;
extern s16 D_807F5FE4;
extern s16 D_807F5FE6;
extern s16 D_807F5FE8;
extern s16 D_807F5FEA;
extern s32 D_80720020;

void func_80026D40(void *, u8);
f32 sqrtf(f32);

void playerUpdateCommon(s32 mode) {
    f32 dy;
    f32 screenX;
    f32 screenY;
    u8 heavyImpact;
    u8 groundImpact;
    u8 floorType;
    u8 materialType;
    Actor *attacker;
    f32 dz;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    f32 dx;
    f32 projX;
    f32 projY;
    EffectNode *fx;
    s16 flags;
    if (gCurrentActor && gCurrentActor) {}  // FAKE: steers uopt candidate colouring (gActivePlayerActor pointer v1)

    attacker = gCurrentActor;
    gActivePlayerState = gCurrentActor->customState;
    if (D_807463B8 == 0) {
        gCurrentActor->flags |= 0x400000;
    } else {
        gCurrentActor->flags &= 0xFFBFFFFF;
    }
    gCurrentActor->flags &= 0xF7FFFFFF;
    gPlayerSlots[gCurrentPlayerIndex].prevFov = gPlayerSlots[gCurrentPlayerIndex].fov;
    if (gCurrentActor->renderFlags & 0x100) {
        gActivePlayerState->lastFrame = gGameFrameCounter;
    }
    if (gActivePlayerState->targetScale[0] == gActivePlayerState->currentScale[0] && gCurrentActor->state != 0x54) {
        if (gCurrentActor->actorType == 4) {
            gCurrentActor->eyeHeight = 0xB;
        } else {
            gCurrentActor->eyeHeight = gCurrentActor->collision->scaledRadius * 0.15 * 0.5;
        }
    }
    playerCheckQueueDropCallback();
    flags = gPlayerStateFlags[gCurrentActor->state][0];
    if (flags & 8) {
        gCurrentActor->flags2 |= 2;
    } else {
        gCurrentActor->flags2 &= 0xFFFD;
    }
    if ((flags & 0x20) && gActivePlayerState->invulnTimer == 0 && gCurrentActor->actorType != 8 && gCurrentActor->actorType != 9) {
        gCurrentActor->flags2 |= 0x10;
    } else {
        gCurrentActor->flags2 &= 0xFFEF;
        gCurrentActor->flags &= ~0x800;
    }
    if (gActivePlayerState->invulnTimer != 0) {
        gActivePlayerState->invulnTimer = gActivePlayerState->invulnTimer - 1;
    }
    if (flags & 0x40) {
        gCurrentActor->flags |= 0x4000;
    } else {
        gCurrentActor->flags &= ~0x4000;
    }
    if ((flags & 0x80) && gActivePlayerState->respawnTimer == 0 && gCurrentActor->actorType != 8 && gCurrentActor->actorType != 9) {
        gCurrentActor->flags2 |= 0x20;
    } else {
        gCurrentActor->flags2 &= 0xFFDF;
    }
    if (gActivePlayerState->respawnTimer != 0) {
        gActivePlayerState->respawnTimer = gActivePlayerState->respawnTimer - 1;
    }
    if (gActivePlayerState->damageCooldown != 0) {
        gActivePlayerState->damageCooldown = gActivePlayerState->damageCooldown - 1;
    }
    playerUpdateScaleAndPhysics();
    playerCheckAndClearCarriedItem();
    playerUpdateSlopeSlidePhysics();
    if (D_80770561 == 0x6B && gCurrentActor->state != 0x6E) {
        sfxStopChannel(0x6B, 0);
    }
    if (gActivePlayerState->unkCA != 0) {
        gActivePlayerState->unkCA = gActivePlayerState->unkCA - 1;
    }
    if (gCurrentActor->flags2 & 0x20) {
        proxPathUpdateAllPlayers();
    }
    gridSetNodeBounds(gCurrentPlayerIndex, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, gCurrentActor->sub4->scaleY / 0.15 * 20.0);
    if (gPlayerCount == 1) {
        if (gCurrentActor->renderFlags & 0x1000) {
            gCurrentActor->renderFlags |= 0x200;
        }
    }
    gCurrentActor->renderFlags &= ~0x1000;
    gPlayerStateHandlers[gCurrentActor->state].fn();
    gActivePlayerState->hitStatus = collisionGetHitStatus();
    if (gPlayerCount == 1) {
        gCurrentActor->renderFlags &= ~0x200;
    }
    if ((gActivePlayerState->stateFlags & 0x01000000) && gActorGlobalState.unk1C != 0 && gCurrentActor->state != 0x47) {
        playerStateQueueCallback(3, NULL, gCurrentPlayerIndex);
    }
    heavyImpact = collisionIsHeavyGroundImpact();
    groundImpact = collisionIsGroundImpact();
    floorType = collisionGetFloorType();
    materialType = collisionGetMaterialType();
    if (gCurrentActor->flags2 & 0x10) {
        playerCheckLedgeGrab();
    }
    gActivePlayerState->stateStep = 0;
    gActivePlayerState->stateFlags &= 0xBFFFFFFF;
    func_806CF580();
    gActivePlayerState->prevState = gActivePlayerActor->state;
    if (gPlayerCount >= 2) {
        if (gCurrentActor->contactFlags & 1) {
            if (gActivePlayerState->attackTimer != 0) {
                gActivePlayerState->attackTimer = gActivePlayerState->attackTimer - 1;
            } else {
                gActivePlayerState->attackerPlayerIndex = -1;
                gActivePlayerState->attackerSpawnNodeId = 0;
            }
        }
        playerClearStaleHitSource();
        {
            s8 attackerIndex = gActivePlayerState->attackerPlayerIndex;
            if (attackerIndex >= 0 && (u32)attackerIndex != gActivePlayerState->playerIndex) { // FAKE: (u32) cast on a != compare steers codegen
                attacker = gPlayerSlots[attackerIndex].actor;
            } else {
                s8 spawnNodeId = gActivePlayerState->attackerSpawnNodeId;
                if (spawnNodeId > 0) {
                    attacker = spawnNodeActivate(spawnNodeId, 0);
                }
            }
        }
        if (D_807552E4 == 0) {
            if (gActivePlayerActor->state == 0x3C) {
                if (gActivePlayerState->effectTimer != 0) {
                    gActivePlayerState->effectTimer = gActivePlayerState->effectTimer - 1;
                }
                if (gActivePlayerState->effectObj == NULL) {
                    effectSetDuration(-1);
                    effectSetMode(0);
                    effectSetColor(0xFF, 0xFF, 0xFF, 0x78);
                    effectEnableFade();
                    gActivePlayerState->effectObj = effectCreateAtPosition(&D_80720020, 0.7f, gActivePlayerActor->x, gActivePlayerActor->y, gActivePlayerActor->z);
                }
            } else {
                if (gActivePlayerState->effectTimer < 0x78) {
                    gActivePlayerState->effectTimer = gActivePlayerState->effectTimer + 1;
                }
                if (gActivePlayerState->effectObj != NULL) {
                    fx = gActivePlayerState->effectObj;
                    gActivePlayerState->effectObj = NULL;
                    effectFreeAndUnlink(fx);
                }
            }
            fx = gActivePlayerState->effectObj;
            if (fx != NULL) {
                actorGetNodePos(gActivePlayerActor, 1, &nodeX, &nodeY, &nodeZ);
                camProjectToScreen(nodeX, nodeY, nodeZ, &projX, &projY, NULL, 1.0f, 0);
                fx->x = projX * 4.0f;
                fx->y = projY * 4.0f;
                fx->z = 5.0f;
                dz = gPlayerSlots[0].camZ - nodeZ;
                dx = gPlayerSlots[0].camX - nodeX;
                dy = gPlayerSlots[0].camY - nodeY;
                dz = sqrtf(dz * dz + (dx * dx + dy * dy));
                fx->scaleX = gCurrentActor->sub4->scaleX * (1000.0f / dz) * 6.666666666666667 * 0.7 * 0.008333334f * (f32)gActivePlayerState->effectTimer;
                fx->scaleY = fx->scaleX;
            }
        }
    }
    if (gActivePlayerState->surfaceTimer != 0) {
        gActivePlayerState->surfaceTimer = gActivePlayerState->surfaceTimer - 1;
    }
    if (groundImpact != 0) {
        playerStateQueueCallback(0x3F, attacker, gCurrentPlayerIndex);
    }
    if (heavyImpact == 1) {
        goto case1;
    }
    if (heavyImpact == 2) {
        goto case2;
    }
    gActivePlayerState->breathTimer = 0;
    goto done;
case1:
    if (gActivePlayerState->stateFlags & 0x10) {
        gActivePlayerState->breathTimer = 0;
    } else {
        gActivePlayerState->breathTimer = gActivePlayerState->breathTimer + 1;
        playerStateQueueCallback(0x2E, attacker, gCurrentPlayerIndex);
        if (gCurrentActor->state != 0x36 && gCurrentActor->state != 0x3B && gActivePlayerState->surfaceTimer == 0) {
            s16 snd = 0x2C0;
            if (gCurrentMap == 0x30) {
                snd = 0x3B0;
            }
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, snd, 0xFF, 0x7F, 0);
        }
    }
    goto done;
case2:
    gActivePlayerState->stateFlags |= 0x1000;
    if (!(gActivePlayerState->stateFlags & 0x10)) {
        if (gCurrentActor->state != 0x36 && gCurrentActor->state != 0x3B && gActivePlayerState->surfaceTimer == 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x2C0, 0xFF, 0x7F, 0);
        }
        if (gCurrentMap == 0x53 || gCurrentMap == 0xC5) {
            playerStateQueueCallback(0x40, attacker, gCurrentPlayerIndex);
        } else {
            playerStateQueueCallback(0x30, attacker, gCurrentPlayerIndex);
        }
    }
done:
    if (floorType != 0) {
        playerStateQueueCallback(0, attacker, gCurrentPlayerIndex);
        if (gActivePlayerState->surfaceTimer == 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x2C0, 0xFF, 0x7F, 0);
        }
    }
    actorGetNodePos(gActivePlayerActor, 6, &((PlayerStruct *)gPlayerSlots)[gCurrentPlayerIndex].headX, &((PlayerStruct *)gPlayerSlots)[gCurrentPlayerIndex].headY, &((PlayerStruct *)gPlayerSlots)[gCurrentPlayerIndex].headZ); // FAKE: redundant (PlayerStruct *) cast on gPlayerSlots steers regalloc
    camProjectToScreen(gActivePlayerActor->x, gPlayerSlots[gCurrentPlayerIndex].headY, gActivePlayerActor->z, &screenX, &screenY, NULL, 1.0f, gCurrentPlayerIndex);
    gActivePlayerState->targetPitch = screenX;
    gActivePlayerState->targetRoll = screenY;
    camProjectToScreen(gActivePlayerActor->x, gActivePlayerActor->y, gActivePlayerActor->z, &screenX, &screenY, NULL, 1.0f, gCurrentPlayerIndex);
    gActivePlayerState->targetYawAngle = screenY;
    gActivePlayerState->prevStateFlags = gActivePlayerState->stateFlags;
    if (gActivePlayerState->transitionTimer != 0) {
        gActivePlayerState->transitionTimer = gActivePlayerState->transitionTimer - 1;
    }
    if ((gCurrentActor->x < D_807F5FE4 || gCurrentActor->z < D_807F5FE6 || D_807F5FE8 < gCurrentActor->x || D_807F5FEA < gCurrentActor->z || materialType != 0) && gActivePlayerState->idleTimeoutFlag == 0 && gFrameCounter >= 0x65 && !(gGlobalOverlayFlags & 0x4000) && gCurrentMap != 0xE) {
        if (gPlayerCount == 1) {
            if (flagGet(0x186, 0) == 0) {
                mapSetPendingTransition(0xB0, 1);
            }
            healthRefill(gCurrentPlayerIndex);
            mapExecuteDeathTransition(gCurrentPlayerIndex);
            gActivePlayerState->idleTimeoutFlag = 1;
        } else {
            func_80026D40(gCurrentActor, gCurrentPlayerIndex);
        }
    }
    if (gCurrentPlayerIndex == 0) {
        switch (gCurrentMap) {
            case 0x7:
            case 0x1A:
            case 0x1E:
            case 0x22:
            case 0x26:
            case 0x30:
            case 0x48:
            case 0x57:
                if (D_8076A094 >= 0x5DD && gActivePlayerState->idleTimeoutFlag == 0) {
                    mapExecuteVoidTransition();
                    gActivePlayerState->idleTimeoutFlag = 1;
                }
                if (D_8076A098 >= 0x5DD && !(gGlobalPauseFlags & 2) && gActivePlayerState->idleTimeoutFlag == 0) {
                    mapExecuteVoidTransition();
                    gActivePlayerState->idleTimeoutFlag = 1;
                }
                if ((gCurrentActor->x != gCurrentActor->prevX || gCurrentActor->y != gCurrentActor->prevY || gCurrentActor->z != gCurrentActor->prevZ || gPlayerPadState[gCurrentPlayerIndex].unk2A != 0 || gPlayerPadState[gCurrentPlayerIndex].unk2E != 0 || gPlayerPadState[gCurrentPlayerIndex].unk2F != 0) && !(gGlobalPauseFlags & 2)) {
                    if (++D_8076A090 == 0x69780) {
                        mapExecuteVoidTransition();
                        gActivePlayerState->idleTimeoutFlag = 1;
                    }
                }
                break;
        }
    }
}


extern f32 gKongTurnDecelRates[];
extern f32 D_80753234[];
extern s16 D_8075326C[];
extern f32 D_80753218[];
extern s32 gCurrentMap;
extern u8 D_807463B8;
extern s32 D_8071FB08;
extern s32 sEffectSparkConfig;

void playerUpdateScaleAndPhysics(void) {
    s32 padHintTimer;
    s32 sparkTimer;
    s32 flag;
    f32 scale;

    if ((gActivePlayerActor->actorType == 8 || gActivePlayerActor->actorType == 9) && gActivePlayerState->unk1FD != 0) {
        if ((gActivePlayerState->stateFlags & 0x800) && gActivePlayerState->sparkTimer == 0) {
            gActivePlayerState->sparkTimer = 0x1E;
            func_80687400();
        }
        sparkTimer = gActivePlayerState->sparkTimer;
        if ((gPlayerPadState[gCurrentPlayerIndex].unk2C & 2) && (gPlayerPadState[gCurrentPlayerIndex].unk2A & 0x2000) && sparkTimer == 0) {
            gActivePlayerState->sparkTimer = 0x1E;
            sparkTimer = gActivePlayerState->sparkTimer;
        }
        if (sparkTimer != 0) {
            effectSetSpeed((randomNonNegative() >> 15) % 10 + 0x8008);
            effectSetDuration(2);
            effectSetCallback(func_80717930);
            effectSetDepth(1);
            effectSetFlags(6);
            effectCreateAtActorBone(&sEffectSparkConfig, ((randomNonNegative() >> 15) % 50) / 80.0 + 0.5, gCurrentActor, 2, 0);
            gActivePlayerState->sparkTimer = gActivePlayerState->sparkTimer - 1;
            sparkTimer = gActivePlayerState->sparkTimer;
        }
        if (sparkTimer == 1) {
            playerStateQueueCallback(0x3B, NULL, gCurrentPlayerIndex);
            gActivePlayerState->unk1FD = 0;
        }
    } else {
        gActivePlayerState->sparkTimer = 0;
    }
    gActivePlayerState->stateFlags &= ~0x800;
    if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 != 1 || (gActivePlayerState->stateFlags & 0x30)) {
        if ((gActivePlayerState->stateFlags & 0x80000000) && gActivePlayerState->padHintTimer == 0) {
            gActivePlayerState->padHintTimer = 0x1E;
            func_80687400();
        }
        padHintTimer = gActivePlayerState->padHintTimer;
        if (padHintTimer != 0) {
            gActivePlayerState->padHintTimer = padHintTimer - 1;
            padHintTimer = gActivePlayerState->padHintTimer;
        }
        if (padHintTimer == 1) {
            gPlayerPadState[gCurrentPlayerIndex].unk2C |= 2;
            gPlayerPadState[gCurrentPlayerIndex].unk2A |= 0x2000;
        }
        if (!(gPlayerStateFlags[gCurrentActor->state][0] & 0x300) && !(gActivePlayerState->stateFlags & 0x14000) && camIsCutsceneActive() == 0 && !(gActivePlayerState->stateFlags2 & 0x10)) {
            slotQueueAddValue(5, gActivePlayerState->playerIndex, -1);
        }
    } else {
        gActivePlayerState->padHintTimer = 0;
    }
    gActivePlayerState->stateFlags &= 0x7FFFFFFF;
    if (((gPlayerPadState[gCurrentPlayerIndex].unk2C & 2) && (gPlayerPadState[gCurrentPlayerIndex].unk2A & 0x2000) && gPlayerCount == 1) || slotQueueGetValue(5, gActivePlayerState->playerIndex) == 0) {
        if (!(gActivePlayerState->stateFlags & 0x2000) && gCurrentMap != 0xCF) {
            flag = 0;
            if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 != 1) {
                playerSetSizeMode(gActivePlayerActor, 1);
                flag = 1;
                if (gActivePlayerState->heldActor != NULL && gActivePlayerActor->actorType == 6 && gActivePlayerActor->state != 0x4A) {
                    gActivePlayerActor->state = 0x4A;
                    gActivePlayerActor->unk155 = 0;
                    actorScriptStart(gActivePlayerActor, 0x1CD);
                }
            }
            if (gActivePlayerState->stateFlags & 0x10) {
                gActivePlayerState->stateFlags &= ~0x10;
                flag = 1;
                gActivePlayerActor->flags |= 0x8000;
                gActivePlayerActor->alpha = 0xFF;
            }
            if (gActivePlayerState->stateFlags & 0x20) {
                gActivePlayerState->stateFlags &= ~0x20;
                flag = 1;
                playerInitNormalMoveParams();
            }
            if (flag != 0) {
                playerCheckAndResetCarriedActor(gCurrentActor);
            }
        }
    }
    if (gActivePlayerState->stateFlags & 0x10) {
        gActivePlayerState->surfaceTimer = 2;
    }
    if (gActivePlayerState->targetScale[0] != gActivePlayerState->currentScale[0]) {
        gCurrentActor->renderFlags |= 0x800;
        switch (gCurrentActor->actorType) {
            default:
                gCurrentActor->unk120 = 0.15f;
                break;
            case 5:
                gCurrentActor->unk120 = 0.15f;
                break;
            case 6:
                gCurrentActor->unk120 = 0.3f;
                break;
        }
        playerScaleTransitionStep();
    } else {
        gCurrentActor->renderFlags &= ~0x800;
    }
    if (gActivePlayerState->stateFlags & 0x40) {
        if (gCurrentActor->actorType != 6) {
            gCurrentActor->flags &= 0xFFFF7FFF;
            gCurrentActor->alpha -= 4;
            if (gCurrentActor->alpha < 0x64) {
                gCurrentActor->alpha = 0x64;
            }
        }
        if (gActivePlayerState->unk1FE != -1) {
            gActivePlayerState->unk1FE = gActivePlayerState->unk1FE - 1;
            if (!(gActivePlayerState->unk1FE & 7)) {
                effectSetCallback(effectZSpinMatrixUpdate);
                effectSetDepth(1);
                effectSetDuration(3);
                effectCreateAtPosition(&D_8071FB08, 1.0f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
            if (gActivePlayerState->unk1FE == 0) {
                sfxStopChannel(0x6C, 0);
                gCurrentActor->flags |= 0x8000;
                playerTransformAnimalEndSfx(gCurrentActor);
            }
        }
    }
    if (gActivePlayerState->unk200 != 0) {
        if (gActivePlayerState->stateFlags & 0x8000000) {
            scale = 1.0f;
            if (gActivePlayerState->unk200 >= 2) {
                scale = 0.5f;
            }
            gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex] * scale;
            gActivePlayerState->airAccel = D_80753234[gCurrentCharacterIndex] * scale;
            gActivePlayerState->turnRate = (s32)(D_8075326C[gCurrentCharacterIndex] * scale);
        }
        if (gCurrentActor->state != 0x7C || (gCurrentActor->state == 0x7C && gActivePlayerState->unk200 == 1)) {
            gActivePlayerState->unk200 = gActivePlayerState->unk200 - 1;
        }
        if (gActivePlayerState->unk200 == 0) {
            gActivePlayerState->stateFlags &= 0xF7FFFF7F;
            if (gCurrentActor->state == 0x7C) {
                playerResumeLocomotion(gCurrentActor);
            }
        }
    }
    if ((gActivePlayerState->stateFlags & 0x20) || D_807463B8 == 3) {
        if (gCurrentMap == 0x30) {
            gActivePlayerState->targetSpeed = 200.0f;
            return;
        }
        gActivePlayerState->targetSpeed = D_80753218[gCurrentCharacterIndex];
    }
}


void playerCheckQueueDropCallback(void) {
    if (gActorGlobalState.unk2 != 0 && gActorGlobalState.unk14 == 1) {
        playerStateQueueCallback(0x20, NULL, gCurrentPlayerIndex);
    }
}

extern f32 gKongCannonInitialPitch[];

void playerCheckLandingSfx(void) {
    if ((gCurrentActor->contactFlags & 0x21) == 1) {
        if (gCurrentActor->contactFlags & 0x200) {
            if (gCurrentActor->soundSlots[0] == -1) {
                sfxPlayActorSound(gCurrentActor, 0x10D, 0, 1, 0, 0xFF, 1.0f, 0);
            }
            gCurrentActor->state = 0xF;
            gCurrentActor->unk155 = 0;
            gCurrentActor->terminalSpeedY = -900.0f;
            gActivePlayerState->turnRate = D_8075326C[gCurrentCharacterIndex];
            gActivePlayerState->decelRate = gKongCannonInitialPitch[gCurrentCharacterIndex];
            gActivePlayerState->airAccel = D_80753234[gCurrentCharacterIndex];
            actorScriptStartByIndex(gCurrentActor, 0x5E);
            gCurrentActor->contactFlags |= 0x20;
            actorScriptExecute(gCurrentActor);
            return;
        }
        if (gCurrentActor->floorSlopeFactor != 0.0f && gActivePlayerState->unkC2 >= 0x15 && gCurrentActor->state != 0x17) {
            if (mathAngleDistance(gCurrentActor->floorTiltYaw, gCurrentActor->yaw) < 0x200) {
                if (gPlayerStateFlags[gActivePlayerActor->state][0] & 0x200) {
                    func_806EAB44(gCurrentActor, 0);
                }
                playerStateQueueCallback(0x21, NULL, gCurrentPlayerIndex);
                return;
            }
            if (mathAngleDistance(gCurrentActor->floorTiltYaw, gCurrentActor->moveYaw) < 0x400 || gCurrentActor->speedXZ < 15.0f) {
                if (gPlayerStateFlags[gActivePlayerActor->state][0] & 0x200) {
                    func_806EAB44(gCurrentActor, 0);
                }
                playerStateQueueCallback(0x22, NULL, gCurrentPlayerIndex);
            }
        }
    }
}

s16 mathAngleSignedDistance(s16 from, s16 to) {
    s16 d = to - from;
    s16 wrapped = d & 0xFFF;

    if (wrapped > 0x800) {
        wrapped -= 0x1000;
    }
    return wrapped;
}

s16 mathAngleDistance(s16 from, s16 to) {
    s16 d = to - from;
    s16 wrapped = d & 0xFFF;

    if (wrapped > 0x800) {
        wrapped = 0x1000 - wrapped;
    }
    return wrapped;
}

s16 mathAngleEaseToward(s16 angle, s16 target, f32 step) {
    s16 diff;
    s16 absd;
    s16 sign;
    f32 dist;

    diff = target - angle;
    if (diff > 0) {
        absd = diff;
    } else {
        absd = -diff;
    }
    if (step != 0.0f && (diff & 0xFFF)) {
        if (diff >= 0) {
            sign = 1;
        } else {
            sign = -1;
        }
        if (absd >= 0x801) {
            absd = 0x1000 - absd;
            sign = -sign;
        }
        dist = absd;
        if (dist < step) {
            step = dist;
        }
        angle += sign * (s16)(dist / step);
    }
    return angle & 0xFFF;
}

s16 mathAngleLerp(s16 angle, s16 target, f32 t) {
    s16 diff;
    s16 absd;
    s16 sign;

    diff = target - angle;
    if (diff > 0) {
        absd = diff;
    } else {
        absd = -diff;
    }
    if (t != 0.0f && (diff & 0xFFF)) {
        if (diff >= 0) {
            sign = 1;
        } else {
            sign = -1;
        }
        if (absd >= 0x801) {
            absd = 0x1000 - absd;
            sign = -sign;
        }
        angle += sign * (s16)(absd * t);
    }
    return angle & 0xFFF;
}


extern s16 D_80753A3C[];
extern s16 D_80753A4C[];

#define ABSF(x) ((x) > 0.0f ? (x) : -(x))

void playerClampToWaterSurface(u8 clampFall) {
    f32 sum;
    f32 radius;

    if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) {
        radius = D_80753A3C[gCurrentCharacterIndex];
    } else {
        radius = D_80753A4C[gCurrentCharacterIndex];
    }
    sum = ABSF(mathSinF(gCurrentActor->roll) * radius) + 1.5;
    sum += ABSF(mathCosF(gCurrentActor->floorTiltPitch) * radius);
    if (gCurrentActor->distToFloor < sum) {
        if (gCurrentActor->floorTiltPitch < 500) {
            gCurrentActor->speedXZ = (gCurrentActor->speedXZ < 50.0f) ? gCurrentActor->speedXZ : 50.0f;
        }
        if (clampFall) {
            if (gCurrentActor->speedY < 0.0f) {
                gCurrentActor->speedY = 0.0f;
            }
        }
        if (radius < gCurrentActor->waterY - gCurrentActor->y) {
            gCurrentActor->y = gCurrentActor->floorY + sum;
        }
    }
}

extern f32 D_807539C0[];

void playerDecelerateAndApplyMotion(void) {
    gCurrentActor->speedXZ = mathApproachF32(gCurrentActor->speedXZ, 0.0f, D_807539C0[gCurrentCharacterIndex]);
    playerApplyMotion();
    playerClampToWaterSurface(1);
}

extern s16 D_80753A2C[];
extern f32 D_80753A5C[];

void playerApplyDecelVelocityVector(f32 unused) {
    f32 vx;
    f32 vz;
    f32 adj;
    f32 rate;
    f32 cosYaw;
    f32 sinYaw;
    f32 speed;

    if (gActivePlayerState->actionTimer != 0) {
        gActivePlayerState->actionTimer--;
        cosYaw = mathCosF(gActivePlayerState->subTimer);
        sinYaw = mathSinF(gActivePlayerState->subTimer);
        speed = gActivePlayerState->targetSpeed;
        vx = speed * cosYaw;
        vz = gActivePlayerState->targetSpeed * -sinYaw;
        adj = 0.0f;
        if (gActivePlayerState->targetSpeed < gCurrentActor->speedXZ) {
            rate = gActivePlayerState->airAccel * 8.0f;
        } else {
            rate = gActivePlayerState->airAccel;
        }
    } else {
        sinYaw = mathSinF(gCurrentActor->roll);
        vz = gCurrentActor->speedXZ * -sinYaw;
        gCurrentActor->speedY = mathApproachF32(gCurrentActor->speedY, vz, 2.0f);
        vx = 0.0f;
        adj = 0.0f;
        rate = gActivePlayerState->decelRate;
    }
    if (0.0f <= vz) {
        if (gCurrentActor->waterY - gCurrentActor->y < D_80753A2C[gCurrentCharacterIndex]) {
            adj = ABSF(D_80753A5C[gCurrentCharacterIndex]);
        }
    }
    vz += adj;
    if (gCurrentActor->distToFloor == 0.0f) {
        if (gCurrentActor->speedY < -0.1) {
            gCurrentActor->speedY = -0.1f;
        }
    }
    gCurrentActor->speedY = mathApproachF32(gCurrentActor->speedY, vz, rate * 2.0);
    gCurrentActor->speedXZ = mathApproachF32(gCurrentActor->speedXZ, vx, rate);
    gCurrentActor->moveYaw = gCurrentActor->yaw;
    actorStepPhysics(gCurrentActor, gCurrentActor->moveYaw, gCurrentActor->yaw);
    actorApplyVelocityCustom(gCurrentActor, gCurrentActor->speedXZ, gCurrentActor->speedY);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    playerClampToWaterSurface(0);
}

extern u8 D_807FD586;

void playerSetUnk586Flag(void) {
    D_807FD586 = 1;
}

void playerApplyFullPhysics(void) {
    playerApplyGravity();
    playerCheckLandingSfx();
    playerUpdateHorizontalVelocity(1);
    playerApplyMotion();
}

void playerApplyMotionWithHorizontalVelocity(void) {
    playerCheckLandingSfx();
    playerUpdateHorizontalVelocity(1);
    playerApplyMotion();
}

void playerApplyHorizontalMotion(void) {
    playerUpdateHorizontalVelocity(1);
    playerApplyMotion();
}

void playerApplyGravityAndMotion(void) {
    playerApplyGravity();
    playerApplyMotion();
}

f32 sqrtf(f32);
extern u32 gFrameDelta;

#define MAXF(a, b) ((a) < (b) ? (b) : (a))

void playerApplyMotion(void) {
    s16 angle;
    f32 dx;
    f32 dz;

    playerUpdateHorizontalVelocity(0);
    if (mathAngleDistance(gCurrentActor->yaw, gCurrentActor->moveYaw) < 0x400) {
        angle = gCurrentActor->yaw;
    } else {
        angle = (gCurrentActor->yaw + 0x800) & 0xFFF;
    }
    actorStepPhysics(gCurrentActor, angle, angle);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, MAXF(-gActivePlayerState->breathTimer * 0.125, -6.0));
    gCurrentActor->flags |= 1;
    dx = gCurrentActor->x - gCurrentActor->prevX;
    dz = gCurrentActor->z - gCurrentActor->prevZ;
    gActivePlayerState->unk20 = sqrtf(dx * dx + dz * dz) / gFrameDelta * 80.0 * 0.15 / gCurrentActor->sub4->scaleX;
}

void playerApplyGravity(void) {
    if (gActivePlayerState->unk50 != 0) {
        gActivePlayerState->unk50--;
        return;
    }
    gCurrentActor->speedY += gCurrentActor->accelY;
    if (gCurrentActor->speedY < gCurrentActor->terminalSpeedY) {
        gCurrentActor->speedY = gCurrentActor->terminalSpeedY;
    }
    if (-gCurrentActor->terminalSpeedY < gCurrentActor->speedY) {
        gCurrentActor->speedY = -gCurrentActor->terminalSpeedY;
    }
}


void playerApproachOrApplyMotion(void) {
    f32 speed = mathScaleByAngleDeltaCos(gActivePlayerState->maxSpeed, gActivePlayerState->targetYaw, gCurrentActor->yaw);

    if (speed > 0.0f) {
        playerApproachVelocity(gCurrentActor->yaw, speed, gActivePlayerState->targetSpeed);
    } else {
        playerApplyDeceleration();
    }
}

s32 playerIsDamageOrKnockbackState(void) {
    switch (gActivePlayerActor->state) {
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
            return 1;
    }
    return 0;
}

typedef struct LinkedActorState {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
} LinkedActorState;


void playerUpdateHorizontalVelocity(apply) u8 apply; {
    f32 forward;
    f32 lateral;
    f32 vx;
    f32 vz;
    f32 speed;
    f32 slope;
    s16 ang;
    s16 m;
    LinkedActorState *sub;

    switch (gCurrentActor->state) {
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
            speed = gCurrentActor->speedXZ;
            ang = gCurrentActor->moveYaw;
            sub = gActivePlayerState->actor->customState;
            gActivePlayerState->prevHasArcBounds = gCurrentActor->hasArcBounds;
            D_807FD586 = 0;
            slope = mathSinF((s16)(s32)(gCurrentActor->floorSlopeFactor * 11.4)) * 10.0;
            forward = gPlayerPadState[gCurrentPlayerIndex].unk2F;
            if (forward < 0.0f) {
                forward = forward * (gCurrentActor->speedXZ / 1600.0);
                if (gCurrentActor->speedXZ < 210.0f) {
                    forward = 0.0f;
                }
            } else {
                forward = forward / 10.0;
            }
            m = (ang - gCurrentActor->floorSlopeYaw > 0 ? ang - gCurrentActor->floorSlopeYaw : -(ang - gCurrentActor->floorSlopeYaw)) % 4096;
            if ((m >= 0x401 && m < 0xC00) || !(gCurrentActor->contactFlags & 0x200)) {
                forward = 0.0f;
            }
            lateral = -gPlayerPadState[gCurrentPlayerIndex].unk2E / 5.5;
            if (gCurrentActor->speedXZ < 50.0f) {
                lateral = lateral * 0.21739130434782608;
            } else if (gCurrentActor->speedXZ < 230.0f) {
                lateral = (gCurrentActor->speedXZ * lateral) / 230.0;
            }
            if (sub->unk14 < sub->unk18) {
                forward = 0.0f;
            }
            vx = mathSinF(ang) * speed;
            vz = mathCosF(ang) * speed;
            if (gCurrentActor->contactFlags & 1) {
                vx += mathSinF(gCurrentActor->floorSlopeYaw) * slope;
                vz += mathCosF(gCurrentActor->floorSlopeYaw) * slope;
                vx += mathSinF(gCurrentActor->moveYaw) * forward;
                vz += mathCosF(gCurrentActor->moveYaw) * forward;
                vx += mathCosF(gCurrentActor->moveYaw) * lateral;
                vz -= mathSinF(gCurrentActor->moveYaw) * lateral;
            } else if ((gCurrentActor->distToFloor > 30.0f || slope == 0.0f || m < 0x400 || m >= 0xC01) &&
                       sub->unk18 == sub->unk14) {
                vx += (mathSinF(gActivePlayerState->targetYaw) * gActivePlayerState->maxSpeed) / 40.0;
                vz += (mathCosF(gActivePlayerState->targetYaw) * gActivePlayerState->maxSpeed) / 40.0;
            }
            speed = sqrtf(vx * vx + vz * vz);
            if (!(gCurrentActor->contactFlags & 0x1000) && 700.0f < speed) {
                speed = 700.0f;
            }
            lateral = mathAtan2(vx, vz);
            if (apply != 0) {
                gCurrentActor->speedXZ = speed;
                gCurrentActor->moveYaw = (s32)((lateral * 4096.0) / 6.2831855f);
                if (gCurrentActor->contactFlags & 1) {
                    if (!(gCurrentActor->contactFlags & 0x200)) {
                        gActivePlayerState->decelRate = 20.0f;
                    } else {
                        gActivePlayerState->decelRate = (gCurrentActor->speedXZ * gCurrentActor->speedXZ) / 35000.0;
                    }
                    playerApplyDeceleration();
                    return;
                }
            }
            return;
        default:
            if (gActivePlayerState->unkC2 >= 0x15) {
                slope = gCurrentActor->floorSlopeFactor;
            } else {
                slope = 0.0f;
            }
            if (slope != 0.0f && gActivePlayerState->unkC2 >= 0x15 && (gCurrentActor->contactFlags & 1)) {
                speed = gCurrentActor->speedXZ;
                ang = gCurrentActor->moveYaw;
            } else {
                speed = gActivePlayerState->maxSpeed;
                ang = gActivePlayerState->targetYaw;
            }
            if (D_807FD586 == 0 && gActivePlayerState->prevHasArcBounds != 0 && gCurrentActor->hasArcBounds == 0) {
                gCurrentActor->moveYaw = ang;
            }
            gActivePlayerState->prevHasArcBounds = gCurrentActor->hasArcBounds;
            D_807FD586 = 0;
            forward = mathSinF(ang) * speed;
            vx = mathSinF(gCurrentActor->floorSlopeYaw) * slope;
            vx = forward + vx;
            forward = mathCosF(ang) * speed;
            vz = mathCosF(gCurrentActor->floorSlopeYaw) * slope;
            vz = forward + vz;
            speed = sqrtf(vx * vx + vz * vz);
            ang = (s32)((mathAtan2(vx, vz) * 4096.0) / 6.2831855f);
            if (apply != 0) {
                if (speed != 0.0f) {
                    playerApproachVelocity(ang, speed, gActivePlayerState->targetSpeed);
                } else {
                    playerApplyDeceleration();
                }
            }
            break;
    }
}


void playerApproachVelocity(s16 yaw, f32 speed, f32 maxSpeed) {
    f32 vA;
    f32 vB;
    f32 cur;
    f32 tgt;
    f32 dist;
    f32 rate;
    f32 lim1;
    f32 lim2;
    f32 f;
    s16 d;
    s16 prev;
    s16 wrap;

    if (gCurrentActor->speedXZ == 0.0f) {
        gCurrentActor->moveYaw = yaw;
    }
    prev = gCurrentActor->moveYaw;
    f = 0.0f;
    if (gCurrentActor->contactFlags & 1) {
        rate = gActivePlayerState->airAccel * (gActivePlayerState->unk26 * 3 + 100) / 400.0f;
        if (gActivePlayerState->unk28 != 0) {
            d = (yaw - prev) & 0xFFF;
            wrap = d;
            if (d > 0x800) {
                wrap = 0x1000 - d;
            }
            f = gActivePlayerState->unk26 * ((f32)wrap / 2048) / 100.0f;
        }
    } else {
        rate = gActivePlayerState->airAccel;
    }
    cur = mathSinF(prev) * gCurrentActor->speedXZ;
    tgt = mathSinF(yaw) * speed;
    if (f != 0.0f) {
        if (cur < tgt) {
            dist = tgt - cur;
        } else {
            dist = -(tgt - cur);
        }
        dist = dist * ((gActivePlayerState->unk26 * 63.0 + 100.0) / 6400.0);
        lim1 = (dist - rate) * f + rate;
    } else {
        if (0.0f < mathSinF(yaw) * rate) {
            lim1 = mathSinF(yaw) * rate;
        } else {
            lim1 = -(mathSinF(yaw) * rate);
        }
        if (0.0f < mathCosF(yaw) * rate) {
            lim2 = mathCosF(yaw) * rate;
        } else {
            lim2 = -(mathCosF(yaw) * rate);
        }
    }
    vA = mathApproachF32(cur, tgt, lim1);
    cur = mathCosF(prev) * gCurrentActor->speedXZ;
    tgt = mathCosF(yaw) * speed;
    if (f != 0.0f) {
        if (cur < tgt) {
            dist = tgt - cur;
        } else {
            dist = -(tgt - cur);
        }
        dist = dist * ((gActivePlayerState->unk26 * 63.0 + 100.0) / 6400.0);
        lim2 = (dist - rate) * f + rate;
    }
    vB = mathApproachF32(cur, tgt, lim2);
    gCurrentActor->speedXZ = sqrtf(vA * vA + vB * vB);
    if (maxSpeed < gCurrentActor->speedXZ) {
        gCurrentActor->speedXZ = maxSpeed;
    }
    if (gCurrentActor->speedXZ != 0.0) {
        gCurrentActor->moveYaw = mathAtan2(vA, vB) * 4096.0 / 6.2831855f;
    }
}

f32 mathApproachF32(f32 current, f32 target, f32 step) {
    if (current < target) {
        current += step;
        if (target < current) {
            current = target;
        }
    } else {
        current -= step;
        if (current < target) {
            current = target;
        }
    }
    return current;
}

void playerApplyDeceleration(void) {
    f32 decel;

    if ((gCurrentActor->contactFlags & 1) && !(gCurrentActor->contactFlags & 0x200)) {
        decel = gActivePlayerState->decelRate * (gActivePlayerState->unk26 * 15 + 100) / 1600.0f;
    } else {
        decel = gActivePlayerState->decelRate;
    }
    gCurrentActor->speedXZ -= decel;
    if (gCurrentActor->speedXZ < 0.0f) {
        gCurrentActor->speedXZ = 0.0f;
    }
}


s16 actorGetStateFlags(Actor *actor) {
    s16 flags = gPlayerStateFlags[actor->state][0];
    return flags;
}

extern f32 D_80753170[];
extern f32 D_8075318C[];
extern f32 D_807531A8[];
extern f32 D_807531C4[];
extern f32 D_807531E0[];
extern u8 gGameMode;

s16 playerSelectMoveTier(Actor *actor, f32 targetSpeed, f32 speed, s16 tier, s16 character) {
    f32 max;

    if (speed < targetSpeed) {
        max = targetSpeed;
    } else {
        max = speed;
    }
    if ((actor->contactFlags | actor->prevContactFlags) & 1) {
        switch (tier) {
            case 0:
            case 1:
            case 2:
                if (speed != 0.0f) {
                    if (speed < D_8075318C[character]) {
                        tier = 3;
                    } else if (speed < D_807531C4[character]) {
                        tier = 4;
                    } else {
                        tier = 5;
                    }
                }
                break;
            case 3:
                if (speed == 0.0f && targetSpeed < D_80753170[character]) {
                    tier = 0;
                    break;
                }
                if (D_807531C4[character] < speed) {
                    tier = 5;
                } else if (D_8075318C[character] < speed) {
                    tier = 4;
                }
                break;
            case 4:
                if (max < D_807531A8[character]) {
                    if (speed < D_80753170[character]) {
                        tier = 0;
                    } else {
                        tier = 3;
                    }
                } else if (D_807531C4[character] < speed) {
                    tier = 5;
                }
                break;
            case 5:
                if (max < D_807531E0[character]) {
                    tier = 4;
                }
                break;
            default:
                if (targetSpeed < D_80753170[character]) {
                    tier = 0;
                } else if (targetSpeed < D_807531A8[character]) {
                    tier = 3;
                } else if (targetSpeed < D_807531E0[character]) {
                    tier = 4;
                } else {
                    tier = 5;
                }
                break;
        }
        if (gActivePlayerState->stateFlags & 0x100) {
            if (tier == 4 || tier == 5) {
                tier = 3;
            }
        }
        if (tier == 0 && (gCurrentMap == 1 || gCurrentMap == 5 || gCurrentMap == 0x19 || gCurrentMap == 0xF)) {
            tier = 2;
        } else if (tier == 0 && (gPlayerCount >= 2 || (gActivePlayerState->stateFlags & 0x40) || !(actor->flags & 4) || gGameMode == 1)) {
            tier = 1;
        } else if (tier == 1 && gPlayerCount < 2 && !(gActivePlayerState->stateFlags & 0x40) && (actor->flags & 4) && gGameMode != 1) {
            tier = 0;
        }
    } else {
        tier = 6;
    }
    return tier;
}


extern u8 gPlayerCharacterId[];

s16 playerSelectWalkRunState(Actor *actor, f32 targetSpeed, f32 speed, s32 unused) {
    s16 nextState;
    f32 scale;
    s16 prevTier;
    s16 tier;

    nextState = actor->state;
    prevTier = gActivePlayerState->unk4C;
    tier = playerSelectMoveTier(actor, targetSpeed, speed, gActivePlayerState->unk4C, gCurrentCharacterIndex);
    if (tier != 6) {
        actor->speedY = 0.0f;
    }
    if (prevTier < 0) {
        playerInitMoveParams();
    }
    if (prevTier != tier) {
        switch (tier) {
            case 0:
                if (gActivePlayerState->stateFlags & 0x100) {
                    actorScriptStart(actor, 0x1AD);
                } else {
                    actorScriptStartByIndex(actor, 9);
                }
                scriptSetActorRampTarget(actor, 1.0f, 0.0f);
                nextState = 0xC;
                break;
            case 1:
                if (gActivePlayerState->stateFlags & 0x100) {
                    actorScriptStart(actor, 0x1AD);
                } else {
                    actorScriptStart(actor, 0x13);
                }
                scriptSetActorRampTarget(actor, 1.0f, 0.0f);
                nextState = 0xC;
                break;
            case 2:
                actorScriptStartByIndex(actor, 0x87);
                scriptSetActorRampTarget(actor, 1.0f, 0.0f);
                nextState = 0xC;
                break;
            case 3:
                if (gActivePlayerState->stateFlags & 0x100) {
                    actorScriptStart(actor, 0x76);
                    controllerAnimSetStateIfChanged(actor, 0x2AC, 0.0f, 6.0f);
                } else {
                    controllerAnimSetStateRemap(actor, 2, 0.0f, 6.0f);
                    actorScriptStartByIndex(actor, 1);
                }
                if (prevTier == 4 || prevTier == 5) {
                    controllerAnimScaleInterpolate(actor, 2);
                }
                nextState = 0xD;
                break;
            case 4:
                actorScriptStartByIndex(actor, 2);
                controllerAnimSetStateRemap(actor, 3, 0.0f, 6.0f);
                if (prevTier == 3) {
                    switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                            controllerAnimScaleInterpolate(actor, 4);
                            break;
                    }
                }
                if (prevTier == 5) {
                    controllerAnimScaleInterpolate(actor, 2);
                }
                nextState = 0xD;
                break;
            case 5:
                actorScriptStartByIndex(actor, 3);
                controllerAnimSetStateRemap(actor, 4, 0.0f, 6.0f);
                if (prevTier == 3 || prevTier == 4) {
                    controllerAnimScaleInterpolate(actor, 4);
                }
                nextState = 0xD;
                break;
            case 6:
                actorScriptStartByIndex(actor, 0x1B);
                actorScriptExecute(actor);
                gCurrentActor->peakY = gCurrentActor->y;
                nextState = 0x1E;
                break;
        }
        gActivePlayerState->unk4C = tier;
    }
    if (gActivePlayerState->unk4C >= 3) {
        if (gActivePlayerState->unk26 == 100) {
            scale = actor->speedXZ;
        } else {
            scale = gActivePlayerState->maxSpeed;
        }
        scale = scale * 0.025;
        if (gActivePlayerState->unk4C == 5) {
            scale = scale * 0.6;
        }
        if (scale > 1.25f) {
            scale = scale - (scale - 1.25f) * 0.4;
        }
        if (actor->sub4->model->speed != 0.0f) {
            if (gActivePlayerState->unk26 == 100) {
                scriptSetActorRampTarget(actor, scale, 2.0f);
            } else {
                if (scale < 0.5) {
                    scale = 0.5f;
                }
                scriptSetActorRampTarget(actor, scale, 10.0f);
            }
        }
    }
    return nextState;
}

s16 playerSelectCarryState(Actor *actor, f32 targetSpeed, f32 speed, s32 unused) {
    s16 nextState;
    f32 scale;
    s16 prevTier;
    s16 tier;

    nextState = actor->state;
    prevTier = gActivePlayerState->unk4C;
    tier = playerSelectMoveTier(actor, targetSpeed, speed, gActivePlayerState->unk4C, gCurrentCharacterIndex);
    actor->speedY = 0.0f;
    if (prevTier < 0) {
        playerInitMoveParams();
    }
    if (prevTier != tier) {
        switch (tier) {
            case 0:
                actorScriptStartByIndex(actor, 0x51);
                scriptSetActorRampTarget(actor, 1.0f, 0.0f);
                nextState = 0x5D;
                break;
            case 1:
                actorScriptStart(actor, 0x23);
                scriptSetActorRampTarget(actor, 1.0f, 0.0f);
                nextState = 0x5D;
                break;
            case 3:
                actorScriptStartByIndex(actor, 0x57);
                controllerAnimSetStateRemap(actor, 0x5C, 0.0f, 6.0f);
                if (prevTier == 4 || prevTier == 5) {
                    controllerAnimScaleInterpolate(actor, 2);
                }
                nextState = 0x5E;
                break;
            case 4:
                actorScriptStartByIndex(actor, 0x56);
                controllerAnimSetStateRemap(actor, 0x58, 0.0f, 6.0f);
                if (prevTier == 3) {
                    switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                            controllerAnimScaleInterpolate(actor, 4);
                            break;
                    }
                }
                if (prevTier == 5) {
                    controllerAnimScaleInterpolate(actor, 0xA);
                }
                nextState = 0x5E;
                break;
            case 5:
                actorScriptStartByIndex(actor, 0x55);
                controllerAnimSetStateRemap(actor, 0x60, 0.0f, 6.0f);
                switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
                    case 4:
                    case 5:
                        if (prevTier == 3) {
                            controllerAnimScaleInterpolate(actor, 8);
                        }
                        break;
                    default:
                        if (prevTier == 3 || prevTier == 4) {
                            controllerAnimScaleInterpolate(actor, 0);
                        }
                        break;
                }
                nextState = 0x5E;
                break;
            case 6:
                actorScriptStartByIndex(actor, 0x58);
                actorScriptExecute(actor);
                gCurrentActor->peakY = gCurrentActor->y;
                nextState = 0x1F;
                break;
        }
        gActivePlayerState->unk4C = tier;
    }
    if (gActivePlayerState->unk4C >= 3) {
        scale = actor->speedXZ;
        scale = scale * 0.025;
        if (gActivePlayerState->unk4C == 5) {
            scale = scale * 0.6;
        }
        if (scale > 1.25f) {
            scale = scale - (scale - 1.25f) * 0.4;
        }
        if (actor->sub4->model->speed != 0.0f) {
            scriptSetActorRampTarget(actor, scale, 2.0f);
        }
    }
    return nextState;
}

s16 playerSelectSurfaceState(Actor *actor, f32 targetSpeed, f32 speed, s32 unused) {
    s16 nextState;
    f32 scale;
    s16 prevTier;
    s16 tier;

    nextState = actor->state;
    prevTier = gActivePlayerState->unk4C;
    tier = playerSelectSurfaceMoveTier(actor, targetSpeed, speed, gActivePlayerState->unk4C, gCurrentCharacterIndex);
    actor->speedY = 0.0f;
    if (prevTier < 0) {
        playerInitNormalMoveParams();
    }
    if (prevTier != tier) {
        switch (tier) {
            case 0:
            case 1:
            case 2:
                actorScriptStart(actor, 0x150);
                scriptSetActorRampTarget(actor, 1.0f, 0.0f);
                nextState = 0x3F;
                break;
            case 4:
                actorScriptStart(actor, 0x151);
                controllerAnimSetStateIfChanged(actor, 0x163, 0.0f, 6.0f);
                if (prevTier == 5) {
                    controllerAnimScaleInterpolate(actor, 4);
                }
                nextState = 0x40;
                break;
            case 5:
                actorScriptStart(actor, 0x152);
                controllerAnimSetStateIfChanged(actor, 0x162, 0.0f, 6.0f);
                if (prevTier == 4) {
                    controllerAnimScaleInterpolate(actor, 0xC);
                }
                nextState = 0x40;
                break;
            case 6:
                actorScriptStartByIndex(actor, 0x1B);
                actorScriptExecute(actor);
                gCurrentActor->peakY = gCurrentActor->y;
                nextState = 0x1E;
                break;
        }
        gActivePlayerState->unk4C = tier;
    }
    if (gActivePlayerState->unk4C >= 3) {
        if (gActivePlayerState->unk26 == 100) {
            scale = actor->speedXZ;
        } else {
            scale = gActivePlayerState->maxSpeed;
        }
        scale = scale * 0.025;
        if (gActivePlayerState->unk4C == 5) {
            scale = scale * 0.6;
        }
        if (scale > 1.25f) {
            scale = scale - (scale - 1.25f) * 0.4;
        }
        if (actor->sub4->model->speed != 0.0f) {
            if (gActivePlayerState->unk26 == 100) {
                scriptSetActorRampTarget(actor, scale, 2.0f);
            } else {
                if (scale < 0.5) {
                    scale = 0.5f;
                }
                scriptSetActorRampTarget(actor, scale, 10.0f);
            }
        }
    }
    return nextState;
}

s16 playerSelectSurfaceMoveTier(Actor *actor, f32 targetSpeed, f32 speed, s16 tier, s16 character) {
    f32 max;

    if (speed < targetSpeed) {
        max = targetSpeed;
    } else {
        max = speed;
    }
    if ((actor->contactFlags | actor->prevContactFlags) & 1) {
        switch (tier) {
            case 0:
            case 1:
            case 2:
                if (speed != 0.0f) {
                    if (speed < D_807531C4[character]) {
                        tier = 4;
                    } else {
                        tier = 5;
                    }
                }
                break;
            case 4:
                if (speed < D_80753170[character]) {
                    tier = 0;
                } else if (D_807531C4[character] < speed) {
                    tier = 5;
                }
                break;
            case 5:
                if (max < D_807531E0[character]) {
                    tier = 4;
                }
                break;
            default:
                if (targetSpeed < D_80753170[character]) {
                    tier = 0;
                } else if (targetSpeed < D_807531E0[character]) {
                    tier = 4;
                } else {
                    tier = 5;
                }
                break;
        }
    } else {
        tier = 6;
    }
    return tier;
}


s16 playerSelectCarryMoveState(Actor *actor, f32 targetSpeed, f32 speed, s32 unused) {
    s16 nextState;
    f32 scale;
    s16 prevTier;
    s16 tier;

    nextState = actor->state;
    prevTier = gActivePlayerState->unk4C;
    tier = playerSelectCarryMoveTier(targetSpeed, speed);
    if (prevTier < 0) {
        playerInitMoveParams();
    }
    if (prevTier != tier) {
        switch (tier) {
            case 0:
                switch (gActivePlayerState->heldActor->actorType) {
                    case 0x3D:
                    case 0x3F:
                    case 0x40:
                    case 0x41:
                    case 0x42:
                    case 0x55:
                    case 0x82:
                        actorScriptStart(gActivePlayerActor, 0x1C9);
                        break;
                    default:
                        actorScriptStartByIndex(actor, 0x2E);
                        break;
                }
                gActivePlayerState->unk4C = 0;
                nextState = 0x48;
                break;
            case 1:
                switch (gActivePlayerState->heldActor->actorType) {
                    case 0x3D:
                    case 0x3F:
                    case 0x40:
                    case 0x41:
                    case 0x42:
                    case 0x43:
                    case 0x55:
                    case 0x82:
                        actorScriptStart(gActivePlayerActor, 0x1CA);
                        break;
                    default:
                        actorScriptStartByIndex(actor, 0x2F);
                        break;
                }
                gActivePlayerState->unk4C = 1;
                nextState = 0x49;
                break;
        }
    }
    if (gActivePlayerState->unk4C > 0) {
        scale = actor->speedXZ * 0.025;
        scale = scale * 0.75 + 0.25;
        if (actor->sub4->model->speed != 0.0f) {
            scriptSetActorRampTarget(actor, scale, 2.0f);
        }
    }
    return nextState;
}

extern f32 D_807532B8[];

s32 playerSelectCarryMoveTier(f32 targetSpeed, f32 speed) {
    s32 tier = gActivePlayerState->unk4C;

    switch (tier) {
        case 0:
            if (speed != 0.0f) {
                tier = 1;
            }
            break;
        case 1:
            if (speed == 0.0f && targetSpeed < D_807532B8[gCurrentCharacterIndex]) {
                tier = 0;
            }
            break;
        default:
            if (targetSpeed < D_807532B8[gCurrentCharacterIndex]) {
                tier = 0;
            } else {
                tier = 1;
            }
            break;
    }
    return tier;
}

extern s16 D_807532A8[];

void playerStartPickupApproach(Actor *target) {
    f32 radius;
    f32 ang;
    f32 mtx[4][4];
    f32 offsetX;
    f32 offsetY;
    f32 offsetZ;
    s32 frames = 15; // FAKE: int constant local steers regalloc (literal 15.0f: one sub.s fewer)

    switch (target->actorType) {
        case 0x3D:
        case 0x3F:
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x55:
        case 0x82:
            radius = 30.0f;
            break;
        default:
            radius = D_807532A8[gCurrentCharacterIndex];
            break;
    }
    if (gActivePlayerState->stateFlags & 0x01000000) {
        ang = gCurrentActor->yaw * 0x168 / 4096;
    } else {
        ang = mathAngleBetweenPointsDeg((s16)target->x, (s16)target->z, (s16)gCurrentActor->x, (s16)gCurrentActor->z);
        ang = 360.0 - ang;
    }
    gActivePlayerState->unk80 = ang * 4095.0 / 360.0;
    guRotateF(mtx, ang, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(mtx, 0.0f, 0.0f, radius, &offsetX, &offsetY, &offsetZ);
    gActivePlayerState->unk78 = ((target->x - offsetX) - gCurrentActor->x) / (f32)frames;
    gActivePlayerState->unk7C = ((target->z - offsetZ) - gCurrentActor->z) / (f32)frames;
}




void playerRegisterHeldActorFollow(f32 blend) {
    ActorCallbackNode *node;

    if (gActivePlayerState->heldActor != NULL) {
        node = heapAlloc(0x14);
        node->callback = playerHeldActorFollowStep;
        node->heldFollow.blend = blend;
        node->heldFollow.player = gCurrentActor;
        node->heldFollow.held = gActivePlayerState->heldActor;
        node->unk4 = 0;
        actorRegisterGlobalCallback(node);
    }
}


void playerComputePickupHoldPitch(void) {
    f32 bx;
    f32 ax;
    f32 by;
    f32 ay;
    f32 bz;
    f32 az;
    f32 dist;
    f32 dy;
    s32 idxA;
    s32 idxB;

    playerGetHoldNodeIndices(&idxA, &idxB);
    actorGetNodePos(gCurrentActor, idxA, &ax, &ay, &az);
    actorGetNodePos(gCurrentActor, idxB, &bx, &by, &bz);
    dy = by - ay;
    dist = sqrtf((bz - az) * (bz - az) + (bx - ax) * (bx - ax));
    gActivePlayerState->holdPitch = 0.0 - mathAtan2(dy, dist) * 57.29577637f + 270.0;
}


void playerHeldActorFollowStep(HeldActorFollowArg *follow) {
    f32 nodeX[2];
    f32 nodeY[2];
    f32 nodeZ[2];
    f32 midX;
    f32 midY;
    f32 midZ;
    f32 outX;
    f32 outY;
    f32 outZ;
    s32 idxA;
    s32 idxB;

    playerGetHoldNodeIndices(&idxA, &idxB);
    actorGetNodePos(follow->player, idxA, &nodeX[0], &nodeY[0], &nodeZ[0]);
    actorGetNodePos(follow->player, idxB, &nodeX[1], &nodeY[1], &nodeZ[1]);
    midX = (nodeX[0] + nodeX[1]) / 2;
    midY = (nodeY[0] + nodeY[1]) / 2;
    midZ = (nodeZ[0] + nodeZ[1]) / 2;
    outX = (midX - follow->held->x) * follow->blend + follow->held->x;
    outY = (midY - follow->held->y) * follow->blend + follow->held->y;
    outZ = (midZ - follow->held->z) * follow->blend + follow->held->z;
    actorAppendMoveTarget3D(follow->player, follow->held, outX, outY, outZ, 2, 1);
}




void playerRegisterHeldActorAlign(void) {
    ActorCallbackNode *node;

    if (gActivePlayerState->heldActor != NULL) {
        node = heapAlloc(0x14);
        node->callback = playerHeldActorAlignStep;
        node->heldAlign.player = gCurrentActor;
        node->heldAlign.held = gActivePlayerState->heldActor;
        node->unk4 = 0;
        actorRegisterGlobalCallback(node);
    }
}

void playerHeldActorAlignStep(HeldActorAlignArg *align) {
    f32 bx;
    f32 ax;
    f32 by;
    f32 ay;
    f32 bz;
    f32 az;
    f32 dy;
    f32 dist;
    f32 pitch;
    f32 pad;
    f32 dir[2];
    f32 delta[2];
    f32 dot;
    f32 dirLen;
    f32 deltaLen;
    s32 idxA;
    s32 idxB;

    playerGetHoldNodeIndices(&idxA, &idxB);
    actorGetNodePos(align->player, idxA, &ax, &ay, &az);
    actorGetNodePos(align->player, idxB, &bx, &by, &bz);
    dy = by - ay;
    dist = sqrtf((bz - az) * (bz - az) + ((bx - ax) * (bx - ax) + dy * dy));
    pitch = asinApprox(dy / dist) * 57.29577637f;
    dir[0] = mathSinF(align->player->yaw) * 50.0f;
    dir[1] = mathCosF(align->player->yaw) * 50.0f;
    delta[0] = bx - ax;
    delta[1] = bz - az;
    dot = dir[0] * delta[0] + dir[1] * delta[1];
    dirLen = sqrtf(dir[0] * dir[0] + dir[1] * dir[1]);
    deltaLen = sqrtf(delta[0] * delta[0] + delta[1] * delta[1]);
    actorAppendCallbackVec2f(align->player, align->held, pitch, 90.0 - acosApprox(dot / (dirLen * deltaLen)) * 57.29577637f);
}

void playerGetHoldNodeIndices(s32 *nodeA, s32 *nodeB) {
    s32 found = 0;

    if (gCurrentActor->actorType == 6) {
        switch (gActivePlayerState->heldActorType) {
            case 0x82:
                *nodeA = 0x13;
                *nodeB = 0x14;
                found = 1;
                break;
            case 0x3D:
            case 0x3F:
            case 0x40:
            case 0x41:
            case 0x42:
            case 0x43:
            case 0x55:
                *nodeA = 0x12;
                *nodeB = 0x11;
                found = 1;
                break;
        }
    }
    if (found == 0) {
        *nodeA = 2;
        *nodeB = 3;
    }
}

extern f32 D_80753428[];
extern f32 D_8075340C[];

void playerThrowHeldActor(Actor *thrower) {
    PlayerState *p;

    if (thrower->collisionFlags & 1) {
        p = thrower->customState;
        if (p->heldActor != NULL) {
            actorAppendCallback4000(gCurrentActor, p->heldActor, gActivePlayerActor->yaw, D_80753428[gCurrentCharacterIndex], (s32)D_8075340C[gCurrentCharacterIndex]);
            p->heldActor = NULL;
            p->queuedHeldActor = NULL;
        }
    }
}


void playerDropHeldActor(Actor *player) {
    PlayerState *p;

    if (player->collisionFlags & 1) {
        p = player->customState;
        if (p->heldActor != NULL) {
            actorAppendCallback(p->heldActor, player, 8, 0, 0, NULL);
        } else if (p->queuedHeldActor != NULL) {
            actorAppendCallback(p->queuedHeldActor, player, 8, 0, 0, NULL);
        }
        p->heldActor = NULL;
        p->queuedHeldActor = NULL;
    }
}


void actorReleaseFromPlayerHold(Actor *actor) {
    s32 i;
    PlayerState *p;

    for (i = 0; i < gPlayerCount; i++) {
        if (gPlayerSlots[i].active != 0) {
            p = gPlayerSlots[i].actor->customState;
            if ((actor == p->heldActor && p->heldActor != NULL) || (actor == p->queuedHeldActor && p->queuedHeldActor != NULL)) {
                p->heldActor = NULL;
                p->queuedHeldActor = NULL;
                playerResumeLocomotion(gPlayerSlots[i].actor);
            }
        }
    }
}

extern u8 D_80750AD0;
extern u8 D_8071FC40;

void func_806CF580(void) {
    if (!(gCurrentActor->flags & 0x10)) {
        gActivePlayerState->unk84 = gFrameCounter;
        gActivePlayerState->unkD0 = gFrameCounter;
    }
    if (gPlayerCharacterId[gCurrentPlayerIndex] == 1) {
        if (gCurrentActor->state == 0x36 && gActivePlayerState->prevState != 0x36) {
            animSetFrameAndSubframe(gCurrentActor, 1, 0, 6.0f);
        }
        if (gCurrentActor->state == 0x36) {
            animSetSpeed(gCurrentActor, 0, 0.5f);
            animSetLoopMode(gCurrentActor, 0, 0);
            animSetDirection(gCurrentActor, 0, 0);
            animResetEndFrame(gCurrentActor, 0);
            animSetStartFrame(gCurrentActor, 0, 4);
            animSetLoopLimit(gCurrentActor, 0, 2);
            animSetSpeed(gCurrentActor, 1, 0.5f);
            animSetLoopMode(gCurrentActor, 1, 0);
            animSetDirection(gCurrentActor, 1, 0);
            animResetEndFrame(gCurrentActor, 1);
            animSetStartFrame(gCurrentActor, 1, 4);
            animSetLoopLimit(gCurrentActor, 1, 2);
        }
        if (gCurrentActor->state != 0x36) {
            if (gActivePlayerState->prevState == 0x36) {
                gActivePlayerState->unk84 = 0;
            }
        }
    }
    if (gCurrentActor->state != 0x36 && func_8072881C(0, &gActivePlayerState->unk84) != 0 &&
        (gPlayerCharacterId[gCurrentPlayerIndex] == 1 || (gPlayerCount == 1 && gPlayerCharacterId[gCurrentPlayerIndex] == 3))) {
        func_8072881C(0x81, &gActivePlayerState->unk84);
    }
    if ((gCurrentActor->state == 0x4F || gCurrentActor->state == 0x7F) && D_80750AD0 == 0 &&
        (u32)(gActivePlayerState->unkD0 + 9) < (u32)gFrameCounter && (u32)randomLcgNext() % 2500 / 200 == 0) {
        effectSetCallback(effectWobbleRiseUpdate);
        effectSetDepth(1);
        effectSetDuration(-1);
        effectCreateAtActorBone(&D_8071FC40, 0, gCurrentActor, 4, 0);
        gActivePlayerState->unkD0 = gFrameCounter;
    }
}


void playerSpawnJumpTrailEffects(void) {
    if (!(gFrameCounter & 3) && gCurrentActor->unk155 >= 5 && gCurrentActor->speedY > 30.0f) {
        effectSetMode(2);
        effectSetDepth(1);
        effectSetCallback(effectZSpinMatrixUpdate);
        effectCreateAtPosition(&D_8071FB08, 0.8f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
    }
}

extern s32 D_8071FF40;

void playerSpawnSpiralDriftEffects(void) {
    s32 i;

    for (i = 0; i != 0xC8; i += 0x28) {
        effectSetCallback(effectSpiralDriftMatrixUpdate);
        effectSetDepth(1);
        effectSetSpeed(i);
        effectSetDuration(0x45);
        effectCreateAtActorBone(&D_8071FF40, 0.05f, gCurrentActor, 6, 2);
    }
}


extern f32 D_80753E10[];
extern s16 D_80753E00[];

void playerCheckLedgeGrab(void) {
    f32 ledgeY;
    u8 foundLedge;
    s16 coordX;
    s16 coordY;
    u8 notWall;
    u8 hit;
    u8 flag;
    s32 pad[2];

    if (!(gGlobalOverlayFlags & 0x20000) && gCurrentActor->hasArcBounds != 0 && gActivePlayerState->gunDrawn == 0 && !(gCurrentActor->contactFlags & 1) && gActivePlayerState->stateStep != 0) {
        flag = (gCurrentMap == 0x53 || gCurrentMap == 0xC5) ? 1 : 0;
        notWall = actorAngleInArc(gCurrentActor, gCurrentActor->yaw) == 0;
        if (notWall || !(D_80753E10[gCurrentCharacterIndex] < gCurrentActor->speedXZ) || flag != 0) {
            foundLedge = playerProbeLedgeAhead(gCurrentActor, &ledgeY, notWall, flag ? 30.0 : 15.0);
            collisionGetCoords(&coordX, &coordY);
            hit = 0;
            if (foundLedge != 0 && gCurrentActor->speedY < 0.0 && coordY >= 0x385) {
                hit = 0;
                if (collisionGetHitFlags() != 0) {
                    if (gCurrentActor->y - gCurrentActor->floorY > 15.0f) {
                        if (flag != 0) {
                            if (D_80753E00[gCurrentCharacterIndex] + gCurrentActor->y < ledgeY + 15.0f && ledgeY - D_80753E00[gCurrentCharacterIndex] - gCurrentActor->y < 80.0f) {
                                hit = 1;
                            }
                        } else {
                            if (D_80753E00[gCurrentCharacterIndex] + gCurrentActor->y < ledgeY - 5.0f && ledgeY - D_80753E00[gCurrentCharacterIndex] - gCurrentActor->y < 15.0f) {
                                hit = 1;
                            }
                        }
                    }
                }
            }
            if (hit != 0 && playerStateQueueCallback(0xA, NULL, gCurrentPlayerIndex) != 0) {
                gActivePlayerState->unkF0 = ledgeY;
            }
        }
    }
}

u8 playerProbeLedgeAhead(Actor *actor, f32 *outFloorY, u8 forward, f32 distance) {
    f32 dx;
    f32 dz;
    s16 angle;
    u8 found;

    angle = actor->yaw;
    if (!forward) {
        angle = (angle + 0x800) & 0xFFF;
    }
    dx = mathSinF(angle) * distance;
    dz = mathCosF(angle) * distance;
    found = collisionCheckActorFloor(actor, actor->x + dx, actor->y + 30.0f, actor->z + dz, outFloorY);
    actor->unk78[0] = collisionGetSurfaceFlags();
    return found;
}


void playerSetBaseGravityIfFalling(void) {
    if (gCurrentActor->speedY < 0.0f) {
        playerSetBaseGravity();
    }
}

extern f32 D_80753700[];

void playerSetTerminalVelocity700(void) {
    if (gCurrentActor->speedY < 0.0f) {
        gCurrentActor->accelY = D_80753700[gCurrentCharacterIndex];
    }
}

extern f32 D_80753658[];

void playerSetTerminalVelocity658(void) {
    if (gCurrentActor->speedY < 0.0f) {
        gCurrentActor->accelY = D_80753658[gCurrentCharacterIndex];
    }
}

extern f32 D_80753754[];

void playerSetTerminalVelocity754(void) {
    if (gCurrentActor->speedY < 0.0f) {
        gActivePlayerActor->accelY = D_80753754[gCurrentCharacterIndex];
    }
}

extern f32 D_80753578[];

void playerSetBaseGravity(void) {
    gActivePlayerActor->accelY = D_80753578[gCurrentCharacterIndex];
}

extern f32 D_80753594[];

void playerSetTerminalVelocity594(void) {
    gActivePlayerActor->accelY = D_80753594[gCurrentCharacterIndex];
}

extern f32 D_807535B0[];

void playerSetTerminalVelocity5B0(void) {
    gActivePlayerActor->accelY = D_807535B0[gCurrentCharacterIndex];
}

extern f32 D_807536E4[];

void playerSetTerminalVelocity6E4(void) {
    gActivePlayerActor->accelY = D_807536E4[gCurrentCharacterIndex];
}

void playerEnterFall(Actor *actor) {
    gCurrentActor->speedY = 0.0f;
    actorScriptStartByIndex(actor, 0x1B);
    actorScriptExecute(actor);
    gCurrentActor->peakY = gCurrentActor->y;
    if (gActivePlayerState->gunDrawn) {
        actor->state = 0x1F;
        actor->unk155 = 0;
    } else {
        actor->state = 0x1E;
        actor->unk155 = 0;
    }
}


void playerResumeLocomotion(Actor *actor) {
    PlayerState *p = actor->customState;
    u8 nextState;

    actor->contactFlags &= ~0x20;
    p->unk4C = -1;
    p->unk10C = 0;
    if (actor->unk144 == 1) {
        actorSetInteractionTimer(actor);
    }
    if (gGlobalOverlayFlags & 0x80000) {
        if (p->actor != NULL && p->actor->actorType == 0x1D) {
            playerEnterBarrelTransition(actor);
            return;
        }
    }
    if (gPlayerCharacterId[gCurrentPlayerIndex] == 7) {
        actor->state = 0x7E;
        actor->unk155 = 0;
        return;
    }
    if ((p->stateFlags & 0x20) && gPlayerCount == 1) {
        nextState = playerSelectSurfaceState(actor, actor->speedXZ, p->maxSpeed, 1);
        actor->state = nextState;
        actor->unk155 = 0;
        if (nextState == 0x3F) {
            actor->unk155 = 1;
        }
    } else if (p->heldActor != NULL) {
        actor->state = playerSelectCarryMoveState(actor, actor->speedXZ, p->maxSpeed, 1);
        actor->unk155 = 0;
    } else if (p->gunDrawn != 0) {
        nextState = playerSelectCarryState(actor, actor->speedXZ, p->maxSpeed, 1);
        if (actor->state != 2) {
            actor->state = nextState;
            actor->unk155 = 0;
        }
    } else {
        nextState = playerSelectWalkRunState(actor, actor->speedXZ, p->maxSpeed, 1);
        if (actor->state != 2) {
            actor->state = nextState;
            actor->unk155 = 0;
        }
    }
}

void playerEnterBarrelTransition(Actor *actor) {
    actor->contactFlags &= ~0x20;
    gActivePlayerState->unk4C = -1;
    gActivePlayerState->unk10C = 0;
    actorScriptStartByIndex(actor, 0x7A);
    actor->state = 7;
    actor->unk155 = 0;
}

extern s16 D_80753328[];
extern f32 D_807532F0[];
extern f32 D_8075330C[];
extern f32 D_807532B8[];
extern f32 D_807532D4[];

void playerSetCarryMoveParams(void) {
    gActivePlayerState->turnRate = D_80753328[gCurrentCharacterIndex];
    gActivePlayerState->airAccel = D_807532F0[gCurrentCharacterIndex];
    gActivePlayerState->decelRate = D_8075330C[gCurrentCharacterIndex];
    gActivePlayerState->unk34 = D_807532B8[gCurrentCharacterIndex];
    gActivePlayerState->targetSpeed = D_807532D4[gCurrentCharacterIndex];
}

extern f32 D_80753338[];

void playerSetNormalMoveParams(void) {
    gActivePlayerState->turnRate = D_8075326C[gCurrentCharacterIndex];
    gActivePlayerState->airAccel = D_80753234[gCurrentCharacterIndex];
    gActivePlayerState->decelRate = gKongCannonInitialPitch[gCurrentCharacterIndex];
    gActivePlayerState->unk34 = D_80753170[gCurrentCharacterIndex];
    if (gActivePlayerState->gunDrawn != 0) {
        gActivePlayerState->targetSpeed = D_80753338[gCurrentCharacterIndex];
        return;
    }
    if ((gActivePlayerState->stateFlags & 0x20) || D_807463B8 == 3) {
        if (gCurrentMap == 0x30) {
            gActivePlayerState->targetSpeed = 200.0f;
            return;
        }
        gActivePlayerState->targetSpeed = D_80753218[gCurrentCharacterIndex];
        return;
    }
    gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
}

void playerSetTerminalVelocity578(void) {
    gActivePlayerActor->accelY = D_80753578[gCurrentCharacterIndex];
    gActivePlayerState->unk50 = 0;
    gActivePlayerState->unk28 = 1;
}


void playerInitMoveParams(void) {
    if (gActivePlayerState->heldActor != NULL) {
        playerSetCarryMoveParams();
    } else {
        playerSetNormalMoveParams();
    }
    playerSetTerminalVelocity578();
}

void playerInitNormalMoveParams(void) {
    playerSetNormalMoveParams();
    playerSetTerminalVelocity578();
}

extern f32 gPlayerLargeModeScale;

void playerSetLargeModeScale(f32 scale) {
    if (scale != 0.0f) {
        gPlayerLargeModeScale = scale;
    } else {
        gPlayerLargeModeScale = 0.3f;
    }
}


void playerSetSizeMode(Actor *actor, u8 mode) {
    PlayerState *state = actor->customState;
    u8 slot = state->playerIndex;
    s32 i;
    f32 diff;
    f32 steps;

    state->targetScaleFactor = 0.4f;
    state->scaleChangeRate = 0.004f;
    switch (mode) {
        case 0:
            state->targetScale[0] = 0.05f;
            state->targetScale[1] = 0.05f;
            state->targetScale[2] = 0.05f;
            break;
        case 2:
            state->targetScale[0] = gPlayerLargeModeScale;
            state->targetScale[1] = gPlayerLargeModeScale;
            state->targetScale[2] = gPlayerLargeModeScale;
            break;
        default:
            state->targetScale[0] = 0.15f;
            state->targetScale[1] = 0.15f;
            state->targetScale[2] = 0.15f;
            if (gPlayerSlots[slot].unk2C0 == 0) {
                state->targetScaleFactor = 0.05f;
                state->scaleChangeRate = 0.001f;
            }
            break;
    }
    if (mode != 1) {
        if (gPlayerCount == 1) {
            for (i = 0; i < 3; i++) {
                state->currentScale[i] = state->targetScale[i];
                (&actor->sub4->scaleX)[i] = state->targetScale[i];
            }
        }
    }
    gPlayerSlots[slot].unk2C0 = mode;
    gPlayerSlots[slot].sizeModeDirty = 1;
    state->scaleMode = 0;
    if (mode == 1 || gPlayerCount >= 2) {
        if (state->currentScale[0] < state->targetScale[0]) {
            diff = state->targetScale[0] - state->currentScale[0];
        } else {
            diff = -(state->targetScale[0] - state->currentScale[0]);
        }
        steps = diff / state->scaleChangeRate;
        if (steps != 0.0f) {
            state->scaleStep = state->targetScaleFactor / steps;
        } else {
            state->scaleStep = 99999.0f;
        }
    }
    camSetZoomLevel(state->camActor, 2);
}



void playerScaleTransitionStep(void) {
    if (gActivePlayerState->currentScale[0] < gActivePlayerState->targetScale[0]) {
        gActivePlayerState->currentScale[0] = gActivePlayerState->currentScale[0] + gActivePlayerState->scaleChangeRate;
        gActivePlayerState->currentScale[1] = gActivePlayerState->currentScale[1] + gActivePlayerState->scaleChangeRate;
        gActivePlayerState->currentScale[2] = gActivePlayerState->currentScale[2] + gActivePlayerState->scaleChangeRate;
        if (gActivePlayerState->targetScale[0] < gActivePlayerState->currentScale[0]) {
            gActivePlayerState->currentScale[0] = gActivePlayerState->targetScale[0];
            gActivePlayerState->currentScale[1] = gActivePlayerState->targetScale[1];
            gActivePlayerState->currentScale[2] = gActivePlayerState->targetScale[2];
        }
    } else {
        gActivePlayerState->currentScale[0] = gActivePlayerState->currentScale[0] - gActivePlayerState->scaleChangeRate;
        gActivePlayerState->currentScale[1] = gActivePlayerState->currentScale[1] - gActivePlayerState->scaleChangeRate;
        gActivePlayerState->currentScale[2] = gActivePlayerState->currentScale[2] - gActivePlayerState->scaleChangeRate;
        if (gActivePlayerState->currentScale[0] < gActivePlayerState->targetScale[0]) {
            gActivePlayerState->currentScale[0] = gActivePlayerState->targetScale[0];
            gActivePlayerState->currentScale[1] = gActivePlayerState->targetScale[1];
            gActivePlayerState->currentScale[2] = gActivePlayerState->targetScale[2];
        }
    }
    if (gActivePlayerState->currentScale[0] == gActivePlayerState->targetScale[0]) {
        gCurrentActor->sub4->scaleX = gActivePlayerState->currentScale[0];
        gCurrentActor->sub4->scaleY = gActivePlayerState->currentScale[1];
        gCurrentActor->sub4->scaleZ = gActivePlayerState->currentScale[2];
        return;
    }
    gCurrentActor->sub4->scaleX = gActivePlayerState->currentScale[0] + sinApprox(gActivePlayerState->scaleMode * 0.11) * gActivePlayerState->targetScaleFactor;
    gCurrentActor->sub4->scaleY = gActivePlayerState->currentScale[1] + sinApprox(gActivePlayerState->scaleMode * 0.2352) * gActivePlayerState->targetScaleFactor;
    gCurrentActor->sub4->scaleZ = gActivePlayerState->currentScale[2] + sinApprox(gActivePlayerState->scaleMode * 0.176) * gActivePlayerState->targetScaleFactor;
    gActivePlayerState->targetScaleFactor = gActivePlayerState->targetScaleFactor - gActivePlayerState->scaleStep;
    if (gActivePlayerState->targetScaleFactor < 0.0) {
        gActivePlayerState->targetScaleFactor = 0.0f;
    }
    gActivePlayerState->scaleMode = gActivePlayerState->scaleMode + 1;
}

s32 playerSlotMatchesSizeMask(s32 mask, u8 playerIndex) {
    s16 type = gPlayerSlots[playerIndex].actor->actorType;

    if (type != 6) {
        if (type == 8) {
            if (mask & 2) {
                return 1;
            }
        }
    } else {
        if ((mask & 1) && gPlayerSlots[playerIndex].unk2C0 != 1) {
            return 1;
        }
    }
    return 0;
}

extern s32 gGlobalCutsceneFlags;


void func_806D09E8(Actor *actor) {
    u8 state;

    if (actor->actorType == 4) {
        state = actor->state;
        if (state == 0x3F || state == 0x40) {
            if (!(gGlobalCutsceneFlags & 0x40)) {
                if (collisionGetHitStatus() == 0) {
                    actor->floorSlopeType = 0x10;
                }
            }
        }
    }
}

void playerSetRenderFlag4(Actor *actor, s32 enable, s32 unused) {
    if (enable) {
        actor->flags |= 4;
    } else {
        actor->flags &= ~4;
    }
}

typedef struct ChildEffectState {
    /* 0x00 */ u16 scriptA;
    /* 0x02 */ u16 scriptB;
    /* 0x04 */ Actor *target;
    /* 0x08 */ s32 targetId;
    /* 0x0C */ u16 targetAnim;
    /* 0x0E */ u8 padE[2];
    /* 0x10 */ f32 yOffset;
} ChildEffectState;



void actorChildEffectUpdate(void) {
    ChildEffectState *state = gCurrentActor->customState;
    Actor *target = state->target;
    f32 speed;
    s32 pad[1];
    f32 dist;

    if (!(gCurrentActor->flags & 0x10)) {
        actorScriptStart(gCurrentActor, state->scriptA);
        gCurrentActor->flags |= 0x400;
        gCurrentActor->yawSpeed = (randomNonNegative() >> 15) % 4096;
    }
    speed = (gCurrentActor->sub4 != NULL ? gCurrentActor->sub4->scaleY : 0.15f) * 6.66666667;
    if (actorTableContains(target) == 0 || target->instanceId != state->targetId) {
        actorDespawn(gCurrentActor);
        return;
    }
    switch (gCurrentActor->state) {
        case 0:
            if (target->sub4->animId != state->targetAnim) {
                actorScriptStart(gCurrentActor, state->scriptB);
            } else {
                actorCopyPoseAndScale(gCurrentActor, target, gCurrentActor->sub4->scaleX);
                gCurrentActor->y += state->yOffset;
            }
            break;
        case 1:
            gCurrentActor->speedY = gCurrentActor->speedY + 0.2;
            gCurrentActor->y = gCurrentActor->y + speed * gCurrentActor->speedY;
            break;
        case 2:
            gCurrentActor->speedY = gCurrentActor->speedY - 0.2;
            gCurrentActor->y = gCurrentActor->y + speed * gCurrentActor->speedY;
            break;
        case 3:
            gCurrentActor->yawSpeed += 0x28;
            gCurrentActor->yawSpeed &= 0xFFF;
            if (gCurrentActor->speedXZ < 1.2) {
                gCurrentActor->speedXZ = gCurrentActor->speedXZ + 0.15;
            }
            dist = gCurrentActor->speedXZ * speed;
            gCurrentActor->x += dist * mathSinF(gCurrentActor->yawSpeed);
            gCurrentActor->z += dist * mathCosF(gCurrentActor->yawSpeed);
            if (gCurrentActor->speedY < 2.5) {
                gCurrentActor->speedY = gCurrentActor->speedY + 0.2;
            }
            gCurrentActor->y = gCurrentActor->y + speed * gCurrentActor->speedY;
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


u8 playerIsSmallerThanAttacker(Actor *victim, Actor *attacker) {
    s32 result;
    s32 attackerNotRolling;
    u8 victimSize;
    u8 attackerSize;
    PlayerState *victimState;
    PlayerState *attackerState;

    victimSize = 1;
    attackerSize = 1;
    attackerNotRolling = 1;
    if ((gPlayerCount < 2) || ((victim->collisionFlags & 4) != 0) || ((attacker->collisionFlags & 4) != 0)) {
        return 0;
    }
    if (victim->collisionFlags & 1) {
        victimState = victim->customState;
        victimSize = gPlayerSlots[victimState->playerIndex].unk2C0;
    }
    if (attacker->collisionFlags & 1) {
        attackerState = attacker->customState;
        attackerSize = gPlayerSlots[attackerState->playerIndex].unk2C0;
        attackerNotRolling = attacker->state != 0x7C;
    }
    result = victimSize < attackerSize;
    if (result != 0) {
        result = attackerNotRolling != 0;
    }
    return result;
}

extern s16 D_8075388C[];
extern s16 D_807538C8[];
extern s16 D_8075387C[];
extern s16 D_807538B8[];

void playerClampWaterSurfaceHeight(Actor *unused) {
    f32 height;
    f32 limit;
    s32 pad[1];
    u8 type;

    type = gPlayerSlots[gCurrentPlayerIndex].unk2C0;
    if (type == 1) {
        height = D_8075388C[gCurrentCharacterIndex];
    } else {
        height = D_807538C8[gCurrentCharacterIndex];
    }
    if (type == 1) {
        limit = D_8075387C[gCurrentCharacterIndex];
    } else {
        limit = D_807538B8[gCurrentCharacterIndex];
    }
    if (gCurrentActor->waterY - gCurrentActor->floorY < limit) {
        playerStateQueueCallback(2, NULL, gCurrentPlayerIndex);
        return;
    }
    if (gCurrentActor->waterY < gCurrentActor->y + height) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x10, 0xFF, 0x7F, 1);
        gCurrentActor->y = gCurrentActor->waterY - height;
        gCurrentActor->speedY = 0.0f;
        actorScriptStartByIndex(gCurrentActor, 0x3D);
        gActivePlayerState->decelRate = gKongCannonInitialPitch[gCurrentCharacterIndex];
        gCurrentActor->state = 0x4E;
        gCurrentActor->unk155 = 0;
    }
}

s16 mathAngleFromVector2D(f32 x, f32 z) {
    s16 angle = (s32)(mathAtan2(x, z) * 4096.0f / 6.2831855f);

    angle -= 0x400;
    return angle & 0xFFF;
}

s32 playerCanCollideWithActor(Actor *actor) {
    s32 result = 1;

    if (actor->collisionFlags & 1) {
        if (gPlayerStateFlags[actor->state][0] & 0x400) {
            result = 0;
        }
    }
    return result;
}
