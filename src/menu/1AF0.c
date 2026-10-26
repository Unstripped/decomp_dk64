#include "common.h"
s32 flagGet(s16, s32);

typedef struct {
    char pad0[4];
    s16 unk4;
    char pad6[4];
    u8 unkA;
    s8 unkB;
    char padC[1];
    u8 unkD;
    u8 unkE;
    u8 unkF;
    char pad10[1];
    u8 unk11;
} Struct_80025D14;

extern u8 D_807FC950[][0x5E];
extern u8 D_8074E77C;

#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/func_80025AF0.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/D_80033A50.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/D_80033A78.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/func_80025B64.s")


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

#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/func_80025E04.s")


#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/func_80025FB4.s")

s32 func_806F8AD4(s32, s32);

s32 menuGetOptionAvailability(Struct_80025D14 *arg0, s32 arg1) {
    s32 ret = 0;

    arg0->unkF = 3;
    if (arg0->unkB >= 0) {
        s32 val = func_806F8AD4(1, 0);
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

#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/func_80026250.s")

void menuResetSubmenuState(s8 *arg0, s32 *arg1) {
    *arg1 = 0;
    arg0[0xF] = 1;
    arg0[0xB] = -1;
}

#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/func_800262A8.s")

void func_800262A8(Struct_80025D14 *, void *, s32);
void func_8061CB08(void);

void menuDispatchSubmenuAction(Struct_80025D14 *arg0, void *arg1, s32 arg2) {
    switch (arg0->unkE) {
    case 0:
        func_800262A8(arg0, arg1, arg2);
        break;
    case 1:
        if (!(D_807FBB40->unk60 & 0x02000000)) {
            arg0->unkE = 0;
            arg0->unkD = arg0->unkF;
            func_8061CB08();
        }
        break;
    }
}


extern void *D_807FBB4C;
void func_806F397C(void *, void *, s32, s32);
void func_8061CC40(s32, s32, s32);
void func_80629174(void);
void func_80025FB4(void *, void *, s32);
void playerStateQueueCallback(s32, void *, s32);

s32 menuExitSubmenu(Struct_80025D14 *arg0, void *arg1, s32 arg2) {
    s32 flag = flagGet((s16)arg2, 0) == 0;

    func_80025FB4(arg0, arg1, flag);
    arg0->unkD = 0;
    arg0->unkE = 0;
    if (flagGet(0x61, 2) == 0) {
        if (flag != 0) {
            func_806F397C(D_807FBB4C, D_807FBB40, 0, 0x1B);
            func_8061CC40(0, 0, 1);
        } else {
            func_8061CC40(0, 4, 1);
            playerStateQueueCallback(0x1B, D_807FBB40, 0);
        }
    } else {
        playerStateQueueCallback(0x1B, D_807FBB40, 0);
        func_8061CC40(0, 0xB, 1);
    }
    func_80629174();
    D_807FBB40->unk60 |= 0x10000000;
    return flag;
}



void menuTransitionToSubmenu(Struct_80025D14 *arg0, void *arg1) {
    arg0->unkA = 1;
    func_8061CC40(0, 0xF, 1);
    func_80629174();
    func_80025FB4(arg0, arg1, 0);
    arg0->unkD = 0;
    arg0->unkE = 0;
    playerStateQueueCallback(0x1B, D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/func_80026874.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/func_80026B28.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/func_80026DAC.s")

void func_80026874(Struct_80025D14 *, void *, s32);
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

#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/func_800270E0.s")

s32 menuDecodeAddressConstant(s32 arg0) {
    return arg0 + 0x21F44F;
}



extern s32 D_8063FA48;
void controllerUpdate(void);
void controllerLatchPad(void);
extern s32 D_8076A0A8;
void behaviourFrameBegin(void);
void func_806BFBF4(void);
void func_806319C4(void *, s32);

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
                dest = (s32 *)menuDecodeAddressConstant((s32)&D_8063FA48 + 0xFFDE0BB1);
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
    func_806319C4(D_807FBB40, 0);
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
    func_806319C4(D_807FBB40, 0);
}


extern Gfx D_1000118[];
extern Mtx D_2000180;
typedef struct { s16 unk0; s16 unk2; } Struct_8003353C;
extern Struct_8003353C D_8003353C[];
Gfx *func_806FC530(Gfx *, s16, s32, s32, s32, s32);

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
            dl = func_806FC530(dl, D_8003353C[i].unk2, 0, 0, fp->unk0[i], 0x80);
            gSPPopMatrix(dl++, G_MTX_MODELVIEW);
        }
    }
    return dl;
}


#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/func_80027988.s")

void func_80027988(void);

void func_80027DEC(void) {
    func_80027988();
}
