// func_8072D13C (src/global/12E800.c): stage 3: size matches (415 insns) and structure/switch/ra-as-variable layout match; frame 0x30 vs target 0x38 (target locals: off@0x18, key@0x2A, moved@0x2D, z/y/x@0x2E/0x30/0x32, type@0x34 with 14 unused bytes 0x1C-0x29), t-reg numbering differs (target idx t3 loaded raw then dir=ra). Tried decl order permutations, idx=unk25; dir=idx&0x80; idx&=0x7F (gets size 415).
typedef struct D1Pair {
    /* 0x00 */ u8 a;
    /* 0x01 */ u8 b;
} D1Pair;

typedef struct D1Dc9cViewG {
    /* 0x00 */ u8 pad0[0xD];
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 pad0E[3];
    /* 0x11 */ u8 unk11;
} D1Dc9cViewG;

typedef struct D1Dc98ViewG {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ void *unk20;
} D1Dc98ViewG;

#define D1DC9CG ((D1Dc9cViewG *)D_807FDC9C)
#define D1DC98G ((D1Dc98ViewG *)D_807FDC98)

extern u16 D_80744508;
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 func_8072D08C(void);
void func_8072B324(Actor *, s32);

typedef struct D1Dc90ViewK {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0xA];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[4];
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 pad21[4];
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 pad26[6];
    /* 0x2C */ s16 unk2C;
} D1Dc90ViewK;

typedef struct D1PtB {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ u8 pad6;
    /* 0x07 */ u8 r;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 pad9;
} D1PtB; // size = 0xA

typedef struct D1DcA0ViewB {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ u8 *unk14;
} D1DcA0ViewB;

typedef struct D1ActorViewK {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[0x20];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ u8 pad8C[4];
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 pad94[0x52];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[6];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} D1ActorViewK;

#define D1DC90K ((D1Dc90ViewK *)D_807FDC90)
#define D1DCA0B ((D1DcA0ViewB *)D_807FDCA0)
#define D1AK ((D1ActorViewK *)D_807FBB40)
#define D1PT(off) ((D1PtB *)(D1DCA0B->unk14 + (off)))

u8 func_8072D13C(u8 arg0, u8 arg1) {
    u8 type;
    s16 x;
    s16 y;
    s16 z;
    u8 moved;
    u8 key;
    s32 v;
    s32 idx;
    s32 dir;
    s32 off;

    idx = D1DC90K->unk25;
    dir = idx & 0x80;
    idx = idx & 0x7F;
    key = ((D1Pair *)D1DC98G->unk20)[idx].a;
    type = ((D1Pair *)D1DC98G->unk20)[idx].b;
    off = key * 10;
    x = D1PT(off)->x;
    y = D1PT(off)->y;
    z = D1PT(off)->z;
    moved = ((D1AK->unk7C - x) * (D1AK->unk7C - x) + (D1AK->unk84 - z) * (D1AK->unk84 - z)) < (f32)(D1PT(off)->r * D1PT(off)->r);
    if (arg1 & 1) {
        if (D1AK->unk88 == D1AK->unk7C && D1AK->unk90 == D1AK->unk84) {
            D1DC90K->unk20++;
            if (D1DC90K->unk20++ > 0x10) {
                moved = 1;
                D1DC90K->unk20 = 0;
            }
        } else {
            D1DC90K->unk20 = 0;
        }
    } else {
        D1DC90K->unk20 = 0;
    }
    switch (arg0) {
        case 0x49:
            v = idx + 1;
            key = 0;
            if (v < D1DC9CG->unk11) {
                key = v;
            }
            D1AK->unkEE = D1AK->unkE6 = mathAngleBetweenPoints2D(D1PT(((D1Pair *)D1DC98G->unk20)[key].a * 10)->x, D1PT(((D1Pair *)D1DC98G->unk20)[key].a * 10)->z, x, z);
        case 0x42:
        case 0x5B:
            D1DC90K->unkA = x;
            D1DC90K->unkC = y;
            D1DC90K->unkE = z;
            break;
        case 2:
        case 0x26:
        case 0x60:
            if (moved) {
                if (type == 6) {
                    D1DC90K->unk25 = D1PT(off)->unk8;
                } else if (idx + 1 < D1DC9CG->unk11) {
                    D1DC90K->unk25 = idx + 1;
                } else {
                    D1DC90K->unk25 = 0;
                }
            } else {
                D1DC90K->unkA = x;
                D1DC90K->unkC = y;
                D1DC90K->unkE = z;
            }
            break;
        case 3:
            if (moved) {
                if (dir != 0) {
                    if (idx > 0) {
                        idx = (u8)(idx - 1);
                    } else {
                        idx = (u8)(idx + 1);
                        dir = 0;
                    }
                } else if (idx < D1DC9CG->unk11 - 1) {
                    idx = (u8)(idx + 1);
                } else {
                    idx = (u8)(idx - 1);
                    dir = 0x80;
                }
                D1DC90K->unk25 = dir | idx;
            } else {
                D1DC90K->unkA = x;
                D1DC90K->unkC = y;
                D1DC90K->unkE = z;
            }
            break;
    }
    idx = D1DC90K->unk25 & 0x7F;
    if (moved) {
        D1DC90K->unk1A |= 4;
        switch (type) {
            case 1:
                key = ((D1Pair *)D1DC98G->unk20)[idx].a;
                D1AK->unkEE = D1AK->unkE6 = func_8072D08C();
                D1AK->unk7C = D1PT(key * 10)->x;
                D1AK->unk80 = D1PT(key * 10)->y;
                D1AK->unk84 = D1PT(key * 10)->z;
                break;
            case 2:
                D1AK->unk154 = 0x26;
                D1AK->unk155 = 0;
                break;
            case 4:
                D1AK->unk154 = 0x19;
                D1AK->unk155 = 0;
                D1DC90K->unk2C = D1PT(off)->unk8;
                break;
            case 5:
                func_8072B324(D_807FBB40, D1PT(off)->unk8);
                return moved;
            case 7:
                D1AK->unk154 = 0x3B;
                moved = 0;
                break;
            case 8:
                D1AK->unk154 = 0x13;
                D1AK->unk155 = 0;
                break;
            case 3:
                if (D1AK->unk58 == 0xAF) {
                    D1AK->unk154 = 0x37;
                    D1AK->unk155 = 0;
                }
                D_80744508++;
                D1AK->unk154 = 0x40;
                break;
        }
    } else {
        D1DC90K->unk1A &= 0xFFFB;
    }
    return moved;
}
