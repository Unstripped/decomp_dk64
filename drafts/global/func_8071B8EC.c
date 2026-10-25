// func_8071B8EC (src/global/11BC10.c): stage 3: m2c-derived state, random, and effect path reconstructed; not retained in final private copy
#include "common.h"

typedef struct { u8 pad0[0x340]; f32 x; f32 y; f32 z; u8 pad34C[8]; s32 count; s32 previousCount; u8 pad35C[0x11]; u8 brightness; } Ub4Actor;
void func_806086CC();
void func_80714998(s32);
void func_8071498C(void *);
void func_80714950(s32);
void func_807149B8(s32);
void func_807149C8();
void func_80714CC0(s32, f32, f32, f32, f32);
s32 func_80611A44(void);
void func_80717D4C(void);
extern u8 D_8071FFA0;

void func_8071B8EC(Ub4Actor *arg0, s8 *arg1) {
    s32 random;
    s16 timer;
    if (arg0->previousCount == 0) {
        if (arg0->brightness < 0xE1) arg0->brightness += 0x1E;
        else arg0->brightness = 0xFF;
    }
    timer = *((s16 *)((u8 *)arg0 + 0x34E));
    if ((timer == 3) || (timer == 0x11) || (timer == 0x15)) func_806086CC(arg0->x, arg0->y, arg0->z, 0x14F, 0xFF, 0x7F, 0x1E, 0x4B, 0.3f, 0);
    if ((arg0->count - arg0->previousCount) < 3) {
        if (arg0->brightness >= 0xB) arg0->brightness -= 0xA;
        else *arg1 = 1;
        return;
    }
    if (((func_80611A44() >> 15) % 100) >= 0x5B) {
        func_80714998(3);
        func_8071498C(&func_80717D4C);
        func_80714950(-0xA);
        func_807149B8(1);
        func_807149C8(0x9B, 0x9B, 0x9B, 0x96);
        random = func_80611A44();
        func_80714CC0((s32)&D_8071FFA0, 0.8f, (f32)(((func_80611A44() >> 15) % 65535) & 7) + arg0->x, arg0->y + 10.0f, (f32)(((random >> 15) % 65535) & 7) + arg0->z);
    }
}
