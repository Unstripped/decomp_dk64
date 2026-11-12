#include "common.h"
#include "actor.h"
#include "proto/global/110F00.h"


void mtxScaleTranslateF(f32 mf[4][4], f32 sx, f32 sy, f32 sz, f32 x, f32 y, f32 z) {
    mtxIdentityF(mf);
    mf[0][0] = sx;
    mf[1][1] = sy;
    mf[2][2] = sz;
    mf[3][3] = 1.0f;
    mf[3][0] = x;
    mf[3][1] = y;
    mf[3][2] = z;
}

void mtxScaleTranslateL(Mtx *m, f32 sx, f32 sy, f32 sz, f32 x, f32 y, f32 z) {
    f32 mf[4][4];

    mtxScaleTranslateF(mf, sx, sy, sz, x, y, z);
    guMtxF2L(mf, m);
}

void mtxMulAffineAliasSafeF(f32 a[4][4], f32 b[4][4], f32 dst[4][4]) {
    f32 t00;
    f32 t01;
    f32 t02;
    f32 t10;
    f32 t11;
    f32 t12;
    f32 t20;
    f32 t21;
    f32 t22;
    f32 t30;
    f32 t31;
    f32 t32;
    t00 = (a[0][0] * b[0][0]) + (a[0][1] * b[1][0]) + (a[0][2] * b[2][0]);
    t01 = (a[0][0] * b[0][1]) + (a[0][1] * b[1][1]) + (a[0][2] * b[2][1]);
    t02 = (a[0][0] * b[0][2]) + (a[0][1] * b[1][2]) + (a[0][2] * b[2][2]);
    t10 = (a[1][0] * b[0][0]) + (a[1][1] * b[1][0]) + (a[1][2] * b[2][0]);
    t11 = (a[1][0] * b[0][1]) + (a[1][1] * b[1][1]) + (a[1][2] * b[2][1]);
    t12 = (a[1][0] * b[0][2]) + (a[1][1] * b[1][2]) + (a[1][2] * b[2][2]);
    t20 = (a[2][0] * b[0][0]) + (a[2][1] * b[1][0]) + (a[2][2] * b[2][0]);
    t21 = (a[2][0] * b[0][1]) + (a[2][1] * b[1][1]) + (a[2][2] * b[2][1]);
    t22 = (a[2][0] * b[0][2]) + (a[2][1] * b[1][2]) + (a[2][2] * b[2][2]);
    t30 = (a[3][0] * b[0][0]) + (a[3][1] * b[1][0]) + (a[3][2] * b[2][0]) + b[3][0];
    t31 = (a[3][0] * b[0][1]) + (a[3][1] * b[1][1]) + (a[3][2] * b[2][1]) + b[3][1];
    t32 = (a[3][0] * b[0][2]) + (a[3][1] * b[1][2]) + (a[3][2] * b[2][2]) + b[3][2];
    dst[0][0] = t00;
    dst[1][0] = t10;
    dst[2][0] = t20;
    dst[3][0] = t30;
    dst[0][1] = t01;
    dst[1][1] = t11;
    dst[2][1] = t21;
    dst[3][1] = t31;
    dst[0][2] = t02;
    dst[1][2] = t12;
    dst[2][2] = t22;
    dst[3][2] = t32;
    dst[0][3] = 0.0f;
    dst[1][3] = 0.0f;
    dst[2][3] = 0.0f;
    dst[3][3] = 1.0f;
}

