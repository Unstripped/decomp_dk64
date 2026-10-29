// func_8071720C (src/global/11BC10.c): stage 4-5: structure+dataflow complete; remaining diff is register allocation only
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} Fx11BAMotion8;

void lightSetFlags();
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void func_8071720C(RotatingEffectActorView *arg0, void *arg1) {
    Fx11BAMotion8 *var_v1;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(8);
        var_v1 = arg0->unk384;
        var_v1->unk0 = (randomNonNegative() >> 15) % 0xFFF;
        var_v1->unk2 = ((randomNonNegative() >> 15) % 10) + 2;
        var_v1->unk4 = 0;
        var_v1->unk6 = -50 - (((randomNonNegative() >> 15) % 10000) % 600);
    }
    var_v1 = arg0->unk384;
    arg0->unk344 = (f32) ((f64) arg0->unk344 - (f64) var_v1->unk6 / 100.0);
    var_v1->unk6 += 0x14;
    arg0->unk340 = (f32) ((f64) arg0->unk340 + 0.04 * (f64) var_v1->unk4 * (f64) func_80612794(var_v1->unk0));
    arg0->unk348 = (f32) ((f64) arg0->unk348 + 0.04 * (f64) var_v1->unk4 * (f64) func_80612790(var_v1->unk0));
    var_v1->unk0 += 0x50;
    var_v1->unk4 += var_v1->unk2;
    if (arg0->unk35C != 0) {
        lightSetFlags(1);
        lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, 40.0f, 0, 0xFF,
                 (randomNonNegative() >> 15) % 0xFF, 0xFF);
    }
}
