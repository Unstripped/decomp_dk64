#include "common.h"

typedef struct ArcadeEntity {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    void *unk14;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 unk1F;
} ArcadeEntity;

extern ArcadeEntity D_8004BCD0[];
extern ArcadeEntity D_8004C6D0;

extern s8 D_8004C71E;
extern u8 D_8004C71D;
extern u8 D_8004C71F;
extern u8 D_8004C721;
extern u8 D_8004C722;
extern u8 D_8004C724;
extern s32 D_8004C708;
extern s32 D_8004C6DC;
extern u8 D_8004A740;
extern u8 D_8004A76C;
extern s32 D_8004A308[];

void func_80024D90(void);
void func_80030FEC(void);
void func_800259D0(Gfx **);
void func_8002B2C0(Gfx **);
void func_8002AFA4(Gfx **, s32);
void func_80029968(void);

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80024000.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002419C.s")

void func_8060C648(s32, s32, u8, s32, s32);
s32 func_8060C6B8(s32, s32, u8, s32);
void func_8060DEA8(void);
extern s32 D_8004A74C[5];
extern u8 D_8004A778[5][3];
extern s32 D_8004A760;

void func_80024320(void) {
    s32 i;
    u8 temp;

    for (i = 0; i < 5; i++) {
        temp = i;
        func_8060C648(0x15, 0, temp, 0, D_8004A74C[i]);
        func_8060C648(0x12, 0, temp, 0, D_8004A778[i][0]);
        func_8060C648(0x13, 0, temp, 0, D_8004A778[i][1]);
        func_8060C648(0x14, 0, temp, 0, D_8004A778[i][2]);
    }
    D_8004A760 = D_8004A74C[0];
    func_8060DEA8();
}

void func_8002440C(void) {
    s32 i;
    u8 temp;

    for (i = 0; i < 5; i++) {
        temp = i;
        D_8004A74C[i] = func_8060C6B8(0x15, 0, temp, 0);
        D_8004A778[i][0] = func_8060C6B8(0x12, 0, temp, 0);
        D_8004A778[i][1] = func_8060C6B8(0x13, 0, temp, 0);
        D_8004A778[i][2] = func_8060C6B8(0x14, 0, temp, 0);
    }
    D_8004A760 = D_8004A74C[0];
}

extern u8 D_8004C725;
extern u8 D_8004C726;
extern u8 D_8004C727;
extern u8 D_8004C728;
void func_800244E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_8004C725 = arg0;
    D_8004C726 = arg1;
    D_8004C727 = arg2;
    D_8004C728 = arg3;
}

extern s32 D_8004C72C;
extern s32 D_8004C730;
void func_80024508(s32 arg0, s32 arg1) {
    D_8004C72C = arg0;
    D_8004C730 = arg1;
}

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002451C.s")

extern u32 D_8004A738;
s32 func_80024644(void) {
    D_8004A738 = D_8004A738 * 0x41C64E6D + 0x3039;
    return (D_8004A738 >> 16) & 0x7FFF;
}

extern s32 D_8004A748;
extern u8 D_8004C71B;
extern u8 D_8004C71C;
void func_80024674(s32 arg0) {
    s32 old = D_8004A748;
    D_8004A748 += arg0;
    if (D_8004A748 >= 0x2710 && old < 0x2710) {
        D_8004C71B++;
        D_8004C71C++;
    }
}

f32 func_800246C8(f32 arg0, f32 arg1) {
    if (arg1 < arg0) {
        return arg1;
    }
    return arg0;
}


s32 func_800246EC(void) {
    s32 i;
    for (i = 0; i < 0x50; i++) {
        if (D_8004BCD0[i].unk18 == 0) {
            return i;
        }
    }
    return 0;
}

