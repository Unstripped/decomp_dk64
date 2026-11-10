#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/1332B0.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/55B20.h"
#include "proto/global/69E60.h"
#include "proto/global/7130.h"
#include "proto/global/79890.h"
#include "proto/global/7CA80.h"
#include "proto/global/80150.h"
#include "proto/global/89250.h"
#include "proto/global/8CA50.h"
#include "proto/global/8F4B0.h"
#include "proto/global/CEAE0.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gPrimaryPlayerActor;
extern ActorGlobalState gActorGlobalState;
extern PlayerStruct *gPlayerSlots;

void actorSetUniformScale(Actor *actor, f32 scale) {
    actor->sub4->scaleX = scale;
    actor->sub4->scaleY = scale;
    actor->sub4->scaleZ = scale;
    if (actor->collision != NULL) {
        actor->eyeHeight = (u32)((f32)actor->collision->scaledRadius * scale * 0.5);
    }
}

void func_80724994(u8 subtype, s16 value0, s16 value1, s16 value2, s16 value3) {
    s16 *payload;
    Actor *target;

    payload = heapAlloc(8);
    heapFreeDeferred(payload);
    payload[0] = value0;
    payload[1] = value1;
    payload[2] = value2;
    payload[3] = value3;
    actorFindActiveByType(0xB, &target);
    actorAppendCallbackMemcpy8(0, target, 0x01000000, subtype, payload, 0);
}

s32 func_80724A20(void) {
    s32 found;
    s16 i;

    found = 0;
    i = 0;
    if (gActorGlobalState.unk254 > 0) {
        do {
            if (gActorGlobalState.unk258[i] == 3) {
                found = 1;
                gCurrentActor->state = gActorGlobalState.unk278[i][1];
                gCurrentActor->unk155 = 0;
            }
            i++;
        } while (found == 0 && i < gActorGlobalState.unk254);
    }
    return found;
}

typedef struct ZoneTable {
    /* 0x0 */ s16 count;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ Zone *zones;
} ZoneTable;

typedef struct SpawnEntry {
    /* 0x00 */ u16 actorType;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ s16 scriptId;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ u32 actorFlags;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 spawnRange;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
} SpawnEntry; // size = 0x18

typedef struct SpawnNodeList {
    /* 0x0 */ s16 count;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ SpawnNode *nodes;
} SpawnNodeList;

extern ZoneTable *D_80755690;
extern SpawnNodeList *D_80755694;
extern SpawnEntry D_8075EB80[];

void zoneEntrySetDisabled(u8 zoneId, u8 entryIndex, u8 disabled) {
    Zone *group;
    s16 i;

    group = D_80755690->zones;
    for (i = 0; i < D_80755690->count;) {
        if (group->id == zoneId) {
            if (entryIndex < group->entryCount) {
                if (disabled != 0) {
                    group->entries[entryIndex].flags |= 0x80;
                } else {
                    group->entries[entryIndex].flags &= ~0x80;
                }
            }
            return;
        }
        i++;
        group++;
    }
}

void zoneEntryGetPosition(u8 zoneId, u8 entryIndex, f32 *outX, f32 *outY, f32 *outZ) {
    Zone *group;
    s16 i;

    group = D_80755690->zones;
    for (i = 0; i < D_80755690->count;) {
        if (group->id == zoneId) {
            if (entryIndex < group->entryCount) {
                *outX = group->entries[entryIndex].x;
                *outY = group->entries[entryIndex].y;
                *outZ = group->entries[entryIndex].z;
            }
            return;
        }
        i++;
        group++;
    }
}


void func_80724C2C(s16 speed) {
    s16 angle;

    angle = (gActorGlobalState.targetActor->moveYaw + 0x800) & 0xFFF;
    gCurrentActor->moveYaw = angle;
    gCurrentActor->yaw = angle;
    gCurrentActor->speedXZ = speed;
}

void func_80724C78(void *mapData) {
    spawnNodeListInitFromMap(mapData, D_80755690, D_80755694);
}

void func_80724CA4(s16 first, s16 count) {
    BoneRotation *table;

    gCurrentActor->sub4->boneRotations = heapAlloc((count + 1) * sizeof(BoneRotation));
    heapClearBlock(gCurrentActor->sub4->boneRotations);
    table = gCurrentActor->sub4->boneRotations;
    table[0].weight = 0x7F;
    table[0].bone = first;
    table[count].weight = 0;
}

void func_80724D28(s16 first, s16 count) {
    BoneVector *table;

    gCurrentActor->sub4->boneOffsets = heapAlloc((count + 1) * sizeof(BoneVector));
    heapClearBlock(gCurrentActor->sub4->boneOffsets);
    table = gCurrentActor->sub4->boneOffsets;
    table[0].bone = first;
    table[0].lastBone = first + 1;
    table[count].bone = 0xFF;
}

void func_80724DB0(s16 first, s16 count) {
    BoneVector *table;

    gCurrentActor->sub4->boneScales = heapAlloc((count + 1) * sizeof(BoneVector));
    heapClearBlock(gCurrentActor->sub4->boneScales);
    table = gCurrentActor->sub4->boneScales;
    table[0].x = 1.0f;
    table[0].y = 1.0f;
    table[0].z = 1.0f;
    table[0].bone = first;
    table[0].lastBone = first;
    table[count].bone = 0xFF;
}

extern u8 gGameMode;

