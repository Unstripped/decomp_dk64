#include "common.h"

typedef struct {
    char pad0[0x340];
    f32 x;
    f32 y;
    f32 z;
} MenuActor_340;

typedef struct MenuStruct_80024000 {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ char pad3[3];
    /* 0x06 */ u8 unk6;
    /* 0x07 */ char pad7[1];
    /* 0x08 */ MenuActor_340 *unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ char pad18;
    /* 0x19 */ s8 unk19;
    /* 0x1A */ u8 unk1A;
} MenuStruct_80024000;

typedef struct {
    s16 unk0;
    s16 unk2;
} MenuStruct_30A2;

extern u8 D_8076A0AB;
extern s32 D_80032F48[][6];
extern MenuStruct_30A2 D_800330A2[];

s32 func_805FF030(s32, s32);
void func_8063DA40(s16, s32);
void func_8061CC40(s32, s32, s32);

void menuPlaySoundFromTable(MenuStruct_80024000 *arg0) {
    s32 temp_v1 = D_80032F48[func_805FF030(D_8076A0AB, 0)][arg0->unk1];

    if (temp_v1 == 0) {
        func_8063DA40(D_800330A2[arg0->unk1A].unk0, 9);
        arg0->unk0 = 4;
        arg0->unk1 = 0;
        return;
    }
    if (temp_v1 == 4) {
        arg0->unk6 = 1;
    }
    func_8061CC40(0, (s16)temp_v1, 1);
    arg0->unk1++;
}


extern u8 D_80720268;
void func_80714998(s32);
void func_807149B8(s32);
void func_807149FC(s32);
MenuActor_340 *func_80714CC0(void *, s32, s32, s32, f32);

void menuSpawnPositionalActor(MenuStruct_80024000 *arg0) {
    arg0->unk10 = 11.35f;
    arg0->unkC = -6.55f;
    arg0->unk14 = 6.6f;
    arg0->unk6 = 0;
    func_80714998(0);
    func_807149B8(1);
    func_807149FC(-1);
    func_80714998(0);
    arg0->unk8 = func_80714CC0(&D_80720268, 0x3E99999A, 0x43350000, 0x40400000, 82.0f);
}

void effectFreeAndUnlink(MenuActor_340 *);

void menuUpdateFallingActor(MenuStruct_80024000 *arg0) {
    MenuActor_340 *temp_v0 = arg0->unk8;
    temp_v0->x += arg0->unkC;
    temp_v0->z += arg0->unk14;
    arg0->unk10 += -1.0f;
    temp_v0->y += arg0->unk10;
    arg0->unk6++;
    if (arg0->unk6 >= 0x16) {
        arg0->unk6 = 0;
        effectFreeAndUnlink(arg0->unk8);
        arg0->unk8 = NULL;
    }
}

extern void *D_807FBB4C;
void func_806CFF9C(void *);
void func_805FF898(void);

void menuResetAudioState(void) {
    func_806CFF9C(D_807FBB4C);
    func_805FF898();
    func_8061CC40(0, 7, 1);
}

typedef struct {
    char pad0[1];
    u8 unk1;
    char pad2[0x17];
    s8 unk19;
} MenuSubStruct_180;

typedef struct {
    char pad0[0x60];
    s32 unk60;
    char pad64[0xFB];
    u8 unk15F;
    char pad160[0x20];
    MenuStruct_80024000 *unk180;
} MenuBB40_60;
extern MenuBB40_60 *D_807FBB40;
extern s16 D_80750AC8;
s32 func_80629148(void);
void func_8070D8C0(void *, s32, u8);
void func_8061CB08(void);
void func_80629174();

void menuPlaySoundFromTable(MenuStruct_80024000 *);
void menuUpdateFallingActor(MenuStruct_80024000 *);

void menuMainStateStep(MenuStruct_80024000 *arg0, s32 arg1) {
    s32 var_v0;

    switch (arg0->unk1) {
    case 0:
        if (func_80629148() != 0) {
            if (arg1 != 0) {
                func_80629174();
                func_8070D8C0(D_807FBB40, 0xB, 0);
                if ((var_v0 = arg0->unk1A) == 1) {
                    var_v0 = 1;
                } else if (var_v0 >= 2) {
                    var_v0 = 2;
                } else {
                    var_v0 = 3;
                }
                D_80750AC8 = arg0->unk1A;
                func_8070D8C0(D_807FBB40, 0xB, var_v0);
            } else {
                if (arg0->unk1A == 1) {
                    var_v0 = 5;
                } else {
                    var_v0 = 6;
                }
                D_80750AC8 = arg0->unk1A;
                func_8070D8C0(D_807FBB40, 0xB, var_v0);
            }
            arg0->unk1++;
        }
        break;
    case 1:
        if (!(D_807FBB40->unk60 & 0x02000000)) {
            func_8061CB08();
            arg0->unk1++;
        }
        break;
    case 2:
        if (func_80629148() != 0) {
            func_80629174();
            if (arg0->unk1A != 0) {
                func_8061CC40(0, 5, 1);
                arg0->unk1++;
            } else {
                arg0->unk0 = 4;
                arg0->unk1 = 0;
            }
        }
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        if (arg0->unk6 != 0) {
            if (arg0->unk6 == 1) {
                if (func_80629148() != 0) {
                    func_80629174();
                    arg0->unk6 = 2;
                }
            } else {
                menuUpdateFallingActor(arg0);
            }
        }
        if (func_80629148() != 0) {
            func_80629174();
            menuPlaySoundFromTable(arg0);
        }
        break;
    }
}

