// func_800254D0 (src/boss/0.c): from .scratch/Boss3B/func_800254D0_best.c
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

typedef struct Boss2A_Struct_807FBB40_4300 {
    u8 pad0[4];
    BossA_Struct_807FBB40_Sub *sub;
    u8 pad8[0x7C - 8];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} Boss2A_Struct_807FBB40_4300;

typedef struct Boss2A_Struct_807FDC90_4300 {
    u8 pad0[0x2C];
    s16 unk2C;
} Boss2A_Struct_807FDC90_4300;
struct BossA_Struct_80024EAC_DC90;
extern struct BossA_Struct_80024EAC_DC90 *D_807FDC90;
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
f32 func_80612794(s16);
f32 func_80612790(s16);

void func_80024300(void) {
    s16 var_s2;
    BossA_Struct_8002413C_1 *var_s0;
    s32 var_a3;
    s32 var_v1;
    s16 temp_lo;

    var_s0 = D_807FBB40->sub->arr1;
    var_a3 = 0;
    var_v1 = 0xFF;
    switch (((Boss2A_Struct_807FDC90_4300 *)D_807FDC90)->unk2C) {
    case 19:
        var_a3 = 0x22;
        break;
    case 17:
        var_a3 = 0xF6;
        break;
    case 15:
        var_a3 = 0x17;
        break;
    case 13:
        var_a3 = 0xED;
        break;
    case 11:
        var_a3 = 0x18;
        break;
    case 9:
        var_a3 = 0x22;
        var_v1 = 0xC8;
        break;
    case 7:
        var_a3 = 0xED;
        var_v1 = 0x82;
        break;
    case 5:
        var_a3 = 0x18;
        var_v1 = 0x46;
        break;
    case 3:
        var_a3 = 0x3C;
        break;
    }

    if (var_a3 != 0) {
        func_806086CC(((Boss2A_Struct_807FBB40_4300 *)D_807FBB40)->unk7C,
                      ((Boss2A_Struct_807FBB40_4300 *)D_807FBB40)->unk80,
                      ((Boss2A_Struct_807FBB40_4300 *)D_807FBB40)->unk84,
                      var_a3, var_v1, 0x7F, 1, 0x1E, 0.3f, 0);
    }

    var_s2 = 0;
    D_807FBB40->sub->arr1[5].x = 99999.0f;
    do {
        if (var_s0->y >= 1800.0f) {
            var_s0->x = 99999.0f;
            var_s0->y = 99999.0f;
            var_s0->z = 99999.0f;
            var_s0++;
        } else {
            temp_lo = var_s2 * 400;
            var_s0->x += 200.0f * func_80612794(temp_lo);
            var_s0->z += 200.0f * func_80612790(temp_lo);
            var_s0->y += 100.0f;
            var_s0++;
        }
        var_s2++;
    } while (var_s2 < 13);
}

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

typedef struct Boss2A_Struct_807FBB40_4FA8 {
    u8 pad0[0x154];
    u8 unk154;
    u8 unk155;
} Boss2A_Struct_807FBB40_4FA8;

u8 func_80024568(u8 *, u8, f32, f32, f32);
void func_8068842C(void *, s32, s32);

void func_80024FA8(u8 arg0, u8 *arg1, s32 arg2, u8 *arg3) {
    u8 i;
    u8 cur;
    u8 res;

    i = 0;
    res = 0;
    switch (((Boss2A_Struct_807FBB40_4FA8 *)D_807FBB40)->unk155) {
    case 2:
        if (*arg3 != 0xFF) {
            do {
                func_8002450C(arg1, arg3[i++], 1);
            } while ((cur = arg3[i]) != 0xFF);
        }
        ((Boss2A_Struct_807FBB40_4FA8 *)D_807FBB40)->unk155 = 3;
        break;
    case 3:
        if (*arg3 != 0xFF) {
            do {
                if (((Boss2A_Struct_807FBB40_4FA8 *)D_807FBB40)->unk154 == 0x27 ||
                    ((Boss2A_Struct_807FBB40_4FA8 *)D_807FBB40)->unk154 == 0x2E) {
                    res = func_80024568(arg1, arg3[i++], 50.0f, 70.0f, 90.0f);
                } else {
                    res = func_80024568(arg1, arg3[i++], 10.0f, 15.0f, 50.0f);
                }
            } while ((cur = arg3[i]) != 0xFF);
        }
        if (res != 0) {
            ((Boss2A_Struct_807FBB40_4FA8 *)D_807FBB40)->unk155 = 4;
            func_8068842C(D_807FBB40, 1, 1);
        }
        break;
    }
}

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

