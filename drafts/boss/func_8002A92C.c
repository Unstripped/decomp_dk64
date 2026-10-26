// func_8002A92C (src/boss/6240.c): from .scratch/Boss3F/func_8002A92C_best.c
typedef struct Boss3F_6240_178 {
    char pad0[0x12];
    u16 unk12;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    char pad17[1];
    u8 unk18;
    char pad19[3];
    s16 unk1C;
} Boss3F_6240_178;
typedef struct Boss3F_6240_Sub4_0 {
    char pad[4];
    f32 unk4;
} Boss3F_6240_Sub4_0;
typedef struct Boss3F_6240_SubActor4 {
    Boss3F_6240_Sub4_0 *unk0;
    char pad4[0x64 - 4];
    u16 unk64;
} Boss3F_6240_SubActor4;
typedef struct Boss3F_6240_Actor {
    char pad0[4];
    Boss3F_6240_SubActor4 *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x6E - 0x64];
    s16 unk6E;
    char pad70[0xC];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x1C];
    f32 unkA4;
    char padA8[0x10];
    f32 unkB8;
    char padBC[4];
    f32 unkC0;
    f32 unkC4;
    char padC8[4];
    u16 unkCC;
    char padCE[0xE6 - 0xCE];
    s16 unkE6;
    char padE8[0x132 - 0xE8];
    s16 unk132;
    s16 unk134;
    char pad136[0xE];
    u8 unk144;
    char pad145[0xF];
    u8 unk154;
    u8 unk155;
    char pad156[0x16A - 0x156];
    u8 unk16A;
    u8 unk16B;
    u8 unk16C;
    char pad16D[0xB];
    Boss3F_6240_178 *unk178;
    BossC_6240_17C *unk17C;
} Boss3F_6240_Actor;
typedef struct Boss3F_6240_Sub1FC {
    char pad[0x5C];
    u8 unk5C;
} Boss3F_6240_Sub1FC;
typedef struct Boss3F_6240_BB70 {
    char pad0[0x15];
    u8 unk15;
    char pad16[0x1FC - 0x16];
    Boss3F_6240_Sub1FC *unk1FC;
    u8 unk200;
} Boss3F_6240_BB70;
typedef struct Boss3F_6240_C924 {
    char pad0[0x2C0];
    s32 unk2C0;
} Boss3F_6240_C924;
typedef struct Boss3F_6240_D580 {
    char pad0[0xD4];
    s16 unkD4;
    char padD6[0x1D8 - 0xD6];
    f32 unk1D8;
} Boss3F_6240_D580;
typedef struct Boss3F_6240_DC90 {
    char pad0[0xA];
    s16 unkA;
    s16 unkC;
    s16 unkE;
    char pad10[6];
    s16 unk16;
    char pad18[2];
    s16 unk1A;
    char pad1C[9];
    u8 unk25;
    char pad26[5];
    s16 unk2C;
} Boss3F_6240_DC90;
typedef struct Boss3F_6240_Sub4 {
    char pad[0x10];
    s16 unk10;
} Boss3F_6240_Sub4;
typedef struct Boss3F_6240_DC94 {
    char pad0[4];
    Boss3F_6240_Sub4 **unk4;
    char pad8[0x74];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} Boss3F_6240_DC94;
typedef struct Boss3F_6240_DC98 {
    char pad0[0x30];
    f32 unk30;
    char pad34[0x46 - 0x34];
    u16 unk46;
} Boss3F_6240_DC98;
typedef struct Boss3F_6240_DC9C {
    char pad0[0xC];
    s16 unkC;
} Boss3F_6240_DC9C;
typedef struct Boss3F_6240_SubA0 {
    char pad[0xA0];
    s16 unkA0;
    s16 unkA2;
    s16 unkA4;
} Boss3F_6240_SubA0;
typedef struct Boss3F_6240_DCA0 {
    char pad0[0x14];
    Boss3F_6240_SubA0 *unk14;
} Boss3F_6240_DCA0;

