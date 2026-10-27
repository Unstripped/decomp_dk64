// func_80668E9C (src/global/6AD90.c): 423 vs 443 insns (delta 20); exact 0x130 frame, exact 9 saved regs, prologue/epilogue/control flow match; rodata matched with (void)2000.0; same near-miss as func_8066A08C
typedef struct {
    f32 minX;
    f32 minY;
    f32 minZ;
    f32 maxX;
    f32 maxY;
    f32 maxZ;
} R5L_BoundingBox;

typedef struct {
    f32 x[3];
    f32 y[3];
    f32 z[3];
    u8 unk24;
    u8 unk25;
    s8 unk26;
    u8 unk27;
} R5L_Triangle;

typedef struct {
    R5L_Triangle *tri_start;
    R5L_Triangle *tri_end;
    s32 timestamp;
    R5L_BoundingBox bbox;
    u8 flags;
    u8 unk25[2];
} R5L_Sub48;

typedef struct {
    u8 pad0[0x4F];
    u8 unk4F;
    u8 pad50[0x71 - 0x50];
    u8 unk71;
} R5L_Sub7C;

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
    R5L_Sub48 unk48;
    void *unk70;
    u8 pad74[0x7C - 0x74];
    R5L_Sub7C *unk7C;
    u8 pad80[0x90 - 0x80];
} R5L_MeshEntry;

typedef struct {
    u8 pad0[0x5C];
    u16 unk5C;
    u8 pad5E[0x78 - 0x5E];
    u8 unk78;
    u8 pad79[0x110 - 0x79];
    u8 unk110;
    u8 pad111[0x174 - 0x111];
    void *unk174;
} R5L_Actor;

struct R3Q_D_807F6000;
struct R3Q_Actor;
struct R1C_TriangleF;
struct R1C_BoundingBox;

extern struct R3Q_D_807F6000 *D_807F6000;
extern u8 D_807F946D;
extern u8 D_807F94AC;
extern u8 D_807F94B1;
extern u8 D_807F94B3;
extern u8 D_807F94BC;
extern s32 D_8076A064;

s32 func_80659470(s32);
void func_806696A0();
s32 func_80669BE8(struct R1C_BoundingBox *, f32, f32);
s32 func_806D0964(s32, u8);
void modelSlotBuildTriangleBufferThunk(s16, s32 *, f32, f32, f32, f32, f32, f32, f32);
s32 func_80669CB4(struct R1C_TriangleF *, f32, f32);
s32 func_80669E04(struct R1C_TriangleF *, f32, f32);
s32 func_80669650(u8, u8 *);
void func_80666D88(f32, f32, s32, void *, s32);
s32 func_80666F04(f32, f32, s32, u8);
void func_806699C4(struct R3Q_Actor *, s16, s8, s8, f32, f32, f32);
void func_80669588(struct R1C_TriangleF *, f32);
s32 func_80669930(struct R1C_TriangleF *);
void func_80669830();
s32 func_80666FC8(f32, f32, f32, u8);

#define MESH_ENTRIES ((R5L_MeshEntry *)D_807F6000)

