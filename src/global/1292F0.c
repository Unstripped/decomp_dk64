#include "common.h"
#include "actor.h"
#include "proto/global/127B00.h"
#include "proto/global/1292F0.h"
#include "proto/global/15050.h"
#include "proto/global/69E60.h"




void pathFollowUpdateHeading(Actor *owner, u8 continuous) {
    s32 fresh;
    PathFollowState *s;
    s32 idx;
    f32 frac;
    f32 x0;
    f32 y0;
    f32 z0;
    f32 x1;
    f32 y1;
    f32 z1;
    s16 heading;
    s32 cnt;
    u8 pathEnded;

    pathEnded = 0;
    fresh = 0;
    if (owner->floorContact == NULL) {
        owner->floorContact = heapAlloc(0x14);
        s = owner->floorContact;
        if (owner->unkB0[0] != -1 && pathExists(owner->unkB0[0]) != 0) {
            s->unk12 = owner->unkB0[0];
        } else {
            s->unk12 = -1;
        }
        s->unkC = 0;
        fresh = 1;
    } else {
        s = owner->floorContact;
    }
    if (continuous != 0 || s->unkC == 0) {
        if (s->unk12 == -1) {
            s->unkC = 1;
            s->unk10 = 0;
            s->unkE = 0;
            return;
        }
        if (fresh != 0) {
            pathFindClosestPoint(s->unk12, owner->x, owner->y, owner->z, &s->unk4, &s->unk8);
        } else {
            pathRefineClosestPoint(s->unk12, owner->x, owner->y, owner->z, &s->unk4, &s->unk8);
        }
        frac = s->unk8;
        idx = s->unk4;
        pathSplineSample(s->unk12, idx, frac, &x0, &y0, &z0);
        frac = frac + 0.4;
        if (frac >= 1.0) {
            idx += 1;
            frac = frac - 1.0;
        }
        pathSplineSample(s->unk12, idx, frac, &x1, &y1, &z1);
        heading = (s32)(mathAngleBetweenPointsDeg((s32)x0, (s32)z0, (s32)x1, (s32)z1) * 2048.0 / 3.14159274101257324);
        heading = 0x1000 - heading;
        heading += 0x800;
        s->unkE = heading & 0xFFF;
        s->unk10 = 0x23;
        cnt = pathEntryCount(s->unk12) - 1;
        if (s->unk4 >= cnt) {
            if (cnt == s->unk4) {
                pathEnded = 1;
                s->unk10 = 0;
            } else {
                pathEnded = 1;
                s->unk10 = 0;
            }
        }
        if (pathEnded != 0 && continuous == 0) {
            s->unkC = 1;
        }
    }
}

void animationOwnerFreeBuffer(Actor *owner) {
    void *buffer;

    buffer = owner->floorContact;
    if (buffer != 0) {
        heapFree(buffer);
        owner->floorContact = NULL;
    }
}

