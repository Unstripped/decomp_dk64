// func_8071B1AC (src/global/11BC10.c): stage 5: correct field offsets and call order; closest diff differs in 0.35 double constant materialization and FPR allocation
#include "common.h"

typedef struct {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    f32 unk348;
} Ub4ActorView;

f32 func_80612794(s16);
f32 func_80612790(s16);

void func_8071B1AC(Ub4ActorView *arg0, s8 *arg1) {
    arg0->unk344 = (f32)((f64)arg0->unk344 - ((f64)0.35f * 0.5));
    arg0->unk340 = (f32)(arg0->unk340 + (0.35f * func_80612794(*((s16 *)((u8 *)arg0 + 0x35E)))));
    arg0->unk348 = (f32)(arg0->unk348 + (0.35f * func_80612790(*((s16 *)((u8 *)arg0 + 0x35E)))));
}
