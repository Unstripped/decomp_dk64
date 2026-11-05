// modelAnimEntryBuildKeyMatrix (src/global/54150.c): stage 4 park (diff 98, count exact 351, frame 256 ok). Levers: deleted all 5 annealed FAKEs (count/diff identical without them), typed AnimKeyMtx_ structs; verified f18 web reuse (360.0 constant -> c6 -> c1). Remaining: c6/c7/c2 FP colours (target: c6 f18 spilled to home 0xEC, c7 ring temp, c1 f18, c2 f2) and arg1 split copy (lwc1 f4 + mov.s f14,f4 before c8) + lbu v0 vs a0 for arg4.
typedef struct AnimKeyMtx_ModelBTrack {
    u8 *unk0;
    u8 *unk4;
} AnimKeyMtx_ModelBTrack;

typedef struct AnimKeyMtx_ModelBKey {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
} AnimKeyMtx_ModelBKey; /* 0x24 */

void matrixMakeRotationX(f32 (*)[4], f32);
void matrixMakeRotationY(f32 (*)[4], f32);
void matrixMakeRotationZ(f32 (*)[4], f32);

void modelAnimEntryBuildKeyMatrix(arg0, arg1, arg2, arg3, arg4)
u8 arg0;
u32 arg1;
AnimKeyMtx_ModelBTrack *arg2;
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
    s32 q0;  // pad words: frame/home layout
    s32 q1;
    s32 q2;
    s32 q3;
    s32 q4;
    float work[4][4];
    float mtx[4][4];

    off = D_807F6BE0;
    fa = ((AnimKeyMtx_ModelBKey *)arg3)[arg0 + 1].unkC;
    fb = ((AnimKeyMtx_ModelBKey *)arg3)[arg0].unkC;
    x = fa - fb;
    if (-180.0 > x) {
        x += 360.0;
    } else if (180.0 < x) {
        x -= 360.0;
    }
    x *= (*(f32 *)&arg1);
    x += fb;
    fa = ((AnimKeyMtx_ModelBKey *)arg3)[arg0 + 1].unk10;
    fb = ((AnimKeyMtx_ModelBKey *)arg3)[arg0].unk10;
    y = fa - fb;
    if (y < -180.0) {
        y += 360.0;
    } else if (y > 180.0) {
        y -= 360.0;
    }
    y *= (*(f32 *)&arg1);
    y += fb;
    fa = ((AnimKeyMtx_ModelBKey *)arg3)[arg0 + 1].unk14;
    fb = ((AnimKeyMtx_ModelBKey *)arg3)[arg0].unk14;
    z = fa - fb;
    if (z < -180.0) {
        z += 360.0;
    } else if (180.0 < z) {
        z -= 360.0;
    }
    z *= (*(f32 *)&arg1);
    z += fb;
    c6 = ((AnimKeyMtx_ModelBKey *)arg3)[1 + arg0].unk18 - ((AnimKeyMtx_ModelBKey *)arg3)[arg0].unk18;
    c6 *= (*(f32 *)&arg1);
    c6 += ((AnimKeyMtx_ModelBKey *)arg3)[arg0].unk18;
    c7 = (*(f32 *)&arg1) * (((AnimKeyMtx_ModelBKey *)arg3)[1 + arg0].unk1C - ((AnimKeyMtx_ModelBKey *)arg3)[arg0].unk1C) + ((AnimKeyMtx_ModelBKey *)arg3)[arg0].unk1C;
    c8 = (((AnimKeyMtx_ModelBKey *)arg3)[arg0 + 1].unk20 - ((AnimKeyMtx_ModelBKey *)arg3)[arg0].unk20) * (*(f32 *)&arg1) + ((AnimKeyMtx_ModelBKey *)arg3)[arg0].unk20;
    c0 = ((AnimKeyMtx_ModelBKey *)arg3)[arg0].unk0 + (*(f32 *)&arg1) * (((AnimKeyMtx_ModelBKey *)arg3)[arg0 + 1].unk0 - ((AnimKeyMtx_ModelBKey *)arg3)[arg0].unk0);
    c1 = (*(f32 *)&arg1) * (((AnimKeyMtx_ModelBKey *)arg3)[1 + arg0].unk4 - ((AnimKeyMtx_ModelBKey *)arg3)[arg0].unk4) + ((AnimKeyMtx_ModelBKey *)arg3)[arg0].unk4;
    c2 = ((AnimKeyMtx_ModelBKey *)arg3)[arg0].unk8 + (*(f32 *)&arg1) * (((AnimKeyMtx_ModelBKey *)arg3)[arg0 + 1].unk8 - ((AnimKeyMtx_ModelBKey *)arg3)[arg0].unk8);
    switch (arg4 & 0xF) {
    case 0:
        break;
    case 1:
        c6 *= (f32)(0.125 * (arg4 >> 4 & 0xF));
        break;
    case 2:
        c7 *= (f32)(0.125 * (arg4 >> 4 & 0xF));
        break;
    case 3:
        c8 *= (f32)(0.125 * (arg4 >> 4 & 0xF));
        break;
    case 4:
        x *= (f32)((arg4 >> 4 & 0xF) * 0.125);
        break;
    case 5:
        y *= (f32)(0.125 * (arg4 >> 4 & 0xF));
        break;
    case 6:
        z *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 7:
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
    guMtxCatF(work, mtx, work);
    guMtxF2L(work, (Mtx *)(off + arg2->unk0));
}
