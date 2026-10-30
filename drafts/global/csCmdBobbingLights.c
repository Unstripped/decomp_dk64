// func_80643440 (src/global/478F0.c): CsNM6 stage 5 (13 lines, FP temp ring only; code/ints/s-regs match). Parked form BBA (blocks 1,2 'p0 + (sn*.5+.5)*(p1-p0)', block 3 '(...)*(..)+p0'). Findings: IDO FP temp numbering and add.d operand order are COUPLED: forms where the CSE'd p[N].y leaf is evaluated first (B: p0 + M*D, or named y0/m/d vars, D*M+p0) give add.d (mul,cvt p0) = target operand order but ring starts f10 and D (f4,f6,f8) is allocated before M (f10,f16,f18); form A 'M*D + p0' gives target numbering (M f4,f6,f8; D f10,f16,f18; cvt p0 f6; mul f4; add f10) but add.d operands (cvt p0, mul). Target = A numbering + B operand order (mul-first); never reached in a mini-harness of ~600 expression/temp/cast/statement-order variants (access forms, named f32/f64 y0/m/d in all orders, 0.5f, /2.0 (changes code), neg/sub forms, wrappers). deadsweep sweep, hill, permuter 600s -j2 no gain (110 vs 110).
typedef struct CsB0Point3f {
    f32 x, y, z;
} CsB0Point3f;
extern CsB0Point3f **D_807F5FD4;
void *heapAlloc(s32);
f32 func_80612794(s16);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void lightSetRadius(s32);

void func_80643440(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 *ang;
    CsB0Point3f *p;
    f32 fy;
    f32 sn;

    if (*(s16 **)cs == NULL) {
        ang = heapAlloc(2);
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
