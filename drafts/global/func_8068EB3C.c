// func_8068EB3C (src/global/936B0.c): distance comparison sub-expression ordering, diff in 254-2e0
typedef struct M93A_Vec3f {
    f32 x, y, z;
} M93A_Vec3f;

void func_8061F2B8(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *);

s32 func_8068EB3C(f32 arg0, f32 arg1, f32 arg2, M93A_Vec3f *arg3, M93A_Vec3f *arg4, M93A_Vec3f *arg5, M93A_Vec3f *arg6, f32 *arg7, f32 *arg8, f32 *arg9) {
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp40;
    f32 sp3C;
    f32 sp38;

    func_8061F2B8(arg0, arg1, arg2, arg3->x, arg3->y, arg3->z, arg4->x, arg4->y, arg4->z, &sp48, &sp4C, &sp50);
    func_8061F2B8(arg0, arg1, arg2, arg5->x, arg5->y, arg5->z, arg6->x, arg6->y, arg6->z, &sp54, &sp58, &sp5C);

    sp38 = arg0;
    sp40 = arg1;
    sp3C = sp48;

    if (((arg0 - sp48) * (arg0 - sp48) + (arg1 - sp4C) * (arg1 - sp4C) + (arg2 - sp50) * (arg2 - sp50)) <
        ((sp38 - sp54) * (sp38 - sp54) + (sp40 - sp58) * (sp40 - sp58) + (arg2 - sp5C) * (arg2 - sp5C))) {
        *arg7 = sp3C;
        *arg8 = sp4C;
        *arg9 = sp50;
        return 0;
    }
    *arg7 = sp54;
    *arg8 = sp58;
    *arg9 = sp5C;
    return 1;
}
