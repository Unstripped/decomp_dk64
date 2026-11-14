#include "common.h"
#include "race.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/131B0.h"
#include "proto/global/135D30.h"
#include "proto/global/126260.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/166A0.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/7130.h"
#include "proto/global/70FD0.h"
#include "proto/global/80150.h"
#include "proto/global/936B0.h"
#include "proto/global/ACDC0.h"
#include "proto/global/EFDC0.h"
#include "proto/global/FCCD0.h"
#include "proto/race/1770.h"
#include "proto/race/36B0.h"
#include "proto/race/7BD0.h"


// Race car actors (raceOpponentCarBehaviorUpdate, raceObstacleCarBehaviorUpdate): Actor plus their
// component pointers from 0x178 on.
typedef struct RaceCarActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ RaceParticipant *participant;
    /* 0x17C */ RacePathState *path;
    /* 0x180 */ u8 *bumpCooldown; // raceHandleCollisionRumble: no new bump while nonzero
    /* 0x184 */ RaceTarget *raceTarget;
} RaceCarActor;

// The racers the cars and the race camera follow: the participant is the customState (0x174),
// the path cursor the second component.
typedef struct RacePathActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ RacePathState *path;
} RacePathActor;

extern Actor *gCurrentActor;


s32 raceGetWaypointDiff(s32 pathLength, RacePathState *curA, RacePathState *curB) {
    s32 diff;
    s32 abs_diff;
    s32 sign;

    diff = curB->unk2 - curA->unk2;
    abs_diff = (diff > 0) ? diff : -diff;
    if ((pathLength / 2) < abs_diff) {
        sign = (diff >= 0) ? 1 : -1;
        diff -= sign * pathLength;
    }
    return diff;
}

#define RB_SQ(v) ((v) * (v))
f32 raceGetWaypointSegmentFraction(s32 pathLength, Actor *actor, RacePathState *cursor) {
    s32 idx1;
    s32 idx2;
    TargetVec3f *base;
    TargetVec3f *cur;
    TargetVec3f *p1;
    TargetVec3f *p2;
    TargetVec3f out;
    f32 d2;
    f32 e2;

    idx1 = raceGetNextWaypointIndex(pathLength, cursor->unk2);
    idx2 = raceGetNextWaypointIndex(pathLength, idx1);
    base = gMinecartTrackPoints[cursor->unk0];
    p1 = &base[idx1];
    p2 = &base[idx2];
    cur = &base[cursor->unk2];
    mathPickCloserTargetPoint3D(actor->x, actor->y, actor->z, cur, p1, p1, p2, &out.x, &out.y, &out.z);
    d2 = RB_SQ(cur->x - p1->x) + RB_SQ(cur->y - p1->y) + RB_SQ(cur->z - p1->z);
    return sqrtf((e2 = RB_SQ(cur->z - out.z) + (RB_SQ(cur->x - out.x) + RB_SQ(cur->y - out.y))) / d2); // FAKE: dead store to e2; dropping it changes the sqrt operand codegen
}

f32 raceGetPathDistance(s32 pathLength, u16 laneIndex, u16 waypointIndex) {
    s32 index;
    TargetVec3f *points;
    TargetVec3f *p1;
    TargetVec3f *p2;
    f32 dx;
    f32 dy;
    f32 dz;

    index = raceGetNextWaypointIndex(pathLength, waypointIndex);
    points = gMinecartTrackPoints[laneIndex];
    p1 = &points[waypointIndex];
    p2 = &points[index];
    dx = p1->x - p2->x;
    dy = p1->y - p2->y;
    dz = p1->z - p2->z;
    return sqrtf((dx * dx) + (dy * dy) + (dz * dz));
}

