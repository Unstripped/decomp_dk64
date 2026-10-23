#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065F1C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065F49C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065F4F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065F5F0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065F614.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065F678.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065F964.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065FB04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065FB64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065FD88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065FEB8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80660070.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80660520.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80660830.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_806608FC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80660D38.s")

s32 func_8066104C(s32 arg0) {
    return ~arg0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80661054.s")

typedef struct R1D63EC0_SubNode {
    u8 pad[0x64];
    u8 val;
    u8 pad65;
    u8 unk66;
} R1D63EC0_SubNode;

typedef struct R1D63EC0_Node {
    R1D63EC0_SubNode *sub;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 pad10[0x3A];
    u8 unk4A;
    u8 unk4B;
    u8 pad4C[4];
    struct R1D63EC0_Node *next;
} R1D63EC0_Node;

typedef struct R1D63EC0_Entry {
    void (*fn0)();
    void (*fn1)();
    void (*fn2)(R1D63EC0_Node *);
    void *res0;
    void *res1;
    u32 flags;
} R1D63EC0_Entry;

extern R1D63EC0_Node *D_807F93C0;
extern R1D63EC0_Entry D_80748A90[];

void func_80661264(s32 arg0, u8 arg1) {
    R1D63EC0_Node *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        node->sub->val = arg1;
    }
}

void func_806612B4(s32 arg0, u8 arg1) {
    R1D63EC0_Node *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        node->unk4A = arg1;
    }
}

u8 func_80661300(s32 arg0) {
    R1D63EC0_Node *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        return node->unk4B;
    }
    return 0;
}

void func_8066134C(s32 arg0, u8 arg1) {
    R1D63EC0_Node *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        node->unk4B = arg1;
    }
}

void func_80661398(s32 arg0, f32 arg1, f32 arg2) {
    R1D63EC0_Node *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        node->unk8 = arg1;
        node->unkC = arg2;
    }
}

void func_806613E8(s32 arg0, f32 arg1, f32 arg2) {
    R1D63EC0_Node *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        node->unk8 += arg1;
        node->unkC = arg2;
    }
}

void func_80661440(f32 *arg0) {
    R1D63EC0_Node *node = D_807F93C0;
    s32 i;
    for (i = 0; node != NULL && i < 32; i++) {
        arg0[i] = node->unk8;
        node = node->next;
    }
}

void func_80661484(f32 *arg0) {
    R1D63EC0_Node *node = D_807F93C0;
    s32 i;
    for (i = 0; node != NULL && i < 32; i++) {
        node->unk8 = arg0[i];
        node->unk4 = node->unk8;
        node = node->next;
    }
}

f32 func_806614D0(s32 arg0) {
    R1D63EC0_Node *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        return node->unk4;
    }
    return 0.0f;
}

extern u8 D_807F93C4;
extern f32 D_807F93C8[2];
extern f32 D_807F93D0;
extern f32 D_807F93D4;
extern f32 D_807F93D8;
extern f32 D_807F93DC;
extern f32 D_807F93E0;
extern f32 D_807F93E4;
extern f32 D_807F93E8;

void func_80661520(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    if (D_807F93C4 == 0) {
        D_807F93C8[0] = arg0;
        D_807F93C8[1] = arg1;
        D_807F93D4 = 0.0f;
        D_807F93D0 = arg2;
        D_807F93D8 = arg3;
        D_807F93DC = 0.0f;
        D_807F93E0 = arg4;
        D_807F93E4 = arg5;
        D_807F93E8 = (arg5 * 2) / 3.0f;
        D_807F93C4 = 1;
    }
}

void func_806615BC(void) {
    if (D_807F93C4 != 0) {
        D_807F93D4 += D_807F93D8;
        if (D_807F93D0 < D_807F93D4) {
            D_807F93D4 = D_807F93D0;
        }
        D_807F93DC += D_807F93E0;
        if (D_807F93E4 < D_807F93DC) {
            D_807F93C4 = 0;
        }
    }
}

void func_8066164C(void) {
    D_807F93C4 = 0;
}

typedef struct R1D63EC0_Struct1 {
    void *unk0;
    u8 pad4[0x18 - 4];
} R1D63EC0_Struct1;
extern R1D63EC0_Struct1 D_80748A9C[];
void *func_8066B0F8(s32, s32, s32, s32);

void func_80661658(u8 arg0) {
    D_80748A9C[arg0].unk0 = func_8066B0F8(7, 0x3C5, 1, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_806616A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_806618A0.s")

typedef struct R1D63EC0_Sub2 {
    u8 pad0[0x14];
    s32 unk14;
    s32 unk18;
    u8 pad1C[0x2C - 0x1C];
    s32 unk2C;
    s32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    u8 pad44[0x64 - 0x44];
    u8 val;
} R1D63EC0_Sub2;

typedef struct R1D63EC0_Obj2 {
    R1D63EC0_Sub2 *sub;
    u8 pad4[0x30 - 4];
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} R1D63EC0_Obj2;

void func_80661AB4(R1D63EC0_Obj2 *arg0) {
    arg0->sub->unk3C -= arg0->sub->unk34;
    if (arg0->sub->unk3C < 0.0) {
        arg0->sub->unk3C = 255.0f;
    }
    arg0->sub->unk40 -= arg0->sub->unk38;
    if (arg0->sub->unk40 < 0.0) {
        arg0->sub->unk40 = 255.0f;
    }
    arg0->unk30 += arg0->sub->unk14;
    arg0->unk34 += arg0->sub->unk18;
    arg0->unk38 += arg0->sub->unk2C;
    arg0->unk3C += arg0->sub->unk30;
}

void func_80661B84(u8 arg0) {
    D_80748A90[arg0].res0 = func_8066B0F8(0x19, 0x2EE, 1, 0);
    D_80748A90[arg0].res1 = func_8066B0F8(0x19, 0x2EF, 1, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80661BF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80661E34.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80661EC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80661F0C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80662108.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80662110.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80662158.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80662180.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80662188.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_806621D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_806623CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_806623D4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8066241C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_806625D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80662618.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_806627CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80662838.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80662AB4.s")
