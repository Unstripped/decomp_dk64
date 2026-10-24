// func_806ADFE0 (src/global/B2CE0.c): text-identical, reloc only: ldc1 of 0.6 double uses .rodata+8 vs expected D_8075AE28 label; nothing else differs. Needed tricks: unkB8 * 2 (int literal -> mul.s, not add.s), func_80665564 second param f32 with int 0 (li a1,0), guTranslateF(sp88,0,-30.0f,0) + guTranslateF(sp48,0,30.0f,0.0f) (mixed 0/0.0f literals avoid CSE'd mtc1 in 2nd call), unk6A&1 tested twice.
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
s32 func_80611A44(void);
void func_80612BC0(f32 (*)[4], f32);
void func_80666280(s32);
void func_80729E6C(void);
void func_8067ACB4(M3Actor *);
void actorApplyVelocity(M3Actor *);
void func_80665564(M3Actor *, f32);
void func_8065D254(M3Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_806319C4(M3Actor *, s32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void actorDespawn(M3Actor *);
extern u8 D_8071FBC8[];

void func_806ADFE0(void) {
    f32 sp88[4][4];
    f32 sp48[4][4];

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unkB8 = (func_80611A44() >> 15) % 50 + 0x46;
        D_807FBB40->unkC0 = D_807FBB40->unkB8 * 2;
        D_807FBB40->unkC4 = -30.0f;
        D_807FBB40->unkC8 = -220.0f;
        D_807FBB40->unk168 = (func_80611A44() >> 15) % 400 + 200;
    }
    D_807FBB40->unkE6 += D_807FBB40->unk168;
    if (D_807FBB40->unk168 > 0) {
        D_807FBB40->unk168 -= 10;
    }
    func_80666280(1);
    func_80729E6C();
    func_8067ACB4(D_807FBB40);
    actorApplyVelocity(D_807FBB40);
    func_80665564(D_807FBB40, 0);
    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 10, 10, 1, 200, 0x80, 0, 1.0f);
    if (D_807FBB40->unk15F != 0) {
        func_806319C4(D_807FBB40, 0);
    } else {
        guTranslateF(sp88, 0, -30.0f, 0);
        func_80612BC0(sp48, 180.0f);
        guMtxCatF(sp88, sp48, sp88);
        guTranslateF(sp48, 0, 30.0f, 0.0f);
        guMtxCatF(sp88, sp48, D_807FBB40->unkC);
        func_806319C4(D_807FBB40, 1);
    }
    if ((D_807FBB40->unk6A & 1) && !(D_807FBB40->unk6C & 1)) {
        func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x56, 0xB4, 0x96, 1, 0x4B, 0.3f, 0);
        D_807FBB40->unkB8 = D_807FBB40->unkB8 * 0.6;
        D_807FBB40->unkC0 = D_807FBB40->unkB8 * 3.0f;
        return;
    }
    if ((D_807FBB40->unk6A & 1) && (D_807FBB40->unk6C & 1)) {
        func_80714CC0(D_8071FBC8, 1.0f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        actorDespawn(D_807FBB40);
    }
}
