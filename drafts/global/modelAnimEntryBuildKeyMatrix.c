// modelAnimEntryBuildKeyMatrix (src/global/54150.c): stage 4-5 (parked NON_MATCHING in src copy; frame 0x100, saves ra+s0 ok; deadsweep line-diff 324 -> 131 of 387 target lines, no FAKE reads an unassigned local). Needed: K&R params typed arg2 (ModelBTrack *), keys ((ModelBKey*)arg3)[arg0+1]/[arg0], x,y,z,c6,c7,c8 as 3-stmt chains, c0..c2 single expr, switch 10 entries (case 0 break), memcpy before guScaleF, 11 dead-if FAKEs found by random hill-climb over statement positions x symbols x forms (+ decl-order swaps), score = deadsweep full diff (0.3s/compile). Left: (1) x/y/z first compare uses reloaded x (swc1;lwc1;cvt.d.s) vs target forwards sub.s result f2 into cvt.d.s with the store after (x only block-locally in a reg, home FC..D8 = 10 words); (2) stack: mtx/work at 0x58/0x98 here (padB after mtx) vs 0x3C/0x7C target (28-byte gaps both below mtx and above work; compiler adds an intrinsic ~36-byte low region, frame=round8(locals+36)); (3) prologue sll/addu order, f12/f14 used as key-load candidates in target; nofake body colours x,y in callee-saved f20/f22 (sdc1) so the target source must keep every float local memory-homed without FAKEs (all nine live across memcpy + 4 calls)
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
