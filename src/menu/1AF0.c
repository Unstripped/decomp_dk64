#include "common.h"
s32 flagGet(s16, s32);

typedef struct {
    char pad0[4];
    s16 unk4;
    char pad6[4];
    u8 unkA;
    s8 unkB;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    u8 unk11;
    u8 unk12;
} Struct_80025D14;

extern u8 D_807FC950[][0x5E];
extern u8 D_8074E77C;

s32 menuCheckBitgridOtherSlots(Struct_80025D14 *arg0, s32 arg1) {
    s32 found = 0;
    s32 i;

    for (i = 0; found == 0 && i != 5; i++) {
        if (i != D_8074E77C) {
            found |= D_807FC950[i][arg0->unkB] & (1 << (arg1 + 0x1F));
        }
    }
    return found;
}

#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/D_80033A50.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/D_80033A78.s")

typedef struct {
    char pad0[0x15F];
    u8 unk15F;
    char pad160[0x178 - 0x160];
    Struct_80025D14 *unk178;
} MenuShopPromptActor;
extern Gfx D_1000118[];
extern Mtx D_20000C0;
Gfx *textDrawStringVtx();
char *func_8070E750(s32, s32, s32);
s32 _sprintf(char *, const char *, ...);

Gfx *func_80025B64(Gfx *dl, MenuShopPromptActor *arg1) {
    Struct_80025D14 *st = arg1->unk178;
    char buf[0x28];

    if (st->unkD == 1) {
        gSPDisplayList(dl++, D_1000118);
        gSPMatrix(dl++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gDPPipeSync(dl++);
        gDPSetCombineLERP(dl++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0);
        switch (st->unkE) {
        case 1:
            arg1->unk15F = 0;
            st->unkE = 5;
        case 5: {
            s32 diff = 0xFF - arg1->unk15F;
            s32 step;

            arg1->unk15F += diff >= 9 ? 8 : diff;
            gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, arg1->unk15F);
            _sprintf(buf, "q %s", func_8070E750(0x24, 0x10, 1));
            dl = textDrawStringVtx(dl, 1, 0x1F4, 0x190, buf, 1);
            _sprintf(buf, "b %s", func_8070E750(0x24, 0x11, 1));
            dl = textDrawStringVtx(dl, 1, 0x1F4, 0x1F4, buf, 1);
            break;
        }
        }
    }
    return dl;
}


typedef struct {
    char pad0[0x58];
    s32 unk58;
    char pad5C[4];
    s32 unk60;
    char pad64[0x178 - 0x64];
    Struct_80025D14 *unk178;
} Struct_BB40_58;
extern Struct_BB40_58 *D_807FBB40;

extern u8 D_807FC950[][0x5E];

void menuSetBitgridValue(Struct_80025D14 *arg0, s32 arg1) {
    D_807FC950[arg1][arg0->unkB] = arg0->unk11;
}

void menuSetBitgridBit(Struct_80025D14 *arg0, s32 arg1) {
    u8 *ptr = &D_807FC950[arg1][arg0->unkB];
    *ptr |= 1 << (arg0->unk11 - 1);
}

void menuUpdateAllBitgridSlots(Struct_80025D14 *arg0, u8 arg1) {
    s32 i = 0;

    do {
        if (arg1) {
            menuSetBitgridBit(arg0, i);
        } else {
            menuSetBitgridValue(arg0, i);
        }
        i++;
    } while (i < 5);
}

typedef struct {
    char pad0[0x2E2];
    u16 unk2E2;
} MenuM1_C924;
extern MenuM1_C924 *D_807FC924;
extern u8 D_800334DC[];
u8 func_806F6E58(u8);
void slotQueueAddValue(s32, s32, s16);
void healthRefill(s32);
void func_8060DEC8(void);

