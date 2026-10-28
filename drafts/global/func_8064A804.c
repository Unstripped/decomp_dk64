// func_8064A804 (src/global/478F0.c): from .scratch/CsB9/func_8064A804_best.c
typedef struct CsB9Pair {
    /* 0x0 */ s16 a;
    /* 0x2 */ s16 b;
} CsB9Pair;
typedef struct CsB9PzView {
    /* 0x00 */ u8 pad0[0x49];
    /* 0x49 */ u8 unk49;
} CsB9PzView;
extern s16 D_8074822C[][2];
extern CsB9Pair D_80748244[];
void func_80609140(s32, s32, f32, f32, s32, s32);

void func_8064A804(CsState *cs, s16 csId, s16 b, s16 c) {
    u8 *p;
    u8 found;
    s32 row;
    s32 col;
    s32 mask;
    u8 *cell;
    u8 nv;
    s16 idx;
    CsB9Pair *pr;

    found = 0;
    if (*(u8 **)cs == NULL) {
        *(u8 **)cs = func_80610FE8(0xA);
        p = *(u8 **)cs;
        for (row = 0; row < 6; row++) p[row] = 0;
        p[6] = 1;
        p[9] = 0;
    }
    p = *(u8 **)cs;
    row = 0;
    do {
        col = 0;
        if (1) {}
        if (1) {}
        if (1) {}
        if (1) {}
        if (found == 0) {
            do {
                if (D_8074822C[row][col] == ((CsB9PzView *)cs)->unk49) {
                    found = 1;
                }
                col++;
            } while (col < 2 && found == 0);
        }
        row++;
    } while (row < 6 && found == 0);
    row--;
    cell = p + row;
    col--;
    mask = 1 << col;
    if (!(*cell & mask)) {
        nv = *cell | mask;
        *cell = nv;
        if (nv == 3) {
            pr = &D_80748244[(s16)(row * 2 + col)];
            modelSlotSetNodeFrame(csId, pr->a, 0, 0);
            modelSlotSetNodeFrame(csId, pr->b, 0, 0);
            func_80609140(0x2A1, 0x7FFF, 63.0f, 1.0f, 0, 0);
            p[9]++;
            if (p[9] == 6) {
                cs->unk4B[1] = 0x32;
            }
        } else if (p[6] != 0) {
            idx = row * 2 + col;
            pr = &D_80748244[idx];
            modelSlotSetNodeFrame(csId, pr->a, 0, 0);
            modelSlotSetNodeFrame(csId, pr->b, 0, 0);
            p[8] = idx;
            p[7] = row;
        } else {
            p[p[7]] = 0;
            *cell = 0;
            modelSlotSetNodeFrame(csId, D_80748244[p[8]].a, 1, 0);
            modelSlotSetNodeFrame(csId, D_80748244[p[8]].b, 1, 0);
            func_80609140(0x2A2, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
        p[6] ^= 1;
    }
}
