// modelAnimEntryBuildKeyMatrix (src/global/54150.c): W2Frame: stage 4-5 unchanged (parked body kept; text 351 insns, frame 0x100 OK). Layout probe: with padB[5] below mtx -> mtx 0x58/work 0x98; target mtx 0x3C/work 0x7C (28B hidden below mtx + 28B above work + 10 named words D8..FC). Sweeping padA[k] (declared before work) / padB[m]: mtx moves down 4B per padA word, hidden-low floor is 32B (mtx 0x40/work 0x80 at padA[6], frame 0x100); padA[7] -> frame 0x108, so the target's 28B low region (3 words fewer than ours + 1) cannot be reached by pads: the low region does not depend on switch/memcpy/guXxx calls (ablated each) but removing all FAKE dead ifs raises frame to 0x110, i.e. the low-region size is coupled to the dead-test set. Next: search FAKE sets scored on stack offsets (mtx must be 0x3C) rather than text.
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
