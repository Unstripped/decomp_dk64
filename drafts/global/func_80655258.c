// func_80655258 (src/global/55B20.c): stage 5-6 near-miss; see M55P4 report
#include "common.h"
#include "actor.h"



void func_80655258(f32, f32, f32, s32);

void func_80654380(f32 arg0, f32 arg1, f32 arg2) {
    s32 i;
    s32 off;

    func_80654418(arg0, arg1);
    i = 0;
    off = 0;
    while (i < D_807F70AC) {
        i++;
        *((u8 *)(D_807F70B0 + off) + 0x18) = 0;
        off += 0x1C;
    }
    func_80655258(arg0, arg1, arg2, -1);
    func_80654A2C(arg0, arg1, arg2);
}
