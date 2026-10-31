// zoneCheckActorInside (src/global/1295B0.c): Stage 5: regalloc only (142/142 insns, frame 0x68 exact). Target s3=5,s4=1(store),s5=found,s6=0xA,s7=1(cmp),s8=&D_807FDC9C; built s3=1,s4=found,s5=0xA,s6=1,s7=5,s8=&D_807FDC9C. Deadsweep if (D_807FDC9C == 0) {} reduces to full=9 text=9 shape=2 (only s3 and s8 swapped).
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

void func_806755A8(s32, s32, s32, s32, void *, void *);

s32 zoneCheckActorInside(Actor *arg0, s32 arg1, s32 arg2, F1Tbl *arg3) {
    f32 x;
    f32 y;
    f32 z;
    s16 i;
    s32 found;
    F1Ent *e;

    arg0->unkF4 = 0;
    arg0->unkF6 = 0xFFF;
    found = 0;
    x = arg0->unk7C;
    y = arg0->unk80;
    z = arg0->unk84;
    for (i = 0; i < arg3->count10; i++) {
        e = F1ENT(arg3, i);
        if (!((e->flags & 0xFFFF) & 0x80)) {
            if (((e->flags & 0x7F) == 0) || ((e->flags & 0x7F) == 1) ||
                (((e->flags & 0x7F) == 5) && ((f64)arg0->unkB8 < (f64)(u32)((u8 *)D_807FDC9C)[0xD] * 1.4))) {
                if (((f32)e->y <= y) && (y <= (f32)(e->y + e->height))) {
                    if (e->flags) {
                    }
                    if (((x - (f32)e->x) * (x - (f32)e->x)) + ((z - (f32)e->z) * (z - (f32)e->z)) < (f32)(e->radius * e->radius)) {
                        func_806755A8((s32)x, (s32)z, e->x, e->z, &arg0->unkF4, &arg0->unkF6);
                        found = 1;
                        arg0->unkFC = 1;
                        arg0->unkFD = 1;
                    }
                }
            }
        }
    }
    return found;
}
