// func_8064A804 (src/global/478F0.c): CsNM4 stage 4: 14 diff lines (was 103). Matched: loop regs row=t0/col=v1/p=t1, frame slots (decl order p,found,nv,idx,row,col,pr), first block. Key finds: u8 nv assigned INSIDE the compare 'D[row][col] == (nv = cs->unk49)' fixes the whole row/col/p shift; 'p[row] = p[row] | (1<<col); nv = p[row];' gives sb of unmasked or. Dead stmts needed: one 'if (1) {}' after col=0, 'if (cs && cs) {}' after the p[row]| store, 'if (nv == 0) {}' before p[6]^=1 (this last one spills nv: sw a0,44 = remaining slot diff). Remaining diff: target spills col (sw v1,0x38 at both loop exits + lw v1,0x38 after, i.e. col post-loop is a separate register web) -- mine keeps col in v1 with row-- in beqzl delay slot; addiu v1,v1,-1 vs li t4,1 order; or/andi regs a0 vs t7 (nv spill sw a0,44 vs sw v0,44 pr slot 0x2c). Tried: decl-order perms (5040), sweep incl. extras and forms, permuter 600s (no 0), separate r2/c2 post vars, col-1 inline.
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
    u8 nv;
    s16 idx;
    s32 row;
    s32 col;
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
        if (!found) {
            do {
                if (D_8074822C[row][col] == (nv = ((CsB9PzView *)cs)->unk49)) {
                    found = 1;
                }
                col++;
            } while (col < 2 && !found);
        }
        row++;
    } while (row < 6 && !found);
    row--;
    col--;
    if (!(p[row] & (1 << col))) {
        p[row] = p[row] | (1 << col);
        if (cs && cs) {}
        nv = p[row];
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
            p[row] = 0;
            modelSlotSetNodeFrame(csId, D_80748244[p[8]].a, 1, 0);
            modelSlotSetNodeFrame(csId, D_80748244[p[8]].b, 1, 0);
            func_80609140(0x2A2, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
        if (nv == 0) {}
        p[6] ^= 1;
    }
}
