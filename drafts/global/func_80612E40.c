// func_80612E40 (src/global/17B40.c): stage 4: exact instruction sequence; remaining v0/v1 allocation swap after mfc1. Tried declaration order, increment form, and reversed temporary roles.
f32 func_80612E40(f32 arg0) {
    s32 temp_ft0;
    s32 var_v0;

    temp_ft0 = (s32) arg0;
    var_v0 = temp_ft0;
    if ((arg0 - (f32) temp_ft0) > 0.00001f) {
        var_v0 = temp_ft0 + 1;
    }
    return (f32) var_v0;
}
