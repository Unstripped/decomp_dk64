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

extern void *D_80754280;

s32 func_806F7FD0(arg0)
u8 arg0;
{
    return (arg0 * 0x2D0) + (s32)D_80754280;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8004.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8170.s")

typedef struct R2FCCD0cSlot {
    void *unk0;
    u8 pad4[0x1C];
    s32 unk20;
    s32 unk24;
    void *unk28;
    u8 unk2C;
    u8 pad2D[3];
} R2FCCD0cSlot;


#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8278.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F833C.s")

extern s32 func_806F7FD0(s32);
void func_806F8A8C(u8 arg0, u8 arg1, s32 arg2) {
    *(s16 *)((u8 *)func_806F7FD0(arg1 & 0xFF) + (arg0 * 0x30) + 4) = arg2;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8AD4.s")

void func_806F8BC4(s32 arg0, u8 arg1, s32 arg2) {
    R2FCCD0cSlot *temp_v0;

    if ((D_807FC928 < 2) && (func_807142D8() == 0)) {
        if (arg0 == 8) {
            func_806F8BC4(9, arg1, arg2 + 0xA);
            if (D_8076A0A8 == 0xF) {
                return;
            }
        }
        ((R2FCCD0cSlot *)D_80754280)[arg0].unk24 = arg1;
        temp_v0 = &((R2FCCD0cSlot *)D_80754280)[arg0];
        if (temp_v0->unk20 == 0) {
            temp_v0->pad4[3] = arg2;
        } else {
            temp_v0->pad4[3] = 0;
        }
        ((R2FCCD0cSlot *)D_80754280)[arg0].unk20 = 1;
        temp_v0 = &((R2FCCD0cSlot *)D_80754280)[arg0];
        if (temp_v0->pad4[2] == 0) {
            temp_v0->pad4[2] = arg1 != 0;
        }
    }
}


void func_806F8CB0(s32 arg0) {
    s32 var_v1;
    void *var_v0;

    if (arg0 == 8) {
        var_v0 = *(void **)((u8 *)D_80754280 + (arg0 * 0x30) + 0x28);
        var_v1 = 0;
        if (var_v0 != NULL) {
            do {
                *(s32 *)((u8 *)var_v0 + 0xC) = var_v1;
                var_v0 = *(void **)((u8 *)var_v0 + 0x18);
                var_v1 += 2;
            } while (var_v0 != NULL);
        }
    }
}


void func_806F8CFC(arg0, arg1)
s32 arg0;
u8 arg1;
{
    s32 temp_v0;

    temp_v0 = arg0 * 0x30;
    *((u8 *)D_80754280 + temp_v0 + 7) = 0;
    *((u8 *)D_80754280 + temp_v0 + 6) = 0;
    if (arg0 == 8) {
        func_806F8D58(9, 0);
    }
}

extern void *D_80754284;

int func_806F8D58(arg0)
s32 arg0;
{
    s32 mask;
    void *var_v0 = D_80754284;

    *((u8 *)D_80754280 + (arg0 * 0x30) + 0x1C) = 0;
    if (var_v0 != NULL) {
        mask = ~(1 << arg0);
        do {
            *(s32 *)var_v0 &= mask;
            var_v0 = *(void **)((u8 *)var_v0 + 4);
        } while (var_v0 != NULL);
    }
    func_806F8CFC();
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8DC4.s")

extern s32 func_80731AA8(s32, s32, s32);

void func_806F8EB4(void) {
    func_80731AA8(0x24D, 0x14, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8EDC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F91B4.s")

extern s32 func_805FF030();

void func_806F93EC(u16 *arg0, s32 arg1) {
    *arg0 |= 1 << func_805FF030(arg1 & 0xFF, 1);
}

void func_806F942C(u16 *arg0, s32 arg1) {
    *arg0 &= ~(1 << func_805FF030(arg1 & 0xFF, 1));
}


s32 func_806F9470(u16 arg0, s32 arg1) {
    return (1 << func_805FF030(arg1 & 0xFF, 1)) & arg0 & 0xFF;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F94AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9518.s")

void func_806F9518(s32);

void func_806F95C8(void) {
    s32 i;

    i = 0;
    do {
        func_806F9518(i);
        i++;
    } while (i != 0xF);
}

typedef struct R1FCCD0bAllocRecord {
    s32 unk0;
    u8 pad4[0x10];
    void *unk14;
} R1FCCD0bAllocRecord;

void *func_80610FE8(s32);
void heapClearBlock(void *);

void func_806F9608(R1FCCD0bAllocRecord **arg0) {
    R1FCCD0bAllocRecord *temp;

    temp = func_80610FE8(0x1C);
    *arg0 = temp;
    heapClearBlock(temp);
    (*arg0)->unk0 = 1;
    (*arg0)->unk14 = func_80610FE8(0xC);
    heapClearBlock((*arg0)->unk14);
}

void func_806F966C(R1FCCD0bAllocRecord **arg0) {
    R1FCCD0bAllocRecord *temp;

    temp = func_80610FE8(0x1C);
    *arg0 = temp;
    heapClearBlock(temp);
    (*arg0)->unk0 = 0;
    (*arg0)->unk14 = func_80610FE8(0x88);
    heapClearBlock((*arg0)->unk14);
}

typedef struct R1FCCD0bEffect {
    u8 pad0[4];
    f32 unk4;
    f32 unk8;
    s32 unkC;
} R1FCCD0bEffect;

void func_806F96CC(R1FCCD0bEffect *arg0, u32 arg1) {
    s32 var_v0;
    s32 var_v1;

    var_v0 = 0;
    var_v1 = 0;
    arg0->unkC = 0;
    switch (arg1) {
    case 0:
    case 13:
    case 14:
        var_v0 = -1;
        break;
    case 9:
    case 10:
    case 12:
        var_v1 = 1;
        break;
    default:
        var_v0 = 1;
        break;
    }
    arg0->unk4 = (f32)(var_v0 * 0x30);
    arg0->unk8 = (f32)(var_v1 * 0x30);
}

typedef struct R1FCCD0bEffectNode {
    u8 pad0[2];
    s16 unk2;
    u8 unk4;
    u8 pad5[3];
    void *unk8;
} R1FCCD0bEffectNode;

void func_806F94AC(void *, s32);
s32 func_806FACE8(s32);
void func_80714944(s32);
void func_80714950(void *);
void func_8071495C(void);
void func_8071498C(void (*)(void));
void func_80714998(u8);
void func_807149C8(s32, s32, s32, s32);
void func_807149FC(s32);
void func_80714A28(s32);
void *func_80714CC0(s32, f32, f32, f32, f32);
void func_8071BE04(void);

void func_806F9744(void *arg0, s32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    u8 unused_byte;
    s32 unused_word;
    s32 sp2C;
    R1FCCD0bEffectNode *temp_s0;

    temp_s0 = *(R1FCCD0bEffectNode **)((u8 *)arg0 + 0x14);
    sp2C = 2;
    func_8071495C();
    func_807149FC(-1);
    if (arg1 == 0xE) {
        sp2C = 1;
    }
    func_80714998(((u8 *)&sp2C)[3]);
    func_80714944(arg4);
    func_80714950(arg0);
    func_8071498C(func_8071BE04);
    func_80714A28(0x21);
    if (arg1 == 3) {
        func_807149C8(0xFF, 0, 0, 0xFF);
    }
    temp_s0->unk8 = func_80714CC0(func_806FACE8(arg1), 1.0f, arg2, arg3, -10.0f);
    temp_s0->unk2 = 0;
    if (arg1 == 7) {
        temp_s0->unk4 = 1;
    } else {
        temp_s0->unk4 = 0;
    }
    func_806F94AC(temp_s0->unk8, arg1);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9848.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9AF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9B64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9CD0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9D8C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FA1A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FA504.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FA5A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FA7A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FA7BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FA9C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FAB20.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FAC64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FACE8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FAFE4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FB218.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FB290.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FB2B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FB370.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FB3D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FB418.s")
