// func_8070C89C (src/global/110F00.c): stage 1: projection matrix assignments reconstructed; division-result FP register allocation remains inverted
typedef struct M110aMat {
    f32 m[4][4];
} M110aMat;

void func_8070CCC4();

void func_8070C89C(M110aMat *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 temp_fv1;
    f32 temp_fv0;

    func_8070CCC4(arg0);
    temp_fv0 = arg1 / arg3;
    arg0->m[1][1] = temp_fv0;
    arg0->m[2][2] = temp_fv0;
    temp_fv1 = arg2 / arg3;
    arg0->m[1][2] = temp_fv1;
    arg0->m[2][1] = -temp_fv1;
}
