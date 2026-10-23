// func_80664044 (src/global/68AA0.c): Near-miss, 78/87 insns matched; regalloc $s4/$s6 swap between &D_807F9420 and arg1/arg2. Inner loop matches 100% with do-while direct unk7_arr indexing
#include "common.h"
#include "actor.h"

typedef struct R2Small_68AA0_Target {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    union {
        struct {
            s8 unk7;
            s8 pad8[4];
        } s;
        s8 unk7_arr[5];
    } u;
} R2Small_68AA0_Target;

extern R2Small_68AA0_Target *D_807F9420;
extern s16 D_807F9424;

typedef struct R3Small_SchedPlayer {
    u8 pad0[0x290];
    s16 unk290;
} R3Small_SchedPlayer;

extern R3Small_SchedPlayer *D_807FC924;

void func_80603340(f32, f32, f32, u8, u8, f32);

void func_80664044(u8 arg0, u8 arg1, u8 arg2, f32 arg3) {
    R2Small_68AA0_Target *entry;
    s32 i;
    s32 j;
    s32 found;

    for (i = 0; i < D_807F9424; i++) {
        entry = &D_807F9420[i];
        if (entry->unk6 == arg0) {
            j = 0;
            found = 0;
            do {
                if (D_807F9420[i].u.unk7_arr[j] == D_807FC924->unk290) {
                    found = 1;
                }
                j++;
                if (j >= 5 || found) {
                    break;
                }
            } while (D_807F9420[i].u.unk7_arr[j] != -1);

            if (found) {
                func_80603340(entry->unk0, entry->unk2, entry->unk4, arg1, arg2, arg3);
            }
        }
    }
}
