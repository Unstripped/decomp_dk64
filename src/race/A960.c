#include "common.h"
#include "race.h"
#include "compiler/ido/memory.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/CEAE0.h"
#include "proto/race/1770.h"
#include "proto/race/52B0.h"
#include "proto/race/7BD0.h"
#include "proto/race/A960.h"

// Race actor: Actor plus its participant component (0x174).
typedef struct RaceActor {
    /* 0x000 */ u8 pad0[0x174];
    /* 0x174 */ RaceParticipant *state;
} RaceActor;

typedef struct RaceWaypoint {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ u16 angle;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 kind;
    /* 0x11 */ u8 pad11[3];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 mode;
    /* 0x19 */ u8 pad19;
    /* 0x1A */ u16 width;
    /* 0x1C */ Actor *actors[2];
    /* 0x24 */ s32 state;
} RaceWaypoint;

typedef struct RaceRoute {
    /* 0x00 */ u16 count;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ u16 *items;
    /* 0x08 */ u16 active;
    /* 0x0A */ u8 padA[2];
} RaceRoute;

typedef struct RaceRouteTable {
    /* 0x00 */ u8 count;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ RaceRoute *items;
    /* 0x08 */ u16 count2;
    /* 0x0A */ u8 pad2[2];
    /* 0x0C */ RaceWaypoint *items2;
} RaceRouteTable;

typedef struct RacePlayerPos {
    u8 pad0[0x210];
    f32 pos[3];
    u8 pad21C[0xC];
    f32 f228;
    f32 f22C;
    f32 f230;
    u8 pad234[0x2F0 - 0x234];
} RacePlayerPos;

extern RaceRouteTable *D_8002FCF0;
extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern RacePlayerPos *gPlayerSlots;
extern u8 gPlayerCount;

RaceRoute *raceGetRoute(u8 idx) {
    RaceRoute *e = &D_8002FCF0->items[idx];

    if (D_8002FCF0 == NULL || idx >= D_8002FCF0->count) {
        return NULL;
    }
    e = &D_8002FCF0->items[idx];
    return e;
}

RaceWaypoint *raceGetWaypoint(u8 idx) {
    RaceWaypoint *e = &D_8002FCF0->items2[idx];

    if (D_8002FCF0 == NULL || idx >= D_8002FCF0->count2) {
        return NULL;
    }
    e = &D_8002FCF0->items2[idx];
    return e;
}


void raceLoadRouteData(u8 *data) {
    u8 *src;
    RaceRoute *ent;
    RaceWaypoint *node;
    s32 i;
    s32 j;
    s32 m;
    s32 sz;

    if (data != NULL) {
        src = data;
        memcpy(D_8002FCF0, src, 1);
        src += 1;
        memcpy(&D_8002FCF0->count2, src, 2);
        src += 2;
        D_8002FCF0->items = heapAlloc(D_8002FCF0->count * sizeof(RaceRoute));
        heapClearBlock(D_8002FCF0->items);
        ent = D_8002FCF0->items;
        for (i = 0; i < D_8002FCF0->count; i++) {
            memcpy(ent, src, 2);
            src += 2;
            ent->items = heapAlloc(ent->count * 2);
            sz = ent->count * 2;
            memcpy(ent->items, src, sz);
            src += sz;
            ent++;
        }
        D_8002FCF0->items2 = heapAlloc(D_8002FCF0->count2 * sizeof(RaceWaypoint));
        heapClearBlock(D_8002FCF0->items2);
        node = D_8002FCF0->items2;
        for (m = 0; m < D_8002FCF0->count2; m++) {
            memcpy(node, src, 0x1C);
            src += 0x1C;
            raceInitGateActors(node);
            node++;
        }
        ent = D_8002FCF0->items;
        for (i = 0; i < D_8002FCF0->count; i++) {
            ent->active = 0;
            for (j = 0; j < ent->count; j++) {
                if (raceGetWaypoint(ent->items[j])->kind != 0) {
                    ent->active++;
                }
            }
            ent++;
        }
    }
}

