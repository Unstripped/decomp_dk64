#include "common.h"
#include "actor.h"
#include "sched.h"
#define PROTO_SKIP_controllerLookupStateByHash // FAKE: callee prototype steer
#define PROTO_SKIP_playerStateQueueCallback // PROTO: The number of arguments doesn't agree with the number in the
#include "proto/global/117190.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/8F050.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/E4090.h"
#include "proto/global/EFDC0.h"
#include "proto/global/F56F0.h"
#include "proto/global/F9450.h"

struct WaypointNode;
struct F56AState;
struct F5N6Input;

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern PlayerState *gActivePlayerState;
extern s16 gCurrentCharacterIndex;
extern s32 gCurrentMap;
extern u8 gPlayerCharacterId[];

void playerKongStopAudioChannels(Actor *actor, u16 actorType) {
    switch (actorType) {
    case 0xC5:
    case 3:
        func_8068A784(actor, 0);
        func_8068A784(actor, 1);
        func_8068A784(actor, 2);
        break;
    case 0xC8:
    case 6:
        func_8068A764(actor, 0);
        func_8068A784(actor, 1);
        break;
    case 0xC6:
    case 4:
        func_8068A764(actor, 0);
        func_8068A784(actor, 1);
        break;
    case 0xC7:
    case 5:
        func_8068A764(actor, 0);
        func_8068A784(actor, 1);
        break;
    case 0xC4:
    case 2:
        func_8068A764(actor, 0);
        func_8068A784(actor, 1);
        break;
    case 7:
        func_8068A764(actor, 1);
        func_8068A784(actor, 0);
        break;
    }
}


void playerPlayKongSpecificSfx(Actor *actor) {
    switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
    case 0:
        sfxPlayFromActorWithAltitudeCheck(actor, 0x17C, 0xFF, 0x7F, 0x19);
        break;
    case 1:
        sfxPlayFromActorWithAltitudeCheck(actor, 0x17C, 0xC8, 0xA0, 5);
        break;
    case 2:
        sfxPlayFromActorWithAltitudeCheck(actor, 0x17C, 0xFF, 0x7F, 5);
        break;
    case 3:
        sfxPlayFromActorWithAltitudeCheck(actor, 0x185, 0xFF, 0x7F, 0x19);
        break;
    default:
        sfxPlayFromActorWithAltitudeCheck(actor, 0x18F, 0xFF, 0x7F, 0x19);
        break;
    }
}

s32 controllerLookupStateByHash(void);

void playerKongStopSoundByState(Actor *actor) {
    s32 pad;
    PlayerState *extra;

    switch (controllerLookupStateByHash()) {
    case 1:
    case 2:
    case 3:
        func_8068A784(actor, 0);
        func_8068A784(actor, 1);
        break;
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x10:
        func_8068A764(actor, 0);
        func_8068A784(actor, 1);
        break;
    case 0xDB:
        func_8068A764(actor, 1);
        func_8068A784(actor, 0);
        break;
    case 6:
    case 7:
    case 8:
        func_8068A764(actor, 0);
        func_8068A784(actor, 1);
        break;
    case 9:
    case 0xA:
    case 0xB:
        func_8068A764(actor, 0);
        func_8068A784(actor, 1);
        break;
    case 4:
    case 5:
        func_8068A764(actor, 0);
        func_8068A784(actor, 1);
        break;
    }
    if (actor->collisionFlags & 1) {
        extra = actor->customState;
        if (extra->gunDrawn != 0) {
            playerPlayKongSpecificSfx(actor);
            extra->gunDrawn = 0;
        }
    }
}

extern u8 D_807FC952[];

void playerKongPlaySoundByState(Actor *actor) {
    s32 pad;
    PlayerState *extra;

    switch (controllerLookupStateByHash()) {
    case 1:
    case 2:
        func_8068A764(actor, 0);
        func_8068A764(actor, 1);
        break;
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x10:
        func_8068A784(actor, 0);
        func_8068A764(actor, 1);
        break;
    case 0xDB:
        func_8068A784(actor, 1);
        func_8068A764(actor, 0);
        break;
    case 6:
    case 7:
        func_8068A784(actor, 0);
        func_8068A764(actor, 1);
        break;
    case 9:
    case 0xA:
        func_8068A784(actor, 0);
        func_8068A764(actor, 1);
        break;
    case 4:
        func_8068A784(actor, 0);
        func_8068A764(actor, 1);
        break;
    }
    if (actor->collisionFlags & 1) {
        extra = actor->customState;
        if (extra->gunDrawn == 0) {
            switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
            case 0:
                sfxPlayFromActorWithAltitudeCheck(actor, 0x186, 0xFF, 0x64, 0x19);
                sfxPlayFromActorWithAltitudeCheck(actor, 0x17C, 0xFF, 0x64, 0x19);
                break;
            case 1:
                sfxPlayFromActorWithAltitudeCheck(actor, 0x17C, 0xC8, 0xBE, 5);
                break;
            case 2:
                sfxPlayFromActorWithAltitudeCheck(actor, 0x186, 0xFF, 0x7F, 0x19);
                sfxPlayFromActorWithAltitudeCheck(actor, 0x17C, 0xFF, 0xA0, 5);
                break;
            case 3:
                sfxPlayFromActorWithAltitudeCheck(actor, 0x185, 0xFF, 0x7F, 0x19);
                break;
            default:
                sfxPlayFromActorWithAltitudeCheck(actor, 0x18E, 0xFF, 0x7F, 0x19);
                break;
            }
            extra->gunDrawn = 1;
        }
        if (func_80714608(0) != 0) {
            D_807FC952[extra->playerIndex * 0x306 + playerGetResolvedKongId(extra->playerIndex) * 0x5E] = 1;
            func_806F5A48(extra->playerIndex, 0, actor, 0x8F);
        }
    }
}


void playerKongClearFlagsByActorType(Actor *actor) {
    PlayerState *state = actor->customState;

    switch (actor->actorType) {
    case 4:
    case 0xC6:
        state->stateFlags &= ~0x100;
    case 3:
    case 5:
    case 6:
    case 0xC5:
    case 0xC7:
    case 0xC8:
        if (!(state->stateFlags & 0x40)) {
            controllerAnimFreeStateAsset(actor);
        }
        break;
    }
    actorSetInteractionTimer(gCurrentActor);
}