typedef struct Boss3B_178 {
    u8 pad0[0x12];
    u16 unk12;
    u8 unk14;
    u8 unk15;
    u8 pad16[2];
    u8 unk18;
    u8 unk19;
} Boss3B_178;

typedef struct Boss3B_Sp78 {
    u8 unk0;
    u8 pad1[0xF];
    s16 unk10;
    s16 unk12;
} Boss3B_Sp78;

typedef struct Boss3B_Sub4 {
    u8 pad0[0x10];
    s16 unk10;
} Boss3B_Sub4;

typedef struct Boss3B_Unk4 {
    Boss3B_Sub4 *unk0;
    u8 pad4[0x34 - 4];
    f32 unk34;
    f32 unk38;
} Boss3B_Unk4;

typedef struct Boss3B_Actor {
    u8 pad0[4];
    Boss3B_Unk4 *unk4;
    u8 pad8[0x60 - 8];
    u32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[4];
    s16 unk70;
    s16 unk72;
    u8 pad74[8];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB4 - 0x88];
    f32 unkB4;
    f32 unkB8;
    u8 padBC[4];
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
    u8 padCC[0xE6 - 0xCC];
    s16 unkE6;
    u8 padE8[0xEE - 0xE8];
    s16 unkEE;
    u8 padF0[0x12A - 0xF0];
    s16 unk12A;
    u8 pad12C[0x138 - 0x12C];
    s32 unk138;
    u8 pad13C[8];
    u8 unk144;
    u8 pad145;
    s16 unk146;
    u8 pad148[0xC];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x16A - 0x156];
    u8 unk16A;
    u8 unk16B;
    u8 unk16C;
    u8 pad16D[0x178 - 0x16D];
    Boss3B_178 *unk178;
    Boss3B_Sp78 *unk17C;
} Boss3B_Actor;

typedef struct Boss3B_DC90 {
    u8 pad0[0xA];
    s16 unkA;
    u8 padC[2];
    s16 unkE;
    u8 pad10[0x2C - 0x10];
    s16 unk2C;
    s16 unk2E;
} Boss3B_DC90;

typedef struct Boss3B_DC94 {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} Boss3B_DC94;

typedef struct Boss3B_DC98 {
    u8 pad0[0x2C];
    f32 unk2C;
    f32 unk30;
    u8 pad34[4];
    f32 unk38;
} Boss3B_DC98;

typedef struct Boss3B_DCA0_Sub {
    u8 pad0[0x28];
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    u8 pad2E[0x82 - 0x2E];
    s16 unk82;
    u8 pad84[2];
    s16 unk86;
} Boss3B_DCA0_Sub;

typedef struct Boss3B_DCA0 {
    u8 pad0[0x14];
    Boss3B_DCA0_Sub *unk14;
} Boss3B_DCA0;

extern Boss3B_Actor *D_807FBB44;
extern Boss3B_Actor *D_807FBB4C;
extern u8 D_807FBB70[];
extern Boss3B_DC98 *D_807FDC98;
extern Boss3B_DCA0 *D_807FDCA0;

extern u8 *D_800358B0[];
extern u8 D_80035980;
extern u8 D_80035984;
extern u8 D_80035988;
extern u8 D_80035CB8;
extern u8 D_80035CC0[];
extern f32 D_80035D68;
extern f32 D_80035D6C;
extern f32 D_80035ED8;
extern f32 D_80035ECC;
extern f32 D_80035EF0;
extern f32 D_80035EF4;
extern f32 D_80035EF8;
extern f32 D_80035F44;
extern f32 D_80035F68;
extern f32 D_80035F88;
extern s32 D_80627F04;
extern s32 D_80661054;
extern s32 D_80661264;
extern u8 D_807444EC;
extern s8 D_80750190;
extern s16 D_807502D8;
extern f32 D_807502F4;
extern s32 D_8076A064;
extern s16 D_80770628[];
extern s16 D_80770710[];
extern s32 D_807F5D10;

