#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/117190_menu_transition.h"
#include "proto/global/133A90_prox_path.h"
#include "proto/global/135D30_flags.h"
#include "proto/global/15050_heap.h"
#include "proto/global/166A0_random.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/9CE20_projectile_behaviours.h"
#include "proto/global/CEAE0_player_update.h"

// This TU's .data (0x807502D0-0x8075039C + 4-byte TU pad): one 4-byte slot per object, the movement
// tuning scalars of the actor and player code (80150, 936B0, 9DD70, A2F10, AA960, B7490, BB300, C4620,
// E4090, 11BC10, 1295B0 and the boss/minecart overlays keep their externs); 9CE20 reads gSwingLeapMaxSpeedXZ and
// gSwingLeapMaxSpeedY, the only text TU between 9BF30 and 9DD70. D_807502D4 and D_80750304..D_80750334 are
// unreferenced.
s16 gCarryMinFallSpeed = -220;
s16 D_807502D4 = -100;
s16 gArmydilloTerminalSpeedY = -600;
s16 gWaypointBossTerminalSpeedY = -500;
s16 gDefaultActorTerminalSpeedY = -220;
f32 gCarryGravity = -20.0f;
f32 gDefaultActorGravity = -20.0f;
f32 gAirPatrolAccelY = -15.0f;
f32 gWaypointBossAccelY = -30.0f;
f32 gActorDefaultAccelY = -30.0f;
f32 gDefaultAccelY = -28.0f;
f32 gPufftossSinkAccelY = -3.0f;
f32 gVehicleGravity = -20.0f;
s16 D_80750304 = 2;
s16 D_80750308 = 10;
s16 D_8075030C = 6;
s16 D_80750310 = 12;
s16 D_80750314 = 10;
s16 D_80750318 = 4;
s16 D_8075031C = 255;
s16 D_80750320 = 8;
s16 D_80750324 = 12;
s16 D_80750328 = 12;
s16 D_8075032C = 8;
s16 D_80750330 = 8;
s16 D_80750334 = 4;
s16 gLadderJumpSpeed = 250;
s16 gVehicleWaterJumpSpeed = 250;
s16 gFlyPatrolShotInterval = 60;
s16 gProjectileLifetime = 200;
s16 gBounceExplodeLifetime = 200;
s16 gBounceExplodeShortLifetime = 30;
s16 gHomingShotLifetime = 50;
s16 gFeatherShotLifetime = 50;
s16 gShotLifetime = 50;
s16 gMultiplayerShotLifetime = 50;
s16 gCoconutShotLifetime = 50;
s16 gHomingShotLongLifetime = 100;
s16 gFeatherShotLongLifetime = 100;
s16 gShotLongLifetime = 100;
s16 gMultiplayerShotLongLifetime = 100;
s16 gCoconutShotLongLifetime = 100;
s16 gNumberedTargetLifetime = 300;
s16 gSwingLeapMaxSpeedXZ = 200;
s16 gSwingLeapMaxSpeedY = 150;
s16 sBounceFadeLaunchSpeedXZ = 200;
f32 sBounceFadeGravity = -160.0f;
s16 sBounceMinSpeedY = -1760;
s16 gBarrelMountLaunchSpeedY = 300;
f32 gSpinningActorGravity = -30.0f;
f32 gFallAndBurstGravity = -15.0f;

typedef struct BoneChainData {
    /* 0x00 */ f32 swingAmplitude;
    /* 0x04 */ f32 phaseStep;
    /* 0x08 */ f32 damping;
    /* 0x0C */ f32 phase;
    /* 0x10 */ f32 nodeAngle;
    /* 0x14 */ u8 playerHolding;
    /* 0x15 */ u8 leapTimer;
    /* 0x16 */ u8 sinkTimer;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ f32 spinAngle;
    /* 0x1C */ f32 baseY;
    /* 0x20 */ f32 bobPhase;
    /* 0x24 */ f32 bobSpeed;
    /* 0x28 */ u8 enabled;
} BoneChainData;

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern PlayerStruct *gPlayerSlots;
extern u32 gFrameDelta;