s32 func_80024764(void) {
    s32 i;
    for (i = D_8004C71F + 1; i < 0x50; i++) {
        if (D_8004BCD0[i].unk18 == 0) {
            return i;
        }
    }
    return 0;
}
s32 func_800247B8(void) {
    s32 i;
    for (i = 0x4F; i >= 0; i--) {
        if (D_8004BCD0[i].unk18 == 0) {
            return i;
        }
    }
    return 0;
}

s32 func_800247F0(void) {
    s32 i;
    for (i = 0x27; i >= 0; i--) {
        if (D_8004BCD0[i].unk18 == 0) {
            return i;
        }
    }
    return 0;
}

s32 func_80024828(void) {
    s32 i;
    for (i = 0x24; i >= 0; i--) {
        if (D_8004BCD0[i].unk18 == 0) {
            return i;
        }
    }
    return 0;
}

s32 func_80024860(s32 arg0) {
    s32 i;
    for (i = 0; i < 0x50; i++) {
        if (arg0 == D_8004BCD0[i].unk18) {
            return i;
        }
    }
    return -1;
}

s32 func_800248D8(s32 arg0) {
    s32 i;
    s32 count = 0;
    for (i = 0; i < 0x50; i++) {
        if (arg0 == D_8004BCD0[i].unk18) {
            count++;
        }
    }
    return count;
}

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80024940.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80024A50.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80024B04.s")

s32 func_8073110C(s32, s32);
void func_8073129C(s32, s32, s32);
void func_805FF898(void);
void func_805FF378(s32, s32);
extern u8 D_8004A73C;
extern u8 D_8004A770;
void func_80024C34(void) {
    if (D_8004A73C == 0) {
        if (D_8004A770 != 0 && D_8004A740 != 0 && func_8073110C(0x84, 0) == 0) {
            if (func_8073110C(0x82, 0) != 0) {
                func_8073129C(0x11, 1, 2);
            } else {
                func_8073129C(0x10, 1, 2);
            }
        }
        if (D_8004A740 != 0) {
            func_805FF898();
        } else {
            func_805FF378(0x50, 0);
        }
        D_8004A73C = 1;
    }
}
void func_80024CF8(Gfx **arg0) {
    Gfx *sp1C = *arg0;
    D_8004C6DC++;
    func_800259D0(&sp1C);
    func_80030FEC();
    func_8002B2C0(&sp1C);
    if (D_8004C6DC >= 0x7BD) {
        if (D_8004A740 != 0) {
            func_80024C34();
        } else {
            func_80024D90();
        }
    }
    *arg0 = sp1C;
}

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80024D90.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80024E84.s")

void func_800257D8(void);
void func_800251D8(Gfx **arg0) {
    Gfx *sp1C = *arg0;
    func_80030FEC();
    func_800259D0(&sp1C);
    func_8002B2C0(&sp1C);
    if (D_8004C6DC++ >= 0x2F9) {
        func_800257D8();
    }
    *arg0 = sp1C;
}

extern s32 D_8004C714;
void func_80025240(void) {
    if (D_8004C722 == 1) {
        D_8004C714 = 0x4D;
    } else if (D_8004C722 == 2) {
        D_8004C714 = 0x4F;
    } else if (D_8004C722 == 4) {
        D_8004C714 = 0x4E;
    } else {
        D_8004C714 = -1;
    }
}

void n_alSndpDeallocate(s32);
extern s32 D_80770DF8;
void func_800252A4(s32 arg0) {
    D_8004C714 = arg0;
    if (D_80770DF8 != 0) {
        n_alSndpDeallocate(D_80770DF8);
    }
}

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800252D8.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002549C.s")

void func_800255A8(void) {
    s32 index;
    do {
        index = func_80024860(0x1C);
        if (index >= 0) {
            D_8004BCD0[index].unk18 = 0;
        }
    } while (index >= 0);
}

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800255F4.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800257D8.s")

