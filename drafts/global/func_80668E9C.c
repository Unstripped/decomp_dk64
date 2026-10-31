// func_80668E9C (src/global/6AD90.c): natural form (dx01..dz02 f64 locals from direct tri->x[i] reads, nx/ny/nz named, d from field reads, sp8C hack dropped; slot address add as 'sp9A*0x90 + base + 0x48'): frame 0x130 + named slots exact; deadsweep score full=38 text=38 shape=17 (was 208/181/109). Remaining: CSE temp for sp9A*0x90 at 0x80 not 0x8C (target has 3 extra temp words), nz/d regs (target nz=f0 spilled to temp 0x70, d=f2 home 0x100; ours nz=f2 home 0x108, d=f18 home 0x100). Parked in src copy.
#include "common.h"
#include "actor.h"

typedef struct {
    f32 x[3];
    f32 y[3];
    f32 z[3];
    u8 unk24;
    u8 unk25;
    s8 unk26;
    u8 unk27;
} CollisionActorTri;

typedef struct {
    CollisionActorTri *tri_start;
    CollisionActorTri *tri_end;
    s32 timestamp;
    u8 bbox[0x24 - 0xC];
    u8 flags;
    u8 unk25[2];
} ModelSlotTriBufferView;

typedef struct {
    u8 pad0[0x4F];
    u8 unk4F;
    u8 pad50[0x71 - 0x50];
    u8 unk71;
} ModelSlotHitFlagsView;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    u8 pad1C[0x24 - 0x1C];
    s32 *unk24;
    u8 pad28[0x48 - 0x28];
    ModelSlotTriBufferView unk48;
    void *unk70;
    u8 pad74[0x7C - 0x74];
    ModelSlotHitFlagsView *unk7C;
    u8 pad80[0x90 - 0x80];
} ModelSlotCollisionView;

typedef struct {
    u8 pad0[0x5C];
    u16 unk5C;
    u8 pad5E[0x78 - 0x5E];
    u8 unk78;
    u8 pad79[0x110 - 0x79];
    u8 unk110;
    u8 pad111[0x174 - 0x111];
    u8 *unk174;
} CollisionSlotActorView;

struct CollisionModelEntry;
struct CollisionBoundingBox;
struct CollisionTriF;

extern struct CollisionModelEntry *D_807F6000;
extern u8 D_807F946D;
extern u8 D_807F94AC;
s32 hashTableLookup();
void actorCheckNearbyNodeInteractions();
s32 collisionCheckBoundingBoxXZ(struct CollisionBoundingBox *, f32, f32);
s32 func_806D0964(s32, u8);
void modelSlotBuildTriangleBufferThunk(s32, void *, f32, f32, f32, f32, f32, f32, f32);
s32 collisionCheckTriangleBoundingBoxXZ(struct CollisionTriF *, f32, f32);
u8 func_80669E04(struct CollisionTriF *, f32, f32);
s32 collisionCheckSurfaceFilter(u8, u8 *);
void collisionRecordTriangleF(struct CollisionTriF *, f32);
s32 collisionCheckTriangleWindingF32(struct CollisionTriF *);
void collisionStoreTriangleNormalAnglesF32();
struct CollisionActorWork;
void collisionAttachActorToObjectNode(struct CollisionActorWork *, s16, s8, u8, f32, f32, f32);

#define MODEL_SLOT_ENTRIES ((ModelSlotCollisionView *)D_807F6000)

