// func_8062EBB8 (src/global/2F550.c): Stage 4 (NM2F3). 124 insns, frame 0x88 (pad[14]), loop shape match. Disproved volatile: O32 ABI stores params naturally to home slots after caller pointer arg; removing volatile matched lines 4368-43FC 100%. D_807F5E50 is D_807F5E20+0x30. Deadsweep reduced diff to 21. Only 12 insns of loop-body scheduling remain.
typedef struct OlD_Plane {
    /* 0x00 */ u8 pad0[0x4C];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ s16 unk5C[3];
    /* 0x62 */ s16 unk62[3];
    /* 0x68 */ s16 unk68[3];
} OlD_Plane;

extern f32 D_807F5E20[];
extern f32 D_807F5E50[];

s32 func_8062EBB8(OlD_Plane *arg0, f32 arg1, f32 arg2, f32 arg3) {
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
    for (; &D_807F5E20[i * 3] < D_807F5E50; i++) {
        if (absd == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (absd && absd) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        d = nx * (f64)(D_807F5E20[i * 3] - arg1) + ny * (f64)(D_807F5E20[i * 3 + 1] - arg2) + nz * (f64)(D_807F5E20[i * 3 + 2] - arg3);
        if (d > 0.01 || d < -0.01) {
            t = dot / d;
            if (t <= 0.0 && 0.0 - t <= 1.0) {
                return 0;
            }
        }
    }
    return 1;
}