void menuApplyPurchase(Struct_80025D14 *arg0, s32 arg1) {
    s16 sp1E = -1;
    u8 sp1D = func_806F6E58(D_8074E77C);

    switch (arg0->unkB) {
    case 2:
    case 4:
        if (arg0->unk11 >= 2) {
            menuUpdateAllBitgridSlots(arg0, 1);
        } else {
            menuSetBitgridBit(arg0, D_8074E77C);
        }
        break;
    case 1:
    case 3:
        menuUpdateAllBitgridSlots(arg0, 0);
        break;
    default:
        menuSetBitgridValue(arg0, D_8074E77C);
        break;
    }
    if (arg0->unkB == 4) {
        u8 v = D_800334DC[arg0->unk11];
        if (D_807FC950[8][0xC] < v) {
            D_807FC950[8][0xC] = v;
            healthRefill(0);
            D_807FC924->unk2E2 |= 0x11;
        }
    }
    switch (arg0->unkB) {
    case 2:
    case 3:
        sp1E = 2;
        break;
    case 4:
        sp1E = 7;
        break;
    case 0:
        if (sp1D == 0 && func_806F6E58(D_8074E77C) != 0) {
            sp1E = 5;
        }
        break;
    }
    slotQueueAddValue(1, 0, -arg0->unk4);
    if (sp1E >= 0) {
        slotQueueAddValue(sp1E, 0, 0x270F);
    }
    func_8060DEC8();
}


extern u16 D_80750AC8;
extern u8 D_807FCC4C;

typedef struct {
    char pad0[4];
    s16 unk4;
    char pad6[5];
    s8 unkB;
    u8 unkC;
    char padD[3];
    u8 unk10;
    s8 unk11;
} MenuM1_State;
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} MenuM1_Entry;
extern MenuM1_Entry D_80033260[][7];
extern MenuM1_Entry D_80033334[][7];
extern MenuM1_Entry D_80033408[][7];
extern u8 D_8076A0AB;
s32 func_805FF030(s32, s32);

#define M1S ((MenuM1_State *)arg0)
#define M1A ((u8 *)arg1)
void func_80025FB4(void *arg0, void *arg1, s32 arg2) {
    MenuM1_Entry *tbl;
    MenuM1_Entry *e;
    s32 found = 0;
    s32 count = 6;
    s32 i;

    if (flagGet(0x1CB, 0) == 0) {
        do {
            count--;
            if (count < 0) {
                break;
            }
        } while (flagGet(count + 0x1C5, 0) == 0);
    }
    count++;
    M1S->unkC = func_805FF030(D_8076A0AB, 0);
    switch (D_807FBB40->unk58) {
    case 0xBD:
        tbl = D_80033260[0];
        break;
    case 0xBF:
        tbl = D_80033334[0];
        break;
    case 0xBE:
        tbl = D_80033408[0];
        break;
    }
    tbl += D_8074E77C * 7;
    for (i = 0; i < count && found == 0; i++) {
        if (tbl[i].unk0 >= 0) {
            switch (tbl[i].unk0) {
            case 2:
            case 4:
                if (!(M1A[tbl[i].unk0] & (1 << (tbl[i].unk2 + 0x1F)))) {
                    found = 1;
                }
                break;
            default:
                if (M1A[tbl[i].unk0] < tbl[i].unk2) {
                    found = 1;
                }
                break;
            }
            if (found != 0) {
                M1S->unkB = tbl[i].unk0;
                D_80750AC8 = (M1S->unk4 = tbl[i].unk4);
                M1S->unk11 = tbl[i].unk2;
            }
        }
    }
    if (found == 0) {
        M1S->unk4 = 0;
        M1S->unkB = -1;
        D_80750AC8 = M1S->unk4;
        if (count >= 7) {
            M1S->unkB = -2;
        }
    }
    M1S->unk10 = D_807FCC4C;
}

s32 slotQueueGetValue(s32, s32);

s32 menuGetOptionAvailability(Struct_80025D14 *arg0, s32 arg1) {
    s32 ret = 0;

    arg0->unkF = 3;
    if (arg0->unkB >= 0) {
        s32 val = slotQueueGetValue(1, 0);
        ret = 2;
        if (val >= arg0->unk4) {
            arg0->unkF = 1;
        } else {
            ret = 3;
        }
    } else if (arg0->unkB == -2) {
        ret = 1;
    }

    if (arg0->unkA != 0) {
        ret += 4;
    }

    return ret;
}

s32 func_80026250(Struct_80025D14 *arg0) {
    s32 ret = D_807FBB40->unk58 == 0xBD;

    if (ret != 0) {
        ret = arg0->unkA == 0;
        if (ret != 0) {
            return arg0->unkB < 0;
        }
    }
}

void menuResetSubmenuState(Struct_80025D14 *arg0, s32 *arg1) {
    *arg1 = 0;
    arg0->unkF = 1;
    arg0->unkB = -1;
}

