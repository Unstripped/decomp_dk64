// func_80603340 (src/global/7130.c): Stage 5, body and floats matched, prologue arg2/arg3 spill ordering diff
typedef signed short s16;
typedef signed int s32;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;
typedef signed char s8;
typedef float f32;
typedef double f64;

f32 func_80602E6C(s32, s32, u16, u8, u8, f32);
extern f32 D_80770DDC;
extern f32 D_80770DE0;
extern f32 D_80770DE8;
extern f32 D_80770DEC;
extern f32 D_80770DF0;
extern f32 D_80770DF4;

f32 func_80603340(s32 arg0, s32 arg1, u16 arg2, u8 arg3, u8 arg4, f32 arg5)
{
    f32 ret;
    f32 temp;

    ret = func_80602E6C(arg0, arg1, arg2, arg3, arg4, arg5);
    if (ret < 10.0f) {
        return 0.0f;
    }

    temp = (f32)((f64)D_80770DDC * 0.00787401574803149595);
    D_80770DE8 += ret * temp;
    D_80770DEC += ret * (1.0f - temp);

    if (D_80770DE0 > 0.0f) {
        D_80770DF0 += ret * D_80770DE0;
    }
    if (D_80770DE0 < 0.0f) {
        D_80770DF4 -= ret * D_80770DE0;
    }

    return ret;
}
