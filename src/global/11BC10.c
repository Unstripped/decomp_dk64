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


#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80716F10.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80716FB4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717100.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071720C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717404.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717760.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717814.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717930.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717B64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717CE8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717D4C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717D84.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717DB4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717F1C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80718080.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_807180F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80718124.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80718188.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071827C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80718380.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071BC80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071BE04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071C004.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071C24C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071C48C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071C620.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071C818.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071C914.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071C9E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071CDE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071D0F0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071D260.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071EEA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071EEE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071EFDC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071F034.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071F660.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071F758.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071F8E4.s")
