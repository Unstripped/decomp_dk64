// func_806EEAF8 (src/global/EFDC0.c): Stage 1 behavioral reconstruction from local asm/m2c; current frame 0x68 vs target 0x40 and broad control-flow/regalloc differences. Corrected countdown nonzero path to return.
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
typedef struct EfL2PlayerState {
    u8 pad0[0x38];
    f32 unk38;
    u8 pad3C[0x14];
    s16 unk50;
    u8 pad52[0x36];
    Actor *unk88;
    u8 pad8C[0x36];
    s16 unkC2;
    u8 padC4[0x10];
    s16 unkD4;
    u8 padD6[0x17A];
    s32 unk250;
} EfL2PlayerState;

typedef struct EfL2PlayerBlock {
    u8 pad0[0x29C];
    s16 unk29C;
    Actor *unk2A0;
    u8 pad2A4[0x1C];
    u8 unk2C0;
    u8 pad2C1[0x2F];
} EfL2PlayerBlock;

typedef struct EfL2Actor {
    u8 pad0[0xB8];
    f32 unkB8;
    u8 padBC[4];
    f32 unkC0;
    f32 unkC4;
} EfL2Actor;

#define EfL2PS ((EfL2PlayerState *)D_807FD580)
#define EfL2Player ((EfL2PlayerBlock *)D_807FC924)
#define EfL2A48 ((EfL2Actor *)D_807FBB48)

extern f32 D_80753024[], D_80753040[], D_8075305C[], D_80753078[];
extern s16 D_807530B0[], D_807530D0[], D_807530E0[], D_80753160[], D_8075386C[];
extern f32 D_807530F0[], D_8075310C[], D_80753128[], D_80753144[], D_807531FC[], D_8075389C[];
extern s32 D_8076A064;
extern void func_80617770(Actor *, s32, s32);
extern s8 func_806C9830(s8, Actor *);
extern s32 func_806C9FD8(Actor *, s16 *);
extern void func_806CA048(s32, Struct807FD580 *);
extern void func_806CA0E8(Actor *, Actor *, s16);
extern s32 func_806CA1B4(s16);
extern void func_806CF42C(Actor *);
extern void func_806F8D58(s32, s32);
extern s32 func_807142D8(void);
extern s32 func_80714608(s32);
extern void func_8072DB68(s32);
extern s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
extern s32 sfxPlayFromActorWithAltitudeCheck(Actor *, s16, u8, s16, u8);

