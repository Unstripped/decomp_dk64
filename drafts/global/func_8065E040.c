// func_8065E040 (src/global/61AA0.c): 33/35 insns matched; only 2 insns diff: addiu v1 vs v0 order in prologue
#include <ultra64.h>

extern s32 D_807F8EC0;
extern s32 D_807F9050;
extern s32 D_807F9054;
extern s32 D_807F905C;
extern s16 D_807F9060;
extern s32 D_807F9064;

s32 func_8065E0CC(void);

void func_8065E040(s32 arg0) {
    s32 *p = &D_807F8EC0;
    do {
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        *(p++) = 0;
        p += 3;
    } while ((u32)&D_807F9050 != (u32)p);

    D_807F9050 = 0;
    D_807F9054 = 0;
    D_807F905C = 0;
    D_807F9060 = 0;
    if (func_8065E0CC()) {
        D_807F9064 = arg0 + 0x70000;
    } else {
        D_807F9064 = arg0;
    }
}
