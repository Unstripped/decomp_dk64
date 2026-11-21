#include "common.h"
#include "race.h"
#include "sched.h"
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

typedef struct RaceRouteTable {
    /* 0x00 */ u8 routeCount;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ RaceRoute *routes;
    /* 0x08 */ u16 waypointCount;
    /* 0x0A */ u8 pad2[2];
    /* 0x0C */ RaceWaypoint *waypoints;
} RaceRouteTable;

RaceRouteTable *sRaceRouteTable = NULL;
extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;

RaceRoute *raceGetRoute(u8 idx) {
    RaceRoute *e = NULL;

    if (sRaceRouteTable == NULL || idx >= sRaceRouteTable->routeCount) {
        return NULL;
    }
    e = &sRaceRouteTable->routes[idx];
    return e;
}

RaceWaypoint *raceGetWaypoint(u8 idx) {
    RaceWaypoint *e = NULL;

    if (sRaceRouteTable == NULL || idx >= sRaceRouteTable->waypointCount) {
        return NULL;
    }
    e = &sRaceRouteTable->waypoints[idx];
    return e;
}


void raceLoadRouteData(u8 *data) {
    u8 *src;
    RaceRoute *route;
    RaceWaypoint *waypoint;
    s32 i;
    s32 j;
    s32 m;
    s32 size;

    if (data != NULL) {
        src = data;
        memcpy(&sRaceRouteTable->routeCount, src, 1);
        src += 1;
        memcpy(&sRaceRouteTable->waypointCount, src, 2);
        src += 2;
        sRaceRouteTable->routes = heapAlloc(sRaceRouteTable->routeCount * sizeof(RaceRoute));
        heapClearBlock(sRaceRouteTable->routes);
        route = sRaceRouteTable->routes;
        for (i = 0; i < sRaceRouteTable->routeCount; i++) {
            memcpy(&route->count, src, 2);
            src += 2;
            route->items = heapAlloc(route->count * sizeof(u16));
            size = route->count * sizeof(u16);
            memcpy(route->items, src, size);
            src += size;
            route++;
        }
        sRaceRouteTable->waypoints = heapAlloc(sRaceRouteTable->waypointCount * sizeof(RaceWaypoint));
        heapClearBlock(sRaceRouteTable->waypoints);
        waypoint = sRaceRouteTable->waypoints;
        for (m = 0; m < sRaceRouteTable->waypointCount; m++) {
            memcpy(waypoint, src, 0x1C);
            src += 0x1C;
            raceInitGateActors(waypoint);
            waypoint++;
        }
        route = sRaceRouteTable->routes;
        for (i = 0; i < sRaceRouteTable->routeCount; i++) {
            route->active = 0;
            for (j = 0; j < route->count; j++) {
                if (raceGetWaypoint(route->items[j])->kind != 0) {
                    route->active++;
                }
            }
            route++;
        }
    }
}

extern u16 gMinigameCoinCount;

void raceInitRoute(s32 routeAssetId) {
    u8 *assetData;

    assetData = assetLoad(0x18, routeAssetId, 1, 1);
    sRaceRouteTable = heapAlloc(sizeof(RaceRouteTable));
    heapClearBlock(sRaceRouteTable);
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
    gMinigameCoinCount = 0;
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
    actorState = gSpawnedActor->customState;
    raceScaleVelocity(gSpawnedActor, scaleFactor);
    actorState->gateKind = kind;
}

