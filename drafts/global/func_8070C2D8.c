// func_8070C2D8 (src/global/110F00.c): stage 1: behaviorally equivalent affine matrix product loop; target is fully unrolled with six callee-saved FP registers
typedef struct M110aMat {
    f32 m[4][4];
} M110aMat;

void func_8070C2D8(M110aMat *arg0, M110aMat *arg1, M110aMat *arg2) {
    s32 i;
    s32 j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            arg2->m[i][j] = (arg0->m[i][0] * arg1->m[0][j]) + (arg0->m[i][1] * arg1->m[1][j]) + (arg0->m[i][2] * arg1->m[2][j]);
        }
        arg2->m[i][3] = 0.0f;
    }
    for (j = 0; j < 3; j++) {
        arg2->m[3][j] = arg1->m[3][j] + (arg0->m[3][0] * arg1->m[0][j]) + (arg0->m[3][1] * arg1->m[1][j]) + (arg0->m[3][2] * arg1->m[2][j]);
    }
    arg2->m[3][3] = 1.0f;
}
