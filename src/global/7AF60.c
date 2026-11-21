#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/117190.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7AF60.h"
#include "proto/global/CEAE0.h"

extern u8 gCsInvulnerable;
extern u8 gPlayerCount;
extern PlayerStruct *gPlayerSlots;

void actorCheckPlayerSmallerThanAttacker(Actor *actor, Actor *attacker, ActorCallbackNode *node) {
    playerIsSmallerThanAttacker(actor, attacker);
}

u8 actorTargetIsVulnerable(Actor *actor, Actor *target, ActorCallbackNode *node) {
    return playerCanCollideWithActor(target) && gCsInvulnerable == 0;
}

u8 actorListHasId2TargetVulnerable(Actor *actor, Actor *target, ActorCallbackNode *node) {
    return func_806767E0(actor, target, node) && actorTargetIsVulnerable(actor, target, node);
}

s32 actorIsDamageFatal(Actor *target, Actor *attacker, u8 damageScale) {
    s16 remaining = target->health - attacker->damage;

    if (remaining <= 0) {
        return 1;
    }
    return 0;
}

u8 actorsFacingEachOther(Actor *actor, Actor *target, ActorCallbackNode *node) {
    u8 ret;

    ret = mathAngleDistance(mathAngleBetweenPoints2D((s16)actor->x, (s16)actor->z, (s16)target->x, (s16)target->z), actor->yaw) < 0x200;
    if (ret) {
        ret = actorIsFacingTarget(actor, target, node);
    }
    return ret;
}

u8 actorIsFacingTarget(Actor *actor, Actor *target, ActorCallbackNode *node) {
    return mathAngleDistance(mathAngleBetweenPoints2D((s16)actor->x, (s16)actor->z, (s16)target->x, (s16)target->z), target->yaw) < 0x3A9;
}

u8 actorIsTargetAbovePitchThreshold(Actor *actor, Actor *target, ActorCallbackNode *node) {
    return mathCalculatePitchAngle(actor->x, actor->y, actor->z, target->x, target->y, target->z, 0) > 0.7;
}

u8 actorIsTargetFallingFromAbove(Actor *actor, Actor *target, ActorCallbackNode *node) {
    return actorIsTargetAbovePitchThreshold(actor, target, node) && target->speedY < -100.0f;
}

u8 actorIsBelowTargetStationary(Actor *actor, Actor *target, u8 unused) {
    return actor->distToFloor < 10.0f && actor->y < target->y;
}

u8 actorIsTargetBelowNode(Actor *actor, Actor *target, ActorCallbackNode *node) {
    f32 x;
    f32 y;
    f32 z;
    s32 pad;

    if (actor->floorNodeId) {
        actorGetNodePos(actor, actor->floorNodeId, &x, &y, &z);
    } else {
        x = actor->x;
        y = actor->y;
        z = actor->z;
    }
    return (target->distToFloor < 10.0f) && (target->y < y);
}

u8 actorListHasId1FacingTarget(Actor *actor, Actor *target, ActorCallbackNode *node) {
    return actorListContainsId(node, 1) && actorIsFacingTarget(actor, target, node);
}

u8 actorListHasId2FacingTarget(Actor *actor, Actor *target, ActorCallbackNode *node) {
    return actorListContainsId(node, 2) && actorIsFacingTarget(actor, target, node);
}

s32 func_80676730(Actor *actor, Actor *target, ActorCallbackNode *node) {
    return actorListContainsId(node, 1);
}

s32 func_8067675C(Actor *actor, Actor *target, ActorCallbackNode *node) {
    return actorListContainsId(node, 3);
}

s32 func_80676788(Actor *actor, Actor *target, ActorCallbackNode *node) {
    return actorListContainsId(node, 5);
}

s32 func_806767B4(Actor *actor, Actor *target, ActorCallbackNode *node) {
    return actorListContainsId(node, 4);
}

s32 func_806767E0(Actor *actor, Actor *target, ActorCallbackNode *node) {
    return actorListContainsId(node, 2);
}