extern u16 D_800334EC[];
extern u16 D_80033500[];
extern u16 D_80033514[];
extern u16 D_80033528[];
extern u8 D_800334DD[];
void currentActorClearFlag(void);
s32 currentActorTestClearFlag();
s32 flagSet(s16, s32, s32);
s32 flagCountRange(s16, s32, s32);
void func_8070D8C0(void *, u16, u8);
void slotQueueInit(s32);
void slotQueueUpdate(s32, s32, s32);
typedef struct {
    u8 hi;
    u8 lo;
} MenuM1_Pair;
#define M1_ARG1 ((u8 *)arg1)
#define M1_UNK12(p) (*((u8 *)(p) + 0x12))

void func_800262A8(Struct_80025D14 *arg0, void *arg1, s32 arg2) {
    MenuM1_Pair *sp44;
    u16 sp42;
    s32 sp3C;
    u16 a;
    u16 b;
    u16 c;
    u16 d;
    s32 avail;
    u16 v;
    u16 sp2C;
    s32 cnt;
    s16 f;

    if (currentActorTestClearFlag() != 0) {
        sp44 = NULL;
        sp3C = menuGetOptionAvailability(arg0, arg2);
        currentActorClearFlag();
        M1_UNK12(arg0) = 0;
        arg0->unkE++;
        switch (D_807FBB40->unk58) {
        case 0xBF:
            a = 3;
            b = 7;
            c = 0xC;
            d = 0xE;
            if (arg0->unkB >= 0) {
                avail = menuCheckBitgridOtherSlots(arg0, 1);
                if (M1_ARG1[arg0->unkB] & 1) {
                    b = 9;
                    if (D_807FCC4C < D_800334DD[M1_ARG1[arg0->unkB]]) {
                        a = 6;
                        c = 0xD;
                        d = 0xF;
                        M1_UNK12(arg0) = 1;
                    } else {
                        a = 5;
                        b = 8;
                    }
                } else if (avail == 0) {
                    a = 4;
                }
            }
            D_80033500[2] = a;
            D_80033500[3] = b;
            D_80033500[6] = c;
            D_80033500[7] = d;
            sp44 = (MenuM1_Pair *)D_80033500;
            sp42 = 9;
            break;
        case 0xBD:
            v = 0;
            arg2 = 0;
            sp2C = D_80750AC8;
            sp3C = menuGetOptionAvailability(arg0, arg2);
            if (sp3C == 0 || sp3C == 1) {
                sp3C = 0;
                sp2C = 0xF;
            }
            sp42 = 8;
            sp44 = (MenuM1_Pair *)D_800334EC;
            if (arg0->unkA == 0) {
                if (flagGet(0x61, 2) != 0) {
                    flagSet(0x61, 0, 2);
                    menuResetSubmenuState(arg0, &sp3C);
                    if (flagGet(0x17B, 0) != 0) {
                        v = 0x20;
                    } else if (flagGet(0x62, 2) != 0) {
                        flagSet(0x62, 0, 2);
                        v = 0x22;
                    } else {
                        v = 0x21;
                    }
                } else {
                    cnt = flagCountRange(0x225, 0x28, 0);
                    if (cnt >= 0xF) {
                        menuResetSubmenuState(arg0, &sp3C);
                        if (flagGet(0x17B, 0) != 0) {
                            v = 0x20;
                        } else {
                            v = 2;
                            sp2C = cnt;
                        }
                    }
                }
            }
            D_80750AC8 = sp2C;
            D_800334EC[0] = v;
            break;
        case 0xBE:
            sp44 = (MenuM1_Pair *)D_80033514;
            if (arg0->unkB == 3) {
                sp44 = (MenuM1_Pair *)D_80033528;
            } else {
                a = 3;
                f = 4;
                if (arg0->unkB >= 0 && (M1_ARG1[arg0->unkB] & 1)) {
                    a = 5;
                    f = 6;
                }
                D_80033514[2] = a;
                D_80033514[3] = f;
            }
            sp42 = 7;
            break;
        }
        if (arg2 != 0) {
            func_8070D8C0(D_807FBB40, sp42, sp44[8].lo);
        }
        func_8070D8C0(D_807FBB40, sp42, sp44[sp3C].lo);
        if (sp3C == 2 || sp3C == 3 || sp3C == 6 || sp3C == 7) {
            slotQueueInit(0);
            slotQueueUpdate(1, 1, 0);
            slotQueueUpdate(0xE, 1, 0);
        }
    }
}

void func_800262A8(Struct_80025D14 *, void *, s32);
void camResumePath(void);

