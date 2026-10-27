// func_80025904 (src/jetpac/1460.c): stage 6: text identical except temp regs of the (s16)(x+0x20)*4 / (y+0x18)*4 args (target t3,t5,t7,t4, count reload t6; ours t2,t9,t0,t5,t3) and tail t9/t0 vs t4/t2. Prim-color block temps match only with gDPSetPrimColor (a hand-written WRITE_GFX shifts them), so temp naming follows IL. Tried (all identical output): arg forms, loop forms, stmt order, line layout, dead first statements, extra locals, prototype type changes, dummy if(!x){} uses, permuter 240s.
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
