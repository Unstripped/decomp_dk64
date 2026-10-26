#include "common.h"
#include "actor.h"

typedef struct Mat4F {
    f32 m[4][4];
} Mat4F;

void mtxIdentityF();
void func_8070CDD0(Mat4F *, Mat4F *, f32, f32, f32);
void func_8070D07C(Mat4F *, Mat4F *, f32, f32, f32, f32, f32, f32);

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070C200.s")

void mtxScaleTranslateF(Mat4F *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    mtxIdentityF(arg0);
    arg0->m[0][0] = arg1;
    arg0->m[1][1] = arg2;
    arg0->m[2][2] = arg3;
    arg0->m[3][3] = 1.0f;
    arg0->m[3][0] = arg4;
    arg0->m[3][1] = arg5;
    arg0->m[3][2] = arg6;
}

void mtxScaleTranslateL(Mtx *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    Mat4F sp28;

    mtxScaleTranslateF(&sp28, arg1, arg2, arg3, arg4, arg5, arg6);
    guMtxF2L(sp28.m, arg0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070C2D8.s")

void mtxMulAffineF(Mat4F *arg0, Mat4F *arg1, Mat4F *arg2) {
    arg2->m[0][0] = (arg0->m[0][0] * arg1->m[0][0]) + (arg0->m[0][1] * arg1->m[1][0]) + (arg0->m[0][2] * arg1->m[2][0]);
    arg2->m[0][1] = (arg0->m[0][0] * arg1->m[0][1]) + (arg0->m[0][1] * arg1->m[1][1]) + (arg0->m[0][2] * arg1->m[2][1]);
    arg2->m[0][2] = (arg0->m[0][0] * arg1->m[0][2]) + (arg0->m[0][1] * arg1->m[1][2]) + (arg0->m[0][2] * arg1->m[2][2]);
    arg2->m[1][0] = (arg0->m[1][0] * arg1->m[0][0]) + (arg0->m[1][1] * arg1->m[1][0]) + (arg0->m[1][2] * arg1->m[2][0]);
    arg2->m[1][1] = (arg0->m[1][0] * arg1->m[0][1]) + (arg0->m[1][1] * arg1->m[1][1]) + (arg0->m[1][2] * arg1->m[2][1]);
    arg2->m[1][2] = (arg0->m[1][0] * arg1->m[0][2]) + (arg0->m[1][1] * arg1->m[1][2]) + (arg0->m[1][2] * arg1->m[2][2]);
    arg2->m[2][0] = (arg0->m[2][0] * arg1->m[0][0]) + (arg0->m[2][1] * arg1->m[1][0]) + (arg0->m[2][2] * arg1->m[2][0]);
    arg2->m[2][1] = (arg0->m[2][0] * arg1->m[0][1]) + (arg0->m[2][1] * arg1->m[1][1]) + (arg0->m[2][2] * arg1->m[2][1]);
    arg2->m[2][2] = (arg0->m[2][0] * arg1->m[0][2]) + (arg0->m[2][1] * arg1->m[1][2]) + (arg0->m[2][2] * arg1->m[2][2]);
    arg2->m[3][0] = (arg0->m[3][0] * arg1->m[0][0]) + (arg0->m[3][1] * arg1->m[1][0]) + (arg0->m[3][2] * arg1->m[2][0]) + arg1->m[3][0];
    arg2->m[3][1] = (arg0->m[3][0] * arg1->m[0][1]) + (arg0->m[3][1] * arg1->m[1][1]) + (arg0->m[3][2] * arg1->m[2][1]) + arg1->m[3][1];
    arg2->m[3][2] = (arg0->m[3][0] * arg1->m[0][2]) + (arg0->m[3][1] * arg1->m[1][2]) + (arg0->m[3][2] * arg1->m[2][2]) + arg1->m[3][2];
    arg2->m[0][3] = 0.0f;
    arg2->m[1][3] = 0.0f;
    arg2->m[2][3] = 0.0f;
    arg2->m[3][3] = 1.0f;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070C808.s")

void mtxRotateXRatioF(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3) {
    f32 temp_fv1;
    f32 temp_fv0;

    mtxIdentityF(arg0);
    temp_fv0 = arg1 / arg3;
    arg0[1][1] = temp_fv0;
    temp_fv1 = arg2 / arg3;
    if (temp_fv1) {
    }
    arg0[2][2] = temp_fv0;
    arg0[1][2] = temp_fv1;
    arg0[2][1] = -temp_fv1;
}

void mtxRotateYRatioF(Mat4F *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 var_fv0;
    f32 var_fv1;

    var_fv0 = arg2 / arg3;
    var_fv1 = arg1 / arg3;
    if ((f64)arg2 == 0.0) {
        var_fv0 = 0.0f;
    }
    if ((f64)arg1 == 0.0) {
        var_fv1 = 0.0f;
    }
    mtxIdentityF(arg0);
    arg0->m[2][0] = var_fv0;
    arg0->m[0][2] = -var_fv0;
    arg0->m[0][0] = var_fv1;
    arg0->m[2][2] = var_fv1;
}

f32 sinApprox(f32);
f32 cosApprox(f32);
void mtxRotateXRatioF(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3);

void mtxIdentityF(f32 arg0[4][4]);
void mtxRotateZRatioF(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3);

void mtxRotateZRatioF(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3) {
    f32 temp_fv0;
    f32 temp_fv1;

    mtxIdentityF(arg0);
    temp_fv0 = arg1 / arg3;
    temp_fv1 = temp_fv0;
    arg0[0][0] = temp_fv1;
    if (1) {
        temp_fv0 = arg2 / arg3;
        arg0[0][1] = temp_fv0;
        arg0[1][0] = -temp_fv0;
    }
    arg0[1][1] = temp_fv1;
}

void mtxRotateXRatioL(Mtx *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp18[4][4];

    mtxRotateXRatioF(sp18, arg1, arg2, arg3);
    guMtxF2L(sp18, arg0);
}

void mtxRotateYRatioL(Mtx *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp18[4][4];

    mtxRotateYRatioF((Mat4F *)sp18, arg1, arg2, arg3);
    guMtxF2L(sp18, arg0);
}

void mtxRotateZRatioL(Mtx *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp18[4][4];

    mtxRotateZRatioF(sp18, arg1, arg2, arg3);
    guMtxF2L(sp18, arg0);
}

void mtxRotateXDegF(f32 arg0[4][4], f32 arg1) {
    f32 temp;
    f32 sin;
    f32 cos;

    temp = arg1 * 0.0174532925199432955;
    sin = sinApprox(temp);
    cos = cosApprox(temp);
    mtxIdentityF(arg0);
    arg0[1][2] = sin;
    arg0[2][1] = -sin;
    arg0[1][1] = cos;
    arg0[2][2] = cos;
}

void mtxRotateYDegF(f32 arg0[4][4], f32 arg1) {
    f32 temp;
    f32 sin;
    f32 cos;

    temp = arg1 * 0.0174532925199432955;
    sin = sinApprox(temp);
    cos = cosApprox(temp);
    mtxIdentityF(arg0);
    arg0[2][0] = sin;
    arg0[0][2] = -sin;
    arg0[0][0] = cos;
    arg0[2][2] = cos;
}

void mtxRotateZDegF(f32 arg0[4][4], f32 arg1) {
    f32 temp;
    f32 sin;
    f32 cos;

    temp = arg1 * 0.0174532925199432955;
    sin = sinApprox(temp);
    cos = cosApprox(temp);
    mtxIdentityF(arg0);
    arg0[0][1] = sin;
    arg0[1][0] = -sin;
    arg0[0][0] = cos;
    arg0[1][1] = cos;
}

void mtxRotateXDegL(Mtx *arg0, f32 arg1) {
    f32 sp18[4][4];

    mtxRotateXDegF(sp18, arg1);
    guMtxF2L(sp18, arg0);
}

void mtxRotateYDegL(Mtx *arg0, f32 arg1) {
    f32 sp18[4][4];

    mtxRotateYDegF(sp18, arg1);
    guMtxF2L(sp18, arg0);
}

void mtxRotateZDegL(Mtx *arg0, f32 arg1) {
    f32 sp18[4][4];

    mtxRotateZDegF(sp18, arg1);
    guMtxF2L(sp18, arg0);
}

void mtxIdentityF(f32 arg0[4][4]) {
    f32 one;
    f32 zero;
    s32 index;

    one = 1.0f;
    zero = 0.0f;
    if (one) {
    }
    arg0[1][0] = zero;
    arg0[2][0] = zero;
    arg0[3][0] = zero;
    arg0[0][1] = zero;
    arg0[2][1] = zero;
    arg0[3][1] = zero;
    arg0[0][2] = zero;
    arg0[1][2] = zero;
    arg0[3][2] = zero;
    arg0[0][3] = zero;
    arg0[1][3] = zero;
    arg0[2][3] = zero;
    index = 2;
    arg0[0][0] = one;
    arg0[1][1] = one;
    arg0[2][index] = one;
    arg0[3][3] = one;
}

void mtxIdentityL(Mtx *arg0) {
    f32 sp18[4][4];

    mtxIdentityF(sp18);
    guMtxF2L(sp18, arg0);
}

void mtxTranslateF(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3) {
    mtxIdentityF(arg0);
    arg0[3][0] = arg1;
    arg0[3][1] = arg2;
    arg0[3][2] = arg3;
}

void mtxTranslateL(Mtx *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp18[4][4];

    mtxTranslateF(sp18, arg1, arg2, arg3);
    guMtxF2L(sp18, arg0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070CDD0.s")

void func_8070D020(Mtx *arg0, Mtx *arg1, f32 arg2, f32 arg3, f32 arg4) {
    Mat4F sp60;
    Mat4F sp20;

    func_8070CDD0(&sp60, &sp20, arg2, arg3, arg4);
    guMtxF2L(sp60.m, arg0);
    guMtxF2L(sp20.m, arg1);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070D07C.s")

void func_8070D300(Mtx *arg0, Mtx *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    Mat4F sp68;
    Mat4F sp28;

    func_8070D07C(&sp68, &sp28, arg2, arg3, arg4, arg5, arg6, arg7);
    guMtxF2L(sp68.m, arg0);
    guMtxF2L(sp28.m, arg1);
}