f32 raceGetPathDistanceBetweenRacers(Actor *actorA, RacePathState *curA, Actor *actorB, RacePathState *curB) {
    s32 count;
    s32 dir;
    f32 fracA;
    f32 fracB;
    f32 distA;
    f32 distB;
    f32 total;
    s32 cur;
    s32 sign;
    s32 end;

    count = gMinecartTrackPoints[curB->unk0 + 1] - gMinecartTrackPoints[curB->unk0];
    dir = raceGetWaypointDiff(count, curA, curB);
    fracA = raceGetWaypointSegmentFraction(count, actorA, curA);
    fracB = raceGetWaypointSegmentFraction(count, actorB, curB);
    distA = raceGetPathDistance(count, curB->unk0, curA->unk2);
    distB = raceGetPathDistance(count, curB->unk0, curB->unk2);
    if (dir == 0) {
        total = fracB * distB - fracA * distA;
    } else {
        if (dir > 0) {
            total = fracB * distB + (1.0f - fracA) * distA;
            cur = raceGetNextWaypointIndex(count, curA->unk2);
            end = curB->unk2;
        } else {
            total = fracA * distA + (1.0f - fracB) * distB;
            cur = raceGetNextWaypointIndex(count, curB->unk2);
            end = curA->unk2;
        }
        while (cur != end) {
            total += raceGetPathDistance(count, curB->unk0, cur);
            cur = raceGetNextWaypointIndex(count, cur);
        }
        sign = (dir >= 0) ? 1 : -1;
        total = sign * total;
    }
    return total;
}


void raceChangeLaneRelative(RacePathState *cursor, s8 dir) {
    if (dir > 0) {
        cursor->unk1++;
    } else {
        cursor->unk1--;
    }
    cursor->unk8 = 0.0f;
}

void raceChangeLaneRandom(RacePathState *cursor) {
    switch (cursor->unk0) {
    case 0:
        cursor->unk1++;
        break;
    case 1:
        if ((randomLcgNext() & 0xFF) >= 0x80) {
            cursor->unk1++;
        } else {
            cursor->unk1--;
        }
        break;
    case 2:
        cursor->unk1--;
        break;
    }
    cursor->unk8 = 0.0f;
}

f32 raceGetCompletionFraction(RacePathState *cursor, RaceParticipant *state, RaceParticipant *leaderState) {
    f32 result;
    s8 lap;
    s32 count;
    f32 num;
    f32 den;

    lap = state->lap;
    result = 0.0f;
    if (lap > 0) {
        count = gMinecartTrackPoints[cursor->unk0 + 1] - gMinecartTrackPoints[cursor->unk0];
        num = (lap - 1) * count + state->unk3A;
        den = leaderState->unk24 * count;
        result = num / den;
    }
    return result;
}

extern void *D_80720120;

void raceTriggerBoostParticles(void) {
    s32 idx;

    for (idx = 1; idx < 3; idx++) {
        effectSetDepth(1);
        effectCreateAtActorBone(&D_80720120, 1.0f, gCurrentActor, idx, 0);
    }
}

