// func_80612A14 (src/global/17540.c): stage 2: raw integer float arguments; remaining spill/register ordering
f32 func_80612A14(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    return (*(f32 *)&arg0 * *(f32 *)&arg3) + (*(f32 *)&arg1 * *(f32 *)&arg4) + (*(f32 *)&arg2 * *(f32 *)&arg5);
}
