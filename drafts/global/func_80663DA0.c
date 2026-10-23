// func_80663DA0 (src/global/68AA0.c): Near-miss, ~120/139 insns matched; regalloc difference in s-registers for loop counters
#include "common.h"
#include "actor.h"

typedef struct R1Small_68AA0_Entry {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[0x84 - 0xC];
    s16 unk84;
    u8 pad86[0xA];
} R1Small_68AA0_Entry;

typedef struct R1Small_68AA0_Target {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    s8 unk7;
    s8 pad8[4];
} R1Small_68AA0_Target;

extern R1Small_68AA0_Entry *D_807F6000;
extern R1Small_68AA0_Target *D_807F9420;
extern s16 D_807F9424;
extern s32 D_80747D70;

void *func_80610FE8(s32);
s32 func_80663FCC(s16);
s8 func_806531B8(f32, f32, f32, s32);
s32 func_80658B08(s8, void *, s32);

void func_80663DA0(void) {
    s16 i;
    s32 k;

    D_807F9424 = 0;
    for (i = 0; i < D_80747D70; i++) {
        if (func_80663FCC(i)) {
            D_807F9424++;
        }
    }

    D_807F9420 = NULL;
    if (D_807F9424 != 0) {
        D_807F9420 = func_80610FE8(D_807F9424 * sizeof(R1Small_68AA0_Target));
        k = 0;
        for (i = 0; i < D_80747D70; i++) {
            s32 res = func_80663FCC(i);
            if (res != 0) {
                s32 temp;
                D_807F9420[k].unk0 = D_807F6000[i].unk0;
                D_807F9420[k].unk2 = D_807F6000[i].unk4;
                D_807F9420[k].unk4 = D_807F6000[i].unk8;
                D_807F9420[k].unk6 = res;
                D_807F9420[k].unk7 = func_806531B8(D_807F6000[i].unk0, D_807F6000[i].unk4, D_807F6000[i].unk8, 0);
                temp = func_80658B08(D_807F9420[k].unk7, &D_807F9420[k].pad8, 4);
                if (temp != 4) {
                    D_807F9420[k].pad8[temp] = -1;
                }
                k++;
            }
        }
    }
}
s32 func_80663FCC(s16 arg0) {
    s16 val = D_807F6000[arg0].unk84;

    if (val == 1 || val == 0xC || val == 0x10 || val == 0xF3 || val == 0x134 || val == 0x135 || val == 0x138) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/68AA0/func_80664044.s")