extern RaceCurvePoint D_8002FBD0[];
extern RaceVec3f D_8002FC00[];
void raceAiUpdateSpeedAndLane(void) {
    RaceParticipant *state;
    RacePathState *cursor;
    Actor *targetActor;
    RacePathState *targetCursor;
    s32 pad44;
    RaceTarget *aux;
    f32 distToTarget;
    f32 targetSpeed;
    u8 flag;
    u8 laneRoll;
    s32 nodeIndex;
    s32 foundCompetitor;
    Actor *competitorActor;
    Actor *leaderActor;
    RaceParticipant *targetState;
    RacePathState *competitorCursor;
    f32 competitorDist;

    state = ((RaceCarActor *)gCurrentActor)->participant;
    cursor = ((RaceCarActor *)gCurrentActor)->path;
    targetActor = cursor->unk30;
    targetCursor = ((RacePathActor *)targetActor)->path;
    aux = ((RaceCarActor *)gCurrentActor)->raceTarget;
    distToTarget = raceGetPathDistanceBetweenRacers(gCurrentActor, cursor, targetActor, targetCursor);
    targetSpeed = raceEvaluateCurveTargetSpeed(aux, distToTarget, D_8002FBD0, D_8002FC00);
    flag = (cursor->unk0 == cursor->unk1) && (cursor->unk4 == 0);
    if (aux->curveMode != 0) {
        leaderActor = state->actor;
        if (raceGetCompletionFraction(cursor, state, leaderActor->customState) > 0.8) {
            raceSetPiecewiseCurveMode(aux, 0, D_8002FBD0, D_8002FC00);
        }
    }
    switch (aux->curveMode) {
    case 5:
        raceTriggerBoostParticles();
    case 0:
    case 1:
        if (flag) {
            laneRoll = (randomLcgNext() & 0xFF) < 0x14;
            if ((D_8002FBD0[1].x < distToTarget) && (distToTarget < D_8002FBD0[2].x) && (cursor->unk0 != targetCursor->unk0) && laneRoll) {
                raceChangeLaneRelative(cursor, targetCursor->unk0 - cursor->unk0);
            } else if ((D_8002FBD0[3].x < distToTarget) && (distToTarget < D_8002FBD0[4].x) && (cursor->unk0 == targetCursor->unk0) && laneRoll) {
                raceChangeLaneRandom(cursor);
            }
            flag = (cursor->unk0 == cursor->unk1) && (cursor->unk4 == 0);
            if (flag) {
                if ((distToTarget < D_8002FBD0[1].x) || (D_8002FBD0[2].x < distToTarget)) {
                    foundCompetitor = 0;
                    for (nodeIndex = 2; nodeIndex < 7 && foundCompetitor == 0; nodeIndex++) {
                        if (spawnNodeHasActor(nodeIndex) != 0) {
                            competitorActor = spawnNodeActivate(nodeIndex, 0);
                            competitorCursor = ((RacePathActor *)competitorActor)->path;
                            if (competitorCursor->unk0 == cursor->unk0) {
                                competitorDist = raceGetPathDistanceBetweenRacers(gCurrentActor, cursor, competitorActor, competitorCursor);
                                if ((competitorDist > 20.0f) && (competitorDist < 300.0f)) {
                                    foundCompetitor = 1;
                                    raceChangeLaneRandom(cursor);
                                }
                            }
                        }
                    }
                }
            }
        }
        break;
    }
    state->throttle = targetSpeed;
    if ((distToTarget < 0.0f) && (aux->distSq > 0.0f)) {
        if (gCurrentActor->soundSlots[1] == -1) {
            sfxPlayActorSound(gCurrentActor, 0x130, 0, 1, 1, 0xFF, 1.0f, 0);
        }
        gCurrentActor->unk72 = 0x14;
    }
    if (gCurrentActor->unk72 > 0) {
        gCurrentActor->unk72--;
    } else if (gCurrentActor->soundSlots[1] != -1) {
        sfxStopSlotSound(gCurrentActor, 1);
    }
    if (distToTarget < -7000.0f) {
        targetState = targetActor->customState;
        targetState->unk45 = 1;
    }
    aux->distSq = distToTarget;
}

void raceHandleCollisionRumble(RacePathState *cursor) {
    Actor *v1;
    s32 pad[2];
    RaceTarget *aux;
    f32 y;
    u8 *flag;

    v1 = cursor->unk30;
    flag = ((RaceCarActor *)gCurrentActor)->bumpCooldown;
    aux = ((RaceCarActor *)gCurrentActor)->raceTarget;
    if (gCurrentActor->speedXZ > v1->speedXZ) {
        y = gCurrentActor->speedXZ - v1->speedXZ;
    } else {
        y = -(gCurrentActor->speedXZ - v1->speedXZ);
    }
    if (*flag == 0) {
        y *= 1.5;
        y = (y > 10.0) ? 10.0 : y;
        *flag = 3;
        rumbleRequest(0, 255.0f * y * 0.1f, *flag);
        sfxPlayOnFreeSlot(0x18A, 0x7FFF, 64.0f, 1.0f, 0xA, 0);
        if (aux->distSq < 0.0f) {
            v1->speedXZ -= y;
            gCurrentActor->speedXZ += y;
        } else {
            v1->speedXZ += y;
            gCurrentActor->speedXZ -= y;
        }
    }
}

void racePlayTireScreechSfx(void) {
    RaceParticipant *state;
    Actor *targetActor;
    RaceParticipant *targetState;

    state = ((RaceCarActor *)gCurrentActor)->participant;
    targetActor = state->actor;
    targetState = targetActor->customState;
    switch (targetState->unk1C) {
    case 0x5A:
        sfxPlayActorSound(gCurrentActor, 0x107, 0, 1, 0, 0xFF, 1.0f, 0);
    case 0x1D:
    case 0x25:
    case 0x2C:
    case 0x30:
    case 0x38:
    case 0x3F:
    case 0x43:
    case 0x47:
    case 0x4E:
    case 0x54:
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x187, 0xFF, (s32)(((f64)(targetState->unk1C - 0x1D) * 0.5) + 157.0), 0, 0, 0.3f, 0);
        break;
    }
}

