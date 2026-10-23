// func_80690AB0 (src/global/936B0.c): 1 delay-slot insn: sh v0,0x40(sp) in jal delay slot
s16 func_80665DE0(f32, f32, f32, f32);
s32 func_806CC14C(s16, s16);
void func_80690930(s16, s16, s16, f32, f32, f32, f32, f32, s32);
extern f32 D_807FC7B0;
extern f32 D_807FC7B8;

void func_80690AB0(s16 arg0, s16 arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, s32 arg9) {
    s16 sp3C;
    s16 sp38;
    s16 var_s0;
    s16 sp40;

    var_s0 = func_80665DE0(arg5, arg7, D_807FC7B0, D_807FC7B8);
    if (arg1 < func_806CC14C(arg0, var_s0)) {
        sp3C = (arg0 - arg1) & 0xFFF;
        sp38 = (arg0 + arg1) & 0xFFF;
        sp40 = func_806CC14C(var_s0, sp3C);
        if (sp40 < func_806CC14C(var_s0, sp38)) {
            var_s0 = sp3C;
        } else {
            var_s0 = sp38;
        }
    }
    func_80690930(var_s0, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}
