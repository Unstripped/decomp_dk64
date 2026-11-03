// mapBspPlaneSideTest (src/global/2F550.c): Revisit 7 (Bsp): stage 5 count-exact (202 lines, frame 0x80), deadsweep full 22 text 22 shape 13 (was 32/32/20). Fixed vs stored park: entry loads/colours/spills (d,nz,ny,nx order f8,f18,f16,f14; slots 40-52) via load source order nz,ny,nx,d + a dead 'ny' test AFTER its use (inside arm; any position after the last use works, also 'if (ny && ny) {}' first) + nx test after s1; dropped the 'nx == 0.0f' block split before s1. Remaining 22: (1) target does n0,n1,n2 divides in natural order with c0,c1 loaded before the first div, ours needs source order 0,2,1 (natural order basin scores 65+); (2) target's three 20.0f are three separate 'mtc1 at,f6' (uncoloured single-use webs); ours has two uses sharing 'mtc1 at,f2' (spelling 20.00f twice) - three distinct spellings (20.0f/20.00f/20.000f) give count 203 and shift the FP ring phase (full 121; hill-climb from there 31-44 at count 202-203); (3) bc1fl+copied 'c.lt.d f2,f12' delay slot of first branch (ours bc1f nop). Tried: 24x24 load-order x decl-order grid, natural n/p orders, 3 hill-climbs x 500s (18k evals each) from the 28/22 bodies, deadsweep rounds with nx ny nz d len n[i] symbols, s1 hoisted to every earlier position (count 203, extra sw a0), direct field expressions instead of nx..d locals (loads stay at use, count 124), loop forms for ea/eb/n/p (uopt does not unroll them, frame 160).
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
    nz = arg0->unk54;
    ny = arg0->unk50;
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
    n[2] = c[2] / len;
    n[1] = c[1] / len;
    n[1] = 20.0f * n[1];
    n[0] = 20.00f * n[0];
    n[2] = n[2] * 20.00f;
    p[0] = n[0] + arg0->unk5C[0];
    p[1] = n[1] + arg0->unk62[0];
    p[2] = n[2] + arg0->unk68[0];
    s1 = nx * arg2 + ny * arg3 + nz * arg4 + d;
    if (nx && nx) {}  // FAKE: nx coloured first (f14)
    if (s1 > 0.0) {
        if (ny > 0.0f) {}  // FAKE: colours nx/ny/nz f14/f16/f18
        if (nx * p[0] + ny * p[1] + nz * p[2] + d > 0.0) {
            if (len == 0.0f) {}  // FAKE: block split steering uopt candidate order
            return 0;
        }
    }
    if (s1 < 0.0) {
        if (nx * p[0] + ny * p[1] + p[2] * nz + d < 0.0) {
            return 0;
        }
    }
    return 1;
}
#undef arg0
