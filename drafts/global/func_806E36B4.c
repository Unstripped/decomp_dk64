// func_806E36B4 (src/global/E4090.c): Stage 6: text equal except lda D_807FBB40 reg: target hoists lui/addiu a3 above first branch; mine places it at the join (D_807FD580 lda takes v1, D_807FBB40 a2). Permuter hint: adding 'if (!D_807FBB40 && !D_807FBB40 && !D_807FBB40) {}' between the two ifs hoists it (18 diff lines left: lw v1/li t6 scheduled above the compare).
typedef struct G24Sub {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ u32 unk58;
} G24Sub;

typedef struct G24Main {
    /* 0x000 */ u8 pad0[0x2C];
    /* 0x02C */ f32 unk2C;
    /* 0x030 */ f32 unk30;
    /* 0x034 */ u8 pad34[4];
    /* 0x038 */ f32 unk38;
    /* 0x03C */ u8 pad3C[2];
    /* 0x03E */ s16 unk3E;
    /* 0x040 */ u8 pad40[0x10];
    /* 0x050 */ s16 unk50;
    /* 0x052 */ u8 pad52[2];
    /* 0x054 */ f32 unk54;
    /* 0x058 */ u32 unk58;
    /* 0x05C */ u8 pad5C[0xA4];
    /* 0x100 */ s32 unk100;
    /* 0x104 */ u8 pad104[0x9C];
    /* 0x1A0 */ u16 unk1A0;
    /* 0x1A2 */ u8 unk1A2;
    /* 0x1A3 */ u8 unk1A3;
    /* 0x1A4 */ u8 pad1A4[8];
    /* 0x1AC */ G24Sub *unk1AC;
} G24Main;

typedef struct G24Act {
    /* 0x000 */ u8 pad0[0x6A];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[2];
    /* 0x06E */ s16 unk6E;
    /* 0x070 */ u8 pad70[0x48];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ u8 padC8[0x18];
    /* 0x0E0 */ f32 unkE0;
    /* 0x0E4 */ u8 padE4[2];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} G24Act;

#define G24_M ((G24Main *)D_807FD580)
#define G24_A ((G24Act *)D_807FBB40)
#define G24_PAD(sym, T) (*(T *)((u8 *)&(sym) + D_807FC929 * 0x34))

extern u32 D_80767CC0;
extern f32 D_807535CC[];

extern u32 D_80767CC0;
void func_806E36B4(void) {
    u32 sel;

    if (G24_PAD(D_807FD63C, u16) & 0x8000) {
        G24_M->unk58 = D_80767CC0;
    }
    if ((D_80767CC0 - G24_M->unk58) < 0xF) {
        G24_A->unk154 = 0x4C;
        G24_A->unk155 = 0;
        G24_M->unk54 = D_807535CC[D_807FD584];
        G24_M->unk50 = 0;
        sel = G24_M->unk1AC->unk58;
        switch (sel) {
            case 0x3D:
            case 0x3F:
            case 0x40:
            case 0x41:
            case 0x42:
            case 0x55:
            case 0x82:
                func_80614EBC(D_807FBB40, 0x1CB);
                break;
            default:
                func_80614E78(D_807FBB40, 0x30);
                break;
        }
        G24_M->unk58 = D_80767CC0 - 0x1E;
    }
}
