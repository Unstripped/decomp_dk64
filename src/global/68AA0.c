#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/68AA0/func_80663DA0.s")

typedef struct R1Small_68AA0_Entry {
    u8 pad[0x84];
    s16 unk84;
    u8 pad86[0xA];
} R1Small_68AA0_Entry;

extern R1Small_68AA0_Entry *D_807F6000;
s32 func_80663FCC(s16 arg0) {
    s16 val = D_807F6000[arg0].unk84;

    if (val == 1 || val == 0xC || val == 0x10 || val == 0xF3 || val == 0x134 || val == 0x135 || val == 0x138) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/68AA0/func_80664044.s")
