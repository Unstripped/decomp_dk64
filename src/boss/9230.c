#include "common.h"

typedef struct Boss2F_9230_178 {
    char pad0[0x14];
    u8 unk14;
    u8 unk15;
    u8 unk16;
    char pad17[1];
    u8 unk18;
    u8 unk19;
} Boss2F_9230_178;

typedef struct Boss2F_9230_Actor {
    char pad[0x60];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x30];
    f32 unkB8;
    char padBC[0x10];
    u8 unkCC;
    char padCD[0x65];
    s16 unk132;
    char pad134[0x12];
    s16 unk146;
    char pad148[0xC];
    u8 unk154;
    u8 unk155;
    char pad156[0x22];
    Boss2F_9230_178 *unk178;
} Boss2F_9230_Actor;

typedef struct Boss2F_9230_BB4C {
    char pad[0x154];
    u8 unk154;
} Boss2F_9230_BB4C;

typedef struct Boss2F_9230_D580 {
    char pad[0xBE];
    s16 unkBE;
} Boss2F_9230_D580;

typedef struct Boss2F_9230_DC90 {
    char pad[0x2C];
    s16 unk2C;
    s16 unk2E;
} Boss2F_9230_DC90;

typedef struct Boss2F_9230_DC9C {
    char pad[0xC];
    u8 unkC;
} Boss2F_9230_DC9C;

extern u8 *D_80035A50[];
extern s32 D_807F5D10;
extern Boss2F_9230_Actor *D_807FBB40;
extern void *D_807FBB44;
extern Boss2F_9230_BB4C *D_807FBB4C;
extern u8 D_807FBD70;
extern Boss2F_9230_D580 *D_807FD580;
extern Boss2F_9230_DC90 *D_807FDC90;
extern Boss2F_9230_DC9C *D_807FDC9C;

