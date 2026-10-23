#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/67890/func_80662B90.s")

typedef struct R1F67890_Entry40 {
    u8 pad0[0x38];
    s16 unk38;
    u8 pad3A[6];
} R1F67890_Entry40;

extern R1F67890_Entry40 *D_807F93F0;
extern s32 D_807F93F8;

s32 func_80663040(s32 arg0) {
    s32 i;

    for (i = 0; i < D_807F93F8; i++) {
        if (arg0 == D_807F93F0[i].unk38) {
            return 1;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/67890/func_8066308C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/67890/func_806634A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/67890/func_80663594.s")
