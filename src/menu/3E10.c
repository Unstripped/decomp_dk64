#include "common.h"

extern s8 D_80745844;
void configureCSPOutputMode(s32);

void menuSetAudioMode(void) {
    s32 val = 1;
    switch (D_80745844) {
    case 0:
        val = 2;
        break;
    case 2:
        val = 4;
        break;
    }
    configureCSPOutputMode(val);
}

typedef struct Menu3A_Struct7E60 {
    f32 unk0;
    char pad[0xE];
    s8 unk12;
    char pad2[3];
    s8 unk16;
} Menu3A_Struct7E60;

s32 func_80030340();
void camEndPath(s32);
void func_80609140(s32, s32, f32, f32, s32, s32);
extern s8 D_80033734;
extern s32 gCamActor;

void func_80027E60(void *arg0, s32 arg1) {
    Menu3A_Struct7E60 *temp_v0 = *(Menu3A_Struct7E60 **)((u8 *)arg0 + 0x174);
    s32 var_v1 = 0;

    if (D_80033734 != 0) {
        D_80033734++;
        if (D_80033734 >= 0xB) {
            var_v1 = 1;
        }
    }
    if (temp_v0->unk0 == 0.0 && (var_v1 != 0 || (arg1 & 1))) {
        temp_v0->unk12 = 1;
        temp_v0->unk16 = -1;
        temp_v0->unk0 = 1.0f;
        func_80030340(arg0, 0, 0, 0);
        camEndPath(gCamActor);
        func_80609140(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
        D_80033734 = 0;
    }
}

s32 func_80027F34(void *arg0, s32 arg1) {
    return arg1;
}

typedef struct Menu3A_Actor {
    char pad[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} Menu3A_Actor;

extern Menu3A_Actor *D_807FBB4C;
extern s8 D_80033734;
extern s32 D_807FBB60;

void menuResetCameraAndFlags(void *arg0, s32 arg1) {
    f32 *temp_v0 = *(f32 **)((u8 *)arg0 + 0x174);
    D_807FBB4C->unk7C = 109.0f;
    D_807FBB4C->unk80 = 6.0f;
    D_807FBB4C->unk84 = 55.0f;
    *temp_v0 = 0.0f;
    D_80033734 = 0;
    D_807FBB60 |= 0x10000;
}

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_80027FAC.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_800286C8.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_80028834.s")

void func_80028C18(void) {
}

typedef struct Menu3R1_Struct174 {
    f32 unk0;
    f32 unk4;
    char pad[0xB];
    s8 unk13;
    char pad2[2];
    s8 unk16;
    s8 unk17;
} Menu3R1_Struct174;

void menuHandleScrollInput();
void menuUpdateScrollAnimation();
void menuUpdateItemTransition(void *, void *, s32);
extern s8 D_80033F48;

void menuHandleSelectionInput(void *arg0, s32 arg1) {
    Menu3R1_Struct174 *temp_s0 = *(Menu3R1_Struct174 **)((u8 *)arg0 + 0x174);
    s32 temp_v0;

    if (temp_s0->unk0 == 0.0f) {
        if (temp_s0->unk4 == 0.0f) {
            if (arg1 & 1) {
                temp_s0->unk16 = 0;
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                switch (temp_s0->unk17) {
                case 2:
                    temp_s0->unk13 = 4;
                    break;
                default:
                    D_80033F48 = temp_s0->unk17;
                    if (D_80033F48 == 3) {
                        D_80033F48 = 2;
                    }
                    temp_s0->unk13 = 3;
                    break;
                }
            } else if (arg1 & 2) {
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                temp_s0->unk16 = 0;
                temp_s0->unk13 = 1;
            } else {
                menuHandleScrollInput(temp_s0, 4, arg1);
            }
        }
        menuUpdateScrollAnimation(temp_s0, 4);
    }
    menuUpdateItemTransition(arg0, temp_s0, 1);
}

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_80028D3C.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_80028EA8.s")


extern u8 D_80033818;
extern u16 D_8003381C[];
extern s8 D_807563B4;
extern u16 D_807ECD48;

#ifdef NON_MATCHING
void func_8002907C(void) {
    u8 temp_t8;

    if (D_8003381C[D_80033818] == D_807ECD48) {
        temp_t8 = D_80033818 + 1;
        D_80033818 = temp_t8;
        if ((u32)(temp_t8 & 0xFF) >= 7U) {
            D_807563B4 = 1;
            func_80609140(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
            D_80033818 = 0;
        }
    } else if (D_807ECD48 != 0) {
        D_80033818 = 0;
    }
}
#else

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002907C.s")
#endif

typedef struct Menu3A_Struct174 {
    f32 unk0;
    f32 unk4;
    char pad[0xB];
    s8 unk13;
    char pad2[2];
    s8 unk16;
    s8 unk17;
} Menu3A_Struct174;

void menuHandleScrollInput();
void menuUpdateScrollAnimation();
void menuUpdateItemTransition(void *, void *, s32);
void menuUpdateCameraPositions(void);
void controllerSetActiveMask(s32);
void func_807144B8(s8);
extern s8 D_80033F48;

void menuHandleConfirmationInput(void *arg0, s32 arg1) {
    Menu3A_Struct174 *temp_s0 = *(Menu3A_Struct174 **)((u8 *)arg0 + 0x174);

    if (temp_s0->unk0 == 0.0f && temp_s0->unk4 == 0.0f) {
        if (arg1 & 1) {
            controllerSetActiveMask(1);
            func_807144B8(D_80033F48);
        } else if (arg1 & 2) {
            func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
            temp_s0->unk16 = 0;
            temp_s0->unk13 = 2;
        }
    }
    menuUpdateItemTransition(arg0, temp_s0, 1);
}

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_800291CC.s")

s32 func_800297A8(s32 arg0) {
    return arg0 + 0x1EFF0;
}

extern u8 D_8072052C;
extern u8 D_80720CF0;
extern u8 D_80720D14;
extern u8 D_807204BC;
extern u8 D_80720C34;
extern u8 D_807211D0;
extern void *D_80750518[];
extern s16 D_807505B2;
extern u32 D_80750AB0;
extern u8 D_807FC950[][0x5E];
extern s8 D_80033804;
extern s8 D_80033805;
extern s32 D_8003380C;
extern s32 D_80033810;
extern u32 D_80033814;
extern f32 D_80033F4C;
extern s8 D_80033F51;
extern u32 D_80671880;
void func_80030894(void *, void *, s32, s32, f32, s32, s32);
void func_8060DC3C(s32, s32);
s32 flagGet(s32, s32);
s32 menuCalculateGamePercentage(void);

#ifdef NON_MATCHING
void func_800297B8(void *arg0, s32 arg1) {
    Menu3A_Struct174 *temp_s6 = *(Menu3A_Struct174 **)((u8 *)arg0 + 0x174);
    u8 *row = D_807FC950[0];
    s8 *p;
    s16 *q;
    s8 *p2;
    void *a1;
    u32 sp64;
    s32 i;
    s32 k;
    s32 j;

    func_80030894(temp_s6, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s6, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s6, &D_8072052C, 0x76, 0x91, 0.6f, 2, 9);
    D_80033F4C = 1600.0f;
    func_8060DC3C((u8)D_80033F48, 0);
    D_80033804 = 1;
    for (i = 0; i < 4; i++) {
        (&D_80033805)[i] = flagGet((&D_807505B2)[i - 1], 0);
    }
    p2 = &D_80033804;
    for (i = 0; i != 5; i++) {
        if (*p2 != 0) {
            a1 = D_80750518[i];
        } else {
            a1 = &D_807211D0;
        }
        func_80030894(temp_s6, a1, i, i, 0.8f, 2, 0xF);
        p2++;
    }
    osPiReadIo(func_800297A8(0xAFFE1464), &sp64);
    if (sp64 != func_800297A8(0x0107183B)) {
        D_80671880 = 0x03E00008;
    }
    D_8003380C = 0;
    for (k = 0; k != 5; k++) {
        for (j = 0; j != 8; j++) {
            D_8003380C += *(u16 *)(row + 0x42 + j * 2);
        }
        row += 0x5E;
    }
    D_80033814 = D_80750AB0 / 60;
    D_80033810 = (s32)D_80033814 / 60;
    D_80033814 = D_80033814 - D_80033810 * 60;
    D_80033F51 = menuCalculateGamePercentage();
}
#else

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_800297B8.s")
#endif

s32 menuCheckSaveFile();

void menuHandleFileSelectInput(void *arg0, s32 arg1) {
    Menu3A_Struct174 *temp_s0 = *(Menu3A_Struct174 **)((u8 *)arg0 + 0x174);

    if (temp_s0->unk0 == 0.0f) {
        if (temp_s0->unk4 == 0.0f) {
            if (arg1 & 1) {
                if (menuCheckSaveFile(temp_s0->unk17) == 0) {
                    temp_s0->unk16 = 0;
                    temp_s0->unk13 = 5;
                    D_80033F48 = temp_s0->unk17;
                } else {
                    func_80609140(0x98, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
            } else if (arg1 & 2) {
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                temp_s0->unk16 = 0;
                temp_s0->unk13 = 2;
            } else {
                menuHandleScrollInput(temp_s0, 3, arg1);
            }
        }
        menuUpdateScrollAnimation(temp_s0, 3);
    }
    menuUpdateItemTransition(arg0, temp_s0, 1);
}

extern s32 *D_80033F28;
int _sprintf(char *, const char *, ...);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, char *);
s32 func_800317E8(void *, f32, f32, f32 *, f32 *, s32, s8, f32);

#ifdef NON_MATCHING
Gfx *func_80029BB4(void *arg0, Gfx *arg1) {
    void *temp_a0 = *(void **)((u8 *)arg0 + 0x174);
    s32 sp120;
    f32 sp118;
    f32 sp114;
    f32 sp110;
    f32 sp10C;
    f32 sp108;
    f32 sp104;
    s16 spFE;
    char sp34[200];
    s32 y;

    arg1->words.w1 = -1;
    arg1->words.w0 = 0xFA000000;
    sp120 = func_800317E8(temp_a0, 160.0f, 25.0f, &sp110, &sp10C, 3, 1, 0.45f);
    arg1 += 1;
    spFE = (s16)(sp110 * 4.0f);
    y = (s32)(sp10C * 4.0f);
    if (menuCheckSaveFile(sp120) != 0) {
        _sprintf(sp34, "%s", (char *)D_80033F28[6]);
    } else {
        _sprintf(sp34, "%s %d", (char *)D_80033F28[7], sp120 + 1);
    }
    return hudDrawScaledText(
        hudDrawScaledText(arg1, spFE, (s16)y, 0.6f, sp34),
        (s16)(sp110 * 4.0f),
        (s16)((s16)y - 0x3C),
        0.6f,
        (char *)D_80033F28[8]
    );
}
#else

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_80029BB4.s")
#endif

extern s8 D_80033F38;

void func_80029D30(void *arg0, s32 arg1) {
    Menu3A_Struct174 *temp_s0 = *(Menu3A_Struct174 **)((u8 *)arg0 + 0x174);
    void *sp34;

    temp_s0->unk17 = 0;
    func_80030894(temp_s0, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s0, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    if (menuCheckSaveFile(0) != 0) {
        D_80033F38 = 0;
    }
    sp34 = (void *)(s32)&D_8072052C;
    func_80030894(temp_s0, sp34, 0, 0, 1.0f, 2, 3);
    if (menuCheckSaveFile(1) != 0) {
        D_80033F38 = 0;
    }
    func_80030894(temp_s0, sp34, 1, 0, 1.0f, 2, 3);
    if (menuCheckSaveFile(2) != 0) {
        D_80033F38 = 0;
    }
    func_80030894(temp_s0, sp34, 2, 0, 1.0f, 2, 3);
    func_80030894(temp_s0, &D_807204BC, 0xA0, 0x78, 1.0f, 2, 4);
    func_80030894(temp_s0, &D_80720C34, 0xA0, 0xD2, 0.75f, 2, 0);
}

extern u8 D_8071FBC8;
extern u8 D_8071FE08;
void func_8071495C(void);
void func_80714CC0(void *, s32, s32, s32, f32);
void func_8060C830(s32, s32);
extern s8 D_80033FAC;

void menuMysteryHandleInput(void *arg0, s32 arg1) {
    Menu3R1_Struct174 *temp_s0 = *(Menu3R1_Struct174 **)((u8 *)arg0 + 0x174);

    if (temp_s0->unk0 == 0.0f && temp_s0->unk4 == 0.0f) {
        if (arg1 & 1) {
            if ((arg1 & 8) && (D_80033FAC != 0)) {
                func_8071495C();
                func_80714CC0(&D_8071FBC8, 0x4124CCCD, 0x43700000, 0x42F00000, -10.0f);
                func_8071495C();
                func_80714CC0(&D_8071FE08, 0x4124CCCD, 0x43700000, 0x42F00000, -10.0f);
                func_80609140(0xF6, 0x7FFF, 63.0f, 1.0f, 0, 0);
                func_8060C830((u8)D_80033F48, 1);
                temp_s0->unk16 = 0;
                temp_s0->unk13 = 2;
            } else if ((arg1 & 4) && (D_80033FAC != 0)) {
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                temp_s0->unk16 = 0;
                temp_s0->unk13 = 2;
            }
        } else if (arg1 & 2) {
            func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
            temp_s0->unk16 = 0;
            temp_s0->unk13 = 2;
        }
    }
    menuUpdateItemTransition(arg0, temp_s0, 1);
}


#ifdef NON_MATCHING
Gfx *func_8002A088(void *arg0, Gfx *arg1) {
    void *temp_a0 = *(void **)((u8 *)arg0 + 0x174);
    s32 sp124;
    s32 sp120;
    s32 sp11C;
    f32 sp118;
    f32 sp114;
    s32 sp110;
    s32 sp10C;
    s16 sp106;
    char sp3C[200];
    s16 y;

    arg1->words.w1 = -1;
    arg1->words.w0 = 0xFA000000;
    func_800317E8(temp_a0, 160.0f, 25.0f, &sp118, &sp114, 5, 0, 0.45f);
    arg1 += 1;
    sp106 = (s16)(sp118 * 4.0f);
    y = (s16)(sp114 * 4.0f);
    if (menuCheckSaveFile(D_80033F48) != 0) {
        _sprintf(sp3C, "%s", (char *)D_80033F28[6]);
    } else {
        _sprintf(sp3C, "%s %d", (char *)D_80033F28[7], D_80033F48 + 1);
    }
    arg1 = hudDrawScaledText(hudDrawScaledText(arg1, sp106, y, 0.6f, sp3C), (s16)(sp118 * 4.0f), (s16)(y - 0x3C), 0.6f, (char *)D_80033F28[8]);
    func_800317E8(temp_a0, 160.0f, 80.0f, &sp118, &sp114, 5, 0, 2.0f);
    arg1 = hudDrawScaledText(arg1, (s16)(sp118 * 4.0f), (s16)(sp114 * 4.0f), 0.6f, (char *)D_80033F28[9]);
    func_800317E8(temp_a0, 80.0f, 120.0f, &sp118, &sp114, 5, 0, 2.0f);
    return hudDrawScaledText(hudDrawScaledText(arg1, (s16)(sp118 * 4.0f), (s16)(sp114 * 4.0f), 0.6f, (char *)D_80033F28[10]), (s16)(0x500 - (s32)(sp118 * 4.0f)), (s16)(sp114 * 4.0f), 0.6f, (char *)D_80033F28[11]);
}
#else

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002A088.s")
#endif

void func_80030894(void *, void *, s32, s32, f32, s32, s32);
extern s8 D_80033FAC;
extern u8 D_80720CF0;
extern u8 D_80720D14;
extern u8 D_80720C34;

void func_8002A36C(void *arg0, s32 arg1) {
    Menu3A_Struct174 *temp_s0 = *(Menu3A_Struct174 **)((u8 *)arg0 + 0x174);

    D_80033FAC = 0;
    temp_s0->unk17 = 0;
    func_80030894(temp_s0, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s0, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s0, &D_807204BC, 0xA0, 0x80, 1.0f, 2, 8);
    func_80030894(temp_s0, &D_80720C34, 0xA0, 0xD2, 0.75f, 2, 0);
}

extern s16 D_80033670;
extern s8 D_80033698;
extern s8 D_80744538;
extern s8 D_8076A104;

void menuBossReplayHandleInput(arg0, arg1)
void *arg0;
s32 arg1;
{
    Menu3R1_Struct174 *temp_s0 = *(Menu3R1_Struct174 **)((u8 *)arg0 + 0x174);

    if (temp_s0->unk0 == 0.0f) {
        if (temp_s0->unk4 == 0.0f) {
            if (arg1 & 1) {
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                temp_s0->unk16 = 0;
                temp_s0->unk13 = 7;
            } else if (arg1 & 2) {
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                temp_s0->unk16 = 0;
                temp_s0->unk13 = 1;
                D_80033698 = 3;
            } else {
                menuHandleScrollInput(temp_s0, 2, arg1);
            }
            if (temp_s0->unk17 == 0) {
                if (!(D_80033670 & 0x10) && (arg1 & 0x10)) {
                    func_80609140(0x75, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    D_80744538++;
                    if (D_80744538 >= 3) {
                        D_80744538 = 0;
                    }
                } else if (!(D_80033670 & 0x20) && (arg1 & 0x20)) {
                    func_80609140(0x75, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    D_80744538--;
                    if (D_80744538 < 0) {
                        D_80744538 = 2;
                    }
                }
            }
        }
        menuUpdateScrollAnimation(temp_s0, 2);
    }
    D_8076A104 = temp_s0->unk17;
    menuUpdateItemTransition(arg0, temp_s0, 1);
}

s32 func_806FC530(s32, s16, s16, s16, void *, s32);
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);
f32 func_80612790(s16);
f32 func_80612794(s16);

#ifdef NON_MATCHING
Gfx *func_8002A638(void *arg0, Gfx *arg1) {
    Menu3A_Struct174 *temp_s2 = *(Menu3A_Struct174 **)((u8 *)arg0 + 0x174);
    s32 idx;
    s32 i;
    s32 id;
    s16 ang;
    s32 pad0;
    f32 sp174;
    f32 sp170;
    char sp98[0xD8];
    s32 pad1;
    s32 pad2;

    D_807FBB60 &= ~0x10;
    arg1->words.w0 = 0xFA000000;
    arg1->words.w1 = -1;
    idx = func_800317E8(temp_s2, 160.0f, 20.0f, &sp174, &sp170, 2, 1, 0.7f);
    arg1 += 1;
    arg1 = (Gfx *)func_806FC530((s32)arg1, 1, (s16)(sp174 * 4.0f), (s16)(sp170 * 4.0f), (void *)D_80033F28[idx + 12], 0x81);
    if (idx == 0) {
        _sprintf(sp98, "%s %d", (char *)D_80033F28[14], D_80744538 + 1);
        func_800317E8(temp_s2, 160.0f, 207.0f, &sp174, &sp170, 2, 0, 0.7f);
        arg1 = hudDrawScaledText(arg1, (s16)(sp174 * 4.0f), (s16)(sp170 * 4.0f), 0.6f, sp98);
    }
    arg1->words.w0 = 0xFA000000;
    arg1->words.w1 = -1;
    arg1++;
    i = 0;
    do {
        ang = (i - (temp_s2->unk17 << 11)) - (s32)((f64)temp_s2->unk4 * 2048.0);
        sp174 = 160.0 - (f64)func_80612794(ang) * 50.0;
        sp170 = 120.0 - (f64)func_80612790(ang) * 50.0;
        func_800317E8(temp_s2, sp174, sp170, &sp174, &sp170, 2, 0, 1.5f);
        sp174 = (f32)((f64)sp174 + 12.0) * 4.0f;
        sp170 = (f32)((f64)sp170 + 28.0) * 4.0f;
        if (i == 0) {
            id = D_80744538 + 0xB2;
        } else {
            id = 0xB1;
        }
        i += 0x800;
        arg1 = func_8068C5A8(
            func_8068C5A8(arg1, (u16)id, 0, 2, 0x20, 0x40, (s32)((f64)sp174 - 96.0), (s32)sp170, 3.0f, -3.0f, 0, 0.0f),
            (u16)(id + 4), 0, 2, 0x20, 0x40, (s32)sp174, (s32)sp170, 3.0f, -3.0f, 0, 0.0f);
    } while (i != 0x1000);
}
#else

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002A638.s")
#endif

extern s8 D_8076A100[];
extern s8 D_8076A0E4[];
extern s8 D_8076A0E8[][4];

void menuAssignPlayerControllerSlot(s32 arg0, s32 arg1) {
    s8 temp_v0 = D_8076A0E4[arg0];
    s8 *temp_v1 = &D_8076A0E4[arg0];
    s32 var_a2 = 0;
    s8 *temp_a3 = &D_8076A100[arg0];
    s8 temp_t0 = *temp_a3;
    s32 var_v0;

    if (temp_t0 >= 0) {
        D_8076A0E8[temp_v0][temp_t0] = -1;
    }
    for (var_v0 = 0; (var_v0 < 4) && (var_a2 == 0); var_v0++) {
        if (D_8076A0E8[arg1][var_v0] == -1) {
            var_a2 = 1;
            *temp_a3 = var_v0;
            D_8076A0E8[arg1][var_v0] = arg0;
        }
    }
    *temp_v1 = arg1;
}

void menuReleasePlayerControllerSlot(s32 arg0) {
    s8 temp_v0 = D_8076A0E4[arg0];
    s8 *temp_v1 = &D_8076A0E4[arg0];
    s8 *temp_a1 = &D_8076A100[arg0];
    s8 temp_a2 = *temp_a1;

    if ((temp_a2 >= 0) && !(temp_v0 & 0x80)) {
        D_8076A0E8[temp_v0][temp_a2] = -1;
    }
    *temp_a1 = -1;
    *temp_v1 = -0x80;
}


extern s8 D_8076A0D6;

void func_8002AB80(void *arg0, s32 arg1) {
    Menu3A_Struct174 *temp_s0 = *(Menu3A_Struct174 **)((u8 *)arg0 + 0x174);
    s32 i;
    s32 j;

    temp_s0->unk17 = D_8076A0D6;
    func_80030894(temp_s0, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s0, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s0, &D_80720C34, 0xA0, 0x78, 0.75f, 2, 4);
    for (i = 0; i < 6; i++) {
        j = 0;
        do {
            D_8076A0E8[i][j] = -1;
            j++;
        } while (j < 4);
    }
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            menuAssignPlayerControllerSlot(i, i);
        } else {
            D_8076A0E4[i] = -0x80;
            menuReleasePlayerControllerSlot(i);
        }
    }
}

s32 func_8002ACD4(s32 arg0) {
    s8 temp_v0 = D_8076A0E4[arg0];
    s8 *row;
    s32 idx;
    s32 flag;

    idx = D_8076A100[arg0];
    flag = 0;
    row = D_8076A0E8[temp_v0];
    row[idx] = -1;
    do {
        idx += 1;
        if (idx >= 4) {
            idx = 0;
        }
        if (row[idx] == -1) {
            flag = 1;
            D_8076A100[arg0] = idx;
            row[idx] = arg0;
        }
    } while (flag == 0);
    return idx;
}

s32 func_8002AD50(s32 arg0) {
    s8 temp_v0 = D_8076A0E4[arg0];
    s8 *row;
    s32 idx;
    s32 flag;

    idx = D_8076A100[arg0];
    flag = 0;
    row = D_8076A0E8[temp_v0];
    row[idx] = -1;
    do {
        idx -= 1;
        if (idx < 0) {
            idx = 3;
        }
        if (row[idx] == -1) {
            flag = 1;
            D_8076A100[arg0] = idx;
            row[idx] = arg0;
        }
    } while (flag == 0);
    return idx;
}

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002ADC8.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002B708.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002C0C8.s")

void func_8002C584(void *arg0, s32 arg1) {
    Menu3A_Struct174 *temp_s0 = *(Menu3A_Struct174 **)((u8 *)arg0 + 0x174);

    if (temp_s0->unk0 == 0.0 && (arg1 & 1)) {
        func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
        temp_s0->unk16 = 0;
        temp_s0->unk13 = 7;
    }
    menuUpdateItemTransition(arg0, temp_s0, 0);
    menuUpdateCameraPositions();
    D_807FBB60 &= ~0x10;
    D_807FBB60 |= 0x10000;
}

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002C634.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002C91C.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002CB18.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002CFA4.s")

extern s16 D_80033674;
extern s32 *D_80033F28;
extern s8 D_8074583C;
extern s8 D_80745840;
extern s8 D_80745844;
s32 func_800317E8(void *, f32, f32, f32 *, f32 *, s32, s8, f32);
s32 func_806FC530(s32, s16, s16, s16, void *, s32);
s32 func_8002F980(s32, void *, void *, s32, u32 *, s16, f32 *, f32, s16);

s32 menuFormatOptionValues(void *arg0, s32 arg1) {
    void *sp64;
    u32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    s16 pad;
    s16 sp4C;
    char sp40[12];

    sp64 = *(void **)((u8 *)arg0 + 0x174);
    D_807FBB60 &= ~0x10;
    func_800317E8(sp64, 160.0f, 20.0f, &sp58, &sp54, 2, 0, 1.5f);
    arg1 = func_8002F980(
        func_806FC530(arg1, 1, 0x280, (s16)(sp54 * 4.0f), *(void **)((u8 *)D_80033F28 + 0x80), 0x81),
        sp64,
        (void *)((u8 *)D_80033F28 + 0x84),
        4,
        &sp60,
        1,
        &sp50,
        80.0f,
        -1
    );
    D_80033674 = 0x3E8;
    func_800317E8(sp64, 160.0f, 150.0f, &sp58, &sp54, 2, 0, 1.5f);
    sp4C = (s16)(sp54 * 4.0f);
    sp58 = (sp58 - sp50) * 4.0f;

    switch (sp60) {
    case 0:
        arg1 = func_806FC530(arg1, 1, (s16)sp58, sp4C, *(void **)((u8 *)D_80033F28 + D_80745844 * 4 + 0x94), 0x81);
        break;
    case 1:
    case 2:
        arg1 = func_806FC530(arg1, 1, (s16)sp58, sp4C, *(void **)((u8 *)D_80033F28 + 0xA0), 0x81);
        _sprintf(sp40, "%d", ((sp60 == 1 ? D_8074583C : D_80745840) + 1) >> 1);
        arg1 = func_806FC530(arg1, 1, (s16)sp58, sp4C + 0x78, sp40, 0x81);
        break;
    case 3:
        D_80033674 = 0;
        break;
    }

    return arg1;
}

typedef struct Menu3B_Sub174 {
    char pad[4];
    f32 unk4;
    char pad8[0xF];
    s8 unk17;
} Menu3B_Sub174;

typedef struct Menu3B_Actor {
    char pad[0x174];
    Menu3B_Sub174 *unk174;
} Menu3B_Actor;

extern u8 D_80720D38;

void func_8002D7EC(Menu3B_Actor *arg0, s32 arg1) {

    Menu3B_Sub174 *temp_a0 = arg0->unk174;
    temp_a0->unk17 = 0;
    func_80030894(temp_a0, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_a0, &D_80720C34, 0xA0, 0x7D, 0.75f, 2, 4);
    func_80030894(temp_a0, &D_80720D38, 0xA0, 0xC8, 1.0f, 2, 0xC);
}

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002D8AC.s")

typedef struct Menu3R3_StructF28 {
    char padA4[0xA4];
    void *unkA4;
    void *unkA8;
    char padAC[0xBC - 0xAC];
    void *unkBC;
    char padC0[0xC4 - 0xC0];
    void *unkC4;
    char padC8[0xCC - 0xC8];
    void *unkCC;
    void *unkD0;
} Menu3R3_StructF28;

extern s16 D_80033674;
extern s8 D_800338FC;
extern s32 *D_80033F28;
extern s8 D_807444C0;
extern s8 D_8074452C;
extern u8 D_80744530;

s32 func_8002DBDC(Menu3B_Actor *arg0, s32 arg1) {
    void *sp6C = arg0->unk174;
    u32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    s32 pad0;
    s32 pad1;
    s32 pad2;
    s32 pad3;
    s32 pad4;
    s32 pad5;
    s16 y;

    D_807FBB60 &= ~0x10;
    func_800317E8(sp6C, 160.0f, 20.0f, &sp64, &sp60, D_800338FC, 0, 1.5f);
    arg1 = func_8002F980(
        func_806FC530(arg1, 1, 0x280, (s16)(sp60 * 4.0f), ((Menu3R3_StructF28 *)D_80033F28)->unkA4, 0x81),
        sp6C,
        &((Menu3R3_StructF28 *)D_80033F28)->unkA8,
        D_800338FC,
        &sp68,
        1,
        &sp5C,
        80.0f,
        -1
    );
    D_80033674 = 0x3E8;
    func_800317E8(sp6C, 160.0f, 150.0f, &sp64, &sp60, 2, 0, 1.5f);
    y = (s16)(sp60 * 4.0f);
    sp64 = (sp64 - sp5C) * 4.0f;

    switch (sp68) {
    case 0:
        arg1 = func_806FC530(arg1, 1, (s16)sp64, y + 0x40, ((Menu3R3_StructF28 *)((u8 *)D_80033F28 + D_807444C0 * 4))->unkBC, 0x81);
        break;
    case 1:
        arg1 = func_806FC530(arg1, 1, (s16)sp64, y + 0x40, ((Menu3R3_StructF28 *)((u8 *)D_80033F28 + D_8074452C * 4))->unkC4, 0x81);
        break;
    case 2:
        D_80033674 = 0;
        break;
    case 3:
        arg1 = func_806FC530(arg1, 1, (s16)sp64, y + 0x40, ((Menu3R3_StructF28 *)((u8 *)D_80033F28 + D_80744530 * 4))->unkD0, 0x81);
        break;
    case 4:
        arg1 = func_806FC530(arg1, 1, (s16)sp64, y + 0x40, ((Menu3R3_StructF28 *)D_80033F28)->unkCC, 0x81);
        break;
    }

    return arg1;
}

void func_8002DEE8(Menu3B_Actor *arg0, s32 arg1) {
    Menu3B_Sub174 *temp_a0 = arg0->unk174;
    temp_a0->unk17 = 0;
    func_80030894(temp_a0, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_a0, &D_80720C34, 0xA0, 0x7D, 0.75f, 2, 4);
    func_80030894(temp_a0, &D_80720D38, 0xA0, 0xC8, 1.0f, 2, 0xC);
}

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002DFA8.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002E420.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002E8B8.s")

typedef struct Menu3B_Struct_6 {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
} Menu3B_Struct_6;

extern Menu3B_Struct_6 D_80744548[];
extern Menu3B_Struct_6 D_80744568[];
s32 func_8060C6B8(s32, s32, u8, s32);
s32 func_8060C648(s32, s32, u8, s32, s32);
void func_8060DEA8(void);


void menuLoadHighScores(void) {
    Menu3B_Struct_6 *v1;
    Menu3B_Struct_6 *v2;
    s32 i;

    for (i = 0, v1 = D_80744548, v2 = D_80744568; i < 5; i++, v1++, v2++) {
        u8 temp_s0 = i;
        v1->unk0 = func_8060C6B8(0x19, 0, temp_s0, 0);
        v1->unk2 = func_8060C6B8(0x16, 0, temp_s0, 0);
        v1->unk3 = func_8060C6B8(0x17, 0, temp_s0, 0);
        v1->unk4 = func_8060C6B8(0x18, 0, temp_s0, 0);
        v1->unk5 = 0;
        v2->unk0 = func_8060C6B8(0x1D, 0, temp_s0, 0);
        v2->unk2 = func_8060C6B8(0x1A, 0, temp_s0, 0);
        v2->unk3 = func_8060C6B8(0x1B, 0, temp_s0, 0);
        v2->unk4 = func_8060C6B8(0x1C, 0, temp_s0, 0);
        v2->unk5 = 0;
    }
}

void menuSaveHighScores(void) {
    Menu3B_Struct_6 *v1;
    Menu3B_Struct_6 *v2;
    s32 i;

    for (i = 0, v1 = D_80744548, v2 = D_80744568; i < 5; i++, v1++, v2++) {
        u8 temp_s0 = i;
        func_8060C648(0x19, 0, temp_s0, 0, v1->unk0);
        func_8060C648(0x16, 0, temp_s0, 0, v1->unk2);
        func_8060C648(0x17, 0, temp_s0, 0, v1->unk3);
        func_8060C648(0x18, 0, temp_s0, 0, v1->unk4);
        func_8060C648(0x1D, 0, temp_s0, 0, v2->unk0);
        func_8060C648(0x1A, 0, temp_s0, 0, v2->unk2);
        func_8060C648(0x1B, 0, temp_s0, 0, v2->unk3);
        func_8060C648(0x1C, 0, temp_s0, 0, v2->unk4);
    }
    func_8060DEA8();
}

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002EF68.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/D_80033BE0.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/D_80033BE4.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/D_80033BE8.s")

#ifdef NON_MATCHING
extern s8 D_80033F60;
extern s8 D_800339A8;
extern s8 D_80033F61;
extern s16 D_80744518;
extern char *D_800339AC[];
extern u32 D_8076A064;

s32 func_8002F284(void *arg0, s32 arg1) {
    void *temp_s0;
    f32 sp140;
    f32 sp13C;
    s32 ft4;
    Menu3B_Struct_6 *e;
    Menu3B_Struct_6 *sp130;
    char sp68[0xC8];
    s16 var_s3;
    s16 i;

    temp_s0 = *(void **)((u8 *)arg0 + 0x174);
    D_807FBB60 &= ~0x10;
    func_800317E8(temp_s0, 160.0f, 20.0f, &sp140, &sp13C, 2, 0, 1.0f);
    arg1 = func_806FC530(arg1, 1, 0x280, (s16)(sp13C * 4.0), ((void **)D_80033F28)[D_800339A8 + 0x5F], 0x81);
    func_800317E8(temp_s0, 160.0f, 205.0f, &sp140, &sp13C, 2, 0, 1.0f);
    i = 0;
    var_s3 = (s16)(sp13C * 4.0);
    if (D_80033F60 >= 0) {
        _sprintf(sp68, "%s", ((void **)D_80033F28)[0x63]);
        i = 1;
    } else if (D_80033F60 == -2) {
        _sprintf(sp68, "%s %d.", ((void **)D_80033F28)[0x64], D_80744518);
        i = 1;
    }
    if (i != 0) {
        arg1 = (s32)hudDrawScaledText((Gfx *)arg1, 0x280, var_s3, 0.6f, sp68);
    }
    i = 0;
    func_800317E8(temp_s0, 20.0f, 120.0f, &sp140, &sp13C, 2, 0, 2.0f);
    var_s3 = 0xC8;
    ft4 = (s16)(s32)(sp140 * 4.0f);
    if (D_800339A8 == 0) {
        sp130 = D_80744548;
    } else {
        sp130 = D_80744568;
    }
    do {
        _sprintf(sp68, "%d.", i + 1);
        e = (Menu3B_Struct_6 *)((u8 *)sp130 + i * 6);
        arg1 = func_806FC530(arg1, 1, (s16)(ft4 + 0x50), var_s3, sp68, 1);
        _sprintf(sp68, "%c %c %c", e->unk2, e->unk3, e->unk4);
        arg1 = func_806FC530(arg1, 0x81, (s16)(ft4 + 0x118), var_s3, sp68, 1);
        _sprintf(sp68, "%d", e->unk0);
        arg1 = func_806FC530(arg1, 0x81, (s16)(0x3E8 - ft4), var_s3, sp68, 1);
        if (i == D_80033F60 && (D_8076A064 & 0x1F) < 0x14) {
            arg1 = func_806FC530(arg1, 0x81, (s16)(ft4 + 0x118), var_s3 + 0x34, D_800339AC[D_80033F61], 1);
        }
        var_s3 += 0x6C;
    } while (++i < 5);
    return arg1;
}
#else

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002F284.s")
#endif

extern s8 D_80033F60;

void func_8002F6C8(Menu3B_Actor *arg0, s32 arg1) {
    Menu3B_Sub174 *sp2C = arg0->unk174;

    if (D_80033F60 == -1) {
        func_80030894(sp2C, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
        func_80030894(sp2C, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    }
}

extern s8 D_800339A8;
extern s8 D_80033F61;
extern s16 D_80744518;

void menuInsertHighScore(void) {
    Menu3B_Struct_6 *table;
    s32 i;
    s32 j;

    if (D_800339A8 == 0) {
        table = D_80744548;
    } else {
        table = D_80744568;
    }

    for (i = 0; i < 5; i++) {
        if (D_80744518 >= table[i].unk0) {
            j = 4;
            if (i < 4) {
                do {
                    table[j].unk0 = table[j - 1].unk0;
                    table[j].unk2 = table[j - 1].unk2;
                    table[j].unk3 = table[j - 1].unk3;
                    table[j].unk4 = table[j - 1].unk4;
                    j--;
                } while (j > i);
            }
            table[i].unk0 = D_80744518;
            table[i].unk2 = 0x2E;
            table[i].unk3 = 0x2E;
            table[i].unk4 = 0x2E;
            D_80033F60 = i;
            D_80033F61 = 0;
            return;
        }
    }
    D_80033F60 = -1;
}

typedef struct Menu3B_Struct_C924 {
    char pad[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    char pad2[0xC];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
} Menu3B_Struct_C924;

extern Menu3B_Struct_C924 *D_807FC924;

void menuUpdateCameraPositions(void) {
    D_807FC924->unk210 = D_807FBB4C->unk7C;
    D_807FC924->unk214 = D_807FBB4C->unk80 + 13.1f;
    D_807FC924->unk218 = D_807FBB4C->unk84 - 50.0f;
    D_807FC924->unk228 = D_807FBB4C->unk7C;
    D_807FC924->unk22C = D_807FC924->unk214;
    D_807FC924->unk230 = D_807FBB4C->unk84 - 100.0f;
}

extern char D_800339C4[];
extern f32 D_80033F44;

s32 func_8002F980(s32 arg0, void *arg1, void *arg2, s32 arg3, u32 *arg4, s16 arg5, f32 *arg6, f32 arg7, s16 arg8) {
    s32 idx = ((Menu3B_Sub174 *)arg1)->unk17;
    f32 v;
    f32 sp3C;
    f32 sp38;
    s16 y;

    if (((Menu3B_Sub174 *)arg1)->unk4 != 0.0f) {
        if (((Menu3B_Sub174 *)arg1)->unk4 > 0.5f) {
            idx++;
        }
        if (idx >= arg3) {
            idx = 0;
        }
    }
    v = ((Menu3B_Sub174 *)arg1)->unk4 - 0.5f;
    if (v < 0.0f) {
        v = -v;
    }
    v = 0.5f - v;
    v = v * 800.0f;
    if (D_80033F44 < 0.0f) {
        v = -v;
    }
    func_800317E8(arg1, (f32)(v + 160.0), arg7, &sp3C, &sp38, 2, 0, 2.0f);
    y = (s16)(sp38 * 4.0f);
    if (arg8 & (1 << idx)) {
        arg0 = func_806FC530(arg0, arg5, (s16)(sp3C * 4.0f), y, *(void **)((u8 *)arg2 + idx * 4), 0x81);
    } else {
        arg0 = func_806FC530(arg0, arg5, (s16)(sp3C * 4.0f), y, D_800339C4, 0x81);
    }
    *arg6 = v;
    *arg4 = idx;
    return arg0;
}

extern f32 D_80033F68[];
extern f32 D_80033F80[];
extern f32 D_80033F98[];

s32 menuSetElementCoordinates(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 four = 4.0f;
    f64 d1 = 32.0;
    f64 d2 = 100.0;

    arg1 &= 0x7F;
    arg2 = arg2 * four;
    arg3 = arg3 * four;
    *(f32 *)((u8 *)D_80033F68 + arg1 * 4) = (f64)arg2 - d1;
    *(f32 *)((u8 *)D_80033F80 + arg1 * 4) = (f64)arg3 - d2;
    *(f32 *)((u8 *)D_80033F98 + arg1 * 4) = (f64)arg4 * 1.333;
    return arg0;
}

typedef struct Menu3R3_StructFC1C {
    f32 unk0;
    char pad4[0xE];
    s8 unk12;
    s8 unk13;
    char pad14[2];
    s8 unk16;
} Menu3R3_StructFC1C;

extern s8 D_80033F50;

void menuUpdateItemTransition(void *arg0, void *arg1_raw, s32 arg2) {
    Menu3R3_StructFC1C *arg1 = (Menu3R3_StructFC1C *)arg1_raw;
    f32 zero = 0.0f;
    if (!arg1->unk16) {
        arg1->unk0 += 0.13f;
        if (arg1->unk0 > 1.3f) {
            arg1->unk0 = 1.0f;
            arg1->unk12 = arg1->unk13;
            arg1->unk16 = -1;
            func_80030340(arg0, 0, 0, 0);
            func_80609140(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
        }
    } else {
        if (arg1->unk0 > zero) {
            arg1->unk0 -= 0.2f;
            if (arg1->unk0 < zero) {
                arg1->unk0 = zero;
                if (arg2 != 0) {
                    func_80609140(0x3C, 0x61A8, 63.0f, 1.0f, 0, 0);
                    D_80033F50 = 3;
                }
            }
        }
    }
}

extern s8 D_800337F0;

extern f32 D_80033F44;

void menuHandleScrollInput(Menu3B_Sub174 *arg0, s32 arg1, s32 arg2) {
    if (arg2 & 4) {
        func_80609140(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
        D_80033F44 = -0.1f;
        arg0->unk17--;
        arg0->unk4 = 1.0f;
        if (arg0->unk17 < 0) {
            arg0->unk17 += arg1;
        }
        D_800337F0 = 0;
    } else if (arg2 & 8) {
        func_80609140(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
        D_80033F44 = 0.1f;
        D_800337F0 = 0;
    }
}


void menuUpdateScrollAnimation(Menu3B_Sub174 *arg0, s32 arg1) {
    if (D_80033F44 > 0.0f) {
        arg0->unk4 += D_80033F44;
        if (arg0->unk4 >= 1.0f) {
            arg0->unk4 = 0.0f;
            arg0->unk17++;
            if (arg0->unk17 >= arg1) {
                arg0->unk17 -= arg1;
            }
            D_80033F44 = 0.0f;
        }
    } else if (D_80033F44 < 0.0f) {
        arg0->unk4 += D_80033F44;
        if (arg0->unk4 <= 0.0f) {
            D_80033F44 = 0.0f;
            arg0->unk4 = 0.0f;
        }
    }
}

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002FEBC.s")

extern Gfx D_1000118;
extern Mtx D_20000C0;


void menuInitGfxState(Gfx *glistp, s32 arg1) {
    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_1000118);
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gDPSetRenderMode(glistp++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, 255);
    gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gSPMatrix(glistp++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    func_80030340(arg1, 1, glistp, 0);
}

extern s8 D_800337F8;
extern f32 D_80033F3C;
extern f32 D_80033F40;
extern u8 D_8076A0D0[];
extern void *D_807ECDEC;
void func_80027FAC();
s32 func_800286C8();
void func_80028834();
s32 func_80028D3C();
void func_80028EA8();
s32 func_800291CC();
void func_800297B8();
Gfx *func_80029BB4();
void func_80029D30();
Gfx *func_8002A088();
Gfx *func_8002A638();
void func_8002AB80();
void func_8002ADC8();
s32 func_8002B708();
void func_8002C0C8();
s32 func_8002C634();
void func_8002C91C();
void func_8002CFA4();
void func_8002D8AC();
void func_8002DFA8();
s32 func_8002E420();
void func_8002E8B8();
void func_8002EF68();
void lightSetColor(f32, f32, f32, s32);

s32 func_80030340(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_t0 = *(void **)((u8 *)arg0 + 0x174);
    s32 sp18 = 0;

    if (**(u16 **)((u8 *)D_807FC924 + 0x298) & 0x8000) {
        sp18 = 1;
    }
    if (**(u16 **)((u8 *)D_807FC924 + 0x298) & 0x4000) {
        sp18 |= 2;
    }
    if (**(u16 **)((u8 *)D_807FC924 + 0x298) & 8) {
        sp18 |= 0x40;
    }
    if (**(u16 **)((u8 *)D_807FC924 + 0x298) & 4) {
        sp18 |= 0x80;
    }
    if (**(u16 **)((u8 *)D_807FC924 + 0x298) & 0x2000) {
        sp18 |= 0x100;
    }
    if (*((s8 *)D_807ECDEC + 2) < -0x28) {
        sp18 |= 4;
    } else if (*((s8 *)D_807ECDEC + 2) >= 0x29) {
        sp18 |= 8;
    }
    if (*((s8 *)D_807ECDEC + 3) < -0x28) {
        sp18 |= 0x20;
    } else if (*((s8 *)D_807ECDEC + 3) >= 0x29) {
        sp18 |= 0x10;
    }
    switch (arg1) {
    case 0:
        D_80033F38 = 1;
        D_80033F44 = 0.0f;
        D_80033F40 = 0.0f;
        D_80033F3C = 0.0f;
        D_807FBB60 &= 0xFFFEFFFF;
        *(s16 *)((u8 *)temp_t0 + 0xC) = 0;
        *(s16 *)((u8 *)temp_t0 + 0xE) = 0;
        D_800337F8 = 1;
        break;
    case 1:
        break;
    case 2:
        D_8076A0D0[*(s8 *)((u8 *)temp_t0 + 0x12)] = *(s8 *)((u8 *)temp_t0 + 0x17);
        lightSetColor(1.0f, 1.0f, 1.0f, 0);
        break;
    }
    switch (*(u8 *)((u8 *)temp_t0 + 0x12)) {
    case 0:
        if (arg1 == 1) {
            return func_80027F34(arg0, arg2);
        }
        if (arg1 == 2) {
            func_80027E60(arg0, sp18);
        } else {
            menuResetCameraAndFlags(arg0, arg3);
        }
        break;
    case 1:
        if (arg1 == 1) {
            return func_800286C8(arg0, arg2);
        }
        if (arg1 == 2) {
            func_80027FAC(arg0, sp18);
        } else {
            func_80028834(arg0, arg3);
        }
        break;
    case 2:
        if (arg1 == 1) {
            return func_80028D3C(arg0, arg2);
        }
        if (arg1 == 2) {
            menuHandleSelectionInput(arg0, sp18);
        } else {
            func_80028EA8(arg0, arg3);
        }
        break;
    case 3:
        if (arg1 == 1) {
            return func_800291CC(arg0, arg2);
        }
        if (arg1 == 2) {
            menuHandleConfirmationInput(arg0, sp18);
        } else {
            func_800297B8(arg0, arg3);
        }
        break;
    case 4:
        if (arg1 == 1) {
            return (s32)func_80029BB4(arg0, arg2);
        }
        if (arg1 == 2) {
            menuHandleFileSelectInput(arg0, sp18);
        } else {
            func_80029D30(arg0, arg3);
        }
        break;
    case 5:
        if (arg1 == 1) {
            return (s32)func_8002A088(arg0, arg2);
        }
        if (arg1 == 2) {
            menuMysteryHandleInput(arg0, sp18);
        } else {
            func_8002A36C(arg0, arg3);
        }
        break;
    case 6:
        if (arg1 == 1) {
            return (s32)func_8002A638(arg0, arg2);
        }
        if (arg1 == 2) {
            menuBossReplayHandleInput(arg0, sp18);
        } else {
            func_8002AB80(arg0, arg3);
        }
        break;
    case 7:
        if (arg1 == 1) {
            return func_8002B708(arg0, arg2);
        }
        if (arg1 == 2) {
            func_8002ADC8(arg0, sp18);
        } else {
            func_8002C0C8(arg0, arg3);
        }
        break;
    case 11:
        if (arg1 == 1) {
            return func_8002C634(arg0, arg2);
        }
        if (arg1 == 2) {
            func_8002C584(arg0, sp18);
        } else {
            func_8002C91C(arg0, arg3);
        }
        break;
    case 8:
        if (arg1 == 1) {
            return menuFormatOptionValues(arg0, arg2);
        }
        if (arg1 == 2) {
            func_8002CFA4(arg0, sp18);
        } else {
            func_8002D7EC(arg0, arg3);
        }
        break;
    case 9:
        if (arg1 == 1) {
            return func_8002DBDC(arg0, arg2);
        }
        if (arg1 == 2) {
            func_8002D8AC(arg0, sp18);
        } else {
            func_8002DEE8(arg0, arg3);
        }
        break;
    case 10:
        if (arg1 == 1) {
            return func_8002E420(arg0, arg2);
        }
        if (arg1 == 2) {
            func_8002DFA8(arg0, sp18);
        } else {
            func_8002E8B8(arg0, arg3);
        }
        break;
    case 12:
        if (arg1 == 1) {
            return func_8002F284(arg0, arg2);
        }
        if (arg1 == 2) {
            func_8002EF68(arg0, sp18);
        } else {
            func_8002F6C8(arg0, arg3);
        }
        break;
    }
    if (D_80033F50 > 0) {
        D_80033F50--;
    }
    D_80033670 = sp18;
    return arg2;
}

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_80030894.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_80030A90.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_80030C14.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8003155C.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_800317E8.s")

f32 menuEvaluateSpline(f32 *arg0, f32 arg1, f32 *arg2) {
    f32 sp[4];
    f32 m2 = -2.0f;
    f32 p3 = 3.0f;
    f32 m3 = -3.0f;

    sp[0] = (arg0[0] + arg0[0] + m2 * arg0[1] + arg0[2]) + arg0[3];
    sp[1] = (m3 * arg0[0] + p3 * arg0[1] + m2 * arg0[2]) - arg0[3];
    sp[2] = arg0[2];
    sp[3] = arg0[0];
    if (arg2 != NULL) {
        *arg2 = ((((p3 * sp[0]) * arg1) + (sp[1] + sp[1])) * arg1) + sp[2];
    }
    return (((((sp[0] * arg1) + sp[1]) * arg1) + sp[2]) * arg1) + sp[3];
}

typedef struct Menu3B_Struct_BB40 {
    char pad[0xE6];
    s16 unkE6;
    char padE8[0x155 - 0xE8];
    u8 unk155;
} Menu3B_Struct_BB40;

extern Menu3B_Struct_BB40 *D_807FBB40;
extern s8 D_80033734;
void actorScriptStart(void *, s32);
void camStartPath(void *, s32, s32);

void menuActorStateDispatch(void) {
    Menu3B_Struct_BB40 *actor = D_807FBB40;

    switch (actor->unk155) {
    case 0:
        actorScriptStart(actor, 0x345);
        D_807FBB40->unkE6 = 0;
        D_807FBB40->unk155 = 1;
        camStartPath(D_807FBB40, 0x13, 5);
        break;
    case 2:
        actor->unk155++;
        break;
    case 4:
        if (D_80033734 == 0) {
            D_80033734 = 1;
        }
        break;
    case 1:
    case 3:
    default:
        break;
    }
}

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_80031B08.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_80032024.s")


s32 menuCheckSaveFile(arg0)
    u8 arg0;
{
    return func_8060C6B8(0xD, 0, 0, arg0) == 0;
}

typedef struct Menu3R3_StructC828 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
} Menu3R3_StructC828;

extern Menu3R3_StructC828 D_807FC828;
void func_806ABE3C(void);

s32 menuCalculateGamePercentage(void) {
    f32 pct;

    func_806ABE3C();
    pct = 0.0f;
    pct = (f64)pct + ((f64)(f32)D_807FC828.unk0 * 0.4);
    pct = (f64)pct + ((f64)(f32)D_807FC828.unk4 * 0.25);
    pct = (f64)pct + ((f64)(f32)D_807FC828.unkA * 0.2);
    pct = (f64)pct + ((f64)(f32)D_807FC828.unk6 * 0.2);
    pct = (f64)pct + ((f64)(f32)D_807FC828.unk2 * 0.5);
    pct = (f64)pct + ((f64)(f32)D_807FC828.unk8 * 0.5);
    pct = (f64)pct + ((f64)(f32)D_807FC828.unkC * 0.5);

    if (D_807FC828.unk0 == 0xC9) {
        pct = (f64)pct - 0.4;
    }

    if ((f64)pct == 100.0) {
        if (flagGet(0x12D, 0) != 0 && flagGet(0x12D, 0) != 0) {
            pct = (f64)pct + 1.0;
        }
    }

    return pct;
}

void *func_80610FE8(s32);
s32 func_8070E750(s32, s32, s32);

void menuLoadTextTable(void) {
    s32 i;

    D_80033F28 = func_80610FE8(0x194);
    i = 0;
    do {
        s32 val = func_8070E750(0x25, i, 0);
        D_80033F28[i] = val;
        i++;
    } while (i != 0x65);
}
