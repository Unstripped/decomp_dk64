#include "common.h"
#include "actor.h"
#define PROTO_SKIP_mathAngleDistance // FAKE: callee prototype steer
#include "proto/global/117190.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7AF60.h"
#include "proto/global/CEAE0.h"

typedef struct PlayerData {
    u8 pad[0x2C0];
    u8 unk2C0;
    u8 pad2[0x2F0 - 0x2C1];
} PlayerData;

extern u8 D_807F6902;
extern u8 gPlayerCount;
extern PlayerData *gPlayerSlots;

s32 mathAngleDistance(s16, s16); // FAKE: callee prototype steer
void actorCheckPlayerSmallerThanAttacker(s32 actor, s32 attacker, s32 unused) {
    playerIsSmallerThanAttacker(actor, attacker);
}

u8 actorTargetIsVulnerable(s32 actor, s32 target, s32 list) {
    s32 ret;

    ret = playerCanCollideWithActor(target) != 0;
    if (ret) {
        ret = D_807F6902 == 0;
    }
    return ret;
}

u8 func_806762C0(s32 actor, s32 target, s32 list) {
    s32 ret;

    ret = func_806767E0(actor, target, list) != 0;
    if (ret) {
        ret = actorTargetIsVulnerable(actor, target, list) != 0;
    }
    return ret;
}

s32 actorIsDamageFatal(void* target, void* attacker, u8 damageScale) {
    s16 diff = *(s16*)((u8*)target + 0x134) - *(s16*)((u8*)attacker + 0x136);

    if (diff <= 0) {
        return 1;
    }
    return 0;
}

u8 actorsFacingEachOther(s32 actor, s32 target, s32 list) {
    u8 ret;

    ret = mathAngleDistance(mathAngleBetweenPoints2D((s16)((Actor*)actor)->x, (s16)((Actor*)actor)->z, (s16)((Actor*)target)->x, (s16)((Actor*)target)->z), *(s16*)((u8*)actor + 0xE6)) < 0x200;
    if (ret) {
        ret = actorIsFacingTarget(actor, target, list);
    }
    return ret;
}

u8 actorIsFacingTarget(s32 arg0, s32 arg1, s32 arg2) {
    Actor* actor = (Actor*)arg0;
    Actor* target = (Actor*)arg1;
    return mathAngleDistance(mathAngleBetweenPoints2D((s16)actor->x, (s16)actor->z, (s16)target->x, (s16)target->z), *(s16*)((u8*)target + 0xE6)) < 0x3A9;
}

u8 actorIsTargetAbovePitchThreshold(Actor* actor, Actor* target, s32 arg2) {
    return (f64)mathCalculatePitchAngle(actor->x, actor->y, actor->z, target->x, target->y, target->z, 0) > 0.7;
}

u8 actorIsTargetFallingFromAbove(void* actor, void* target, s32 list) {
    s32 ret;

    ret = actorIsTargetAbovePitchThreshold(actor, target, list) != 0;
    if (ret) {
        ret = *(f32*)((u8*)target + 0xC0) < -100.0f;
    }
    return ret;
}


u8 actorIsBelowTargetStationary(Actor* actor, Actor* target, u8 arg2) {
    s32 ret;

    ret = *(f32*)((u8*)actor + 0xB4) < 10.0f;
    if (ret) {
        ret = actor->y < target->y;
    }
    return ret;
}

u8 actorIsTargetBelowNode(Actor* actor, Actor* target, s32 arg2) {
    f32 x;
    f32 y;
    f32 z;
    s32 pad;

    if (*(u8*)((u8*)actor + 0xCC)) {
        actorGetNodePos(actor, *(u8*)((u8*)actor + 0xCC), &x, &y, &z);
    } else {
        x = actor->x;
        y = actor->y;
        z = actor->z;
    }
    return (*(f32*)((u8*)target + 0xB4) < 10.0f) && (target->y < y);
}

u8 func_80676690(s32 actor, s32 target, s32 list) {
    s32 ret;

    ret = actorListContainsId(list, 1) != 0;
    if (ret) {
        ret = actorIsFacingTarget(actor, target, list) != 0;
    }
    return ret;
}

u8 func_806766E0(s32 actor, s32 target, s32 list) {
    s32 ret;

    ret = actorListContainsId(list, 2) != 0;
    if (ret) {
        ret = actorIsFacingTarget(actor, target, list) != 0;
    }
    return ret;
}


s32 func_80676730(s32 arg0, s32 arg1, s32 list) {
    return actorListContainsId(list, 1);
}

s32 func_8067675C(s32 arg0, s32 arg1, s32 list) {
    return actorListContainsId(list, 3);
}

s32 func_80676788(s32 arg0, s32 arg1, s32 list) {
    return actorListContainsId(list, 5);
}

