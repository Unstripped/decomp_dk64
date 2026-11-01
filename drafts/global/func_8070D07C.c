// func_8070D07C (src/global/110F00.c): stage 6 (parked NON_MATCHING): full=2 (was 29): ONLY diff: 'swc1 f2,44(a1)' (arg1->m[2][3]=0) sits after arg0 m[0][2] store instead of last; moving it last (natural) gives full=44 (f0/f20 roles of arg5/arg6 swap). LESSON: previous tail order was a hill-climb overfit; restarting the store-order hill-climb from NATURAL column-major order (arg0 then arg1) with move-statement/swap/line-join moves, tie-accepting, then exhaustive pair-moves over the mismatching units (pair.py) gave 29->8->6->4->2. Tried without effect from here: deadsweep (16 locals), ILS/tabu/SA, triple moves of zero stores.
void func_8070D07C(Mat4F *arg0, Mat4F *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 padtop[3]; // FAKE: pad words steer the frame size
    f32 t;
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
        t = -arg2 * inv;
        m00 = -arg4 * inv;
        m10 = arg3 * t;
        m21 = -arg3;
        m02 = -t;
        m12 = arg3 * m00;
        m20 = -arg2;
        m22 = -arg4;
    }
    arg0->m[0][0] = m00;
    arg0->m[1][0] = m10;
    arg0->m[2][0] = m20;
    arg0->m[3][0] = -arg5;
    arg0->m[0][1] = 0.0f;
    arg0->m[1][1] = m11;
    arg0->m[2][1] = m21;
    arg0->m[0][2] = m02;
    arg0->m[3][1] = -arg6;
    arg1->m[2][3] = 0.0f;
    arg0->m[1][2] = m12;
    arg0->m[2][2] = m22;
    arg0->m[0][3] = 0.0f;
    arg0->m[3][2] = -arg7;
    arg0->m[3][3] = 1.0f;
    arg0->m[1][3] = 0.0f;
    arg0->m[2][3] = 0.0f;
    arg1->m[0][0] = m00;
    arg1->m[3][0] = (arg5 * m00) + (arg7 * m02);
    arg1->m[1][0] = 0.0f;
    arg1->m[2][0] = m02;
    arg1->m[0][1] = m10;
    arg1->m[1][1] = m11;
    arg1->m[2][1] = m12;
    arg1->m[3][1] = (arg5 * m10) + (arg6 * m11) + (arg7 * m12);
    arg1->m[0][2] = m20;
    arg1->m[1][2] = m21;
    arg1->m[2][2] = m22;
    arg1->m[0][3] = 0.0f;
    arg1->m[1][3] = 0.0f;
    arg1->m[3][2] = (arg5 * m20) + (arg6 * m21) + (arg7 * m22);
    arg1->m[3][3] = 1.0f;
}
