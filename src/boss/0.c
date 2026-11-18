#include "common.h"
#include "actor.h"
#include "boss.h"
#include "proto/boss/0.h"
#include "proto/boss/3840.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/1295B0.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/63EC0.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/80150.h"
#include "proto/global/89250.h"
#include "proto/global/8CA50.h"
#include "proto/global/8F050.h"
#include "proto/global/936B0.h"

// Bone indices of the six smoke puffs bossArmydilloSpawnSmoke spawns (sArmydilloSmokeBones).
typedef struct BossSmokeBones {
    u8 bones[6];
} BossSmokeBones;

extern Actor *gCurrentActor;
extern BossSmokeBones sArmydilloSmokeBones;
extern u8 sEffectSparkConfig[];


void bossArmydilloSpawnSmoke(void) {
    s16 i;

    for (i = 0; i < 6; i++) {
        BossSmokeBones smokeBones = sArmydilloSmokeBones;

        tagBarrelSpawnNodeSmokePuffs(gCurrentActor, smokeBones.bones[i], 3.0f);
    }

    for (i = 0; i < 12; i++) {
        effectSetCallback(effectDecelDriftFadeUpdate);
        effectSetSpeed(i);
        effectSetDepth(1);
        effectSetColor(0x8C, 0x8C, 0x8C, 0xFF);
        effectSetMode(3);
        effectCreateAtPosition(sEffectSparkConfig, 2.5f, gCurrentActor->x, gCurrentActor->y + 40.0f, gCurrentActor->z);
    }
}

// Stowed pose of one armadillo piece (sArmydilloPiecePoses[arena mode][piece]): bone offset and bone scale.
// bossPieceStep moves a piece from it to offset 0, scale 1 and back.
typedef struct BossPiecePose {
    s8 x;
    s8 y;
    s8 z;
    u8 pad3;
    f32 scaleX;
    f32 scaleY;
    f32 scaleZ;
} BossPiecePose;

extern s32 gCurrentMap;
extern u8 sArmydilloPieceBones[5];
extern BossPiecePose sArmydilloPiecePoses[][5];
extern u8 D_80035994[8];

void bossArmydilloInitArena(void) {
    s32 pad[4];
    u8 mode;
    s16 i;
    ActorSub4 *sub;
    BoneVector *offset;
    BoneVector *scale;
    BoneRotation *rotation;
    BossPiecePose *pose;

    if (gCurrentMap == 8) {
        mode = 0;
    } else {
        mode = 1;
    }
    if (mode == 0) {
        if (flagGet(0x68, 2) != 0) {
            mode = 1;
            gCurrentActor->segmentFlags = 3;
        }
    }
    func_80724D28(1, 0xD);
    func_80724DB0(1, 5);
    func_80724CA4(1, 5);

    sub = gCurrentActor->sub4;
    pose = sArmydilloPiecePoses[mode];
    offset = sub->boneOffsets;
    scale = sub->boneScales;
    rotation = sub->boneRotations;

    for (i = 0; i < 5; i++) {
        offset->bone = sArmydilloPieceBones[i];
        offset->lastBone = 0xFF;
        offset->x = pose[i].x;
        offset->y = pose[i].y;
        offset->z = pose[i].z;

        scale->bone = sArmydilloPieceBones[i];
        scale->lastBone = 0xFF;
        scale->x = pose[i].scaleX;
        scale->y = pose[i].scaleY;
        scale->z = pose[i].scaleZ;

        rotation->weight = -0x80;
        rotation->bone = sArmydilloPieceBones[i];
        rotation->rotX = 0;
        rotation->rotY = 0;
        rotation->rotZ = 0;

        offset++;
        scale++;
        rotation++;
    }

    for (i = 0; i < 8; i++) {
        offset->bone = D_80035994[i];
        offset->lastBone = 0xFF;
        offset->x = 0.0f;
        offset->y = 0.0f;
        offset->z = 0.0f;
        offset++;
    }
}


void bossArmydilloDebrisUpdate(void) {
    s16 i;
    BoneVector *debris;
    s16 soundId;
    u8 soundVol;
    s16 angle;

    debris = gCurrentActor->sub4->boneOffsets;
    soundId = 0;
    soundVol = 0xFF;
    switch (gBehaviourWorkState->timer) {
    case 19:
        soundId = 0x22;
        break;
    case 17:
        soundId = 0xF6;
        break;
    case 15:
        soundId = 0x17;
        break;
    case 13:
        soundId = 0xED;
        break;
    case 11:
        soundId = 0x18;
        break;
    case 9:
        soundId = 0x22;
        soundVol = 0xC8;
        break;
    case 7:
        soundId = 0xED;
        soundVol = 0x82;
        break;
    case 5:
        soundId = 0x18;
        soundVol = 0x46;
        break;
    case 3:
        soundId = 0x3C;
        break;
    }

    if (soundId != 0) {
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, soundId, soundVol, 0x7F, 1, 0x1E, 0.3f, 0);
    }

    gCurrentActor->sub4->boneOffsets[5].x = 99999.0f;
    for (i = 0; i < 13; i++) {
        if (debris->y >= 1800.0f) {
            debris->x = 99999.0f;
            debris->y = 99999.0f;
            debris->z = 99999.0f;
            debris++;
        } else {
            angle = i * 400;
            debris->x += 200.0f * mathSinF(angle);
            debris->z += 200.0f * mathCosF(angle);
            debris->y += 100.0f;
            debris++;
        }
    }
}