void func_80724E48(u8 mode) {
    f32 angle;
    f32 pitch;
    f32 yaw;
    BoneRotation *rot;
    f32 curYaw;
    f32 limit;
    s32 pitchArg;
    s16 res;

    pitch = 0.0f;
    angle = 0.0f;
    if (mode == 8) {
        pitchArg = 0x46;
        yaw = gPrimaryPlayerActor->yaw * 3.1415927f * (1.0 / 2048.0);
        rot = gPrimaryPlayerActor->sub4->boneRotations;
        limit = 1.0431069f;
    } else {
        yaw = gCurrentActor->yaw * 3.1415927f * (1.0 / 2048.0);
        rot = gCurrentActor->sub4->boneRotations;
        pitchArg = D_8075EB80[gBehaviourAnimState->entryIndex].unkD;
        limit = D_8075EB80[gBehaviourAnimState->entryIndex].unkC * 4 * 3.1415927f * (1.0 / 2048.0);
        if (pitchArg == 0xFF) {
            pitchArg = 0x3E8;
        }
    }
    if (0 != rot) {
        curYaw = (f64)(u32)rot->rotY / 65535.0 * 6.2831854820251465;
        if (gGameMode == 1 && mode != 5 && mode != 7) {
            mode = 6;
        }
        switch (mode) {
            case 8:
                pitch = mathCalculatePitchAngle(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, gPrimaryPlayerActor->x, gPrimaryPlayerActor->y, gPrimaryPlayerActor->z, pitchArg);
                angle = mathAngleBetweenPointsRad(gCurrentActor->x, gCurrentActor->z, gPrimaryPlayerActor->x, gPrimaryPlayerActor->z) - yaw;
                break;
            case 7:
                pitch = mathCalculatePitchAngle(gBehaviourTargetActor->x, gBehaviourTargetActor->y, gBehaviourTargetActor->z, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, pitchArg);
                angle = mathAngleBetweenPointsRad(gBehaviourTargetActor->x, gBehaviourTargetActor->z, gCurrentActor->x, gCurrentActor->z) - yaw;
                break;
            case 6:
                pitch = mathCalculatePitchAngle(gPlayerSlots->camX, gPlayerSlots->camY, gPlayerSlots->camZ, gCurrentActor->x, gCurrentActor->y + (u32)gCurrentActor->eyeHeight, gCurrentActor->z, pitchArg);
                angle = mathAngleBetweenPointsRad(gPlayerSlots->camX, gPlayerSlots->camZ, gCurrentActor->x, gCurrentActor->z) - yaw;
                break;
            case 0:
                pitch = mathCalculatePitchAngle(gPlayerSlots->headX, gPlayerSlots->headY, gPlayerSlots->headZ, gCurrentActor->x, gCurrentActor->y + (u32)gCurrentActor->eyeHeight, gCurrentActor->z, pitchArg);
            case 1:
                angle = mathAngleBetweenPointsRad(gPlayerSlots->headX, gPlayerSlots->headZ, gCurrentActor->x, gCurrentActor->z) - yaw;
                break;
            case 2:
                angle = gBehaviourWorkState->unk24 * 2 * 0.017453292f;
                break;
            case 3:
                pitch = mathCalculatePitchAngle(gBehaviourWorkState->targetX, gBehaviourWorkState->targetY, gBehaviourWorkState->targetZ, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, pitchArg);
                angle = mathAngleBetweenPointsRad(gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, gCurrentActor->x, gCurrentActor->z) - yaw;
                break;
        }
        if (angle < 0.0f) {
            angle += 6.2831855f;
        }
        if (limit != 0.0f) {
            if (limit < angle && angle <= 3.1415927f) {
                angle = limit;
                if (curYaw > 3.1415927f) {
                    angle = limit + 6.2831855f;
                }
            } else if (angle < 6.2831855f - limit && angle > 3.1415927f) {
                angle = 6.2831855f - limit;
                if (curYaw < 3.1415927f) {
                    angle = angle - 6.2831855f;
                }
            }
        }
        if (angle > 3.1415927f) {
            angle -= 6.2831855f;
        }
        if (curYaw > 3.1415927f) {
            curYaw -= 6.2831855f;
        }
        res = mathAngleEaseToward((s32)(curYaw * 2048.0 / 3.1415927410125732), (s32)(angle * 2048.0 / 3.1415927410125732), 5.0f);
        rot->rotX = (u32)(pitch / 6.2831855f * 65535.0);
        rot->rotY = (u32)(res / 4095.0 * 65535.0);
        rot->rotZ = 0;
    }
}

s32 lineSegmentIntersect2D(s16 x1, s16 z1, s16 x2, s16 z2, s16 x3, s16 z3, s16 x4, s16 z4, f32 *outX, f32 *outZ) {
    f32 a1;
    f32 b1;
    f32 c1;
    f32 a2;
    f32 b2;
    f32 c2;
    f32 d1;
    f32 d2;
    f32 d3;
    f32 d4;
    f32 det;
    f32 half;
    f32 y;
    f32 two;
    s16 ix;
    s16 iy;

    a1 = z2 - z1;
    b1 = x1 - x2;
    c1 = x2 * z1 - x1 * z2;
    d3 = x3 * a1 + b1 * z3 + c1;
    d4 = x4 * a1 + b1 * z4 + c1;
    if (d3 != 0.0f && d4 != 0.0f && ((s32)((u32)d3 ^ (u32)d4)) >= 0) {
        return 0;
    }
    a2 = z4 - z3;
    b2 = x3 - x4;
    c2 = x4 * z3 - x3 * z4;
    d1 = x1 * a2 + b2 * z1 + c2;
    d2 = x2 * a2 + b2 * z2 + c2;
    if (d1 != 0.0f && d2 != 0.0f && ((s32)((u32)d1 ^ (u32)d2)) >= 0) {
        return 0;
    }
    det = a1 * b2 - a2 * b1;
    if (det == 0.0f) {
        return 2;
    }
    two = 2.0f;
    if (det < 0.0f) {
        half = -det / two;
    } else {
        half = det / two;
    }
    if (b1 * c2 < b2 * c1) {
        two = (b1 * c2 - b2 * c1) - half;
    } else {
        two = (b1 * c2 - b2 * c1) + half;
    }
    *outX = two / det;
    if (a2 * c1 < a1 * c2) {
        two = (a2 * c1 - a1 * c2) - half;
    } else {
        two = (a2 * c1 - a1 * c2) + half;
    }
    y = two / det;
    *outZ = y;
    ix = (s32)*outX;
    iy = (s32)y;
    if ((ix == x1 && iy == z1) || (ix == x2 && iy == z2) || (ix == x3 && iy == z3) || (ix == x4 && iy == z4)) {
        return 3;
    }
    return 1;
}

u8 rectContainsPoint2D(s16 px, s16 pz, s16 minX, s16 minZ, s16 maxX, s16 maxZ) {
    s32 ret;

    ret = px >= minX;
    if (ret != 0) {
        ret = maxX >= px;
        if (ret != 0) {
            ret = pz >= minZ;
            if (ret != 0) {
                ret = maxZ >= pz;
            }
        }
    }
    return ret;
}


u8 polygonContainsPoint2D(s16 x, s16 z, Zone *zone) {
    s32 res;
    f32 hitX;
    f32 hitZ;
    s16 hits;
    s16 i;
    u8 edgeHits;

    hits = 0;
    if (rectContainsPoint2D(x, z, zone->minX, zone->minZ, zone->maxX, zone->maxZ)) {
        edgeHits = 0;
        i = 1;
        if (zone->vertexCount >= 2) {
            do {
                if (i + 1 != zone->vertexCount) {
                    res = lineSegmentIntersect2D(x, z, -0x8000, -0x8000, zone->vertices[i].x, zone->vertices[i].z, zone->vertices[i + 1].x, zone->vertices[i + 1].z, &hitX, &hitZ);
                } else {
                    res = lineSegmentIntersect2D(x, z, -0x8000, -0x8000, zone->vertices[i].x, zone->vertices[i].z, zone->vertices[1].x, zone->vertices[1].z, &hitX, &hitZ);
                }
                hits += res != 0;
                if (res == 3) {
                    edgeHits++;
                }
                i++;
            } while (i < zone->vertexCount);
        }
        if (edgeHits != 0 && !(edgeHits & 1) && hits == edgeHits) {
            hits--;
        }
    }
    return hits & 1;
}


u8 segmentIntersectsCircle2D(s16 x1, s16 z1, s16 x2, s16 z2, s16 cx, s16 cz, s16 radius) {
    f32 outX;
    f32 outY;
    f32 outZ;

    camClosestPointOnSegment(cx, 0.0f, cz, x1, 0.0f, z1, x2, 0.0f, z2, &outX, &outY, &outZ);
    return ((outX - cx) * (outX - cx) + (outZ - cz) * (outZ - cz) < (f32)(radius * radius));
}


