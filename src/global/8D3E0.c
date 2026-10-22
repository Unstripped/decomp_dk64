#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_806886E0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80688940.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80688A6C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80688C30.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80688C84.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80688CC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80688CF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80688D20.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80688E08.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80688E68.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80688EA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80688EE4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80688F74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80688FC0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80689064.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80689114.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_806891D8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80689250.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80689418.s")

void func_80689710(s32, s32);

void func_806896D0(s32 arg0) {
    func_80689710(arg0, 1);
}

void func_806896F0(s32 arg0) {
    func_80689710(arg0, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80689710.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_806897F0.s")

typedef struct ActD3B_Node {
    char pad[0x44];
    Actor *unk44;
    u8 unk48;
    char pad49[3];
    u8 unk4C;
    char pad4D[0x5A - 0x4D];
    s16 unk5A;
    char pad5C[0x68 - 0x5C];
    struct ActD3B_Node *next;
} ActD3B_Node;

extern ActD3B_Node *D_807FC400;
void heapFree(void *);

void func_806898A8(void) {
    ActD3B_Node *node;
    ActD3B_Node *next;

    node = D_807FC400;
    if (node != NULL) {
        do {
            next = node->next;
            heapFree(node);
            node = next;
        } while (node != NULL);
    }
    D_807FC400 = NULL;
}

s32 func_806898F8(void) {
    ActD3B_Node *node;
    s32 count;

    node = D_807FC400;
    count = 0;
    if (node != NULL) {
        do {
            if (node->unk4C == 0 || (node->unk44 != NULL && (node->unk44->unk64 & 0x400))) {
                count++;
            }
            node = node->next;
        } while (node != NULL);
    }
    return (count * 0x38) + 4;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80689958.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80689A80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80689B10.s")

s32 func_80689BAC(s16 arg0) {
    ActD3B_Node *node;
    s32 found = 0;

    node = D_807FC400;
    if (node != NULL) {
        do {
            if (arg0 == node->unk5A) {
                found = 1;
            } else {
                node = node->next;
            }
        } while (node != NULL && found == 0);
    }
    if (!found) {
        return 0;
    }
    if (node->unk48 != 0) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80689C20.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80689DD4.s")

s32 func_80689E98(s32 arg0) {
    return 1;
}

typedef struct ActD3B_StructSub {
    char pad[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x114 - 0x88];
    void *unk114;
    char pad118[0x12C - 0x118];
    s16 unk12C;
    char pad12E[0x154 - 0x12E];
    u8 unk154;
} ActD3B_StructSub;

typedef struct ActD3B_Struct1 {
    char pad[0x10];
    f32 unk10;
    f32 unk14;
    f32 unk18;
    char pad1C[0x44 - 0x1C];
    ActD3B_StructSub *unk44;
    u8 unk48;
    u8 pad49;
    s16 unk4A;
    char pad4C[0x54 - 0x4C];
    f32 unk54;
    char pad58[0x5A - 0x58];
    s16 unk5A;
} ActD3B_Struct1;

s32 func_80652E58(s32, void *);
s32 func_80689F2C(void);
u8 func_80689F80(ActD3B_Struct1 *);

void func_80689EA4(ActD3B_Struct1 *arg0) {
    if (func_80689F2C()) {
        func_80652E58(arg0->unk4A, arg0);
    } else {
        func_80689F80(arg0);
    }
}

u8 func_80689FEC(ActD3B_Struct1 *);

u8 func_80689EE4(ActD3B_Struct1 *arg0) {
    if (func_80689F2C()) {
        return func_80652E58(arg0->unk44->unk12C, arg0) == 0;
    }
    return func_80689FEC(arg0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80689F2C.s")

f32 func_80689DD4(f32, f32, f32);

u8 func_80689F80(ActD3B_Struct1 *arg0) {
    s32 var_a0 = func_80652E58(arg0->unk4A, arg0) != 0;
    if (var_a0 != 0) {
        f32 dist = func_80689DD4(arg0->unk10, arg0->unk14, arg0->unk18);
        var_a0 = 0;
        if (dist < arg0->unk54) {
            var_a0 = 1;
        }
    }
    return var_a0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80689FEC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_8068A074.s")

s32 func_8068A10C(s32 arg0) {
    return 0;
}


u8 func_8068A118(ActD3B_Struct1 *arg0) {
    s32 var_v1;
    f32 dist = func_80689DD4(arg0->unk10, arg0->unk14, arg0->unk18);
    var_v1 = 0;
    if (dist < arg0->unk54) {
        var_v1 = 1;
    }
    return var_v1;
}

u8 func_8068A164(ActD3B_Struct1 *arg0) {
    return !(func_80689DD4(arg0->unk44->unk7C, arg0->unk44->unk80, arg0->unk44->unk84) < arg0->unk54);
}

extern s16 D_807FC5D0[16];
extern s16 D_807FC5F0[16];
extern u8 D_807FC610;
extern u8 D_807FC611;

void func_8068A1B8(void) {
    D_807FC610 = 0;
    D_807FC611 = 0;
}

void func_8068A1CC(s16 arg0) {
    if (D_807FC610 != 0x10) {
        D_807FC5D0[D_807FC610++] = arg0;
    }
}

void func_8068A20C(s16 arg0) {
    if (D_807FC611 != 0x10) {
        D_807FC5F0[D_807FC611++] = arg0;
    }
}

s32 func_8068A24C(ActD3B_Struct1 *arg0) {
    s32 i;
    for (i = 0; i < D_807FC610; i++) {
        if (arg0->unk5A == D_807FC5D0[i] && arg0->unk48 == 0) {
            return 1;
        }
    }
    return 0;
}

s32 func_8068A2A4(ActD3B_Struct1 *arg0) {
    s32 i;
    for (i = 0; i < D_807FC611; i++) {
        if (arg0->unk5A == D_807FC5F0[i] && arg0->unk48 != 0) {
            return 1;
        }
    }
    return 0;
}

void func_8066E6C8(Actor *, s32, s32);

void func_8068A2FC(Actor *arg0) {
    arg0->unk128 = 0;
    arg0->unk60 &= ~0x8000;
    arg0->unk144 = 1;
    arg0->unk138 = 0;
    arg0->unk154 = 0x63;
    func_8066E6C8(arg0, 0, 0);
}
