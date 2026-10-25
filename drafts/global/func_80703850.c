// func_80703850 (src/global/103AB0.c): stage 1 m2c viewport draft; compiled and fdiffed, conversion/FP register allocation differs
typedef struct { u8 pad[0x270]; s16 x0, y0, x1, y1, w, h; u8 pad2[4]; f32 ratio; } R1F103AB0cPlayerView;
s32 func_805FCA64();
extern s16 D_80744490, D_80744494, D_80744498, D_8074449C, D_807444A0, D_807444A4, D_807444AC, D_807444B0;
extern void *D_807FC924;
void func_80703850(s32 arg0) {
    f32 sp1C;
    f32 temp_fv0 = (f32)((f64)(f32)(arg0 & 0xFF) / 255.0);
    R1F103AB0cPlayerView *view = D_807FC924;
    sp1C = temp_fv0;
    if (func_805FCA64() != 0) {
        view->y0 = (s16)((f32)D_8074449C + ((((s16)D_80744494 >> 1) - D_8074449C - 1) * temp_fv0));
        view->y1 = (s16)((f32)D_807444A4 + ((((s16)D_80744494 >> 1) - D_807444A4) * temp_fv0));
    } else {
        view->y0 = (s16)((f32)D_807444AC + ((((s16)D_80744494 >> 1) - D_807444AC - 1) * temp_fv0));
        view->y1 = (s16)((f32)D_807444B0 + ((((s16)D_80744494 >> 1) - D_807444B0) * temp_fv0));
    }
    view->x0 = (s16)((f32)D_80744498 + ((((s16)D_80744490 >> 1) - D_80744498 - 1) * temp_fv0));
    view->x1 = (s16)((f32)D_807444A0 + ((((s16)D_80744490 >> 1) - D_807444A0) * temp_fv0));
    view->h = view->y1 - view->y0;
    view->w = view->x1 - view->x0;
    view->ratio = (f32)view->w / (f32)view->h;
}
