// mapBspPlaneSideTest (src/global/2F550.c): Stage 5 count-exact (200 insns, size 0x320, frame 0x80), parked NON_MATCHING in Bsp copy; deadsweep score 32 (was 65 draft/111 stored). Locals decl order ea eb c n len p f64 s1 nx ny nz d = target stack layout; len==0.0f dead test + 20.0f/20.00f/20.f literal spellings + store order ny,nx,nz,d + c-cross operand order. Remaining: FP ring phase (target d f8; lwc1 f16/f18 load order at entry), 20.0f web, mtc1 at,f2 hoist.
#define arg0 ((Bsp_Plane *)arg0v)
u8 mapBspPlaneSideTest(void *arg0v, u8 *arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 ea[3];
    f32 eb[3];
    f32 c[3];
    f32 n[3];
    f32 len;
    f32 p[3];
    f64 s1;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 d;

    *arg1 = mapBspPlaneDistanceCheck(arg0, arg2, arg3, arg4);
    ny = arg0->unk50;
    nz = arg0->unk54;
    nx = arg0->unk4C;
    d = arg0->unk58;
    ea[0] = arg0->unk5C[2] - arg0->unk5C[0];
    ea[1] = arg0->unk62[2] - arg0->unk62[0];
    ea[2] = arg0->unk68[2] - arg0->unk68[0];
    eb[0] = arg0->unk5C[1] - arg0->unk5C[0];
    eb[1] = arg0->unk62[1] - arg0->unk62[0];
    eb[2] = arg0->unk68[1] - arg0->unk68[0];
    c[0] = ea[1] * eb[2] - ea[2] * eb[1];
    c[1] = ea[2] * eb[0] - ea[0] * eb[2];
    c[2] = ea[0] * eb[1] - ea[1] * eb[0];
    len = sqrtf(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
    n[0] = c[0] / len;
    if (len == 0.0f) {}  // FAKE
    n[2] = c[2] / len;
    n[1] = c[1] / len;
    n[0] = 20.0f * n[0];
    n[2] = 20.0f * n[2];
    n[1] = 20.00f * n[1];
    p[0] = n[0] + arg0->unk5C[0];
    p[2] = n[2] + arg0->unk68[0];
    p[1] = n[1] + arg0->unk62[0];
    if (nx == 0.0f) {}  // FAKE: block split before s1
    s1 = nx * arg2 + ny * arg3 + nz * arg4 + d;
    if (s1 > 0.0) {
        if (len && len) {}  // FAKE: block split steering uopt candidate order
        if (nx * p[0] + ny * p[1] + p[2] * nz + d > 0.0) {
            return 0;
        }
    }
    if (s1 < 0.0) {
        if (nx * p[0] + ny * p[1] + nz * p[2] + d < 0.0) {
            return 0;
        }
    }
    return 1;
}
#undef arg0
