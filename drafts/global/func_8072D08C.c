// func_8072D08C (src/global/12E800.c): PARKED NON_MATCHING, stage 5: identical except u8 key spill slot: target sb 0x1E(sp) (x/y/z at 0x1C/0x1A/0x18), built 0x1F(sp) with key declared first. Needs a way to put the u8 at 0x1E; also t6/t8 swapped lui order follows.
typedef struct D1Pair {
    /* 0x00 */ u8 a;
    /* 0x01 */ u8 b;
} D1Pair;

typedef struct D1Pt {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ s16 pad6[2];
} D1Pt; // size = 0xA

typedef struct D1DcA0View {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ D1Pt *unk14;
} D1DcA0View;

typedef struct D1Dc90ViewG {
    /* 0x00 */ u8 pad0[0x25];
    /* 0x25 */ u8 unk25;
} D1Dc90ViewG;

typedef struct D1Dc98ViewG {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ void *unk20;
} D1Dc98ViewG;

#define D1DC90G ((D1Dc90ViewG *)D_807FDC90)
#define D1DC98G ((D1Dc98ViewG *)D_807FDC98)
#define D1DCA0 ((D1DcA0View *)D_807FDCA0)

void func_8072CFE8(s16 *, s16 *, s16 *);
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);

s32 func_8072D08C(void) {
    u8 key;
    s16 x;
    s16 y;
    s16 z;

    key = ((D1Pair *)D1DC98G->unk20)[D1DC90G->unk25 & 0x7F].a;
    func_8072CFE8(&x, &y, &z);
    return mathAngleBetweenPoints2D(x, z, D1DCA0->unk14[key].x, D1DCA0->unk14[key].z);
}