// Armadillo piece/cannon animation state (BossArmydilloActor.pieceAnim): per piece a timer, a state, an angle
// and a fly-off velocity.
typedef struct BossPieceAnim {
    /* 0x00 */ u8 endSfxPlayed; // sfx 0x174 played once the cannon-open animation ended (bossArmydilloStep)
    /* 0x01 */ u8 timer[5]; // frames into the detach/attach move (bossPieceStep states 1-4)
    /* 0x06 */ u8 state[5];
    /* 0x0B */ u8 pad0B;
    union {
        /* 0x0C */ s16 ang[5]; // fly-off heading per piece (bossPieceStep states 5-6)
        struct {
            /* 0x0C */ u8 pad0C[4];
            /* 0x10 */ s16 cannonAngA; // bone 2 rotX (bossArmydilloStep, bossPieceSetAngle(2, ...))
            /* 0x12 */ s16 cannonAngB; // bone 3 rotX
            /* 0x14 */ u8 pad14[2];
        };
    };
    /* 0x16 */ u8 pad16[2];
    /* 0x18 */ f32 speedXZ[5]; // fly-off speed along ang
    /* 0x2C */ f32 speedY[5]; // fly-off vertical speed: -10 per frame, halved and reversed on a bounce
} BossPieceAnim; // size = 0x40

void bossPieceSetState(BossPieceAnim *pieceData, u8 index, u8 state) {
    pieceData->state[index] = state;
}

void bossPieceSetAngle(u8 index, s16 angle) {
    BoneRotation *entry = &gCurrentActor->sub4->boneRotations[index];
    if (index == 3) {
        entry->bone = 0x2F;
    }
    entry->rotX = angle;
}

u8 bossPieceStep(BossPieceAnim *animData, u8 pieceIdx, f32 maxTimer, f32 scriptTimer, f32 endTimer) {
    u8 ret;
    BoneVector *offset;
    BoneVector *scale;
    Actor *boss;

    boss = gCurrentActor;
    ret = 0;
    offset = &boss->sub4->boneOffsets[pieceIdx];
    scale = &boss->sub4->boneScales[pieceIdx];
    switch (animData->state[pieceIdx]) {
    case 5:
        animData->speedXZ[pieceIdx] = 30.0f;
        animData->ang[pieceIdx] = pieceIdx * 0x800 + 0x400;
        animData->speedY[pieceIdx] = 100.0f;
        animData->state[pieceIdx] = 6;
        /* fallthrough */
    case 6:
        offset->x += animData->speedXZ[pieceIdx] * mathSinF(animData->ang[pieceIdx]);
        offset->z += animData->speedXZ[pieceIdx] * mathCosF(animData->ang[pieceIdx]);
        offset->y += animData->speedY[pieceIdx];
        animData->speedY[pieceIdx] -= 10.0f;
        if (animData->speedY[pieceIdx] < -200.0f) {
            animData->speedY[pieceIdx] = -200.0f;
        }
        if (offset->y < -300.0f) {
            offset->y = -300.0f;
            if (-50.0f < animData->speedY[pieceIdx]) {
                tagBarrelSpawnNodeSmokePuffs(gCurrentActor, pieceIdx + 1, 1.5f);
                actorClearSegmentFlag(gCurrentActor, pieceIdx);
                animData->state[pieceIdx] = 0;
                ret = 1;
                break;
            }
            if (!pieceIdx) {
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x36, 120.0f - animData->speedY[pieceIdx] > 255.0f ? 255.0f : 120.0f - animData->speedY[pieceIdx], 0x7F, 0x28, 0, 0.3f, 0);
            }
            animData->speedY[pieceIdx] *= -0.5;
        }
        break;
    case 1:
        switch (pieceIdx) {
        case 0:
            sfxPlayActorSound(gCurrentActor, 0x127, 0, 1, 1, 0xFF, 1.0f, 0);
            break;
        case 2:
            sfxPlayActorSound(gCurrentActor, 0x127, 0, 1, 1, 0xFF, 1.1f, 0);
            break;
        case 4:
            sfxPlayActorSound(gCurrentActor, 0x127, 0, 1, 1, 0xFF, 1.3f, 0);
            break;
        }
        actorSetSegmentFlag(gCurrentActor, pieceIdx);
        animData->state[pieceIdx] = 2;
        animData->timer[pieceIdx] = 0;
        /* fallthrough */
    case 2:
        if (++animData->timer[pieceIdx] < maxTimer) {
            f32 t = animData->timer[pieceIdx] / maxTimer;
            offset->x = sArmydilloPiecePoses[0][pieceIdx].x + (-sArmydilloPiecePoses[0][pieceIdx].x) * t;
            offset->y = sArmydilloPiecePoses[0][pieceIdx].y + (-sArmydilloPiecePoses[0][pieceIdx].y) * t;
            offset->z = sArmydilloPiecePoses[0][pieceIdx].z + (-sArmydilloPiecePoses[0][pieceIdx].z) * t;
        } else if (maxTimer == animData->timer[pieceIdx]) {
            switch (pieceIdx) {
            case 0:
            case 2:
            case 4:
                sfxStopSlotSound(gCurrentActor, 1);
                break;
            }
        } else if (scriptTimer == animData->timer[pieceIdx]) {
            switch (gCurrentActor->state) {
            case 0x27:
                actorScriptStart(gCurrentActor, 0x264);
                break;
            case 0x2E:
                actorScriptStart(gCurrentActor, 0x265);
                break;
            default:
                actorScriptStart(gCurrentActor, 0x266);
                break;
            }
        } else if (scriptTimer + 1.0f == animData->timer[pieceIdx]) {
            scale->x = 1.0f;
            scale->y = 1.0f;
            scale->z = 1.0f;
        } else if (endTimer < animData->timer[pieceIdx]) {
            ret = 1;
            animData->state[pieceIdx] = 0;
        }
        break;
    case 3:
        switch (pieceIdx) {
        case 0:
            sfxPlayActorSound(gCurrentActor, 0x127, 0, 1, 1, 0xFF, 1.0f, 0);
            break;
        case 2:
            sfxPlayActorSound(gCurrentActor, 0x127, 0, 1, 1, 0xFF, 1.1f, 0);
            break;
        }
        animData->state[pieceIdx] = 4;
        animData->timer[pieceIdx] = endTimer;
        /* fallthrough */
    case 4:
        if (maxTimer < --animData->timer[pieceIdx]) {
            scale->x = scale->x + (sArmydilloPiecePoses[0][pieceIdx].scaleX - scale->x) * 0.08;
            scale->y = scale->y + (sArmydilloPiecePoses[0][pieceIdx].scaleY - scale->y) * 0.08;
            scale->z = scale->z + (sArmydilloPiecePoses[0][pieceIdx].scaleZ - scale->z) * 0.09;
        } else if (animData->timer[pieceIdx] > 0) {
            f32 t = animData->timer[pieceIdx] / maxTimer;
            offset->x = sArmydilloPiecePoses[0][pieceIdx].x + (-sArmydilloPiecePoses[0][pieceIdx].x) * t;
            offset->y = sArmydilloPiecePoses[0][pieceIdx].y + (-sArmydilloPiecePoses[0][pieceIdx].y) * t;
            offset->z = sArmydilloPiecePoses[0][pieceIdx].z + (-sArmydilloPiecePoses[0][pieceIdx].z) * t;
        } else {
            actorClearSegmentFlag(gCurrentActor, pieceIdx);
            animData->state[pieceIdx] = 0;
            if (pieceIdx == 0 || pieceIdx == 2) {
                sfxStopSlotSound(gCurrentActor, 1);
            }
            ret = 1;
        }
        break;
    }
    return ret;
}

