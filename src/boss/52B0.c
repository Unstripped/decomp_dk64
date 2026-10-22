#include "common.h"

typedef struct {
    char pad0[0x38];
    f32 unk38;
} BossB_Sub44;

typedef struct {
    char pad0[4];
    BossB_Sub44 *unk4;
    char pad8[0x80 - 8];
    f32 unk80;
} BossB_ActorBB44;

typedef struct {
    char pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} BossB_ActorBB40;

extern BossB_ActorBB40 *D_807FBB40;
extern BossB_ActorBB44 *D_807FBB44;

void func_80691830(s32, f32, s32, s32, s32, s32, f32, f32, f32, f32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_80613C48(void *, s16, f32, f32);
void func_80614D00(void *, f32, f32);

void func_800292B0(f32 arg0) {
    f32 zero = 0.0f;

    func_80691830(0x6A, 1.2f, 0, 0x96, 0xFF, 0xB, 1.015f, zero, zero, zero);
    func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x221, 0x80, 0x7F, 1, 0, 0.3f, 0);
    D_807FBB44->unk80 = D_807FBB40->unk80;
    D_807FBB44->unk4->unk38 *= arg0;
    func_80613C48(D_807FBB44, 0x4F9, zero, zero);
    func_80614D00(D_807FBB44, 1.5f, zero);
}


s32 func_80611A44(void);
void func_807149B8(s32);
void func_80714998(s32);
void func_807149C8(s32, s32, s32, s32);
void func_8068588C(void *, s16, f32, f32, f32, f32, s32);

void func_800293C0(void) {
    func_80611A44();
    func_807149B8(1);
    func_80714998(3);
    func_807149C8(0x78, 0x78, 0x78, 0xC8);
    func_8068588C(D_807FBB40, (((func_80611A44() >> 15) % 0x7FFF) % 16) + 3, 2.0f, 0.0f, 0.0f, 0.0f, -0x96);
}

typedef struct Boss3F_52B0_178 {
    char pad0[8];
    s16 unk8;
    char padA[0xA];
    u8 unk14;
    u8 unk15;
    char pad16[2];
    u8 unk18;
    u8 unk19;
} Boss3F_52B0_178;

typedef struct Boss3F_52B0_Actor {
    char pad0[0x60];
    s32 unk60;
    s32 unk64;
    char pad68[0x14];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x24];
    f32 unkAC;
    char padB0[8];
    f32 unkB8;
    char padBC[4];
    f32 unkC0;
    f32 unkC4;
    char padC8[6];
    s16 unkCE;
    char padD0[0x16];
    s16 unkE6;
    char padE8[0x5C];
    u8 unk144;
    char pad145[0xF];
    u8 unk154;
    u8 unk155;
    char pad156[9];
    u8 unk15F;
    char pad160[0x18];
    Boss3F_52B0_178 *unk178;
} Boss3F_52B0_Actor;

typedef struct Boss3F_52B0_BB4C {
    char pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} Boss3F_52B0_BB4C;

typedef struct Boss3F_52B0_D580 {
    char pad0[0x88];
    void *unk88;
} Boss3F_52B0_D580;

typedef struct Boss3F_52B0_DC90 {
    char pad0[0x2C];
    s16 unk2C;
    s16 unk2E;
} Boss3F_52B0_DC90;

typedef struct Boss3F_52B0_DC94 {
    char pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x30];
    f32 unkB8;
    char padBC[0x2A];
    s16 unkE6;
} Boss3F_52B0_DC94;

typedef struct Boss3F_52B0_DC98 {
    char pad0[0x46];
    u16 unk46;
} Boss3F_52B0_DC98;

