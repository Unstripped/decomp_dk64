#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/117190.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7AF60.h"
#include "proto/global/CEAE0.h"

// Model header reached through Actor.animState.
typedef struct ActorModelHeader {
    u8 pad0[0x1C];
    s16 unk1C;
} ActorModelHeader;

extern u8 D_807F6902;
extern u8 gPlayerCount;
extern PlayerStruct *gPlayerSlots;
extern u8 D_807FBBA9;

void actorCheckPlayerSmallerThanAttacker(Actor *actor, Actor *attacker, ActorCollisionList *list) {
    playerIsSmallerThanAttacker(actor, attacker);
}

u8 actorTargetIsVulnerable(Actor *actor, Actor *target, ActorCollisionList *list) {
    return playerCanCollideWithActor(target) && D_807F6902 == 0;
}

u8 func_806762C0(Actor *actor, Actor *target, ActorCollisionList *list) {
    return func_806767E0(actor, target, list) && actorTargetIsVulnerable(actor, target, list);
}

s32 actorIsDamageFatal(Actor *target, Actor *attacker, u8 damageScale) {
    s16 remaining = target->health - attacker->damage;

    if (remaining <= 0) {
        return 1;
    }
    return 0;
}

u8 actorsFacingEachOther(Actor *actor, Actor *target, ActorCollisionList *list) {
    u8 ret;

    ret = mathAngleDistance(mathAngleBetweenPoints2D((s16)actor->x, (s16)actor->z, (s16)target->x, (s16)target->z), actor->yaw) < 0x200;
    if (ret) {
        ret = actorIsFacingTarget(actor, target, list);
    }
    return ret;
}

u8 actorIsFacingTarget(Actor *actor, Actor *target, ActorCollisionList *list) {
    return mathAngleDistance(mathAngleBetweenPoints2D((s16)actor->x, (s16)actor->z, (s16)target->x, (s16)target->z), target->yaw) < 0x3A9;
}

u8 actorIsTargetAbovePitchThreshold(Actor *actor, Actor *target, ActorCollisionList *list) {
    return (f64)mathCalculatePitchAngle(actor->x, actor->y, actor->z, target->x, target->y, target->z, 0) > 0.7;
}

u8 actorIsTargetFallingFromAbove(Actor *actor, Actor *target, ActorCollisionList *list) {
    return actorIsTargetAbovePitchThreshold(actor, target, list) && target->speedY < -100.0f;
}

u8 actorIsBelowTargetStationary(Actor *actor, Actor *target, u8 unused) {
    return actor->distToFloor < 10.0f && actor->y < target->y;
}

u8 actorIsTargetBelowNode(Actor *actor, Actor *target, ActorCollisionList *list) {
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

u8 func_80676690(Actor *actor, Actor *target, ActorCollisionList *list) {
    return actorListContainsId(list, 1) && actorIsFacingTarget(actor, target, list);
}

u8 func_806766E0(Actor *actor, Actor *target, ActorCollisionList *list) {
    return actorListContainsId(list, 2) && actorIsFacingTarget(actor, target, list);
}

s32 func_80676730(Actor *actor, Actor *target, ActorCollisionList *list) {
    return actorListContainsId(list, 1);
}

s32 func_8067675C(Actor *actor, Actor *target, ActorCollisionList *list) {
    return actorListContainsId(list, 3);
}

s32 func_80676788(Actor *actor, Actor *target, ActorCollisionList *list) {
    return actorListContainsId(list, 5);
}

s32 func_806767B4(Actor *actor, Actor *target, ActorCollisionList *list) {
    return actorListContainsId(list, 4);
}

s32 func_806767E0(Actor *actor, Actor *target, ActorCollisionList *list) {
    return actorListContainsId(list, 2);
}

s32 actorCheckPlayerProximityVertical(Actor *actor, Actor *player, ActorCollisionList *list) {
    f32 height;
    f32 topY;
    f32 dist;
    f32 threshold;
    u32 type;

    if (player->collisionFlags & 1) {
        PlayerState *ps = player->customState;
        if (ps->stateFlags & 0x01000000) {
            return 1;
        }
    }

    if (!actorIsFacingTarget(actor, player, list)) {
        return 0;
    }

    height = actor->sub4->scaleY * (f32)((ActorModelHeader *)actor->animState)->unk1C;
    topY = actor->y + height;
    if (player->y < topY) {
        dist = topY - player->y;
    } else {
        dist = -(topY - player->y);
    }
    type = actor->actorType;
    switch (type) {
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

    if (D_807FBBA9 != 0) {
        return 0;
    }

    if (!(actor->flags2 & 1)) {
        return 0;
    }
    return 1;
}

u8 func_806769A8(Actor *actor, Actor *player, ActorCollisionList *list) {
    if (player->actorType == 6) {
        u8 index = ((PlayerState *)player->customState)->playerIndex;
        if (gPlayerSlots[index].unk2C0 != 1) {
            return 1;
        }
    }
    return 0;
}

u8 func_80676A0C(Actor *actor, Actor *player, ActorCollisionList *list) {
    if (player->actorType == 5) {
        u8 index = ((PlayerState *)player->customState)->playerIndex;
        if (gPlayerSlots[index].unk2C0 != 1) {
            return 1;
        }
    }
    return 0;
}

u8 func_80676A70(Actor *actor, Actor *player, ActorCollisionList *list) {
    return func_806769A8(actor, player, list) && actorCheckPlayerProximityVertical(actor, player, list);
}

u8 func_80676AB8(Actor *actor, Actor *target, ActorCollisionList *list) {
    u8 index = ((PlayerState *)actor->customState)->playerIndex;
    u8 ret = 0;

    if (target->collisionFlags & 2) {
        ret = gPlayerSlots[index].unk2C0 == 2;
        if (ret && gPlayerCount == 1) {
            ret = actor->actorType == 6;
        }
    }
    return ret;
}

u8 func_80676B38(Actor *actor, Actor *target, ActorCollisionList *list) {
    return func_80676AB8(actor, target, list) && (actor->contactFlags & 1);
}

u8 func_80676B70(Actor *actor, Actor *target, ActorCollisionList *list) {
    return func_80676AB8(actor, target, list) && (actorIsTargetFallingFromAbove(target, actor, list) || func_80714608(0));
}

u8 func_80676BCC(Actor *actor, Actor *target, ActorCollisionList *list) {
    u8 index = ((PlayerState *)target->customState)->playerIndex;
    return gPlayerSlots[index].unk2C0 == 2;
}

u8 func_80676C10(Actor *actor, Actor *target, ActorCollisionList *list) {
    PlayerState *ps = target->customState;

    return (ps->surfaceTimer ? 1 : 0) || func_806769A8(actor, target, list); // FAKE: redundant ?1:0 normalisation steers codegen
}

s32 func_80676C64(Actor *actor, Actor *target, ActorCollisionList *list) {
    if (actorListContainsId(list, 1)) {
        if (target->state == 0x1C) {
            return 1;
        }
    }
    return 0;
}

s32 actorListContainsId(list, id)
ActorCollisionList *list;
u8 id;
{
    ActorCollisionEntry *entries = list->entries;
    s32 i = 0;

    while (i < list->count) {
        if (entries[i].id == id) {
            return 1;
        }
        i++;
    }
    return 0;
}