void func_80025960(Gfx **arg0) {
    Gfx *sp1C = *arg0;
    func_800259D0(&sp1C);
    func_8002B2C0(&sp1C);
    if (D_8004C6DC++ >= 0xA1) {
        func_80029968();
        D_8004C724 = 5;
    }
    *arg0 = sp1C;
}

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800259D0.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80025C08.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80026050.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002628C.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800263EC.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80026518.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80026680.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800268AC.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80026EF4.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800274E0.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800275E8.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80027A38.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80027E8C.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80027F0C.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002843C.s")

extern s32 D_8004C6E0;
extern s32 D_8004C6E4;
extern s32 D_8004C6E8;
extern s32 D_8004C6EC;
extern s32 D_8004C6F0;
extern s32 D_8004C6F4;
extern s32 D_8004C6F8;


s32 func_80029ACC(s32, s32);
s32 func_80029CD0(s32, s32);
s32 func_80029EFC(s32, s32);
s32 func_8002A264(s32, s32);


s32 func_8002A474(s32, s32);
s32 func_8002A734(s32, s32);
s32 func_8002AA24(s32, s32);
s32 func_8002AC54(s32, s32);


void func_80005A90(void *, void *, s32, u8, u8, u8, s32, s32, s32, s32);
void func_8070E8F0(s32 *, void *);
void func_8070F2C8(s32, s16, s32, u8);
void func_8070F2FC(s32 *, s16, s16);
extern u8 D_8004A338[];
extern u8 D_8004A358[];
extern u8 D_8004A378[];
extern u8 D_8004AC00[];
extern u8 D_807444FC;

extern f32 D_8004BCD4;
extern f32 D_8004BCF4;

extern u8 D_80034610[];
extern u8 D_80034818[];
extern u8 D_80034A20[];
extern u8 D_80034C28[];
extern u8 D_80034E30[];
extern u8 D_80035038[];
extern u8 D_80035240[];
extern u8 D_80035448[];
extern u8 D_80035650[];
extern u8 D_80035898[];
extern u8 D_80035AE0[];
extern u8 D_80035CE8[];


extern u8 D_8004C723;
extern u8 D_8004A788[];
extern s32 D_8004C710;
extern u8 D_8004C718;
extern u8 D_8004A764;

void func_80027F0C(void);
void func_8002843C(void);
void func_800289F0(void);
void func_800290F0(void);

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800289F0.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800290F0.s")

void func_80029968(void) {
    s32 i;
    s32 temp;

    D_8004C708 = 0;
    D_8004C722 = D_8004A788[D_8004C723 & 3];
    for (i = 0; i < 80; i++) {
        D_8004BCD0[i].unk18 = 0;
    }
    switch (D_8004C722) {
    case 1:
        func_80027F0C();
        break;
    case 2:
        func_8002843C();
        break;
    case 3:
        func_800289F0();
        break;
    default:
        func_800290F0();
        break;
    }
    func_80025240();
    temp = D_8004A76C * 10 + 40;
    if (temp >= 91) {
        D_8004C71E = 90;
    } else {
        D_8004C71E = temp;
    }
    D_8004C710 = 0;
    D_8004C718 = 0xFF;
    D_8004A764 = 0;
    D_8004C6DC = 0;
    D_8004C71D = 1;
    D_8004C6F8 = 1;
    D_8004C721 = 1;
    D_8004A308[0] = 0;
    D_8004A308[1] = 0;
    D_8004A308[2] = 0;
    D_8004A308[3] = 0;
}

