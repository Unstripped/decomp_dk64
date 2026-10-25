// func_8070C2D8 (src/global/110F00.c): compilable affine product candidate; target retains six FP callee-saved registers and stages output through stack
void func_8070C2D8(M110aMat *arg0, M110aMat *arg1, M110aMat *arg2) {
    arg2->m[0][0] = (arg0->m[0][0] * arg1->m[0][0]) + (arg0->m[0][1] * arg1->m[1][0]) + (arg0->m[0][2] * arg1->m[2][0]);
    arg2->m[0][1] = (arg0->m[0][0] * arg1->m[0][1]) + (arg0->m[0][1] * arg1->m[1][1]) + (arg0->m[0][2] * arg1->m[2][1]);
    arg2->m[0][2] = (arg0->m[0][0] * arg1->m[0][2]) + (arg0->m[0][1] * arg1->m[1][2]) + (arg0->m[0][2] * arg1->m[2][2]);
    arg2->m[1][0] = (arg0->m[1][0] * arg1->m[0][0]) + (arg0->m[1][1] * arg1->m[1][0]) + (arg0->m[1][2] * arg1->m[2][0]);
    arg2->m[1][1] = (arg0->m[1][0] * arg1->m[0][1]) + (arg0->m[1][1] * arg1->m[1][1]) + (arg0->m[1][2] * arg1->m[2][1]);
    arg2->m[1][2] = (arg0->m[1][0] * arg1->m[0][2]) + (arg0->m[1][1] * arg1->m[1][2]) + (arg0->m[1][2] * arg1->m[2][2]);
    arg2->m[2][0] = (arg0->m[2][0] * arg1->m[0][0]) + (arg0->m[2][1] * arg1->m[1][0]) + (arg0->m[2][2] * arg1->m[2][0]);
    arg2->m[2][1] = (arg0->m[2][0] * arg1->m[0][1]) + (arg0->m[2][1] * arg1->m[1][1]) + (arg0->m[2][2] * arg1->m[2][1]);
    arg2->m[2][2] = (arg0->m[2][0] * arg1->m[0][2]) + (arg0->m[2][1] * arg1->m[1][2]) + (arg0->m[2][2] * arg1->m[2][2]);
    arg2->m[3][0] = (arg0->m[3][0] * arg1->m[0][0]) + (arg0->m[3][1] * arg1->m[1][0]) + (arg0->m[3][2] * arg1->m[2][0]) + arg1->m[3][0];
    arg2->m[3][1] = (arg0->m[3][0] * arg1->m[0][1]) + (arg0->m[3][1] * arg1->m[1][1]) + (arg0->m[3][2] * arg1->m[2][1]) + arg1->m[3][1];
    arg2->m[3][2] = (arg0->m[3][0] * arg1->m[0][2]) + (arg0->m[3][1] * arg1->m[1][2]) + (arg0->m[3][2] * arg1->m[2][2]) + arg1->m[3][2];
    arg2->m[0][3] = 0.0f;
    arg2->m[1][3] = 0.0f;
    arg2->m[2][3] = 0.0f;
    arg2->m[3][3] = 1.0f;
}
