// func_8071B2EC (src/global/11BC10.c): stage 6: exact 0x15C body; direct 0x384 accesses reproduce target allocation path, stack frame, calls, and clamp, with only FP register allocation and rodata relocation remaining
#include "common.h"

typedef struct { u8 pad0[0xB8]; f32 unkB8; u8 padBC[0x32]; s16 unkEE; } Ub4ParentView;
typedef struct { f32 unk0; f32 unk4; } Ub4MotionView;
typedef struct {
    u8 pad0[0x330]; void *unk330; u8 pad334[4]; void *unk338; u8 pad33C[4];
    f32 unk340, unk344, unk348; u8 pad34C[0x38]; void *unk384;
} Ub4ActorView;
void *func_80610FE8(s32);
f32 func_80612790(s16);
f32 func_80612794(s16);

void func_8071B2EC(Ub4ActorView *arg0, s8 *arg1) {
    f32 speed;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(8);
        ((Ub4MotionView *)arg0->unk384)->unk0 = (f32)((Ub4ParentView *)arg0->unk338)->unkEE;
        ((Ub4MotionView *)arg0->unk384)->unk4 = ((Ub4ParentView *)arg0->unk338)->unkB8 + 30.0f;
    }
    speed = 0.35f;
    arg0->unk344 = (f32)((f64)arg0->unk344 + ((f64)speed * 0.5));
    speed = (f32)((f64)((Ub4MotionView *)arg0->unk384)->unk4 * 0.02);
    arg0->unk340 = (f32)(arg0->unk340 + (speed * func_80612794((s16)(s32)((Ub4MotionView *)arg0->unk384)->unk0)));
    arg0->unk348 = (f32)(arg0->unk348 + (speed * func_80612790((s16)(s32)((Ub4MotionView *)arg0->unk384)->unk0)));
    ((Ub4MotionView *)arg0->unk384)->unk4 -= 15.0f;
    if (((Ub4MotionView *)arg0->unk384)->unk4 < 0.0f) {
        ((Ub4MotionView *)arg0->unk384)->unk4 = 0.0f;
    }
}
