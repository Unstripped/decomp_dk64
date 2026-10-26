// func_807255A8 (src/global/1295B0.c): Stage 4 (frame 0x60 exact, 354/356 opcodes, first 238 insns identical): zero const f0/a1 f12 right until det compare, then IDO folds (a1*b2-a2*b1)<0 into sp8<sp4 so det is not kept in f12 and half/y regs shift; target keeps c.lt.s det,zero. Zero variable or 'd3 = 0.0f' avoids the fold (score 1377) but shifts early allocation (a1 f0). 15 f32/s16 locals needed (d1/d2 = 7th/8th for sp44/sp40); div by two needs a var (two = 2.0f)
s32 func_807255A8(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, f32 *arg8, f32 *arg9) {
    f32 a1;
    f32 b1;
    f32 c1;
    f32 a2;
    f32 b2;
    f32 c2;
    f32 d1;
    f32 d2;
    f32 d3;
    f32 d4;
    f32 det;
    f32 half;
    f32 y;
    f32 two;
    s16 ix;

    a1 = arg3 - arg1;
    b1 = arg0 - arg2;
    c1 = arg2 * arg1 - arg0 * arg3;
    d3 = arg4 * a1 + b1 * arg5 + c1;
    d4 = arg6 * a1 + b1 * arg7 + c1;
    if (d3 != 0.0f && d4 != 0.0f && ((s32)((u32)d3 ^ (u32)d4)) >= 0) {
        return 0;
    }
    a2 = arg7 - arg5;
    b2 = arg4 - arg6;
    c2 = arg6 * arg5 - arg4 * arg7;
    d1 = arg0 * a2 + b2 * arg1 + c2;
    d2 = arg2 * a2 + b2 * arg3 + c2;
    if (d1 != 0.0f && d2 != 0.0f && ((s32)((u32)d1 ^ (u32)d2)) >= 0) {
        return 0;
    }
    if (a1 * b2 == a2 * b1) {
        return 2;
    }
    det = a1 * b2 - a2 * b1;
    two = 2.0f;
    if (det < 0.0f) {
        half = -det / two;
    } else {
        half = det / two;
    }
    if (b1 * c2 < b2 * c1) {
        *arg8 = ((b1 * c2 - b2 * c1) - half) / det;
    } else {
        *arg8 = ((b1 * c2 - b2 * c1) + half) / det;
    }
    if (a2 * c1 < a1 * c2) {
        y = ((a2 * c1 - a1 * c2) - half) / det;
    } else {
        y = ((a2 * c1 - a1 * c2) + half) / det;
    }
    *arg9 = y;
    ix = (s32)*arg8;
    if ((ix == arg0 && (s16)(s32)y == arg1) || (ix == arg2 && (s16)(s32)y == arg3) || (ix == arg4 && (s16)(s32)y == arg5) || (ix == arg6 && (s16)(s32)y == arg7)) {
        return 3;
    }
    return 1;
}
