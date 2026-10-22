#include "common.h"

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/func_80024000.s")

typedef struct BossA_Struct_80024524_Entry {
    u8 pad0;
    u8 unk1;
    s16 unk2;
    u8 pad4[4];
} BossA_Struct_80024524_Entry;

typedef struct BossA_Struct_8002413C_1 {
    u8 id;
    u8 unk1;
    u8 pad2[2];
    f32 x;
    f32 y;
    f32 z;
} BossA_Struct_8002413C_1;

typedef struct BossA_Struct_8002413C_3 {
    s8 unk0;
    u8 id;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} BossA_Struct_8002413C_3;

typedef struct BossA_Struct_8002413C_Template {
    s8 x;
    s8 y;
    s8 z;
    u8 pad3;
    f32 rotX;
    f32 rotY;
    f32 rotZ;
} BossA_Struct_8002413C_Template;

typedef struct BossA_Struct_807FBB40_Sub {
    u8 pad0[0x1C];
    union {
        BossA_Struct_80024524_Entry *entries;
        BossA_Struct_8002413C_3 *arr3;
    } u1C;
    BossA_Struct_8002413C_1 *arr2;
    BossA_Struct_8002413C_1 *arr1;
    u8 pad28[0x64 - 0x28];
    u16 unk64;
} BossA_Struct_807FBB40_Sub;

typedef struct BossA_Struct_807FBB40 {
    u8 pad0[4];
    BossA_Struct_807FBB40_Sub *sub;
    u8 pad8[0xE6 - 8];
    s16 unkE6;
    u8 padE8[0x146 - 0xE8];
    s16 unk146;
} BossA_Struct_807FBB40;

extern s32 D_8076A0A8;
extern BossA_Struct_807FBB40 *D_807FBB40;
extern u8 D_800358D8[5];
extern BossA_Struct_8002413C_Template D_800358E0[][5];
extern u8 D_80035994[8];

s32 func_8073110C(s32, s32);
void func_80724D28(s32, s32);
void func_80724DB0(s32, s32);
void func_80724CA4(s32, s32);

void func_8002413C(void) {
    s32 pad[4];
    u8 mode;
    s16 i;
    BossA_Struct_807FBB40_Sub *sub;
    BossA_Struct_8002413C_1 *v0;
    BossA_Struct_8002413C_1 *a0;
    BossA_Struct_8002413C_3 *a1;
    BossA_Struct_8002413C_Template *t;

    if (D_8076A0A8 == 8) {
        mode = 0;
    } else {
        mode = 1;
    }
    if (mode == 0) {
        if (func_8073110C(0x68, 2) != 0) {
            mode = 1;
            D_807FBB40->unk146 = 3;
        }
    }
    func_80724D28(1, 0xD);
    func_80724DB0(1, 5);
    func_80724CA4(1, 5);

    sub = D_807FBB40->sub;
    t = D_800358E0[mode];
    v0 = sub->arr1;
    a0 = sub->arr2;
    a1 = sub->u1C.arr3;

    for (i = 0; i < 5; i++) {
        v0->id = D_800358D8[i];
        v0->unk1 = 0xFF;
        v0->x = t[i].x;
        v0->y = t[i].y;
        v0->z = t[i].z;

        a0->id = D_800358D8[i];
        a0->unk1 = 0xFF;
        a0->x = t[i].rotX;
        a0->y = t[i].rotY;
        a0->z = t[i].rotZ;

        a1->unk0 = -0x80;
        a1->id = D_800358D8[i];
        a1->unk2 = 0;
        a1->unk4 = 0;
        a1->unk6 = 0;

        v0++;
        a0++;
        a1++;
    }

    for (i = 0; i < 8; i++) {
        v0->id = D_80035994[i];
        v0->unk1 = 0xFF;
        v0->x = 0.0f;
        v0->y = 0.0f;
        v0->z = 0.0f;
        v0++;
    }
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/func_80024300.s")

void func_8002450C(u8 *arg0, u8 arg1, u8 arg2) {
    arg0[arg1 + 6] = arg2;
}

void func_80024524(u8 arg0, s16 arg1) {
    BossA_Struct_80024524_Entry *entry = &D_807FBB40->sub->u1C.entries[arg0];
    if (arg0 == 3) {
        entry->unk1 = 0x2F;
    }
    entry->unk2 = arg1;
}


#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/func_80024568.s")

typedef struct BossA_Struct_80024EAC_DC90 {
    u8 pad0[8];
    s16 unk8;
} BossA_Struct_80024EAC_DC90;

typedef struct BossA_Struct_80024EAC_DC94 {
    u8 pad0[0x7C];
    f32 unk7C;
    u8 pad80[4];
    f32 unk84;
} BossA_Struct_80024EAC_DC94;

extern BossA_Struct_80024EAC_DC90 *D_807FDC90;
extern BossA_Struct_80024EAC_DC94 *D_807FDC94;

void func_80614D00(void *, f32, f32);
void func_80614EBC(void *, s32);
s32 func_806CC10C(s16, s16);
void func_8072AB74(s32, f32, f32, s32, f32);

void func_80024EAC(void) {
    s32 res;
    u16 sp2A;

    sp2A = D_807FBB40->sub->unk64;
    func_806CC10C(D_807FDC90->unk8, D_807FBB40->unkE6);
    func_8072AB74(0x45, D_807FDC94->unk7C, D_807FDC94->unk84, 0x16, 0.0f);
    res = func_806CC10C(D_807FDC90->unk8, D_807FBB40->unkE6);
    if (res > 0) {
        if (sp2A != 0x260) {
            func_80614EBC(D_807FBB40, 0x260);
        }
    } else if (res < 0) {
        if (sp2A != 0x25F) {
            func_80614EBC(D_807FBB40, 0x25F);
        }
    } else if (sp2A != 0x25A) {
        func_80614EBC(D_807FBB40, 0x25A);
        func_80614D00(D_807FBB40, 1.0f, 0.0f);
    }
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/func_80024FA8.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/func_800251A0.s")

void func_8066EA90(void *, s32);
void func_8066EA64(void *, s32);

void func_8002531C(void) {
    func_8066EA90(D_807FBB40, 3);
    func_8066EA90(D_807FBB40, 4);
    func_8066EA90(D_807FBB40, 5);
}

void func_80025364(void) {
    func_8066EA64(D_807FBB40, 3);
    func_8066EA64(D_807FBB40, 4);
    func_8066EA64(D_807FBB40, 5);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/func_800253AC.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/func_800254D0.s")

extern s32 D_8076A064;

s32 func_80611A44(void);
void func_80714998(s32);
void func_807149C8(s32, s32, s32, s32);
void func_8068588C(void *, s16, f32, f32, f32, f32, s32);

void func_80027770(void) {
    u8 val;

    if (!(D_8076A064 & 3)) {
        if (!(D_8076A064 & 0xF)) {
            val = 0xC;
        } else {
            val = ((func_80611A44() >> 15) % 0x7FFF) % 7 + 0x1D;
        }
        func_80714998(3);
        func_807149C8(0x50, 0x50, 0x50, 0xC8);
        func_8068588C(D_807FBB40, val, 2.0f, 0.0f, 0.0f, 0.0f, -0x78);
    }
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C00.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C14.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C28.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C3C.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C44.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C5C.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C78.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C94.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035CB8.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035CC0.s")
