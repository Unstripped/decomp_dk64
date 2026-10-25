// func_8070B324 (src/global/10E1D0.c): Stage 1: volume-scale transition with thread-priority guard and null-terminated channel iteration. Compiles; IDO temporary/register allocation remains unmatched.
extern s8 D_8074583C;
extern s32 D_807550A4;

void func_80737B58(s32, s32);
void seqSetChannelVolumeScale(s32, f32);

void func_8070B324(f32 arg0, s32 arg1, s32 *arg2) {
    s32 sp34;
    s32 sp28;
    s32 *var_s0;
    s32 temp_s0;
    s32 temp_t7;
    s32 var_a0;

    temp_t7 = (u32)(25000.0f * arg0) & 0xFFFF;
    temp_s0 = (u32)((f64)(temp_t7 * D_8074583C) / 40.0) & 0xFFFF;
    sp28 = temp_t7;
    sp34 = osGetThreadPri(NULL);
    osSetThreadPri(NULL, 0x1A);
    func_80737B58(0, temp_s0 & 0xFFFF);
    if (arg1 != 0) {
        D_807550A4 = 1;
        func_80737B58(2, temp_s0 & 0xFFFF);
        if ((D_80755070 == 0) && ((D_8076A0B1 & 1) || !(D_8076A0B1 & 0x40))) {
            seqSetChannelVolumeScale(0, arg0);
        }
    } else {
        func_80737B58(3, (u32)((f64)(sp28 * D_8074583C) / 40.0) & 0xFFFF);
        if (D_807550A4 != 0) {
            D_807550A4 = 0;
            func_80737B58(2, (u32)((f64)(D_8074583C * 0x61A8) / 40.0) & 0xFFFF);
            func_80737B58(1, (u32)((f64)(D_8074583C * 0x61A8) / 40.0) & 0xFFFF);
        }
    }
    if (arg2 != NULL) {
        var_s0 = arg2;
        if (*arg2 != 0) {
            var_a0 = *var_s0;
loop:
            seqSetChannelVolumeScale(var_a0, arg0);
            var_s0 += 1;
            if (arg2 != NULL) {
                var_a0 = *var_s0;
                if (var_a0 != 0) {
                    goto loop;
                }
            }
        }
    }
    osSetThreadPri(NULL, sp34);
}
