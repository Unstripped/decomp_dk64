// func_8071F444 (src/global/11BC10.c): Stage 4 m2c behavior; target frame 0x20/s0 allocation differs from 0x30 draft.
void *func_80610FE8(?);                             /* extern */
s32 func_80611A44();                                /* extern */
f32 func_80612794(s16);                             /* extern */
extern s32 D_8076A064;

void func_8071F444(void *arg0, s8 *arg1) {
    f32 temp_ft1;
    f32 temp_ft4;
    void *temp_v0;
    void *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        if (D_8076A064 & 1) {
            arg0->unk360 = (f32) (arg0->unk360 * -1.0f);
        }
        temp_v0 = func_80610FE8(8);
        arg0->unk384 = temp_v0;
        temp_ft4 = (f32) (((s32) (func_80611A44() >> 0xF) % 20) + 5);
        temp_v0->unk4 = 0.0f;
        temp_v0->unk0 = temp_ft4;
        temp_ft1 = (f32) (((s32) (func_80611A44() >> 0xF) % 100) + 0xA);
        temp_v0->unkC = 0.0f;
        temp_v0->unk8 = temp_ft1;
        var_v1 = arg0->unk384;
    }
    arg0->unk344 = (f32) ((f64) arg0->unk344 + ((1.0 + (f64) func_80612794((s16) (s32) var_v1->unk4)) * (f64) (f32) (1.0 + ((f64) var_v1->unk0 * 0.4))));
    arg0->unk340 = (f32) (arg0->unk340 + (func_80612794((s16) (s32) var_v1->unkC) * (f32) ((f64) var_v1->unk8 * 0.5)));
    if (arg0->unk350 == 0) {
        arg0->unk34E = (s16) (s32) (((f64) func_80612794((s16) (s32) var_v1->unkC) * 2.5) + 2.5);
    }
    var_v1->unk4 = (f32) (var_v1->unk4 + 100.0f);
    var_v1->unkC = (f32) (var_v1->unkC + 50.0f);
    if (arg0->unk344 > 960.0f) {
        *arg1 = 1;
    }
}
