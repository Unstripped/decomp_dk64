#include "common.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/7BBD0/func_80676ED0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7BBD0/func_80677148.s")

#include "actor.h"

typedef f32 Beh7BB_MtxF[4][4];

typedef struct Beh7BB_Struct_760C {
    u8 pad0[0x70];
    void *unk70;
    Mtx *unk74[2];
    u8 pad7C[0xC];
    s32 unk88;
} Beh7BB_Struct_760C;

extern u8 D_807444FC;
extern s32 D_8076A064;
void func_8067760C(Beh7BB_Struct_760C *arg0, Beh7BB_MtxF arg1, s8 arg2) {
    u8 var_v0;
    Mtx *mtx;

    if (D_8076A064 == arg0->unk88) {
        var_v0 = D_807444FC;
    } else {
        var_v0 = D_807444FC ^ 1;
    }
    mtx = arg0->unk74[var_v0];
    if (arg2 == -1) {
        memcpy(arg1, arg0->unk70, 0x40);
    } else {
        guMtxL2F(arg1, &mtx[arg2]);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7BBD0/func_806776A0.s")
typedef struct Beh7BB_Target {
    u8 pad0[0x48];
    s16 unk48;
    u8 pad4A[2];
    u8 unk4C;
} Beh7BB_Target;
extern Beh7BB_Target *D_807FB5D8;

s32 func_80677CAC(s16 arg0, s16 arg1) {
    s16 var_v0;
    s16 diff;

    var_v0 = D_807FB5D8->unk48;
    if (D_807FB5D8->unk4C != 0) {
        var_v0 -= 0x800;
    }
    if (var_v0 < 0) {
        var_v0 += 0x1000;
    }
    diff = var_v0 - arg0;
    if (diff < 0) {
        diff = -diff;
    }
    if (diff >= 0x801) {
        diff = 0xFFF - diff;
    }
    if (diff < arg1) {
        return 1;
    }
    return 0;
}

s32 func_80677D58(Actor *arg0) {
    return func_80677CAC(arg0->unkE6, 400);
}