s32 zoneFindBestReachablePoint(u8 mode, Actor *actor, Zone *zone, s16 *outX, s16 *outY, s16 *outZ) {
    s16 i;
    u8 stop;
    u8 found;
    s32 best;
    ZoneEntry *e;
    s32 d;

    stop = 0;
    found = 0;
    if (mode & 1) {
        best = 0;
    } else {
        best = 0xF423F;
    }
    for (i = 0; i < zone->entryCount && !stop; i++) {
        e = &zone->entries[i];
        if (!(e->flags & 0x80) && ((e->flags & 0x7F) == 3)) {
            if (segmentIntersectsCircle2D((s32)actor->x, (s32)actor->z, e->x, e->z, (s32)gBehaviourTargetActor->x, (s32)gBehaviourTargetActor->z, 0x14) == 0) {
                if (zoneCanReachPoint(actor, e->x, e->y, e->z, zone) != 0) {
                    if (((mode & 1) && (d = (s32)(((gBehaviourTargetActor->x - e->x) * (gBehaviourTargetActor->x - e->x)) + ((gBehaviourTargetActor->z - e->z) * (gBehaviourTargetActor->z - e->z))), best < d)) ||
                        ((mode & 2) && (d = (s32)(((actor->x - e->x) * (actor->x - e->x)) + ((actor->z - e->z) * (actor->z - e->z))), d < best))) {
                        best = d;
                        *outX = e->x;
                        *outY = e->y;
                        *outZ = e->z;
                        found = 1;
                        if (mode & 0x80) {
                            if (((randomNonNegative() >> 0xF) % 100) >= 0x33) {
                                stop = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return found;
}


s32 zoneCanReachPoint(Actor *actor, s16 targetX, s16 targetY, s16 targetZ, Zone *zone) {
    s32 res;
    f32 hitX;
    f32 hitZ;
    f32 x;
    f32 y;
    f32 z;
    s16 i;
    s16 cross;
    u8 edges;

    cross = 0;
    edges = 0;
    x = actor->x;
    y = actor->y + (f32)(u32)actor->eyeHeight;
    z = actor->z;
    for (i = 1; i < zone->vertexCount; i++) {
        if ((i + 1) != zone->vertexCount) {
            res = lineSegmentIntersect2D(targetX, targetZ, -0x8000, -0x8000, zone->vertices[i].x, zone->vertices[i].z, zone->vertices[i + 1].x, zone->vertices[i + 1].z, &hitX, &hitZ);
        } else {
            res = lineSegmentIntersect2D(targetX, targetZ, -0x8000, -0x8000, zone->vertices[i].x, zone->vertices[i].z, zone->vertices[1].x, zone->vertices[1].z, &hitX, &hitZ);
        }
        cross += (res != 0);
        if (res == 3) {
            edges++;
        }
    }
    if (edges != 0) {
        if (!(edges & 1) && (cross == edges)) {
            cross--;
        }
    }
    res = 1;
    if (cross & 1) {
        for (i = 0; res && i < zone->entryCount; i++) {
            if (!(zone->entries[i].flags & 0x80)) {
                if (((zone->entries[i].flags & 0x7F) == 0) || ((zone->entries[i].flags & 0x7F) == 5)) {
                    if (segmentIntersectsCircle2D((s32)x, (s32)z, targetX, targetZ, zone->entries[i].x, zone->entries[i].z, zone->entries[i].radius) != 0) {
                        if (((f32)zone->entries[i].y <= y) && (y <= (f32)(zone->entries[i].y + zone->entries[i].height))) {
                            res = 0;
                        }
                    }
                }
            }
        }
    } else {
        res = 0;
    }
    return res;
}


s32 zoneCheckActorInside(Actor *actor, f32 prevX, f32 prevZ, Zone *zone) {
    f32 x;
    f32 y;
    f32 z;
    s16 i;
    s32 found;
    ZoneEntry *e;
    u8 sel;

    actor->arcYawMin = 0;
    actor->arcYawMax = 0xFFF;
    found = 0;
    x = actor->x;
    y = actor->y;
    z = actor->z;
    for (i = 0; i < zone->entryCount; i++) {
        e = &zone->entries[i];
        sel = e->flags & 0x7F;
        if (!(e->flags & 0x80)) {
            if ((sel == 0) || (sel == 1) ||
                ((sel == 5) && ((f64)actor->speedXZ < (f64)(u32)gBehaviourExtraState->unkD * 1.4))) {
                if (((f32)e->y <= y) && (y <= (f32)(e->y + e->height))) {
                    if (e->flags != 0) {} // FAKE: live range steers flags/count10 colouring (a1/t0)
                    if (i == 5) {} // FAKE: steer s3 and s8 constant coloring
                    if (((x - (f32)e->x) * (x - (f32)e->x)) + ((z - (f32)e->z) * (z - (f32)e->z)) < (f32)(e->radius * e->radius)) {
                        func_806755A8((s32)x, (s32)z, e->x, e->z, &actor->arcYawMin, &actor->arcYawMax);
                        found = 1;
                        actor->hasArcBounds = 1;
                        if (zone) {} // FAKE: steers ret temps
                        actor->collisionHit = 1;
                    }
                }
            }
        }
    }
    return found;
}

void actorSetPositionFromPoint(Actor *actor, SpawnNode *pt) {
    actor->x = pt->x;
    actor->y = pt->y;
    actor->prevY = pt->y;
    actor->z = pt->z;
    actor->yaw = pt->yaw;
}

// Spawn-node actors of entry type 6 have a third component; its pointer sits at 0x17C.
typedef struct ActorExt17C {
    /* 0x000 */ Actor base;
    /* 0x178 */ void *unk178;
    /* 0x17C */ s16 *unk17C;
} ActorExt17C;

extern f32 D_807502E8;
extern s16 D_807502E0;
extern s16 D_8075570C[];
extern s32 gGlobalCutsceneFlags;
extern u8 gPlayerCount;
extern u8 D_80755698[];
extern s32 gCurrentMap;

void spawnNodeInitActorFromEntry(Actor *act, SpawnNode *node) {
    BehaviourWorkState *st;
    s32 pad;
    s16 pad2;
    s16 scriptId;
    s32 pad3;
    u8 type;
    u8 idx;
    s16 *entry;
    s32 v;

    st = act->customState;
    idx = node->entryIndex;
    type = D_80755698[idx];
    node->state = 5;
    node->actor = act;
    node->unk30 = 1.0f;
    node->unk2C = 0.01f;
    if (D_8075EB80[idx].unk17 != 0) {
        node->unk38 = 1.0 / D_8075EB80[idx].unk17;
    } else {
        node->unk38 = 0.0f;
    }
    scriptId = D_8075EB80[idx].scriptId;
    if (scriptId != 0) {
        actorScriptStart(act, scriptId);
    }
    gBehaviourAnimState = node;
    behaviourSetAnimIds(scriptId, scriptId, scriptId);
    if (act->sub4 != NULL) {
        actorSetUniformScale(act, ((node->scale * 5) / 255.0) * 0.15);
    }
    actorSetPositionFromPoint(act, node);
    act->floorSlopePitch = 0x400;
    act->accelY = D_807502E8;
    act->terminalSpeedY = D_807502E0;
    act->chunkIndex = node->chunkIndex;
    if (D_8075EB80[idx].spawnRange == 0) {
        act->drawDistance = 0x7D0;
    }
    actorSetTargetSpeed(act, node->targetSpeed);
    st->node = node;
    v = act->yaw;
    act->moveYaw = v;
    st->unk25 = 0;
    st->unk34 = 0xFF;
    st->unk8 = v;
    st->unk10 = act->x;
    st->unk12 = act->y;
    st->unk14 = act->z;
    act->unk144 = 0x24;
    act->flags &= ~0x10000;
    act->flags |= 0x20000;
    act->flags |= D_8075EB80[idx].actorFlags;
    if (act->sub4 != NULL) {
        act->flags2 |= 0xC0;
    }
    act->unk16E[0] = D_8075EB80[idx].unk14;
    act->unk16E[1] = D_8075EB80[idx].unk15;
    v = D_8075EB80[idx].unkF;
    st->unk22 = v;
    st->unk23 = v;
    st->unk1E = D_8075EB80[idx].unk10;
    st->unk1F = D_8075EB80[idx].unk11;
    st->unk21 = D_8075EB80[idx].unk12;
    st->unk35 = D_8075EB80[idx].unk13;
    st->unk37 = D_8075EB80[idx].unk16;
    act->state = node->actorState;
    act->unk155 = 0;
    switch (type) {
        case 0:
        case 2:
        case 3:
            node->flags |= 0x4000;
        case 1:
            node->flags |= 8;
            break;
        case 10:
            node->flags |= 0x80;
            break;
        case 6:
            entry = ((ActorExt17C *)act)->unk17C;
            if (act->actorType == 0xFE) {
                *entry = D_8075570C[node->unkA];
            } else {
                *entry = controllerLookupStateByHash(act);
            }
            break;
    }
    act->tintR = 0xFF;
    act->tintG = 0xFF;
    act->tintB = 0xFF;
    switch (gCurrentMap) {
        case 0x4E:
        case 0x4F:
        case 0x83:
            v = node->unkD + (node->spawnCount * 0xA);
            if (v >= 0x100) {
                node->unkD = 0xFF;
            } else {
                node->unkD = v;
            }
            break;
        case 0x53:
        case 0xC5:
            if (type != 6) {
                break;
            }
        case 0x4C:
            act->cullMarginX = 0x3C;
            act->cullMarginY = 0x3C;
            act->state = 0;
            act->unk155 = 0;
            act->unk144 = 1;
            act->flags |= 0x10000000;
        case 0x6:
        case 0xE:
        case 0x1B:
        case 0x1C:
        case 0x27:
        case 0x37:
        case 0x52:
        case 0x6A:
        case 0x98:
        case 0x99:
        case 0xAC:
        case 0xB9:
        case 0xD0:
            node->flags |= 0x20;
        case 0x3:
        case 0x43:
        case 0x44:
        case 0x4A:
        case 0xD1:
            act->flags |= 0x800000;
            break;
        case 0x45:
            act->flags |= 0x800000;
        case 0x42:
        case 0x68:
        case 0x7C:
        case 0x88:
        case 0x89:
        case 0xA5:
            if (node->actorState != 4) {
                st->unk37 = 7;
            }
            break;
        case 0xD4:
            act->drawDistance = 0x7D0;
        case 0xD3:
            node->flags |= 4;
            break;
        case 0x50:
            act->flags &= ~0x1000000;
            break;
    }
    if (gPlayerCount >= 2) {
        st->unk4 = gPlayerSlots[(randomNonNegative() >> 0xF) % gPlayerCount].actor;
    } else {
        st->unk4 = gPrimaryPlayerActor;
    }
    node->unk34 = 0.75f;
    act->floorY = node->y;
    if (type != 8) {
        actorUpdateFloorContactAndTilt(act, 0.0f);
        if (gGlobalCutsceneFlags & 2) {
            act->attachMode = 0;
        } else if ((type == 4) || (act->actorType == 0xF8)) {
            node->flags |= 0x800;
            act->attachMode = 0;
        } else if (act->attachMode == 1) {
            node->flags |= 0x200;
        }
    }
    if (type == 5) {
        gCurrentActor->contactFlags |= 4;
        gCurrentActor->prevContactFlags |= 4;
    }
}


u8 spawnNodeHasActor(u8 id) {
    return spawnNodeHasState(id, 5) || spawnNodeHasState(id, 6);
}

u8 spawnNodeIsInCooldown(u8 id) {
    return spawnNodeHasState(id, 7);
}

u8 spawnNodeHasState(u8 id, u8 state) {
    s16 i;
    SpawnNode *node;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if (node->id == id) {
            return node->state == state;
        }
    }
    return 0;
}

void spawnNodesSetActorStateByFlag(u16 mask, u8 state) {
    s16 i;
    SpawnNode *node;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if (node->state == 5) {
            if (node->actor->collisionFlags & mask) {
                node->actor->state = state;
            }
        }
    }
}


void func_80726EE0(u8 command) {
    s16 i;
    SpawnNode *node;
    s32 mode;

    mode = command;
    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if (node->flags & 0x80) {
            continue;
        }
        if ((node->state == 5) && (node->actor->collisionFlags & 2)) {
            actorQueueDelayedCallback(node->actor, 0, 8, 0, 0, 0, 1);
            do {
            } while (0); // FAKE: extra block steers func_80726EE0 saved-register colouring (Q0268)
        } else if ((node->state == 6) && (node->actor->collisionFlags & 2)) {
            node->state = 7;
            node->respawnTimer = node->respawnDelay * 0x1E;
            camClearActorRefs(node->actor);
            actorDespawn(node->actor);
        }
        switch (mode) {
            case 0:
            case 1:
                node->flags |= 2;
                break;
            case 2:
                node->flags &= ~2;
                break;
        }
    }
}


void spawnNodeActivateAndSetState(s16 id, u8 state, u16 flags) {
    Actor *a = spawnNodeActivate(id, flags);

    if (a != NULL) {
        a->state = state;
        a->unk155 = 0;
    }
}


Actor *spawnNodeActivate(s16 id, u16 flags) {
    s16 i;
    SpawnNode *node;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if (id == node->id) {
            if (node->state == 5) {
                node->flags |= flags;
                return node->actor;
            } else if ((node->state == 6) && (flags & 0x400)) {
                actorRegisterActive(node->actor);
                node->state = 5;
                return node->actor;
            }
        }
    }
    return NULL;
}

u8 spawnNodeIdForActor(Actor *actor) {
    s16 i;
    SpawnNode *node;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if ((actor == node->actor) && (node->state == 5)) {
            return node->id;
        }
    }
    return 0;
}

Actor *spawnNodeSpawnById(s16 id, s16 x, s16 y, s16 z, s16 yaw, s16 speed, s16 speedY) {
    s16 i;
    SpawnNode *node;
    SpawnEntry *entry;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if ((id == node->id) && (node->state != 5)) {
            entry = &D_8075EB80[node->entryIndex];
            if (actorSpawn(entry->actorType, entry->unk2) != 0) {
                node->flags |= 4;
                spawnNodeInitActorFromEntry(gSpawnedActor, node);
                if (x != 0) {
                    gSpawnedActor->x = x;
                    gSpawnedActor->y = y;
                    gSpawnedActor->z = z;
                    gSpawnedActor->moveYaw = yaw;
                    gSpawnedActor->yaw = yaw;
                }
                gSpawnedActor->speedXZ = speed;
                gSpawnedActor->speedY = speedY;
                gSpawnedActor->contactFlags = 0;
                return gSpawnedActor;
            }
        }
    }
    return NULL;
}


void spawnNodeSpawnAtTablePoint(s16 id, u8 slot) {
    u8 tbl;
    s16 yaw;

    tbl = gBehaviourAnimState->path[slot][0];
    yaw = (s16)(s32)((mathAngleBetweenPointsDeg((s32)gBehaviourTargetActor->x, (s32)gBehaviourTargetActor->z, D_807FDCA0->entries[tbl].x, D_807FDCA0->entries[tbl].z) * 4096.0f) / 360.0f);
    if (spawnNodeSpawnById(id, D_807FDCA0->entries[tbl].x, D_807FDCA0->entries[tbl].y, D_807FDCA0->entries[tbl].z, yaw, ((randomNonNegative() >> 0xF) % 100) + 0x64, ((randomNonNegative() >> 0xF) % 100) + 0xC8) != 0) {
        gSpawnedActor->state = 0x17;
        gSpawnedActor->unk155 = 0;
    }
}


void spawnNodeSpawnFacingPoint(s16 id, s16 x, s16 y, s16 z, s16 targetX, s16 targetY, s16 targetZ, s16 duration, s16 speedY) {
    s16 yaw;
    f32 dist;
    s32 dx;
    s32 dy;
    s32 dz;

    dx = targetX - x;
    dy = targetY - y;
    dz = targetZ - z;
    yaw = mathAngleBetweenPoints2D((f32)targetX, (f32)targetZ, (f32)x, (f32)z);
    dist = sqrtf((f32)((dx * dx) + (dy * dy) + (dz * dz)));
    dy = (s32)(sqrtf((f32)((dx * dx) + (dz * dz))) / (dist / (f32)duration));
    if (spawnNodeSpawnById(id, x, y, z, yaw, dy, speedY) != 0) {
        gSpawnedActor->state = 0x17;
        gSpawnedActor->unk155 = 0;
    }
}

void func_80727678(void) {
    s32 pad;
    s16 i;
    SpawnNode *node;
    s16 j;
    s16 *ptr;
    SpawnEntry *entry;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        for (j = 0; j < gActorGlobalState.unk254; j++) {
            ptr = gActorGlobalState.unk278[j];
            if (node->id == *ptr) {
                switch (gActorGlobalState.unk258[j]) {
                    case 1:
                        if ((node->state == 0) && (spawnFlagConditionMet(gCurrentMap, node->id) != 0) && (actorSpawn(D_8075EB80[node->entryIndex].actorType, D_8075EB80[node->entryIndex].unk2) != 0)) {
                            spawnNodeInitActorFromEntry(gSpawnedActor, node);
                        } else if ((node->state == 3) && (spawnFlagConditionMet(gCurrentMap, node->id) != 0)) {
                            entry = &D_8075EB80[node->entryIndex];
                            if (actorSpawn(entry->actorType, entry->unk2) != 0) {
                                spawnNodeInitActorFromEntry(gSpawnedActor, node);
                                gSpawnedActor->state = 0x36;
                            }
                        }
                        break;
                    case 2:
                        if (node->state == 7) {
                            node->state = node->initialState;
                        }
                        break;
                    case 3:
                    case 4:
                        if (node->state == 5) {
                            actorAppendCallbackMemcpy8(gCurrentActor, node->actor, 0x01000000, gActorGlobalState.unk258[j], ptr, 0);
                        }
                        break;
                }
            }
        }
    }
}

