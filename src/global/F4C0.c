#include "common.h"

#ifdef NON_MATCHING
typedef struct {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    s16 unk4;
} MapActionEntry;

typedef struct { u8 unk0[0x5C]; u16 unk5C; } PlayerStateContext;
typedef struct { u8 unk0[0x1A4]; u8 unk1A4; } GlobalContextView;
typedef struct { u8 unk0[0x2C0]; u8 unk2C0; } PlayerRaceContext;

extern MapActionEntry D_80746340[];
extern s16 D_80745BDE[];
extern s32 D_8076A0A8;
extern PlayerStateContext *D_807FBB40;
extern s32 D_807FC924;
extern GlobalContextView *D_807FD580;

s16 func_8060A7C0(s16 arg0, void *arg1, u8 arg2) {
    s16 temp_v1;
    s32 var_v1 = 0;
    s32 var_v0;
    s16 *var_a1 = &D_80746340[var_v0 = 0].unk0;

    arg2 &= 0xFF;
    do {
        if ((arg0 == *var_a1) && (arg2 == *((u8 *)var_a1 + 2))) {
            var_v1 = 1;
        } else {
            var_v0++;
            var_a1 = (s16 *)((u8 *)var_a1 + 6);
        }
    } while ((var_v0 < 0xE) && (var_v1 == 0));
    if (var_v1 != 0) {
        if ((D_807FBB40->unk5C & 1) && (((PlayerRaceContext *)(D_807FC924 + D_807FD580->unk1A4 * 0x2F0))->unk2C0 == 2)) {
            return 0x97;
        }
        if (*((u16 *)((u8 *)arg1 + 0x6A)) & 4) {
            return 0xA;
        }
        temp_v1 = D_80746340[var_v0].unk4;
        if (temp_v1 == 0) {
            return *(s16 *)((u8 *)D_80745BDE + D_8076A0A8 * 4);
        }
        return temp_v1;
    }
    return arg0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/F4C0/func_8060A7C0.s")
#endif
