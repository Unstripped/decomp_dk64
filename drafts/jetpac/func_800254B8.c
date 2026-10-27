// func_800254B8 (src/jetpac/1460.c): Stage 6, text-identical (code + reloc targets match); only .rodata differs: expected has 8 zero bytes after the 0.97 double (hidden TU boundary / rodata pad, AB28..AB2F), C puts them at end of rodata. Needs: s32 i local with 'cell->color[i = 2] = ((u8*)arg3)[i]' (frame 0x30) + three 'if (1) { }' before the color copy (reg alloc item=v0/cell=a0/n=v1). Found by permuter.
void func_800254B8(JetpacSprite *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    JetpacCell *cell;
    s32 i;
    JetpacCellItem *item;

    item = NULL;
    if (arg1 >= 0 && arg2 >= 0 && arg1 < 0x101 && arg2 < 0xC1) {
        cell = &D_8002F3D0[0][0] + (arg1 / 8 + ((arg2 / 8) << 5));
        if (cell->count < 6) {
            item = &cell->items[cell->count++];
        }
        if (item != NULL) {
            item->x = arg1;
            item->y = arg2;
            *(s32 *)&item->pad8[0] = arg4;
            item->unkC = (s32)arg0;
            if (cell->color[3] == 0 || (cell->color[3] < 0xFF && jetpacRandFloat() > 0.97)) {
                if (1) { }
                if (1) { }
                if (1) { }
                cell->color[0] = ((u8 *)arg3)[0];
                cell->color[1] = ((u8 *)arg3)[1];
                cell->color[i = 2] = ((u8 *)arg3)[i];
                cell->color[3] = ((u8 *)arg3)[3];
            }
        }
    }
}
