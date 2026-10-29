// func_80717404 (src/global/11BC10.c): stage 4-5: structure+dataflow complete; remaining diff is register allocation only
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Fx11BAMotion12;

typedef struct {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x10];
    s32 unk35C;
    u8 pad360[0xF];
    u8 unk36F;
    u8 pad370[0x14];
    Fx11BAMotion12 *unk384;
} Fx11BAEffectActor;

void func_80717404(Fx11BAEffectActor *arg0, void *arg1) {
    Fx11BAMotion12 *motion;
    s16 *var_s2;
    f64 scale;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(0xC);
        motion = arg0->unk384;
        var_s2 = (s16 *) &arg0->unk35C;
        if (*var_s2 != 0) {
            motion->unk0 = (f32) (((randomNonNegative() >> 15) % 200) + *var_s2 - 100);
        } else {
            motion->unk0 = (f32) ((randomNonNegative() >> 15) % 0xFFF);
        }
        scale = (arg0->unk36F != 0) ? 4.0 : 1.0;
        motion->unk4 = (f32) ((((randomNonNegative() >> 15) % 10) + 5) * scale);
        motion->unk8 = (f32) (var_s2[1] + ((randomNonNegative() >> 15) % 6));
    }
    motion = arg0->unk384;
    var_s2 = (s16 *) &arg0->unk35C;
    if (arg0->unk36F != 0) {
        arg0->unk340 = (f32) ((f64) arg0->unk340 + 4.0 * ((f64) func_80612794((s16) motion->unk0) * (0.01 * (f64) var_s2[1])));
        arg0->unk344 = (f32) ((f64) arg0->unk344 + 4.0 * ((f64) func_80612790((s16) motion->unk0) * (0.01 * (f64) var_s2[1])));
    } else {
        arg0->unk340 = (f32) ((f64) arg0->unk340 + (f64) func_80612794((s16) motion->unk0) * (0.04 * (f64) var_s2[1]));
        arg0->unk348 = (f32) ((f64) arg0->unk348 + (f64) func_80612790((s16) motion->unk0) * (0.04 * (f64) var_s2[1]));
        if (*var_s2 == 0) {
            arg0->unk344 = arg0->unk344 + motion->unk8;
            motion->unk8 = (f32) ((f64) motion->unk8 - 0.5);
        } else {
            arg0->unk344 = (f32) ((f64) arg0->unk344 + (f64) motion->unk8 * 0.2);
        }
    }
    var_s2[1] = (s16) (var_s2[1] + motion->unk4);
}
