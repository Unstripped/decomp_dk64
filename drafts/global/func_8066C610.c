// func_8066C610 (src/global/70FD0.c): Closest diff: logic 100% matched, frame 0xF0 matched, callee-saved float f20 used for 0.0f CSE across guRotateF calls
#include "common.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066C2D0.s")

typedef struct M70A_Unk24 {
    u8 pad0[0x60];
    s32 unk60;
} M70A_Unk24;

typedef struct M70A_Struct_C610 {
    u8 pad0[0x24];
    M70A_Unk24 *unk24;
    u8 pad28[0x50];
    s32 *unk78;
    u8 pad7C[0x14];
} M70A_Struct_C610;

extern u8 D_807444FC;
extern M70A_Struct_C610 *D_807F6000;

void func_806357F8();
void func_8066C7F4();

void func_8066C610(s16 arg0, s8 arg1, f32 (*arg2)[4]) {
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    s32 spD0;
    float sp8C[4][4];
    float sp4C[4][4];
    s32 sp48;
    void *sp44;
    M70A_Struct_C610 *entry;

    entry = &D_807F6000[arg0];
    if (entry->unk78 != NULL) {
        sp48 = entry->unk78[D_807444FC];
    } else {
        sp48 = 0;
    }
    sp44 = (u8 *)entry->unk24 + entry->unk24->unk60;
    func_806357F8(arg0, &spEC, &spE8, &spE4, &spE0, &spDC, &spD8, &spD4, &spD0, 0);
    guScaleF(sp8C, spD4, spD4, spD4);
    guRotateF(sp4C, spE0, 1.0f, 0, 0);
    guMtxCatF(sp8C, sp4C, sp8C);
    guRotateF(sp4C, spDC, 0, 1.0f, 0);
    guMtxCatF(sp8C, sp4C, sp8C);
    guRotateF(sp4C, spD8, 0, 0, 1.0f);
    guMtxCatF(sp8C, sp4C, sp8C);
    guTranslateF(sp4C, spEC, spE8, spE4);
    if (arg1 != -1) {
        guMtxCatF(sp8C, sp4C, sp8C);
        func_8066C7F4((u8 *)sp44 + (arg1 << 5), sp48, arg2);
        guMtxCatF(arg2, sp8C, arg2);
        return;
    }
    guMtxCatF(sp8C, sp4C, arg2);
}

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066C958.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066CB88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066CCD8.s")

void func_8066CDF8(void);
void func_806687E0(void);

void func_8066CDD0(void) {
    func_8066CDF8();
    func_806687E0();
}
typedef struct M70A_Struct_CDF8 {
    void *unk0;
    void *unk4;
    s32 unk8;
    u8 padC[0xC];
} M70A_Struct_CDF8;

extern s32 D_8076A064;
extern M70A_Struct_CDF8 *D_807FB534;
extern s32 D_807FB538;
extern u8 D_807FB549;

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
