// func_806582F8 (src/global/55B20.c): stage 1: m2c-derived clip loop; target keeps prev in s1 and cur in s2 with s7 temp, out pointer s0 advanced per memcpy, plane in s4; double check y/z dot-product order and no outer 'if (arg2 > 0)' (for-loop pre-test only)
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

void func_8065850C(f32 *, f32 *, s32, f32 *);

void func_806582F8(f32 *arg0, f32 *arg1, s32 arg2, s32 *arg3, s32 arg4) {
    f32 sp7C[3];
    M55P7Plane *plane;
    f32 *prev;
    f32 *cur;
    s32 n;
    s32 i;
    f64 y;
    f64 z;

    n = 0;
    prev = &arg0[arg2 * 3 - 3];
    plane = (M55P7Plane *)(D_807F5E68 + (arg4 << 6));
    cur = arg0;
    for (i = 0; i < arg2; i++) {
        y = plane->unk38 + (((plane->unk20 * cur[0]) + (plane->unk28 * cur[1])) + (plane->unk30 * cur[2]));
        z = plane->unk38 + (((plane->unk20 * prev[0]) + (plane->unk28 * prev[1])) + (plane->unk30 * prev[2]));
        if (y >= 0.0) {
            if (z >= 0.0) {
                memcpy(&arg1[n * 3], cur, 0xC);
                n++;
            } else {
                func_8065850C(prev, cur, arg4, sp7C);
                memcpy(&arg1[n * 3], sp7C, 0xC);
                n++;
                memcpy(&arg1[n * 3], cur, 0xC);
                n++;
            }
        } else if (z >= 0.0) {
            func_8065850C(prev, cur, arg4, sp7C);
            memcpy(&arg1[n * 3], sp7C, 0xC);
            n++;
        }
        prev = cur;
        cur += 3;
    }
    *arg3 = n;
}
