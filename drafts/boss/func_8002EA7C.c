// func_8002EA7C (src/boss/A7A0.c): from .scratch/Boss3E/func_8002EA7C_best.c
typedef struct Boss2E_A7A0_178 {
    void *unk0;
    char pad4[0x10];
    u8 unk14;
    u8 unk15;
} Boss2E_A7A0_178;

typedef struct Boss2E_A7A0_Sub4 {
    char pad0[0x64];
    u16 unk64;
} Boss2E_A7A0_Sub4;

typedef struct Boss2E_A7A0_Sub140 {
    char pad0[0xC];
    s32 unkC;
} Boss2E_A7A0_Sub140;

typedef struct Boss2E_A7A0_Actor {
    char pad0[4];
    Boss2E_A7A0_Sub4 *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x60];
    f32 unkC4;
    char padC8[4];
    u8 unkCC;
    char padCD[0x73];
    Boss2E_A7A0_Sub140 *unk140;
    char pad144[2];
    s16 unk146;
    char pad148[0xC];
    u8 unk154;
    u8 unk155;
    char pad156[0x22];
    Boss2E_A7A0_178 *unk178;
} Boss2E_A7A0_Actor;

typedef struct Boss2E_A7A0_BB70 {
    char pad[0x1B];
    u8 unk1B;
    char pad1C[0x200 - 0x1C];
    u8 unk200;
} Boss2E_A7A0_BB70;

typedef struct Boss2E_A7A0_DC90 {
    char pad[0x1A];
    u16 unk1A;
} Boss2E_A7A0_DC90;

typedef struct Boss2E_A7A0_DC94 {
    char pad[0x7C];
    f32 unk7C;
    char pad80[4];
    f32 unk84;
} Boss2E_A7A0_DC94;

typedef struct Boss2E_A7A0_DC9C {
    char pad[0xD];
    u8 unkD;
} Boss2E_A7A0_DC9C;

extern u8 *D_80035A80[];
extern Boss2E_A7A0_DC90 *D_807FDC90;
extern Boss2E_A7A0_DC94 *D_807FDC94;
void behaviourFrameBegin(void);
void func_80028878(u8 *);
void func_80724CA4(s32, s32);
void func_8002DC60(void);
void func_8061CC40(void *, s32, s32);
s32 func_8061CB98(s32);
void actorMoveWithinZone(s32, f32, f32, s32, f32);
void playerStateQueueCallback(s32, void *, s32);
void func_8066EB40(void *, f32);
void func_8066E5F8(void *, s32, s32);
s32 func_80629148(void);
void func_805FF158(s32);
void func_805FF378(s32, s32);
void func_80027BA8(u8 *, s32, f32);
void func_80614D00(void *, f32, f32);
void func_8072A450(void);
s32 func_8072881C(s32, void *);

#define ACTOR40 ((Boss2E_A7A0_Actor *)D_807FBB40)
#define ACTOR4C ((Boss2E_A7A0_Actor *)D_807FBB4C)
#define BB70 (*(Boss2E_A7A0_BB70 *)&D_807FBB70)
#define DC9C ((Boss2E_A7A0_DC9C *)D_807FDC9C)

