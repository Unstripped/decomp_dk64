// func_806F94AC (src/global/FCCD0.c): m2c behavioural starter; 27-insn scale update.
void func_806F94AC(void *arg0, s32 arg1) {
    f32 temp_fa0;
    f32 var_fv1;
    void *temp_v0;

    temp_v0 = arg0->unk330;
    temp_fa0 = 32.0f / (f32) (temp_v0->unk9 * temp_v0->unkE);
    var_fv1 = temp_fa0;
    if (arg1 == 9) {
        var_fv1 = (f32) ((f64) temp_fa0 * 1.2);
    }
    arg0->unk360 = (f32) (arg0->unk360 * var_fv1);
    arg0->unk364 = (f32) (arg0->unk364 * var_fv1);
}
