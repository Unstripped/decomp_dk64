// func_80672134 (src/global/70FD0.c): Exact size 127 insns, 0x20 frame; K&R spills match; minor branch condition and temp regalloc diffs in angle diff abs
s16 func_80672A70();

s16 func_80672134(arg0, arg1, arg2, arg3)
s16 arg0;
s16 arg1;
s16 arg2;
s16 arg3;
{
    s16 var_a3;
    f32 var_fv1;
    s16 bisect;
    s16 diff1;
    s16 diff2;

    if (arg1 >= arg0) {
        if (arg2 >= arg0 && arg1 >= arg2) {
            return 0x270F;
        }
    } else if (arg2 >= arg0 || arg1 >= arg2) {
        return 0x270F;
    }

    var_a3 = arg2 + 0x800;
    if (var_a3 >= 0x1000) {
        var_a3 -= 0x1000;
    }

    bisect = func_80672A70(arg0, arg1);
    diff1 = arg0 - bisect;
    if (diff1 <= 0) {
        diff1 = -diff1;
    }
    if (diff1 >= 0x800) {
        diff1 = 0xFFF - diff1;
    }

    diff2 = var_a3 - bisect;
    if (diff2 <= 0) {
        diff2 = -diff2;
    }
    if (diff2 >= 0x800) {
        diff2 = 0xFFF - diff2;
    }

    if (diff1 != 0) {
        var_fv1 = (f32)diff2 / (f32)diff1;
    } else {
        var_fv1 = 0.0f;
    }

    if (var_fv1 > 1.0) {
        var_fv1 = 1.0f;
    }
    if (var_fv1 < 0.2) {
        var_fv1 = 0.0f;
    }
    return (s16)(s32)((f32)arg3 * var_fv1);
}