s32 func_80029ACC(s32 arg0, s32 arg1) {
    s32 ret;
    s32 temp;

    if (arg1 < 0x5D) {
        D_8004C6F0 = 0x88;
    } else {
        D_8004C6F0 = 0x36;
    }
    D_8004C6F4 = 0x10A;

    if (arg1 < 0x3F) {
        D_8004C6F8 = 0;
        if (arg0 >= 0x85 && arg0 < 0xBC) {
            ret = 0x37;
        } else {
            ret = 0xF8;
        }
    } else if (arg1 < 0x5D) {
        D_8004C6F8 = 1;
        temp = arg0 / 16;
        ret = temp;
        if (temp < 0xB) {
            ret = 0xB;
        }
        ret += 0x48;
        if (arg0 >= 0x105) {
            ret = 0xF8;
        }
    } else if (arg1 < 0x7F) {
        D_8004C6F8 = 2;
        ret = 0x7C - (arg0 / 16);
        if (arg0 < 0x3C) {
            ret = 0xF8;
        }
    } else if (arg1 < 0xA0) {
        D_8004C6F8 = 3;
        ret = (arg0 / 16) + 0x8A;
        if (arg0 >= 0x105) {
            ret = 0xF8;
        }
    } else if (arg1 < 0xC3) {
        D_8004C6F8 = 4;
        ret = 0xBE - (arg0 / 16);
        if (arg0 < 0x3C) {
            ret = 0xF8;
        }
    } else if (arg1 < 0xE1) {
        D_8004C6F8 = 5;
        ret = (arg0 / 16) + 0xCC;
        if (arg0 >= 0x105) {
            ret = 0xF8;
        }
    } else {
        D_8004C6F8 = 6;
        ret = 0x100 - (arg0 / 16);
        if (ret >= 0xF8) {
            ret = 0xF7;
        }
    }

    if (ret < arg1) {
        D_8004C6F8++;
    }
    return ret;
}

