// func_8070CDD0 (src/global/110F00.c): stage 4 (parked NON_MATCHING): full diff 30 (was 39): frame 0x60, prologue, zero-branch, final stores, T4(-arg4) spill sp28 + m00t sp20 + -arg2 in f12 all match (needs m00/m22 before m20 and m02 = -m20 * inv, which is a 3rd use of -arg2 -> its adjsave 4.0 beats -arg4 3.0). Remaining: target shares t=m20*inv (spilled sp24, reloaded for m10 and neg m02) where mine multiplies twice and has no sp24 slot; with m02 = -(m20*inv) the f12/spill roles flip back unless -arg2 is first seen before -arg4 (B,A,E order), but then T4/m00t share a slot (frame slots 0x24/0x28 not 0x28/0x24/0x20) and -arg3 neg is hoisted. Tried: exhaustive topo orders x expr forms, named temps, lsweep of dead local uses, permuter 63k iters.
void func_8070CDD0(Mat4F *arg0, Mat4F *arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 padtop[4]; // FAKE: pad words steer the frame size
    f32 m00;
    f32 m10;
    f32 m20;
    f32 inv;
    f32 m11;
    f32 m21;
    f32 m02;
    f32 m12;
    f32 m22;

    if ((arg2 == 0.0f) && (arg4 == 0.0f)) {
        if (arg3 == 0.0f) {
            mtxIdentityF(arg0->m);
            mtxIdentityF(arg1->m);
            return;
        }
        m00 = 1.0f;
        m10 = 0.0f;
        m20 = 0.0f;
        m11 = 0.0f;
        m21 = -1.0f;
        m02 = 0.0f;
        m12 = 1.0f;
        m22 = 0.0f;
    } else {
        inv = 1.0 / sqrtf((arg2 * arg2) + (arg3 * arg3) + (arg4 * arg4));
        arg2 = arg2 * inv;
        arg3 = arg3 * inv;
        arg4 = arg4 * inv;
        m11 = sqrtf((arg2 * arg2) + (arg4 * arg4));
        inv = 1.0 / m11;
        m00 = -arg4 * inv;
        m22 = -arg4;
        m20 = -arg2;
        m10 = arg3 * (m20 * inv);
        m12 = arg3 * m00;
        m02 = -m20 * inv;
        m21 = -arg3;
    }
    arg0->m[0][0] = m00;
    arg0->m[1][0] = m10;
    arg0->m[2][0] = m20;
    arg0->m[3][0] = 0.0f;
    arg0->m[0][1] = 0.0f;
    arg0->m[1][1] = m11;
    arg0->m[2][1] = m21;
    arg0->m[3][1] = 0.0f;
    arg0->m[0][2] = m02;
    arg0->m[1][2] = m12;
    arg0->m[3][2] = 0.0f;
    arg0->m[0][3] = 0.0f;
    arg0->m[1][3] = 0.0f;
    arg0->m[2][3] = 0.0f;
    arg0->m[3][3] = 1.0f;
    arg0->m[2][2] = m22;
    arg1->m[0][0] = m00;
    arg1->m[1][0] = 0.0f;
    arg1->m[3][0] = 0.0f;
    arg1->m[0][1] = m10;
    arg1->m[1][1] = m11;
    arg1->m[2][0] = m02;
    arg1->m[3][1] = 0.0f;
    arg1->m[0][2] = m20;
    arg1->m[1][2] = m21;
    arg1->m[2][1] = m12;
    arg1->m[3][2] = 0.0f;
    arg1->m[0][3] = 0.0f;
    arg1->m[1][3] = 0.0f;
    arg1->m[2][3] = 0.0f;
    arg1->m[3][3] = 1.0f;
    arg1->m[2][2] = m22;
}
