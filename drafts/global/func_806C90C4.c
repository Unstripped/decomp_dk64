// func_806C90C4 (src/global/CC800.c): G01 stage 6 near-miss: only order of two lw sp24 before bgtzl
typedef struct G01Sub104 {
    /* 0x000 */ u8 pad0[0x15F];
    /* 0x15F */ u8 unk15F;
} G01Sub104;

typedef struct G01Ctl {
    /* 0x000 */ u8 pad0[0x50];
    /* 0x050 */ s16 unk50;
    /* 0x052 */ u8 pad52[0xB2];
    /* 0x104 */ G01Sub104 *unk104;
} G01Ctl;

typedef struct G01Act {
    /* 0x000 */ u8 pad0[0x6A];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x18];
    /* 0x0A0 */ f32 unkA0;
    /* 0x0A4 */ u8 padA4[8];
    /* 0x0AC */ f32 unkAC;
    /* 0x0B0 */ u8 padB0[0x36];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x1E];
    /* 0x174 */ G01Ctl *unk174;
} G01Act;

typedef struct G01Pos {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 unk9;
} G01Pos;

#define G01A ((G01Act *)D_807FBB48)

extern s16 D_8076AEE2;
extern s32 D_807FBB60;
extern s8 D_80770DC9;
G01Pos *func_806C96C4(s32);
void func_80614D00(Actor *, f32, f32);
void func_8067ACB4(Actor *);
void func_80614E78(Actor *, s32);
void func_806F39E8(Actor *, void *, s32);

/* stage 6: only the order of the two `lw sp24` reloads before bgtzl differs (else-branch copy first in target) */
void func_806C90C4(s32 arg0) {
    G01Ctl *sp24 = G01A->unk174;
    G01Pos *p = func_806C96C4(arg0);

    D_8076AEE2 = 0;
    D_807FBB60 &= ~0x400;
    switch (p->unk8) {
    case 2:
        G01A->unk154 = 0x4F;
        G01A->unk155 = 3;
        func_80614D00(D_807FBB48, 0.5f, 0.0f);
        sp24->unk50 = 1;
        G01A->unk6A |= 4;
        func_8067ACB4(D_807FBB48);
        func_80614E78(D_807FBB48, 0x34);
        /* fallthrough */
    case 0:
        G01A->unkAC = -10000.0f;
        G01A->unk7C = p->unk0;
        G01A->unk80 = G01A->unkA0 = p->unk2;
        G01A->unk84 = p->unk4;
        G01A->unkE6 = (p->unk6 / 255.0) * 4095.0;
        G01A->unkEE = G01A->unkE6;
        break;
    case 1:
        func_806F39E8(D_807FBB48, p, 0x32);
        break;
    }
    G01A->unk6A &= 0xFDFF;
    if ((s32)p->unk7 <= 0) {
        sp24->unk104->unk15F = 1;
    } else {
        sp24->unk104->unk15F = p->unk7;
    }
    if (p->unk9 & 1) {
        D_80770DC9 = 1;
    }
}
