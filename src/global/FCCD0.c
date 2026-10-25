#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern u8 D_807FC950[][0x5E];
extern s32 D_8076A0A8;
extern u8 D_8076A0AB;
extern u8 D_8076A0B1;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_807444F8;
extern u8 D_807444FC;

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F7FD0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8004.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8170.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8278.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F833C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8A8C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8AD4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8BC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8CB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8CFC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8D58.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8DC4.s")

extern s32 func_80731AA8(s32, s32, s32);

void func_806F8EB4(void) {
    func_80731AA8(0x24D, 0x14, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8EDC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F91B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F93EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F942C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9470.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F94AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9518.s")

void func_806F9518(s32);

void func_806F95C8(void) {
    s32 i;

    i = 0;
    do {
        func_806F9518(i);
        i++;
    } while (i != 0xF);
}

typedef struct R1FCCD0bAllocRecord {
    s32 unk0;
    u8 pad4[0x10];
    void *unk14;
} R1FCCD0bAllocRecord;

void *func_80610FE8(s32);
void heapClearBlock(void *);

void func_806F9608(R1FCCD0bAllocRecord **arg0) {
    R1FCCD0bAllocRecord *temp;

    temp = func_80610FE8(0x1C);
    *arg0 = temp;
    heapClearBlock(temp);
    (*arg0)->unk0 = 1;
    (*arg0)->unk14 = func_80610FE8(0xC);
    heapClearBlock((*arg0)->unk14);
}

void func_806F966C(R1FCCD0bAllocRecord **arg0) {
    R1FCCD0bAllocRecord *temp;

    temp = func_80610FE8(0x1C);
    *arg0 = temp;
    heapClearBlock(temp);
    (*arg0)->unk0 = 0;
    (*arg0)->unk14 = func_80610FE8(0x88);
    heapClearBlock((*arg0)->unk14);
}

typedef struct R1FCCD0bEffect {
    u8 pad0[4];
    f32 unk4;
    f32 unk8;
    s32 unkC;
} R1FCCD0bEffect;

void func_806F96CC(R1FCCD0bEffect *arg0, u32 arg1) {
    s32 var_v0;
    s32 var_v1;

    var_v0 = 0;
    var_v1 = 0;
    arg0->unkC = 0;
    switch (arg1) {
    case 0:
    case 13:
    case 14:
        var_v0 = -1;
        break;
    case 9:
    case 10:
    case 12:
        var_v1 = 1;
        break;
    default:
        var_v0 = 1;
        break;
    }
    arg0->unk4 = (f32)(var_v0 * 0x30);
    arg0->unk8 = (f32)(var_v1 * 0x30);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9744.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9848.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9AF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9B64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9CD0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9D8C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FA1A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FA504.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FA5A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FA7A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FA7BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FA9C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FAB20.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FAC64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FACE8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FAFE4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FB218.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FB290.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FB2B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FB370.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FB3D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FB418.s")
