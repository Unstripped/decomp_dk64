// func_800251A0 (src/boss/0.c): from .scratch/Boss3A/func_800251A0_best.c
#include "common.h"

typedef struct BossA_Struct_807FBB40 {
    u8 pad0[4];
} BossA_Struct_807FBB40;

typedef struct Boss2A_Struct_807FBB40_4FA8 {
    u8 pad0[0x154];
    u8 unk154;
    u8 unk155;
} Boss2A_Struct_807FBB40_4FA8;

extern BossA_Struct_807FBB40 *D_807FBB40;

void func_8002450C(u8 *, u8, s32);
u8 func_80024568(u8 *, u8, f32, f32, f32);
void func_8068842C(void *, s32, s32);

void func_800251A0(u8 arg0, u8 *arg1, s32 arg2, u8 *arg3) {
    u8 i;
    u8 cur;
    u8 res;

    i = 0;
    res = 0;
    switch (((Boss2A_Struct_807FBB40_4FA8 *)D_807FBB40)->unk155) {
    case 2:
        if (*arg3 != 0xFF) {
            do {
                func_8002450C(arg1, arg3[i++], 3);
            } while ((cur = arg3[i]) != 0xFF);
        }
        ((Boss2A_Struct_807FBB40_4FA8 *)D_807FBB40)->unk155 = 3;
        break;
    case 3:
        if (*arg3 != 0xFF) {
            do {
                res = func_80024568(arg1, arg3[i++], 10.0f, 20.0f, 30.0f);
            } while ((cur = arg3[i]) != 0xFF);
        }
        if (res != 0) {
            ((Boss2A_Struct_807FBB40_4FA8 *)D_807FBB40)->unk155 = 4;
            func_8068842C(D_807FBB40, 1, 1);
        }
        break;
    }
}
