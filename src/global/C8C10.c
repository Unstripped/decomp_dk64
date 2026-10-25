#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern Struct807FD580 *D_807FD580;

#pragma GLOBAL_ASM("asm/global/nonmatchings/C8C10/func_806C3F10.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C8C10/func_806C43A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C8C10/func_806C4414.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C8C10/func_806C4904.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C8C10/func_806C4948.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C8C10/func_806C498C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C8C10/func_806C49D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C8C10/func_806C4AC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C8C10/func_806C4E8C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C8C10/func_806C4EB4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C8C10/func_806C4EE0.s")

typedef struct LgC4F5CA {
    /* 0x000 */ u8 pad0[0x60];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x1C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x3E];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[8];
    /* 0x0F0 */ s16 unkF0;
    /* 0x0F2 */ u8 padF2[0x38];
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[0x28];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[8];
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 pad15F[9];
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 pad16A[0x16];
    /* 0x180 */ s16 *unk180;
} LgC4F5CA;

typedef struct LgC4F5CG {
    /* 0x000 */ u8 pad0[0x1F4];
    /* 0x1F4 */ u32 unk1F4;
} LgC4F5CG;

typedef struct LgC4F5CS90 {
    /* 0x00 */ u8 pad0[0x1A];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[9];
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 pad26[2];
    /* 0x28 */ u8 unk28[4];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
} LgC4F5CS90;

#define LgA ((LgC4F5CA *)D_807FBB40)
#define LgB ((LgC4F5CA *)D_807FBB4C)
#define LgG ((LgC4F5CG *)D_807FD580)
#define LgS ((LgC4F5CS90 *)D_807FDC90)

void func_80729B00(void);
void func_8072B79C(s32, s32, s32);
void func_806BFBF4(void);
s32 func_80629148(void);
void func_8063DA40(s32, s32);
void func_8070D8C0(Actor *, s32, u8);
void func_80614EBC(Actor *, s32);
void func_806B49B0(s32, s32, s32);
void func_8061CC40(Actor *, s32, s32);
void func_8070E8DC(s32);
s32 func_8061CB50(void);
void func_806FB370(s32, s32, s32);
void func_8072A450(void);
void func_806C4EB4(void);
void hudSpawnTextScreen(s32);
s32 func_80724A20(void);
void func_80724B5C(s32, s32, f32 *, f32 *, f32 *);
void actorClearMovementFlags(void *);
s32 func_806C4AC4(s32, s32);
void func_806C4EE0(s32, s32);
s32 func_8072881C(s32, void *);

