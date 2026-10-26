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

#pragma GLOBAL_ASM("asm/global/nonmatchings/17540/func_80612970.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17540/func_80612A14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17540/func_80612A54.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/17540/func_80612B48.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17540/func_80612BC0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17540/func_80612C30.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17540/func_80612CA0.s")
