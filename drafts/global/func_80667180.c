// func_80667180 (src/global/699B0.c): regalloc in case 3: cvt.s.d into f0 vs f8 (6 diffs)
s32 func_80666FC8(f32, f32, f32, s32);
s32 func_806672B8(f32, f32, f32 *, s32);
u8 func_806679BC(f32, f32, f32 *);
extern u8 D_807F94B6;

u8 func_80667180(f32 arg0, f32 arg1, f32 *arg2, s32 arg3) {
    u8 sp3F;
    f32 sp38;
    f32 sp34;
    s32 dummy;
    u8 sp2E;
    u8 val;
    s32 var_v1;

    sp38 = *arg2;
    sp3F = func_806679BC(arg0, arg1, &sp38);
    sp34 = *arg2;
    val = func_806672B8(arg0, arg1, &sp34, arg3) * 2;
    val += sp3F;
    switch (val) {
    case 0:
        break;
    case 1:
        *arg2 = sp38;
        break;
    case 2:
        *arg2 = sp34;
        D_807F94B6 = 1;
        break;
    case 3:
        sp2E = val;
        if (func_80666FC8(sp38, sp34, (f32)((f64)*arg2 + 4.0), 0) != 0) {
            *arg2 = sp34;
            D_807F94B6 = 1;
        } else {
            *arg2 = sp38;
        }
        break;
    }
    if (val != 0) {
        var_v1 = 1;
    } else {
        var_v1 = 0;
    }
    return var_v1;
}
