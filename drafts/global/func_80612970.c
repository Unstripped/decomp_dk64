// func_80612970 (src/global/17540.c): stage 3: raw integer float arguments; remaining register spills and operand ordering
typedef struct { f32 x; f32 y; f32 z; } P17b4Vec3;
P17b4Vec3 *func_80612970(P17b4Vec3 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    P17b4Vec3 temp;
    f32 length;
    length = sqrtf((*(f32 *)&arg1 * *(f32 *)&arg1) + (*(f32 *)&arg2 * *(f32 *)&arg2) + (*(f32 *)&arg3 * *(f32 *)&arg3));
    if (length != 0.0f) {
        temp.x = *(f32 *)&arg1 / length;
        temp.y = *(f32 *)&arg2 / length;
        temp.z = *(f32 *)&arg3 / length;
    }
    *arg0 = temp;
    return arg0;
}
