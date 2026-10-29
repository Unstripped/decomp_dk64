// func_80715B30 (src/global/119370.c): text-identical, reloc only: rodata dlabels (D_8075E6A0/A8/B0/B8) vs .rodata+addend; .rodata bytes verified identical. Permuter score 0 (mutation: value = mathAngleBetweenPointsRad(...) before guRotateF). Layout: f32 pad[2]; distance; value; absValue; angle; temp; scale; transform; Mtx mtx.
#include "common.h"
s32 func_80611E60(s32);
void matrixMakeRotationZ(f32 (*)[4], f32);
f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
f32 distance3D(f32, f32, f32, f32, f32, f32);

void func_80715B30(Mtx *arg0, u8 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u8 arg10) {
    f32 pad[2];
    f32 distance;
    f32 value;
    f32 absValue;
    s32 angle;
    s32 temp;
    f32 scale[4][4];
    f32 transform[4][4];
    Mtx mtx;

    if (arg10 == 0) {
        distance = distance3D(arg4, arg5, arg6, arg7, arg8, arg9);
        value = distance;
        if ((f64)distance < 0.1) {
            value = 1.0f;
        }
        distance = (arg5 - arg8) / value;
        if (distance > 0.0f) {
            absValue = distance;
        } else {
            absValue = -distance;
        }
        temp = func_80611E60((s32)((f64)absValue * 65536.0)) >> 4;
        angle = temp;
        if (distance >= 0.0f) {
            angle = 0xFFF - temp;
        }
        if (arg1 != 2) {
            guScaleF(scale, arg2, arg3, 0.0f);
        } else {
            guScaleF(scale, 1.0f, 1.0f, 1.0f);
        }
        guRotateF(transform, (f32)(((f64)angle / 4095.0) * 360.0), 1.0f, 0.0f, 0.0f);
        guMtxCatF(scale, transform, scale);
        value = mathAngleBetweenPointsRad(arg4, arg6, arg7, arg9);
        guRotateF(transform, value * 57.295776f, 0.0f, 1.0f, 0.0f);
        guMtxCatF(scale, transform, scale);
        guTranslateF(transform, arg7, arg8, arg9);
        guMtxCatF(scale, transform, scale);
    } else {
        if (arg1 != 2) {
            guScaleF(scale, arg2, arg3, 0.0f);
        } else {
            guScaleF(scale, 1.0f, 1.0f, 1.0f);
        }
        matrixMakeRotationZ(transform, (f32)D_807FDB34);
        guMtxCatF(scale, transform, scale);
        guTranslateF(transform, arg7, arg8, arg9);
        guMtxCatF(scale, transform, scale);
    }
    if ((arg1 == 1) || (arg1 == 2)) {
        guMtxF2L(scale, &mtx);
        guMtxCatL(arg0, &mtx, arg0);
    } else {
        guMtxF2L(scale, arg0);
    }
}
