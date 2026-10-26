// func_80612A54 (src/global/17540.c): stage 2: m2c starter; remaining diff not yet reduced
void *func_80612A54(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 spC;
    f32 sp8;
    f32 sp4;

    sp4 = (arg2 * arg6) - (arg3 * arg5);
    sp8 = (arg3 * arg4) - (arg1 * arg6);
    spC = (arg1 * arg5) - (arg2 * arg4);
    arg0->unk0 = (f32) sp4.unk0;
    arg0->unk4 = (s32) sp4.unk4;
    arg0->unk8 = (s32) sp4.unk8;
    return arg0;
}
