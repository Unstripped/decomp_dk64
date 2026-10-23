// func_806726DC (src/global/70FD0.c): Closest diff: all 4 call sites to func_806728F0 match byte-for-byte; only 16 bytes off in return delay slot / goto ret_0 consolidation
s16 func_806728F0(s16, s16, s16);

s32 func_806726DC(arg0, arg1, arg2, arg3, arg4, arg5)
s32 arg0;
s16 arg1;
s16 arg2;
s16 arg3;
s16 *arg4;
s16 arg5;
{
    s16 temp_t1;
    s16 temp_t0;
    s16 var_t2;
    s16 var_t3;
    u8 var_a0;

    temp_t1 = arg3 - arg5;
    temp_t0 = arg2 + arg5;
    var_t2 = temp_t0;
    var_t3 = temp_t1;
    if (arg3 >= arg2) {
        if (temp_t0 < temp_t1 && arg1 >= temp_t0 && temp_t1 >= arg1) {
            *arg4 = arg1;
            return 1;
        }
        *arg4 = func_806728F0(arg2, arg3, arg1);
        return 0;
    }

    var_a0 = 0;
    if (temp_t0 >= 0x1000) {
        var_t2 = temp_t0 - 0x1000;
        var_a0 = 1;
    }
    if (temp_t1 < 0) {
        var_t3 = temp_t1 + 0x1000;
        var_a0 += 2;
    }

    switch (var_a0) {
    case 0:
        if (arg1 >= var_t2 || var_t3 >= arg1) {
            *arg4 = arg1;
            return 1;
        }
        *arg4 = func_806728F0(arg2, arg3, arg1);
        return 0;
    case 1:
    case 2:
        if (var_t2 < var_t3 && arg1 >= var_t2 && var_t3 >= arg1) {
            *arg4 = arg1;
            return 1;
        }
        *arg4 = func_806728F0(arg2, arg3, arg1);
        return 0;
    case 3:
        *arg4 = func_806728F0(arg2, arg3, arg1);
        return 0;
    default:
        return 0;
    }
}