void func_806C4F5C(void) {
    s32 pad;
    s16 *sp28;
    f32 dx;
    f32 dy;
    f32 dz;

    sp28 = LgA->unk180;
    func_80729B00();
    if (!(LgA->unk60 & 0x10)) {
        LgA->unk154 = 0x1E;
        func_8072B79C(0x244, 0x244, 0x246);
        LgA->unk15E = (u32)LgA->unk15E / 2.0;
    }
    LgG->unk1F4 &= ~0x40;
    switch (LgA->unk154) {
        case 0:
        case 14:
        case 15:
        case 30:
            func_806BFBF4();
            if (func_80629148() != 0) {
                func_8063DA40(0x2D, 0x14);
                LgA->unk12A = 0x3E8;
                D_807FDC98->unk46 |= 0x24;
                func_8070D8C0(D_807FBB40, 0xF, 0);
                func_80614EBC(D_807FBB40, 0x244);
                LgA->unk154 = 0x27;
                LgS->unk2E = 0xF0;
            }
            break;
        case 39:
            LgG->unk1F4 |= 0x40;
            func_806B49B0(2, 0x244, 0x246);
            if ((LgS->unk1A & 4) && ((LgS->unk25 & 0x7F) == 3)) {
                LgA->unk154 = 0x28;
                LgA->unk155 = 0;
                func_80614EBC(D_807FBB40, 0x244);
            }
            break;
        case 40:
            LgG->unk1F4 |= 0x40;
            switch (LgA->unk155) {
                case 0:
                case 1:
                case 2:
                    if (LgA->unkA4 + 10.0f < LgA->unk80) {
                        LgA->unk80 -= 2.0f;
                    }
                    dx = LgB->unk7C - LgA->unk7C;
                    dy = LgB->unk80 - LgA->unk80;
                    dz = LgB->unk84 - LgA->unk84;
                    if (dx * dx + dy * dy + dz * dz < 6400.0f) {
                        LgA->unk155 = 3;
                        func_8061CC40(D_807FBB40, 0x1A, 1);
                        func_80614EBC(D_807FBB40, 0x245);
                    } else if (LgS->unk2E != 0) {
                        LgS->unk2E--;
                    } else {
                        LgA->unk154 = 0x29;
                        LgA->unk155 = 0;
                        LgS->unk2E = 0;
                        func_8070E8DC(1);
                        func_8070D8C0(D_807FBB40, 0xF, 2);
                    }
                    break;
                case 3:
                    if (func_8061CB50() == 0) {
                        func_8063DA40(0x2C, 0x1E);
                        *sp28 = 0x78;
                        LgS->unk2C = 0xA;
                        LgA->unk154 = 2;
                        LgA->unk155 = 0;
                        func_806FB370(5, 0, 1);
                        func_80614EBC(D_807FBB40, 0x244);
                    }
                    break;
            }
            func_8072A450();
            break;
        case 41:
            if (LgA->unkF0 == 0) {
                func_8061CC40(D_807FBB40, 0x1C, 1);
                LgA->unkF0++;
            } else if (func_8061CB50() == 0) {
                if (LgA->unk168 == 0) {
                    func_806C4EB4();
                    hudSpawnTextScreen(3);
                    LgA->unk154 = 0x2A;
                    LgA->unk155 = 0;
                } else if (LgA->unkF0 == 1) {
                    func_8063DA40(0xEB, 0xA);
                    LgA->unkF0++;
                }
                LgA->unk80 += 3.0f;
                LgS->unk2E++;
                if (LgS->unk2E >= 0x83) {
                    D_807FDC98->unk46 &= 0xFFFB;
                    func_806C4EB4();
                    LgA->unk154 = 0x3C;
                }
            }
            func_8072A450();
            break;
        case 42:
            func_80724A20();
            break;
        case 48:
            LgA->unkE6 = 0xA82;
            LgB->unkE6 = 0xA82;
            func_80724B5C(8, 2, &LgA->unk7C, &LgA->unk80, &LgA->unk84);
            actorClearMovementFlags(D_807FBB4C);
            func_80724B5C(8, 2, &LgB->unk7C, &LgB->unk80, &LgB->unk84);
            LgB->unk80 -= 25.0f;
            LgA->unk154 = 0x28;
            LgA->unk155 = 0;
            func_80614EBC(D_807FBB40, 0x244);
            LgS->unk25 = 2;
            func_806FB370(5, 0, 1);
            break;
    }
    switch (func_806C4AC4(0x78, 0xA)) {
        case 1:
            func_806C4EE0(2, 0);
            break;
        case 2:
            func_806C4EE0(3, 1);
            break;
    }
    func_8072881C(0, LgS->unk28);
}

void func_806C55D8(void) {
}

typedef struct LgC55E0Sub4 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} LgC55E0Sub4;

typedef struct LgC55E0A {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ LgC55E0Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x58];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x5C];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[0x40];
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[0x28];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x12];
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 pad16A[0x16];
    /* 0x180 */ s16 *unk180;
} LgC55E0A;

typedef struct LgC55E0G {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ u32 unk1F0;
    /* 0x1F4 */ u32 unk1F4;
} LgC55E0G;

typedef struct LgC55E0S90 {
    /* 0x00 */ u8 pad0[0x25];
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 pad26[2];
    /* 0x28 */ u8 unk28[4];
    /* 0x2C */ s16 unk2C;
} LgC55E0S90;

#define LA ((LgC55E0A *)D_807FBB40)
#define LA4C ((LgC55E0A *)D_807FBB4C)
#define LG ((LgC55E0G *)D_807FD580)
#define LS90 ((LgC55E0S90 *)D_807FDC90)

void func_80728950(s32);
void func_807289B0(s32, s32);
void func_8061CB08(void);
void func_806F8BC4(s32, s32, s32);
void func_806C4E8C(void);
void func_8072DC7C(s32);
void func_807266E8(Actor *, Struct807FDC9C *);
f32 func_80612790(s16);
f32 func_80612794(s16);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void effectSpawnSmoke(u8);

