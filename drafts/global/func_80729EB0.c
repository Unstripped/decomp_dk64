// func_80729EB0 (src/global/12E800.c): TEXT-IDENTICAL, RELOC ONLY (fdiff whole-file FAILED because expected resolves D_8075FD00 as a raw lui 0x8076 with no reloc: reloc count 801 vs 799; jtbl/D_8075FD18 as .rodata vs named). Instruction stream, frame (120), rodata bytes (jtbl idx 0x42/0x45) all match. Trailing unused 's32 e;' local is needed to put the s16 spill at 100(sp).
typedef struct D1Dc90ViewJ {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0xA];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[2];
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ u8 pad20;
    /* 0x21 */ u8 unk21;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ u8 unk24;
} D1Dc90ViewJ;

typedef struct D1Dc98ViewJ {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ u8 pad30[0x16];
    /* 0x46 */ u16 unk46;
} D1Dc98ViewJ;

typedef struct D1ActorViewJ {
    /* 0x00 */ u8 pad0[0x5C];
    /* 0x5C */ u16 unk5C;
    /* 0x5E */ u8 pad5E[0xC];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 pad6C[0x10];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x30];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x28];
    /* 0xE4 */ s16 unkE4;
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[6];
    /* 0xEE */ s16 unkEE;
} D1ActorViewJ;

#define D1AJ ((D1ActorViewJ *)D_807FBB40)
#define D1DC90J ((D1Dc90ViewJ *)D_807FDC90)
#define D1DC98J ((D1Dc98ViewJ *)D_807FDC98)

s32 func_80611A44(void);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 func_806CC10C(s16, s16);
s16 func_806CC190(s16, s16, f32);
void func_80614D00(void *, f32, f32);

void func_80729EB0(u8 mode, f32 arg1, f32 arg2, u16 flags) {
    s16 *cur = &D1AJ->unkE6;
    s16 *cur2 = &D1AJ->unkEE;
    s16 *tgt = &D1DC90J->unk8;
    f32 spd;
    u8 s;
    s16 dist;
    s32 e;

    switch (mode) {
        case 1:
            if (D1DC90J->unk22-- == 0) {
                s = D1DC90J->unk21;
                *tgt = *cur + ((((func_80611A44() >> 15) % (s * 2)) - s) << 15) / 0x168;
                D1DC90J->unk22 = D1DC90J->unk23;
                D1DC98J->unk46 &= ~0x2000;
                if (D1AJ->unkE6 & 1) {
                    D1DC90J->unk24 = (func_80611A44() >> 15) % 0xB4;
                }
            }
            break;
        case 0x24:
            *tgt = mathAngleBetweenPoints2D(D1AJ->unk7C, D1AJ->unk84, arg1, arg2);
            break;
        case 2:
        case 3:
        case 4:
        case 0x15:
        case 0x23:
        case 0x26:
        case 0x33:
        case 0x34:
        case 0x42:
        case 0x45:
        case 0x5B:
            *tgt = mathAngleBetweenPoints2D(arg1, arg2, D1AJ->unk7C, D1AJ->unk84);
            break;
        case 0x10:
            *tgt = mathAngleBetweenPoints2D(D1AJ->unk7C, D1AJ->unk84, arg1, arg2);
            break;
        case 0x35:
            if ((func_80611A44() >> 15) % 0x1E == 0) {
                D1DC90J->unk24 = (func_80611A44() >> 15) % 0xB4;
            }
        case 7:
            *tgt = mathAngleBetweenPoints2D(D1DC90J->unkA, D1DC90J->unkE, D1AJ->unk7C, D1AJ->unk84);
            break;
        case 0:
            *tgt = *cur;
            break;
    }
    dist = func_806CC10C(*tgt, *cur);
    if (!(flags & 0x100) && mode != 0x37) {
        if (flags & 4) {
            spd = (u32)D1DC90J->unk1E;
        } else {
            spd = (D1DC90J->unk1A & 0x80)
                ? (D1DC90J->unk1E / 2)
                : ((u32)D1DC90J->unk1E /
                   (((0.1 < D1AJ->unkB8 / 30.0 ? D1AJ->unkB8 / 30.0 : 0.1) < 2.0)
                        ? (0.1 < D1AJ->unkB8 / 30.0 ? D1AJ->unkB8 / 30.0 : 0.1)
                        : 2.0));
        }
        *cur = func_806CC190(*cur, *tgt, spd);
        if ((D1AJ->unk6A & 1) || (flags & 0x80) || (D1AJ->unk5C & 0x40)) {
            *cur2 = func_806CC190(*cur2, *cur, (u32)D1DC90J->unk1F);
        }
    }
    if (flags & 0x40) {
        D1AJ->unkE4 = (((dist > -0x320 ? dist : -0x320) < 0x320 ? (dist > -0x320 ? dist : -0x320) : 0x320) - D1AJ->unkE4) * 0.1 + D1AJ->unkE4;
    }
    if (flags & 4) {
        if (dist != 0) {
            f32 t = dist * D1DC98J->unk2C;
            f32 a = 0.0f < t ? t : -t;

            func_80614D00(D_807FBB40, a > 1.0 ? 1.0 : a, 0.0f);
        }
    }
}
