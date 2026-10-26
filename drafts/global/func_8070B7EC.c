// func_8070B7EC (src/global/10E1D0.c): Stage 1 semantic transition/render list builder; compiles but frame is 0x108 vs target 0xF8 and raw display command schedule remains.
extern f32 *D_807FD9A4;
extern Lg10E1D0_RenderInfo *D_807FD9A8;
extern s32 D_807FD9AC, D_807FD9A0, D_807FD9C8, D_80755068, D_8075506C, D_807550A8[4];
extern void *D_807FD9C0;
extern f32 D_807FD9C4;
extern u16 D_8076A09C;
extern Gfx D_1000020[], D_2000000[], D_2000200[];
void *func_80610FE8(s32); void heapFreeDeferred(void *); void func_8070A220(Lg10E1D0_RenderInfo *, s32, s32); void func_8070B05C(u16 *); void func_8070B324(f32, s32, s32 *); void n_alSndpPostEvent(); void *func_8066B0F8(s32, s32, s32, s32); void assetFreeBuffer(void *, s32, s32); void n_alSndpStop(s32, s32, void *, s32);

s32 func_8070B7EC(Gfx **arg0, s32 arg1, u16 *arg2) {
    Gfx *glist = *arg0;
    Gfx *start;
    Mtx *matrix;
    s32 channels[4], volume, i;
    s8 delta = D_807444F8 == 1 ? 3 : -4;
    for (i = 0; i < 4; i++) channels[i] = D_807550A8[i];
    start = func_80610FE8(0x4800); heapFreeDeferred(start);
    if (D_807FD9C8 != 0) {
        if (D_807444F8 == 1) {
            f64 value = (f64)D_80755068 - 20.0;
            D_807FD9C4 = (f32)((0.9 / ((value * 0.001 * value) + 1.0)) + 0.6);
            volume = D_80755068 < 60 ? 0x7FFF : 0x7FFF - ((D_80755068 * 0x7FFF + 0xFFE2003C) / 60);
        } else {
            f32 value = 120 - D_80755068; f64 first = value - 40.0f, second = value - 30.0f;
            D_807FD9C4 = (f32)(((1.5 / ((first * 0.001 * first) + 1.0)) + (0.0002 * second * second)) - 0.2);
            volume = value < 110.0f ? 0x7FFF : (s32)(32767.0f - ((value - 110.0f) * 32767.0f / 10.0f));
        }
        n_alSndpPostEvent(D_807FD9C8, 0x10, D_807FD9C4, volume); n_alSndpPostEvent(D_807FD9C8, 8, volume);
    }
    func_8070B324(1.0f - (f32)((f64)D_80755068 / 120.0), D_807444F8 == 1, channels);
    glist->words.w0 = 0xE3000A01; glist++->words.w1 = 0;
    glist->words.w0 = 0xD9000000; glist++->words.w1 = 0;
    glist->words.w0 = 0xD9FFFFFF; glist++->words.w1 = 0x00200005;
    glist->words.w0 = 0xE200001C; glist++->words.w1 = 0x00553078;
    glist->words.w0 = 0xFCFFFFFF; glist++->words.w1 = 0xFFFCF279;
    glist->words.w0 = 0xD7000002; glist++->words.w1 = 0x80008000;
    glist->words.w0 = 0xE3000C00; glist++->words.w1 = 0x00080000;
    glist->words.w0 = 0xDE000000; glist++->words.w1 = (u32)D_1000020;
    glist->words.w0 = 0xE7000000; glist++->words.w1 = 0;
    for (i = 0; i < D_807FD9A8->vertex_count; i++) {
        D_807FD9A8->vertices[i * 3] = D_807FD9A4[i * 3]; D_807FD9A8->vertices[i * 3 + 1] = D_807FD9A4[i * 3 + 1]; D_807FD9A8->vertices[i * 3 + 2] = D_807FD9A4[i * 3 + 2];
    }
    func_8070A220(D_807FD9A8, D_807FD9AC, D_80755068);
    D_807FD9A0 = ((D_80755068 * 0xF0) - (delta < 0 ? 0x960 : 0x4B0)) / 80;
    if (D_80755068 >= 5 && D_80755068 < 0x56) func_8070B05C(arg2);
    if (D_80755068 >= 0x6D && (f64)D_80755068 <= 120.0) D_8075506C = 0xDC - D_80755068 * 2;
    glist->words.w0 = 0xDA380007; glist++->words.w1 = (u32)D_2000000;
    glist->words.w0 = 0xDA380005; glist++->words.w1 = (u32)D_2000200;
    glist->words.w0 = 0xDB0E0000; glist++->words.w1 = D_8076A09C;
    matrix = func_80610FE8(0x40); heapFreeDeferred(matrix); guTranslate(matrix, 0.0f, (f32)D_8075506C, 0.0f);
    glist->words.w0 = 0xDA380003; glist++->words.w1 = (u32)matrix;
    glist->words.w0 = 0xE3001801; glist++->words.w1 = 0xC0;
    glist->words.w0 = 0xE3001A01; glist++->words.w1 = 0x30;
    func_80709BC4(&glist, D_807FD9A8, (u8 *)arg2);
    D_80755068 += delta;
    D_807FD9C0 = func_8066B0F8(0xE, 0x6A - ((D_807FD9A0 / 26) < 0 ? 0 : ((D_807FD9A0 / 26) > 9 ? 9 : D_807FD9A0 / 26)), 1, 1);
    assetFreeBuffer(D_807FD9C0, 0x381, 0x4A);
    glist->words.w0 = 0xDE000000; glist++->words.w1 = (u32)start; *arg0 = glist;
    if (D_80755068 < 0 || (f64)D_80755068 > 120.0) n_alSndpStop(D_807FD9C8, D_807FD9A0, glist, D_80755068 < 0);
    return D_80755068 < 0 || (f64)D_80755068 > 120.0;
}