void menuDispatchSubmenuAction(Struct_80025D14 *arg0, void *arg1, s32 arg2) {
    switch (arg0->unkE) {
    case 0:
        func_800262A8(arg0, arg1, arg2);
        break;
    case 1:
        if (!(D_807FBB40->unk60 & 0x02000000)) {
            arg0->unkE = 0;
            arg0->unkD = arg0->unkF;
            camResumePath();
        }
        break;
    }
}


extern void *D_807FBB4C;
void func_806F397C(void *, void *, s32, s32);
void camStartPath(s32, s32, s32);
void func_80025FB4(void *, void *, s32);
s32 playerStateQueueCallback(s32, void *, s32);

s32 menuExitSubmenu(Struct_80025D14 *arg0, void *arg1, s32 arg2) {
    s32 flag = flagGet((s16)arg2, 0) == 0;

    func_80025FB4(arg0, arg1, flag);
    arg0->unkD = 0;
    arg0->unkE = 0;
    if (flagGet(0x61, 2) == 0) {
        if (flag != 0) {
            func_806F397C(D_807FBB4C, D_807FBB40, 0, 0x1B);
            camStartPath(0, 0, 1);
        } else {
            camStartPath(0, 4, 1);
            playerStateQueueCallback(0x1B, D_807FBB40, 0);
        }
    } else {
        playerStateQueueCallback(0x1B, D_807FBB40, 0);
        camStartPath(0, 0xB, 1);
    }
    currentActorClearFlag();
    D_807FBB40->unk60 |= 0x10000000;
    return flag;
}



void menuTransitionToSubmenu(Struct_80025D14 *arg0, void *arg1) {
    arg0->unkA = 1;
    camStartPath(0, 0xF, 1);
    currentActorClearFlag();
    func_80025FB4(arg0, arg1, 0);
    arg0->unkD = 0;
    arg0->unkE = 0;
    playerStateQueueCallback(0x1B, D_807FBB40, 0);
}

typedef struct {
    char pad0[4];
    Struct_BB40_58 *unk4;
} MenuM1b_C924;
#define M1B_C924 ((MenuM1b_C924 *)D_807FC924)
extern s32 D_807FBB60;
s32 slotQueueGetMaxValue(s32, s32);

void renderCallbacksRegister(void *, void *, s32);
void slotQueueCancel(s32, s32);
s32 actorSpawn(s32, s32);
void func_80614E78(void *, s32);

void func_80026874(arg0, arg1)
Struct_80025D14 *arg0;
void *arg1;
{
    s32 sp24;
    s32 sp20;

    switch (arg0->unkE) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            arg0->unkE++;
        }
        break;
    case 1:
    case 5:
        renderCallbacksRegister(func_80025B64, D_807FBB40, 3);
        break;
    case 10:
        if (func_80026250(arg0) == 0) {
            slotQueueCancel(1, 0);
            slotQueueCancel(0xE, 0);
            menuApplyPurchase(arg0, (s32)arg1);
            switch (arg0->unkB) {
            case 0:
            case 1:
                playerStateQueueCallback(0x52, 0, 0);
                D_807FBB60 &= 0xFFFEFFCF;
                M1B_C924->unk4->unk60 |= 0x40000000;
                break;
            case 4:
                actorSpawn(0x144, 0);
                playerStateQueueCallback(0x53, 0, 0);
                break;
            case 2:
            case 3:
                actorSpawn(0x144, 0);
                func_80614E78(M1B_C924->unk4, 0x85);
                break;
            }
            camStartPath((s32)M1B_C924->unk4, 2, 1);
            arg0->unkD = 2;
            arg0->unkE = 0;
        } else {
            camStartPath(0, 0xA, 1);
            flagSet(0x61, 1, 2);
            arg0->unkE++;
        }
        break;
    case 15:
        sp24 = -1;
        switch (D_807FBB40->unk58) {
        case 0xBD:
            sp24 = 8;
            if (func_80026250(arg0) != 0) {
                arg0->unkA = 1;
                menuTransitionToSubmenu(arg0, arg1);
                return;
            }
            sp20 = 0xA;
            goto done;
        case 0xBF:
            sp24 = 9;
            sp20 = 0x11;
            goto done;
        case 0xBE:
            sp24 = 7;
            sp20 = 0x10;
        default:
        done:
            slotQueueCancel(1, 0);
            slotQueueCancel(0xE, 0);
            camStartPath((s32)M1B_C924->unk4, 3, 1);
            arg0->unkD = 3;
            arg0->unkE = 0;
            func_8070D8C0(D_807FBB40, sp24, sp20);
            break;
        }
        break;
    }
}