void actorBoneChainSwingUpdate(nodeCount)
u8 nodeCount;
{
    BoneChainData *data;
    BoneRotation *node;
    s16 i;
    f32 padA;
    PlayerState *player;
    f32 padC;
    s16 *p;
    u8 dir;
    f32 maxAmplitude = 15.0f;

    data = gCurrentActor->customState;
    player = gPlayerSlots->actor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        data->swingAmplitude = 0.0f;
        data->phaseStep = 0.10471976f;
        data->damping = 0.75f;
        data->nodeAngle = 0.0;
        data->phase = 0.f; // FAKE: literal spelling; cfe keeps f32 literal text, so `0.f` is its own zero constant (Q0473): mtc1 zero,$f16 at 0x5c instead of sharing the 0.0f/0.0 register
        data->baseY = gCurrentActor->y;
        data->bobPhase = 0.000f; // FAKE: literal spelling; a fourth distinct zero constant (Q0473) for mtc1 zero,$f4 at 0x78; `0.0f`/`0.0`/`0`/`0.0F` share a web with swingAmplitude or nodeAngle (257-263)
        data->bobSpeed = ((randomNonNegative() >> 15) % 100) / 1000.0 + 0.1;
        data->spinAngle = 0.0f;
        gCurrentActor->sub4->boneRotations = heapAlloc(0x80);
        proxPathAdd(gCurrentActor, 0, 0, 0, nodeCount, 0.0f, nodeCount * 0.333333, 0.15f, 100.0f, 20.0f, 8.0f, 0, 0.0f, 0.0f, 0);
        for (i = 1; i <= nodeCount; i++) {
            proxPathSetSegment(gCurrentActor, 0, i - 1, i, i + 1, 0.333333f, 0.0f, 0.0f, 0, 0, 0, 0, 0);
        }
        gCurrentActor->cullMarginX = 0x3C;
        gCurrentActor->cullMarginY = 0xC8;
        data->playerHolding = 0;
        data->leapTimer = 0;
        data->enabled = flagGet(0x183, 0) || (gGlobalOverlayFlags & 0x10000000) || menuIsTransitionType3Or4();
    }
    if (gPrimaryPlayerActor->state == 0x63 || !data->enabled ||
        (*(s32 *)gCurrentActor->spawnData == 1 && !(player->stateFlags & 0x40))) {
        gCurrentActor->flags &= ~0x04000004;
    } else {
        gCurrentActor->flags |= 0x04000004;
    }
    for (i = 0; i < gActorGlobalState.volumeTriggerQueueCount; i++) {
        p = gActorGlobalState.volumeTriggerQueueId[i];
        switch (*p) { // FAKE: one-case switch whose case ends in continue (the loop tail, so same as break) shapes the store-path blocks; break 261, plain if 149
        case 0:
            data->sinkTimer = 0x50;
            continue;
        }
    }
    if (data->sinkTimer != 0) {
        gCurrentActor->y -= 1.0;
        data->sinkTimer--;
        data->baseY -= 1.0;
    }
    node = gCurrentActor->sub4->boneRotations;
    if (data->swingAmplitude > 2.0f) {
        if (data->phase < 3.926991f && data->phase + data->phaseStep >= 3.926991f) {
            if (gCurrentActor->actorType == 0x74) {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x257, data->swingAmplitude * 100.0 / maxAmplitude, 0x7F, 5);
            } else {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1C, data->swingAmplitude * 100.0 / maxAmplitude, 0x7F, 5);
            }
        }
        if (data->phase < 0.7853982f && data->phase + data->phaseStep >= 0.7853982f) {
            if (gCurrentActor->actorType == 0x74) {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x258, data->swingAmplitude * 25.0 / maxAmplitude, 0x7F, 0x14);
            } else {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1D, data->swingAmplitude * 25.0 / maxAmplitude, 0x7F, 0x14);
            }
        }
    }
    if (gCurrentActor->actorType != 0x74 && data->swingAmplitude > 10.0f) {
        if (data->phase < 2.3561945f && data->phase + data->phaseStep >= 2.3561945f) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1E, 0xFF, 0x7F, 0x14);
        }
        if (data->phase < 5.497787f && data->phase + data->phaseStep >= 5.497787f) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1E, 0xFF, 0x7F, 0x14);
        }
    }
    switch (gCurrentActor->actorType) {
    case 0x44:
    case 0x74:
        dir = 1;
        break;
    case 0x21:
    case 0x45:
        dir = 2;
        break;
    }
    data->phase += data->phaseStep * gFrameDelta * 0.5;
    data->nodeAngle = sinApprox(data->phase) * data->swingAmplitude;
    for (i = 0; i < 0xE; i++) {
        node[i].weight = -0x80;
        node[i].bone = i + dir;
        node[i].rotY = 0;
        node[i].rotX = (s16)(data->nodeAngle / 360.0 * 65535.0);
        node[i].rotZ = 0;
        data->nodeAngle *= data->damping;
    }
    if (gCurrentActor->actorType == 0x45 || gCurrentActor->actorType == 0x21) {
        node[i].weight = -0x80;
        node[i].bone = 1;
        node[i].rotY = (s16)(data->spinAngle / 360.0 * 65535.0);
        node[i].rotX = 0;
        node[i].rotZ = 0;
        i++;
        data->spinAngle += 20.0f;
        if (data->spinAngle > 360.0f) {
            data->spinAngle -= 360.0f;
        }
    }
    node[i].weight = 0;
    if (gPrimaryPlayerActor->state == 0x58) {
        data->leapTimer = 5;
    } else if (data->leapTimer != 0) {
        data->leapTimer--;
    }
    if ((gPrimaryPlayerActor->contactFlags & 0x40) && data->playerHolding == 0 && gCurrentActor == player->pathOwner) {
        data->swingAmplitude = maxAmplitude;
        if (mathAngleDistance(gPrimaryPlayerActor->yaw, gCurrentActor->yaw) < 0x400) {
            data->phase = 3.1415927f;
        } else {
            data->phase = 0.0f;
        }
    }
    if (data->phase >= 6.2831855f) {
        data->phase -= 6.2831855f;
    }
    if (data->phase < 0.0f) {
        data->phase += 6.2831855f;
    }
    if ((gPrimaryPlayerActor->contactFlags & 0x40) && gCurrentActor == player->pathOwner) {
        data->playerHolding = 1;
        data->swingAmplitude += 0.2;
        if (data->swingAmplitude > maxAmplitude) {
            data->swingAmplitude = maxAmplitude;
        }
    } else {
        data->playerHolding = 0;
        data->swingAmplitude += (0.0 - data->swingAmplitude) * 0.03;
        if (data->swingAmplitude < 2.0) {
            data->swingAmplitude = 0.0f;
        }
    }
    if ((gPrimaryPlayerActor->contactFlags & 0x40) && gCurrentActor == player->pathOwner) {
        if (player->pathDist < 1.5 && ((data->phase > 4.0 && (f64)data->phase < 4.712389f) ||
                                     ((f64)data->phase < 1.5707964f && data->phase > 0.9))) {
            player->leapSpeedXZ = gSwingLeapMaxSpeedXZ * (data->swingAmplitude / maxAmplitude);
            player->leapSpeedY = gSwingLeapMaxSpeedY * (data->swingAmplitude / maxAmplitude);
        } else {
            player->leapSpeedXZ = 200.0f;
            player->leapSpeedY = 200.0f;
        }
        player->leapYaw = gCurrentActor->yaw & 0xFFF;
        if ((f64)data->phase < 1.5707964f || data->phase > 4.71238911151886) {
            player->leapYaw = (player->leapYaw + 0x800) & 0xFFF;
        }
    }
    switch (gCurrentActor->actorType) {
    case 0x21:
    case 0x45:
        gCurrentActor->y = sinApprox(data->bobPhase) * 5.0 + data->baseY;
        data->bobPhase += data->bobSpeed;
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void projectileBehaviourEntryA(void) {
    actorBoneChainSwingUpdate(0xE);
}

void projectileBehaviourEntryB(void) {
    actorBoneChainSwingUpdate(0xB);
}

void projectileBehaviourEntryC(void) {
    actorBoneChainSwingUpdate(0xB);
}

void projectileBehaviourEntryD(void) {
    actorBoneChainSwingUpdate(0xE);
}