void playerKongSpawnTransformationSmoke(Actor *actor) {
    switch (actor->actorType) {
        case 2:
        case 0xC4:
            playerKongStopSoundByState(actor);
            actorSpawn(0xEF, 0xA6);
            actorCopyPoseAndScale(gSpawnedActor, actor, actor->sub4->scaleY * 1.25);
            gSpawnedActor->pitch = actor->pitch;
            gSpawnedActor->roll = actor->roll;
            gSpawnedActor->flags |= 0x40000000;
            break;
        case 3:
        case 0xC5:
            playerKongStopSoundByState(actor);
            controllerAnimLoadStateAsset(actor, 2);
            break;
        case 4:
        case 0xC6:
            playerKongStopSoundByState(actor);
            controllerAnimLoadStateAsset(actor, 7);
            break;
        case 5:
        case 0xC7:
            playerKongStopSoundByState(actor);
            controllerAnimLoadStateAsset(actor, 0xA);
            break;
        case 6:
        case 0xC8:
            playerKongStopSoundByState(actor);
            controllerAnimLoadStateAsset(actor, 0xD);
            break;
    }
}

extern s32 gGlobalCutsceneFlags;

void playerTransformAnimalStartSfx(Actor *actor) {
    PlayerState *extra = actor->customState;

    if (actor->actorType == 6) {
        controllerAnimLoadStateAsset(actor, 0x10);
        sfxPlayAtPositionPooled(actor->x, actor->y, actor->z, 0x2E2, 0xFF, 0xA0, 0, 0x32, 0.0f, 0);
        if (!(gGlobalCutsceneFlags & 2)) {
            sfxAllocateChannel(0x6C, 1.0f);
        }
    }
    extra->stateFlags |= 0x40;
}

void playerTransformAnimalEndSfx(Actor *actor) {
    PlayerState *extra = actor->customState;

    if (actor->actorType == 6) {
        controllerAnimFreeStateAsset(actor);
        sfxStopChannel(0x6C, 0);
    }
    extra->stateFlags &= ~0x40;
}


void playerFireWeaponPrimary(s32 unused) {
    playerFireWeapon(0, 1);
}

void f56f0Noop1378(s32 unused) {}

void scriptCmdCompareSpeedXZ(Actor *actor) {
    f32 temp;

    scriptReadU32(&temp);
    actor->sub4->scriptResult = (s32)(actor->speedXZ - temp);
}




void scriptCmdCompareMoveTier(Actor *actor) {
    u8 temp;

    scriptReadU8(&temp);
    actor->sub4->scriptResult =
        playerSelectMoveTier(actor, actor->speedXZ, actor->speedXZ, gActivePlayerState->unk4C, gCurrentCharacterIndex) - temp;
}

typedef struct F5APlayerCoefficient {
    f32 value;
    u8 pad4[0x30];
} F5APlayerCoefficient;

extern F5APlayerCoefficient D_807FD618[];

void playerResumeLocomotionDecel(Actor *actor) {
    f32 value;

    playerResumeLocomotion(actor);
    value = gCurrentActor->speedXZ;
    gCurrentActor->speedXZ =
        D_807FD618[gCurrentPlayerIndex].value * (value - (value / 2)) + (value / 2);
}


void playerD0150Wrapper(Actor *actor) {
    playerEnterBarrelTransition(actor);
}

void playerKongCalculateHealthScale(Actor *actor) {
    f32 limit;
    u8 amount;
    f64 den;
    f32 base;
    f32 value;
    f32 high;
    f32 ratio;
    s32 count;

    scriptReadU32(&limit);
    scriptReadU8(&amount);
    base = actor->sub4->model->frame;
    actor->sub4->scriptResult = 0;
    if ((actor->contactFlags & 2) && ((actor->waterY - actor->floorY) > 12.0f)) {
        high = (actor->waterY < actor->floorY) ? actor->floorY : actor->waterY;
        value = actor->y - high;
        if (value < 0.0f) {
            value = 0.0f;
        }
    } else {
        value = actor->distToFloor;
    }
    count = mathCalculateRatioClamped(value * 40.0f, actor->speedY, actor->terminalSpeedY, actor->accelY);
    if (count == 0) {
        actor->sub4->scriptResult = 1;
        return;
    }
    ratio = ((f32)(u32)amount - base) / (f32)count;
    if (ratio < 0.0f) {
        ratio = 0.01f;
    }
    den = (actor->sub4->model->speed < 0.01) ? 0.01 : actor->sub4->model->speed;
    ratio = ratio / den;
    if (limit < ratio) {
        ratio = limit;
    }
    scriptSetActorRampTarget(actor, ratio, 0.0f);
}


s32 mathCalculateRatioClamped(f32 distance, f32 speed, f32 maxSpeed, f32 accel) {
    f32 quot;
    f32 val;
    f32 res;

    if ((distance < 0.0f) || (0.0f < maxSpeed) || (0.0f <= accel)) {
        return 0;
    }
    quot = (maxSpeed - speed) / accel;
    val = distance;
    val += ((speed + maxSpeed) / 2) * quot;
    if (val > 0.0f) {
        res = quot - val / maxSpeed;
    } else {
        res = (-sqrtf((speed * speed) - (2 * accel * distance)) - speed) / accel;
    }
    return (s32)(res + 0.5);
}


extern u16 D_80752F20[];

void playerWeaponCalculateTrajectory7(Actor *actor, BoneRotation *slots, s32 *count) {
    s32 index;
    u16 angle;
    angle = 7U;  // FAKE: the bound shares angle with the table value (one register)
    index = gActivePlayerState->unk8E - 0x14;
    if ((index >= 0) && ((u32) index < angle)) {
        angle = D_80752F20[index];
        slots[*count].weight = 0x7F;
        slots[*count].bone = gActivePlayerState->unk91 != 0 ? 9 : 8;
        slots[*count].rotX = 0;
        slots[*count].rotY = gActivePlayerState->unk91 != 0 ? angle : -angle;
        slots[*count].rotZ = 0;
        *count += 1;
    }
}

extern u16 D_80752F30[];