extern u8 *D_80035A20[];
extern u8 *D_80035A34[];
extern u8 D_800362F0[];
extern u8 D_8071FB34[];
extern f32 D_807502E8;
extern f32 D_807502FC;
extern s32 D_8076A0A8;
extern s32 D_8076D1F8;
extern s32 D_807F5D10;
extern void *D_807FBB44;
extern Boss3F_6240_BB70 D_807FBB70;
extern Boss3F_6240_C924 *D_807FC924;
extern Boss3F_6240_D580 *D_807FD580;
extern Boss3F_6240_DC90 *D_807FDC90;
extern Boss3F_6240_DC94 *D_807FDC94;
extern Boss3F_6240_DC98 *D_807FDC98;
extern Boss3F_6240_DC9C *D_807FDC9C;
extern Boss3F_6240_DCA0 *D_807FDCA0;

void func_80027840(void *);
void func_80027BA8(u8 *, s32, f32);
void func_80028478(s32, s16, s16, s16, s32, s32);
void func_80604CBC(void *, f32, f32, f32, s32, s32, f32, s32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_80609140(s32, s32, f32, f32, s32, s32);
void func_80613C48(void *, s16, f32, f32);
void func_80614D00(void *, f32, f32);
void func_80614EBC(void *, s32);
void func_8061C458(s32, void *);
void func_8061C464(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
s32 func_8061CB50(void);
void func_8061CC40(void *, s32, s32);
void func_806224CC(s32, void *);
void func_806225C0(s32);
void func_80626110(s32, s32, s32);
s32 func_80629148(void);
void func_80629174(void);
void func_806319C4(void *, s32);
void func_8063DA40(s16, s32);
f32 func_806614D0(f32);
void func_8066164C(void);
void func_806653C0(void *, f32, f32);
s16 func_80665DE0(f32, f32, f32, f32);
void func_8066635C(void *, f32, f32, f32, void *);
void func_8066E9EC(void *, s32, f32);
void func_80671C0C(void *, u8, f32 *, f32 *, f32 *);
s32 func_8067AF44(void *);
void func_80686F90(s32, s16, s16);
void func_806871DC(s32);
void func_80690814(void *, s32);
void func_80690A28(s32, s32, f32, f32, f32, f32, f32, void *);
void func_80690AB0(s16, s32, s32, s32, f32, f32, f32, f32, f32, void *);
void func_80691830(s32, f32, s32, s32, s32, s32, f32, f32, f32, f32);
void func_806978FC(void);
void func_806D0430(f32);
void func_806D0468(void *, s32);
void func_806FB370(s32, s32, s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_807158C0(void);
void func_8072881C(s32, void *);
void behaviourFrameBegin(void);
void actorApplyGravity(void);
void actorTurnTowardTarget(s32, f32, f32, s32);
void func_8072A450(void);
void actorMoveWithinZone(s32, f32, f32, s32, f32);
void actorSetTargetSpeed(void *, u8);
s32 func_8072D13C(s32, s32);
s32 flagGet(s32, s32);
void n_alSndpPlay(s32, s16, s32, s32, f32, s32, void *);
void n_alSndpStop(s32);


#define ACTOR ((Boss3F_6240_Actor *)D_807FBB40)

void func_8002A92C(void) {
    BossC_6240_17C *sp88;
    u8 *sp84;
    f32 sp80;
    u8 sp7F;
    u8 sp7E;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    s16 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    s32 sp54;
    s32 temp_s0;

    s32 var_v0;
    s16 var_v0_3, temp_v1_2;
    f32 var_fv0, var_fv1;
    Boss3F_6240_SubA0 *temp_v0_2;

                Boss3F_6240_178 *temp_s1;
    
    temp_s1 = ACTOR->unk178;
    sp88 = ACTOR->unk17C;
    if (D_8076A0A8 == 0xC5) {
        var_v0 = 0;
    } else {
        var_v0 = 1;
    }
    sp84 = *(D_80035A20 + (var_v0 * 5) + temp_s1->unk14);
    sp7E = 1;
    sp7F = 1;
    sp80 = ACTOR->unk80;
    behaviourFrameBegin();
    if (!(ACTOR->unk60 & 0x10)) {
        func_80626110(D_807F5D10, 0, 0);
        func_806FB370(5, 0, 1);
        func_80629174();
        func_806D0430(1.2f);
        func_806978FC();
        ACTOR->unkCC = 2U;
        func_80027840(&D_800362F0);
        D_807FDC98->unk30 = 3.0f;
        ACTOR->unkB8 = 0.0f;
        ACTOR->unk60 = (s32) (ACTOR->unk60 | 0x800000);
        D_807FDC98->unk46 = (u16) (D_807FDC98->unk46 | 0x20);
        temp_s1->unk1C = 0;
        ACTOR->unk154 = (u8) *(temp_s1->unk15 + sp84);
        temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
        ACTOR->unk155 = 0U;
    }
    if (D_807FD580->unkD4 < 0x32) {
        D_807FD580->unkD4 = D_807FD580->unkD4;
    } else {
        D_807FD580->unkD4 = 0x32;
    }
    ACTOR->unk16A = (u8) (u32) (((f64) func_80612794((s16) (D_8076A064 * 0x64)) * 50.0) + 200.0);
    ACTOR->unk16B = (u8) ACTOR->unk16A;
    ACTOR->unk16C = (u8) ACTOR->unk16A;
    if (ACTOR->unk154 == 0x55) {
        ACTOR->unk132 = 2;
    } else {
        ACTOR->unk132 = 1;
    }
    ACTOR->unk144 = 0x24;
    if (D_807FBB70.unk200 == 4) {
        if (temp_s1->unk14 == 3) {
            func_8066E9EC(D_807FBB40, 1, 0x43480000);
            func_8002A41C(0);
            ACTOR->unk154 = 0x56U;
            ACTOR->unk155 = 0U;
            func_80614EBC(D_807FBB40, 0x2D1);
            D_807FDC90->unk2C = 0x12C;
        } else {
            func_807158C0();
            func_8066164C();
            ACTOR->unk154 = 0x4DU;
            ACTOR->unk155 = 0U;
            ACTOR->unkC4 = (f32) D_807502FC;
            func_80614EBC(D_807FBB40, 0x2CD);
            D_807FDC90->unkC = -0x2BC;
            temp_s1->unk15 = 0U;
            sp84 = D_80035A34[++temp_s1->unk14];
            if ((temp_s1->unk14 == 3) && (D_8076A0A8 == 0xC5)) {
                func_8061CC40(D_807FBB40, 8, 1);
            } else {
                func_8061CC40(D_807FBB40, 2, 1);
            }
        }
    } else if ((D_807FBB70.unk200 == 5) && (D_807FC924->unk2C0 != 1)) {
        sp6C = 0x14B;
        func_80614EBC(D_807FBB40, 0x2D2);
        func_80671C0C(D_807FBB40, 2U, &sp78, &sp74, &sp70);
        if (ACTOR->unk134 == 1) {
            D_807FDC90->unk1A = (u16) (D_807FDC90->unk1A | 0x8000);
        }
        D_807FDC90->unk16 = (s16) (*D_807FDC94->unk4)->unk10;
        ACTOR->unk60 = (s32) (ACTOR->unk60 | 0x20000000);
        sp54 = func_80611A44();
        temp_s0 = func_80611A44();
        func_80714CC0(&D_8071FB34, 0x40000000, ((f32) ((s32) (sp54 >> 0xF) % 30) + sp78) - 15.0f, ((f32) ((s32) (temp_s0 >> 0xF) % 30) + sp74) - 15.0f, ((f32) ((s32) (func_80611A44() >> 0xF) % 30) + sp70) - 15.0f);
        func_80609140(0x1CA, 0x7FFF, 0x427C0000, 0x3F800000, 0, 0);
        temp_v1_2 = ((s32) (func_80611A44() >> 0xF) % 2048) & 0xFFFF;
        if (temp_v1_2 < 0x2A8) {
            sp6C = 0x14E;
        } else if (temp_v1_2 < 0x550) {
            sp6C = 0x14D;
        }
        if (temp_s1->unk1C != 0) {
            n_alSndpStop(temp_s1->unk1C);
        }
        n_alSndpPlay(D_8076D1F8, sp6C, 0x7FFF, 0x3F, 1.0f, 0, (void *)((u8 *)temp_s1 + 0x1C));
    } else if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (func_8067AF44(D_807FBB70.unk1FC) != 0) && (D_807FBB70.unk1FC->unk5C == 1)) {
        func_806D0468(D_807FBB4C, 2);
        func_8002A41C(1);
        func_8063DA40(0, 0xA);
        func_806225C0(D_807F5D10);
        func_8061CC40(D_807FBB40, 8, 1);
        ACTOR->unk154 = 0x37U;
        ACTOR->unk155 = 0U;
        ACTOR->unk60 = (s32) (ACTOR->unk60 & ~4);
    }
    if (!(temp_s1->unk12 & 1) && (func_806614D0(1) > 640.0f) && (((Boss3F_6240_Actor *)D_807FBB4C)->unk154 != 0x42)) {
        if (D_807FC924->unk2C0 != 1) {
            func_806D0468(D_807FBB4C, 1);
            D_807FD580->unk1D8 = 0.1f;
        }
        func_8061CC40(D_807FBB40, 0xA, 1);
        temp_s1->unk14 = 4U;
        temp_s1->unk12 = (u16) (temp_s1->unk12 | 1);
        temp_s1->unk15 = 0U;
        var_v0 = 1;
        if (D_8076A0A8 == 0xC5) {
            var_v0 = 0;
        }
        sp84 = D_80035A20[(var_v0 * 5) + temp_s1->unk14]; ACTOR->unk154 = sp84[temp_s1->unk15];
        temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
        ACTOR->unk155 = 0U;
    }
        switch (ACTOR->unk154) {                              /* switch 1 */
    case 0x6A:                                      /* switch 1 */
block_178:
        break;
    case 0x56:                                      /* switch 1 */
        sp7E = 0;
        ACTOR->unk132 = 4;
        actorMoveWithinZone(0x45, 606.0f, 566.0f, 0x292, 0.0f);
        if (ACTOR->unk155 == 1) {
            func_8002A8B8((s32)((u8 *)D_807FDCA0 + 0x24));
        }
        if ((ACTOR->unk155 == 0) && (((Boss3F_6240_Actor *)D_807FBB4C)->unk154 == 0x42)) {
            ACTOR->unk155 = 1;
            func_8061C464(D_807F5D10, D_807FBB40, 4, 0xD48, 0x320, 0, 0, 0xC8, 0x64, 0, 0.03f);
            func_8061C458(D_807F5D10, D_807FBB4C);
        }
        if (!(D_807FDC90->unk1A & 0x8000)) {
            var_v0_3 = D_807FDC90->unk2C;
            if (var_v0_3 != 0) {
                if (var_v0_3 == 0x64) {
                    func_8002A41C(2);
                    var_v0_3 = D_807FDC90->unk2C;
                }
                if (var_v0_3 < 0x15) {
                    ACTOR->unk60 = (s32) (ACTOR->unk60 | 0x20000000);
                    var_v0_3 = D_807FDC90->unk2C;
                }
                if (var_v0_3 == 0x14) {
                    if (D_807FC924->unk2C0 != 1) {
                        D_807FD580->unkD4 = 0x64;
                    }
                    func_806224CC(D_807F5D10, D_807FBB4C);
                    func_806D0468(D_807FBB4C, 1);
                    D_807FD580->unk1D8 = 0.04f;
                    var_v0_3 = D_807FDC90->unk2C;
                }
                D_807FDC90->unk2C = (s16) (var_v0_3 - 1);
            } else {
                ACTOR->unk60 = (s32) (ACTOR->unk60 & 0xDFFFFFFF);
                func_8066E9EC(D_807FBB40, 1, 0x42800000);
                func_8002A41C(1);
                temp_s1->unk15 = temp_s1->unk16;
                ACTOR->unk154 = sp84[temp_s1->unk15++];
                ACTOR->unk155 = 0;
            }
            goto block_178;
        }
        break;
    case 0x37:                                      /* switch 1 */
        sp7F = 0;
        sp7E = 0;
        ACTOR->unk132 = 4;
        func_8002A8B8((s32)((u8 *)D_807FDCA0 + 0x24));
        if ((ACTOR->unk155 == 0) && (func_80629148() != 0)) {
            ACTOR->unk155 = (u8) (ACTOR->unk155 + 1);
            temp_v0_2 = D_807FDCA0->unk14;
            func_80028478(0xEC, temp_v0_2->unkA0, (s16) (temp_v0_2->unkA2 + 0x14), temp_v0_2->unkA4, 0x5DC, 4);
        }
        goto block_178;
    case 0x27:                                      /* switch 1 */
        sp7E = 0;
        switch (ACTOR->unk155) {                          /* switch 2 */
        case 0:                                     /* switch 2 */
            if (D_8076A0A8 != 0xC5) {
                if (flagGet(0x69, 2) != 0) {
                    goto block_71;
                }
                func_80613C48(D_807FBB40, 0x539, 0, 0);
                func_80614D00(D_807FBB40, 0, 0);
                ACTOR->unk155 = 1U;
            } else {
block_71:
                if (D_8076A0A8 == 0xC5) {
                    ACTOR->unk60 = (s32) (ACTOR->unk60 & ~4);
                } else {
                    func_80614EBC(ACTOR, 0x2C6);
                }
                ACTOR->unk155 = 6U;
            }
            break;
        case 1:                                     /* switch 2 */
            if (func_80629148() != 0) {
                func_80614EBC(D_807FBB40, 0x2C4);
                func_80614D00(D_807FBB40, 0x3F000000, 0);
                ACTOR->unk155 = 2U;
            }
            break;
        case 3:                                     /* switch 2 */
            if (func_80629148() != 0) {
                D_807FDC90->unkC = 0x1F4;
                func_80614EBC(D_807FBB40, 0x2C5);
                ACTOR->unk155 = 4U;
            }
            break;
        case 5:                                     /* switch 2 */
            var_fv1 = ACTOR->unkA4;
            var_fv0 = ACTOR->unk80;
            if ((var_fv1 + 180.0f) < var_fv0) {
                ACTOR->unk154 = 0x11;
                ACTOR->unk155 = 0U;
                var_fv0 = ACTOR->unk80;
                var_fv1 = ACTOR->unkA4;
            }
            ACTOR->unk80 = (f32) ((f64) var_fv0 + ((f64) ((var_fv1 + 200.0f) - var_fv0) * 0.12));
            break;
        case 6:                                     /* switch 2 */
            if (func_80629148() != 0) {
                ACTOR->unk154 = (u8) *(temp_s1->unk15 + sp84);
                temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                ACTOR->unk155 = 0U;
            }
            break;
        }
        goto block_178;
    case 0x2B:                                      /* switch 1 */
        ACTOR->unk132 = 2;
        switch (ACTOR->unk155) {                        /* switch 3; irregular */
        case 0:                                     /* switch 3 */
            func_80614EBC(D_807FBB40, 0x2CF);
            ACTOR->unk155 = 1U;
            break;
        case 2:                                     /* switch 3 */
            if (func_80629148() != 0) {
                func_8063DA40(0, 1);
                ACTOR->unk154 = (u8) *(temp_s1->unk15 + sp84);
                temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                ACTOR->unk155 = 0U;
            }
            break;
        }
        goto block_178;
    case 0x29:                                      /* switch 1 */
        ACTOR->unk132 = 2;
        switch (ACTOR->unk155) {                        /* switch 4; irregular */
        case 0:                                     /* switch 4 */
            func_80614EBC(D_807FBB40, 0x2CE);
            ACTOR->unk155 = 1U;
            break;
        case 2:                                     /* switch 4 */
            func_806086CC(ACTOR->unk7C, ACTOR->unk80, ACTOR->unk84, 0x14A, 0xFF, 0x7F, 0, 0, 0, 0);
            func_806086CC(ACTOR->unk7C, ACTOR->unk80, ACTOR->unk84, 0x221, 0xFF, 0x7F, 0, 0, 0, 0);
            func_80691830(0xBB, 0x3E0F5C29, 0xFF, 0x96, 0x64, 6, 1.04f, 40.0f, 8.0f, 600.0f);
            func_80613C48(D_807FBB44, 0x4F9, 0, 0);
            func_80614D00(D_807FBB44, 0x3F000000, 0);
            ACTOR->unk154 = (u8) *(temp_s1->unk15 + sp84);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            ACTOR->unk155 = 0U;
            break;
        }
        goto block_178;
    case 0x28:                                      /* switch 1 */
        actorTurnTowardTarget(0x23, 606.0f, 566.0f, 0);
        switch (ACTOR->unk155) {                          /* switch 5 */
        case 0:                                     /* switch 5 */
            D_807FDC90->unk25 = (u8) (D_807FDC90->unk25 + 4);
            func_8072D13C(0x42, 0);
            D_807FDC90->unk25 = (u8) (D_807FDC90->unk25 - 4);
            func_80614EBC(D_807FBB40, 0x2CB);
            ACTOR->unk155 = 1U;
            D_807FDC90->unk2C = 0;
            break;
        case 2:                                     /* switch 5 */
            func_80686F90(2, (s16) ((((s32) (func_80611A44() >> 0xF) % 2048) + ACTOR->unkE6) - 0x400), (s16) ((s32) (func_80611A44() >> 0xF) % 2048));
            /* fallthrough */
        case 3:                                     /* switch 5 */
            func_8002A5CC();
            break;
        case 5:                                     /* switch 5 */
            func_80690814(D_807FBB40, 1);
            if (D_807FDC90->unk2C != 0) {
                func_80690A28(0x51, 1, (f32) (((f64) ((s32) (func_80611A44() >> 0xF) % 10) / 20.0) + 0.8), (f32) D_807FDC90->unkA, (f32) D_807FDC90->unkC, (f32) D_807FDC90->unkE, 500.0f, D_807FBB40);
            } else {
                func_80690A28(0x1E, 0x14, 0.2f, (f32) D_807FDC90->unkA, (f32) D_807FDC90->unkC, (f32) D_807FDC90->unkE, 500.0f, D_807FBB40);
            }
            D_807FDC90->unk2C = 1;
            break;
        case 7:                                     /* switch 5 */
            ACTOR->unk154 = (u8) *(temp_s1->unk15 + sp84);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            ACTOR->unk155 = 0U;
            break;
        }
        goto block_178;
    case 0x2A:                                      /* switch 1 */
    case 0x2C:                                      /* switch 1 */
        sp7E = 0;
        ACTOR->unk132 = 2;
        switch (ACTOR->unk155) {                        /* switch 6; irregular */
        case 0:                                     /* switch 6 */
            D_807FDC90->unk25 = (u8) (D_807FDC90->unk25 + 4);
            ACTOR->unk155 = 1U;
            /* fallthrough */
        case 1:                                     /* switch 6 */
            actorMoveWithinZone(0x42, (f32) D_807FDC90->unkA, (f32) D_807FDC90->unkE, 0x291, 0.0f);
            if (func_8072D13C(0x42, 0) != 0) {
                ACTOR->unkC0 = 100.0f;
                func_80614EBC(D_807FBB40, 0x2C8);
                ACTOR->unk155 = 2U;
                D_807FDC90->unk25 = (u8) (D_807FDC90->unk25 - 4);
                if (ACTOR->unk154 == 0x2C) {
                    func_8061CC40(D_807FBB40, 6, 1);
                }
            }
            break;
        case 2:                                     /* switch 6 */
            actorMoveWithinZone(0x45, 606.0f, 566.0f, 0x292, 0.0f);
            break;
        case 3:                                     /* switch 6 */
            ACTOR->unk154 = (u8) *(temp_s1->unk15 + sp84);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            ACTOR->unk155 = 0U;
            break;
        }
        goto block_178;
    case 0x48:                                      /* switch 1 */
        ACTOR->unk132 = 2;
        switch (ACTOR->unk155) {                        /* switch 7; irregular */
        case 0:                                     /* switch 7 */
            func_80614EBC(D_807FBB40, 0x2C9);
            D_807FDC90->unk2C = (s16) *(temp_s1->unk15 + sp84);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            ACTOR->unk155 = 1U;
            /* fallthrough */
        case 1:                                     /* switch 7 */
            if (D_807FDC90->unk2C != 0) { D_807FDC90->unk2C--;
            } else {
                ACTOR->unk154 = (u8) *(temp_s1->unk15 + sp84);
                temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                ACTOR->unk155 = 0U;
            }
            break;
        }
        goto block_178;
    case 0x43:                                      /* switch 1 */
        ACTOR->unk132 = 2;
                switch (ACTOR->unk155) {                        /* switch 8; irregular */
        case 0:                                     /* switch 8 */
            func_80614EBC(ACTOR, 0x2CA);
            ACTOR->unk155 = 1U;
            break;
        case 2:                                     /* switch 8 */
            var_fv1 = ACTOR->unkA4;
            var_fv0 = ACTOR->unk80;
            if ((var_fv1 + 180.0f) < var_fv0) {
                actorSetTargetSpeed(ACTOR, D_807FDC9C->unkC);
                ACTOR->unk154 = (u8) *(temp_s1->unk15 + sp84);
                temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                ACTOR->unk155 = 0U;
                var_fv0 = ACTOR->unk80;
                var_fv1 = ACTOR->unkA4;
            }
            ACTOR->unk80 = (f32) ((f64) var_fv0 + ((f64) ((var_fv1 + 200.0f) - var_fv0) * 0.12));
            sp7E = 0;
            break;
        }
        goto block_178;
    case 0x11:                                      /* switch 1 */
        actorMoveWithinZone(0x45, D_807FDC94->unk7C, D_807FDC94->unk84, 0x293, 0.0f);
        if (func_80629148() != 0) {
            ACTOR->unk154 = (u8) *(temp_s1->unk15 + sp84);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            ACTOR->unk155 = 0U;
        }
        goto block_178;
    case 0x46:                                      /* switch 1 */
        actorMoveWithinZone(0x45, D_807FDC94->unk7C, D_807FDC94->unk84, 0x293, 0.0f);
                switch (ACTOR->unk155) {                        /* switch 9 */
        case 0:                                     /* switch 9 */
            temp_s1->unk18 = sp84[temp_s1->unk15++];
            sp88->unk6 = (s16) (func_80665DE0(606.0f, 566.0f, ACTOR->unk7C, ACTOR->unk84) + 0x400);
            ACTOR->unk155 = 1U;
            /* fallthrough */
        case 1:                                     /* switch 9 */
            func_80614EBC(ACTOR, 0x2C7);
            ACTOR->unk155 = 2U;
            break;
        case 2:                                     /* switch 9 */
            func_8002A55C(0, (f32) (((f64) ACTOR->unk4->unk0->unk4 * 0.06) + 2.0));
            break;
        case 3:                                     /* switch 9 */
            func_80690814(ACTOR, 1);
            func_80690AB0(ACTOR->unkE6, 0x320, 0x1E, 0xB, 1.2f, D_807FDC94->unk7C, D_807FDC94->unk80 + 30.0f, D_807FDC94->unk84, (f32) ((temp_s1->unk14 * 0x50) + 0x2BC), D_807FBB40);
            ACTOR->unk155 = 4U;
            break;
        case 5:                                     /* switch 9 */
            if (temp_s1->unk18-- != 0) {
                ACTOR->unk155 = 1U;
            } else {
                ACTOR->unk154 = (u8) *(temp_s1->unk15 + sp84);
                temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                ACTOR->unk155 = 0U;
            }
            break;
        }
        func_8002A240();
        goto block_178;
    case 0x4D:                                      /* switch 1 */
        sp7E = 0;
        switch (ACTOR->unk155) {                        /* switch 10 */
        case 1:                                     /* switch 10 */
            func_8002A55C(3, 3.0f);
            break;
        case 2:                                     /* switch 10 */
            sp7F = 0;
            actorApplyGravity();
            ACTOR->unk80 = (f32) (ACTOR->unk80 + ACTOR->unkC0);
            if (ACTOR->unk80 < (f32) D_807FDC90->unkC) {
                ACTOR->unk155 = 3U;
                func_806086CC(ACTOR->unk7C, ACTOR->unk80, ACTOR->unk84, 0xC, 0xFF, 0x50, 0, 0, 0, 0);
            }
            if ((D_8076A0A8 == 0xC5) && (temp_s1->unk14 == 3) && (func_80629148() != 0)) {
                temp_v0_2 = D_807FDCA0->unk14;
                func_80028478(0x4A, temp_v0_2->unkA0, (s16) (temp_v0_2->unkA2 + 0x14), temp_v0_2->unkA4, 0x5DC, 4);
            }
            break;
        case 3:                                     /* switch 10 */
            sp7F = 0;
            if (func_80629148() != 0) {
                if ((D_8076A0A8 == 0xC5) && (temp_s1->unk14 == 3)) {
                    ACTOR->unk154 = 0x37U;
                    ACTOR->unk155 = 1U;
                } else {
                    ACTOR->unkC4 = (f32) D_807502E8;
                    func_80614EBC(D_807FBB40, 0x2CC);
                    ACTOR->unk155 = 4U;
                    D_807FDC90->unkC = 0xC8;
                }
            }
            break;
        case 4:                                     /* switch 10 */
            func_806871DC(0);
            sp7F = 0;
            var_fv0 = ACTOR->unk80;
            ACTOR->unk80 = (f32) (((f64) ((f32) (D_807FDC90->unkC + 5) - var_fv0) * 0.12) + (f64) var_fv0);
            actorTurnTowardTarget(0x23, D_807FDC94->unk7C, D_807FDC94->unk84, 0);
                        var_v0_3 = D_807FDC90->unkC;
            var_fv0 = ACTOR->unk80;
            if ((f32) (var_v0_3 - 0x12C) < var_fv0) {
                if (ACTOR->unk6E == -1) {
                    func_80604CBC(ACTOR, 0x10F, 0, 1, 0, 0xFF, 0.8f, 0);
                }
                func_80613C48(ACTOR, 0x53D, 0, 0x41C00000);
                var_v0_3 = D_807FDC90->unkC;
                var_fv0 = ACTOR->unk80;
            }
            if ((f32) var_v0_3 < var_fv0) {
                func_80614EBC(ACTOR, 0x2D0);
                ACTOR->unk155 = 5U;
            }
            break;
        case 5:                                     /* switch 10 */
            func_806871DC(0);
            break;
        case 6:                                     /* switch 10 */
            func_806871DC(1);
            break;
        case 7:                                     /* switch 10 */
            actorSetTargetSpeed(ACTOR, D_807FDC9C->unkC);
            ACTOR->unk154 = 0x11U;
            ACTOR->unk155 = 0U;
            break;
        }
        goto block_178;
    case 0x42:                                      /* switch 1 */
        ACTOR->unk144 = 1;
        if (ACTOR->unk4->unk64 != 0x2C6) {
            func_80614EBC(D_807FBB40, 0x2C6);
        }
        /* fallthrough */
    default:                                        /* switch 1 */
        func_80027BA8(sp84, 0x291, 0);
        goto block_178;
    }
    if (sp7E != 0) {
        f32 var_fv0 = (f32) D_807FDC90->unkC;
        if (ACTOR->unk80 < var_fv0) {
            ACTOR->unk80 = (f32) (((f64) (var_fv0 - sp80) * 0.03) + (f64) sp80);
            ACTOR->unkC0 = 0.0f;
        } else {
            actorApplyGravity();
            if ((f32) D_807FDC90->unkC < ACTOR->unk80) {
                func_806653C0(D_807FBB40, 0, ACTOR->unkC0);
            }
        }
    }
    func_8072881C(0, D_807FDC90 + 0x28);
    if (sp7F != 0) {
        func_80671C0C(D_807FBB40, ACTOR->unkCC, &sp68, &sp64, &sp60);
        func_8066635C(D_807FBB40, sp68, sp64, sp60, D_807FBB40 + 0xA4);
        func_8072A450();
    }
    if (func_8061CB50() != 0) {
        ACTOR->unk144 = 1;
    }
    func_806319C4(D_807FBB40, 0);
}
