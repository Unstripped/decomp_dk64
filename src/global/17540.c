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

void func_80612AD8(Vec3f *arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->x = arg1;
    arg0->y = arg2;
    arg0->z = arg3;
}
