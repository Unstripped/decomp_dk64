#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern void *D_807FC924;
extern s32 D_8076A0A8;
extern u8 D_80755314;
extern u8 D_80755318;

extern s32 func_80731AA8(s32, s32, s32);
extern s8 D_8075536C;
extern s32 D_80755338;
extern s32 D_8075533C;
extern u8 D_80755350;
extern s8 D_80755330;
extern s8 D_80750754;




void func_805FF378(s32, s32);

void func_80712490(s32 arg0, s32 arg1, u8 arg2) {
    func_805FF378(arg0, arg1);
    D_80755318 = arg2;
}

void func_805FF158(s32);
s32 func_80712798(void);

void func_807124B8(s32 arg0, s32 arg1, u8 arg2) {
    if (func_80712798() == 0) {
        func_805FF158(0);
        func_80712490(arg0, D_8075536C, arg2);
        D_80755338 = 1;
        D_8075533C = arg1;
        D_8075536C = 0;
    }
}

void func_80712524(s32 arg0, s32 arg1) {
    func_807124B8(arg0, arg1, D_80755318);
}

s32 func_80712548(void) {
    return func_80731AA8(0x1FD, 0x28, 0) + 0xA;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80712574.s")

void func_8071261C(void) {
    D_80755350 = 0;
}

s32 func_80712628(void) {
    return D_80755350;
}

void func_80712634(s32 arg0, s32 arg1) {
    func_807124B8(arg0, arg1, 0xB);
    D_80755330 = 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80712658.s")

void func_8071268C(void) {
    if (D_80755314 == 0xB) {
        D_80755330 = 1;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_807126B0.s")

void func_80712774(s32 arg0) {
    func_80712490(arg0, 0, 0xD);
}

s32 func_80712798(void) {
    return D_80755314 != D_80755318;

}
void func_805FFFC8(void);
void func_8073129C(s32, s32, s32);

void func_807127B4(void) {
    func_805FFFC8();
    func_8073129C(0x314, 1, 0);
    func_807124B8(0x1C, 0x17, 7);
}

void func_807127F4(s32 arg0) {
    u8 temp;

    if (arg0 == 0) {
        temp = 0xA;
    } else {
        temp = 0xE;
    }
    func_807124B8(0x99, 0xB, temp);
    D_80750754 = -2;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80712830.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80712944.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80712A40.s")

extern u8 D_80755328;
extern s8 D_8074E77C;
extern u8 D_80750AC0;
extern u16 D_8075531C;
extern u16 D_807ECD66;
extern u8 D_8075E5C0[];

void func_8060B750(s32);
s32 func_8060B7C4(void);

void func_80712B80(void) {
    if (D_80755318 == 3) {
        func_8060B750(D_8075E5C0[D_80755328 * 4]);
        D_8074E77C = func_8060B7C4();
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80712BD4.s")

void func_80712EDC(void) {
    D_80750AC0 = 1;
    func_80712490(0x50, 0, 5);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80712F10.s")


#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80712FC8.s")

void func_8070B308(s32);

void func_80713088(void) {
    D_8075531C = 0x1E;
    if (D_807ECD66 & 0x8000) {
        func_8070B308(0);
        func_80712490(0x50, 0, 5);
    }
}

s32 func_8061CB50(void);

void func_807130D4(void) {
    if (func_8061CB50()) {
        D_8075531C = 0x1E;
    }
    if ((D_80755330 == 1) || (D_8075531C == 0) || (D_807ECD66 & 0x8000)) {
        func_8070B308(0);
        D_80755330 = 0;
        func_80712490(0x50, 0, 5);
        D_80755330 = 2;
    }
}
#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80713168.s")

extern u8 D_8075532C;
void func_8060B7D0(s32 *, s32 *);

void func_807131BC(void) {
    s32 arg0;
    s32 arg1;

    D_8075532C = 0;
    func_8060B750(D_8075E5C0[D_80755328 * 4]);
    func_8060B7D0(&arg0, &arg1);
    func_805FF158(1);
    func_80712490(arg0, arg1, 3);
}
extern s32 D_80755334;
extern u16 D_807ECD48;
void func_807131BC(void);

void func_8071321C(void) {
    if ((D_8075531C == 0) || ((D_80755334 >= 0xA) && (D_807ECD48 & 0x1000))) {
        func_807131BC();
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80713270.s")
#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_807132DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_8071338C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/D_8075E5C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80713438.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_807135B4.s")

s32 func_8071375C(s32 arg0) {
    return arg0;
}
#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80713764.s")

void *func_807132DC(void);
void func_807135B4(void *);

void func_807138A4(void) {
    func_807135B4(func_807132DC());
}
#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_807138CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80713AA8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80713B40.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80713C8C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80713DFC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80713EA8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80713EB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80714060.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_807142D8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_8071432C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80714360.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80714394.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_807143E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_8071441C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80714450.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80714464.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_807144B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_8071458C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_807145F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80714608.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80714638.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80714660.s")
