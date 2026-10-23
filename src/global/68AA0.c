#include "common.h"
#include "actor.h"


typedef struct ActorTargetSource {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[0x84 - 0xC];
    s16 unk84;
    u8 pad86[0xA];
} ActorTargetSource;

typedef struct ActorTargetEntry {
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
} ActorTargetEntry;

extern ActorTargetSource *D_807F6000;
extern ActorTargetEntry *D_807F9420;
extern s16 D_807F9424;
extern s32 D_80747D70;

void *func_80610FE8(s32);
u8 func_80663FCC(s16);
s8 func_806531B8(f32, f32, f32, s32);
s32 func_80658B08(s8, void *, s16);

void actorInitTargetEntries(void) {
    s32 k = 0;
    s32 i;
    s32 res;

    D_807F9424 = 0;
    for (i = 0; i < D_80747D70; i++) {
        if (func_80663FCC(i)) {
            D_807F9424++;
        }
    }

    D_807F9420 = NULL;
    if (D_807F9424 != 0) {
        D_807F9420 = func_80610FE8(D_807F9424 * sizeof(ActorTargetEntry));
        for (i = 0; i < D_80747D70; i++) {
            s32 cond = func_80663FCC(i);
            u8 res = cond;
            if (cond) {
                s32 temp;
                D_807F9420[k].unk0 = D_807F6000[i].unk0;
                D_807F9420[k].unk2 = D_807F6000[i].unk4;
                D_807F9420[k].unk4 = D_807F6000[i].unk8;
                D_807F9420[k].unk6 = res;
                D_807F9420[k].u.s.unk7 = func_806531B8(D_807F6000[i].unk0, D_807F6000[i].unk4, D_807F6000[i].unk8, 0);
                temp = func_80658B08(D_807F9420[k].u.s.unk7, &D_807F9420[k].u.s.pad8, 4);
                if (temp != 4) {
                    D_807F9420[k].u.s.pad8[temp] = -1;
                }
                k++;
            }
        }
    }
}

typedef struct ActorTargetType {
    u8 pad[0x84];
    s16 unk84;
    u8 pad86[0xA];
} ActorTargetType;

u8 func_80663FCC(s16 arg0) {
    s16 val = ((ActorTargetType *)D_807F6000)[arg0].unk84;

    if (val == 1 || val == 0xC || val == 0x10 || val == 0xF3 || val == 0x134 || val == 0x135 || val == 0x138) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/68AA0/func_80664044.s")

