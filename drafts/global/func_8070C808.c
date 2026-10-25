// func_8070C808 (src/global/110F00.c): stage 4: exact leaf size/frame; target evaluates product sums before translation, while this candidate retains translation outermost; uopt trace inspected
void func_8070C808(M110aMat *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fa0;
    f32 temp_fv2;
    f32 temp_fv3;
    f32 temp_fv4;

    temp_fv0 = *arg1;
    temp_fv1 = *arg2;
    temp_fa0 = *arg3;
    temp_fv2 = arg0->m[3][0] + ((temp_fv0 * arg0->m[0][0]) + (temp_fv1 * arg0->m[1][0]) + (temp_fa0 * arg0->m[2][0]));
    temp_fv3 = arg0->m[3][1] + ((temp_fv0 * arg0->m[0][1]) + (temp_fv1 * arg0->m[1][1]) + (temp_fa0 * arg0->m[2][1]));
    *arg1 = temp_fv2;
    *arg2 = temp_fv3;
    temp_fv4 = arg0->m[3][2] + ((temp_fv0 * arg0->m[0][2]) + (temp_fv1 * arg0->m[1][2]) + (temp_fa0 * arg0->m[2][2]));
    *arg3 = temp_fv4;
}
