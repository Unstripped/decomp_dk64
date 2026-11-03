// proxPathActorFollowSpline (src/global/133A90.c): W3Count: COUNT-EXACT 486/486 frame ok (parked), full=8 shape=4. idx2 int + (s8) casts, idx2 declared after p0, no w2 pad, idx2=(s8)(arg3&0xFF) (avoid CSE with idx), dead 'if (arg2->unk7 && arg2->unk7) {}'. Remaining 8: idiom1 sum cand v1/t7 vs v0/t8 (target: cand and var share v0), idx2 init 'move v0,s0;sll;sra' vs 'sll v0,s0;sra t2;move v0,t2', idiom2 sum cand a0 vs v0. Cand+var interfere in same bb in ours; no spelling found that avoids forwarding of the compare (tried if/else, assignment-in-cond, two-step, bb-boundary fakes, 12k-eval dead-test anneal, deadsweep 2 rounds).
void proxPathActorFollowSpline(H1ActorB *arg0, H1ActorState *arg1, ProxPath *arg2, u8 arg3, f32 arg4) {
    f32 one;
    f32 pad1[20];
    f32 p2[3];
    f32 p1[3];
    f32 p0[3];
    int idx2;
    f32 a;
    f32 b;
    s16 slot;
    f32 m1[4][4];
    f32 m2[4][4];
    s32 gapw;
    f32 m3[4][4];
    f32 ox;
    f32 oy;
    f32 oz;
    f32 yaw;
    f32 pad2[4];
    Mtx mA;
    int idx;
    f32 savedScale;
    Mtx mB;
    Mtx mC;
    splineSetBasisTension(0.5f);
    idx = (s8)arg3;
    a = arg4 - 0.1;
    if (a < 0.0) {
        a = a + 1.0;
        idx = (s8)(arg3 - 1);
        if (idx < 0) {
            a = 0.0f;
            idx = 0;
        }
    }
    idx = idx & 0xFF; // FAKE: no-code def, idx coloured v0 (forbidden-v0 call-arg use moves)
    proxPathInterpolatePosition(idx, a, arg2, &p0[0], &p0[1], &p0[2]);
    one = 1.0f;
    b = arg4 + 0.1;
    idx2 = (s8)(arg3 & 0xFF); // FAKE: no-code mask keeps (s8)arg3 from CSE with idx's chain
    if (b > 1.0) {
        b = b - 1.0;
        idx2 = (s8)(arg3 + 1);
        if (arg2->unk7 && arg2->unk7) {} // FAKE: dead field test steers idx2 sum colouring
        if (idx2 == arg2->unk7) {
            idx2 = arg2->unk7 - 1; idx2 = (s8)idx2; // LAYOUT: two-step narrow
            b = 1.0f;
        }
    }
    proxPathInterpolatePosition(idx2, b, arg2, &p1[0], &p1[1], &p1[2]);
    proxPathInterpolatePosition(arg3, arg4, arg2, &p2[0], &p2[1], &p2[2]);
    savedScale = arg1->unk148;
    arg1->unk148 = one;
    arg0->unk7C = (p2[0] - arg1->unk13C) * arg1->unk148 + arg1->unk13C;
    arg0->unk80 = (p2[1] - arg1->unk140) * arg1->unk148 + arg1->unk140;
    arg0->unk84 = (p2[2] - arg1->unk144) * arg1->unk148 + arg1->unk144;
    func_80611A70(p0[0], p0[2], &p1[0], &p1[2]);
    yaw = func_80611BB4(p1[0] - p0[0], p1[2] - p0[2]) * 57.29577637f + 180.0f;
    guTranslateF(m1, 0.0f, arg1->unk148 * -80.0f, 0.0f);
    guScaleF(m2, arg0->unk4->unk34, arg0->unk4->unk38, arg0->unk4->unk3C);
    guMtxCatF(m1, m2, m1);
    guRotateF(m2, arg0->unkE6 / 4095.0 * 360.0, 0.0f, one, 0.0f);
    guMtxCatF(m1, m2, m1);
    guRotateF(m2, -90.0f, one, 0.0f, 0.0f);
    guMtxCatF(m1, m2, m1);
    guAlignF(m2, yaw, p1[0] - p0[0], p1[1] - p0[1], p1[2] - p0[2]);
    guMtxCatF(m1, m2, m1);
    guRotateF(m3, arg0->unkE6 / 4095.0 * 360.0, 0.0f, one, 0.0f);
    yaw = arg2->unk34[arg3].unk8 + (arg2->unk34[arg3].unkC - arg2->unk34[arg3].unk8) * arg4;
    guMtxXFMF(m3, 0.0f, 0.0f, -yaw * arg1->unk148, &ox, &oy, &oz);
    guTranslateF(m2, ox, oy, oz);
    guMtxCatF(m1, m2, m1);
    guMtxCatF(m1, m2, m1);
    guTranslateF(m2, arg0->unk7C, arg0->unk80, arg0->unk84);
    guMtxCatF(m1, m2, arg0->unkC);
    arg1->unk148 = savedScale;
    if (savedScale < 1.0) {
        guMtxF2L((f32 (*)[4])arg1->unk15C, &mB);
        guMtxF2L(arg0->unkC, &mC);
        mtxLerpL(&mB, &mC, 1.0 - arg1->unk148, &mA);
        guMtxL2F(arg0->unkC, &mA);
    }
    arg1->unk148 = arg1->unk148 + 0.1;
    if (arg1->unk148 > 1.0) {
        arg1->unk148 = one;
    }
    arg1->unk19C = (s16)(arg2->unk34[arg3].unk10 + (arg2->unk34[arg3].unk12 - arg2->unk34[arg3].unk10) * arg4);
    arg1->unk19E = (s16)(arg2->unk34[arg3].unk14 + (arg2->unk34[arg3].unk16 - arg2->unk34[arg3].unk14) * arg4);
    switch (arg2->unk4) {
    case 1:
    case 2:
        slot = hashTableLookup(arg2->unk0);
        arg1->unk19C = ((s32)(D_807F6000[slot].unk14 * 4096.0f / 360.0f) + arg1->unk19C) & 0xFFF;
        arg1->unk19E = ((s32)(D_807F6000[slot].unk14 * 4096.0f / 360.0f) + arg1->unk19E) & 0xFFF;
        break;
    case 0:
        arg1->unk19C = (arg1->unk19C + arg2->unk0->unkE6) & 0xFFF;
        arg1->unk19E = (arg1->unk19E + arg2->unk0->unkE6) & 0xFFF;
        break;
    }
}
