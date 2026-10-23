// func_80664044 (src/global/68AA0.c): Near-miss, 78/87 insns matched; regalloc $s4/$s6 swap between &D_807F9420 and arg1/arg2
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

typedef struct R1Small_68AA0_Entry2 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    s8 unk7[5];
} R1Small_68AA0_Entry2;

typedef struct R1Small_SchedPlayer {
    u8 pad0[0x290];
    s16 unk290;
} R1Small_SchedPlayer;

extern R1Small_68AA0_Entry2 *D_807F9420;
extern s16 D_807F9424;
extern R1Small_SchedPlayer *D_807FC924;

void func_80603340(f32, f32, f32, u8, u8, f32);

void func_80664044(u8 arg0, u8 arg1, u8 arg2, f32 arg3) {
    R1Small_68AA0_Entry2 *entry;
    s32 i;
    s32 j;
    s32 found;

    for (i = 0; i < D_807F9424; i++) {
        entry = &D_807F9420[i];
        j = 0;
        found = 0;
        if (entry->unk6 == arg0) {
            do {
                s8 val = D_807F9420[i].unk7[j];
                if (val == D_807FC924->unk290) {
                    found = 1;
                }
                j++;
                if (j >= 5 || found) {
                    break;
                }
            } while (D_807F9420[i].unk7[j] != -1);

            if (found) {
                func_80603340(entry->unk0, entry->unk2, entry->unk4, arg1, arg2, arg3);
            }
        }
    }
}