void playerWeaponCalculateTrajectory4(Actor *actor, BoneRotation *slots, s32 *count) {
    s32 index;
    u16 angle;
    angle = 4U;  // FAKE: the bound shares angle with the table value (one register)
    index = gActivePlayerState->unk8E - 0x14;
    if ((index >= 0) && ((u32) index < angle)) {
        angle = D_80752F30[index];
        slots[*count].weight = 0x7F;
        slots[*count].bone = 4;
        slots[*count].rotX = 0;
        slots[*count].rotY = angle;
        slots[*count].rotZ = 0;
        *count += 1;
    }
}



extern u16 D_80752F38[];
extern u16 D_80752F40[];
extern f32 mathCosF(s16);

void playerWeaponCalculateTrajectory22(Actor *actor, BoneRotation *slots, s32 *count) {
    s32 tableIndex;
    u16 angle;

    angle = 0x16;  // FAKE: the base shares angle's register with the table value
    tableIndex = gActivePlayerState->unk8E - angle;
    if ((tableIndex >= 0) && ((u32)tableIndex < 4U)) {
        angle = D_80752F38[tableIndex];
        slots[*count].weight = 0x7F;
        slots[*count].bone = 1;
        slots[*count].rotX = 0;
        slots[*count].rotY = angle;
        slots[*count].rotZ = 0;
        *count += 1;
    }
}

void playerWeaponCalculateTrajectory23(Actor *actor, BoneRotation *slots, s32 *count) {
    u16 angle;

    angle = D_80752F40[gActivePlayerState->unk8E];
    slots[*count].weight = 0x7F;
    slots[*count].bone = 1;
    slots[*count].rotX = angle;
    slots[*count].rotY = angle;
    slots[*count].rotZ = 0;
    *count += 1;
}

typedef struct F5N1Spring {
    f32 offset;
    f32 angle;
    f32 velocity;
} F5N1Spring;

f32 cosApprox(f32);
f32 sinApprox(f32);

void playerWeaponCalculateTrajectory24(f32 force, f32 damping, F5N1Spring *spring, f32 *angle) {
    s32 pad[1];
    f32 cosTilt;

    cosTilt = cosApprox(spring->angle);
    spring->velocity += force * cosApprox(*angle) * cosTilt;
    spring->velocity -= damping * sinApprox(spring->angle);
    spring->velocity = (f32)((f64)spring->velocity * 0.93);
    spring->angle = (f32)(spring->angle + spring->velocity);
    *angle += spring->angle + spring->offset;
}

typedef struct F56APair {
    F5N1Spring springX;
    F5N1Spring springY;
} F56APair;

typedef struct F56AState {
    f32 prevAngle;
    f32 prevY;
    f32 prevVelY;
    f32 sway;
    f32 weight;
    u8 holdTimer;
    u8 pad15[3];
    s32 mode;
    F56APair springs[8];
    u8 padDC[0x60];
} F56AState;

f32 playerWeaponCalculateTrajectory25(Actor *actor, F56AState *state, f32 scale) {
    f32 delta;
    f32 sway;

    sway = mathCosF((s16)(actor->yaw - actor->moveYaw)) * (actor->speedXZ * 0.0076923077f);
    delta = sway - state->sway;
    state->sway = sway;
    return (delta + sway) * scale;
}

s32 playerWeaponCalculateTrajectory26(Actor *actor, F56AState *state, s32 mode) {
    s32 ret = (actor->flags & 0x100) != 0;

    if (ret != 0) {
        ret = state->holdTimer == 0;
        if (ret != 0) {
            return mode == state->mode;
        }
    } // FAKE: no final return keeps ret in $v0 (same idiom as func_80026250)
}

f32 mathAngleRadDeltaTurns(f32 *prevAngle, f32 angle) {
    f32 diff;

    diff = angle - *prevAngle;
    *prevAngle = angle;
    if (diff > 3.1415927f) {
        diff = 6.2831855f - diff;
    } else if (diff < -3.1415927f) {
        diff = -(6.2831855f + diff);
    }
    diff *= 0.15915494f;
    return diff;
}

typedef struct {
    u8 pad0[0x178];
    F56AState *weaponState;
} F56AActor;


void playerWeaponAimTarget(Actor *actor, BoneRotation *slots, s32 *count) {
    F56AState *state = ((F56AActor *) actor)->weaponState;
    F56APair *pair;
    s32 pad5[1];
    f32 posB[3];
    f32 posA[3];
    s32 value = -0x80;
    f32 accel0 = 0.0f;
    f32 accel1 = 0.0f;
    f32 angle;
    s32 active;
    s32 index;
    s32 i;
    f32 ret;
    f32 angle0;
    f32 angle1;
    s32 kind;
    s32 pad4[2];

    pair = state->springs;
    active = playerWeaponCalculateTrajectory26(actor, state, 2);
    angle0 = 0.0f;
    angle1 = 0.0f;
    index = *count;
    kind = 0x14;
    actorGetNodePos(actor, 0xD, &posA[0], &posA[1], &posA[2]);
    actorGetNodePos(actor, 0xE, &posB[0], &posB[1], &posB[2]);
    angle = mathAtan2(posA[2] - posB[2], posA[0] - posB[0]);
    if (active == 0) {
        state->prevAngle = angle;
        state->prevY = posA[1];
        if ((state->holdTimer != 0) && (actor->flags & 0x100) && (state->mode == 2)) {
            state->holdTimer -= 1;
        }
    } else {
        ret = mathAngleRadDeltaTurns(&state->prevAngle, angle);
        state->weight = state->weight + ((-128.0f - state->weight) * 0.3);
        value = (s8) (s32) state->weight;
        accel1 = 0.4f * ret;
        accel0 = playerWeaponCalculateTrajectory25(actor, state, 0.02f);
    }
    for (i = 0; i != 4; i++) {
        if (active != 0) {
            playerWeaponCalculateTrajectory24(accel0, 0.06f, &pair->springX, &angle0);
            playerWeaponCalculateTrajectory24(accel1, 0.06f, &pair->springY, &angle1);
        }
        slots[index].weight = value;
        slots[index].bone = kind;
        slots[index].rotX = (s32) ((pair->springX.angle + pair->springX.offset) * 10430.218905280077);
        slots[index].rotY = 0;
        slots[index].rotZ = (s32) ((pair->springY.angle + pair->springY.offset) * 10430.218905280077);
        pair++;
        index++;
        kind++;
    }
    *count = index;
}

extern s8 D_80752CBF[];