void mtxMulAffineF(f32 a[4][4], f32 b[4][4], f32 dst[4][4]) {
    dst[0][0] = (a[0][0] * b[0][0]) + (a[0][1] * b[1][0]) + (a[0][2] * b[2][0]);
    dst[0][1] = (a[0][0] * b[0][1]) + (a[0][1] * b[1][1]) + (a[0][2] * b[2][1]);
    dst[0][2] = (a[0][0] * b[0][2]) + (a[0][1] * b[1][2]) + (a[0][2] * b[2][2]);
    dst[1][0] = (a[1][0] * b[0][0]) + (a[1][1] * b[1][0]) + (a[1][2] * b[2][0]);
    dst[1][1] = (a[1][0] * b[0][1]) + (a[1][1] * b[1][1]) + (a[1][2] * b[2][1]);
    dst[1][2] = (a[1][0] * b[0][2]) + (a[1][1] * b[1][2]) + (a[1][2] * b[2][2]);
    dst[2][0] = (a[2][0] * b[0][0]) + (a[2][1] * b[1][0]) + (a[2][2] * b[2][0]);
    dst[2][1] = (a[2][0] * b[0][1]) + (a[2][1] * b[1][1]) + (a[2][2] * b[2][1]);
    dst[2][2] = (a[2][0] * b[0][2]) + (a[2][1] * b[1][2]) + (a[2][2] * b[2][2]);
    dst[3][0] = (a[3][0] * b[0][0]) + (a[3][1] * b[1][0]) + (a[3][2] * b[2][0]) + b[3][0];
    dst[3][1] = (a[3][0] * b[0][1]) + (a[3][1] * b[1][1]) + (a[3][2] * b[2][1]) + b[3][1];
    dst[3][2] = (a[3][0] * b[0][2]) + (a[3][1] * b[1][2]) + (a[3][2] * b[2][2]) + b[3][2];
    dst[0][3] = 0.0f;
    dst[1][3] = 0.0f;
    dst[2][3] = 0.0f;
    dst[3][3] = 1.0f;
}

void mtxTransformPointF(f32 mf[4][4], f32 *px, f32 *py, f32 *pz) {
    f32 x = *px;
    f32 y = *py;
    f32 z = *pz;
    f32 ox = ((x * mf[0][0] + y * mf[1][0]) + z * mf[2][0]) + mf[3][0];
    f32 oy = ((x * mf[0][1] + y * mf[1][1]) + z * mf[2][1]) + mf[3][1];
    f32 oz = ((x * mf[0][2] + y * mf[1][2]) + z * mf[2][2]) + mf[3][2];
    *px = ox;
    *py = oy;
    *pz = oz;
}

void mtxRotateXRatioF(f32 mf[4][4], f32 y, f32 z, f32 dist) {
    f32 sin;
    f32 cos;

    mtxIdentityF(mf);
    sin = z / dist;
    cos = y / dist;
    mf[1][1] = cos;
    mf[1][2] = sin;
    mf[2][2] = cos;
    mf[2][1] = -sin;
}

void mtxRotateYRatioF(f32 mf[4][4], f32 z, f32 x, f32 dist) {
    f32 sin;
    f32 cos;

    sin = x / dist;
    cos = z / dist;
    if (x == 0.0) {
        sin = 0.0f;
    }
    if (z == 0.0) {
        cos = 0.0f;
    }
    mtxIdentityF(mf);
    mf[2][0] = sin;
    mf[0][2] = -sin;
    mf[0][0] = cos;
    mf[2][2] = cos;
}



void mtxRotateZRatioF(f32 mf[4][4], f32 x, f32 y, f32 dist) {
    f32 sin;
    f32 cos;

    mtxIdentityF(mf);
    sin = y / dist;
    cos = x / dist;
    mf[0][0] = cos;
    mf[0][1] = sin;
    mf[1][0] = -sin;
    mf[1][1] = cos;
}

void mtxRotateXRatioL(Mtx *m, f32 y, f32 z, f32 dist) {
    f32 mf[4][4];

    mtxRotateXRatioF(mf, y, z, dist);
    guMtxF2L(mf, m);
}

void mtxRotateYRatioL(Mtx *m, f32 z, f32 x, f32 dist) {
    f32 mf[4][4];

    mtxRotateYRatioF(mf, z, x, dist);
    guMtxF2L(mf, m);
}

void mtxRotateZRatioL(Mtx *m, f32 x, f32 y, f32 dist) {
    f32 mf[4][4];

    mtxRotateZRatioF(mf, x, y, dist);
    guMtxF2L(mf, m);
}

void mtxRotateXDegF(f32 mf[4][4], f32 angle) {
    f32 temp;
    f32 sin;
    f32 cos;

    temp = angle * 0.0174532925199432955;
    sin = sinApprox(temp);
    cos = cosApprox(temp);
    mtxIdentityF(mf);
    mf[1][2] = sin;
    mf[2][1] = -sin;
    mf[1][1] = cos;
    mf[2][2] = cos;
}

