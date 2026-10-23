#include "common.h"

typedef struct Actor_3340 {
    char pad0[0x60];
    s32 unk60;
    char pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x154 - 0x88];
    u8 unk154;
    u8 unk155;
    char pad156[0x1A4 - 0x156];
    u8 unk1A4;
} Actor_3340;

extern Actor_3340 *D_807FBB40;
extern Actor_3340 *D_807FBB4C;
extern Actor_3340 *D_807FD580;
extern s32 D_8076A064;

void func_80729B00(void);
void func_80604CBC(Actor_3340 *, s32, s32, s32, s32, s32, f32, s32);
s32 func_8073110C(s32, s32);
void func_80614EBC(Actor_3340 *, s32);
s32 func_80731AA8(s32, s32, s32);
void func_8073129C(s32, s32, s32);
void func_8061CC40(Actor_3340 *, s32, s32);
void func_80629174(void);
s32 func_80629148(Actor_3340 *);
void effectSpawnBurst(s32);
void func_80614E78(Actor_3340 *, s32);
void func_80608528(Actor_3340 *, s32, s32, s32, s32);
void func_80605314(Actor_3340 *, s32);
void func_806F8BC4(s32, s32, s32);
void func_806F91B4(s32, u8, s32);
void func_806319C4(Actor_3340 *, s32);

void animSetLoopLimit(void *, s32, s32);
void animSetSpeed(void *, s32, f32);
void animSetFrameAndSubframe(void *, s32, s16, f32);
void animSetFinished(void *, s32, s32);

/* Non-matching draft: 1 instruction swap in prologue (sw ra vs move s2) */
#if 0
void func_80027340(s32 arg0) {
    s32 var_s0;
    f32 zero = 0.0f;

    for (var_s0 = 2; var_s0 >= 0; var_s0--) {
        animSetLoopLimit(D_807FBB40, var_s0, 1);
        animSetSpeed(D_807FBB40, var_s0, zero);
        animSetFrameAndSubframe(D_807FBB40, var_s0, (arg0 % 10) + 1, zero);
        animSetFinished(D_807FBB40, var_s0, 0);
        arg0 /= 10;
    }
}
#endif
#pragma GLOBAL_ASM("asm/critter/nonmatchings/3340/func_80027340.s")

#pragma GLOBAL_ASM("asm/critter/nonmatchings/3340/func_80027448.s")

/* Non-matching draft: actor spill to sp34 at 0x34(sp) and stack frame scheduling */
#if 0
void func_80027DC0(void) {
    Actor_3340 *sp34;
    Actor_3340 **s0;
    Actor_3340 *actor;
    f32 dx;
    f32 dz;
    s32 var_t5;
    s32 var_t6;

    func_80729B00();
    s0 = &D_807FBB40;
    actor = *s0;
    if (!(actor->unk60 & 0x10)) {
        func_80604CBC(actor, 0x10F, 0x46, 1, 0, 0x1E, 1.0f, 0);
        (*s0)->unk154 = 0;
        if (func_8073110C(0x179, 0) == 0) {
            (*s0)->unk154 = 1;
        } else if (func_8073110C(0x189, 0) != 0) {
            func_80614EBC(*s0, 0x2B5);
        } else if (func_80731AA8(0x24D, 0x14, 0) == 0x14) {
            func_80614EBC(*s0, 0x2B5);
            (*s0)->unk154 = 3;
        }
    }
    actor = *s0;
    dx = actor->unk7C - D_807FBB4C->unk7C;
    dz = actor->unk84 - D_807FBB4C->unk84;
    switch (actor->unk154) {
    case 1:
        var_t5 = 0;
        if ((dx * dx + dz * dz) < 10000.0f) {
            var_t5 = 1;
        }
        if (var_t5 != 0) {
            func_8073129C(0x179, 1, 0);
            func_8061CC40(D_807FBB4C, 0, 1);
            func_80629174();
            (*s0)->unk154 = 2;
        }
        break;
    case 2:
        sp34 = actor;
        if (actor->unk155 != 0) {
            actor->unk155++;
            if ((*s0)->unk155 < 0x4B) {
                *s0 = D_807FBB4C;
                if (!(D_8076A064 & 3)) {
                    effectSpawnBurst(0);
                }
                *s0 = sp34;
            } else {
                *s0 = D_807FBB4C;
                D_807FBB4C->unk154 = 0x2D;
                D_807FBB4C->unk155 = 0;
                func_80614E78(D_807FBB4C, 0x42);
                func_80608528(D_807FBB4C, 0xF2, 0xFF, 0x7F, 0);
                *s0 = sp34;
                sp34->unk155 = 0;
                func_80605314(D_807FBB4C, 1);
            }
        } else if (func_80629148(actor) != 0) {
            (*s0)->unk155 = 1;
            func_80604CBC(D_807FBB4C, 0x104, 0x3C, 1, 1, 0xFF, 1.0f, 0);
            func_806F8BC4(6, 0, 0);
            func_806F91B4(6, D_807FD580->unk1A4, 0x3E7);
        }
        break;
    case 3:
        var_t6 = 0;
        if ((dx * dx + dz * dz) < 10000.0f) {
            var_t6 = 1;
        }
        if (var_t6 != 0) {
            func_8061CC40(*s0, 0, 1);
            func_80629174();
            (*s0)->unk154 = 4;
        }
        break;
    case 4:
        break;
    }
    func_806319C4(*s0, 0);
}
#endif
#pragma GLOBAL_ASM("asm/critter/nonmatchings/3340/func_80027DC0.s")

#pragma GLOBAL_ASM("asm/critter/nonmatchings/3340/func_80028120.s")
