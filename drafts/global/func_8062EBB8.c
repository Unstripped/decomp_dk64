// func_8062EBB8 (src/global/2F550.c): Stage 4 (NM2F3). 124 insns, frame 0x88 (pad[14]) and loop shape match. Key finds: params must be `volatile f32 arg1..3` (reloaded from arg homes each use, not hoisted), and the loop body needs named f32 dx,dy,dz locals (`dx = D[i*3]-arg1; ...; d = nx*dx + ny*dy + nz*dz`) -- that alone took the diff 144->56 lines and promotes ny,nz,0.01,-0.01,1.0,dot into f20-f30 like the target. Remaining: loop-body scheduling (target interleaves sub/cvt/mul, mine loads x,y first, mul operand order dx*nx vs nx*dx), t8/t9 numbering of the D_807F5E20 address temp, prologue lwc1 order, and loop end bound reloc D_807F5E50 vs D_807F5E20+0x30. Tried dx/dy/dz f32/f64 combos, reuse of dist/t/absd/len as temps, 6 statement orders, mul operand/assoc forms, dead-if alias hoist blockers, permuter 500s (810->655).
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

s32 func_8062EBB8(R2F550fPlane *arg0, volatile f32 arg1, volatile f32 arg2, volatile f32 arg3) {
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
        dx = D_807F5E20[i * 3] - arg1;
        dy = D_807F5E20[i * 3 + 1] - arg2;
        dz = D_807F5E20[i * 3 + 2] - arg3;
        d = nx * dx + ny * dy + nz * dz;
        if (d > 0.01 || d < -0.01) {
            t = dot / d;
            if (t <= 0.0 && 0.0 - t <= 1.0) {
                return 0;
            }
        }
    }
    return 1;
}