s32 func_80029CD0(s32 arg0, s32 arg1) {
    s32 ret;

    D_8004C6F0 = 0x36;
    D_8004C6F4 = 0x10A;
    if (arg1 < 0x6E) {
        D_8004C6F8 = 1;
        if (arg0 >= 0x4D && arg0 < 0xF4 &&
            (arg0 < 0x6C || arg0 >= 0x6D || (D_8004C718 & 0x40)) &&
            (arg0 < 0xD4 || arg0 >= 0xD5 || (D_8004C718 & 0x80))) {
            ret = 0x5D;
        } else {
            ret = 0xF7;
        }
    } else if (arg1 < 0x8C) {
        D_8004C6F8 = 2;
        if (arg0 >= 0x45 && arg0 < 0xFC &&
            (arg0 < 0x6C || arg0 >= 0x6D || (D_8004C718 & 0x10)) &&
            (arg0 < 0xD4 || arg0 >= 0xD5 || (D_8004C718 & 0x20))) {
            ret = 0x84;
        } else {
            ret = 0xF7;
        }
    } else if (arg1 < 0xBE) {
        D_8004C6F8 = 3;
        if (arg0 >= 0x3D && arg0 < 0x104 &&
            (arg0 < 0x6C || arg0 >= 0x6D || (D_8004C718 & 4)) &&
            (arg0 < 0xD4 || arg0 >= 0xD5 || (D_8004C718 & 8))) {
            ret = 0xAA;
        } else {
            ret = 0xF7;
        }
    } else if (arg1 < 0xDC) {
        D_8004C6F8 = 4;
        if ((arg0 < 0x6C || arg0 >= 0x6D || (D_8004C718 & 1)) &&
            (arg0 < 0xD4 || arg0 >= 0xD5 || (D_8004C718 & 2))) {
            ret = 0xD0;
        } else {
            ret = 0xF7;
        }
    } else {
        D_8004C6F8 = 5;
        ret = 0xF7;
    }

    if (ret < arg1) {
        D_8004C6F8++;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80029EFC.s")

s32 func_8002A264(s32 arg0, s32 arg1) {
    s32 ret;

    D_8004C6F0 = 0x36;
    D_8004C6F4 = 0x10A;
    if (arg1 < 0x6E) {
        D_8004C6F8 = 0;
        ret = 0x57;
    } else if (arg1 < 0x8C) {
        if (arg0 < 0x9C) {
            ret = 0x7F;
            D_8004C6F8 = 1;
        } else if (arg0 >= 0xA5) {
            ret = 0x7F;
            D_8004C6F8 = 2;
        } else {
            ret = 0xF7;
        }
    } else if (arg1 < 0xBE) {
        D_8004C6F8 = 4;
        if ((arg0 < 0x64 || arg0 >= 0x6D) && (arg0 < 0xCC || arg0 >= 0xD5)) {
            ret = 0xA7;
        } else {
            ret = 0xF7;
        }
    } else if (arg1 < 0xDC) {
        D_8004C6F8 = 3;
        ret = 0xCF;
    } else {
        D_8004C6F8 = 5;
        ret = 0xF7;
    }
    if (ret < arg1) {
        D_8004C6F8++;
    }
    return ret;
}

s32 func_8002A390(s32 arg0, s32 arg1) {
    if (D_8004C722 == 1) {
        return func_80029ACC(arg0, arg1);
    } else if (D_8004C722 == 2) {
        return func_80029CD0(arg0, arg1);
    } else if (D_8004C722 == 3) {
        return func_80029EFC(arg0, arg1);
    } else {
        return func_8002A264(arg0, arg1);
    }
}

s32 func_8002A408(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if ((arg1 >= arg3) & (arg5 >= arg1) & ((arg2 - 4) < arg0) & (arg0 < (arg2 + 3))) {
        D_8004C6E0 = arg2;
        D_8004C6E4 = arg3;
        D_8004C6E8 = arg5;
        D_8004C6EC = arg4;
        return 1;
    }
    return 0;
}

s32 func_8002A474(s32 arg0, s32 arg1) {
    if (func_8002A408(arg0, arg1, 0x84, 0xD4, 0xEB, 0xF7)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0xEC, 0xDA, 0xDA, 0xF2)) {
        return 2;
    }
    if (func_8002A408(arg0, arg1, 0x94, 0xB5, 0xB5, 0xD5)) {
        return 3;
    }
    if (func_8002A408(arg0, arg1, 0x54, 0xB9, 0xB9, 0xD1)) {
        return 4;
    }
    if (func_8002A408(arg0, arg1, 0x74, 0x91, 0xAB, 0xB7)) {
        return 5;
    }
    if (func_8002A408(arg0, arg1, 0xAC, 0x94, 0x94, 0xB4)) {
        return 6;
    }
    if (func_8002A408(arg0, arg1, 0xEC, 0x98, 0x98, 0xB0)) {
        return 7;
    }
    if (func_8002A408(arg0, arg1, 0xDC, 0x6F, 0x8B, 0x97)) {
        return 8;
    }
    if (func_8002A408(arg0, arg1, 0x7C, 0x75, 0x75, 0x91)) {
        return 9;
    }
    if (func_8002A408(arg0, arg1, 0x54, 0x77, 0x77, 0x8F)) {
        return 10;
    }
    if (func_8002A408(arg0, arg1, 0x8C, 0x53, 0x64, 0x74)) {
        return 11;
    }
    if (func_8002A408(arg0, arg1, 0xEC, 0x56, 0x56, 0x6E)) {
        return 12;
    }
    if (func_8002A408(arg0, arg1, 0xB4, 0x37, 0x37, 0x53)) {
        return 13;
    }
    D_8004C6E0 = 0;
    D_8004C6E4 = 0x12C;
    D_8004C6EC = 0x12C;
    D_8004C6E8 = 1;
    return 0;
}

s32 func_8002A734(s32 arg0, s32 arg1) {
    if (func_8002A408(arg0, arg1, 0x3C, 0xD0, 0xD0, 0xF7)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0x9C, 0xD0, 0xD0, 0xF7)) {
        return 2;
    }
    if (func_8002A408(arg0, arg1, 0x104, 0xD0, 0xD0, 0xF7)) {
        return 3;
    }
    if (func_8002A408(arg0, arg1, 0x44, 0xAA, 0xAA, 0xD0)) {
        return 4;
    }
    if (func_8002A408(arg0, arg1, 0x7C, 0xAA, 0xAA, 0xD0)) {
        return 5;
    }
    if (func_8002A408(arg0, arg1, 0xC4, 0xAA, 0xAA, 0xD0)) {
        return 6;
    }
    if (func_8002A408(arg0, arg1, 0xFC, 0xAA, 0xAA, 0xD0)) {
        return 7;
    }
    if (func_8002A408(arg0, arg1, 0x4C, 0x84, 0x84, 0xAA)) {
        return 8;
    }
    if (func_8002A408(arg0, arg1, 0x9C, 0x84, 0x84, 0xAA)) {
        return 9;
    }
    if (func_8002A408(arg0, arg1, 0xF4, 0x84, 0x84, 0xAA)) {
        return 10;
    }
    if (func_8002A408(arg0, arg1, 0x54, 0x5D, 0x5D, 0x84)) {
        return 11;
    }
    if (func_8002A408(arg0, arg1, 0x74, 0x5D, 0x5D, 0x84)) {
        return 12;
    }
    if (func_8002A408(arg0, arg1, 0xCC, 0x5D, 0x5D, 0x84)) {
        return 13;
    }
    if (func_8002A408(arg0, arg1, 0xEC, 0x5D, 0x5D, 0x84)) {
        return 14;
    }
    D_8004C6E0 = 0;
    D_8004C6E4 = 0x12C;
    D_8004C6EC = 0x12C;
    D_8004C6E8 = 1;
    return 0;
}

