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

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613448.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_806134B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_806136B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613794.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613944.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613A50.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613AF8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613BA0.s")

typedef struct {
    void *unk0;
    u8 pad4[0xC];
    s16 unk10;
    u8 pad12[0x12];
    f32 unk24;
} P17bState;

typedef struct {
    P17bState *unk0;
} P17bStateHolder;

typedef struct {
    u8 pad0[4];
    P17bStateHolder *unk4;
} P17bControllerView;

void func_80613CA8(P17bControllerView *, s16, f32, f32);


void func_80613C48(P17bControllerView *arg0, s16 arg1, f32 arg2, f32 arg3) {
    P17bState *state;

    state = arg0->unk4->unk0;
    if (arg1 == state->unk10) {
        state->unk24 = *(f32 *)state->unk0;
        return;
    }
    func_80613CA8(arg0, arg1, arg2, arg3);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613CA8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613FB0.s")


#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614014.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614130.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_8061421C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614644.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614A54.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614A64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614B34.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614C38.s")