void mtxRotateYDegF(f32 mf[4][4], f32 angle) {
    f32 temp;
    f32 sin;
    f32 cos;

    temp = angle * 0.0174532925199432955;
    sin = sinApprox(temp);
    cos = cosApprox(temp);
    mtxIdentityF(mf);
    mf[2][0] = sin;
    mf[0][2] = -sin;
    mf[0][0] = cos;
    mf[2][2] = cos;
}

void mtxRotateZDegF(f32 mf[4][4], f32 angle) {
    f32 temp;
    f32 sin;
    f32 cos;

    temp = angle * 0.0174532925199432955;
    sin = sinApprox(temp);
    cos = cosApprox(temp);
    mtxIdentityF(mf);
    mf[0][1] = sin;
    mf[1][0] = -sin;
    mf[0][0] = cos;
    mf[1][1] = cos;
}

void mtxRotateXDegL(Mtx *m, f32 angle) {
    f32 mf[4][4];

    mtxRotateXDegF(mf, angle);
    guMtxF2L(mf, m);
}

void mtxRotateYDegL(Mtx *m, f32 angle) {
    f32 mf[4][4];

    mtxRotateYDegF(mf, angle);
    guMtxF2L(mf, m);
}

void mtxRotateZDegL(Mtx *m, f32 angle) {
    f32 mf[4][4];

    mtxRotateZDegF(mf, angle);
    guMtxF2L(mf, m);
}

void mtxIdentityF(f32 mf[4][4]) {
    f32 one;
    f32 zero;

    one = 1.0f;
    zero = 0.0f;
    if (one) {
    }
    mf[1][0] = zero;
    mf[2][0] = zero;
    mf[3][0] = zero;
    mf[0][1] = zero;
    mf[2][1] = zero;
    mf[3][1] = zero;
    mf[0][2] = zero;
    mf[1][2] = zero;
    mf[3][2] = zero;
    mf[0][3] = zero;
    mf[1][3] = zero;
    mf[2][3] = zero;
    mf[0][0] = one;
    mf[1][1] = one;
    mf[2][2] = one;
    mf[3][3] = one;
}

void mtxIdentityL(Mtx *m) {
    f32 mf[4][4];

    mtxIdentityF(mf);
    guMtxF2L(mf, m);
}

void mtxTranslateF(f32 mf[4][4], f32 x, f32 y, f32 z) {
    mtxIdentityF(mf);
    mf[3][0] = x;
    mf[3][1] = y;
    mf[3][2] = z;
}

void mtxTranslateL(Mtx *m, f32 x, f32 y, f32 z) {
    f32 mf[4][4];

    mtxTranslateF(mf, x, y, z);
    guMtxF2L(mf, m);
}

void mtxLookDirF(f32 view[4][4], f32 cam[4][4], f32 dx, f32 dy, f32 dz) {
    f32 pad[3];
    f32 t;
    f32 m00;
    f32 m10;
    f32 m20;
    f32 inv;
    f32 m11;
    f32 m21;
    f32 m02;
    f32 m12;
    f32 m22;

    if ((dx == 0.0f) && (dz == 0.0f)) {
        if (dy == 0.0f) {
            mtxIdentityF(view);
            mtxIdentityF(cam);
            return;
        }
        m00 = 1.0f;
        m10 = 0.0f;
        m20 = 0.0f;
        m11 = 0.0f;
        m21 = -1.0f;
        m02 = 0.0f;
        m12 = 1.0f;
        m22 = 0.0f;
    } else {
        inv = 1.0 / sqrtf((dx * dx) + (dy * dy) + (dz * dz));
        dx = dx * inv;
        dy = dy * inv;
        dz = dz * inv;
        m11 = sqrtf((dx * dx) + (dz * dz));
        inv = 1.0 / m11;
        t = -dx * inv;
        m00 = -dz * inv;
        m10 = dy * t;
        m21 = -dy;
        m02 = -t;
        m12 = dy * m00;
        m20 = -dx;
        m22 = -dz;
    }
    view[0][0] = m00;
    view[1][0] = m10;
    view[2][0] = m20;
    view[3][0] = 0.0f;
    view[0][1] = 0.0f;
    view[1][1] = m11;
    view[2][1] = m21;
    view[3][1] = 0.0f;
    view[0][2] = m02;
    view[1][2] = m12;
    view[2][2] = m22;
    view[3][2] = 0.0f;
    view[0][3] = 0.0f;
    view[1][3] = 0.0f;
    view[2][3] = 0.0f;
    view[3][3] = 1.0f;
    cam[0][0] = m00;
    cam[1][0] = 0.0f;
    cam[2][0] = m02;
    cam[3][0] = 0.0f;
    cam[0][1] = m10;
    cam[1][1] = m11;
    cam[2][1] = m12;
    cam[3][1] = 0.0f;
    cam[0][2] = m20;
    cam[1][2] = m21;
    cam[2][2] = m22;
    cam[3][2] = 0.0f;
    cam[0][3] = 0.0f;
    cam[1][3] = 0.0f;
    cam[2][3] = 0.0f;
    cam[3][3] = 1.0f;
}

