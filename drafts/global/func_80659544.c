// func_80659544 (src/global/5E020.c): stage 5, score 200: all insns match, 2 extra delay nops before jr ra in else branch
#include "common.h"

s32 func_80659544(s32 arg0) {
    int new_var = arg0;

    if (new_var > 0) {
        return new_var % 100;
    } else {
        new_var = (-new_var) % 100;
        return new_var;
    }
}
