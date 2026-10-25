#include "common.h"
#include "actor.h"

typedef struct M110aMat {
    f32 m[4][4];
} M110aMat;

void func_8070CCC4();

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070C89C.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070C990.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070C9E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070CA2C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070CA70.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070CAB4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070CB2C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070CBA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070CC1C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070CC54.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070CC8C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070CCC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070CD14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070CD44.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070CD8C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070CDD0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070D020.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070D07C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/110F00/func_8070D300.s")
