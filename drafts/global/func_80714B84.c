// func_80714B84 (src/global/119370.c): Stage 1 m2c-derived draft; not compiled to a match.
? func_806335B0(s32, ?, s32, s32 *, s32 *, f32 *);  /* extern */
? func_80714D08(s32, s32, s32, s32, f32, s32, s32, s32, s32); /* extern */

void func_80714B84(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    s32 sp3C;
    s32 sp38;
    f32 sp34;

    func_806335B0(arg2, 1, arg3, &sp3C, &sp38, &sp34);
    func_80714D08(arg0, arg1, sp3C, sp38, sp34, 0, arg2, arg3, (s32) arg4);
}
