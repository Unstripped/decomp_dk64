// func_8064FA7C (src/global/54150.c): stage 6: identical instruction stream/length after volatile-store fix (*(volatile u32*)&D_807F6BE0 gives lui/addiu/sw, not $at); only regalloc of a/b/arg0 (extra early move of arg0) and temp v0/v1 differ
#include "common.h"

extern u32 D_807F6BE0;
extern u32 D_807F6BE4;
extern u8 D_807444FC;
void func_8065054C();

void func_8064FA7C(u32 *arg0, u32 *arg1) {
    u8 *node;
    s16 stride;
    s32 i;
    u8 *p;
    u32 a;
    u32 b;

    node = (u8 *)*arg1;
    stride = *(u8 *)node * 0x24 + 8;
    a = arg0[D_807444FC ^ 1];
    *(volatile u32 *)&D_807F6BE0 = a;
    b = arg0[D_807444FC];
    *(volatile u32 *)&D_807F6BE4 = b;
    p = node + 0x3C;
    i = 0;
    while (i < *(u8 *)(node + 0x39)) {
        func_8065054C(arg0, *(u32 *)p + a, *(u32 *)p + b);
        i++;
        p += stride;
    }
}
