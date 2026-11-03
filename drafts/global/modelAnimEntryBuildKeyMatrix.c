// modelAnimEntryBuildKeyMatrix (src/global/54150.c): W2Fp (leftovers7 wave2): stage 4 park 131 -> 126 (deadsweep full 126 text 126 reloc 0 shape 68; count exact 351 insns, frame 256). NEW LEVER: named key temps fa/fb (f32, declared right after c2, padB 5->4) for x and y only (fa = key[arg0+1].unkC; fb = key[arg0].unkC; x = fa - fb; ... x += fb): the target's x/y heads (lwc1 f12,48(v1); lwc1 f14,12(a1); sub.s f2; cvt.d.s f0,f2; swc1 f2,248) are reproduced exactly (the plain spelling made uopt reload x after the store: has_ilod blocks copy propagation of an expression containing indirect loads, named single-use ilod vars stay coloured f12/f14 vars). Annealer (.scratch/W2Fp/ann.py: commutative/compare flips + dead tests, 540 s x 6 runs) took 131 -> 126; the 9-component temp-subset grid (512 subsets x pad x order) best shape was mask x,y,c6,c8,c1,c2 (shape 39, full 177, count 352), annealed from there 130; temps for z or c0-c2 add 6-7 insns. Remaining diff: ours colours z f18 and the 360.0 double const f16 (target z f16, 360.0 f18: the const must colour AFTER z), key temps f2/f12 vs target f12/f14 (x piece must colour before fa/fb), switch-case reg phases.
typedef struct ModelBTrack {
    u8 *unk0;
    u8 *unk4;
} ModelBTrack;

typedef struct ModelBKey {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
} ModelBKey; /* 0x24 */

void matrixMakeRotationX(f32 (*)[4], f32);
void matrixMakeRotationY(f32 (*)[4], f32);
void matrixMakeRotationZ(f32 (*)[4], f32);

void modelAnimEntryBuildKeyMatrix(arg0, arg1, arg2, arg3, arg4)
u8 arg0;
u32 arg1;
ModelBTrack *arg2;
u8 *arg3;
u8 arg4;
{
    u32 off;
    f32 x;
    f32 y;
    f32 z;
    f32 c6;
    f32 c7;
    f32 c8;
    f32 c0;
    f32 c1;
    f32 c2;
    f32 fa;
    f32 fb;
    float work[4][4];
    float mtx[4][4];
    s32 padB[4];

    off = D_807F6BE0;
    fa = ((ModelBKey *)arg3)[arg0 + 1].unkC;
    fb = ((ModelBKey *)arg3)[arg0].unkC;
    x = fa - fb;
    if (x < -180.0) {
        x += 360.0;
    } else if (x > 180.0) {
        x -= 360.0;
    }
    x *= (*(f32 *)&arg1);
    x += fb;
    fa = ((ModelBKey *)arg3)[arg0 + 1].unk10;
    fb = ((ModelBKey *)arg3)[arg0].unk10;
    y = fa - fb;
    if (y < -180.0) {
        y += 360.0;
    } else if (180.0 < y) {
        y -= 360.0;
    }
    if (off == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    y *= (*(f32 *)&arg1);
    y += fb;
    z = ((ModelBKey *)arg3)[arg0 + 1].unk14 - ((ModelBKey *)arg3)[arg0].unk14;
    if (-180.0 > z) {
        z += 360.0;
    } else if (180.0 < z) {
        z -= 360.0;
    }
    z *= (*(f32 *)&arg1);
    z += ((ModelBKey *)arg3)[arg0].unk14;
    c6 = ((ModelBKey *)arg3)[1 + arg0].unk18 - ((ModelBKey *)arg3)[arg0].unk18;
    c6 *= (*(f32 *)&arg1);
    c6 += ((ModelBKey *)arg3)[arg0].unk18;
    if (arg0 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    c7 = ((ModelBKey *)arg3)[1 + arg0].unk1C - ((ModelBKey *)arg3)[arg0].unk1C;
    c7 *= (*(f32 *)&arg1);
    c7 += ((ModelBKey *)arg3)[arg0].unk1C;
    c8 = ((ModelBKey *)arg3)[1 + arg0].unk20 - ((ModelBKey *)arg3)[arg0].unk20;
    c8 *= (*(f32 *)&arg1);
    c8 += ((ModelBKey *)arg3)[arg0].unk20;
    c0 = (((ModelBKey *)arg3)[arg0 + 1].unk0 - ((ModelBKey *)arg3)[arg0].unk0) * *(f32 *)&arg1 + ((ModelBKey *)arg3)[arg0].unk0;
    c1 = *(f32 *)&arg1 * (((ModelBKey *)arg3)[1 + arg0].unk4 - ((ModelBKey *)arg3)[arg0].unk4) + ((ModelBKey *)arg3)[arg0].unk4;
    if (work && work) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (arg4 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    c2 = ((ModelBKey *)arg3)[arg0].unk8 + *(f32 *)&arg1 * (((ModelBKey *)arg3)[arg0 + 1].unk8 - ((ModelBKey *)arg3)[arg0].unk8);
    if (x && x) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    switch (arg4 & 0xF) {
    case 0:
        break;
    case 1:
        c6 *= (f32)(0.125 * (arg4 >> 4 & 0xF));
        break;
        if (off) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    case 2:
        c7 *= (f32)(0.125 * (arg4 >> 4 & 0xF));
        if (work == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        break;
    case 3:
        c8 *= (f32)(0.125 * (arg4 >> 4 & 0xF));
        break;
    case 4:
        if (c7) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (work && work) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        x *= (f32)((arg4 >> 4 & 0xF) * 0.125);
        break;
    case 5:
        y *= (f32)(0.125 * (arg4 >> 4 & 0xF));
        break;
    case 6:
        z *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 7:
        if (c6 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        c0 *= (f32)((arg4 >> 4 & 0xF) * 0.125);
        break;
    case 8:
        c1 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 9:
        c2 *= (f32)(0.125 * (arg4 >> 4 & 0xF));
        break;
    }
    memcpy(work, arg2->unk4 + off, 0x40);
    guScaleF(mtx, c0, c1, c2);
    guMtxCatF(work, mtx, work);
    matrixMakeRotationZ(mtx, z);
    guMtxCatF(work, mtx, work);
    matrixMakeRotationY(mtx, y);
    guMtxCatF(work, mtx, work);
    matrixMakeRotationX(mtx, x);
    guMtxCatF(work, mtx, work);
    guTranslateF(mtx, c6, c7, c8);
    guMtxCatF(work, mtx, work);
    memcpy(mtx, arg2->unk4 + 0x40 + off, 0x40);
    if (c1) {}  // FAKE: steers FP colouring (annealed)
    guMtxCatF(work, mtx, work);
    guMtxF2L(work, (Mtx *)(off + arg2->unk0));
    if (c2 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
}