u8 func_80668E9C(R5L_Actor *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 *arg5) {
    f32 pad;
    R5L_Triangle *tri_end;
    R5L_Triangle *hit_tri;
    f32 pad2[5];
    f64 sp100;
    f32 hit_y;
    u8 hit;
    s16 sp9A;
    R5L_Sub48 *sp90;
    s32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f64 sp70;
    f32 sp68;
    R5L_Triangle *tri;
    f32 temp_fa1;
    f32 temp_fs1;
    f32 temp_ft5;
    f64 temp_fa0;
    f64 temp_ft4;
    f64 temp_fv0;
    f64 temp_fs2;
    f64 temp_fs3;
    f64 temp_fv1;
    f64 nx;
    f64 ny;
    f64 nz;
    f64 d;
    f32 y;
    R5L_Sub7C *sub7C;

    hit = 0;
    hit_y = 999999.0f;
    (void)2000.0;

    sp9A = func_80659470(arg1);
    if (sp9A == -1) {
        return 0;
    }

    sp90 = &MESH_ENTRIES[sp9A].unk48;
    if (arg0 != NULL && MESH_ENTRIES[sp9A].unk70 != NULL && D_807F946D != 0) {
        func_806696A0(arg0, sp9A, MESH_ENTRIES[sp9A].unk70);
    }

    if (!(sp90->flags & 4)) {
        return 0;
    }

    if (func_80669BE8((struct R1C_BoundingBox *)&sp90->bbox, arg2, arg3) == 0) {
        return 0;
    }

    if (D_807F94B3 != 0 && !(sp90->flags & 2)) {
        return 0;
    }

    sp8C = sp9A * 0x90;
    if (arg0 != NULL && (arg0->unk5C & 1)) {
        if (func_806D0964(*MESH_ENTRIES[sp9A].unk24, ((u8 *)arg0->unk174)[0x1A4]) != 0) {
            return 0;
        }
    }

    sub7C = MESH_ENTRIES[sp9A].unk7C;
    if (sub7C != NULL && sub7C->unk71 == 0) {
        return 0;
    }

    if (!(sp90->flags & 1)) {
        modelSlotBuildTriangleBufferThunk(sp9A, MESH_ENTRIES[sp9A].unk24,
            MESH_ENTRIES[sp9A].unk0, MESH_ENTRIES[sp9A].unk4, MESH_ENTRIES[sp9A].unk8,
            MESH_ENTRIES[sp9A].unk10, MESH_ENTRIES[sp9A].unk14, MESH_ENTRIES[sp9A].unk18,
            MESH_ENTRIES[sp9A].unkC);
    } else {
        sp90->timestamp = D_8076A064;
    }

    tri = sp90->tri_start;
    tri_end = sp90->tri_end;
    if (tri != tri_end) {
        do {
            if (func_80669CB4((struct R1C_TriangleF *)tri, arg2, arg3) != 0 &&
                func_80669E04((struct R1C_TriangleF *)tri, arg2, arg3) != 0 &&
                func_80669650(tri->unk27, sp90->unk25) != 0 &&
                ((sp88 = tri->x[1],
                  temp_fa1 = tri->x[0],
                  sp84 = tri->y[1],
                  temp_ft5 = tri->y[0],
                  temp_fa0 = (f64)(temp_fa1 - sp88),
                  sp80 = tri->z[1],
                  temp_ft4 = (f64)(temp_ft5 - sp84),
                  temp_fs1 = tri->z[0],
                  temp_fv0 = (f64)(temp_fs1 - sp80),
                  temp_fs2 = (f64)(temp_fa1 - tri->x[2]),
                  temp_fs3 = (f64)(temp_ft5 - tri->y[2]),
                  sp68 = sp88,
                  temp_fv1 = (f64)(temp_fs1 - tri->z[2]),
                  nx = (temp_ft4 * temp_fv1) - (temp_fv0 * temp_fs3),
                  ny = (temp_fv0 * temp_fs2) - (temp_fa0 * temp_fv1),
                  nz = (temp_fa0 * temp_fs3) - (temp_ft4 * temp_fs2),
                  d = -(((f64)sp80 * nz) + ((nx * (f64)sp68) + (ny * (f64)sp84))),
                  0.01 < ny * 2000.0) || ny * 2000.0 < -0.01)) {
                if (arg0 != NULL) {
                    y = (f32)((2000.0 * (0.0 - ((((f64)arg2 * nx) + (ny * -1000.0) + (nz * (f64)arg3) + d) / (ny * 2000.0)))) - 1000.0);
                    func_80666D88(arg4, y, 0, arg0, 0);
                    if (func_80666F04(arg4, y, 0, tri->unk24) != 0 && D_807F946D != 0) {
                        func_806699C4((struct R3Q_Actor *)arg0, sp9A, -1, 0, arg2, y, arg3);
                        arg0->unk110 = 2;
                    }
                }
                if (D_807F94BC != 0) {
                    func_80669588((struct R1C_TriangleF *)tri, (f32)((2000.0 * (0.0 - ((((f64)arg2 * nx) + (ny * -1000.0) + (nz * (f64)arg3) + d) / (ny * 2000.0)))) - 1000.0));
                }
                if (func_80669930((struct R1C_TriangleF *)tri) != 0) {
                    y = (f32)((2000.0 * (0.0 - ((((f64)arg2 * nx) + (ny * -1000.0) + (nz * (f64)arg3) + d) / (ny * 2000.0)))) - 1000.0);
                    if (func_80666FC8(hit_y, y, (f32)((f64)arg4 + 4.0), 0) != 0) {
                        hit_tri = tri;
                        hit = 1;
                        hit_y = y;
                    }
                }
            }
            tri++;
        } while (tri != tri_end);
    }

    if (hit != 0 && func_80666FC8(*arg5, hit_y, (f32)((f64)arg4 + 4.0), 0) != 0) {
        *arg5 = hit_y;
        func_80669830(arg0, hit_tri, 1);
        sub7C = MESH_ENTRIES[sp9A].unk7C;
        if (sub7C != NULL && sub7C->unk4F != 0) {
            D_807F94AC = 1;
        }
        if (arg0 != NULL) {
            if (arg0->unk110 != 2 && arg0->unk110 != 3) {
                func_806699C4((struct R3Q_Actor *)arg0, sp9A, hit_tri->unk26, hit_tri->unk27, arg2, hit_y, arg3);
            }
            arg0->unk78 = hit_tri->unk25;
        }
        D_807F94B1 = hit_tri->unk25;
    }
    return hit;
}
