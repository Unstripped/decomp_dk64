// func_807095E4 (src/global/10E1D0.c): stage 2: inferred grid-cell dimensions and edge handling; loop layout and cell structure remain unmatched
typedef struct R1F10E1D0a_GridCell { s32 offset, width, height; } R1F10E1D0a_GridCell;
extern R1F10E1D0a_GridCell *D_807FD9B4;
void func_807095E4(s32 width, s32 height) {
    s32 column, row, columns = D_80744490 / width, rows = D_80744494 / height;
    s32 last_width = D_80744490 - (columns * width), last_height = D_80744494 - (rows * height);
    if (last_width > 0) columns++; if (last_height > 0) rows++;
    for (row = 0; row < rows; row++) for (column = 0; column < columns; column++) {
        D_807FD9B4[(row * columns) + column].offset = (row * height) + (column * width);
        D_807FD9B4[(row * columns) + column].width = column == columns - 1 ? last_width : width;
        D_807FD9B4[(row * columns) + column].height = row == rows - 1 ? last_height : height;
    }
}