extern s16 D_80750AC4;

void raceInitRoute(s32 routeAssetId) {
    u8 *assetData;

    assetData = assetLoad(0x18, routeAssetId, 1, 1);
    D_8002FCF0 = heapAlloc(0x10);
    heapClearBlock(D_8002FCF0);
    raceLoadRouteData(assetData);
    switch (routeAssetId) {
        case 0x1B:
            raceInitSplineAndOpponent();
            break;
        case 0x27:
            raceInitCompetitorsAndManager();
            break;
        case 0xE:
        case 0x52:
            raceInitBeetleRaceManager();
            break;
        case 0xB9:
            raceInitGenericRaceManager();
            break;
    }
    D_80750AC4 = 0;
}

void raceScaleVelocity(Actor *actor, f32 scaleFactor) {
    actor->sub4->scaleX *= scaleFactor;
    actor->sub4->scaleY = actor->sub4->scaleX;
    actor->sub4->scaleZ = actor->sub4->scaleY;
}


void raceSpawnGateActor(f32 scaleFactor, s32 kind, u8 mode) {
    RaceParticipant *actorState;

    switch (kind) {
        case 1:
            if (mode != 0) {
                actorSpawn(0x137, 0xB0);
                actorScriptStart(gSpawnedActor, 0x2A9);
            } else {
                actorSpawn(0x137, 0xB1);
                actorScriptStart(gSpawnedActor, 0x2AA);
            }
            break;
        case 2:
            actorSpawn(0x137, mode != 0 ? 0xD8 : 0xD9);
            break;
    }
    actorState = ((RaceActor *)gSpawnedActor)->state;
    raceScaleVelocity(gSpawnedActor, scaleFactor);
    actorState->unk0 = kind;
}

void raceInitGateActors(RaceWaypoint *node) {
    f32 mA[4][4];
    f32 mB[4][4];
    f32 pad[5];
    u32 j;
    f32 xoff;
    u8 i;

    if (node->kind != 0) {
        if (node->mode == 2) {
            xoff = (f32)node->width * 0.5f;
            for (i = 0; i < 2; i++) {
                raceSpawnGateActor(node->unk14, node->kind, i ^ 1);
                j = i;
                node->actors[j] = gSpawnedActor;
                gSpawnedActor->yaw = (node->angle + 0x800) & 0xFFF;
                if (j != 0) {
                    xoff *= -1.0f;
                }
                guRotateF(mA, gSpawnedActor->yaw * 0.087890625f, 0.0f, 1.0f, 0.0f);
                guTranslateF(mB, node->x, node->y, node->z);
                guMtxCatF(mA, mB, mA);
                guMtxXFMF(mA, xoff, 0.0f, 0.0f, &gSpawnedActor->x, &gSpawnedActor->y, &gSpawnedActor->z);
            }
        } else {
            raceSpawnGateActor(node->unk14, node->kind, node->mode == 1);
            node->actors[0] = gSpawnedActor;
            gSpawnedActor->yaw = (node->angle + 0x800) & 0xFFF;
            gSpawnedActor->x = node->x;
            gSpawnedActor->y = node->y;
            gSpawnedActor->z = node->z;
        }
    }
}

f32 raceLineIntersectParam(f32 x1, f32 y1, f32 dx1, f32 dy1, f32 x2, f32 y2, f32 dx2, f32 dy2) {
    f32 r = 0.0f;
    f32 a = dy2 * dx1;
    f32 b = dx2 * dy1;

    if (a != b) {
        r = (((x2 - x1) * dy1) + (dx1 * (y1 - y2))) / (a - b);
    }
    return r;
}