void playerWeaponSpawnProjectile(Actor *actor, BoneRotation *slots, s32 *count) {
    F56AState *state = ((F56AActor *) actor)->weaponState;
    F56APair *pair;
    BoneRotation *slot;
    f32 trajectory;
    s32 index;
    s32 kind;
    s32 value;
    s32 i;
    s32 k;
    f32 angle0;
    f32 angle1;
    f32 ret;
    f32 angle;
    f32 pos[2][3];
    f32 y;
    f32 newvel;
    f32 delta;
    F56AState *cur;
    s32 active;
    f32 boost;
    f32 accel0;
    f32 accel1;

    index = *count;
    ret = 0;
    kind = 0x16;
    cur = state;
    active = playerWeaponCalculateTrajectory26(actor, state, 5);
    value = -0x80;
    actorGetNodePos(actor, 0xD, &pos[0][0], &pos[0][1], &pos[0][2]);
    actorGetNodePos(actor, 0xE, &pos[1][0], &pos[1][1], &pos[1][2]);
    angle = mathAtan2(pos[0][2] - pos[1][2], pos[0][0] - pos[1][0]);
    if (active == 0) {
        for (k = 0; k != 2; k++) {
            cur[k].prevAngle = angle;
            cur[k].prevY = pos[k][1];
        }
        if (k == 0) {}  // FAKE: dead use of k after loop 1 (index in s7, slots in s2)
        if ((state->holdTimer != 0) && (actor->flags & 0x100) && (state->mode == 5)) {
            state->holdTimer -= 1;
        }
    } else {
        s16 idx = actor->sub4->model->animId;

        if (idx >= 0) {
            newvel = D_80752CBF[idx];
        } else {
            newvel = -128.0f;
        }
        state->weight = state->weight + ((newvel - state->weight) * 0.3);
        value = (s8) (s32) state->weight;
        ret = mathAngleRadDeltaTurns(&state->prevAngle, angle);
        trajectory = playerWeaponCalculateTrajectory25(actor, state, 0.02f);
    }
    slot = slots; slot += index; k = 0; do { // LAYOUT: one source line lets as1 schedule the loop preheader
        accel1 = 0.0f;
        accel0 = 0.0f;
        angle0 = 0.0f;
        angle1 = 0.0f;
        pair = cur->springs;
        if (active != 0) {
            y = pos[k][1];
            newvel = y - cur->prevY;
            delta = newvel - cur->prevVelY;
            cur->prevY = y;
            cur->prevVelY = newvel;
            boost = 0.4f * ret;
            y = (0 < ret) ? ret : -ret;
            if (k != 0) {
                accel0 = -trajectory;
                accel1 = -((y * 0.3f) + (-0.015f * delta - 0.0008f * newvel));
            } else {
                accel0 = trajectory;
                accel1 = (y * 0.3f) + (-0.015f * delta - 0.0008f * newvel);
            }
            accel0 += boost;
        }
        i = 0;
        do {
            if (active != 0) {
                playerWeaponCalculateTrajectory24(accel1, 0.06f, &pair->springX, &angle0);
                playerWeaponCalculateTrajectory24(accel0, 0.06f, &pair->springY, &angle1);
            }
            slot->weight = value;
            slot->bone = kind;
            slot->rotX = 0;
            slot->rotY = (s32) ((pair->springY.angle + pair->springY.offset) * 10430.218905280077);
            slot->rotZ = (s32) ((pair->springX.angle + pair->springX.offset) * 10430.218905280077);
            i++;
            pair++;
            index++;
            slot++;
            kind++;
        } while (i != 8);
        k++; cur++; // LAYOUT: one source line orders the k/cur reload-increment-store tail
    } while (k != 2);
    *count = index;
}

extern s8 D_80752D4E[];
extern f32 D_80752F4C;

void playerWeaponInitCrosshair(Actor *actor, BoneRotation *slots, s32 *count) {
    F56AState *state;
    F56APair *pair;
    s32 index;
    s32 kind;
    s32 active;
    s32 i;
    s32 pad;
    f32 angle0;
    f32 angle1;
    f32 jitterScale;
    f32 gain;
    f32 fs3;
    f32 fs2;
    f32 fs1;
    f32 fs0;
    f32 z;
    f32 y;
    f32 x;
    s8 value[4];
    f32 target;
    f32 dz;
    f32 result;
    f64 pad2;

    state = ((F56AActor *) actor)->weaponState;
    index = *count;
    kind = 0x1A;
    pair = state->springs;
    angle1 = 0.0f;
    angle0 = 0.0f;
    fs3 = 0.0f;
    fs2 = 0.0f;
    jitterScale = 0.0003f;
    gain = 1.0f;
    fs1 = 0.06f;
    active = playerWeaponCalculateTrajectory26(actor, state, 3);
    value[3] = -0x80;
    actorGetNodePos(actor, 5, &x, &y, &z);
    if (active == 0) {
        state->prevAngle = (f32) actor->yaw;
        state->prevY = y;
        D_80752F4C = 0.0f;
        if ((state->holdTimer != 0) && (actor->flags & 0x100) && (state->mode == 3)) {
            state->holdTimer -= 1;
        }
    } else {
        fs2 = y - state->prevY;
        dz = fs2 - state->prevVelY;
        fs0 = state->prevAngle - (f32) actor->yaw;
        if (actor->sub4->model->animId >= 0) {
            target = (f32) D_80752D4E[actor->sub4->model->animId];
        } else {
            target = -128.0f;
        }
        state->prevAngle = (f32) actor->yaw;
        state->weight = (f32) ((f64) state->weight + ((f64) (target - state->weight) * 0.3));
        value[3] = (s8) state->weight;
        if (actor->state == 0x4F) {
            fs1 = 0.01f;
            jitterScale = 0.0001f;
            gain = 0.4f;
        }
        result = playerWeaponCalculateTrajectory25(actor, state, 0.011f);
        state->prevY = y;
        state->prevVelY = fs2;
        fs3 = (-result - ((0.005f * dz) + (0.0008f * fs2))) * gain;
        if ((32.0f + ((1.0f - gain) * 8.0f)) < (f32) ((randomNonNegative() >> 15) % 40)) {
            D_80752F4C = (f32) (0x14 - ((randomNonNegative() >> 15) % 40)) * jitterScale;
        }
        if (fs0 > 2048.0f) {
            fs0 = 4096.0f - fs0;
        } else if (fs0 < -2048.0f) {
            fs0 = -(4096.0f + fs0);
        }
        fs2 = (f32) ((f64) ((1.0f - (actor->speedXZ / 130.0f)) * D_80752F4C) + (2e-05 * (f64) fs0));
    }
    for (i = 0; i != 11; i++) {
        if (active != 0) {
            playerWeaponCalculateTrajectory24(fs3, fs1, &pair->springX, &angle0);
            playerWeaponCalculateTrajectory24(fs2, fs1, &pair->springY, &angle1);
        }
        slots[index].weight = value[3];
        slots[index].bone = kind;
        if (kind == 0) {}  // FAKE: extra use raises kind's uopt priority above the hoisted loop addresses (kind in s3)

        slots[index].rotX = (s16) (s32) ((f64) (pair->springX.angle + pair->springX.offset) * 10430.218905280077);
        slots[index].rotY = (s16) (s32) ((f64) (pair->springY.angle + pair->springY.offset) * 10430.218905280077);
        slots[index].rotZ = 0;
        pair++;
        index++;
        kind++;
    }
    *count = index;
}

