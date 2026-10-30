// mapTriangleHeightAtPoint (src/global/55B20.c): stage 3: instruction order differs (97 text lines) and frame 0x20 vs 0x40. Target = cross products n1..n3 of edge diffs d68,d02,dC10,dCE,d6A,d04 (cvt'd early), q=-(n1*u2+n2*u8+n3*uE) spilled to 0x20(sp), 2000.0 hoisted to f24, n2*2000 recomputed 3x (CSE candidate uncolored), f20 saved+restored unused, locals area 0x20..0x3F (4 slots). Tried: f64 locals for diffs (frame 0x70, n3 also spills), unused f64/array pads (dropped in leaf), scale=2000.0 local (folded, identical), deadsweep (no gain)
typedef struct S55dTri {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
} S55dTri;

f32 mapTriangleHeightAtPoint(S55dTri *arg0, f32 arg1, f32 arg2) {
    f64 n1;
    f64 n2;
    f64 n3;
    f64 q;
    f64 t;

    n1 = (f64)(arg0->unk6 - arg0->unk8) * (f64)(arg0->unkC - arg0->unk10) - (f64)(arg0->unkC - arg0->unkE) * (f64)(arg0->unk6 - arg0->unkA);
    n2 = (f64)(arg0->unkC - arg0->unkE) * (f64)(arg0->unk0 - arg0->unk4) - (f64)(arg0->unk0 - arg0->unk2) * (f64)(arg0->unkC - arg0->unk10);
    n3 = (f64)(arg0->unk0 - arg0->unk2) * (f64)(arg0->unk6 - arg0->unkA) - (f64)(arg0->unk6 - arg0->unk8) * (f64)(arg0->unk0 - arg0->unk4);
    q = -((n1 * (f64)arg0->unk2 + n2 * (f64)arg0->unk8) + n3 * (f64)arg0->unkE);
    if (n2 * 2000.0 > 0.01 || n2 * 2000.0 < -0.01) {
        t = ((arg1 * n1 + n2 * -1000.0) + n3 * arg2) + q;
        t = t / (n2 * 2000.0);
        if (t < 0.0) {
            t = 0.0 - t;
        }
        return (f32)(2000.0 * t - 1000.0);
    }
    return -32768.0f;
}
