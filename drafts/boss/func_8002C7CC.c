// func_8002C7CC (src/boss/8520.c): stage 3: frame 48 vs 40 and var_t0/t1/v1 land in t1/t2/t0 instead of t0/t1/v1; expected keeps 'or t0,v0,zero' copy then andi t7,t0,0x80 (var_t0 own live range) -- copy propagation removes it in all tried forms (u8 var_t0 = val, a=val, (u8)val casts, val+=1 forms). Structure/branches already match.
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
    s32 val;

    val = D_807FDC90->unk28;
    var_t0 = val;
    val &= 0xF;
    var_t0 &= 0x80;
    if (var_t0 != 0) {
        val += 1;
        var_v1 = val & 0xFF;
        if (var_v1 < 2) {
            var_t1 = 0x8000;
            goto done;
        }
        var_t0 = 0;
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
