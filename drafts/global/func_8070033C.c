// func_8070033C (src/global/103AB0.c): Stage 3: compiled behavioral vector and trail-record reconstruction; frame and vector ABI remain divergent.
typedef struct {
    u8 unk0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    f32 unk21C;
    f32 unk220;
    f32 unk224;
} R2F103AB0dPlayerView;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s32 unkC;
} R2F103AB0dTrailPoint;

extern u8 D_80754BC0;
extern R2F103AB0dTrailPoint D_807FD808[2];
extern f32 D_807FD840[2][3][3];
extern f32 D_807FD848[2][3][3];
extern s32 D_807444FC;
#define R2F103AB0dPlayer ((R2F103AB0dPlayerView *)D_807FC924)

void func_80612970(f32 *, f32, f32, f32);
void func_80626F8C(f32, f32, f32, f32 *, f32 *, s32, f32, s32);

void func_8070033C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, u8 arg8, u8 arg9) {
    f32 sp84;
    f32 sp80;
    u8 sp7F;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 temp_fv1;
    u8 var_v1;

    if (D_80754BC0 < 2) {
        var_v1 = 1;
        if (arg6 != 0.0f) {
            sp70 = arg3 - arg0;
            sp74 = arg4 - arg1;
            sp78 = arg5 - arg2;
            sp7F = 1;
            func_80612970(&sp58, sp70, sp74, sp78);
            sp70 = R2F103AB0dPlayer->unk210 - arg0;
            sp74 = R2F103AB0dPlayer->unk214 - arg1;
            sp78 = R2F103AB0dPlayer->unk218 - arg2;
            func_80612970(&sp64, sp70, sp74, sp78);
            var_v1 = sp7F;
            temp_fv1 = (sp64 * sp58) + (sp68 * sp5C) + (sp6C * sp60);
            if ((f64)temp_fv1 < 0.0) {
                temp_fv1 = 0.0f;
            }
            if (temp_fv1 < arg6) {
                var_v1 = 0;
            }
        }
        if (var_v1 != 0) {
            sp70 = R2F103AB0dPlayer->unk21C - arg0;
            sp74 = R2F103AB0dPlayer->unk220 - arg1;
            sp78 = R2F103AB0dPlayer->unk224 - arg2;
            D_807FD848[D_807444FC][D_80754BC0][0] = sqrtf((sp78 * sp78) + ((sp70 * sp70) + (sp74 * sp74)));
            if (D_807FD848[D_807444FC][D_80754BC0][0] > 995.0f) {
                D_807FD848[D_807444FC][D_80754BC0][0] = 995.0f;
            }
            func_80626F8C(arg0, arg1, arg2, &sp84, &sp80, 0, 4.0f, 0);
            D_807FD840[D_807444FC][D_80754BC0][0] = (f32)((f64)sp84 * 0.25);
            D_807FD840[D_807444FC][D_80754BC0][1] = (f32)((f64)sp80 * 0.25);
            D_807FD808[D_80754BC0].unk0 = arg0;
            D_807FD808[D_80754BC0].unk4 = arg1;
            D_807FD808[D_80754BC0].unk8 = arg2;
            D_807FD808[D_80754BC0].unkC = arg7 | (arg8 << 8) | (arg9 << 0x10);
            D_80754BC0 += 1;
        }
    }
}
