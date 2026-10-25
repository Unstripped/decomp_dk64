// func_8070C200 (src/global/110F00.c): stage 1: roundf emits a libcall; (s32)(x + 0.5f) emits add plus trunc, not round.w.s
s32 func_8070C200(f32 arg0) {
    return (s32) roundf(arg0);
}