s32 actorCheckPlayerProximityVertical(Actor *actor, Actor *player, ActorCallbackNode *node) {
    f32 height;
    f32 topY;
    f32 dist;
    f32 threshold;

    if (player->collisionFlags & 1) {
        PlayerState *ps = player->customState;
        if (ps->stateFlags & 0x01000000) {
            return 1;
        }
    }

    if (!actorIsFacingTarget(actor, player, node)) {
        return 0;
    }

    height = actor->sub4->scaleY * ((AnimInitData *)actor->animState)->height;
    topY = actor->y + height;
    if (player->y < topY) {
        dist = topY - player->y;
    } else {
        dist = -(topY - player->y);
    }
    switch (actor->actorType) {
        case 0x13:
        case 0x1A:
        case 0x55:
        case 0x85:
        case 0x95:
            threshold = 8.0f;
            break;
        case 0x3F:
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
            threshold = 14.0f;
            break;
        case 0x3D:
        case 0x82:
            threshold = 25.0f;
            break;
        default:
            threshold = 0.0f;
            break;
    }

    if (threshold < dist) {
        return 0;
    }

    if (gActorGlobalState.riderCount != 0) {
        return 0;
    }

    if (!(actor->flags2 & 1)) {
        return 0;
    }
    return 1;
}

u8 actorTargetIsGiantKong(Actor *actor, Actor *player, ActorCallbackNode *node) {
    if (player->actorType == 6) {
        u8 index = ((PlayerState *)player->customState)->playerIndex;
        if (gPlayerSlots[index].sizeMode != 1) {
            return 1;
        }
    }
    return 0;
}

u8 actorTargetIsMiniKong(Actor *actor, Actor *player, ActorCallbackNode *node) {
    if (player->actorType == 5) {
        u8 index = ((PlayerState *)player->customState)->playerIndex;
        if (gPlayerSlots[index].sizeMode != 1) {
            return 1;
        }
    }
    return 0;
}

u8 actorGiantKongInReach(Actor *actor, Actor *player, ActorCallbackNode *node) {
    return actorTargetIsGiantKong(actor, player, node) && actorCheckPlayerProximityVertical(actor, player, node);
}

u8 playerIsGiantAgainstEnemy(Actor *actor, Actor *target, ActorCallbackNode *node) {
    u8 index = ((PlayerState *)actor->customState)->playerIndex;
    u8 ret = 0;

    if (target->collisionFlags & 2) {
        ret = gPlayerSlots[index].sizeMode == 2;
        if (ret && gPlayerCount == 1) {
            ret = actor->actorType == 6;
        }
    }
    return ret;
}

u8 playerIsGiantGroundedAgainstEnemy(Actor *actor, Actor *target, ActorCallbackNode *node) {
    return playerIsGiantAgainstEnemy(actor, target, node) && (actor->contactFlags & 1);
}

u8 playerIsGiantLandingOnEnemy(Actor *actor, Actor *target, ActorCallbackNode *node) {
    return playerIsGiantAgainstEnemy(actor, target, node) && (actorIsTargetFallingFromAbove(target, actor, node) || mpIsMatchType(0));
}

u8 actorTargetIsLargeMode(Actor *actor, Actor *target, ActorCallbackNode *node) {
    u8 index = ((PlayerState *)target->customState)->playerIndex;
    return gPlayerSlots[index].sizeMode == 2;
}

u8 actorCheckTargetOnSurfaceOrSmaller(Actor *actor, Actor *target, ActorCallbackNode *node) {
    PlayerState *ps = target->customState;
    s32 onSurface;

    if (ps->surfaceTimer) {
        onSurface = 1;
    } else {
        onSurface = 0;
    }
    return onSurface || actorTargetIsGiantKong(actor, target, node);
}

s32 func_80676C64(Actor *actor, Actor *target, ActorCallbackNode *node) {
    if (actorListContainsId(node, 1)) {
        if (target->state == 0x1C) {
            return 1;
        }
    }
    return 0;
}

s32 actorListContainsId(ActorCallbackNode *node, u8 id) {
    CollisionHitRecord *records = node->payload;
    s32 i;

    for (i = 0; i < node->payloadCount; i++) {
        if (records[i].nodeIndex == id) {
            return 1;
        }
    }
    return 0;
}
