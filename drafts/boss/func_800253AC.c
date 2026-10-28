// func_800253AC (src/boss/0.c): stage 5: parked NON_MATCHING in src; ptr arg &D_8071AF30 as CSE'd s32 temp (spill) reproduces sw/lw a0 spill and frame 64; only diff: spill slots swapped (ptr at 36/val at 32, want ptr 32/val 36). Decl order/inline val/named p do not move it; permuter 150s no gain.
#include "common.h"

struct BossA_Struct_807FBB40;
extern struct BossA_Struct_807FBB40 *D_807FBB40;

typedef struct BsA_Struct_807FBB40_53AC {
    u8 pad0[0xC0];
    f32 unkC0;
} BsA_Struct_807FBB40_53AC;

extern u8 D_8071AF30;
extern u8 D_80720120;

void func_807149B8(s32);
void func_8071498C(void *);
void func_807149A8(s32);
void func_80714950();
void func_80714C08(void *, f32, void *, s32, s32);

void func_800253AC(void) {
    f32 val;
    s32 p;
    f64 dval;

    dval = (0.0 < (f64)((BsA_Struct_807FBB40_53AC *)D_807FBB40)->unkC0) ? (f64)((BsA_Struct_807FBB40_53AC *)D_807FBB40)->unkC0 : 0.0;
    p = (s32)&D_8071AF30;
    func_807149B8(1);
    func_8071498C((void *)p);
    func_807149A8(1000);
    func_80714950(D_807FBB40);
    val = (f32)((f32)((dval / 150.0) * 0.12) + 0.3) * 4.0f;
    func_80714C08(&D_80720120, val, D_807FBB40, 3, 0);
    func_807149B8(1);
    func_8071498C((void *)p);
    func_807149A8(1000);
    func_80714950(D_807FBB40);
    func_80714C08(&D_80720120, val, D_807FBB40, 4, 0);
}
