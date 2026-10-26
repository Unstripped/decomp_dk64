// func_80725ED4 (src/global/1295B0.c): func_80725ED4 (src/global/1295B0.c): matches except frame 0x70 vs 0x68 (one spill/local word too many). Tried dropping e/d/stop/found, types, dead uses.
#include "common.h"
#include "actor.h"

extern ActorGlobalState D_807FBB70;

typedef struct F1Ent {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ u8 flags;
    /* 0x7 */ u8 radius;
    /* 0x8 */ u8 height;
    /* 0x9 */ u8 pad9;
    /* 0xA */ s16 unkA;
} F1Ent; // size = 0xC? (stride 0xA)

typedef struct F1Tbl {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s16 count8;
    /* 0x0A */ u8 padA[2];
    /* 0x0C */ u8 *entsC;
    /* 0x10 */ s16 count10;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ u8 *ents14;
} F1Tbl;

#define F1ENT(t, i) ((F1Ent *)((t)->ents14 + (i) * 0xA))

s32 segmentIntersectsCircle2D(s16, s16, s16, s16, s16, s16, s16);
s32 zoneCanReachPoint(Actor *, s16, s16, s16, F1Tbl *);
s32 func_80611A44(void);

s32 func_80725ED4(u8 arg0, Actor *arg1, F1Tbl *arg2, s16 *arg3, s16 *arg4, s16 *arg5) {
    s32 found;
    s32 best;
    s32 stop;
    s16 i;
    F1Ent *e;
    s32 d;

    stop = 0;
    found = 0;
    if (arg0 & 1) {
        best = 0;
    } else {
        best = 0xF423F;
    }
    for (i = 0; i < arg2->count10 && !stop; i++) {
        e = F1ENT(arg2, i);
        if (!(e->flags & 0x80) && ((e->flags & 0x7F) == 3)) {
            if (segmentIntersectsCircle2D((s32)arg1->unk7C, (s32)arg1->unk84, e->x, e->z, (s32)D_807FDC94->unk7C, (s32)D_807FDC94->unk84, 0x14) == 0) {
                if (zoneCanReachPoint(arg1, e->x, e->y, e->z, arg2) != 0) {
                    if (((arg0 & 1) && (d = (s32)(((D_807FDC94->unk7C - e->x) * (D_807FDC94->unk7C - e->x)) + ((D_807FDC94->unk84 - e->z) * (D_807FDC94->unk84 - e->z))), best < d)) ||
                        ((arg0 & 2) && (d = (s32)(((arg1->unk7C - e->x) * (arg1->unk7C - e->x)) + ((arg1->unk84 - e->z) * (arg1->unk84 - e->z))), d < best))) {
                        best = d;
                        *arg3 = e->x;
                        *arg4 = e->y;
                        *arg5 = e->z;
                        found = 1;
                        if (arg0 & 0x80) {
                            if (((func_80611A44() >> 0xF) % 100) >= 0x33) {
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