s32 func_806767B4(s32 arg0, s32 arg1, s32 list) {
    return actorListContainsId(list, 4);
}

s32 func_806767E0(s32 arg0, s32 arg1, s32 list) {
    return actorListContainsId(list, 2);
}

typedef struct ActorProximitySub0 {
    u8 pad[0x1C];
    s16 unk1C;
} ActorProximitySub0;

typedef struct ActorProximityActor {
    ActorProximitySub0* unk0;
    ActorSub4* unk4;
    u8 pad[0x80 - 8];
    f32 unk80;
} ActorProximityActor;

extern u8 D_807FBBA9;

s32 actorCheckPlayerProximityVertical(actor, player, list)
Actor* actor;
Actor* player;
s32 list;
{
    f32 x;
    f32 y;
    f32 diff;
    f32 threshold;
    u32 type;

    if (player->collisionFlags & 1) {
        u8* beh = player->customState;
        if (*(s32*)(beh + 0x1F0) & 0x01000000) {
            return 1;
        }
    }

    if (!actorIsFacingTarget((s32)actor, (s32)player, list)) {
        return 0;
    }

    x = ((ActorProximityActor*)actor)->unk4->scaleY * (f32)((ActorProximityActor*)actor)->unk0->unk1C;
    y = ((ActorProximityActor*)actor)->unk80 + x;
    if (player->y < y) {
        diff = y - player->y;
    } else {
        diff = -(y - player->y);
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

    if (threshold < diff) {
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

u8 func_806769A8(s32 arg0, Actor* player, s32 arg2) {
    if (player->actorType == 6) {
        u8 kong = ((u8*)player->customState)[0x1A4];
        if (gPlayerSlots[kong].unk2C0 != 1) {
            return 1;
        }
    }
    return 0;
}

u8 func_80676A0C(s32 arg0, Actor* player, s32 arg2) {
    if (player->actorType == 5) {
        u8 kong = ((u8*)player->customState)[0x1A4];
        if (gPlayerSlots[kong].unk2C0 != 1) {
            return 1;
        }
    }
    return 0;
}

u8 func_80676A70(s32 actor, Actor* player, s32 list) {
    s32 ret;

    ret = func_806769A8(actor, player, list) != 0;
    if (ret) {
        ret = actorCheckPlayerProximityVertical(actor, player, list) != 0;
    }
    return ret;
}

u8 func_80676AB8(Actor* actor, Actor* target, s32 arg2) {
    u8 kong = ((u8*)actor->customState)[0x1A4];
    u8 ret = 0;

    if (target->collisionFlags & 2) {
        ret = gPlayerSlots[kong].unk2C0 == 2;
        if (ret && gPlayerCount == 1) {
            ret = actor->actorType == 6;
        }
    }
    return ret;
}

u8 func_80676B38(Actor* actor, Actor* target, s32 arg2) {
    s32 ret;

    ret = func_80676AB8(actor, target, arg2) != 0;
    if (ret) {
        ret = (*(u16*)((u8*)actor + 0x6A) & 1) != 0;
    }
    return ret;
}

u8 func_80676B70(Actor* actor, Actor* target, s32 list) {
    s32 ret;

    ret = func_80676AB8(actor, target, list) != 0;
    if (ret) {
        ret = actorIsTargetFallingFromAbove(target, actor, list) != 0;
        if (!ret) {
            ret = func_80714608(0) != 0;
        }
    }
    return ret;
}
u8 func_80676BCC(s32 arg0, Actor* target, s32 arg2) {
    u8 kong = ((u8*)target->customState)[0x1A4];
    return gPlayerSlots[kong].unk2C0 == 2;
}

u8 func_80676C10(s32 actor, Actor* target, s32 list) {
    u8* beh = target->customState;
    s32 ret;
    s32 hasCustomOffset = *(s16*)(beh + 0xD4) != 0 ? 1 : 0;

    ret = hasCustomOffset != 0;
    if (!ret) {
        ret = func_806769A8(actor, target, list) != 0;
    }
    return ret;
}

s32 func_80676C64(s32 arg0, Actor* target, s32 list) {
    if (actorListContainsId(list, 1)) {
        if (*(u8*)((u8*)target + 0x154) == 0x1C) {
            return 1;
        }
    }
    return 0;
}

typedef struct Beh7AF3_Node {
    char pad[0x14];
    s32 id;
    char pad2[4];
} Beh7AF3_Node;

typedef struct Beh7AF3_List {
    char pad[0xC];
    s32 count;
    Beh7AF3_Node* items;
} Beh7AF3_List;

s32 actorListContainsId(list, id)
Beh7AF3_List* list;
u8 id;
{
    Beh7AF3_Node* items = list->items;
    s32 i = 0;

    while (i < list->count) {
        if (items[i].id == id) {
            return 1;
        }
        i++;
    }
    return 0;
}