void playerWeaponCrosshairUpdate(Actor *actor, BoneRotation *slots, s32 *count) {
    f32 x;
    s16 delta;
    CamState *camState;
    f32 y;
    f32 planarAngle;
    camState = ((PlayerState *)actor->customState)->camActor->customState;
    delta = (camState->unkB2 - actor->yaw) - 0x800;
    x = gPlayerSlots[gCurrentPlayerIndex].camZ - gPlayerSlots[gCurrentPlayerIndex].focusZ;
    y = gPlayerSlots[gCurrentPlayerIndex].camX - gPlayerSlots[gCurrentPlayerIndex].focusX;
    planarAngle = mathAtan2(gPlayerSlots[gCurrentPlayerIndex].camY - gPlayerSlots[gCurrentPlayerIndex].focusY, sqrtf((x * x) + (y * y)));
    delta &= 0xFFF;
    if ((delta < 0xC00) && (delta >= 0x801)) {
        actor->yaw = (actor->yaw + delta) - 0xC00;
        delta = 0xC00;
    } else if ((delta >= 0x401) && (delta < 0x800)) {
        actor->yaw = (actor->yaw + delta) - 0x400;
        delta = 0x400;
    }
    slots[*count].weight = -128;
    slots[*count].bone = 2;
    slots[*count].rotY = (s16)(u32)(((f64)delta / 4095.0) * 65535.0);
    slots[*count].rotX = (s16)(u32)((f64)(planarAngle / 6.2831855f) * 65535.0);
    slots[*count].rotZ = 0;
    *count += 1;
}



void playerWeaponCrosshairRender(Actor *actor, BoneVector *entries, s32 *count) {
    f32 fade;
    f32 scaleY;
    f32 scaleX;
    u16 timer;
    s32 adj;
    s32 inc;
    s32 sel;
    if (gActivePlayerState && gActivePlayerState) {}  // FAKE: dead global test steers uopt (ps in v0, u16 in v1)
    timer = gActivePlayerState->unk21E;
    fade = (f32)timer * 0.03333333507f;
    if ((f64)fade < 1e-05) fade = 0.000009999999747f;
    sel = actor->state;
    if ((sel == 0x34) || (sel == 0x84)) {
        if ((f64)gActivePlayerState->unk25C > 0.01) {
            gActivePlayerState->unk258 = (f32)((f64)gActivePlayerState->unk258 * 1.07);
            gActivePlayerState->unk25C = (f32)((f64)gActivePlayerState->unk25C * 0.7);
        } else {
            actor->flags &= ~0x8000;
            if (gActivePlayerState->unk21E != 0) gActivePlayerState->unk21E -= 1;
            actor->alpha = (s16)(255.0f * fade);
        }
        scaleX = gActivePlayerState->unk258;
        scaleY = gActivePlayerState->unk25C;
    } else {
        scaleY = fade;
        scaleX = fade;
        if (timer < 0x1E) {
            actor->flags |= 0x8000;
            adj = 0x1E - gActivePlayerState->unk21E;
            if (timer == 0) {}  // FAKE: dead use steers uopt priority
            inc = (adj >= 3) ? 2 : adj;
            gActivePlayerState->unk21E += inc;
            gActivePlayerState->unk258 = 1.0f;
            gActivePlayerState->unk25C = gActivePlayerState->unk258;
        }
    }
    if (entries && entries) {}  // FAKE: dead use of arg1 raises its uopt priority (entries in s0, count stays in a2)
    entries[*count].bone = 0;
    entries[*count].lastBone = 0xFF;
    entries[*count].x = scaleX;
    entries[*count].y = scaleY;
    entries[*count].z = scaleX;
    *count += 1;
}

extern f32 mathSinF(s16);
void playerWeaponUpdateHomingTarget(Actor *actor, BoneRotation *slots, s32 *count) {
    s32 entry_index;
    s8 v;
    u16 angle;
    u16 yaw;
    u16 scaled;
    f32 amplitude;
    f32 cosine;
    entry_index = *count;
    if (actor->contactFlags & 1) {
        gActivePlayerState->homingStrength += 2;
        if (gActivePlayerState->homingStrength >= 0x80) gActivePlayerState->homingStrength = 0x7F;
    } else {
        gActivePlayerState->homingStrength -= 2;
        if (gActivePlayerState->homingStrength < 0) gActivePlayerState->homingStrength = 0;
    }
    if (gActivePlayerState->homingStrength != 0) {
        yaw = (actor->floorSlopeYaw - 0x800) & 0xFFF;
        scaled = (0x400 - actor->floorSlopePitch) & 0xFFF;
        if (scaled >= 0x156) scaled = 0x155;
        scaled = scaled * 0x10;
        angle = mathAngleSignedDistance(actor->yaw, yaw);
        amplitude = mathCosF(angle) * scaled;
        cosine = mathSinF(angle);
        v = gActivePlayerState->homingStrength * 6 / 10;
        if (v != 0) {
            slots[entry_index].bone = 1;
            slots[entry_index].rotY = 0;
            slots[entry_index].weight = v;
            slots[entry_index].rotX = (s16)amplitude;
            slots[entry_index].rotZ = (s16)((-cosine) * (f32)scaled);
            entry_index += 1;
        }
        v = gActivePlayerState->homingStrength * 3 / 10;
        if (v != 0) {
            slots[entry_index].bone = 2;
            slots[entry_index].rotY = 0;
            slots[entry_index].weight = v;
            slots[entry_index].rotX = (s16)amplitude;
            slots[entry_index].rotZ = (s16)((-cosine) * (f32)scaled);
            entry_index += 1;
        }
    }
    *count = entry_index;
}


