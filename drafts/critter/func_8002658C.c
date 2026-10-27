// func_8002658C (src/critter/0.c): stage 5: frame 0x78 + all stack slots match; remaining: tx/tz reloaded from home (lwc1 0x74/0x6c(sp)) in target but kept in f10/f4 in ours; arg0->0x28 reloaded after store (lwc1 0x28(s0)) in target but forwarded; float regs numbering after that. Tricks: u8-narrow flag as s32 with (u8) casts at uses, rate=0.02f before flag, extra locals ty,dxz,ret,ang + use_y declared last
extern f32 sqrtf(f32);
f32 func_80611BB4(f32, f32);
f32 func_80612790(s16);
f32 func_80612800(s16);
s16 func_806CC190(s16, s16, s32);
s16 mathAngleDiscrete(f32, f32, f32, f32, f32);

void func_8002658C(u8 *arg0, void *arg1, s32 arg2, void *arg3) {
    f32 tx;
    f32 ty;
    f32 tz;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 dxz;
    f32 d2;
    f32 old;
    f32 tgt;
    f32 spd;
    f32 rate;
    s16 *off;
    s32 ret;
    s16 ang;
    s32 use_y;

    rate = 0.02f;
    use_y = (arg0[0x1E1] & 2) == 0;
    if (arg2 != 0) {
        ((void (*)(u8 *, void *))arg2)(arg0, arg1);
    }
    off = *(s16 **)(arg0 + 0x54);
    tx = *(f32 *)(arg0 + 0x18) + (f32)off[0];
    ty = *(f32 *)(arg0 + 0x1C) + (f32)off[1];
    tz = *(f32 *)(arg0 + 0x20) + (f32)off[2];
    dx = tx - *(f32 *)(arg0 + 8);
    dy = ty - *(f32 *)(arg0 + 0xC);
    dz = tz - *(f32 *)(arg0 + 0x10);
    if (arg0[0x1E2] != 2) {
        dxz = dx * dx + dz * dz;
        d2 = dxz;
        if ((u8)use_y) {
            d2 = dxz + dy * dy;
        }
        tgt = *(f32 *)(arg0 + 0x34);
        if (d2 < 2500.0f) {
            tgt = (f32)((f64)tgt * 0.3 + 0.7 * (f64)tgt * (f64)(d2 * 0.0004f));
            rate = 0.1f;
            if (d2 < 25.0f && arg3 != NULL) {
                ret = ((s32 (*)(u8 *, void *))arg3)(arg0, arg1);
                if (ret != 0) {
                    return;
                }
            }
        }
        old = *(f32 *)(arg0 + 0x28);
        *(f32 *)(arg0 + 0x28) = old + (tgt - old) * rate;
        *(f32 *)(arg0 + 0x30) = *(f32 *)(arg0 + 0x28) - old;
    }
    dist = sqrtf(dx * dx + dz * dz);
    if ((u8)use_y) {
        *(s16 *)(arg0 + 2) = func_806CC190(*(s16 *)(arg0 + 2), (s16)(s32)(((f64)func_80611BB4(dy, dist) * 2048.0) / 3.1415927410125732), *(s32 *)(arg0 + 0x24));
    }
    ang = mathAngleDiscrete(tx, tz, *(f32 *)(arg0 + 8), *(f32 *)(arg0 + 0x10), dist);
    *(s16 *)(arg0 + 4) = *(s16 *)(arg0 + 0);
    *(s16 *)(arg0 + 0) = func_806CC190(*(s16 *)(arg0 + 0), ang, *(s32 *)(arg0 + 0x24));
    spd = *(f32 *)(arg0 + 0x28);
    *(f32 *)(arg0 + 8) = spd * func_80612794(*(s16 *)(arg0 + 0)) + *(f32 *)(arg0 + 8);
    *(f32 *)(arg0 + 0x10) = spd * func_80612790(*(s16 *)(arg0 + 0)) + *(f32 *)(arg0 + 0x10);
    if ((u8)use_y) {
        *(f32 *)(arg0 + 0xC) = spd * func_80612800(*(s16 *)(arg0 + 2)) + *(f32 *)(arg0 + 0xC);
    }
}
