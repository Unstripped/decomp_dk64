// func_80626CAC (src/global/201B0.c): stage 6: frame/size/text structure match; only regalloc differs (target hi=t0,d1=t1,d2=a3,clamped=t2,st=t3 vs mine hi=a3,d1=t0,d2=v0,clamped=t1,st=t2: d2 takes v0 in mine). Needs top prototype s16 return (was void). Tried decl order, stmt order, lo/hi locals, permuter 300s.
s16 func_80626CAC(CamState *arg0, f32 *arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5) {
    s16 ang;
    s16 mid;
    s16 a;
    s16 b;
    s16 c;
    s16 d1;
    s16 d2;
    u8 clamped;

    ang = mathAngleBetweenPoints2D(*arg1, *arg2, arg3, arg4);
    mid = arg0->unkC8 + (arg0->unkCA - arg0->unkC8) * 0.5;
    clamped = 0;
    if (arg0->unkC8 < arg0->unkCA) {
        mid = (mid + 0x800) & 0xFFF;
    }
    a = (arg0->unkC8 - mid) & 0xFFF;
    b = (arg0->unkCA - mid) & 0xFFF;
    c = (ang - mid) & 0xFFF;
    d1 = (c < a) ? a - c : c - a;
    d2 = (c < b) ? b - c : c - b;
    if (a < b) {
        if (a < c && c < b) {
            if (d1 < d2) {
                ang = arg0->unkC8;
            } else {
                ang = arg0->unkCA;
            }
            clamped = 1;
        }
    } else {
        if (c < a && b < c) {
            if (d1 < d2) {
                ang = arg0->unkC8;
            } else {
                ang = arg0->unkCA;
            }
            clamped = 1;
        }
    }
    if (arg5 < 40.0f) {
        ang = mathAngleLerp(mid, ang, arg5 / 40.0);
        D_807476A4 = arg5 / 40.0 * 0.25 + 0.05;
        if (!clamped) {
            arg5 = (arg5 > 1.0) ? 1.0 : arg5;
        }
        arg0->unkAC |= 0x80;
    }
    *arg1 = func_80612794(ang) * arg5 + arg3;
    *arg2 = func_80612790(ang) * arg5 + arg4;
    return ang;
}