void playerWeaponFireGun(Actor *actor, BoneVector *entries, s32 *count, u8 kind0, u8 kind1, f32 charge, f32 amplitude) {
    f32 angle;

    angle = mathSinF((s16)(charge * 2048.0f));
    entries[*count].bone = kind0;
    entries[*count].lastBone = kind1;
    entries[*count].x = 1.0f;
    entries[*count].y = ((f32)angle * amplitude) + 1.0;
    entries[*count].z = 1.0f;
    *count += 1;
}


void playerWeaponReload(Actor *actor, PlayerState *ps, u16 weapon) {
    u8 state0;
    u8 state2;
    u16 bone;
    s32 selector;
    s32 shouldSpawn;

    selector = weapon;
    switch (selector) {
    case 0:
        state0 = ps->unk8E;
        if (state0 != 0) {
            if ((state0 == 0x10) && ((s32)ps->unk8F < 4)) {
                ps->unk8F = 0;
                return;
            }
        } else {
            if ((s32)ps->unk8F >= 4) {
                effectSpawnBoneWhite(actor, 0xA, 0.3f, 0.0f, 0.0f, 0.0f, -10);
                return;
            }
            return;
        }
        break;
    case 1:
        selector = ps->unk8E;
        shouldSpawn = 0;
        if ((selector != 0) && (selector != 3)) {
            if ((selector == 0x10) && ((s32)ps->unk8F < 6)) {
                ps->unk8F = 0;
            }
        } else if ((s32)ps->unk8F >= 6) {
            shouldSpawn = 1;
        }
        if (shouldSpawn != 0) {
            if (ps->unk8E != 0) {
                bone = ps->unk90 + 9;
            } else {
                bone = ps->unk91 + 9;
            }
            effectSpawnBoneWhite(actor, bone, 0.2f, 0.0f, 0.0f, 0.0f, -10);
            return;
        }
        break;
    case 4:
    case 5:
        state2 = ps->unk8E;
        if (state2 != 0) {
            if ((state2 == 0x10) && ((s32)ps->unk8F < 3)) {
                ps->unk8F = 0;
                return;
            }
        } else if ((s32)ps->unk8F >= 3) {
            effectSpawnBoneWhite(actor, 0xA, 0.6f, 0.0f, 0.0f, 0.0f, -10);
        }
        break;
    }
}


extern u8 gWaypointFlags;

void playerWeaponSpawnMuzzleFlash(Actor *actor, u16 weapon) {
    PlayerState *ps;
    s32 slotCount;
    s32 entryCount;
    ActorSub4 *sub;
    BoneRotation *slots;
    BoneVector *entries;
    BoneVector *offsets;
    f32 charge;
    f32 t;
    f32 v;

    ps = actor->customState;
    if ((actor->state != 0x77) && (actor->flags & 4)) {
        sub = actor->sub4;
        slots = sub->boneRotations;
        entries = sub->boneScales;
        offsets = sub->boneOffsets;
        slotCount = 0;
        entryCount = 0;
        if ((func_80714608(0) != 0) && ((ps->unk21E != 0x1E) || (actor->state == 0x34))) {
            playerWeaponCrosshairRender(actor, entries, &entryCount);
        }
        switch (weapon) {
        case 0:
            playerWeaponUpdateHomingTarget(actor, slots, &slotCount);
            playerWeaponAimTarget(actor, slots, &slotCount);
            if (ps->unk8E != 0) {
                playerWeaponCalculateTrajectory4(actor, slots, &slotCount);
            }
            break;
        case 1:
            switch (actor->state) {
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
                break;
            case 2:
                playerWeaponCrosshairUpdate(actor, slots, &slotCount);
                break;
            default:
            case 3:
            case 4:
            case 5:
            case 6:
                playerWeaponUpdateHomingTarget(actor, slots, &slotCount);
                break;
            }
            playerWeaponInitCrosshair(actor, slots, &slotCount);
            if (ps->unk8E != 0) {
                playerWeaponCalculateTrajectory7(actor, slots, &slotCount);
            }
            break;
        case 2:
            switch (actor->state) {
            case 0x26:
                if (actor->unk155 != 0) {
                    t = actor->sub4->model->frame;
                    if (t < 6.0f) {
                        v = 0.0f;
                    } else {
                        v = t - 6.0f;
                    }
                    charge = (f64)v / 17.0 > 1.0 ? 1.0 : (f64)v / 17.0;
                    playerWeaponFireGun(actor, entries, &entryCount, 0xA, 0xB, charge, (f32)(gCurrentMap == 0xCD ? 17.0 : 2.5));
                }
                break;
            case 0x27: {
                t = actor->sub4->model->frame;
                if (t < 6.0f) {
                    v = 0.0f;
                } else {
                    v = t - 6.0f;
                }
                charge = (f64)v / 17.0 > 1.0 ? 1.0 : (f64)v / 17.0;
                playerWeaponFireGun(actor, entries, &entryCount, 5, 6, charge, (f32)(gCurrentMap == 0xCD ? 17.0 : 2.5));
                break;
            }
            case 0x28: {
                t = actor->sub4->model->frame;
                if (t < 7.0f) {
                    v = 0.0f;
                } else {
                    v = t - 7.0f;
                }
                charge = (f64)v / 14.0 > 1.0 ? 1.0 : (f64)v / 14.0;
                playerWeaponFireGun(actor, entries, &entryCount, 9, 0xB, charge, 1.8f);
                playerWeaponFireGun(actor, entries, &entryCount, 4, 6, charge, 1.8f);
                break;
            }
            case 0x29: {
                t = actor->sub4->model->frame;
                if (t < 4.0f) {
                    v = 0.0f;
                } else {
                    v = t - 4.0f;
                }
                charge = (f64)v / 6.0 > 1.0 ? 1.0 : (f64)v / 6.0;
                playerWeaponFireGun(actor, entries, &entryCount, 9, 0xB, charge, 1.3f);
                playerWeaponFireGun(actor, entries, &entryCount, 4, 6, charge, 1.3f);
                break;
            }
            }
            break;
        case 3:
            playerWeaponSpawnProjectile(actor, slots, &slotCount);
            if (ps->unk8E != 0) {
                playerWeaponCalculateTrajectory23(actor, slots, &slotCount);
            }
            break;
        case 4:
        case 5:
            if (ps->unk8E != 0) {
                playerWeaponCalculateTrajectory22(actor, slots, &slotCount);
            }
            break;
        case 6:
            break;
        }
        slots[slotCount].weight = 0;
        entries[entryCount].bone = 0xFF;
        offsets->bone = 0xFF;
        if (ps->unk8E != 0) {
            ps->unk8E -= 1;
            if (ps->gunDrawn != 0) {
                playerWeaponReload(actor, ps, weapon);
            }
        }
        if (ps->unk8E == 0) {
            ps->unk8F = 0;
        }
    }
}



