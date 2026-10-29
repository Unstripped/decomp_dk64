// func_80668E9C (src/global/6AD90.c): stage 4: frame 0x130, saved s0/s1/ra+f20-f30, control flow equal; f32 spv[3] stack array reproduces the x1/y1/z1 store+reload. ~180 text diff lines, regalloc only: target colors fv0,fv1,fa0,x0,ft4,y0 in f0,f2,f12,f14,f16,f18 (ny f20, z0 f22, fs2/fs3 f24/f26, nx f30; nz/d caller-saved f0/f2 spilled 0x70/0x100 around calls); ours spills fs3 as an f4 temp and spills all three x1/y1/z1 reloads (target spills only x1 at 0x68). Tried: deadsweep (no gain), named/inline temp combos (2^13), decl-order+pad hill-climb, statement-order search, permuter 45k iters. Same near-miss shape as func_8066A08C.
typedef struct {
    f32 x[3];
    f32 y[3];
    f32 z[3];
    u8 unk24;
    u8 unk25;
    s8 unk26;
    u8 unk27;
} L668E9C_Tri;

typedef struct {
    L668E9C_Tri *tri_start;
    L668E9C_Tri *tri_end;
    s32 timestamp;
    u8 bbox[0x24 - 0xC];
    u8 flags;
    u8 unk25[2];
} L668E9C_Sub;

typedef struct {
    u8 pad0[0x4F];
    u8 unk4F;
    u8 pad50[0x71 - 0x50];
    u8 unk71;
} L668E9C_Sub7C;

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
    L668E9C_Sub unk48;
    void *unk70;
    u8 pad74[0x7C - 0x74];
    L668E9C_Sub7C *unk7C;
    u8 pad80[0x90 - 0x80];
} L668E9C_Entry;

typedef struct {
    u8 pad0[0x5C];
    u16 unk5C;
    u8 pad5E[0x78 - 0x5E];
    u8 unk78;
    u8 pad79[0x110 - 0x79];
    u8 unk110;
    u8 pad111[0x174 - 0x111];
    u8 *unk174;
} L668E9C_Actor;

struct CollisionModelEntry;
struct CollisionBoundingBox;
struct CollisionTriF;

extern struct CollisionModelEntry *D_807F6000;
extern u8 D_807F946D;
extern u8 D_807F94AC;
extern u8 D_807F94B1;
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

#define L668E9C_ENTRIES ((L668E9C_Entry *)D_807F6000)

u8 func_80668E9C(L668E9C_Actor *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 *arg5) {
    f64 ny;
    L668E9C_Tri *hit_tri;
    L668E9C_Sub *sp90;
    f32 pad1[1];
    f32 temp_ft5;
    L668E9C_Tri *tri;
    f64 temp_ft4;
    f64 nx;
    f64 nz;
    f32 pad2[4];
    f32 temp_fs1;
    s16 sp9A;
    f64 d;
    f64 temp_fa0;
    L668E9C_Sub7C *sub7C;
    f64 temp_fs2;
    f64 temp_fv1;
    f32 y;
    f64 temp_fv0;
    f32 hit_y;
    u8 hit;
    f32 temp_fa1;
    s32 sp8C;
    f64 temp_fs3;
    L668E9C_Tri *tri_end;
    f32 spv[3];

    hit = 0;
    hit_y = 999999.0f;
    (void)2000.0; // FAKE: reserves the first 2000.0 rodata literal slot

    sp9A = hashTableLookup(arg1);
    if (sp9A == -1) {
        return 0;
    }

    sp90 = &L668E9C_ENTRIES[sp9A].unk48;
    if (arg0 != NULL && L668E9C_ENTRIES[sp9A].unk70 != NULL && D_807F946D != 0) {
        actorCheckNearbyNodeInteractions(arg0, sp9A, L668E9C_ENTRIES[sp9A].unk70);
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
        if (func_806D0964(*L668E9C_ENTRIES[sp9A].unk24, arg0->unk174[0x1A4]) != 0) {
            return 0;
        }
    }

    sub7C = L668E9C_ENTRIES[sp9A].unk7C;
    if (sub7C != NULL && sub7C->unk71 == 0) {
        return 0;
    }

    if (!(sp90->flags & 1)) {
        modelSlotBuildTriangleBufferThunk(sp9A, L668E9C_ENTRIES[sp9A].unk24,
            L668E9C_ENTRIES[sp9A].unk0, L668E9C_ENTRIES[sp9A].unk4, L668E9C_ENTRIES[sp9A].unk8,
            L668E9C_ENTRIES[sp9A].unk10, L668E9C_ENTRIES[sp9A].unk14, L668E9C_ENTRIES[sp9A].unk18,
            L668E9C_ENTRIES[sp9A].unkC);
    } else {
        sp90->timestamp = D_8076A064;
    }

    tri = sp90->tri_start;
    tri_end = sp90->tri_end;
    if (tri != tri_end) {
        do {
            if (collisionCheckTriangleBoundingBoxXZ((struct CollisionTriF *)tri, arg2, arg3) != 0 &&
                func_80669E04((struct CollisionTriF *)tri, arg2, arg3) != 0 &&
                collisionCheckSurfaceFilter(tri->unk27, sp90->unk25) != 0 &&
                ((spv[2] = tri->x[1],
                  temp_fa1 = tri->x[0],
                  spv[1] = tri->y[1],
                  temp_ft5 = tri->y[0],
                  temp_fa0 = (f64)(temp_fa1 - spv[2]),
                  spv[0] = tri->z[1],
                  temp_ft4 = (f64)(temp_ft5 - spv[1]),
                  temp_fs1 = tri->z[0],
                  temp_fv0 = (f64)(temp_fs1 - spv[0]),
                  temp_fs2 = (f64)(temp_fa1 - tri->x[2]),
                  temp_fs3 = (f64)(temp_ft5 - tri->y[2]),
                  temp_fv1 = (f64)(temp_fs1 - tri->z[2]),
                  nx = (temp_ft4 * temp_fv1) - (temp_fv0 * temp_fs3),
                  ny = (temp_fv0 * temp_fs2) - (temp_fa0 * temp_fv1),
                  nz = (temp_fa0 * temp_fs3) - (temp_ft4 * temp_fs2),
                  d = -(((f64)spv[0] * nz) + ((nx * (f64)spv[2]) + (ny * (f64)spv[1]))),
                  0.01 < ny * 2000.0) || ny * 2000.0 < -0.01)) {
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
            tri++;
        } while (tri != tri_end);
    }

    if (hit != 0 && mathCheckCloserFloatThreshold(*arg5, hit_y, (f32)((f64)arg4 + 4.0), 0) != 0) {
        *arg5 = hit_y;
        collisionStoreTriangleNormalAnglesF32(arg0, hit_tri, 1);
        sub7C = L668E9C_ENTRIES[sp9A].unk7C;
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
