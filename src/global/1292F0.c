#include "common.h"
#include "actor.h"

void *heapAlloc(s32);

typedef struct AnimationOwner {
    u8 unk0[0x118];
    void *unk118;
} AnimationOwner;

void heapFree(void *);

typedef struct PathFollowState {
    u8 pad0[4];
    s32 unk4;
    f32 unk8;
    u8 unkC;
    u8 padD;
    s16 unkE;
    s16 unk10;
    s16 unk12;
} PathFollowState;

typedef struct PathFollowOwner {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x28];
    s8 unkB0;
    u8 padB1[0x67];
    PathFollowState *unk118;
} PathFollowOwner;

s32 pathExists(u8);
void pathFindClosestPoint(s32, f32, f32, f32, s32 *, f32 *);
void pathRefineClosestPoint(s32, f32, f32, f32, s32 *, f32 *);
void pathSplineSample(s32, s32, f32, f32 *, f32 *, f32 *);
f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);
s16 pathEntryCount(s32);

void pathFollowUpdateHeading(PathFollowOwner *owner, u8 continuous) {
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
    if (owner->unk118 == NULL) {
        owner->unk118 = heapAlloc(0x14);
        s = owner->unk118;
        if (owner->unkB0 != -1 && pathExists(owner->unkB0) != 0) {
            s->unk12 = owner->unkB0;
        } else {
            s->unk12 = -1;
        }
        s->unkC = 0;
        fresh = 1;
    } else {
        s = owner->unk118;
    }
    if (continuous != 0 || s->unkC == 0) {
        if (s->unk12 == -1) {
            s->unkC = 1;
            s->unk10 = 0;
            s->unkE = 0;
            return;
        }
        if (fresh != 0) {
            pathFindClosestPoint(s->unk12, owner->unk7C, owner->unk80, owner->unk84, &s->unk4, &s->unk8);
        } else {
            pathRefineClosestPoint(s->unk12, owner->unk7C, owner->unk80, owner->unk84, &s->unk4, &s->unk8);
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

void animationOwnerFreeBuffer(AnimationOwner *owner) {
    void *buffer;

    buffer = owner->unk118;
    if (buffer != 0) {
        heapFree(buffer);
        owner->unk118 = NULL;
    }
}

