#include "common.h"
#include "race.h"
#include "actor.h"
#include "sched.h"
#include "text.h"
#include "proto/global/117190_menu_transition.h"
#include "proto/global/119370_effect_grid.h"
#include "proto/global/131B0_rumble.h"
#include "proto/global/135D30_flags.h"
#include "proto/global/126260_command_queue.h"
#include "proto/global/1295B0_spawn_nodes.h"
#include "proto/global/12E800_behaviour.h"
#include "proto/global/166A0_random.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/2C910.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/3C10_map_transition.h"
#include "proto/global/42630_cutscene_interp.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/70FD0_collision_geometry.h"
#include "proto/global/80150_barrels.h"
#include "proto/global/936B0_projectile.h"
#include "proto/global/ACDC0_pause_menu.h"
#include "proto/global/EFDC0_player_state_enter.h"
#include "proto/global/FCCD0_slot_queue.h"
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

    diff = curB->waypoint - curA->waypoint;
    abs_diff = (diff > 0) ? diff : -diff;
    if ((pathLength / 2) < abs_diff) {
        sign = (diff >= 0) ? 1 : -1;
        diff -= sign * pathLength;
    }
    return diff;
}

f32 raceGetWaypointSegmentFraction(s32 pathLength, Actor *actor, RacePathState *cursor) {
    s32 nextIdx;
    s32 nextNextIdx;
    TargetVec3f *points;
    TargetVec3f *cur;
    TargetVec3f *p1;
    TargetVec3f *p2;
    TargetVec3f out;
    f32 d2;
    f32 e2;

    nextIdx = raceGetNextWaypointIndex(pathLength, cursor->waypoint);
    nextNextIdx = raceGetNextWaypointIndex(pathLength, nextIdx);
    points = gMinecartTrackPoints[cursor->lane];
    p1 = &points[nextIdx];
    p2 = &points[nextNextIdx];
    cur = &points[cursor->waypoint];
    mathPickCloserTargetPoint3D(actor->x, actor->y, actor->z, cur, p1, p1, p2, &out.x, &out.y, &out.z);
    d2 = SQ(cur->x - p1->x) + SQ(cur->y - p1->y) + SQ(cur->z - p1->z);
    return sqrtf((e2 = SQ(cur->z - out.z) + (SQ(cur->x - out.x) + SQ(cur->y - out.y))) / d2); // ORIG: target stores e2 to its home 76(sp) at 0x1b0 and reloads at 0x1b4
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

    count = gMinecartTrackPoints[curB->lane + 1] - gMinecartTrackPoints[curB->lane];
    dir = raceGetWaypointDiff(count, curA, curB);
    fracA = raceGetWaypointSegmentFraction(count, actorA, curA);
    fracB = raceGetWaypointSegmentFraction(count, actorB, curB);
    distA = raceGetPathDistance(count, curB->lane, curA->waypoint);
    distB = raceGetPathDistance(count, curB->lane, curB->waypoint);
    if (dir == 0) {
        total = fracB * distB - fracA * distA;
    } else {
        if (dir > 0) {
            total = fracB * distB + (1.0f - fracA) * distA;
            cur = raceGetNextWaypointIndex(count, curA->waypoint);
            end = curB->waypoint;
        } else {
            total = fracA * distA + (1.0f - fracB) * distB;
            cur = raceGetNextWaypointIndex(count, curB->waypoint);
            end = curA->waypoint;
        }
        while (cur != end) {
            total += raceGetPathDistance(count, curB->lane, cur);
            cur = raceGetNextWaypointIndex(count, cur);
        }
        sign = (dir >= 0) ? 1 : -1;
        total = sign * total;
    }
    return total;
}


void raceChangeLaneRelative(RacePathState *cursor, s8 dir) {
    if (dir > 0) {
        cursor->targetLane++;
    } else {
        cursor->targetLane--;
    }
    cursor->laneBlend = 0.0f;
}

