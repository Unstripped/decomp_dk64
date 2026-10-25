// func_80713764 (src/global/117190.c): Stage 2: display-list writes and draw call recovered; floating-point scheduling and frame differ substantially.
extern s16 D_80744490;
extern s16 D_80744494;
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);

void func_80713764(Gfx *arg0, u8 arg1, f32 arg2) {
    Gfx *temp_a0;
    Gfx *temp_a0_2;
    Gfx *temp_a0_3;

    temp_a0 = arg0 + 1;
    arg0->words.w0 = 0xE200001C;
    arg0->words.w1 = 0x504240;
    temp_a0->words.w0 = 0xFA000000;
    temp_a0_2 = temp_a0 + 1;
    temp_a0->words.w1 = (s32) (arg1 | ~0xFF);
    temp_a0_3 = temp_a0_2 + 1;
    temp_a0_2->words.w0 = 0xFCFF97FF;
    temp_a0_2->words.w1 = 0xFF2CFE7F;
    temp_a0_3->words.w0 = 0xE3001201;
    temp_a0_3->words.w1 = 0;
    func_8068C5A8(temp_a0_3 + 1, 0x2C, 0, 2, 0xE0, 0x80, (s32) (f32) ((f64) D_80744490 * 0.5), (s32) (f32) (((f64) D_80744494 * 0.5) - 20.0 + (f64) arg2), 1.0f, 1.0f, 0, 0.0f);
}