void func_80024000();
void func_80024EAC();
void func_800251A0();
void func_800253AC();
void func_80027770();
void func_80027840();
void func_80027BA8(u8 *, s32, f32);
void func_80028478();
void func_80604CBC(void *, s32, s32, s32, s32, s32, f32, s32);
void func_80605314();
s32 func_80611A44();
void func_80613C48(void *, s16, f32, f32);
void func_80613CA8(s32, s16, f32, f32);
s32 func_8061CB50();
void func_8061CC40(void *, s32, s32);
void func_8061F0B0();
void func_80626110();
s32 func_80629148();
void func_80629174();
void func_806319C4();
void func_80661520(f32, f32, f32, f32, f32, f32);
s32 func_80665DE0(f32, f32, f32, f32);
void func_8067E2E4(void *, s32, f32);
void func_80684A00();
void func_8068581C(void *, s32, f32, f32, f32, f32, s32);
void func_8068780C();
void func_80688370(void *, s32, f32);
void func_806883C8();
s32 func_80688540();
void func_806907F0(f32, f32, f32);
void func_80690814();
void func_8069084C(s32, s32, f32, s16, f32, f32, void *);
void func_80690A28(s32, s16, f32, f32, f32, f32, f32, void *);
void func_80690AB0(s16, s32, s32, s32, f32, f32, f32, f32, f32, void *);
void func_80691830(s32, f32, s32, s32, s32, s32, f32, f32, f32, f32);
void func_807248B0(void *, f32);
s32 func_8072881C();
void func_80729B00();
void func_8072A450();
s32 func_8072D13C();

