#include "common.h"
#include "actor.h"

typedef struct Mat4F {
    f32 m[4][4];
} Mat4F;

void mtxIdentityF();
void mtxLookDirF(Mat4F *view, Mat4F *cam, f32 dx, f32 dy, f32 dz);
void mtxLookDirPosF(Mat4F *view, Mat4F *cam, f32 dx, f32 dy, f32 dz, f32 px, f32 py, f32 pz);

void mtxScaleTranslateF(Mat4F *mf, f32 sx, f32 sy, f32 sz, f32 x, f32 y, f32 z) {
    mtxIdentityF(mf);
    mf->m[0][0] = sx;
    mf->m[1][1] = sy;
    mf->m[2][2] = sz;
    mf->m[3][3] = 1.0f;
    mf->m[3][0] = x;
    mf->m[3][1] = y;
    mf->m[3][2] = z;
}

void mtxScaleTranslateL(Mtx *m, f32 sx, f32 sy, f32 sz, f32 x, f32 y, f32 z) {
    Mat4F mf;

    mtxScaleTranslateF(&mf, sx, sy, sz, x, y, z);
    guMtxF2L(mf.m, m);
}

void mtxMulAffineAliasSafeF(Mat4F *a, Mat4F *b, Mat4F *dst) {
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
    t00 = (a->m[0][0] * b->m[0][0]) + (a->m[0][1] * b->m[1][0]) + (a->m[0][2] * b->m[2][0]);
    t01 = (a->m[0][0] * b->m[0][1]) + (a->m[0][1] * b->m[1][1]) + (a->m[0][2] * b->m[2][1]);
    t02 = (a->m[0][0] * b->m[0][2]) + (a->m[0][1] * b->m[1][2]) + (a->m[0][2] * b->m[2][2]);
    t10 = (a->m[1][0] * b->m[0][0]) + (a->m[1][1] * b->m[1][0]) + (a->m[1][2] * b->m[2][0]);
    t11 = (a->m[1][0] * b->m[0][1]) + (a->m[1][1] * b->m[1][1]) + (a->m[1][2] * b->m[2][1]);
    t12 = (a->m[1][0] * b->m[0][2]) + (a->m[1][1] * b->m[1][2]) + (a->m[1][2] * b->m[2][2]);
    t20 = (a->m[2][0] * b->m[0][0]) + (a->m[2][1] * b->m[1][0]) + (a->m[2][2] * b->m[2][0]);
    t21 = (a->m[2][0] * b->m[0][1]) + (a->m[2][1] * b->m[1][1]) + (a->m[2][2] * b->m[2][1]);
    t22 = (a->m[2][0] * b->m[0][2]) + (a->m[2][1] * b->m[1][2]) + (a->m[2][2] * b->m[2][2]);
    t30 = (a->m[3][0] * b->m[0][0]) + (a->m[3][1] * b->m[1][0]) + (a->m[3][2] * b->m[2][0]) + b->m[3][0];
    t31 = (a->m[3][0] * b->m[0][1]) + (a->m[3][1] * b->m[1][1]) + (a->m[3][2] * b->m[2][1]) + b->m[3][1];
    t32 = (a->m[3][0] * b->m[0][2]) + (a->m[3][1] * b->m[1][2]) + (a->m[3][2] * b->m[2][2]) + b->m[3][2];
    dst->m[0][0] = t00;
    dst->m[1][0] = t10;
    dst->m[2][0] = t20;
    dst->m[3][0] = t30;
    dst->m[0][1] = t01;
    dst->m[1][1] = t11;
    dst->m[2][1] = t21;
    dst->m[3][1] = t31;
    dst->m[0][2] = t02;
    dst->m[1][2] = t12;
    dst->m[2][2] = t22;
    dst->m[3][2] = t32;
    dst->m[0][3] = 0.0f;
    dst->m[1][3] = 0.0f;
    dst->m[2][3] = 0.0f;
    dst->m[3][3] = 1.0f;
}

