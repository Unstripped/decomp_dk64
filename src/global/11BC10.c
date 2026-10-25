#include "common.h"
#include "actor.h"

extern u8 D_807444FC;
extern u32 D_8076A064;
extern s32 D_8076A0A8;
extern Actor *D_807FBB4C;

void *func_80610FE8(s32);
u32 func_806119A0(void);
f32 func_806119FC(void);
s32 func_80611A44(void);
f32 func_80612790(s16);
f32 func_80612794(s16);
f32 func_80612D10(f32);
f32 func_80612D1C(f32);

typedef struct {
    u8 pad0[0x32C];
    u8 unk32C;
    u8 pad32D[0x13];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x10];
    s32 unk35C;
    f32 unk360;
    f32 unk364;
    u8 pad368[0x1C];
    void *unk384;
} Ub1ActorView;

void func_80716F10(Ub1ActorView *arg0, void *arg1) {
    f32 sp68[4][4];
    f32 sp28[4][4];

    guScaleF(sp68, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp28, (f32)arg0->unk35C, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp68, sp28, sp68);
    guMtxF2L(sp68, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    arg0->unk32C = 2;
}

typedef struct {
    f32 unk0;
    f32 unk4;
} Ub1Rotation;

void func_80716FB4(Ub1ActorView *arg0, void *arg1) {
    f32 sp70[4][4];
    f32 sp30[4][4];
    Ub1Rotation *var_v1;

    var_v1 = (Ub1Rotation *)arg0->unk384;
    if (var_v1 == NULL) {
        arg0->unk384 = func_80610FE8(8);
        ((Ub1Rotation *)arg0->unk384)->unk0 = (func_806119A0() % 36000U) / 100U;
        ((Ub1Rotation *)arg0->unk384)->unk4 = (func_806119A0() % 400U) / 100U;
        var_v1 = (Ub1Rotation *)arg0->unk384;
    }
    var_v1->unk0 += var_v1->unk4;
    guScaleF(sp70, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp30, ((Ub1Rotation *)arg0->unk384)->unk0, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp70, sp30, sp70);
    guMtxF2L(sp70, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    arg0->unk32C = 2;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717100.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071720C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717404.s")

void func_80714950(s32);
void func_80717404();
void func_8071498C(void *);
void func_807149B8(s32);
void func_80714CC0(s32, f32, f32, f32, f32);
extern s32 D_8074E880[];

void func_80717760(Ub1ActorView *arg0, u8 *arg1) {
    s32 temp_v0;

    temp_v0 = arg0->unk35C;
    *((u8 *)arg0 + 0x36D) = 0;
    if (temp_v0 != 0) {
        arg0->unk35C = temp_v0 - 1;
        func_807149B8(1);
        func_8071498C(func_80717404);
        func_80714950(0xA);
        func_80714CC0(D_8074E880[((func_80611A44() >> 0xF) % 1000) % 3], 0.8f, arg0->unk340, arg0->unk344, arg0->unk348);
        return;
    }
    *arg1 = 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717814.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717930.s")

typedef struct {
    u8 pad0[0x330];
    void *unk330;
    u8 pad334[4];
    void *unk338;
    u8 pad33C[4];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    s16 unk34C;
    u8 pad34E[2];
    u8 unk350;
    u8 pad351[0xB];
    s32 unk35C;
    f32 unk360;
    f32 unk364;
    u8 pad368[5];
    u8 unk36D;
    u8 pad36E[0x16];
    void *unk384;
} Ub2ActorView;


void func_80714998(s32);
void func_80718380();
extern u8 D_8071FEF4;

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717B64.s")

void func_80717CE8(arg0, arg1)
Ub2ActorView *arg0;
s8 *arg1;
{
    if (arg0->unk36D != 0xFF) {
        arg0->unk36D += 0x14;
    }
    if ((s32) arg0->unk36D >= 0xEB) {
        arg0->unk36D = 0xFFU;
    }
    arg0->unk344 = (f32) ((f64) arg0->unk344 - ((f64) arg0->unk35C / 100.0));
}

void func_80717D4C(arg0, arg1)
Ub2ActorView *arg0;
s8 *arg1;
{
    arg0->unk344 = (f32) ((f64) arg0->unk344 - ((f64) arg0->unk35C / 100.0));
}

void func_80717D84(Ub2ActorView *arg0, s8 *arg1) {
    s32 temp_v0;
    u8 temp_v1;

    temp_v0 = arg0->unk35C;
    temp_v1 = arg0->unk36D;
    if (temp_v0 < (s32) temp_v1) {
        arg0->unk36D = (u8) (temp_v1 - temp_v0);
        return;
    }
    arg0->unk36D = 0U;
    *arg1 = 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717DB4.s")

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} Ub2VelocityMotion;

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717F1C.s")


void func_80718080(Ub2ActorView *arg0) {
    f32 temp_fv0;
    Ub2VelocityMotion *temp_v0;

    func_80717F1C();
    temp_v0 = arg0->unk384;
    arg0->unk360 = temp_v0->unkC * temp_v0->unk8;
    arg0->unk364 = arg0->unk360;
    temp_fv0 = temp_v0->unkC;
    if (temp_fv0 < 2.0f) {
        temp_v0->unkC = (f32) ((f64) temp_fv0 + 0.2);
    }
}

void func_807180F4(s32 arg0, s32 arg1) {
    func_80717D4C();
    func_80716FB4((Ub1ActorView *)arg0, (void *)arg1);
}

void func_80718124(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    func_807149B8(1);
    func_80714998(3);
    func_8071498C(&func_80718380);
    func_80714CC0((s32)&D_8071FEF4, arg0, arg1, arg2, arg3);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80718188.s")

typedef f32 Ub2bMtxF[4][4];

void func_8071827C(Ub2ActorView *arg0, s8 *arg1) {
    Ub2bMtxF sp70;
    Ub2bMtxF sp30;
    u8 temp_v0;

    guScaleF(sp70, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp30, 90.0f, 1.0f, 0.0f, 0.0f);
    guMtxCatF(sp70, sp30, sp70);
    guTranslateF(sp30, arg0->unk340, arg0->unk344, arg0->unk348);
    guMtxCatF(sp70, sp30, sp70);
    temp_v0 = arg0->unk36D;
    arg0->unk360 = (f32) ((f64) arg0->unk360 + 0.07);
    arg0->unk364 = (f32) ((f64) arg0->unk364 + 0.07);
    if ((s32) temp_v0 >= 0xA) {
        arg0->unk36D = (u8) (temp_v0 - 0xA);
    } else {
        arg0->unk36D = 0U;
    }
    guMtxF2L(sp70, (Mtx *) ((u8 *) arg0 + (D_807444FC << 6) + 0x128));
    ((u8 *) arg0)[0x32C] = 3;
}

void func_80718380(Ub2ActorView *arg0, s8 *arg1) {
    Ub2bMtxF sp70;
    Ub2bMtxF sp30;
    u32 temp_v1;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(4);
        temp_v1 = (u32) (func_806119A0() % 36000U) / 100U;
        *(f32 *) arg0->unk384 = (f32) temp_v1;
    }
    guScaleF(sp70, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp30, 90.0f, 1.0f, 0.0f, 0.0f);
    guMtxCatF(sp70, sp30, sp70);
    guRotateF(sp30, *(f32 *) arg0->unk384, 0.0f, 1.0f, 0.0f);
    guMtxCatF(sp70, sp30, sp70);
    guTranslateF(sp30, arg0->unk340, arg0->unk344, arg0->unk348);
    guMtxCatF(sp70, sp30, sp70);
    if ((s32) arg0->unk36D >= 0xA) {
        arg0->unk36D -= 0xA;
    } else {
        arg0->unk36D = 0U;
    }
    guMtxF2L(sp70, (Mtx *) ((u8 *) arg0 + (D_807444FC << 6) + 0x128));
    ((u8 *) arg0)[0x32C] = 3;
    if (arg0->unk36D == 0) {
        *arg1 = 1;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_807184F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_807186C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_807189BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80718BF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071910C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_807195D4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_807197B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80719A0C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80719B88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80719C00.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80719EF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071A038.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071A1E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071A440.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071A674.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071A8B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071AADC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071ABDC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071AF30.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071B1AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071B24C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071B2EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071B44C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071B520.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071B758.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071B89C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071B8EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071BB14.s")

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Ub6Motion;

void func_8071BC80(Ub2ActorView *arg0, s8 *arg1) {
    f32 sp90[4][4];
    f32 sp50[4][4];
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    Ub6Motion *var_v0;

    var_v0 = arg0->unk384;
    if (var_v0 == NULL) {
        arg0->unk384 = func_80610FE8(0xC);
        guRotateF(sp90, -(f32)((func_806119A0() % 36000U) / 1000U), 1.0f, 0.0f, 0.0f);
        guRotateF(sp50, (f32)((arg0->unk35C * 0x168) / 4096), 0.0f, 1.0f, 0.0f);
        guMtxCatF(sp90, sp50, sp90);
        guMtxXFMF(sp90, 0.0f, 0.0f, 10.0f, &sp48, &sp44, &sp40);
        ((Ub6Motion *)arg0->unk384)->unk0 = sp48;
        ((Ub6Motion *)arg0->unk384)->unk4 = sp44;
        ((Ub6Motion *)arg0->unk384)->unk8 = sp40;
        var_v0 = arg0->unk384;
    }
    arg0->unk340 += var_v0->unk0;
    arg0->unk344 += var_v0->unk4;
    arg0->unk348 += var_v0->unk8;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071BE04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071C004.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071C24C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071C48C.s")

void func_8071C620(Ub2ActorView *arg0, s8 *arg1) {
    f32 sp90[4][4];
    f32 sp50[4][4];
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    Ub6Motion *var_v0;

    var_v0 = arg0->unk384;
    if (var_v0 == NULL) {
        arg0->unk384 = func_80610FE8(0xC);
        guRotateF(sp90, (f32)((func_806119A0() % 36000U) / 100U), 1.0f, 0.0f, 0.0f);
        guRotateF(sp50, (f32)((func_806119A0() % 36000U) / 100U), 0.0f, 0.0f, 1.0f);
        guMtxCatF(sp90, sp50, sp90);
        guRotateF(sp90, (f32)((func_806119A0() % 36000U) / 100U), 0.0f, 1.0f, 0.0f);
        guMtxCatF(sp90, sp50, sp90);
        guMtxXFMF(sp90, 0.0f, 0.0f, 0.5f, &sp4C, &sp48, &sp44);
        ((Ub6Motion *)arg0->unk384)->unk0 = sp4C;
        ((Ub6Motion *)arg0->unk384)->unk4 = sp48;
        ((Ub6Motion *)arg0->unk384)->unk8 = sp44;
        var_v0 = arg0->unk384;
    }
    arg0->unk340 += var_v0->unk0;
    arg0->unk344 += var_v0->unk4;
    arg0->unk348 += var_v0->unk8;
}

void func_8071C818(Ub2ActorView *arg0, s8 *arg1) {
    f32 sp70[4][4];
    f32 sp30[4][4];

    arg0->unk360 = (f32)((f64)arg0->unk360 - 0.05);
    arg0->unk364 = (f32)((f64)arg0->unk364 - 0.05);
    if (arg0->unk360 <= 0.0f) {
        *arg1 = 1;
    }
    arg0->unk35C = arg0->unk35C + 5;
    guScaleF(sp70, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp30, (f32)arg0->unk35C, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp70, sp30, sp70);
    guMtxF2L(sp70, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    arg0->pad0[0x32C] = 2;
}

void func_8071C914(Ub2ActorView *arg0, s8 *arg1) {
    f32 sp70[4][4];
    f32 sp30[4][4];
    f32 scale;

    arg0->unk360 = (f32)((f64)arg0->unk360 * 1.07);
    arg0->unk35C = arg0->unk35C + 0xA;
    scale = arg0->unk360;
    arg0->unk364 = scale;
    guScaleF(sp70, scale, scale, 0.0f);
    guRotateF(sp30, (f32)arg0->unk35C, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp70, sp30, sp70);
    guMtxF2L(sp70, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    arg0->pad0[0x32C] = 2;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071C9E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071CDE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071D0F0.s")

void func_8071D260(Ub2ActorView *arg0, s8 *arg1) {
    u16 difference;
    s32 amount;
    u8 remaining;
    s32 completed;

    amount = arg0->unk35C;
    difference = arg0->unk36D - amount;
    completed = 1;
    remaining = difference;
    arg0->unk36D = remaining;
    if (amount >= remaining) {
        *arg1 = completed;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071D28C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071D5BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071D784.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071D94C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071DB74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071DC90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071E028.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071E110.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071E1C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071E3EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071E864.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071EA24.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071EB70.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071EDEC.s")

void func_8071EEA4(Ub2ActorView *arg0, s32 arg1) {
    arg0->unk364 = (f32) (((f64) arg0->unk35C / 100.0) + 1.0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071EEE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071EFDC.s")

typedef struct {
    u8 unk0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} Ud1dPositionSource;

void func_8071F034(Ub2ActorView *arg0, s32 arg1) {
    if (*(s16 *) ((u8 *) arg0 + 0x34E) == 0) {
        arg0->unk340 = ((Ud1dPositionSource *) D_807FBB4C)->unk7C;
        arg0->unk344 = ((Ud1dPositionSource *) D_807FBB4C)->unk80;
        arg0->unk348 = ((Ud1dPositionSource *) D_807FBB4C)->unk84;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071F078.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071F1D0.s")

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} Ud1MotionState;
typedef struct {
    u8 unk0[4];
    f32 *unk4;
} Ud1ScaleRoot;

typedef struct {
    u8 unk0[0x38];
    f32 unk38;
} Ud1ScaleSource;

typedef struct {
    u8 unk0[0x338];
    Ud1ScaleRoot *unk338;
    u8 unk33C[4];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 unk34C[2];
    s16 unk34E;
    u8 unk350;
    u8 unk351[3];
    s32 unk354;
    s32 unk358;
    s32 unk35C;
    f32 unk360;
    f32 unk364;
    u8 unk368[0x1C];
    Ud1MotionState *unk384;
} Ud1ActorView;

void func_8071F2F8(Ud1ActorView *arg0, s32 arg1) {
    f32 temp_fv0;
    Ud1MotionState *temp_v0;
    Ud1MotionState *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(8);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = (f32) (arg0->unk35C & 0xFFFF);
        temp_v0->unk4 = (f32) ((s32) arg0->unk35C >> 0x10);
        var_v1 = arg0->unk384;
    }
    arg0->unk344 = arg0->unk344 + var_v1->unk0;
    temp_fv0 = var_v1->unk0;
    if (temp_fv0 > -20.0f) {
        var_v1->unk0 = (f32) ((f64) temp_fv0 - ((f64) var_v1->unk4 * 0.01));
    }
}

void func_8071F3C0(Ud1ActorView *arg0, s32 arg1) {
    Ud1MotionState *temp_v0;
    Ud1MotionState *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(4);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = (f32) ((f64) arg0->unk364 * 6.666666666666667);
        var_v1 = arg0->unk384;
    }
    arg0->unk360 = ((Ud1ScaleSource *) arg0->unk338->unk4)->unk38 * var_v1->unk0;
    arg0->unk364 = arg0->unk360;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071F444.s")

typedef struct {
    u8 unk0[0x32C];
    u8 unk32C;
    u8 unk32D[0xB];
    u8 unk338[0x1C];
    s32 unk354;
    s32 unk358;
    u8 unk35C[4];
    f32 unk360;
    f32 unk364;
} Ud1F660ActorView;

void func_80612CA0(f32 (*arg0)[4], f32 arg1);

void func_8071F660(Ud1F660ActorView *arg0, void *arg1) {
    f32 sp68[4][4];
    f32 sp28[4][4];
    f32 sp24;

    sp24 = (f32) arg0->unk358 / (f32) (arg0->unk354 - 1);
    arg0->unk360 = (f32) ((f64) func_80612794((s16) (s32) (sp24 * 2048.0f)) * 3.0);
    arg0->unk364 = arg0->unk360;
    guScaleF(sp68, arg0->unk360, arg0->unk360, 0.0f);
    func_80612CA0(sp28, sp24 * 180.0f);
    guMtxCatF(sp68, sp28, sp68);
    guMtxF2L(sp68, (Mtx *) ((s32) arg0 + (D_807444FC << 6) + 0x128));
    arg0->unk32C = 2;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071F758.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071F8E4.s")