void playerWaypointPathsLoad(s16 pathsId) {
    void *buffer;

    buffer = assetLoad(0x15, pathsId, 1, 0);
    playerWaypointPathsParse(buffer);
    if (buffer != NULL) {
        assetFreeBuffer(buffer, 0x4C, 0x56);
    }
}

typedef struct WaypointNode {
    s16 x;
    s16 y;
    s16 z;
    u8 timer0;
    u8 timer1;
    u8 timer2;
    u8 speed;
    s16 timer3;
    s16 timer4;
    s16 timer5;
    s16 delay;
} WaypointNode;

void actorSetPositionAndFacingAngle(Actor *actor, WaypointNode *node) {
    s16 angle;

    actorClearMovementFlags(actor);
    actor->x = node->x;
    actor->y = node->y;
    actor->z = node->z;
    angle = mathAngleBetweenPoints2D(node[1].x, node[1].z, node->x, node->z);
    actor->moveYaw = angle;
    actor->yaw = angle;
}

typedef struct WaypointPath {
    s16 count;
    u8 pad2[2];
    WaypointNode *nodes;
} WaypointPath;

typedef struct WaypointPathTable {
    s16 count;
    u8 pad2[2];
    WaypointPath *paths;
} WaypointPathTable;

extern s8 D_807463B8;
extern WaypointPathTable *gWaypointPaths;
extern u8 gScreenRenderFlags;
extern WaypointPath *gWaypointPathEntry;
extern WaypointNode *gWaypointCursor;
extern Actor *gWaypointActor;
extern s16 gWaypointIndex;
extern s16 gWaypointCallbackId;
extern void *gWaypointCallbackParam;

void playerWaypointPathStart(u8 pathIndex, Actor *actor, void *callbackParam, s16 callbackId, u8 skipPlace) {
    PlayerState *ps;

    ps = actor->customState;
    if (gWaypointPaths->count >= pathIndex) {
        D_807463B8 = 3;
        gScreenRenderFlags |= 0x10;
        gWaypointActor = actor;
        ps->stateFlags &= ~1;
        gWaypointIndex = 0;
        gWaypointPathEntry = gWaypointPaths->paths + pathIndex;
        gWaypointCursor = gWaypointPathEntry->nodes;
        gWaypointCallbackId = callbackId;
        gWaypointCallbackParam = callbackParam;
        if (skipPlace == 0) {
            actorSetPositionAndFacingAngle(actor, gWaypointCursor);
        }
    }
}


typedef struct F5DDeferredEntry {
    s16 count;
    u8 pad2[2];
    void *data;
} F5DDeferredEntry;


void deferredEntryFree(F5DDeferredEntry *entry) {
    heapFreeDeferred(entry->data);
    entry->count = 0;
}



void playerWaypointPathStartPacked(Actor *actor, void *callbackParam, s16 packedPath, s16 callbackId) {
    s32 skipPlace;

    if (packedPath & 0x8000) {
        skipPlace = 1;
    } else {
        skipPlace = 0;
    }
    packedPath &= 0x7FFF;
    playerWaypointPathStart((u8) packedPath, actor, callbackParam, callbackId, skipPlace);
    gWaypointFlags = 0;
}

extern s32 gGlobalPauseFlags;


typedef struct F5N6Input {
    s16 x;
    s16 y;
    s16 z;
    u8 angle;
} F5N6Input;

void playerWaypointPathStartLineFromPoint(Actor *actor, F5N6Input *input, u8 length) {
    WaypointNode *p;
    WaypointNode *q;
    WaypointPath *entry;

    entry = &gWaypointPaths->paths[gWaypointPaths->count];
    entry->count = 2;
    entry->nodes = heapAlloc(2 * sizeof(WaypointNode));
    heapClearBlock(entry->nodes);
    q = entry->nodes + 1;
    p = entry->nodes;
    p->x = input->x;
    p->y = input->y;
    p->z = input->z;
    p->speed = 0x32;
    q->x = mathSinF((s16)((input->angle / 255.0) * 4095.0)) * length + input->x;
    q->y = input->y;
    q->z = mathCosF((s16)((input->angle / 255.0) * 4095.0)) * length + input->z;
    q->speed = 0x32;
    playerWaypointPathStart(gWaypointPaths->count, actor, 0, 0, 0);
    gWaypointFlags = 0;
    gGlobalPauseFlags |= 0x400;
}


void playerWaypointPathStartLineFromActor(Actor *actor, s16 targetX, s16 targetZ, u8 length) {
    WaypointNode *p;
    s16 angle;
    WaypointNode *q;
    WaypointPath *entry;

    angle = mathAngleBetweenPoints2D((f32)targetX, (f32)targetZ, actor->x, actor->z);
    entry = &gWaypointPaths->paths[gWaypointPaths->count];
    if (actor->state != 0x44) {
        entry->count = 2;
        entry->nodes = heapAlloc(2 * sizeof(WaypointNode));
        heapClearBlock(entry->nodes);
        q = entry->nodes + 1;
        p = entry->nodes;
        p->x = actor->x;
        p->y = actor->y;
        p->z = actor->z;
        p->speed = 0x28;
        q->x = mathSinF(angle) * length + actor->x;
        q->y = actor->y;
        q->z = mathCosF(angle) * length + actor->z;
        q->speed = 0x28;
        playerWaypointPathStart(gWaypointPaths->count, actor, 0, 0, 0);
        gWaypointFlags = 0;
        gGlobalPauseFlags |= 0x400;
    }
}


