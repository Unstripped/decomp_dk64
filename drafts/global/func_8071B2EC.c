// func_8071B2EC (src/global/11BC10.c): stage 4: m2c logic and corrected 0x384 layout compile; closest diff starts at delay-slot/local lifetime and float constant placement
#include "common.h"

typedef struct { u8 pad0[0xB8]; f32 unkB8; u8 padBC[0x32]; s16 unkEE; } Ub4Parent;
typedef struct { f32 angle; f32 speed; } Ub4Motion;
typedef struct { u8 pad0[0x338]; Ub4Parent *parent; u8 pad33C[0x48]; f32 x; f32 y; f32 z; u8 pad34C[0x36]; Ub4Motion *motion; } Ub4Actor;
void *func_80610FE8(s32);
f32 func_80612794(s16);
f32 func_80612790(s16);

void func_8071B2EC(Ub4Actor *arg0, s8 *arg1) {
    f32 speed;
    Ub4Motion *motion = arg0->motion;
    if (motion == NULL) {
        arg0->motion = func_80610FE8(8);
        arg0->motion->angle = (f32)arg0->parent->unkEE;
        arg0->motion->speed = arg0->parent->unkB8 + 30.0f;
        motion = arg0->motion;
    }
    arg0->y = (f32)((f64)arg0->y + ((f64)0.35f * 0.5));
    speed = (f32)((f64)motion->speed * 0.02);
    arg0->x = (f32)(arg0->x + (speed * func_80612794((s16)(s32)motion->angle)));
    arg0->z = (f32)(arg0->z + (speed * func_80612790((s16)(s32)motion->angle)));
    motion->speed -= 15.0f;
    if (motion->speed < 0.0f) motion->speed = 0.0f;
}
