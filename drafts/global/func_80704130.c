// func_80704130 (src/global/103AB0.c): stage 4 behavioral transform draft; compiled and fdiffed, 16-byte longer from f64 conversion shape
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
} R1F103AB0cView;

f32 func_80612794(s16);

void func_80704130(R1F103AB0cView *arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5) {
    f64 var_ft1;
    f64 var_ft4;
    s32 temp;

    arg0->unkC = arg1;
    arg0->unkD = arg2;
    arg0->unkE = arg3;
    arg0->unkF = arg4;
    if (arg5 & 0x10) {
        if (arg5 & 0x40) {
            temp = arg4;
            var_ft1 = (f64) temp;
            if (temp < 0) {
                var_ft1 += 4294967296.0;
            }
            arg0->unk2 = (s16) (s32) ((f32) arg0->unk2 + (64.0f * func_80612794((s16) (s32) ((var_ft1 * 12.05) + 1024.0))));
            return;
        }
        temp = arg4;
        var_ft4 = (f64) temp;
        if (temp < 0) {
            var_ft4 += 4294967296.0;
        }
        arg0->unk2 = (s16) (s32) ((f32) arg0->unk2 - (64.0f * func_80612794((s16) (s32) ((var_ft4 * 12.05) + 1024.0))));
    }
}
