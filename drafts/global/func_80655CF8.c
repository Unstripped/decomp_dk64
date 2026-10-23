// func_80655CF8 (src/global/55B20.c): stage 5-6 near-miss; see M55P4 report
#include "common.h"
#include "actor.h"



s32 func_80655CF8(s16 arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        if (arg0 == D_807F6C30[i]) {
            return 1;
        }
    }
    return 0;
}
