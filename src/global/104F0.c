#include "common.h"
#include "actor.h"

extern s16 D_807ECEA0[];
extern u8 D_807467C8;

extern s32 func_80631C20(s32);

void func_8060B7F0(void) {
    s32 temp_v0;
    s32 var_s0;

    D_807ECEA0[0] = 0;
    var_s0 = 0;
    do {
        temp_v0 = func_80631C20(var_s0 & 0xFF);
        var_s0 += 1;
        D_807ECEA0[0] += temp_v0;
    } while (var_s0 != 8);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060B84C.s")

extern s8 D_80744460;
extern void (*D_807467D0[])(void);
extern OSMesgQueue D_807F02B8;

void func_8060B8F8(s32 arg0) {
    if (osGetThreadId(NULL) == 9) {
        D_807467D0[arg0]();
        return;
    }
    if (D_80744460 == 0) {
        osSendMesg(&D_807F02B8, (void *)arg0, 0);
    }
}



#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060B968.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060B9D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BA14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BB18.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BBE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BCA0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BEA8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060BF84.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C2C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C340.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C430.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C648.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C6B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C724.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C758.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C830.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060C8AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060CB74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060CB9C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060CBBC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060D0A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060D14C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060D2C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060D768.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060D788.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060D7A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060DC3C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060DEA8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060DEC8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060E128.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060E1A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060E25C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060E3B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/func_8060E430.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/D_80757020.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/D_80757024.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/D_80757044.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/D_80757064.s")
