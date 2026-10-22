// func_800253AC (src/boss/0.c): from .scratch/Boss3A/func_800253AC_best.c
#include "common.h"

typedef struct Boss3A_Struct_807FBB40_53AC {
    u8 pad0[0xC0];
    f32 unkC0;
} Boss3A_Struct_807FBB40_53AC;

extern struct BossA_Struct_807FBB40 *D_807FBB40;
extern u8 D_8071AF30;
extern u8 D_80720120;

void func_807149B8(s32);
void func_8071498C(void *);
void func_807149A8(s32);
void func_80714950(void *);
void func_80714C08(void *, f32, void *, s32, s32);

void func_800253AC(void) {
    f64 dval;
    f32 val;

    dval = (0.0 < (f64)((Boss3A_Struct_807FBB40_53AC *)D_807FBB40)->unkC0) ? (f64)((Boss3A_Struct_807FBB40_53AC *)D_807FBB40)->unkC0 : 0.0;
    func_807149B8(1);
    func_8071498C(&D_8071AF30);
    func_807149A8(1000);
    func_80714950(D_807FBB40);
    val = (f32)((f32)((dval / 150.0) * 0.12) + 0.3) * 4.0f;
    func_80714C08(&D_80720120, val, D_807FBB40, 3, 0);
    func_807149B8(1);
    func_8071498C(&D_8071AF30);
    func_807149A8(1000);
    func_80714950(D_807FBB40);
    func_80714C08(&D_80720120, val, D_807FBB40, 4, 0);
}
