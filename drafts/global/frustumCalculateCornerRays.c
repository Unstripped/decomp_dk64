// frustumCalculateCornerRays (src/global/2F550.c): Stage 5, INSN COUNT EXACT (273) only when the 12 f32 at 0x807F5DF0 are DEFINED in the TU (bss carve, like 55B20/135D30): tail as 'for (i=0;i<4;i++){ scale=negZ/C[i*3+2]; C[i*3]*=scale; C[i*3+1]*=scale; C[i*3+2]=negZ; }' unrolls by uopt and gives per-access lui exactly like target; head args &C[0..11]. Draft names the array BspCorner (must be D_807F5DF0 with yaml .bss subsegment 0x807F5DF0..0x807F5E20 for 2F550 + frustumCornersTransformByInverse's extern changed). Remaining text diff: spill slots sp58/sp54/neg at 84/76/72 vs 88/84/76 (declare i/negZ/sp58 so only 2 reserved words below sp64) + reloc/addend only. Without the carve it is 279 insns (pointerizes) / 99 with 273 non-loop.
f32 BspCorner[12];
void frustumCalculateCornerRays(f32 arg0, f32 arg1, f32 arg2) {
    f32 scale;
    f32 sp54;
    f32 spB0[4][4];
    f32 sp70[4][4];
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 negZ;
    f32 sp58;
    s32 i;

    sp58 = arg0 * 0.5;
    guRotateF(spB0, sp58, 1.0f, 0.0f, 0.0f);
    negZ = -arg2;
    guMtxXFMF(spB0, 0.0f, 0.0f, (-arg2), &sp64, &sp68, &sp6C);
    sp54 = sp58 * arg1;
    guRotateF(sp70, sp54, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &BspCorner[0], &BspCorner[1], &BspCorner[2]);
    guRotateF(sp70, -sp54, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &BspCorner[3], &BspCorner[4], &BspCorner[5]);
    guRotateF(spB0, -sp58, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(spB0, 0.0f, 0.0f, (-arg2), &sp64, &sp68, &sp6C);
    guRotateF(sp70, sp54, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &BspCorner[6], &BspCorner[7], &BspCorner[8]);
    guRotateF(sp70, -sp54, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &BspCorner[9], &BspCorner[10], &BspCorner[11]);
    for (i = 0; i < 4; i++) {
        scale = negZ / BspCorner[i * 3 + 2];
        BspCorner[i * 3] *= scale;
        BspCorner[i * 3 + 1] *= scale;
        BspCorner[i * 3 + 2] = negZ;
    }
}
