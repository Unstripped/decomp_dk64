// func_80671D64 (src/global/70FD0.c): Closest diff: a2 vs v0 regalloc diff in loop unrolled by 4
#include "common.h"

typedef struct M70E_Node {
    f32 x;
    f32 y;
    f32 z;
    u8 padC[0xC];
    u32 unk18;
    struct M70E_Node *next;
} M70E_Node;

typedef struct M70E_SubActor {
    u8 pad0[0x74];
    s32 unk74[2];
    u8 pad7C[0xC];
    s32 unk88;
    void *unk8C;
    M70E_Node *unk90;
} M70E_SubActor;

typedef struct M70E_Actor {
    u8 pad0[0x140];
    M70E_SubActor *unk140;
} M70E_Actor;

extern u8 D_807444FC;
extern s32 D_8076A064;

s32 func_80671D64(M70E_Actor *arg0, s32 arg1) {
    M70E_SubActor *sub = arg0->unk140;
    s32 count = arg1 - 1;
    u8 val;
    M70E_Node *node;

    if (D_8076A064 == sub->unk88) {
        val = D_807444FC;
    } else {
        val = D_807444FC ^ 1;
    }

    node = sub->unk90;
    while (count != 0) {
        node = node->next;
        count--;
    }

    return (((u32)node->unk18 >> 6) << 6) + sub->unk74[val];
}
