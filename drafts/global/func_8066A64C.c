// func_8066A64C (src/global/6AD90.c): near-miss: 68 insns, branch delay-slot choice addiu a0,sp,0x78 vs li t5,1 shifts subsequent regalloc
#include "common.h"
#include "actor.h"

extern u8 D_807444FC;
extern s32 D_8076A064;
extern Actor *D_807F9470;
extern f32 D_807F9474;
extern f32 D_807F9478;
extern f32 D_807F947C;
extern u32 D_807F9480;
extern s8 D_807F94B2;

void func_8062FF10(float [4][4], float [4][4]);

typedef struct {
    u8 pad0[0x48];
    u32 unk48;
    u32 unk4C;
    u32 unk50;
} R2D_StructA64C;

void func_8066A64C(s32 arg0, Actor *arg1, R2D_StructA64C *arg2, f32 arg3, f32 arg4, f32 arg5) {
    float sp78[4][4];
    float sp38[4][4];
    ActorSub140 *sub;
    u8 idx;
    Mtx *mtx;

    D_807F9470 = arg1;
    sub = arg1->unk140;
    if (D_8076A064 == sub->unk88) {
        idx = D_807444FC;
    } else {
        idx = (D_807444FC ^ 1) & 0xFF;
    }
    mtx = (Mtx *)((Mtx **)&sub->unk74)[idx];
    if ((arg2->unk4C != arg2->unk48) || (arg2->unk50 != arg2->unk48)) {
        D_807F94B2 = 1;
    }
    D_807F9480 = arg2->unk48;
    if (arg2->unk48 == -1) {
        memcpy(sp78, (void *)sub->unk70, 0x40);
    } else {
        guMtxL2F(sp78, (Mtx *)(((arg2->unk48 >> 6) << 6) + (u8 *)mtx));
    }
    func_8062FF10(sp38, sp78);
    guMtxXFMF(sp38, arg3, arg4, arg5, &D_807F9474, &D_807F9478, &D_807F947C);
}
