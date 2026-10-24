#include "common.h"
#include "actor.h"

typedef struct M3Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ActorSub4 *unk4;
    /* 0x008 */ u8 pad8[4];
    /* 0x00C */ f32 unkC[4][4];
    /* 0x04C */ u8 pad4C[0x14];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u32 unk64;
    /* 0x068 */ u8 pad68[2];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0xE];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x1C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x10];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ f32 unkC8;
    /* 0x0CC */ u8 padCC[0x1A];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x42];
    /* 0x132 */ s16 unk132;
    /* 0x134 */ u8 pad134[0x20];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[9];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ u8 pad160[8];
    /* 0x168 */ s16 unk168;
} M3Actor;

extern M3Actor *D_807FBB40;
extern M3Actor *D_807FBB44;

s32 func_80611A44(void);
void func_806319C4(M3Actor *, s32);

#pragma GLOBAL_ASM("asm/global/nonmatchings/B2CE0/func_806ADFE0.s")

s32 actorSpawn(s32, s32);
u32 actorGetNodePos(M3Actor *, s16, f32 *, f32 *, f32 *);
void func_807248B0(void *, s32);

void func_806AE2B0(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    if (actorSpawn(0xED, arg0) != 0) {
        actorGetNodePos(D_807FBB40, arg2, &sp2C, &sp28, &sp24);
        D_807FBB44->unkA4 = D_807FBB40->unkA4;
        D_807FBB44->unkE6 = D_807FBB40->unkE6 + arg1;
        D_807FBB44->unkEE = D_807FBB44->unkE6;
        D_807FBB44->unk168 = arg3;
        D_807FBB44->unk7C = sp2C;
        D_807FBB44->unk80 = sp28;
        D_807FBB44->unk84 = sp24;
        func_807248B0(D_807FBB44, *(s32 *)&D_807FBB40->unk4->unk38);
    }
}

s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void func_8070033C(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32);
f32 func_80612790(s16);
f32 func_80612794(s16);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void func_806EB0C0(s32, M3Actor *, s32);

void func_806AE394(f32 arg0, f32 arg1) {
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    s16 sp4E;

    actorGetNodePos(D_807FBB40, 1, &sp64, &sp60, &sp5C);
    actorGetNodePos(D_807FBB40, 2, &sp58, &sp54, &sp50);
    sp4E = mathAngleBetweenPoints2D(sp58, sp50, sp64, sp5C);
    func_8070033C(sp64, sp60, sp5C, sp58, sp54, sp50, 0.6f, 0xFF, 0xFF, 0xFF);
    sp64 = func_80612794(sp4E) * arg0 + D_807FBB40->unk7C;
    sp5C = func_80612790(sp4E) * arg0 + D_807FBB40->unk84;
    lightAdd(sp64, D_807FBB40->unk80, sp5C, 0.0f, 0.0f, 0.0f, arg1, 0, 0xFF, 0xFF, 0xFF);
    if (D_807FBB40->unk154 != 0) {
        if ((D_807FDC94->unk7C - sp64) * (D_807FDC94->unk7C - sp64) + (D_807FDC94->unk80 - D_807FBB40->unk80) * (D_807FDC94->unk80 - D_807FBB40->unk80) + (D_807FDC94->unk84 - sp5C) * (D_807FDC94->unk84 - sp5C) < arg1 * arg1) {
            D_807FBB40->unkE6 = mathAngleBetweenPoints2D(D_807FDC94->unk7C, D_807FDC94->unk84, D_807FBB40->unk7C, D_807FBB40->unk84);
            func_806EB0C0(0x43, D_807FBB40, 0);
            D_807FBB40->unk154 = 0;
            D_807FBB40->unk155 = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/B2CE0/func_806AE588.s")

typedef struct M3View90 {
    /* 0x00 */ u8 pad0[0x1A];
    /* 0x1A */ u16 unk1A;
} M3View90;

s32 func_8072DE10(s32);

void func_806AEE08(void) {
    if ((func_80611A44() >> 15) % 1000 >= 0x3D5 && func_8072DE10(0xFA0) != 0 && !(((M3View90 *)D_807FDC90)->unk1A & 0x80)) {
        D_807FBB40->unk154 = 0x25;
        D_807FBB40->unk155 = 0;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/B2CE0/func_806AEE84.s")

extern ActorGlobalState D_807FBB70;
void func_8072B79C(s32, s32, s32);
void func_80724CA4(s32, s32);
void func_80614EBC(M3Actor *, s32);
void func_80724E48(u8);
void func_8072AB74(u8, f32, f32, s32, f32);
void func_8072B324(M3Actor *, s32);
void func_8072A450(void);
void func_8072DE44(s32);
s32 func_8072E54C(void);
void func_8072D13C(u8, s32);
void func_8072B7CC(s32);
void func_80729B00(void);

void func_806AF688(void) {
    s32 var;

    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_8072B79C(0x2C0, 0x2C1, 0x2C1);
        func_80724CA4(0xE, 1);
        ((M3View90 *)D_807FDC90)->unk1A |= 0x800;
        D_807FBB40->unk60 |= 0x400;
    }
    func_806AE394(40.0f, 70.0f);
    if (D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) {
        D_807FBB40->unk154 = 0x3A;
        D_807FBB40->unk155 = 0;
    }
    switch (D_807FBB40->unk154) {
        case 0x11:
            func_80724E48(2);
            switch (D_807FBB40->unk155) {
                case 0:
                    func_8072B324(D_807FBB40, 0);
                    func_80614EBC(D_807FBB40, 0x2C0);
                    D_807FBB40->unk155++;
                case 1:
                    func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
                    if (D_807FBB40->unkB8 < 1.0f) {
                        D_807FBB40->unk155++;
                    }
                    break;
                case 2:
                    func_8072A450();
                    if ((func_80611A44() >> 15) % 1000 >= 0x3E4) {
                        func_8072DE44(0x1FB);
                    }
                    break;
            }
            break;
        case 1:
            if (func_8072E54C() != 0) {
                D_807FBB40->unk154 = 0x11;
                D_807FBB40->unk155 = 0;
            }
            func_80724E48(D_807FBB40->unk154 == 1 ? 2 : 0);
            func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0, 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            func_80724E48(D_807FBB40->unk154 == 0x35 ? 2 : 3);
            func_8072AB74(D_807FBB40->unk154, D_807FDC90->unkA, D_807FDC90->unkE, 0, 0.0f);
            break;
        case 0x37:
            D_807FBB40->unk154 = 0x40;
            break;
        default:
            func_8072B7CC(0x2C0);
            break;
    }
    switch (D_807FBB40->unk154) {
        case 2:
        case 3:
            func_8072D13C(D_807FBB40->unk154, 1);
            break;
        case 0x31:
        case 0x37:
        case 0x40:
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/B2CE0/func_806AFA60.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/B2CE0/func_806AFB58.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/B2CE0/func_806B02EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/B2CE0/func_806B0354.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/B2CE0/func_806B0770.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/B2CE0/func_806B0848.s")