extern PlayerState *gActivePlayerState;

void spawnNodeSelectEntry(SpawnNode *node) {
    if ((gCurrentMap == 0x30) && (gActivePlayerState->stateFlags & 0x100000) && (D_80755698[node->baseEntryIndex] != 0xA)) {
        switch (node->baseEntryIndex) {
            case 28:
                node->entryIndex = 0x63;
                return;
            case 9:
                node->entryIndex = 0x54;
                return;
            case 44:
                node->entryIndex = 0x67;
                return;
        }
    } else {
        node->entryIndex = node->baseEntryIndex;
    }
}


extern s16 gCurrentLevelIndex;
extern s32 gGlobalOverlayFlags;

void spawnNodesUpdate(void) {
    s16 i;
    SpawnNode *node;
    s32 dist;
    u8 active;
    s32 best;
    s16 p;
    SpawnEntry *entry;
    f32 dz;
    f32 dx;
    s32 d;
    PlayerState *sub;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        active = (node->state >= 5) && (node->state < 7);
        if (active) {
            gBehaviourWorkState = node->actor->customState;
        }
        dist = D_8075EB80[node->entryIndex].spawnRange * 0x64;
        dist = dist * dist;
        if (active) {
            node->chunkIndex = node->actor->chunkIndex;
        }
        if ((dist == 0) || (node->flags & 4) || (gGlobalOverlayFlags & 0x100)) {
            dist = 0x7FFFFFFF;
        }
        if (active && (node->actor->state == 0x3B)) {
            camClearActorRefs(node->actor);
            actorDespawn(node->actor);
            node->state = 0;
        } else if (active && (node->actor->state == 0x3C)) {
            camClearActorRefs(node->actor);
            actorDespawn(node->actor);
            node->state = node->initialState;
            node->flags &= ~4;
        } else if ((node->state == 7) && (node->respawnTimer != 0)) {
            if (!(node->flags & 2)) {
                node->respawnTimer -= 1;
                if (node->respawnTimer == 0) {
                    node->spawnCount += 1;
                    node->state = node->initialState;
                    node->chunkIndex = mapChunkFindByPosition((f32)node->x, (f32)node->y, (f32)node->z, 0);
                    spawnNodeSelectEntry(node);
                    entry = &D_8075EB80[node->entryIndex];
                    if (actorSpawn(entry->actorType, entry->unk2) != 0) {
                        spawnNodeInitActorFromEntry(gSpawnedActor, node);
                        gSpawnedActor->state = 0x36;
                        node->flags |= 1;
                    }
                }
            }
        } else if (node->state == 2) {
            if ((spawnNodeInRangeAndVisible(node, dist) != 0) && (spawnFlagConditionMet(gCurrentLevelIndex, node->id) != 0)) {
                spawnNodeSelectEntry(node);
                entry = &D_8075EB80[node->entryIndex];
                if (actorSpawn(entry->actorType, entry->unk2) != 0) {
                    spawnNodeInitActorFromEntry(gSpawnedActor, node);
                }
            }
        } else if (active && (node->actor->state == 0x40)) {
            node->state = 7;
            node->respawnTimer = node->respawnDelay * 0x1E;
            if (node->zone->occupant == node->actor) {
                node->zone->occupant = 0;
            }
            camClearActorRefs(node->actor);
            actorDespawn(node->actor);
        } else if (active) {
            best = 0xF423F;
            if ((gBehaviourWorkState->unk4->collisionFlags & 1) && (gBehaviourWorkState->unk4->state == 0x67)) {
                if ((node->actor->collisionFlags & 2) && (node->state == 5)) {
                    if ((node->actor->state != 0x16) && (node->actor->state != 0x37) && !(node->flags & 0x40)) {
                        node->actor->state = 0x16;
                        node->actor->unk155 = 0;
                    }
                }
            }
            if (gPlayerCount >= 2) {
                for (p = 0; p < gPlayerCount; p++) {
                    sub = gPlayerSlots[0].actor->customState;
                    dz = gCurrentActor->z - gPlayerSlots[p].actor->z;
                    dx = gCurrentActor->x - gPlayerSlots[p].actor->x;
                    d = (s32)((dz * dz) + (dx * dx));
                    if ((d < best) || (sub->surfaceTimer != 0)) {
                        best = d;
                        gBehaviourWorkState->unk4 = gPlayerSlots[p].actor;
                    }
                }
            }
            if (node->state == 6) {
                if (spawnNodeActorOutOfRangeScaled(node, dist) != 0) {
                    actorDespawn(node->actor);
                    node->state = node->initialState;
                } else if (spawnNodeActorInRangeAndVisible(node, dist) != 0) {
                    actorRegisterActive(node->actor);
                    node->state = 5;
                    node->flags |= 0x8000;
                }
            } else if ((node->state == 5) && (spawnNodeActorOutOfRangeOrHidden(node, dist) != 0)) {
                if ((node->actor->state != 0x16) && (node->actor->state != 0x37)) {
                    if (node->actor->actorType == 0xF8) {
                        sfxStopChannel(0x42, 0);
                    }
                    sfxStopSlotSound(node->actor, 0);
                    sfxStopSlotSound(node->actor, 1);
                    actorDeregisterActive(node->actor);
                    node->state = 6;
                    gBehaviourWorkState->stepCount = 0;
                }
            }
        }
    }
}


