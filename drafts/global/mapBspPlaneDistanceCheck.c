// mapBspPlaneDistanceCheck (src/global/2F550.c): stage 5, diff 4 (was 21): named f64 locals dx/dy/dz (f64 = f32 diff) + d = nx*dx+ny*dy+nz*dz, pad[14], dead 'if (dx) {}' after dz def; dropped two absd dead tests. Remaining: ring t8/t9 in preheader i*3*4: target sll t7,t7,2 in place + lui t8; ours sll t8 + lui t9 (i*3 temp held), and FP f0/f2 vs ... (4 lines). Tried i/idx spellings, cond casts, no-code x=x defs, dead-test grid.
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
    f64 dx;
    f64 dy;
    f64 dz;

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
        dx = D_807F5E20[i * 3] - arg1;
        dy = D_807F5E20[i * 3 + 1] - arg2;
        dz = D_807F5E20[i * 3 + 2] - arg3;
        if (dx) {}  // FAKE: lowers dx priority (extra block in its range)
        d = nx * dx + ny * dy + nz * dz;
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
