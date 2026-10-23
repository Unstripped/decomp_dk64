// func_80659544 (src/global/5E020.c): stage 5, all insns and registers match; 2 extra hazard nops before jr ra in else branch due to IDO as1 hazard insertion before exit label
#include "common.h"

s32 func_80659544(s32 arg0) {
    int new_var = arg0;

    if (new_var > 0) {
        return new_var % 100;
    }
    new_var = -new_var;
    return new_var % 100;
}
