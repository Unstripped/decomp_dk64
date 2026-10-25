// func_8070CDD0 (src/global/110F00.c): compilable structured candidate; frame 0x50 vs target 0x60 and register allocation differ
void func_8070CDD0(Mat4F *arg0, Mat4F *arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv2;
    f32 temp_fv3;
    f32 temp_fv4;
    f32 temp_fv5;
    f32 temp_fv6;
    f32 temp_fv7;
    f32 temp_fv8;

    if ((arg2 == 0.0f) && (arg4 == 0.0f)) {
        if (arg3 == 0.0f) {
            mtxIdentityF(arg0);
            mtxIdentityF(arg1);
            return;
        }
        temp_fv0 = 1.0f;
        temp_fv1 = 0.0f;
        temp_fv2 = 0.0f;
        temp_fv3 = 0.0f;
        temp_fv4 = 0.0f;
        temp_fv5 = -1.0f;
        temp_fv6 = 0.0f;
        temp_fv7 = 0.0f;
        temp_fv8 = 1.0f;
    } else {
        temp_fv0 = 1.0 / sqrtf((arg2 * arg2) + (arg3 * arg3) + (arg4 * arg4));
        arg2 *= temp_fv0;
        arg3 *= temp_fv0;
        arg4 *= temp_fv0;
        temp_fv1 = sqrtf((arg2 * arg2) + (arg4 * arg4));
        temp_fv2 = -arg4;
        temp_fv3 = -arg2;
        temp_fv4 = temp_fv2 / temp_fv1;
        temp_fv5 = temp_fv3 / temp_fv1;
        temp_fv6 = arg3 * temp_fv5;
        temp_fv7 = -arg3;
        temp_fv8 = arg3 * temp_fv4;
        temp_fv0 = temp_fv4;
        temp_fv1 = temp_fv5;
    }
    arg0->m[0][0] = temp_fv0;
    arg0->m[1][0] = temp_fv6;
    arg0->m[2][0] = temp_fv3;
    arg0->m[3][0] = 0.0f;
    arg0->m[0][1] = 0.0f;
    arg0->m[1][1] = temp_fv1;
    arg0->m[2][1] = temp_fv7;
    arg0->m[3][1] = 0.0f;
    arg0->m[0][2] = -temp_fv5;
    arg0->m[1][2] = temp_fv8;
    arg0->m[2][2] = 0.0f;
    arg0->m[3][2] = 0.0f;
    arg0->m[0][3] = 0.0f;
    arg0->m[1][3] = 0.0f;
    arg0->m[2][3] = 0.0f;
    arg0->m[3][3] = 1.0f;
    arg1->m[0][0] = temp_fv0;
    arg1->m[1][0] = 0.0f;
    arg1->m[2][0] = -temp_fv5;
    arg1->m[3][0] = 0.0f;
    arg1->m[0][1] = temp_fv6;
    arg1->m[1][1] = temp_fv1;
    arg1->m[2][1] = temp_fv8;
    arg1->m[3][1] = 0.0f;
    arg1->m[0][2] = temp_fv3;
    arg1->m[1][2] = temp_fv7;
    arg1->m[2][2] = 0.0f;
    arg1->m[3][2] = 0.0f;
    arg1->m[0][3] = 0.0f;
    arg1->m[1][3] = 0.0f;
    arg1->m[2][3] = temp_fv2;
    arg1->m[3][3] = 1.0f;
}
