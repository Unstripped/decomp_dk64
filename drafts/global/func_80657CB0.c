// func_80657CB0 (src/global/55B20.c): stage 4: s64 negate + 4x __ll_to_f + div; call order A,B,C,D matches; remaining: frame 0x50 vs 0x38, arg reload ldcl/cvt.s.d vs lwc1
typedef struct R2P6aXform {
    /* 0x00 */ long long unk0;
    /* 0x08 */ long long unk8;
    /* 0x10 */ long long unk10;
    /* 0x18 */ long long unk18;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ u8 pad28[8];
} R2P6aXform;

extern R2P6aXform *D_807F6C24;

void func_80657CB0();

void func_80657CB0(arg0, arg1, arg2, arg3, arg4, arg5, arg6)
s32 arg0;
f32 arg1;
f32 arg2;
f32 arg3;
f32 *arg4;
f32 *arg5;
f32 *arg6;
{
    f32 a;
    f32 t;

    a = (f32)(-D_807F6C24[arg0].unk18);
    t = (a - ((f32)D_807F6C24[arg0].unk10 * arg3 + ((f32)D_807F6C24[arg0].unk0 * arg1 + (f32)D_807F6C24[arg0].unk8 * arg2))) / D_807F6C24[arg0].unk24;
    *arg4 = (f32)D_807F6C24[arg0].unk0 * t + arg1;
    *arg5 = (f32)D_807F6C24[arg0].unk8 * t + arg2;
    *arg6 = (f32)D_807F6C24[arg0].unk10 * t + arg3;
}
