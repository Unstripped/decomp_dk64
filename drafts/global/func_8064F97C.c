// func_8064F97C (src/global/54150.c): stage 6: identical instruction stream/length; only regalloc of a/b locals (theirs a=s5,b=s6; ours b gets s3) and v+b CSE placement in the bnez delay slot differ
#include "common.h"

typedef struct M54AOwner {
    u8 *unk0;
    u32 unk4;
    u8 pad8[6];
    u8 unkE;
    u8 padF[2];
    u8 unk11;
    u8 pad12;
    u8 unk13;
} M54AOwner;

extern u32 D_807F6BE0;
extern u32 D_807F6BE4;
extern u32 D_807F6BE8;

void func_8064FB64();
void func_8065054C();
void func_806505F0();

void func_8064F97C(M54AOwner *arg0) {
    u8 *node;
    s16 stride;
    s32 i;
    u8 *p;
    u32 a;
    u32 b;

    node = arg0->unk0;
    stride = *(u8 *)node * 0x24 + 8;
    a = D_807F6BE0;
    b = D_807F6BE4;
    i = 0;
    p = node + 0x3C;
    while (i < *(u8 *)(node + 0x39)) {
        u32 v;

        func_8064FB64(arg0->unk11, arg0->unk4, p, p + 8, arg0->unk13);
        v = *(u32 *)p;
        if (arg0->unkE == 0) {
            func_8065054C(D_807F6BE8, v + a, v + b);
        } else {
            func_806505F0(v + b);
        }
        i++;
        p += stride;
    }
}
