// func_8066C958 (src/global/70FD0.c): Frame 0x68 vs 0x60 caused by s2 holding &D_807FB549; loop structure and logic matched
#include "common.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066C2D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066C610.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066C7F4.s")

void func_8066C2D0(s32, s32, f32, f32, f32, f32, f32, f32, f32);

void func_8066C8B0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    func_8066C2D0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

typedef struct M70A_Struct_C904 {
    u8 pad0[0x10];
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 pad16[2];
    void *unk18;
    u8 pad1C[4];
} M70A_Struct_C904;

void heapFree(void *);

void func_8066C904(M70A_Struct_C904 *arg0) {
    if (arg0->unk18 != NULL && (arg0->unk15 & 1)) {
        heapFree(arg0->unk18);
    }
    arg0->unk15 &= ~1;
}

typedef struct M70A_Struct_C958 {
    s32 unk0;
    u8 pad4[5];
    u8 unk9;
    u8 padA[6];
    s16 unk10;
    s16 unk12;
} M70A_Struct_C958;

typedef struct M70A_Struct_CB88 {
    void *unk0;
    void *unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} M70A_Struct_CB88;

extern s32 D_8076A064;
extern s32 D_8076A0A8;
extern s32 D_807FB530;
extern M70A_Struct_CB88 *D_807FB534;
extern s32 D_807FB538;
extern u8 D_807FB549;

void *func_8066B0F8(s32, s32, s32, s32);
s32 func_8066B020(s32, s32);
void func_8066B424(void);
void func_8066B434(void *, s32, s32);
void *func_80610FE8(s32);
void gunzip(void *, void *, void *);

void func_8066C958(M70A_Struct_C958 *arg0) {
    void *sp60;
    void *sp5C;
    void *sp58;
    s32 sp38;
    void *sp30;
    void *var_s0;
    s32 *var_a2;
    u8 *var_v1;
    u8 *temp_a0;
    s32 temp_lo;
    s32 var_a3;
    s32 var_s1;
    s32 elem_size;

    var_s1 = 4;
    var_s0 = func_8066B0F8(2, D_8076A0A8, 1, 0);
    D_807FB549 = 0;
    if (arg0->unk9 & 1) {
        sp60 = var_s0;
        var_s0 = func_80610FE8(arg0->unk0);
        sp30 = func_80610FE8(0x2400);
        sp5C = var_s0;
        sp58 = sp60;
        gunzip(&sp58, &sp5C, sp30);
        heapFree(sp30);
        func_8066B424();
        func_8066B434(sp60, 0x14C, 0xA);
        D_807FB549 = 1;
    }
    sp38 = func_8066B020(2, D_8076A0A8);
    D_807FB530 = *(s32 *)var_s0;
    D_807FB534 = func_80610FE8(0x1518);
    temp_lo = arg0->unk10 * arg0->unk12;
    var_a2 = (s32 *)((u8 *)var_s0 + 4);
    var_a3 = 0;
    var_v1 = (u8 *)var_s0 + var_s1;
    elem_size = 24;
    D_807FB538 = temp_lo;
    if (temp_lo > 0) {
        do {
            temp_a0 = var_v1 + 4;
            var_s1 = *var_a2;
            if (D_807FB549 != 0) {
                D_807FB534[var_a3].unk4 = temp_a0;
            } else {
                D_807FB534[var_a3].unk4 = NULL;
            }
            D_807FB534[var_a3].unk0 = NULL;
            var_v1 = (u8 *)var_s0 + var_s1;
            D_807FB534[var_a3].unkC = sp38 + (temp_a0 - (u8 *)var_s0);
            D_807FB534[var_a3].unk10 = var_v1 - temp_a0;
            var_a2 = (s32 *)var_v1;
            D_807FB534[var_a3].unk8 = 0;
            D_807FB534[var_a3].unk14 = (var_v1 - temp_a0) / elem_size;
            var_a3++;
        } while (var_a3 < D_807FB538);
    }
    if (D_807FB549 == 0) {
        func_8066B424();
        func_8066B434(var_s0, 0x17C, 0xA);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066CB88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066CCD8.s")

void func_8066CDF8(void);
void func_806687E0(void);

void func_8066CDD0(void) {
    func_8066CDF8();
    func_806687E0();
}
void func_8066CDF8(void) {
    s32 i;

    for (i = 0; i < D_807FB538; i++) {
        if (D_807FB534[i].unk0 != NULL && (u32)(D_8076A064 - D_807FB534[i].unk8) >= 0x15) {
            if (D_807FB549 == 0) {
                heapFree(D_807FB534[i].unk4);
                D_807FB534[i].unk4 = NULL;
            }
            heapFree(D_807FB534[i].unk0);
            D_807FB534[i].unk0 = NULL;
        }
    }
}

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
