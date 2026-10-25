// func_807102AC (src/global/114270.c): Stage 5: F101 allocation pattern makes every instruction match except 0.07 rodata relocation/scheduling; improved source applied transiently.
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

extern f32 D_807FD9EC;
f32 func_80612794(s16);
void func_8070FA58(M114aAngle *);
void func_8070FC40(M114aAngle *);

s32 func_807102AC(M114aAngle *arg0) {
    s32 var_v1;
    u8 temp_v0;
    u8 temp_v0_2;

    func_8070FA58(arg0);
    arg0->unk4 = (f32)(arg0->unk4 + (func_80612794(arg0->unk20) * arg0->unk28));
    func_8070FC40(arg0);
    arg0->unk8 = (f32)arg0->unk4;
    temp_v0 = arg0->unkB0;
    arg0->unk20 = (s16)(arg0->unk20 + 0x32);
    arg0->unkB0 = (u8)(temp_v0 + 1);
    arg0->unkC = (f32)((f64)arg0->unkC + ((f64)((10.0f - ((f32)((1.0 / ((f64)arg0->unk10 * 3.0)) * 8.0) - 10.0f)) + 10.0f) * 0.07));
    if ((s32)temp_v0 >= 0x6F) {
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