u8 raceCheckGateCrossed(RaceWaypoint *node) {
    f32 gateDx;
    f32 gateDz;
    f32 dx;
    f32 dz;
    f32 gateX;
    f32 gateZ;
    f32 res;
    u8 crossed;
    Actor *a;
    Actor *b;

    crossed = 0;
    if (node->kind == 0) {
        return 1;
    }
    switch (node->mode) {
        case 2:
            a = node->actors[1];
            b = node->actors[0];
            gateDx = a->x - b->x;
            gateDz = a->z - b->z;
            gateX = b->x;
            gateZ = b->z;
            break;
        case 0:
            gateDx = -node->unkC;
            gateDz = node->unk8;
            gateX = node->x;
            gateZ = node->z;
            break;
        case 1:
            gateDx = node->unkC;
            gateDz = -node->unk8;
            gateX = node->x;
            gateZ = node->z;
            break;
    }
    dx = gCurrentActor->prevX - gCurrentActor->x;
    dz = gCurrentActor->prevZ - gCurrentActor->z;
    res = raceLineIntersectParam(gCurrentActor->x, gCurrentActor->z, dx, dz, gateX, gateZ, gateDx, gateDz);
    switch (node->mode) {
        case 2:
            if (res > 0.0f && res < 1.0f) {
                crossed = 1;
            }
            break;
        case 0:
        case 1:
            if (res > 0.0f) {
                crossed = 1;
            }
            break;
    }
    return crossed;
}


u8 raceIsFacingWaypoint(RaceWaypoint *node) {
    f32 diff_x = gCurrentActor->x - (f32)node->x;
    f32 diff_z = gCurrentActor->z - (f32)node->z;
    s16 angle = (s32)(mathAtan2(diff_x, diff_z) * 651.8986206f) & 0xFFF;

    return mathAngleDistance(angle, node->angle) < 0x400;
}

f32 raceGetNormalDistanceToWaypoint(RaceWaypoint *node, f32 x, f32 z) {
    f32 normZ = node->unkC;
    f32 normX = node->unk8;

    return raceLineIntersectParam((f32)node->x, (f32)node->z, -normZ, normX, x, z, normX, normZ);
}


void raceActivateNextGate(RaceParticipant *tracker, RaceRoute *route) {
    RaceWaypoint *node;

    if (route->active != 0) {
        do {
            u16 val;
            tracker->unk3C += 1;
            tracker->unk3C %= route->count;
            val = route->items[tracker->unk3C];
            node = raceGetWaypoint(val);
        } while (node->kind == 0);
        raceSetGateVisualState(node, 1);
    }
}

void raceAdvanceActiveGate(RaceParticipant *tracker, RaceRoute *route) {
    if (route->active != 0) {
        if (tracker->unk3C == tracker->unk3A) {
            u16 val = route->items[tracker->unk3C];
            raceSetGateVisualState(raceGetWaypoint(val), 0);
            raceActivateNextGate(tracker, route);
        }
    }
}


void raceUpdateLapAndWaypointTracker(RaceParticipant *tracker) {
    Actor *actor;
    RaceParticipant *state;
    RaceRoute *list;
    RaceWaypoint *node;
    s32 pad;
    f32 headingAngle;
    u16 val;

    actor = tracker->actor;
    state = ((RaceActor *)actor)->state;
    list = raceGetRoute(state->route);
    if (list != NULL) {
        val = list->items[tracker->unk3A];
        node = raceGetWaypoint(val);
        if (node != NULL) {
            if (((f32)node->x - gCurrentActor->x) * ((f32)node->x - gCurrentActor->x) + ((f32)node->z - gCurrentActor->z) * ((f32)node->z - gCurrentActor->z) > 900.0f) {
                headingAngle = mathAngleBetweenPointsDeg(node->x, node->z, (s32)gCurrentActor->x, (s32)gCurrentActor->z);
                gCurrentActor->unkEC = (s32)(headingAngle - mathAngleBetweenPointsDeg(
                    (s32)gPlayerSlots[tracker->playerIdx].f228,
                    (s32)gPlayerSlots[tracker->playerIdx].f230,
                    (s32)gPlayerSlots[tracker->playerIdx].pos[tracker->playerIdx],
                    (s32)gPlayerSlots->pos[2]));
            }
            if (tracker->unk38 != 0) {
                tracker->unk38 = raceIsFacingWaypoint(node);
            } else if (raceIsFacingWaypoint(node) != 0) {
                if (tracker->unk27 == 0) {
                    if (node->kind != 0) {
                        if (raceCheckGateCrossed(node) == 0) {
                            sfxPlayAtPositionPooled(node->x, node->y, node->z, 0x98, 0xFF, 0x7F, 0, 0, 0.3f, 0);
                            if (tracker->unk44 != 0) {
                                tracker->unk44--;
                            } else {
                                tracker->unk45 = 1;
                            }
                        } else {
                            sfxAllocateChannel(0x43, 1.0f);
                        }
                    }
                    raceAdvanceActiveGate(tracker, list);
                }
                tracker->unk3A += 1;
                tracker->unk3A %= list->count;
                if (tracker->unk3A == 0) {
                    tracker->lap++;
                }
                val = list->items[tracker->unk3A];
                node = raceGetWaypoint(val);
                tracker->unk38 = raceIsFacingWaypoint(node);
            }
            tracker->unk40 = raceGetNormalDistanceToWaypoint(node, gCurrentActor->x, gCurrentActor->z);
        }
    }
}

