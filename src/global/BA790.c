#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBD70;

#pragma GLOBAL_ASM("asm/global/nonmatchings/BA790/func_806B5A90.s")

s32 func_806B5A90();
void func_80729B00(void);

void func_806B63E0(void) {
    func_80729B00();
    func_806B5A90(0x2710, 0);
}

typedef struct R1AView {
    /* 0x000 */ u8 pad0[0x178];
    /* 0x178 */ s16 *unk178;
} R1AView;

#define R1AA ((R1AView *)D_807FBB40)

typedef struct R1AView9C {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
} R1AView9C;

#define R1A9C ((R1AView9C *)D_807FDC9C)

extern u8 D_807444EC;
extern s32 D_8076A0A8;

void actorClearNodeFlag(Actor *, s32);
void func_80614EBC(void *, s32);
void func_8068A858(void *, void *, void *);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);

void func_806B640C(void) {
    s16 *p = R1AA->unk178;
    s16 i;
    s32 sel;
    s32 a;

    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        actorClearNodeFlag(D_807FBB40, 3);
        *p = -R1A9C->unkA;
    }
    if (D_807444EC == 1) {
        for (i = 0; i < D_807FBB70.unk254; i++) {
            if (D_807FBB70.unk258[i] == 3) {
                D_807FBB40->unk144 = 0x24;
                func_80614EBC(D_807FBB40, 0x24F);
            }
        }
        func_8068A858(&D_807FBB40->unk16A, &D_807FBB40->unk16B, &D_807FBB40->unk16C);
    }
    sel = D_807FBB40->unk154;
    if (sel != 0x37 && sel != 0x38) {
        if (*p > 0) {
            (*p)--;
            if (*p == 0xA) {
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x150, 0xFF, 0x7F, 0x1E, 0x32, 0.3f, 0);
            }
            if (*p == 0) {
                D_807FBB70.unk200 = 9;
            }
        }
    }
    if (D_8076A0A8 == 6) {
        a = 0x9C40;
    } else {
        a = 0x2710;
    }
    if (func_806B5A90(a, *p) != 0) {
        *p = -*p;
    }
}
