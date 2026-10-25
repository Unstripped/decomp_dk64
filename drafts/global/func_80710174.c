// func_80710174 (src/global/114270.c): Stage 4 semantic reconstruction; threshold ordering and floating-point register allocation remain.
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

f32 func_80612794(s16);
void func_8070FA58(M114aAngle *);
void func_8070FC40(M114aAngle *);

s32 func_80710174(M114aAngle *arg0) {
    s32 var_v1;
    u8 temp_v0;
    u8 temp_v0_2;

    func_8070FA58(arg0);
    arg0->unk4 = (f32)(arg0->unk4 + (func_80612794(arg0->unk20) * arg0->unk28));
    func_8070FC40(arg0);
    arg0->unk8 = (f32)arg0->unk4;
    temp_v0 = arg0->unkB0;
    arg0->unk20 = (s16)(arg0->unk20 + 0x14);
    arg0->unkB0 = (u8)(temp_v0 + 1);
    arg0->unkC = (f32)((f64)arg0->unkC + ((f64)((10.0f - ((f32)((1.0 / ((f64)arg0->unk10 * 4.0)) * 8.0) - 10.0f)) + 10.0f) * 0.25));
    if ((s32)temp_v0 >= 0x3D) {
        temp_v0_2 = arg0->unkB1;
        if ((s32)temp_v0_2 >= 0xA) {
            arg0->unkB1 = (u8)(temp_v0_2 - 0xA);
        }
    }
    var_v1 = 0;
    if (arg0->unkC > 240.0f) {
        var_v1 = 1;
    }
    if (var_v1 == 0) {
        var_v1 = (s32)arg0->unkB1 < 0xA;
    }
    return var_v1 & 0xFF;
}
