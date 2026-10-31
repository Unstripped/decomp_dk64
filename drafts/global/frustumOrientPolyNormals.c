// frustumOrientPolyNormals (src/global/2F550.c): OlR2a: stage 5 unchanged (2 diff lines: final add.d/c.lt.d f8 vs f0). New findings: f0 comes from a NAMED f64 local (BD820 func_806B8C78 does the same: t = x + 0.5 colours f0). 't = poly->d + (...); if (t < (0, 0.0))' with 'f64 t;' declared before poly (replacing pad0, frame 0x90 kept) gives add.d f0 + c.lt.d f0,f20 but uopt then picks the ys pointer instead of zs as the LFTR loop-end IV (s1=ys@100, s4=xs end; target s1=zs@80, s4=100): 13 diff lines. Declaration order (720 perms), loop header forms, sum forms (8), (0,x) wraps on 71 sites singles + 91 pairs, did not restore the IV choice. Permuter 540s from the old base: best stays 10. Next idea if resumed: find a source change that makes uopt pick the zs IV with t present (candidate ids shift with expression count).
typedef struct PlanePoly {
    /* 0x00 */ s16 v[12];
    /* 0x18 */ u8 type;
    /* 0x19 */ u8 pad19[7];
    /* 0x20 */ f64 a;
    /* 0x28 */ f64 b;
    /* 0x30 */ f64 c;
    /* 0x38 */ f64 d;
} PlanePoly; /* 0x40 */

void polyFlipWinding(PlanePoly *);
void planePolyCalcEquation(PlanePoly *);

void frustumOrientPolyNormals(f32 arg0, f32 arg1, f32 arg2, PlanePoly *arg3, f32 *arg4) {
    s32 i;
    f32 xs[5];
    f32 ys[5];
    f32 zs[5];
    PlanePoly *poly;
    s32 pad0;

    poly = arg3;
    for (i = 0; i < 4; i++) {
        poly++;
        poly[-1].v[0] = arg0;
        poly[-1].v[1] = arg1;
        poly[-1].v[2] = arg2;
        poly[-1].type = 3;
    }
    arg3[0].v[3] = arg4[0];
    arg3[0].v[4] = arg4[1];
    arg3[0].v[5] = arg4[2];
    arg3[0].v[6] = arg4[3];
    arg3[0].v[7] = arg4[4];
    arg3[0].v[8] = arg4[5];
    xs[0] = arg4[6];
    ys[0] = arg4[7];
    zs[0] = arg4[8];
    arg3[1].v[3] = arg4[6];
    arg3[1].v[4] = arg4[7];
    arg3[1].v[5] = arg4[8];
    arg3[1].v[6] = arg4[0];
    arg3[1].v[7] = arg4[1];
    arg3[1].v[8] = arg4[2];
    xs[1] = arg4[9];
    ys[1] = arg4[10];
    zs[1] = arg4[11];
    arg3[2].v[3] = arg4[9];
    arg3[2].v[4] = arg4[10];
    arg3[2].v[5] = arg4[11];
    arg3[2].v[6] = arg4[6];
    arg3[2].v[7] = arg4[7];
    arg3[2].v[8] = arg4[8];
    xs[2] = arg4[0];
    ys[2] = arg4[1];
    zs[2] = arg4[2];
    arg3[3].v[3] = arg4[3];
    arg3[3].v[4] = arg4[4];
    arg3[3].v[5] = arg4[5];
    arg3[3].v[6] = arg4[9];
    arg3[3].v[7] = arg4[10];
    arg3[3].v[8] = arg4[11];
    xs[3] = arg4[0];
    ys[3] = arg4[1];
    zs[3] = arg4[2];
    arg3[4].type = 4;
    arg3[4].v[0] = arg4[6];
    arg3[4].v[1] = arg4[7];
    arg3[4].v[2] = arg4[8];
    arg3[4].v[3] = arg4[9];
    arg3[4].v[4] = arg4[10];
    arg3[4].v[5] = arg4[11];
    arg3[4].v[6] = arg4[0];
    arg3[4].v[7] = arg4[1];
    arg3[4].v[8] = arg4[2];
    arg3[4].v[9] = arg4[3];
    arg3[4].v[10] = arg4[4];
    arg3[4].v[11] = arg4[5];
    zs[4] = arg2;
    ys[4] = arg1;
    xs[4] = arg0;
    poly = arg3;
    for (i = 0; i < 5; poly++, i++) {
        planePolyCalcEquation(poly);
        if (poly->d + (poly->a * xs[i] + poly->b * ys[i] + poly->c * zs[i]) < (0, 0.0)) {
            polyFlipWinding(poly);
            planePolyCalcEquation(poly);
        }
    }
}
