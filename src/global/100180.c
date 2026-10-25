#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern u8 D_807FC950[][0x5E];
extern s32 D_8076A0A8;
extern u8 D_8076A0AB;
extern u8 D_8076A0B1;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_807444F8;
extern u8 D_807444FC;

void func_806FB480(void) {
}

void func_806FB488(void) {
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FB490.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FB714.s")

typedef struct {
    u8 unk0[0x17C];
    s16 unk17C;
    u8 unk17E;
} R1F100180_Entry;

typedef struct {
    u8 unk0[8];
    s32 unk8;
} R1F100180_Heap;

void func_806FB490(u8, s32, s32, s16, s32, s8 *, s32);
extern R1F100180_Entry *D_80754A18[];
extern void *D_807FD7F0;
void *func_806FBB9C(s16);

void func_806FB8B0(s32 arg0) {
    s8 sp2F;

    sp2F = 0;
    func_806FBB9C(2);
    func_806FB490(D_80754A18[0]->unk17E, arg0, ((R1F100180_Heap *) D_807FD7F0)->unk8, D_80754A18[0]->unk17C, 2,
                  &sp2F, 0x30);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/D_8075DC20.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FB914.s")

s32 func_80610FE8(s32);
void heapClearBlock(s32);
extern u8 *D_807FD7F4;

void func_806FBB58(void) {
    s32 allocation;
    s32 *allocation_slot;
    s32 temp_v0;
    u8 **heap_buffer;

    D_807FD7F0 = func_80610FE8(0xAC);
    temp_v0 = func_80610FE8(0x2B);
    heap_buffer = &D_807FD7F4;
    allocation_slot = (s32 *)heap_buffer;
    allocation = (*allocation_slot = temp_v0);
    heapClearBlock(allocation);
}

void *func_8066B0F8(s32, s16, u8, s32);


void *func_806FBB9C(s16 arg0) {
    s16 temp_a1;
    s32 var_v1;
    u8 *temp_v0;

    temp_v0 = arg0 + D_807FD7F4;
    temp_a1 = arg0;
    var_v1 = temp_a1 * 4;
    if (*temp_v0 == 0) {
        arg0 = arg0;
        var_v1 = arg0 * 4;
        *(void **)((u8 *) D_807FD7F0 + var_v1) = func_8066B0F8(0xE, temp_a1, 1, 1);
        *(D_807FD7F4 + arg0) = 3;
    } else {
        *temp_v0 = 3;
    }
    return *(void **)((u8 *) D_807FD7F0 + var_v1);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FBC34.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FBD5C.s")

s16 func_806FBEAC(u8 *arg0) {
    s16 var_v1;
    u8 temp_v0;

    temp_v0 = *arg0;
    var_v1 = 0;
    arg0 += 1;
    if (temp_v0 != 0) {
        do {
            if (arg0[-1] != 0x20) {
                var_v1 += 1;
            }
            temp_v0 = arg0[0];
            arg0 += 1;
        } while (temp_v0 != 0);
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FBEF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FC530.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FCC88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FD094.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FD490.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FD7A8.s")

extern u8 D_80754A36[];

u8 func_806FD894(s16 arg0) {
    if (arg0 & 0x80) {
        arg0 ^= 0x80;
    }
    return D_80754A36[arg0 * 6];
}
