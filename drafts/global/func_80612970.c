// func_80612970 (src/global/17540.c): stage 2: m2c starter; remaining diff not yet reduced
void *func_80612970(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 temp_fv0;

    temp_fv0 = sqrtf((arg1 * arg1) + (arg2 * arg2) + (arg3 * arg3));
    if (temp_fv0 != 0.0f) {
        sp1C = arg1 / temp_fv0;
        sp20 = arg2 / temp_fv0;
        sp24 = arg3 / temp_fv0;
    }
    arg0->unk0 = (f32) sp1C.unk0;
    arg0->unk4 = (s32) sp1C.unk4;
    arg0->unk8 = (s32) sp1C.unk8;
    return arg0;
}
