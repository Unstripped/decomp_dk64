// func_8066C7F4 (src/global/70FD0.c): Frame 0x80 and &sp38 at 0x38 matched with declaration order (s32 i=1; s32 *var_s0; Mtx sp38; s32 var_s1;); volatile i forces sp7C store/reload; remaining diff is arg0 home-slot spill vs s1 cache
#include "common.h"

void *memcpy(void *, const void *, size_t);

void func_8066C7F4(s32 *arg0, u8 *arg1, float arg2[4][4]) {
    volatile s32 i = 1;
    s32 *var_s0;
    Mtx sp38;
    s32 var_s1;

    memcpy(&sp38, arg1 + arg0[0], sizeof(Mtx));
    var_s0 = arg0 + i;
    if (arg0[1] != -1) {
        var_s1 = *var_s0;
        do {
            guMtxCatL(&sp38, (Mtx *)(arg1 + var_s1), &sp38);
            var_s0++;
            var_s1 = *var_s0;
        } while (var_s1 != -1);
    }
    guMtxL2F(arg2, &sp38);
}
