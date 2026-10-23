// func_80602104 (src/global/6710.c): stage 6, 2 insns, IDO commoned &D_807454E8 into v0
#include "common.h"
#include "actor.h"

extern s32 D_807454E8;

void func_80602104(s32 arg0) {
    if (((osAiGetLength() >> 2) == 0) && (D_807454E8 == 0)) {
        D_807454E8 = 0;
    }
}
