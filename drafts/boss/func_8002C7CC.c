// func_8002C7CC (src/boss/8520.c): stage 3: branch layout, regs (t0/t1/v1/v0), copy 'or t0,v0,zero' and slots all match (var_t0 = val & 0x80 then val &= 0xF, 'if (var_v1 >= 2) {var_t0=0; goto done;} var_t1=0x8000; goto done;' else-branch 'val -= 1'); remaining: frame 48 vs 40 + $t ring (t9/t4/t2/t3 vs t3/t6/t4/t5). Expected has only 3 named locals (var_t1 u16,var_t0 u8,var_v1 s32: homes 38,37 + spill 32/28); the 4th named local 'val' costs +8 frame, and every attempt to make val an expression temp (inline D->unk28&0xF, block scope, register, K&R param) loses the hoisted 'andi t8,v0,0xf; move v0,t8' before the branch.
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
    s32 var_v1;
    s32 val;
    u16 var_t1 = 0;
    u8 var_t0;

    val = D_807FDC90->unk28;
    var_t0 = val & 0x80;
    val &= 0xF;
    if (var_t0) {
        val += 1;
        var_v1 = val & 0xFF;
        if (var_v1 >= 2) {
            var_t0 = 0;
            goto done;
        }
        var_t1 = 0x8000;
        goto done;
    } else {
        val -= 1;
        var_v1 = val & 0xFF;
        if (var_v1 <= 0) {
            var_t0 = 0x80;
            goto done;
        }
    }
    var_t1 = 0x8000;
done:
    func_806883F4(D_807FBB40, 0, (s16)var_v1, 0.0f);
    func_806883F4(D_807FBB40, 1, (s16)var_v1, 0.0f);
    D_807FDC90->unk28 = var_t1 | var_v1 | var_t0;
}
