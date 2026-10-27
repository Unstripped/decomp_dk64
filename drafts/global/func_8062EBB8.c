// func_8062EBB8 (src/global/2F550.c): stage 3-4: frame OK (s32 pad[14] gives 0x88), prologue/dot/sqrtf/abs/branch/loop-pointer match. Diff = fp regalloc only: target keeps ny,nz,0.01,-0.01,1.0,dot in fs0-fs5 and never promotes x,y,z (reloaded from arg homes 0x8C/0x90/0x94 inside loop, not hoisted), mine promotes x,y into f28/f30 and leaves nx..nz in temps (z-term then evaluated first). Tried: struct-by-value Vec3 (target passes 3 scalar f32), volatile struct (stops hoist but changes alloc), address-taken, named f64 nx/ny/nz, absd local. permuter 600s best 903/2464 not matching. Loop end bound is D_807F5E50 reloc vs mine D_807F5E20+0x30.
typedef struct R2F550fPlane {
    /* 0x00 */ u8 pad0[0x4C];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ s16 unk5C[3];
    /* 0x62 */ s16 unk62[3];
    /* 0x68 */ s16 unk68[3];
} R2F550fPlane;

extern f32 D_807F5E20[];

s32 func_8062EBB8(R2F550fPlane *arg0, f32 arg1, f32 arg2, f32 arg3) {
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

    i = 0;
    dot = arg0->unk4C * arg1 + arg0->unk50 * arg2 + arg0->unk54 * arg3 + arg0->unk58;
    len = sqrtf(arg0->unk4C * arg0->unk4C + arg0->unk50 * arg0->unk50 + arg0->unk54 * arg0->unk54);
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
    for (; i < 4; i++) {
        d = nx * (D_807F5E20[i * 3] - arg1) + ny * (D_807F5E20[i * 3 + 1] - arg2) + nz * (D_807F5E20[i * 3 + 2] - arg3);
        if (d > 0.01 || d < -0.01) {
            t = dot / d;
            if (t <= 0.0 && 0.0 - t <= 1.0) {
                return 0;
            }
        }
    }
    return 1;
}