u8 func_80668E9C(CollisionSlotActorView *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 *arg5) {
    s32 pad;
    CollisionActorTri *tri_end;
    CollisionActorTri *hit_tri;
    CollisionActorTri *tri;
    f64 nx, ny, nz;
    f64 d;
    f64 dx01, dy01, dz01, dx02, dy02, dz02;
    f32 y;
    ModelSlotHitFlagsView *sub7C;
    f32 padB[8];
    f32 hit_y;
    u8 hit;
    s32 pad9C;
    s16 sp9A;
    s32 pad94;
    ModelSlotTriBufferView *sp90;
    s32 sp8C;
    s32 padLo[2];

    hit = 0;
    hit_y = 999999.0f;
    (void)2000.0; // FAKE: reserves the first 2000.0 rodata literal slot

    sp9A = hashTableLookup(arg1);
    if (sp9A == -1) {
        return 0;
    }

    sp90 = &MODEL_SLOT_ENTRIES[sp9A].unk48;
    if (arg0 != NULL && MODEL_SLOT_ENTRIES[sp9A].unk70 != NULL && D_807F946D != 0) {
        actorCheckNearbyNodeInteractions(arg0, sp9A, MODEL_SLOT_ENTRIES[sp9A].unk70);
    }

    if (!(sp90->flags & 4)) {
        return 0;
    }

    if (collisionCheckBoundingBoxXZ((struct CollisionBoundingBox *)sp90->bbox, arg2, arg3) == 0) {
        return 0;
    }

    if (D_807F94B3 != 0 && !(sp90->flags & 2)) {
        return 0;
    }

    sp8C = sp9A * 0x90;
    if (arg0 != NULL && (arg0->unk5C & 1)) {
        if (func_806D0964(*MODEL_SLOT_ENTRIES[sp9A].unk24, arg0->unk174[0x1A4]) != 0) {
            return 0;
        }
    }

    sub7C = MODEL_SLOT_ENTRIES[sp9A].unk7C;
    if (sub7C != NULL && sub7C->unk71 == 0) {
        return 0;
    }

    if (!(sp90->flags & 1)) {
        modelSlotBuildTriangleBufferThunk(sp9A, MODEL_SLOT_ENTRIES[sp9A].unk24,
            MODEL_SLOT_ENTRIES[sp9A].unk0, MODEL_SLOT_ENTRIES[sp9A].unk4, MODEL_SLOT_ENTRIES[sp9A].unk8,
            MODEL_SLOT_ENTRIES[sp9A].unk10, MODEL_SLOT_ENTRIES[sp9A].unk14, MODEL_SLOT_ENTRIES[sp9A].unk18,
            MODEL_SLOT_ENTRIES[sp9A].unkC);
    } else {
        sp90->timestamp = D_8076A064;
    }

    tri = sp90->tri_start;
    tri_end = sp90->tri_end;
    if (tri != tri_end) {
        do {
            if (collisionCheckTriangleBoundingBoxXZ((struct CollisionTriF *)tri, arg2, arg3) != 0 &&
                func_80669E04((struct CollisionTriF *)tri, arg2, arg3) != 0 &&
                collisionCheckSurfaceFilter(tri->unk27, sp90->unk25) != 0) {
                dx01 = (f64)(tri->x[0] - tri->x[1]);
                dy01 = (f64)(tri->y[0] - tri->y[1]);
                dz01 = (f64)(tri->z[0] - tri->z[1]);
                dx02 = (f64)(tri->x[0] - tri->x[2]);
                dy02 = (f64)(tri->y[0] - tri->y[2]);
                dz02 = (f64)(tri->z[0] - tri->z[2]);
                nx = (dy01 * dz02) - (dz01 * dy02);
                ny = (dz01 * dx02) - (dx01 * dz02);
                nz = (dx01 * dy02) - (dy01 * dx02);
                d = -((nx * (f64)tri->x[1]) + (ny * (f64)tri->y[1]) + (nz * (f64)tri->z[1]));
                if (0.01 < ny * 2000.0 || ny * 2000.0 < -0.01) {
                if (arg0 != NULL) {
                    y = (f32)((2000.0 * (0.0 - ((((f64)arg2 * nx) + (ny * -1000.0) + (nz * (f64)arg3) + d) / (ny * 2000.0)))) - 1000.0);
                    func_80666D88(arg4, y, 0, (Actor *)arg0, 0);
                    if (func_80666F04(arg4, y, 0, tri->unk24) != 0 && D_807F946D != 0) {
                        collisionAttachActorToObjectNode((struct CollisionActorWork *)arg0, sp9A, -1, 0, arg2, y, arg3);
                        arg0->unk110 = 2;
                    }
                }
                if (D_807F94BC != 0) {
                    collisionRecordTriangleF((struct CollisionTriF *)tri, (f32)((2000.0 * (0.0 - ((((f64)arg2 * nx) + (ny * -1000.0) + (nz * (f64)arg3) + d) / (ny * 2000.0)))) - 1000.0));
                }
                if (collisionCheckTriangleWindingF32((struct CollisionTriF *)tri) != 0) {
                    y = (f32)((2000.0 * (0.0 - ((((f64)arg2 * nx) + (ny * -1000.0) + (nz * (f64)arg3) + d) / (ny * 2000.0)))) - 1000.0);
                    if (mathCheckCloserFloatThreshold(hit_y, y, (f32)((f64)arg4 + 4.0), 0) != 0) {
                        hit_tri = tri;
                        hit = 1;
                        hit_y = y;
                    }
                }
                }
            }
            tri++;
        } while (tri != tri_end);
    }

    if (hit != 0 && mathCheckCloserFloatThreshold(*arg5, hit_y, (f32)((f64)arg4 + 4.0), 0) != 0) {
        *arg5 = hit_y;
        collisionStoreTriangleNormalAnglesF32(arg0, hit_tri, 1);
        sub7C = MODEL_SLOT_ENTRIES[sp9A].unk7C;
        if (sub7C != NULL && sub7C->unk4F != 0) {
            D_807F94AC = 1;
        }
        if (arg0 != NULL) {
            if (arg0->unk110 != 2 && arg0->unk110 != 3) {
                collisionAttachActorToObjectNode((struct CollisionActorWork *)arg0, sp9A, hit_tri->unk26, hit_tri->unk27, arg2, hit_y, arg3);
            }
            arg0->unk78 = hit_tri->unk25;
        }
        D_807F94B1 = hit_tri->unk25;
    }
    return hit;
}