s16 mathAngleSignedDistance(s16, s16);
void actorMoveWithinZone(s32, f32, f32, s32, f32); // ORIG: the target passes bossArmydilloStep's int ternary flags (0x210/0x212) straight to a3 at 0x287C/0x2880 (li a3); the owner's u16 prototype adds a sw/lhu 82(sp) narrowing, so these callers saw an s32 flags parameter

void bossArmydilloAimTowardTarget(void) {
    s32 yawDiff;
    u16 animState;

    animState = gCurrentActor->sub4->animId;
    mathAngleSignedDistance(gBehaviourWorkState->targetYaw, gCurrentActor->yaw);
    actorMoveWithinZone(0x45, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x16, 0.0f);
    yawDiff = mathAngleSignedDistance(gBehaviourWorkState->targetYaw, gCurrentActor->yaw);
    if (yawDiff > 0) {
        if (animState != 0x260) {
            actorScriptStart(gCurrentActor, 0x260);
        }
    } else if (yawDiff < 0) {
        if (animState != 0x25F) {
            actorScriptStart(gCurrentActor, 0x25F);
        }
    } else if (animState != 0x25A) {
        actorScriptStart(gCurrentActor, 0x25A);
        scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
    }
}

void bossArmydilloOpenCannons(void *state, BossPieceAnim *pieceData, u8 *script, u8 *pieceList) {
    u8 i;
    u8 done;

    i = 0;
    done = 0;
    switch (gCurrentActor->unk155) {
    case 2:
        while (pieceList[i] != 0xFF) {
            bossPieceSetState(pieceData, pieceList[i++], 1);
        }
        gCurrentActor->unk155 = 3;
        break;
    case 3:
        while (pieceList[i] != 0xFF) {
            if (gCurrentActor->state == 0x27 || gCurrentActor->state == 0x2E) {
                done = bossPieceStep(pieceData, pieceList[i++], 50.0f, 70.0f, 90.0f);
            } else {
                done = bossPieceStep(pieceData, pieceList[i++], 10.0f, 15.0f, 50.0f);
            }
        }
        if (done != 0) {
            gCurrentActor->unk155 = 4;
            animSetLoopLimit(gCurrentActor, 1, 1);
        }
        break;
    }
}

void bossPieceListStep(void *state, BossPieceAnim *pieceData, u8 *script, u8 *pieceList) {
    u8 i;
    u8 done;

    i = 0;
    done = 0;
    switch (gCurrentActor->unk155) {
    case 2:
        while (pieceList[i] != 0xFF) {
            bossPieceSetState(pieceData, pieceList[i++], 3);
        }
        gCurrentActor->unk155 = 3;
        break;
    case 3:
        while (pieceList[i] != 0xFF) {
            done = bossPieceStep(pieceData, pieceList[i++], 10.0f, 20.0f, 30.0f);
        }
        if (done != 0) {
            gCurrentActor->unk155 = 4;
            animSetLoopLimit(gCurrentActor, 1, 1);
        }
        break;
    }
}

void bossArmydilloHideCannons(void) {
    actorClearNodeFlag(gCurrentActor, 3);
    actorClearNodeFlag(gCurrentActor, 4);
    actorClearNodeFlag(gCurrentActor, 5);
}

void bossArmydilloShowCannons(void) {
    actorSetNodeFlag(gCurrentActor, 3);
    actorSetNodeFlag(gCurrentActor, 4);
    actorSetNodeFlag(gCurrentActor, 5);
}

extern u8 D_80720120[];

void bossArmydilloSpawnExhaustSmoke(void) {
    f32 scale;
    f64 speedY;

    speedY = (0.0 < gCurrentActor->speedY) ? gCurrentActor->speedY : 0.0;
    scale = (f32)((f32)((speedY / 150.0) * 0.12) + 0.3) * 4.0f;
    effectSetDepth(1);
    effectSetCallback(effectFollowParentUpdate);
    effectSetMaxDistance(1000);
    effectSetSpeed((s32)gCurrentActor);
    effectCreateAtActorBone(D_80720120, scale, gCurrentActor, 3, 0);
    effectSetDepth(1);
    effectSetCallback(effectFollowParentUpdate);
    effectSetMaxDistance(1000);
    effectSetSpeed((s32)gCurrentActor);
    effectCreateAtActorBone(D_80720120, scale, gCurrentActor, 4, 0);
}

