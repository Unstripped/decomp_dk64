// func_80030EC4 (src/boss/C920.c): from .scratch/Boss3E/func_80030EC4_best.c
typedef struct Boss2E_C920_Sub178 {
    u8 pad0[0x14];
    u8 unk14;
    u8 unk15;
} Boss2E_C920_Sub178;

typedef struct Boss2E_C920_Actor {
    u8 pad0[0x60];
    s32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[0xC4 - 0xBC];
    f32 unkC4;
    u8 padC8[0xCC - 0xC8];
    u8 unkCC;
    u8 padCD[0xE4 - 0xCD];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    u8 padEA[0xEC - 0xEA];
    s16 unkEC;
    s16 unkEE;
    u8 padF0[0x110 - 0xF0];
    u8 unk110;
    u8 pad111[0x128 - 0x111];
    s16 unk128;
    u8 pad12A[0x132 - 0x12A];
    s16 unk132;
    u8 pad134[0x144 - 0x134];
    u8 unk144;
    u8 pad145[1];
    s16 unk146;
    u8 pad148[0x154 - 0x148];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x160 - 0x156];
    f64 unk160;
    u8 pad168[0x178 - 0x168];
    Boss2E_C920_Sub178 *unk178;
} Boss2E_C920_Actor;

typedef struct Boss2E_C920_DC98 {
    u8 pad0[0x20];
    s16 unk20[1];
} Boss2E_C920_DC98;

typedef struct Boss2E_C920_C924 {
    u8 pad0[0x2C0];
    u8 unk2C0;
} Boss2E_C920_C924;

typedef struct Boss2E_C920_DC9C {
    u8 pad0[0xC];
    u8 unkC;
} Boss2E_C920_DC9C;

typedef struct Boss2E_C920_D580 {
    u8 pad0[0xD4];
    s16 unkD4;
} Boss2E_C920_D580;

extern u8 *D_80035AC0[];
extern f32 D_80035AC4[];
extern u8 *D_80035AC8[];
extern u8 D_80035ACF[];
extern f32 D_80035AD4[];
extern f32 D_80035AE4[];
extern f32 D_80036AC0;
extern u8 D_807FBD70;
extern Boss2E_C920_C924 *D_807FC924;
extern Boss2E_C920_D580 *D_807FD580;
extern Boss2E_C920_DC98 *D_807FDC98;
extern Boss2E_C920_DC9C *D_807FDC9C;

