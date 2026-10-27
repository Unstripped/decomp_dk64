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

void func_80030340();
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

s32 func_80027F34(u8 arg0, s32 arg1) {
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

void menuResetCameraAndFlags(void *arg0, u8 arg1) {
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


#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002907C.s")

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

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_800297B8.s")

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

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_80029BB4.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_80029D30.s")

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

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002A088.s")

void func_80030894(void *, void *, s32, s32, f32, s32, s32);
extern s8 D_80033FAC;
extern u8 D_80720CF0;
extern u8 D_80720D14;
extern u8 D_807204BC;
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

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002A638.s")

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

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002AB80.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002ACD4.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002AD50.s")

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
s32 func_8002F980(s32, void *, void *, s8, u32 *, s16, f32 *, f32, s16);
int _sprintf(char *, const char *, ...);

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

extern u8 D_80720C34;
extern u8 D_80720D14;
extern u8 D_80720D38;
void func_80030894(void *, void *, s32, s32, f32, s32, s32);

void func_8002D7EC(Menu3B_Actor *arg0, s8 arg1) {

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
s32 func_800317E8(void *, f32, f32, f32 *, f32 *, s32, s8, f32);
s32 func_8002F980(s32, void *, void *, s8, u32 *, s16, f32 *, f32, s16);
s32 func_806FC530(s32, s16, s16, s16, void *, s32);

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

void func_8002DEE8(Menu3B_Actor *arg0, s8 arg1) {
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

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002F284.s")

extern s8 D_80033F60;
extern u8 D_80720CF0;

void func_8002F6C8(Menu3B_Actor *arg0, s8 arg1) {
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

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002F980.s")

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

extern f32 D_80033F44;

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

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_80030340.s")

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
s32 flagGet(s32, s32);

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

extern s32 *D_80033F28;
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