void raceInitGateActors(RaceWaypoint *node) {
    f32 mA[4][4];
    f32 mB[4][4];
    f32 pad[5];
    f32 xoff;
    u8 i;

    if (node->kind != 0) {
        if (node->mode == 2) {
            xoff = (f32)node->width * 0.5f;
            for (i = 0; i < 2; i++) {
                raceSpawnGateActor(node->gateScale, node->kind, i ^ 1);
                node->actors[i] = gSpawnedActor;
                gSpawnedActor->yaw = (node->angle + 0x800) & 0xFFF;
                if (i) {
                    xoff *= -1.0f;
                }
                guRotateF(mA, gSpawnedActor->yaw * 0.087890625f, 0.0f, 1.0f, 0.0f);
                guTranslateF(mB, node->x, node->y, node->z);
                guMtxCatF(mA, mB, mA);
                guMtxXFMF(mA, xoff, 0.0f, 0.0f, &gSpawnedActor->x, &gSpawnedActor->y, &gSpawnedActor->z);
            }
        } else {
            raceSpawnGateActor(node->gateScale, node->kind, node->mode == 1);
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
            gateDx = -node->normalZ;
            gateDz = node->normalX;
            gateX = node->x;
            gateZ = node->z;
            break;
        case 1:
            gateDx = node->normalZ;
            gateDz = -node->normalX;
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
    f32 normZ = node->normalZ;
    f32 normX = node->normalX;

    return raceLineIntersectParam((f32)node->x, (f32)node->z, -normZ, normX, x, z, normX, normZ);
}


void raceActivateNextGate(RaceParticipant *tracker, RaceRoute *route) {
    RaceWaypoint *node;

    if (route->active != 0) {
        do {
            u16 val;
            tracker->activeGatePos += 1;
            tracker->activeGatePos %= route->count;
            val = route->items[tracker->activeGatePos];
            node = raceGetWaypoint(val);
        } while (node->kind == 0);
        raceSetGateVisualState(node, 1);
    }
}

void raceAdvanceActiveGate(RaceParticipant *tracker, RaceRoute *route) {
    if (route->active != 0) {
        if (tracker->activeGatePos == tracker->routePos) {
            u16 val = route->items[tracker->activeGatePos];
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
    state = actor->customState;
    list = raceGetRoute(state->route);
    if (list != NULL) {
        val = list->items[tracker->routePos];
        node = raceGetWaypoint(val);
        if (node != NULL) {
            if (((f32)node->x - gCurrentActor->x) * ((f32)node->x - gCurrentActor->x) + ((f32)node->z - gCurrentActor->z) * ((f32)node->z - gCurrentActor->z) > 900.0f) {
                headingAngle = mathAngleBetweenPointsDeg(node->x, node->z, (s32)gCurrentActor->x, (s32)gCurrentActor->z);
                gCurrentActor->arrowAngle = (s32)(headingAngle - mathAngleBetweenPointsDeg(
                    (s32)gPlayerSlots[tracker->playerIdx].focusX,
                    (s32)gPlayerSlots[tracker->playerIdx].focusZ,
                    (s32)(&gPlayerSlots[tracker->playerIdx].camX)[tracker->playerIdx], // ORIG: the target reads camX + playerIdx * 4 of the slot (sll t8,t0,2; addu t9,v0,t8; lwc1 528(t9) at 0xc34)
                    (s32)gPlayerSlots->camZ));
            }
            if (tracker->facingWaypoint != 0) {
                tracker->facingWaypoint = raceIsFacingWaypoint(node);
            } else if (raceIsFacingWaypoint(node) != 0) {
                if (tracker->isCpu == 0) {
                    if (node->kind != 0) {
                        if (raceCheckGateCrossed(node) == 0) {
                            sfxPlayAtPositionPooled(node->x, node->y, node->z, 0x98, 0xFF, 0x7F, 0, 0, 0.3f, 0);
                            if (tracker->gateMissesLeft != 0) {
                                tracker->gateMissesLeft--;
                            } else {
                                tracker->eliminated = 1;
                            }
                        } else {
                            sfxAllocateChannel(0x43, 1.0f);
                        }
                    }
                    raceAdvanceActiveGate(tracker, list);
                }
                tracker->routePos += 1;
                tracker->routePos %= list->count;
                if (tracker->routePos == 0) {
                    tracker->lap++;
                }
                val = list->items[tracker->routePos];
                node = raceGetWaypoint(val);
                tracker->facingWaypoint = raceIsFacingWaypoint(node);
            }
            tracker->nextPointDist = raceGetNormalDistanceToWaypoint(node, gCurrentActor->x, gCurrentActor->z);
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

    cur = trackerA->lap * route->count + trackerA->routePos;
    end = trackerB->lap * route->count + trackerB->routePos;
    diff = end - cur;
    acc = trackerA->nextPointDist - trackerB->nextPointDist;
    if (diff < 0) {
        cur ^= end;
        end ^= cur;
        cur ^= end;
        acc = -acc;
    }
    first = 1;
    if (cur != end) {
        for (; cur <= end; cur++) {
            idx = cur % route->count;
            val = route->items[idx];
            node = raceGetWaypoint(val);
            if (!first) {
                acc += raceGetNormalDistanceToWaypoint(node, prevX, prevZ);
            }
            first = 0;
            prevX = node->x;
            prevZ = node->z;
        }
    }
    acc *= diff >= 0 ? 1 : -1;
    return acc;
}

f32 raceGetProgressPercent(RaceRoute *route, RaceParticipant *tracker, RaceParticipant *actorState) {
    u16 waypointCount = route->count;
    f32 num = (tracker->lap - 1) * waypointCount + tracker->routePos;
    f32 den = actorState->lapCount * waypointCount;

    return num / den;
}


void raceUpdateWaypointActivation(RaceParticipant *actorState) {
    RaceRoute *route;
    RaceWaypoint *node;
    s32 i;
    s32 j;
    s32 k;
    s32 farAway;
    f32 dist;

    route = raceGetRoute(actorState->route);
    if (route != NULL) {
        for (i = 0; i < route->count; i++) {
            node = raceGetWaypoint(route->items[i]);
            if (node->kind != 0) {
                farAway = 0;
                for (j = 0; j < gPlayerCount; j++) {
                    f32 *camPos = &gPlayerSlots[j].camX;

                    dist = (camPos[0] - node->x) * (camPos[0] - node->x) +
                           (camPos[1] - node->y) * (camPos[1] - node->y) +
                           (camPos[2] - node->z) * (camPos[2] - node->z);
                    farAway |= dist > 302500.0f;
                }
                if (farAway != node->state) {
                    for (k = 0; k < 2; k++) {
                        if (node->actors[k] != NULL) {
                            if (farAway != 0) {
                                actorDeregisterActive(node->actors[k]);
                            } else {
                                actorRegisterActive(node->actors[k]);
                            }
                        }
                    }
                    node->state = farAway;
                }
            }
        }
    }
}
