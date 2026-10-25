#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern Struct807FD580 *D_807FD580;
extern s16 D_807FD584;
extern s32 D_8076A0A8;
extern u8 D_8074E77C[];

void func_806F5270(void);
void func_806F4778(void);

void func_806F4750(void) {
    func_806F5270();
    func_806F4778();
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F4778.s")

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} F9N3_FloatTableEntry;

extern F9N3_FloatTableEntry D_807FD740[];
extern s32 D_807FD780[];

void func_806F4D70(u8 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    unsigned short temp_t6;
    F9N3_FloatTableEntry *temp_v0;
    f32 new_var;

    temp_t6 = arg0;
    temp_v0 = &D_807FD740[temp_t6];
    temp_v0->unk0 = arg1;
    new_var = arg4;
    temp_v0->unk4 = arg2;
    temp_v0->unk8 = arg3;
    temp_v0->unkC = new_var;
    D_807FD780[temp_t6] = 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F4DC0.s")

extern s16 D_80753EF0;

s32 func_806F4E74(s16 arg0) {
    s16 *var_a1;
    s32 var_v0;
    s32 var_v1;

    var_v1 = 0;
    var_v0 = 0;
    var_a1 = &D_80753EF0;
    do {
        if (arg0 == *var_a1) {
            var_v0 = 1;
        } else {
            var_v1++;
            var_a1 = (s16 *) ((u8 *) var_a1 + 0x14);
        }
    } while (var_v0 == 0);
    return var_v1;
}

extern s16 D_807FD722;
extern s16 D_807FD724;

s32 func_806F4EBC(f32 arg0, f32 arg1) {
    s32 temp_ft1;
    s32 temp_ft3;

    temp_ft3 = (s32) (arg0 / 500.0f);
    temp_ft1 = (s32) (arg1 / 500.0f);
    if ((D_807FD722 < temp_ft3) || (D_807FD724 < temp_ft1) || (arg0 < 0.0f) || (arg1 < 0.0f)) {
        return -1;
    }
    return (D_807FD722 * temp_ft1) + temp_ft3;
}

typedef struct F9F1_Rect {
    f32 unk0;
    u8 pad4[4];
    f32 unk8;
    f32 unkC;
} F9F1_Rect;

typedef struct F9F1_Node {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 padF;
    s16 unk10;
    u8 unk12;
    u8 unk13;
    u8 unk14;
    u8 pad15[3];
    struct F9F1_Node *next;
} F9F1_Node;

extern s8 D_807FCC4B[];
extern F9F1_Node **D_80754244;
extern s16 D_807FD726;
extern s16 D_807FD728;
extern F9F1_Node *D_807FD72C;
void func_806F6204(F9F1_Node *, u8, F9F1_Rect *);

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F4F50.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F50C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F5270.s")

typedef struct F9A_LinkedNode {
    s16 unk0;
    s16 unk2;
    u8 pad4[0x16];
    u8 unk1A;
    u8 pad1B;
    struct F9A_LinkedNode *next;
} F9A_LinkedNode;

extern F9A_LinkedNode *D_807FD730;
void heapFree(void *);

typedef struct F9A_CleanupNode {
    u8 pad0[0x18];
    struct F9A_CleanupNode *next;
} F9A_CleanupNode;



extern u8 D_807FD738;
void func_806F54E0(s32, s16, u8);
void func_806355DC(s16, s32);

void func_806F5378(void) {
    F9A_LinkedNode *var_s0;
    F9A_LinkedNode *var_s1;

    D_807FD738 = 1;
    var_s0 = D_807FD730;
    while (var_s0 != NULL) {
        var_s1 = var_s0->next;
        func_806F54E0(0, var_s0->unk2, var_s0->unk1A);
        func_806355DC(var_s0->unk0, 1);
        heapFree(var_s0);
        var_s0 = var_s1;
    }
    D_807FD730 = NULL;
}

typedef struct {
    s16 unk0;
    s16 unk2;
    u8 pad4[0xC];
    s16 unk10;
    u8 unk12;
    u8 unk13;
} F9A_SourceNode;

typedef struct {
    s16 unk0;
    s16 unk2;
    u8 pad4[0xC];
    u8 unk10;
    u8 pad11[3];
    f32 unk14;
    s8 unk18;
    u8 unk19;
    u8 unk1A;
} F9A_DestinationNode;

void *func_80610FE8(s32);

F9A_DestinationNode *func_806F53EC(F9A_SourceNode *arg0) {
    F9A_DestinationNode *temp_v0;

    temp_v0 = func_80610FE8(0x20);
    temp_v0->unk10 = 0;
    temp_v0->unk14 = 0.0f;
    temp_v0->unk0 = arg0->unk0;
    temp_v0->unk18 = arg0->unk10;
    temp_v0->unk2 = arg0->unk2;
    temp_v0->unk19 = arg0->unk12;
    temp_v0->unk1A = arg0->unk13;
    return temp_v0;
}

s32 func_806F544C(s32 arg0, s32 arg1, u8 arg2) {
    if ((arg1 == 0x91) || (arg1 == 0x15D) || (arg1 == 0x15E) || (arg1 == 0x15F) || (arg1 == 0x160)) {
        if (arg2 != 0) {
            arg0 = 3;
        }
    }
    return arg0;
}

void func_8061CC40(Actor *, s32, s32);
s32 func_8073110C(s32, s32);
void func_8073129C(s32, s32, s32);

void func_806F5498(void) {
    if (func_8073110C(0x16C, 0) == 0) {
        func_8061CC40(NULL, 0x20, 5);
        func_8073129C(0x16C, 1, 0);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F54E0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F58A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F5A48.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F5C30.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F5CE4.s")

extern s32 func_80611A44(void);
extern s32 D_80754248[];

void func_806F5D80(s32 *arg0, s32 *arg1) {
    *arg0 = D_80754248[((u32) (func_80611A44() >> 0xF) % 7U)];
    *arg1 = ((s32) ((s32) (func_80611A44() >> 0xF) % 32767) % 391) + 0xD2;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F5DF8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F5EB4.s")

s32 func_806F5C30(s32);
void func_806F5DF8(s32, s32, s16, s16, s16, s32);
s32 func_80714608(s32);

void func_806F5F2C(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4) {
    if ((func_80714608(0) != 0) && (func_806F5C30(arg0) != 0)) {
        func_806F5D80(&arg0, &arg1);
    }
    func_806F5DF8(arg0, 1, arg2, arg3, arg4, arg1);
}

void func_806F5FA0(s16 arg0, s16 arg1, s16 arg2) {
    func_806F5F2C(0x76, 0, arg0, arg1, arg2);
}

s32 func_806F5CE4();

void func_806F5FE8(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    if (func_806F5CE4() != 0) {
        func_806F5DF8(arg0, 0, arg1, arg2, arg3, arg4);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F603C.s")
#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F6204.s")


void func_806F6554(u8 arg0, F9F1_Rect *arg1) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    s32 temp_v0;

    if (D_807FCC4B[arg0 * 0x306] > 0) {
        temp_fv0 = arg1->unkC;
        temp_fa0 = arg1->unk0;
        if (temp_fa0 <= ((f32) D_807FD726 + temp_fv0)) {
            temp_fa1 = arg1->unk8;
            if (temp_fa1 <= ((f32) D_807FD728 + temp_fv0)) {
                temp_v0 = func_806F4EBC(temp_fa0, temp_fa1);
                if (temp_v0 >= 0) {
                    func_806F6204(D_80754244[temp_v0], arg0, arg1);
                }
            }
        }
        func_806F6204(D_807FD72C, arg0, arg1);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F6644.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F69A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F6E58.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F6EDC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F6F28.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F70A8.s")


#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F70FC.s")

f32 func_806F7378(s32 arg0) {
    if (arg0 == 0x8C) {
        return -13.0f;
    }
    return 0.0f;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F73A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F79E0.s")
