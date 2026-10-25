// func_806C9D7C (src/global/CC800.c): G01 stage 6 near-miss: row ptr v0 + unfolded sll zero; i/v swapped regs
extern u8 D_807FC950[][0x5E];
extern u8 D_8074E77C[];

typedef struct G01Row {
    /* 0x00 */ u8 pad0[0x42];
    /* 0x42 */ u16 unk42[8];
    /* 0x52 */ u8 pad52[0xC];
} G01Row;

/* stage 6: target keeps the row pointer in v0 and builds the walking pointer as v0 + (0 << 1) (sll t9,zero,1 not folded),
 * i in a0, v in v1; ours folds to a1 = base, i in v1, v in a0. Tried struct member array, u16* + 0x21 index, for/break. */
s32 func_806C9D7C(void) {
    G01Row *row = (G01Row *)D_807FC950[D_8074E77C[0]];
    s32 i;
    s32 v;

    i = 0;
    do {
        v = row->unk42[i] > 0;
        i++;
    } while (i < 8 && !v);
    return v;
}