#define D_807FBB40 ((Boss3B_Actor *)D_807FBB40)
#define D_807FDC90 ((Boss3B_DC90 *)D_807FDC90)
#define D_807FDC94 ((Boss3B_DC94 *)D_807FDC94)
void func_800254D0(void) {
    s32 pad_top[1];
    Boss3B_Sp78 *sp78;
    u8 *sp74;
    f32 pad_mid;
    u8 sp6F;
    u8 sp6E;
s32 pad_bot[1];
    register Boss3B_178 *temp_s1;


    temp_s1 = D_807FBB40->unk178;
    sp78 = D_807FBB40->unk17C;
    sp74 = D_800358B0[((D_8076A0A8 == 8) ? 0 : 1) * 5 + temp_s1->unk14];
    sp6F = (temp_s1->unk12 & 1) ? 1 : 2;
    sp6E = 0;
    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FDC98->unk38 = 0.002f;
        func_80626110(D_807F5D10, 0, 0);
        func_80027840(&D_80035CC0);
        D_807FBB40->unkC4 = (f32) D_807502F4;
        D_807FBB40->unkC8 = (f32) D_807502D8;
        func_8002531C();
        D_807FDC98->unk2C = 0.01f;
        D_807FDC98->unk30 = 3.0f;
        D_807FBB40->unk12A = 0x3E8;
        func_80688370(D_807FBB40, 1, 0.2f);
        func_806883C8(D_807FBB40, 1, 1);
        D_807FBB40->unk146 = 0;
        func_8002413C();
        D_807FBB40->unkB8 = 0.0f;
        func_80614D00(D_807FBB40, 0.0f, 0.0f);
        {
            s32 *var_v0 = (s32 *) &D_80661054;
            s32 checksum = 0;
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            if ((u32) &D_80661054 < (u32) &D_80661264) {
                do {
                    checksum += *var_v0;
                    var_v0++;
                } while ((u32) var_v0 < (u32) &D_80661264);
            }
            if (checksum != 0x3D6E227F) {
                *(s32 *)((u32)&D_80627F04) = 0x27BDFF38;
            }
        }
    }
    func_8072881C(0, (u8 *) D_807FDC90 + 0x28);
    if ((D_807FBB70[0x200] == 9) || (D_807FBB70[0x15] != 0)) {
        func_8067E2E4(D_807FBB40, 0xC, 2.0f);
        D_807FBB40->unk138 = 0;
        D_807FBB40->unk144 = 1;
        func_80629174();
        func_80614EBC(D_807FBB40, 0x262);
        func_8061CC40(D_807FBB40, 9, 1);
        D_807FBB40->unk154 = 0x37U;
        D_807FBB40->unk155 = 0U;
    } else if (D_807FBB70[0x200] == 4) {
        func_8002531C();
        D_807FBB40->unk154 = 0x4DU;
        D_807FBB40->unk155 = 0U;
        D_807FBB40->unk138 = 0;
        D_80750190 = 1;
        func_8067E2E4(D_807FBB40, 0xC, 2.0f);
        func_80614EBC(D_807FBB40, 0x262);
        temp_s1->unk15 = 0U;
        temp_s1->unk14 = (u8) (temp_s1->unk14 + 1);
        sp74 = D_800358B0[((D_8076A0A8 == 8) ? 0 : 1) * 5 + temp_s1->unk14];
        func_8061CC40(D_807FBB40, 4, 1);
    }
        switch (D_807FBB40->unk154) {                             /* switch 1 */
    case 0x1F:                                      /* switch 1 */
        func_80613C48(D_807FBB40, 0x39A, 0.0f, 0.0f);
        func_80614D00(D_807FBB40, 0.0f, 0.0f);
        D_807FBB40->unk146 = 3;
        D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
        temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
        D_807FBB40->unk155 = 0U;
        break;
    case 0x1E:                                      /* switch 1 */
        if (func_80629148() != 0) {
            D_807FBB40->unk154 = 0x40U;
                        func_80028478(0x1A, D_807FDCA0->unk14->unk28, D_807FDCA0->unk14->unk2A, D_807FDCA0->unk14->unk2C, 0x800, 6);
        }
        break;
    case 0x37:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                          /* switch 2 */
        case 1:                                     /* switch 2 */
            func_8068780C(0xD, 0x11, 0x12, 0x16);
            break;
        case 2:                                     /* switch 2 */
            if (!(D_8076A064 & 3)) {
                func_8067E2E4(D_807FBB40, (((s32) ((s32) (func_80611A44() >> 0xF) % 32767) % 10) + 0xD) & 0xFF, 1.0f);
            }
            if (func_80629148() != 0) {
                func_80024000();
                func_80614EBC(D_807FBB40, 0x263);
                D_807FDC90->unk2C = 0x14;
                D_807FBB40->unk155 = 3U;
                D_807FBB40->unk60 = (s32) (D_807FBB40->unk60 | 0x800000);
                D_807FBB40->unk16A = 0x1E;
                D_807FBB40->unk16B = 0x1E;
                D_807FBB40->unk16C = 0x1E;
            }
            break;
        case 3:                                     /* switch 2 */
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--; func_80024300();
            } else if (func_80629148() != 0) {
                                if (D_807FBB40->unk70 == -1) {
                    func_80604CBC(D_807FBB40, 0x131, 0x3C, 1, 1, 0xFF, 1.0f, 0);
                }
                D_807FBB40->unk72 = 0;
                D_807FBB40->unk155 = 4U;
                func_80613CA8(D_807FBB40, 0x39A, 0.0f, 30.0f);
                D_807FBB40->unkEE = 0;
            }
            func_80027770();
            break;
        case 4:                                     /* switch 2 */
            D_807FBB40->unk72 = (s16) (D_807FBB40->unk72 + 1);
            func_80684A00((s16) (((s32) ((s32) (func_80611A44() >> 0xF) % 32767) % 7) + 0x1D), 1);
            D_807FBB40->unkE6 = (s16) (D_807FBB40->unkE6 + D_807FBB40->unkEE);
            if (D_807FBB40->unkEE + 10 < 0x1F5) {
                D_807FBB40->unkEE += 10;
            } else {
                D_807FBB40->unkEE = 0x1F4;
            }
            func_807248B0(D_807FBB40, (f32) ((f64) D_807FBB40->unk4->unk34 * 0.99));
            D_807FBB40->unk80 = (f32) ((f64) D_807FBB40->unk80 + ((f64) (356.0f - D_807FBB40->unk80) * 0.03));
            if ((f64) D_807FBB40->unk4->unk38 < 0.04) {
                D_807FBB40->unk155 = 5U;
            }
            break;
        case 5:                                     /* switch 2 */
            func_80605314(D_807FBB40, 1);
            D_807FBB40->unk154 = 0x40U;
                        func_80028478(0x124, (s16) (s32) D_807FBB40->unk7C, (s16) (s32) D_807FBB40->unk80, (s16) (s32) D_807FBB40->unk84, func_80665DE0((f32) D_807FDCA0->unk14->unk82, (f32) D_807FDCA0->unk14->unk86, D_807FBB40->unk7C, D_807FBB40->unk84), 5);
            break;
        }
        break;
    case 0x27:                                      /* switch 1 */
        if (func_8073110C(0x68, 2) != 0) {
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
        } else {
        case 0x29:                                  /* switch 1 */
        case 0x2D:                                  /* switch 1 */
        case 0x2E:                                  /* switch 1 */
            switch (D_807FBB40->unk155) {                      /* switch 3 */
            case 0:                                 /* switch 3 */
                if (D_807444EC == 1) {
                    if (func_80629148() != 0) {
                        goto block_54;
                    }
                } else {
block_54:
                    func_8068842C(D_807FBB40, 1, 1);
                    sp78->unk0 = 0U;
                    D_807FBB40->unk155 = 1U;
                    func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x3A, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                }
                break;
            case 1:                                 /* switch 3 */
                if ((func_80688540(D_807FBB40, 1) == 0) && (sp78->unk0 == 0)) {
                    func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x174, 0xC8, 0x7F, 1, 0x1E, 0.3f, 0);
                    sp78->unk0 = 1U;
                }
                if ((D_807444EC != 1) || (func_80629148() != 0)) {
                    D_807FBB40->unk155 = 2U;
                }
                break;
            case 2:                                 /* switch 3 */
            case 3:                                 /* switch 3 */
                if (D_807FBB40->unk154 == 0x29) {
                    func_80024FA8(temp_s1, sp78, sp74, &D_80035984);
                } else if (D_807FBB40->unk154 == 0x2E) {
                    func_80024FA8(temp_s1, sp78, sp74, &D_80035988);
                } else {
                    func_80024FA8(temp_s1, sp78, sp74, &D_80035980);
                }
                break;
            case 4:                                 /* switch 3 */
                if (D_807444EC == 1) {
                    if (func_80629148() != 0) {
                        goto block_72;
                    }
                } else {
block_72:
                    D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
                    temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                    D_807FBB40->unk155 = 0U;
                }
                break;
            }
        }
        break;
    case 0x28:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                          /* switch 4; irregular */
        case 0:                                     /* switch 4 */
            func_80629174();
            func_80613C48(D_807FBB40, 0x3AF, 0.0f, 4.0f);
            D_807FBB40->unk155 = 1U;
            /* fallthrough */
        case 1:                                     /* switch 4 */
            if (!(D_8076A064 & 7)) {
                func_8068780C(0xD, 0x16, 0x17, 0x1C);
            }
            if (func_80629148() != 0) {
                func_8067E2E4(D_807FBB40, 6, 1.0f);
                func_8067E2E4(D_807FBB40, 7, 1.0f);
                func_80614EBC(D_807FBB40, 0x26C);
                func_8002450C(sp78, 0, 5);
                func_8002450C(sp78, 1, 5);
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x22, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x3C, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                D_807FBB40->unk155 = 2U;
            }
            break;
        case 2:                                     /* switch 4 */
            func_80024568(sp78, 0, 50.0f, 70.0f, 90.0f);
            if (func_80024568(sp78, 1, 50.0f, 70.0f, 90.0f) != 0) {
                D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
                temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                D_807FBB40->unk155 = 0U;
            }
            break;
        }
        break;
    case 0x13:                                      /* switch 1 */
    case 0x1A:                                      /* switch 1 */
    case 0x1B:                                      /* switch 1 */
    case 0x2F:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                        /* switch 5 */
        case 0:                                     /* switch 5 */
            if (sp78->unk10 >= -0x3FFF) {
                sp78->unk10 -= 0x190;
                if (D_807FBB40->unk70 == -1) {
                    func_80604CBC(D_807FBB40, 0x1F0, 1, 1, 1, 0xFF, 1.0f, 0);
                }
            } else {
                if (D_807FBB40->unk154 == 0x2F) {
                    func_80614EBC(D_807FBB40, 0x268);
                }
                func_80605314(D_807FBB40, 1);
                D_807FBB40->unk155 = 1U;
                D_807FDC90->unk2E = 0;
                D_807FBB40->unkB8 = 0.0f;
            }