// Armadillo boss actor: Actor plus its two component pointers (0x178 script state, 0x17C piece animation state).
typedef struct BossArmydilloActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ BossScriptState *scriptState;
    /* 0x17C */ BossPieceAnim *pieceAnim;
} BossArmydilloActor;

extern Actor *gSpawnedActor;
extern Actor *gPrimaryPlayerActor;

extern u8 *sArmydilloPhaseScripts[][5];
extern u8 D_80035980[];
extern u8 sArmydilloCannonPieceList[];
extern u8 D_80035988[];
extern const u8 D_80035CB8[];
extern const u8 D_80035CC0[];
extern u8 gGameMode;
extern u8 D_80750190;
extern s16 D_807502D8;
extern f32 gActorDefaultAccelY;
extern s16 gSfxSourceVoice[];
extern s16 gSfxVoiceSoundId[];

void behaviourFrameBegin(void);
void behaviourUpdateShadowAlpha(void);
u8 patrolPathStep(u8, u8);


void bossArmydilloStep(void) {
    s32 pad_top[1];
    BossPieceAnim *pieceAnim;
    u8 *scriptData;
    s32 pad_mid;
    u8 cannonBone;
    u8 playSfx;
    s32 pad_bot[1];
    BossScriptState *state;

    state = ((BossArmydilloActor *)gCurrentActor)->scriptState;
    pieceAnim = ((BossArmydilloActor *)gCurrentActor)->pieceAnim;
    scriptData = sArmydilloPhaseScripts[(gCurrentMap == 8) ? 0 : 1][state->phase];
    cannonBone = (state->unk12 & 1) ? 1 : 2;
    playSfx = 0;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourAnimState->unk38 = 0.002f;
        camSetSecondTarget(gCamActor, 0, 0);
        bossInitScriptData(D_80035CC0);
        gCurrentActor->accelY = gActorDefaultAccelY;
        gCurrentActor->terminalSpeedY = D_807502D8;
        bossArmydilloHideCannons();
        gBehaviourAnimState->unk2C = 0.01f;
        gBehaviourAnimState->unk30 = 3.0f;
        gCurrentActor->drawDistance = 0x3E8;
        animSetSpeed(gCurrentActor, 1, 0.2f);
        animSetLoopMode(gCurrentActor, 1, 1);
        gCurrentActor->segmentFlags = 0;
        bossArmydilloInitArena();
        gCurrentActor->speedXZ = 0.0f;
        scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
        {
            u32 checkPtr = (u32) effectUpdateAndDispatch;
            u32 end = (u32) effectNodeSetSubVal;
            s32 checksum = 0;
            gCurrentActor->state = scriptData[state->scriptPos++];
            gCurrentActor->unk155 = 0;
            while (checkPtr < end) {
                checksum += *(s32 *) checkPtr;
                checkPtr += 4;
            }
            if (checksum != 0x3D6E227F) {
                *(s32 *)camPathCommandDispatch = 0x27BDFF38;
            }
        }
    }
    currentActorAnimTryIdleVariant(0, &gBehaviourWorkState->idleAnimFrame);
    if ((gActorGlobalState.bossFightPhase == 9) || (gActorGlobalState.unk15 != 0)) {
        tagBarrelSpawnNodeSmokePuffs(gCurrentActor, 0xC, 2.0f);
        gCurrentActor->callbackMask = 0;
        gCurrentActor->unk144 = 1;
        currentActorClearFlag();
        actorScriptStart(gCurrentActor, 0x262);
        camStartPath(gCurrentActor, 9, 1);
        gCurrentActor->state = 0x37;
        gCurrentActor->unk155 = 0;
    } else if (gActorGlobalState.bossFightPhase == 4) {
        bossArmydilloHideCannons();
        gCurrentActor->state = 0x4D;
        gCurrentActor->unk155 = 0;
        gCurrentActor->callbackMask = 0;
        D_80750190 = 1;
        tagBarrelSpawnNodeSmokePuffs(gCurrentActor, 0xC, 2.0f);
        actorScriptStart(gCurrentActor, 0x262);
        state->scriptPos = 0;
        state->phase++;
        scriptData = sArmydilloPhaseScripts[(gCurrentMap == 8) ? 0 : 1][state->phase];
        camStartPath(gCurrentActor, 4, 1);
    }
    switch (gCurrentActor->state) {
    case 0x1F:
        controllerAnimSetStateIfChanged(gCurrentActor, 0x39A, 0.0f, 0.0f);
        scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
        gCurrentActor->segmentFlags = 3;
        gCurrentActor->state = scriptData[state->scriptPos++];
        gCurrentActor->unk155 = 0;
        break;
    case 0x1E:
        if (currentActorTestClearFlag() != 0) {
            gCurrentActor->state = 0x40;
            bossSpawnParticleRing(0x1A, gBehaviourZone->entries[4].x, gBehaviourZone->entries[4].y, gBehaviourZone->entries[4].z, 0x800, 6);
        }
        break;
    case 0x37:
        switch (gCurrentActor->unk155) {
        case 1:
            effectSpawnJointBeam(0xD, 0x11, 0x12, 0x16);
            break;
        case 2:
            if (!(gFrameCounter & 3)) {
                tagBarrelSpawnNodeSmokePuffs(gCurrentActor, ((randomNonNegative() >> 15) % 32767 % 10) + 0xD, 1.0f);
            }
            if (currentActorTestClearFlag() != 0) {
                bossArmydilloSpawnSmoke();
                actorScriptStart(gCurrentActor, 0x263);
                gBehaviourWorkState->timer = 0x14;
                gCurrentActor->unk155 = 3;
                gCurrentActor->flags |= 0x800000;
                gCurrentActor->tintR = 0x1E;
                gCurrentActor->tintG = 0x1E;
                gCurrentActor->tintB = 0x1E;
            }
            break;
        case 3:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
                bossArmydilloDebrisUpdate();
            } else if (currentActorTestClearFlag() != 0) {
                if (gCurrentActor->soundSlots[1] == -1) {
                    sfxPlayActorSound(gCurrentActor, 0x131, 0x3C, 1, 1, 0xFF, 1.0f, 0);
                }
                gCurrentActor->unk72 = 0;
                gCurrentActor->unk155 = 4;
                controllerAnimSetState(gCurrentActor, 0x39A, 0.0f, 30.0f);
                gCurrentActor->moveYaw = 0;
            }
            bossArmydilloDebrisFall();
            break;
        case 4:
            gCurrentActor->unk72++;
            effectSpawnBoneDebris((randomNonNegative() >> 15) % 32767 % 7 + 0x1D, 1);
            gCurrentActor->yaw += gCurrentActor->moveYaw;
            if (gCurrentActor->moveYaw + 10 > 500) {
                gCurrentActor->moveYaw = 500;
            } else {
                gCurrentActor->moveYaw += 10;
            }
            actorSetUniformScale(gCurrentActor, gCurrentActor->sub4->scaleX * 0.99);
            gCurrentActor->y += (356.0f - gCurrentActor->y) * 0.03;
            if (gCurrentActor->sub4->scaleY < 0.04) {
                gCurrentActor->unk155 = 5;
            }
            break;
        case 5:
            sfxStopSlotSound(gCurrentActor, 1);
            gCurrentActor->state = 0x40;
            bossSpawnParticleRing(0x124, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, mathAngleBetweenPoints2D(gBehaviourZone->entries[13].x, gBehaviourZone->entries[13].z, gCurrentActor->x, gCurrentActor->z), 5);
            break;
        }
        break;
    case 0x27:
        if (flagGet(0x68, 2) != 0) {
            gCurrentActor->state = scriptData[state->scriptPos++];
            gCurrentActor->unk155 = 0;
            break;
        }
        /* fallthrough */
    case 0x29:
    case 0x2D:
    case 0x2E:
        switch (gCurrentActor->unk155) {
        case 0:
            if ((gGameMode != 1) || (currentActorTestClearFlag() != 0)) {
                animSetLoopLimit(gCurrentActor, 1, 1);
                pieceAnim->endSfxPlayed = 0;
                gCurrentActor->unk155 = 1;
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x3A, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            }
            break;
        case 1:
            if ((animIsPlaying(gCurrentActor, 1) == 0) && (pieceAnim->endSfxPlayed == 0)) {
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x174, 0xC8, 0x7F, 1, 0x1E, 0.3f, 0);
                pieceAnim->endSfxPlayed = 1;
            }
            if ((gGameMode != 1) || (currentActorTestClearFlag() != 0)) {
                gCurrentActor->unk155 = 2;
            }
            break;
        case 2:
        case 3:
            if (gCurrentActor->state == 0x29) {
                bossArmydilloOpenCannons(state, pieceAnim, scriptData, sArmydilloCannonPieceList);
            } else if (gCurrentActor->state == 0x2E) {
                bossArmydilloOpenCannons(state, pieceAnim, scriptData, D_80035988);
            } else {
                bossArmydilloOpenCannons(state, pieceAnim, scriptData, D_80035980);
            }
            break;
        case 4:
            if ((gGameMode != 1) || (currentActorTestClearFlag() != 0)) {
                gCurrentActor->state = scriptData[state->scriptPos++];
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0x28:
        switch (gCurrentActor->unk155) {
        case 0:
            currentActorClearFlag();
            controllerAnimSetStateIfChanged(gCurrentActor, 0x3AF, 0.0f, 4.0f);
            gCurrentActor->unk155 = 1;
            /* fallthrough */
        case 1:
            if (!(gFrameCounter & 7)) {
                effectSpawnJointBeam(0xD, 0x16, 0x17, 0x1C);
            }
            if (currentActorTestClearFlag() != 0) {
                tagBarrelSpawnNodeSmokePuffs(gCurrentActor, 6, 1.0f);
                tagBarrelSpawnNodeSmokePuffs(gCurrentActor, 7, 1.0f);
                actorScriptStart(gCurrentActor, 0x26C);
                bossPieceSetState(pieceAnim, 0, 5);
                bossPieceSetState(pieceAnim, 1, 5);
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x22, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x3C, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                gCurrentActor->unk155 = 2;
            }
            break;
        case 2:
            bossPieceStep(pieceAnim, 0, 50.0f, 70.0f, 90.0f);
            if (bossPieceStep(pieceAnim, 1, 50.0f, 70.0f, 90.0f) != 0) {
                gCurrentActor->state = scriptData[state->scriptPos++];
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0x13:
    case 0x1A:
    case 0x1B:
    case 0x2F:
        switch (gCurrentActor->unk155) {
        case 0:
            if (pieceAnim->cannonAngA >= -0x3FFF) {
                pieceAnim->cannonAngA -= 0x190;
                if (gCurrentActor->soundSlots[1] == -1) {
                    sfxPlayActorSound(gCurrentActor, 0x1F0, 1, 1, 1, 0xFF, 1.0f, 0);
                }
            } else {
                if (gCurrentActor->state == 0x2F) {
                    actorScriptStart(gCurrentActor, 0x268);
                }
                sfxStopSlotSound(gCurrentActor, 1);
                gCurrentActor->unk155 = 1;
                gBehaviourWorkState->unk2E = 0;
                gCurrentActor->speedXZ = 0.0f;
            }
            pieceAnim->cannonAngB = pieceAnim->cannonAngA;
            bossPieceSetAngle(2, pieceAnim->cannonAngA);
            bossPieceSetAngle(3, pieceAnim->cannonAngB);
            break;
        case 1:
            gBehaviourWorkState->unk2E += (gCurrentActor->state == 0x2F) ? 10 : 4;
            if (gBehaviourWorkState->unk2E >= 0x12D) {
                gBehaviourWorkState->unk2E = 0x12C;
            }
            gCurrentActor->speedY = gBehaviourWorkState->unk2E;
            bossArmydilloSpawnExhaustSmoke();
            playSfx = 1;
            actorMoveWithinZone(0x45, 510.0f, 480.0f, 0x292, 0.0f);
            if (gCurrentActor->distToFloor > 30.0f) {
                gCurrentActor->speedXZ = 100.0f;
            }
            if (gCurrentActor->distToFloor > 150.0f) {
                gCurrentActor->unk155 = 2;
            }
            break;
        case 2:
            actorMoveWithinZone(0x45, 510.0f, 480.0f, 0x292, 0.0f);
            if (gFrameCounter & 8) {
                bossArmydilloSpawnExhaustSmoke();
                playSfx = 1;
                gCurrentActor->speedY = 100.0f;
            }
            if ((gGameMode != 1) || (currentActorTestClearFlag() != 0)) {
                if (gCurrentActor->state == 0x2F) {
                    gCurrentActor->state = scriptData[state->scriptPos++];
                    gCurrentActor->unk155 = 0;
                } else {
                    gCurrentActor->unk155 = 3;
                }
            }
            break;
        case 3:
            actorMoveWithinZone(0x45, 510.0f, 480.0f, 0x292, 0.0f);
            if (gCurrentActor->contactFlags & 1) {
                projectileSpawnWithShockwave(0xB8, 0.14f, 0x64, 0xFF, 0x96, 7, 1.04f, 40.0f, 8.0f, 600.0f);
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x221, 0xC8, 0x7F, 1, 0, 0.3f, 0);
                controllerAnimSetStateIfChanged(gSpawnedActor, 0x4F9, 0.0f, 0.0f);
                scriptSetActorRampTarget(gSpawnedActor, 0.5f, 0.0f);
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x24A, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x36, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                gCurrentActor->unk155 = 4;
                gBehaviourWorkState->timer = 0x3C;
            }
            break;
        case 4:
            if ((gBehaviourWorkState->timer == 0x28) || (gBehaviourWorkState->timer == 0x32)) {
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x1C1, 0xB4, 0x7F, 1, 0x1E, 0.3f, 0);
            }
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->state = scriptData[state->scriptPos++];
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0x2C:
        {
            s32 pad;
            pieceAnim->cannonAngA = -pieceAnim->cannonAngA * 0.1 + pieceAnim->cannonAngA;
            pieceAnim->cannonAngB = -pieceAnim->cannonAngB * 0.1 + pieceAnim->cannonAngB;
            bossPieceSetAngle(3, pieceAnim->cannonAngB);
            bossPieceSetAngle(2, pieceAnim->cannonAngA);
        }
        /* fallthrough */
    case 0x2B:
        switch (gCurrentActor->unk155) {
        case 0:
            animSetLoopLimit(gCurrentActor, 1, 1);
            gCurrentActor->unk155 = 2;
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x3A, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            break;
        case 2:
        case 3:
            bossPieceListStep(state, pieceAnim, scriptData, (gCurrentActor->state == 0x2B) ? D_80035980 : sArmydilloCannonPieceList);
            break;
        case 4:
            gCurrentActor->state = scriptData[state->scriptPos++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x2A:
        switch (gCurrentActor->unk155) {
        case 0:
            actorScriptStart(gCurrentActor, 0x257);
            gCurrentActor->unk155 = 1;
            break;
        case 2:
            gCurrentActor->state = scriptData[state->scriptPos++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x11:
    case 0x57:
        switch (gCurrentActor->unk155) {
        case 0:
            actorScriptStart(gCurrentActor, (gCurrentActor->state == 0x57) ? 0x258 : 0x259);
            gCurrentActor->unk155 = 1;
            /* fallthrough */
        case 1:
            actorMoveWithinZone(0x45, gBehaviourTargetActor->x, gBehaviourTargetActor->z, (gCurrentActor->state == 0x57) ? 0x210 : 0x212, 0.0f);
            break;
        case 2:
            actorMoveWithinZone(0x45, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x212, 0.0f);
            break;
        case 3:
            if (gCurrentActor->state == 0x11) {
                waterRippleStart(gCurrentActor->x, gCurrentActor->z, 20.0f, 2.0f, 8.0f, 400.0f);
            }
            camStartShake(gCamActor, 5, 0x14);
            break;
        case 5:
            gCurrentActor->speedXZ = 0.0f;
            gCurrentActor->state = scriptData[state->scriptPos++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x30:
        actorMoveWithinZone(0x45, 510.0f, 480.0f, 0x292, 0.0f);
        if (gFrameCounter & 8) {
            bossArmydilloSpawnExhaustSmoke();
            playSfx = 1;
            gCurrentActor->speedY = 100.0f;
        }
        switch (gCurrentActor->unk155) {
        case 0:
            state->unk18[0] = scriptData[state->scriptPos++];
            state->unk18[1] = state->unk18[0];
            gCurrentActor->unk155 = 1;
            actorScriptStart(gCurrentActor, 0x269);
            break;
        case 2:
            projectileGetTargetCoords(gCurrentActor, 5);
            projectileSpawnNodeEntry(0x1E, 5, 1.2f, gCurrentActor->yaw, 600.0f, 300.0f, gCurrentActor);
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0xF6, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            effectSpawnBoneWhite(gCurrentActor, 5, 2.0f, 0.0f, 0.0f, 0.0f, -0x50);
            if (state->unk18[1] != 0) {
                state->unk18[1]--;
                gCurrentActor->unk155 = 1;
            } else {
                actorScriptStart(gCurrentActor, 0);
                controllerAnimSetStateIfChanged(gCurrentActor, 0x3A8, 0.0f, 10.0f);
                gCurrentActor->unk155 = 3;
                gBehaviourWorkState->timer = 0x1E;
            }
            break;
        case 3:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->unk155 = 4;
            }
            break;
        case 4:
            projectileSetTargetCoords((randomNonNegative() >> 15) % 20 + gBehaviourTargetActor->x, gBehaviourTargetActor->y + 400.0f, (randomNonNegative() >> 15) % 20 + gBehaviourTargetActor->z);
            projectileAimAndSpawn(0x1E, 0xA, 1.2f, gBehaviourTargetActor->x, gBehaviourTargetActor->y, gBehaviourTargetActor->z, 600.0f, gCurrentActor);
            gBehaviourWorkState->timer = 0x14;
            gCurrentActor->unk155 = 5;
            /* fallthrough */
        case 5:
            if (gBehaviourWorkState->timer == 0xF) {
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0xF4, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            }
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                state->unk18[0]--;
                if (state->unk18[0] != 0) {
                    gCurrentActor->unk155 = 4;
                } else {
                    gCurrentActor->state = scriptData[state->scriptPos++];
                    gCurrentActor->unk155 = 0;
                }
            }
            break;
        }
        break;
    case 0x46:
        switch (gCurrentActor->unk155) {
        case 0:
            state->unk12 |= 1;
            state->unk18[0] = scriptData[state->scriptPos++];
            state->unk18[1] = scriptData[state->scriptPos++];
            gCurrentActor->unk155 = 1;
            /* fallthrough */
        case 1:
            gBehaviourWorkState->timer = state->unk18[1];
            if (!(state->unk12 & 1) && (state->phase != 0)) {
                gBehaviourWorkState->timer = 0;
                state->unk18[0]++;
            }
            gCurrentActor->unk155 = 2;
            /* fallthrough */
        case 2:
            if (gBehaviourWorkState->timer != 0) {
                bossArmydilloAimTowardTarget();
                gBehaviourWorkState->timer--;
            } else {
                actorScriptStart(gCurrentActor, (cannonBone == 1) ? 0x25D : 0x25E);
                gCurrentActor->unk155 = 3;
            }
            break;
        case 4:
            projectileGetTargetCoords(gCurrentActor, cannonBone);
            projectileClampAngleAndSpawn(gCurrentActor->yaw, 0x320, 0x1E, 1, 0.7f, gBehaviourTargetActor->x, gBehaviourTargetActor->y + 5.0f, gBehaviourTargetActor->z, state->phase * 0x50 + 0x1F4, gCurrentActor);
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x18, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            effectSpawnBoneWhite(gCurrentActor, cannonBone, 2.0f, 0.0f, 0.0f, 0.0f, -0x50);
            state->unk12 ^= 1;
            gCurrentActor->unk155 = 5;
            break;
        case 6:
            if (state->unk18[0] != 0) {
                state->unk18[0]--;
                gCurrentActor->unk155 = 1;
                break;
            }
            gCurrentActor->state = scriptData[state->scriptPos++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x48:
        switch (gCurrentActor->unk155) {
        case 0:
            gCurrentActor->callbackMask = -1;
            bossArmydilloShowCannons();
            gBehaviourWorkState->timer = scriptData[state->scriptPos++];
            if (camIsCutsceneActive() != 0) {
                actorScriptStart(gCurrentActor, 0x267);
            } else {
                actorScriptStart(gCurrentActor, 0x261);
            }
            gCurrentActor->unk155 = 1;
            /* fallthrough */
        case 1:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
                break;
            }
            bossArmydilloHideCannons();
            gCurrentActor->state = scriptData[state->scriptPos++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x4D:
        switch (gCurrentActor->unk155) {
        case 0:
            currentActorClearFlag();
            actorMoveWithinZone(0x4D, 0.0f, 0.0f, 0x12, 0.0f);
            break;
        case 1:
            actorMoveWithinZone(0x4D, 0.0f, 0.0f, 0x12, 0.0f);
            effectSpawnJointBeam(0xD, 0x16, 0x17, 0x1C);
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gCurrentActor, 0x263);
                gCurrentActor->unk155 = 3;
            }
            effectSpawnJointBeam(0xD, 0x16, 0x17, 0x1C);
            effectSpawnJointBeam(9, 0xB, 0xC, 0xC);
            break;
        case 3:
            effectSpawnBoneWhite(gCurrentActor, ((randomNonNegative() >> 0xF) % 32767 % 20) + 9, 2.0f, 0.0f, 0.0f, 0.0f, -0x50);
            if (currentActorTestClearFlag() != 0) {
                gCurrentActor->callbackMask = -1;
                gCurrentActor->state = scriptData[state->scriptPos++];
                gCurrentActor->unk155 = 0;
                D_80750190 = 0;
            }
            break;
        }
        break;
    case 0x26:
        switch (gCurrentActor->unk155) {
        case 0:
            bossInitScriptData(D_80035CB8);
            gCurrentActor->unk155 = 1;
            /* fallthrough */
        case 1:
            actorMoveWithinZone(0x42, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0x290, 0.0f);
            if (gFrameCounter & 8) {
                bossArmydilloSpawnExhaustSmoke();
                playSfx = 1;
                gCurrentActor->speedY = 100.0f;
            }
            if (patrolPathStep(gCurrentActor->state, 0) != 0) {
                gCurrentActor->unk155 = 2;
            }
            break;
        case 2:
            gCurrentActor->state = scriptData[state->scriptPos++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x43:
    case 0x44:
        switch (gCurrentActor->unk155) {
        case 0:
            actorScriptStart(gCurrentActor, (gCurrentActor->state == 0x44) ? 0x25C : 0x25B);
            gCurrentActor->unk155 = 1;
            break;
        case 2:
            if (gCurrentActor->state == 0x44) {
                waterRippleStart(gCurrentActor->x, gCurrentActor->z, 20.0f, 2.0f, 8.0f, 400.0f);
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x36, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            }
            gCurrentActor->state = scriptData[state->scriptPos++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x47:
        switch (gCurrentActor->unk155) {
        case 2:
        case 4:
            break;
        case 0:
            actorScriptStart(gCurrentActor, 0x26A);
            gCurrentActor->unk155 = 1;
            /* fallthrough */
        case 1:
            actorMoveWithinZone(0x45, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x292, 0.0f);
            if (gCurrentActor->contactFlags & 1) {
                actorScriptStart(gCurrentActor, 0x26B);
                gCurrentActor->unk155 = 2;
            }
            break;
        case 3:
            projectileGetTargetCoords(gCurrentActor, 5);
            projectileAimAndSpawn(0x59, 1, 1.5f, gPrimaryPlayerActor->x, gPrimaryPlayerActor->y + 2.0f, gPrimaryPlayerActor->z, 300.0f, gCurrentActor);
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x128, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x188, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            gCurrentActor->unk155 = 4;
            break;
        default:
            gCurrentActor->state = scriptData[state->scriptPos++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x23:
    case 0x42:
        if (gCurrentActor->sub4->model->animId != 0x39A) {
            actorScriptStart(gCurrentActor, 0x256);
        }
        /* fallthrough */
    default:
        bossScriptStep(scriptData, 0x10, 0.0f);
        break;
    }
    if (playSfx != 0) {
        if ((gCurrentActor->soundSlots[1] != -1) && (gSfxVoiceSoundId[gSfxSourceVoice[gCurrentActor->soundSlots[1]]] != 0x114)) {
            sfxStopSlotSound(gCurrentActor, 1);
        }
        if (gCurrentActor->soundSlots[1] == -1) {
            sfxPlayActorSound(gCurrentActor, 0x114, 1, 1, 1, 0xFF, 0.5f, 0);
        }
    } else if ((gCurrentActor->soundSlots[1] != -1) && (gSfxVoiceSoundId[gSfxSourceVoice[gCurrentActor->soundSlots[1]]] == 0x114)) {
        sfxStopSlotSound(gCurrentActor, 1);
    }
    behaviourUpdateShadowAlpha();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void bossArmydilloDebrisFall(void) {
    u8 bone;

    if (!(gFrameCounter & 3)) {
        if (!(gFrameCounter & 0xF)) {
            bone = 0xC;
        } else {
            bone = ((randomNonNegative() >> 15) % 0x7FFF) % 7 + 0x1D;
        }
        effectSetMode(3);
        effectSetColor(0x50, 0x50, 0x50, 0xC8);
        effectSpawnBoneDefault(gCurrentActor, bone, 2.0f, 0.0f, 0.0f, 0.0f, -0x78);
    }
}

const u8 D_80035C00[18] = {
    0x54, 0x41, 0x00, 0x57, 0x27, 0x43, 0x4F, 0x46, 0x03, 0x14, 0x48, 0xDC, 0x44, 0x4B, 0x00, 0x03,
    0x11, 0x50,
};

const u8 D_80035C14[19] = {
    0x44, 0x23, 0x8C, 0x4C, 0x00, 0x03, 0x11, 0x4F, 0x46, 0x04, 0x14, 0x48, 0xB4, 0x44, 0x4B, 0x00,
    0x03, 0x11, 0x50,
};

const u8 D_80035C28[19] = {
    0x44, 0x23, 0xAA, 0x4C, 0x00, 0x03, 0x11, 0x4F, 0x46, 0x05, 0x14, 0x48, 0x8C, 0x44, 0x4B, 0x00,
    0x03, 0x11, 0x50,
};

const u8 D_80035C3C[6] = { 0x5F, 0x05, 0x28, 0x5F, 0x07, 0x1E };

const u8 D_80035C44[21] = {
    0x1F, 0x54, 0x41, 0x00, 0x57, 0x48, 0x3C, 0x54, 0x43, 0x4F, 0x46, 0x03, 0x14, 0x48, 0xDC, 0x44,
    0x4B, 0x00, 0x03, 0x11, 0x50,
};

const u8 D_80035C5C[26] = {
    0x44, 0x23, 0x8C, 0x4C, 0x00, 0x03, 0x2A, 0x5F, 0x02, 0x2B, 0x29, 0x13, 0x2C, 0x2D, 0x4F, 0x4B,
    0x00, 0x03, 0x11, 0x46, 0x04, 0x14, 0x48, 0xB4, 0x44, 0x50,
};

const u8 D_80035C78[25] = {
    0x44, 0x23, 0xAA, 0x4C, 0x00, 0x03, 0x2A, 0x2B, 0x29, 0x1B, 0x13, 0x2C, 0x2D, 0x4F, 0x4B, 0x00,
    0x03, 0x11, 0x46, 0x05, 0x14, 0x48, 0x8C, 0x44, 0x50,
};

const u8 D_80035C94[34] = {
    0x5F, 0x05, 0x28, 0x44, 0x23, 0xAA, 0x4C, 0x00, 0x03, 0x2A, 0x29, 0x1A, 0x13, 0x13, 0x4B, 0x00,
    0x03, 0x2A, 0x57, 0x5F, 0x07, 0x2E, 0x54, 0x2F, 0x4F, 0x30, 0x06, 0x47, 0x48, 0xB4, 0x2F, 0x26,
    0x2F, 0x50,
};

const u8 D_80035CB8[6] = { 0x05, 0x08, 0x0B, 0x09, 0x0A, 0x0C };

const u8 D_80035CC0[5] = { 0x04, 0x00, 0x01, 0x02, 0x03 };
