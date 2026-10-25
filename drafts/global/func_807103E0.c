// func_807103E0 (src/global/114270.c): Stage 3 m2c reconstruction; target uses a 0x28 frame while this starter uses 0x48.
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
    s16 unk22;
    s16 unk24;
    f32 unk28;
    u8 unk2C[0x84];
    u8 unkB0;
    u8 unkB1;
    u8 unkB2;
    u8 unkB3;
} M114aAngle;

extern f32 D_807FD9EC;
f32 func_80612794(s16);
void func_8070FA58(M114aAngle *);
void func_8070FC40(M114aAngle *);

s32 func_807103E0(M114aAngle *arg0) {
    f32 temp_fv1;
    f32 var_fa0;
    f64 temp_ft4;
    s32 temp_t7;
    s32 var_v1;
    u8 temp_v0;
    u8 temp_v0_2;

    func_8070FA58(arg0);
    arg0->unk4 = (f32)(arg0->unk4 + (func_80612794((s16)(s32)((f64)arg0->unk22 * 0.5)) * (f32)((f64)arg0->unk28 * 0.05)));
    func_8070FC40(arg0);
    arg0->unk8 = (f32)arg0->unk4;
    temp_ft4 = 1.0 + (f64)func_80612794(arg0->unk22);
    arg0->unk22 = (s16)(arg0->unk22 + 0x64);
    arg0->unkC = (f32)((f64)arg0->unkC + (temp_ft4 * (f64)(f32)(1.0 + ((f64)arg0->unk20 * 0.08))));
    temp_v0 = arg0->unkB3;
    temp_fv1 = arg0->unk10;
    temp_t7 = (s32)temp_v0 * -4;
    arg0->unk24 = (s16)(s32)(((((f64)func_80612794((s16)(s32)((f64)arg0->unk22 * 0.5)) * 0.5) + 0.5) * (f64)((temp_v0 * 4) - temp_t7)) + (f64)temp_t7);
    if (temp_fv1 > 0.0f) {
        var_fa0 = temp_fv1;
    } else {
        var_fa0 = -temp_fv1;
    }
    if ((var_fa0 * 140.0f) < arg0->unkC) {
        temp_v0_2 = arg0->unkB1;
        if ((s32)temp_v0_2 >= 0xA) {
            arg0->unkB1 = (u8)(temp_v0_2 - 0xA);
        }
    }
    var_v1 = 0;
    if (D_807FD9EC < arg0->unkC) {
        var_v1 = 1;
    }
    if (var_v1 == 0) {
        var_v1 = (s32)arg0->unkB1 < 0xA;
    }
    return var_v1 & 0xFF;
}
