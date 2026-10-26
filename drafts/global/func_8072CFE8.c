// func_8072CFE8 (src/global/12E800.c): stage 6, 8 diff lines: if((idx=(unk25&0x7F)+1)<cnt) idx=(u8)idx; else idx=0
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

typedef struct D1Dc9cViewG {
    /* 0x00 */ u8 pad0[0x11];
    /* 0x11 */ u8 unk11;
} D1Dc9cViewG;

typedef struct D1Dc98ViewG {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ void *unk20;
} D1Dc98ViewG;

#define D1DC90G ((D1Dc90ViewG *)D_807FDC90)
#define D1DC9CG ((D1Dc9cViewG *)D_807FDC9C)
#define D1DC98G ((D1Dc98ViewG *)D_807FDC98)
#define D1DCA0 ((D1DcA0View *)D_807FDCA0)

typedef struct D1Pair {
    /* 0x00 */ u8 a;
    /* 0x01 */ u8 b;
} D1Pair;

void func_8072CFE8(s16 *arg0, s16 *arg1, s16 *arg2) {
    s32 idx;
    s32 v;

    if ((idx = (D1DC90G->unk25 & 0x7F) + 1) < D1DC9CG->unk11) {
        idx = (u8)idx;
    } else {
        idx = 0;
    }
    v = ((D1Pair *)D1DC98G->unk20)[idx].a;
    *arg0 = D1DCA0->unk14[v].x;
    *arg1 = D1DCA0->unk14[v].y;
    *arg2 = D1DCA0->unk14[v].z;
}
