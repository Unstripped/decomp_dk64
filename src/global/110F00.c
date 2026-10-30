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

void func_8070C2D8(Mat4F *arg0, Mat4F *arg1, Mat4F *arg2) {
    f32 t00;
    f32 t01;
    f32 t02;
    f32 t10;
    f32 t11;
    f32 t12;
    f32 t20;
    f32 t21;
    f32 t22;
    f32 t30;
    f32 t31;
    f32 t32;
    t00 = (arg0->m[0][0] * arg1->m[0][0]) + (arg0->m[0][1] * arg1->m[1][0]) + (arg0->m[0][2] * arg1->m[2][0]);
    t01 = (arg0->m[0][0] * arg1->m[0][1]) + (arg0->m[0][1] * arg1->m[1][1]) + (arg0->m[0][2] * arg1->m[2][1]);
    t02 = (arg0->m[0][0] * arg1->m[0][2]) + (arg0->m[0][1] * arg1->m[1][2]) + (arg0->m[0][2] * arg1->m[2][2]);
    t10 = (arg0->m[1][0] * arg1->m[0][0]) + (arg0->m[1][1] * arg1->m[1][0]) + (arg0->m[1][2] * arg1->m[2][0]);
    t11 = (arg0->m[1][0] * arg1->m[0][1]) + (arg0->m[1][1] * arg1->m[1][1]) + (arg0->m[1][2] * arg1->m[2][1]);
    t12 = (arg0->m[1][0] * arg1->m[0][2]) + (arg0->m[1][1] * arg1->m[1][2]) + (arg0->m[1][2] * arg1->m[2][2]);
    t20 = (arg0->m[2][0] * arg1->m[0][0]) + (arg0->m[2][1] * arg1->m[1][0]) + (arg0->m[2][2] * arg1->m[2][0]);
    t21 = (arg0->m[2][0] * arg1->m[0][1]) + (arg0->m[2][1] * arg1->m[1][1]) + (arg0->m[2][2] * arg1->m[2][1]);
    t22 = (arg0->m[2][0] * arg1->m[0][2]) + (arg0->m[2][1] * arg1->m[1][2]) + (arg0->m[2][2] * arg1->m[2][2]);
    t30 = (arg0->m[3][0] * arg1->m[0][0]) + (arg0->m[3][1] * arg1->m[1][0]) + (arg0->m[3][2] * arg1->m[2][0]) + arg1->m[3][0];
    t31 = (arg0->m[3][0] * arg1->m[0][1]) + (arg0->m[3][1] * arg1->m[1][1]) + (arg0->m[3][2] * arg1->m[2][1]) + arg1->m[3][1];
    t32 = (arg0->m[3][0] * arg1->m[0][2]) + (arg0->m[3][1] * arg1->m[1][2]) + (arg0->m[3][2] * arg1->m[2][2]) + arg1->m[3][2];
    arg2->m[0][0] = t00;
    arg2->m[1][0] = t10;
    arg2->m[2][0] = t20;
    arg2->m[3][0] = t30;
    arg2->m[0][1] = t01;
    arg2->m[1][1] = t11;
    arg2->m[2][1] = t21;
    arg2->m[3][1] = t31;
    arg2->m[0][2] = t02;
    arg2->m[1][2] = t12;
    arg2->m[2][2] = t22;
    arg2->m[3][2] = t32;
    arg2->m[0][3] = 0.0f;
    arg2->m[1][3] = 0.0f;
    arg2->m[2][3] = 0.0f;
    arg2->m[3][3] = 1.0f;
}

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

void func_8070C808(Mat4F *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 x = *arg1;
    f32 y = *arg2;
    f32 z = *arg3;
    f32 ox = ((x * arg0->m[0][0] + y * arg0->m[1][0]) + z * arg0->m[2][0]) + arg0->m[3][0];
    f32 oy = ((x * arg0->m[0][1] + y * arg0->m[1][1]) + z * arg0->m[2][1]) + arg0->m[3][1];
    f32 oz = ((x * arg0->m[0][2] + y * arg0->m[1][2]) + z * arg0->m[2][2]) + arg0->m[3][2];
    *arg1 = ox;
    *arg2 = oy;
    *arg3 = oz;
}

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

