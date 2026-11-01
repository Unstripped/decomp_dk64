// func_8070D07C (src/global/110F00.c): func_8070D07C (src/global/110F00.c): stage 6 (parked NON_MATCHING), full=2: ONLY 'swc1 f2,44(a1)' (arg1->m[2][3]=0) sits after arg0 m[0][2] instead of last. W3Near 2026-11-01 root cause (as1-stream experiments, hand-run cfe|uopt|ugen|as1, .scratch/W3Near/{mkugen,as1lib,v9..v30}.py): the expected as1 output is reproduced EXACTLY (diff 0) by A's ugen stream with the zero-store group moved last, load of arg7 (lwc1 164(sp)) left where A has it (after the m[1][2] store). But ugen puts the arg7 homed load after a fixed count (11 stores / 13 recs / abs rec idx 177 in 99/130 random tail orders), so natural zero-last order puts it one store later (after m[2][2]) -> full=44 (f0/f20 roles swap). Candidate colours are identical in A and B (only lr 98->97). Orders with zero last and load count 12 exist (60 single moves) but score >=2 (4(a0)/40(a0) store swap). Tried this round (no gain): 80k-sample random move/swap hill-climb over the 32-statement tail (ties accepted), beam search depth 5 width 12 (10k cands/level), exhaustive 1- and 2-moves from natural order, exhaustive stream-level single/pair moves, operand-order toggles of all 18 sums (A and B bases), //comma-merged/line-joined statements (no effect on load position), dead tests (shift everything). Untried: a source construct that makes ugen defer the load by one fewer store (e.g. extra early store as1 later sinks), K&R/prototype changes of mtxIdentityF/sqrtf.
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
