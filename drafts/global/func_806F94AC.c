// func_806F94AC (src/global/FCCD0.c): stage 4: exact instruction count; FPU register allocation differs
typedef struct {
    u8 pad0[9];
    u8 unk9;
    u8 padA[4];
    s16 unkE;
} ScaleInfo;

typedef struct {
    u8 pad0[0x330];
    ScaleInfo *unk330;
    u8 pad334[0x2C];
    f32 unk360;
    f32 unk364;
} ScaleActor;

void func_806F94AC(ScaleActor *arg0, s32 arg1) {
    f32 temp_fa0;
    f32 var_fv1;

    var_fv1 = 32.0f / (arg0->unk330->unk9 * arg0->unk330->unkE);
    temp_fa0 = var_fv1;
    if (arg1 == 9) {
        temp_fa0 = (f64)var_fv1 * 1.2;
    }
    arg0->unk360 = arg0->unk360 * temp_fa0;
    arg0->unk364 = arg0->unk364 * temp_fa0;
}
