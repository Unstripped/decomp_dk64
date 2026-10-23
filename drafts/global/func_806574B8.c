// func_806574B8 (src/global/55B20.c): structure right (do-while + blez guard); expected rematerialises base in loop (no CSE) and keeps p++ in bne delay slot
#include "common.h"

extern u8 D_807F7070;
extern u8 D_807F7060[];

s32 func_806574B8(s32 arg0) {
    u8 *p = D_807F7060;

    if (D_807F7070 > 0) {
        do {
            if (arg0 == *p) {
                return 0;
            }
            p++;
        } while (p < D_807F7060 + D_807F7070);
    }
    return 1;
}
