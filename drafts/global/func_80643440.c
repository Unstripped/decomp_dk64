// func_80643440 (src/global/478F0.c): Stage 5 (text shape/regs-except-FP-temps match, 2 FP temp numbering): only $f4-$f18 temp numbering differs (13 insn lines); form A '(sn*.5+.5)*(p1-p0)+p0' matches block1 numbering but IDO emits add.d operands swapped; form B 'p0+(...)' gets add order but wrong pool start; mixed forms BBA best; permuter 110->100, deadsweep no gain. Parked NON_MATCHING in 478F0 copy.
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
