// func_80703AB0 (src/global/103AB0.c): stage 2 display-list builder draft; compiled and fdiffed, command pointer order/frame differ
typedef struct { s16 x0, y0; u8 pad0[0xB]; u8 a0; s16 x1, y1; u8 pad1[0xB]; u8 a1; s16 x2, y2; u8 pad2[0xB]; u8 a2; s16 x3, y3; u8 pad3[0xB]; u8 a3; } R1F103AB0cRectView;
extern u8 D_1000118[], D_2000080[], D_2000180[];
extern R1F103AB0cRectView D_80754C48[];
extern s16 D_80744490, D_80744494;
extern u8 D_807444FC;
Gfx *func_80703AB0(Gfx *gfx, u8 alpha) {
    R1F103AB0cRectView *rect;
    s8 alpha2;
    gfx->words.w0 = 0xDE000000; gfx->words.w1 = (u32)D_1000118; gfx++;
    gfx->words.w0 = 0xDA380007; gfx->words.w1 = (u32)D_2000080; gfx++;
    gfx->words.w0 = 0xDA380003; gfx->words.w1 = (u32)D_2000180; gfx++;
    gfx->words.w0 = 0xD9000000; gfx->words.w1 = 0; gfx++;
    gfx->words.w0 = 0xD9FFFFFF; gfx->words.w1 = 0x200004; gfx++;
    gfx->words.w0 = 0xD7000000; gfx->words.w1 = -1; gfx++;
    gfx->words.w0 = 0xE7000000; gfx->words.w1 = 0; gfx++;
    gfx->words.w0 = 0xE3000A01; gfx->words.w1 = 0; gfx++;
    gfx->words.w0 = 0xE3000C00; gfx->words.w1 = 0; gfx++;
    gfx->words.w0 = 0xE200001C; gfx->words.w1 = 0x00504240; gfx++;
    gfx->words.w0 = 0xFCFFFFFF; gfx->words.w1 = 0xFFFE793C; gfx++;
    alpha2 = alpha * 2; rect = &D_80754C48[D_807444FC];
    rect->a0 = alpha2 >= 0x100 ? 0xFF : alpha2; rect->a1 = alpha;
    rect->a2 = alpha2 >= 0x100 ? 0xFF : alpha2; rect->a3 = alpha;
    rect->x1 = rect->x2 = D_80744490; rect->y2 = rect->y3 = D_80744494;
    gfx->words.w0 = 0x01004008; gfx->words.w1 = osVirtualToPhysical(rect); gfx++;
    gfx->words.w0 = 0x06000204; gfx->words.w1 = 0x406; gfx++;
    gfx->words.w0 = 0xE7000000; gfx->words.w1 = 0; return gfx + 1;
}