void mtxMulAffineF(Mat4F *a, Mat4F *b, Mat4F *dst) {
    dst->m[0][0] = (a->m[0][0] * b->m[0][0]) + (a->m[0][1] * b->m[1][0]) + (a->m[0][2] * b->m[2][0]);
    dst->m[0][1] = (a->m[0][0] * b->m[0][1]) + (a->m[0][1] * b->m[1][1]) + (a->m[0][2] * b->m[2][1]);
    dst->m[0][2] = (a->m[0][0] * b->m[0][2]) + (a->m[0][1] * b->m[1][2]) + (a->m[0][2] * b->m[2][2]);
    dst->m[1][0] = (a->m[1][0] * b->m[0][0]) + (a->m[1][1] * b->m[1][0]) + (a->m[1][2] * b->m[2][0]);
    dst->m[1][1] = (a->m[1][0] * b->m[0][1]) + (a->m[1][1] * b->m[1][1]) + (a->m[1][2] * b->m[2][1]);
    dst->m[1][2] = (a->m[1][0] * b->m[0][2]) + (a->m[1][1] * b->m[1][2]) + (a->m[1][2] * b->m[2][2]);
    dst->m[2][0] = (a->m[2][0] * b->m[0][0]) + (a->m[2][1] * b->m[1][0]) + (a->m[2][2] * b->m[2][0]);
    dst->m[2][1] = (a->m[2][0] * b->m[0][1]) + (a->m[2][1] * b->m[1][1]) + (a->m[2][2] * b->m[2][1]);
    dst->m[2][2] = (a->m[2][0] * b->m[0][2]) + (a->m[2][1] * b->m[1][2]) + (a->m[2][2] * b->m[2][2]);
    dst->m[3][0] = (a->m[3][0] * b->m[0][0]) + (a->m[3][1] * b->m[1][0]) + (a->m[3][2] * b->m[2][0]) + b->m[3][0];
    dst->m[3][1] = (a->m[3][0] * b->m[0][1]) + (a->m[3][1] * b->m[1][1]) + (a->m[3][2] * b->m[2][1]) + b->m[3][1];
    dst->m[3][2] = (a->m[3][0] * b->m[0][2]) + (a->m[3][1] * b->m[1][2]) + (a->m[3][2] * b->m[2][2]) + b->m[3][2];
    dst->m[0][3] = 0.0f;
    dst->m[1][3] = 0.0f;
    dst->m[2][3] = 0.0f;
    dst->m[3][3] = 1.0f;
}

void mtxTransformPointF(Mat4F *mf, f32 *px, f32 *py, f32 *pz) {
    f32 x = *px;
    f32 y = *py;
    f32 z = *pz;
    f32 ox = ((x * mf->m[0][0] + y * mf->m[1][0]) + z * mf->m[2][0]) + mf->m[3][0];
    f32 oy = ((x * mf->m[0][1] + y * mf->m[1][1]) + z * mf->m[2][1]) + mf->m[3][1];
    f32 oz = ((x * mf->m[0][2] + y * mf->m[1][2]) + z * mf->m[2][2]) + mf->m[3][2];
    *px = ox;
    *py = oy;
    *pz = oz;
}

void mtxRotateXRatioF(f32 mf[4][4], f32 y, f32 z, f32 dist) {
    f32 sin;
    f32 cos;

    mtxIdentityF(mf);
    cos = y / dist;
    mf[1][1] = cos;
    sin = z / dist;
    if (sin) {
    }
    mf[2][2] = cos;
    mf[1][2] = sin;
    mf[2][1] = -sin;
}

void mtxRotateYRatioF(Mat4F *mf, f32 z, f32 x, f32 dist) {
    f32 sin;
    f32 cos;

    sin = x / dist;
    cos = z / dist;
    if ((f64)x == 0.0) {
        sin = 0.0f;
    }
    if ((f64)z == 0.0) {
        cos = 0.0f;
    }
    mtxIdentityF(mf);
    mf->m[2][0] = sin;
    mf->m[0][2] = -sin;
    mf->m[0][0] = cos;
    mf->m[2][2] = cos;
}

f32 sinApprox(f32);
f32 cosApprox(f32);
void mtxRotateXRatioF(f32 mf[4][4], f32 y, f32 z, f32 dist);

void mtxIdentityF(f32 mf[4][4]);
void mtxRotateZRatioF(f32 mf[4][4], f32 x, f32 y, f32 dist);

void mtxRotateZRatioF(f32 mf[4][4], f32 x, f32 y, f32 dist) {
    f32 sin;
    f32 cos;

    mtxIdentityF(mf);
    sin = x / dist;
    cos = sin;
    mf[0][0] = cos;
    if (1) {
        sin = y / dist;
        mf[0][1] = sin;
        mf[1][0] = -sin;
    }
    mf[1][1] = cos;
}

