#include "common.h"
#include "actor.h"

void *func_80610FE8(s32);

typedef struct {
    u8 unk0[0x118];
    void *unk118;
} AnimationOwner;

void heapFree(void *);

#pragma GLOBAL_ASM("asm/global/nonmatchings/1292F0/func_807245F0.s")

void animationOwnerFreeBuffer(AnimationOwner *arg0) {
    void *temp_a1;

    temp_a1 = arg0->unk118;
    if (temp_a1 != 0) {
        heapFree(temp_a1);
        arg0->unk118 = NULL;
    }
}