void behaviourFrameBegin(void);
void func_80028878(u8 *);
void func_80626110(void *, s32, s32);
void func_80724CA4(s32, s32);
void func_806D0430(f32);
void func_800290D4(s32);
void flagSet(s32, s32, s32);
void func_8061CC40(void *, s32, s32);
void func_80641874(s32, s32);
void actorSetTargetSpeed(void *, s32);
void actorMoveWithinZone(s32, f32, f32, s32, f32);
void func_80614D00(void *, f32, f32);
void func_80614EBC(void *, s32);
s32 func_8061CB50(void);
void func_806D0468(void *, s32);
s32 func_806C9974(s32, s32);
void func_80614E78(void *, s32);
void func_8072CFE8(s16 *, s16 *, s16 *, void *);
void func_806A1008(u8 *);
s16 func_806CC10C(s16, s16);
s16 func_806CC190(s16, s16, f32);
s32 func_80629148(void);
void func_80027BA8(u8 *, s32, void *);
void func_8065D244(s32);
void func_8065D254(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
s32 func_8072881C(s32, void *);
void func_806319C4(void *, s32);

void func_80030EC4(void) {
    Boss2E_C920_Sub178 *sp178;
    u8 *sp28;
    s16 sp54;
    s16 sp52;
    s16 sp50;
    Boss2E_C920_Actor *actor;
    s32 var_a0;

    actor = (Boss2E_C920_Actor *)D_807FBB40;
    sp178 = actor->unk178;
    sp28 = D_80035AC0[sp178->unk14];
    behaviourFrameBegin();
    func_80028878(sp28);
    actor = (Boss2E_C920_Actor *)D_807FBB40;
    if (!(actor->unk60 & 0x10)) {
        func_80626110(D_807F5D10, 0, 0);
        ((Boss2E_C920_Actor *)D_807FBB40)->unk146 = 5;
        ((Boss2E_C920_Actor *)D_807FBB40)->unk154 = 0x1E;
        ((Boss2E_C920_Actor *)D_807FBB40)->unk155 = 0;
        ((Boss2E_C920_Actor *)D_807FBB40)->unkCC = 0;
        func_80724CA4(2, 1);
        ((Boss2E_C920_Actor *)D_807FBB40)->unk110 = 0;
        actor = (Boss2E_C920_Actor *)D_807FBB40;
        actor->unk60 &= ~0x8000;
        func_806D0430(0.45f);
        func_800290D4(0);
        flagSet(0x5F, 0, 2);
        actor = (Boss2E_C920_Actor *)D_807FBB40;
    }
    if (D_807FDC90->unk1A & 1) {
        actor->unk128 -= (sp178->unk14 <= 0) ? 5 : 10;
        actor = (Boss2E_C920_Actor *)D_807FBB40;
        if (actor->unk128 < 0) {
            actor->unk128 = 0;
            D_807FDC90->unk1A &= ~1;
        }
    } else if ((actor->unk154 == 0x29) && (D_807FDC90->unk1A & 0x40) && (actor->unk128 < 0xFF)) {
        if (!(D_807FDC90->unk1A & 0x8000)) {
            func_8061CC40(actor, 2, 1);
            D_807FDC90->unk1A |= 0x8000;
        } else {
            func_80641874(2, 0);
            actor->unk128 += 5;
            if (actor->unk128 > 0x100) {
                actor->unk128 = 0xFF;
            }
        }
    }
    if ((D_807FC924->unk2C0 == 1 || actor->unk154 == 0x42 || actor->unk154 == 0x27) && actor->unk144 == 1) {
        actorSetTargetSpeed(D_807FBB40, 0);
        actor->unk154 = 0x29;
        actor->unk155 = 1;
    }
    switch (actor->unk154) {
    case 0x29:
        switch (actor->unk155) {
        case 0:
            actorMoveWithinZone(0, (f32)D_807FDC90->unkA, (f32)D_807FDC90->unkE, 0x309, 0.0f);
            break;
        case 1:
            if (sp178->unk14 >= 2) {
                func_80030E58();
            }
            actor->unk132 = 4;
            func_80030920(0);
            func_80614D00(actor, D_80035AE4[sp178->unk14], 0.0f);
            actor->unk155++;
            break;
        case 3:
            actor->unk160 = 0.0;
            actor->unk155++;
            /* fallthrough */
        case 4:
            func_80030C30(D_80035AD4[sp178->unk14]);
            if (sp178->unk14 == 3) {
                func_80030D50();
            }
            break;
        case 5:
            actor->unk155++;
            break;
        case 6:
            if (D_807FBD70 == 5 && D_807FBB4C->unk154 == 0x24 && actor->unk160 > 0.79) {
                if (sp178->unk14 == 3) {
                    actor->unk154 = 0x37;
                    actor->unk155 = 0;
                } else {
                    func_80614EBC(D_807FBB4C, 0);
                    func_80614EBC(D_807FBB40, 0);
                    func_8061CC40(D_807FBB40, 0x16, 1);
                    flagSet(0x1B0, 1, 0);
                }
            } else {
                actor->unk132 = 1;
                actor->unk155 = 8;
                func_8061CC40(D_807FBB40, 0x17, 1);
                func_80614EBC(D_807FBB40, 0);
                func_80641874(2, 0xFF);
            }
            break;
        case 7:
            D_807FD580->unkD4 = 0x12C;
            func_8061CC40(D_807FBB40, 0x18, 1);
            func_80641874(2, 0xFF);
            func_80614D00(D_807FBB40, 1.0f, 0.0f);
            func_80614EBC(D_807FBB40, 0);
            actor->unk155 = 0xA;
            break;
        case 8:
            if (func_8061CB50() == 0) {
                actor->unk155++;
            }
            break;
        case 9:
            sp178->unk15 = 0;
            sp178->unk14++;
            sp28 = D_80035AC0[sp178->unk14];
            /* fallthrough */
        case 10:
        case 11:
            break;
        case 12:
            if (func_8061CB50() == 0) {
                func_806D0468(D_807FBB4C, 1);
                actorSetTargetSpeed(D_807FBB40, D_807FDC9C->unkC);
                if (actor->unk132 != 1) {
                    if (func_806C9974(0, -1) != 0) {
                        func_80614E78(D_807FBB4C, 0x27);
                        D_807FBB4C->unk154 = 0x36;
                        D_807FBB4C->unk155 = 0;
                        actor->unk132 = 1;
                        sp178->unk15 = 0;
                        sp178->unk14 = 3;
                        func_80030AE0(NULL);
                        actor->unk154 = sp28[sp178->unk15++];
                        actor->unk155 = 0;
                    } else {
                        func_80614EBC(D_807FBB40, 0x3E4);
                        func_80030E58();
                    }
                }
            }
            break;
        }
        var_a0 = actor->unk60;
        break;
    case 0x28:
        func_80030E58();
        actor->unk154 = sp28[sp178->unk15++];
        actor->unk155 = 0;
        var_a0 = actor->unk60;
        break;
    case 0x27:
        switch (actor->unk155) {
        case 0:
            func_8072CFE8(&sp54, &sp52, &sp50, actor);
            func_806A1008(D_80035ACF + (D_807FDC98->unk20[D_807FDC90->unk1A & 0x7F] * 2));
            actor->unkEC = func_80665DE0((f32)sp54, (f32)sp50, actor->unk7C, actor->unk84);
            if (func_806CC10C(actor->unkE6, actor->unkEC) < 0) {
                func_80614EBC(D_807FBB40, 0x401);
            } else {
                func_80614EBC(D_807FBB40, 0x402);
            }
            actorSetTargetSpeed(D_807FBB40, 0);
            actor->unk155++;
            break;
        case 1:
            actor->unkE6 = func_806CC190(actor->unkE6, (s16)(actor->unkEC + 0x800), 0x41200000);
            actorMoveWithinZone(0, (f32)D_807FDC90->unkA, (f32)D_807FDC90->unkE, 0x309, 0.0f);
            break;
        case 2:
            actor->unkEE = actor->unkE6;
            actor->unkB8 = -150.0f;
            actor->unk155++;
            /* fallthrough */
        case 3:
            actorMoveWithinZone(0, (f32)D_807FDC90->unkA, (f32)D_807FDC90->unkE, 0x309, 0.0f);
            break;
        case 4:
            actor->unkB8 = actor->unkB8;
            actor->unkE6 = actor->unkEC + 0x800;
            actor->unkEE = actor->unkE6;
            actorSetTargetSpeed(D_807FBB40, D_807FDC9C->unkC);
            actor->unk154 = sp28[sp178->unk15++];
            actor->unk155 = 0;
            break;
        }
        var_a0 = actor->unk60;
        break;
    case 0x1E:
        sp178->unk14 = 0;
        sp178->unk15 = 0;
        actor->unk154 = sp28[sp178->unk15++];
        actor->unk155 = 0;
        if (D_807FDC9C->unkC != 0) {
            actor->unkB8 = (f32)D_807FDC9C->unkC;
        }
        var_a0 = actor->unk60;
        break;
    case 0:
        if (actor->unk155 != 0) {
            if (actor->unk155 == 2) {
                actor->unk154 = sp28[sp178->unk15++];
                actor->unk155 = 0;
            }
        } else {
            func_80614EBC(D_807FBB40, 0x3EA);
            actor->unk155++;
        }
        var_a0 = actor->unk60;
        break;
    case 0x37:
        if (actor->unk155 == 0) {
            if (func_80629148() != 0) {
                D_807FBB4C->unk60 |= 4;
                func_8061CC40(D_807FBB40, 0x1A, 1);
                actor->unk155++;
            }
        } else {
            actor->unk155++;
        }
        var_a0 = actor->unk60;
        break;
    default:
        func_80027BA8(sp28, 0x19, D_807FBB40);
        var_a0 = actor->unk60;
        break;
    }
    if (var_a0 & 4) {
        func_8065D244(1);
        func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0x3C, 0x3C, 1, 0x12C, 0, 0x44000000, 0, 1.0f);
    }
    if (func_8072881C(0, (u8 *)D_807FDC90 + 0x28) != 0) {
        func_8072881C(0x81, (u8 *)D_807FDC90 + 0x28);
    }
    func_806319C4(D_807FBB40, 0);
}
