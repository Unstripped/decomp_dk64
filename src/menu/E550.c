#include "common.h"

typedef struct {
    char pad0[0x60];
    s32 unk60;
    char pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xCD - 0x88];
    u8 unkCD;
    char padCE[0x154 - 0xCE];
    u8 unk154;
    u8 unk155;
    char pad156[0x15F - 0x156];
    u8 unk15F;
    char pad160[0x16A - 0x160];
    u8 unk16A;
    u8 unk16B;
    u8 unk16C;
} MenuBB40_E550;

extern MenuBB40_E550 *D_807FBB40;
extern u8 D_80033FB0;
extern u8 D_80033FB1;
extern u8 D_80033FB2;

void behaviourFrameBegin(void);
void func_8068A858(u8 *, u8 *, u8 *);
s32 func_80629148(void);
void func_80629174(void);
void func_80614EBC(MenuBB40_E550 *, s32);
void func_806319C4(MenuBB40_E550 *, s32);

#pragma GLOBAL_ASM("asm/menu/nonmatchings/E550/func_80032550.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/E550/func_8003264C.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/E550/func_8003292C.s")
