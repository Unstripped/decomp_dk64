// func_806D8B08 (src/global/D5E10.c): text-identical, reloc only: C matches instruction-for-instruction (nv2 form, goto end tail), fdiff FAILED only because the switch jump table reloc is .rodata+0x124 vs jtbl_8075CE14; parked NON_MATCHING in src copy
#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Struct807FD580 *D_807FD580;
extern s16 D_807FD584;
extern f32 D_80753AFC[];
extern s16 D_80753A78[];
extern f32 D_80753A5C[];
s32 func_806DF6D4();
void func_806319C4();
void func_806CC5DC();
void func_806CC638(f32);
f32 func_806CD898(f32, f32, f32);
void func_80614D00(void *, f32, f32);
void func_80614E78(Actor *, s32);

typedef struct G16Player {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[2];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ u8 pad26[6];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0x14];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ u8 pad52[2];
    /* 0x54 */ f32 unk54;
    /* 0x58 */ u8 pad58[0x14];
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ s16 unk70;
    /* 0x72 */ u8 pad72[0x3E];
    /* 0xB0 */ f32 unkB0;
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x48];
    /* 0x104 */ s32 unk104;
} G16Player;

typedef struct G16Sub4 {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0xC];
    /* 0x48 */ f32 unk48;
    /* 0x4C */ u8 pad4C[0x2C];
    /* 0x78 */ s32 unk78;
} G16Sub4;

typedef struct G16Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ G16Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[6];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0xE];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x24];
    /* 0x0AC */ f32 unkAC;
    /* 0x0B0 */ u8 padB0[8];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ u8 padC8[0x1C];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[4];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0xC];
    /* 0x0FC */ u8 unkFC;
    /* 0x0FD */ u8 padFD[0x47];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0x10];
    /* 0x155 */ u8 unk155;
} G16Actor;

#define G16_P ((G16Player *)D_807FD580)
#define G16_A ((G16Actor *)D_807FBB40)

extern s16 D_807538C8[];
extern s16 D_80753A88[];
extern f32 D_80753AE0[];
void effectSpawnAuraBurst(u8);
void func_806D0EBC(void *);

void func_806D8B08(void) {
    s16 v;
    f32 t;
    f32 fv0;

    G16_P->unk24 = G16_P->unk24 + 1;
    G16_P->unk2C = D_80753AFC[D_807FD584];
    switch (G16_A->unk155) {
        case 0:
            func_806DF6D4(0x4C);
            t = D_80753A5C[D_807FD584];
            G16_A->unkC0 = func_806CD898(G16_A->unkC0, t, G16_P->unk1C);
            if (t <= G16_A->unkC0) {
                if (G16_A->unkB8 != 0.0f || G16_P->unk10 != 0) {
                    G16_A->unk155 = 3;
                } else {
                    G16_A->unk155 = 2;
                }
                G16_A->unk4->unk78 &= ~0x4000;
            }
            func_806CC5DC();
            effectSpawnAuraBurst(1);
            goto end;
        case 1:
            func_806DF6D4(0x4F);
            func_806CC638(0.0f);
            if (G16_P->unk10 == 0) {
                G16_A->unk155 = 3;
            }
            t = G16_P->unk10 / 7.5 + 1.0;
            if (G16_A->unk4->unk48 < t) {
                func_80614D00(D_807FBB40, t, 0.0f);
            } else {
                func_80614D00(D_807FBB40, t, 15.0f);
            }
            effectSpawnAuraBurst(2);
            fv0 = G16_A->unkAC;
            if (fv0 < (f32)D_807538C8[D_807FD584] + G16_A->unk80) {
                G16_A->unk80 = fv0 - (f32)D_807538C8[D_807FD584];
            }
            goto end;
        default:
            func_806DF6D4(0x54);
            func_806CC638(D_80753A5C[D_807FD584]);
            if (G16_A->unkB8 != 0.0f) {
                G16_P->unk18 = 0;
                G16_A->unk155 = 3;
            } else {
                if (G16_P->unk50 != 0) {
                    G16_P->unk50 = G16_P->unk50 - 1;
                    if (G16_P->unk50 == 0) {
                        func_80614E78(D_807FBB40, 0x34);
                    }
                }
            }
            func_806D0EBC(D_807FBB40);
            goto end;
        case 3:
            func_806DF6D4(0x50);
            func_806CC638(0.0f);
            break;
        case 4:
            func_806DF6D4(0x51);
            G16_P->unk12 = G16_A->unkE8;
            G16_P->unk14 = G16_A->unkE6;
            G16_P->unk38 = D_80753AE0[D_807FD584];
            G16_P->unk10 = D_80753A88[D_807FD584];
            func_806CC638(0.0f);
            G16_A->unk155 = G16_A->unk155 + 1;
            break;
        case 5:
            func_806DF6D4(0x51);
            func_806CC638(0.0f);
            break;
        case 6:
            func_806DF6D4(0x52);
            func_806CC638(0.0f);
            break;
        case 7:
            func_806DF6D4(0x51);
            func_806CC638(0.0f);
            break;
        case 8:
            func_806DF6D4(0x53);
            func_806CC638(0.0f);
            break;
    }
    if (G16_A->unkB8 == 0.0f || G16_P->unk18 != 0) {
        G16_P->unk50 = D_80753A78[D_807FD584];
        func_80614D00(D_807FBB40, 0.5f, (f32)G16_P->unk50);
        G16_A->unk155 = 2;
    }
    func_806D0EBC(D_807FBB40);
end:
    func_806319C4(D_807FBB40, 0);
}
