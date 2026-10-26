#include "common.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

Vec3f func_80612840(Vec3f a, Vec3f b) {
    Vec3f r;

    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}

Vec3f func_806128A8(Vec3f a, Vec3f b) {
    Vec3f r;

    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    return r;
}

Vec3f func_80612910(Vec3f a, f32 s) {
    Vec3f r;

    r.x = a.x * s;
    r.y = a.y * s;
    r.z = a.z * s;
    return r;
}

Vec3f func_80612970(Vec3f a) {
    Vec3f r;
    f32 length;

    length = sqrtf((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
    if (length != 0.0f) {
        r.x = a.x / length;
        r.y = a.y / length;
        r.z = a.z / length;
    }
    return r;
}
f32 func_80612A14(Vec3f a, Vec3f b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}


Vec3f func_80612A54(Vec3f a, Vec3f b) {
    Vec3f r;

    r.x = (a.y * b.z) - (a.z * b.y);
    r.y = (a.z * b.x) - (a.x * b.z);
    r.z = (a.x * b.y) - (a.y * b.x);
    return r;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/17540/func_80612AD8.s")



f32 func_80612B00(f32 arg0, s16 arg1) {
    f32 result;
    s16 i;

    result = 1.0f;
    if (arg1 != 0) {
        i = 0;
        if (arg1 > 0) {
            do {
                i++;
                result *= arg0;
            } while (i < arg1);
        }
    }
    return result;
}

f32 func_80612B48(s16 arg0) {
    s16 digits;

    digits = 0;
    if (arg0 != 0) {
        do {
            arg0 = (s16)(arg0 / 10);
            digits++;
        } while (arg0 != 0);
    }
    return (f32)(digits - 1);
}

f32 func_80612D10(f32);
f32 func_80612D1C(f32);

void func_80612BC0(f32 (*arg0)[4], f32 arg1) {
    f32 sine;
    f32 cosine;

    arg1 *= 0.01745329238f;
    sine = func_80612D1C(arg1);
    cosine = func_80612D10(arg1);
    guMtxIdentF(arg0);
    arg0[1][2] = sine;
    arg0[2][1] = -sine;
    arg0[1][1] = cosine;
    arg0[2][2] = cosine;
}
void func_80612C30(f32 (*arg0)[4], f32 arg1) {
    f32 sine;
    f32 cosine;

    arg1 *= 0.01745329238f;
    sine = func_80612D1C(arg1);
    cosine = func_80612D10(arg1);
    guMtxIdentF(arg0);
    arg0[2][0] = sine;
    arg0[0][2] = -sine;
    arg0[0][0] = cosine;
    arg0[2][2] = cosine;
}

void func_80612CA0(f32 (*arg0)[4], f32 arg1) {
    f32 sine;
    f32 cosine;

    arg1 *= 0.01745329238f;
    sine = func_80612D1C(arg1);
    cosine = func_80612D10(arg1);
    guMtxIdentF(arg0);
    arg0[0][1] = sine;
    arg0[1][0] = -sine;
    arg0[0][0] = cosine;
    arg0[1][1] = cosine;
}


