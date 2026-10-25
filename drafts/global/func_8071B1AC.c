// func_8071B1AC (src/global/11BC10.c): stage 6: permutation search found explicit first-call temporary; exact 0xA0 body and control flow, remaining post-call FP operand/register allocation and rodata relocation
#include "common.h"

typedef struct {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x12];
    s16 unk35E;
} Ub4ActorView;

f32 func_80612790(s16);
f32 func_80612794(s16);

void func_8071B1AC(Ub4ActorView *arg0, s8 *arg1) {
    f32 new_var;
    f32 speed;

    speed = 0.35f;
    arg0->unk344 = (f32)((f64)arg0->unk344 - ((f64)speed * 0.5));
    new_var = func_80612794(arg0->unk35E);
    arg0->unk340 = (f32)(arg0->unk340 + (new_var * speed));
    arg0->unk348 = (f32)(arg0->unk348 + (func_80612790(arg0->unk35E) * speed));
}
