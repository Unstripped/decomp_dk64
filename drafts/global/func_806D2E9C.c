// func_806D2E9C (src/global/D5E10.c): Closest: text diff only li a1,0x7e position (target after lwc1 unk80, mine before lui), beqzl vs beqz+nop after 'if (unk1A2)' ('sel = sel;' after the if-chain removes that), and the 0x80/0x7F else-arms (target keeps both li in own blocks, mine hoists li 0x7f into beqz delay). Also reloc-only: D_FFFF09E8 hi/lo split and rodata (floats 590/987/571/965, double 0.7) are symbols in expected. Tried ternary vs if/else for v, nested ternary, swapped arms, local f32 u, comma, permuter 7min.
typedef struct G10Sub4 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} G10Sub4;

typedef struct G10Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ G10Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x62];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x38];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ u8 padC8[0x7C];
    /* 0x144 */ u8 unk144;
} G10Actor;

typedef struct G10Player {
    /* 0x000 */ u8 pad0[0x1A0];
    /* 0x1A0 */ u16 unk1A0;
    /* 0x1A2 */ u8 unk1A2;
    /* 0x1A3 */ u8 pad1A3[0x4D];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ u8 pad1F4[0x4C];
    /* 0x240 */ u8 unk240;
} G10Player;

typedef struct G10Actor4C {
    /* 0x000 */ u8 pad0[0x12C];
    /* 0x12C */ s16 unk12C;
} G10Actor4C;

#define G10_A ((G10Actor *)D_807FBB40)
#define G10_P ((G10Player *)D_807FD580)

extern f32 D_807536E4[];
extern s32 D_807FBB68;
void func_80687400();
s32 func_806F8AD4();
void func_806F91B4();
f32 func_806F46B0(s16);
void sfxPlayFromActorWithAltitudeCheck();

void func_806D2E9C(void) {
    f32 v;
    f32 r;
    s32 sel;

    if (D_807FBB68 & 2) {
        f64 t = (G10_A->unk80 - 120.0f) * 0.5;

        v = (t > 0.0) ? t : 0.0;
        if (G10_A->unk7C < 590.0f - v) {
            G10_A->unk7C = 590.0f - v;
        }
        if (987.0f + v < G10_A->unk7C) {
            G10_A->unk7C = 987.0f + v;
        }
        if (G10_A->unk84 < 571.0f - v) {
            G10_A->unk84 = 571.0f - v;
        }
        if (965.0f + v < G10_A->unk84) {
            G10_A->unk84 = 965.0f + v;
        }
        G10_A->unk144 &= 0xFFF7;
    }
    func_806DF6D4(0x1B);
    r = func_806F46B0(((G10Actor4C *)D_807FBB4C)->unk12C);
    sel = 0x7E;
    if (r < G10_A->unk80) {
        G10_A->unkC4 = D_807536E4[D_807FD584];
        if (G10_A->unkC0 > 0.0f) {
            G10_A->unkC0 = G10_A->unkC0 * 0.7;
        }
    }
    if (G10_P->unk1A2 != 0) {
        s32 x = G10_P->unk1A0;

        if (x >= 0x8000) {
            x -= 0x10000;
        }
        x += 0x9E8;
        if (x >= 0x7D1) {
            sel = 0x7D;
        } else if (x < -0x7D0) {
            sel = 0x80;
        } else {
            sel = 0x7F;
        }
    }
    if ((sel != G10_A->unk4->unk64) && (G10_A->unk4->unk64 != 0x81)) {
        func_80614EBC(D_807FBB40, sel);
    }
    if ((G10_P->unk1F0 & 0x40000000) && (G10_P->unk240 == 0)) {
        func_80687400();
        G10_P->unk240 = 0x1E;
    }
    if (G10_P->unk240 != 0) {
        G10_P->unk240--;
    }
    if ((G10_A->unk6A & 1) || (G10_P->unk240 == 1)) {
        if (D_807FBB68 & 2) {
            G10_A->unk144 |= 8;
        }
        func_806CFF9C(D_807FBB40);
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 1, 0xFF, 0x7F, 0x1E);
    }
    if (func_8061CB50() == 0) {
        func_806CC948();
        if ((func_806F8AD4(5, D_807FC929) != 0) && !(G10_P->unk1F0 & 0x10000)) {
            func_806F91B4(5, D_807FC929, -1);
        }
    }
    func_806319C4(D_807FBB40, 0);
}
