// frustumCalculateCornerRays (src/global/2F550.c): Carve 2026-11-02: stage 5, count-exact 273 (needs the 2F550 .bss carve defining f32 D_807F5DF0[12]; asm refs D_807F5DF4..E1C become interior labels): deadsweep text=3 (full 44, reloc 43 = D_807F5DF0+off vs per-label names, ROM-neutral). ONLY diff: sp54 spill at 80(sp) vs 84 (3 insns: swc1/lwc1/lw), sp58 88 and -sp54 76 exact. Win: dropping named negZ (use (-arg2) at both guMtxXFMF z args and the loop) 8 -> 3. Robust: spill slots do not move with decl order (720 orders), pads, array sp64[3], inlining sp58/sp54, scale removal, i type, ptr loops, 13.8k dead-test mutations, no-code defs (x=x|0).
extern f32 D_807F5DF0[12]; // 2F550 bss carve (commit 0b2f0ec in .scratch/wtCarve)
void frustumCalculateCornerRays(f32 arg0, f32 arg1, f32 arg2) {
    f32 scale;
    f32 sp54;
    f32 spB0[4][4];
    f32 sp70[4][4];
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp58;
    s32 i;

    sp58 = arg0 * 0.5;
    guRotateF(spB0, sp58, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(spB0, 0.0f, 0.0f, (-arg2), &sp64, &sp68, &sp6C);
    sp54 = sp58 * arg1;
    guRotateF(sp70, sp54, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &D_807F5DF0[0], &D_807F5DF0[1], &D_807F5DF0[2]);
    guRotateF(sp70, -sp54, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &D_807F5DF0[3], &D_807F5DF0[4], &D_807F5DF0[5]);
    guRotateF(spB0, -sp58, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(spB0, 0.0f, 0.0f, (-arg2), &sp64, &sp68, &sp6C);
    guRotateF(sp70, sp54, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &D_807F5DF0[6], &D_807F5DF0[7], &D_807F5DF0[8]);
    guRotateF(sp70, -sp54, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &D_807F5DF0[9], &D_807F5DF0[10], &D_807F5DF0[11]);
    for (i = 0; i < 4; i++) {
        scale = (-arg2) / D_807F5DF0[i * 3 + 2];
        D_807F5DF0[i * 3] *= scale;
        D_807F5DF0[i * 3 + 1] *= scale;
        D_807F5DF0[i * 3 + 2] = (-arg2);
    }
}
