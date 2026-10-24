#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBD70;

typedef struct L5Node {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} L5Node;

typedef struct L5Sub1C {
    /* 0x00 */ u8 pad0[6];
    /* 0x06 */ u16 unk6;
} L5Sub1C;

typedef struct L5Sub4 {
    /* 0x00 */ L5Node *unk0;
    /* 0x04 */ u8 pad4[0x18];
    /* 0x1C */ L5Sub1C *unk1C;
} L5Sub4;

typedef struct L5View {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ L5Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x68];
    /* 0x070 */ s16 unk70;
    /* 0x072 */ u8 pad72[0x106];
    /* 0x178 */ s16 *unk178;
} L5View;

#define L5A ((L5View *)D_807FBB40)

typedef struct L5View90 {
    /* 0x00 */ u8 pad0[0x2E];
    /* 0x2E */ s16 unk2E;
} L5View90;

#define L590 ((L5View90 *)D_807FDC90)

typedef struct L5View9C {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
} L5View9C;

#define L59C ((L5View9C *)D_807FDC9C)

extern u8 D_80770629[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];

void func_8072B79C(s32, s32, s32);
void func_80724CA4(s32, s32);
void actorClearNodeFlag(void *, s32);
void func_8072D714(s32, s32);
void func_8072DEA8();
void func_8072DE44();
void func_8072B324(Actor *, s32);
void func_80614EBC(void *, s32);
s32 func_8072AB74(u8, f32, f32, s32, f32);
void func_8072A450();
s32 func_80611A44(void);
void func_8072B330();
s32 func_8072E54C();
s32 func_8072DE10(u16);
void func_8072DC7C(s32);
void func_8072B7CC();
void func_80729B00(void);
void func_8072C918(s32, s32, s32);
void func_8072D13C(u32, s32);
void func_806319C4(Actor *, s32);
void sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void sfxSpawnTableNodes(void *);
void sfxStopSlotSound(Actor *, s32);

