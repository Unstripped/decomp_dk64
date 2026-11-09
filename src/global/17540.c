#include "common.h"
#include "proto/global/17540.h"

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

Vec3f vec3fSub(Vec3f a, Vec3f b) {
    Vec3f r;

    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}

Vec3f vec3fAdd(Vec3f a, Vec3f b) {
    Vec3f r;

    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    return r;
}

Vec3f vec3fScale(Vec3f a, f32 s) {
    Vec3f r;

    r.x = a.x * s;
    r.y = a.y * s;
    r.z = a.z * s;
    return r;
}

Vec3f vec3fNormalize(Vec3f a) {
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

f32 vec3fDot(Vec3f a, Vec3f b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vec3f vec3fCross(Vec3f a, Vec3f b) {
    Vec3f r;

    r.x = (a.y * b.z) - (a.z * b.y);
    r.y = (a.z * b.x) - (a.x * b.z);
    r.z = (a.x * b.y) - (a.y * b.x);
    return r;
}

void vec3fSet(Vec3f *v, f32 x, f32 y, f32 z) {
    v->x = x;
    v->y = y;
    v->z = z;
}