extern u16 D_80033A50[][4];
extern u16 D_80033A78[];
extern u16 D_800334E4[];

#define M1B_ARG1 ((u8 *)arg1)

void func_80026B28(Struct_80025D14 *arg0, void *arg1, s32 arg2) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;

    switch (arg0->unkE) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            sp24 = -1;
            D_807FBB60 |= 0x10030;
            M1B_C924->unk4->unk60 &= 0xBFFFFFFF;
            sp28 = 0;
            sp2C = -1;
            if (sp2C) {
            }
            currentActorClearFlag();
            switch (arg0->unkB) {
            case 0:
                sp2C = D_80033A50[D_8074E77C][M1B_ARG1[arg0->unkB]];
            case 1:
                if (sp2C == -1) {
                    sp2C = D_80033A78[M1B_ARG1[arg0->unkB]];
                }
                sp28 = 8;
                break;
            case 4:
                if (arg0->unk11 == 1) {
                    if (menuCheckBitgridOtherSlots(arg0, 1) == 0) {
                        sp24 = 0x15;
                    }
                    sp2C = 0x12;
                    sp28 = 9;
                } else {
                    sp2C = 0x13;
                    if (*((u8 *)arg0 + 0x10) + 1 == *(u8 *)&D_807FCC4C) {
                        sp2C = 0x14;
                        sp28 = 9;
                    } else {
                        sp28 = 9;
                    }
                }
                break;
            case 2:
                sp2C = D_800334E4[arg0->unk11];
            case 3:
                if (sp2C == -1) {
                    D_80750AC8 = slotQueueGetMaxValue(2, 0);
                    sp2C = 0x15;
                }
                sp28 = 7;
                break;
            }
            func_8070D8C0(D_807FBB40, sp28, sp2C);
            if (sp24 >= 0) {
                func_8070D8C0(D_807FBB40, sp28, sp24);
            }
            arg0->unkE++;
        }
        break;
    case 1:
        if (!(D_807FBB40->unk60 & 0x02000000)) {
            flagSet(arg2, 1, 0);
            camResumePath();
            arg0->unkE++;
        }
        break;
    case 2:
        if (currentActorTestClearFlag() != 0) {
            menuTransitionToSubmenu(arg0, arg1);
        }
        break;
    }
}

void func_805FF898(void);
void func_806CFF9C(void *);

void func_80026DAC(Struct_80025D14 *arg0, void *arg1, s32 arg2) {
    s32 x;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 v;

    switch (arg0->unkE) {
    case 0:
        if (!(D_807FBB40->unk60 & 0x02000000)) {
            camResumePath();
            arg0->unkE++;
            flagSet(arg2, 1, 0);
        }
        break;
    case 2:
        if (!(D_807FBB40->unk60 & 0x02000000)) {
            x = -1;
            camResumePath();
            arg0->unkE = 4;
            switch (D_807FBB40->unk58) {
            case 0xBE:
                x = 2;
            case 0xBF:
                if (x < 0) {
                    x = 7;
                }
                slotQueueUpdate(x, 0, 0);
                break;
            }
        }
        break;
    case 1:
        if (currentActorTestClearFlag() != 0) {
            sp30 = 1;
            sp24 = -1;
            v = -1;
            currentActorClearFlag();
            func_806CFF9C(D_807FBB4C);
            switch (D_807FBB40->unk58) {
            case 0xBE:
                sp2C = 7;
                sp28 = 0x11;
                sp24 = 2;
                v = 2;
            case 0xBF:
                if (sp24 < 0) {
                    sp2C = 9;
                    sp28 = 0x10;
                    sp24 = 7;
                    v = 4;
                }
                if (v >= 0 && (((u8 *)arg1)[v] & 1)) {
                    if (slotQueueGetValue((u8)sp24, 0) < slotQueueGetMaxValue(sp24, 0)) {
                        func_8070D8C0(D_807FBB40, sp2C, sp28);
                        slotQueueAddValue(sp24, 0, 0x3E7);
                        arg0->unkE = 0;
                        sp30 = 5;
                    }
                }
                break;
            }
            arg0->unkE += 2;
            camStartPath(0, (s16)sp30, 1);
        }
        break;
    case 4:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
    case 3:
            func_805FF898();
            arg0->unkE = 0xA;
        }
        break;
    }
}