void func_806C55E0(void) {
    s32 pad;
    s16 *sp20;

    sp20 = LA->unk180;
    func_80729B00();
    if (!(LG->unk1F0 & 0x100000)) {
        LA->unk154 = 0x40;
        return;
    }
    if (!(LA->unk60 & 0x10)) {
        func_8072B79C(0x357, 0x357, 0x359);
        D_807FDC98->unk46 |= 0x20;
        LA->unk154 = 0x1E;
        LA->unk12A = 0x3E8;
        func_80728950(0);
    }
    switch (LA->unk154) {
        case 0x1E:
            effectSpawnSmoke(1);
            func_80724A20();
            break;
        case 0x27:
            switch (LA->unk155) {
                case 0:
                    if (func_8061CB50() == 0) {
                        func_807289B0(0, 0);
                        func_8061CC40(D_807FBB40, 0x13, 1);
                        LA->unk155++;
                    }
                    break;
                case 1:
                    if (func_80629148() != 0) {
                        func_80614EBC(D_807FBB40, 0x354);
                        LA->unk155++;
                    }
                    break;
                case 3:
                    func_8070D8C0(D_807FBB40, 0x15, 0);
                    LA->unk155++;
                    break;
                case 4:
                    if (!(LA->unk60 & 0x2000000)) {
                        func_8061CB08();
                        LA->unk154 = 0x28;
                    }
                    break;
            }
            break;
        case 0x28:
            if (LA4C->unk154 == 0x63) {
                if ((LA->unk7C - LA4C->unk7C) * (LA->unk7C - LA4C->unk7C) + (LA->unk84 - LA4C->unk84) * (LA->unk84 - LA4C->unk84) < 10000.0f) {
                    func_8061CC40(D_807FBB40, 0x15, 1);
                    func_8070D8C0(D_807FBB40, 0x15, 1);
                    LA->unk154 = 0x29;
                    LA->unk155 = 0;
                }
            }
            break;
        case 0x29:
            switch (LA->unk155) {
                case 0:
                    if (!(LA->unk60 & 0x2000000)) {
                        func_80614EBC(D_807FBB40, 0x358);
                        LA->unk155 = 1;
                    }
                    break;
                case 2:
                    func_8061CB08();
                    D_807FDC98->unk46 |= 0x24;
                    LA->unk154 = 2;
                    func_806FB370(5, 0, 1);
                    func_806F8BC4(5, 1, 0);
                    *sp20 = 0x78;
                    LS90->unk2C = 0x10;
                    LA->unk168 = 0;
                    func_80614EBC(D_807FBB40, 0x357);
                    break;
            }
            break;
        case 0x2A:
            switch (LA->unk155) {
                case 0:
                    LA->unkE4 = 0;
                    LA->unkE8 = 0;
                    if (!(LA->unk60 & 0x2000000)) {
                        func_8061CB08();
                        func_806C4E8C();
                        if (LA->unk4->unk64 == 0x35A && LA4C->unk154 == 0x63) {
                            hudSpawnTextScreen(4);
                            LA->unk155 = 3;
                        } else {
                            LA->unk155++;
                            LA->unk60 &= ~0x8000;
                        }
                    }
                    break;
                case 1:
                    func_8072DC7C(5);
                    break;
                case 2:
                    LA->unk154 = 0x3C;
                    break;
                case 3:
                    func_80724A20();
                    break;
            }
            break;
        case 0x30:
            func_80614EBC(D_807FBB40, 0x355);
            func_807266E8(D_807FBB40, D_807FDC9C);
            LS90->unk25 = 0;
            LA->unk168 = 0;
            actorClearMovementFlags(D_807FBB4C);
            LA4C->unk80 = LA->unk80;
            LA4C->unk7C = func_80612794(LA->unkE6) * 50.0f + LA->unk7C;
            LA4C->unk84 = func_80612790(LA->unkE6) * 50.0f + LA->unk84;
            LA4C->unkE6 = mathAngleBetweenPoints2D(LA->unk7C, LA->unk84, LA4C->unk7C, LA4C->unk84);
            func_8061CC40(D_807FBB40, 0x15, 1);
            func_8070D8C0(D_807FBB40, 0x15, 1);
            LA->unk154 = 0x29;
            LA->unk155 = 0;
            break;
    }
    LG->unk1F4 &= ~0x40;
    switch (func_806C4AC4(0x78, 0x10)) {
        case 1:
            func_807266E8(D_807FBB40, D_807FDC9C);
            func_8070D8C0(D_807FBB40, 0x15, 2);
            func_80614EBC(D_807FBB40, 0x35A);
            LA->unk154 = 0x2A;
            LA->unk155 = 0;
            func_8061CC40(D_807FBB40, 0x16, 1);
            break;
        case 2:
            func_807266E8(D_807FBB40, D_807FDC9C);
            func_8070D8C0(D_807FBB40, 0x15, 3);
            func_80614EBC(D_807FBB40, 0x35B);
            LA->unk154 = 0x2A;
            LA->unk155 = 0;
            func_8061CC40(D_807FBB40, 0x14, 1);
            break;
    }
    if (LA->unk154 != 0x1E) {
        func_8072881C(0, LS90->unk28);
    }
}

