// mapTriangleHeightAtPoint (src/global/55B20.c): W2Frame: stage 4 (deadsweep full=56 text=56 vs 99 before; 120/120 lines, frame 0x40, saves f24/f22/f20, q spilled at 32(sp), tail after the branch (t f12, abs f2, ret f12 + mov.s f0,f12, N2 f0, 0.0 f14, 2000.0 f24) identical). Remaining: front block colouring/schedule: target d68 f12,d02 f2,dC10 f24,dCE f22,d6A f16,d04 f14,N1 f18,N3 f22 and f20 never used (only saved, early ldc1 f20,8(sp) restore); ours uses f20 for a d value and loads fields uE/uC/u4/u0 first (target u8,u6,u2,u0,uC,u10,uE,uA,u4). Found by hill-climb (mixed named s32/f64/inline d values, inline N3 expression, ret var, abs via u=t copy) with deadsweep score, floor 112 over 4 x 280s runs; deadsweep globals none.
f32 mapTriangleHeightAtPoint(MapTriangle *arg0, f32 arg1, f32 arg2) {
    f64 dCE;
    f64 n2;
    f32 ret;
    f64 q;
    f64 u;
    f64 dC10;
    f64 n1;
    f64 d6A;
    f64 d04;
    s32 d02;
    f64 t;

    d04 = (f64)(arg0->unk0 - arg0->unk4);
    dCE = (f64)(arg0->unkC - arg0->unkE);
    dC10 = (f64)(arg0->unkC - arg0->unk10);
    if (dC10 == 0) {} // FAKE: x
    d02 = arg0->unk0 - arg0->unk2;
    d6A = (f64)(arg0->unk6 - arg0->unkA);
    n2 = (dCE * d04 - (f64)d02 * dC10);
    n1 = ((f64)(arg0->unk6 - arg0->unk8) * dC10 - dCE * d6A);
    if (d02 != 0) {} // FAKE: x
    q = -((n1 * (f64)arg0->unk2 + n2 * (f64)arg0->unk8) + ((f64)d02 * d6A - (f64)(arg0->unk6 - arg0->unk8) * d04) * (f64)arg0->unkE);
    if (n2 * 2000.0 > 0.01 || n2 * 2000.0 < -0.01) {
        t = (((arg1 * n1 + n2 * -1000.0) + ((f64)d02 * d6A - (f64)(arg0->unk6 - arg0->unk8) * d04) * arg2) + q) / (n2 * 2000.0);
        u = t;
        if (t < 0.0) {
            u = 0.0 - t;
        }
        ret = (f32)(2000.0 * u - 1000.0);
    } else {
        ret = -32768.0f;
    }
    return ret;
}