u8 spawnNodeInRangeAndVisible(SpawnNode *node, s32 rangeSq) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 ret;

    dz = gPlayerSlots[0].camZ - node->z;
    dx = gPlayerSlots[0].camX - node->x;
    dy = gPlayerSlots[0].camY - node->y;
    ret = 0;
    if (((dz * dz) + ((dx * dx) + (dy * dy))) < rangeSq) {
        ret = 1;
    }
    if (ret) {
        ret = D_80755698[node->entryIndex] == 6;
        if (!ret) {
            ret = (node->flags & 0x20) != 0;
            if (!ret) {
                ret = mapChunkIsVisibleForPlayer(0, node->chunkIndex) != 0;
            }
        }
    }
    return ret;
}

u8 spawnNodeActorInRangeAndVisible(SpawnNode *node, s32 rangeSq) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 ret;

    dz = gPlayerSlots[0].camZ - node->actor->z;
    dx = gPlayerSlots[0].camX - node->actor->x;
    dy = gPlayerSlots[0].camY - node->actor->y;
    ret = 0;
    if (((dz * dz) + ((dx * dx) + (dy * dy))) < rangeSq) {
        ret = 1;
    }
    if (ret) {
        ret = (node->actor->collisionFlags & 0x40) != 0;
        if (!ret) {
            ret = (node->flags & 0x20) != 0;
            if (!ret) {
                ret = mapChunkIsVisibleForPlayer(0, node->chunkIndex) != 0;
            }
        }
    }
    return ret;
}

