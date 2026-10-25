// func_8071B44C (src/global/11BC10.c): stage 6: exact 0xD4 body; direct 0x384 accesses reproduce allocation path and all operations, with only post-call FP register allocation and rodata relocation remaining
#include "common.h"

typedef struct { u8 pad0[0xB8]; f32 unkB8; } Ub4ParentView;
typedef struct { f32 unk0; } Ub4MotionView;
typedef struct {
    u8 pad0[0x330]; void *unk330; u8 pad334[4]; void *unk338; u8 pad33C[4];
    f32 unk340, unk344, unk348; u8 pad34C[0x12]; s16 unk35E; u8 pad360[0x24]; void *unk384;
} Ub4ActorView;
void *func_80610FE8(s32);
f32 func_80612790(s16);
f32 func_80612794(s16);

void func_8071B44C(Ub4ActorView *arg0, s8 *arg1) {
    f32 speed;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(4);
        ((Ub4MotionView *)arg0->unk384)->unk0 = ((Ub4ParentView *)arg0->unk338)->unkB8;
    }
    speed = 0.35f;
    arg0->unk344 = (f32)((f64)arg0->unk344 + ((f64)speed * 0.5));
    speed = (f32)((f64)((Ub4MotionView *)arg0->unk384)->unk0 * 0.02);
    arg0->unk340 = (f32)(arg0->unk340 + (speed * func_80612794(arg0->unk35E)));
    arg0->unk348 = (f32)(arg0->unk348 + (speed * func_80612790(arg0->unk35E)));
}