void func_806B91E0(void) {
    u16 sp36 = 0;
    s16 *sp30 = L5A->unk178;

    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_8072B79C(0x321, 0x322, 0x323);
        func_80724CA4(0x11, 1);
        actorClearNodeFlag(D_807FBB40, 4);
        *sp30 = L59C->unkA * 10;
    }
    if ((D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) && D_807FBB40->unk154 != 0x37) {
        D_807FDC90->unk2C = 0x1388;
        func_8072D714(D_807FBB70.unk1FC, 0x327);
        D_807FBB40->unk138 &= 0xFFFF7FFF;
    } else if (D_807FBB70.unk200 == 4) {
        func_8072DEA8(0x325, 0x31, D_807FBB70.unk1FC);
    } else if (D_807FBB70.unk200 == 5) {
        func_8072DEA8(0x326, 0x31, D_807FBB70.unk1FC);
    }
    switch (D_807FBB40->unk154) {
    case 0x18:
        switch (D_807FBB40->unk155[0]) {
        case 0:
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
            } else {
                D_807FBB40->unk155[0]++;
                D_807FDC90->unk2C = 0xD;
            }
            L5A->unk4->unk1C->unk6 += 0x7D0;
            break;
        case 1:
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
                break;
            }
            if (L590->unk2E != 0) {
                D_807FBB40->unk155[0] = 0;
                L590->unk2E--;
                D_807FDC90->unk2C = 0xA;
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1BA, 0x96, 0x7F, 0);
                break;
            }
            func_8072DE44(0x322);
            break;
        }
        break;
    case 0x31:
        if ((D_807FBB40->unk155[0] != 0) || (L5A->unk4->unk0->unk24 == 0.0f)) {
            func_8072DE44(0x322);
        }
        func_8072AB74(0, 0.0f, 0.0f, 0x4300, 0.0f);
        break;
    case 0x11:
        switch (D_807FBB40->unk155[0]) {
        case 0:
            func_8072B324(D_807FBB40, 0);
            func_80614EBC(D_807FBB40, 0x321);
            D_807FBB40->unk155[0]++;
        case 1:
            func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
            if (D_807FBB40->unkB8 < 1.0f) {
                D_807FBB40->unk155[0]++;
            }
            break;
        case 2:
            func_8072A450();
            if ((func_80611A44() >> 15) % 1000 >= 0x3E4) {
                func_8072DE44(0x322);
            }
            break;
        }
        break;
    case 0x27:
        L5A->unk4->unk1C->unk6 -= D_807FBB40->unkB8 * 50.0f;
        func_8072AB74(0x23, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
        switch (D_807FBB40->unk155[0]) {
        case 0:
            func_8072B324(D_807FBB40, 0);
            func_80614EBC(D_807FBB40, 0x324);
            D_807FBB40->unk155[0] = 1;
            break;
        case 2:
            D_807FBB40->unk132 = 2;
            break;
        case 3:
            D_807FBB40->unk132 = 1;
            break;
        case 4:
            func_8072DE44(0x322);
            break;
        }
        break;
    case 1:
        if (func_8072E54C() != 0) {
            D_807FBB40->unk154 = 0x11;
            D_807FBB40->unk155[0] = 0;
        }
    case 0x23:
        if (D_807FBB70.unk200 == 2) {
            if (func_8072DE10(0x2710) != 0) {
                D_807FBB40->unk154 = 0x27;
                D_807FBB40->unk155[0] = 0;
            }
        }
    case 0x10:
        if ((D_807FBB40->unk154 != 0x11) && (D_807FBB40->unk154 != 0x27)) {
            if (D_807FBB40->unk155[0] == 0) {
                *sp30 = L59C->unkA * 2;
                D_807FBB40->unk155[0] = 1;
            }
            if (*sp30 != 0) {
                (*sp30)--;
            } else {
                sp36 = 0x20;
                func_8072B330(0);
                if (D_807FBB40->unkB8 != 0.0f) {
                    D_807FBB40->unkB8 = D_807FBB40->unkB8 - 1.0f;
                } else {
                    D_807FBB40->unk154 = 0x18;
                    D_807FBB40->unk155[0] = 0;
                    D_807FBB40->unk155[0] = 1;
                    D_807FDC90->unk2C = 0;
                    L590->unk2E = 4;
                }
            }
        }
        L5A->unk4->unk1C->unk6 -= D_807FBB40->unkB8 * 50.0f;
        func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, sp36, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        func_8072AB74(D_807FBB40->unk154, (f32)D_807FDC90->unkA, (f32)D_807FDC90->unkE, 0, 0.0f);
        break;
    case 0x37:
        L5A->unk4->unk1C->unk6 -= D_807FDC90->unk2C;
        if (D_807FDC90->unk2C != 0) {
            D_807FDC90->unk2C -= 0x32;
        }
        switch (D_807FBB40->unk155[0]) {
        case 0:
            func_8072AB74(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 1:
            sfxSpawnTableNodes(D_807FBB40);
            D_807FBB40->unk155[0]++;
        case 2:
            func_8072AB74(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            func_8072DC7C(8);
            break;
        case 3:
            D_807FBB40->unk154 = 0x40;
            break;
        }
        break;
    case 0x40:
        break;
    default:
        func_8072B7CC(0x322);
        break;
    }
    if (D_807FBB40->unkB8 != 0.0f) {
        if (L5A->unk70 == -1) {
            sfxPlayActorSound(D_807FBB40, 0x10A, 0, 1, 1, 0xFF, 1.0f, 0);
        } else {
            f64 t = ((f64)D_807FBB40->unkB8 * 0.6) / 40.0;
            u8 idx = D_80770629[L5A->unk70 * 2];

            D_80770B68[idx] = (t < 0.0 ? 0.0 : t) + 0.4;
            D_80770BC0[idx] = 1.0f;
        }
    } else {
        sfxStopSlotSound(D_807FBB40, 1);
    }
    switch (D_807FBB40->unk154) {
    case 0x31:
    case 0x37:
    case 0x40:
        break;
    case 2:
    case 3:
        func_8072D13C(D_807FBB40->unk154, 1);
    default:
        func_8072C918(0x57E4, 0x322, 0x323);
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806B9CB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806B9CE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806B9EB4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806BA130.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806BA240.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806BA76C.s")


void func_806BA8C8(void) {
    u8 arg = D_807FBB40->unk154;
    s32 sel = arg;

    switch (sel) {
        case 0x15:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            func_8072D13C(arg, 0);
        default:
            func_8072C918(0x2710, 0, 0);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/BDEE0/func_806BA93C.s")

typedef struct R1EView90 {
    /* 0x00 */ u8 pad0[0x2E];
    /* 0x2E */ s16 unk2E;
} R1EView90;

#define R1E90 ((R1EView90 *)D_807FDC90)

void func_806B9CE0();

void func_806BB32C(void) {
    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk16A = 0xFA;
        D_807FBB40->unk16B = 0xFA;
        D_807FBB40->unk16C = 0xFA;
    }
    if (D_807FBB40->unk154 == 0x17) {
        func_806B9CE0(0, 0);
    }
    if (R1E90->unk2E != 0) {
        R1E90->unk2E--;
        D_807FBB40->unkFC = 0;
        if (R1E90->unk2E == 0 && D_807FDC94 == D_807FBB4C) {
            D_807FBB40->unk144 = 0x24;
        }
    }
}

typedef struct L1S1C {
    u8 pad0[0x1C];
    s32 unk1C;
    u8 unk20;
} L1S1C;

extern L1S1C *D_807FDCA0;

typedef struct R1EView4 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} R1EView4;

typedef struct R1EView98 {
    /* 0x00 */ u8 pad0[0x28];
    /* 0x28 */ u16 unk28;
} R1EView98;

void func_806D0430(f32);
void func_807248B0(Actor *, f32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void func_806BB400(void) {
    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_806D0430(0.525f);
        D_807FBB4C->unk60 |= 0x400;
        D_807FBB4C->unk12A = 0x7D0;
        D_807FBB40->unk60 &= ~4;
        func_807248B0(D_807FBB40, 1.0f);
        D_807FBB40->unk15F = 0;
        D_807FBB40->unkE6 = mathAngleBetweenPoints2D(D_807FBB4C->unk7C, D_807FBB4C->unk84, D_807FBB40->unk7C, D_807FBB40->unk84);
        func_80614EBC(D_807FBB40, 0x21B);
        D_807FDC98->unk46 |= 8;
        ((R1EView98 *)D_807FDC98)->unk28 = 0x21C;
    }
    switch (D_807FBB40->unk154) {
        case 4:
            D_807FBB40->unk154 = 0x23;
            D_807FBB40->unk155[0] = 0;
        case 0x23:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    func_8072AB74(0x37, 0.0f, 0.0f, 0x202, 0.0f);
                    break;
                default:
                    D_807FBB40->unk155[0] = 1;
                    goto join;
                join:
                case 1:
                    if (((R1EView4 *)D_807FBB40->unk4)->unk64 != 0x21C) {
                        func_80614EBC(D_807FBB40, 0x21C);
                    }
                    func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0, 0.0f);
                    break;
                case 2:
                    break;
            }
            break;
        case 0x37:
            func_806D0430(0.3f);
            D_807FBB40->unk154 = 0x40;
            break;
    }
    D_807FDCA0->unk20 = 0;
    func_806319C4(D_807FBB40, 0);
}

typedef struct R1EView174 {
    /* 0x00 */ struct R1EView174Sub *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 pad8[0x26];
    /* 0x2E */ s16 unk2E;
} R1EView174;

typedef struct R1EView174Sub {
    /* 0x00 */ u8 pad0[0x46];
    /* 0x46 */ u16 unk46;
} R1EView174Sub;

extern Actor *D_807FBB44;

s32 func_807271F4(u8, s16, s16, s16, s32, s32, s32);

s32 func_806BB604(u8 arg0, s16 arg1, s16 arg2, s32 arg3) {
    R1EView174 *v;
    s32 r3;
    s32 r2;
    s32 r1;

    if (D_807FDC90->unk2C != 0) {
        func_806B9CE0(0, 0xA);
        D_807FDC90->unk2C--;
        return 0;
    }
    r1 = func_80611A44();
    r2 = func_80611A44();
    r3 = func_80611A44();
    if (func_807271F4(arg0,
                      (s16)((f32)((r1 >> 15) % 10) + (D_807FBB40->unk7C - 5.0f)),
                      (s16)(D_807FBB40->unk80 + 5.0f),
                      (s16)((f32)((r2 >> 15) % 10) + (D_807FBB40->unk84 - 5.0f)),
                      ((r3 >> 15) % 1024) + D_807FBB40->unkE6 - 0x200,
                      arg1, arg2) != 0) {
        D_807FBB44->unk154 = 0x17;
        D_807FBB44->unk155[0] = 0;
        v = D_807FBB44->unk174;
        v->unk2E = 0x1E;
        if (arg3 != 0) {
            v->unk0->unk46 &= ~8;
            v->unk4 = arg3;
        }
        D_807FBB44->unk144 = 1;
        D_807FBB44->unk12A = 0x3E8;
        return 1;
    }
    return 0;
}

void sfxAllocateChannel(s32, f32);

void func_806BB81C(void) {
    sfxPlayActorSound(D_807FBB40, 0x11F, 0, 0, 0, 0xFF, 1.0f, 0);
    sfxAllocateChannel(0x3B, 1.0f);
}

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

typedef struct L1P2C0 {
    u8 pad0[0x2C0];
    u8 unk2C0;
} L1P2C0;

typedef struct L1D1D8 {
    u8 pad0[0x1D8];
    f32 unk1D8;
} L1D1D8;

extern L1P2C0 *D_807FC924;
extern L1D1D8 *D_807FD580;
extern s32 D_807FBB68;
extern s32 D_807F5D10;
extern L1Tbl D_80750638;

void func_806BB81C();
s32 func_80726D7C(s32);
void func_80641874(s32, s32);
f32 func_80612790(s16);
f32 func_80612794(s16);
void func_8061CC40(void *, s32, s32);
void func_8061C464(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_8061C458(s32, void *);
void func_806224CC(s32, void *);
void func_80726EE0(s32);
void func_806D0468(void *, s32);
void func_8063DA40(s32, s32);
void func_80686F90(s32, s16, s16);
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

void func_806AD260();
s32 func_806BA240();

void func_806BC080(void) {
    func_806BB32C();
    if (D_807FDC9C->unkA == 0 || func_806BA240(0, 0x446) == 0) {
        func_806AD260(0x2ED, 1, 0);
        func_806319C4(D_807FBB40, 0);
    }
}

void func_806BC0E4(void) {
    func_806BB32C();
    if (D_807FDC9C->unkA == 0 || func_806BA240(0x32, 0x44E) == 0) {
        func_806AD260(0x2EC, 1, 0);
        func_806319C4(D_807FBB40, 0);
    }
}

void func_806BC148(void) {
    func_806BB32C();
    if (D_807FDC9C->unkA == 0 || func_806BA240(0x14, 0x44A) == 0) {
        func_806AD260(0x2EE, 1, 0);
        func_806319C4(D_807FBB40, 0);
    }
}

void func_806BA93C();

void func_806BC1AC(void) {
    func_806BB32C();
    func_806BA93C(0x24, 0x14, 0x1E);
}