#ifdef NON_MATCHING
void func_8070CDD0(Mat4F *arg0, Mat4F *arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 padtop[4]; // FAKE: pad words steer the frame size
    f32 m00;
    f32 m10;
    f32 m20;
    f32 inv;
    f32 m11;
    f32 m21;
    f32 m02;
    f32 m12;
    f32 m22;

    if ((arg2 == 0.0f) && (arg4 == 0.0f)) {
        if (arg3 == 0.0f) {
            mtxIdentityF(arg0->m);
            mtxIdentityF(arg1->m);
            return;
        }
        m00 = 1.0f;
        m10 = 0.0f;
        m20 = 0.0f;
        m11 = 0.0f;
        m21 = -1.0f;
        m02 = 0.0f;
        m12 = 1.0f;
        m22 = 0.0f;
    } else {
        inv = 1.0 / sqrtf((arg2 * arg2) + (arg3 * arg3) + (arg4 * arg4));
        arg2 = arg2 * inv;
        arg3 = arg3 * inv;
        arg4 = arg4 * inv;
        m11 = sqrtf((arg2 * arg2) + (arg4 * arg4));
        inv = 1.0 / m11;
        m00 = -arg4 * inv;
        m22 = -arg4;
        m20 = -arg2;
        m10 = arg3 * (m20 * inv);
        m12 = arg3 * m00;
        m02 = -m20 * inv;
        m21 = -arg3;
    }
    arg0->m[0][0] = m00;
    arg0->m[1][0] = m10;
    arg0->m[2][0] = m20;
    arg0->m[3][0] = 0.0f;
    arg0->m[0][1] = 0.0f;
    arg0->m[1][1] = m11;
    arg0->m[2][1] = m21;
    arg0->m[3][1] = 0.0f;
    arg0->m[0][2] = m02;
    arg0->m[1][2] = m12;
    arg0->m[3][2] = 0.0f;
    arg0->m[0][3] = 0.0f;
    arg0->m[1][3] = 0.0f;
    arg0->m[2][3] = 0.0f;
    arg0->m[3][3] = 1.0f;
    arg0->m[2][2] = m22;
    arg1->m[0][0] = m00;
    arg1->m[1][0] = 0.0f;
    arg1->m[3][0] = 0.0f;
    arg1->m[0][1] = m10;
    arg1->m[1][1] = m11;
    arg1->m[2][0] = m02;
    arg1->m[3][1] = 0.0f;
    arg1->m[0][2] = m20;
    arg1->m[1][2] = m21;
    arg1->m[2][1] = m12;
    arg1->m[3][2] = 0.0f;
    arg1->m[0][3] = 0.0f;
    arg1->m[1][3] = 0.0f;
    arg1->m[2][3] = 0.0f;
    arg1->m[3][3] = 1.0f;
    arg1->m[2][2] = m22;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070CDD0.s")
#endif

void func_8070D020(Mtx *arg0, Mtx *arg1, f32 arg2, f32 arg3, f32 arg4) {
    Mat4F sp60;
    Mat4F sp20;

    func_8070CDD0(&sp60, &sp20, arg2, arg3, arg4);
    guMtxF2L(sp60.m, arg0);
    guMtxF2L(sp20.m, arg1);
}

#ifdef NON_MATCHING
void func_8070D07C(Mat4F *arg0, Mat4F *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 padtop[4]; // FAKE: pad words steer the frame size
    f32 m00;
    f32 m10;
    f32 m20;
    f32 inv;
    f32 m11;
    f32 m21;
    f32 m02;
    f32 m12;
    f32 m22;

    if ((arg2 == 0.0f) && (arg4 == 0.0f)) {
        if (arg3 == 0.0f) {
            mtxIdentityF(arg0->m);
            mtxIdentityF(arg1->m);
            return;
        }
        m00 = 1.0f;
        m10 = 0.0f;
        m20 = 0.0f;
        m11 = 0.0f;
        m21 = -1.0f;
        m02 = 0.0f;
        m12 = 1.0f;
        m22 = 0.0f;
    } else {
        inv = 1.0 / sqrtf((arg2 * arg2) + (arg3 * arg3) + (arg4 * arg4));
        arg2 = arg2 * inv;
        arg3 = arg3 * inv;
        arg4 = arg4 * inv;
        m11 = sqrtf((arg2 * arg2) + (arg4 * arg4));
        m22 = -arg4;
        inv = 1.0 / m11;
        m00 = -arg4 * inv;
        m21 = -arg3;
        m20 = -arg2;
        m10 = arg3 * (m20 * inv);
        m02 = -(m20 * inv);
        m12 = arg3 * m00;
    }
    arg0->m[0][0] = m00;
    arg0->m[3][0] = -arg5;
    arg0->m[1][0] = m10;
    arg0->m[2][0] = m20;
    arg0->m[3][1] = -arg6;
    arg0->m[0][1] = 0.0f;
    arg0->m[1][1] = m11;
    arg0->m[2][1] = m21;
    arg0->m[0][2] = m02;
    arg0->m[1][2] = m12;
    arg0->m[2][2] = m22;
    arg0->m[0][3] = 0.0f;
    arg0->m[3][3] = 1.0f;
    arg0->m[1][3] = 0.0f;
    arg0->m[2][3] = 0.0f;
    arg0->m[3][2] = -arg7;
    arg1->m[3][1] = (arg5 * m10) + (arg6 * m11) + (arg7 * m12);
    arg1->m[0][0] = m00;
    arg1->m[3][0] = (arg5 * m00) + (arg7 * m02);
    arg1->m[1][0] = 0.0f;
    arg1->m[2][0] = m02;
    arg1->m[0][1] = m10;
    arg1->m[1][1] = m11;
    arg1->m[2][1] = m12;
    arg1->m[0][2] = m20;
    arg1->m[1][2] = m21;
    arg1->m[2][2] = m22;
    arg1->m[0][3] = 0.0f;
    arg1->m[1][3] = 0.0f;
    arg1->m[3][3] = 1.0f;
    arg1->m[3][2] = (arg5 * m20) + (arg6 * m21) + (arg7 * m22);
    arg1->m[2][3] = 0.0f;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070D07C.s")
#endif

void func_8070D300(Mtx *arg0, Mtx *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    Mat4F sp68;
    Mat4F sp28;

    func_8070D07C(&sp68, &sp28, arg2, arg3, arg4, arg5, arg6, arg7);
    guMtxF2L(sp68.m, arg0);
    guMtxF2L(sp28.m, arg1);
}
