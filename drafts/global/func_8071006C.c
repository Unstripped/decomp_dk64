// func_8071006C (src/global/114270.c): Baseline semantic reconstruction; byte-test and floating-point scheduling differ.
typedef struct M114aAngle {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    s16 unk20;
    f32 unk24;
    f32 unk28;
    u8 unk2C[0x84];
    u8 unkB0;
    u8 unkB1;
} M114aAngle;

void func_8070FA58(M114aAngle *);
void func_8070FC40(M114aAngle *);

s32 func_8071006C(M114aAngle *arg0) {
    s32 var_v1;
    u8 temp_v0;
    u8 temp_v0_2;

    func_8070FA58(arg0);
    func_8070FC40(arg0);
    temp_v0 = arg0->unkB0;
    arg0->unkB0 = (u8)(temp_v0 + 1);
    arg0->unk8 = (f32)arg0->unk4;
    if ((s32)temp_v0 >= 0xF) {
        temp_v0_2 = arg0->unkB1;
        if ((s32)temp_v0_2 >= 0x50) {
            arg0->unkB1 = (u8)(temp_v0_2 - 0x50);
        }
    }
    var_v1 = 0;
    arg0->unkC = (f32)((f64)arg0->unkC + ((f64)((30.0f - ((f32)((1.0 / ((f64)arg0->unk10 * 4.0)) * 60.0) - 30.0f)) + 30.0f) * 0.2));
    if (arg0->unkC > 240.0f) {
        var_v1 = 1;
    }
    if (var_v1 == 0) {
        var_v1 = (s32)arg0->unkB1 < 0x50;
    }
    return var_v1 & 0xFF;
}