void mtxLookDirL(Mtx *view, Mtx *cam, f32 dx, f32 dy, f32 dz) {
    f32 viewMf[4][4];
    f32 camMf[4][4];

    mtxLookDirF(viewMf, camMf, dx, dy, dz);
    guMtxF2L(viewMf, view);
    guMtxF2L(camMf, cam);
}

void mtxLookDirPosF(f32 view[4][4], f32 cam[4][4], f32 dx, f32 dy, f32 dz, f32 px, f32 py, f32 pz) {
    f32 pad[3];
    f32 t;
    f32 m00;
    f32 m10;
    f32 m20;
    f32 inv;
    f32 m11;
    f32 m21;
    f32 m02;
    f32 m12;
    f32 m22;

    if ((dx == 0.0f) && (dz == 0.0f)) {
        if (dy == 0.0f) {
            mtxIdentityF(view);
            mtxIdentityF(cam);
            return;
        }
        m00 = 1.0f;
        m10 = 0.0f;
        m20 = 0.0f;
        m11 = 0.0f;
        m21 = -1.0f;
        m02 = 0.0f;
        m12 = 1.0f;
        m22 = 0.0f;
    } else {
        inv = 1.0 / sqrtf((dx * dx) + (dy * dy) + (dz * dz));
        dx = dx * inv;
        dy = dy * inv;
        dz = dz * inv;
        m11 = sqrtf((dx * dx) + (dz * dz));
        inv = 1.0 / m11;
        t = -dx * inv;
        m00 = -dz * inv;
        m10 = dy * t;
        m21 = -dy;
        m02 = -t;
        m12 = dy * m00;
        m20 = -dx;
        m22 = -dz;
    }
    view[0][0] = m00;
    view[1][0] = m10;
    view[2][0] = m20;
    view[3][0] = -px;
    view[0][1] = 0.0f;
    view[1][1] = m11;
    view[2][1] = m21;
    view[0][2] = m02;
    view[3][1] = -py;
    view[1][2] = m12;
    t = -pz;
    view[2][2] = m22;
    view[0][3] = 0.0f;
    view[3][2] = t;
    view[3][3] = 1.0f;
    view[1][3] = 0.0f;
    view[2][3] = 0.0f;
    cam[0][0] = m00;
    cam[3][0] = (px * m00) + (pz * m02);
    cam[1][0] = 0.0f;
    cam[2][0] = m02;
    cam[0][1] = m10;
    cam[1][1] = m11;
    cam[2][1] = m12;
    cam[3][1] = (px * m10) + (py * m11) + (pz * m12);
    cam[0][2] = m20;
    cam[1][2] = m21;
    cam[2][2] = m22;
    cam[0][3] = 0.0f;
    cam[1][3] = 0.0f;
    cam[3][2] = (px * m20) + (py * m21) + (pz * m22);
    cam[3][3] = 1.0f;
    cam[2][3] = 0.0f;
}

void mtxLookDirPosL(Mtx *view, Mtx *cam, f32 dx, f32 dy, f32 dz, f32 px, f32 py, f32 pz) {
    f32 viewMf[4][4];
    f32 camMf[4][4];

    mtxLookDirPosF(viewMf, camMf, dx, dy, dz, px, py, pz);
    guMtxF2L(viewMf, view);
    guMtxF2L(camMf, cam);
}
