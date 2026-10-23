// func_80672328 (src/global/70FD0.c): Exact 163 insns, frame 0x50, all branches/calls/return logic match; sp44/sp40 stack slot order diff (0x44/0x40 vs 0x4c/0x48)
typedef struct M70O_Actor {
    u8 pad0[0x88];
    f32 unk88;
    u8 pad8C[4];
    f32 unk90;
} M70O_Actor;

s32 func_80611E60(s32);
s32 func_806725A0();

s32 func_80672328(struct M70F_Actor *arg0, f32 arg1, f32 arg2) {
    s32 sp44;
    s32 sp40;
    f32 sp34;
    s16 var_a2;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;

    sp44 = (s32)(((M70O_Actor *)arg0)->unk88 * 8.0f);
    sp40 = (s32)(((M70O_Actor *)arg0)->unk90 * 8.0f);
    sp28 = (s32)(arg1 * 8.0f);
    sp24 = (s32)(arg2 * 8.0f);
    sp20 = sp28 - sp44;
    sp1C = sp24 - sp40;
    sp34 = sqrtf((f32)((sp20 * sp20) + (sp1C * sp1C)));
    if ((f64)sp34 == 0.0) {
        return 1;
    }
    if (sp20 >= 0 && sp1C >= 0) {
        var_a2 = (s16)(func_80611E60((s32)(((f64)sp20 * 65535.9) / (f64)sp34)) >> 4);
    }
    if (sp20 >= 0 && sp1C < 0) {
        var_a2 = (func_80611E60((s32)(((f64)(sp40 - sp24) * 65535.9) / (f64)sp34)) >> 4) + 0x400;
    }
    if (sp20 < 0 && sp1C < 0) {
        var_a2 = (func_80611E60((s32)(((f64)(sp44 - sp28) * 65535.9) / (f64)sp34)) >> 4) + 0x800;
    }
    if (sp20 < 0 && sp1C >= 0) {
        var_a2 = (func_80611E60((s32)(((f64)sp1C * 65535.9) / (f64)sp34)) >> 4) + 0xC00;
    }
    if (func_806725A0(arg0, var_a2)) {
        return 1;
    } else {
        return 0;
    }
}