extern s16 D_80770628[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];

void raceUpdateOpponentEnginePitch(f32 moveSpeed) {
    s16 idx;

    idx = D_80770628[gCurrentActor->soundSlots[0]];
    gCurrentActor->unk74 = 1.0f;
    D_80770B68[idx] = (f64)(moveSpeed * 0.05f) + 1.0;
    D_80770BC0[idx] = 1.0f;
}

extern s16 D_80750AC8;
extern s32 D_8002FC0C[];

void raceOpponentCarBehaviorUpdate(void) {
    s32 pad70[2];
    u8 *flagPtr;
    RaceTarget *aux;
    s32 count;
    Actor *targetActor;
    RaceParticipant *state;
    RacePathState *cursor;
    u32 cursorVal;
    f32 unclampedVal;
    s32 phase;
    s32 idx;
    s32 statePhase;
    s32 endPhase;
    s32 pad38[1];
    s32 cam;
    s32 audioSlot;
    s32 pad30;

    state = ((RaceCarActor *)gCurrentActor)->participant;
    cursor = ((RaceCarActor *)gCurrentActor)->path;
    flagPtr = ((RaceCarActor *)gCurrentActor)->bumpCooldown;
    aux = ((RaceCarActor *)gCurrentActor)->raceTarget;
    targetActor = state->actor;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        count = gMinecartTrackPoints[cursor->unk0 + 1] - gMinecartTrackPoints[cursor->unk0];
        gCurrentActor->unk144 = 0x3C;
        gCurrentActor->flags &= ~1;
        cursor->unk0 = cursor->unk1 = 2;
        aux->distSq = 0.0f;
        cursor->unk2 = raceGetPrevWaypointIndex(count, 0);
        aux->unk10 = 1;
        raceSetPiecewiseCurveMode(aux, 5, D_8002FBD0, D_8002FC00);
        state->raceStatus = 0;
        if ((flagGet(0x12, 2) == 0) && (flagGet(0x8B, 0) == 0) && (func_807142D8() == 0)) {
            camStartPath(gCurrentActor, 0, 1);
            flagSet(0x12, 1, 2);
        } else {
            state->unk35 = 3;
        }
        currentActorClearFlag();
        D_80750AC8 = 0xA;
        actorClearNodeFlag(gCurrentActor, 4);
    }
    if (gActorGlobalState.bossFightPhase == 4) {
        raceHandleCollisionRumble(cursor);
    } else if (gActorGlobalState.bossFightPhase == 5) {
        cursor->unk39 = 0x1E;
        cursor->unk20 = 0.0f;
    }
    if (*flagPtr != 0) {
        (*flagPtr)--;
    }
    cursorVal = cursor->unk39;
    if (cursorVal != 0) {
        unclampedVal = (f32)cursorVal;
        if (unclampedVal > 10.0f) {
            cursor->unk20 = (unclampedVal - 10.0f) * 204.8f;
        } else {
            cursor->unk20 = 0.0f;
        }
    } else if ((state->raceStatus >= 2) && (state->raceStatus < 4)) {
        raceAiUpdateSpeedAndLane();
    }
    if (state->raceStatus == 1) {
        racePlayTireScreechSfx();
    }
    if (state->raceStatus < 5) {
        racePathFollowStep(cursor, state, 1);
        gCurrentActor->y += 50.0f * mathSinF((s16)(cursor->unk20 * 0.5f));
    } else {
        gCurrentActor->speedXZ = 0.0f;
    }
    raceUpdateOpponentEnginePitch(gCurrentActor->speedXZ);
    if (state->raceStatus == 0) {
        phase = state->unk35;
        statePhase = state->unk35;
        cursorVal = statePhase; // FAKE: phase/statePhase/cursorVal copies of unk35; switching on phase reallocates the switch selector
        switch (cursorVal) {
        case 0:
            if (gCurrentActor->flags & 0x02000000) {
                state->unk35 = state->unk35 + 1;
                phase = state->unk35;
            }
            break;
        case 1:
            if (!(gCurrentActor->flags & 0x02000000)) {
                camResumePath();
                state->unk35++;
                phase = state->unk35;
            }
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                state->unk35++;
            }
            phase = state->unk35;
            break;
        }
        if (phase < 3) {
            raceSetIntroCutscenePhase(targetActor);
        } else {
            raceClearIntroCutscenePhase(targetActor);
            for (idx = 2; idx < 7; idx++) {
                spawnNodeSpawnById(idx, 0, 0, 0, 0, 0, 0);
            }
        }
    } else if (state->raceStatus == 4) {
        if (state->unk35 == 0) {
            if (flagGet(0x8B, 0) == 0) {
                cam = D_8002FC0C[raceCheckLapCompletionThreshold(state, aux->participant, 0xA)];
                camStartPath(gCurrentActor, cam, 1);
                currentActorClearFlag();
            } else {
                mapCheckAutoTransition();
            }
            state->unk35++;
        }
    } else if (state->raceStatus == 5) {
        endPhase = state->unk35;
        switch (endPhase) {
        case 0:
            if (flagGet(0x8B, 0) == 0) {
                playerStateQueueCallback(0x55, 0, 0);
                idx = 0;
                gCurrentActor->pitch = 0;
                audioSlot = 0;
                gCurrentActor->roll = 0;
                do {
                    if (*(s16 *)((u8 *)gCurrentActor->soundSlots + audioSlot) != -1) { // FAKE: byte-offset iterator audioSlot; soundSlots[idx] changes the loop induction
                        sfxStopSlotSound(gCurrentActor, idx);
                    }
                    idx += 1;
                    audioSlot += 2;
                } while (idx != 2);
            }
            state->unk35++;
            break;
        case 1:
            if (gCurrentActor->flags & 0x02000000) {
                state->unk35++;
            }
            break;
        case 2:
            if (!(gCurrentActor->flags & 0x02000000)) {
                camResumePath();
                if ((state->place == 0) || (slotQueueGetValue(0xB, 0) < 0xA)) {
                    state->unk35 = 3;
                }
                state->unk35++;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                csModelStateSetFirstByte(0x62, 0xA);
                state->unk35++;
            }
            break;
        case 4:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                if (flagGet(0x8B, 0) != 0) {
                    mapCheckAutoTransition();
                } else {
                    hudSpawnTextScreen(1);
                }
                state->unk35++;
            }
            break;
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern PlayerStruct *gPlayerSlots;

void raceCameraBehaviorUpdate(void) {
    s32 pad54[3];
    Actor *targetActor;
    RaceParticipant *targetState;
    RacePathState *targetCursor;
    s32 pad44;
    RaceParticipant *playerState;
    s32 pad3C;
    s32 pathLength;
    f32 distToTarget;
    f32 offsetSign;
    f32 dist;
    f32 camYOffset;
    f32 distNorm;
    u8 tgtStateMode;
    u8 tgtCursorSub;
    RacePathState *cursor;
    RaceParticipant *state;
    Actor *playerActor;

    cursor = ((RacePathActor *)gCurrentActor)->path;
    state = gCurrentActor->customState;
    targetActor = cursor->unk30;
    targetState = targetActor->customState;
    targetCursor = ((RacePathActor *)targetActor)->path;
    playerActor = gPlayerSlots[targetState->playerIdx].actor;
    playerState = playerActor->customState;
    pathLength = gMinecartTrackPoints[cursor->unk0 + 1] - gMinecartTrackPoints[cursor->unk0];
    offsetSign = 1.0f;
    if (!(gCurrentActor->flags & 0x10)) {
        cursor->unk2 = raceGetPrevWaypointIndex(pathLength, targetCursor->unk2);
        cursor->unk2 = raceGetPrevWaypointIndex(pathLength, cursor->unk2);
        cursor->unk0 = cursor->unk1 = 1;
        racePathFollowStep(cursor, state, 0);
    }
    tgtStateMode = targetState->raceStatus;
    if (state->raceStatus != tgtStateMode) {
        state->raceStatus = tgtStateMode;
        state->unk35 = 0;
    }
    dist = raceGetPathDistanceBetweenRacers(gCurrentActor, cursor, targetActor, targetCursor);
    distToTarget = dist;
    tgtCursorSub = targetCursor->unk1;
    if (cursor->unk1 != tgtCursorSub) {
        cursor->unk1 = tgtCursorSub;
        cursor->unk8 = 0.0f;
    }
    if ((state->raceStatus >= 2) && (state->raceStatus < 4)) {
        if ((u32)targetCursor->unk10 > 24.0) {
            offsetSign = -2.5f;
        } else if (targetCursor->unk14 > 0.5f) {
            offsetSign = 2.5f;
        }
        cursor->unk39 = targetCursor->unk39;
        cursor->unk10 = targetCursor->unk10;
        state->throttle = targetState->throttle + ((dist - (90.0f * offsetSign)) * 0.006f);
        if (dist < 30.0f) {
            if (targetActor->speedXZ < gCurrentActor->speedXZ) {
                gCurrentActor->speedXZ = targetActor->speedXZ;
            }
        }
        racePathFollowStep(cursor, state, 0);
    }
    if ((state->raceStatus < 4) && (state->raceStatus > 0)) {
        distNorm = distToTarget / 90.0f;
        if (distNorm < 0.0f) {
            camYOffset = 0.0f;
        } else {
            if (distNorm > 1.0f) {
                dist = 1.0f;
            } else {
                dist = distNorm;
            }
            camYOffset = dist;
        }
        camYOffset = (20.0f * camYOffset) + 20.0f;
        camSetFixedView(playerState->unk104, gCurrentActor->x, gCurrentActor->y + camYOffset, gCurrentActor->z, targetActor->x, targetActor->y + 20.0f, targetActor->z, 1);
    }
}


void raceFindNearestWaypoint(RacePathState *cursor) {
    TargetVec3f *p;
    s32 count;
    s32 i;
    s32 j;
    f32 best;
    f32 px;
    f32 py;
    f32 pz;
    f32 d;

    count = gMinecartTrackPoints[1] - gMinecartTrackPoints[0];
    p = gMinecartTrackPoints[0];
    best = 10000000.0f;
    px = gCurrentActor->x;
    py = gCurrentActor->y;
    pz = gCurrentActor->z;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < count; j++) {
            d = RB_SQ(px - p->x) + RB_SQ(py - p->y) + RB_SQ(pz - p->z);
            if (d < best) {
                cursor->unk2 = j;
                cursor->unk0 = i;
                cursor->unk1 = i;
                best = d;
            }
            p++;
        }
    }
}


