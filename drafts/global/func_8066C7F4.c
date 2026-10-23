// func_8066C7F4 (src/global/70FD0.c): Closest diff: frame 0x80 vs 0x88, sp7C=1 spill and arg0 home-slot spill
#include "common.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066C2D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066C610.s")

void *memcpy(void *, const void *, size_t);

void func_8066C7F4(s32 *arg0, u8 *arg1, float arg2[4][4]) {
    s32 i = 1;
    Mtx sp38;
    s32 *var_s0;
    s32 var_s1;

    memcpy(&sp38, arg1 + arg0[0], sizeof(Mtx));
    var_s0 = arg0 + i;
    if (arg0[1] != -1) {
        var_s1 = *var_s0;
        do {
            guMtxCatL(&sp38, (Mtx *)(arg1 + var_s1), &sp38);
            var_s0++;
            var_s1 = *var_s0;
        } while (var_s1 != -1);
    }
    guMtxL2F(arg2, &sp38);
}

void func_8066C2D0(s32, s32, f32, f32, f32, f32, f32, f32, f32);

void func_8066C8B0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    func_8066C2D0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

typedef struct M70A_Struct_C904 {
    u8 pad0[0x15];
    u8 unk15;
    u8 pad16[2];
    void *unk18;
} M70A_Struct_C904;

void heapFree(void *);

void func_8066C904(M70A_Struct_C904 *arg0) {
    if (arg0->unk18 != NULL && (arg0->unk15 & 1)) {
        heapFree(arg0->unk18);
    }
    arg0->unk15 &= ~1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066C958.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066CB88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066CCD8.s")

void func_8066CDF8(void);
void func_806687E0(void);

void func_8066CDD0(void) {
    func_8066CDF8();
    func_806687E0();
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066CDF8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066CEE4.s")

typedef struct M70A_Triangle_s16 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
} M70A_Triangle_s16;

s32 func_8066D250(M70A_Triangle_s16 *arg0) {
    s16 temp_a1;
    s16 temp_v0;
    s16 temp_v1;

    temp_v0 = arg0->unk6;
    temp_v1 = arg0->unk0;
    if ((temp_v0 == temp_v1) && (arg0->unk2 == arg0->unk8) && (arg0->unk4 == arg0->unkA)) {
        return 1;
    }
    temp_a1 = arg0->unkC;
    if ((temp_v0 == temp_a1) && (arg0->unkE == arg0->unk8) && (arg0->unk10 == arg0->unkA)) {
        return 1;
    }
    if ((temp_a1 == temp_v1) && (arg0->unk2 == arg0->unkE) && (arg0->unk4 == arg0->unk10)) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066D2F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066D4DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066DB40.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066DD34.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066E21C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066E2C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066E5CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066E5F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066E62C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066E664.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066E6C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066E72C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066E854.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066E8E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066E990.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066E9EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066EA64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066EA90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066EABC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066EAEC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066EB40.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066EB50.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066EBF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066EC6C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066EE50.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066F06C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066F1F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066F250.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066F274.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066F400.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066F4AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066F84C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066FC0C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066FD6C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066FE08.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80670548.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80670C5C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80670F04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80670FA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_806710E0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671260.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_806713E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671528.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_806717FC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671880.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671A6C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671C0C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671D10.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671D64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671E00.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671F54.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672134.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672328.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_806725A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_806725E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672630.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672680.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_806726DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_806728F0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672A70.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672AFC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672B1C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672BD4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672C30.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672C70.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672CBC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672E6C.s")
