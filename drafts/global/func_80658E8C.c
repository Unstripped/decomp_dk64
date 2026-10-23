// func_80658E8C (src/global/55B20.c): frame/slots/signature/branch layout all match; remaining: 3 ramp mul.s operand order, one extra b in target, temp colours
// func_80658E8C: frame 0x48, every stack slot (sp40/sp44 at 0x40/0x44, x/z at 0x3E/0x3C),
// the 5-param signature (u8 arg3 for the x bounds, u8 arg4 read from the caller's stack
// slot for the z bounds), the sqrtf sum association z^2 + (x^2 + y^2), the shared-return-1
// OR-ed rectangle test and the `if (d >= 180.0f) z1 = 50; else <ramp>` branch layout all
// match. Remaining: the three ramp mul.s keep the constant as the left operand in the
// target (IDO emits t*const here), the target has one extra `b` before the final
// `sra a2,t5,0x10` of the ramp, and a few temp-register colours (t5/t6 vs t6/t7).
typedef struct R3dPos {
    /* 0x000 */ u8 pad0[0x21C];
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
} R3dPos;

void func_80626F8C(f32, f32, f32, f32 *, f32 *, s32, f32, s32);
f32 sqrtf(f32);

typedef struct R3dPos {
    /* 0x000 */ u8 pad0[0x21C];
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
} R3dPos;

void func_80626F8C(f32, f32, f32, f32 *, f32 *, s32, f32, s32);
f32 sqrtf(f32);

s32 func_80658E8C(f32 arg0, f32 arg1, f32 arg2, u8 arg3, u8 arg4) {
    f32 sp44;
    f32 sp40;
    s16 x;
    s16 z;
    s16 x0;
    s16 x1;
    s16 z0;
    s16 z1;
    f32 d;

    func_80626F8C(arg0, arg1, arg2, &sp44, &sp40, 0, 1.0f, D_807FC929);
    x = (s16)sp44;
    z = (s16)sp40;
    d = sqrtf(((arg2 - ((R3dPos *)&D_807FC924[D_807FC929])->unk224) * (arg2 - ((R3dPos *)&D_807FC924[D_807FC929])->unk224))
            + (((arg0 - ((R3dPos *)&D_807FC924[D_807FC929])->unk21C) * (arg0 - ((R3dPos *)&D_807FC924[D_807FC929])->unk21C))
            + ((arg1 - ((R3dPos *)&D_807FC924[D_807FC929])->unk220) * (arg1 - ((R3dPos *)&D_807FC924[D_807FC929])->unk220))));
    if (d < 90.0f) {
        return 0;
    }
    x0 = 20;
    x1 = 20;
    z0 = 0;
    if (d >= 180.0f) {
        z1 = 50;
    } else {
        x0 = 80;
        x1 = 80;
        z0 = 130;
        z1 = 130;
        if ((d - 60.0f) / 120.0f > 0.0) {
            x0 = -60.0f * ((d - 60.0f) / 120.0f) + 80.0f;
            x1 = -60.0f * ((d - 60.0f) / 120.0f) + 80.0f;
            z0 = -130.0f * ((d - 60.0f) / 120.0f) + 130.0f;
            z1 = -80.0f * ((d - 60.0f) / 120.0f) + 130.0f;
        }
    }
    if ((x < D_807F7358 - x0 - arg3) || (D_807F735C + x1 + arg3 < x)
        || (z < D_807F735A - z0 - arg4) || (D_807F735E + z1 + arg4 < z)) {
        return 1;
    }
    return 0;
}
