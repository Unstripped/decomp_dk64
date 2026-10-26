// func_80611A70 (src/global/166A0.c): stage 2: m2c starter; remaining diff not yet reduced
void func_80611A70(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f64 temp_fv1;
    f64 temp_fv1_2;
    f64 temp_fv1_3;
    f64 temp_fv1_4;

    temp_fv0 = *arg2;
    temp_fv1 = (f64) (temp_fv0 - arg0);
    if ((temp_fv1 < 0.25) && (temp_fv1 >= 0.0)) {
        *arg2 = (f32) ((f64) temp_fv0 + 0.125);
    }
    temp_fv0_2 = *arg3;
    temp_fv1_2 = (f64) (temp_fv0_2 - arg1);
    if ((temp_fv1_2 < 0.25) && (temp_fv1_2 >= 0.0)) {
        *arg3 = (f32) ((f64) temp_fv0_2 + 0.125);
    }
    temp_fv0_3 = *arg2;
    temp_fv1_3 = (f64) (temp_fv0_3 - arg0);
    if ((temp_fv1_3 > -0.25) && (temp_fv1_3 <= 0.0)) {
        *arg2 = (f32) ((f64) temp_fv0_3 - 0.125);
    }
    temp_fv0_4 = *arg3;
    temp_fv1_4 = (f64) (temp_fv0_4 - arg1);
    if ((temp_fv1_4 > -0.25) && (temp_fv1_4 <= 0.0)) {
        *arg3 = (f32) ((f64) temp_fv0_4 - 0.125);
    }
}
