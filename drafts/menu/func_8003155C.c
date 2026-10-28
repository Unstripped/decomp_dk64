// func_8003155C (src/menu/3E10.c): stage 3-4: frame 0x40 vs target 0x38; target idx*16 as two shifts (sll t7,s0,2 then sll v1,t7,2 / sll t0,t7,2 shared t7, folded to single sll 4 here); idx in s0 + ret slot sp30 and a3 spill sp28/t0 sp2C; 59 diff lines of ~160 (regalloc/frame), permuter 240s no gain
/* func_8003155C: ring item position/scale/alpha along spline tables */
typedef struct Menu10_Sel {
    f32 unk0;
    f32 unk4;
    char pad8[4];
    s16 unkC;
    char padE[9];
    s8 unk17;
} Menu10_Sel;

extern f32 D_8003373C[];
extern f32 D_8003378C[];
f32 menuEvaluateSpline(f32 *, f32, f32 *);

s32 func_8003155C(void *arg0, s32 arg1, f32 *arg2, f32 *arg3, f32 *arg4, s16 *arg5, s16 *arg6) {
    s32 idx;
    s32 ret;
    f32 *p;
    f32 *q;
    f32 temp;
    f32 v;

    idx = arg1 + ((Menu10_Sel *)arg0)->unk17;
    if (idx >= 5) {
        idx -= 5;
    }
    q = &D_8003378C[idx * 4];
    p = &D_8003373C[idx * 4];
    ret = idx;
    p[2] = -q[0];
    p[3] = -q[1];
    q[2] = p[0];
    q[3] = p[1];
    *arg2 = menuEvaluateSpline(&D_8003373C[idx * 4], ((Menu10_Sel *)arg0)->unk4, NULL);
    temp = menuEvaluateSpline(&D_8003378C[idx * 4], ((Menu10_Sel *)arg0)->unk4, NULL);
    *arg3 = temp;
    if (temp < -40.0f) {
        v = -*arg3 - 40.0f;
        if (v > 20.0f) {
            v = 20.0f;
        }
        *arg4 = (v / 60.0f) + 1.0f;
        *arg5 = (s32)(v * 6.2f) + 0x80;
    } else {
        *arg4 = 1.0f;
        *arg5 = 0x80;
    }
    *arg6 = 0xFF;
    if (p == D_8003373C) {
        *arg3 *= 1.0f - D_80033F3C;
        *arg4 += D_80033F3C * 3.5f;
        if (D_80033F3C != 0.0f) {
            *arg6 = 0xFF - (s32)(((Menu10_Sel *)arg0)->unk0 * 255.0f);
            if (*arg6 < 0) {
                *arg6 = 0;
            }
        }
    }
    *arg2 *= 4.0f + (((Menu10_Sel *)arg0)->unk0 * 4.0f);
    *arg3 *= 4.0f + (((Menu10_Sel *)arg0)->unk0 * 4.0f);
    *arg2 += 640.0f;
    *arg3 += 480.0f;
    return ret;
}
