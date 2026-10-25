// func_80715B30 (src/global/119370.c): Stage 3: complete matrix construction compiles. m2c identifies target locals in order angle/spF8, scale/spB4, transform/sp74, Mtx/sp30, mode/sp2C; this draft orders them accordingly for the next fdiff pass.
#include "common.h"
s32 func_80611E60(s32);
void func_80612CA0(f32 (*)[4], f32);
f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
f32 func_80715E38(f32, f32, f32, f32, f32, f32);
extern s16 D_807FDB34;

void func_80715B30(Mtx *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u8 arg10) {
    s32 angle;
    f32 scale[4][4];
    f32 transform[4][4];
    Mtx mtx;
    s32 mode;
    f32 distance;
    f32 value;
    f32 absValue;
    s32 temp;

    mode = arg1 & 0xFF;
    if (arg10 == 0) {
        distance = func_80715E38(arg4, arg5, arg6, arg7, arg8, arg9);
        value = distance;
        if ((f64)distance < 0.1) value = 1.0f;
        distance = (arg5 - arg8) / value;
        if (distance > 0.0f) absValue = distance; else absValue = -distance;
        temp = func_80611E60((s32)((f64)absValue * 65536.0)) >> 4;
        angle = temp;
        if (distance >= 0.0f) angle = 0xFFF - temp;
        if (mode != 2) guScaleF(scale, arg2, arg3, 0.0f); else guScaleF(scale, 1.0f, 1.0f, 1.0f);
        guRotateF(transform, (f32)(((f64)angle / 4095.0) * 360.0), 1.0f, 0.0f, 0.0f);
        guMtxCatF(scale, transform, scale);
        guRotateF(transform, mathAngleBetweenPointsRad(arg4, arg6, arg7, arg9) * 57.295776f, 0.0f, 1.0f, 0.0f);
        guMtxCatF(scale, transform, scale);
        guTranslateF(transform, arg7, arg8, arg9);
        guMtxCatF(scale, transform, scale);
    } else {
        if (mode != 2) guScaleF(scale, arg2, arg3, 0.0f); else guScaleF(scale, 1.0f, 1.0f, 1.0f);
        func_80612CA0(transform, (f32)D_807FDB34);
        guMtxCatF(scale, transform, scale);
        guTranslateF(transform, arg7, arg8, arg9);
        guMtxCatF(scale, transform, scale);
    }
    if ((mode == 1) || (mode == 2)) {
        guMtxF2L(scale, &mtx);
        guMtxCatL(arg0, &mtx, arg0);
    } else {
        guMtxF2L(scale, arg0);
    }
}
