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

typedef struct {
    u32 unk0;
    u32 unk4;
} Perm3Command;

typedef struct {
    Perm3Command *unk0;
} Perm3CommandArray;

typedef struct {
    u8 pad0[4];
    Perm3CommandArray *unk4;
} Perm3CommandStorage;

typedef struct {
    Perm3CommandStorage *unk0;
    u8 pad4[0x5C];
    u32 unk60;
} Perm3CommandOwner;

void func_80613358(Perm3CommandOwner *arg0, s32 arg1, Perm3Command *arg2) {
    u32 *arg2_words;
    Perm3Command *commands;
    Perm3Command *destination;

    arg2_words = &arg2->unk0;
    if (!(arg0->unk60 & 0x10)) {
        goto command_lookup;
command_lookup:
        commands = arg0->unk0->unk4->unk0;
        destination = commands + arg1;
        if ((destination->unk0 != *arg2_words) || (arg2->unk4 != destination->unk4)) {
            memcpy(destination, arg2, 8);
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_806133C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613448.s")

typedef struct {
    void *unk0;
    void *unk4;
    void *unk8;
    void *unkC;
    u8 pad10[0xC];
    void *unk1C;
    void *unk20;
    void *unk24;
} P17LAnim;

typedef struct {
    void *unk0;
    P17LAnim *unk4;
} P17LController;

void animListFree(void *);
void heapFreeDeferred();

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_806134B4.s")

void func_806136B4(P17LController *arg0) {
    void *temp_a1;
    void *temp_a1_2;
    void *temp_a1_3;

    func_80613794((P17aController *)arg0, 0);
    func_80613794((P17aController *)arg0, 1);
    func_80613794((P17aController *)arg0, 2);
    animListFree((u8 *)arg0 + 0x158);
    func_80613944(arg0, arg0->unk4->unk0);
    func_80613944(arg0, arg0->unk4->unk4);
    func_80613944(arg0, arg0->unk4->unk8);
    func_80613944(arg0, arg0->unk4->unkC);
    temp_a1 = arg0->unk4->unk1C;
    if (temp_a1 != NULL) {
        heapFreeDeferred(temp_a1);
    }
    temp_a1_2 = arg0->unk4->unk20;
    if (temp_a1_2 != NULL) {
        heapFreeDeferred(temp_a1_2);
    }
    temp_a1_3 = arg0->unk4->unk24;
    if (temp_a1_3 != NULL) {
        heapFreeDeferred(temp_a1_3);
    }
    heapFreeDeferred(arg0->unk4);
}

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

typedef struct {
    u8 pad0[4];
    f32 unk4;
} P17cParent;

typedef struct {
    P17cParent *unk0;
} P17cState;

typedef struct {
    u8 pad0[4];
    P17cState *unk4;
} P17cStateOwner;

f32 func_80614A54(P17cStateOwner *arg0) {
    return arg0->unk4->unk0->unk4;
}

typedef struct {
    u8 pad0[4];
    void *unk4;
    s32 unk8;
    u8 padC[0x54];
    s32 unk60;
    u8 pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} P17cActorView;

extern u8 D_807444FC;
void func_806195D0(f32, f32);
void actorTouchSub140Timestamp();
void func_80614A64(P17cActorView *arg0) {
    f32 x = arg0->unk7C;
    if (x >= -8192.0f) {
        f32 y = arg0->unk80;
        if (y >= -8192.0f) {
            f32 z = arg0->unk84;
            if ((z >= -8192.0f) && (x <= 8192.0f) && (y <= 8192.0f) && (z <= 8192.0f)) {
                arg0->unk8 = *(s32 *) ((u8 *) arg0->unk4 + (D_807444FC * 4) + 0x14);
                func_806195D0(z, 8192.0f);
                actorTouchSub140Timestamp(arg0);
                arg0->unk60 |= 0x200;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614B34.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614C38.s")