u8 spawnNodeActorOutOfRangeOrHidden(SpawnNode *node, s32 rangeSq) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 ret;

    dz = gPlayerSlots[0].camZ - node->actor->z;
    dx = gPlayerSlots[0].camX - node->actor->x;
    dy = gPlayerSlots[0].camY - node->actor->y;
    ret = rangeSq < (dz * dz) + ((dx * dx) + (dy * dy));
    dx = 0.0f; // FAKE: dead store kills the store-forwarding of the compare into the ret test (ret stays v1, bnezl)
    if (ret == 0) {
        ret = (node->actor->collisionFlags & 0x40) == 0;
        if (ret != 0) {
            ret = (node->flags & 0x20) == 0;
            if (ret != 0) {
                ret = mapChunkIsVisibleForPlayer(0, node->chunkIndex) == 0;
            }
        }
    }
    return ret;
}

u8 spawnNodeActorOutOfRangeScaled(SpawnNode *node, s32 rangeSq) {
    f32 dz;
    f32 dx;
    f32 r;
    s32 t;
    s32 ret;

    r = sqrtf(rangeSq);
    ret = (node->actor->collisionFlags & 2) != 0;
    if (ret) {
        ret = (node->flags & 0x20) == 0;
        if (ret) {
            ret = node->initialState == 2;
            if (ret) {
                t = (s32)(r * 1.5);
                dz = gPlayerSlots[0].camZ - node->actor->z;
                dx = gPlayerSlots[0].camX - node->actor->x;
                r = gPlayerSlots[0].camY - node->actor->y;
                ret = (f32)(t * t) < ((dz * dz) + ((dx * dx) + (r * r)));
            }
        }
    }
    return ret;
}

void zoneAssignToBehaviour(SpawnNode *node) {
    s16 i;
    Zone *entry;

    entry = D_80755690->zones;
    i = 0;
    if (D_80755690->count > 0) {
        do {
            entry->occupant = NULL;
            entry->unk20 = 0;
            if (entry->id == node->zoneId) {
                node->zone = entry;
                break;
            }
            i++;
            entry++;
        } while (i < D_80755690->count);
    }
    if (node->zone == NULL) {
        node->zone = D_80755690->zones;
    }
}



// Map-file records copied verbatim: a node's first 0x16 bytes and one 2-byte path step.
typedef struct SpawnNodeRecord {
    s16 v[11];
} SpawnNodeRecord;

typedef struct SpawnPathStep {
    u8 v[2];
} SpawnPathStep;

