// func_80666FC8 (src/global/699B0.c): branch structure for cond0/cond1 and diff comparison
s32 func_80666FC8(f32 arg0, f32 arg1, f32 arg2, u8 arg3) {
    f32 var_fv0;
    f32 diff0;
    f32 diff1;
    s32 cond0;
    s32 cond1;

    var_fv0 = (arg3 == 1) ? 60.0 : 10.0;

    if (arg0 <= arg2) {
        cond0 = 1;
    } else {
        cond0 = 0;
        if ((arg0 - arg2) < var_fv0) {
            cond0 = 1;
        }
    }

    if (arg1 <= arg2) {
        cond1 = 1;
    } else {
        cond1 = 0;
        if ((arg1 - arg2) < var_fv0) {
            cond1 = 1;
        }
    }

    if (!cond0 && !cond1) {
        return 0;
    }
    if (!cond1) {
        return 0;
    }
    if (!cond0) {
        return 1;
    }

    if (arg2 < arg0) {
        diff0 = arg0 - arg2;
    } else {
        diff0 = arg2 - arg0;
    }

    if (arg2 < arg1) {
        diff1 = arg1 - arg2;
    } else {
        diff1 = arg2 - arg1;
    }

    if (diff0 < diff1) {
        return 0;
    }
    return 1;
}
