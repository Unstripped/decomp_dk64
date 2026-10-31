// mapTriangleHeightAtPoint (src/global/55B20.c): stage 3 (MapA): frame now 0x40 like target (6 named s32 edge diffs d68,d02,dC10,dCE,d6A,d04 + f64 q,t locals; n1..n3 inline via macros so n2*2000.0 is a CSE expr, not a var) but still 99 text lines: mine saves extra $f26, q not spilled to 0x20(sp), load order unk10/unkC/unk8/unk6 vs target unk8,unk6,unk2,unk0,unkC,unk10. Hypothesis: target = leaf with a spilled f64 q forcing the full 4-slot locals area (0x20..0x3F); callee-saved set f20,f22,f24 with f20 unused. Random decl/assign order grid (400) best full=114 (vs 130).
#define MapAN1 ((f64)d68 * (f64)dC10 - (f64)dCE * (f64)d6A)
#define MapAN2 ((f64)dCE * (f64)d04 - (f64)d02 * (f64)dC10)
#define MapAN3 ((f64)d02 * (f64)d6A - (f64)d68 * (f64)d04)
f32 mapTriangleHeightAtPoint(MapTriangle *arg0, f32 arg1, f32 arg2) {
    s32 d68;
    s32 dCE;
    s32 dC10;
    s32 d02;
    s32 d04;
    s32 d6A;
    f64 q;
    f64 t;

    d68 = arg0->unk6 - arg0->unk8;
    dCE = arg0->unkC - arg0->unkE;
    dC10 = arg0->unkC - arg0->unk10;
    d6A = arg0->unk6 - arg0->unkA;
    d02 = arg0->unk0 - arg0->unk2;
    d04 = arg0->unk0 - arg0->unk4;
    q = -((MapAN1 * (f64)arg0->unk2 + MapAN2 * (f64)arg0->unk8) + MapAN3 * (f64)arg0->unkE);
    if (MapAN2 * 2000.0 > 0.01 || MapAN2 * 2000.0 < -0.01) {
        t = ((arg1 * MapAN1 + MapAN2 * -1000.0) + MapAN3 * arg2) + q;
        t = t / (MapAN2 * 2000.0);
        if (t < 0.0) {
            t = 0.0 - t;
        }
        return (f32)(2000.0 * t - 1000.0);
    }
    return -32768.0f;
}
