// func_8071B758 (src/global/11BC10.c): stage 5: field offsets and light call are correct; closest diff is compiler temporary scheduling and frame size
#include "common.h"

typedef struct { u8 pad0[0x330]; void *parent; u8 pad334[0x1A]; s16 timer; u8 pad350[0x10]; f32 x; f32 y; f32 z; } Ub4Actor;
void lightAdd();

void func_8071B758(Ub4Actor *arg0, s8 *arg1) {
    f32 amount;
    s16 total = *((s16 *)((u8 *)arg0->parent + 0x16));
    s32 intensity;
    amount = (f32)(total - arg0->timer) / (f32)total;
    if ((f64)amount > 0.7) amount = 1.0f;
    intensity = (u32)((-155.0f * amount) + 255.0f) & 0xFF;
    lightAdd(arg0->x, arg0->y, arg0->z, 0, 0.0f, 0.0f, 50.0f, 0, intensity, intensity, intensity);
}
