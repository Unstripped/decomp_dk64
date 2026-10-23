// func_80654CCC (src/global/55B20.c): stage5-6 near-miss (M55P4)
#include "common.h"
#include "actor.h"

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
} M55P4Tri;

f32 func_80654CCC(M55P4Tri *arg0, f32 arg1, f32 arg2) {
    f64 t1;
    f64 t2;
    f64 t3;
    f64 t4;
    f64 t5;
    f64 t6;
    f64 n1;
    f64 n2;
    f64 n3;
    f64 q;
    f64 t;

    t1 = (f64)(arg0->unk6 - arg0->unk8);
    t2 = (f64)(arg0->unk0 - arg0->unk2);
    t3 = (f64)(arg0->unkC - arg0->unk10);
    t4 = (f64)(arg0->unkC - arg0->unkE);
    t5 = (f64)(arg0->unk6 - arg0->unkA);
    t6 = (f64)(arg0->unk0 - arg0->unk4);
    n1 = t1 * t3 - t4 * t5;
    n2 = t4 * t6 - t2 * t3;
    n3 = t2 * t5 - t1 * t6;
    q = -((n3 * (f64)arg0->unkE + (n1 * (f64)arg0->unk2 + n2 * (f64)arg0->unk8)));
    if (n2 * 2000.0 > 0.01 || n2 * 2000.0 < -0.01) {
        t = ((arg1 * n1 + n2 * -1000.0) + n3 * arg2) + q;
        t = t / (n2 * 2000.0);
        if (t < 0.0) {
            t = -t;
        }
        return (f32)(2000.0 * t - 1000.0);
    }
    return -32768.0f;
}
