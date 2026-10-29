// func_8066B4D4 (src/global/6AD90.c): stage 5: 1 insn: then-path addu a0,t5,t4 (D_8000DDCC first) vs ours addu a0,t4,t5; numbering (and=t4,D=t5) already equal. Tried: operand/cast/pointer/named-temp spellings, dead expr stmts, u32/s16/u8 param+local types, 200 random decl orders, deadsweep 75 variants, permuter 300s: none flips operand order (uopt canonical operand order by expr ids). 80666090 shows the same reversed (var vs complex) addu order.
extern s32 D_8000DDCC;
extern s32 *D_807F9528[];
void func_8060B140(s32, void *, void *, s32, s32, s32, s32);

s32 func_8066B4D4(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    s32 pad[2];
    s32 sp44;
    s32 t;
    u64 sp38;
    s32 *table;
    s32 temp_v0;
    s32 sp2C;
    s32 var_t0;

    var_t0 = arg1;
    table = &D_807F9528[arg0][arg1];
    temp_v0 = table[0];
    if (temp_v0 & 0x80000000) {
        sp2C = 8;
        func_8060B140(D_8000DDCC + (temp_v0 & 0x7FFFFFFF), &sp38, &sp2C, 0, 0, 0, 0);
        sp44 = (s16)(sp38 >> 48);
        func_8066B4D4(arg0, sp44, arg2, arg3);
        var_t0 = sp44;
    } else {
        t = table[1] & 0x7FFFFFFF;
        *arg2 = D_8000DDCC + temp_v0;
        *arg3 = t - temp_v0;
    }
    return var_t0;
}