void mtxRotateXRatioL(Mtx *m, f32 y, f32 z, f32 dist) {
    f32 mf[4][4];

    mtxRotateXRatioF(mf, y, z, dist);
    guMtxF2L(mf, m);
}

void mtxRotateYRatioL(Mtx *m, f32 z, f32 x, f32 dist) {
    f32 mf[4][4];

    mtxRotateYRatioF((Mat4F *)mf, z, x, dist);
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
    s32 index;

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
    index = 2;
    mf[0][0] = one;
    mf[1][1] = one;
    mf[2][index] = one;
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

void mtxLookDirF(Mat4F *view, Mat4F *cam, f32 dx, f32 dy, f32 dz) {
    f32 padtop[3];
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
            mtxIdentityF(view->m);
            mtxIdentityF(cam->m);
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
    view->m[0][0] = m00;
    view->m[1][0] = m10;
    view->m[2][0] = m20;
    view->m[3][0] = 0.0f;
    view->m[0][1] = 0.0f;
    view->m[1][1] = m11;
    view->m[2][1] = m21;
    view->m[3][1] = 0.0f;
    view->m[0][2] = m02;
    view->m[1][2] = m12;
    view->m[2][2] = m22;
    view->m[3][2] = 0.0f;
    view->m[0][3] = 0.0f;
    view->m[1][3] = 0.0f;
    view->m[2][3] = 0.0f;
    view->m[3][3] = 1.0f;
    cam->m[0][0] = m00;
    cam->m[1][0] = 0.0f;
    cam->m[2][0] = m02;
    cam->m[3][0] = 0.0f;
    cam->m[0][1] = m10;
    cam->m[1][1] = m11;
    cam->m[2][1] = m12;
    cam->m[3][1] = 0.0f;
    cam->m[0][2] = m20;
    cam->m[1][2] = m21;
    cam->m[2][2] = m22;
    cam->m[3][2] = 0.0f;
    cam->m[0][3] = 0.0f;
    cam->m[1][3] = 0.0f;
    cam->m[2][3] = 0.0f;
    cam->m[3][3] = 1.0f;
}

void mtxLookDirL(Mtx *view, Mtx *cam, f32 dx, f32 dy, f32 dz) {
    Mat4F viewMf;
    Mat4F camMf;

    mtxLookDirF(&viewMf, &camMf, dx, dy, dz);
    guMtxF2L(viewMf.m, view);
    guMtxF2L(camMf.m, cam);
}

void mtxLookDirPosF(Mat4F *view, Mat4F *cam, f32 dx, f32 dy, f32 dz, f32 px, f32 py, f32 pz) {
    f32 padtop[3];
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
            mtxIdentityF(view->m);
            mtxIdentityF(cam->m);
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
    view->m[0][0] = m00;
    view->m[1][0] = m10;
    view->m[2][0] = m20;
    view->m[3][0] = -px;
    view->m[0][1] = 0.0f;
    view->m[1][1] = m11;
    view->m[2][1] = m21;
    view->m[0][2] = m02;
    view->m[3][1] = -py;
    view->m[1][2] = m12;
    t = -pz;
    view->m[2][2] = m22;
    view->m[0][3] = 0.0f;
    view->m[3][2] = t;
    view->m[3][3] = 1.0f;
    view->m[1][3] = 0.0f;
    view->m[2][3] = 0.0f;
    cam->m[0][0] = m00;
    cam->m[3][0] = (px * m00) + (pz * m02);
    cam->m[1][0] = 0.0f;
    cam->m[2][0] = m02;
    cam->m[0][1] = m10;
    cam->m[1][1] = m11;
    cam->m[2][1] = m12;
    cam->m[3][1] = (px * m10) + (py * m11) + (pz * m12);
    cam->m[0][2] = m20;
    cam->m[1][2] = m21;
    cam->m[2][2] = m22;
    cam->m[0][3] = 0.0f;
    cam->m[1][3] = 0.0f;
    cam->m[3][2] = (px * m20) + (py * m21) + (pz * m22);
    cam->m[3][3] = 1.0f;
    cam->m[2][3] = 0.0f;
}

void mtxLookDirPosL(Mtx *view, Mtx *cam, f32 dx, f32 dy, f32 dz, f32 px, f32 py, f32 pz) {
    Mat4F viewMf;
    Mat4F camMf;

    mtxLookDirPosF(&viewMf, &camMf, dx, dy, dz, px, py, pz);
    guMtxF2L(viewMf.m, view);
    guMtxF2L(camMf.m, cam);
}