typedef struct R1C8CBG {
    /* 0x000 */ u8 pad0[0x1F4];
    /* 0x1F4 */ u32 unk1F4;
} R1C8CBG;

typedef struct R1C8CBA {
    /* 0x000 */ u8 pad0[0x60];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x5C];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[2];
    /* 0x0EC */ s16 unkEC;
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ s16 unkF0;
    /* 0x0F2 */ u8 padF2[0x62];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[9];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ u8 pad160[8];
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 pad16A[0xA];
    /* 0x174 */ R1C8CBG *unk174;
} R1C8CBA;

typedef struct R1C8CBCfg {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ Actor *unkC;
    /* 0x10 */ R1C8CBA *unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u8 pad18[2];
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s8 unk1E;
} R1C8CBCfg;

typedef struct R1C8CBPlayer {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ u8 pad214[4];
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0x68];
    /* 0x284 */ f32 unk284;
} R1C8CBPlayer;

typedef struct R1C8CB580 {
    /* 0x000 */ u8 pad0[0x1EC];
    /* 0x1EC */ u8 unk1EC;
    /* 0x1ED */ u8 pad1ED[3];
    /* 0x1F0 */ s32 unk1F0;
} R1C8CB580;

#define R1A ((R1C8CBA *)D_807FBB40)
#define R1A4C ((R1C8CBA *)D_807FBB4C)
#define R1D580 ((R1C8CB580 *)D_807FD580)

extern u32 D_8076A064;
extern s16 D_8076A0AA;
extern s32 D_8071FB08;
extern u32 D_807FBB60;
extern R1C8CBPlayer *D_807FC924;
extern s16 D_807FD802;
extern s16 D_807FD804;
extern s16 D_807FD806;
void actorAttachChildCallbacks(void);
void actorDespawn(Actor *);
void actorPlaceAttachedChildren(s32);
void actorSpawnNodeEntryAtActor(s32, s16);
void func_80614E78(Actor *, s32);
void func_806319C4(Actor *, s32);
void func_80724CA4(s32, s32);
void func_80724E48(u8);
s32 func_80611A44(void);
void func_8072AB74(s32, f32, f32, s32, f32);
void func_807149B8(s32);
void func_8071C818(void);
void func_8071498C(void (*)(void));
void func_80714CC0(void *, f32, f32, f32, f32);
f32 sqrtf(f32);
s32 func_8072DE10(u16);
s32 func_80727194(Actor *);
s32 func_80731784(s16, s16, s32 *);
void func_8073129C(s16, s32, s32);
void func_8060DEC8();
void func_80626F8C(f32, f32, f32, f32 *, f32 *, s32, f32, s32);
s32 func_8073195C(s16);
void lightSetColor(f32, f32, f32, s16);
void sfxAllocateChannel(s32, f32);
void sfxStopChannel();

void func_806C5C20(void) {
    f32 sp54;
    f32 sp50;
    f32 dist;
    s32 sp44[2];

    func_80729B00();
    actorClearMovementFlags(D_807FBB40);
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FDC98->unk46 |= 0x40;
        D_807FBB40->unk12A = 0xFA;
        func_80724CA4(2, 1);
    }
    if ((func_80611A44() >> 15) % 1000 >= 0x3CB) {
        D_807FBB40->unkB8 = D_807FDC9C->unkC << 2;
    }
    func_80724E48(6);
    func_8072AB74(1, D_807FDC94->unk7C, D_807FDC94->unk84, 0x2C9, 0.0f);
    if (!(D_8076A064 & 3)) {
        func_807149B8(1);
        func_8071498C(func_8071C818);
        func_80714CC0(&D_8071FB08, 1.6f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
    }
    if (!(D_807FD580->unk1F0 & 0x8000)) {
        dist = sqrtf((D_807FC924->unk218 - D_807FBB40->unk84) * (D_807FC924->unk218 - D_807FBB40->unk84) +
                     (D_807FC924->unk210 - D_807FBB40->unk7C) * (D_807FC924->unk210 - D_807FBB40->unk7C)) -
               D_807FC924->unk284;
        if (D_807FD804 >= 0x8A && D_807FD804 < 0xB1 && D_807FD806 >= 0x61 && D_807FD806 < 0x88 && dist < D_807FD802) {
            if (R1D580->unk1EC != 1) {
                if (func_8072DE10(0x1388) != 0) {
                    func_80614EBC(D_807FBB40, 0x2B6);
                }
            }
            R1D580->unk1EC = 1;
        } else {
            if (R1D580->unk1EC != 2) {
                func_80614EBC(D_807FBB40, 0x2B5);
            }
            R1D580->unk1EC = 2;
        }
    }
    if ((D_807FD580->unk1F0 & 0x8000) && R1D580->unk1EC == 1) {
        if (D_807FBB40->unk154 != 0x40) {
            func_8073129C(func_80731784(D_8076A0AA, func_80727194(D_807FBB40), sp44), 1, 0);
            func_8060DEC8();
        }
        D_807FBB40->unk154 = 0x40;
    }
    if (D_807FBB40->unk154 != 0x40) {
        sfxAllocateChannel(0x42, 1.0f);
    } else {
        sfxStopChannel(0x42, 0);
    }
    func_80626F8C(D_807FBB40->unk7C, D_807FBB40->unk80 + 10.0f, D_807FBB40->unk84, &sp54, &sp50, 0, 1.0f, 0);
    D_807FD804 = sp54;
    D_807FD806 = sp50;
    func_806319C4(D_807FBB40, 0);
}


