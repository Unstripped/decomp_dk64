// func_800258B0 (src/critter/0.c): stage 5: text same size/frame as target; diff ~22 lines: zero const lands in $f14 (target $f18; temp_fa1 gets $f18 instead of $f14) and 2-3 zero swc1 stores/mtc1 at,$f4 scheduled differently. Needs s16 params (s32+casts gives frame 0x58); src prototype in file is s32 so def would need K&R/prototype change. Tried chain m[0][3]=m[1][3]=m[2][3]=0, zero positions search, inline fa1, nv=0 index tricks, permuter (best 251).
f32 func_80612790(s32);

void func_800258B0(f32 (*m)[4], s16 arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 temp_fa1;
    f32 temp_fa1_2;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fv0;

    temp_fs0 = func_80612794(arg1);
    temp_fs1 = func_80612790(arg1);
    sp40 = func_80612794(arg2);
    sp34 = func_80612790(arg2);
    sp3C = func_80612794(arg3);
    temp_fv0 = func_80612790(arg3);
    m[0][0] = sp34 * temp_fv0 * arg4;
    m[0][1] = sp34 * sp3C * arg4;
    m[0][3] = 0.0f;
    m[0][2] = -sp40 * arg4;
    m[1][3] = 0.0f;
    temp_fa1 = temp_fs0 * sp40;
    m[1][0] = ((temp_fa1 * temp_fv0) - (temp_fs1 * sp3C)) * arg4;
    m[1][1] = ((temp_fa1 * sp3C) + (temp_fs1 * temp_fv0)) * arg4;
    m[1][2] = temp_fs0 * sp34 * arg4;
    m[2][3] = 0.0f;
    temp_fa1_2 = temp_fs1 * sp40;
    m[2][0] = ((temp_fa1_2 * temp_fv0) + (temp_fs0 * sp3C)) * arg4;
    m[2][1] = ((temp_fa1_2 * sp3C) - (temp_fs0 * temp_fv0)) * arg4;
    m[2][2] = temp_fs1 * sp34 * arg4;
    m[3][0] = arg5;
    m[3][1] = arg6;
    m[3][3] = 1.0f;
    m[3][2] = arg7;
}
