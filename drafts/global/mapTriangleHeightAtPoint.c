// mapTriangleHeightAtPoint (src/global/55B20.c): leftovers5 MapA: stage 5 (deadsweep full=17 text=17 shape=0 vs 56): all 6 diffs f64 named locals, N1/N2 f64 named, N3 inline, tail identical, colours/frame/schedule all match; remaining only commutative operand order + ring temps in q block: target mul.d f8,f18,f6 (N1*u2, ours f6,f18), mul.d f6,f8,f22 ok, add.d f4,f6,f10 (prod3+sum12; ours f10,f6), then mul.d f10,f0,f24 / ldc1 f6 (ours f6/f10) and cascade through t. Operand order not source-controlled (exhaustive q-term swaps/assoc 12x8x4, u2/u8/uE named s32/f64 temps 125x, N inline/named x d forms x decl orders, 2x270s hill-climb with dead tests: floor 17).
f32 mapTriangleHeightAtPoint(MapTriangle *arg0, f32 arg1, f32 arg2) {
    f64 t;
    f64 dCE;
    f64 d02;
    f64 q;
    f64 d04;
    f64 d6A;
    f64 N1;
    f64 N2;
    f64 dC10;
    f32 ret;
    f64 d68;

    d02 = (f64)(arg0->unk0 - arg0->unk2);
    d68 = (f64)(arg0->unk6 - arg0->unk8);
    dCE = (f64)(arg0->unkC - arg0->unkE);
    d04 = (f64)(arg0->unk0 - arg0->unk4);
    d6A = (f64)(arg0->unk6 - arg0->unkA);
    dC10 = (f64)(arg0->unkC - arg0->unk10);
    N1 = d68 * dC10 - dCE * d6A;
    N2 = dCE * d04 - d02 * dC10;
    q = -((f64)arg0->unk2 * N1 + N2 * (f64)arg0->unk8 + (f64)arg0->unkE * (d02 * d6A - d68 * d04));
    if (N2 * 2000.0 > 0.01 || N2 * 2000.0 < -0.01) {
        t = N1 * arg1 + N2 * -1000.0 + arg2 * (d02 * d6A - d68 * d04) + q;
        t = t / (N2 * 2000.0);
        if (t < 0.0) {
            t = 0.0 - t;
        }
        ret = (f32)(2000.0 * t - 1000.0);
    } else {
        ret = -32768.0f;
    }
    return ret;
}
