// func_8071AF30 (src/global/11BC10.c): stage 2: m2c-derived control flow; closest diff preserves allocation, random rotation, and copy tail but parent-motion branch remains incomplete
#include "common.h"

typedef struct { u8 pad0[0x58]; s32 mode; u8 pad5C[4]; u32 flags; u8 pad64[0x54]; f32 scale; u8 padBC[0x32]; s16 angle; } Ub4Parent;
typedef struct { u8 pad0[0x32C]; u8 state; u8 pad32D[0xB]; f32 x; f32 y; f32 z; u8 pad34C[0x10]; Ub4Parent *parent; f32 scaleX; f32 scaleY; u8 pad368[0x1C]; void *matrix; } Ub4Actor;
void *func_80610FE8(s32);
s32 func_806119A0(void);
f32 func_80612794(s16);
f32 func_80612790(s16);

void func_8071AF30(Ub4Actor *arg0, s8 *arg1) {
    f32 mtx0[4][4], mtx1[4][4];
    u32 angle;
    Ub4Parent *parent = arg0->parent;
    if ((parent->flags & 4) == 0) {
        *arg1 = 1;
        return;
    }
    if (arg0->matrix == NULL) {
        arg0->matrix = func_80610FE8(0x40);
        angle = (u32)(func_806119A0() % 36000U) / 100U;
        guScaleF(mtx0, arg0->scaleX, arg0->scaleY, 0.0f);
        guRotateF(mtx1, (f32)angle, 0.0f, 0.0f, 1.0f);
        guMtxCatF(mtx0, mtx1, mtx0);
        guMtxF2L(mtx0, arg0->matrix);
    }
    if ((parent->mode == 0xC5) && ((f64)arg0->scaleX < 0.5)) {
        arg0->x = (f32)((f64)arg0->x - (10.0 * (f64)arg0->scaleX * (f64)func_80612794(parent->angle)));
        arg0->z = (f32)((f64)arg0->z - (10.0 * (f64)arg0->scaleX * (f64)func_80612790(parent->angle)));
    }
    memcpy((u8 *)arg0 + (D_807444FC << 6) + 0x128, arg0->matrix, 0x40);
    arg0->state = 2;
}
