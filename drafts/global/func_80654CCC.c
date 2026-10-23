// func_80654CCC (src/global/55B20.c): stage4-5: inline cross-product form, instructions close; frame 0x20 vs 0x40 (target spills q at 0x20 and keeps 2000.0 in f24 across the branch, recomputes n2*2000 in 2nd || arm)
// Instruction sequence matches the target closely (n1/n2/n3 via inline cross products,
// 2000.0/0.01/-0.01/-1000/1000 constants, 0.0 - t abs, q = -(...) then + q) but the frame
// is 0x20 vs the target's 0x40: the target spills q (-(n1*unk2+n2*unk8+n3*unkE)) to 0x20(sp)
// and keeps 2000.0 in f24 across the branch, while this form keeps q in f18 and reloads
// 2000.0 from .rodata; target also recomputes n2*2000 in the second || arm.
#include "common.h"
#include "actor.h"

f32 func_80654CCC(M55P4Tri *arg0, f32 arg1, f32 arg2) {
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
