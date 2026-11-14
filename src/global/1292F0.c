#include "common.h"
#include "actor.h"
#include "proto/global/127B00.h"
#include "proto/global/1292F0.h"
#include "proto/global/15050.h"
#include "proto/global/69E60.h"

void pathFollowUpdateHeading(Actor *owner, u8 continuous) {
    s32 justAllocated;
    PathFollowState *state;
    s32 point;
    f32 frac;
    f32 x0;
    f32 y0;
    f32 z0;
    f32 x1;
    f32 y1;
    f32 z1;
    s16 heading;
    s32 lastPoint;
    u8 pathEnded;

    pathEnded = 0;
    justAllocated = 0;
    if (owner->pathFollow == NULL) {
        owner->pathFollow = heapAlloc(sizeof(PathFollowState));
        state = owner->pathFollow;
        if (owner->unkB0[0] != -1 && pathExists(owner->unkB0[0]) != 0) {
            state->pathId = owner->unkB0[0];
        } else {
            state->pathId = -1;
        }
        state->done = 0;
        justAllocated = 1;
    } else {
        state = owner->pathFollow;
    }
    if (continuous != 0 || state->done == 0) {
        if (state->pathId == -1) {
            state->done = 1;
            state->speed = 0;
            state->yaw = 0;
            return;
        }
        if (justAllocated != 0) {
            pathFindClosestPoint(state->pathId, owner->x, owner->y, owner->z, &state->point, &state->pointFrac);
        } else {
            pathRefineClosestPoint(state->pathId, owner->x, owner->y, owner->z, &state->point, &state->pointFrac);
        }
        frac = state->pointFrac;
        point = state->point;
        pathSplineSample(state->pathId, point, frac, &x0, &y0, &z0);
        frac += 0.4;
        if (frac >= 1.0) {
            point++;
            frac -= 1.0;
        }
        pathSplineSample(state->pathId, point, frac, &x1, &y1, &z1);
        heading = (s32)(mathAngleBetweenPointsDeg((s32)x0, (s32)z0, (s32)x1, (s32)z1) * 2048.0 / 3.14159274101257324);
        heading = 0x1000 - heading;
        heading += 0x800;
        state->yaw = heading & 0xFFF;
        state->speed = 0x23;
        lastPoint = pathEntryCount(state->pathId) - 1;
        if (state->point >= lastPoint) {
            if (lastPoint == state->point) { // ORIG: target tests lastPoint != unk4 (bne at 0x234) and keeps both identical bodies
                pathEnded = 1;
                state->speed = 0;
            } else {
                pathEnded = 1;
                state->speed = 0;
            }
        }
        if (pathEnded != 0 && continuous == 0) {
            state->done = 1;
        }
    }
}

void pathFollowFree(Actor *owner) {
    PathFollowState *state;

    state = owner->pathFollow;
    if (state != NULL) {
        heapFree(state);
        owner->pathFollow = NULL;
    }
}

