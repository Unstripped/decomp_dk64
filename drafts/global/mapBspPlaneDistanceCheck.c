// mapBspPlaneDistanceCheck (src/global/2F550.c): Stage 5, 124 insns (135 lines objdump matches 135 lines), frame 0x88 matches, reloc=0, diff 21 (12 insns loop-body scheduling and regalloc t8/t9, f8/f4)
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

s32 mapBspPlaneDistanceCheck(Bsp_Plane *arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 pad[14];
    s32 i;
    f64 dot;
    f32 len;
    f64 dist;
    f64 d;
    f64 t;
    f64 absd;
    f64 nx;
    f64 ny;
    f64 nz;
    f32 dx;
    f32 dy;
    f32 dz;

    i = 0;
    dot = arg0->unk4C * arg1 + arg0->unk50 * arg2 + arg0->unk54 * arg3 + arg0->unk58;
    len = sqrtf(arg0->unk4C * arg0->unk4C + arg0->unk50 * arg0->unk50 + arg0->unk54 * arg0->unk54);
    if (dot && dot) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    dist = dot / len;
    absd = dist;
    if (dist < 0.0) {
        absd = 0.0 - dist;
    }
    if (absd > 300.0) {
        return 2;
    }
    nx = arg0->unk4C;
    ny = arg0->unk50;
    nz = arg0->unk54;
    do {
        if (absd == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (absd && absd) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        d = nx * (f64)(D_807F5E20[i * 3] - arg1) + ny * (f64)(D_807F5E20[i * 3 + 1] - arg2) + nz * (f64)(D_807F5E20[i * 3 + 2] - arg3);
        if (d > 0.01 || d < -0.01) {
            t = dot / d;
            if (t <= 0.0 && 0.0 - t <= 1.0) {
                return 0;
            }
        }
        i++;
    } while (&D_807F5E20[i * 3] < D_807F5E50);
    return 1;
}