s32 func_8002AA24(s32 arg0, s32 arg1) {
    if (func_8002A408(arg0, arg1, 0xB4, 0x37, 0x37, 0x57)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0xD4, 0x57, 0x57, 0x77)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0x104, 0x67, 0x67, 0x8F)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0xBC, 0x7F, 0x7F, 0x9F)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0xEC, 0x8F, 0x8F, 0xAF)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0x104, 0xB7, 0xB7, 0xCF)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0x44, 0x87, 0x87, 0xBF)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0x74, 0x87, 0x87, 0xCF)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0x84, 0x87, 0x87, 0xCF)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0x3C, 0xBF, 0xBF, 0xE7)) {
        return 1;
    }
    D_8004C6E0 = 0;
    D_8004C6E4 = 0x12C;
    D_8004C6EC = 0x12C;
    D_8004C6E8 = 1;
    return 0;
}

s32 func_8002AC54(s32 arg0, s32 arg1) {
    s32 var_v0;
    if (func_8002A408(arg0, arg1, 0x4C, 0xCF, 0xCF, 0xF7)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0x84, 0xCF, 0xCF, 0xF7)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0xBC, 0xCF, 0xCF, 0xF7)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0xF4, 0xCF, 0xCF, 0xF7)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0x74, 0xA7, 0xA7, 0xCF)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0xC4, 0xA7, 0xA7, 0xCF)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0x4C, 0x7F, 0x7F, 0xA7)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0x84, 0x7F, 0x7F, 0xA7)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0xBC, 0x7F, 0x7F, 0xA7)) {
        return 1;
    }
    if (func_8002A408(arg0, arg1, 0xF4, 0x7F, 0x7F, 0xA7)) {
        return 1;
    }
    var_v0 = (s32) D_8004BCD4;
    if (var_v0 == 0x61) {
        var_v0 = 0x57;
    } else {
        var_v0 = 0x74;
    }
    if (func_8002A408(arg0, arg1, 0x44, 0x57, var_v0, 0x7F)) {
        return 1;
    }
    var_v0 = (s32) D_8004BCF4;
    if (var_v0 == 0x61) {
        var_v0 = 0x57;
    } else {
        var_v0 = 0x74;
    }
    if (func_8002A408(arg0, arg1, 0xFC, 0x57, var_v0, 0x7F)) {
        return 1;
    }
    D_8004C6E0 = 0;
    D_8004C6E4 = 0x12C;
    D_8004C6EC = 0x12C;
    D_8004C6E8 = 1;
    return 0;
}

