// modelAnimEntryBuildKeyMatrix (src/global/54150.c): leftovers6 W2FrameA: stage 4 (NOT 5): count 351 and frame 0x100 OK but whole-function score full=131 text=127 reloc=4 shape=67 (park gives 383 vs 387 lines incl. relocs); stack homes 216..264 exact, only mtx 88(sp) vs 60(sp). Structural differences beyond frame: target keeps the argument-4 byte in v0 across the switch (sra t1,v0,4) while ours reloads lw 264(sp) in every case arm; target colours the two arg3 field loads f12/f14 (x += arg3[arg0].unkC reuses f14) and x as f18 spilled at 236(sp) while ours uses ring f4/f2; ldc1 -180.0/180.0 constants hoisted differently (target lui+ldc1 once). Next: fix those colourings first (arg4 u8 as coloured candidate: K&R u8 formal copy / dead use before the switch; CSE of arg3[arg0].unkC) before any frame work; frame low region (28B below mtx, 28B between mtx/work and homes) follows from the uopt temp area and will move with those.
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
    float work[4][4];
    float mtx[4][4];
    s32 padB[5];

    off = D_807F6BE0;
    x = ((ModelBKey *)arg3)[arg0 + 1].unkC - ((ModelBKey *)arg3)[arg0].unkC;
    if (x < -180.0) {
        x += 360.0;
    } else if (x > 180.0) {
        x -= 360.0;
    }
    x *= (*(f32 *)&arg1);
    x += ((ModelBKey *)arg3)[arg0].unkC;
    y = ((ModelBKey *)arg3)[arg0 + 1].unk10 - ((ModelBKey *)arg3)[arg0].unk10;
    if (y < -180.0) {
        y += 360.0;
    } else if (y > 180.0) {
        y -= 360.0;
    }
    if (off == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    y *= (*(f32 *)&arg1);
    y += ((ModelBKey *)arg3)[arg0].unk10;
    z = ((ModelBKey *)arg3)[arg0 + 1].unk14 - ((ModelBKey *)arg3)[arg0].unk14;
    if (z < -180.0) {
        z += 360.0;
    } else if (z > 180.0) {
        z -= 360.0;
    }
    z *= (*(f32 *)&arg1);
    z += ((ModelBKey *)arg3)[arg0].unk14;
    c6 = ((ModelBKey *)arg3)[arg0 + 1].unk18 - ((ModelBKey *)arg3)[arg0].unk18;
    c6 *= (*(f32 *)&arg1);
    c6 += ((ModelBKey *)arg3)[arg0].unk18;
    if (arg0 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    c7 = ((ModelBKey *)arg3)[arg0 + 1].unk1C - ((ModelBKey *)arg3)[arg0].unk1C;
    c7 *= (*(f32 *)&arg1);
    c7 += ((ModelBKey *)arg3)[arg0].unk1C;
    c8 = ((ModelBKey *)arg3)[arg0 + 1].unk20 - ((ModelBKey *)arg3)[arg0].unk20;
    c8 *= (*(f32 *)&arg1);
    c8 += ((ModelBKey *)arg3)[arg0].unk20;
    c0 = (((ModelBKey *)arg3)[arg0 + 1].unk0 - ((ModelBKey *)arg3)[arg0].unk0) * (*(f32 *)&arg1) + ((ModelBKey *)arg3)[arg0].unk0;
    c1 = (((ModelBKey *)arg3)[arg0 + 1].unk4 - ((ModelBKey *)arg3)[arg0].unk4) * (*(f32 *)&arg1) + ((ModelBKey *)arg3)[arg0].unk4;
    if (work && work) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (arg4 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    c2 = (((ModelBKey *)arg3)[arg0 + 1].unk8 - ((ModelBKey *)arg3)[arg0].unk8) * (*(f32 *)&arg1) + ((ModelBKey *)arg3)[arg0].unk8;
    if (x && x) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    switch (arg4 & 0xF) {
    case 0:
        break;
    case 1:
        c6 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
        if (off) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    case 2:
        c7 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        if (work == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        break;
    case 3:
        c8 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 4:
        if (c7) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (work && work) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        x *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 5:
        y *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 6:
        z *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 7:
        if (c6 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        c0 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 8:
        c1 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 9:
        c2 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
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
    memcpy(mtx, arg2->unk4 + off + 0x40, 0x40);
    guMtxCatF(work, mtx, work);
    guMtxF2L(work, (Mtx *)(arg2->unk0 + off));
    if (c2 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
}
