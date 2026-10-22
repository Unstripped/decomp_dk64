// func_8002C7CC (src/boss/8520.c): from .scratch/Boss3C/func_8002C7CC_best.c
#include "common.h"

typedef struct {
    char pad0[0x1A];
    u16 unk1A;
    u8 pad1C[0x28 - 0x1C];
    s32 unk28;
} BossA_Struct_807FDC90;

extern BossA_Struct_807FDC90 *D_807FDC90;
extern void *D_807FBB40;

void func_806883F4(void *, s32, s16, f32);

void func_8002C7CC(void) {
    u16 var_t1 = 0;
    u8 var_t0;
    s32 var_v1;
    s32 sp1C[1];
    s32 val = D_807FDC90->unk28;

    var_t0 = val & 0x80;
    val &= 0xF;
    if (var_t0 != 0) {
        var_v1 = (val + 1) & 0xFF;
        if (var_v1 < 2) {
            var_t1 = 0x8000;
            goto done;
        }
        var_t0 = 0;
        goto done;
    } else {
        var_v1 = (val - 1) & 0xFF;
        if (var_v1 <= 0) {
            var_t0 = 0x80;
            goto done;
        }
    }
    var_t1 = 0x8000;
done:
    sp1C[0] = (s16)var_v1;
    func_806883F4(D_807FBB40, 0, (s16)var_v1, 0.0f);
    func_806883F4(D_807FBB40, 1, sp1C[0], 0.0f);
    D_807FDC90->unk28 = var_t1 | var_v1 | var_t0;
}