s32 func_8002AF2C(s32 arg0, s32 arg1) {
    if (D_8004C722 == 1) {
        return func_8002A474(arg0, arg1);
    } else if (D_8004C722 == 2) {
        return func_8002A734(arg0, arg1);
    } else if (D_8004C722 == 3) {
        return func_8002AA24(arg0, arg1);
    } else {
        return func_8002AC54(arg0, arg1);
    }
}

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002AFA4.s")

void func_8002B2C0(Gfx **arg0) {
    s32 i;
    Gfx *sp38;
    sp38 = *arg0;
    for (i = 0; i < 80; i++) {
        if (D_8004BCD0[i].unk18 != 0 && D_8004BCD0[i].unk14 != 0) {
            if (D_8004BCD0[i].unk18 >= 8 || D_8004C71D < 2) {
                func_8002AFA4(&sp38, i);
            }
        }
    }
    *arg0 = sp38;
}

s32 func_8002B378(s32 arg0) {
    if (arg0 >= 0) {
        return arg0;
    }
    return -arg0;
}

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002B390.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002B89C.s")

void func_8002CBD8(s32 arg0) {
    ArcadeEntity *ptr = &D_8004BCD0[arg0];
    s32 val = (s32)ptr->unk10;

    if (ptr->unk19 == 5 || ptr->unk19 == 7 || ptr->unk19 == 1) {
        if (ptr->unk1D != 0) {
            switch (val & 1) {
            case 0:
                ptr->unk14 = D_80035AE0;
                return;
            case 1:
                ptr->unk14 = D_80035CE8;
                return;
            }
        } else {
            switch (val & 1) {
            case 0:
                ptr->unk14 = D_80035650;
                return;
            case 1:
                ptr->unk14 = D_80035898;
                return;
            }
        }
    } else {
        if (ptr->unk1D != 0) {
            switch (val & 3) {
            case 0:
                ptr->unk14 = D_80035448;
                return;
            case 1:
                ptr->unk14 = D_80035240;
                return;
            case 2:
                ptr->unk14 = D_80035038;
                return;
            case 3:
                ptr->unk14 = D_80034E30;
                return;
            }
        } else {
            switch (val & 3) {
            case 0:
                ptr->unk14 = D_80034C28;
                return;
            case 1:
                ptr->unk14 = D_80034A20;
                return;
            case 2:
                ptr->unk14 = D_80034818;
                return;
            case 3:
                ptr->unk14 = D_80034610;
                return;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002CD64.s")

extern s8 D_8004A768;
extern u8 D_80037B98[];
extern u8 D_80037DA0[];
extern u8 D_80037FA8[];
extern u8 D_8003E438[];
extern u8 D_800383B8[];
extern u8 D_800385C0[];
extern u8 D_800387C8[];
extern u8 D_80039D18[];
extern u8 D_80039F60[];
extern u8 D_8003A1A8[];
extern u8 D_8003A3F0[];
extern u8 D_8003AE58[];
extern u8 D_800389D0[];
extern u8 D_8003DB18[];
extern u8 D_8003DD60[];
extern u8 D_80038BD8[];
extern u8 D_8003E680[];
extern u8 D_8003E868[];
extern s32 D_8076D1F8;
void n_alSndpAllocate(s32, s32, s32, s32, f32, s32, s32);
#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002D6FC.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002E158.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002E3D4.s")

void func_8002E6E0(s32 arg0) {
    ArcadeEntity *entry = &D_8004BCD0[arg0];

    if (D_8004C722 == 2) {
        entry->unk1A = D_8004BCD0[D_8004C71F].unk0 < 160.0f;
        entry->unk0 = 152.0f;
        if (D_8004C708 == 2) {
            entry->unk1A = 0;
            entry->unk4 = 63.0f;
        }
    }
    if (D_8004C721 == 0) {
        entry->unk14 = NULL;
    } else {
        entry->unk14 = D_8003E438;
    }
}

void func_8002E794(s32 arg0) {
    ArcadeEntity *entry = &D_8004BCD0[arg0];

    if (D_8004C722 == 2) {
        entry->unk1A = D_8004BCD0[D_8004C71F].unk0 < 160.0f;
        entry->unk0 = 152.0f;
        if (D_8004C708 == 2) {
            entry->unk1A = 0;
            entry->unk4 = 79.0f;
        }
    }
    if (D_8004C721 == 0) {
        entry->unk14 = NULL;
        return;
    }
    if (entry->unk14 == NULL) {
        entry->unk14 = D_8003DB18;
    }
    if (D_8004C71D == 0) {
        if ((entry->unk1C++ & 0xC8) || (D_8004C724 == 1)) {
            entry->unk14 = D_8003DB18;
        } else {
            entry->unk14 = D_8003DD60;
        }
    }
}

void func_8002E8A0(s32 arg0) {
    D_8004BCD0[arg0].unk14 = D_8003AE58;
    if (D_8004C721 != 0) {
        D_8004BCD0[arg0].unk4 = D_8004BCD0[func_80024860(0x1A)].unk4 - 8.0f;
        D_8004BCD0[arg0].unk0 = D_8004BCD0[func_80024860(0x1A)].unk0;
    } else {
        if (D_8004BCD0[arg0 - 1].unk14 == NULL) {
            D_8004BCD0[arg0].unk14 = NULL;
        }
        D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0 - 1].unk4 + 20.0f;
        D_8004BCD0[arg0].unk0 = D_8004BCD0[arg0 - 1].unk0 + 30.0f;
    }
    D_8004BCD0[func_80024860(0x1A)].unk14 = NULL;
    D_8004BCD0[func_80024860(0x1B)].unk14 = NULL;
    if (func_80024860(0x1D) >= 0 && D_8004BCD0[func_80024860(0x1D)].unk14 != D_800389D0) {
        D_8004BCD0[func_80024860(0x1D)].unk14 = NULL;
    }
}
#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002E9DC.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002EB40.s")
#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002EC04.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002EEB8.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002F82C.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002FE28.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80030044.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80030210.s")

void func_800302B4(s32 arg0) {
    if (D_8004BCD0[arg0].unk0 == (f32)(s32)D_8004BCD0[D_8004C71F].unk0 &&
        D_8004BCD0[arg0].unk4 == (f32)(s32)D_8004BCD0[D_8004C71F].unk4) {
        D_8004BCD0[arg0].unk18 = 0x14;
        if (D_8004A76C == 1) {
            D_8004BCD0[arg0].unk14 = D_800383B8;
            func_80024674(0x12C);
        } else if (D_8004A76C == 2) {
            D_8004BCD0[arg0].unk14 = D_800385C0;
            func_80024674(0x1F4);
        } else {
            D_8004BCD0[arg0].unk14 = D_800387C8;
            func_80024674(0x320);
        }
    }
}

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800303B8.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80030734.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80030880.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80030A04.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80030B08.s")

void func_80030C70(u8 arg0) {
    s32 temp_v1;

    if (460.0f < D_8004BCD0[func_80024860(0x17)].unk10) {
        return;
    }
    temp_v1 = D_8004BCD0[arg0].unk1C;
    D_8004BCD0[arg0].unk1C = (D_8004BCD0[arg0].unk1A = (temp_v1 / 8) & 1, temp_v1 + 1);
}

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80030CEC.s")

void func_80030FB0(u8 arg0) {
    if (D_8004BCD0[arg0].unk1C >= D_8004C71E) {
        D_8004BCD0[arg0].unk18 = 0;
    }
}

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80030FEC.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800311E0.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800313B8.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8003159C.s")

void func_80031948(s8 arg0) {
    if (arg0 == D_8004A768) {
        func_800244E4(0xFF, 0xFF, 0xFF, 0xFF);
    } else if (D_8004C722 == 2) {
        func_800244E4(0xFF, 0xA0, 0x10, 0xFF);
    } else {
        func_800244E4(0, 0xFF, 0xFF, 0xFF);
    }
}

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800319D4.s")
