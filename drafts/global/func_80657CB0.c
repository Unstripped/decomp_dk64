// func_80657CB0 (src/global/55B20.c): stage 6: everything matches except the 'a' slot (ours home 0x34 vs target temp 0x24) and temps (0x24/0x28 vs 0x28/0x2C); must be a PROTOTYPED f32 definition (K&R promotes float params to double: ldc1+cvt.s.d, frame 0x50)
typedef struct R3bXform {
    /* 0x00 */ s64 unk0;
    /* 0x08 */ s64 unk8;
    /* 0x10 */ s64 unk10;
    /* 0x18 */ s64 unk18;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ u8 pad28[8];
} R3bXform;

#define R3bX ((R3bXform *)D_807F6C24)

void func_80657CB0(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
    f32 t;
    f32 a = (f32)(-R3bX[arg0].unk18);

    t = (a - ((f32)R3bX[arg0].unk10 * arg3 + ((f32)R3bX[arg0].unk0 * arg1 + (f32)R3bX[arg0].unk8 * arg2))) / R3bX[arg0].unk24;
    *arg4 = (f32)R3bX[arg0].unk0 * t + arg1;
    *arg5 = (f32)R3bX[arg0].unk8 * t + arg2;
    *arg6 = (f32)R3bX[arg0].unk10 * t + arg3;
}
