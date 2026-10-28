// func_80643440 (src/global/478F0.c): Stage 5 (13 lines, FP temp numbering only; code/ints/s-regs match). Per-block forms: A '(sn*.5+.5)*(p1-p0)+p0' = target numbering (cvt sn f4..) but add.d operands swapped (cvt p0,mpy vs target mpy,cvt p0); B/Q/'w=m; p0+w*d' = right add order but ring starts f10 (alloc order d-chain then m-chain). 12 form families x3 blocks (named f32/f64 temps, y0/y1, d*m, +=, dead cvt) full cross product of A,B,D,F,H,Q: nothing < 13. Permuter 600s -j2 (best 100 vs base 125, no zero), deadsweep sweep (D_807F5FD4 forms): no gain. Parked form = BBA (blocks 1,2 'p0 + ...', block 3 '(...)+p0').
typedef struct CsB0Point3f {
    f32 x, y, z;
} CsB0Point3f;
extern CsB0Point3f **D_807F5FD4;
void *func_80610FE8(s32);
f32 func_80612794(s16);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void lightSetRadius(s32);

void func_80643440(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 *ang;
    CsB0Point3f *p;
    f32 fy;
    f32 sn;

    if (*(s16 **)cs == NULL) {
        ang = func_80610FE8(2);
        *(s16 **)cs = ang;
        *ang = 0;
    }
    ang = *(s16 **)cs;
    sn = func_80612794(*ang);
    p = D_807F5FD4[1];
    fy = p[0].y + (sn * 0.5 + 0.5) * (p[1].y - p[0].y);
    lightSetRadius(0x5DC);
    p = D_807F5FD4[1];
    lightAdd(p[0].x, fy, p[0].z, 0.0f, 0.0f, 0.0f, 500.0f, 0, 0xFF, 0xFF, 0xFF);
    sn = func_80612794(*ang + 0x514);
    p = D_807F5FD4[1];
    fy = p[2].y + (sn * 0.5 + 0.5) * (p[3].y - p[2].y);
    lightSetRadius(0x5DC);
    p = D_807F5FD4[1];
    lightAdd(p[2].x, fy, p[2].z, 0.0f, 0.0f, 0.0f, 500.0f, 0, 0xFF, 0xFF, 0xFF);
    sn = func_80612794(*ang + 0xA28);
    p = D_807F5FD4[1];
    fy = (sn * 0.5 + 0.5) * (p[5].y - p[4].y) + p[4].y;
    lightSetRadius(0x5DC);
    p = D_807F5FD4[1];
    lightAdd(p[4].x, fy, p[4].z, 0.0f, 0.0f, 0.0f, 500.0f, 0, 0xFF, 0xFF, 0xFF);
    *ang += 0x32;
}