void playerWaypointSnapInput(void) {
    gWaypointFlags |= 2;
}

void timerDecrementOrSetFlag(u16 *flags, s16 *timer, u8 *count, u16 bit) {
    if (*timer != 0) {
        (*timer)--;
        return;
    }
    if (*count != 0) {
        (*count)--;
        *flags |= bit;
    }
}


#define WAYPOINT_MAX(a, b) ((a) > (b) ? (a) : (b))
#define WAYPOINT_MIN(a, b) ((a) < (b) ? (a) : (b))
#define WAYPOINT_CLAMP_S8(x) WAYPOINT_MIN(WAYPOINT_MAX(x, -128.0f), 127.0f)

s32 playerStateQueueCallback();
extern u8 gGameMode;
extern u8 sHudDisabled;

void playerStateWaypointAimUpdate(OSContPad *control, OSContPad *unused) {
    PlayerState *tgt;
    f32 ang;
    f32 camAng;
    f32 pitch;
    WaypointNode *cur;
    WaypointNode *next;
    f32 blend;
    f32 speed;
    s16 yawT;
    s32 eq;
    f32 dx;
    f32 dz;
    u8 close;
    u8 flags;
    s16 pitchT;

    cur = gWaypointCursor;
    tgt = gWaypointActor->customState;
    blend = 0.2f;
    next = gWaypointCursor + 1;
    speed = (u32)cur->speed * 0.7;
    dx = gWaypointActor->x - next->x;
    dz = gWaypointActor->z - next->z;
    close = dx * dx + dz * dz < 100.0f;
    if (close) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    flags = gWaypointFlags;
    if (gWaypointCallbackParam && gWaypointCallbackParam) {}  // FAKE: dead test
    if ((flags == 0) & 1) {  // FAKE: & 1 steers the flags test
        if (gWaypointCursor != 0) {}  // FAKE: dead test at block start
        gWaypointFlags |= 1;
        control->stick_x = 0;
        control->stick_y = 0;
    }
    if (gWaypointFlags || gWaypointCallbackParam) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (close) {
        eq = gWaypointIndex + 2 == gWaypointPathEntry->count;
        if (flags == 0) {}  // FAKE: dead test
        if (eq) {
            D_807463B8 = 0;
            if (gGameMode == 0) {
                gScreenRenderFlags &= 0xFFEF;
                sHudDisabled = 0xFF;
            }
            if (gWaypointCallbackId != 0) {
                if (gWaypointFlags != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                playerStateQueueCallback(gWaypointCallbackId, gWaypointCallbackParam, 0, &gWaypointCursor); // FAKE: 4th arg keeps &gWaypointCursor hoisted in $a3
                if (gWaypointCursor == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
            tgt->stateFlags |= 1;
            gGlobalPauseFlags &= ~0x400;
            playerInitMoveParams();
        } else {
            gWaypointIndex += 1;
            gWaypointCursor++;
            cur = gWaypointCursor;
            next = cur + 1;
            if (gWaypointIndex || gWaypointFlags) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
    }
    control->button = 0;
    timerDecrementOrSetFlag(&control->button, &cur->timer3, &cur->timer0, 0x8000);
    timerDecrementOrSetFlag(&control->button, &cur->timer4, &cur->timer1, 0x4000);
    timerDecrementOrSetFlag(&control->button, &cur->timer5, &cur->timer2, 0x2000);
    pitchT = 0;
    if (cur->delay != 0) {
        cur->delay = cur->delay - 1;
        yawT = 0;
    } else {
        if (gWaypointFlags & 2) {
            blend = 1.0f;
            gWaypointFlags &= 0xFFFD;
        }
        if (gWaypointActor->state == 0x4F) {
            ang = mathAngleBetweenPointsDeg(next->x, next->z, gWaypointActor->x, gWaypointActor->z) * 0.017453292f - (gWaypointActor->yaw * 3.1415927f) * 0.00048828125;
            pitch = mathCalculatePitchAngle(next->x, next->y, next->z, gWaypointActor->x, gWaypointActor->y, gWaypointActor->z, 0);
            control->button |= 0x4000;
            yawT = ang;
            pitchT = WAYPOINT_CLAMP_S8(sinApprox(pitch) * speed);
        } else {
            camAng = mathAngleBetweenPointsDeg(gPlayerSlots->focusX, gPlayerSlots->focusZ, gPlayerSlots->camX, gPlayerSlots->camZ);
            ang = mathAngleBetweenPointsDeg(next->x, next->z, gWaypointActor->x, gWaypointActor->z) * 0.017453292f - camAng * 0.017453292f;
            yawT = WAYPOINT_CLAMP_S8(sinApprox(ang) * speed);
            pitchT = WAYPOINT_CLAMP_S8(cosApprox(ang) * speed);
        }
    }
    control->stick_x = control->stick_x + (yawT - control->stick_x) * blend;
    control->stick_y = control->stick_y + (pitchT - control->stick_y) * blend;
}

void playerWaypointPathsParse(void *data) {
    u8 *next;
    WaypointNode *destination;
    u8 *source;
    WaypointPath *entry;
    s16 outer;
    s16 inner;

    if (data != NULL) {
        gWaypointPaths->count = *(s16 *)data;
        source = (u8 *)data + 2;
        gWaypointPaths->paths = heapAlloc((gWaypointPaths->count + 1) * sizeof(WaypointPath));
        entry = gWaypointPaths->paths;
        for (outer = 0; outer < gWaypointPaths->count; outer++) {
            entry->count = *(s16 *)source;
            next = source + 2;
            for (inner = 0; inner < entry->count; inner++) {
                if (inner == 0) {
                    entry->nodes = heapAlloc(entry->count * sizeof(WaypointNode));
                    destination = entry->nodes;
                } else {
                    destination++;
                }
                *destination = *(WaypointNode *)next;
                next += sizeof(WaypointNode);
            }
            source = next;
            entry++;
        }
    } else {
        gWaypointPaths->count = 0;
    }
}