extern u8 *D_80035A00[];
extern s32 D_8076A064;
extern Boss3F_52B0_BB4C *D_807FBB4C;
extern Boss3F_52B0_D580 *D_807FD580;
extern Boss3F_52B0_DC90 *D_807FDC90;
extern Boss3F_52B0_DC94 *D_807FDC94;
extern Boss3F_52B0_DC98 *D_807FDC98;
void func_80027BA8(u8 *, s32, f32);
void func_80028478(s32, s16, s16, s16, s32, s32);
f32 func_80612790(s16);
f32 func_80612794(s16);
void func_80614EBC(void *, s32);
s32 func_8061CB50(void);
void func_8061CC40(void *, s32, s32);
s32 func_80629148(void);
void func_806319C4(void *, s32);
void func_8063DA40();
void func_80659670(f32, f32, f32, s32);
s16 func_80665DE0(f32, f32, f32, f32);
void func_8068780C(s32, s32, s32, s32);
void func_806907F0(f32, f32, f32);
void func_80690814(void *, s32);
void func_8069084C(s32, s32, f32, s32, f32, f32, void *);
void func_80690A28(s32, s32, f32, f32, f32, f32, f32, void *);
void func_80697184(void);
s32 func_806CC10C(s16, s16);
s32 func_806CC14C(s16, s16);
s32 func_80724A20(void);
void func_80729B00(void);
void func_8072AB74(s32, f32, f32, s32, f32);
void func_8072E1A4(s32, void *);

#define ACTOR ((Boss3F_52B0_Actor *)D_807FBB40)