void spawnNodeListInitFromMap(s16 *data, ZoneTable *zones, SpawnNodeList *nodes) {
    s32 t;
    s16 *src;
    s16 cnt;
    s16 *p;
    s16 *q;
    s16 j;
    void *mem;
    s32 same;
    SpawnNode *node;
    s16 i;
    s16 prev;
    Zone *rec;
    s16 *r;

    src = data;
    if (src != NULL) {
        t = *src++;
        cnt = t;
        zones->count = t;
    } else {
        zones->count = 0;
        cnt = zones->count;
    }
    rec = heapAlloc(cnt * sizeof(Zone));
    zones->zones = rec;
    for (i = 0; i < zones->count; i++) {
        same = 1;
        j = 0;
        if (i != 0) {
            rec++;
        }
        rec->minX = 0x7FFF;
        rec->minZ = rec->minX;
        rec->maxX = -0x8000;
        rec->maxZ = rec->maxX;
        if (src != NULL) {
            t = *src++;
            cnt = t;
            rec->vertexCount = t;
        } else {
            rec->vertexCount = 0;
            cnt = rec->vertexCount;
        }
        p = src;
        if (cnt != 0) {
            rec->vertices = heapAlloc(cnt * sizeof(ZoneVertex));
        }
        if (cnt > 0) {
            do {
                rec->vertices[j] = *(ZoneVertex *)p;
                p += 3;
                rec->minX = (rec->minX < rec->vertices[j].x) ? rec->minX : rec->vertices[j].x;
                rec->minZ = (rec->minZ < rec->vertices[j].z) ? rec->minZ : rec->vertices[j].z;
                rec->maxX = (rec->vertices[j].x < rec->maxX) ? rec->maxX : rec->vertices[j].x;
                rec->maxZ = (rec->vertices[j].z < rec->maxZ) ? rec->maxZ : rec->vertices[j].z;
                if (j == 0) {
                    prev = rec->vertices[j].y;
                } else {
                    if (prev != rec->vertices[j].y) {
                        same = 0;
                    }
                    prev = rec->vertices[j].y;
                }
                j++;
            } while (j < cnt);
            j = 0;
        }
        src = p;
        if (src != NULL) {
            t = *src++;
            cnt = t;
            rec->entryCount = t;
        } else {
            rec->entryCount = 0;
            cnt = rec->entryCount;
        }
        q = src;
        if (cnt != 0) {
            rec->entries = heapAlloc(cnt * sizeof(ZoneEntry));
        }
        if (cnt > 0) {
            do {
                rec->entries[j] = *(ZoneEntry *)q;
                j++;
                q += 5;
            } while (j < cnt);
        }
        src = q;
        if (src != NULL) {
            rec->id = *src++;
            rec->unk19 = *src++;
            if (same != 0) {
                rec->unk19 = 1;
            }
        }
    }
    i = 0;
    if (src != NULL) {
        t = *src++;
        nodes->count = t;
        cnt = t;
    } else {
        nodes->count = 0;
        cnt = 0;
    }
    mem = heapAlloc(cnt * sizeof(SpawnNode));
    nodes->nodes = mem;
    heapClearBlock(mem);
    r = src;
    node = nodes->nodes;
    for (; i < nodes->count; i++) {
        j = 0;
        if (i != 0) {
            node++;
        }
        *(SpawnNodeRecord *)node = *(SpawnNodeRecord *)r;
        r += 11;
        node->state = node->initialState;
        node->entryIndex = node->baseEntryIndex;
        node->actor = NULL;
        node->flags = 0;
        node->respawnTimer = 0;
        node->spawnCount = 0;
        node->unk3C = 0.0f;
        node->chunkIndex = mapChunkFindByPosition((f32)node->x, (f32)node->y, (f32)node->z, 0);
        node->path = heapAlloc(node->pathCount * 2);
        q = r;
        if (node->pathCount > 0) {
            do {
                ((SpawnPathStep *)node->path)[j] = *(SpawnPathStep *)q;
                j++;
                q += 1;
            } while (j < node->pathCount);
        }
        r = q;
        zoneAssignToBehaviour(node);
    }
}

extern u32 gFrameCounter;


u8 func_8072881C(u8 anim, u32 *lastFrame) {
    u8 ret;

    ret = 0;
    if ((anim & 0x80) || (((*lastFrame + 0x32) < gFrameCounter) && (((randomNonNegative() >> 0xF) % 1000) >= 0x3C1) && (animIsPlaying(gCurrentActor, anim) == 0))) {
        anim &= 0x7F;
        animSetSpeed(gCurrentActor, anim, 1.0f);
        animSetLoopMode(gCurrentActor, anim, 1);
        animSetDirection(gCurrentActor, anim, 0);
        animSetEndFrame(gCurrentActor, anim, 3);
        animClearStartFrame(gCurrentActor, anim);
        animSetFrameAndSubframe(gCurrentActor, anim, 0, 0.0f);
        animSetLoopLimit(gCurrentActor, anim, 2);
        *lastFrame = gFrameCounter;
        ret = 1;
    }
    return ret;
}


void func_80728950(u8 anim) {
    animSetLoopLimit(gCurrentActor, anim, 1);
    animSetFinished(gCurrentActor, anim, 1);
    animSetFrameAndSubframe(gCurrentActor, anim, 2, 0.0f);
}

void currentActorAnimSetFrame(u8 frame, u8 subframe) {
    animSetFrameAndSubframe(gCurrentActor, frame, subframe, 0.0f);
}

typedef struct A2PtrPair {
    void *p[2];
} A2PtrPair;

typedef struct A2BytePair {
    u8 b[2];
} A2BytePair;

extern A2PtrPair D_80755794;
extern A2BytePair D_8075579C;
extern u8 D_8071FB34[];
extern u8 D_8071FB54[];
extern u8 D_8071FC0C[];
extern u8 D_8071FC40[];
extern u8 D_8071FC58[];
extern u8 sEffectSparkConfig[];
extern void *D_8074E880[];
extern Actor *gCamActor;


