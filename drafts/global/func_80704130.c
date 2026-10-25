// func_80704130 (src/global/103AB0.c): stage 6 direct u8-to-f64 expression matches target instruction count and conversion blocks; remaining differences are register allocation and late-rodata relocation labels
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6[2];
    s16 unk8;
    s16 unkA;
    s8 unkC;
    s8 unkD;
    s8 unkE;
    u8 unkF;
} R1F103AB0cTransformView;

f32 func_80612794(s16);

void func_80704130(R1F103AB0cTransformView *arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5) {
    arg0->unkC = arg1;
    arg0->unkD = arg2;
    arg0->unkE = arg3;
    arg0->unkF = arg4;
    if (arg5 & 0x10) {
        if (arg5 & 0x40) {
            arg0->unk2 = (s16)(s32)((f32)arg0->unk2
                + (64.0f * func_80612794((s16)(s32)(((f64)arg4 * 12.05) + 1024.0))));
        } else {
            arg0->unk2 = (s16)(s32)((f32)arg0->unk2
                - (64.0f * func_80612794((s16)(s32)(((f64)arg4 * 12.05) + 1024.0))));
        }
    }
}