void func_806C5FEC(void) {
    R1C8CBCfg *p;

    p = (R1C8CBCfg *)D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        p->unk1C = 0;
        D_807FBB40->unk60 |= 0x400;
    }
    p->unk1C++;
    switch (p->unk1E) {
        case 1:
            if (R1A4C->unk155 == 3) {
                func_8070D8C0(D_807FBB40, 0x1E, 3);
                p->unk1E = 2;
            } else if (p->unk10->unk154 != 0x83) {
                p->unk1E = 3;
            }
            break;
        case 2:
            if (!(D_807FBB40->unk60 & 0x2000000)) {
                p->unk1E = 3;
                func_8061CB08();
            }
            break;
        default:
            if (p->unk10->unk154 != 0x83) {
                p->unk10->unk174->unk1F4 &= ~0x10;
                p->unk10->unk60 &= ~0x40000000;
                p->unk10->unk60 |= 1;
                p->unk10->unkE8 = p->unk16;
                p->unk10->unkE4 = p->unk14;
                D_807FBB60 |= 0x10030;
                lightSetColor(p->unk0, p->unk4, p->unk8, p->unk1A);
                sfxStopChannel(0x3B, 0);
                actorDespawn(p->unkC);
                actorDespawn(D_807FBB40);
                return;
            }
            break;
    }
    func_806319C4(D_807FBB40, 0);
}


void func_806C61C8(void) {
    f32 x;
    f32 z;
    f32 sinv;

    if (!(D_807FBB40->unk60 & 0x10)) {
        R1A->unkEC = 0x3C;
        func_80614EBC(D_807FBB40, 0x23D);
        if (R1A4C->unk154 == 0xC) {
            func_80614E78((Actor *)D_807FBB4C, 0x87);
        }
    }
    x = func_80612794(R1A4C->unkE6) * 50.0f + R1A4C->unk7C;
    z = func_80612790(R1A4C->unkE6) * 50.0f + R1A4C->unk84;
    R1A->unkE6 = (R1A4C->unkE6 + 0x800) & 0xFFF;
    if (R1A->unkEC == 0x3C) {
        D_807FBB40->unk7C = func_80612794(R1A->unkEE) * 10.0f + x;
        D_807FBB40->unk84 = func_80612790(R1A->unkEE) * 10.0f + z;
    }
    R1A->unk80 = func_80612794(D_8076A064 * 100) * 5.0f + (R1A->unk15F + R1A4C->unk80 + 3.0f + R1A->unkEC);
    if (!(D_807FBB40->unk60 & 0x10)) {
        if (R1A->unkF0 != 0) {
            R1A->unk15F = 0x14;
            actorSpawnNodeEntryAtActor(0x2D, func_8073195C(R1A->unkF0));
        }
    }
    if (R1A->unkF0 != 0) {
        actorPlaceAttachedChildren(-0x1E);
    }
    sinv = func_80612794(D_8076A064 * 50);
    R1A->unkEE = R1A->unkEE + 60.0f * sinv;
    if (D_807FBB40->unk60 & 0x2000000) {
        R1A->unk168 = 0x14;
    }
    if (R1A->unk168 != 0) {
        R1A->unk168--;
    }
    if (R1A->unk168 == 0) {
        R1A->unkEC++;
        if (R1A->unkEC >= 0x3D) {
            if (R1A->unkF0 != 0) {
                actorAttachChildCallbacks();
            }
            actorDespawn(D_807FBB40);
            func_8061CB08();
            if (R1A4C->unk154 == 0xC) {
                func_80614E78((Actor *)D_807FBB4C, 9);
            }
        }
    } else if (R1A->unkEC >= 0x10) {
        R1A->unkEC--;
    }
    func_806319C4(D_807FBB40, 0);
}
