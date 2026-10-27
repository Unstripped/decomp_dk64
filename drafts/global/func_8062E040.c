// func_8062E040 (src/global/2F550.c): Stage 4. Instruction stream and frame 0x60 identical; only stack offsets differ: sp3C/sp38 at 0x40/0x3C vs target 0x3C/0x38, sp58 0x50 vs 0x58 (declared f32 sp58,sp3C,sp38,sp30,temp_fs1,temp_fs2,var_fs0; named locals needed for the store/reload pairs).
f32 func_8062E040(s16, s16, s16, s16, s16, s16, f32, f32, f32);

f32 func_8062E040(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, f32 arg6, f32 arg7, f32 arg8) {
    f32 sp58;
    f32 sp3C;
    f32 sp38;
    f32 sp30;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 var_fs0;

    sp3C = (((f32)arg0 - arg6) * ((f32)arg0 - arg6));
    sp38 = (((f32)arg1 - arg7) * ((f32)arg1 - arg7));
    temp_fs1 = (((f32)arg2 - arg8) * ((f32)arg2 - arg8));
    temp_fs2 = (((f32)arg5 - arg8) * ((f32)arg5 - arg8));
    var_fs0 = (sp3C + sp38) + temp_fs1;
    sp30 = ((sp3C + sp38) + temp_fs2);
    sp58 = sp30;
    if (sp30 < var_fs0) {
        var_fs0 = sp30;
    }
    if ((sp3C + (((f32)arg4 - arg7) * ((f32)arg4 - arg7))) + temp_fs1 < var_fs0) {
        var_fs0 = (sp3C + (((f32)arg4 - arg7) * ((f32)arg4 - arg7))) + temp_fs1;
    }
    if ((sp3C + (((f32)arg4 - arg7) * ((f32)arg4 - arg7))) + temp_fs2 < var_fs0) {
        var_fs0 = (sp3C + (((f32)arg4 - arg7) * ((f32)arg4 - arg7))) + temp_fs2;
    }
    if (((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + sp38) + temp_fs1 < var_fs0) {
        var_fs0 = ((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + sp38) + temp_fs1;
    }
    if (((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + sp38) + temp_fs2 < var_fs0) {
        var_fs0 = ((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + sp38) + temp_fs2;
    }
    if (((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + (((f32)arg4 - arg7) * ((f32)arg4 - arg7))) + temp_fs1 < var_fs0) {
        var_fs0 = ((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + (((f32)arg4 - arg7) * ((f32)arg4 - arg7))) + temp_fs1;
    }
    if (((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + (((f32)arg4 - arg7) * ((f32)arg4 - arg7))) + temp_fs2 < var_fs0) {
        var_fs0 = ((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + (((f32)arg4 - arg7) * ((f32)arg4 - arg7))) + temp_fs2;
    }
    return sqrtf(var_fs0);
}
