// func_8062E898 (src/global/2F550.c): Stage 2-3 (NM2F3). Draft now compiles against the file: definition must be `u8 func_8062E898(void *arg0v,...)` (file prototype returns u8, takes void *); local `#define arg0 ((R2F550fPlane *)arg0v)` used for the plane. Frame 0x78 vs target 0x80, 201 vs 200 insns; target memory layout (0x18-0x24 duplicate stores, nx/ny/nz at 0x34/0x30/0x2C, p 0x40, n 0x50, c 0x5C, ea 0x68, eb 0x74) suggests struct/array vec locals copied into arg-like temps; not reproduced.
typedef struct R2F550fPlane {
    /* 0x00 */ u8 pad0[0x4C];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ s16 unk5C[3];
    /* 0x62 */ s16 unk62[3];
    /* 0x68 */ s16 unk68[3];
} R2F550fPlane;

s32 func_8062EBB8(R2F550fPlane *, f32, f32, f32);


#define arg0 ((R2F550fPlane *)arg0v)
u8 func_8062E898(void *arg0v, u8 *arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 nx;
    f32 ny;
    f32 nz;
    f32 d;
    f32 ea[3];
    f32 eb[3];
    f32 c[3];
    f32 n[3];
    f32 p[3];
    f32 len;
    f64 s1;
    f64 s2;

    *arg1 = func_8062EBB8((R2F550fPlane *)arg0v, arg2, arg3, arg4);
    d = arg0->unk58;
    nz = arg0->unk54;
    ny = arg0->unk50;
    nx = arg0->unk4C;
    ea[0] = arg0->unk5C[2] - arg0->unk5C[0];
    ea[1] = arg0->unk62[2] - arg0->unk62[0];
    ea[2] = arg0->unk68[2] - arg0->unk68[0];
    eb[0] = arg0->unk5C[1] - arg0->unk5C[0];
    eb[1] = arg0->unk62[1] - arg0->unk62[0];
    eb[2] = arg0->unk68[1] - arg0->unk68[0];
    c[0] = ea[1] * eb[2] - eb[1] * ea[2];
    c[1] = ea[2] * eb[0] - eb[2] * ea[0];
    c[2] = ea[0] * eb[1] - eb[0] * ea[1];
    len = sqrtf(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
    n[0] = c[0] / len;
    n[1] = c[1] / len;
    n[2] = c[2] / len;
    n[0] = n[0] * 20.0f;
    n[1] = n[1] * 20.0f;
    n[2] = n[2] * 20.0f;
    p[0] = n[0] + arg0->unk5C[0];
    p[1] = n[1] + arg0->unk62[0];
    p[2] = n[2] + arg0->unk68[0];
    s1 = nx * arg2 + ny * arg3 + nz * arg4 + d;
    s2 = nx * p[0] + ny * p[1] + nz * p[2] + d;
    if (s1 > 0.0 && s2 > 0.0) {
        return 0;
    }
    if (s1 < 0.0 && s2 < 0.0) {
        return 0;
    }
    return 1;
}
#undef arg0
