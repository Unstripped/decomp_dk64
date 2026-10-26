#include "common.h"
#include "actor.h"

extern s16 D_807FBB30;
extern s16 D_807FBB32;
extern Struct807FD580 *D_807FD580;

typedef struct {
    u8 unk0[0x50];
    void *unk50;
} P17aController;


void *func_80612E90(void *, s16, s32);
void func_80613794(P17aController *, s32);

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80612E90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613044.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_806130A4.s")

void func_80613194(P17aController *arg0, s16 arg1) {
    if (arg0->unk50 == NULL) {
        arg0->unk50 = func_80612E90(arg0, arg1, 0);
    }
}

void func_806131D4(P17aController *arg0, s16 arg1) {
    if (arg0->unk50 == NULL) {
        arg0->unk50 = func_80612E90(arg0, arg1, 1);
    }
}

void func_80613214(P17aController *arg0) {
    if (arg0->unk50 != NULL) {
        func_80613794(arg0, 2);
        arg0->unk50 = NULL;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_8061324C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613358.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_806133C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_806133F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613448.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_806134B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_806136B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613794.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_806138B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613944.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613A50.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613AF8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613BA0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613C48.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613CA8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613D6C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613E70.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613FB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614014.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614130.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_8061421C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614644.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614A54.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614A64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614B34.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614C38.s")
