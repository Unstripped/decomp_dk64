// func_8071B44C (src/global/11BC10.c): stage 4: m2c logic and corrected 0x384 layout compile; closest diff starts at delay-slot/local lifetime and float constant placement
#include "common.h"

typedef struct { u8 pad0[0xB8]; f32 unkB8; } Ub4Parent;
typedef struct { f32 angle; } Ub4Motion;
typedef struct { u8 pad0[0x338]; Ub4Parent *parent; u8 pad33C[0x48]; f32 x; f32 y; f32 z; u8 pad34C[0x36]; Ub4Motion *motion; } Ub4Actor;
void *func_80610FE8(s32);
f32 func_80612794(s16);
f32 func_80612790(s16);

void func_8071B44C(Ub4Actor *arg0, s8 *arg1) {
    f32 speed;
    Ub4Motion *motion = arg0->motion;
    if (motion == NULL) {
        arg0->motion = func_80610FE8(4);
        arg0->motion->angle = arg0->parent->unkB8;
        motion = arg0->motion;
    }
    arg0->y = (f32)((f64)arg0->y + ((f64)0.35f * 0.5));
    speed = (f32)((f64)motion->angle * 0.02);
    arg0->x = (f32)(arg0->x + (speed * func_80612794(*((s16 *)((u8 *)arg0 + 0x35E)))));
    arg0->z = (f32)(arg0->z + (speed * func_80612790(*((s16 *)((u8 *)arg0 + 0x35E)))));
}