void func_80026874();
void func_80026B28(Struct_80025D14 *, void *, s32);
void func_80026DAC(Struct_80025D14 *, void *, s32);

void menuDispatchCurrentMenuAction(Struct_80025D14 *arg0, void *arg1, s32 arg2) {
    s32 flag = flagGet((s16)arg2, 0) == 0;

    switch (arg0->unkD) {
    case 0:
        menuDispatchSubmenuAction(arg0, arg1, flag);
        break;
    case 1:
        func_80026874(arg0, arg1, arg2);
        break;
    case 2:
        func_80026B28(arg0, arg1, arg2);
        break;
    case 3:
        func_80026DAC(arg0, arg1, arg2);
        break;
    }
}

typedef struct {
    char pad0[0x154];
    u8 unk154;
    u8 unk155;
} MenuScriptActor;
#define M3A ((MenuScriptActor *)D_807FBB40)
extern s32 D_8076A0A8;
void behaviourFrameBegin(void);
void func_806BFBF4(void);
void actorUpdateModelMatrix(void *, s32);
void actorScriptStart(void *, s32);

void func_800270E0(void) {
    s32 i;
    s32 n;
    s32 sp2C;
    Struct_80025D14 *st;
    s32 pad;
    u8 *p;
    s32 flag;
    s32 a3;

    behaviourFrameBegin();
    if (D_8076A0A8 == 5) {
        st = D_807FBB40->unk178;
        p = D_807FC950[D_8074E77C];
        if (!(D_807FBB40->unk60 & 0x10)) {
            if (flagGet(0x180, 0) != 0) {
                M3A->unk155 = 0;
            } else {
                M3A->unk155 = 0xFF;
            }
        }
        if (M3A->unk155 != 0xFF) {
            flag = 0x17F;
            if (func_805FF030(D_8076A0AB, 0) != 7) {
                flag = 0x177;
            }
            a3 = 0x26E;
            if (!(D_807FBB40->unk60 & 0x10)) {
                if (menuExitSubmenu(st, p, flag) != 0) {
                    a3 = 0x26F;
                }
                actorScriptStart(D_807FBB40, a3);
            }
            menuDispatchCurrentMenuAction(st, p, flag);
        } else {
            if (!(D_807FBB40->unk60 & 0x10)) {
                *((u8 *)st + 0xC) = 7;
                if (flagGet(0x17F, 0) == 0) {
                    actorScriptStart(D_807FBB40, 0x26E);
                    camStartPath(0, 5, 1);
                    M3A->unk154 = 0;
                    flagSet(0x64, 1, 2);
                } else {
                    n = 0;
                    i = 0;
                    do {
                        n += flagGet(i + 0x182, 0) != 0;
                        i++;
                    } while (i != 4);
                    if (n != 4) {
                        sp2C = 0;
                        M3A->unk154 = 3;
                    } else {
                        sp2C = 6;
                        M3A->unk154 = 4;
                        st->unkB = 1;
                        st->unk4 = 0;
                        st->unk11 = 1;
                        menuApplyPurchase(st, (s32)p);
                        flagSet(0x180, 1, 0);
                    }
                    func_806F397C(D_807FBB4C, D_807FBB40, 0, 0x1B);
                    camStartPath(0, (s16)sp2C, 1);
                    currentActorClearFlag();
                    actorScriptStart(D_807FBB40, 0x26E);
                }
            }
            switch (M3A->unk154) {
            case 0:
                if (currentActorTestClearFlag() != 0) {
                    func_8070D8C0(D_807FBB40, 8, 0x1C);
                    M3A->unk154 = 1;
                }
                break;
            case 1:
                if (!(D_807FBB40->unk60 & 0x02000000)) {
                    func_806CFF9C(D_807FBB4C);
                    currentActorClearFlag();
                    camStartPath(0, 1, 1);
                    func_805FF898();
                    M3A->unk154 = 2;
                }
                break;
            case 3:
                if (currentActorTestClearFlag() != 0) {
                    func_8070D8C0(D_807FBB40, 8, 0x1D);
                    M3A->unk154 = 1;
                }
                break;
            case 4:
                if (currentActorTestClearFlag() != 0) {
                    func_8070D8C0(D_807FBB40, 8, 0x1E);
                    M3A->unk154 = 5;
                }
                break;
            case 5:
                if (!(D_807FBB40->unk60 & 0x02000000)) {
                    camResumePath();
                    M3A->unk154 = 6;
                }
                break;
            case 6:
                if (currentActorTestClearFlag() != 0) {
                    playerStateQueueCallback(0x52, 0, 0);
                    D_807FBB60 &= 0xFFFEFFCF;
                    M1B_C924->unk4->unk60 |= 0x40000000;
                    M3A->unk154 = 7;
                    currentActorClearFlag();
                    camStartPath((s32)M1B_C924->unk4, 2, 1);
                }
                break;
            case 7:
                if (currentActorTestClearFlag() != 0) {
                    D_807FBB60 |= 0x10030;
                    D_80750AC8 = 0xF;
                    func_8070D8C0(D_807FBB40, 8, 0x1F);
                    M3A->unk154 = 1;
                }
                break;
            }
        }
    }
    if (D_807FBB40->unk60 & 0x10000000) {
        behaviourFrameBegin();
        func_806BFBF4();
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

s32 menuDecodeAddressConstant(s32 arg0) {
    return arg0 + 0x21F44F;
}



extern s32 csCmdExec;
void controllerUpdate(void);
void controllerLatchPad(void);

void menuCheckControllerAntiPiracy(void) {
    Struct_80025D14 *temp;
    u8 *ptr;
    s32 pad[4];
    s32 *dest;

    behaviourFrameBegin();
    if (D_8076A0A8 == 0x19) {
        temp = D_807FBB40->unk178;
        ptr = D_807FC950[D_8074E77C];

        if (!(D_807FBB40->unk60 & 0x10)) {

            s32 *cur = (s32 *)controllerUpdate;
            s32 *end = (s32 *)controllerLatchPad;
            s32 sum = 0;

            if ((u32)cur < (u32)end) {
                do {
                    sum += *cur;
                    cur++;
                } while ((u32)cur < (u32)end);
            }

            if (sum != (s32)0xA1C0EB24) {
                dest = (s32 *)menuDecodeAddressConstant((s32)&csCmdExec + 0xFFDE0BB1);
                *dest = menuDecodeAddressConstant(0x03BE0BB9);
            }
            menuExitSubmenu(temp, ptr, 0x175);
        }
        menuDispatchCurrentMenuAction(temp, ptr, 0x175);
    }
    if (D_807FBB40->unk60 & 0x10000000) {
        behaviourFrameBegin();
        func_806BFBF4();
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
void func_80027738(void) {
    behaviourFrameBegin();
    if (D_8076A0A8 == 1) {
        Struct_80025D14 *temp = D_807FBB40->unk178;
        u8 *ptr = D_807FC950[D_8074E77C];

        if (!(D_807FBB40->unk60 & 0x10)) {
            menuExitSubmenu(temp, ptr, 0x176);
        }
        menuDispatchCurrentMenuAction(temp, ptr, 0x176);
    }
    if (D_807FBB40->unk60 & 0x10000000) {
        behaviourFrameBegin();
        func_806BFBF4();
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}


extern Mtx D_2000180;
typedef struct { s16 unk0; s16 unk2; } Struct_8003353C;
extern Struct_8003353C D_8003353C[];

typedef struct {
    s32 unk0[2];
    u8 unk8;
    char pad9[7];
    Mtx unk10[2];
} Struct_174;

Gfx *menuDrawTransformedWidgets(Gfx *dl, void *arg1) {
    Struct_174 *fp = *(Struct_174 **)((u8 *)arg1 + 0x174);
    s32 i;

    gSPDisplayList(dl++, D_1000118);
    gSPMatrix(dl++, &D_2000180, G_MTX_LOAD | G_MTX_PUSH);
    gDPPipeSync(dl++);
    gDPSetCombineLERP(dl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, fp->unk8);

    for (i = 0; i < 2; i++) {
        if (fp->unk0[i] != 0) {
            gSPMatrix(dl++, &fp->unk10[i], G_MTX_LOAD | G_MTX_PUSH);
            dl = textDrawStringVtx(dl, D_8003353C[i].unk2, 0, 0, fp->unk0[i], 0x80);
            gSPPopMatrix(dl++, G_MTX_MODELVIEW);
        }
    }
    return dl;
}


typedef struct {
    s32 unk0[2];
    u8 unk8;
    char pad9[7];
    Mtx unk10[2];
    s32 unk90;
    Struct_BB40_58 *unk94;
} MenuWidgetState;
typedef struct {
    s32 a[2];
} MenuTextIdPair;
extern MenuTextIdPair D_8003365C[];
extern s32 D_80033544[5][4][2];
extern s32 D_800335E4[4][2];
extern s32 D_80033604[];
extern s32 D_80033618[];
extern s32 D_80033628[];
extern s32 D_80033634[];
extern s32 D_80033648[];
extern s16 D_80033542;
Struct_BB40_58 *spawnNodeActivate(s32, s32);
s32 textGetFontHeight(s32);
void actorDespawn(void *);
void renderCallbacksRegister(void *, void *, s32);

void menuUpdateTransformedWidgets(void) {
    MenuWidgetState *fp = *(MenuWidgetState **)((u8 *)D_807FBB40 + 0x174);
    s32 done = 0;
    Struct_80025D14 *st = NULL;
    f32 mA[4][4];
    f32 mB[4][4];
    MenuTextIdPair sp34;
    s32 i;
    s32 cnt;
    s32 d;

    if (fp->unk94 == NULL) {
        fp->unk94 = spawnNodeActivate(1, 0);
    }
    if (fp->unk94 != NULL) {
        st = fp->unk94->unk178;
    }
    if (st != NULL) {
        if (!(D_807FBB40->unk60 & 0x10)) {
            sp34 = D_8003365C[0];
            guScaleF(mA, 0.6f, 0.6f, 1.0f);
            guTranslateF(mB, 640.0f, 800.0f, 0.0f);
            guMtxCatF(mA, mB, mA);
            guMtxF2L(mA, &fp->unk10[0]);
            cnt = textGetFontHeight(D_80033542);
            guTranslateF(mB, 0.0f, (f32)(cnt * 4), 0);
            guMtxCatF(mA, mB, mA);
            guMtxF2L(mA, &fp->unk10[1]);
            if (st->unkB == 0) {
                for (i = 0; i < 2; i++) {
                    sp34.a[i] = D_80033544[D_8074E77C][st->unk11][i];
                }
            } else if (st->unkB == 1) {
                for (i = 0; i < 2; i++) {
                    sp34.a[i] = D_800335E4[st->unk11][i];
                }
            } else if (st->unkB == 2) {
                fp->unk90 = 0x82;
                if (st->unk11 >= 2) {
                    sp34.a[0] = D_80033618[st->unk11];
                } else {
                    sp34.a[0] = D_80033604[D_8074E77C];
                }
            } else if (st->unkB == 3) {
                fp->unk90 = 0x82;
                sp34.a[0] = D_80033628[st->unk11];
            } else if (st->unkB == 4) {
                fp->unk90 = 0x82;
                if (st->unk11 == 1) {
                    sp34.a[0] = D_80033634[D_8074E77C];
                } else if (M1_UNK12(st) == 0) {
                    sp34.a[0] = D_80033648[st->unk11];
                } else {
                    sp34.a[0] = 0x32;
                }
            }
            for (i = 0; i < 2; i++) {
                if (sp34.a[i] >= 0) {
                    fp->unk0[i] = (s32)func_8070E750(0x27, sp34.a[i], 0);
                } else {
                    fp->unk0[i] = 0;
                }
            }
        }
        if (fp->unk90 != 0) {
            fp->unk90--;
            if (fp->unk90 == 0) {
                done = 1;
            }
        }
        switch (fp->unk90) {
        case 0x78:
            M3A->unk154 = 1;
            break;
        case 0x1E:
            M3A->unk154 = 2;
            break;
        }
        switch (M3A->unk154) {
        case 1:
            d = (0xFF - fp->unk8 > 0x10) ? 0x10 : 0xFF - fp->unk8;
            fp->unk8 += d;
            break;
        case 2:
            cnt = (fp->unk8 > 0x10) ? 0x10 : fp->unk8;
            fp->unk8 -= cnt;
            break;
        }
        if (done == 0) {
            if (M3A->unk154 != 0) {
                renderCallbacksRegister(menuDrawTransformedWidgets, D_807FBB40, 3);
            }
            if (D_807FBB40->unk58 == 0x140) {
                actorUpdateModelMatrix(D_807FBB40, 0);
            }
        } else {
            actorDespawn(D_807FBB40);
        }
    }
}

void menuUpdateTransformedWidgets(void);

void func_80027DEC(void) {
    menuUpdateTransformedWidgets();
}
