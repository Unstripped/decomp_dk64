// func_80613A50 (src/global/17B90.c): stage 1: m2c starter recovered from local asm; requires typed animation views and C compile
? func_80614644(void *, f32, s16);                  /* extern */

void func_80613A50(void *arg0, s8 arg1) {
    s32 temp_ft4;
    void *temp_a1;
    void *temp_v0;
    void *temp_v1;

    temp_v1 = arg0->unk4;
    temp_a1 = temp_v1->unk0;
    temp_v0 = temp_v1->unk8;
    temp_ft4 = (s32) ((temp_a1->unk18 - temp_a1->unk14) + 1.0f);
    func_80614644(temp_a1, ((temp_v0->unk4 * (f32) (s16) temp_ft4) / (f32) (s16) (s32) ((temp_v0->unk18 - temp_v0->unk14) + 1.0f)) + (f32) arg1, (s16) temp_ft4);
}
