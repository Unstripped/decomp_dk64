// func_8070C89C (src/global/110F00.c): stage 6: instruction order/frame exact; first and second division results are allocated f0/f2 instead of target f2/f0, moving one repeated store
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
