#include "common.h"
#include "actor.h"

typedef struct M110aMat {
    f32 m[4][4];
} M110aMat;

void func_8070CCC4();
void func_8070CDD0(M110aMat *, M110aMat *, f32, f32, f32);
void func_8070D07C(M110aMat *, M110aMat *, f32, f32, f32, f32, f32, f32);

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070C200.s")

void func_8070C210(M110aMat *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    func_8070CCC4(arg0);
    arg0->m[0][0] = arg1;
    arg0->m[1][1] = arg2;
    arg0->m[2][2] = arg3;
    arg0->m[3][3] = 1.0f;
    arg0->m[3][0] = arg4;
    arg0->m[3][1] = arg5;
    arg0->m[3][2] = arg6;
}

void func_8070C27C(Mtx *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    M110aMat sp28;

    func_8070C210(&sp28, arg1, arg2, arg3, arg4, arg5, arg6);
    guMtxF2L(sp28.m, arg0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070C2D8.s")

void func_8070C590(M110aMat *arg0, M110aMat *arg1, M110aMat *arg2) {
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

void func_8070C89C(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3) {
    f32 temp_fv1;
    f32 temp_fv0;

    func_8070CCC4(arg0);
    temp_fv0 = arg1 / arg3;
    arg0[1][1] = temp_fv0;
    temp_fv1 = arg2 / arg3;
    if (temp_fv1) {
    }
    arg0[2][2] = temp_fv0;
    arg0[1][2] = temp_fv1;
    arg0[2][1] = -temp_fv1;
}

void func_8070C8F4(M110aMat *arg0, f32 arg1, f32 arg2, f32 arg3) {
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
    func_8070CCC4(arg0);
    arg0->m[2][0] = var_fv0;
    arg0->m[0][2] = -var_fv0;
    arg0->m[0][0] = var_fv1;
    arg0->m[2][2] = var_fv1;
}

f32 func_80612D1C(f32);
f32 func_80612D10(f32);
void func_8070C89C(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3);

void func_8070CCC4(f32 arg0[4][4]);
void func_8070C990(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3);

void func_8070C990(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3) {
    f32 temp_fv0;
    f32 temp_fv1;

    func_8070CCC4(arg0);
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

void func_8070C9E8(Mtx *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp18[4][4];

    func_8070C89C(sp18, arg1, arg2, arg3);
    guMtxF2L(sp18, arg0);
}

void func_8070CA2C(Mtx *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp18[4][4];

    func_8070C8F4((M110aMat *)sp18, arg1, arg2, arg3);
    guMtxF2L(sp18, arg0);
}

void func_8070CA70(Mtx *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp18[4][4];

    func_8070C990(sp18, arg1, arg2, arg3);
    guMtxF2L(sp18, arg0);
}

void func_8070CAB4(f32 arg0[4][4], f32 arg1) {
    f32 temp;
    f32 sin;
    f32 cos;

    temp = arg1 * 0.0174532925199432955;
    sin = func_80612D1C(temp);
    cos = func_80612D10(temp);
    func_8070CCC4(arg0);
    arg0[1][2] = sin;
    arg0[2][1] = -sin;
    arg0[1][1] = cos;
    arg0[2][2] = cos;
}

void func_8070CB2C(f32 arg0[4][4], f32 arg1) {
    f32 temp;
    f32 sin;
    f32 cos;

    temp = arg1 * 0.0174532925199432955;
    sin = func_80612D1C(temp);
    cos = func_80612D10(temp);
    func_8070CCC4(arg0);
    arg0[2][0] = sin;
    arg0[0][2] = -sin;
    arg0[0][0] = cos;
    arg0[2][2] = cos;
}

void func_8070CBA4(f32 arg0[4][4], f32 arg1) {
    f32 temp;
    f32 sin;
    f32 cos;

    temp = arg1 * 0.0174532925199432955;
    sin = func_80612D1C(temp);
    cos = func_80612D10(temp);
    func_8070CCC4(arg0);
    arg0[0][1] = sin;
    arg0[1][0] = -sin;
    arg0[0][0] = cos;
    arg0[1][1] = cos;
}

void func_8070CC1C(Mtx *arg0, f32 arg1) {
    f32 sp18[4][4];

    func_8070CAB4(sp18, arg1);
    guMtxF2L(sp18, arg0);
}

void func_8070CC54(Mtx *arg0, f32 arg1) {
    f32 sp18[4][4];

    func_8070CB2C(sp18, arg1);
    guMtxF2L(sp18, arg0);
}

void func_8070CC8C(Mtx *arg0, f32 arg1) {
    f32 sp18[4][4];

    func_8070CBA4(sp18, arg1);
    guMtxF2L(sp18, arg0);
}

void func_8070CCC4(f32 arg0[4][4]) {
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

void func_8070CD14(Mtx *arg0) {
    f32 sp18[4][4];

    func_8070CCC4(sp18);
    guMtxF2L(sp18, arg0);
}

void func_8070CD44(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3) {
    func_8070CCC4(arg0);
    arg0[3][0] = arg1;
    arg0[3][1] = arg2;
    arg0[3][2] = arg3;
}

void func_8070CD8C(Mtx *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp18[4][4];

    func_8070CD44(sp18, arg1, arg2, arg3);
    guMtxF2L(sp18, arg0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070CDD0.s")

void func_8070D020(Mtx *arg0, Mtx *arg1, f32 arg2, f32 arg3, f32 arg4) {
    M110aMat sp60;
    M110aMat sp20;

    func_8070CDD0(&sp60, &sp20, arg2, arg3, arg4);
    guMtxF2L(sp60.m, arg0);
    guMtxF2L(sp20.m, arg1);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070D07C.s")

void func_8070D300(Mtx *arg0, Mtx *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    M110aMat sp68;
    M110aMat sp28;

    func_8070D07C(&sp68, &sp28, arg2, arg3, arg4, arg5, arg6, arg7);
    guMtxF2L(sp68.m, arg0);
    guMtxF2L(sp28.m, arg1);
}
