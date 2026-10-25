// func_80713764 (src/global/117190.c): Stage 2: direct Gfx writes and FP expressions recover the target instruction forms; remaining differences are FP and GPR allocation.
extern s16 D_80744490;
extern s16 D_80744494;
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);

void func_80713764(Gfx *arg0, u8 arg1, f32 arg2) {
    f32 x;
    f64 y;

    x = (f32) ((f64) D_80744490 * 0.5);
    y = ((f64) D_80744494 * 0.5) + -20.0 + (f64) arg2;
    R117D_WRITE_GFX(arg0++, 0xE200001C, 0x504240);
    R117D_WRITE_GFX(arg0++, 0xFA000000, (s32) (arg1 | ~0xFF));
    R117D_WRITE_GFX(arg0++, 0xFCFF97FF, 0xFF2CFE7F);
    R117D_WRITE_GFX(arg0++, 0xE3001201, 0);
    func_8068C5A8(arg0, 0x2C, 0, 2, 0xE0, 0x80, (s32) x, (s32) (f32) y, 1.0f, 1.0f, 0, 0.0f);
}