f32 raceGetPathDistanceBetweenTrackers(RaceRoute *route, RaceParticipant *trackerA, RaceParticipant *trackerB) {
    s32 diff;
    f32 acc;
    f32 prevX;
    f32 prevZ;
    s32 first;
    s32 cur;
    s32 end;
    RaceWaypoint *node;
    s32 idx;
    u16 val;

    cur = trackerA->lap * route->count + trackerA->unk3A;
    end = trackerB->lap * route->count + trackerB->unk3A;
    diff = end - cur;
    acc = trackerA->unk40 - trackerB->unk40;
    if (diff < 0) {
        cur ^= end;
        end ^= cur;
        cur ^= end;
        acc = -acc;
    }
    first = 1;
    if (cur != end) {
        if (cur <= end) {
            do {
                idx = cur % route->count;
                val = route->items[idx];
                node = raceGetWaypoint(val);
                if (!first) {
                    acc += raceGetNormalDistanceToWaypoint(node, prevX, prevZ);
                }
                first = 0;
                cur++;
                prevX = node->x;
                prevZ = node->z;
            } while (cur <= end);
        }
    }
    acc *= diff >= 0 ? 1 : -1;
    return acc;
}

f32 raceGetProgressPercent(RaceRoute *route, RaceParticipant *tracker, RaceParticipant *actorState) {
    u16 waypointCount = route->count;
    f32 num = (tracker->lap - 1) * waypointCount + tracker->unk3A;
    f32 den = actorState->unk24 * waypointCount;

    return num / den;
}


void raceUpdateWaypointActivation(RaceParticipant *actorState) {
    RaceRoute *list;
    RaceWaypoint *node;
    s32 i;
    s32 j;
    s32 k;
    s32 near;
    f32 dist;

    list = raceGetRoute(actorState->route);
    if (list != NULL) {
        for (i = 0; i < list->count; i++) {
            node = raceGetWaypoint(list->items[i]);
            if (node->kind != 0) {
                near = 0;
                for (j = 0; j < gPlayerCount; j++) {
                    f32 *p = gPlayerSlots[j].pos;
                    f32 dz = p[2] - node->z;
                    f32 dx = p[0] - node->x;
                    f32 dy = p[1] - node->y;

                    dist = dz * dz + (dx * dx + dy * dy);
                    dz = 302500.0f;
                    near |= dist > dz;
                }
                if (near != node->state) {
                    for (k = 0; k < 2; k++) {
                        if (node->actors[k] != NULL) {
                            if (near != 0) {
                                actorDeregisterActive(node->actors[k]);
                            } else {
                                actorRegisterActive(node->actors[k]);
                            }
                        }
                    }
                    node->state = near;
                }
            }
        }
    }
}
