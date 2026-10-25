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

#pragma GLOBAL_ASM("asm/global/nonmatchings/C8C10/func_806C4F5C.s")

void func_806C55D8(void) {
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/C8C10/func_806C55E0.s")

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
void actorClearMovementFlags(void *);
void actorDespawn(Actor *);
void actorPlaceAttachedChildren(s32);
void actorSpawnNodeEntryAtActor(s32, s16);
f32 func_80612790(s16);
f32 func_80612794(s16);
void func_80614E78(Actor *, s32);
void func_80614EBC(Actor *, s32);
void func_8061CB08(void);
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
void func_80729B00(void);
void func_8070D8C0(Actor *, s32, u8);
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
