// func_8066A75C (src/global/699B0.c): near-miss: inner block scopes sp28 at 0x28, scalars land at 0x74/0x78/0x7C vs 0x70/0x74/0x78 (4 byte shift)
#include "common.h"
#include "actor.h"

extern u8 D_807444FC;
extern s32 D_8076A064;

void func_8066A75C(Actor *actor, u32 arg1, f32 *arg2, f32 arg3, f32 *arg4) {
    f32 sp78;
    f32 sp74;
    f32 sp70;
    ActorSub140 *sub;
    u8 idx;
    u32 mtxOffset;
    {
        float sp28[4][4];

        sp78 = *arg2;
        sp74 = *arg4;
        sub = actor->unk140;
        mtxOffset = (arg1 >> 6) << 6;
        if (D_8076A064 == sub->unk88) {
            idx = D_807444FC;
        } else {
            idx = (D_807444FC ^ 1) & 0xFF;
        }
        if (arg1 == -1) {
            memcpy(sp28, (void *)sub->unk70, 0x40);
        } else {
            guMtxL2F(sp28, (Mtx *)(mtxOffset + (u8 *)((Mtx **)&sub->unk74)[idx]));
        }
        guMtxXFMF(sp28, sp78, arg3, sp74, arg2, &sp70, arg4);
    }
}
