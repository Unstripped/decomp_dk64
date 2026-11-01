// mapBspPlaneSideTest (src/global/2F550.c): Stage 4 (NM2F3). 200 insns, frame 0x80 matches, diff 111 (load/store scheduling in cross product and s2 inlining)
typedef struct Bsp_Plane {
    /* 0x00 */ u8 pad0[0x4C];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ s16 unk5C[3];
    /* 0x62 */ s16 unk62[3];
    /* 0x68 */ s16 unk68[3];
} Bsp_Plane;

s32 mapBspPlaneDistanceCheck(Bsp_Plane *, f32, f32, f32);

#define arg0 ((Bsp_Plane *)arg0v)
u8 mapBspPlaneSideTest(void *arg0v, u8 *arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 ea[3];
    f32 eb[3];
    f32 c[3];
    f32 n[3];
    f32 p[3];
    f32 s1;
    f32 len;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 d;

    *arg1 = mapBspPlaneDistanceCheck(arg0, arg2, arg3, arg4);
    d = arg0->unk58;
    nz = arg0->unk54;
    ny = arg0->unk50;
    nx = arg0->unk4C;
    ea[0] = arg0->unk5C[2] - arg0->unk5C[0];
    ea[1] = arg0->unk62[2] - arg0->unk62[0];
    ea[2] = arg0->unk68[2] - arg0->unk68[0];
    eb[0] = arg0->unk5C[1] - arg0->unk5C[0];
    eb[1] = arg0->unk62[1] - arg0->unk62[0];
    eb[2] = arg0->unk68[1] - arg0->unk68[0];
    c[0] = ea[1] * eb[2] - eb[1] * ea[2];
    c[1] = ea[2] * eb[0] - eb[2] * ea[0];
    c[2] = ea[0] * eb[1] - eb[0] * ea[1];
    len = sqrtf(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
    n[0] = c[0] / len;
    n[1] = c[1] / len;
    n[2] = c[2] / len;
    n[0] = n[0] * 20.0f;
    n[1] = n[1] * 20.0f;
    n[2] = n[2] * 20.0f;
    p[0] = n[0] + arg0->unk5C[0];
    p[1] = n[1] + arg0->unk62[0];
    p[2] = n[2] + arg0->unk68[0];
    s1 = nx * arg2 + ny * arg3 + nz * arg4 + d;
    if (s1 > 0.0) {
        if (nx * p[0] + ny * p[1] + nz * p[2] + d > 0.0) {
            if (s1 && s1) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
