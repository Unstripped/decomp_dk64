#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBD70;

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806B91E0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806B9CB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806B9CE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806B9EB4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806BA130.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806BA240.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806BA76C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806BA8C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806BA93C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806BB32C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806BB400.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806BB604.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806BB81C.s")

typedef struct L1View {
    /* 0x000 */ u8 pad0[0x130];
    /* 0x130 */ u8 unk130;
    /* 0x131 */ u8 unk131;
    /* 0x132 */ u8 pad132[0x22];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} L1View;
#define L1A ((L1View *)D_807FBB40)

typedef struct L1Tbl {
    u8 b[11];
} L1Tbl;

typedef struct L1S1C {
    u8 pad0[0x1C];
    s32 unk1C;
} L1S1C;

typedef struct L1P2C0 {
    u8 pad0[0x2C0];
    u8 unk2C0;
} L1P2C0;

typedef struct L1D1D8 {
    u8 pad0[0x1D8];
    f32 unk1D8;
} L1D1D8;

extern Actor *D_807FBB44;
extern L1S1C *D_807FDCA0;
extern L1P2C0 *D_807FC924;
extern L1D1D8 *D_807FD580;
extern s32 D_807FBB68;
extern s32 D_807F5D10;
extern L1Tbl D_80750638;

s32 func_80611A44(void);
void func_80729B00(void);
void func_80614EBC(void *, s32);
void func_806319C4(Actor *, s32);
s32 func_806BB604();
void func_806BB81C();
s32 func_80726D7C(s32);
void func_80641874(s32, s32);
f32 func_80612790(s16);
f32 func_80612794(s16);
s32 func_807271F4(s16, s16, s16, s16, s32, s32, s32);
void func_8061CC40(void *, s32, s32);
void func_8061C464(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_8061C458(s32, void *);
void func_806224CC(s32, void *);
void func_80726EE0(s32);
void func_806D0468(void *, s32);
void func_8063DA40(s32, s32);
void func_80686F90(s32, s16, s16);
void sfxAllocateChannel(s32, f32);
void sfxStopChannel();

void func_806BB874(void) {
    s16 i;
    s16 x;
    s16 y;
    L1Tbl tbl;
    u8 t;
    s32 w;

    x = (func_80611A44() >> 15) % 100 + 0x64;
    y = (func_80611A44() >> 15) % 250 + 0xC8;
    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        L1A->unk130 = 0x3C;
        L1A->unk131 = 0x3C;
        D_807FBB40->unk12A = 0x3E8;
        D_807FBB40->unk154 = 0;
        L1A->unk155 = 0;
        func_80614EBC(D_807FBB40, 0x3DC);
        D_807FDC90->unk2C = 0x78;
        D_807FBB40->unk64 |= 0x20;
    }
    switch (D_807FBB40->unk154) {
    case 0: {
        for (i = 0; i < D_807FBB70.unk254; i++) {
            if (D_807FBB70.unk258[i] == 3) {
                D_807FBB40->unk154++;
            }
        }
        break;
    }
    case 1:
        switch (L1A->unk155) {
        case 0:
            if (D_807FDC90->unk2C-- < 0x3C) {
                D_807FBB40->unk60 |= 0x400;
                func_80614EBC(D_807FBB40, 0x3DD);
                L1A->unk155++;
            }
            break;
        case 2:
            func_80686F90(0, (func_80611A44() >> 15) % 2048 + D_807FBB40->unkE6 - 0x400, (func_80611A44() >> 15) % 1024);
            break;
        case 3:
            D_807FBB68 |= 1;
            sfxAllocateChannel(0x68, 1.0f);
            D_807FDC90->unk2C = 0x32;
            func_806BB81C();
            D_807FBB40->unk154++;
            break;
        }
        break;
    case 2:
        if (func_806BB604(0x2A, x, y, 0) != 0) {
            D_807FBB40->unk154++;
        }
        break;
    case 3:
        if (func_80726D7C(0x2A) == 0) {
            D_807FDC90->unk2C = 0xA;
            D_807FBB40->unk154++;
        }
        break;
    case 4:
        func_806BB81C();
        func_806BB604(0x28, x, y, 0);
        if (func_806BB604(0x29, (s16)(x + 0x28), (s16)(y + 0x50), 0) != 0) {
            D_807FBB40->unk154++;
        }
        break;
    case 5:
        if (func_80726D7C(0x28) == 0 && func_80726D7C(0x29) == 0) {
            D_807FDC90->unk2C = 0xA;
            D_807FBB40->unk154++;
        }
        break;
    case 6:
        func_806BB81C();
        func_806BB604(0x2B, x, y, 0);
        if (func_806BB604(0x2C, (s16)(x + 0x28), (s16)(y + 0x50), 0) != 0) {
            D_807FBB40->unk154++;
        }
        break;
    case 7:
        if (func_80726D7C(0x2B) == 0 && func_80726D7C(0x2C) == 0) {
            func_80641874(0x11, 1);
            func_807271F4(0x2D, func_80612794(D_807FBB40->unkE6) * 80.0f + D_807FBB40->unk7C, D_807FBB40->unk80, func_80612790(D_807FBB40->unkE6) * 80.0f + D_807FBB40->unk84, D_807FBB40->unkE6, 0, 0);
            D_807FDCA0->unk1C = (s32)D_807FBB44;
            func_8061CC40(D_807FBB40, 0x1F, 1);
            D_807FBB40->unk154++;
            D_807FDC90->unk2C = 0x1E;
            L1A->unk155 = 0xA;
        }
        break;
    case 8:
        if (D_807FDC90->unk2C != 0) {
            D_807FDC90->unk2C--;
        } else {
            tbl = D_80750638;
            t = 0xA - L1A->unk155;
            if (L1A->unk155 == 0xA) {
                func_806BB81C();
            }
            if (L1A->unk155) {
                func_806BB604((u8)(tbl.b[L1A->unk155--] + 0x22), (s16)(t * 8 + 0x64), (s16)(t * 20 + 0xFA), D_807FDCA0->unk1C);
            } else {
                D_807FBB40->unk60 &= 0xFFFF7FFF;
                D_807FBB40->unk144 = 1;
                D_807FBB40->unk154++;
                func_8061C464(D_807F5D10, D_807FBB40, 4, 0x1129, 0x264, 0, 0, 0xAF, 0, 0, 1.0f);
                func_8061C458(D_807F5D10, D_807FBB4C);
            }
            D_807FDC90->unk2C = 0xF;
        }
        break;
    case 9: {
        w = D_807FBB40->unk128 - 0xA;
        if (w < 0) {
            D_807FBB40->unk128 = 0;
        } else {
            D_807FBB40->unk128 = w;
        }
        if (func_80726D7C(0x2D) == 0) {
            func_80641874(0x11, 0xFF);
            func_806224CC(D_807F5D10, D_807FBB4C);
            func_80726EE0(0);
            D_807FBB68 &= ~1;
            if (D_807FC924->unk2C0 != 1) {
                func_806D0468(D_807FBB4C, 1);
                D_807FD580->unk1D8 = 0.05f;
            }
            D_807FBB40->unk154++;
            sfxStopChannel(0x68, 0);
            func_8063DA40(0x7C, 0xA);
            D_807FBB4C->unk12A = 0x1F4;
            D_807FBB4C->unk60 &= ~0x400;
            D_807FBB40->unk144 = 0x24;
            func_8061CC40(D_807FBB40, 0x1F, 5);
        }
        break;
    }
    case 10: {
        w = D_807FBB40->unk128 + 0xA;
        if (w >= 0x100) {
            D_807FBB40->unk128 = 0xFF;
        } else {
            D_807FBB40->unk128 = w;
        }
        break;
    }
    }
    func_806319C4(D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806BC080.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806BC0E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806BC148.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806BC1AC.s")