void func_8002EA7C(void) {
    Boss2E_A7A0_178 *sp178;
    u8 *sp28;

    sp178 = (Boss2E_A7A0_178 *)D_807FBB40->unk178;
    sp28 = D_80035A80[sp178->unk14];
    behaviourFrameBegin();
    func_80028878(sp28);
    if (!(ACTOR40->unk60 & 0x10)) {
        ACTOR40->unk146 = 1;
        ACTOR40->unk154 = 0x1E;
        ACTOR40->unk155 = 0;
        ACTOR40->unkCC = 1;
        func_80724CA4(2, 1);
        func_8002DC60();
        ACTOR40->unkC4 = 0.0f;
    }
    if ((ACTOR4C->unk154 == 0x48) && !(D_807FDC90->unk1A & 0x8000)) {
        func_8061CC40(ACTOR40, 0, 1);
        D_807FDC90->unk1A |= 0x8000;
    }
    if ((func_8061CB98(0) == 0) && (func_8061CB98(1) == 0) && ((ACTOR4C->unk154 != 0x67) || (ACTOR40->unk154 != 0x42))) {
        switch (ACTOR40->unk154) {
        case 0x2B:
            switch (ACTOR40->unk155) {
            case 0:
                actorSetTargetSpeed(D_807FBB40, 0);
                func_8061CC40(ACTOR4C, 9, 1);
                func_8002E9B8(0x3F5, 0x679);
                ACTOR40->unk155++;
                break;
            case 2:
                actorSetTargetSpeed(D_807FBB40, DC9C->unkD);
                func_8002E9B8(0x3F4, 0x678);
                ACTOR40->unk155++;
                break;
            case 3:
                if (BB70.unk1B != 0) {
                    ACTOR40->unk154 = 0x31;
                    ACTOR40->unk155 = 0;
                } else if (BB70.unk200 == 2) {
                    func_8002E7A0(NULL);
                    ACTOR40->unk154 = 0x2C;
                    ACTOR40->unk155 = 0;
                }
                actorMoveWithinZone(0x23, D_807FDC94->unk7C, D_807FDC94->unk84, 0, 0.0f);
                break;
            }
            break;
        case 0x2C:
            if (ACTOR40->unk155 == 0) {
                playerStateQueueCallback(0x36, ACTOR40, 0);
                func_8002EA14();
                ACTOR40->unk154 = 0x42;
                ACTOR40->unk155 = 0;
            }
            break;
        case 0x1E:
            sp178->unk14 = 0;
            sp178->unk15 = 0;
            ACTOR40->unk154 = sp28[sp178->unk15++];
            ACTOR40->unk155 = 0;
            break;
        case 0:
            switch (ACTOR40->unk155) {
            case 0:
                func_8002E9B8(0x3F5, 0x679);
                ACTOR40->unk155++;
                break;
            case 2:
                func_8002EA14();
                ACTOR40->unk154 = sp28[sp178->unk15++];
                ACTOR40->unk155 = 0;
                func_8066EB40(ACTOR4C, (f32)(ACTOR4C->unk140->unkC * 2));
                func_8066E5F8(ACTOR4C, 6, 1);
                func_8066E5F8(ACTOR4C, 7, 1);
                func_8066E5F8(ACTOR4C, 8, 1);
                func_8066E5F8(ACTOR4C, 9, 1);
                func_8066E5F8(ACTOR4C, 0xA, 1);
                func_8066E5F8(ACTOR4C, 0xB, 1);
                break;
            }
            break;
        case 0x31:
            switch (ACTOR40->unk155) {
            case 0:
                if (sp178->unk14 == 3) {
                    ACTOR40->unk154 = 0x37;
                    ACTOR40->unk155 = 0;
                } else {
                    func_80614EBC(D_807FBB40, 0x3F2);
                    func_80614EBC(sp178->unk0, 0x3F1);
                    actorSetTargetSpeed(D_807FBB40, 0);
                    ACTOR40->unk155++;
                }
                break;
            case 1:
                actorMoveWithinZone(0, 0.0f, 0.0f, 0x310, 0.0f);
                break;
            case 2:
                func_8002E7A0(NULL);
                func_8002EA14();
                sp178->unk15 = 0;
                sp178->unk14++;
                ACTOR40->unk154 = D_80035A80[sp178->unk14][sp178->unk15++];
                ACTOR40->unk155 = 0;
                break;
            }
            break;
        case 0x37:
            switch (ACTOR40->unk155) {
            case 0:
                func_806782C0(sp178->unk0);
                func_80614EBC(D_807FBB40, 0);
                func_8061CC40(ACTOR40, 5, 1);
                ACTOR40->unk155++;
                break;
            case 1:
                if (func_80629148() != 0) {
                    func_805FF158(0);
                    func_805FF378(0xCE, 0);
                    ACTOR40->unk155++;
                }
                break;
            }
            break;
        default:
            func_80027BA8(sp28, 0x10, 0.0f);
            break;
        }
    } else if (ACTOR40->unk4->unk64 == 0x406) {
        func_80614D00(ACTOR40, 0.0f, 0.0f);
    }
    func_8072A450();
    if (func_8072881C(0, (u8 *)D_807FDC90 + 0x28) != 0) {
        func_8072881C(0x81, (u8 *)D_807FDC90 + 0x28);
    }
    func_806319C4(D_807FBB40, 0);
}

#undef ACTOR40
#undef ACTOR4C
#undef BB70
#undef DC9C
