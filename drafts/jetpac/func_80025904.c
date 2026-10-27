// func_80025904 (src/jetpac/1460.c): Stage 6: text identical except temp regs of the (s16)(x+0x20)*4 / (y+0x18)*4 args (target t3,t5,t7,t4 then count reload t6; ours t2,t9,t0,t5 then t3) and tail t9/t0 vs t4/t2. Tried decl-order permutations (40), px/py locals, dead statements, permuter 200s: no change.
void func_80025904(Gfx **arg0) {
    JetpacCell *cell;
    JetpacCellItem *item;
    s32 item_idx;
    Gfx *g;
    s32 col;
    s32 row;

    g = *arg0;
    cell = &D_8002F3D0[0][0];
    for (row = 0; row < 24; row++) {
        col = 0;
        do {
            if (cell->count != 0) {
                gDPSetPrimColor(g++, 0, 0, cell->color[0], cell->color[1], cell->color[2], 0xFF);
            }
            item = &cell->items[0];
            if (cell->count > 0) {
                item_idx = 0;
                do {
                    func_8070E8F0(&g, item->unkC);
                    func_8070F2C8(0x400, 0x400, item->unkB, 0);
                    func_8070F2FC(&g, (s16)(item->x + 0x20) * 4, (s16)(item->y + 0x18) * 4);
                    item_idx++;
                    item++;
                } while (item_idx < cell->count);
            }
            col++;
            cell++;
        } while (col != 32);
    }
    *arg0 = g;
}
