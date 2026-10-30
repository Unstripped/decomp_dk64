// func_8064FB64 (src/global/54150.c): stage 4-5 (asm-differ score 13424 -> 5110): frame 0x100, saves only ra+s0(=work), switch now 10-entry (case 0: break), x/y/z/c6-c8 memory homes D8..F8, off FC as target. Needed: K&R params typed arg2 (ModelBTrack *), no arg2/kk locals, keys ((ModelBKey*)arg3)[arg0+1]/[arg0] (two t7/t8 bases), work declared BEFORE mtx (first declared = HIGHER addr), s32 padB[5] above work (target gap 28 bytes), x,y,z,c6,c7,c8 as 3-stmt chains, c0,c1,c2 single expr, 12 greedy dead-if FAKEs (found by an fdiff-score greedy sweep over statement positions x {x,y,z,c0..c8,off,arg0,arg1,work,mtx}; fdiff is ~0.3s per compile so a 1500-variant round is ~5 min). Left: mtx/work at 0x44/0x84 vs 0x3C/0x7C (lower gap 8 bytes too large, upper gap 20 vs 28), target forwards the def of x/y/z into the compare (cvt.d.s f0,f2; swc1) vs ours swc1+lwc1 reload, c6-c8 evaluation interleave, s0 addiu hoisted early
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

void func_8064FB64(arg0, arg1, arg2, arg3, arg4)
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
    s32 padB[5];
    float work[4][4];
    float mtx[4][4];

    off = D_807F6BE0;
    x = ((ModelBKey *)arg3)[arg0 + 1].unkC - ((ModelBKey *)arg3)[arg0].unkC;
    if (x < -180.0) {
        x += 360.0;
    } else if (x > 180.0) {
        x -= 360.0;
    }
    if (work) {} // FAKE: deadsweep-style (steers float/uopt allocation)
    if (arg1 == 0) {} // FAKE: deadsweep-style (steers float/uopt allocation)
    x *= (*(f32 *)&arg1);
    x += ((ModelBKey *)arg3)[arg0].unkC;
    if (arg0 == 0) {} // FAKE: deadsweep-style (steers float/uopt allocation)
    y = ((ModelBKey *)arg3)[arg0 + 1].unk10 - ((ModelBKey *)arg3)[arg0].unk10;
    if (y < -180.0) {
        y += 360.0;
    } else if (y > 180.0) {
        y -= 360.0;
    }
    y *= (*(f32 *)&arg1);
    y += ((ModelBKey *)arg3)[arg0].unk10;
    z = ((ModelBKey *)arg3)[arg0 + 1].unk14 - ((ModelBKey *)arg3)[arg0].unk14;
    if (z < -180.0) {
        z += 360.0;
    } else if (z > 180.0) {
        z -= 360.0;
    }
    if (work) {} // FAKE: deadsweep-style (steers float/uopt allocation)
    z *= (*(f32 *)&arg1);
    z += ((ModelBKey *)arg3)[arg0].unk14;
    c6 = ((ModelBKey *)arg3)[arg0 + 1].unk18 - ((ModelBKey *)arg3)[arg0].unk18;
    c6 *= (*(f32 *)&arg1);
    if (mtx == 0) {} // FAKE: deadsweep-style (steers float/uopt allocation)
    c6 += ((ModelBKey *)arg3)[arg0].unk18;
    if (arg0 && arg0) {} // FAKE: deadsweep-style (steers float/uopt allocation)
    c7 = ((ModelBKey *)arg3)[arg0 + 1].unk1C - ((ModelBKey *)arg3)[arg0].unk1C;
    if (c1) {} // FAKE: deadsweep-style (steers float/uopt allocation)
    if (work && work) {} // FAKE: deadsweep-style (steers float/uopt allocation)
    c7 *= (*(f32 *)&arg1);
    c7 += ((ModelBKey *)arg3)[arg0].unk1C;
    c8 = ((ModelBKey *)arg3)[arg0 + 1].unk20 - ((ModelBKey *)arg3)[arg0].unk20;
    c8 *= (*(f32 *)&arg1);
    c8 += ((ModelBKey *)arg3)[arg0].unk20;
    if (mtx == 0) {} // FAKE: deadsweep-style (steers float/uopt allocation)
    c0 = (((ModelBKey *)arg3)[arg0 + 1].unk0 - ((ModelBKey *)arg3)[arg0].unk0) * (*(f32 *)&arg1) + ((ModelBKey *)arg3)[arg0].unk0;
    c1 = (((ModelBKey *)arg3)[arg0 + 1].unk4 - ((ModelBKey *)arg3)[arg0].unk4) * (*(f32 *)&arg1) + ((ModelBKey *)arg3)[arg0].unk4;
    c2 = (((ModelBKey *)arg3)[arg0 + 1].unk8 - ((ModelBKey *)arg3)[arg0].unk8) * (*(f32 *)&arg1) + ((ModelBKey *)arg3)[arg0].unk8;
    switch (arg4 & 0xF) {
    case 0:
        break;
    case 1:
        c6 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 2:
        c7 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 3:
        c8 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 4:
        x *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 5:
        y *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 6:
        z *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 7:
        c0 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 8:
        c1 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 9:
        c2 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    }
    if (c8 == 0) {} // FAKE: deadsweep-style (steers float/uopt allocation)
    if (c1 && c1) {} // FAKE: deadsweep-style (steers float/uopt allocation)
    if (c6 && c6) {} // FAKE: deadsweep-style (steers float/uopt allocation)
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
    memcpy(mtx, arg2->unk4 + off + 0x40, 0x40);
    guMtxCatF(work, mtx, work);
    guMtxF2L(work, (Mtx *)(arg2->unk0 + off));
}
