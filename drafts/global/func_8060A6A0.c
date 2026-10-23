// func_8060A6A0 (src/global/7130.c): Stage 5, blocked on alCSPSetChlPan prototype mismatch (jal vs jalr)
#include "common.h"

extern u8 D_8077058E;
extern u8 D_80770560[];
extern u16 D_80745658[];
extern ALCSPlayer *gSeqPlayers[];
void func_8060A1B0(s32, u8, f32);
void func_806049CC(s32);

void func_8060A6A0(s32 arg0, u8 arg1, f32 arg2) {
    f64 var_fv0;
    f32 pan, vol;

    func_8060A1B0(arg0, arg1, arg2);
    var_fv0 = (f64)(u32)D_8077058E;
    pan = (var_fv0 * 0.3) / 255.0;
    vol = ((var_fv0 * 0.35) / 255.0) + 1.0;
    if (arg0 != 0) {
        if (D_80745658[D_80770560[arg0]] & 1) {
            ((void (*)(ALCSPlayer *, f32, f32))alCSPSetChlPan)(gSeqPlayers[arg0], pan, vol);
        } else {
            ((void (*)(ALCSPlayer *, f32, f32))alCSPSetChlPan)(gSeqPlayers[arg0], 0.0f, 1.0f);
        }
    }
    func_806049CC(arg0);
}