void menuTransitionStep(arg0, arg1)
MenuStruct_80024000 *arg0;
u8 arg1;
{
    switch (arg0->unk1) {
    case 0:
        if (func_80629148() != 0) {
            func_8070D8C0(D_807FBB40, 0xB, arg1);
            arg0->unk1++;
        }
        break;
    case 1:
        if (!(D_807FBB40->unk60 & 0x02000000)) {
            func_8061CB08();
            arg0->unk1++;
        }
        break;
    case 2:
        if (func_80629148() != 0) {
            func_80629174();
            arg0->unk0 = 4;
            arg0->unk1 = 0;
        }
        break;
    }
}

#ifndef WRITE_GFX
#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }
#endif

extern u8 D_1000118[];
extern u8 D_20000C0[];
extern u8 D_2000180[];

s32 _sprintf(char *, const char *, ...);
Gfx *hudDrawScaledText(Gfx *, s32, s32, f32, char *);
Gfx *func_806FC530(Gfx *, s32, s32, s32, char *, s32);
char *func_8070E750(s32, s32, s32);

#pragma GLOBAL_ASM("asm/menu/nonmatchings/0/func_800244EC.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/0/func_80024788.s")

s16 func_80712548(MenuStruct_80024000 *);

void menuProcessOptionInput(MenuStruct_80024000 *arg0) {
    switch (arg0->unk1) {
    case 0:
        if (func_80629148() != 0) {
            func_80629174(arg0);
            arg0->unk1++;
            D_80750AC8 = func_80712548(arg0);
            func_8070D8C0(D_807FBB40, 0xB, 8);
        }
        break;
    case 1:
        if (!(D_807FBB40->unk60 & 0x02000000)) {
            func_8061CB08();
            arg0->unk1++;
        }
        break;
    }
}

extern u8 D_80032F50;
extern u8 D_8074E77C;
extern s16 D_8076AEF2;

void func_806F397C(void *, s32, s32, s32);
void func_8073129C(s32, s32, s32);
s32 func_8073110C(s32, s32);
u8 func_80731AA8(s32, s32, s32);
u8 func_80731A04(s32, s32, s32, u8);
void func_80024788(MenuStruct_80024000 *);
void func_80729B00(void);
void func_806BFBF4(void);
void func_806319C4(void *, s32);

void menuDispatchAction(void) {
    s32 pad;
    s32 var_a3;
    s32 pad2;
    s32 sp20;
    register u8 var_v1;
    MenuStruct_80024000 *temp_s0;

    var_a3 = -1;
    var_v1 = 0;
    temp_s0 = D_807FBB40->unk180;
    if (!(D_807FBB40->unk60 & 0x10)) {
        sp20 = 1;
        temp_s0->unk2 = func_80731AA8(0x1FD, 0x28, 0);
        temp_s0->unk1A = func_80731A04(0x1D5, 0, 7, D_8074E77C);
        temp_s0->unk1A -= func_80731A04(0x1FD, 0, 7, D_8074E77C);
        if (D_8076AEF2 != 0x1C) {
            if (func_8073110C(0x174, 0) == 0) {
                temp_s0->unk0 = 0;
                temp_s0->unk1 = 0;
                sp20 = 0;
                func_806F397C(D_807FBB4C, 0, 0, 0);
                func_8073129C(0x174, 1, 0);
            } else {
                if (temp_s0->unk2 == 0x28) {
                    temp_s0->unk0 = 2;
                    temp_s0->unk1 = 0;
                } else {
                    if (temp_s0->unk1A == 0) {
                        temp_s0->unk0 = 1;
                        temp_s0->unk1 = 0;
                    } else {
                        temp_s0->unk0 = 3;
                        temp_s0->unk1 = 0;
                    }
                }
            }
            func_8061CC40(0, (s16)sp20, 1);
        } else {
            temp_s0->unk0 = 5;
            temp_s0->unk1 = 0;
        }
        func_80629174();
        menuSpawnPositionalActor(temp_s0);
        var_v1 = D_80032F50;
        D_80032F50 = 0;
    }
    switch (temp_s0->unk0) {
    case 0:
        menuMainStateStep(temp_s0, 1);
        break;
    case 3:
        menuMainStateStep(temp_s0, 0);
        break;
    case 1:
        var_a3 = 4;
        /* fallthrough */
    case 2:
        if (var_a3 < 0) {
            var_a3 = 7;
        }
        if (var_v1 != 0) {
            var_a3 = 0xB;
        }
        menuTransitionStep(temp_s0, var_a3);
        break;
    case 4:
        func_80024788(temp_s0);
        break;
    case 5:
        menuProcessOptionInput(temp_s0);
        break;
    }
    func_80729B00();
    func_806BFBF4();
    func_806319C4(D_807FBB40, 0);
}
#pragma GLOBAL_ASM("asm/menu/nonmatchings/0/func_80024EF0.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/0/func_800252AC.s")

void func_80025AE0(void) {
}
