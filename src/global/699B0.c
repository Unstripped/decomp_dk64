#include "common.h"
#include "actor.h"

typedef struct {
    u8 unk0;
    u8 pad[0x1F];
} R1A_Struct8BA0;

extern R1A_Struct8BA0 D_80748BA0[];
extern u8 D_807F9440[];
extern s32 D_807F9448;

void func_80664CB0(arg0)
s16 arg0;
{
    s32 limit;
    u8 *ptr;
    s32 i;

    limit = 13;
    D_807F9448 = 0;
    for (i = 0, ptr = (u8 *)D_80748BA0; i < limit; i++, ptr += 0x20) {
        if (arg0 == *ptr) {
            if (D_807F9448 != 8) {
                D_807F9440[D_807F9448++] = i;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80664D20.s")
