// func_80612A54 (src/global/17540.c): stage 2: raw integer float arguments; remaining operand ordering
typedef struct { f32 x; f32 y; f32 z; } P17b4Vec3;
P17b4Vec3 *func_80612A54(P17b4Vec3 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    P17b4Vec3 temp;
    temp.x = (*(f32 *)&arg2 * *(f32 *)&arg6) - (*(f32 *)&arg3 * *(f32 *)&arg5);
    temp.y = (*(f32 *)&arg3 * *(f32 *)&arg4) - (*(f32 *)&arg1 * *(f32 *)&arg6);
    temp.z = (*(f32 *)&arg1 * *(f32 *)&arg5) - (*(f32 *)&arg2 * *(f32 *)&arg4);
    *arg0 = temp;
    return arg0;
}