void zoneEntrySpawnEffect(s16 effect, s16 entryIndex, s16 param, s16 count) {
    Zone *group;
    s16 x;
    s16 y;
    s16 z;
    s16 i;
    f32 ox0;
    f32 oy0;
    f32 oz0;
    A2PtrPair fx6;
    A2BytePair idx6;
    u8 sel6;
    s16 ex6;
    s16 ez6;
    s16 ang6;
    f32 scale8;
    f32 kx8;
    f32 kz8;
    s32 rnd10;
    f32 ox10;
    f32 oy10;
    s8 jx;
    s8 jy;
    s8 jz;
    f32 kx14;
    f32 ky14;
    f32 kz14;

    group = D_80755690->zones;
    x = group->entries[entryIndex].x;
    y = group->entries[entryIndex].y;
    z = group->entries[entryIndex].z;
    switch (effect) {
        case 0:
            for (i = 0; i < count; i++) {
                ox0 = (f32)((randomNonNegative() >> 0xF) % 0x8000 % 40 - 20.0);
                oy0 = (f32)((randomNonNegative() >> 0xF) % 0x8000 % 20);
                oz0 = (f32)((randomNonNegative() >> 0xF) % 0x8000 % 40 - 20.0);
                effectSetColor(0xE6, 0xE6, 0xE6, 0xC8);
                effectSetCallback(func_80717D4C);
                effectSetSpeed(-(i * 20));
                effectSetDepth(1);
                effectSetMode(param);
                effectCreateAtPosition(sEffectSparkConfig, 1.5f, (f32)x + ox0, (f32)y + oy0, (f32)z + oz0);
            }
            return;
        case 7:
            break;
        case 1:
            effectSpawnMultiTierRing(0.36f, 1, (f32)x, (f32)(y + 5), (f32)z);
            camStartShake(gCamActor, 0x14, 0xF);
            return;
        case 2:
            enemyAggroEnable();
            return;
        case 3:
            actorSpawnEffectChild((f32)x, (f32)y, (f32)z, param * 0.01, count * 0.01, NULL, 0);
            return;
        case 4:
            tagBarrelSpawnSmokeAndPuffs((f32)x, (f32)y, (f32)z, param * 0.01, 0, 0);
            return;
        case 5:
            if (param != 0x14) {
                actorSpawn(0x104, 0);
                gSpawnedActor->splineT = count;
            }
            switch (param) {
                case 0:
                    gSpawnedActor->x = 450.0f;
                    gSpawnedActor->y = 500.0f;
                    gSpawnedActor->unk15F = 0x14;
                    break;
                case 1:
                    gSpawnedActor->x = 820.0f;
                    gSpawnedActor->y = 500.0f;
                    gSpawnedActor->unk15F = 0x15;
                    break;
                case 10:
                    sfxPlayOnFreeSlot(0x3F3, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    gSpawnedActor->unk15F = 0;
                    gSpawnedActor->x = 500.0f;
                    gSpawnedActor->y = 80.0f;
                    break;
                case 11:
                    sfxPlayOnFreeSlot(0x3F4, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    gSpawnedActor->unk15F = 0x89;
                    gSpawnedActor->x = 600.0f;
                    gSpawnedActor->y = 80.0f;
                    break;
                case 12:
                    sfxPlayOnFreeSlot(0x3F4, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    gSpawnedActor->unk15F = 0x47;
                    gSpawnedActor->x = 600.0f;
                    gSpawnedActor->y = 80.0f;
                    break;
                case 13:
                    gSpawnedActor->unk15F = 0x23;
                    gSpawnedActor->x = 600.0f;
                    gSpawnedActor->y = 80.0f;
                    break;
                case 20:
                    actorSpawn(0x92, 0x73);
                    actorScriptStart(gSpawnedActor, 0x42A);
                    return;
                case 30:
                case 31:
                case 32:
                case 33:
                case 34:
                case 35:
                    gSpawnedActor->unk15F = param;
                    gSpawnedActor->x = 500.0f;
                    gSpawnedActor->y = 80.0f;
                    break;
            }
            break;
        case 15:
            actorSpawn(0x92, 0x73);
            actorScriptStart(gSpawnedActor, 0x42A);
            return;
        case 6:
            for (i = 0; i < count; i++) {
                fx6 = D_80755794;
                idx6 = D_8075579C;
                sel6 = (randomNonNegative() >> 0xF) % 2;
                ex6 = group->entries[param].x;
                ez6 = group->entries[param].z;
                ang6 = mathAngleBetweenPoints2D((f32)ex6, (f32)ez6, (f32)x, (f32)z);
                effectSetDepth(1);
                effectSetDuration(idx6.b[sel6]);
                effectSetCallback(effectConfettiPhysicsUpdate);
                effectSetSpeed((ang6 << 16) + 3);
                effectCreateAtPosition(fx6.p[sel6], (f32)((randomNonNegative() >> 0xF) % 1000 * 0.0005 + 0.2), (f32)x, (f32)(y + 10), (f32)z);
            }
            return;
        case 12:
            effectSetMaxDistance(0x7D0);
            effectSetMode(1);
            effectCreateAtPosition(D_8071FC0C, param * 0.01, (f32)x, (f32)y, (f32)z);
            return;
        case 8:
            scale8 = param * 0.01;
            for (i = 0; i < count; i++) {
                kx8 = ((randomNonNegative() >> 0xF) % 0x8000 % 40 - 20.0) * scale8;
                kz8 = ((randomNonNegative() >> 0xF) % 0x8000 % 40 - 20.0) * scale8;
                effectSetMaxDistance(0x7D0);
                effectSetDepth(1);
                effectCreateAtPosition(D_8071FB54, scale8 * 1.3, (f32)x + kx8, (f32)y, (f32)z + kz8);
                effectSetColor(0xD2, 0xD2, 0xD2, 0xC8);
                effectSpawnBoneDefault(NULL, 0, scale8 * 1.2, (f32)x + kx8, (f32)y, (f32)z + kz8, -0xB4);
            }
            return;
        case 9:
            for (i = 0; i < param; i++) {
                effectSetMode(2);
                effectSetCallback(effectPuffRiseUpdate);
                effectSetDepth(1);
                effectSetSpeed(1);
                effectSetAngle(i * 3);
                effectCreateAtPosition(D_8074E880[(randomNonNegative() >> 0xF) % 1000 % 3], count * 0.01, (f32)x, (f32)y, (f32)z);
            }
            return;
        case 10:
            for (i = 0; i < param; i++) {
                rnd10 = randomNonNegative() >> 0xF;
                ox10 = (f32)(rnd10 % 300);
                oy10 = (f32)((randomNonNegative() >> 0xF) % 200);
                effectEnableFade();
                effectCreateAtPosition(D_8071FB34, count * 0.01, ox10, oy10, -10.0f);
            }
            return;
        case 11:
            for (i = 0; i < param; i++) {
                jx = (randomLcgNext() / 10000 % 200) / 10.0 - 10.0;
                jy = (randomLcgNext() / 10000 % 200) / 10.0 - 7.0;
                jz = (randomLcgNext() / 10000 % 200) / 10.0 - 10.0;
                effectSetDepth(1);
                effectSetDuration(2);
                effectSetSpeed(0x64);
                effectSetCallback(func_80717D4C);
                effectSetAngle(i / 7);
                effectCreateAtPosition(D_8071FC58, count * 0.01, (f32)(x + jx), (f32)(y + jy), (f32)(z + jz));
            }
            return;
        case 13:
            effectSpawnDebrisParticles(NULL, param * 0.01, (f32)x, (f32)y, (f32)z);
            return;
        case 14:
            for (i = 0; i < param; i++) {
                kx14 = (f32)(randomLcgNext() / 10000 % 200) / 10.0 - 5.0;
                ky14 = (f32)(randomLcgNext() / 10000 % 200) / 10.0 - 5.0;
                kz14 = (f32)(randomLcgNext() / 10000 % 200) / 10.0 - 5.0;
                effectSetDepth(1);
                effectSetSpeed(2);
                effectSetDuration(-1);
                effectSetCallback(effectWobbleRiseUpdate);
                effectSetFlags(4);
                effectCreateAtPosition(D_8071FC40, 0.0f, (f32)x + kx14, (f32)y + ky14, (f32)z + kz14);
            }
            break;
    }
}



void func_80729AA4(u8 id) {
    Actor *a;

    a = spawnNodeActivate(id, 0);
    if (a == NULL) {
        a = gPrimaryPlayerActor;
    }
    a->contactFlags |= 0x100;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/D_8075EB80.s")
