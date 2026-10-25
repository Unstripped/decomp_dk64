// func_8071B89C (src/global/11BC10.c): stage 6: only remaining target/current difference is div.s by 4.0 versus IDO folding to multiply by 0.25
#include "common.h"

typedef struct {
    u8 pad0[0x34E];
    s16 unk34E;
    u8 pad350[0x10];
    f32 unk360;
    f32 unk364;
} Ub4ActorView;

void func_8071B89C(Ub4ActorView *arg0, s8 *arg1) {
    f32 temp_fv0;
    f32 temp_fv1;
    s16 var_v0;

    var_v0 = arg0->unk34E;
    if (var_v0 >= 5) {
        var_v0 = 4;
    }
    temp_fv1 = 4.0f;
    temp_fv0 = (f32)((f64)((f32)var_v0 / temp_fv1) * 3.0);
    arg0->unk360 = temp_fv0;
    arg0->unk364 = temp_fv0;
}
