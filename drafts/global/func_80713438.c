// func_80713438 (src/global/117190.c): Stage 3: behavior and target frame recovered; target preserves separate double multiplies and display-list scheduling differs.
s32 func_8070E750(s32, s32, s32);
s32 func_80610FE8(s32);
void heapFreeDeferred(s32);
s32 func_806FBD5C(s32, s32);
void func_806FC530(Gfx *, s32, s16, s16, s32, s32);
extern s16 D_80744490;

void func_80713438(Gfx *arg0, u8 arg1) {
    s32 sp34;
    s32 sp30;
    f32 sp28;
    f64 temp_ft4;
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v0_2;
    Gfx *temp_t0;
    Gfx *temp_t1;

    temp_v0 = func_8070E750(0xC, 1, 1);
    sp30 = temp_v0;
    temp_a0 = strlen(temp_v0) + 2;
    sp28 = (f32) ((f64) D_80744490 * 0.5 * 2.0);
    temp_v0_2 = func_80610FE8(temp_a0);
    sp34 = temp_v0_2;
    heapFreeDeferred(temp_v0_2);
    _sprintf(sp34, "%c%s", 0x63, sp30);
    temp_ft4 = 0.5 * (f64) func_806FBD5C(1, sp34);
    arg0->words.w0 = 0xE200001C;
    arg0->words.w1 = 0x504240;
    temp_t0 = arg0 + 1;
    temp_t0->words.w0 = 0xFA000000;
    temp_t1 = temp_t0 + 1;
    temp_t0->words.w1 = arg1;
    temp_t1->words.w0 = 0xFCFF97FF;
    temp_t1->words.w1 = 0xFF2CFE7F;
    func_806FC530(temp_t1 + 1, 1, (s16) (s32) ((f32) ((f64) sp28 - temp_ft4) * 4.0f), (s16) (s32) (418.0f * 4.0f), sp34, 4);
}
