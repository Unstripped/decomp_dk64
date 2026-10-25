// func_80723CCC (src/global/127B00.c): stage 1 m2c recovery; needs local Uc1 array view and codegen refinement
f32 func_80627A00(f64, f32, void *, u8, f32, f32);  /* extern */
? func_80627B58(?);                                 /* extern */
extern ? D_807FDB90;

void func_80723CCC(s32 arg0, s32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    s8 sp37;
    s8 sp36;
    u8 sp35;
    s8 sp34;
    void *sp30;
    f64 sp20;
    f64 temp_fa0;
    s16 temp_v0;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 var_a1;
    s8 temp_v0_2;
    s8 temp_v1;
    s8 temp_v1_2;
    void *temp_a0;

    func_80627B58(0x3F000000);
    var_a1 = arg1;
    temp_a0 = *(&D_807FDB90 + (arg0 * 4));
    temp_v0 = temp_a0->unk4;
    if (var_a1 >= temp_v0) {
        var_a1 = temp_v0 - 1;
    }
    temp_v0_2 = var_a1 - 1;
    if (temp_v0_2 < 0) {
        sp34 = 0;
    } else {
        sp34 = temp_v0_2;
    }
    sp35 = (u8) var_a1;
    temp_v0_3 = temp_a0->unk4;
    temp_v1 = var_a1 + 1;
    if (temp_v1 >= temp_v0_3) {
        sp36 = temp_v0_3 - 1;
    } else {
        sp36 = temp_v1;
    }
    temp_v0_4 = temp_a0->unk4;
    temp_v1_2 = var_a1 + 2;
    if (temp_v1_2 >= temp_v0_4) {
        sp37 = temp_v0_4 - 1;
    } else {
        sp37 = temp_v1_2;
    }
    temp_v0_5 = temp_a0->unk0;
    temp_fa0 = (f64) arg2;
    sp20 = temp_fa0;
    sp30 = temp_a0;
    *arg3 = func_80627A00(temp_fa0, (f32) (temp_v0_5 + ((u8) sp34 * 0xA))->unk2, temp_a0, (u8) var_a1, (f32) (temp_v0_5 + ((u8) sp36 * 0xA))->unk2, (f32) (temp_v0_5 + ((u8) sp37 * 0xA))->unk2);
    temp_v0_6 = temp_a0->unk0;
    *arg4 = func_80627A00(temp_fa0, (f32) (temp_v0_6 + ((u8) sp34 * 0xA))->unk4, temp_a0, (bitwise u8) (f32) (temp_v0_6 + ((u8) sp36 * 0xA))->unk4, (f32) (temp_v0_6 + ((u8) sp37 * 0xA))->unk4);
    temp_v0_7 = temp_a0->unk0;
    *arg5 = func_80627A00(temp_fa0, (f32) (temp_v0_7 + ((u8) sp34 * 0xA))->unk6, temp_a0, (bitwise u8) (f32) (temp_v0_7 + ((u8) sp36 * 0xA))->unk6, (f32) (temp_v0_7 + ((u8) sp37 * 0xA))->unk6);
}
