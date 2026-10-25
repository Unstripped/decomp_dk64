// func_8071B89C (src/global/11BC10.c): MATCHED: non-constant f32 divisor local assigned 4.0f before clamp preserves target div.s.
#include "common.h"

typedef struct {
    u8 pad0[0x330];
    void *unk330;
    u8 pad334[4];
    void *unk338;
    u8 pad33C[4];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    s16 unk34C;
    u8 pad34E[2];
    u8 unk350;
    u8 pad351[0xB];
    s32 unk35C;
    f32 unk360;
    f32 unk364;
} Ub4bActorView;

void func_8071B89C(Ub4bActorView *arg0, s8 *arg1) {
    f32 temp_fv0;
    f32 divisor;
    s16 var_v0;

    divisor = 4.0f;
    var_v0 = *((s16 *)((u8 *)arg0 + 0x34E));
    if (var_v0 >= 5) {
        var_v0 = 4;
    }
    temp_fv0 = (f32)((f64)((f32)var_v0 / divisor) * 3.0);
    arg0->unk360 = temp_fv0;
    arg0->unk364 = temp_fv0;
}
