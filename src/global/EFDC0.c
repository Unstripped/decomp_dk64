#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern Struct807FD580 *D_807FD580;
extern s16 D_807FD584;
extern s32 D_8076A0A8;
extern u8 D_8074E77C[];

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EB0C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EB178.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EB194.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EB2B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EB364.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EB400.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EB4B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EB4F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EB544.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EB5C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EB6D8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EB744.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EB8CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EB964.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EBA04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EBA74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EBAF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EBB44.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EBBD0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EBC60.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EBCF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EBDAC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EBDC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EBE8C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EBED0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EBF34.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EBF74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EBFD0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EC014.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EC044.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EC1A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EC2CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EC3BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EC4AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EC708.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EC800.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EC8C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EC994.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806ECA74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806ECAC4.s")

void func_80614D90(Actor *);
void func_80614E78(void *, s32);

void func_806ECBD4(void) {
    D_807FBB48->unk6A |= 0x40;
    D_807FBB48->unk64 &= ~0x2000;
    D_807FBB48->unk154 = 0x57;
    D_807FBB48->unk155[0] = 0;
    func_80614E78(D_807FBB48, 0x69);
    func_80614D90(D_807FBB48);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806ECC48.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806ECCDC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806ECDD4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806ECE2C.s")

typedef struct EfCActorC0 {
    u8 pad0[0xC0];
    f32 unkC0;
} EfCActorC0;

typedef struct EfCPlayer48 {
    u8 pad0[0x50];
    s16 unk50;
} EfCPlayer48;

void func_80614D00(Actor *, f32, f32);
void func_806CF42C(Actor *);
void func_806CFE7C(void);

void func_806ECF1C(void) {
    ((EfCActorC0 *)D_807FBB48)->unkC0 = 260.0f;
    func_806CFE7C();
    ((EfCPlayer48 *)D_807FD580)->unk50 = 0;
    func_80614E78(D_807FBB48, 0x20);
    func_80614D00(D_807FBB48, 1.0f, 0.0f);
    D_807FBB48->unk154 = 0x30;
    D_807FBB48->unk155[0] = 0;
    func_806CF42C(D_807FBB48);
}

typedef struct EfCPlayer68 {
    u8 pad0[0x50];
    s16 unk50;
    u8 pad52[0x16];
    f32 unk68;
} EfCPlayer68;

extern s16 D_807537FC[];
extern s16 D_8075383C[];
extern s16 D_8075384C[];

void func_806ECF9C(void) {
    ((EfCPlayer68 *)D_807FD580)->unk50 = D_807537FC[D_807FD584];
    ((EfCPlayer68 *)D_807FD580)->unk68 += D_8075383C[D_807FD584];
    if (D_8075384C[D_807FD584] < ((EfCPlayer68 *)D_807FD580)->unk68) {
        ((EfCPlayer68 *)D_807FD580)->unk68 = D_8075384C[D_807FD584];
    }
    ((EfCActorC0 *)D_807FBB48)->unkC0 = 0.0f;
    ((EfCPlayer68 *)D_807FD580)->unk50 = 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806ED050.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806ED0FC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806ED244.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806ED420.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806ED508.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806ED5C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806ED6B0.s")

typedef struct EfCPlayerState {
    u8 pad0[0x1EE];
    s16 unk1EE;
} EfCPlayerState;

void func_806C8E58(s16);
void func_806CFF9C(Actor *);

void func_806EDFF8(void) {
    func_806C8E58(((EfCPlayerState *)D_807FD580)->unk1EE);
    func_806CFF9C(D_807FBB48);
}

void func_806CF398(Actor *);

void func_806EE02C(void) {
    func_806CF398(D_807FBB48);
    D_807FBB48->unk154 = 0x55;
    D_807FBB48->unk155[0] = 0;
}

typedef struct EfCPlayerState06 {
    u8 pad0[0x38];
    f32 unk38;
    u8 pad3C[0x14];
    s16 unk50;
    u8 pad52[0x36];
    Actor *unk88;
} EfCPlayerState06;

typedef struct EfCCamBlock {
    u8 pad0[0x2A0];
    Actor *unk2A0;
    u8 pad2A4[0x4C];
} EfCCamBlock;

#define EfCCam ((EfCCamBlock *)D_807FC924)

void func_806EE06C(void) {
    func_806CF398(D_807FBB48);
    D_807FBB48->unk154 = 0x56;
    D_807FBB48->unk155[0] = 0;
    func_80614E78(D_807FBB48, 0x87);
    ((EfCPlayerState06 *)D_807FD580)->unk50 = 0;
    ((EfCPlayerState06 *)D_807FD580)->unk38 = 0.0f;
    ((EfCPlayerState06 *)D_807FD580)->unk88 = EfCCam[D_807FC929].unk2A0;
}

typedef struct EfCPlayerD4 {
    u8 pad0[0xD4];
    s16 unkD4;
} EfCPlayerD4;

s32 func_806C9974(u8, s8);
s32 func_806EB400(Actor *);
void func_806CA2AC(void);
extern s16 D_807530B0[];

void func_806EE10C(void) {
    if (func_806EB400(D_807FBB48) != 0) {
        func_806CA2AC();
        if (func_806C9974(D_807FC929, -1) != 0) {
            if (D_807FBB48->unk6A & 4) {
                func_80614E78(D_807FBB48, 0x29);
            } else {
                func_80614E78(D_807FBB48, 0x27);
            }
            D_807FBB48->unk154 = 0x36;
            D_807FBB48->unk155[0] = 0;
        }
        ((EfCPlayerD4 *)D_807FD580)->unkD4 = D_807530B0[D_807FD584];
    }
}

typedef struct EfCPlayer1AC {
    u8 pad0[0x1AC];
    s32 unk1AC;
    s32 unk1B0;
} EfCPlayer1AC;

typedef struct EfCActorC0S32 {
    u8 pad0[0xC0];
    s32 unkC0;
} EfCActorC0S32;

void func_8067A784(Actor *, s32, s16, s32, s32);

void func_806EE1C4(void) {
    s32 value = ((EfCPlayer1AC *)D_807FD580)->unk1AC;

    if (value != 0) {
        func_8067A784(D_807FBB40, value, D_807FBB48->unkE6,
                      ((EfCActorC0S32 *)D_807FBB40)->unkC0, (s32)D_807FBB40->unkB8);
        ((EfCPlayer1AC *)D_807FD580)->unk1AC = 0;
        ((EfCPlayer1AC *)D_807FD580)->unk1B0 = 0;
    }
    func_806CA2AC();
    func_80614E78(D_807FBB40, 0x1C);
    D_807FBB48->unk154 = 0x20;
    D_807FBB48->unk155[0] = 0;
}


void func_806EE26C(void) {
    func_806CA2AC();
    func_80614E78(D_807FBB40, 0x1C);
    D_807FBB48->unk154 = 0x21;
    D_807FBB48->unk155[0] = 0;
}

typedef struct EfCPlayer104 {
    u8 pad0[0x104];
    void *unk104;
} EfCPlayer104;

void sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);

void func_806EE2B8(void) {
    s32 value = 1;
    s8 selector;
    Actor *target;

    if (func_806EB400(D_807FBB48) != 0) {
        selector = -1;
        func_806CA2AC();
        target = EfCCam[D_807FC929].unk2A0;
        if ((target != NULL) && (target->unk58 == 0x123)) {
            selector = -2;
        }
        if (func_806C9974(D_807FC929, selector) != 0) {
            value = 0;
            if (D_807FBB48->unk6A & 4) {
                func_80614E78(D_807FBB48, 0x29);
            } else {
                func_80614E78(D_807FBB48, 0x27);
            }
            D_807FBB48->unk154 = 0x36;
            D_807FBB48->unk155[0] = 0;
        } else {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x16, 0xFF, 0x7F, 0);
            func_80614E78(D_807FBB40, 0x1E);
            D_807FBB40->unk154 = 0x20;
            D_807FBB40->unk155[0] = 1;
        }
    }
    if ((((EfCPlayerD4 *)D_807FD580)->unkD4 == 0) && (D_807FC928 < 2)) {
        ((EfCPlayerD4 *)D_807FD580)->unkD4 = D_807530B0[D_807FD584];
    }
    if (value != 0) {
        func_8061F0B0(((EfCPlayer104 *)D_807FD580)->unk104, 0x14, 0x14);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EE454.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EE5A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EE634.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EE660.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EE6B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EE700.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EE74C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EE7B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EE7F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EE878.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EE924.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EE994.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EEA5C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EEAF8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EF830.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EF944.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EFA08.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EFA1C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EFA3C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EFB4C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EFC38.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EFD50.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EFDFC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EFF34.s")

void func_806F006C(void) {
}

void func_806F0074(void) {
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806F007C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806F00BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806F014C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806F0184.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806F01D8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806F0238.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806F027C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806F0344.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806F03C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806F0624.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806F06A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806F0700.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806F07CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806F0878.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806F0930.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/D_8075D380.s")