void raceObstacleCarBehaviorUpdate(void) {
    Actor *targetActor;
    RacePathState *cursor;
    RaceParticipant *state;
    RaceParticipant *targetState;
    f32 nodeZ;
    f32 nodeY;
    f32 nodeX;

    state = ((RaceCarActor *)gCurrentActor)->participant;
    cursor = ((RaceCarActor *)gCurrentActor)->path;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        raceFindNearestWaypoint(cursor);
        gCurrentActor->unk144 = 0x3C;
        state->throttle = 0.5f;
        actorClearNodeFlag(gCurrentActor, 1);
        cursor->unk30 = spawnNodeActivate(1, 0);
        gCurrentActor->flags &= ~1;
    }
    targetActor = cursor->unk30;
    targetState = ((RaceCarActor *)targetActor)->participant;
    if ((gActorGlobalState.bossFightPhase == 9) || (gActorGlobalState.unk15 != 0)) {
        tagBarrelSpawnActorSmokePuffs(0, 1);
        gCurrentActor->state = 0x40;
    }
    actorGetNodePos(gCurrentActor, 6, &nodeX, &nodeY, &nodeZ);
    commandQueuePush(gCurrentActor, (s16)nodeX, (s16)nodeY, (s16)nodeZ, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    actorGetNodePos(gCurrentActor, 0xB, &nodeX, &nodeY, &nodeZ);
    commandQueuePush(gCurrentActor, (s16)nodeX, (s16)nodeY, (s16)nodeZ, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    racePathFollowStep(cursor, state, 1);
    if ((state->raceStatus == 0) && (targetState->raceStatus == 5)) {
        gBehaviourExtraState->respawnDelay = 0;
        gCurrentActor->state = 0x40;
        state->raceStatus++;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
