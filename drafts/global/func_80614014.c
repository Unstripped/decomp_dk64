// func_80614014 (src/global/17B90.c): stage 1: m2c starter recovered from local asm; requires typed state/controller views and C compile
? func_80613944(void *);                            /* extern */
void *func_80614130(u16);                           /* extern */
? func_80614644(void *, void *, s32);               /* extern */

void func_80614014(void *arg0, u16 arg1, s32 arg2, u8 arg3) {
    s32 sp24;
    void *temp_s0;
    void *temp_v0;

    temp_s0 = arg0->unk4->unk4;
    if (temp_s0->unk0 != NULL) {
        func_80613944(temp_s0);
    }
    sp24 = (s32) arg1;
    temp_v0 = func_80614130(arg1);
    if (temp_v0 != NULL) {
        temp_s0->unk0 = temp_v0;
        temp_s0->unk10 = arg1;
        temp_s0->unk14 = 0.0f;
        temp_s0->unk1C = (u16) temp_v0->unk4;
        temp_s0->unk34 = 0.0f;
        temp_s0->unk18 = (f32) (temp_v0->unk12 - 1);
        temp_s0->unk24 = (f32) temp_v0->unk0;
        temp_s0->unk2C = (f32) temp_v0->unk0;
        temp_s0->unk30 = 0.0f;
        temp_s0->unk28 = (f32) temp_v0->unk0;
        arg0->unk4->unk28 = 0;
        arg0->unk4->unk2C = 0xFF;
        arg0->unk4->unk2E = (s16) arg3;
    } else {
        temp_s0->unk0 = NULL;
        temp_s0->unk10 = -1U;
        temp_s0->unk1C = 0U;
        temp_s0->unk14 = 0.0f;
        temp_s0->unk34 = 0.0f;
        temp_s0->unk24 = 0.0f;
        temp_s0->unk2C = 0.0f;
        temp_s0->unk28 = 0.0f;
        temp_s0->unk30 = 0.0f;
        temp_s0->unk18 = 0.0f;
    }
    func_80614644(arg0, temp_s0, arg2);
}
