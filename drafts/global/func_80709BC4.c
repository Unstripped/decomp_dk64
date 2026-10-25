// func_80709BC4 (src/global/10E1D0.c): Stage 1 semantic display-list renderer; frame is 0xD8 vs target 0xC0, shared data layouts recovered.
typedef struct Lg10E1D0_GridCell { s32 offset, width, height; } Lg10E1D0_GridCell;
typedef struct Lg10E1D0_RenderCell { s32 x0, y0, x1, v0, v1, x2, texture; } Lg10E1D0_RenderCell;
typedef struct Lg10E1D0_TextureInfo { s32 texture_offset, width, height; } Lg10E1D0_TextureInfo;
typedef struct Lg10E1D0_RenderInfo { s32 vertex_count, unk4; f32 *vertices; Lg10E1D0_RenderCell *cells; u16 *screen_vertices[2]; s32 *column_counts, *column_ends, *column_starts; } Lg10E1D0_RenderInfo;
extern Lg10E1D0_GridCell *D_807FD9B4;
extern Lg10E1D0_TextureInfo D_80754F80[];
extern u16 D_80754FC8[];
s16 func_8070C200(f32);

void func_80709BC4(Gfx **arg0, Lg10E1D0_RenderInfo *arg1, u8 *arg2) {
    Gfx *glist = *arg0;
    s32 vertex, coordinate, row, column, texture, previous_texture;
    if (arg1->vertex_count > 0) {
        for (vertex = coordinate = 0; vertex < arg1->vertex_count; vertex++, coordinate += 3) {
            u16 *out = (u16 *)((u8 *)arg1->screen_vertices[D_807444FC] + vertex * 0x10);
            out[0] = func_8070C200(arg1->vertices[coordinate]);
            out[1] = func_8070C200(arg1->vertices[coordinate + 1]);
            out[2] = func_8070C200(arg1->vertices[coordinate + 2]);
        }
    }
    for (row = 0; arg1->column_counts[row] != 0; row++) {
        s32 base = arg1->column_starts[row];
        s32 count = arg1->column_ends[row] - base + 1;
        glist->words.w0 = ((count & 0xFF) << 12) | 0x01000000 | ((count & 0x7F) * 2);
        glist++->words.w1 = osVirtualToPhysical((u8 *)arg1->screen_vertices[D_807444FC] + base * 0x10);
        previous_texture = -0x63;
        for (column = 0; column < arg1->column_counts[row]; column++) {
            Lg10E1D0_RenderCell *cell = &arg1->cells[row * 7 + column];
            texture = cell->texture;
            if (texture != previous_texture) {
                previous_texture = texture;
                if (texture < 0) {
                    Lg10E1D0_TextureInfo *info = &D_80754F80[-1 - texture];
                    glist->words.w0 = 0xFD100000; glist++->words.w1 = D_80754FC8 + info->texture_offset * 2;
                    glist->words.w0 = 0xF5100000; glist++->words.w1 = 0x07000000;
                    glist->words.w0 = 0xE6000000; glist++->words.w1 = 0;
                    glist->words.w0 = 0xF3000000; glist++->words.w1 = 0x07000000 | ((((info->height - 1) * info->width - 1) & 0x7FF) << 12);
                    glist->words.w0 = 0xE7000000; glist++->words.w1 = 0;
                    glist->words.w0 = 0xF5100000 | ((((info->width * 2) + 7) >> 3) & 0x1FF) << 9; glist++->words.w1 = 0;
                    glist->words.w0 = 0xF2000000; glist++->words.w1 = (((info->height - 2) * 4) & 0xFFF) | ((((info->width - 1) * 4) & 0xFFF) << 12);
                } else {
                    Lg10E1D0_GridCell *grid = &D_807FD9B4[texture];
                    glist->words.w0 = 0xFD10013F; glist++->words.w1 = arg2 + grid->offset * 2;
                    glist->words.w0 = 0xF5100000 | ((((grid->width * 2) + 9) >> 3) & 0x1FF) << 9; glist++->words.w1 = 0x07000000;
                    glist->words.w0 = 0xE6000000; glist++->words.w1 = 0;
                    glist->words.w0 = 0xF4000000; glist++->words.w1 = 0;
                    glist->words.w0 = 0xF5100000 | ((((grid->width * 2) + 9) >> 3) & 0x1FF) << 9; glist++->words.w1 = 0;
                    glist->words.w0 = 0xF2000000; glist++->words.w1 = (((grid->height - 1) * 4) & 0xFFF) | (((grid->width * 4) & 0xFFF) << 12);
                }
            }
            glist->words.w0 = 0x02140000 | (((cell->x0 - base) * 2) & 0xFFFF); glist++->words.w1 = cell->v0;
            glist->words.w0 = 0x02140000 | (((cell->y0 - base) * 2) & 0xFFFF); glist++->words.w1 = cell->v1;
            glist->words.w0 = 0x02140000 | (((cell->x1 - base) * 2) & 0xFFFF); glist++->words.w1 = cell->x2;
            glist->words.w0 = 0x05000000 | ((((cell->x0 - base) * 2) & 0xFF) << 16) | ((((cell->y0 - base) * 2) & 0xFF) << 8) | (((cell->x1 - base) * 2) & 0xFF); glist++->words.w1 = 0;
        }
    }
    *arg0 = glist;
}
