// func_8071B24C (src/global/11BC10.c): stage 6: exact 0xA0 body and control flow; local 0.35f reproduces target double arithmetic and all operations, with only post-call FP register allocation/rodata relocation remaining
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

void func_8071B24C(Ub4ActorView *arg0, s8 *arg1) {
    f32 speed;

    speed = 0.35f;
    arg0->unk344 = (f32)((f64)arg0->unk344 + ((f64)speed * 0.5));
    arg0->unk340 = (f32)(arg0->unk340 + (func_80612794(arg0->unk35E) * speed));
    arg0->unk348 = (f32)(arg0->unk348 + (func_80612790(arg0->unk35E) * speed));
}
