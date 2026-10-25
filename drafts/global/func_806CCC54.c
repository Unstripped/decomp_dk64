// func_806CCC54 (src/global/CEAE0.c): Stage 3 (structure/opcode stream identical, frame -88 vs target -80, a1/a3 swap ang<->&D_807FD586 addr, default-tail s16 m copy). Closest: nd=68 diff lines of 593 after dead 'if (!sub) {}' x2 (raises sub priority so sub gets a2). Tried: locals reorder (fa1,fv1,sp44,sp40,speed,sp38,ang,sub order fixes slot layout), ret/pad/absd/diff removal, pad arrays, compound vs expanded +=, permuter 900s (no gain; frame offset noise).
typedef struct LCEAE0aPad {
    /* 0x00 */ u8 pad0[0x2A];
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ s8 unk2E;
    /* 0x2F */ s8 unk2F;
    /* 0x30 */ u8 pad30[4];
} LCEAE0aPad;

extern LCEAE0aPad D_807FD610[];

typedef struct LCEAE0aSub174 {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
} LCEAE0aSub174;

typedef struct LCEAE0aP88 {
    /* 0x000 */ u8 pad0[0x174];
    /* 0x174 */ LCEAE0aSub174 *unk174;
} LCEAE0aP88;

typedef struct LCEAE0aPlayer {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[0x24];
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0x4C];
    /* 0x88 */ LCEAE0aP88 *unk88;
    /* 0x8C */ u8 pad8C[0x36];
    /* 0xC2 */ s16 unkC2;
    /* 0xC4 */ u8 padC4[0x14];
    /* 0xD8 */ u8 unkD8;
} LCEAE0aPlayer;

typedef struct LCEAE0aActor {
    /* 0x00 */ u8 pad0[0x6A];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 pad6C[0x48];
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x20];
    /* 0xDC */ s16 unkDC;
    /* 0xDE */ u8 padDE[2];
    /* 0xE0 */ f32 unkE0;
    /* 0xE4 */ u8 padE4[0xA];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[0xC];
    /* 0xFC */ u8 unkFC;
    /* 0xFD */ u8 padFD[0x57];
    /* 0x154 */ u8 unk154;
} LCEAE0aActor;

#define LA_A ((LCEAE0aActor *)D_807FBB40)
#define LA_P ((LCEAE0aPlayer *)D_807FD580)

f32 func_80611BB4(f32, f32);

void func_806CCC54(arg0) u8 arg0; {
    f32 fa1;
    f32 fv1;
    f32 sp44;
    f32 sp40;
    f32 speed;
    f32 sp38;
    s16 ang;
    LCEAE0aSub174 *sub;
    s32 rem;
    s16 m;

    switch (LA_A->unk154) {
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
            speed = LA_A->unkB8;
            ang = LA_A->unkEE;
            sub = LA_P->unk88->unk174;
            if (!sub) {
            }
            if (!sub) {
            }
            LA_P->unkD8 = LA_A->unkFC;
            D_807FD586 = 0;
            sp38 = func_80612794((s16)(s32)(LA_A->unkE0 * 11.4)) * 10.0;
            fa1 = D_807FD610[D_807FC929].unk2F;
            if (fa1 < 0.0f) {
                fa1 = fa1 * (LA_A->unkB8 / 1600.0);
                if (LA_A->unkB8 < 210.0f) {
                    fa1 = 0.0f;
                }
            } else {
                fa1 = fa1 / 10.0;
            }
            rem = (ang - LA_A->unkDC > 0 ? ang - LA_A->unkDC : -(ang - LA_A->unkDC)) % 4096;
            m = rem;
            if ((m >= 0x401 && m < 0xC00) || !(LA_A->unk6A & 0x200)) {
                fa1 = 0.0f;
            }
            fv1 = -D_807FD610[D_807FC929].unk2E / 5.5;
            if (LA_A->unkB8 < 50.0f) {
                fv1 = fv1 * 0.21739130434782608;
            } else if (LA_A->unkB8 < 230.0f) {
                fv1 = (LA_A->unkB8 * fv1) / 230.0;
            }
            if (sub->unk14 < sub->unk18) {
                fa1 = 0.0f;
            }
            sp44 = func_80612794(ang) * speed;
            sp40 = func_80612790(ang) * speed;
            if (LA_A->unk6A & 1) {
                sp44 += func_80612794(LA_A->unkDC) * sp38;
                sp40 += func_80612790(LA_A->unkDC) * sp38;
                sp44 += func_80612794(LA_A->unkEE) * fa1;
                sp40 += func_80612790(LA_A->unkEE) * fa1;
                sp44 += func_80612790(LA_A->unkEE) * fv1;
                sp40 -= func_80612794(LA_A->unkEE) * fv1;
            } else if ((LA_A->unkB4 > 30.0f || sp38 == 0.0f || m < 0x400 || m >= 0xC01) &&
                       sub->unk18 == sub->unk14) {
                sp44 = sp44 + (func_80612794(LA_P->unkA) * LA_P->unk4) / 40.0;
                sp40 = sp40 + (func_80612790(LA_P->unkA) * LA_P->unk4) / 40.0;
            }
            speed = sqrtf(sp44 * sp44 + sp40 * sp40);
            if (!(LA_A->unk6A & 0x1000) && 700.0f < speed) {
                speed = 700.0f;
            }
            fv1 = func_80611BB4(sp44, sp40);
            if (arg0 != 0) {
                LA_A->unkB8 = speed;
                LA_A->unkEE = (s32)((fv1 * 4096.0) / 6.2831855f);
                if (LA_A->unk6A & 1) {
                    if (!(LA_A->unk6A & 0x200)) {
                        LA_P->unk30 = 20.0f;
                    } else {
                        LA_P->unk30 = (LA_A->unkB8 * LA_A->unkB8) / 35000.0;
                    }
                    func_806CD8EC();
                    return;
                }
            }
            return;
        default:
            if (LA_P->unkC2 >= 0x15) {
                sp38 = LA_A->unkE0;
            } else {
                sp38 = 0.0f;
            }
            if (sp38 != 0.0f && LA_P->unkC2 >= 0x15 && (LA_A->unk6A & 1)) {
                speed = LA_A->unkB8;
                ang = LA_A->unkEE;
            } else {
                speed = LA_P->unk4;
                ang = LA_P->unkA;
            }
            if (D_807FD586 == 0 && LA_P->unkD8 != 0 && LA_A->unkFC == 0) {
                LA_A->unkEE = ang;
            }
            LA_P->unkD8 = LA_A->unkFC;
            D_807FD586 = 0;
            fa1 = func_80612794(ang) * speed;
            sp44 = fa1 + func_80612794(LA_A->unkDC) * sp38;
            fa1 = func_80612790(ang) * speed;
            sp40 = fa1 + func_80612790(LA_A->unkDC) * sp38;
            speed = sqrtf(sp44 * sp44 + sp40 * sp40);
            rem = (s32)((func_80611BB4(sp44, sp40) * 4096.0) / 6.2831855f);
            m = rem;
            if (arg0 != 0) {
                if (speed != 0.0f) {
                    func_806CD424(m, speed, LA_P->unk38);
                } else {
                    func_806CD8EC();
                }
            }
            break;
    }
}
