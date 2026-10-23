// func_8066B4D4 (src/global/6AD90.c): near-miss: 61 insns, stack slots 0x38/0x44 and 0x7FFFFFFF hoist match, sp2C slot 0x34 vs 0x2C remains
#include "common.h"

extern s32 D_8000DDCC;
extern s32 *D_807F9528[];
void func_8060B140(s32, void *, void *, s32, s32, s32, s32);

s32 func_8066B4D4(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    s32 pad[2];
    s32 sp44;
    u64 sp38;
    s32 sp2C;
    s32 *table;
    s32 temp_v0;
    s32 var_t0;

    table = &D_807F9528[arg0][arg1];
    temp_v0 = table[0];
    var_t0 = arg1;
    if (temp_v0 & 0x80000000) {
        sp2C = 8;
        func_8060B140(D_8000DDCC + (temp_v0 & 0x7FFFFFFF), &sp38, &sp2C, 0, 0, 0, 0);
        sp44 = (s16)(sp38 >> 48);
        func_8066B4D4(arg0, sp44, arg2, arg3);
        var_t0 = sp44;
    } else {
        *arg2 = D_8000DDCC + temp_v0;
        *arg3 = (table[1] & 0x7FFFFFFF) - temp_v0;
    }
    return var_t0;
}