void raceChangeLaneRandom(RacePathState *cursor) {
    switch (cursor->lane) {
    case 0:
        cursor->targetLane++;
        break;
    case 1:
        if ((randomLcgNext() & 0xFF) >= 0x80) {
            cursor->targetLane++;
        } else {
            cursor->targetLane--;
        }
        break;
    case 2:
        cursor->targetLane--;
        break;
    }
    cursor->laneBlend = 0.0f;
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
        count = gMinecartTrackPoints[cursor->lane + 1] - gMinecartTrackPoints[cursor->lane];
        num = (lap - 1) * count + state->routePos;
        den = leaderState->lapCount * count;
        result = num / den;
    }
    return result;
}

extern void *gEffectSpriteFireBurst;

void raceTriggerBoostParticles(void) {
    s32 idx;

    for (idx = 1; idx < 3; idx++) {
        effectSetDepth(1);
        effectCreateAtActorBone(&gEffectSpriteFireBurst, 1.0f, gCurrentActor, idx, 0);
    }
}

RaceCurvePoint raceCarSpeedCurve[6] = {
    { -1000.0f, 0.7f }, { -200.0f, 1.2f }, { -70.0f, 1.2f }, { 0.0f, 1.2f }, { 500.0f, 1.2f }, { 1000.0f, 2.4f },
};
RaceVec3f raceCarSpeedLevels[1] = { { 0.7f, 1.2f, 2.4f } };
void raceAiUpdateSpeedAndLane(void) {
    RaceParticipant *state;
    RacePathState *cursor;
    Actor *targetActor;
    RacePathState *targetCursor;
    s32 pad44;
    RaceTarget *raceTarget;
    f32 distToTarget;
    f32 targetSpeed;
    u8 laneSettled;
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
    targetActor = cursor->targetActor;
    targetCursor = ((RacePathActor *)targetActor)->path;
    raceTarget = ((RaceCarActor *)gCurrentActor)->raceTarget;
    distToTarget = raceGetPathDistanceBetweenRacers(gCurrentActor, cursor, targetActor, targetCursor);
    targetSpeed = raceEvaluateCurveTargetSpeed(raceTarget, distToTarget, raceCarSpeedCurve, raceCarSpeedLevels);
    laneSettled = (cursor->lane == cursor->targetLane) && (cursor->laneSettleTimer == 0);
    if (raceTarget->curveMode != 0) {
        leaderActor = state->actor;
        if (raceGetCompletionFraction(cursor, state, leaderActor->customState) > 0.8) {
            raceSetPiecewiseCurveMode(raceTarget, 0, raceCarSpeedCurve, raceCarSpeedLevels);
        }
    }
    switch (raceTarget->curveMode) {
    case 5:
        raceTriggerBoostParticles();
    case 0:
    case 1:
        if (laneSettled) {
            laneRoll = (randomLcgNext() & 0xFF) < 0x14;
            if ((raceCarSpeedCurve[1].x < distToTarget) && (distToTarget < raceCarSpeedCurve[2].x) && (cursor->lane != targetCursor->lane) && laneRoll) {
                raceChangeLaneRelative(cursor, targetCursor->lane - cursor->lane);
            } else if ((raceCarSpeedCurve[3].x < distToTarget) && (distToTarget < raceCarSpeedCurve[4].x) && (cursor->lane == targetCursor->lane) && laneRoll) {
                raceChangeLaneRandom(cursor);
            }
            laneSettled = (cursor->lane == cursor->targetLane) && (cursor->laneSettleTimer == 0);
            if (laneSettled) {
                if ((distToTarget < raceCarSpeedCurve[1].x) || (raceCarSpeedCurve[2].x < distToTarget)) {
                    foundCompetitor = 0;
                    for (nodeIndex = 2; nodeIndex < 7 && foundCompetitor == 0; nodeIndex++) {
                        if (spawnNodeHasActor(nodeIndex) != 0) {
                            competitorActor = spawnNodeActivate(nodeIndex, 0);
                            competitorCursor = ((RacePathActor *)competitorActor)->path;
                            if (competitorCursor->lane == cursor->lane) {
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
    if ((distToTarget < 0.0f) && (raceTarget->distSq > 0.0f)) {
        if (gCurrentActor->soundSlots[1] == -1) {
            sfxPlayActorSound(gCurrentActor, 0x130, 0, 1, 1, 0xFF, 1.0f, 0);
        }
        gCurrentActor->soundTimer = 0x14;
    }
    if (gCurrentActor->soundTimer > 0) {
        gCurrentActor->soundTimer--;
    } else if (gCurrentActor->soundSlots[1] != -1) {
        sfxStopSlotSound(gCurrentActor, 1);
    }
    if (distToTarget < -7000.0f) {
        targetState = targetActor->customState;
        targetState->eliminated = 1;
    }
    raceTarget->distSq = distToTarget;
}

void raceHandleCollisionRumble(RacePathState *cursor) {
    Actor *targetActor;
    s32 pad[2];
    RaceTarget *raceTarget;
    f32 impulse;
    u8 *bumpCooldown;

    targetActor = cursor->targetActor;
    bumpCooldown = ((RaceCarActor *)gCurrentActor)->bumpCooldown;
    raceTarget = ((RaceCarActor *)gCurrentActor)->raceTarget;
    if (gCurrentActor->speedXZ > targetActor->speedXZ) {
        impulse = gCurrentActor->speedXZ - targetActor->speedXZ;
    } else {
        impulse = -(gCurrentActor->speedXZ - targetActor->speedXZ);
    }
    if (*bumpCooldown == 0) {
        impulse *= 1.5;
        impulse = (impulse > 10.0) ? 10.0 : impulse;
        *bumpCooldown = 3;
        rumbleRequest(0, 255.0f * impulse * 0.1f, *bumpCooldown);
        sfxPlayOnFreeSlot(0x18A, 0x7FFF, 64.0f, 1.0f, 0xA, 0);
        if (raceTarget->distSq < 0.0f) {
            targetActor->speedXZ -= impulse;
            gCurrentActor->speedXZ += impulse;
        } else {
            targetActor->speedXZ += impulse;
            gCurrentActor->speedXZ -= impulse;
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
    switch (targetState->phaseTimer) {
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
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x187, 0xFF, (s32)(((f64)(targetState->phaseTimer - 0x1D) * 0.5) + 157.0), 0, 0, 0.3f, 0);
        break;
    }
}

extern s16 gSfxSourceVoice[];
extern f32 gSfxVoicePitch[];
extern f32 gSfxVoiceModCounter[];

void raceUpdateOpponentEnginePitch(f32 moveSpeed) {
    s16 idx;

    idx = gSfxSourceVoice[gCurrentActor->soundSlots[0]];
    gCurrentActor->soundVolume = 1.0f;
    gSfxVoicePitch[idx] = (f64)(moveSpeed * 0.05f) + 1.0;
    gSfxVoiceModCounter[idx] = 1.0f;
}

s32 raceCarResultCamPathIds[5] = { 2, 1, 4, 3, 0 };

void raceOpponentCarBehaviorUpdate(void) {
    s32 pad70[2];
    u8 *bumpCooldown;
    RaceTarget *raceTarget;
    s32 count;
    Actor *targetActor;
    RaceParticipant *state;
    RacePathState *cursor;
    u8 stunTimer;
    s32 idx;
    s32 pathId;
    s32 pad44[2];

    state = ((RaceCarActor *)gCurrentActor)->participant;
    cursor = ((RaceCarActor *)gCurrentActor)->path;
    bumpCooldown = ((RaceCarActor *)gCurrentActor)->bumpCooldown;
    raceTarget = ((RaceCarActor *)gCurrentActor)->raceTarget;
    targetActor = state->actor;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        count = gMinecartTrackPoints[cursor->lane + 1] - gMinecartTrackPoints[cursor->lane];
        gCurrentActor->collisionMode = 0x3C;
        gCurrentActor->flags &= ~1;
        cursor->lane = cursor->targetLane = 2;
        raceTarget->distSq = 0.0f;
        cursor->waypoint = raceGetPrevWaypointIndex(count, 0);
        raceTarget->chaseEnabled = 1;
        raceSetPiecewiseCurveMode(raceTarget, 5, raceCarSpeedCurve, raceCarSpeedLevels);
        state->raceStatus = 0;
        if ((flagGet(0x12, 2) == 0) && (flagGet(0x8B, 0) == 0) && (menuIsTransitionType3Or4() == 0)) {
            camStartPath(gCurrentActor, 0, 1);
            flagSet(0x12, 1, 2);
        } else {
            state->statusStep = 3;
        }
        currentActorClearFlag();
        gTextNumberArg = 0xA;
        actorClearNodeFlag(gCurrentActor, 4);
    }
    if (gActorGlobalState.bossFightPhase == 4) {
        raceHandleCollisionRumble(cursor);
    } else if (gActorGlobalState.bossFightPhase == 5) {
        cursor->stunTimer = 0x1E;
        cursor->shakeRoll = 0.0f;
    }
    if (*bumpCooldown != 0) {
        (*bumpCooldown)--;
    }
    stunTimer = cursor->stunTimer;
    if (stunTimer != 0) {
        if (stunTimer > 10.0f) {
            cursor->shakeRoll = (stunTimer - 10.0f) * 204.8f;
        } else {
            cursor->shakeRoll = 0.0f;
        }
    } else if ((state->raceStatus >= 2) && (state->raceStatus < 4)) {
        raceAiUpdateSpeedAndLane();
    }
    if (state->raceStatus == 1) {
        racePlayTireScreechSfx();
    }
    if (state->raceStatus < 5) {
        racePathFollowStep(cursor, state, 1);
        gCurrentActor->y += 50.0f * mathSinF(cursor->shakeRoll * 0.5f);
    } else {
        gCurrentActor->speedXZ = 0.0f;
    }
    raceUpdateOpponentEnginePitch(gCurrentActor->speedXZ);
    if (state->raceStatus == 0) {
        switch (state->statusStep) {
        case 0:
            if (gCurrentActor->flags & 0x02000000) {
                state->statusStep++;
            }
            break;
        case 1:
            if (!(gCurrentActor->flags & 0x02000000)) {
                camResumePath();
                state->statusStep++;
            }
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                state->statusStep++;
            }
            break;
        }
        if (state->statusStep < 3) {
            raceSetIntroCutscenePhase(targetActor);
        } else {
            raceClearIntroCutscenePhase(targetActor);
            for (idx = 2; idx < 7; idx++) {
                spawnNodeSpawnById(idx, 0, 0, 0, 0, 0, 0);
            }
        }
    } else if (state->raceStatus == 4) {
        if (state->statusStep == 0) {
            if (flagGet(0x8B, 0) == 0) {
                pathId = raceCarResultCamPathIds[raceCheckLapCompletionThreshold(state, raceTarget->participant, 0xA)];
                camStartPath(gCurrentActor, pathId, 1);
                currentActorClearFlag();
            } else {
                mapCheckAutoTransition();
            }
            state->statusStep++;
        }
    } else if (state->raceStatus == 5) {
        switch (state->statusStep) {
        case 0:
            if (flagGet(0x8B, 0) == 0) {
                playerStateQueueCallback(0x55, 0, 0);
                gCurrentActor->pitch = 0;
                gCurrentActor->roll = 0;
                for (idx = 0; idx < 2; idx++) {
                    if (gCurrentActor->soundSlots[idx] != -1) {
                        sfxStopSlotSound(gCurrentActor, idx);
                    }
                }
            }
            state->statusStep++;
            break;
        case 1:
            if (gCurrentActor->flags & 0x02000000) {
                state->statusStep++;
            }
            break;
        case 2:
            if (!(gCurrentActor->flags & 0x02000000)) {
                camResumePath();
                if ((state->place == 0) || (slotQueueGetValue(0xB, 0) < 0xA)) {
                    state->statusStep = 3;
                }
                state->statusStep++;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                csModelStateSetFirstByte(0x62, 0xA);
                state->statusStep++;
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
                state->statusStep++;
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
    PlayerState *playerState;
    s32 pad3C;
    s32 pathLength;
    f32 dist;
    f32 gapScale;
    f32 camYOffset;
    f32 distNorm;
    RacePathState *cursor;
    RaceParticipant *state;
    Actor *playerActor;

    cursor = ((RacePathActor *)gCurrentActor)->path;
    state = gCurrentActor->customState;
    targetActor = cursor->targetActor;
    targetState = targetActor->customState;
    targetCursor = ((RacePathActor *)targetActor)->path;
    playerActor = gPlayerSlots[targetState->playerIdx].actor;
    playerState = playerActor->customState;
    pathLength = gMinecartTrackPoints[cursor->lane + 1] - gMinecartTrackPoints[cursor->lane];
    gapScale = 1.0f;
    if (!(gCurrentActor->flags & 0x10)) {
        cursor->waypoint = raceGetPrevWaypointIndex(pathLength, targetCursor->waypoint);
        cursor->waypoint = raceGetPrevWaypointIndex(pathLength, cursor->waypoint);
        cursor->lane = cursor->targetLane = 1;
        racePathFollowStep(cursor, state, 0);
    }
    if (state->raceStatus != targetState->raceStatus) {
        state->raceStatus = targetState->raceStatus;
        state->statusStep = 0;
    }
    dist = raceGetPathDistanceBetweenRacers(gCurrentActor, cursor, targetActor, targetCursor);
    if (cursor->targetLane != targetCursor->targetLane) {
        cursor->targetLane = targetCursor->targetLane;
        cursor->laneBlend = 0.0f;
    }
    if ((state->raceStatus >= 2) && (state->raceStatus < 4)) {
        if (targetCursor->boostTimer > 24.0) {
            gapScale = -2.5f;
        } else if (targetCursor->boostAmount > 0.5f) {
            gapScale = 2.5f;
        }
        cursor->stunTimer = targetCursor->stunTimer;
        cursor->boostTimer = targetCursor->boostTimer;
        state->throttle = targetState->throttle + ((dist - (90.0f * gapScale)) * 0.006f);
        if ((dist < 30.0f) && (targetActor->speedXZ < gCurrentActor->speedXZ)) {
            gCurrentActor->speedXZ = targetActor->speedXZ;
        }
        racePathFollowStep(cursor, state, 0);
    }
    if ((state->raceStatus < 4) && (state->raceStatus > 0)) {
        distNorm = dist / 90.0f;
        camYOffset = (distNorm < 0.0f) ? 0.0f : (distNorm > 1.0f) ? 1.0f : distNorm;
        camYOffset = (20.0f * camYOffset) + 20.0f;
        camSetFixedView(playerState->camActor, gCurrentActor->x, gCurrentActor->y + camYOffset, gCurrentActor->z, targetActor->x, targetActor->y + 20.0f, targetActor->z, 1);
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
            d = SQ(px - p->x) + SQ(py - p->y) + SQ(pz - p->z);
            if (d < best) {
                cursor->waypoint = j;
                cursor->lane = i;
                cursor->targetLane = i;
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
        gCurrentActor->collisionMode = 0x3C;
        state->throttle = 0.5f;
        actorClearNodeFlag(gCurrentActor, 1);
        cursor->targetActor = spawnNodeActivate(1, 0);
        gCurrentActor->flags &= ~1;
    }
    targetActor = cursor->targetActor;
    targetState = ((RaceCarActor *)targetActor)->participant;
    if ((gActorGlobalState.bossFightPhase == 9) || (gActorGlobalState.damaged != 0)) {
        tagBarrelSpawnActorSmokePuffs(0, 1);
        gCurrentActor->state = 0x40;
    }
    actorGetNodePos(gCurrentActor, 6, &nodeX, &nodeY, &nodeZ);
    commandQueuePush(gCurrentActor, nodeX, nodeY, nodeZ, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    actorGetNodePos(gCurrentActor, 0xB, &nodeX, &nodeY, &nodeZ);
    commandQueuePush(gCurrentActor, nodeX, nodeY, nodeZ, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    racePathFollowStep(cursor, state, 1);
    if ((state->raceStatus == 0) && (targetState->raceStatus == 5)) {
        gBehaviourExtraState->respawnDelay = 0;
        gCurrentActor->state = 0x40;
        state->raceStatus++;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
