// func_806D3608 (src/global/D5E10.c): text-identical, reloc only: double 0.15 (D_8075CD08) is .rodata+0x18 vs symbol in expected; rest identical
typedef struct G10Sub4 {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ f32 unk38;
} G10Sub4;

typedef struct G10Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ G10Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x78];
    /* 0x080 */ f32 unk80;
    /* 0x084 */ u8 pad84[0x18];
    /* 0x09C */ f32 unk9C;
} G10Actor;

#define G10_A ((G10Actor *)D_807FBB40)

extern s32 D_807FBB64;
s32 func_8061CB50();
void func_806D3530();

void func_806D3608(void) {
    f32 temp = G10_A->unk4->unk38 / 0.15;

    if (!(D_807FBB64 & 0x40000) && (func_8061CB50() == 0)) {
        if (D_8076A0A8 == 0xE) {
            func_806D3530();
            return;
        }
        if ((290.0f * temp) < (G10_A->unk9C - G10_A->unk80)) {
            func_806EB0C0(0x2C, 0, D_807FC929);
        }
    }
}
