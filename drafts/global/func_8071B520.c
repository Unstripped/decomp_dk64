// func_8071B520 (src/global/11BC10.c): stage 3: control-flow and matrix tail reconstructed; closest diff is stack layout and signed-byte conversions in terrain branch
#include "common.h"

typedef struct { u8 pad0[0x32C]; u8 state; u8 pad32D[0x1F]; f32 x; f32 y; f32 z; s16 unk34C; s16 timer; u8 unk350; u8 unk351; u8 pad352[0xA]; s32 rotation; f32 scaleX; f32 scaleY; u8 pad368[5]; u8 brightness; } Ub4Actor;
s32 collisionCheckGroundAtPoint(f32, f32, f32 *);
extern u8 D_807444FC;

void func_8071B520(Ub4Actor *arg0, s8 *arg1) {
    f32 mtx0[4][4], mtx1[4][4], groundY, y, magnitude, a, b, c;
    s16 timer;
    u8 p, q;
    groundY = arg0->y;
    if (collisionCheckGroundAtPoint(arg0->x, arg0->z, &groundY) != 0) {
        y = arg0->y;
        magnitude = y < groundY ? groundY - y : -(groundY - y);
        if ((f64)magnitude > 10.0) goto update;
    } else {
update:
        p = arg0->unk351;
        timer = arg0->timer;
        a = (f32)p;
        if ((s32)p < 0) a += 4294967296.0f;
        q = arg0->unk350;
        b = (f32)q;
        if ((s32)q < 0) b += 4294967296.0f;
        if (timer >= 7) arg0->y = (f32)((f64)arg0->y - (0.3 * ((f64)(0xE - (s32)(20.0f - ((f32)timer + (a / b)))) / 14.0)));
    }
    if (arg0->timer == 0x10) arg0->unk350 = 0xA;
    guScaleF(mtx0, arg0->scaleX, arg0->scaleY, 0.0f);
    guRotateF(mtx1, (f32)((arg0->rotation * 0x168) / 4096), 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx0, mtx1, mtx0);
    guTranslateF(mtx1, arg0->x, arg0->y, arg0->z);
    guMtxCatF(mtx0, mtx1, mtx0);
    guMtxF2L(mtx0, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    if (arg0->timer >= 0x13) arg0->brightness -= 0x14;
    arg0->state = 3;
}