void func_80029468(void) {

    Boss3F_52B0_178 *sp4C;
    s32 pad48;
    u8 *sp44;
    s16 sp42;
    s16 sp40;
    f32 sp3C;
    f32 sp38;

    sp4C = ACTOR->unk178;
    sp44 = D_80035A00[sp4C->unk14];
    sp42 = func_80665DE0(D_807FBB4C->unk7C, D_807FBB4C->unk84, ACTOR->unk7C, ACTOR->unk84);
    func_80729B00();
    if (!(ACTOR->unk60 & 0x10)) {
        ACTOR->unkCE = 0x64;
        ACTOR->unk15F = 0;
        D_807FDC98->unk46 |= 0x20;
        ACTOR->unk64 |= 4;
        ACTOR->unk144 = 0x24;
        func_80659670(0.0f, 0.0f, 0.0f, -1);
        sp4C->unk14 = 0;
        sp4C->unk15 = 0;
        ACTOR->unk154 = 0x1E;
        ACTOR->unk155 = 0;
    }
    func_80724A20();
    switch (ACTOR->unk154) {
    case 0x2D:
        switch (ACTOR->unk155) {
        case 0:
            func_80614EBC(ACTOR, 0x219);
            ACTOR->unk155++;
            break;
        case 2:
            func_800292B0(1.8f);
            D_807FDC90->unk2C = 0x14;
            ACTOR->unk155++;
            break;
        case 3:
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
            } else {
                func_800292B0(1.0f);
                ACTOR->unk155++;
            }
            break;
        case 5:
            ACTOR->unk154 = sp44[sp4C->unk15++];
            ACTOR->unk155 = 0;
            break;
        }
        break;
    case 0x1E:
        switch (ACTOR->unk155) {
        case 0:
            if (func_80629148() != 0) {
                func_80614EBC(D_807FBB4C, 0x3B1);
                func_80614EBC(D_807FD580->unk88, 0x3B7);
                ACTOR->unk155++;
            }
            break;
        case 1:
            if (func_80629148() != 0) {
                func_80614EBC(D_807FBB4C, 0x3B2);
                func_80614EBC(D_807FD580->unk88, 0x3B8);
                ACTOR->unk155++;
            }
            break;
        case 2:
            if (func_80629148() != 0) {
                func_80614EBC(D_807FBB4C, 0x3B3);
                func_80614EBC(D_807FD580->unk88, 0x3B9);
                ACTOR->unk155++;
            }
            break;
        case 3:
            if (func_80629148() != 0) {
                func_80614EBC(ACTOR, 0x217);
                ACTOR->unk155++;
            }
            break;
        case 4:
            if (func_80629148() != 0) {
                func_80614EBC(D_807FBB4C, 0x3B4);
                func_80614EBC(D_807FD580->unk88, 0x3BA);
                ACTOR->unk155++;
            }
            break;
        case 5:
            if (func_80629148() != 0) {
                func_80613C48(D_807FBB4C, 0x1C7, 0.0f, 0.0f);
                ACTOR->unk154 = sp44[sp4C->unk15++];
                ACTOR->unk155 = 0;
            }
            break;
        }
        break;
    case 0x2C:
        func_8063DA40(sp44[sp4C->unk15++], 0xA);
        ACTOR->unk154 = sp44[sp4C->unk15++];
        ACTOR->unk155 = 0;
        break;
    case 0x2B:
        func_8063DA40(sp44[sp4C->unk15++], 0);
        ACTOR->unk154 = sp44[sp4C->unk15++];
        ACTOR->unk155 = 0;
        break;
    case 0x4D:
        if (sp4C->unk14 == 4) {
            ACTOR->unk154 = 0x37;
            ACTOR->unk155 = 0;
            func_8061CC40(ACTOR, 4, 1);
            func_80697184();
        } else {
            switch (ACTOR->unk155) {
            case 0:
                ACTOR->unkE6 = 0;
                func_80614EBC(ACTOR, 0x213);
                func_8061CC40(ACTOR, 2, 1);
                func_80697184();
                ACTOR->unk155++;
                break;
            case 1:
                if (func_80629148() != 0) {
                    func_80614EBC(ACTOR, 0x21A);
                    ACTOR->unk155++;
                }
                break;
            case 2:
                func_8068780C(3, 6, 7, 0xA);
                func_8068780C(0xB, 0xE, 0xF, 0x12);
                break;
            case 3:
                if (!(D_8076A064 & 3)) {
                    func_800293C0();
                }
                break;
            case 4:
                func_8063DA40(0, 0);
                func_8063DA40(6, 0);
                func_8063DA40(7, 0);
                func_8063DA40(9, 0);
                func_8063DA40(0xB, 0);
                sp4C->unk15 = 0;
                sp4C->unk14++;
                sp44 = D_80035A00[sp4C->unk14];
                ACTOR->unk154 = sp44[sp4C->unk15++];
                ACTOR->unk155 = 0;
                break;
            }
        }
        break;
    case 0x28:
    case 0x2A:
        func_8072E1A4(0x14, D_807FDC94);
        goto block_28;
    case 0x46:
        ACTOR->unkE6 += D_807FDC90->unk2E;
        if (func_806CC10C(ACTOR->unkE6, sp42) > 0) {
            pad48 = D_807FDC90->unk2E + 2;
            if (pad48 < 0x32) {
                D_807FDC90->unk2E = pad48;
            } else {
                D_807FDC90->unk2E = 0x32;
            }
        } else {
            pad48 = D_807FDC90->unk2E - 2;
            if (pad48 >= -0x31) {
                D_807FDC90->unk2E = pad48;
            } else {
                D_807FDC90->unk2E = -0x32;
            }
        }
block_28:
        switch (ACTOR->unk155) {
        case 0:
            sp4C->unk18 = sp44[sp4C->unk15++];
            sp4C->unk19 = sp4C->unk18;
            sp4C->unk8 = sp44[sp4C->unk15++];
            if (ACTOR->unk154 == 0x46) {
                ACTOR->unk155 = 2;
            } else {
                func_80614EBC(ACTOR, 0x214);
                ACTOR->unk155++;
            }
            break;
        case 2:
            if (func_8061CB50() == 0) {
                if (ACTOR->unk154 == 0x46) {
                    if (func_806CC14C(ACTOR->unkE6, func_80665DE0(D_807FBB4C->unk7C, D_807FBB4C->unk84, ACTOR->unk7C, ACTOR->unk84)) < 0x320) {
                        func_80614EBC(ACTOR, 0x218);
                        ACTOR->unk155++;
                    }
                } else {
                    func_80614EBC(ACTOR, 0x215);
                    ACTOR->unk155++;
                }
            }
            break;
        case 4:
            func_806086CC(ACTOR->unk7C, ACTOR->unk80, ACTOR->unk84, 0xF6, 0x37, 0x7F, 1, 0x1E, 0.3f, 0);
            func_80690814(ACTOR, 2);
            switch (ACTOR->unk154) {
            case 0x2A:
                func_80690A28(0xA9, 1, 1.0f, D_807FBB4C->unk7C, D_807FBB4C->unk80 + 2.0f, D_807FBB4C->unk84, 450.0f, ACTOR);
                func_80614EBC(ACTOR, 0x213);
                ACTOR->unk154 = sp44[sp4C->unk15++];
                ACTOR->unk155 = 0;
                break;
            case 0x46:
                func_8069084C(0x1E, 0x63, 0.7f, ACTOR->unkE6, 300.0f, 0.0f, ACTOR);
                D_807FDC90->unk2C = sp4C->unk8;
                ACTOR->unk155 = 8;
                break;
            default:
                func_8069084C(0x1E, 5, 0.7f, ACTOR->unkE6, 600.0f, 500.0f, ACTOR);
                ACTOR->unk155++;
                break;
            }
            break;
        case 6:
            func_80614EBC(ACTOR, 0x213);
            ACTOR->unk155++;
            sp4C->unk18 = sp4C->unk19;
            break;
        case 7:
            sp40 = ((func_80611A44() >> 15) % 1024) - 0x200;
            sp3C = ((f64)func_80612794(D_807FDC94->unkE6 + sp40) * ((f64)D_807FDC94->unkB8 * 1.2)) + (f64)D_807FDC94->unk7C;
            sp38 = ((f64)func_80612790(D_807FDC94->unkE6 + sp40) * ((f64)D_807FDC94->unkB8 * 1.2)) + (f64)D_807FDC94->unk84;
            func_806907F0(sp3C, D_807FDC94->unk80 + 500.0f, sp38);
            func_80690A28(0x1E, 0x1E, 1.0f, sp3C, D_807FDC94->unk80, sp38, 600.0f, ACTOR);
            D_807FDC90->unk2C = sp4C->unk8;
            ACTOR->unk155 = 9;
            /* fallthrough */
        case 9:
        case 10:
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
            } else {
                sp4C->unk18--;
                if (sp4C->unk18 != 0) {
                    if (ACTOR->unk154 == 0x46) {
                        ACTOR->unk155 = 2;
                    } else {
                        ACTOR->unk155 = 7;
                    }
                } else {
                    func_80614EBC(ACTOR, 0x213);
                    ACTOR->unk154 = sp44[sp4C->unk15++];
                    ACTOR->unk155 = 0;
                }
            }
            break;
        }
        break;
    case 0x37:
        if (func_80629148() != 0) {
            func_80028478(0xA8, (s16)ACTOR->unk7C, (s16)ACTOR->unk80, (s16)ACTOR->unk84, 0x5DC, 1);
            ACTOR->unk154 = 0x40;
        }
        break;
    case 0:
        switch (ACTOR->unk155) {
        case 0:
        case 1:
            func_80614EBC(ACTOR, 0x213);
            sp4C->unk8 = sp44[sp4C->unk15++];
            ACTOR->unk155 = 2;
            break;
        default:
            if (sp4C->unk8 != 0) {
                sp4C->unk8--;
            } else {
                ACTOR->unk154 = sp44[sp4C->unk15++];
                ACTOR->unk155 = 0;
            }
            break;
        }
        func_8072AB74(0x23, 0.0f, 0.0f, 0x202, 0.0f);
        break;
    default:
        func_80027BA8(sp44, 0, 0.0f);
        break;
    }
    if (ACTOR->unk80 < ACTOR->unkAC) {
        ACTOR->unk80 = ACTOR->unkAC;
        ACTOR->unkC0 = ACTOR->unkC4;
    }
    func_806319C4(ACTOR, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_80036160.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_8003616C.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_80036178.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_80036188.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_8003619C.s")
