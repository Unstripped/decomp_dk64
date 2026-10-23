// func_80602E6C (src/global/7130.c): Stage 3, 3D audio listener calculation with mathAngleBetweenPointsRad, sqrtf, D_807FC924 listener position and orientation
typedef signed short s16;
typedef signed int s32;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;
typedef signed char s8;
typedef float f32;
typedef double f64;

typedef struct {
    char pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    char pad21C[0xC];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
    char pad234[0x90];
    f32 unk2C4;
} AudPlayerPos;

extern f32 D_80770DDC;
extern f32 D_80770DE0;
extern f32 D_80770DE4;
extern AudPlayerPos *D_807FC924;

f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
f32 func_80612D10(f32, f32);
f32 func_80612D1C(f32);
f32 sqrtf(f32);

f32 func_80602E6C(f32 arg0, f32 arg1, f32 arg2, u8 arg3, u8 arg4, f32 arg5) {
    f32 sp2C;
    f32 sp24;
    f32 sp20;
    f32 sp18;
    f32 dy;
    f64 diff;

    sp18 = 0.0f;
    sp2C = D_807FC924->unk210 - arg0;
    dy = D_807FC924->unk214 - arg1;
    sp24 = D_807FC924->unk218 - arg2;

    diff = (f64)arg5 - 0.8;
    if (diff < 0.0) {
        diff = -diff;
    }

    if (diff < 0.1 && dy < 0.0f) {
        dy *= 20.0f;
    }

    D_80770DE4 = sqrtf((sp2C * sp2C) + (dy * dy) + (sp24 * sp24));

    if ((f64)arg5 >= 0.8) {
        f32 l_dz = D_807FC924->unk230 - D_807FC924->unk218;
        f32 l_dx = D_807FC924->unk228 - D_807FC924->unk210;
        sp18 = mathAngleBetweenPointsRad(D_807FC924->unk214, 0.0f, D_807FC924->unk22C, sqrtf((l_dz * l_dz) + (l_dx * l_dx)));

        l_dz = arg2 - D_807FC924->unk218;
        l_dx = arg0 - D_807FC924->unk210;
        D_80770DDC = mathAngleBetweenPointsRad(D_807FC924->unk214, 0.0f, arg1, sqrtf((l_dz * l_dz) + (l_dx * l_dx))) - sp18;

        if (D_80770DDC < 0.0f) {
            D_80770DDC += 6.2831855f;
        }

        if (D_80770DDC > 0.3926991f && (f64)D_80770DDC < 5.890486389398575) {
            D_80770DE4 *= 1.0f - (func_80612D1C((f32)(((f64)D_80770DDC * 4.0 / 7.0) + 2.942101601958275)) * 4.0f);
        }
    }

    D_80770DDC = mathAngleBetweenPointsRad(D_807FC924->unk210, D_807FC924->unk218, arg0, arg2) - D_807FC924->unk2C4;
    if (D_80770DDC < 0.0f) {
        D_80770DDC += 6.2831855f;
    }

    if (D_80770DDC > 0.7853982f && (f64)D_80770DDC < 5.497787296772003 && (f64)sp18 < 4.0) {
        D_80770DE4 *= 1.0f - (func_80612D1C((f32)(((2.0 * (f64)D_80770DDC) / 3.0) + 2.617993950843811)) * arg5);
    }

    if (D_80770DE4 < 1.0f) {
        D_80770DE4 = 1.0f;
    }

    {
        f32 dist = (f32)(arg4 * 0xFA0);
        f64 temp = ((f64)(dist / sqrtf(D_80770DE4))) - (((f64)dist * 0.12909946) - 32767.0);
        f64 a3_f64 = (f64)arg3;
        sp20 = (f32)(temp * a3_f64 * 0.00392156862745098);
    }

    if (sp20 < 10.0f) {
        return 0.0f;
    }

    D_80770DE0 = func_80612D10(D_80770DDC, D_80770DE4);
    D_80770DDC = (f32)((f64)(1.0f - func_80612D1C(D_80770DDC)) * 63.5);

    if (sp20 < 10.0f) {
        return 0.0f;
    }

    if (sp20 > 32767.0f) {
        sp20 = 32767.0f;
    }

    return sp20;
}