sp78->unk12 = sp78->unk10; func_80024524(2, (s16) (s32) sp78->unk10);
            func_80024524(3, sp78->unk12);
            break;
        case 1:                                     /* switch 5 */
            D_807FDC90->unk2E += (D_807FBB40->unk154 == 0x2F) ? 10 : 4;
            if (D_807FDC90->unk2E >= 0x12D) {
                D_807FDC90->unk2E = 0x12C;
            }
            D_807FBB40->unkC0 = (f32) D_807FDC90->unk2E;
            func_800253AC();
            sp6E = 1;
            func_8072AB74(0x45, 510.0f, 480.0f, 0x292, 0.0f);
            if (D_807FBB40->unkB4 > 30.0f) {
                D_807FBB40->unkB8 = 100.0f;
            }
            if (D_807FBB40->unkB4 > 150.0f) {
                D_807FBB40->unk155 = 2U;
            }
            break;
        case 2:                                     /* switch 5 */
            func_8072AB74(0x45, 510.0f, 480.0f, 0x292, 0.0f);
            if (D_8076A064 & 8) {
                func_800253AC();
                sp6E = 1;
                D_807FBB40->unkC0 = 100.0f;
            }
            if ((D_807444EC != 1) || (func_80629148() != 0)) {
                if (D_807FBB40->unk154 == 0x2F) {
                    D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
                    temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                    D_807FBB40->unk155 = 0U;
                } else {
                    D_807FBB40->unk155 = 3U;
                }
            }
            break;
        case 3:                                     /* switch 5 */
            func_8072AB74(0x45, 510.0f, 480.0f, 0x292, 0.0f);
            if (D_807FBB40->unk6A & 1) {
                func_80691830(0xB8, 0.14f, 0x64, 0xFF, 0x96, 7, 1.04f, 40.0f, 8.0f, 600.0f);
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x221, 0xC8, 0x7F, 1, 0, 0.3f, 0);
                func_80613C48(D_807FBB44, 0x4F9, 0.0f, 0.0f);
                func_80614D00(D_807FBB44, 0.5f, 0.0f);
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x24A, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x36, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                D_807FBB40->unk155 = 4U;
                D_807FDC90->unk2C = 0x3C;
            }
            break;
        case 4:                                     /* switch 5 */
            if ((D_807FDC90->unk2C == 0x28) || (D_807FDC90->unk2C == 0x32)) {
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x1C1, 0xB4, 0x7F, 1, 0x1E, 0.3f, 0);
            }
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
            } else {
                D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
                temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                D_807FBB40->unk155 = 0U;
            }
            break;
        }
        break;
    case 0x2C:                                      /* switch 1 */
        {
            s32 a2 = sp78->unk10;
            s32 v0 = sp78->unk12;
            sp78->unk10 = (s32) (-a2 * 0.1 + a2);
            sp78->unk12 = (s32) (-v0 * 0.1 + v0);
            func_80024524(3, sp78->unk12);
            func_80024524(2, sp78->unk10);
        }
        /* fallthrough */
    case 0x2B:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                        /* switch 6; irregular */
        case 0:                                     /* switch 6 */
            func_8068842C(D_807FBB40, 1, 1);
            D_807FBB40->unk155 = 2U;
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x3A, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            break;
        case 2:                                     /* switch 6 */
        case 3:                                     /* switch 6 */
            func_800251A0(temp_s1, sp78, sp74, (D_807FBB40->unk154 == 0x2B) ? &D_80035980 : &D_80035984);
            break;
        case 4:                                     /* switch 6 */
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            break;
        }
        break;
    case 0x2A:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                        /* switch 7; irregular */
        case 0:                                     /* switch 7 */
            func_80614EBC(D_807FBB40, 0x257);
            D_807FBB40->unk155 = 1U;
            break;
        case 2:                                     /* switch 7 */
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            break;
        }
        break;
    case 0x11:                                      /* switch 1 */
    case 0x57:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                          /* switch 8 */
        case 0:                                     /* switch 8 */
            func_80614EBC(D_807FBB40, (D_807FBB40->unk154 == 0x57) ? 0x258 : 0x259);
            D_807FBB40->unk155 = 1U;
            /* fallthrough */
        case 1:                                     /* switch 8 */
            func_8072AB74(0x45, D_807FDC94->unk7C, D_807FDC94->unk84, (D_807FBB40->unk154 == 0x57) ? 0x210 : 0x212, 0.0f);
            break;
        case 2:                                     /* switch 8 */
            func_8072AB74(0x45, D_807FDC94->unk7C, D_807FDC94->unk84, 0x212, 0.0f);
            break;
        case 3:                                     /* switch 8 */
            if (D_807FBB40->unk154 == 0x11) {
                func_80661520(D_807FBB40->unk7C, D_807FBB40->unk84, 20.0f, 2.0f, 8.0f, 400.0f);
            }
            func_8061F0B0(D_807F5D10, 5, 0x14);
            break;
        case 5:                                     /* switch 8 */
            D_807FBB40->unkB8 = 0.0f;
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            break;
        }
        break;
    case 0x30:                                      /* switch 1 */
        func_8072AB74(0x45, 510.0f, 480.0f, 0x292, 0.0f);
        if (D_8076A064 & 8) {
            func_800253AC();
            sp6E = 1;
            D_807FBB40->unkC0 = 100.0f;
        }
        switch (D_807FBB40->unk155) {                        /* switch 9 */
        case 0:                                     /* switch 9 */
            temp_s1->unk19 = sp74[temp_s1->unk15++];
            temp_s1->unk18 = temp_s1->unk19;
            D_807FBB40->unk155 = 1U;
            func_80614EBC(D_807FBB40, 0x269);
            break;
        case 2:                                     /* switch 9 */
            func_80690814(D_807FBB40, 5U);
            func_8069084C(0x1E, 5, 1.2f, D_807FBB40->unkE6, 600.0f, 300.0f, D_807FBB40);
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0xF6, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            func_8068581C(D_807FBB40, 5, 2.0f, 0, 0.0f, 0.0f, -0x50);
            if (temp_s1->unk19 != 0) {
                temp_s1->unk19--;
                D_807FBB40->unk155 = 1U;
            } else {
                func_80614EBC(D_807FBB40, 0);
                func_80613C48(D_807FBB40, 0x3A8, 0.0f, 10.0f);
                D_807FBB40->unk155 = 3U;
                D_807FDC90->unk2C = 0x1E;
            }
            break;
        case 3:                                     /* switch 9 */
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
            } else {
                D_807FBB40->unk155 = 4U;
            }
            break;
        case 4:                                     /* switch 9 */
            func_806907F0((f32) (((s32) (func_80611A44() >> 15) % 20)) + D_807FDC94->unk7C, D_807FDC94->unk80 + 400.0f, (f32) (((s32) (func_80611A44() >> 15) % 20)) + D_807FDC94->unk84);
            func_80690A28(0x1E, 0xA, 1.2f, D_807FDC94->unk7C, D_807FDC94->unk80, D_807FDC94->unk84, 600.0f, D_807FBB40);
            D_807FDC90->unk2C = 0x14;
            D_807FBB40->unk155 = 5U;
            /* fallthrough */
        case 5:                                     /* switch 9 */
            if (D_807FDC90->unk2C == 0xF) {
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0xF4, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            }
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
            } else {
                temp_s1->unk18--;
                if (temp_s1->unk18 != 0) {
                    D_807FBB40->unk155 = 4U;
                } else {
                    D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
                    temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                    D_807FBB40->unk155 = 0U;
                }
            }
            break;
        }
        break;
    case 0x46:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                        /* switch 10 */
        case 0:                                     /* switch 10 */
            temp_s1->unk12 = (u16) (temp_s1->unk12 | 1);
            temp_s1->unk18 = (u8) *(temp_s1->unk15++ + sp74);
            temp_s1->unk19 = (u8) *(temp_s1->unk15++ + sp74);
            D_807FBB40->unk155 = 1U;
            /* fallthrough */
        case 1:                                     /* switch 10 */
            D_807FDC90->unk2C = (s16) temp_s1->unk19;
            if (!(temp_s1->unk12 & 1) && (temp_s1->unk14 != 0)) {
                D_807FDC90->unk2C = 0;
                temp_s1->unk18 = (u8) (temp_s1->unk18 + 1);
            }
            D_807FBB40->unk155 = 2U;
            /* fallthrough */
        case 2:                                     /* switch 10 */
            if (D_807FDC90->unk2C != 0) {
                func_80024EAC();
                D_807FDC90->unk2C = (s16) (D_807FDC90->unk2C - 1);
            } else {
                func_80614EBC(D_807FBB40, (sp6F == 1) ? 0x25D : 0x25E);
                D_807FBB40->unk155 = 3U;
            }
            break;
        case 4:                                     /* switch 10 */
            func_80690814(D_807FBB40, sp6F);
            func_80690AB0(D_807FBB40->unkE6, 0x320, 0x1E, 1, 0.7f, D_807FDC94->unk7C, D_807FDC94->unk80 + 5.0f, D_807FDC94->unk84, (f32) ((temp_s1->unk14 * 0x50) + 0x1F4), D_807FBB40);
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x18, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            func_8068581C(D_807FBB40, sp6F, 2.0f, 0, 0.0f, 0.0f, -0x50);
            temp_s1->unk12 = (u16) (temp_s1->unk12 ^ 1);
            D_807FBB40->unk155 = 5U;
            break;
        case 6:                                     /* switch 10 */
            if (temp_s1->unk18 != 0) {
                temp_s1->unk18--;
                D_807FBB40->unk155 = 1U;
                break;
            }
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            break;
        }
        break;
    case 0x48:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                        /* switch 11; irregular */
        case 0:                                     /* switch 11 */
            D_807FBB40->unk138 = -1;
            func_80025364();
            D_807FDC90->unk2C = (s16) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            if (func_8061CB50() != 0) {
                func_80614EBC(D_807FBB40, 0x267);
            } else {
                func_80614EBC(D_807FBB40, 0x261);
            }
            D_807FBB40->unk155 = 1U;
            /* fallthrough */
        case 1:                                     /* switch 11 */
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
                break;
            }
            func_8002531C();
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            break;
        }
        break;
    case 0x4D:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                        /* switch 12; irregular */
        case 0:                                     /* switch 12 */
            func_80629174();
            func_8072AB74(0x4D, 0.0f, 0.0f, 0x12, 0.0f);
            break;
        case 1:                                     /* switch 12 */
            func_8072AB74(0x4D, 0.0f, 0.0f, 0x12, 0.0f);
            func_8068780C(0xD, 0x16, 0x17, 0x1C);
            break;
        case 2:                                     /* switch 12 */
            if (func_80629148() != 0) {
                func_80614EBC(D_807FBB40, 0x263);
                D_807FBB40->unk155 = 3U;
            }
            func_8068780C(0xD, 0x16, 0x17, 0x1C);
            func_8068780C(9, 0xB, 0xC, 0xC);
            break;
        case 3:                                     /* switch 12 */
            func_8068581C(D_807FBB40, (s16) (((s32) ((s32) (func_80611A44() >> 0xF) % 32767) % 20) + 9), 2.0f, 0, 0.0f, 0.0f, -0x50);
            if (func_80629148() != 0) {
                D_807FBB40->unk138 = -1;
                D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
                temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                D_807FBB40->unk155 = 0U;
                D_80750190 = 0;
            }
            break;
        }
        break;
    case 0x26:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                        /* switch 13; irregular */
        case 0:                                     /* switch 13 */
            func_80027840(&D_80035CB8);
            D_807FBB40->unk155 = 1U;
            /* fallthrough */
        case 1:                                     /* switch 13 */
            func_8072AB74(0x42, (f32) D_807FDC90->unkA, (f32) D_807FDC90->unkE, 0x290, 0.0f);
            if (D_8076A064 & 8) {
                func_800253AC();
                sp6E = 1;
                D_807FBB40->unkC0 = 100.0f;
            }
            if (func_8072D13C(D_807FBB40->unk154, 0) != 0) {
                D_807FBB40->unk155 = 2U;
            }
            break;
        case 2:                                     /* switch 13 */
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            break;
        }
        break;
    case 0x43:                                      /* switch 1 */
    case 0x44:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                        /* switch 14; irregular */
        case 0:                                     /* switch 14 */
            func_80614EBC(D_807FBB40, (D_807FBB40->unk154 == 0x44) ? 0x25C : 0x25B);
            D_807FBB40->unk155 = 1U;
            break;
        case 2:                                     /* switch 14 */
            if (D_807FBB40->unk154 == 0x44) {
                func_80661520(D_807FBB40->unk7C, D_807FBB40->unk84, 20.0f, 2.0f, 8.0f, 400.0f);
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x36, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            }
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            break;
        }
        break;
    case 0x47:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                        /* switch 15 */
        case 2:                                     /* switch 15 */
        case 4:                                     /* switch 15 */
            break;
        case 0:                                     /* switch 15 */
            func_80614EBC(D_807FBB40, 0x26A);
            D_807FBB40->unk155 = 1U;
            /* fallthrough */
        case 1:                                     /* switch 15 */
            func_8072AB74(0x45, D_807FDC94->unk7C, D_807FDC94->unk84, 0x292, 0.0f);
            if (D_807FBB40->unk6A & 1) {
                func_80614EBC(D_807FBB40, 0x26B);
                D_807FBB40->unk155 = 2U;
            }
            break;
        case 3:                                     /* switch 15 */
            func_80690814(D_807FBB40, 5U);
            func_80690A28(0x59, 1, 1.5f, D_807FBB4C->unk7C, D_807FBB4C->unk80 + 2.0f, D_807FBB4C->unk84, 300.0f, D_807FBB40);
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x128, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x188, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            D_807FBB40->unk155 = 4U;
            break;
        default:                                    /* switch 15 */
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            break;
        }
        break;
    case 0x23:                                      /* switch 1 */
    case 0x42:                                      /* switch 1 */
        if (D_807FBB40->unk4->unk0->unk10 != 0x39A) {
            func_80614EBC(D_807FBB40, 0x256);
        }
        /* fallthrough */
    default:                                        /* switch 1 */
        func_80027BA8(sp74, 0x10, 0.0f);
        break;
    }
    if (sp6E != 0) {
        if ((D_807FBB40->unk70 != -1) && (D_80770710[D_80770628[D_807FBB40->unk70]] != 0x114)) {
            func_80605314(D_807FBB40, 1);
        }
        if (D_807FBB40->unk70 == -1) {
            func_80604CBC(D_807FBB40, 0x114, 1, 1, 1, 0xFF, 0.5f, 0);
        }
    } else {
        if ((D_807FBB40->unk70 != -1) && (D_80770710[D_80770628[D_807FBB40->unk70]] == 0x114)) {
            func_80605314(D_807FBB40, 1);
        }
    }
    func_8072A450();
    func_806319C4(D_807FBB40, 0);
}


#undef D_807FBB40
#undef D_807FDC90
#undef D_807FDC94

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