void func_80027BA8(u8 *, s32, f32);
void func_80028878(u8 *);
void func_80641874(s32, s32);
void func_805FF378(s32, s32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_80613C48(void *, s32, f32, f32);
void func_80614D00(void *, f32, f32);
void actorScriptStart(Boss2F_9230_Actor *, s32);
s32 func_8061CB50(void);
void func_8061CC40(Boss2F_9230_Actor *, s32, s32);
void func_80626110(s32, s32, s32);
s32 func_80629148();
void func_806319C4(Boss2F_9230_Actor *, s32);
void func_80641874();
void projectileSpawnWithShockwave(s32, f32, s32, s32, s32, s32, f32, f32, f32, f32);
s32 func_8072881C(s32, void *);
void behaviourFrameBegin(void);
void func_8072A450(void);
void actorMoveWithinZone(s32, f32, f32, s32, f32);
void actorSetTargetSpeed(Boss2F_9230_Actor *, s32);
void func_8072DEA8(s32, s32, void *);
void func_8072E1A4(s32, void *);

void func_8002D230(void) {
    Boss2F_9230_178 *sp44;
    s32 pad40;
    u8 *sp3C;

    sp44 = D_807FBB40->unk178;
    sp3C = D_80035A50[sp44->unk14];
    behaviourFrameBegin();
    func_80028878(sp3C);
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80626110(D_807F5D10, 0, 0);
        D_807FBB40->unk146 = 5;
        D_807FBB40->unk154 = 0x1E;
        D_807FBB40->unk155 = 0;
        D_807FBB40->unkCC = 1;
    }
    switch (D_807FBB40->unk154) {
    case 0x2B:
        func_80641874(1, 0);
        func_80641874(2, 0);
        func_80641874(3, 0);
        func_80641874(4, 0);
        D_807FBB40->unk154 = sp3C[sp44->unk15++];
        D_807FBB40->unk155 = 0;
        break;
    case 0x1E:
        sp44->unk14 = 0;
        sp44->unk15 = 0;
        D_807FBB40->unk154 = sp3C[sp44->unk15++];
        D_807FBB40->unk155 = 0;
        D_807FBB40->unkB8 = D_807FDC9C->unkC;
        break;
    case 0:
        switch (D_807FBB40->unk155) {
        case 0:
            actorScriptStart(D_807FBB40, 0x3EA);
            D_807FBB40->unk155++;
            break;
        case 2:
            D_807FBB40->unk154 = sp3C[sp44->unk15++];
            D_807FBB40->unk155 = 0;
            break;
        }
        break;
    case 0x29:
    case 0x2A:
        func_8072E1A4(0xA, D_807FBB4C);
        if (D_807FBD70 == 4) {
            func_80641874(D_807FD580->unkBE, 1);
            if (sp44->unk14 == 3) {
                D_807FBB40->unk154 = 0x37;
                D_807FBB40->unk155 = 0;
            } else {
                func_8072DEA8(0x3EE, 0x31, D_807FBB4C);
                func_8061CC40(D_807FBB40, 1, 1);
                D_807FBB40->unkB8 *= 0.7;
            }
        } else if (D_807FBD70 == 2 && D_807FBB40->unk155 > 0) {
            actorScriptStart(D_807FBB40, 0);
            D_807FBB40->unk154 = 0;
            D_807FBB40->unk155 = 0;
        } else
            if (D_807FBB4C->unk154 != 0x42 && D_807FBB4C->unk154 != 0x44 && D_807FBB40->unk155 > 0) {
                actorScriptStart(D_807FBB40, 0);
                D_807FBB40->unk154 = sp3C[sp44->unk15++];
                D_807FBB40->unk155 = 0;
            } else {
            switch (D_807FBB40->unk155) {
            case 0:
                sp44->unk18 = sp3C[sp44->unk15++];
                sp44->unk19 = sp3C[sp44->unk15++];
                D_807FBB40->unk155++;
                /* fallthrough */
            case 1:
                D_807FDC90->unk2C = sp44->unk18;
                D_807FBB40->unk155++;
                /* fallthrough */
            case 2:
                D_807FBB40->unk132 = 1;
                actorScriptStart(D_807FBB40, 0x3EC);
                D_807FBB40->unk155++;
                break;
            case 4:
                if (D_807FDC90->unk2C != 0) {
                    D_807FDC90->unk2C--;
                    D_807FBB40->unk155 = 2;
                } else {
                    D_807FBB40->unk132 = 2;
                    actorScriptStart(D_807FBB40, 0x3E9);
                    D_807FDC90->unk2C = sp44->unk19;
                    D_807FBB40->unk155++;
                }
                break;
            case 5:
                if (D_807FDC90->unk2C != 0) {
                    D_807FDC90->unk2C--;
                } else if (D_807FBB40->unk154 == 0x2A) {
                    D_807FBB40->unk154 = sp3C[sp44->unk15++];
                    D_807FBB40->unk155 = 0;
                } else {
                    D_807FBB40->unk155 = 1;
                }
                break;
            }
        }
        break;
    case 0x28:
    case 0x2C:
        func_8072E1A4(0xA, D_807FBB4C);
        if (D_807FBB4C->unk154 == 0x42 && D_807FBB40->unk155 > 0) {
            actorScriptStart(D_807FBB40, 0);
            D_807FBB40->unk154 = sp3C[sp44->unk15++];
            D_807FBB40->unk155 = 0;
        } else {
            switch (D_807FBB40->unk155) {
            case 0:
                sp44->unk18 = sp3C[sp44->unk15++];
                D_807FBB40->unk155++;
                /* fallthrough */
            case 1:
                if (func_8061CB50() == 0) {
                    D_807FDC90->unk2C = sp44->unk18;
                    D_807FDC90->unk2E = 9;
                    actorScriptStart(D_807FBB40, 0x3E7);
                    D_807FBB40->unk155++;
                }
                break;
            case 3:
                if (D_807FBB40->unk154 == 0x28 || (D_807FBB40->unk154 == 0x2C && (D_807FDC90->unk2E % 3) == 0)) {
                    projectileSpawnWithShockwave(0xB8, 0.14f, 0x64, 0xFF, 0x96, 3, (f32)(((f64)sp44->unk14 * 0.01) + 1.04), 0.0f, 0.0f, 0.0f);
                    func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x25A, 0xFF, 0x7F, 1, 0, 0.3f, 0);
                    func_80613C48(D_807FBB44, 0x4F9, 0.0f, 0.0f);
                    func_80614D00(D_807FBB44, 0.5f, 0.0f);
                }
                if (D_807FBB40->unk154 == 0x28 || (D_807FBB40->unk154 == 0x2C && D_807FDC90->unk2E == 0)) {
                    D_807FBB40->unk155++;
                } else {
                    D_807FDC90->unk2E--;
                    break;
                }
                /* fallthrough */
            case 4:
                if (D_807FDC90->unk2C != 0) {
                    D_807FDC90->unk2C--;
                } else if (sp44->unk16 != 0) {
                    D_807FBB40->unk155 = 1;
                } else {
                    D_807FBB40->unk154 = sp3C[sp44->unk15++];
                    D_807FBB40->unk155 = 0;
                }
                break;
            }
        }
        break;
    case 0x31:
        switch (D_807FBB40->unk155) {
        case 0:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4310, 0.0f);
            break;
        case 1:
            D_807FBB40->unkB8 = -40.0f;
            D_807FBB40->unk155++;
            /* fallthrough */
        case 2:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4310, 0.0f);
            break;
        case 3:
            actorSetTargetSpeed(D_807FBB40, D_807FDC9C->unkC);
            sp44->unk15 = 0;
            sp44->unk16 = 0;
            sp44->unk14++;
            sp3C = D_80035A50[sp44->unk14];
            actorScriptStart(D_807FBB40, 0x3E3);
            D_807FBB40->unk154 = sp3C[sp44->unk15++];
            D_807FBB40->unk155 = 0;
            break;
        }
        break;
    case 0x37:
        switch (D_807FBB40->unk155) {
        case 0:
            actorScriptStart(D_807FBB40, 0);
            func_8061CC40(D_807FBB40, 2, 1);
            D_807FBB40->unk155++;
            break;
        case 1:
            if (func_80629148() != 0) {
                func_805FF158(0);
                func_805FF378(0xCC, 0);
                D_807FBB40->unk155++;
            }
            break;
        }
        break;
    default:
        func_80027BA8(sp3C, 0x10, 0.0f);
        break;
    }
    func_8072A450();
    if (func_8072881C(0, (u8 *)D_807FDC90 + 0x28) != 0) {
        func_8072881C(0x81, (u8 *)D_807FDC90 + 0x28);
    }
    func_806319C4(D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9230/D_80036660.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9230/D_80036678.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9230/D_80036688.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9230/D_8003669C.s")
