#include "common.h"
#include "actor.h"

extern u8 D_807444FC;
extern u8 D_80750AB4;
extern s16 D_807FDB34;

void *func_80610FE8(s32);
u32 func_806119A0(void);


#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80714670.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_807146A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_807146E0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_807146F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80714708.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80714778.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80714944.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80714950.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_8071495C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_8071496C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_8071497C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_8071498C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80714998.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_807149A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_807149B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_807149C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_807149FC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80714A08.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80714A28.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80714A38.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80714A58.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80714A68.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80714A9C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80714B84.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80714C08.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80714CC0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80714D08.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_8071509C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80715270.s")

typedef struct Ua2Effect {
    u8 pad0[0x20];
    u8 itemCount;
    u8 pad21[0x317];
    s32 resource;
    u8 pad33C[0x33];
    u8 mode;
    u8 pad370[0x14];
    void *allocation;
    u8 pad388[4];
    u16 flags;
    u8 pad38E[0xA];
    struct Ua2Effect *previous;
    struct Ua2Effect *next;
} Ua2Effect;

extern Ua2Effect *D_807FDB04;

void func_80715908(Ua2Effect *);

void func_8071586C(s32 arg0) {
    Ua2Effect *effect;

    effect = D_807FDB04;
    if (effect != NULL) {
        do {
            if (arg0 == effect->resource) {
                func_80715908(effect);
            }
            effect = effect->next;
        } while (effect != NULL);
    }
}

void func_807158C0(void) {
    Ua2Effect *effect;
    Ua2Effect *next;

    effect = D_807FDB04;
    if (effect != NULL) {
        do {
            next = effect->next;
            func_80715908(effect);
            effect = next;
        } while (next != NULL);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80715908.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80715A3C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80715B30.s")

f32 func_80715E38(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 x;
    f32 y;
    f32 z;

    x = arg0 - arg3;
    y = arg1 - arg4;
    z = arg2 - arg5;
    return sqrtf((x * x) + (y * y) + (z * z));
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80715E94.s")
