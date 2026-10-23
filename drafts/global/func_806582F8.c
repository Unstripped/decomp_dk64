// func_806582F8 (src/global/55B20.c): frame 0x88 and buffer/local layout match; remaining: arg1 spill vs s5, s7 cur-copy scheduling, &arg1[n*3] byte-pointer strength reduction
// func_806582F8: frame 0x88, local layout (sp7C at 0x7C, f64 locals y/z/d) and the
// whole loop body match; remaining diffs are regalloc/scheduling only:
// (a) target spills arg1 to its home slot 0x8C and keeps &sp7C in $s5, this draft keeps
// arg1 in $s5; (b) target copies cur to $s7 so the branch delay slot holds "prev = old cur"
// (this draft puts "move s1,s2" before "addiu s2,s2,12"); (c) target strength-reduces
// &arg1[n*3] to a byte pointer ($s0 += 0xC), this draft keeps the index and scales.
typedef struct M55P7Plane {
    /* 0x00 */ f64 unk0;
    /* 0x08 */ f64 unk8;
    /* 0x10 */ f64 unk10;
    /* 0x18 */ f64 unk18;
    /* 0x20 */ f64 unk20;
    /* 0x28 */ f64 unk28;
    /* 0x30 */ f64 unk30;
    /* 0x38 */ f64 unk38;
} M55P7Plane;

typedef struct R3dVec3 {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} R3dVec3;

void func_8065850C(f32 *, f32 *, s32, f32 *);

void func_806582F8(f32 *arg0, f32 *arg1, s32 arg2, s32 *arg3, s32 arg4) {
    f32 sp7C[3];
    M55P7Plane *plane;
    R3dVec3 *prev;
    R3dVec3 *cur;
    s32 n;
    s32 i;
    f64 y;
    f64 z;
    f64 d;

    n = 0;
    prev = (R3dVec3 *)&arg0[arg2 * 3] - 1;
    cur = (R3dVec3 *)arg0;
    plane = (M55P7Plane *)(D_807F5E68 + (arg4 << 6));
    for (i = 0; i < arg2; i++) {
        d = plane->unk38;
        y = d + (((plane->unk20 * cur->x) + (plane->unk28 * cur->y)) + (plane->unk30 * cur->z));
        z = d + (((plane->unk20 * prev->x) + (plane->unk28 * prev->y)) + (plane->unk30 * prev->z));
        if (y >= 0.0) {
            if (z >= 0.0) {
                memcpy(arg1 + n * 3, cur, 0xC);
                n++;
            } else {
                func_8065850C((f32 *)prev, (f32 *)cur, arg4, sp7C);
                memcpy(arg1 + n * 3, sp7C, 0xC);
                n++;
                memcpy(arg1 + n * 3, cur, 0xC);
                n++;
            }
        } else if (z >= 0.0) {
            func_8065850C((f32 *)prev, (f32 *)cur, arg4, sp7C);
            memcpy(arg1 + n * 3, sp7C, 0xC);
            n++;
        }
        prev = cur++;
    }
    *arg3 = n;
}
