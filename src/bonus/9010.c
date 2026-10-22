
#include "common.h"

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/9010/func_8002D010.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/9010/func_8002D2F0.s")
#pragma GLOBAL_ASM("asm/bonus/nonmatchings/9010/func_8002D6F8.s")

extern s8 D_8002D92C;
extern s8 D_8002D930;
extern s8 D_8002DEF0[];

void func_8002D7E8(s16 arg0) {
    s8 var_v0;

    if (arg0 == 0xD4) {
        var_v0 = 0xA;
    } else {
        var_v0 = 2;
    }
    if (D_8002D92C < 6) {
        D_8002DEF0[D_8002D92C] = var_v0;
        D_8002D92C += 1;
        D_8002D930 = 0x14;
    }
    if (D_8002D92C >= 5) {
        D_8002D930 = 0;
    }
}