void func_806EEAF8(s16 arg0) {
    u8 sp33;
    s32 sp2C;
    f32 var_fv0;
    s16 temp_v0_2;
    s16 temp_v0_4;
    s16 var_a0;
    s32 temp_v1;
    s32 var_v1;
    s8 temp_v0;
    u8 var_t9;
    Actor *temp_a0;
    Actor *temp_s0;
    Actor *temp_s0_2;
    Actor *temp_v0_3;
    EfL2PlayerBlock *temp_v1_2;
    EfL2PlayerBlock *temp_v1_3;
    EfL2PlayerBlock *var_v1_2;

    sp33 = 0;
    if (D_807FBB48->unk6A & 4) {
        if (EfL2Player[D_807FC929].unk2C0 == 1) {
            var_fv0 = D_8075386C[D_807FD584];
        } else {
            var_fv0 = D_8075389C[D_807FD584];
        }
        var_t9 = 0;
        if (var_fv0 < (D_807FBB40->unkAC - D_807FBB40->unkA4)) {
            var_t9 = 1;
        }
        sp33 = var_t9;
    }
    if (func_806EB400(D_807FBB48) != 0) {
        sfxStopChannel(0x6B, 0);
        D_807FBB48->unk60 |= 4;
        EfL2PS->unk38 = D_807531FC[D_807FD584];
        D_807FBB48->unk6A &= 0xFFBF;
        func_806F8D58(6, 1);
        if (EfL2PS->unkD4 == 0) {
            func_806CA2AC();
            func_806CF42C(D_807FBB48);
            temp_a0 = EfL2PS->unk88;
            if ((temp_a0 != NULL) &&
                ((temp_v1 = temp_a0->unk58, temp_v1 == 0x1D) || (temp_v1 == 0x57) ||
                 (temp_v1 == 0x50) || (temp_v1 == 0x3E))) {
                EfL2PS->unkD4 = D_807530E0[D_807FD584];
                func_80614EBC(EfL2PS->unk88, 0x292);
                func_80617770(D_807FBB48, 0x11, 0);
                if (EfL2PS->unk88->unk58 != 0x57) {
                    func_8072DB68(3);
                }
            } else {
                sp2C = 0;
                if (D_807FC928 >= 2) {
                    if (func_806CA1B4(EfL2Player[D_807FC929].unk29C) != 0) {
                        temp_v1_2 = &EfL2Player[D_807FC929];
                        func_806CA0E8(D_807FBB48, temp_v1_2->unk2A0, temp_v1_2->unk29C);
                        if ((func_80714608(0) != 0) && (D_807FBB48->unk154 == 0x3C) &&
                            (EfL2Player[D_807FC929].unk29C != 0xE)) {
                            EfL2PS->unk250 -= arg0 * 0xA;
                            var_v1 = EfL2PS->unk250;
                            if (var_v1 < 0) {
                                EfL2PS->unk250 = 0;
                                var_v1 = EfL2PS->unk250;
                            }
                            if (var_v1 != 0) {
                                return;
                            }
                        }
                    }
                }
                if (((D_807FC928 != 1) || (EfL2Player[D_807FC929].unk29C != 0x2B)) &&
                    (func_807142D8() == 0)) {
                    temp_v0 = func_806C9830((s8)-arg0, D_807FBB48);
                    if (temp_v0 < 0) {
                        sp2C = func_806C9974(D_807FC929, temp_v0);
                    }
                }
                temp_s0 = D_807FBB48;
                if (sp2C != 0) {
                    if (temp_s0->unk6A & 4) {
                        func_80614E78(temp_s0, 0x29);
                    } else {
                        func_80614E78(temp_s0, 0x27);
                    }
                    D_807FBB48->unk154 = 0x36;
                    D_807FBB48->unk155[0] = 0;
                    if (func_80714608(0) != 0) {
                        EfL2A48->unkC0 = D_80753128[D_807FD584] * 5.0f;
                        EfL2A48->unkB8 = D_80753144[D_807FD584] * 5.0f;
                        EfL2PS->unk38 = D_807531FC[D_807FD584] * 5.0f;
                        EfL2A48->unkC4 = D_8075310C[D_807FD584];
                    }
                    var_v1_2 = &EfL2Player[D_807FC929];
                } else {
                    var_v1_2 = &EfL2Player[D_807FC929];
                    temp_v0_2 = var_v1_2->unk29C;
                    if (temp_v0_2 >= 0xF) {
                        switch (temp_v0_2) {
                        case 0x31:
                            if (sp33 != 0) {
                                temp_s0->unk154 = 0x37;
                                D_807FBB48->unk155[0] = 0;
                                func_80614E78(D_807FBB48, 0x28);
                            } else {
                                temp_s0->unk154 = 0x34;
                                D_807FBB48->unk155[0] = 0;
                                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x16, 0xFF, 0x7F, 0);
                                func_80614E78(D_807FBB40, 0x1E);
                            }
                            var_v1_2 = &EfL2Player[D_807FC929];
                            break;
                        case 0x2B:
                            if (sp33 != 0) {
                                temp_s0->unk154 = 0x37;
                                D_807FBB48->unk155[0] = 0;
                                func_80614E78(D_807FBB48, 0x28);
                            } else {
                                temp_s0->unk154 = 0x32;
                                D_807FBB48->unk155[0] = 0;
                                func_80614E78(D_807FBB48, 0x25);
                            }
                            var_v1_2 = &EfL2Player[D_807FC929];
                            break;
                        case 0x32:
                            if (sp33 != 0) {
                                temp_s0->unk154 = 0x37;
                                D_807FBB48->unk155[0] = 0;
                                func_80614E78(D_807FBB48, 0x28);
                            } else {
                                temp_s0->unk154 = 0x35;
                                D_807FBB48->unk155[0] = 0;
                                func_80614E78(D_807FBB48, 0x26);
                            }
                            var_v1_2 = &EfL2Player[D_807FC929];
                            break;
                        case 0x37:
                            temp_s0->unk154 = 0x33;
                            D_807FBB48->unk155[0] = 0;
                            func_80614EBC(D_807FBB48, 4);
                            var_v1_2 = &EfL2Player[D_807FC929];
                            break;
                        case 0x2E:
                        case 0x2F:
                            if (sp33 != 0) {
                                if (D_8076A0A8 == 0x6F) {
                                    temp_s0->unk154 = 0x38;
                                    D_807FBB48->unk155[0] = 0;
                                    func_80614EBC(D_807FBB48, 0x3B5);
                                    func_80614EBC(EfL2PS->unk88, 0x3BB);
                                    if (D_8076A064 & 1) {
                                        EfL2PS->unkC2 = -0xFA;
                                    } else {
                                        EfL2PS->unkC2 = 0xFA;
                                    }
                                } else {
                                    temp_s0->unk154 = 0x37;
                                    D_807FBB48->unk155[0] = 0;
                                    func_80614E78(D_807FBB48, 0x28);
                                }
                            } else if (temp_s0->unk154 != 0x63) {
                                temp_s0->unk154 = 0x31;
                                D_807FBB48->unk155[0] = 0;
                                func_80614E78(D_807FBB48, 0x24);
                            } else {
                                func_80614EBC(temp_s0, 0x81);
                            }
                            var_v1_2 = &EfL2Player[D_807FC929];
                            break;
                        }
                    } else if (temp_v0_2 == 0xE) {
                        temp_s0->unk154 = 0x66;
                        D_807FBB48->unk155[0] = 0;
                        func_80614E78(D_807FBB48, 0x26);
                        EfL2A48->unkC4 = D_8075310C[D_807FD584];
                        var_v1_2 = &EfL2Player[D_807FC929];
                    }
                }
after_action:
                temp_v0_3 = var_v1_2->unk2A0;
                if (temp_v0_3 != NULL) {
                    var_a0 = mathAngleBetweenPoints2D(temp_s0->unk7C, temp_s0->unk84, temp_v0_3->unk7C, temp_v0_3->unk84);
                } else {
                    var_a0 = (temp_s0->unkE6 + 0x800) & 0xFFF;
                }
                temp_s0->unkE6 = var_a0;
                temp_v1_3 = &EfL2Player[D_807FC929];
                temp_v0_4 = temp_v1_3->unk29C;
                switch (temp_v0_4) {
                case 0x2E:
                case 0x2F:
                    temp_s0_2 = D_807FBB48;
                    if (temp_s0_2->unk6A & 4) {
                        EfL2A48->unkB8 = D_8075305C[D_807FD584];
                        EfL2PS->unkD4 = D_807530B0[D_807FD584];
                    } else {
                        if (D_807FC928 >= 2) {
                            func_806CA048(func_806C9FD8(temp_v1_3->unk2A0, &D_807FD584), D_807FD580);
                        }
                        EfL2A48->unkC0 = D_80753040[D_807FD584];
                        EfL2A48->unkB8 = D_8075305C[D_807FD584];
                        EfL2PS->unkD4 = D_807530B0[D_807FD584];
                        EfL2A48->unkC4 = D_80753024[D_807FD584];
                    }
                    break;
                case 0x32:
                    if (D_807FC928 >= 2) {
                        func_806CA048(func_806C9FD8(temp_v1_3->unk2A0, &D_807FD584), D_807FD580);
                    }
                    EfL2PS->unkD4 = D_807530D0[D_807FD584];
                    EfL2A48->unkB8 = D_807530F0[D_807FD584];
                    EfL2A48->unkC4 = D_8075310C[D_807FD584];
                    break;
                case 0xE:
                    if (D_807FC928 >= 2) {
                        func_806CA048(func_806C9FD8(temp_v1_3->unk2A0, &D_807FD584), D_807FD580);
                    }
                    if (func_80714608(0) != 0) {
                        EfL2A48->unkC0 = D_80753128[D_807FD584] * 10.0f;
                        EfL2A48->unkB8 = D_80753144[D_807FD584] * 10.0f;
                        EfL2PS->unk38 = D_807531FC[D_807FD584] * 10.0f;
                        EfL2PS->unkD4 = 0xA;
                        EfL2A48->unkC4 = D_8075310C[D_807FD584];
                    } else {
                        EfL2A48->unkC0 = D_80753128[D_807FD584];
                        EfL2A48->unkB8 = D_80753144[D_807FD584];
                        if (arg0 != 0) {
                            EfL2PS->unkD4 = D_80753160[D_807FD584];
                        }
                        EfL2A48->unkC4 = D_8075310C[D_807FD584];
                    }
                    break;
                case 0x37:
                    EfL2PS->unkD4 = D_807530B0[D_807FD584];
                    break;
                }
                if ((D_807FC928 >= 2) && (sp2C == 0)) {
                    EfL2PS->unkD4 = 0x3C;
                }
                if (D_807FBB48->unk154 == 0x36) {
                    if (D_807FBB48->unk6A & 4) {
                        EfL2A48->unkC0 = D_80753078[D_807FD584] / 4.0f;
                    } else {
                        EfL2A48->unkC0 = D_80753078[D_807FD584];
                    }
                }
                EfL2PS->unk50 = 0;
            }
        }
    }
}
