// func_806634A4 (src/global/67890.c): 98% match, 1-instruction scheduling in prologue (addiu s3 vs lw s1) and late_rodata relocation
#include "common.h"
#include "actor.h"

typedef struct R2F684C0_Entry14 {
    f32 unk0;
    u8 pad4[0xC];
    u8 unk10;
    u8 unk11;
    u8 pad12[2];
} R2F684C0_Entry14;

extern R2F684C0_Entry14 *D_807F93F4;
extern s32 D_807F93F8;
s32 func_80663594(s32, s32);

s32 func_806634A4(s32 arg0) {
    s32 pad;
    volatile s32 sp38;
    f32 temp_fv0;
    f32 var_fs0;
    f32 var_fv1;
    s32 var_s0;
    s32 var_s1;
    s32 var_v0;
    R2F684C0_Entry14 *var_v1;

    var_fs0 = 100000000.0f;
    var_s1 = sp38;
    do {
        var_s0 = 0;
        var_fv1 = 0.0f;
        var_v0 = 0;
        if (D_807F93F8 > 0) {
            do {
                if (D_807F93F4[var_v0].unk11 != 0) {
                    temp_fv0 = D_807F93F4[var_v0].unk0;
                    if ((temp_fv0 < var_fs0) && (var_fv1 < temp_fv0)) {
                        var_s1 = var_v0;
                        var_fv1 = temp_fv0;
                        var_s0 = 1;
                    }
                }
                var_v0 += 1;
            } while (var_v0 < D_807F93F8);
        }
        var_fs0 = var_fv1;
        if (var_s0 != 0) {
            arg0 = func_80663594(arg0, var_s1);
        }
    } while (var_s0 != 0);
    sp38 = var_s1;
    return arg0;
}
