// func_8066D2F4 (src/global/70FD0.c): near miss: cross-product regalloc; 3-vector layout matches stack frame 0x48 exactly
f32 func_80611BB4(f32, f32);

s8 func_8066D2F4(CollisionTri *arg0) {
    f32 v2[3];
    f32 v1[3];
    f32 cross[3];
    f32 len;
    f32 angle;
    f32 temp;
    s32 ret;

    v2[0] = arg0->unkC - arg0->unk0;
    v2[1] = arg0->unkE - arg0->unk2;
    v2[2] = arg0->unk10 - arg0->unk4;
    v1[0] = arg0->unk6 - arg0->unk0;
    v1[1] = arg0->unk8 - arg0->unk2;
    v1[2] = arg0->unkA - arg0->unk4;
    cross[0] = (v2[1] * v1[2]) - (v1[1] * v2[2]);
    cross[1] = (v2[2] * v1[0]) - (v1[2] * v2[0]);
    cross[2] = (v2[0] * v1[1]) - (v1[0] * v2[1]);

    len = sqrtf((cross[2] * cross[2]) + (cross[0] * cross[0]));
    if (((f64)len < 0.01) && ((f64)len > -0.01)) {
        angle = 1.57f;
    } else {
        temp = -cross[1];
        if (0.0f < cross[1]) {
            temp = cross[1];
        }
        angle = func_80611BB4(temp, len);
    }

    if ((f64)(f32)((f64)angle * 57.29577791868205) < 10.0) {
        return 1;
    }
    ret = 0;
    if ((f64)(f32)((f64)angle * 57.29577791868205) < 45.0) {
        ret = 2;
    }
    return ret;
}
